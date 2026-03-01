# TPMS Analysis Report — B13200091 (2011 Lotus Evora NA)

NOTE: The TPMS module communicates on a dedicated CAN bus
(FlexCAN B, using fcb_buffer). Some functions are named
flexcan_c_* by the analyst, but they all use fcb_buffer
and are on the same bus as flexcan_b_rx_540. All TPMS
traffic is on CAN B, separate from vehicle CAN A.

---

## Section 1: CAN Message Summary

### CAN B — ECU transmits TO TPMS module

| ID    | Content |
|-------|---------|
| 0x220 | Handshake sync (fixed: `19 81 00 20 02 40 00 00`) |
| 0x240 | Protocol messages (multi-frame, variable payload) |
| 0x460 | Engine speed + vehicle speed |
| 0x7A0 | Intake air temperature |

### CAN B — ECU receives FROM TPMS module

| ID    | Content |
|-------|---------|
| 0x540 | Tire pressures + validity/error flags |
| 0x256 | Handshake responses (from the 0x240 protocol dialog) |

### CAN A — ECU transmits TO vehicle cluster

| ID    | Content |
|-------|---------|
| 0x401 | `tpms_tx_401_data` (never populated — see §4) |
| 0x402 | `tpms_output` (tire pressures + status flags) |

---

## Section 2: Runtime Variables

### `tpms0` / `tpms1` / `tpms2` / `tpms3` — `undefined1`

Tire pressure values, one per sensor.

- **Source**: CAN B 0x540 bytes [2][4][3][5] respectively.
  Note: byte order in CAN frame is tpms0, tpms2, tpms1, tpms3.
- **Units**: Unresolved. Best estimate **2 kPa/count** based on
  the left-shift-1 applied before cluster output and the need
  for values to stay below 128 to avoid byte overflow.
- **Value 0**: Sentinel for invalid/error — explicitly zeroed
  when the per-sensor error bit is set.
- **Wheel assignment** (FL/FR/RL/RR): Not confirmed from code.

---

### `obd_ii_tire_pressure_valid_and_error` — `undefined2`

16-bit status bitfield populated from CAN B 0x540.

| Bit | Mask   | Meaning |
|-----|--------|---------|
| 0   | 0x0001 | tpms0 sensor error |
| 1   | 0x0002 | tpms2 sensor error |
| 2   | 0x0004 | tpms1 sensor error |
| 3   | 0x0008 | tpms3 sensor error |
| 4   | 0x0010 | tpms0 pressure valid |
| 5   | 0x0020 | tpms2 pressure valid |
| 6   | 0x0040 | tpms1 pressure valid |
| 7   | 0x0080 | tpms3 pressure valid |
| 8   | 0x0100 | TPMS module initialized / data valid (from CAN 0x540 byte[6] bit 7) |
| 9   | 0x0200 | Sensor relearn in progress |
| 15:10 | —   | Reserved |

For each sensor: pressure is valid only when the valid bit is SET
and the error bit is CLEAR. Bit 8 (0x100) = master "module alive"
flag. Bit 9 (0x200) = set by relearn state machine; gates vehicle
speed reporting to TPMS module.

---

### `tpms_output[8]` — `byte[8]`

CAN A 0x402 frame payload sent to instrument cluster.

| Byte | Content |
|------|---------|
| [0]  | `tpms0 << 1` (pressure, ~1 kPa/count after shift) |
| [1]  | `tpms1 << 1` |
| [2]  | `tpms2 << 1` |
| [3]  | `tpms3 << 1` |
| [4]  | Per-sensor OK flags (see below) |
| [5:7] | 0x00 |

Byte [4] bitfield (valid AND no error for each sensor):

| Bit | Sensor |
|-----|--------|
| 0   | tpms0 OK |
| 1   | tpms1 OK |
| 2   | tpms2 OK |
| 3   | tpms3 OK |
| 7:4 | Preserved/unused |

Only packed when `DAT_40009046 == 0` (gen-1 module). Note:
tpms1/tpms2 bit ordering in byte [4] is re-sorted to natural
0/1/2/3 order (they are swapped in the internal bitfield).

When TPMS not fitted: bytes [0:3] = 0xFF, byte [4] upper nibble
cleared.

---

### `tpms_tx_401_data[8]` — `byte[8]`

CAN A 0x401 payload. **Never written** anywhere in the firmware.
Transmitted only when `tpms_tx_pending_flags` bit 0 is set, but
that bit is also never set. Dead/reserved code path.

---

### `tpms_tx_pending_flags` — `undefined1`

| Bit | Mask | Meaning |
|-----|------|---------|
| 0   | 0x01 | CAN A 0x401 TX pending (never set — dead code) |
| 1   | 0x02 | CAN A 0x402 TX pending |

Bit 1 set after populating `tpms_output`. Cleared by
`flexcan_a_tx_401_402_tpms` after transmission.

---

## Section 3: State Machine Variables

### Init handshake (`tpms_init_handshake_state_machine`)

| Variable | Meaning |
|----------|---------|
| `DAT_4000227e` | State counter (0x00–0x10 active; 0xFF = idle/done) |
| `DAT_40001498` | Inner retry counter (reloads to 3 per state) |
| `DAT_40001499` | Outer retry counter (full handshake restart attempts) |
| `DAT_40001a96` | Init failed flag. Set=1 on timeout/failure; triggers warning light. Cleared by OBD clear-DTC. |

### Sensor relearn (`tpms_sensor_relearn_state_machine`)

| Variable | Meaning |
|----------|---------|
| `DAT_40002274` | State counter (0–5; set directly by OBD handler) |
| `DAT_40002276` | Relearn busy flag (1 = in progress, 0 = idle) |
| `DAT_40002281` | Inter-message interval countdown (reloads from `DAT_4000149a`) |
| `DAT_4000149a` | Interval reload value for `DAT_40002281` |
| `DAT_4000149b` | Relearn completion timeout countdown |

### Multi-frame transmit (`flexcan_c_send_unknown`)

| Variable | Meaning |
|----------|---------|
| `DAT_40002270` | CAN message ID register (always set to 0x240) |
| `DAT_40002272` | Payload byte count for current message |
| `DAT_40002273` | Continuation frame sequence counter (0 = first frame) |
| `DAT_4000227f` | Total frame count for multi-frame message |
| `DAT_40002280` | More frames pending flag (1 = pending; checked by init handshake) |

### Receive buffer (from CAN B 0x256 responses)

| Variable | Meaning |
|----------|---------|
| `DAT_400083c1` | Response byte 1 — checked for 0x7B (ACK marker) |
| `DAT_400083c2` | Response byte 2 — command echo byte |
| `DAT_400083c3` | Response byte 3 — CVN high byte |
| `DAT_400083c4` | Response byte 4 — CVN low byte |
| `DAT_400083c5` | Response byte 5 — wheel-profile COD bit echo |

### TPMS module variant

| Variable | Meaning |
|----------|---------|
| `DAT_40009046` | Gen-2 module flag (0 = gen-1, 1 = gen-2). Never written in decompiled C; initialized by startup code. Combined with `VIN[9] < 'F'` (MY2015) check: either condition alone forces gen-1 paths. |
| `DAT_40002277` | TPMS module comms watchdog. Set to 0x32 (50) on receipt of CAN B 0x540; decrements each task call. Zero = module has stopped transmitting. |

---

## Section 4: Calibration Values

Pressure thresholds programmed into the TPMS module during init.
Wheel profile selected by `COD[0] bit 20`:
- 0 = 18" front / 19" rear
- 1 = 19" front / 20" rear

| Address    | Suggested Name |
|------------|----------------|
| 0x4000d202 | `CAL_tpms_low_pressure_threshold_18_19` byte A |
| 0x4000d203 | `CAL_tpms_low_pressure_threshold_18_19` byte B |
| 0x4000d204 | `CAL_tpms_low_pressure_threshold_19_20` byte A |
| 0x4000d205 | `CAL_tpms_low_pressure_threshold_19_20` byte B |
| 0x4000d316 | `CAL_tpms_high_pressure_threshold_19_20` byte A |
| 0x4000d317 | `CAL_tpms_high_pressure_threshold_19_20` byte B |
| 0x4000d318 | `CAL_tpms_gen2_low_pressure_threshold_19_20` byte A |
| 0x4000d319 | `CAL_tpms_gen2_low_pressure_threshold_19_20` byte B |
| 0x4000d329 | `CAL_tpms_high_pressure_threshold_18_19` byte A |
| 0x4000d32a | `CAL_tpms_high_pressure_threshold_18_19` byte B |
| 0x4000d32b | `CAL_tpms_gen2_low_pressure_threshold_18_19` byte A |
| 0x4000d32c | `CAL_tpms_gen2_low_pressure_threshold_18_19` byte B |

Sent in state 0x03 as: `low_A, low_B, (high_A - low_A), (high_B - low_B)`.
Sent in state 0x0F as: `high_A, high_B` (final programming).

---

## Section 5: Function Descriptions

### `flexcan_b_rx_540`

CAN B receive handler for TPMS module message 0x540. Only active
when TPMS fitted (`COD[1] bit 13`) and
`CAL_ecu_flexcan_diag_bus_select != 2`.

Extracts tire pressures from bytes [2:5]:

| CAN byte | Variable |
|----------|----------|
| [2] | tpms0 |
| [3] | tpms2 |
| [4] | tpms1 |
| [5] | tpms3 |

Builds `obd_ii_tire_pressure_valid_and_error` from bytes [0] and [1]
(validity and error flags). If error bit set for a sensor, that tpms
value is forced to 0. Bit 8 (0x100) set from byte[6] bit 7. Sets
`DAT_40002277 = 0x32` (comms watchdog reload).

---

### `flexcan_c_send_220` — CAN B 0x220

Sends fixed 8-byte sync/preamble frame: `19 81 00 20 02 40 00 00`.
Called before each major init handshake sequence and at the start of
sensor relearn.

---

### `flexcan_c_send_unknown` / `flexcan_c_tx_0x240` — CAN B 0x240

General multi-frame transmit on CAN B ID 0x240. Uses staging
registers `DAT_40008440`–`DAT_4000844c` for payload bytes.
`DAT_40002272` = byte count.

Frame format (byte [1] always = 0x97):

| Frame type | Byte [0] | Bytes [2:] |
|------------|----------|------------|
| Single (len < 5) | `0x40` | `len, payload...` |
| First frame (len ≥ 5) | `0xC0\|frame_count` | `len, payload[0:5]` |
| Continuation | `0x80\|seq` | `payload[n:n+6]` |

Sets `DAT_40002280 = 1` when more frames remain.

---

### `FUN_000a521c` → `tpms_init_handshake_state_machine`

One-shot 17-state (0x00–0x10) handshake with the TPMS module,
called at 10 Hz when TPMS fitted. State machine driven by
`DAT_4000227e`. Aborts if `ecu_run_timer > 0x32` (>500 ms elapsed
since ECU start) or key diagnostic fault present. On abort or retry
exhaustion: `DAT_40001a96 = 1`.

Gen-1 path (`DAT_40009046 == 0` or `VIN[9] < 'F'`): states 5, 7, 9
are skipped (state += 2). Gen-2 path: all 17 states run.

| State | Action |
|-------|--------|
| 0x00 | Send 0x220 sync message |
| 0x01 | Send `0x3B, 0x2F` — CVN challenge request |
| 0x02 | Wait for 0x2F response; verify `CAL_ecu_cvn` and wheel-profile COD bit match reply |
| 0x03 | Send `0x3B, 0x40` — pressure thresholds (low, high−low range, per wheel profile) |
| 0x04 | Wait ACK 0x40 |
| 0x05* | Send `0x3B, 0x61, 0x01` |
| 0x06* | Wait ACK 0x61 |
| 0x07* | Send `0x3B, 0x67` with extra parameters |
| 0x08* | Wait ACK 0x67 |
| 0x09* | Send `0x3B, 0x69` — warning thresholds |
| 0x0A* | Wait ACK 0x69 |
| 0x0B | Send `0x3B, 0x61, 0x00` |
| 0x0C | Wait ACK 0x61 |
| 0x0D | Send `0x3B, 0x47, 0x00, 0x01` |
| 0x0E | Wait ACK 0x47 |
| 0x0F | Send `0x3B, 0x2F` — final programming: `CAL_ecu_cvn` (2 bytes), wheel-profile bit, `0x34`, `0x35`, high pressure threshold (wheel-profile), `0x18` (gen-1) or `0x0C` (gen-2), `0x5A` |
| 0x10 | Wait ACK 0x2F → `DAT_4000227e = -1` (complete) |

\* = gen-2 only

---

### `FUN_000a60bc` → `tpms_sensor_relearn_state_machine`

6-state relearn protocol driven by `DAT_40002274`. Triggered by OBD
proprietary service when `obd_req[2] == 5` and TPMS fitted. OBD
handler sets `DAT_40002274 = obd_req[3]` before calling, allowing
the tester to select the starting state (state 5 = cancel/abort).

| State | Action |
|-------|--------|
| 0 | If not busy: call `tpms_module_reset_and_wake`, set state=1, busy=1. If busy: decrement interval timer; on expiry send `0x3E` keepalive, reload timer. |
| 1 | Send `0x3B, 0x48` with params `{0x1E, 5, 4, 4, 1, 0x90}` — configure sensor detection |
| 2 | Wait for ACK `{0x7B, 0x48}` |
| 3 | Send `0x21, 0x15` — request sensor scan |
| 4 | Wait for `{0x15, 0x01}` (sensor found) → state=0, set bit 0x200 in status |
| 5 | Clear bit 0x200. Decrement timeout; on expiry: if bit 0x100 clear (no live data) call reset. Reset state=0, busy=0. |

---

### `FUN_000a63a8` → `tpms_module_reset_and_wake`

Sends 0x220 sync then `0x3B, 0x14, 0xFF, 0x00` on CAN B 0x240.
Used to reset TPMS module state at relearn start and on relearn
timeout.

---

### `FUN_000a6338` → `tpms_module_wake_alt`

Sends 0x220 sync then `0x3B, 0x18, 0x00, 0xFF, 0x00` on CAN B
0x240. Alternate wake/reset variant.

---

### `flexcan_a_tx_401_402_tpms`

Transmits pending TPMS data on CAN A. Bit 1 (0x402) takes priority
over bit 0 (0x401).

- **0x402 path**: sends `tpms_output[8]` (pressures + status flags).
- **0x401 path**: sends `tpms_tx_401_data[8]` — dead code, flag never
  set.

---

### `flexcan_c_tx_460` — CAN B 0x460

Transmits engine speed and vehicle speed to TPMS module.

| Byte | Content |
|------|---------|
| [0] | 0x00 |
| [1:2] | `engine_speed_2` (16-bit RPM) |
| [3:4] | Vehicle speed in 0.1 km/h units, OR `0x01F4` (= 500 = 50.0 km/h) when relearn in progress (bit 0x200 set) |
| [5:7] | 0x00 |

Speed is clamped during relearn to prevent TPMS sensor learning at
road speed.

---

### `flexcan_c_tx_7a0` — CAN B 0x7A0

Transmits air temperature to TPMS module. Temperature source:
`air_temp_intake_unknown`, or `temp_engine_air` if `COD[1] bit 10`
set.

Scaling: `val * 50 / 8`, converting `u8_temp_5/8-40c` raw value to
0.1 °C steps above −40 °C. Capped at 900 (= 90 °C effective).
Temperature is duplicated in bytes [1:2] and [3:4]. Called every
8 main loop cycles (~8 ms).

---

## Section 6: Cluster Warning Light Logic

### Activation condition

Warning active when any of:
- Any tire: valid bit CLEAR, OR error bit SET
- Init failed: `DAT_40001a96 == 1`

### Blink algorithm (runs at 10 Hz)

```
if cluster_tpms_blink_timer < 650:
    increment timer
    if cluster_tpms_blink_cycle_timer == 0:
        toggle cluster_tpms_blink_state (XOR 2)
        reload cycle timer = 5
    else:
        decrement cycle timer
    drive indicator from blink_state
else:
    indicator stays solid ON
```

### Timing

| Parameter | Value |
|-----------|-------|
| Blink half-cycle | 6 × 100 ms = 600 ms |
| Full blink period | 1.2 seconds (~0.83 Hz) |
| Duration before solid | 650 × 100 ms = 65 seconds |

`cluster_indicator_flags` bit 1 = TPMS warning light output.

---

## Section 7: OBD-II Exposure

### PID 0x215 (custom) — Tire pressures

Response bytes 3–6: `tpms0, tpms2, tpms1, tpms3`
(raw sensor values, unshifted, likely 2 kPa/count)

### PID 0x216 (custom) — Status bitfield

Response bytes 3–4: high byte, low byte of
`obd_ii_tire_pressure_valid_and_error`

### OBD relearn trigger (proprietary service)

- `obd_req[2] == 5` → invoke relearn state machine
- `obd_req[3]` = desired starting state (0–5; 5 = cancel)
- Only when TPMS fitted and `CAL_ecu_flexcan_diag_bus_select != 2`

---

## Section 8: System Overview

```
             [TPMS Module]
                  |
         CAN B (FlexCAN B)
         RX 0x540, 0x256
         TX 0x220, 0x240, 0x460, 0x7A0
                  |
     +------------+------------+
     |                         |
flexcan_b_rx_540        response buffer
     |                DAT_400083c0-c5
tpms0–3                        |
obd_ii_tire_pressure_    handshake validation
valid_and_error
     |
[cluster update / 10 Hz task]
     |                    |
tpms_output          blink logic
     |
CAN A 0x402
     |
[Cluster / Dash]
```

**Init flow (startup):** `tpms_init_handshake_state_machine` runs
once, ~17 round-trips on CAN B 0x240/0x256, programs pressure
thresholds and CVN into module. Failure → `DAT_40001a96 = 1` →
warning light.

**Relearn flow (workshop):** OBD tester triggers proprietary service.
`tpms_sensor_relearn_state_machine` exchanges ~4 round-trips on
CAN B 0x240. Vehicle speed clamped to 50 km/h during process. Bit
0x200 gates speed reporting to TPMS module.
