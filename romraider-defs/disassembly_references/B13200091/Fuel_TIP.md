# Transient Throttle Fueling — B13200091 (Lotus Evora NA 2011)

## Two Separate Mechanisms

There are two distinct transient mechanisms that work together:

1. **Alpha-N load selection** — switches the *load signal source* from MAF to TPS during transients
2. **Injtip enrichment/enleanment** — adds or removes fuel based on filtered TPS rate

They're complementary: Alpha-N gives the *right load target* when the MAF is lying (air column inertia), and injtip compensates for *fuel film* wetting the intake ports.

---

## 1. MAF → Alpha-N Switching

Every 200 Hz cycle, the ECU checks whether to use MAF-computed load or TPS-computed (Alpha-N) load:

```c
// Trigger if throttle rate exceeds either opening or closing threshold:
if (tps_rate_current > CAL_load_alphaN_tps_rate_opening_threshold ||
    tps_rate_current < -CAL_load_alphaN_tps_rate_closing_threshold ||
    tps_2 > load_selection_tps_threshold) {
    transient_load_timer = CAL_load_alphaN_hold_time;   // countdown in 5ms steps
}

if (transient_load_timer != 0 && engine_speed < CAL_load_alphaN_max_rpm) {
    load_selected_raw = load_computed_alphaN + load_comp_idle;   // TPS-based
} else {
    load_selected_raw = load_computed_maf + load_comp_idle;      // MAF-based
}
```

**Key calibrations:**

| Name | Type | Effect |
|------|------|--------|
| `CAL_load_alphaN_tps_rate_opening_threshold` | `u16_factor_1/255` | TPS opening rate to trigger Alpha-N |
| `CAL_load_alphaN_tps_rate_closing_threshold` | `u16_factor_1/255` | TPS closing rate to trigger Alpha-N |
| `CAL_load_alphaN_hold_time` | `u8_time_5ms` | How long to stay in Alpha-N after trigger |
| `CAL_load_alphaN_max_rpm` | `u16_rspeed_rpm` | Alpha-N only allowed below this RPM |

---

## 2. X-Tau Fuel Film Compensation

After the load source is selected, a 1st-order lag filter models fuel film dynamics on the port walls:

```c
// Classic exponential moving average — the "tau" in X-tau
_load_filtered_xtau1 = (0x100 - CAL_inj_fuel_fillm_xtau_coeff) * load_filtered1;
load_filtered1 = (_load_filtered_xtau1 >> 8) + CAL_inj_fuel_fillm_xtau_coeff * load_selected_raw;
```

This is `load_filtered1 = (1 - α) × load_filtered1 + α × load_selected_raw` where α = `CAL_inj_fuel_fillm_xtau_coeff / 256`.

Higher coefficient = faster response (less film lag compensation). Lower = more sluggish (simulates heavy wetting).

---

## 3. Injtip Enrichment/Enleanment

The `injtip()` function computes a pulse-width adjustment based on filtered throttle rate.

**Throttle rate filtering** uses a circular buffer of 16 TPS samples, with asymmetric attack/decay:
- **Attack:** Immediate — if raw rate exceeds threshold, filtered value jumps directly
- **Decay:** Slow — counts cycles using `injtip_decay_cycle_counter` before stepping toward zero
- Independent rates for opening vs. closing

**Enrichment calculation (opening):**
```
enrichment = CAL_injtip_time_base × gear_adj × rpm_scale × coolant_scale × tps_rate_filtered
```

**Enleanment calculation (closing):**
```
enleanment = CAL_injtip_time_base × rpm_scale × coolant_scale × (-tps_rate_filtered)
```

The `CAL_injtip_in_adj_gears[]` gear-dependent scaling means lower gears get more enrichment,
consistent with the higher driveshaft accelerations typical in 1st/2nd gear tip-ins.

---

## Variable Naming Suggestions

| Current Name | Better Name | Reason |
|---|---|---|
| `load_filtered1` | `fuel_film_load_state` | This is the X-tau integrator state, not just "filtered load" |
| `load_selected_raw` | `load_before_xtau` | Clarifies it feeds the X-tau filter |
| `tps_delta_rate` | `tps_rate_raw` | This is unfiltered; distinguishes from the filtered version |
| `tps_rate_filtered_for_ign_comp` | `tps_rate_transient` | Used for both ignition comp AND injtip — the `_for_ign_comp` is misleading |
| `injtip_decay_cycle_counter` | `tps_rate_decay_divider` | It's a cycle divider that slows the decay rate, not a counter |
| `injtip_in_enrichment_raw` | `accel_enrichment_pw_raw` | Makes clear it's a pulse-width delta |
| `injtip_out_enleanment_raw` | `decel_enleanment_pw_raw` | Units are microseconds of injection |
| `inj_tip_adj_enrichment` | `transient_enrichment_pw` | Post-gating (engine running check) value |
| `inj_tip_adj_enleanment` | `transient_enleanment_pw` | Same |
| `DAT_40008fa0` | `injtip_in_decay_divider` | Cycle count for opening decay speed |
| `DAT_40008fa1` | `injtip_out_decay_divider` | Cycle count for closing decay speed |
| `DAT_40008fa6` | `tps_rate_open_clamp` | Upper clamp on `tps_rate_transient` during opening |
| `DAT_40008fa8` | `tps_rate_close_deadband` | Closing rate below which is ignored |

---

## Complete 200 Hz Execution Flow

```
1. Sample TPS into 16-entry circular buffer
2. tps_rate_raw = TPS[now] - TPS[n samples ago]  (n = CAL_tps_delta_rate_window_size)
3. Apply asymmetric filter → tps_rate_transient
4. Check if tps_rate_transient or TPS level triggers Alpha-N; reload hold timer
5. Select load: Alpha-N (TPS) or MAF based on hold timer
6. Apply X-tau filter: fuel_film_load_state ← blend of old + new load
7. injtip(): compute accel enrichment or decel enleanment from tps_rate_transient × RPM × temp × gear
8. Final PW = base_fuel_pw + accel_enrichment_pw - decel_enleanment_pw
```
