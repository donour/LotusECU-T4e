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

Source citations below are pinned to commit `90c3180`; their visible labels give
file and line number. Large C exports may not render with GitHub line anchors.
Download the pinned raw files and use those line numbers in a local editor:
[GT430 C](https://raw.githubusercontent.com/donour/LotusECU-T4e/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c),
[NA091 C](https://raw.githubusercontent.com/donour/LotusECU-T4e/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c),
[later GT C](https://raw.githubusercontent.com/donour/LotusECU-T4e/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/E132E0288/E132E0288.c).

| Profile | Calibration entries / RAM base | Learned entries / RAM base |
|---|---|---|
| NA091 | 1,091 / `40008E24` | 695 / `40002D40` |
| GT430 | 937 / `40008654` | 727 / `400030E8` |

These definitions contain 3,450 root entries and 3,161 nested axes. Names alone
are not unique identifiers. Some static voltage axes are legitimate implicit
ADC grids; only arrays with established gear/cylinder/boundary semantics have
been relabeled. Gear labels use `Gear #1` through `Gear #6` in both profiles. Learned data includes diagnostic state and adaptation, rather
than only tunable targets.

### GT430 scaling and axes

The corrections cover the calibration and learned-data entries listed below. All
offsets below are hexadecimal file offsets: CAL uses RAM base `40008654`,
while rows marked LEA use learned-data RAM base `400030E8`.

| Entry / file offset | Corrected interpretation | Exported evidence |
|---|---|---|
| Cylinder ignition trim `005A` | Six unsigned bytes, `(x-128)/4` degrees, inverse `x*4+128`; cylinder labels replace a voltage grid. | [Signed-XOR trim (C132E0278.c:16135)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L16135), [quarter-degree timing (C132E0278.c:16314)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L16314). Labels follow array indices, without independently identifying harness/firing order. |
| Injector deadtime IAT compensation `18EE` | Restore its eight stored temperature breakpoints at `18E6`, `x*5/8-40 °C`. Payload remains a percent multiplier on deadtime. | [Lookup (C132E0278.c:16616)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L16616); CSV axis `40009F3A` minus the calibration base. Intake/manifold temperature selection follows `CAL_tmap_use_for_inj`. |
| Stopped-coolant upper bound `004E` | Rename minimum to maximum, matching its distinct CSV address. | CSV minimum/maximum at `400086A1/A2`. The malformed [gate (C132E0278.c:15867)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L15867) remains a separate issue. |
| Cold-start ignition `06C2` | Move its eight-cell coolant axis from `06B5` to **`06BA`**. | [Lookup adds five bytes (C132E0278.c:15775)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L15775), [adjacent idle consumer (C132E0278.c:28769)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L28769); the later GT and NA independently corroborate the packed layout below. |
| Startup TPS ignition `195E` | Unsigned base-timing retention fraction: `x*100/255 %`, inverse `x*255/100`. Raw 255 is neutral. | [Unsigned lookup and sentinel (C132E0278.c:15718)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L15718), [base-timing multiply/divide (C132E0278.c:16050)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L16050); NA and later GT have the same arithmetic. This is not an additive angle. |
| Fuel/manifold/oil pressure offsets `02EE`, `0032`, `0302` | Signed 16-bit direct mbar offsets. | Explicit `(short)` sign extension [for fuel/manifold (C132E0278.c:15205)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L15205) and [oil (C132E0278.c:15404)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L15404), repeated in the later GT. Purge offset `002E` remains unsigned because its consumer differs. |
| A/C coolant bounds `0060`, `0061` | Percent → absolute `x*5/8-40 °C`. | [Direct coolant comparisons (C132E0278.c:53477)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L53477). |
| Fan temperature drop `010E` | Remove absolute-temperature offset: `x*5/8 °C` difference. | [Subtraction cancels the -40 offset (C132E0278.c:20725)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L20725). |
| STFT limit `014E` | `x/20 %`, replacing `x*100/20 %`. | [Pulse contribution (C132E0278.c:16980)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L16980), [clamp (C132E0278.c:26692)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L26692). |
| Vehicle limit `0262` | `2*x km/h`. Raw-255 no-limit behavior is documented. | [Consumer forms raw*200 in centikph (C132E0278.c:55185)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L55185). |
| Advisory RPM thresholds `45D4`, `45D5`, `45DA`; hysteresis `45F0` | Thresholds `5*x+500 RPM`; hysteresis `5*x RPM`, without the absolute offset. | [Gear advisory arithmetic (C132E0278.c:57152)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L57152). The `slip` naming does not make these wheel-slip traction thresholds. |
| Advisory maximum `45E4` | Direct RPM, replacing car-speed units/name. | Compared with estimated gear RPM in the same advisory consumer. |
| Gear/direction arrays `45B0`, `45BC`, `45C8`, `45D5`, `45DA`, `4670` | Gear ratios now display `x/10 rpm/(km/h)`. Replace voltage placeholders with gears 1–6, gears 2–6, or opening/closing, respectively. | [Advisory indexing (C132E0278.c:57152)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L57152), [throttle rate limits (C132E0278.c:52832)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L52832). |
| Torque PI axes `276E`, `07F4` | Decode load error as `x-128`, replacing `x-127`. | [Error is biased by 128 (C132E0278.c:52757)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L52757). No new physical gain units are inferred. |
| DPM filter `5C6C`; throttle filter `0222` | Weights use `/256` and `/1024`, respectively. | [DPM filter (C132E0278.c:58500)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L58500), [throttle filter (C132E0278.c:52832)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L52832). |
| Mode 2F timeout `4438` | `x/200 seconds`, replacing `x/10`. | Raw counter loads, [decrement (C132E0278.c:39728)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L39728) and [200 Hz task call (C132E0278.c:11016)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L11016). |
| Spark-efficiency RPM axis `3606` of payload `3626` | Standard `x*125/4+500 RPM`, replacing a raw number. | [Lookup uses `engine_speed_8bit` (C132E0278.c:52375)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L52375), [speed-byte calculation (C132E0278.c:15454)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L15454). |
| Fan afterrun `1846`; dwell `19AE` | Correct descriptions: five seconds/count afterrun; existing 64 µs/count dwell and its lookup inputs. | [Afterrun counter (C132E0278.c:19808)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L19808), [dwell consumer (C132E0278.c:15657)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L15657). Scaling is retained. |
| Scaling records `4FE0`, `4FC8`, `43A6` | Remove one identical duplicate each; retain real alternative units. | Exact XML duplicate attributes; the existing exporter still has a duplicate datatype registration that can regenerate these records. |
| Ignition idle-error axes `0CA6`, `073C`, `0342` of payloads `0CB6`, `074C`, `0352` | `(x*4)-512 RPM`, replacing an unscaled or incorrectly biased error. | [Saturating byte lookup input (C132E0278.c:15878)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L15878) formed from [actual-minus-requested RPM (C132E0278.c:28141)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L28141). NA and later GT agree. |
| Idle controller `416E`, `425E`, axes `414E`, `423E` | Axes `x-32768 RPM`; payloads `x-32768` signed controller counts, stored as unsigned words. | [Biased lookup inputs and signed-XOR output decoding (C132E0278.c:28320)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L28320). Physical gain/output units remain unresolved. |
| Clutch antistall speed `0026` | `x/10 km/h`, replacing direct km/h. | [Consumer divides centikph by ten (C132E0278.c:28426)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L28426), with byte saturation. |
| Idle barometric/voltage compensation CAL `0DD6`, `235E` | Unsigned offset-binary words: `x-32768` signed controller counts. The lookup returns an unsigned word before signed-XOR decoding; physical airflow units remain unresolved. | [GT lookup and decoding (C132E0278.c:28266)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L28266), [later GT (E132E0288.c:28466)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/E132E0288/E132E0288.c#L28466). |
| Learned idle LEA `06A4`, `06A6`, `0AB4`, `0AB6` | Signed `int16` raw accumulator counts, replacing unsigned words and unsupported flow displays. The controller contributes `10*raw/1024`, with interpolation and integer truncation; no physical airflow unit is asserted. | [Signed endpoint selection (C132E0278.c:28090)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L28090), [warm off value (C132E0278.c:28669)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L28669). |
| Fuel-learning STFT CAL `01E8`, `01EA` | Newly exposed unsigned offset-binary thresholds `(x-32768)/20 %`, matching NA. Raw 32768 is zero; inverse `20*x+32768`. | [GT comparison (C132E0278.c:27076)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L27076), [filtered STFT (C132E0278.c:27368)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L27368). |
| External torque margin CAL `5EB4` | Additive `x*9/5 Nm`, replacing percent. The display is linear; the consumer truncates the result to integer Nm before adding it to the request. | [GT constant and sum (C132E0278.c:52140)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L52140), [later GT explicit raw*180/100 (E132E0288.c:53968)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/E132E0288/E132E0288.c#L53968). All 256 GT byte results match `floor(raw*9/5)`. |
| Temperature/filter weights CAL `0085`, `020B`, `45ED` | Intake-air temperature uses `x*100/2560 %`; throttle-related and gear-advisory filters use `x*100/256 %`, replacing raw percent or `/255`. | [Temperature filter (C132E0278.c:15294)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L15294), [throttle filter (C132E0278.c:53403)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L53403), [advisory filter (C132E0278.c:57433)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L57433). |
| Thermal timing CAL `010C`, `0158` | Recirculation afterrun `5*x seconds`; engine-bay fan activation delay `x/200 seconds`. The former loads 1000 ticks/count; the latter compares a raw elapsed counter, both at 200 Hz. | [Pump load (C132E0278.c:19933)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L19933), [countdown and delay increment (C132E0278.c:10841)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L10841), [fan comparison (C132E0278.c:20216)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L20216). |
| Shift lights CAL `1546`, `154E`, `4026`, `402E` | Restore the payloads' stored gear axes, remove the redundant standalone breakpoint views, and show stage spacing `S=2*x RPM`. Upward thresholds are hard limit minus `4*S`, `3*S`, `2*S`; the former `8*x` display was only the first-light lead. | [Fixed-bin helper (C132E0278.c:14093)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L14093), [lookup, spacing and thresholds (C132E0278.c:20383)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L20383), [quarter-RPM tach representation (C132E0278.c:21411)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L21411). The lookup selects the first breakpoint at or above the gear, capped at the final point, without interpolation. |
| Oil warning CAL `6098` | Payload `16*x mbar`, replacing RPM units. Its stored RPM axis `6090` remains unchanged. | [Pressure comparison (C132E0278.c:20511)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L20511), [ADC pressure conversion (C132E0278.c:15402)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L15402), [later GT (E132E0288.c:20650)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/E132E0288/E132E0288.c#L20650). |
| Cooling low-RPM hysteresis CAL `02FE` | Replace voltage labels with inhibit-entry and inhibit-clearance thresholds; preserve the existing `4*x RPM` values. | [Indexed comparisons (C132E0278.c:20062)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L20062). |

### NA091 scaling and axes

The changes cover the calibration and learned-data entries listed below. CAL
and LEA offsets refer to their respective RAM bases in the table above.

| Image / offsets | Correction | Exported evidence |
|---|---|---|
| CAL `0262` | Vehicle limit: `x` becomes `2*x km/h`. Document raw 255's no-limit context and conditional enforcement. | [C target multiplied by 200 (B13200091.c:55103)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L55103), [CSV address (B13200091-symbols.csv:3917)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091-symbols.csv#L3917) |
| CAL `45D4`, `45D5`, `45DA` | Advisory thresholds: `4*x+500` becomes `5*x+500 RPM`; manual/IPS five-cell arrays identify gears 2–6. | [C five-RPM arithmetic (B13200091.c:56854)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L56854), [gear-to-cell selection (B13200091.c:56684)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L56684), [CSV family (B13200091-symbols.csv:4724)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091-symbols.csv#L4724) |
| CAL `45EF`, `45F0` | Downshift idle margin and RPM offset: generic counts become `5*x RPM` differences, without a 500 RPM bias. | [C differences (B13200091.c:56920)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L56920), [CSV addresses (B13200091-symbols.csv:4740)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091-symbols.csv#L4740) |
| CAL `45E4`, `45E6` | Maximum candidate-gear RPM and manual speed offset gain direct RPM and km/h units, respectively. Values retain identity scaling. | [C RPM comparison (B13200091.c:56863)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L56863), [speed multiplied by 100 (B13200091.c:56827)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L56827), [CSV addresses (B13200091-symbols.csv:4730)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091-symbols.csv#L4730) |
| CAL `45B0`, `45BC`, `45C8` | Six gear ratios: generic counts become `x/10 rpm/(km/h)`; replace voltage axes with gears 1–6. | [C centikph-to-RPM equation (B13200091.c:56836)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L56836), [family selection (B13200091.c:56678)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L56678), [CSV family (B13200091-symbols.csv:4721)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091-symbols.csv#L4721) |
| CAL `0206`, `452E`, `4532`, `4536` | Four airbox pairs identify lower/upper RPM boundaries. The primary Tour pair also gains RPM units. No electrical-polarity or physical-valve-position claim is added. | [C hysteresis and coding (B13200091.c:22444)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L22444), [Tour address (B13200091-symbols.csv:3848)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091-symbols.csv#L3848), [remaining addresses (B13200091-symbols.csv:4634)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091-symbols.csv#L4634) |
| CAL `005A` | Replace false voltage labels with six cylinder-array entries. Existing offset-binary quarter-degree scaling remains unchanged. | [C signed-XOR trim (B13200091.c:18312)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L18312), [CSV address/type (B13200091-symbols.csv:3557)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091-symbols.csv#L3557) |
| CAL `01E8`, `01EA` | Fuel-learning STFT thresholds: `int16` / `x/20` becomes `uint16` / `(x-32768)/20 %`; inverse is `x*20+32768`. | [C signed word after XOR 0x8000 (B13200091.c:28237)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L28237), [CSV addresses (B13200091-symbols.csv:3829)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091-symbols.csv#L3829) |
| CAL `0083`, `0084`, `0085` | Remove one attribute-identical duplicate scaling record from each thermal filter. Preserve `/2560` conversion and alternative-unit records elsewhere. | [C filter arithmetic (B13200091.c:17638)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L17638), [CSV coefficients (B13200091-symbols.csv:3589)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091-symbols.csv#L3589) |
| LEA `0576`, `0986` | Two A/C-on learned-idle corrections: unsigned raw mg/s becomes signed `x*100/1024 mg/s`, matching the existing off entry. | [C signed interpolation (B13200091.c:29214)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L29214), [fixed-point airflow use (B13200091.c:29746)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L29746), [hot address (B13200091-symbols.csv:2701)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091-symbols.csv#L2701), [cold address (B13200091-symbols.csv:2717)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091-symbols.csv#L2717) |
| CAL `0C56`, `0C76`, axes `0C46`, `0C66` | Proportional airflow correction `(x-128)*100 mg/s`; unsigned integral-step magnitude `x*100/1024 mg/s` per eligible update. Both RPM-error axes decode `4*x-512`, replacing raw numbers/percent. Integral sign comes from error direction; update cadence is gated separately. | [Error encoding and lookup (B13200091.c:29434)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L29434), [signed proportional term and integral updates (B13200091.c:29555)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L29555), [100 mg/s airflow sum (B13200091.c:29747)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L29747). |
| CAL `006E`, `006F`, `02BF` | Learned-idle upper bound and positive lower-bound magnitude `100*x mg/s`; temperature-pair labels identify cold/warm interpolation boundaries. | [Upper/lower comparisons (B13200091.c:29626)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L29626), [cold/warm interpolation (B13200091.c:29214)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L29214). |
| CAL `010C`, `0150`, `0158` | Recirculation stopped-engine duration `5*x seconds`; fan 1 and engine-bay auxiliary activation delays `x/200 seconds`. The auxiliary stopped-engine path bypasses its delay. | [200 Hz counters (B13200091.c:14047)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L14047), [pump load (B13200091.c:21782)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L21782), [fan 1 (B13200091.c:21894)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L21894), [auxiliary fan (B13200091.c:22047)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L22047). |
| CAL `0059`, `26EE`, axis `26CE` | Evaporator-temperature filter weight `x*100/256 %`; conversion payload `(x-400)/10 °C`, with voltage axis `5*x/1023 V`. | [Lookup subtracts 400 (B13200091.c:17624)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L17624), [filter (B13200091.c:17654)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L17654). |
| CAL `4426`, `442A` | Pedal D/E valid-voltage ranges `5*x/1023 V`, with minimum/maximum labels replacing generated voltage axes. | [Track D thresholds (B13200091.c:54367)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L54367), [track E thresholds (B13200091.c:54589)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L54589). |
| CAL `154E`, `402E` | Shiftlight stage spacing `S=2*x RPM`; stored gear axes remain at `1546`, `4026`. Upward thresholds are hard limit minus `4*S`, `3*S`, `2*S`, with separate downward deadband. | [Fixed-bin lookup and spacing (B13200091.c:22112)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L22112), [tach representation (B13200091.c:23266)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L23266). |

### Cold-start packing and startup-factor corroboration

The GT packed region, in absolute RAM addresses, is:

| Region | Meaning |
|---|---|
| `40008D04..08` | Five-byte idle-decay temperature axis |
| `40008D09..0D` | Five-byte idle-decay data; the CSV's cold-start-axis label is misplaced here |
| `40008D0E..15` | Eight-byte cold-start temperature axis, file `06BA` |
| `40008D16..1D` | Eight-byte cold-start ignition data, file `06C2` |

The [GT lookup helper (C132E0278.c:22426)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/C132E0278/C132E0278.c#L22426) establishes data/axis argument order. The
[later GT cold-start call (E132E0288.c:15852)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/E132E0288/E132E0288.c#L15852) also adds five bytes, while the NA
CSV identifies the equivalent five-axis/five-data/eight-axis/eight-data layout
at `400094D4`, `400094D9`, `400094DE`, `400094E6`, with the corresponding
[idle consumer (B13200091.c:29846)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L29846). Original bytes are still needed to inspect actual
breakpoints and ordering, but the pointer correction is supported independently
of their values.

The [NA startup factor (B13200091.c:17965)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L17965) and [later GT factor (E132E0288.c:15797)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/E132E0288/E132E0288.c#L15797)
repeat the unsigned lookup, neutral 255 and multiplication by `factor/255`.
NA's definition already uses `u8_factor_1/255` for this map. The malformed
stopped-coolant gate does not change the established map storage or arithmetic.


### Duplicate table names

These pre-existing groups remain ambiguous. RomRaider uses table names as
identifiers, so separate offsets must not be treated as interchangeable entries.
NA has 10 calibration and 3 learned-data groups, covering 26 entries; GT has
three calibration groups and one learned-data group. Resolve their address-bound
consumers before assigning bank/channel meanings or removing entries.

| Profile / image | Exact table name | File offsets |
|---|---|---|
| NA CAL | `ac: inhibit rpm cutoff min hold` | `0072`, `0133` |
| NA CAL | `closedloop: fuel learn baro min` | `01AC`, `01AD` |
| NA CAL | `closedloop: max tipout enleanment` | `4540`, `4541` |
| NA CAL | `clutch: confidence increment` | `4582`, `4583` |
| NA CAL | `gsi: max gear step` | `45F2`, `45F4` |
| NA CAL | `idle: flow integral adj max` | `006C`, `006D` |
| NA CAL | `idle: sensor fault coolant temp` | `455D`, `455E` |
| NA CAL | `inj: soak time max` | `0304`, `030C` |
| NA CAL | `knock: threshold obd ii check enable load` | `45A8`, `45A9` |
| NA CAL | `obd: ii P0141` | `4B74`, `4C14` |
| NA LEA | `obd: ii P0141 fail counter` | `185A`, `1977` |
| NA LEA | `obd: ii P0141 flags` | `1859`, `1976` |
| NA LEA | `obd: ii P0141 pass counter` | `185B`, `1978` |
| GT CAL | `sensor: o2 lean voltage threshold` | `4478`, `4480` |
| GT CAL | `sensor: o2 rich voltage threshold` | `447A`, `447E` |
| GT CAL | `tps: limit severe misfire 1 cut` | `0205`, `0214` |
| GT LEA | `unused: byte3` | `1B4E`, `1B4F` |

### GT430 idle airflow scale

GT subtracts `idle_bypass_airflow/10` in `C132E0278.c:28674`; NA subtracts
`idle_bypass_airflow/100` in `B13200091.c:29761`. Their bypass producers use the
same arithmetic (GT `38516–38519`, NA `39159–39163`), and both charge conversions
use flow times period divided by 1,000,000 (GT `22308–22312`, NA `23711–23715`).
This supports a tenfold difference in controller counts, while GT's
`u16_flow_100mg_s` annotation suggests otherwise. If bypass flow is mg/s, GT
controller counts would be 10 mg/s and learned corrections `100*raw/1024 mg/s`,
matching NA's physical scale. That premise still needs original-binary and
physical-unit confirmation. GT learned/correction entries therefore remain raw
counts; the existing `idle: comp while moving` display is also raw counts rather
than retaining an unsupported `100*raw mg/s` label.

## Binary verification still needed

| Item | Evidence / uncertainty | Required verification |
|---|---|---|
| Patched torque caps `16BE`, `2966` | XML explicitly requires patched **4 Nm/count**; current stock C uses **2 Nm/count**. The existing patched scales and warnings are preserved. | Identify the matching executable and patch, then inspect its load/shift instructions. Do not select a scale by calibration name alone. |
| Stopped-coolant startup gate | Export still says `min < temperature && temperature < min`, despite distinct minimum/maximum CSV addresses. | Resolve literal operands and branch directions in original instructions. Renaming the XML upper bound does not fix executable code. |
| Throttle domains and controller gains | Some throttle paths mix apparent 10-/12-bit domains; several controller gains/outputs and GT learned-idle corrections lack established physical airflow units. The additive torque-margin scale is resolved above. | Inspect instruction widths, constants and input/output normalization before changing the remaining shared types or physical units. |
| Fuel-mass units | `u16_mass_100ug` conflicts with an apparent 10 µg/count mass-to-time equation. | Confirm upstream charge/AFR/flow units and operation widths in the original program. Existing shared types are retained. |
| CAC control reconstruction | Current C still compares a Boolean PWM state with `true` in three branches; prior analysis described a byte-state reconstruction that is absent from this export. | Recover the actual load width and state comparisons at C lines 20319/20323/20327 from instructions before relying on the reconstructed branch behavior. |
| MAF-derived load and learned coordinates | Current C still assigns zero to `load_measured_maf`, `load_unknown`, `load_u8_tmp`; a comment reconstructs a likely expression. | Recover operations and density normalization from instructions and trace their consumers. These placeholders do not establish zero live load. |
| Duplicate calibration names | O2 threshold and severe-misfire labels still refer to multiple addresses in historical exports. Shiftlight axis/payload pairing is resolved above. | Match remaining addresses to bank/channel consumers before assigning semantic names; use address-based identities. |
| Values, image layout and active selection | Exports do not prove actual cell contents, breakpoint order, manual/IPS coding, active knock mode, checksums or file-header mapping. | Obtain matching original images/projects; verify mapping, patch identity, boundaries, coding and unchanged-byte round trips. Bench checks are needed for wiring, polarity and actuator behavior. |

For NA091, current C/XML distinguish injector-offset step `00BD` from pedal-zero
gain `00BE`, despite duplicate historical CSV labels. CAL `0300` and `0302`
also have cooling/oil labels that conflict with O2-voltage comparisons in the
[current consumer (B13200091.c:39279)](https://github.com/donour/LotusECU-T4e/blob/90c318032c40e835ca077f076beef94c12f86cca/disassembly/evora/B13200091/B13200091.c#L39279); their
address bindings and voltage domain remain unresolved. Verify the literal
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
scalings. A fresh export can therefore restore incorrect metadata; this PR does
not yet prevent regeneration drift. CSV/C annotation alignment and an exporter
that preserves these corrections are separate follow-up work.

Align the Ghidra annotations and exporter before accepting a regeneration, then
compare ROM ids, payload addresses/dimensions, signedness, axis references and
the conversions documented above. Preserve actual alternative units and the
GT430 patched torque-cap warnings. XML parsing alone cannot verify these
semantics or establish that the executable matches the definition.
