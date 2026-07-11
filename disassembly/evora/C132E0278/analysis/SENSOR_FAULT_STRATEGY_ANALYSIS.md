# GT430 Sensor Acquisition and Fault Strategy

## Scope and confidence

This report describes the sensor acquisition, plausibility, substitution, and controller-gating strategy visible in firmware `C132E0278`. It focuses on architecture and high-confidence behavior rather than enumerating every OBD DTC.

The main conclusion is that the firmware does not treat a sensor DTC as a single global shutdown event. It separates:

1. acquisition of the latest hardware value,
2. electrical-range and cross-sensor plausibility,
3. time/confidence qualification,
4. diagnostic state,
5. a cross-subsystem availability bitmap, and
6. a consumer-specific response.

That response can be continued operation, use of one surviving redundant track, substitution of a calibrated/modelled value, inhibition of adaptive learning, or a hard limp/default mode. This hierarchy is strongly supported by the code. Some individual bits in the aggregate failure word still lack a defensible sensor name and are deliberately not named here.

## Acquisition pipeline

The high-level analog path is:

```text
eQADC conversion command streams
        |
        v
eDMA writes 16-bit result RAM: adc_dma_dest[256]
        |
        +--> foreground decode: adc_decode_dma_samples()
        |       named raw sensor voltages/current signals
        |
        +--> 200 Hz snapshot: adc_snapshot_buffers_200hz()
                channels 0x00-0x2c and 0x30-0x3a
        |
        v
lookup/scaling/filtering -> plausibility/debounce -> diagnostic monitor state
        |
        v
engine_state_failure_flags -> controller-specific fallback or inhibition
```

`adc_decode_dma_samples()` does not start a conversion and does not wait for hardware. It reads result RAM that eDMA is already updating. Most samples are 12-bit payloads stored left-shifted in 16-bit entries, hence the pervasive `>> 4` decode.

`adc_snapshot_buffers_200hz()` copies 45 primary results and 11 secondary results into stable buffers. This provides a rate-bounded view for slower consumers while foreground and interrupt paths can continue to use the live DMA area.

Knock acquisition has two distinct roles:

- channels `0x22` and `0x23` are continuously sampled for circuit diagnostics;
- channels `0x34` and `0x35` are crank-window samples used for combustion knock processing.

That distinction prevents the continuous diagnostic samples from being mistaken for the angle-synchronous knock measurements.

## High-confidence ADC assignments

| DMA index | Signal or role | Notes |
|---:|---|---|
| `0x04`-`0x07` | Four oxygen-sensor heater currents | Circuit/control feedback inputs |
| `0x0b` | Transmission-fluid temperature | Read only when `COD[1].bit19` enables the analog path; otherwise raw value is zeroed |
| `0x0d` | Engine coolant temperature | Thermistor lookup, filtering, calibrated fallback |
| `0x0e` | Primary inlet/engine air temperature | Thermistor lookup, filtering, calibrated fallback |
| `0x0f` | Charge-cooler/TMAP temperature | Thermistor lookup; modelled replacement on failure |
| `0x10` | Cruise switch analog voltage | Part of driver-input diagnostics |
| `0x11` | Fuel-level voltage | Clipped before lookup and separately filtered |
| `0x13` | EVAP pressure voltage | Scale/offset conversion and filtering |
| `0x14` | ECU supply voltage | Raw value receives a 1/8 new, 7/8 previous low-pass filter during decode |
| `0x15` | Ignition voltage | Also participates in initialization/ignition-state qualification |
| `0x16`-`0x19` | Four oxygen-sensor voltages | Bank/sensor channels 1, 5, 2, and 6 in symbol order |
| `0x1a` | Oil-pressure analog voltage | Used only when coding/calibration selects an analog sensor |
| `0x1b` | Manifold pressure | Linear scale/offset with saturation |
| `0x1c` | Clutch potentiometer | Coding-dependent, filtered only while its fault state permits |
| `0x1d` | Paddle-shift analog input | Relevant to IPS/transmission variants |
| `0x1e` | Fuel-pressure voltage | Linear scale/offset, filtered, modelled target fallback |
| `0x1f` | A/C evaporator temperature | Lookup and low-pass filtering |
| `0x22`, `0x23` | Continuous knock circuit values | Used for low/high circuit monitoring |
| `0x25` | Accelerator midpoint/reference check | Additional pedal plausibility input |
| `0x27` | Barometric pressure | Linear scale/offset, calibrated failure fallback |
| `0x32` | MAF input | Lookup-scaled airflow source |
| `0x34`, `0x35` | Crank-window knock samples | Banked combustion-knock path |

TPS and accelerator-pedal processing also consumes secondary ADC channels and named voltage values. Their safety behavior is more important than forcing every raw channel to a name at this stage.

## Scaling, filtering, and substitution

The conversion layer uses the physical shape appropriate to each sensor rather than one generic ADC transform.

| Sensor family | Conversion/filter | Failure behavior |
|---|---|---|
| Coolant thermistor | Lookup table plus filtered internal state | Uses `CAL_sensor_coolant_temp_fallback_value` when aggregate bit `0x00000002` is set |
| Primary IAT thermistor | Lookup table plus filtered internal state | Uses `CAL_sensor_iat_fallback` when bit `0x00000001` is set |
| Charge-cooler/TMAP temperature | Lookup plus filter | Synthesizes manifold temperature from primary IAT and an RPM/load model when bit `0x00800000` is set |
| Barometer | Linear scale/offset with lower-bound handling | Uses `CAL_sensor_baro_sensor_failure_fallback` when bit `0x00000008` is set |
| MAP | Linear scale/offset and saturation | Uses `manifold_pressure_calculated` when bit `0x01000000` is set |
| Fuel pressure | Linear scale/offset, saturation, low-pass filter | Reconstructs absolute pressure from commanded target plus barometric pressure when bit `0x04000000` is set |
| Ambient/alternate air temperature | Network or alternate source when coded and healthy | Reverts to primary IAT, then the IAT calibration fallback if needed |
| Clutch potentiometer | Low-pass filter | Output is forced to zero when its local fault state disallows the signal |
| Oil pressure | Linear scale/offset and saturation | Analog calculation exists only when oil-warning mode selects `ANALOG_SENSOR` |
| Fuel level | Input clipping, lookup, separate filtering | Bad/raw extremes are contained before percentage/state logic |

The substitutions are intentionally domain-specific. A fixed temperature is suitable for coolant/IAT; calculated MAP is more useful to airflow control; commanded differential pressure plus barometer keeps fuel-pressure consumers coherent. A substituted value should therefore be interpreted as a control value, not evidence that the physical sensor recovered.

## Validation hierarchy

### 1. Electrical bounds

Raw voltages are checked against calibrated upper and lower limits. `test_threshold()` classifies values as high, in range, or low. Pressure calculations include explicit lower bounds and `0x7fff` saturation where appropriate.

### 2. Temporal qualification

The firmware generally avoids acting on a single sample. The TPS/pedal helper `tps_debounce_with_hysteresis()` is representative:

- an accumulator rises or falls at calibrated rates;
- separate thresholds govern fault confirmation and recovery;
- intermediate accumulator values are marked as debouncing;
- a `threshold_2` value of `0xffff` makes a confirmed condition latch.

Other monitors use counters, confidence values, enable conditions, and pass/fail history before changing diagnostic or availability state.

### 3. Redundant-channel plausibility

TPS and accelerator-pedal tracks are independently range checked and mutually compared. The pedal also checks an additional midpoint/reference channel. This detects faults that remain electrically in range but disagree with the paired track.

### 4. Diagnostic state

Individual OBD monitor state remains distinct from immediate raw validity. Monitors have enable criteria, debounce, completion, and pass/fail state. A DTC state therefore must not be equated directly with the live control substitution state.

### 5. Cross-subsystem availability

`engine_state_failure_flags` aggregates debounced monitor health into a bitmap used throughout control. It is best understood as an availability/fallback contract between diagnostics and controllers, not as a packed DTC list.

## High-confidence aggregate failure bits

| Mask | High-confidence meaning | Directly observed consequence |
|---:|---|---|
| `0x00000001` | Primary IAT unavailable | Calibrated IAT fallback; learning/controller gates |
| `0x00000002` | Coolant temperature unavailable | Calibrated coolant fallback; thermal and learning gates |
| `0x00000004` | TPS/ETB-related aggregate failure | Torque/cruise gating |
| `0x00000008` | Barometric pressure unavailable | Calibrated barometer fallback |
| `0x00000010` | MAF/load source unavailable | Engine-load calculation changes to alpha-N |
| `0x00000400` | ABS/vehicle-speed CAN unavailable | Speed-dependent and cruise/traction functions disabled or invalidated |
| `0x00000800` | IPS powertrain fault request | Set/cleared from validated network state |
| `0x00008000` | Accelerator-pedal aggregate failure | Driver-demand and cruise gating |
| `0x00010000` | Hard ETB/throttle fault | Throttle actuator and torque-path limp behavior |
| `0x00100000` | Cruise input failure | Cruise eligibility removed |
| `0x00800000` | Charge-cooler/TMAP temperature unavailable | Modelled temperature substitution |
| `0x01000000` | MAP unavailable | Calculated manifold-pressure substitution |
| `0x02000000` | Low-oil-pressure event/availability state | Oil-protection and limp-related gating |
| `0x04000000` | Fuel-pressure measurement unavailable | Commanded-target pressure substitution |
| `0x20000000` | Network/alternate ambient-source health group | Alternate ambient source rejected |
| `0x40000000` | Ambient-temperature source unavailable | Primary-IAT fallback |

Bits `0x20` through `0x100` clearly gate cam/VVT and knock functions, but their exact one-to-one sensor labels are not yet proven. Other bits represent monitor groups such as mixture, auxiliary cooling, knock/misfire, and network health. The masks and consumers are real; assigning precise public names to every bit would currently be speculative.

## Throttle and accelerator fault strategy

The electronic-throttle input design supports degraded operation before hard failure.

For accelerator pedal position:

- D and E tracks are scaled independently;
- each track has range/debounce state;
- the tracks are compared for agreement;
- an additional midpoint/reference ADC channel is qualified;
- one failed track selects the surviving plausible track;
- a critical or dual-track failure forces pedal demand to zero;
- left-foot-braking override is applied after track selection.

For throttle feedback:

- two position tracks receive equivalent range and plausibility treatment;
- one failed track permits selection of the remaining track and marks a degraded state;
- a confirmed system failure replaces the normal position with `CAL_tps_commanded_during_fault`;
- the ETB state machine separately marks hard fault/actuator inhibition.

The pairs `accel_pedal_state_degraded` / `accel_pedal_fault_active` and `tps_state_degraded` / `tps_fault_active` are important distinctions. “Degraded” means redundancy has been lost but a plausible track remains. “Fault active” is the hard-failure state that triggers the stronger default.

## Digital driver inputs

Fourteen SIU GPIO inputs are sampled at 100 Hz through `digital_input_debounce()`.

The per-input configuration contains:

- polarity inversion (`flags.bit0`),
- calibrated press and release debounce times,
- ordinary momentary behavior or edge-toggle behavior (`flags.bit1`), and
- an edge latch preventing repeated toggles while a button remains held.

`digital_inputs_zero()` clears toggle-configured states during initialization/reset. Brake and clutch processing also has startup qualification; the identified `brake_clutch_startup_debounce_timer` is reset to 40 ticks while ignition is inactive.

Vehicle-mode inputs are not trusted in isolation. Sport, race, launch, traction-control, and clutch behaviors depend on variant coding and are reset toward Tour/default operation when ignition, ABS/ESP/network, speed-limit, or related plausibility conditions make the requested mode unsafe.

## Coding-dependent hardware paths

The same binary supports materially different vehicle hardware. Important coding fields observed in control flow include:

| Coding field | Hardware/behavior selected |
|---|---|
| `COD[0].bits13-15` | Transmission type; manual versus IPS paths, paddles, TCU CAN, gear logic, idle and rev-limit tables |
| `COD[0].bits25-27` | Cruise-control type |
| `COD[0].bits28-30` | HVAC type |
| `COD[1].bit10` | Alternate/ambient temperature source |
| `COD[1].bit12` | Steering-angle sensor presence |
| `COD[1].bit19` | Analog transmission-temperature channel |
| `COD[1].bits21-22` | Clutch input type, including potentiometer versus network/discrete paths |
| `COD[1].bit20` | Transmission cooling pump |
| `COD[1].bit26` | Engine-bay auxiliary fan |
| `COD[1].bits7,8,23,24` | Race, launch, sport-button, and traction-button features |

`coding_validated` is set only after a market/feature combination consistency check. Invalid coding sets a main diagnostic flag. This means a channel reading zero or an inactive controller can be intentional variant behavior, not necessarily an unrecognized fault.

## How fault state gates major controllers

| Consumer | Behavior when required state is unavailable |
|---|---|
| Air/load estimation | MAF/load failure selects alpha-N for steady and transient load calculation |
| Fuel pressure | Failed feedback is replaced with target differential pressure plus barometer so downstream control remains coherent |
| Fuel trims/adaptation | Large critical-sensor masks inhibit closed-loop learning and long-term adaptation without necessarily stopping base fueling |
| Ignition/knock | Knock correction and learning are suppressed by knock-supporting and cam/timing availability groups |
| VVT | Bank/controller operation is gated by cam-related failure bits; fallback angle behavior remains available |
| Cooling | Missing alternate ambient temperature falls back to primary IAT; critical temperature faults can drive conservative/high fan duty |
| Electronic throttle | Single-track faults permit degraded feedback; hard ETB/pedal faults use calibrated/zero defaults and disable normal actuator demand |
| Cruise control | Requires healthy throttle, pedal, MAF/load, vehicle speed, TMAP temperature, cruise input, and non-limp rev-limit state |
| Traction/slip logic | ABS/vehicle-speed loss invalidates or disables speed/slip-dependent behavior |
| Rev limiter | Composite mask `0x0dcefbf7`, plus misfire state, selects `CAL_revlimit_limp_mode` rather than the normal mode-dependent limit |
| CAN torque/status | Some throttle/ignition fault combinations produce invalid sentinels instead of plausible-looking torque/status values |

This shows two broad safety policies:

1. preserve basic engine operation using physically coherent substitutes where possible;
2. remove authority from adaptive, performance, and driver-assistance layers when their inputs cannot be trusted.

## Remaining uncertainties

- The exact semantic name of every `engine_state_failure_flags` bit is not yet justified. Several can be localized to cam/VVT, mixture, auxiliary cooling, or network groups but not safely assigned one-to-one.
- A few analog channels remain unnamed despite identifiable consumers. Additional eQADC command-table reconstruction would improve the channel map.
- Some monitor-to-aggregate transitions are spread across the large OBD completion routine and separate local setters. A machine-generated writer/reader matrix would make the remaining groups easier to resolve.
- Transmission/clutch behavior has several coding variants and deserves a focused manual-versus-IPS trace if that distinction becomes important.

## Marginal value of this pass

The marginal value is **high for architecture and safe interpretation**, and **moderate for additional symbol recovery**.

High-value gains are:

- proving that ADC decoding reads continuously DMA-fed result RAM rather than synchronously sampling hardware;
- separating live raw validity, monitor/DTC state, aggregate availability, and controller response;
- identifying the modelled/calibrated fallback strategy for coolant, IAT, TMAP temperature, barometer, MAP, ambient temperature, and fuel pressure;
- documenting the dual-track throttle/pedal degraded-versus-hard-fault hierarchy;
- showing that coding controls whether several hardware paths exist at all; and
- tying global fault state to load estimation, learning, knock, VVT, cooling, DBW, cruise, traction, rev limiting, and CAN validity.

Further exhaustive DTC enumeration would add relatively little at this point. The next useful step would be a targeted writer/reader matrix for the unresolved aggregate bits or reconstruction of the eQADC command lists, not a flat list of trouble codes.
