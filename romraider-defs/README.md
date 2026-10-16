## Introduction

To edit the "calrom.bin" files in RomRaider a definition file is required.

It's also possible to open the "decram.bin" file to show some learned data.

The T4e RomRaider definition is very complete and avalaible for free. For the
T6 definition please contact me.

## Usage

The "T4E90_defs.xml" file was created for a 2008 T4e ECU. It should also work
with 2006–2007 ECUs, but for best results, update your software to the latest
version.

Read the description of the tables:

![Description](../documentation/Usage/RomRaider2.png)

## GT430 and NA091 definitions

The GT430 `T6-EVORA--F430-V000E_defs.xml` matches the `C132E0278` export;
NA091 `T6-V00BU_defs.xml` matches `B13200091`. `T6-V00A0` is a separate profile.
The corrections below follow exported C consumers and address metadata from
`donour/master_t6e` revision `90c318032c40e835ca077f076beef94c12f86cca`, with
cross-variant corroboration where noted. Original firmware images and Ghidra
projects are unavailable, so actual calibration contents and hardware behavior
remain unverified. Payload addresses, dimensions and ROM identities are preserved.

| Profile | Calibration entries / RAM base | Learned entries / RAM base |
|---|---|---|
| NA091 | 1,091 / `40008E24` | 695 / `40002D40` |
| GT430 | 937 / `40008654` | 727 / `400030E8` |

These definitions contain 3,450 root entries and 3,161 nested axes. Names alone
are not unique identifiers. Some static voltage axes are legitimate implicit
ADC grids; only arrays with established gear/cylinder/boundary semantics have
been relabeled. Learned data includes diagnostic state and adaptation, rather
than only tunable targets.

### GT430 scaling and axes

The changes affect 39 root entries. All offsets below are hexadecimal file
offsets relative to calibration RAM base `40008654`.

| Entry / file offset | Corrected interpretation | Exported evidence |
|---|---|---|
| Cylinder ignition trim `005A` | Six unsigned bytes, `(x-128)/4` degrees, inverse `x*4+128`; cylinder labels replace a voltage grid. | [Signed-XOR trim](../disassembly/evora/C132E0278/C132E0278.c#L16135), [quarter-degree timing](../disassembly/evora/C132E0278/C132E0278.c#L16314). Labels follow array indices, without independently identifying harness/firing order. |
| Injector deadtime IAT compensation `18EE` | Restore its eight stored temperature breakpoints at `18E6`, `x*5/8-40 °C`. Payload remains a percent multiplier on deadtime. | [Lookup](../disassembly/evora/C132E0278/C132E0278.c#L16613); CSV axis `40009F3A` minus the calibration base. Intake/manifold temperature selection follows `CAL_tmap_use_for_inj`. |
| Stopped-coolant upper bound `004E` | Rename minimum to maximum, matching its distinct CSV address. | CSV minimum/maximum at `400086A1/A2`. The malformed [gate](../disassembly/evora/C132E0278/C132E0278.c#L15867) remains a separate issue. |
| Cold-start ignition `06C2` | Move its eight-cell coolant axis from `06B5` to **`06BA`**. | [Lookup adds five bytes](../disassembly/evora/C132E0278/C132E0278.c#L15775), [adjacent idle consumer](../disassembly/evora/C132E0278/C132E0278.c#L28769); the later GT and NA independently corroborate the packed layout below. |
| Startup TPS ignition `195E` | Unsigned base-timing retention fraction: `x*100/255 %`, inverse `x*255/100`. Raw 255 is neutral. | [Unsigned lookup and sentinel](../disassembly/evora/C132E0278/C132E0278.c#L15718), [base-timing multiply/divide](../disassembly/evora/C132E0278/C132E0278.c#L16050); NA and later GT have the same arithmetic. This is not an additive angle. |
| Fuel/manifold/oil pressure offsets `02EE`, `0032`, `0302` | Signed 16-bit direct mbar offsets. | Explicit `(short)` sign extension [for fuel/manifold](../disassembly/evora/C132E0278/C132E0278.c#L15205) and [oil](../disassembly/evora/C132E0278/C132E0278.c#L15404), repeated in the later GT. Purge offset `002E` remains unsigned because its consumer differs. |
| A/C coolant bounds `0060`, `0061` | Percent → absolute `x*5/8-40 °C`. | [Direct coolant comparisons](../disassembly/evora/C132E0278/C132E0278.c#L53477). |
| Fan temperature drop `010E` | Remove absolute-temperature offset: `x*5/8 °C` difference. | [Subtraction cancels the -40 offset](../disassembly/evora/C132E0278/C132E0278.c#L20723). |
| STFT limit `014E` | `x/20 %`, replacing `x*100/20 %`. | [Pulse contribution](../disassembly/evora/C132E0278/C132E0278.c#L16980), [clamp](../disassembly/evora/C132E0278/C132E0278.c#L26692). |
| Vehicle limit `0262` | `2*x km/h`. Raw-255 no-limit behavior is documented. | [Consumer forms raw*200 in centikph](../disassembly/evora/C132E0278/C132E0278.c#L55185). |
| Advisory RPM thresholds `45D4`, `45D5`, `45DA`; hysteresis `45F0` | Thresholds `5*x+500 RPM`; hysteresis `5*x RPM`, without the absolute offset. | [Gear advisory arithmetic](../disassembly/evora/C132E0278/C132E0278.c#L57152). The `slip` naming does not make these wheel-slip traction thresholds. |
| Advisory maximum `45E4` | Direct RPM, replacing car-speed units/name. | Compared with estimated gear RPM in the same advisory consumer. |
| Gear/direction arrays `45B0`, `45BC`, `45C8`, `45D5`, `45DA`, `4670` | Gear ratios now display `x/10 rpm/(km/h)`. Replace voltage placeholders with gears 1–6, gears 2–6, or opening/closing, respectively. | [Advisory indexing](../disassembly/evora/C132E0278/C132E0278.c#L57152), [throttle rate limits](../disassembly/evora/C132E0278/C132E0278.c#L52832). |
| Torque PI axes `276E`, `07F4` | Decode load error as `x-128`, replacing `x-127`. | [Error is biased by 128](../disassembly/evora/C132E0278/C132E0278.c#L52757). No new physical gain units are inferred. |
| DPM filter `5C6C`; throttle filter `0222` | Weights use `/256` and `/1024`, respectively. | [DPM filter](../disassembly/evora/C132E0278/C132E0278.c#L58500), [throttle filter](../disassembly/evora/C132E0278/C132E0278.c#L52832). |
| Mode 2F timeout `4438` | `x/200 seconds`, replacing `x/10`. | Raw counter loads, [decrement](../disassembly/evora/C132E0278/C132E0278.c#L39728) and [200 Hz task call](../disassembly/evora/C132E0278/C132E0278.c#L11016). |
| Spark-efficiency RPM axis `3606` of payload `3626` | Standard `x*125/4+500 RPM`, replacing a raw number. | [Lookup uses `engine_speed_8bit`](../disassembly/evora/C132E0278/C132E0278.c#L52375), [speed-byte calculation](../disassembly/evora/C132E0278/C132E0278.c#L15454). |
| Fan afterrun `1846`; dwell `19AE` | Correct descriptions: five seconds/count afterrun; existing 64 µs/count dwell and its lookup inputs. | [Afterrun counter](../disassembly/evora/C132E0278/C132E0278.c#L19808), [dwell consumer](../disassembly/evora/C132E0278/C132E0278.c#L15657). Scaling is retained. |
| Scaling records `4FE0`, `4FC8`, `43A6` | Remove one identical duplicate each; retain real alternative units. | Exact XML duplicate attributes; the existing exporter still has a duplicate datatype registration that can regenerate these records. |
| Ignition idle-error axes `0CA6`, `073C`, `0342` of payloads `0CB6`, `074C`, `0352` | `(x*4)-512 RPM`, replacing an unscaled or incorrectly biased error. | [Saturating byte lookup input](../disassembly/evora/C132E0278/C132E0278.c#L15878) formed from [actual-minus-requested RPM](../disassembly/evora/C132E0278/C132E0278.c#L28141). NA and later GT agree. |
| Idle controller `416E`, `425E`, axes `414E`, `423E` | Axes `x-32768 RPM`; payloads `x-32768` signed controller counts, stored as unsigned words. | [Biased lookup inputs and signed-XOR output decoding](../disassembly/evora/C132E0278/C132E0278.c#L28320). Physical gain/output units remain unresolved. |
| Clutch antistall speed `0026` | `x/10 km/h`, replacing direct km/h. | [Consumer divides centikph by ten](../disassembly/evora/C132E0278/C132E0278.c#L28426), with byte saturation. |

### NA091 scaling and axes

The changes affect 21 calibration entries and two learned-data entries. CAL
and LEA offsets refer to their respective RAM bases in the table above.

| Image / offsets | Correction | Exported evidence |
|---|---|---|
| CAL `0262` | Vehicle limit: `x` becomes `2*x km/h`. Document raw 255's no-limit context and conditional enforcement. | [C target multiplied by 200](../disassembly/evora/B13200091/B13200091.c#L55103), [CSV address](../disassembly/evora/B13200091/B13200091-symbols.csv#L3917) |
| CAL `45D4`, `45D5`, `45DA` | Advisory thresholds: `4*x+500` becomes `5*x+500 RPM`; manual/IPS five-cell arrays identify gears 2–6. | [C five-RPM arithmetic](../disassembly/evora/B13200091/B13200091.c#L56854), [gear-to-cell selection](../disassembly/evora/B13200091/B13200091.c#L56684), [CSV family](../disassembly/evora/B13200091/B13200091-symbols.csv#L4724) |
| CAL `45EF`, `45F0` | Downshift idle margin and RPM offset: generic counts become `5*x RPM` differences, without a 500 RPM bias. | [C differences](../disassembly/evora/B13200091/B13200091.c#L56920), [CSV addresses](../disassembly/evora/B13200091/B13200091-symbols.csv#L4740) |
| CAL `45E4`, `45E6` | Maximum candidate-gear RPM and manual speed offset gain direct RPM and km/h units, respectively. Values retain identity scaling. | [C RPM comparison](../disassembly/evora/B13200091/B13200091.c#L56863), [speed multiplied by 100](../disassembly/evora/B13200091/B13200091.c#L56827), [CSV addresses](../disassembly/evora/B13200091/B13200091-symbols.csv#L4730) |
| CAL `45B0`, `45BC`, `45C8` | Six gear ratios: generic counts become `x/10 rpm/(km/h)`; replace voltage axes with gears 1–6. | [C centikph-to-RPM equation](../disassembly/evora/B13200091/B13200091.c#L56836), [family selection](../disassembly/evora/B13200091/B13200091.c#L56678), [CSV family](../disassembly/evora/B13200091/B13200091-symbols.csv#L4721) |
| CAL `0206`, `452E`, `4532`, `4536` | Four airbox pairs identify lower/upper RPM boundaries. The primary Tour pair also gains RPM units. No electrical-polarity or physical-valve-position claim is added. | [C hysteresis and coding](../disassembly/evora/B13200091/B13200091.c#L22444), [Tour address](../disassembly/evora/B13200091/B13200091-symbols.csv#L3848), [remaining addresses](../disassembly/evora/B13200091/B13200091-symbols.csv#L4634) |
| CAL `005A` | Replace false voltage labels with six cylinder-array entries. Existing offset-binary quarter-degree scaling remains unchanged. | [C signed-XOR trim](../disassembly/evora/B13200091/B13200091.c#L18312), [CSV address/type](../disassembly/evora/B13200091/B13200091-symbols.csv#L3557) |
| CAL `01E8`, `01EA` | Fuel-learning STFT thresholds: `int16` / `x/20` becomes `uint16` / `(x-32768)/20 %`; inverse is `x*20+32768`. | [C signed word after XOR 0x8000](../disassembly/evora/B13200091/B13200091.c#L28237), [CSV addresses](../disassembly/evora/B13200091/B13200091-symbols.csv#L3829) |
| CAL `0083`, `0084`, `0085` | Remove one attribute-identical duplicate scaling record from each thermal filter. Preserve `/2560` conversion and alternative-unit records elsewhere. | [C filter arithmetic](../disassembly/evora/B13200091/B13200091.c#L17638), [CSV coefficients](../disassembly/evora/B13200091/B13200091-symbols.csv#L3589) |
| LEA `0576`, `0986` | Two A/C-on learned-idle corrections: unsigned raw mg/s becomes signed `x*100/1024 mg/s`, matching the existing off entry. | [C signed interpolation](../disassembly/evora/B13200091/B13200091.c#L29214), [fixed-point airflow use](../disassembly/evora/B13200091/B13200091.c#L29746), [hot address](../disassembly/evora/B13200091/B13200091-symbols.csv#L2701), [cold address](../disassembly/evora/B13200091/B13200091-symbols.csv#L2717) |

### Cold-start packing and startup-factor corroboration

The GT packed region, in absolute RAM addresses, is:

| Region | Meaning |
|---|---|
| `40008D04..08` | Five-byte idle-decay temperature axis |
| `40008D09..0D` | Five-byte idle-decay data; the CSV's cold-start-axis label is misplaced here |
| `40008D0E..15` | Eight-byte cold-start temperature axis, file `06BA` |
| `40008D16..1D` | Eight-byte cold-start ignition data, file `06C2` |

The [GT lookup helper](../disassembly/evora/C132E0278/C132E0278.c#L22426) establishes data/axis argument order. The
[later GT cold-start call](../disassembly/evora/E132E0288/E132E0288.c#L15852) also adds five bytes, while the NA
CSV identifies the equivalent five-axis/five-data/eight-axis/eight-data layout
at `400094D4`, `400094D9`, `400094DE`, `400094E6`, with the corresponding
[idle consumer](../disassembly/evora/B13200091/B13200091.c#L29846). Original bytes are still needed to inspect actual
breakpoints and ordering, but the pointer correction is supported independently
of their values.

The [NA startup factor](../disassembly/evora/B13200091/B13200091.c#L17965) and [later GT factor](../disassembly/evora/E132E0288/E132E0288.c#L15797)
repeat the unsigned lookup, neutral 255 and multiplication by `factor/255`.
NA's definition already uses `u8_factor_1/255` for this map. The malformed
stopped-coolant gate does not change the established map storage or arithmetic.

## Binary verification still needed

| Item | Evidence / uncertainty | Required verification |
|---|---|---|
| Patched torque caps `16BE`, `2966` | XML explicitly requires patched **4 Nm/count**; current stock C uses **2 Nm/count**. The existing patched scales and warnings are preserved. | Identify the matching executable and patch, then inspect its load/shift instructions. Do not select a scale by calibration name alone. |
| Stopped-coolant startup gate | Export still says `min < temperature && temperature < min`, despite distinct minimum/maximum CSV addresses. | Resolve literal operands and branch directions in original instructions. Renaming the XML upper bound does not fix executable code. |
| Additive torque margin, throttle domains and controller gains | An apparent additive torque margin is labeled percent; some throttle paths mix apparent 10-/12-bit domains; several controller gains/outputs lack established physical units. | Inspect instruction widths, constants and input/output normalization before changing shared types or scales. |
| Fuel-mass units | `u16_mass_100ug` conflicts with an apparent 10 µg/count mass-to-time equation. | Confirm upstream charge/AFR/flow units and operation widths in the original program. Existing shared types are retained. |
| CAC control reconstruction | Current C still compares a Boolean PWM state with `true` in three branches; prior analysis described a byte-state reconstruction that is absent from this export. | Recover the actual load width and state comparisons at C lines 20319/20323/20327 from instructions before relying on the reconstructed branch behavior. |
| MAF-derived load and learned coordinates | Current C still assigns zero to `load_measured_maf`, `load_unknown`, `load_u8_tmp`; a comment reconstructs a likely expression. | Recover operations and density normalization from instructions and trace their consumers. These placeholders do not establish zero live load. |
| Duplicate calibration names | Multiple addresses share shift-light, O2 threshold and severe-misfire labels. | Match each address to bank/channel/axis consumers before assigning names; use address-based identities. |
| Values, image layout and active selection | Exports do not prove actual cell contents, breakpoint order, manual/IPS coding, active knock mode, checksums or file-header mapping. | Obtain matching original images/projects; verify mapping, patch identity, boundaries, coding and unchanged-byte round trips. Bench checks are needed for wiring, polarity and actuator behavior. |

For NA091, current C/XML distinguish injector-offset step `00BD` from pedal-zero
gain `00BE`, despite duplicate historical CSV labels. Verify their literal
instruction/address bindings before relying on the old names. Signed learned
idle values, active coding, actual breakpoints, checksums and installed actuator
wiring also need matching image or bench evidence. The
[NA injector guide](../disassembly/evora/B13200091/TuningInjectors.md) explains
additive trims, eligibility-dependent learning and possible limit overshoot.

## Regenerating Evora definitions

The C/CSV semantic annotations are historical and still disagree with several
corrected XML types and axes. In particular, the GT cold-start label is misplaced,
startup TPS is typed as an angle instead of an unsigned factor, pressure offsets
have unsigned annotations, and generic array axes can become voltage grids.
The exporter also has a duplicate datatype registration that produces identical
scalings. A fresh export can therefore restore incorrect metadata.

Align the Ghidra annotations and exporter before accepting a regeneration, then
compare ROM ids, payload addresses/dimensions, signedness, axis references and
the conversions documented above. Preserve actual alternative units and the
GT430 patched torque-cap warnings. XML parsing alone cannot verify these
semantics or establish that the executable matches the definition.
