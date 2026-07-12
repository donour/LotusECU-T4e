# Diagnostic Monitor Framework Analysis

## Principal correction

The 35-record structure at `0x40004D68` is not the generic OBD/DTC lifecycle table. It is a lower-level 35-channel fault-source debounce and arbitration table used by `o2_sensor_fault_detection()` and related hardware-source logic. The pending/confirmed/aging lifecycle is implemented separately by common DTC functions operating on each calibration byte, learned state byte, and fail/pass counters.

Keeping these layers separate explains why the 35 records have uniform timer fields but no DTC numbers, freeze-frame pointers, or learned-state addresses.

## 1. The 35 fault-source records

`FUN_0006A9D8()` at `0x0006A9D8` initializes 35 (`0x23`) records at `0x40004D68`, stride `0x0C`:

| Offset | Size | Meaning |
|---:|---:|---|
| `+0x00` | u8 | Last/nonzero fault-source ID |
| `+0x01` | u8 | Debounce state |
| `+0x02` | u16 | Fail/assert threshold |
| `+0x04` | u16 | Recovery/pass threshold |
| `+0x06` | u16 | Fail counter |
| `+0x08` | u16 | Recovery counter |
| `+0x0A` | u16 | Unused by the recovered consumer |

Recovered record states are:

| State | Meaning |
|---:|---|
| 0 | Idle/no source |
| 1 | Accumulating failure |
| 2 | Active/asserted |
| 3 | Accumulating recovery |

Defaults are fail `180`, recovery `1000`, with source/state/counters zero. Overrides are:

| Record indices | Fail / recovery |
|---|---|
| 1, 2, 3 | 100 / 400 |
| 4, 8, 12 | 500 / 2000 |
| 11 | 500 / 500 |
| 19..22 | 500 / 1000 |
| 25..28 | Calibration-derived / 10000 |
| 29..34 | 1 / 1 |

The per-source active map is a 34-byte area at `0x40004F0C`; `0x40001CB0` is the global any-source-fault latch. Known call sites establish indices 25..28 as four O2-heater overcurrent channels with source IDs `0x18..0x1B`, and indices 29..34 as six engine-running source bits with IDs `0x1C..0x21`.

The lower indices still need call-site/source enumeration. Their layout and state machine are high confidence; assigning physical names from thresholds alone would be speculative.

## 2. Shared DTC lifecycle

The actual generic lifecycle is centered on:

| Function | Address | Role |
|---|---:|---|
| `obd_ii_monitor_fail_transition` | `0x00068540` | Mature a failing monitor, capture snapshots, update lists/state |
| compact snapshot capture | `0x0006929C` | Capture common live values at failure |
| standard Mode $02 freeze frame | Exact export address unresolved | Select/store the reportable freeze frame |
| `obd_ii_monitor_pass` | `0x00069138` | Mark monitor completion/pass behavior |
| `obd_ii_set_active_code_and_FF` | `0x000697D4` | Drive-cycle finalization, aging, freeze-frame cleanup |
| `obd_set_dtc_processing` | `0x00069FC0` | Spread initialization/processing state machine |
| `obdii_update_dtc_state` | `0x0006A29C` | Reconcile learned state and pending/confirmed lists |

The exact Mode $02 helper address should be re-exported because the current symbol/report truncates its last digit. Its behavior and call placement are nevertheless clear.

### Configuration byte

The per-DTC calibration/configuration byte is interpreted as:

| Bits | Meaning |
|---|---|
| `0..2` | Maturation policy 1..4; zero disables the monitor |
| `0x10` | Emissions/J1979 lifecycle, snapshots, pending/confirmed/permanent processing |
| `0x20` | Additional Mode $08-related lifecycle/timer behavior |
| `0x40` | Permanent-code clearing policy |
| `0x80` | Freeze-frame priority |

Policies 1 and 4 confirm immediately. Policies 2 and 3 implement two-trip behavior: the first failing cycle arms the prior-cycle bit; a later qualifying failing cycle sets the confirmed/current bit and records the DTC.

### Learned state byte

The learned per-DTC state byte has the following recovered roles:

| Bit | Role |
|---:|---|
| 0 | Currently matured/confirmed failure |
| 1 | Retained confirmed-history/aging state; exact OEM name unresolved |
| 2 | Failed this drive cycle |
| 3 | Monitor completed this drive cycle |
| 4 | Previous-cycle failure / two-trip maturation armed |
| 5 | Pending-list insertion this cycle |
| 7 | One-time confirmed-list recording marker |

On immediate confirmation, fail transition ORs `0x0D`. Two-trip policies initially OR `0x0C`; bit 0 and confirmed recording occur only when bit 4 was already carried from a previous drive cycle. Terminal failure resets the monitor's fail/pass counters.

`obd_ii_monitor_pass()` primarily marks bit 3. Policy 4 has additional common-pass behavior when bit 0 is active.

At drive-cycle finalization, `obd_ii_set_active_code_and_FF()`:

1. ages an active bit-0 fault after more than two qualifying passed cycles;
2. promotes transient bit 7 into retained bit 1;
3. promotes pending bit 5 into prior-cycle bit 4;
4. clears failed-this-cycle bit 2;
5. clears transient bits 7 and 5.

When no current bit-0 failure remains, a calibrated warm-up threshold at `DAT_4000CA12` clears retained bit 1 and the standard freeze frame. Permanent DTCs are tracked separately in eight slots consisting of a 16-bit DTC plus status byte.

## 3. Freeze frames and event snapshots

For configuration bit `0x10`, failure first captures a compact common snapshot including RPM, MAF, road speed/load, coolant/IAT/TPS, trims, and O2 values.

The standard Mode $02 freeze frame is replaced only when no frame exists or the incoming DTC has priority bit `0x80`. `obd_ii_DTC_causing_FF` stores the packed P/C/B/U code.

Five additional event-snapshot slots beginning near `0x4000491A` retain per-DTC data such as DTC, RPM, load, MAF, and counters for applicable policies. These event slots are distinct from the single reportable Mode $02 freeze frame.

## 4. Initialization and monitor families

`obd_set_dtc_processing()` is a spread state machine with states `0..0x19`. Rather than initializing every monitor in one long call, it processes monitor families over successive invocations. Recovered families include sensors/injectors, catalyst, fuel trim, O2, crank/cam, idle, misfire, ECU, EVAP, thermostat, VVT, throttle, A/C, CAN, fuel-pump, and transmission diagnostics.

Representative consumers confirm that all these families share the DTC lifecycle rather than the 35-source record array:

- crank/cam diagnostics include P0335, P0341, P0346, P0366, and P0391;
- throttle diagnostics include P2135 and the P210x/P2119/P0638 paths;
- sensor and actuator groups pass their own learned state and counters into the same fail/pass helpers.

## 5. Layered fault flow

```text
raw hardware/source condition
    -> optional 35-record debounce/arbitration
    -> subsystem fault flags
    -> monitor-specific enable and qualification logic
    -> common fail/pass transition
    -> learned DTC state byte + fail/pass counters
    -> pending / confirmed / permanent lists
    -> freeze frame and drive-cycle aging
```

Not every DTC uses the 35-source table, and one fault-source record can feed subsystem logic before a particular DTC monitor is enabled. This distinction should be preserved in future renaming and documentation.

## Remaining work

1. Enumerate all callers supplying record indices 0..24 and map their source IDs.
2. Verify the exact name/semantics of learned-state bit 1 against list-management consumers.
3. Recover the exact Mode $02 freeze-frame helper address from the original Ghidra project.
4. Map the eight permanent-DTC slots and five event-snapshot slots byte-for-byte.
5. Document drive-cycle and warm-up-cycle qualification inputs that trigger finalization.

Confidence is high for the 35-record layout, its separation from DTC state, the principal learned bits, and immediate/two-trip transitions. The OEM term for bit 1 and unidentified low-index hardware sources remain medium/low confidence.
