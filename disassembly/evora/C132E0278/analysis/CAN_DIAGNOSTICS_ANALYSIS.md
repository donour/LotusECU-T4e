# C132E0278 CAN and diagnostics analysis

Target: 2019 Evora GT430 ROW/UK manual engine ECU (`C132E0278`), MPC5534.

This note is based on direct control-flow and mailbox inspection in `C132E0278.c`. It separates three protocols which share CAN hardware but are not the same diagnostic stack:

1. J1979 and Lotus-extended services over ISO-TP on CAN A.
2. A proprietary high-speed logger on CAN ID `0x350`/`0x351` (CAN A or C, calibration-selected).
3. An `ecu_unlocked`-gated raw memory access protocol on IDs `0x50` through `0x57`, replying on `0x7A0`.

## Normal diagnostic transport

| CAN ID | Direction | Role | Evidence |
|---|---|---|---|
| `0x7DF` | tester -> ECU | Functional OBD request | `flexcan_a_rx_7df`, mailbox 9 |
| `0x7E0` | tester -> ECU | Physical engine-ECU request | `flexcan_a_rx_7e0`, mailbox 10 |
| `0x7E8` | ECU -> tester | Engine-ECU response | `flexcan_a_obd_send_messages`, mailbox 0x16 |

Both receive handlers copy exactly eight CAN data bytes to `obd_ii_request` and call `obd_ii_processing`. The dispatcher interprets byte 0 as the ISO-TP PCI/length byte and byte 1 as the service/mode. It also recognizes flow-control PCI (`0x3x`) and records flow status, block size, and STmin.

Response transmission implements single frames, first frames, and consecutive frames. `obd_ii_send_200hz` advances a segmented response after flow control. STmin values in the ordinary millisecond range are quantized by the 5 ms task (`isotp_stmin / 5`); all `0xFx` values result in zero scheduler delay rather than only the ISO-TP-defined `0xF1`-`0xF9` range.

Receive behavior is more limited and is now conclusive from the application export:

- Both `0x7DF` and `0x7E0` handlers always copy one eight-byte CAN frame directly into `obd_ii_request` and immediately dispatch it.
- `obd_ii_processing` recognizes only flow-control PCI (`request[0] & 0xF0 == 0x30`). Every other PCI value is treated as though `request[1]` were a service byte.
- There is no first-frame state, consecutive-frame sequence counter, receive length, reassembly buffer, or receive timeout anywhere in this path.
- A tester first frame (`0x1n`) or consecutive frame (`0x2n`) therefore cannot form a multi-frame request and may accidentally dispatch its second byte as a service.
- The single-frame length nibble and actual CAN DLC are not validated before mode handlers index request bytes.

The supported request envelope is consequently one classic-CAN frame, normally a single-frame payload of at most seven bytes. Multi-frame **responses** are supported; multi-frame **requests** are not.

### Service map

| Request | Positive response | Observed purpose | Confidence |
|---|---:|---|---|
| `0x01` | `0x41` | Current powertrain data, including standard PIDs and Lotus PID `0x77` (charge-cooler temperature) | High |
| `0x02` | `0x42` | Freeze-frame data | High |
| `0x03` | `0x43` | Confirmed/current emissions DTCs | High |
| `0x04` | `0x44` | Clear DTCs, freeze frame, monitor state | High |
| `0x06` | `0x46` | On-board monitor test results | High |
| `0x07` | `0x47` | Pending DTCs | High |
| `0x08` | `0x48` | System-control test; PID 1 initiates the EVAP-related output/test path when engine-off | High |
| `0x09` | `0x49` | Vehicle information: VIN, calibration ID, CVN, counters, ECU name | High |
| `0x0A` | `0x4A` | Permanent DTCs, conditional on OBD calibration | High |
| `0x11` | `0x51` | Lotus extension which resets three learned/adaptation groups | High behavior; medium exact semantic grouping |
| `0x13` | `0x53` | Deferred custom DTC report combining current and mode-08-recorded DTCs | High |
| `0x14` | `0x54` | Lotus clear-DTC variant, accepted for a short request or selector `0xFF` | High |
| `0x22` | `0x62` | Lotus extended live-data identifiers | High |
| `0x2F` | `0x6F` | I/O control / actuator overrides by two-byte identifier | High |
| `0x3B` | `0x7B` | VIN programming in four chunks (VIN bytes 3 through 16); engine-stopped is the only downstream gate found | High |

Unsupported services fall through silently; there is no general negative-response handler in the dispatcher. Mode `0x2F` explicitly returns `7F 2F 22` when its operating conditions are not satisfied.

This is not a complete UDS session stack. No application handlers for DiagnosticSessionControl (`0x10` in UDS meaning), SecurityAccess (`0x27`), RequestDownload (`0x34`), TransferData (`0x36`), or ECUReset (`0x11` in UDS meaning) were found. Here service `0x10` is treated as SAE J1979 permanent-DTC mode and service `0x11` has a Lotus learned-value-reset meaning. Calling the `0x2F` implementation “UDS-shaped I/O control” is reasonable, but calling the whole application protocol UDS would overstate the evidence.

## Mode `0x2F` actuator and indication controls

The identifier is `request[2]:request[3]`. Most controls require `obd_ii_engine_speed == 0` and an engine-off settling timer to expire. Rejected conditions produce NRC `0x22`. Successful commands refresh `obd_ii_mode2f_timeout`; the 200 Hz maintenance task clears stale tests. Injector and coil pulse tests are mutually excluded by their enabled-bit groups.

| Identifier(s) | Observed control | Main conditions / notes | Confidence |
|---|---|---|---|
| `0x0100`, `0x0120`, `0x0140`, `0x0160`, `0x0180` | Supported-ID bitmaps | Discovery ranges | High |
| `0x0101`-`0x0106` | Injector pulse tests, cylinders 1-6 | Engine stopped; timed eTPU events 4-9 | High |
| `0x0121` | VVT oil-control-valve output | Engine stopped; nonzero request clipped to minimum 4 | High |
| `0x0127` | EVAP purge-valve output | Engine stopped; nonzero request clipped to minimum 4 | High |
| `0x0128` | Cluster tachometer command | Engine stopped; two-byte J1979 RPM/4 request, capped at 9000 rpm | High |
| `0x012A` | Traction/slip indicator | Available only when slip-indicator mode permits | High |
| `0x0141` | Fuel-pump output | Engine stopped; `0xFF` selects asserted state | High |
| `0x0143` | Lambda/O2 heater output | Engine stopped | High |
| `0x0144` | Coolant recirculation pump | Engine stopped | High |
| `0x0146` | A/C clutch-relay indication/control path | Engine stopped; identified by downstream `obd_ii_relay_status` use | High |
| `0x0147` | MIL/check-engine indicator | Engine stopped; downstream cluster indicator bit `0x10` | High |
| `0x0148` | Oil-pressure warning indicator | Engine stopped; downstream cluster indicator bit `0x08` | High |
| `0x0149` | EVAP vent/output solenoid | Engine stopped; downstream GPIO `0xC3`; also used by mode 08 | Medium-high |
| `0x014C` | Engine-bay fan | Engine stopped; `0xFF` selects asserted state | High |
| `0x014E` | Exhaust flap | May operate at stationary idle, unlike most tests | High |
| `0x0150` | Main cooling-fan duty | Engine stopped; byte command stored as duty request | High |
| `0x0151` | Charge-cooler pump duty | Engine stopped; byte command stored as duty request | High |
| `0x0152` | Transmission cooling pump output | Engine stopped and recirculation-pump GPIO must be inactive | High |
| `0x0153` | Transmission-fluid pump request | No engine-off check in this handler | Medium-high |
| `0x0161`-`0x0166` | Ignition-coil pulse tests, cylinders 1-6 | Engine stopped; timed eTPU events `0x12`-`0x17` | High |
| `0x0167` | Legacy variable-intake-manifold/ACIS output test | In B13200091 the same identifier and bit drive GPIO `0xC9`. GT430 retains command state but has no consumer, so it does not actuate an output in this application | High lineage; high no-op result for GT430 |
| `0x0170` | Dynamometer-mode latch | Sets `obd_dyno_mode_active`; affects wheel speed, IPS checks, sport-button CAN DTC gating, low-fuel gating, and catalyst math | High behavior; medium intended workshop meaning |
| `0x0184` | Starter relay | Ignition input off and engine stopped; request starts a bounded timer | High |
| `0x0185` | Mark engine break-in distance complete | One-way set when request byte is nonzero | High |

`0x0146` through `0x0149` were previously unlabeled in the switch. Their meanings above come from tracing each unique override bit to its downstream consumer, not from guessing adjacent identifier numbering.

## Vehicle CAN A receive map

| CAN ID | Main decoded content | Confidence / evidence |
|---|---|---|
| `0x0B7` | ABS/ESP fast and slow torque requests, active flags, rolling counter and XOR checksum | High (`flexcan_a_rx_B7`) |
| `0x0C7` | IPS TCU torque request and request-active state | High (`flexcan_a_rx_C7`; mailbox arbitration value is `0x0C7`) |
| `0x085` | Steering angle, angle rate, and three packed status bits; bytes 3-4 ignored | High (`flexcan_a_rx_85`) |
| `0x0A2` | Left/right front wheel speeds and vehicle speed | High (`flexcan_a_rx_wheelspeeds`) |
| `0x0A4` | Left/right rear wheel speeds and brake-related/status data | High (`flexcan_a_rx_wheelspeeds`) |
| `0x0A8` | ABS/ESP activity/status flags | High (`flexcan_a_rx_wheelspeeds`) |
| `0x202` | IPS selected/actual gear, shift-active and fault flags | High (`flexcan_a_rx_202`) |
| `0x250` | IPS speed-limit, fault/throttle-inhibit flags, monitor inhibits, cluster override, calibration version, oil temperature, and cruise-torque divisor | High field routing; medium physical scaling (`flexcan_a_rx_250`) |
| `0x303` | IMU yaw rate and lateral acceleration | High (`flexcan_a_rx_303`) |
| `0x310`-`0x312` | Generic four-channel 16-bit acquisition frames; stored but unused by this application | High layout; unknown vehicle meaning (`flexcan_a_rx_310_311_312`) |
| `0x350` | Proprietary logger command when high-speed logger is on CAN A | High (`flexcan_a_rx_350`) |
| `0x407` | Ambient-air temperature | High (`flexcan_a_rx_407`) |
| `0x502` | Module coding data | High (`flexcan_a_rx_502`) |
| `0x7DF`, `0x7E0` | Functional and physical OBD diagnostics | High |
| `0x50`-`0x57` | Unlock-gated raw memory commands | High |

The `0x0C7` correction matters: the old function name `flexcan_a_rx_199` expressed decimal 199, while most nearby names express hexadecimal IDs. The mailbox arbitration field and decoded TCU variables prove the on-wire ID is `0x0C7`, not `0x199`.

### Remaining receive-field details

#### ID `0x085` steering angle

| Bytes/bits | Use in GT430 |
|---|---|
| bytes 0-1 | Little-endian signed steering-angle word, typed as 0.1 degree (`data[1] << 8 | data[0]`) |
| byte 2 | Raw steering angle-rate byte |
| byte 3 bits 0-2 | Mirrored into `steering_angle_sensor_status` bits 0-2 |
| byte 4 | Received into the local buffer but never consumed |

This layout is identical in B13200091 and E132E0288. No checksum, rolling-counter, or DLC check is performed in the handler; byte 4 could carry sender metadata, but this ECU ignores it.

#### ID `0x250` IPS status

| Field | Use in GT430 |
|---|---|
| byte 0 bit 0 | Makes the byte-1 speed limit valid and sets `ips_enforce_speed_limit` |
| byte 1 | Speed-limit value; `0xFF` when inactive |
| byte 0 bit 1 | Sets engine failure flag `0x800` and a duplicated IPS status latch |
| byte 0 bit 2 | Throttle-inhibit/fault input used by throttle-control fault gating |
| byte 2 | IPS OBD/monitor-inhibit flags; bit 2 also sets `main_diagnostic_flags` bit `0x20` |
| byte 3 | Cluster indicator override copied into the upper three cluster-indicator bits |
| byte 4 | IPS calibration/version byte, compared with `(CAL_ecu_ips_calibration_version << 4) | 6` |
| byte 5 | Transmission oil temperature exposed through extended diagnostics |
| byte 6 | Cruise torque scaling divisor; accepted only when `>= 0x80` |
| byte 7 | Copied locally but unused |

This handler also performs no checksum, rolling-counter, or DLC validation. Timeouts are handled later by the CAN-monitor task rather than per-frame integrity checks.

#### IDs `0x310`-`0x312`

Each frame is exactly four big-endian 16-bit channels:

- `0x310`: stores four raw words, then creates a second set scaled as `(raw * 10) >> 2`, i.e. 2.5 times raw.
- `0x311`: stores four words directly and snapshots them into another four-word set.
- `0x312`: stores a separate four-word set directly.

There are no checksum/counter fields and none of the resulting values is read anywhere else in C132E0278. The exact same receive skeleton exists in the early NA engine firmware, the Federal GT firmware, and the IPS TCU export, also without enough semantic use to name the channels. The previous TPMS interpretation is therefore withdrawn: these IDs may be calibration/acquisition infrastructure, but their vehicle-level source and units remain unproven.

## Important transmit messages

| CAN ID | Main payload | Confidence |
|---|---|---|
| `0x102` | Net/combustion engine torque and validity state for ABS/ESP | High |
| `0x114` | Tachometer, accelerator pedal, driver/drivetrain flags; tach can be overridden by mode `0x2F/0x0128` | High |
| `0x0D2` | IPS transmission request/control message | Medium-high |
| `0x351` | Proprietary logger response/stream data | High |
| `0x400` | Cluster fuel use, fuel level, coolant temperature, warning and indicator flags | High |
| `0x403` | Fuel range/economy cluster data | High |
| `0x503` | Gear-related/body message | Medium |
| `0x7A0` | Unlock-gated raw-memory read response | High |
| `0x7E8` | OBD/extended diagnostic response | High |

## Proprietary high-speed logger (`0x350` / `0x351`)

`CAL_logger_high_speed_logger_enable` selects the bus: value 1 uses CAN A and value 2 uses CAN C. Commands arrive on `0x350`; replies and scheduled samples use `0x351`.

`logger_command_dispatch_0x350` implements the following stable command set. Cross-comparison with B13200091 supplied useful function names; the structures differ in capacity, but command semantics match.

| Command | Request/result semantics |
|---:|---|
| `0x01` | Start/open logger command session; resets all groups and the telemetry queue when entering from idle |
| `0x02` | Set stream pointer 0. `data[2]` must be zero; `data[3]` is a reserved address-space tag and bytes 4-7 are the address |
| `0x03` | Write `data[2]` bytes from the packet to stream pointer 0, advancing the pointer |
| `0x04` | Read `data[2]` bytes from stream pointer 0 into the immediate response, advancing the pointer |
| `0x05` | Close/end command session handshake |
| `0x06` | Stop, configure-only, or configure-and-arm one telemetry group; group index, message count, schedule slot, and 16-bit period are supplied |
| `0x07` | Pause streaming or stop/reset all groups depending on `data[2]` |
| `0x08` | Stop all (`data[2]=0`) or start all configured groups (`data[2]=1`) |
| `0x09` | Return the saved logger base/timer word set by command `0x11` |
| `0x0E` | Compute a 16-bit additive checksum over `length` bytes starting at stream pointer 0; work is chunked 256 bytes per scheduler call |
| `0x0F` | Set a temporary direct address and immediately read `data[2]` bytes into the response |
| `0x11` | Save stream pointer 0 as the logger base/status word returned by command `0x09` |
| `0x14` | Stop and initialize one of ten groups; clears its descriptors and resets the shared queue |
| `0x15` | Select descriptor `[group < 10][message < 12][field < 8]` for subsequent configuration |
| `0x16` | Set selected descriptor width (`1`, `2`, or `4`) and direct source address |
| `0x17` | Return logger identity-string length and metadata `0x0003008E`, while setting stream pointer 0 to the identity string |
| `0x1B` | Return the two-byte payload `02 01`; likely protocol/capability version, exact meaning unproven |
| `0x23` | Write the packet's six trailing bytes to stream pointer 0, advancing it |

Telemetry has ten groups, up to twelve eight-byte messages per group, and up to eight directly addressed fields per message. Each field width is 1, 2, or 4 bytes. The scheduler uses a group schedule slot and a 16-bit tick period, packs fields in descriptor order, and queues complete eight-byte messages. The first byte is a group/message-derived tag; bit 7 reports a prior field-build failure.

Address handling is deliberately thin: `chlog_decode_address` ignores the address-space/tag byte and returns the supplied 32-bit address unchanged. Stream reads and writes then dereference it without the flash/RAM bounds enforced by the separate unlocked `0x50`-`0x57` protocol. Logger enablement is calibration-selected, but no additional `ecu_unlocked` check appears in this command dispatcher. This is a security-relevant distinction, though practical exposure depends on whether production calibration enables logger CAN reception.

Several response status bytes resemble diagnostic negative-response values (`0x22`, `0x31`, `0x33`), but the framing is proprietary and must not be confused with UDS negative responses. No command `0x0B` case exists in this build. The precise external names for the `0x1B` version response and `0x11` saved-base value remain open.

## Unlock-gated raw memory protocol

`flexcan_a_rx_unlocked_memory_access_0x50_0x57` is enabled only when `ecu_unlocked` is true; CAN mailbox 15 is otherwise not enabled for this path. It is a direct address protocol, not ISO-TP and not UDS:

| ID | Operation | Request shape / bounds observed |
|---|---|---|
| `0x50` | read 32-bit | four-byte address; flash below approximately `0x000FFFFD` or RAM `0x40000000..0x4000FFFC` |
| `0x51` | read 16-bit | four-byte address; corresponding two-byte bounds |
| `0x52` | read 8-bit | four-byte address; corresponding one-byte bounds |
| `0x53` | block read | address plus 8- or 16-bit length; segmented raw CAN replies on `0x7A0` |
| `0x54` | write 32-bit | RAM only |
| `0x55` | write 16-bit | RAM only |
| `0x56` | write 8-bit | RAM only |
| `0x57` | block write | RAM only; first frame supplies address and length, later frames supply bytes |

An ID `0x53` request with DLC 4 returns constant `0x000CE984`; its meaning is unknown (possibly an image/build identifier or protocol capability value). No flash erase/program operation exists in this application handler. Reflash/session/security behavior should therefore be sought in `T6E_bootloader`, not inferred from this raw RAM-write interface.

`ecu_unlocked` is established directly at application startup from four calibration bytes. `CAL_ecu_unlock_magic == "WTF?"` sets it true; every other value clears it. This is therefore a calibration-selected development mode, not an unlock negotiated over the application diagnostic dispatcher. Besides enabling the `0x50`-`0x57` mailbox, it gates the 333 ms coding service and bypasses selected program/CVN validity interlocks. This is a high-confidence and security-relevant result.

The normal `0x3B` VIN-write handler does **not** check `ecu_unlocked`. `set_vin_byte` only requires the engine to be stopped, accumulates VIN positions 3 through 16, and commits them to coding/EEPROM once the full arrival mask is present. Whether an upstream tester/session convention is expected is unknown, but no in-application authorization check protects this service.

## Call flow

```text
CAN A RX interrupt
  -> mailbox-specific receive handler
     -> 0x7DF / 0x7E0: copy 8 bytes -> obd_ii_processing
        -> ISO-TP flow control, or service switch
        -> mode-specific response builder
        -> flexcan_a_obd_send_messages -> 0x7E8
        -> obd_ii_send_200hz continues segmented response
     -> 0x350: logger_command_dispatch_0x350
        -> immediate 0x351 reply or queued/scheduled telemetry
     -> 0x50..0x57 (only ecu_unlocked): direct bounded memory operation
        -> raw reply/continuation on 0x7A0
```

## Open questions and recommended next traces

1. Verify on hardware whether `0x3B` VIN programming is reachable exactly as the application trace indicates, and whether an external gateway imposes policy absent from this ECU.
2. Confirm logger address access and maximum immediate-read length on a bench ECU with logger mode explicitly enabled; source inspection shows no dispatcher bounds check.
3. Identify the actual producer and engineering units for the unused `0x310`-`0x312` four-channel frames from a vehicle capture or Lotus/Life protocol documentation.
4. Determine whether the no-op GT430 ACIS test `0x0167` is retained solely for workshop-tool compatibility or was intended to control deleted hardware.

## Confidence policy

“High” means the ID/service comparison and downstream state or hardware output are visible in the same trace. “Medium” means the ID and data path are certain but the vehicle-level name depends on surrounding variable naming. No name in this note should be treated as an OEM symbol unless separately sourced.
