# C132E0278 calibration coverage and tuning-readiness audit

Scope: GT430 `C132E0278.c` and `C132E0278_symbols.csv`. This is a definition-readiness assessment,
not an assertion that an edited image is safe to flash. The directory contains a decompiler export
and symbol inventory, not a verified binary editing/checksum workflow.

## Executive assessment

Calibration understanding is broad enough to build a useful engineering definition for the main
engine-control surfaces, but not yet complete enough for indiscriminate whole-ROM tuning.

- The CSV contains 1,238 `CAL_*` rows representing 1,233 unique names.
- The C export references about 1,240 unique `CAL_*` identifiers.
- 623 CSV calibration rows are arrays and 325 are named X/Y axes.
- Approximately 231 payload tables have at least one same-name typed axis and are strong candidates
  for automated definition generation.
- Only 16 CAL rows retain an `undefined*` type and 17 retain `unknown`/`?` in the name after this
  audit, but those counts overstate completion: the C export still contains roughly 821 unique
  generic `DAT_4000xxxx` references inside likely calibration address ranges.
- Five duplicate CAL names remain at different addresses, which is a hard blocker for blindly
  generating definitions by name alone.

The best-covered tuning domains are base fueling, ignition, throttle/pedal shaping, load, torque,
VVT, rev limit, knock, cooling, fuel pressure/pump, and GT430 DPM traction control. Idle, AC, EVAP,
emissions/readiness, diagnostic thresholds, and several transient/protection details have coherent
algorithms but incomplete table naming or scaling.

## What “ready” means in this audit

### Tier A — ready for a draft definition

A Tier-A item has:

- a stable address and non-overlapping type;
- a known dimensional unit or exact encoded formula;
- identified axis order and dimensions;
- a traced consumer establishing direction and purpose;
- no unresolved duplicate-name/address collision.

These items can be exported to an XDF/A2L-like draft and compared against a known stock binary.

### Tier B — named, but not tuning-ready

Tier B has a credible function and address but one or more missing details:

- raw `uint8_t/uint16_t` payload with no physical scale;
- polarity, signedness, or sentinel behavior not proven;
- axis values known but output unit composite/internal;
- coding/manual/IPS variant selection not fully characterized;
- diagnostic table whose calibration changes emissions compliance behavior.

### Tier C — discovery only

Tier C consists of generic `DAT_*` blocks, overlapping/duplicate symbols, decompiler-lost
expressions, unknown checksums/storage layout, or tables inferred only from adjacency. These should
not appear as user-editable parameters.

## Inventory by subsystem

Counts below are CSV name-prefix counts; they measure named coverage, not correctness.

| Group | CAL rows | Current readiness |
|---|---:|---|
| OBD-II/diagnostics | 235 | Mostly configuration/DTC severity; many thresholds remain generic |
| Ignition | 87 | High for base/limits/temperature/transient maps |
| Injection | 70 | High for AFR, flow, timing, startup and bank balance |
| Injection transient/DFCO | 65 | Medium-high; core paths known, several internal factors raw |
| Idle | 56 | Medium; targets and PI known, many accessory/feed-forward tables generic |
| Sensors | 55 | High for primary scaling and thresholds |
| Torque | 52 | High for main model/limits; some internal normalization remains composite |
| Knock | 44 | High for thresholds, gains and learned retard behavior |
| Rev limit | 43 | Medium-high after airflow PI tracing; escalation/state details still dense |
| Closed loop | 42 | High for gains/thresholds; IPS scalar timing units partly internal |
| Load | 38 | High except the lost MAF density-normalized lookup coordinate |
| Cooling | 38 | High for fan/pump surfaces; some hysteresis flags raw |
| ECU/general | 36 | Mixed; useful scalars plus coding/diagnostic behavior |
| Cruise | 31 | Medium-high, outside core power tuning |
| TPS smoothing | 29 | High, with encoded rate/step behavior traced |
| Misfire | 29 | Medium; maps typed but emissions/safety implications are high |
| Slip | 28 | Medium; early slip layer plus some ambiguous legacy fields |
| Fuel/pump | 26 | High for pressure target and PWM controller |
| VVT | 25 | High for targets, coolant correction and PI gains |
| DPM traction | 23 | High for GT430 variable-slip target/torque cut |
| TPS target / TPS | 42 combined | High for mode/gear pedal-to-throttle surfaces |
| Cluster | 19 | Medium; duplicate shift-light symbols remain |
| Transmission | 17 | Mixed and not a replacement for the separate TCU definition |
| Exhaust | 17 | High for flap control, limited tuning consequence |
| AC | 14 | Low-medium; algorithm known, many PID/load constants generic |
| DCA | 14 | Medium; launch/drive-cycle-assist terminology incomplete |
| EVAP | 7 | Low for tuning; control known but emissions calibration should remain locked |
| CAC | 7 | High for charge-cooler pump demand/output mapping |
| Emissions | 4 named payload groups | Improved, but most monitor thresholds remain generic |

## Tier-A definition candidates

### Fuel and air

- `CAL_inj_afr_base[rpm][load]`, encoded as table value `*5 + 500` AFR*100.
- `CAL_inj_flow_rate[differential fuel pressure]` in mg/s.
- `CAL_inj_time_base[ECU voltage][differential pressure]` in 20 us steps.
- `CAL_inj_angle[rpm][load]` in 720/256-degree units.
- `CAL_inj_efficiency[rpm][load]`, bank-balance, IAT, coolant/load and startup corrections.
- Injector maximum duty and pulse-window-derived load limit.
- Fuel-pressure target `[rpm][load]`, feed-forward pump command, proportional and integral terms.
- MAF voltage scaling and Alpha-N/load/VE maps.

The primary dual-MAF charge expression and later density-normalized torque-to-TPS coordinate are
both recovered from raw instructions. The coordinate saturates measured charge at 1380 mg/stroke,
normalizes it by selected air density, and maps 0..1173 mg/stroke to 0..255.

### Ignition and knock

- Base manual/IPS ignition maps, minimum/maximum limits and per-cylinder trims.
- Coolant, manifold-temperature, IAT, TPS-rate and idle-error compensations.
- Knock detection windows, RPM/load thresholds, enable/inhibit surfaces, retard/decay and octane
  learning limits.

This audit also resolves the adjacent stopped-coolant thresholds as distinct minimum and maximum
bounds; the previous duplicate name generated an impossible condition in C.

### Throttle, torque, and load

- Tour/Sport, gear and transmission pedal target maps.
- TPS slew/rate/decay and torque-derived opening limits.
- Torque-to-load/load-to-TPS surfaces, friction/pumping/volumetric terms and principal torque limits.
- DPM slip target and torque-cut maps, including driver-selectable GT430 slip behavior.

These are definition-ready in structure, but changing one layer without the coupled torque/load/TPS
layers is not tuning-ready as a strategy.

### VVT, idle targets, thermal, and rev limit

- Normal and low-load intake/exhaust VVT target maps, coolant offsets, transition and PI gains.
- Manual Tour/Sport and IPS idle RPM target tables.
- Radiator fan, engine-bay fan, charge-cooler pump and coolant/transmission pump thresholds/maps.
- Manual/IPS rev-limit base surfaces and the airflow controller's proportional/integral limits.

`CAL_revlimit_flow_integral_limit` is newly identified as the symmetric clamp on the rev-limit
airflow integral contribution, rather than an unknown flow scalar.

## Tier-B named but incompletely scaled areas

### Idle airflow

The target, proportional table, integral-step table, AC/fan compensation and learned values are
understood. However, IPS expected-airflow surfaces, VVT airflow correction, bay-fan load, anti-stall,
startup and several bounds remain `DAT_*`. The final sum is traceable, but publishing only the named
subset would give a misleading impression of complete idle authority.

### AC compressor load

The OFF/START/RUN/SHUTDOWN state machine and evaporator-temperature controller are understood, yet
most gains, clamps, slew periods and derived load scale remain generic. AC tuning should wait for a
typed state structure and logged compressor-load validation.

### Misfire and catalyst protection

Misfire thresholds and catalyst-damage limits are often typed, but altering them affects both engine
protection and emissions compliance. Several severity and cylinder-cut thresholds remain ambiguous
or duplicated. These belong in a read-only engineering definition until validated against logs and
requirements.

### Closed-loop, emissions, and EVAP

Closed-loop gains and sensor thresholds are mostly usable; monitor enable logic and DTC thresholds
are not. EVAP/catalyst algorithms are now coherent, but definition-ready addresses do not imply
tuning suitability. Emissions monitor tables should be read-only by default.

### Internal factor tables

Many raw `uint8_t` payloads are directionally understood but lack a physical unit. Examples include
some torque efficiency, transient fuel, diagnostic compensation, and DCA factors. They can be
displayed as raw values for research but should not receive guessed percent/degree labels.

## Tier-C gaps and structural hazards

### Generic calibration-region references

Approximately 821 unique generic `DAT_4000xxxx` references occur in probable calibration ranges:

- about 234 in the dense scalar region `0x40008600..0x400089ff`;
- about 18 in the mid table region `0x40008a00..0x4000bfff`;
- about 569 in later diagnostic/table regions `0x4000c000..0x4000efff`.

The late-region count is dominated by OBD, AC, EVAP, emissions, idle and diagnostic state-machine
thresholds. Address adjacency alone is insufficient to type them safely.

### Duplicate names

Five CAL names still occur at different CSV addresses:

- upstream/downstream or monitor-specific rich/lean O2 voltage thresholds;
- manual and IPS shift-light offset axis/payload pairs;
- severe-misfire one-cut thresholds.

These require address-specific call-site or raw instruction recovery. A definition generator must
key by address and reject duplicate names rather than silently overwrite one entry.

### Decompiler and storage limitations

- The C export is not buildable source and includes lost arithmetic, overlapping globals and bad
  prototypes.
- RAM calibration addresses describe the runtime copy; flash source offsets and exact copy range
  must be verified against the original image.
- Calibration checksum, firmware checksum/signature, byte order, block padding and programming
  process are not established by this directory alone.
- COD/LEA learned data are adjacent conceptual domains and must not be mistaken for editable CAL.

## Highest-value gaps traced in this audit

### Catalyst MAF bins and enable bytes

The prior symbols treated each 16-byte manual/IPS block as an 8-byte MAF axis plus an unused
“MAF compensation” table. The code actually:

1. copies the first eight bytes into catalyst upstream/downstream learned bin axes;
2. uses the next eight bytes as per-bin enables;
3. pre-marks a catalyst bin complete/disabled when its enable byte is zero.

They are now named `CAL_emissions_cat_monitor_X_maf_flow_{manual,ips}` and
`CAL_emissions_cat_monitor_bin_enable_{manual,ips}`, eliminating out-of-bounds array notation in C.

The coolant-indexed `CAL_emissions_cat_monitor_min_maf_accumulated` table is also resolved: its
output is compared with accumulated MAF since start shifted by four. The role is high-confidence;
the output's physical mass scale remains an internal 16-count MAF unit.

### DFCO recovery enrichment

`CAL_injtip_dfco_recovery_enrichment_duration_factor` is proven to be a two-byte table. It is looked
up without an explicit axis using fuel-cut duration, multiplied by `CAL_injtip_comp_base`, added as
microseconds to both bank pulses, and decayed afterward. Shape and direction are ready; its factor
scale remains raw, so it is Tier B rather than Tier A.

### Engine running/stopped thresholds

Addresses `0x4000877e` and `0x40008780` are separate 16-bit engine-period thresholds. The first
declares running when period falls below it; the second declares stopped when period rises above it,
providing hysteresis. They are now typed/named accordingly instead of an 8-bit array plus an
undefined word.

### Closed-loop startup integral scaling

`CAL_closedloop_integral_gain_startup_duration` is not a generic learning timer. For the specified
number of engine-run hours, the normal integral gain is reduced by a manual or IPS scale factor.
Afterward full integral gain applies. This is definition-ready as a duration but should be described
as controller conditioning, not trim-learning enable time.

## Prioritized next work

1. **Complete flash-path verification.** The stock CPT now proves the `CAL_base`-relative mapping and
   CRC-16/ARC calibration CVN. Identify any integrity layer outside the CAL block and prove a
   no-change flash read/write round trip.
2. **Generate a read-only draft definition.** Export Tier-A entries keyed by address, reject duplicate
   names/overlaps, and include encoded formulas plus source/confidence metadata.
3. **Continue stock-value validation.** Both CPTs now pass bounds, overlap and monotonic-axis checks;
   validate physical ranges and manual/IPS coding selection with logs and the separate COD image.
4. **Resolve safety-critical duplicates.** O2 thresholds, severe-misfire limits and any overlapping
   CAL labels must be address-specific before editable release.
5. **Complete coupled torque/load/TPS definitions.** Validate logged requested torque, selected
   charge, throttle limit and actual TPS before treating pedal/throttle maps independently.
6. **Type idle and accessory feed-forward blocks.** Focus on IPS airflow, VVT airflow, AC, radiator
   and engine-bay loads, using logs to confirm units.
7. **Keep compliance/protection groups read-only.** Emissions, misfire catalyst-damage and diagnostic
   confirmation calibrations should remain locked unless the project explicitly undertakes a
   validation/compliance program.

## Practical tuning-readiness conclusion

The firmware is ready for a high-quality *definition project* and for read-only comparison of major
maps. It is not yet ready for a general-purpose editable tune package or a flashable calibration
release.

Safe early engineering work would be limited to confirming Tier-A addresses/scales, comparing stock
variants, and correlating maps with logs. Power, torque, throttle, knock, fuel-pressure and rev-limit
changes are tightly coupled; none should be changed from a single table in isolation. Protection and
emissions tables should not be exposed merely because their addresses are known.

## Confidence and diminishing returns

- High confidence: quantitative inventory, Tier-A structural candidates, newly resolved engine
  period thresholds, catalyst bin blocks, DFCO table shape, closed-loop startup duration and rev-limit
  integral clamp.
- Medium-high: subsystem readiness ranking and internal-factor Tier-B classification.
- Medium: exact physical scale of several raw factor outputs and boundaries of generic late-region
  calibration blocks.
- Newly established from the stock CPT: exact `CAL_base` mapping, original values and CRC-16/ARC
  calibration CVN (`0x3378`).
- Not established: integrity outside the CAL block, binary flash round-trip, writable block format
  or safe modified-image programming.

This final audit reaches diminishing returns for the decompiler/CSV alone. Additional broad symbol
renaming would improve apparent coverage without materially improving safe tuning readiness. The
next step with the highest marginal value is no longer another C-reading pass: it is flash-path
round-trip verification, address-keyed definition generation, and log-backed validation.
