# GT430 and NA091 definition map comparison

This comparison covers every calibration and learned-data entry in
`T6-EVORA--F430-V000E_defs.xml` and `T6-V00BU_defs.xml`, with a consumer-based
walkthrough across their subsystems. The main finding is that these definitions
describe a coupled controller, diagnostic system, and persistent state image;
matching table names or units alone is insufficient to transfer a calibration.

The source baseline is `donour/master_t6e` commit
`90c318032c40e835ca077f076beef94c12f86cca`, with the reviewed corrections
recorded in [the GT430 review](../C132E0278/analysis/GT430_ROMRAIDER_REVIEW.md)
and [NA091 review](../B13200091/DEFINITION_REVIEW.md).
The NA091 target is the `B13200091` C/symbol export paired with `T6-V00BU` by
its `CAL_base` metadata. The separate `T6-V00A0` definition is not included.
Model-year strings in the generic XML header do not independently identify a
specific car or prove compatibility with its firmware.

All entry names, storage, addresses, dimensions, axes, and arithmetic formulas
have been inventoried. Behavioral conclusions below come from selected C
consumers, not verification of every individual entry. Original images, active
coding, actual calibration values, and runtime behavior remain unmeasured.

## Complete entry inventory

| Profile and image | Root entries | Nested axes | Unique named CSV address matches | Other root matches |
|---|---:|---:|---:|---|
| NA091 calibration | 1,091 | 952 | 1,083 | 7 unmatched; 1 with multiple named labels |
| NA091 learned data | 695 | 702 | 695 | None |
| GT430 calibration | 937 | 779 | 900 | 37 unmatched |
| GT430 learned data | 727 | 728 | 708 | 14 unmatched; 5 generic-address-only matches |

Together these are **3,450 root entries and 3,161 nested axes**. A CSV address
match is a navigation aid, not proof of a correct unit or machine-code operand.
An unmatched entry may represent newer XML annotations, older CSV exports,
an interior address, or an error; it is not automatically invalid.

The reproducible audit tool records every root entry and its axes, RAM address,
candidate CSV symbols, dimensions, byte length, scaling formulas and review
flags. Its JSON records SHA-256 identities for the four input files. The CSV is
a flat index of every root entry; nested-axis details remain in the JSON.

```sh
python3 romraider-defs/audit_definition_maps.py --output-dir /tmp/evora-definition-map-review
```

Without `--output-dir`, the tool prints a summary and writes nothing. It never
rewrites definitions, symbols, calibration images, or Ghidra projects.

### Structural findings across all entries

- There are 19 duplicate-name groups involving 38 root entries across the four
  images. Use `(profile, image, address)` as an entry's identity, not its name.
- There are 119 static axes with voltage scaling, marked for review. Some are
  legitimate ADC conversion grids; others are generated placeholders on gear,
  cylinder, hysteresis or rate-limit arrays. A voltage-axis flag alone is not
  sufficient evidence to change an entry.
- Three identical duplicate `<scaling>` records were removed from each
  calibration definition, along with their duplicate exporter registration.
  The 13 NA and 3 GT calibration alternative-unit choices are preserved.
- GT430 has five XML/CSV byte-length disagreements. Three thermistor curves are
  34 cells in current C and XML, versus 33/33/32 in the CSV; this favors stale CSV
  typing. The other two CSV types are generic `undefined` placeholders, which
  cannot settle the actual payload width.
- Four comments used C-style escaped quotes instead of CSV doubled quotes.
  Repairing only those quotes removes all parsed fragments and extra columns.
  Strict parsing now yields 5,116 NA and 4,744 GT records, preserving every
  name/address/type identity. The audit reports no remaining CSV issues.
- No algebraic forward/inverse mismatch was found in the evaluated numeric
  scalings. The two NA engine-running period conversions `15000000/x` have an
  undefined zero input; other sampled values round-trip. Passing this arithmetic
  check does not establish the intended physical unit, signedness, or offset.

The tool exhaustively evaluates 8-bit arithmetic domains and samples wider
domains. It checks the declared XML file bounds, not the bounds of an original
image. Static-axis labels have no writable storage domain. Formatting, GUI
rounding, switch-state interpretation and hardware behavior are outside this
audit.

## Coverage across all calibration categories

Every one of the 52 category names used by either calibration definition is
included below. Counts measure named XML coverage, not implementation size or
feature availability. In particular, GT430's four `evap` entries do not imply
that its EVAP implementation is smaller or absent; much of it remains under
other or generic names.

| Area and all assigned category names | NA091 | GT430 | Main interpretation |
|---|---:|---:|---|
| Inputs: `sensor`, `tmap`, `wheel`, `clutch`, `engine` | 66 | 59 | Signal conversion, validity, fallback values, wheel/clutch qualification and engine reference constants |
| Charge model: `load` | 19 | 22 | MAF/Alpha-N selection, learned charge correction and load-to-throttle relationships |
| Mixture: `inj`, `fuel`, `injtip`, `dfco`, `closedloop`, `evap`, `o2` | 172 | 127 | Mass-to-pulse model, transient terms, trims, pump/pressure and purge control |
| Combustion: `ign`, `knock`, `misfire`, `roughness` | 115 | 101 | Spark scheduling, knock correction/adaptation, intentional cuts and misfire protection |
| Torque and throttle: `torque`, `tpstarget`, `tps`, `tpssmooth`, `etb`, `lfb`, `dca` | 91 | 114 | Driver demand, torque/airflow limits, smoothing, actuator control and conditional assist paths |
| Limits: `revlimit`, `overrev`, `vehicle` | 33 | 34 | Soft/hard RPM envelopes, recovery and vehicle-speed enforcement |
| Driver coordination: `gear`, `gsi`, `slip`, `dpm`, `cruise`, `ips`, `trans` | 53 | 85 | Gear advisory, actual DPM traction control, cruise and transmission requests |
| Idle and cams: `idle`, `vvt` | 82 | 51 | Target speed/airflow, learned accessory corrections and cam target/feedback control |
| Thermal management: `cooling`, `cac`, `oil` | 47 | 34 | Fans, pumps, charge cooling, shutdown/afterrun and oil-related supervision |
| Accessories: `ac`, `acis`, `airbox`, `exhaust`, `accessory` | 55 | 24 | Compressor permission/load, intake-path and exhaust-state selection |
| Vehicle/network interface: `can`, `cluster`, `tpms`, `logger` | 19 | 19 | CAN health/logging, cluster presentation and tire-pressure supervision |
| Configuration/diagnostics: `ecu`, `misc`, `obd`, `emissions` | 339 | 267 | General constants, coding-related branches and diagnostic monitor/reporting policy |
| Total | 1,091 | 937 | All calibration root entries |

## How the controller layers fit together

Sensor conversion and validation supply measured speed, air charge, temperatures
and pressure. Coding selects installed hardware and transmission behavior.
Driver pedal curves produce demand, then idle, cruise, rev limits, torque
requests, misfire/fault restrictions and smoothing modify that demand before
throttle actuation. Injection and spark share load/torque estimates but retain
their own scheduling and protective cuts. Learned state feeds corrections back
into the charge, idle, fuel and knock models.

### Driver demand, torque, throttle and limiting

The NA load-to-torque and torque-to-load maps are 16x16 byte surfaces with
2 Nm/count and 4 mg/stroke/count respectively. GT430 uses 16x16 word surfaces
with direct Nm and mg/stroke. Friction maps also differ in dimensions and
normalization. GT430 has eleven 16-point pedal curves versus seven in NA,
including additional low-gear/transmission-mode distinctions. [NA torque][na-torque],
[GT430 torque][gt-torque], [NA pedal][na-pedal], [GT430 pedal][gt-pedal].

GT430 selects the smaller gear/RPM or coolant torque ceiling, converts torque
into load and throttle feedforward, then adds PI load-error correction and
opening/closing limits. Its injector-duty policy supplies a second allowable
air-charge ceiling by inverting the fuel model. Raw duty 255 disables that
derived ceiling with a `0xFFFF` sentinel; it is not simply a direct injector
pulse clip. [Torque/throttle arbitration][gt-throttle], [capacity inversion][gt-capacity].

**The GT430 XML is not uniformly a stock-code definition.** Two torque-cap
tables explicitly say their 4 Nm/count scaling requires patched code, while the
exported C still shifts by one, giving 2 Nm/count. Neither conversion can be
selected safely from the calibration name alone. The matching executable and
patch identity are required. [Definition warning][gt-patched-xml], [consumer][gt-throttle].

NA rev-limit envelopes are 8x8 byte maps encoded as `6000+10*x RPM`; GT430 uses
4x4 direct-RPM word maps. Soft limiting reduces airflow/throttle, while hard
limiting directly sets injection-cut state. These mechanisms are distinct from
external torque requests. [NA limiter][na-limiter], [GT430 limiter][gt-limiter].

### Gear advisory, traction, cruise and transmission

GT430's `slip:*` family largely corresponds to NA `gsi:*`, `gear:*` and
`overrev:*` logic. It estimates engine speed in candidate gears, selects a
recommended gear from RPM/power criteria, and drives cluster indicators. It
should not be described as the adjustable wheel-slip torque controller merely
because of its names. [NA advisory][na-gsi], [GT430 advisory][gt-gsi].

Actual GT430 adjustable traction control is the separate `dpm:*` family. It
compares maximum rear and front wheel speeds at 1/8-percent resolution, combines
mode-level and pedal/speed targets, and produces separate spark/throttle torque
ceilings. Speed/RPM, valid-wheel/CAN state, manual coding and vehicle-mode gates
determine whether it can intervene. NA's lack of this named family is supported
by the reviewed control paths, not by a claim that all stability functions are
absent. [DPM calculation][gt-dpm], [supervision][gt-dpm-supervision].

Cruise and IPS branches coexist with manual code. Their presence does not
establish that a particular car enables them. Cruise requests ultimately share
the airflow/throttle constraints; retained transmission maps participate in
shift matching and requested torque arbitration. Coding and live state are part
of a map's effective selection context.

### Idle, cams, thermal management and accessories

Idle is a requested-speed and airflow controller, not only an RPM target map.
Coolant, transmission, driving mode and gear select targets; base airflow is
indexed by requested idle RPM. Accessory/feedforward, PI correction and
persistent cold/hot and A/C learning then contribute to airflow. Some idle error
axes use signed RPM error biased by 32768; these GT axes now decode that bias.
Ignition idle-error axes instead use four RPM/count with a 512 RPM bias.
[NA idle][na-idle], [GT430 idle][gt-idle], [GT430 error encoding][gt-idle-error].

Both applications retain normal 16x16 and low-load 6x6 VVT targets, subject to
temperature, transmission, mode, axis-interior and fault gates. Coolant
compensation is subtracted, so increasing it can reduce commanded cam angle.
The GT430 intake/exhaust clamping values are raw 172/140, corresponding to
43/35 degrees under the declared quarter-degree scale. [NA VVT][na-vvt],
[GT430 VVT][gt-vvt].

GT430 radiator-fan demand arbitrates between coolant and A/C/air-temperature
paths, adds operating/fault/diagnostic overrides, then passes through a drive
conversion and inverted PWM. CAC demand has its own conversion map. NA has
low/high fan hysteresis, coding-dependent bay fan and recirculation-pump afterrun
paths. A demand percentage, electrical PWM percentage and physical flow are
therefore different quantities. [GT430 fan][gt-fan], [NA cooling][na-cooling].

NA ACIS/airbox control uses RPM/load hysteresis plus coding and mode selection.
The two entries of an airbox threshold pair mean lower/upper boundaries, not
voltage samples. Exhaust maps select discrete states, with extra startup,
standstill and assist-mode conditions; a byte map does not imply continuously
variable valve opening. Reported accessory states are often reconstructed from
commanded GPIO bits rather than independent position feedback.
[NA intake paths][na-intake], [NA exhaust][na-exhaust], [accessory reconstruction][na-accessory].

### Sensors, diagnostics, coding and learned data

Implicit thermistor conversion grids genuinely use 32-ADC-count spacing when
the no-axis helper is called with shift 3. Generated voltage axes can therefore
be meaningful on those maps. Pressure conversion instead uses slope/offset
arithmetic, and validity gates may substitute fallback calibrations. An
unresolved sensor label or "unused" suffix is not evidence of wiring absence.
[No-axis interpolation][gt-noaxis], [signal conversion][gt-sensors].

Diagnostic `obd:*` settings are policy bitfields, not uniform enabled/disabled
switches. Monitoring, reporting, priority, emissions state and freeze-frame
behavior depend on different bits and consumers. Vehicle coding occupies a
separate flash structure and selects major hardware/controller branches; it is
not equivalent to changing a similarly named calibration constant.
[DTC policy consumers][gt-dtc], [coding copy][gt-coding].

The learned definitions contain 600 NA and 688 GT430 `obd` records, mostly DTC
state/counters; this explains much of their size. The remaining entries cover
fuel/idle/load/octane adaptation, catalyst histories, CRC/coding stamps,
performance/use counters, throttle/HC08 history and unresolved bytes. They are
not a second collection of desired tuning targets. Their storage can be reset
because of program identity, CRC, coding or changed-axis checks. The so-called
EEPROM writer actually erases/writes a flash learned-data region.
[NA persistence][na-persistence], [GT430 load validation][gt-persistence].

## Applied whole-map corrections

Corrections use the exported consumer arithmetic, with cross-variant evidence
where needed. The patch changes 39 GT and 23 NA root entries, preserving all payload addresses
and dimensions. No calibration bytes are changed. The detailed ledgers list
addresses, evidence and remaining unknowns: [GT430][gt-review] and [NA091][na-review].

| Area | Applied interpretation | Evidence |
|---|---|---|
| Vehicle limit, both | `2*x km/h`, replacing `x`; document the raw-255 no-limit context. | [NA][na-speed], [GT430][gt-speed]. |
| Gear advisory, both | `5*x+500 RPM` thresholds and `5*x RPM` differences without an absolute offset. Replace false voltage axes with gear indices. Both ratio families now display `x/10 rpm/(km/h)`. | [NA][na-gsi], [GT430][gt-gsi]. |
| GT430 advisory maximum | Direct engine RPM, replacing car-speed units/name. | [Comparison][gt-gsi]. |
| GT430 A/C and cooling | A/C coolant bounds `5*x/8-40 °C`; fan drop `5*x/8 °C` difference; afterrun description five seconds/count. | [A/C][gt-ac], [drop][gt-tempdrop]. |
| NA intake/cylinder arrays | Four airbox pairs identify lower/upper RPM boundaries; trim labels identify the six cylinder entries. | [Intake][na-intake], [NA ledger][na-review]. |
| GT430 PI and filters | Load-error axes `x-128`; DPM weight `/256`; throttle filter `/1024`; opening/closing labels on the rate pair. | [PI][gt-pi], [DPM][gt-dpm-filter], [TPS][gt-tps-filter]. |
| GT430 actuator-test timing | Mode 2F timeout `x/200 seconds`. | [Decrement][gt-mode2f], [200 Hz call][gt-mode2f-call]. |
| GT430 STFT | Limit `x/20 %`, correcting a factor of 100. | [Pulse equation][gt-stft], [clamp][gt-stft-limit]. |
| NA fuel learning and learned idle | Unsigned offset-binary STFT thresholds `(x-32768)/20 %`; signed A/C-on learned airflow `x*100/1024 mg/s`. | [Learning][na-learn], [interpolation][na-idle-learn], [airflow use][na-idle-use]. |
| GT430 ignition | Biased cylinder trim; restored deadtime IAT axis; cold-start axis `06BA`; unsigned startup base-timing factor; encoded RPM for spark efficiency; correctly scaled idle-error axes and clutch-antistall speed. | [GT430 ledger][gt-review] documents the exact pointer/arithmetic evidence and independent NA/later-GT corroboration. |
| GT430 pressure and idle controller | Signed fuel/manifold/oil pressure offsets; offset-binary idle RPM-error axes and correction counts. Purge offset and unknown gain units are preserved. | [Signal conversion][gt-sensors], [idle error][gt-idle-error], [GT430 ledger][gt-review]. |
| Shared export integrity | Remove identical duplicate scalings, repair malformed CSV quoting, preserve alternative units and symbol identities, add explicit metadata reconciliation after export. | [Regeneration commands](../../../romraider-defs/README.md). |

Original machine code remains necessary where the available exports conflict.
In particular, patched torque caps, an additive margin labeled percent, some
10-/12-bit throttle domains, unknown controller gain units and the malformed
startup coolant comparison are deferred, with concrete verification steps in
the ledgers. Correcting a resolvable axis or factor does not claim that all gates
or calibration contents have been verified.

## NA091 learning and injector-guide reconciliation

The duplicate CSV label at RAM `0x40008EE1/2` can now be separated at the C/XML
level: XML `0x00BD` is the learned injector-offset step, whereas `0x00BE` is the
pedal-zero gain currently called `sensor: pps unknown1`. C has distinct consumers:
the former adds/subtracts microseconds, while the latter moves a pedal zero by
`gain*(zero-measured)/256`, only toward lower measured values and subject to
separate track floors. Original instruction/address binding remains unverified.
[Learning update][na-learn], [pedal-zero update][na-pedal-zero].

The injector guide also overstates the learning clamp: the code checks the
current learned offset before adding/subtracting a whole step, without a
post-update saturation. The offset can therefore pass a nominal bound by up to
`step-1` integer microseconds. Equality of a DTC threshold and the learning limit
does not universally prevent that DTC from firing; it depends on the reachable
update grid and other monitor gates. Learning cadence is likewise eligibility
dependent: the countdown pauses when the learning branch is inactive.
[Update and gates][na-learn].

Fuel trims compose additively in the pulse equation,
`pre*(1+LTFT/1000+STFT/2000)`, with deadtime and learned microsecond offsets added
afterward. They are not successive multiplicative factors. This distinction,
the bank-flow denominator, and the difference between total-pulse and
fuel-only-time thresholds matter when interpreting the guide; its worked
injector values are not independently validated by this review.

## Remaining work and confidence

The complete structural inventory and subsystem comparison are finished for
these input files, and the unambiguous corrections from this pass are applied.
Per-entry physical interpretation remains partial. The 119 voltage-axis review
flags and duplicate names are a review queue, not 119 confirmed errors.

The regression suite checks independent consumer equations, encoding boundaries,
axis labels, CSV identity preservation and guarded post-export reconciliation.
The checked-in definitions remain the reviewed source for that explicit
reconciliation step; historical C/CSV semantic annotations are not silently
rewritten to resemble a new Ghidra export.

Original matching binaries/projects are required to settle absolute address
binding, stock/patch identity, actual values and breakpoint monotonicity,
callback references, signed loads and decompiler artifacts. Bench evidence is
required for installed coding, sensor/valve wiring and polarity, physical
actuator response and measured task timing. Another successful XML parse or
CSV import cannot supply those facts.

[na-torque]: ../B13200091/B13200091.c#L52331
[gt-torque]: ../C132E0278/C132E0278.c#L52103
[na-pedal]: ../B13200091/B13200091.c#L38081
[gt-pedal]: ../C132E0278/C132E0278.c#L37437
[gt-throttle]: ../C132E0278/C132E0278.c#L44586
[gt-capacity]: ../C132E0278/C132E0278.c#L17104
[gt-patched-xml]: ../../../romraider-defs/T6-EVORA--F430-V000E_defs.xml#L7399
[na-limiter]: ../B13200091/B13200091.c#L55142
[gt-limiter]: ../C132E0278/C132E0278.c#L55224
[na-gsi]: ../B13200091/B13200091.c#L56749
[gt-gsi]: ../C132E0278/C132E0278.c#L57031
[gt-dpm]: ../C132E0278/C132E0278.c#L58357
[gt-dpm-supervision]: ../C132E0278/C132E0278.c#L58592
[na-idle]: ../B13200091/B13200091.c#L29055
[gt-idle]: ../C132E0278/C132E0278.c#L28044
[gt-idle-error]: ../C132E0278/C132E0278.c#L28320
[na-vvt]: ../B13200091/B13200091.c#L42993
[gt-vvt]: ../C132E0278/C132E0278.c#L43542
[gt-fan]: ../C132E0278/C132E0278.c#L20078
[na-cooling]: ../B13200091/B13200091.c#L21839
[na-intake]: ../B13200091/B13200091.c#L22419
[na-exhaust]: ../B13200091/B13200091.c#L22682
[na-accessory]: ../B13200091/B13200091.c#L22058
[gt-noaxis]: ../C132E0278/C132E0278.c#L22503
[gt-sensors]: ../C132E0278/C132E0278.c#L15160
[gt-dtc]: ../C132E0278/C132E0278.c#L24461
[gt-coding]: ../C132E0278/C132E0278.c#L54739
[na-persistence]: ../B13200091/B13200091.c#L19549
[gt-persistence]: ../C132E0278/C132E0278.c#L17699
[na-speed]: ../B13200091/B13200091.c#L55103
[gt-speed]: ../C132E0278/C132E0278.c#L55185
[gt-ac]: ../C132E0278/C132E0278.c#L53477
[gt-tempdrop]: ../C132E0278/C132E0278.c#L20723
[gt-pi]: ../C132E0278/C132E0278.c#L52757
[gt-dpm-filter]: ../C132E0278/C132E0278.c#L58500
[gt-tps-filter]: ../C132E0278/C132E0278.c#L52832
[gt-mode2f]: ../C132E0278/C132E0278.c#L39728
[gt-mode2f-call]: ../C132E0278/C132E0278.c#L11016
[gt-stft]: ../C132E0278/C132E0278.c#L16980
[gt-stft-limit]: ../C132E0278/C132E0278.c#L26692
[na-learn]: ../B13200091/B13200091.c#L28215
[na-idle-learn]: ../B13200091/B13200091.c#L29214
[na-idle-use]: ../B13200091/B13200091.c#L29746
[na-pedal-zero]: ../B13200091/B13200091.c#L38518

[gt-review]: ../C132E0278/analysis/GT430_ROMRAIDER_REVIEW.md
[na-review]: ../B13200091/DEFINITION_REVIEW.md
