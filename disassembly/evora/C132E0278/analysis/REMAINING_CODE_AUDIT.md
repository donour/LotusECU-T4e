# C132E0278 remaining-code leverage audit

## Purpose and method

This is a stopping audit of the still-generic `FUN_`/`DAT_` regions after the subsystem reports in this directory were completed. It ranks code by behavioral leverage rather than by symbol count alone. The review used textual callers, nearby named state, MMIO access patterns, repeated channel structure, and downstream consumers. Definition-only functions were not automatically treated as dead: several are interrupt-vector targets whose references are absent from the C export.

The headline result is that most remaining generic functions are platform glue, interrupt acknowledgements, tiny output wrappers, or compiler/runtime support. The best remaining engine-behavior finds were at callback boundaries where the export had lost vector xrefs.

## Ranked disposition

| Rank | Generic area before this pass | Connectivity / evidence | Behavioral leverage | Disposition |
|---:|---|---|---|---|
| 1 | `FUN_00047934`–`FUN_000484ec` | Six same-shape, definition-only eTPU handlers; each acknowledges a distinct ignition channel and manipulates the corresponding cut/fire bit | High: final per-cylinder enforcement of startup inhibit, injection cut, per-cylinder cut, bank misfire protection, coil fault protection, and sequential re-enable | Resolved as `ignition_cylinder1_event_isr()` through `ignition_cylinder6_event_isr()` |
| 2 | `FUN_0007b2c8` | Called from crank-event processing with an interval and decoded cylinder; its two six-element histories are consumed by `misfire_detect_per_cylinder_200hz()` | High: hardware timing input to combustion-roughness/misfire logic | Resolved as `misfire_record_cylinder_interval()` |
| 3 | `FUN_0004561c` | Called at the end of crank-event processing; checks six evenly spaced event positions and previous-position progression | High: crank/cylinder sequence validation upstream of event confidence | Resolved as `crank_event_sequence_monitor()` |
| 4 | `FUN_00042290`, `FUN_00042440`, `FUN_00042520`, `FUN_00042534`, `FUN_00053964`, `FUN_00053a90`, `FUN_00053bc4`, `FUN_00053fb0` | Highest textual call counts (up to 21), but all operate on eTPU code/parameter RAM, allocate parameter blocks, read 8/24-bit fields, or instantiate channels | Low strategy leverage; high platform-documentation leverage | Leave generic pending an eTPU ABI/type reconstruction pass |
| 5 | `FUN_00048870`, `FUN_000adb38` | Original image recovered from git history resolves vectors `0x47` and `0x63` as eTPU channels 3 and 31 | Medium-high hardware-boundary value | Resolved as auxiliary crank-sync/reference and knock-window-boundary callbacks; exact proprietary channel-3 microfunction remains unknown |
| 6 | `FUN_0006a9d8` and its surrounding 35-entry state array | Twelve-byte records contain source/state, fail/recovery thresholds, and counters | Medium diagnostic-boundary value | Resolved as low-level fault-source debounce/arbitration, separate from the common DTC lifecycle |
| 7 | `FUN_0004b870`, `FUN_0004b8bc`, `FUN_0004b964` | Register offsets identify eMIOS channels 6, 5, and 9; downstream math identifies vehicle-speed and A/C compressor-speed periods | Medium sensor-boundary value | Channel 5 is vehicle/wheel speed, channel 9 is A/C compressor speed, channel 6 callback appears dormant after repurposing as throttle PWM |
| 8 | `FUN_0005a18c` | Clears four adjacent 32 x u16 persistent buffers at `0x40003f54..0x40004053` plus associated counters | Medium implementation value, low new-strategy value | Physical layout resolved; subsystem semantics still need producer/consumer recovery |
| 9 | `FUN_000b8d74`, `FUN_000b8ea0`, `FUN_000b8fd0`, `FUN_000b9060` | eSCI setup plus 32-byte RX ring-buffer and TX interrupt service used by HC08 communication | Low powertrain-strategy value | Serial-driver cluster; safe to rename only during a dedicated HC08 protocol pass |
| 10 | `FUN_000b49e4`–`FUN_000b5cc4` | FlexCAN mailbox/interrupt flag acknowledgements, usually one register write and no control calculation | Low | CAN driver residue; message behavior is already described by named TX/RX routines and the CAN report |
| 11 | `FUN_00098bc4`, `FUN_000beeb8`, `FUN_000737a0`, `FUN_000b066c` | One-line eTPU-channel setters, HC08 reset GPIO release, and a scalar setter | Low | Tiny wrappers; names require resolving the attached output/signal, not more control-flow reading |
| 12 | `FUN_00040a14`, `FUN_000cbea8`, `FUN_000cbedc`, `FUN_000cbff0`, `FUN_000cc034` | Descriptor/singleton setup and teardown around library code; no engine-state decisions | None for firmware strategy | Compiler/runtime support |

## Findings resolved in this pass

### Per-cylinder ignition interrupt enforcement

The six handlers at `0x47934`–`0x484ec` are interrupt callbacks, which explains why textual caller ranking initially hid them. Each handler:

- acknowledges its eTPU ignition event;
- participates in the shared ignition-startup delay;
- suppresses the cylinder for ignition-off state, a per-cylinder event fault, the applicable bank misfire flag, or its coil-pack fault bit;
- distinguishes an ordinary no-fire command from a fault-forced safe state;
- updates `ign_cyl_cut_flags` and `cyl_fuelcut_sparking_mask`;
- advances the per-cylinder re-enable countdown in firing-order-dependent fashion; and
- updates the rotating cylinder anchor used by later combustion processing.

The odd physical cylinders use bank flag `0x20`; the even physical cylinders use `0x40`. This confirms that bank-wide catalyst-protection cuts reach the hardware boundary in the ignition event ISRs, not only in the slower diagnostic logic.

### Crank sequence and misfire timing handoff

`crank_event_sequence_monitor()` recognizes event positions `7, 0x13, 0x1f, 0x2b, 0x37, 0x43`, spaced by 12 teeth/events, and sets one validity bit only when the previous position matches the expected predecessor. The associated state is reset to invalid by the unresolved callback at `0x48870`.

At crank positions `4, 0x10, 0x1c, 0x28, 0x34, 0x40`, the crank routine maps the event into cylinder order, computes a 24-bit interval, and calls `misfire_record_cylinder_interval()`. That function retains current and previous intervals for all six cylinders and records the last cylinder. The 200 Hz misfire detector then compares these histories. This closes the trace from eTPU crank timing to cylinder-specific misfire classification.

## Unresolved high-value candidates

1. **Channel-3 eTPU microfunction identity.** The raw vector proves that `FUN_00048870` is eTPU channel 3's auxiliary crank-sync/reference event, but proprietary eTPU metadata is still needed to distinguish the exact reference/sync-loss condition.
2. **eMIOS5 connector assignment.** Its vehicle/wheel-speed behavior is proven by the consumer; the connector pin requires an MCU-ball/netlist schematic. eMIOS9 correlates to pin `LC1 AC COMP SPEED SIG`.
3. **Low-index fault-source identities.** The 35-record layout and high-index O2/engine-running users are recovered; indices 0..24 still need complete caller enumeration.

The raw image closed two former candidates: the torque-to-TPS density-normalized index is
now reconstructed from `0x6167C..0x61700`, and the four persistent buffers are electronic-throttle
calibration/fault histories produced by `tps_capture_fault_data()`.

These are good targets only if additional artifacts are available. More reading of the same C text is unlikely to settle their exact identities.

## Low-value and decompiler-residue categories

Remaining generic `DAT_` names are dominated by:

- MMIO register aliases where the peripheral base is known but the generated field name is not;
- eTPU parameter RAM whose meaning depends on channel-function ABI and byte offsets;
- packed diagnostic records expressed as byte arithmetic instead of structures;
- calibration-table axes or overlapping symbols whose boundaries were lost;
- interrupt counters, watchdog latches, queue cursors, and transport scratch state;
- compiler temporaries, singleton/guard state, and runtime descriptors; and
- duplicate/overlapping function interpretations, including suspicious recursive names in FlexCAN interrupt output.

Bulk-renaming these from proximity would create false certainty. Structure definitions, vector references, and peripheral metadata will improve them more than another prose pass.

## Diminishing-returns judgment

Further **C-export-only** passes now have sharply diminishing returns for C132E0278. The major control strategies and their hardware boundaries are covered by the subsystem reports, and this audit resolved the last obvious high-leverage generic callback cluster. The remaining high-count functions are mostly reusable drivers; the remaining behaviorally interesting functions lack precisely the xrefs and types discarded by export.

The next productive work should use at least one of:

- the original binary/project with Ghidra vector-table and reference navigation;
- eTPU microcode/function metadata and parameter-RAM layouts;
- MPC5534 interrupt and peripheral structure typing;
- board pin/schematic correlation for eMIOS and GPIO signals;
- runtime logs that correlate unknown state with crank sync, knock windows, and diagnostic transitions; or
- cross-firmware differential analysis to identify calibration and implementation changes.

Without those, future passes should be narrowly hypothesis-driven rather than another whole-file naming sweep.
