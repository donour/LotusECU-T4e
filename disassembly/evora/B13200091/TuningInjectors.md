# Injector Rescaling Guide — B13200091 (2011 Lotus Evora NA)

How to move this calibration from the stock injectors to a different set, using the
Injector Dynamics ID1050-XDS as the worked example.

All line numbers refer to `B13200091.c`. Addresses are RAM addresses of the cal block
(cal base `0x40008E24`). The **file offset** column refers to the cal file
(`B132E0091_TAB.cpt`, 25050 bytes), which is a byte-for-byte copy of the RAM cal block
apart from its 32-byte text header:

```
file offset = RAM address − 0x40008E24          (all values big-endian)
```

The RomRaider defs (`T6-V00BU_defs.xml`) use the same offsets.

---

## 0. The governing principle

The fuel model computes a **fuel mass** first, then converts it to time using a flow
constant:

```
fuel_mass_required (10µg) = load_mass_per_stroke_raw × 10000 / afr_target      [18630]
inj_flow_rate      (mg/s) = CAL_inj_flow_rate × inj_efficiency / 200           [18609]
pw_fuel            (µs)   = fuel_mass × 10000 / (inj_flow_rate × bank_split)   [18642]
pw_pre_trim        (µs)   = pw_fuel × enrichments + dfco + tip_in + tip_out    [18752]
pw_commanded       (µs)   = inj_deadtime_base + LEA_offset
                            + pw_pre_trim × (1 + ltft + stft/2)                [18784]
```

Everything upstream of `pw_fuel` is in the **mass domain** and is injector-agnostic —
AFR targets, warmup factors, cranking enrichments, purge fuel subtraction. None of it
changes.

Five classes of thing matter for the swap:

| Class | Behaviour on swap | Examples |
|---|---|---|
| **The flow constant** | Scales by the flow ratio | `CAL_inj_flow_rate` |
| **µs added on top of deadtime** | Divide by the flow ratio | prime pulse, transient scaler, learned-offset limits and DTC thresholds |
| **µs that *include* deadtime** | `new_dt + (old − old_dt) / ratio` | EVAP gates, Mode `$2F` test pulse |
| **Injector properties** | Replace outright, do *not* scale | deadtime |
| **Ratios / masses** | Leave alone | AFR map, enrichment factors, bank balance |

The split between the two µs classes is the subtle part. Above the opening point every
extra µs delivers `flow_rate × µs` of fuel, so a term that rides on top of deadtime
scales cleanly by 1/ratio. A term compared against, or standing in for, the *whole*
pulse contains a deadtime component that does not shrink with injector size. That term
must be split, its fuel part scaled, and the new deadtime added back.

---

## 1. Before you touch anything: determine the flow ratio

### 1.1 There is no fuel pressure compensation in this firmware

`fuel_pressure_unused` is computed at line 17551 and never consumed. There is no pump
control loop — `siu_gpdo[0xb5]` is a plain on/off relay. Whatever differential pressure
the car runs is **baked into the flow constant**.

Consequences:

* Keep the rail pressure unchanged, or rescale by `sqrt(ΔP_new / ΔP_old)` yourself.
* Rate both injectors at the **same** pressure when computing the ratio.
* Because flow goes as `sqrt(ΔP)` for both injectors equally, the ratio is
  load-independent even though this car's returnless rail sees ΔP vary with MAP. The
  existing load-dependent shaping in `CAL_inj_efficiency` stays valid.

### 1.2 Compute the ratio

```
ratio = new_injector_cc_min / stock_injector_cc_min     (both at the same pressure)
```

Do **not** derive the stock figure from the ECU constant. `CAL_inj_flow_rate` is the
ECU's *belief* about the stock injector, and that belief already absorbs MAF and VE
calibration error. Scaling the belief by the true physical ratio preserves that
relationship, so all the existing trims and map shaping stay meaningful. Deriving the
ratio from the constant would double-count the error.

### 1.3 Worked example — ID1050-XDS

* ID1050-XDS: **1065 cc/min at 3 bar** (from ID's published spec — confirm against the
  documentation for your actual part).
* Stock Evora NA injector: confirm the rating independently. For reference, the ECU
  constant of 4350 mg/s implies roughly 348 cc/min at ρ=0.75, which sanity-checks
  against a ~276 hp NA V6 sitting near 67% max duty at redline.

```
ratio = 1065 / 348 ≈ 3.06
```

The rest of this guide uses **ratio = 3.06**.

---

## 2. Step 1 — `CAL_inj_flow_rate`

| | |
|---|---|
| Address | `0x40009024` (file `0x0200`) |
| Type | `u16_flow_mg/s` |
| Stock | **4350** (`10 FE`) |
| Used at | 18609 (fuel model), 18896 (trip computer), 38922 (EVAP purge headroom) |

This is per-injector. Confirmed from the bank-split math at 18642: a neutral
`inj_bank_balance_ratio` of 200 gives each bank a ×1.0 divisor against per-cylinder
fuel mass.

```
new = 4350 × 3.06 = 13311   (33 FF)
```

Range is fine — u16 caps at 65535, and the derived `inj_flow_rate` peaks near 17000
with the efficiency map at its maximum of 255.

---

## 3. Step 2 — deadtime

| | |
|---|---|
| Table | `CAL_inj_deadtime_base` @ `0x4000b4b2` (file `0x268E`), 8×8, `u8_time_20us` |
| X axis | `CAL_inj_deadtime_base_X_voltage` @ `0x4000b4a2` (file `0x267E`), `u8_voltage_72/1023v` |
| Y axis | `CAL_inj_deadtime_base_Y_airtemp_maf` @ `0x4000b4aa` (file `0x2686`), `u8_temp_5/8-40c` |
| Layout | row = IAT, column = voltage; byte index = row × 8 + col |
| Applied at | 18534 (lookup on `sensor_adc_ecu_voltage >> 2`, `airtemp_tmaf`; `× 20` → µs), added at 18784 |

**Deadtime does not scale with injector size.** It is an electromechanical property of
the injector. Replace the surface with the new injector's data; do not multiply or
divide it by the flow ratio.

This matters more here than in most ECUs because deadtime is added *after* the fuel
trims (18784). STFT and LTFT scale only the fuel portion, so they cannot absorb a
deadtime error — it shows up instead as trims that disagree between idle and load, and
as the learned offsets (§7) running to their limits.

### 3.1 Stock table (µs)

```
IAT \ V     6.48   6.48   6.48   6.48   9.01  11.54  14.01  16.54
   0C       3040   3040   3040   3040   1620    840    660    520
  10C       3080   3080   3080   3080   1680    900    720    580
  20C       3120   3120   3120   3120   1740    960    780    640
  40C       3240   3240   3240   3240   1880   1080    880    740
  60C       3420   3420   3420   3420   2060   1240   1000    880
  80C       3700   3700   3700   3700   2260   1380   1140   1020
 100C       3920   3920   3920   3920   2500   1580   1280   1160
 119C       4180   4180   4180   4180   2720   1760   1420   1280
```

Raw cal bytes are these values ÷ 20. Resolution is 20 µs/count; range is 0–5100 µs.
Stock axes: X = `5C 5C 5C 5C 80 A4 C7 EB`, Y = `40 50 60 80 A0 C0 E0 FF`
(0, 10, 20, 40, 60, 80, 100, 119 °C).

### 3.2 Fix the voltage axis first

Four of the eight breakpoints are a degenerate clamp at 6.48 V, so the table has only
five usable voltage points. Re-space it to use ID's curve properly:

```
volts    6    8   10   11   12   13   14   16
raw     85  114  142  156  171  185  199  227          (raw = V × 1023/72)
hex     55   72   8E   9C   AB   B9   C7   E3
```

Leave the IAT axis alone.

### 3.3 Fill the temperature dimension

ID publishes offset vs voltage only, with no temperature axis. Put the ID curve in the
20 °C row, then choose:

* **Flat** — write the same curve into all eight IAT rows. Safe default.
* **Keep a reduced stock trend** — the stock temperature climb (+760 µs from 0 °C to
  119 °C at 14 V) models injector coil heating with IAT as the proxy. A heuristic is to
  keep the stock 14 V trend divided by the ratio, which gives per-row add counts
  relative to the 20 °C row of:

  ```
  IAT    0C  10C  20C  40C  60C  80C  100C  119C
  add    -2   -1    0   +2   +4   +6    +8   +10     (counts of 20 µs)
  ```

  This is a judgement call, not something derived from ID data.

If you go flat and later find LTFT walking with IAT, that is the signal that the
temperature dimension was doing real work. See §11.2.

### 3.4 Fit deadtime to the pulse range you actually run

ID's offset figure is the intercept of a linear flow fit. The ID1050-XDS is strongly
nonlinear below about 1 ms total pulse, and this firmware has **no short-pulse
correction table** (§11). The deadtime value is therefore the only lever that sets where
the linear model is accurate.

At 3× the warm idle pulse is roughly 0.9–1.0 ms total (§5), which sits right at the
edge of the nonlinear region. If ID's short-pulse data is available, regress
delivered mass vs pulse width over roughly **0.9–2.0 ms** and use that intercept as the
offset at each voltage. This trades accuracy at WOT (where deadtime is a small fraction
of the pulse and errors hardly matter) for accuracy at idle and light cruise (where it
dominates).

### 3.5 Naming note

`_base` is misleading — there is no second deadtime term anywhere in the firmware.
`CAL_inj_pulse_offset` would be the honest name.

---

## 4. Step 3 — the cranking prime pulse

| | |
|---|---|
| Table | `CAL_inj_startup_enrichment_offset` @ `0x4000a6ea` (file `0x18C6`), 16 × `u8_time_256us` |
| X axis | `..._X_coolant_temp_engine_stopped` @ `0x4000a6da` (file `0x18B6`, −30 °C … 118.8 °C) |
| Used at | 18553 (`offset×256 + deadtime`), fired at 14879 |

This is a raw time, not a mass. At first crank sync the ECU fires **all six injectors
simultaneously** (staggered 1° apart) for `inj_startup_pulse_time`. Stock is 28.7 ms
per injector at 20 °C and clips at 65.5 ms below −20 °C.

Deadtime is added separately at 18553, so this table is pure fuel time — divide it by
the ratio. Left alone with a 3× injector it is a flooded cold start.

```
coolant °C   -30  -20  -10    0   10   20   30   40   50   60   70   80   90  100  110  119
stock raw    255  255  234  191  150  112   87   67   51   42   42   41   41   41   41   41
stock hex     FF   FF   EA   BF   96   70   57   43   33   2A   2A   29   29   29   29   29
÷ 3.06        83   83   76   62   49   37   28   22   17   14   14   13   13   13   13   13
new hex       53   53   4C   3E   31   25   1C   16   11   0E   0E   0D   0D   0D   0D   0D
```

Bonus: the cold end no longer saturates at 255, so sub-zero starts regain resolution
they did not have stock.

---

## 5. Step 4 — the EVAP purge gates

**This is the step that is easy to miss and will fail an emissions readiness check.**

| Cal | Address | File | Type | Stock | ×8 |
|---|---|---|---|---|---|
| `CAL_evap_purge_min_inj_pulse_enter` | `0x40008ec9` | `0x00A5` | `u8_time_8us` | 188 | **1504 µs** |
| `CAL_evap_purge_min_inj_pulse_exit` | `0x40008eca` | `0x00A6` | `u8_time_8us` | 162 | **1296 µs** |

Used at 38881–38895 and 38924. They form a hysteresis pair gating purge permission on
the **full commanded pulse** `obd_ii_injector_pulse_time_bankN_us` — deadtime + LEA
offset + trimmed fuel.

### Why it breaks

Stock idle pulse is roughly 1.7 ms — comfortably above the 1504 µs enter threshold, so
purge runs at idle. At 3× the idle pulse drops to roughly 0.9–1.0 ms, **below the
1296 µs exit threshold**. Purge never enables at idle or light load. The canister
saturates, P0441 sets, the leak test never collects its prerequisites, and EVAP
readiness never completes.

(Those pulse figures are estimates from the load model, not logged data — but the
direction and rough magnitude are not in doubt.)

### The rescale

Preserve the *fuel mass* trigger point rather than the raw time:

```
new_us = new_deadtime + (old_us − old_deadtime) / ratio
raw    = round(new_us / 8)
```

`old_deadtime` and `new_deadtime` are the values at the warm-idle operating point
(log `sensor_adc_ecu_voltage`, `airtemp_tmaf` and `inj_deadtime_base`, or assume ~14 V
and 20–40 °C, which gives 780–880 µs stock). Worked at 780 µs stock deadtime, 600 µs
new deadtime, ratio 3.06:

```
enter:  600 + (1504 − 780)/3.06 = 837 µs  ->  raw 105  (69)
exit:   600 + (1296 − 780)/3.06 = 769 µs  ->  raw  96  (60)
```

Recompute with the real ID offset at your idle voltage. Enter must stay above exit.

### Why not just divide by 3

A straight ÷3.06 gives 61 / 53 raw (≈ 491 / 424 µs). That is **below the new deadtime
itself**, so every running pulse exceeds it: purge is permanently permitted, including
at near-zero fuel, and the hysteresis is meaningless. Worse, line 38924 computes the
purge fuel headroom as `inj_flow_rate × (enter_threshold − inj_deadtime_base) / 10000`.
With enter below deadtime that bracket goes negative and is masked/truncated into a u16
(`DAT_40001f98`), so the purge fuel limit becomes garbage.

With the correct transform, flow triples while the bracket thirds, so the resulting
mass limit is invariant — the code stays self-consistent. The new values come out at
about 0.55× stock, not 0.33×.

---

## 6. Step 5 — the transient µs scaler

| | |
|---|---|
| Cal | `CAL_dfco_recovery_enrich_scale_us` @ `0x40008f9e` (file `0x017A`), `u8_time_us` |
| Stock | **120** |
| New | 120 / 3.06 = **39** (`27`) |
| Used at | 23236 (tip-out), 23247 (tip-in), 23388 (DFCO recovery) |

One cal, three consumers. It is a **µs-per-count unit**, not a pulse width:

```
dfco_recovery_enrichment  = scale_us × lookup(CAL_dfco_recovery_enrich_X_cut_duration)   (count up to 255)
injtip_in_enrichment_raw  = scale_us × (tps_rate × rpm_scale × coolant_scale × gear_scale)
injtip_out_enleanment_raw = scale_us × (tps_rate × rpm_scale × coolant_scale)
```

All three land directly on `inj_pw_bankN_pre_trim_us` at 18752, on top of an injector
that is already open. Every µs therefore delivers `flow_rate × µs` of fuel — 3.06× more
on the ID1050-XDS. Left at 120, DFCO recovery, tip-in and tip-out all run about 3× too
rich, and closed loop cannot pull it back because `cl_transient_holdoff` suspends
correction while any of these adders is non-zero (27605, 27882).

**Injector nonlinearity does not change this.** The ID's short-pulse behaviour is a
function of the *total* commanded pulse. An adder only lengthens a pulse that already
contains deadtime + base fuel, so it moves the pulse out of the nonlinear region; the
incremental fuel is at the linear slope apart from any part of the span that is below
~1 ms. Short-pulse error belongs in deadtime (§3.4) and `CAL_inj_efficiency` (§11.1),
which act on the total pulse.

Dividing every count table (`CAL_dfco_recovery_enrich_X_cut_duration`, the
`CAL_injtip_*` scales) instead would also work, but it is many more edits and loses
resolution in small u8 tables. Rounding to 39 is 0.6% lean on transients. Treat it as a
starting point and tune tip-in and DFCO resume from logged lambda last.

**Naming:** the current name describes only one of three uses.
`CAL_inj_transient_us_per_count` is more accurate.

---

## 7. Step 6 — learned-offset limits and fuel-trim DTC thresholds

| Cal | Address | File | Type | Stock | New |
|---|---|---|---|---|---|
| `CAL_inj_fuel_learn_lean_time_limit` | `0x40009010` | `0x01EC` | `u8_time_10us` | 46 (460 µs) | **15** (`0F`) |
| `CAL_inj_fuel_learn_rich_time_limit` | `0x40009011` | `0x01ED` | `u8_time_10us` | 46 (460 µs) | **15** (`0F`) |
| `CAL_obd_P0171_learn_time_threshold` | `0x4000d226` | `0x4402` | `u8_time_10us` | 45 (450 µs) | **14** (`0E`) |
| `CAL_obd_P0172_learn_time_threshold` | `0x4000d227` | `0x4403` | `u8_time_10us` | 45 (450 µs) | **14** (`0E`) |

`LEA_inj_offset_learn_idle/off_idle_bankN` is a learned µs adder applied alongside
deadtime (18784). It is clamped at ±`limit × 10` µs (28085–28108, 28163–28186).
P0171/P0174 set when it exceeds +`threshold × 10` µs, and P0172/P0175 when it goes below
−`threshold × 10` µs (28294–28366; bank 2 uses the same two thresholds).

Stock, 460 µs is about 2 mg of fuel per injection. On the ID1050-XDS it is about 6 mg:
3× the trim authority, and the fuel-trim DTCs would only set at 3× the stock fuel error.
Divide by the ratio.

**Keep each threshold below its limit.** The tests are strict comparisons, so with
threshold == limit the offset can never exceed the threshold and the DTC can never set.
Stock keeps a 1-count (10 µs) gap; so does 15 / 14.

`CAL_inj_fuel_learn_time_step` (2 µs per step) can stay. Note the symbol export lists
this label at both `0x40008ee1` (file `0x00BD`, value 2) and `0x40008ee2` (file `0x00BE`,
value 128); it has not been confirmed from the code which address is read. 2 is the
only plausible step against a ±460 µs clamp, but do not edit either byte until that is
resolved.

---

## 8. Step 7 — recompute the cal checksum (required)

**The engine will not start if you skip this.**

| | |
|---|---|
| Computed at | 13288: `calibration_verification_number = CRC16(&CAL_ecu_data_base, len − 34)` |
| Checked at | 14819: spark is only scheduled if it matches `CAL_ecu_cvn`, or the ECU is unlocked |
| Stored at | `CAL_ecu_cvn` @ `0x4000effc` (file `0x61D8`), big-endian, stock `F7CA` |
| Covers | file `0x0020`–`0x61D7` (RAM `0x40008E44`–`0x4000EFFB`) |
| Algorithm | CRC-16/ARC: reflected poly `0xA001`, init 0 (table at `0xc27f8`) |

Run this after every edit, as the last step:

```python
import sys
p = sys.argv[1]; d = bytearray(open(p, 'rb').read())
c = 0
for b in d[0x20:0x61D8]:
    c ^= b
    for _ in range(8):
        c = (c >> 1) ^ 0xA001 if c & 1 else c >> 1
print(hex(c))
d[0x61D8:0x61DA] = c.to_bytes(2, 'big')
open(p, 'wb').write(d)
```

On the unmodified file it prints `0xf7ca`; check that first to confirm the script and
file match.

The alternative bypass is the `"WTF?"` magic at `CAL_ecu_unlock_magic` @ `0x4000eff8`
(file `0x61D4`), but that also unlocks the dev-mode CAN memory access. Fix the CRC
instead.

P0601 is unrelated to this check (it comes from `main_diagnostic_flags` bit 0).

---

## 9. Step 8 — clear the adaptives

The learned data is stored in **absolute µs** and was learned against the stock
injectors. It must be cleared, not edited.

* `LEA_inj_offset_learn_idle_bank1/2` and `_off_idle_bank1/2` — i16 µs adders. The real
  risk; these are added raw at 18784. Stale stock values could also sit beyond the new
  ±150 µs clamp from §7.
* `LEA_obd_ii_fuel_learn_zone_2/3_bank1/2`
* idle learns, alpha-N trims, octane scalers, misfire baselines

Long-term fuel trim is not stored separately — `ltft_bank1/2` is recomputed each cycle
from the above (27980-28059), so clearing them clears the trims.

`lea_reset3()` (19503) does all of it; the offsets are zeroed at 19530. Two ways to
invoke:

* **OBD mode `$11`** — `obd_ii_mode11_processing()` at 32258 calls reset3 + reset2 + reset1.
* **Poke `0x5352` into `diag_lea_reset_trigger`** over the dev-mode CAN window
  (`lea_diag_reset_command_handler`, 20830). It answers `0x4b4f`.

Note that editing map **axes** does not auto-clear anything relevant —
`lea_reset_learned_if_axes_changed()` (20710) only stamps the cat-monitor MAF axis and
the two load-estimation rpm axes.

---

## 10. Do NOT change these

| Cal | Why |
|---|---|
| `CAL_inj_afr_base` | AFR target, dimensionless |
| `CAL_inj_warmup_factor_ips/_manual` | multiplicative factor |
| `CAL_inj_cranking_enrichment_*` | 1/32 multiplicative factors |
| `CAL_inj_bank_balance` | ratio, clamped 170-230 (0.85-1.15) |
| `CAL_injtip_*` scales, `CAL_dfco_recovery_enrich_X_cut_duration` | unitless counts; the µs unit is §6 |
| `CAL_inj_angle` | start-of-injection angle, not a duration |
| `CAL_inj_stft_limit` | percentage of fuel portion |
| `CAL_obd_ii_mode2f_injector_test_duration` | test duration, not pulse width |
| EVAP purge fuel subtraction | mass domain (18631-18654) |

`CAL_inj_angle` deserves one caveat: `inj_set_trigger` (14435) schedules the **start**
angle and holds for the pulse duration, so a 3× shorter pulse now ends injection
considerably earlier in the cycle. That changes mixture prep even though the cal itself
needs no arithmetic change. Revisit it only if you see a driveability or emissions
symptom.

A full sweep of µs-typed cals finds nothing else injector-related:
`CAL_misc_engine_detection_on/off` (crank period) and `CAL_ign_dwell_time` are not fuel.

---

## 11. The real engineering problem: small pulses

At 3× the fuel-delivering portion of the idle pulse drops to roughly **300 µs**, and the
total idle pulse to roughly 0.9–1.0 ms — at the edge of the nonlinear region for the
ID1050-XDS. Light-load decel and DFCO resume go lower.

**There is no small-pulse correction table in this firmware.** Deadtime is a single
offset vs voltage and IAT. Nonlinearity is uncompensated for *all* fueling below ~1 ms,
not just transients. Your levers are:

1. **Deadtime fit** (§3.4) — the biggest lever. Fit to the range you run.
2. **`CAL_inj_efficiency`** (§11.1) — a rough short-pulse correction via load.
3. **The learned offsets** (§11.3) — absorb what is left at idle.

### 11.1 `CAL_inj_efficiency`

| | |
|---|---|
| Table | `0x40009e0a` (file `0x0FE6`), 32×32, `u8_factor_1/200` |
| X axis | `0x40009dca` (rpm) |
| Y axis | `0x40009dea` (load, mg/stroke) |
| Used at | 18594 |

A flow multiplier vs rpm and load — the right home for a low-load flow correction,
since load tracks pulse width. Note it is **not** a pure injector characteristic today:
it runs 210-255 (1.05-1.275×) and is richest at idle, so it is clearly absorbing MAF and
VE error. Treat it as a correction surface, not as injector data.

**Fix the axes first.** The load axis wastes 15 of its 32 breakpoints at 68 mg/stroke
and the rpm axis wastes 15 at 562 rpm. Idle sits on the bottom load breakpoint, so
everything below 68 mg/stroke collapses into a single cell — you cannot correct idle
and light cruise differently until you re-space it. There are 15 free breakpoints
sitting there.

### 11.2 `CAL_inj_comp_iat` — an empty slot worth knowing about

| | |
|---|---|
| Table | `0x4000a502` (file `0x16DE`), 8 load × 16 IAT, `u8_factor_1/128` |
| X axis | `0x4000a4ea` (load) · Y axis `0x4000a4f2` (IAT) |
| Used at | 18674 |

**All 128 entries are 128, i.e. 1.000.** A fully-wired multiplicative trim on load × IAT
with nothing in it. If hot-fuel behaviour needs compensating after the swap, this is
the correct home for it — multiplicative, in the mass-to-time chain — rather than
bending the deadtime table.

### 11.3 The learned offsets

`LEA_inj_offset_learn_idle/off_idle_bankN` adapt idle and off-idle in µs independently.
After §9 they start from zero and will re-learn the residual. If they sit near the new
±150 µs clamp (§7), the deadtime fit is off — fix §3.4 rather than widening the clamp.

---

## 12. Verification

### First start

1. Confirm the prime pulse scaled (§4) **before** first crank — this is the one that
   floods the engine.
2. Confirm the CRC was recomputed (§8). If the engine cranks but never fires, check
   this first.
3. Expect STFT to be active and working. Authority is ±30%
   (`CAL_inj_stft_limit` @ `0x40008f72` = 600, `i16_factor_1/20`), so if the flow
   constant is within ~30% the engine runs and trims its way out.
4. Watch for P0171/P0172/P0174/P0175. They can come from LTFT (flow constant off) or
   from the learned offsets hitting ±140 µs (deadtime off at idle).

### Deadtime check

Log LTFT against IAT at steady cruise via the dev-mode CAN channels. Flat trims as IAT
climbs from 25 °C to 60 °C means the deadtime surface is right. LTFT walking negative as
IAT rises means it is over-compensating — revisit §3.3.

### Load sweep

Log LTFT and the learned offsets at idle and at load. Trims that disagree between the
two ends point at deadtime (§3), not at the flow constant — the constant moves both
ends together.

### EVAP

Confirm purge actually commands at idle after §5. If it never enables, the gates are
still too high. If it commands everywhere including decel, they are below deadtime.

### Transients

Log lambda on throttle tip-in and on fuel resume after DFCO. Trim §6 or the
`CAL_injtip_*` scales from there.

### Not a concern

The 160 µs minimum pulse clamp (18795/18829) is hardcoded and unreachable — deadtime
alone is 600-780 µs, so total commanded pulse can never approach it. Likewise duty
cycle: the only clamp is `inj_pw_max_available_us` ~ full 720° cycle minus 250 µs
(~99%), and a larger injector moves away from it. At 3× the redline WOT duty drops to
roughly 22%.

---

## 13. Optional / cosmetic

### Trip computer

| | |
|---|---|
| Cal | `CAL_fuel_usage_to_flow_scaling` @ `0x4000d35e` (file `0x453A`) |
| Stock | 9867 |
| Unit | fuel density, 0.075 g/L per count (9867 → 740 g/L, i.e. gasoline) |

```
fuel_usage_instantaneous = rpm × (CAL_inj_flow_rate × avg_pulse_us / S) / 15000    [18896]
fuel_mileage_instantaneous = fuel_usage × 360 / kph                                [18911]
```

With 3 injections per revolution, `fuel_usage_instantaneous` comes out in 0.01 ml/s
(36 ml/h) and `fuel_mileage_instantaneous` in 0.01 L/100 km. The current
`u16_economy_1/10ml_per_km` type on `fuel_usage_instantaneous` is wrong.

The formula uses the **whole** commanded pulse, deadtime included. Deadtime goes from
~46% to ~70% of the idle pulse, so indicated consumption over-reads by roughly 1.4-1.8×
depending on load. In practice S is a density-plus-deadtime trim — raise it. One scalar
cannot correct both idle and load, so pick the operating point you care about.

### Mode $2F injector test

| | |
|---|---|
| Pulse | `0x4000d264` (file `0x4440`), u16 µs, stock 1000 (`03 E8`) |
| Duration | `CAL_obd_ii_mode2f_injector_test_duration` @ `0x4000d266` (file `0x4442`) — leave alone |
| Used at | 39219 (`× 10` → eTPU 0.1 µs ticks) |

The service-mode injector test fires a raw pulse with **no deadtime added**, so it is in
the "includes deadtime" class (§0), not the ÷ratio class. Dividing 1000 by 3.06 would
give 327 µs, below the ID's opening time, and the injector would barely move. Use the
EVAP transform:

```
600 + (1000 − 780) / 3.06 ≈ 672 µs   ->  02 A0
```

Recompute with the real ID offset at ~14 V. In the current export the symbol collides
with the `eTPU_init_single_shot_pulse` function name, so it is listed under that name.

---

## 14. Quick reference

| Step | Cal | Address | File | Stock | New |
|---|---|---|---|---|---|
| 1 | `CAL_inj_flow_rate` | `0x40009024` | `0x0200` | 4350 | 13311 (`33 FF`) |
| 2 | `CAL_inj_deadtime_base_X_voltage` | `0x4000b4a2` | `0x267E` | 4 wasted points | `55 72 8E 9C AB B9 C7 E3` |
| 2 | `CAL_inj_deadtime_base` | `0x4000b4b2` | `0x268E` | 8×8 ×20 µs | ID data, fit per §3.4 |
| 3 | `CAL_inj_startup_enrichment_offset` | `0x4000a6ea` | `0x18C6` | 255…41 | ÷ ratio (§4 table) |
| 4 | `CAL_evap_purge_min_inj_pulse_enter` | `0x40008ec9` | `0x00A5` | 188 (1504 µs) | ~105 (recompute) |
| 4 | `CAL_evap_purge_min_inj_pulse_exit` | `0x40008eca` | `0x00A6` | 162 (1296 µs) | ~96 (recompute) |
| 5 | `CAL_dfco_recovery_enrich_scale_us` | `0x40008f9e` | `0x017A` | 120 | 39 (`27`) |
| 6 | `CAL_inj_fuel_learn_lean_time_limit` | `0x40009010` | `0x01EC` | 46 | 15 (`0F`) |
| 6 | `CAL_inj_fuel_learn_rich_time_limit` | `0x40009011` | `0x01ED` | 46 | 15 (`0F`) |
| 6 | `CAL_obd_P0171_learn_time_threshold` | `0x4000d226` | `0x4402` | 45 | 14 (`0E`) |
| 6 | `CAL_obd_P0172_learn_time_threshold` | `0x4000d227` | `0x4403` | 45 | 14 (`0E`) |
| 7 | `CAL_ecu_cvn` (CRC) | `0x4000effc` | `0x61D8` | `F7CA` | recompute, last |
| 8 | LEA adaptives | — | — | — | mode `$11` |
| 11 | `CAL_inj_efficiency` (+ axes) | `0x40009e0a` | `0x0FE6` | 210-255 | tune after |
| 13 | `CAL_fuel_usage_to_flow_scaling` | `0x4000d35e` | `0x453A` | 9867 | raise |
| 13 | Mode `$2F` test pulse | `0x4000d264` | `0x4440` | 1000 µs | ~672 (`02 A0`) |

**Minimum viable change list:** steps 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 (CRC) -> 8
(clear). Everything else is refinement.

---

## 15. Caveats

* The ID1050-XDS figures (1065 cc/min at 3 bar, high impedance) are from the
  manufacturer's published spec, not from this firmware. Verify against the
  documentation for your actual part.
* Idle and WOT pulse-width figures throughout are estimates derived from the load
  model, not logged data. They are used to show direction and rough magnitude.
* The 600 µs new deadtime used in the worked examples is a placeholder. Every value
  computed with the "includes deadtime" transform (EVAP gates, Mode `$2F`) must be
  recomputed with the real ID offset at your idle voltage.
* The stock injector's true flow rating should be confirmed independently rather than
  inferred from `CAL_inj_flow_rate` (see §1.2).
* `CAL_inj_fuel_learn_time_step` has a duplicate label at `0x40008ee1`/`0x40008ee2`
  (§7); resolve before editing.
* Keep the injectors high-impedance / saturated. Per-cylinder circuit diagnostics exist
  for all six cylinders — P0261/P0262, P0264/P0265, P0267/P0268, P0270/P0271,
  P0273/P0274, P0276/P0277, enabled at `0x4000d9ab`-`0x4000d9b6`.
