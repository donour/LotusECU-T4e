# GT430 RomRaider corrections and verification gaps

Reviewed upstream revision: `donour/master_t6e` at
`90c318032c40e835ca077f076beef94c12f86cca` (2026-10-14).
Target: `romraider-defs/T6-EVORA--F430-V000E_defs.xml`, calibration ID
`T6-EVORA--F430-V000E`. The [whole-map comparison](../../analysis/DEFINITION_MAP_COMPARISON.md)
covers both GT430 and NA091, including learned data and non-engine subsystems.

The patch changes 39 GT root entries. These corrections follow exported C consumers, checked against address metadata
and other Evora exports where available. They change definition metadata, not
calibration bytes. Original firmware images and Ghidra databases are absent;
no fresh instruction decoding, calibration-value inspection or hardware test is
claimed. CSV names/types are historical annotations and can disagree with the
current C/XML.

## Applied corrections

Offsets below are relative to `CAL_base = 0x40008654`.

| Entry / file offset | Corrected interpretation | Exported evidence |
|---|---|---|
| Cylinder ignition trim `005A` | Six unsigned bytes, `(x-128)/4` degrees, inverse `x*4+128`; cylinder labels replace a voltage grid. | [Signed-XOR trim][trim-code], [quarter-degree timing][timing-code]. Labels follow array indices, without independently identifying harness/firing order. |
| Injector deadtime IAT compensation `18EE` | Restore its eight stored temperature breakpoints at `18E6`, `x*5/8-40 °C`. Payload remains a percent multiplier on deadtime. | [Lookup][deadtime-code]; CSV axis `40009F3A` minus the calibration base. Intake/manifold temperature selection follows `CAL_tmap_use_for_inj`. |
| Stopped-coolant upper bound `004E` | Rename minimum to maximum, matching its distinct CSV address. | CSV minimum/maximum at `400086A1/A2`. The malformed [gate][coolant-code] remains a separate issue. |
| Cold-start ignition `06C2` | Move its eight-cell coolant axis from `06B5` to **`06BA`**. | [Lookup adds five bytes][coldstart-code], [adjacent idle consumer][coldstart-other-code]; the later GT and NA independently corroborate the packed layout below. |
| Startup TPS ignition `195E` | Unsigned base-timing retention fraction: `x*100/255 %`, inverse `x*255/100`. Raw 255 is neutral. | [Unsigned lookup and sentinel][startup-lookup-code], [base-timing multiply/divide][startup-consumer-code]; NA and later GT have the same arithmetic. This is not an additive angle. |
| Fuel/manifold/oil pressure offsets `02EE`, `0032`, `0302` | Signed 16-bit direct mbar offsets. | Explicit `(short)` sign extension [for fuel/manifold][pressure-code] and [oil][oil-code], repeated in the later GT. Purge offset `002E` remains unsigned because its consumer differs. |
| A/C coolant bounds `0060`, `0061` | Percent → absolute `x*5/8-40 °C`. | [Direct coolant comparisons][ac-code]. |
| Fan temperature drop `010E` | Remove absolute-temperature offset: `x*5/8 °C` difference. | [Subtraction cancels the -40 offset][tempdrop-code]. |
| STFT limit `014E` | `x/20 %`, replacing `x*100/20 %`. | [Pulse contribution][stft-code], [clamp][stft-limit-code]. |
| Vehicle limit `0262` | `2*x km/h`. Raw-255 no-limit behavior is documented. | [Consumer forms raw*200 in centikph][speed-code]. |
| Advisory RPM thresholds `45D4`, `45D5`, `45DA`; hysteresis `45F0` | Thresholds `5*x+500 RPM`; hysteresis `5*x RPM`, without the absolute offset. | [Gear advisory arithmetic][gsi-code]. The `slip` naming does not make these wheel-slip traction thresholds. |
| Advisory maximum `45E4` | Direct RPM, replacing car-speed units/name. | Compared with estimated gear RPM in the same advisory consumer. |
| Gear/direction arrays `45B0`, `45BC`, `45C8`, `45D5`, `45DA`, `4670` | Gear ratios now display `x/10 rpm/(km/h)`. Replace voltage placeholders with gears 1–6, gears 2–6, or opening/closing, respectively. | [Advisory indexing][gsi-code], [throttle rate limits][tps-filter-code]. |
| Torque PI axes `276E`, `07F4` | Decode load error as `x-128`, replacing `x-127`. | [Error is biased by 128][pi-code]. No new physical gain units are inferred. |
| DPM filter `5C6C`; throttle filter `0222` | Weights use `/256` and `/1024`, respectively. | [DPM filter][dpm-code], [throttle filter][tps-filter-code]. |
| Mode 2F timeout `4438` | `x/200 seconds`, replacing `x/10`. | Raw counter loads, [decrement][mode2f-code] and [200 Hz task call][mode2f-call]. |
| Spark-efficiency RPM axis `3606` of payload `3626` | Standard `x*125/4+500 RPM`, replacing a raw number. | [Lookup uses `engine_speed_8bit`][spark-code], [speed-byte calculation][speed-byte-code]. |
| Fan afterrun `1846`; dwell `19AE` | Correct descriptions: five seconds/count afterrun; existing 64 µs/count dwell and its lookup inputs. | [Afterrun counter][afterrun-code], [dwell consumer][dwell-code]. Scaling is retained. |
| Scaling records `4FE0`, `4FC8`, `43A6` | Remove one identical duplicate each; retain real alternative units. | Exact XML duplicate attributes; the duplicate exporter datatype registration is removed too. |
| Ignition idle-error axes `0CA6`, `073C`, `0342` of payloads `0CB6`, `074C`, `0352` | `(x*4)-512 RPM`, replacing an unscaled or incorrectly biased error. | [Saturating byte lookup input][idle-ign-code] formed from [actual-minus-requested RPM][idle-error-origin]. NA and later GT agree. |
| Idle controller `416E`, `425E`, axes `414E`, `423E` | Axes `x-32768 RPM`; payloads `x-32768` signed controller counts, stored as unsigned words. | [Biased lookup inputs and signed-XOR output decoding][idle-word-code]. Physical gain/output units remain unresolved. |
| Clutch antistall speed `0026` | `x/10 km/h`, replacing direct km/h. | [Consumer divides centikph by ten][antistall-code], with byte saturation. |

### Cold-start packing and startup-factor corroboration

The GT packed region, in absolute RAM addresses, is:

| Region | Meaning |
|---|---|
| `40008D04..08` | Five-byte idle-decay temperature axis |
| `40008D09..0D` | Five-byte idle-decay data; the CSV's cold-start-axis label is misplaced here |
| `40008D0E..15` | Eight-byte cold-start temperature axis, file `06BA` |
| `40008D16..1D` | Eight-byte cold-start ignition data, file `06C2` |

The [GT lookup helper][lookup-code] establishes data/axis argument order. The
[later GT cold-start call][later-coldstart] also adds five bytes, while the NA
CSV identifies the equivalent five-axis/five-data/eight-axis/eight-data layout
at `400094D4`, `400094D9`, `400094DE`, `400094E6`, with the corresponding
[idle consumer][na-idle-code]. Original bytes are still needed to inspect actual
breakpoints and ordering, but the pointer correction is supported independently
of their values.

The [NA startup factor][na-startup-code] and [later GT factor][later-startup-code]
repeat the unsigned lookup, neutral 255 and multiplication by `factor/255`.
NA's definition already uses `u8_factor_1/255` for this map. The malformed
stopped-coolant gate does not change the established map storage or arithmetic.

## Remaining binary verification

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

Existing subsystem reports' claims that the primary MAF expression was restored,
the coolant comparison was fixed, or purge mass is established as 100 µg/count
are not supported by the current exported C. This review does not repeat those
claims as verified facts.

## Validation and regeneration

Run the [README commands](../../../../romraider-defs/README.md) for the regression
suite, whole-map inventory and post-export reconciliation. Tests check independent
consumer arithmetic, offset-binary/signed encoding, inverse conversion, table
boundaries, labels, legitimate alternative units, and preserved patched-cap
warnings. They do not test RomRaider GUI behavior or an original firmware image.

The C and CSV semantic annotations remain historical. In particular, the CSV's
cold-start axis identity, startup factor type, pressure signedness and trim bias
are stale. CSV repairs in this change fix quoting only and preserve every
symbol identity/type/address. The generic exporter cannot infer all these fixes
from those annotations. Export to a separate file and run the explicit reviewed
metadata reconciliation step; its address and geometry guards prevent applying
these metadata overrides to a different layout. Updating the actual Ghidra
annotations remains future project work when that database is available.

[trim-code]: ../C132E0278.c#L16135
[timing-code]: ../C132E0278.c#L16314
[deadtime-code]: ../C132E0278.c#L16613
[coolant-code]: ../C132E0278.c#L15867
[coldstart-code]: ../C132E0278.c#L15775
[coldstart-other-code]: ../C132E0278.c#L28769
[startup-lookup-code]: ../C132E0278.c#L15718
[startup-consumer-code]: ../C132E0278.c#L16050
[pressure-code]: ../C132E0278.c#L15205
[oil-code]: ../C132E0278.c#L15404
[ac-code]: ../C132E0278.c#L53477
[tempdrop-code]: ../C132E0278.c#L20723
[stft-code]: ../C132E0278.c#L16980
[stft-limit-code]: ../C132E0278.c#L26692
[speed-code]: ../C132E0278.c#L55185
[gsi-code]: ../C132E0278.c#L57152
[pi-code]: ../C132E0278.c#L52757
[dpm-code]: ../C132E0278.c#L58500
[tps-filter-code]: ../C132E0278.c#L52832
[mode2f-code]: ../C132E0278.c#L39728
[mode2f-call]: ../C132E0278.c#L11016
[spark-code]: ../C132E0278.c#L52375
[speed-byte-code]: ../C132E0278.c#L15454
[afterrun-code]: ../C132E0278.c#L19808
[dwell-code]: ../C132E0278.c#L15657
[lookup-code]: ../C132E0278.c#L22426
[later-coldstart]: ../../E132E0288/E132E0288.c#L15852
[na-idle-code]: ../../B13200091/B13200091.c#L29846
[na-startup-code]: ../../B13200091/B13200091.c#L17965
[later-startup-code]: ../../E132E0288/E132E0288.c#L15797

[idle-ign-code]: ../C132E0278.c#L15878
[idle-error-origin]: ../C132E0278.c#L28141
[idle-word-code]: ../C132E0278.c#L28320
[antistall-code]: ../C132E0278.c#L28426
