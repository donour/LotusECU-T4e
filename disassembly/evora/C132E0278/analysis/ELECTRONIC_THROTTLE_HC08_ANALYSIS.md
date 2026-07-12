# Electronic Throttle and HC08 Safety-Supervisor Analysis

## Scope and principal conclusion

This document traces the C132E0278 electronic-throttle path from the accelerator pedal to the motor drive, then back through redundant position sensing, the HC08 safety processor, limp behavior, and OBD fault reporting.

The most important architectural result is that the HC08 is **not the primary throttle motor controller**. The MPC5534 executes the 1 kHz position loop, including redundant-TPS selection, PI/feed-forward control, battery-voltage compensation, direction output, and eMIOS PWM. The HC08 independently observes redundant analog signals and a timer-captured position representation, runs plausibility/self-test state machines, and asserts separate fault and shutdown outputs. It is therefore best described as an electronic-throttle safety supervisor/interlock.

This corrects the provisional model in which throttle feedback control and motor output were assigned to the HC08. The safety boundary is still central: normal motor operation requires the MPC control path and the HC08 supervisory path to agree.

Sources used:

- `C132E0278.c` and `C132E0278_symbols.csv`: MPC5534 application decompilation and address export.
- `TPS_control.txt`: prior pedal/request/limit analysis.
- `../t6_etb_hc08_C132E0278/hc08_firmware.c`: native HC08 decompilation.
- `../T6E_bootloader/T6E_bootloader.c`: embedded-HC08 programming path.

Unless stated otherwise, MPC function addresses below are exported symbol addresses. HC08 behavior is high-confidence from the decompilation, but most HC08 function addresses require a fresh native binary/Ghidra symbol export.

## End-to-end control path

```text
pedal tracks D/E
    -> MPC ADC conversion, shaping, and redundant validation
    -> 200 Hz pedal-map selection
    -> torque/rev/misfire/warmup/brake/idle limiting
    -> bidirectional command smoothing
    -> 1 kHz MPC TPS validation and position controller
    -> MPC direction GPIO + eMIOS PWM + bridge enable
    -> throttle motor and spring-loaded throttle body
    -> TPS tracks A/B
       |-> MPC 1 kHz feedback and diagnostics
       `-> HC08 ADC/captured-position plausibility monitor
             -> HC08 fault/shutdown discrete interlocks
             -> eSCI state/status -> MPC fault and OBD propagation
```

There are three different state variables which must not be conflated:

| State | Owner | Purpose |
|---|---|---|
| `etb_initialization_state` | MPC | Local calibration/controller lifecycle: init, closed-stop learning, normal, fault |
| `throttle_control_mode` | MPC | Requested operating/degradation mode sent to the HC08 |
| `throttle_actuator_state` | HC08, received by MPC | Safety-supervisor lifecycle `TSL_INIT` through `TSL_RUN`, `TSL_FAULT`, and `TSL_SHUTDOWN` |

## 1. Pedal input and torque request generation

`accel_pedal_position_from_voltage()` at `0x000C1638` converts and validates the two accelerator tracks. `accel_pedal_200hz()` at `0x00095524` then selects a 16-point TPS-versus-pedal table using transmission coding, Tour/Sport mode, low-gear selection, and IPS shift state. The table families and selection matrix in `TPS_control.txt` remain valid.

The principal values are:

| Value | RAM address | Meaning |
|---|---:|---|
| `tps_target` | `0x40002134` | Raw selected pedal-map request, 0..1023 |
| `tps_requested_scaled_by_limit` | `0x4000212C` | RPM-scaled request, 0..1023 |
| `tps_requested_scaled_by_limit2` | `0x4000212E` | Eight-bit companion value |
| `obd_ii_commanded_throttle_actuator` | `0x4000245C` | Final smoothed command, 0..4095 |

An invalid/overridden pedal condition can force the raw target to zero. Brake/wheel-deceleration logic can clamp it to `CAL_tps_brake_safety_floor`. While the engine is running, the request is also scaled by the RPM-dependent `CAL_tps_scaling_factor_rpm` result.

This is a pedal-to-position request path, but it is not independent of the torque model. `throttle_and_torque_control()` at `0x000AB0A0` combines the scaled pedal request with idle demand and subjects it to the current torque ceiling.

## 2. TPS limiting and smoothing

The effective limiting chain in `throttle_and_torque_control()` is:

1. Combine scaled pedal TPS and `idle_tps_requested`.
2. Apply the configured rev-limit TPS ceiling.
3. Convert an active torque ceiling into a TPS ceiling.
4. Apply sensor/pedal degradation, severe-misfire, and engine-failure caps.
5. Apply the warm-up maximum and `CAL_tps_min`.
6. Apply left-foot-brake maximum unless an earlier torque reduction has precedence.
7. Rate-shape the surviving command.
8. Reapply the fixed fault command if TPS/system fault state requires it.

The torque conversion is more than a static lookup. `calc_tps_for_torque_limit()` at `0x000BD570` converts the torque limit to net torque, accounts for friction, ignition retard, and cylinder availability, maps torque to load, and calls `calc_load_to_tps()` at `0x000BD3E4`. The feed-forward TPS value combines the calibrated 20x20 load-to-TPS map with the learned 20x20 `LEA_torque_torque_to_tps_scaling` surface and density compensation. When limiting is active, a load-error PI term corrects the result against measured MAF load.

Smoothing is asymmetric and mode-sensitive:

- Opening uses parking, Tour, or Sport delta tables, with a minimum step derived from neutral or RPM calibrations.
- Closing uses delta and RPM tables with gear/transmission compensation and optional cruise scaling.
- Updates are paced by `CAL_tpssmooth_step_timer`.
- Certain torque-limit and rev-limit interventions bypass the drivability ramp and jump directly to the safe limited request.
- A TPS fault or confirmed system fault overrides the result with `CAL_tps_commanded_during_fault << 4`.

The decompiled `TPS_SMOOTH_STEP_UP`/`DOWN` names appear reversed relative to the numerical direction in part of this routine. Treat those enum labels as uncertain; the arithmetic direction is clear.

## 3. MPC ETB initialization and calibration

`tps_control_1000hz()` at `0x000AC330` owns the local ETB lifecycle:

| State | Behavior |
|---|---|
| `ETB_INIT` | Disable PWM/bridge; select a 1000-tick first delay or 100-tick retry delay |
| `ETB_INIT_DELAY` | Wait before attempting closed-stop calibration |
| `ETB_CALIBRATE_START` | Reset the closed-position search |
| `ETB_CALIBRATE_MONITOR` | Drive/observe closure, require stable readings, capture both tracks |
| `ETB_CALIBRATE_RANGE` | Validate closed values and calculate track shaping |
| `ETB_CALIBRATE_DEFAULT` | Install fallback closed values `0x23C/0x725` and latch calibration failure |
| `ETB_FIRST_CYCLE` | Validate tracks, initialize controller history, issue the first command |
| `ETB_NORMAL` | Run redundant validation, request generation, safety checks, and motor control |
| `ETB_FAULT` | Mark confirmed fault, disable drive, and set engine failure state |

The closed-position monitor accepts track A in approximately `0x1FF..0x26A`, requires stability for more than 49 samples, and times out after roughly 1000 1 kHz iterations. A retry result returns to init; a persistent failure records fault data and enters fault. Low ECU voltage during calibration states can select the default values instead. Default calibration is degraded startup, not immediate shutdown: `throttle_calibrate_fail` is set, but execution proceeds to the first control cycle.

The decompiler output for the tail of `tps_calibrate_range()` contains unrelated-looking code. The range constants and fallback behavior are well supported, but its exact return-bit semantics should be checked in the original Ghidra listing.

The MPC forces `ETB_FAULT` when any of these supervisory conditions is present:

- left-foot-brake fault bit 3;
- engine failure bit `0x10000`;
- the latched P2107 path (`DAT_40001CC9`);
- HC08 `throttle_actuator_state >= TSL_FAULT`;
- locally confirmed TPS system fault.

## 4. MPC feedback controller and motor output

`throttle_command_actuator()` at `0x000ABDD8` proves that the MPC owns the inner motor loop. It contains:

- position-error proportional action;
- an accumulated and clamped integral term;
- a throttle-position feed-forward table;
- an optional position-history/derivative-like correction;
- battery-voltage normalization;
- calibrated duty limiting;
- direction selection on `siu_gpdo[0xBB]`;
- PWM output through `set_throttle_pwm()` at `0x000AA808`;
- bridge enable on `siu_gpdo[0xCC]`.

Calibration-state drive is capped at 50%. A sustained high-duty condition also falls back to the 50% cap after 100 iterations. PWM is forced to zero if TPS is faulted, the selected track is out of range, or the key-off/stopped condition applies. `throttle_disable()` at `0x000AAB6C` sets PWM to zero, direction high, and bridge enable low.

Therefore the HC08 cannot accurately be described as producing the throttle motor PWM or closing the main position loop. Its discrete outputs instead provide an independent hardware safety authority. The precise electrical destinations of those outputs still require board/schematic tracing.

## 5. eSCI transport and messages

### MPC driver

| Function | Address | Role |
|---|---:|---|
| eSCI-A initialization | `0x000B8D74` | Configure eSCI-A, pins `0x59/0x5A`, interrupt source `0x92` |
| RX ring dequeue | `0x000B8E3C` | Remove from 32-byte ring at `0x40007F78` |
| RX ISR | `0x000B8EA0` | Read byte and enqueue; drops bytes if full |
| TX staging | `0x000B8F1C` | Copy frame to `0x40007F58`, transmit first byte |
| TX ISR | `0x000B8FD0` | Transmit remaining bytes and disable TX interrupt |
| Combined ISR | `0x000B9060` | Service RX then TX |
| Frame parser | `0x000B9084` | Length, timeout, checksum, and sequence validation |
| Frame builder | `0x000B9220` | Append sequence and checksum |
| Command sender | `0x000B92BC` | Send type `0x81` command/status request |
| Response handler | `0x000B936C` | Decode CRC or normal status response |

The wire format is:

```text
[LEN] [TYPE + PAYLOAD (LEN bytes)] [SEQ] [~SUM(LEN through SEQ)]
```

`SEQ` increments for each MPC request. The HC08 echoes that sequence in its response; the MPC rejects a valid-checksum frame with the wrong sequence. Both sides use 32-byte receive rings. The MPC parser permits at most 23 total bytes and resets a partial frame after six 5 ms ticks, approximately 30 ms.

The MPC command is seven bytes total:

```text
04 81 MM FF PP SS CC
```

- `MM`: low seven bits are `throttle_control_mode`; bit 7 is a configuration/mode bit.
- `FF`: `throttle_control_flags`, including selected pedal/TPS tracks, engine failure, Sport, and transmission information.
- `PP`: high eight bits of the final commanded position, also used as the self-test position/offset input.
- `SS`: sequence.
- `CC`: complemented additive checksum.

`HC08_com()` at `0x000737D8` sends every `0x14` 5 ms ticks, or approximately 100 ms, then drains received frames.

### HC08 responses

Type `0x80` is a CRC response with two CRC bytes. Type `0x81` has `LEN=0x14` and is 23 bytes total:

| Frame index | Meaning |
|---:|---|
| 1 | Type `0x81` |
| 2 | HC08 `TSL_*` state |
| 3 | HC08 status flags |
| 4..6 | TPS1, TPS2, and cross-check reference |
| 7 | ADC channel 7 sample |
| 8..10 | Rotating/history diagnostics |
| 11..12 | Auxiliary ADC channel 3/9 samples |
| 13..14 or parser `[0x0E..0x0F]` | Firmware/calibration CRC bytes, depending on payload/frame indexing convention |
| 16..20 in the MPC parse buffer | Five maximum debounce/monitor counters |

The field ordering is proven by reciprocal construction and parsing. Some physical channel names and the exact semantics of the rotating history fields remain unknown.

The eSCI baud rate is not established by the decompilation alone. It should not be labeled 115200 without decoding `LPR=0xC5990000` against the actual peripheral clock.

## 6. HC08 safety monitoring

The native HC08 image is decompiled under `disassembly/evora/t6_etb_hc08_C132E0278`. Its startup initializes PTD3/PTD4 as outputs, timer input capture, SCI, tick state, ADC state, and the monitor state machine. Initial outputs release shutdown (PTD3 high) and fault (PTD4 low).

### Inputs and plausibility checks

`adc_sample_all()` samples ADC channels 2, 4, 6, 1, 3, 7, and 9. `linearize_tps_channels()` selects track sources and breakpoint sets using incoming calibration-selection bits and normalizes both throttle tracks to 0..255.

The main redundant check maps one track through a 16-point expected-track table and compares the result with the other track using calibrated bias, threshold, and debounce values at HC08 ROM `0xDC12..0xDC67`. In `TSL_RUN`, a separate absolute ceiling check is applied to the second track.

A timer input-capture ISR also measures a periodic/pulse-width-coded signal, which `compute_position_scaled()` converts to an independent position representation. This captured value participates in command/position plausibility and self-test logic. Its physical source should be confirmed from the board schematic, but its existence shows that the HC08 does more than re-read the same two TPS ADC channels.

### HC08 state machine

| Value | State | Meaning |
|---:|---|---|
| 0 | `TSL_INIT` | Reset/handshake |
| 1..3 | `TSL_MODE_1..3` | Preliminary operating handshakes |
| 4..6 | `TSL_MONITOR_4..6` | Armed self-tests/auxiliary checks |
| 7 | `TSL_REARM` | Re-arm tests and await run |
| 8 | `TSL_RUN` | Normal independent monitoring |
| 9 | `TSL_FAULT` | Assert fault output |
| 10 | `TSL_SHUTDOWN` | Assert fault and shutdown outputs |

Commands 4, 5, and 6 exercise bounded self-tests using the MPC-supplied position offset and calibrated thresholds/timeouts. Command 6 also checks auxiliary ADC channels 3 and 9; an incoming flag can disable the channel-9 check. A self-test failure disarms that test and returns to rearm rather than immediately entering the terminal fault state.

In `TSL_FAULT`, the HC08 continues monitoring ADC channel 7. A sustained value beyond its calibrated threshold escalates to `TSL_SHUTDOWN`. An incoming calibration-selection bit `0x04` can also force shutdown.

Fault assertion is monotonic: once state 9 is reached, ordinary release logic cannot clear PTD4; state 10 similarly latches the shutdown output. Recovery therefore requires HC08 reset. The likely physical result is driver inhibit followed by mechanical spring return, but the exact interlock circuit must be confirmed from the schematic.

No explicit HC08 COP/watchdog feed was identified in the decompiled firmware. The default unexpected-interrupt path enters a fail-stop-like loop through SWI, but native vector and COP configuration review is still required before claiming complete watchdog coverage.

## 7. Communication watchdogs and fault propagation

The two processors watch each other independently:

- HC08: a valid command reloads `comm_timeout=100`. Expiry sets status bit `0x08` (`SF_COMM_LOSS`) and enters `TSL_FAULT`. The exact HC08 tick period remains to be established.
- MPC: a valid response reloads a 100-count timer decremented at 200 Hz, giving approximately 500 ms. Expiry flushes the receive ring and sets status bit `0x80` locally.
- MPC CRC: the received HC08 CRC is checked against the expected result. A mismatch injects status bit `0x40`; this bit is MPC-generated rather than an HC08 native flag.

The MPC begins with `hc08_crc16=0x25FE`; `HC08_check_CRC()` tests the complementary representation against `0xDA01`. This awkward representation should be preserved when describing or patching the check.

Fault propagation to diagnostics is explicit:

| DTC | Trigger in this path |
|---|---|
| P2104 | HC08 state at/above fault, or MPC severe-fault mode |
| P2105 | HC08 `TSL_SHUTDOWN` |
| P2107 | HC08 CRC mismatch `0x40` or MPC communication timeout `0x80`; persistent failure latches the MPC ETB fault path |
| P2100/P2102/P2103/P2108 | Individual captured TPS/actuator error bits |
| P2106 | Degraded pedal or TPS state |
| P2119 | Throttle-body calibration/range-performance failure |
| P0638 | Commanded-versus-observed throttle actuator performance model |

Thus a single fault has two routes to safety: the HC08 can assert hardware interlocks without waiting for MPC software, and the MPC can independently disable PWM/bridge and enter its local fault state based on sensor, serial, CRC, or HC08-state evidence.

## 8. Embedded HC08 image and boot boundary

`HC08CODE_base` at MPC flash `0x00040080` is a bootloader descriptor containing the ASCII name `HC08CODE`, a programming magic value, and a firmware pointer. `HC08_firmware` points to `0x000D13F0`.

The original image confirms a `0x2400`-byte payload at MPC flash
`0x000D13F0..0x000D37EF`, mapped natively at HC08 `0xDC00..0xFFFF`. Its SHA-256 is
`6cf23591de05c6720e050b150458b1dfa04ee78104bfee052e4cd0b7f2c2911f`.

Native vector recovery gives:

| HC08 vector slot | Handler | Proven role |
|---:|---:|---|
| `0xFFE2` | `0xEACD` | SCI transmit ISR; advances the TX buffer and writes SCI data `0x18` |
| `0xFFE4` | `0xEA9D` | SCI receive ISR; reads SCI data `0x18` into the 32-byte RX ring |
| `0xFFEC` | `0xEF01` | timer-overflow/base-tick ISR; clears timer status and services countdowns |
| `0xFFF4` | `0xE8FE` | timer input-capture/period-state ISR |
| `0xFFFE` | `0xDC89` | reset entry; initializes SP to `0x015F`, peripherals, then enables IRQs |

Bytes `0xFFF6..0xFFFD` contain the identifier `EFI Srl ` rather than live vector pointers; unused
slots are `0xFFFF`.

The normal MPC application does not execute or reference the blob. The T6E bootloader validates the descriptor/name/magic, retrieves the firmware pointer, and programs the HC08. At runtime, the only operational boundary is eSCI plus reset and discrete safety GPIOs.

## 9. Remaining evidence needed

The software-level actuator analysis is now substantially complete. The remaining gaps are narrower and evidence-specific:

1. Convert the HC08 peripheral addresses into the exact controller-variant register names and finish
   COP/watchdog review.
2. Combine HC08 SCI baud register `0x19 = 0x02` and MPC eSCI `LPR=0xC5990000` with verified clocks to
   establish the exact baud/frame configuration.
3. Derive the base tick from timer control `0x30 = 0x53` and modulo `0x0C26` once the HC08 bus clock
   is established.
4. Trace HC08 PTD3/PTD4, captured-timer input, ADC channels 3/7/9, MPC GPIO `0xBB/0xCC`, and eMIOS output to ECU connector pins and the H-bridge schematic.
5. Capture a live request/response exchange to validate cadence, sequence echo, diagnostic fields,
   and both communication timeouts.

## Confidence summary

- **High:** MPC owns the motor loop/PWM; HC08 is a safety supervisor; pedal/limit/smoothing flow; three separate state machines; reciprocal serial framing; status/command core fields; redundant TPS checks; fault/shutdown latching; MPC OBD propagation.
- **High:** embedded HC08 payload boundary, reset/SCI RX/SCI TX/timer vector addresses, and raw SCI/
  timer setup values.
- **Medium:** physical meaning of the timer-captured signal and auxiliary ADC channels; external electrical effect of PTD3/PTD4.
- **Low/unresolved:** exact UART baud and scheduler tick without verified clocks, plus complete
  COP/watchdog behavior.
