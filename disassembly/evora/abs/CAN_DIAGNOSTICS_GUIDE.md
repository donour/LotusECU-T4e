# Bosch ESP8 ABS — CAN Diagnostics & Programming Guide

## Lotus Evora (BB68638 V0201 / A132J0314A)

This guide covers diagnostic communication with the Bosch ESP8 ABS/ESP module
over CAN bus using **KWP2000 (ISO 14230)** over **ISO-TP (ISO 15765-2)**.

**Module:** Bosch ESP8.1 ABS — Texas Instruments TMS470 (ARM7TDMI, big-endian), ERCOSEK RTOS.  
**This is the ABS/ESP module only** — not the engine ECU. The ECU is a separate
module (EFI Technology, MPC5534) on the same CAN bus but uses different diagnostic
CAN IDs (engine = 0x7E0/0x7E8, ABS = 0x6F4/0x6F5 per ISO 15765-4).

---

## 1. Hardware Setup

### CAN Bus Connection

| Parameter | Value |
|-----------|-------|
| Bus speed | 500 kbps |
| Diagnostic CAN IDs (ABS) | **0x6F4** (tester → ABS), **0x6F5** (ABS → tester) |
| Diagnostic CAN IDs (functional) | **0x7DF** (broadcast — all modules listen) |
| Transport | ISO-TP (ISO 15765-2) — CAN multi-frame |
| Protocol | KWP2000 (ISO 14230) — normal addressing mode |
| Addressing | 11-bit CAN IDs |

### Diagnostic CAN ID Assignment

| Module | Request ID | Response ID |
|--------|-----------|-------------|
| Engine ECU | 0x7E0 | 0x7E8 |
| **ABS / ESP (this module)** | **0x6F4** | **0x6F5** |
| Functional (all modules) | 0x7DF | — |

> **Confirmed on vehicle.** The ABS does NOT use ISO 15765-4 standard IDs.
> It uses proprietary CAN IDs 0x6F4/0x6F5 configured at build time by the
> ERCOSEK COM stack. The engine ECU uses standard 0x7E0/0x7E8.

### Tools

Any CAN interface supporting 500 kbps with ISO-TP support:

| Tool | Software | Notes |
|------|----------|-------|
| **SocketCAN** (Linux) | `can-utils` + kernel `can-isotp` | Recommended — fully scriptable |
| **PCAN-USB** | Peak PCAN-View / PCAN-ISO-TP API | Windows; good debugging GUI |
| **Macchina M2 / A0** | SavvyCAN / SocketCAN (via GVRET) | Low-cost alternative |
| **Tactrix OpenPort 2.0** | J2534 driver + custom software | Reprogramming capable |
| **Arduino + MCP2515** | Custom firmware + ISO-TP library | Hobbyist option |

### OBD-II Pinout

| Pin | Signal | Usage |
|-----|--------|-------|
| 6 | CAN High (CAN-H) | Primary CAN bus |
| 14 | CAN Low (CAN-L) | Primary CAN bus |
| 4 | Chassis Ground | Ground reference |
| 5 | Signal Ground | Signal reference |
| 16 | Battery +12V | Power (if needed) |

The ABS module is on the same CAN bus as the ECU — no gateway between them.

---

## 2. ISO-TP Transport Layer

KWP2000 messages can exceed the 8-byte CAN frame. ISO-TP (ISO 15765-2)
fragments and reassembles them.

### Frame Types

| Type | PCI Byte | Payload | When Used |
|------|----------|---------|-----------|
| Single Frame (SF) | `0x0N` — N = payload length (0–7) | N bytes | Message fits in one CAN frame |
| First Frame (FF) | `0x1N` — N = length high nibble (4 bits) | 6 bytes + 1 length byte | Message > 7 bytes |
| Consecutive Frame (CF) | `0x2N` — N = sequence number (0–15, wraps) | 7 bytes | Follows FF after flow control |
| Flow Control (FC) | `0x30 00 00 00 00 00 00 00` | — | Receiver says "keep sending" |

### Multi-Frame Example

```
→ Tester sends ReadEcuIdentification (20-byte request doesn't fit in SF):
  0x6F4  10 14  1A 87 FF FF FF FF    (FF: total length = 0x014 = 20 bytes)
  0x6F5  30 00 00 00 00 00 00 00    (FC: clear to send, no block size limit)
  0x6F4  21  xx xx xx xx xx xx xx    (CF seq=1, bytes 7–13 of payload)
  0x6F4  22  xx xx xx xx xx xx xx    (CF seq=2, bytes 14–20 of payload)

← ABS responds (response also multi-frame if >7 bytes):
  0x6F5  10 2A  5A 87 01 42 42 36    (FF: total length = 0x02A = 42 bytes)
  0x6F4  30 00 00 00 00 00 00 00    (FC: tester grants send)
  0x6F5  21  xx xx xx xx xx xx xx    (CF seq=1)
  0x6F5  22  xx xx xx xx xx xx xx    (CF seq=2)
  ...etc...
```

### Timing Parameters

| Parameter | Value | Notes |
|-----------|-------|-------|
| P2can | 25 ms | Module response time on CAN |
| P2\*can | 2500 ms | Extended response (NRC 0x78 pending) |
| STmin | 5 ms | Minimum separation between consecutive frames |
| Block size | 0 (unlimited) | No flow control blocking |

**Implementation note:** After sending a First Frame, wait for the Flow Control
frame before sending Consecutive Frames. If no FC arrives within 25 ms, retry
or check bus connection. The module sends NRC 0x78 (responsePending) if it needs
more than P2can to process — wait for the final response.

---

## 3. Session Management

### Supported Sessions

| Session | Byte | Description |
|---------|------|-------------|
| Default | 0x01 | Power-on state; read services, DTC operations |
| Programming | 0x02 | Flash reprogramming; SecurityAccess available here |
| Extended | 0x03 | Configuration changes; WriteDataByLocalId allowed |

### Entering a Session

```
→ 02 10 02              (StartDiagnosticSession, programmingSession)
← 06 50 02 00 32 00 C8  (positive response: session=0x02, P2 timing params)
```

The P2 timing parameters in the response (bytes 3–6) encode the module's
supported timing: `00 32` = P2can = 50 ms, `00 C8` = P2*can = 200 ms. These
may vary by firmware version — use the values from the response, not hardcoded
defaults.

### Session Keep-Alive

The session times out after **~5 seconds of inactivity**. Send TesterPresent
periodically (every 2–3 seconds):

```
→ 02 3E 00              (TesterPresent, require response)
← 02 7E 00              (positive response)

→ 02 3E 80              (TesterPresent, suppress response — reduces bus load)
                        (no response sent)
```

### Session State Diagram

```
              Power-On / ECU Reset
                     │
                     ▼
             ┌───────────────┐
             │  Default (0x01)│  ← always available
             └──────┬────────┘
                    │ 10 02
                    ▼
             ┌───────────────┐
             │ Programming   │  ← SecurityAccess available
             │ Session (0x02)│
             └──┬─────┬──────┘
   10 03        │     │  10 01 / 10 02
    ┌───────────┘     └──────────┐
    ▼                            ▼
┌───────────────┐       ┌───────────────┐
│ Extended      │       │ Default       │
│ Session (0x03)│       │ Session (0x01) │
└───────────────┘       └───────────────┘
    │ 10 01
    └──────────► back to Default
```

---

## 4. Service Dispatch — Confirmed SIDs

The ABS module has **15 supported services** confirmed from the firmware
dispatch table at `0xB90DC`. No others will work — you'll get NRC 0x11
(serviceNotSupported).

### Complete Service Table

| SID | Name | Default | Prog | Ext | Security | Notes |
|-----|------|:---:|:---:|:---:|:---:|-------|
| **0x10** | StartDiagnosticSession | ✓ | ✓ | ✓ | — | Session switching always available |
| **0x14** | ClearDiagnosticInformation | ✓ | — | — | — | Clear DTCs in default session only |
| **0x17** | ReadStatusOfDTC | — | ✓ | — | Level 1 | DTC status report; needs unlock |
| **0x18** | ReadDtcByStatus | ✓ | ✓ | ✓ | Level 1 | Read DTCs in any session after unlock |
| **0x1A** | ReadEcuIdentification | — | ✓ | ✓ | Level 1 | ECU ID info; needs prog or ext session |
| **0x21** | ReadDataByLocalId | ✓ | ✓ | — | Level 1 | Read calibration/status by local ID |
| **0x23** | ReadMemoryByAddress | ✓ | — | — | Level 1 | Read RAM/flash by address |
| **0x27** | SecurityAccess | — | ✓ | — | — | **Only in programming session** |
| **0x2E** | WriteDataByCommonId | ✓ | — | — | Level 1 | Write by common identifier |
| **0x31** | StartRoutineByLocalId | — | ✓ | — | Level 1 | Start actuator test / routine |
| **0x32** | StopRoutineByLocalId | ✓ | — | — | — | Stop routine, any time |
| **0x33** | RequestRoutineResults | ✓ | — | — | — | Poll routine results |
| **0x3B** | WriteDataByLocalId | — | ✓ | ✓ | Level 1 | Write calibration / recode |
| **0x3D** | WriteMemoryByAddress | ✓ | — | — | **?** | Write RAM/flash; mask=0x85 (default only). Security requirement unconfirmed — likely has runtime address-range checks. See §6. |
| **0x3E** | TesterPresent | ✓ | ✓ | ✓ | — | Session keep-alive |

> **Not supported:**
> - 0x11 (ECUReset) — not in dispatch table
> - 0x22 (ReadDataByCommonId) — NOT in dispatch table; use 0x21 instead
> - 0x34/0x36/0x37 (Flash download) — in bootloader, not application

### Permission Mask Decoding

Each SID has a permission byte at `0xB90EC`. The bit encoding (Bosch convention):

| Bit | Mask | Meaning |
|-----|------|---------|
| 7 | 0x80 | Allowed in default session (0x01) |
| 6 | 0x40 | Allowed in programming session (0x02) |
| 5 | 0x20 | Allowed in extended session (0x03) |
| 4 | 0x10 | Allowed in supplier session |
| 3–0 | 0x0F | Required security level (1 = unlocked) |

Example: mask 0xD7 = 0x80 | 0x40 | 0x10 | 0x07 → Default + Programming + Supplier,
Security Level 1.

---

## 5. SecurityAccess — Unlock Procedure

The SecurityAccess (0x27) service uses a fixed seed with an SBOX substitution
key derivation. It is **only available in the programming session** — you must
send `10 02` first.

### Algorithm

```
1. Enter programming session: 10 02
2. Request seed:              27 01
3. ECU returns:               67 01 11 22 33 44  (fixed 4-byte seed)
4. Compute key:               key[i] = SBOX[seed[i]]
5. Send key:                  27 02 D0 BD 6D 67
6. ECU returns:               67 02  (unlocked)
```

### SBOX (256-Byte Substitution Table)

Located at flash `0xB8530`. Properties: XOR-linear (SBOX[a⊕b] = SBOX[a]⊕SBOX[b]),
full permutation, SBOX[0x00] = 0x00.

```
      00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
      ------------------------------------------------
0x00: 00 1D 3A 27 74 69 4E 53 E8 F5 D2 CF 9C 81 A6 BB
0x10: CD D0 F7 EA B9 A4 83 9E 25 38 1F 02 51 4C 6B 76
0x20: 87 9A BD A0 F3 EE C9 D4 6F 72 55 48 1B 06 21 3C
0x30: 4A 57 70 6D 3E 23 04 19 A2 BF 98 85 D6 CB EC F1
0x40: 13 0E 29 34 67 7A 5D 40 FB E6 C1 DC 8F 92 B5 A8
0x50: DE C3 E4 F9 AA B7 90 8D 36 2B 0C 11 42 5F 78 65
0x60: 94 89 AE B3 E0 FD DA C7 7C 61 46 5B 08 15 32 2F
0x70: 59 44 63 7E 2D 30 17 0A B1 AC 8B 96 C5 D8 FF E2
0x80: 26 3B 1C 01 52 4F 68 75 CE D3 F4 E9 BA A7 80 9D
0x90: EB F6 D1 CC 9F 82 A5 B8 03 1E 39 24 77 6A 4D 50
0xA0: A1 BC 9B 86 D5 C8 EF F2 49 54 73 6E 3D 20 07 1A
0xB0: 6C 71 56 4B 18 05 22 3F 84 99 BE A3 F0 ED CA D7
0xC0: 35 28 0F 12 41 5C 7B 66 DD C0 E7 FA A9 B4 93 8E
0xD0: F8 E5 C2 DF 8C 91 B6 AB 10 0D 2A 37 64 79 5E 43
0xE0: B2 AF 88 95 C6 DB FC E1 5A 47 60 7D 2E 33 14 09
0xF0: 7F 62 45 58 0B 16 31 2C 97 8A AD B0 E3 FE D9 C4
```

### Unlock Sequence (Complete CAN Trace)

```
======= STEP 1: Enter Programming Session =======

→ CAN ID: 0x6F4
  Data:   02 10 02
          │  │  └── sessionType: 0x02 = programmingSession
          │  └───── SID: 0x10 = StartDiagnosticSession
          └──────── PCI: single frame, 2 data bytes

← CAN ID: 0x6F5
  Data:   06 50 02 00 32 00 C8
          │  │  │  └─────────┘
          │  │  │     P2 timing (may vary by firmware)
          │  │  └── sessionType echoed
          │  └───── SID | 0x40 = positive response
          └──────── PCI: single frame, 6 data bytes


======= STEP 2: Request Seed (SecurityAccess Level 1) =======

→ CAN ID: 0x6F4
  Data:   02 27 01
          │  │  └── securityAccessType: 0x01 = requestSeed
          │  └───── SID: 0x27 = SecurityAccess
          └──────── PCI: single frame, 2 data bytes

← CAN ID: 0x6F5
  Data:   06 67 01 11 22 33 44
          │  │  │  └────────┘
          │  │  │     seed bytes (fixed: 0x11, 0x22, 0x33, 0x44)
          │  │  └── securityAccessType echoed
          │  └───── SID | 0x40 = positive response
          └──────── PCI: single frame, 6 data bytes


======= STEP 3: Compute Key =======

  seed[0] = 0x11 → SBOX[0x11] = 0xD0
  seed[1] = 0x22 → SBOX[0x22] = 0xBD
  seed[2] = 0x33 → SBOX[0x33] = 0x6D
  seed[3] = 0x44 → SBOX[0x44] = 0x67

  Key = D0 BD 6D 67


======= STEP 4: Send Key =======

→ CAN ID: 0x6F4
  Data:   06 27 02 D0 BD 6D 67
          │  │  │  └────────┘
          │  │  │     computed key (4 bytes)
          │  │  └── securityAccessType: 0x02 = sendKey
          │  └───── SID: 0x27
          └──────── PCI: single frame, 6 data bytes

← CAN ID: 0x6F5
  Data:   02 67 02
          │  │  └── securityAccessType echoed
          │  └───── SID | 0x40 = positive response → UNLOCKED
          └──────── PCI: single frame, 2 data bytes


======= Security Unlocked — Protected Services Now Available =======
```

---

## 6. Common Diagnostic Operations

### Read ECU Identification (0x1A)

Reads module part number, software version, and other identification data.
**Requires programming or extended session + SecurityAccess Level 1.**

```
→ 02 1A 87                 (ReadEcuIdentification, all records)
← (multi-frame response — see ISO-TP section above)

Example response data (varies by firmware):
  Part Number:    A132J0314A
  Software ID:    Bosch.CSDE.Lotus_ESP8.01.001
  Internal ID:    68638V0201
  Build Date:     2015-05-21
```

### Read Variant Coding / Process Byte (0x21)

**This is the correct way to read variant/process bytes.** The current guide
previously showed SID 0x22 (ReadDataByCommonId), but that SID is **not supported**
by this module. Use ReadDataByLocalId (0x21).

ReadDataByLocalId uses a 2-byte local identifier (dataIdentifier):

```
→ 03 21 F1 90              (ReadDataByLocalId, record 0xF190)
          └─────┘
          dataIdentifier (16-bit, big-endian)

← 06 61 F1 90 xx xx xx     (positive response: SID|0x40, echoed ID, then data)
          └─────┘ └─────┘
          echoed identifier  data bytes

→ 03 21 F1 91              (example: read process byte record 0xF191)
← 04 61 F1 91 xx           (single data byte expected)
```

Known dataIdentifiers (from firmware — exact contents need experimental verification):

| Identifier | Likely Content |
|------------|----------------|
| 0xF190 | Variant coding byte |
| 0xF191 | Process byte / configuration flags |
| 0xF1xx | Other configuration records |

### Read DTCs by Status (0x18)

```
→ 04 18 00 FF 00           (ReadDtcByStatus, report all DTCs, any status)
          └── reportType: 0x00 = by status mask
              └── status mask: 0xFF = all statuses
                  └── 0x00 = reserved

← (multi-frame response with DTC list)
  Each DTC: 3 bytes DTC code + 1 byte status
  Example: 01 23 45 2F → DTC C12345, status 0x2F (testFailed, confirmed)
```

### Clear DTCs (0x14)

```
→ 03 14 FF FF FF           (ClearDiagnosticInformation, all DTC groups)
          └── groupOfDTC: 0xFFFFFF = all groups

← 01 54                    (positive response)
```

Can also clear specific groups:
```
→ 03 14 00 00 01           (clear powertrain DTCs only)
→ 03 14 00 00 10           (clear chassis DTCs only)
→ 03 14 00 00 40           (clear body DTCs only)
```

### Read Memory by Address (0x23)

Read raw memory from the module. **Format: addressAndLength byte + address bytes + length byte.**

The `addressAndLength` byte encodes:
- Upper nibble: number of address bytes (1–4)
- Lower nibble: number of length bytes (1–4)

For the ESP8 (32-bit address space, small reads):
```
→ 05 23 34 00 47 00 01 10
          │  └────────┘ └── length byte: read 0x10 = 16 bytes
          │     address: 0x00470001
          └── addressAndLength: 0x34 = 3 address bytes, 4 length bytes
```

> **This format needs experimental verification.** The exact addressAndLength
> encoding used by this module may differ from the KWP2000 standard. Start with
> small, well-known addresses (e.g., 0xBFF40 for version string) and adjust.

Safe addresses to test:
```
→ (read version string at flash 0xBFF40, 16 bytes)
→ (read calibration at RAM 0x004022C4, 16 bytes)
→ (read SBOX table at flash 0xB8530, 256 bytes)
```

### Write Memory by Address (0x3D)

**Requires understanding of the memory protection scheme.** This service is
available in the default session but may have address-range restrictions at
runtime.

```
→ 0A 3D 34 00 47 00 01 04 AA BB CC DD
          │  └────────┘ └── length
          │     address: 0x00470001
          └── addressAndLength: 0x34
                              └────────┘
                              data bytes (4 bytes: AA BB CC DD)

← 01 7D                    (positive response)
```

### Start / Stop Routine by LocalId (0x31 / 0x32)

Actuator tests and diagnostic routines. Start requires programming session +
SecurityAccess Level 1.

```
→ Start actuator test:
  03 31 01 xx              (StartRoutineByLocalId, routineId = 0x01xx)

→ Stop:
  03 32 01 xx              (StopRoutineByLocalId)

→ Poll results:
  03 33 01 xx              (RequestRoutineResults)
```

### TesterPresent — Keep Session Alive (0x3E)

Send every 2–3 seconds to prevent session timeout (~5 seconds):

```
→ 02 3E 00                 (TesterPresent, response required)
← 02 7E 00                 (positive response)

→ 02 3E 80                 (TesterPresent, suppress response)
                            (no response — reduces CAN bus load)
```

---

## 7. Negative Response Codes (NRCs)

All negative responses: `7F <SID> <NRC>`

| NRC | Name | Meaning |
|-----|------|---------|
| 0x10 | generalReject | Request rejected for unspecified reason |
| 0x11 | serviceNotSupported | SID not in dispatch table (only 15 SIDs supported) |
| 0x12 | subFunctionNotSupported | Bad sub-function parameter |
| 0x13 | incorrectMessageLength | Wrong number of bytes in request |
| 0x22 | conditionsNotCorrect | Wrong operating conditions (engine running, speed > 0, etc.) |
| 0x24 | requestSequenceError | Must send service A before service B |
| 0x31 | requestOutOfRange | Address or value out of allowed range |
| 0x33 | **securityAccessDenied** | Protected service used without unlock — send `27 01` → `27 02` |
| 0x34 | **requiredTimeDelayNotExpired** | Too soon after last failed attempt — wait ~10 seconds |
| 0x35 | **invalidKey** | Wrong key computed or SBOX mismatch |
| 0x36 | **exceedNumberOfAttempts** | Too many failed keys — restart session (`10 02` → `27 01`) |
| 0x37 | requiredTimeDelayNotExpired | Delay variant — wait before retry |
| 0x78 | responsePending | Request accepted, processing — wait for final response |

---

## 8. Python Reference Implementation

### ISO-TP on SocketCAN (Linux)

```python
"""
Bosch ESP8 ABS — KWP2000 diagnostic client over ISO-TP (SocketCAN).

Dependencies:
    pip install python-can

Kernel setup:
    sudo ip link set can0 type can bitrate 500000
    sudo ip link set up can0
"""

import can
import time
import struct

# ─── SBOX from firmware flash 0xB8530 ───
SBOX = bytes([
    0x00, 0x1D, 0x3A, 0x27, 0x74, 0x69, 0x4E, 0x53, 0xE8, 0xF5, 0xD2, 0xCF, 0x9C, 0x81, 0xA6, 0xBB,
    0xCD, 0xD0, 0xF7, 0xEA, 0xB9, 0xA4, 0x83, 0x9E, 0x25, 0x38, 0x1F, 0x02, 0x51, 0x4C, 0x6B, 0x76,
    0x87, 0x9A, 0xBD, 0xA0, 0xF3, 0xEE, 0xC9, 0xD4, 0x6F, 0x72, 0x55, 0x48, 0x1B, 0x06, 0x21, 0x3C,
    0x4A, 0x57, 0x70, 0x6D, 0x3E, 0x23, 0x04, 0x19, 0xA2, 0xBF, 0x98, 0x85, 0xD6, 0xCB, 0xEC, 0xF1,
    0x13, 0x0E, 0x29, 0x34, 0x67, 0x7A, 0x5D, 0x40, 0xFB, 0xE6, 0xC1, 0xDC, 0x8F, 0x92, 0xB5, 0xA8,
    0xDE, 0xC3, 0xE4, 0xF9, 0xAA, 0xB7, 0x90, 0x8D, 0x36, 0x2B, 0x0C, 0x11, 0x42, 0x5F, 0x78, 0x65,
    0x94, 0x89, 0xAE, 0xB3, 0xE0, 0xFD, 0xDA, 0xC7, 0x7C, 0x61, 0x46, 0x5B, 0x08, 0x15, 0x32, 0x2F,
    0x59, 0x44, 0x63, 0x7E, 0x2D, 0x30, 0x17, 0x0A, 0xB1, 0xAC, 0x8B, 0x96, 0xC5, 0xD8, 0xFF, 0xE2,
    0x26, 0x3B, 0x1C, 0x01, 0x52, 0x4F, 0x68, 0x75, 0xCE, 0xD3, 0xF4, 0xE9, 0xBA, 0xA7, 0x80, 0x9D,
    0xEB, 0xF6, 0xD1, 0xCC, 0x9F, 0x82, 0xA5, 0xB8, 0x03, 0x1E, 0x39, 0x24, 0x77, 0x6A, 0x4D, 0x50,
    0xA1, 0xBC, 0x9B, 0x86, 0xD5, 0xC8, 0xEF, 0xF2, 0x49, 0x54, 0x73, 0x6E, 0x3D, 0x20, 0x07, 0x1A,
    0x6C, 0x71, 0x56, 0x4B, 0x18, 0x05, 0x22, 0x3F, 0x84, 0x99, 0xBE, 0xA3, 0xF0, 0xED, 0xCA, 0xD7,
    0x35, 0x28, 0x0F, 0x12, 0x41, 0x5C, 0x7B, 0x66, 0xDD, 0xC0, 0xE7, 0xFA, 0xA9, 0xB4, 0x93, 0x8E,
    0xF8, 0xE5, 0xC2, 0xDF, 0x8C, 0x91, 0xB6, 0xAB, 0x10, 0x0D, 0x2A, 0x37, 0x64, 0x79, 0x5E, 0x43,
    0xB2, 0xAF, 0x88, 0x95, 0xC6, 0xDB, 0xFC, 0xE1, 0x5A, 0x47, 0x60, 0x7D, 0x2E, 0x33, 0x14, 0x09,
    0x7F, 0x62, 0x45, 0x58, 0x0B, 0x16, 0x31, 0x2C, 0x97, 0x8A, 0xAD, 0xB0, 0xE3, 0xFE, 0xD9, 0xC4,
])

FIXED_SEED = bytes([0x11, 0x22, 0x33, 0x44])

def compute_key(seed: bytes) -> bytes:
    """Compute SecurityAccess key from 4-byte seed using SBOX."""
    return bytes(SBOX[b] for b in seed)


class ESP8Client:
    """KWP2000 diagnostic client for Bosch ESP8 ABS over ISO-TP."""

    TX_ID = 0x6F4   # ABS physical request (ISO 15765-4)
    RX_ID = 0x6F5   # ABS physical response
    TIMEOUT = 1.0  # seconds

    def __init__(self, channel: str = "can0"):
        self.bus = can.interface.Bus(channel=channel, interface="socketcan")
        self._unlocked = False

    # ─── Low-level ISO-TP ───────────────────────────────────

    def _send(self, payload: bytes) -> None:
        """Send a KWP2000 payload over ISO-TP."""
        plen = len(payload)
        if plen <= 7:
            # Single frame: PCI byte = length
            data = bytes([plen]) + payload
            self.bus.send(can.Message(arbitration_id=self.TX_ID, data=data, is_extended_id=False))
        else:
            # First frame: PCI = 0x10 | (length >> 8), then length low byte, then 6 data bytes
            data = bytes([0x10 | (plen >> 8), plen & 0xFF]) + payload[:6]
            self.bus.send(can.Message(arbitration_id=self.TX_ID, data=data, is_extended_id=False))
            # Wait for flow control
            self._recv(timeout=0.1)  # expect FC frame (0x30) — discard for now
            # Send consecutive frames
            seq = 1
            for offset in range(6, plen, 7):
                chunk = payload[offset:offset + 7]
                data = bytes([0x20 | (seq & 0x0F)]) + chunk
                self.bus.send(can.Message(arbitration_id=self.TX_ID, data=data, is_extended_id=False))
                seq = (seq + 1) & 0x0F

    def _recv(self, timeout: float | None = None) -> bytes:
        """Receive and reassemble an ISO-TP response. Returns payload bytes."""
        if timeout is None:
            timeout = self.TIMEOUT
        msg = self.bus.recv(timeout=timeout)
        if msg is None:
            raise TimeoutError("No response from ABS module")
        pci = msg.data[0]
        if (pci & 0xF0) == 0x00:
            # Single frame
            length = pci & 0x0F
            payload = msg.data[1:1 + length]
        elif (pci & 0xF0) == 0x10:
            # First frame
            total_len = ((pci & 0x0F) << 8) | msg.data[1]
            payload = bytearray(msg.data[2:8])  # first 6 bytes
            # Send flow control
            fc = can.Message(arbitration_id=self.TX_ID, data=b'\x30\x00\x00\x00\x00\x00\x00\x00',
                             is_extended_id=False)
            self.bus.send(fc)
            # Receive consecutive frames
            while len(payload) < total_len:
                cf = self.bus.recv(timeout=timeout)
                if cf is None:
                    raise TimeoutError("Missing consecutive frame")
                payload.extend(cf.data[1:8])
            payload = bytes(payload[:total_len])
        else:
            raise ValueError(f"Unexpected PCI byte: 0x{pci:02X}")
        return bytes(payload)

    def _kwp(self, sid: int, data: bytes = b"") -> bytes:
        """Send a KWP2000 request and return the response payload."""
        self._send(bytes([sid]) + data)
        resp = self._recv()
        # Check for negative response
        if len(resp) >= 2 and resp[0] == 0x7F:
            nrc = resp[2]
            nrc_names = {
                0x10: "generalReject", 0x11: "serviceNotSupported",
                0x12: "subFunctionNotSupported", 0x13: "incorrectMessageLength",
                0x22: "conditionsNotCorrect", 0x33: "securityAccessDenied",
                0x34: "timeDelayNotExpired", 0x35: "invalidKey",
                0x36: "exceedNumberOfAttempts", 0x78: "responsePending",
            }
            raise RuntimeError(f"NRC 0x{nrc:02X} ({nrc_names.get(nrc, 'unknown')}) for SID 0x{sid:02X}")
        return resp

    # ─── High-level operations ───────────────────────────────

    def enter_session(self, session: int = 0x02) -> None:
        """Enter a diagnostic session. 0x01=Default, 0x02=Programming, 0x03=Extended."""
        resp = self._kwp(0x10, bytes([session]))
        if resp[0] == 0x50:
            print(f"Session 0x{session:02X} entered")
        self._unlocked = False  # session change resets security

    def security_access(self) -> bool:
        """Perform SecurityAccess unlock. Returns True on success."""
        # Request seed
        resp = self._kwp(0x27, b'\x01')
        if resp[0] != 0x67:
            return False
        seed = resp[2:6]
        print(f"Seed: {seed.hex(' ')}")
        # Compute key
        key = compute_key(seed)
        print(f"Key:  {key.hex(' ')}")
        # Send key
        resp = self._kwp(0x27, b'\x02' + key)
        self._unlocked = (resp[0] == 0x67 and resp[1] == 0x02)
        return self._unlocked

    def read_memory(self, address: int, length: int) -> bytes:
        """Read memory by address (0x23). Uses 3-byte address + 1-byte length format."""
        addr_and_len = 0x31  # 3 address bytes, 1 length byte
        payload = bytes([addr_and_len,
                         (address >> 16) & 0xFF,
                         (address >> 8) & 0xFF,
                         address & 0xFF,
                         length & 0xFF])
        resp = self._kwp(0x23, payload)
        if resp[0] == 0x63:
            return resp[1:]  # skip echoed SID
        raise RuntimeError(f"Unexpected response SID: 0x{resp[0]:02X}")

    def read_data_by_local_id(self, identifier: int) -> bytes:
        """Read calibration data by local identifier (0x21)."""
        payload = bytes([(identifier >> 8) & 0xFF, identifier & 0xFF])
        resp = self._kwp(0x21, payload)
        if resp[0] == 0x61:
            return resp[3:]  # skip echoed SID + identifier
        raise RuntimeError(f"Unexpected response SID: 0x{resp[0]:02X}")

    def read_dtcs(self) -> list[tuple[int, int]]:
        """Read all DTCs. Returns list of (dtc_code, status) tuples."""
        resp = self._kwp(0x18, b'\x00\xFF\x00')
        if resp[0] != 0x58:
            raise RuntimeError(f"Unexpected response: 0x{resp[0]:02X}")
        dtcs = []
        # Format after 0x58: [dtcStatusAvailabilityMask] [DTC+status]*N
        data = resp[1:]
        i = 0
        while i + 4 <= len(data):
            dtc_code = (data[i] << 16) | (data[i + 1] << 8) | data[i + 2]
            status = data[i + 3]
            dtcs.append((dtc_code, status))
            i += 4
        return dtcs

    def clear_dtcs(self, group: int = 0xFFFFFF) -> None:
        """Clear DTCs for the specified group (default: all)."""
        self._kwp(0x14, bytes([(group >> 16) & 0xFF, (group >> 8) & 0xFF, group & 0xFF]))
        print("DTCs cleared")

    def read_ecu_id(self) -> bytes:
        """Read ECU identification (0x1A)."""
        resp = self._kwp(0x1A, b'\x87')
        if resp[0] == 0x5A:
            return resp[1:]
        raise RuntimeError(f"Unexpected response: 0x{resp[0]:02X}")

    def tester_present(self, suppress: bool = False) -> None:
        """Send TesterPresent to keep session alive."""
        sub = 0x80 if suppress else 0x00
        self._kwp(0x3E, bytes([sub]))

    def close(self) -> None:
        self.bus.shutdown()


# ─── Example Usage ──────────────────────────────────────

if __name__ == "__main__":
    abs_module = ESP8Client("can0")

    # Unlock sequence
    abs_module.enter_session(0x02)     # programming session
    if abs_module.security_access():
        print("Security unlocked!")

        # Read variant coding
        variant = abs_module.read_data_by_local_id(0xF190)
        print(f"Variant coding: {variant.hex(' ')}")

        # Read version string from flash
        version = abs_module.read_memory(0xBFF40, 32)
        print(f"Version: {version.decode('ascii', errors='replace')}")

        # Read DTCs
        dtcs = abs_module.read_dtcs()
        for code, status in dtcs:
            print(f"DTC 0x{code:06X} status=0x{status:02X}")

        # Keep session alive
        abs_module.tester_present(suppress=True)

    abs_module.close()
```

### Key / Seed Utility (Without CAN)

```python
"""Compute ESP8 SecurityAccess key from seed — no CAN hardware needed."""

SBOX = bytes([
    0x00, 0x1D, 0x3A, 0x27, 0x74, 0x69, 0x4E, 0x53, 0xE8, 0xF5, 0xD2, 0xCF, 0x9C, 0x81, 0xA6, 0xBB,
    0xCD, 0xD0, 0xF7, 0xEA, 0xB9, 0xA4, 0x83, 0x9E, 0x25, 0x38, 0x1F, 0x02, 0x51, 0x4C, 0x6B, 0x76,
    0x87, 0x9A, 0xBD, 0xA0, 0xF3, 0xEE, 0xC9, 0xD4, 0x6F, 0x72, 0x55, 0x48, 0x1B, 0x06, 0x21, 0x3C,
    0x4A, 0x57, 0x70, 0x6D, 0x3E, 0x23, 0x04, 0x19, 0xA2, 0xBF, 0x98, 0x85, 0xD6, 0xCB, 0xEC, 0xF1,
    0x13, 0x0E, 0x29, 0x34, 0x67, 0x7A, 0x5D, 0x40, 0xFB, 0xE6, 0xC1, 0xDC, 0x8F, 0x92, 0xB5, 0xA8,
    0xDE, 0xC3, 0xE4, 0xF9, 0xAA, 0xB7, 0x90, 0x8D, 0x36, 0x2B, 0x0C, 0x11, 0x42, 0x5F, 0x78, 0x65,
    0x94, 0x89, 0xAE, 0xB3, 0xE0, 0xFD, 0xDA, 0xC7, 0x7C, 0x61, 0x46, 0x5B, 0x08, 0x15, 0x32, 0x2F,
    0x59, 0x44, 0x63, 0x7E, 0x2D, 0x30, 0x17, 0x0A, 0xB1, 0xAC, 0x8B, 0x96, 0xC5, 0xD8, 0xFF, 0xE2,
    0x26, 0x3B, 0x1C, 0x01, 0x52, 0x4F, 0x68, 0x75, 0xCE, 0xD3, 0xF4, 0xE9, 0xBA, 0xA7, 0x80, 0x9D,
    0xEB, 0xF6, 0xD1, 0xCC, 0x9F, 0x82, 0xA5, 0xB8, 0x03, 0x1E, 0x39, 0x24, 0x77, 0x6A, 0x4D, 0x50,
    0xA1, 0xBC, 0x9B, 0x86, 0xD5, 0xC8, 0xEF, 0xF2, 0x49, 0x54, 0x73, 0x6E, 0x3D, 0x20, 0x07, 0x1A,
    0x6C, 0x71, 0x56, 0x4B, 0x18, 0x05, 0x22, 0x3F, 0x84, 0x99, 0xBE, 0xA3, 0xF0, 0xED, 0xCA, 0xD7,
    0x35, 0x28, 0x0F, 0x12, 0x41, 0x5C, 0x7B, 0x66, 0xDD, 0xC0, 0xE7, 0xFA, 0xA9, 0xB4, 0x93, 0x8E,
    0xF8, 0xE5, 0xC2, 0xDF, 0x8C, 0x91, 0xB6, 0xAB, 0x10, 0x0D, 0x2A, 0x37, 0x64, 0x79, 0x5E, 0x43,
    0xB2, 0xAF, 0x88, 0x95, 0xC6, 0xDB, 0xFC, 0xE1, 0x5A, 0x47, 0x60, 0x7D, 0x2E, 0x33, 0x14, 0x09,
    0x7F, 0x62, 0x45, 0x58, 0x0B, 0x16, 0x31, 0x2C, 0x97, 0x8A, 0xAD, 0xB0, 0xE3, 0xFE, 0xD9, 0xC4,
])

FIXED_SEED = bytes([0x11, 0x22, 0x33, 0x44])
EXPECTED_KEY = bytes([0xD0, 0xBD, 0x6D, 0x67])


def compute_key(seed: bytes) -> bytes:
    assert len(seed) == 4
    return bytes(SBOX[b] for b in seed)


def compute_seed(key: bytes) -> bytes:
    """Inverse: find what seed produces a given key."""
    assert len(key) == 4
    inv = [0] * 256
    for i in range(256):
        inv[SBOX[i]] = i
    return bytes(inv[b] for b in key)


# Verify
assert compute_key(FIXED_SEED) == EXPECTED_KEY
assert compute_seed(EXPECTED_KEY) == FIXED_SEED
print(f"Seed: {FIXED_SEED.hex(' ')} → Key: {EXPECTED_KEY.hex(' ')}")
print("SBOX algorithm verified.")
```

---

## 9. Diagnostic Workflow for Software Authors

### Typical Session Flow

```
1. Open CAN interface (500 kbps)
2. Enter programming session:     → 10 02
3. SecurityAccess unlock:         → 27 01 (get seed)
                                  → 27 02 (send key)
4. Perform protected operations:  → 21, 3B, 23, 31, etc.
5. Keep alive:                    → 3E 80 (every 2-3 seconds)
6. Return to default session:     → 10 01 (or let timeout)
```

### Minimal Unlock Script

```python
def unlock_abs(can_channel="can0"):
    """Minimal unlock — returns an ESP8Client ready for protected operations."""
    client = ESP8Client(can_channel)
    client.enter_session(0x02)
    if not client.security_access():
        client.close()
        raise RuntimeError("SecurityAccess failed")
    return client
```

### Reading the Full Calibration Block

```python
def dump_calibration(client: ESP8Client, output_path: str):
    """Dump the 1843-byte calibration block from RAM 0x004022C4."""
    CAL_RAM = 0x004022C4
    CAL_SIZE = 1843  # 0x733 bytes
    CHUNK = 64  # read 64 bytes at a time

    data = bytearray()
    for offset in range(0, CAL_SIZE, CHUNK):
        chunk = client.read_memory(CAL_RAM + offset, min(CHUNK, CAL_SIZE - offset))
        data.extend(chunk)
        print(f"Read {len(data)}/{CAL_SIZE} bytes...")

    with open(output_path, "wb") as f:
        f.write(data)
    print(f"Calibration saved to {output_path}")
```

### Porting Notes for Non-SocketCAN Platforms

For PCAN-USB (Windows):
```python
import can
bus = can.interface.Bus(channel="PCAN_USBBUS1", interface="pcan")
```

For Macchina M2 / GVRET (cross-platform):
```python
bus = can.interface.Bus(channel="COM3", interface="serial")  # Windows
bus = can.interface.Bus(channel="/dev/ttyUSB0", interface="serial")  # Linux
```

The `ESP8Client` class above works with any python-can backend — just change the
Bus constructor.

---

## 10. Quick Reference Card

```
┌──────────────────────────────────────────────────┐
│ Bosch ESP8 ABS — KWP2000 Diagnostic Quick Ref    │
├──────────────────────────────────────────────────┤
│ Module:    ESP8.1 (TMS470/ARM7TDMI, ERCOSEK)    │
│ CAN IDs:   TX=0x6F4, RX=0x6F5 (ISO 15765-4 ABS)     │
│ Bus:       500 kbps, 11-bit IDs                  │
│ Transport: ISO-TP (ISO 15765-2)                  │
│ Protocol:  KWP2000 (ISO 14230)                   │
│ SIDs:      15 supported (see dispatch table)     │
├──────────────────────────────────────────────────┤
│ UNLOCK:                                          │
│   1.  10 02              → programming session   │
│   2.  27 01              → request seed          │
│   3.  seed = 11 22 33 44 (fixed)                │
│   4.  key  = SBOX[seed]  → D0 BD 6D 67          │
│   5.  27 02 D0 BD 6D 67  → send key             │
│   6.  67 02              → unlocked              │
├──────────────────────────────────────────────────┤
│ COMMANDS:                                        │
│   1A 87              read ECU identification     │
│   21 F1 90           read variant coding         │
│   3B xx yy zz        write recoding data         │
│   18 00 FF 00        read all DTCs               │
│   14 FF FF FF        clear all DTCs              │
│   23 31 ADDR LEN     read memory by address      │
│   3E 00              tester present (keep-alive) │
├──────────────────────────────────────────────────┤
│ SECURITY:                                        │
│   3 wrong keys → 7F 27 36 (restart: 10 02)       │
│   Too fast     → 7F 27 34 (wait 10 seconds)      │
│   Not unlocked → 7F xx 33 (call security_access) │
│   Wrong sess   → 7F 27 22 (must be 0x02)         │
└──────────────────────────────────────────────────┘
```

---

## 11. References

- **Firmware:** `PRJ_CodeBlock_BB68638_V0201_ECC_CSW_S.hex` (A132J0314A)
- **Analysis:** `CLAUDE.md` — full ESP8 reverse engineering reference
- **Yaw control:** `YAW_CONTROL_ANALYSIS.md` — bicycle model + calibration analysis
- **CAN messages:** `CAN_MESSAGES.md` — runtime CAN message bit-level documentation
- **SBOX:** flash `0xB8530` — 256-byte substitution table
- **SID dispatch:** flash `0xB90DC` — 15-service dispatch table
- **Permission masks:** flash `0xB90EC` — per-SID session/security requirements
- **Security seed:** flash `0xB92FC` — fixed seed `11 22 33 44`
- **Handler table:** flash `0xB9164` — 9 diagnostic handler functions

### Standards

- ISO 14230 (KWP2000) — diagnostic protocol
- ISO 15765-2 (ISO-TP) — CAN transport layer
- ISO 11898 — CAN physical layer

---

*Document compiled from reverse engineering analysis of Bosch ESP8.1 firmware
BB68638 V0201 (A132J0314A), Lotus Evora. For research, educational, and
diagnostic software development purposes.*
