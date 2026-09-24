# Injector Rescaling Guide — B13200091 (2011 Lotus Evora NA)

How to move this calibration from the stock injectors to a different set, using the
Injector Dynamics ID1050-XDS as the worked example.

All line numbers refer to `B13200091.c`. All addresses are absolute in the ROM image
(file offset == address). Cal base is `0x40008E24`.

---

## 0. The governing principle

The fuel model computes a **fuel mass** first, then converts it to time using a flow
constant:

```
fuel_mass_required (10µg) = load_mass_per_stroke_raw × 10000 / afr_target      [18630]
inj_flow_rate      (mg/s) = CAL_inj_flow_rate × inj_efficiency / 200           [18609]
pw_fuel            (µs)   = fuel_mass × 10000 / (inj_flow_rate × bank_split)   [18642]
pw_commanded       (µs)   = inj_deadtime_base + LEA_offset
                            + pw_fuel × (1 + ltft + stft/2)                    [18789]
```

Everything upstream of `pw_fuel` is in the **mass domain** and is injector-agnostic —
AFR targets, warmup factors, cranking enrichments, purge fuel subtraction. None of it
changes.

Only two classes of thing care about the swap:

| Class | Behaviour on swap | Examples |
|---|---|---|
| **The flow constant** | Scales by the flow ratio | `CAL_inj_flow_rate` |
| **Absolute µs terms** | Divide by the flow ratio | prime pulse, transient adders, EVAP gates |
| **Injector properties** | Replace outright, do *not* scale | deadtime |
| **Ratios / masses** | Leave alone | AFR map, enrichment factors, bank balance |

Getting these four categories right is the whole job.

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
| Address | `0x40009024` |
| Type | `u16_flow_mg/s` |
| Stock | **4350** |
| Used at | 18609 (fuel model), 18896 (trip computer) |

This is per-injector. Confirmed from the bank-split math at 18642: a neutral
`inj_bank_balance_ratio` of 200 gives each bank a ×1.0 divisor against per-cylinder
fuel mass.

```
new = 4350 × 3.06 = 13311
```

Range is fine — u16 caps at 65535, and the derived `inj_flow_rate` peaks near 17000
with the efficiency map at its maximum of 255.

---

## 3. Step 2 — deadtime

| | |
|---|---|
| Table | `CAL_inj_deadtime_base` @ `0x4000b4b2`, 8×8, `u8_time_20us` |
| X axis | `CAL_inj_deadtime_base_X_voltage` @ `0x4000b4a2`, `u8_voltage_72/1023v` |
| Y axis | `CAL_inj_deadtime_base_Y_iat` @ `0x4000b4aa`, `u8_temp_5/8-40c` |
| Applied at | 18538 (`× 20` → µs), added at 18789 |

**Deadtime does not scale with injector size.** It is an electromechanical property of
the injector. Replace the surface with the new injector's data; do not multiply or
divide it by the flow ratio.

This matters more here than in most ECUs because deadtime is added *after* the fuel
trims (18789). STFT and LTFT scale only `pw_fuel`, so they cannot absorb a deadtime
error — it shows up instead as trims that disagree between idle and load.

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

### 3.2 Fix the voltage axis first

Four of the eight breakpoints are a degenerate clamp at 6.48 V, so the table has only
five usable voltage points. Re-space it to use ID's curve properly:

```
volts    6    8   10   11   12   13   14   16
raw     85  114  142  156  171  185  199  227          (raw = V × 1023/72)
```

### 3.3 Fill the temperature dimension

ID publishes offset vs voltage only, with no temperature axis. Two defensible choices:

* **Flat** — write the ID curve identically into all eight IAT rows. Safe default.
* **Keep a reduced stock trend** — the stock temperature climb (+760 µs from 0 °C to
  119 °C at 14 V) models injector coil heating with IAT as the proxy. If you believe it
  roughly transfers, scale it down and add it on top of the ID curve.

If you go flat and later find LTFT walking with IAT, that is the signal that the
temperature dimension was doing real work. See §9.2.

### 3.4 Naming note

`_base` is misleading — there is no second deadtime term anywhere in the firmware.
`CAL_inj_pulse_offset` would be the honest name.

---

## 4. Step 3 — the cranking prime pulse

| | |
|---|---|
| Table | `CAL_inj_startup_enrichment_offset` @ `0x4000a6ea`, 16 × `u8_time_256us` |
| X axis | `..._X_coolant_temp_engine_stopped` @ `0x4000a6da` (−30 °C … 118.8 °C) |
| Used at | 18553 (`offset×256 + deadtime`), fired at 14879 |

This is a raw time, not a mass. At first crank sync the ECU fires **all six injectors
simultaneously** (staggered 1° apart) for `inj_startup_pulse_time`. Stock is 28.7 ms
per injector at 20 °C and clips at 65.5 ms below −20 °C.

Left alone with a 3× injector that is a flooded cold start. Divide by the ratio:

```
coolant °C   -30  -20  -10    0   10   20   30   40   50   60   70   80   90  100  110  119
stock raw    255  255  234  191  150  112   87   67   51   42   42   41   41   41   41   41
÷ 3.06        83   83   76   62   49   37   28   22   17   14   14   13   13   13   13   13
```

Bonus: the cold end no longer saturates at 255, so sub-zero starts regain resolution
they did not have stock.

---

## 5. Step 4 — the EVAP purge gates

**This is the step that is easy to miss and will fail an emissions readiness check.**

| Cal | Address | Type | Stock | ×8 |
|---|---|---|---|---|
| `CAL_evap_purge_min_inj_pulse_enter` | `0x40008ec9` | `u8_time_8us` | 188 | **1504 µs** |
| `CAL_evap_purge_min_inj_pulse_exit` | `0x40008eca` | `u8_time_8us` | 162 | **1296 µs** |

Used at 38883/38885 (exit) and 38891/38893/38924 (enter). They form a hysteresis pair
gating purge permission on **absolute commanded pulse width**.

### Why it breaks

Stock idle pulse is roughly 1.7 ms — comfortably above the 1504 µs enter threshold, so
purge runs at idle. At 3× the idle pulse drops to roughly 1.0 ms, **below the 1296 µs
exit threshold**. Purge never enables at idle or light load. The canister saturates,
P0441 sets, the leak test never collects its prerequisites, and EVAP readiness never
completes.

(Those pulse figures are estimates from the load model, not logged data — but the
direction and rough magnitude are not in doubt.)

### The rescale

Preserve the *fuel mass* trigger point rather than the raw time:

```
new_us = new_deadtime + (old_us − old_deadtime) / ratio
```

Worked at 780 µs stock deadtime, 600 µs new deadtime, ratio 3.06:

```
enter:  600 + (1504 − 780)/3.06 = 837 µs  ->  raw 105
exit:   600 + (1296 − 780)/3.06 = 769 µs  ->  raw  96
```

This is the correct transform rather than a guess. Line 38924 computes the purge fuel
headroom as `inj_flow_rate × (enter_threshold − inj_deadtime_base) / 10000`. Flow
triples while the bracket thirds, so the resulting mass limit is invariant — the code
stays self-consistent.

---

## 6. Step 5 — the transient µs scaler

| | |
|---|---|
| Cal | `CAL_dfco_recovery_enrich_scale_us` (read the address from Ghidra) |
| Used at | 23236 (tip-out enleanment), 23247 (tip-in enrichment), 23388 (DFCO recovery) |

One cal, three consumers. All three produce absolute µs adders that land directly on
`inj_pw_bankN_pre_trim_us` at 18758. Divide by the ratio.

---

## 7. Step 6 — clear the adaptives

The learned data is stored in **absolute µs** and was learned against the stock
injectors. It must be cleared, not edited.

* `LEA_inj_offset_learn_idle_bank1/2` and `_off_idle_bank1/2` — i16 µs adders. The real
  risk; these are added raw at 18789.
* `LEA_obd_ii_fuel_learn_zone_2/3_bank1/2`
* idle learns, alpha-N trims, octane scalers, misfire baselines

Long-term fuel trim is not stored separately — `ltft_bank1/2` is recomputed each cycle
from the above (27980-28059), so clearing them clears the trims.

`lea_reset3()` (19503) does all of it. Two ways to invoke:

* **OBD mode `$11`** — `obd_ii_mode11_processing()` at 32258 calls reset3 + reset2 + reset1.
* **Poke `0x5352` into `diag_lea_reset_trigger`** over the dev-mode CAN window
  (`lea_diag_reset_command_handler`, 20830). It answers `0x4b4f`.

Note that editing map **axes** does not auto-clear anything relevant —
`lea_reset_learned_if_axes_changed()` (20710) only stamps the cat-monitor MAF axis and
the two load-estimation rpm axes.

---

## 8. Do NOT change these

| Cal | Why |
|---|---|
| `CAL_inj_afr_base` | AFR target, dimensionless |
| `CAL_inj_warmup_factor_ips/_manual` | multiplicative factor |
| `CAL_inj_cranking_enrichment_*` | 1/32 multiplicative factors |
| `CAL_inj_bank_balance` | ratio, clamped 170-230 (0.85-1.15) |
| `CAL_inj_angle` | start-of-injection angle, not a duration |
| EVAP purge fuel subtraction | mass domain (18631-18654) |

`CAL_inj_angle` deserves one caveat: `inj_set_trigger` (14435) schedules the **start**
angle and holds for the pulse duration, so a 3× shorter pulse now ends injection
considerably earlier in the cycle. That changes mixture prep even though the cal itself
needs no arithmetic change. Revisit it only if you see a driveability or emissions
symptom.

---

## 9. The real engineering problem: small pulses

At 3× the fuel-delivering portion of the idle pulse drops to roughly **300 µs**, which
is into the nonlinear region for an injector that size.

**There is no small-pulse correction table in this firmware.** No offset-vs-pulsewidth
curve exists. Your levers are:

### 9.1 `CAL_inj_efficiency`

| | |
|---|---|
| Table | `0x40009e0a`, 32×32, `u8_factor_1/200` |
| X axis | `0x40009dca` (rpm) |
| Y axis | `0x40009dea` (load, mg/stroke) |
| Used at | 18594 |

A flow multiplier vs rpm and load — the right home for a low-load flow correction.
Note it is **not** a pure injector characteristic today: it runs 210-255 (1.05-1.275×)
and is richest at idle, so it is clearly absorbing MAF and VE error. Treat it as a
correction surface, not as injector data.

**Fix the axes first.** The load axis wastes 15 of its 32 breakpoints at 68 mg/stroke
and the rpm axis wastes 15 at 562 rpm. Idle sits on the bottom load breakpoint, so
everything below 68 mg/stroke collapses into a single cell — you cannot correct idle
and light cruise differently until you re-space it. There are 15 free breakpoints
sitting there.

### 9.2 `CAL_inj_comp_iat` — an empty slot worth knowing about

| | |
|---|---|
| Table | `0x4000a502`, 8 load × 16 IAT, `u8_factor_1/128` |
| X axis | `0x4000a4ea` (load) · Y axis `0x4000a4f2` (IAT) |
| Used at | 18674 |

**All 128 entries are 128, i.e. 1.000.** A fully-wired multiplicative trim on load × IAT
with nothing in it. If hot-fuel behaviour needs compensating after the swap, this is
the correct home for it — multiplicative, in the mass-to-time chain — rather than
bending the deadtime table.

### 9.3 The learned offsets

`LEA_inj_offset_learn_idle/off_idle_bankN` adapt idle and off-idle in µs independently.
After §7 they start from zero and will re-learn the residual.

---

## 10. Verification

### First start

1. Confirm the prime pulse scaled (§4) **before** first crank — this is the one that
   floods the engine.
2. Expect STFT to be active and working. Authority is ±30%
   (`CAL_inj_stft_limit` @ `0x40008f72` = 600, `i16_factor_1/20`), so if the flow
   constant is within ~30% the engine runs and trims its way out.
3. Watch for P0171/P0172/P0174/P0175. Those indicate the flow constant is off, not that
   something is broken.

### Deadtime check

Log LTFT against IAT at steady cruise via the dev-mode CAN channels. Flat trims as IAT
climbs from 25 °C to 60 °C means the deadtime surface is right. LTFT walking negative as
IAT rises means it is over-compensating — revisit §3.3.

### Load sweep

Log LTFT at idle and at load. Trims that disagree between the two ends point at
deadtime (§3), not at the flow constant — the constant moves both ends together.

### EVAP

Confirm purge actually commands at idle after §5. If it never enables, the gates are
still too high.

### Not a concern

The 160 µs minimum pulse clamp (18795/18829) is unreachable — deadtime alone is
600-780 µs, so total commanded pulse can never approach it. Likewise duty cycle: the
only clamp is `inj_pw_max_available_us` ~ full 720° cycle minus 250 µs (~99%), and a
larger injector moves away from it. At 3× the redline WOT duty drops to roughly 22%.

---

## 11. Optional / cosmetic

### Trip computer

`fuel_usage_instantaneous` (18896) multiplies `CAL_inj_flow_rate` by the **whole**
commanded pulse, deadtime included. Deadtime goes from ~46% to ~70% of the idle pulse,
so indicated economy over-reads by roughly 1.4-1.8× depending on load.

`CAL_fuel_usage_to_flow_scaling` @ `0x4000d35e` = 9867 is the trim — raise it. One
scalar cannot correct both idle and load, so pick the operating point you care about.

### Mode $2F injector test

The service-mode injector test pulse width (passed at 39219) is an absolute time and
should be divided by the ratio. In the current export its symbol collides with the
`eTPU_init_single_shot_pulse` function name, so resolve it by address in Ghidra.

---

## 12. Quick reference

| Step | Cal | Address | Stock | Action |
|---|---|---|---|---|
| 1 | `CAL_inj_flow_rate` | `0x40009024` | 4350 | × ratio -> 13311 |
| 2 | `CAL_inj_deadtime_base` | `0x4000b4b2` | 8×8 ×20 µs | replace with ID data |
| 2 | `CAL_inj_deadtime_base_X_voltage` | `0x4000b4a2` | 4 wasted points | re-space |
| 3 | `CAL_inj_startup_enrichment_offset` | `0x4000a6ea` | 255…41 | ÷ ratio |
| 4 | `CAL_evap_purge_min_inj_pulse_enter` | `0x40008ec9` | 188 (1504 µs) | -> 105 |
| 4 | `CAL_evap_purge_min_inj_pulse_exit` | `0x40008eca` | 162 (1296 µs) | -> 96 |
| 5 | `CAL_dfco_recovery_enrich_scale_us` | (from Ghidra) | — | ÷ ratio |
| 6 | LEA adaptives | — | — | mode `$11` |
| 9 | `CAL_inj_efficiency` (+ axes) | `0x40009e0a` | 210-255 | tune after |
| 11 | `CAL_fuel_usage_to_flow_scaling` | `0x4000d35e` | 9867 | raise |

**Minimum viable change list:** steps 1 -> 2 -> 3 -> 4 -> 5 -> 6. Everything else is
refinement.

---

## 13. Caveats

* The ID1050-XDS figures (1065 cc/min at 3 bar, high impedance) are from the
  manufacturer's published spec, not from this firmware. Verify against the
  documentation for your actual part.
* Idle and WOT pulse-width figures throughout are estimates derived from the load
  model, not logged data. They are used to show direction and rough magnitude.
* The stock injector's true flow rating should be confirmed independently rather than
  inferred from `CAL_inj_flow_rate` (see §1.2).
* Keep the injectors high-impedance / saturated. Per-cylinder circuit diagnostics exist
  for all six cylinders — P0261/P0262, P0264/P0265, P0267/P0268, P0270/P0271,
  P0273/P0274, P0276/P0277, enabled at `0x4000d9ab`-`0x4000d9b6`.
* `CAL_dfco_recovery_enrich_scale_us` has no address recorded here because it was
  renamed after the last symbol export; read it from Ghidra.
