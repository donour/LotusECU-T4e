# Porting C132E0278 (GT430) onto B13200091 (MY11 NA Evora) hardware

Scope: hardware I/O and sensor inputs only. Control strategy, torque model,
emissions monitors and DPM are out of scope except where they consume a
sensor that the NA harness does not populate.

Method: pad configuration (`siu_pcr[]`), GPIO (`siu_gpdo[]`), SPI relay-driver
bits, eMIOS/eTPU channel and ADC channel maps were extracted from both C
exports and attributed to their enclosing functions, then each differing
output was traced to its control function and its coding/calibration gate.

## Executive conclusion

The two ECUs are the same MPC5534 platform with the same pinout, the same
DSPI relay driver, the same throttle and HC08 monitor, and the same VVT,
evap, knock, A/C and fuel-level hardware. **The core engine-control I/O ports
unchanged.**

The blocking problem is not that the GT430 has extra devices. It is that
Lotus **reassigned six existing pads and two relay-driver bits** between the
two model years, and the GT430 firmware carries no fallback path for any of
the older arrangements. Three of the reassignments are safety-relevant.

`C132E0278` cannot be made to run correctly on `B13200091` hardware by
calibration and coding alone. Of the four subsystems asked about, two are
code patches, one is a clean coding-bit change, and one is a code patch that
is easy but non-obvious because the PWM output is inverted.

## Pad and relay reassignment map

Pads where the two firmwares disagree. `0xecc` = alternate function (eMIOS),
`0x284`/`0x2cc` = GPIO.

| Pad | B13200091 (NA) | C132E0278 (GT430) | Consequence on NA hardware |
|---|---|---|---|
| `0xcf` | **ECU main relay** (`shutdown`, with `CAL_ecu_ign_off_relay_hold_time`) | RACE-mode lamp, blinked during mode change | **Blocker.** Main relay follows drive mode |
| `0xb5` | SPORT lamp (GPIO) | **Fuel pump PWM** (eMIOS ch 2) | **Blocker.** Pump feed never energised |
| `0xb6` | Engine-bay fan (GPIO) | **Radiator fan PWM** (eMIOS ch 3) | **Blocker.** Rad fan relay unused |
| `0xc9` | ACIS variable-intake solenoid (GPIO) | Chargecooler pump PWM (eMIOS ch 22) | ACIS solenoid gets ~10 kHz PWM |
| `0x8f` | Airbox flapper valve (GPIO) | Exhaust flap output 3 | Flapper follows exhaust flap logic |
| `0xb4` | TC/ESP button lamp (GPIO) | Exhaust flap output 2 | Lamp follows exhaust flap logic |
| `0x7c` | Accessory output (seat heaters?) | Transmission fluid pump | Accessory follows trans pump logic |
| `0x7d` | Accessory output (seat heaters?) | Transmission cooler pump | Accessory follows trans pump logic |

SPI relay-driver byte (`obd_ii_relay_status`, DSPI_B). The driver chip and the
`relay_driver_write` transaction are identical in both images.

| Bit | B13200091 (NA) | C132E0278 (GT430) | Consequence |
|---|---|---|---|
| `0x10` | Starter/enable interlock | Starter/enable interlock | compatible |
| `0x20` | A/C clutch | A/C clutch | compatible |
| `0x40` | **Radiator fan LOW** | Engine-bay fan | Rad fan low follows bay-fan logic |
| `0x80` | **Radiator fan HIGH** | SPORT lamp | **Rad fan high follows SPORT button** |

Unchanged and portable: `0xb7` coolant recirculation pump, `0xcb` ECU power
hold, `0xb9`/`0xbb`/`0xcc` plus eMIOS ch 6 electronic throttle,
`0xce`/`0x16`/`0xd1`/`0xd6` HC08 throttle monitor, `0xd3`/`0xd4` knock AGC
gain select, `0x8c` plus eTPU ch 26 exhaust flap, `0x8d` plus eTPU ch 27 evap
purge, eTPU ch 16 A/C compressor PWM, VVT (eTPU ch 15 and 28 plus eMIOS ch 17
and 18 — four solenoids, byte-identical init), the eMIOS input-capture
fuel-level sensor, and the DSPI_C status device (identical transaction;
named `spi_read_cac_pump_driver_status` in 0278 but present unnamed in 0091,
so that name is probably wrong).

## ADC channel differences

| Ch | B13200091 | C132E0278 | Note |
|---|---|---|---|
| `0x0b` | not sampled | Transmission fluid temp | gated by `COD[1]` bit 19 |
| `0x0f` | `sensor_adc_airtemp_not_wired` | Chargecooler / intake air temp | **not populated on NA** |
| `0x1a` | Oil pressure **switch** | Oil pressure switch *or* analog | `CAL_oil_pressure_warning_light_mode` |
| `0x1b` | MAP (estimated; pin reads baro) | Real TMAP | `CAL_tmap_use_for_inj` / `_for_load` |
| `0x1e` | `sensor_adc_unused_ch1e` | **Fuel rail pressure** | **not populated on NA** |
| `4`-`7` | `sensor_adc_unused_ch4..7` | O2 heater current sense | **not populated on NA** |

Everything else is identical: `0x0d` coolant, `0x0e` engine air, `0x10` cruise
switch, `0x11` fuel level, `0x13` evap pressure, `0x14`/`0x15` supply
voltages, `0x16`-`0x19` O2, `0x1c` clutch, `0x1d` paddle, `0x1f` A/C evap,
`0x22`/`0x23`/`0x34`/`0x35` knock, `0x27` baro, `0x30`/`0x31` TPS, `0x32`
MAF, `0x00`/`0x01` pedal.

## The four questions

### 1. Does 0278 support a relay-type (non-PWM) fuel pump? No

There is a coding bit for it: `fuel_pump_is_pwm` = `COD[1]` bit 18, decoded in
`cod_decode_flags_and_validate` and re-encoded in `init_cod_base`. **It is
never read by any control path.** Those three sites are its only references in
the entire image.

`fuel_pump()` unconditionally runs the closed-loop PI — feed-forward
`CAL_fuel_pump_command` scaled by supply voltage, plus a proportional term on
rail-pressure error — converts through `fuel_pump_dc_to_pwm_scale`, and writes
eMIOS ch 2 via `fuel_pump_set_output`. There is no relay branch anywhere.

Two independent faults on NA hardware:

- the PWM lands on pad `0xb5`, which is the SPORT lamp on the NA harness;
- the NA fuel pump is fed from the ECU main relay on pad `0xcf`, and 0278
  never drives `0xcf` as a relay at all.

This is a code patch, not a calibration change.

### 2. Can the chargecooler pump be disabled? Only by patching

`cooling_chargecooler_pump_100ms()` is called unconditionally from
`interrupt_timer_2000hz` and **has no coding gate**. It also self-initialises
the pad on first entry — `init_eMIOS(0x16, 10000)` then `siu_pcr[0xc9] =
0xecc` — so it takes `0xc9` away from GPIO regardless of what `init_siu` did.

The output is inverted:

```c
pwm_set_dutycycle((int)((0xff - (uint)cac_pwm_output) * 10000) / 0xff, 22);
```

so zeroing `CAL_cac_pump_dutycycle` / `CAL_cac_pump_dc_drive_output` drives the
pad to **100 %**, not off. Calibrating it away is actively wrong.

Cleanest fix: NOP the call in `interrupt_timer_2000hz`. That also leaves
`0xc9` as GPIO, though 0278 contains no ACIS code to use it (see §5).

### 3. Can the transmission cooler pump be disabled? Yes, by coding

This is the one clean case. Two separate outputs, each with a real gate:

- **Trans fluid pump**, pad `0x7c`, driven by `trans_fluid_pump_enable()` /
  `_disable()` from `trans_cooler_control()`.
  `cluster_and_exhaust_flaps_100ms` calls it only when `COD[1]` bit 19
  (`trans_fluid_pump`) is set.
- **Trans cooler pump**, pad `0x7d`, in `cooling_pump_control()`. Gated by
  `COD[1]` bit 20 (`recirc_valve_installed`); when clear, the pad is forced
  low on every pass.

Clearing bit 19 also stops ADC ch `0x0b` being sampled (`trans_temp_voltage`
is forced to 0) and suppresses the P2797/P0897/P0712/P0713 monitors.

Coding-validation caveat: `cod_decode_flags_and_validate` requires bit 19 set
only when `cod_trans_type == 0` (IPS). For a manual car bit 19 is free.
Clearing bit 20 also disables the supercharger recirculation valve, which is
correct on an NA car anyway.

### 4. Is relay (non-PWM) radiator fan logic supported? No

`cooling_fan_radiator_control()` is PWM-only and ungated, called from
`cooling_control()`. Like the CAC pump it self-initialises its pad
(`init_eMIOS(3, 100000)`, `siu_pcr[0xb6] = 0xecc`) and its output is inverted.
There is no two-stage relay path in the image.

0278 does still drive one fan relay — bit `0x40` — but that is the
**engine-bay** fan (`cooling_fan_engine_bay_control`, gated by `COD[1]` bit 26,
`aux_cooling_fan_installed`). On the NA harness bit `0x40` is radiator-fan-low.

Net result unpatched: rad-fan-low relay driven by engine-bay-fan logic,
rad-fan-high relay driven by the SPORT button, engine-bay fan relay fed a
100 kHz PWM. Code patch required.

### 5. Other hardware that will cause trouble

**ECU main relay, the single worst item.** `B13200091:shutdown()` drives
`siu_gpdo[0xcf]` as the main relay with a calibrated ign-off hold
(`CAL_ecu_ign_off_relay_hold_time`, `ign_off_main_relay_hold_timer`) and an OBD
mode-2F actuator test at request `0x141` labelled "fuel pump". 0278 has no
main-relay concept at all — no hold timer, no `main_relay_state` — and uses
`0xcf` as the RACE lamp, including a deliberate ~5 Hz blink alternating with
relay bit `0x80` during mode transitions. Unpatched, the NA main relay would
toggle with drive-mode state.

**Fuel rail pressure sensor (ADC `0x1e`), not fitted on NA.** Consequences, in
order of severity:

- `injection()` computes `fuel_pressure_abs2 - map` and uses it for both
  `CAL_inj_deadtime_base` (Y axis) and `CAL_inj_flow_rate` (X axis). Fuelling
  depends on it directly.
- The sensor-fault fallback is graceful and, helpfully, *correct* for a
  fixed-gauge-pressure returnless system: when
  `engine_state_failure_flags & 0x4000000` is set, `adc_convert` substitutes
  `fuel_pressure_abs2 = CAL target x 50 + baro`, so rail-minus-manifold still
  tracks MAP properly. Setting `CAL_fuel_pressure_target*` to the NA regulator
  pressure makes the injector maths right.
- But that same fault bit is one of the interlocks in `o2_fuel_learn_100ms`, so
  **long-term fuel trim learning is permanently blocked** while it is set. That
  is the real cost, and it needs either a code patch or a real sensor.
- P0087/P0088/P0191/P0192/P0193 will set. All are individually disable-able via
  their `CAL_obd_ii_Pxxxx & 7` gate.

**Chargecooler / intake air temp (ADC `0x0f`), not fitted on NA.** Feeds
`chargecooler_temp_div_160`, `obd_ii_manifold_temp` (the CAC pump axis) and
`temp_engine_air_cooling_control` (radiator and bay fan axes). Open circuit
sets a DTC and takes the fallback path.

**O2 heater current sense (ADC `4`-`7`), not fitted on NA.** 0278 runs
heater-current diagnostics (P0030 family, plus
P0080/P0082/P0083/P0085/P0086) that the NA harness cannot satisfy.
Calibration-disable-able.

**ACIS and airbox flapper are lost.** `B13200091:intake_path_control()` drives
the 2GR-FE variable intake runner (`0xc9`, `CAL_acis_open_rpm`/`_load`) and the
airbox flapper (`0x8f`, four rpm-threshold pairs for tour/sport). 0278 has no
variable-intake code at all, and both pads are reused. On an NA 2GR-FE this is
a real midrange torque loss, and it is the one item on this list that needs new
code rather than a patch.

**TPMS is lost.** 121 `tpms` references in 0091 — handshake and relearn state
machines are ECU-resident — versus 3 in 0278 (coding bit only).

**Coding validation.** `cod_decode_flags_and_validate` requires
`traction_control_level == 3`, `abs_present`, `sas_present`,
`yaw_sensor_present`, `instrument_cluster_is_2011plus`,
`sport_button_installed`, `race_button_installed` and
`silencer_bypass_valve_installed`; and forbids `tcp_esp_button_installed`,
`launch_mode_present` and `dpm_switch_installed`. Failure only sets
`main_diagnostic_flags |= 8`, giving P0610; `coding_validated` itself is
written but never read, so this is not a no-start. The individual features
still fault if the hardware is absent.

**Favourable findings.** `CAL_tmap_use_for_inj` and `CAL_tmap_use_for_load` are
boolean calibrations that select MAF-based rather than TMAP-based paths, which
matches NA hardware. `CAL_oil_pressure_warning_light_mode` selects switch
versus analog. Every OBD monitor is individually gated by
`CAL_obd_ii_Pxxxx & 7`.

## Work required

Coding only:

1. Clear `COD[1]` bit 19 — trans fluid pump, its temp sensor and its DTCs.
2. Clear `COD[1]` bit 20 — trans cooler pump and SC recirc valve.
3. Set `COD[1]` bit 26 as appropriate for the bay fan.

Calibration only:

4. `CAL_tmap_use_for_inj` and `CAL_tmap_use_for_load` false.
5. `CAL_oil_pressure_warning_light_mode` = SWITCH.
6. `CAL_fuel_pressure_target*` to the NA regulator pressure, so the
   sensor-fault fallback produces correct injector maths.
7. Disable P0087/P0088/P0191/P0192/P0193, the O2 heater-current family, and the
   intake-air-temp codes.

Code patches, in dependency order:

8. Restore `0xcf` to main-relay duty and move the RACE lamp elsewhere, or drop
   it. Nothing else can be tested safely until this is done.
9. Rewrite `fuel_pump()` output to energise the main relay instead of eMIOS
   ch 2, and release pad `0xb5` back to the SPORT lamp.
10. Replace `cooling_fan_radiator_control()` PWM output with two-stage relay
    logic on bits `0x40`/`0x80`, and move the bay fan from bit `0x40` to pad
    `0xb6`.
11. NOP `cooling_chargecooler_pump_100ms()` in `interrupt_timer_2000hz`. Do not
    try to calibrate it to zero — the output is inverted.
12. Optional: clear the fuel-pressure fault bit's veto in `o2_fuel_learn_100ms`
    to restore LTFT learning.
13. Optional: port `intake_path_control()` back from 0091 for ACIS and the
    airbox flapper, freeing pads `0xc9` and `0x8f` from 0278's CAC and
    exhaust-flap use.
