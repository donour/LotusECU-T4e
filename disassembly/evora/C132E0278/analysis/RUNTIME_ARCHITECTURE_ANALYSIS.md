# C132E0278 runtime architecture

Target: 2019 Evora GT430 ROW/UK manual engine ECU (`C132E0278`), MPC5534.

This note describes verified application runtime structure: reset/startup, memory images, foreground and interrupt execution, persistence, coding flash, ignition-off after-run, and shutdown. Function names in the export remain analyst names unless explicitly stated.

## Executive model

The application is not a single 1 kHz cooperative scheduler. It has three execution layers:

1. A continuously running, non-blocking background engine-control loop in `main`.
2. A hardware-timed 2000 Hz eMIOS interrupt which owns deterministic periodic task groups down to 1 Hz.
3. Higher-priority event interrupts for eTPU engine events, knock acquisition, sensor edges, and CAN mailboxes.

The background loop performs the primary fuel, spark, load, torque, throttle-request, cooling, diagnostic-state, HC08 communication, and output calculations as fast as execution and preemption allow. The 500 us interrupt supplies fixed-time filters, watchdogs, rate-limited controls, timeout accounting, learning, and slower housekeeping. eTPU/eQADC/eDMA provide crank-angle and acquisition timing independently of either software loop.

## Verified startup flow

```text
reset/application entry: init
  -> configure flash bus interface
  -> clock/FMPLL and low-level TLB/cache setup
  -> initialize/clear RAM and install INTC setup trampoline
  -> copy initialized runtime data from flash to RAM; clear BSS segments
  -> initialize SIU/EBI segment
  -> main
     -> fill 0x4000F000..0x4000FDFF with 0x55 stack/free-RAM sentinel
     -> init_devices
        -> copyCAL2RAM
           -> copy calibration flash 0x00020000... to RAM near 0x40008652
           -> copy/validate coding 0x0001C000 -> COD_base 0x40008060
           -> calculate calibration verification number
           -> derive ecu_unlocked from CAL_ecu_unlock_magic
        -> decode coding and initialize supported diagnostic identifiers
        -> EEPROM_load: load and validate learned image 0x00010000 -> LEA_base
        -> configure SIU, eDMA, eQADC, pin mux, eMIOS, DSPI, eTPU
        -> initialize ignition drivers, CAN A/C, throttle, VVT, fuel, knock, HC08
        -> enable INTC handling
     -> init_globals
     -> enter infinite background engine-control loop
```

### Early runtime segment initialization

`data_segment_setup___` directly copies 5704 bytes (`0x1648`) from flash around `0x000D38C8` to RAM beginning at `0x40000000`. A generic segment-table implementation (`init_segment`) also exists in the export, but the reset trace calls the fixed-copy helper. This area contains initialized runtime globals rather than calibration or learned data.

`init_ram_pattern_fill` decompiles poorly and appears polluted by saved-register values; its broad purpose as early SRAM/cache initialization is credible, but individual apparent stores should not be treated as an intentional C structure.

## Memory and persistence map

| Address/range | Role | Evidence and confidence |
|---|---|---|
| `0x00010000` | Learned/adaptation and diagnostic flash image | `EEPROM_lea_base`, explicit erase/write/load; high |
| `0x0001C000` | Variant coding, VIN, model, CRC flash image | `EEPROM_variant_coding`, 68-byte load/write; high |
| `0x00020000` | Calibration flash image base | `copyCAL2RAM` source and coding-write upper bound; high |
| approximately `0x00040000...` | Application code and constants | Function addresses and segment metadata; high base, exact upper boundary not established |
| around `0x000D38C8` | Initial values for low RAM `.data` | fixed 5704-byte startup copy; high |
| `0x40000000...` | Initialized/transient runtime globals | startup data destination; high |
| `0x400030E8` | `LEA_base`, learned RAM image | loaded/saved length `0x1BE4`; high |
| `0x40008060` | `COD_base`, live 68-byte coding structure | copied from `0x1C000`; high |
| near `0x40008652` | Calibration RAM shadow | approximately `0x69AC` bytes copied from `0x20000`; high size, two-byte start ambiguity from decompilation |
| `0x4000F000..0x4000FDFF` | free-RAM/stack watermark sentinel | filled with `0x55555555`, scanned from low to high; high |
| `0x40010000` | top of 64 KB internal RAM | free-RAM calculation and debug-memory bounds; high |

### Calibration shadow

`copyCAL2RAM` performs `0x1A6B` iterations copying two 16-bit words per iteration: approximately `0x69AC` bytes. The decompiler expresses the first source/destination accesses awkwardly (`0x1FFFE`, `0x40008652` with pre-incremented pointers), while symbols begin the human-readable header at `CAL_base = 0x40008654`. The stable conclusion is that flash calibration beginning at `0x00020000` is shadowed into RAM through approximately `0x4000EFFF`; exact first-word alignment should be checked in assembly before reconstructing a binary patcher.

Runtime code reads and occasionally modifies `CAL_*` symbols in this RAM shadow. Changes are therefore live RAM calibration changes unless an external reflash process updates the flash image.

### Free-RAM watermark

Before device initialization, `freeram_fill_0x55` fills `0xE00` bytes at `0x4000F000`. Each background-loop iteration, `freeram_counter` checks four words and advances the scan pointer until the sentinel has been disturbed. This is a stack/high-water monitoring mechanism, not allocator-managed heap space. Once corruption is seen, `free_ram_overrun_flag` latches and the pointer backs up one block.

## Execution and timing model

### Background loop

`main` contains no explicit delay, event wait, or 1 ms gate. Each iteration:

- services knock DSP setup/processing and retriggers the watchdog;
- reads serial peripherals and current eQADC/eDMA samples;
- advances OBD state and engine speed/load calculations;
- runs shutdown/after-run management;
- calculates cooling, idle, EVAP, injection transients, gear, closed-loop fuel, injection, ignition, VVT, knock, torque, traction, fuel level, cruise, rev limit, and A/C;
- commits pending coding if permitted;
- updates fuel pump, eTPU periods, free-RAM watermark, and execution-time statistics.

The loop frequency is not proven by this export. Naming `engine_speed_and_cyl_cut_update_1000hz` does not impose a 1 kHz software cadence. Foreground-loop period should be measured using `timer_main`, `timing_main_loop_last`, or a bench trace.

### Deterministic 2000 Hz interrupt scheduler

`init_emios_uc4` configures the time base and assigns INTC vector `0x37` priority 1. `interrupt_timer_2000hz` executes every 500 us and derives these phase-aligned groups:

| Effective rate | Divider/reload | Representative work |
|---:|---:|---|
| 2000 Hz | base interrupt | O2 heater micro-PWM, logger timeslot countdowns, execution timing |
| 1000 Hz | 2 base ticks | throttle control, idle airflow decay, IPS shift state, mixture tests, CAC diagnostics, load low-pass |
| 200 Hz | 10 base ticks | ADC snapshot, accelerator pedal, speed/roughness, closed-loop fuel, transient fuel, VVT, torque, DPM, cruise, rev limit, CAN timeouts, diagnostic timers, ISO-TP TX |
| 100 Hz | 2 x 200 Hz | digital input debounce, brake/clutch, optional clutch sensor, IPS message `0xD2`, engine speed reference, IMU, oil pressure |
| 50 Hz | 4 x 200 Hz | task/timeslot phase marker; no substantive application routine currently visible |
| 20 Hz | 10 x 200 Hz | task/timeslot phase marker; no substantive application routine currently visible |
| 10 Hz | 20 x 200 Hz | cooling/charge-cooler, cluster/exhaust, EVAP, O2 learning, knock threshold, VVT zero timers, speed history, slip/steering, fuel summary, runtime counters |
| 5 Hz | 2 x 10 Hz | O2 sensor fault detection |
| 3.33 Hz | 3 x 10 Hz = 300 ms | eMIOS/fuel-level watchdogs and unlocked coding command service |
| 2 Hz | 5 x 10 Hz | logger timeslot phase marker |
| 1 Hz | 10 x 10 Hz | logger timeslot phase marker |

The existing `*_333ms` function names are nominal or inherited: the observed divider is three 100 ms ticks, exactly 300 ms if the 2000 Hz base is correct.

The ISR records start/end timestamps and maximum execution time for its groups. Because slower groups are nested, a 10 Hz invocation also performs the 200 Hz work in that interrupt and can have a much larger worst-case latency than an ordinary 200 Hz tick.

## Interrupt and peripheral coordination

| Source | INTC priority | Role |
|---|---:|---|
| knock acquisition | 15 | Highest-priority triggered eQADC/eDMA sample processing during crank-angle knock windows |
| injection and crank/cam/eTPU events | 14 | Cylinder injection scheduling, four VVT cam-edge ISRs, MAF/MAP edge processing |
| CAN C mailboxes | 3 | Logger CAN-C receive/transmit completion paths |
| eMIOS input capture | 3 | Configured per channel for discrete/frequency inputs |
| CAN A mailboxes | 2 | Vehicle CAN, OBD, logger, and unlocked debug transport |
| eSCI receive | 2 | Serial/circular-buffer receive path |
| 2000 Hz scheduler | 1 | Lowest named periodic interrupt priority |

Priority values and vector assignments are direct register evidence. The exact MPC5534 nesting policy depends on INTC configuration, but the priority scheme clearly favors crank-angle/knock correctness over periodic housekeeping and CAN.

### eTPU

eTPU is responsible for angle/time-critical engine I/O rather than relying on the foreground loop. Verified consumers include:

- injection events and per-cylinder cut scheduling;
- ignition/coil events and Mode `0x2F` pulse tests;
- crank/cam edge timing and VVT phase measurement;
- throttle/HC08-related timing support;
- knock window scheduling and a shared 24-bit timestamp used for profiling;
- periodic/frequency output updates.

The CPU updates eTPU parameter RAM and acknowledges channel/event flags in ISRs. Detailed eTPU microcode is not present as decompiled C, so channel semantics inferred only from CPU setup remain lower confidence.

### eQADC and eDMA

Initialization configures eQADC command queues and two eDMA paths. Conversion results continuously populate `adc_dma_dest[256]`; foreground `adc_sample` reads live entries, while the 200 Hz task copies stable primary and secondary snapshots.

Knock uses two acquisition modes:

- continuously sampled bank voltages for circuit diagnostics;
- crank-angle-triggered samples at indices `0x34/0x35`, consumed by the priority-15 knock interrupt for DSP windows.

This division explains why ADC values can be read in the foreground without a blocking conversion call: `adc_sample` is a buffer decode, not a trigger-and-wait routine.

### CAN

CAN receive/transmit is mailbox-interrupt-driven. The periodic scheduler owns timeout aging, ISO-TP consecutive-frame pacing, message construction triggers, and logger group timeslots. The background loop optionally advances logger checksum work and performs higher-level state calculations. CAN interrupts therefore move frames promptly, while deterministic tasks consume the resulting state at 200/100/10 Hz.

## Learned-data persistence (`LEA`)

### Image layout and save

The learned image begins at `LEA_base = 0x400030E8` and is `0x1BE4` bytes. It contains much more than adaptive fuel values:

- program identity and calibration compatibility markers;
- knock/octane, idle, fuel/O2, MAF/load, and torque-to-throttle learning;
- OBD DTC state, freeze-frame data, readiness, and permanent codes;
- trip/fuel-economy/range statistics;
- RPM, speed, temperature, lateral-g, over-rev, and oil-pressure event history.

`EEPROM_save` computes:

- a core CRC16 over the first `0x1638` bytes;
- a full CRC16 over the first `0x1BE0` bytes;
- a recorded core size (`0x1638`) and total write size (`0x1BE4`).

It first finalizes OBD/DTC state, then erases the learned flash sector and writes the entire image to `0x00010000`, padding the last flash phrase with `0xFF` if necessary. Flash operations periodically retrigger the watchdog.

### Load and compatibility policy

`EEPROM_load` copies the full image and validates both CRC/size domains, program name, and a calibration/version marker:

| Failure | Recovery action |
|---|---|
| core CRC/size invalid, or calibration marker incompatible | full learned/adaptive factory reset plus OBD/trip reset |
| full CRC/size invalid, or program name changed | retain compatible core adaptation but reset OBD/trip portion |
| coding changed | clear DTC/freeze-frame state and reinitialize O2/fuel-trim domains |
| valid and compatible | preserve learned data; selectively refresh misfire baselines if their calibration changed |

The loader then writes current program/version markers into RAM and normalizes learned table axes against current calibration. Invalid persistence sets `main_diagnostic_flags` bit 0.

### Save timing

Learned data is not continuously written. On ignition-voltage loss, the shutdown manager waits for engine stop and any cooling/power-hold timer. It saves once if ECU voltage is above the configured safe threshold or the low-voltage DTC state indicates the alternate allowed case. `shutdown_eeprom_saved` prevents repeated sector erases while the supply decays.

Sudden power removal before this path runs can lose changes since the previous successful shutdown, but the dual CRC/compatibility policy prevents silently accepting a partial image on the next boot.

## Coding/VIN/model flash path

Coding is a separate 68-byte image at `0x0001C000`:

- bytes 0-63: coding, VIN, and model payload;
- final CRC field: CRC16 over the first 64 bytes.

At startup, invalid/blank model or bad CRC causes `COD_base` repair from calibration defaults and an immediate rewrite request. At runtime `eeprom_update_flags` represents coding, VIN, model/default-repair, and erase-only requests.

`EEPROM_commit_coding_to_flash` only operates with engine speed zero. It temporarily masks CAN-A interrupt priorities `0xAA/0xAB`, erases the coding sector, writes the full structure unless erase-only was requested, restores priorities, optionally sends message `0x503`, and clears the request flags. `flash_write_cod_data` restricts writes to aligned addresses from `0x0001C000` up to but excluding calibration base `0x00020000`.

The 300 ms `service_coding_333ms` command executor is gated by `ecu_unlocked`; however, other diagnostic/coding entry points should be assessed individually rather than assuming that this one gate protects every way `eeprom_update_flags` can be set.

## Ignition-off, after-run, and shutdown

`ecu_power_hold_and_shutdown_manager` runs every foreground iteration.

With ignition voltage present it:

- asserts the ECU power-hold output (`siu_gpdo[0xCB]`);
- calculates a fan after-run duration from air and coolant temperature;
- extends `ecu_shutdown_timer` while the engine runs or when the new requirement is longer.

With ignition voltage absent it:

- clears ignition state;
- waits for engine speed zero and left-foot-braking/diagnostic shutdown conditions;
- allows radiator, engine-bay, recirculation, and transmission cooling logic to keep extending or consuming the shutdown timer;
- performs the one-shot LEA save when voltage permits;
- releases the power-hold output.

The application does not enter a final software sleep loop after releasing the output; the foreground loop continues until external power actually collapses. HC08 reset-line transitions surround the save/power-release sequence, but the signal's active polarity is not sufficiently clear to rename those helpers safely.

## Flash safety and concurrency

- Flash erase/program helpers disable external interrupts around critical controller operations and retrigger the watchdog.
- Coding commit additionally masks two CAN interrupt priorities while its sector is erased and rewritten.
- Learned and coding data occupy separate sectors and use distinct erase masks (`4` and `8`).
- Application-side coding writes cannot cross `0x00020000`, protecting the calibration image.
- Application learned/coding paths do not reprogram application code; firmware reflash belongs to the T6 bootloader.

## Confidence and unresolved gaps

High-confidence conclusions are backed by direct address copies, hardware registers, divider reloads, or flash calls. The layered execution model, task rates, persistence sizes, CRC domains, and coding bounds are high confidence.

Remaining gaps:

1. Measure the foreground-loop frequency and jitter under idle, high RPM, active knock DSP, and heavy CAN traffic.
2. Recover the exact segment tables and first/last calibration copy words from assembly to remove the two-byte alignment ambiguity.
3. Map every eTPU channel and interrupt vector to its microcode function; CPU-side setup alone cannot reveal the complete timing program.
4. Determine exact physical polarity/ownership of GPIO `0xCB` power hold and `0xCE` HC08 reset on GT430 hardware.
5. Confirm whether flash functions execute from RAM/cache during programming and characterize worst-case interrupt blackout.
6. Audit all writers of `eeprom_update_flags` and all persistence-reset services for authorization and wear implications.

## Marginal value of this pass

This pass materially changes the architectural understanding. The earlier “1000 Hz base loop” shorthand hides a verified 2000 Hz interrupt scheduler plus an unpaced foreground loop. The persistence trace also establishes exact learned/coding flash regions, dual CRC recovery tiers, save timing, and flash write boundaries. Those findings are directly useful for safe calibration tooling, bench instrumentation, scheduler profiling, and avoiding accidental learned/coding-sector damage.
