# T6 Mode 0x13 Programming Guide

Reading Diagnostic Trouble Codes over CAN (ISO-TP / OBD-II) from the Lotus T6e engine ECU.

## 1. Overview

Mode `0x13` is a **proprietary, non-standard OBD-II service** implemented in the Lotus / EFI
Technology "T6e" engine ECU (Freescale MPC5534, FlexCAN). Unlike the standard, mandatory Mode
`0x03` ("request emission-related DTCs"), Mode `0x13` aggregates **three** DTC populations into a
single response:

1. **Current** DTCs (active / pending faults),
2. **Confirmed** DTCs (stored, MIL-triggering faults),
3. **TPMS** DTCs (retrieved live from the tyre-pressure module over vehicle CAN).

The response is one flat list of 2-byte DTC codes. This makes Mode `0x13` ideal for a scan tool
that wants a fast "dump every fault the ECU knows about" query in a single round-trip — including
faults the standard services do not expose.

> This document describes the wire protocol as reverse-engineered from firmware `B13200091`
> (2011 Evora NA). The same service exists across the T6e family (E132E0288, C132E0278,
> C132E0271); the TPMS segment is gated by the vehicle's TPMS configuration (see §7).

---

## 2. Protocol Stack

```
+---------------------+
|   Application       |   Mode 0x13 request / response payload
+---------------------+
|   ISO-TP (15765-2)  |   Segmentation of >7-byte responses
+---------------------+
|   CAN 2.0B          |   11-bit IDs, 500 kbit/s
+---------------------+
```

Diagnostics use ISO 15765-2 (ISO-TP) framing over normal fixed addressing (ISO 15765-4), on an
11-bit (standard) CAN network at 500 kbit/s.

---

## 3. CAN Addressing

| CAN ID | Direction        | Meaning                       |
|--------|------------------|-------------------------------|
| `0x7E0`| Tester → ECU     | Physical request (engine ECU) |
| `0x7DF`| Tester → ECU     | Functional request (all ECUs) |
| `0x7E8`| ECU → Tester     | Engine ECU response           |

- **Physical (`0x7E0`)** — use for a single-ECU scan tool.
- **Functional (`0x7DF`)** — the ECU does **not** suppress its reply on functional requests; it
  always answers on `0x7E8` (it does not use the `0x7E9+` functional-response convention).
- The flow-control frame (see §5.3) is sent by the tester back to the request ID you used
  (`0x7E0` or `0x7DF`).

---

## 4. Request

Mode `0x13` accepts a **single-frame** ISO-TP request. Two forms are valid; both produce the same
full response.

**Form A — bare service:**

```
CAN data:  01 13 00 00 00 00 00 00
           ^  ^
           |  SID = 0x13
           ISO-TP SF PCI = 0x01 (1 data byte)
```

**Form B — "report all" sub-function (recommended, explicit):**

```
CAN data:  03 13 FF 00 00 00 00 00
           ^  ^  ^  ^
           |  |  |  padding (ignored)
           |  |  sub-function = 0xFF00 (read all DTCs)
           |  SID = 0x13
           ISO-TP SF PCI = 0x03 (3 data bytes)
```

Internally the ECU copies the 8 raw CAN data bytes into `obd_req[0..7]` and matches:

- `obd_req[0] == 1` (bare), **or**
- `obd_req[0] == 3 && obd_req[2] == 0xFF && obd_req[3] == 0x00` (read-all)

where `obd_req[0]` is the ISO-TP PCI byte and `obd_req[1]` is the SID.

> **Use Form B.** It is unambiguous and future-proof; some scan-tool frameworks expect an explicit
> sub-function. Form A is provided for compatibility with the bare service request.

> **No multi-frame request is supported.** The ECU reads the 8 receive-buffer bytes directly and
> performs no request reassembly, so keep the request within one frame (≤ 7 payload bytes).

---

## 5. Response

### 5.1 Payload layout

```
Byte 0         response SID = 0x53  (= 0x13 + 0x40)
Byte 1..2      DTC #1   (big-endian, high byte first)
Byte 3..4      DTC #2
  ...
Byte 2N-1..2N  DTC #N
```

The payload is the response SID followed by a **flat, contiguous** list of 2-byte DTC codes. The
ECU appends, in order:

1. `obd_DTC_current[]` — current DTCs,
2. `obd_DTC_confirmed[]` — confirmed DTCs,
3. TPMS DTCs — only if TPMS is configured (see §7).

The total is capped at 128 internal bytes, i.e. **127 payload bytes = 63 DTC codes**. The response
length (`obd_resp_length`) counts the SID byte.

> **There is no per-group count byte** (unlike standard Mode `0x03`, which emits a DTC count in the
> second byte). On the wire the reader **cannot** tell which group a code came from — treat the
> result as an unsorted set and de-duplicate if necessary.

### 5.2 Single frame (payload ≤ 7 bytes)

If `obd_resp_length < 8` the ECU emits one CAN frame:

```
CAN data:  <len> <payload[0..len-1]> <0x00 padding to 8 bytes>
```

Example — two codes (5-byte payload): `05 53 03 01 04 20 00 00`.

### 5.3 Multi-frame + flow control (payload ≥ 8 bytes)

If `obd_resp_length ≥ 8` the ECU uses ISO-TP multi-frame.

**First frame (FF):**

```
data[0] = 0x10 | (length >> 8)        // length ≤ 127 ⇒ always 0x10 here
data[1] = length & 0xFF               // full payload length
data[2..7] = payload[0..5]            // first 6 payload bytes
```

**The tester MUST respond with a Flow Control (FC) frame** on the request ID, or the transfer
halts:

```
CAN data:  30 BS ST 00 00 00 00 00
           ^  ^  ^
           |  |  STmin      (0x00 = no separation time)
           |  BlockSize    (0x00 = send all without further FC)
           PCI 0x30 = Clear To Send
```

The ECU parses the FC as `flow_status = data[0] & 0xF`, `block_size = data[1]`, `stmin = data[2]`,
and honours:

- `BlockSize = 0x00` → transmit all consecutive frames without a further FC,
- `STmin = 0x00` → no minimum separation between frames,
- `flow_status` `0x01` (Wait) and `0x02` (Abort) are also honoured.

> **This is the single most common integration failure.** Without the FC frame the ECU will not
> send the consecutive frames and the read will hang. Always send `30 00 00` immediately after the
> first frame.

**Consecutive frames (CF):**

```
data[0] = 0x20 | (seq & 0x0F)         // sequence number 0..15, wrapping
data[1..7] = next 7 payload bytes     // final CF zero-padded to 7
```

The ECU sends 7 payload bytes per CF (the final frame zero-padded), using ISO-TP sequence numbers
`0..15` that wrap around as needed.

---

## 6. DTC Code Encoding

Each DTC is a 2-byte value in the standard ISO 15031-6 / SAE J2012 encoding, transmitted
**big-endian** (high byte first).

```
High byte:   bits 7-6   letter   00=P, 01=C, 10=B, 11=U
             bits 5-4   digit 1  (0..3)
             bits 3-0   digit 2  (hex)
Low byte:    bits 7-4   digit 3  (hex)
             bits 3-0   digit 4  (hex)
```

Decode (C):

```c
static const char LETTER[4] = {'P','C','B','U'};

void decode_dtc(uint16_t code, char out[6]) {
    out[0] = LETTER[(code >> 14) & 3];
    out[1] = '0' + ((code >> 12) & 3);          // digit 1
    out[2] = "0123456789ABCDEF"[(code >> 8) & 0xF];  // digit 2
    out[3] = "0123456789ABCDEF"[(code >> 4) & 0xF];  // digit 3
    out[4] = "0123456789ABCDEF"[ code        & 0xF]; // digit 4
    out[5] = '\0';
}
```

Encode (C):

```c
uint16_t encode_dtc(char letter, int d1, int d2, int d3, int d4) {
    int l = (letter == 'C') ? 1 : (letter == 'B') ? 2 : (letter == 'U') ? 3 : 0;
    return (uint16_t)((l << 14) | (d1 << 12) | (d2 << 8) | (d3 << 4) | d4);
}
// P0301 = encode_dtc('P',0,3,0,1) = 0x0301
// P0420 = encode_dtc('P',0,4,2,0) = 0x0420
```

---

## 7. TPMS Handshake and Timing

If the vehicle is TPMS-equipped (configuration bit `COD[1] bit 13` set) and the ECU is not in
high-speed-logger mode, Mode `0x13` first interrogates the TPMS module over vehicle CAN:

1. ECU sends a TPMS request (`0x220`) on FlexCAN C.
2. TPMS module replies (`0x256`) with a header plus up to 5 × 2-byte DTC codes.
3. ECU merges those codes into the Mode `0x13` response.

The whole query runs in the ECU's 200 Hz (5 ms) task. The TPMS wait is **8 ticks ≈ 40 ms**; if the
TPMS module does not answer in that window the ECU times out and proceeds without TPMS codes
(setting an internal timeout flag).

### Timeout guidance for the scan tool

- **P2** (request → first response frame): allow **≥ 100 ms**. With TPMS absent/prompt the ECU
  answers within one 5 ms tick, but the TPMS handshake can delay the first response to ~40 ms, so
  the OBD-II default of 50 ms is too tight on TPMS-equipped cars.
- **P2\*** (extended): a few seconds is safe. Mode `0x13` never needs it, but a robust
  implementation should have a generous upper bound.
- **Flow-control window**: send the FC frame within ~10 ms of receiving the first frame.

---

## 8. Complete Worked Examples

Request (physical, read-all):

```
CAN 0x7E0:  03 13 FF 00 00 00 00 00
```

**Example 1** — two current DTCs (`P0301`, `P0420`), none confirmed, TPMS absent:

```
payload (5 bytes): 53 03 01 04 20
CAN 0x7E8 (SF):    05 53 03 01 04 20 00 00
```

**Example 2** — three DTCs (`P0301`, `P0302`, `P0420`), 7-byte payload → still single frame:

```
payload (7 bytes): 53 03 01 03 02 04 20
CAN 0x7E8 (SF):    07 53 03 01 03 02 04 20
```

**Example 3** — four DTCs (`P0301`, `P0302`, `P0420`, `P0500`), 9-byte payload → multi-frame:

```
payload (9 bytes): 53 03 01 03 02 04 20 05 00

CAN 0x7E8 (FF):    10 09 53 03 01 03 02 04
tester → 0x7E0:    30 00 00 00 00 00 00 00
CAN 0x7E8 (CF):    21 20 05 00 00 00 00 00
```

---

## 9. Reference Implementation

```python
DTC_LETTER = {0: 'P', 1: 'C', 2: 'B', 3: 'U'}
HEX = "0123456789ABCDEF"


def decode_dtc(code: int) -> str:
    return (DTC_LETTER[(code >> 14) & 3] +
            str((code >> 12) & 3) +
            HEX[(code >> 8) & 0xF] +
            HEX[(code >> 4) & 0xF] +
            HEX[code & 0xF])


def read_mode13(can_tx, can_rx) -> list[str]:
    # 1. Send single-frame "read all" request (physical addressing).
    can_tx.send(0x7E0, [0x03, 0x13, 0xFF, 0x00, 0, 0, 0, 0])

    # 2. Wait for the first response frame (P2 = 100 ms).
    data = can_rx.recv(0x7E8, timeout=0.100)
    pci = data[0] & 0xF0

    if pci == 0x00:                       # single frame
        length = data[0] & 0x0F
        payload = bytes(data[1:1 + length])
    elif pci == 0x10:                     # first frame
        length = ((data[0] & 0x0F) << 8) | data[1]
        payload = bytearray(data[2:8])
        can_tx.send(0x7E0, [0x30, 0x00, 0x00, 0, 0, 0, 0, 0])   # flow control
        while len(payload) < length:
            cf = can_rx.recv(0x7E8, timeout=0.100)
            payload += cf[1:8]
        payload = bytes(payload[:length])
    else:
        raise ProtocolError(f"unexpected PCI 0x{pci:02X}")

    # 3. Strip the response SID and decode big-endian 2-byte codes.
    assert payload[0] == 0x53
    dtc_bytes = payload[1:]
    codes = [int.from_bytes(dtc_bytes[i:i + 2], 'big')
             for i in range(0, len(dtc_bytes), 2)]
    return [decode_dtc(c) for c in codes]
```

---

## 10. Gotchas

- **Always send flow control** for any response ≥ 8 bytes, or the read hangs.
- **No count bytes** — the response is a flat list; current / confirmed / TPMS codes are not
  separable on the wire.
- **Big-endian** DTC codes — high byte first.
- **Functional requests (`0x7DF`) are answered** on `0x7E8` — no response suppression.
- **Response length cap** = 63 codes (127 payload bytes); excess codes are silently truncated.
- **TPMS presence is vehicle-config-dependent**; on non-TPMS cars that segment is simply absent
  (the response is current + confirmed only).
- **Only single-frame requests** are accepted — do not attempt a multi-frame request.

---

## 11. References

Firmware: `disassembly/evora/B13200091/B13200091.c`

- `obd_ii_send_mode13_data()` — response assembly (runs in the 200 Hz task),
- `obd_ii_processing()` — request dispatch + flow-control parsing,
- `flexcan_a_obd_send_messages()` — ISO-TP single/multi-frame transmit,
- `obd_ii_dtc_format()` / `obd_ii_dtc_unpack()` — DTC code encoding,
- `tpms_module_send_command()` + the `0x256` RX handler — TPMS handshake.

Standards: ISO 15765-2 (ISO-TP), ISO 15765-4 (OBD-II on CAN), ISO 15031-6 / SAE J2012 (DTC
definitions).
