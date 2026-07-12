# eMIOS Capture Input Analysis

## Conclusion

The three previously unresolved callbacks at `0x0004B870`, `0x0004B8BC`, and `0x0004B964` do not represent three unknown live sensors:

- `0x0004B8BC` is eMIOS channel 5 period capture for the optional hard-wired vehicle/wheel-speed input.
- `0x0004B964` is eMIOS channel 9 period capture for A/C compressor speed. Several associated RAM names incorrectly call this fuel-level data.
- `0x0004B870` acknowledges eMIOS channel 6 and increments a counter, but channel 6 is initialized later as the electronic-throttle PWM output. No application consumer of the counter exists. It is most likely a dormant/test callback or stale vector-table assignment, not a third active capture sensor.

The supplied ECU pinout provides a direct connector candidate for A/C compressor speed (`LC1`). It does not name a dedicated vehicle-speed pulse pin, so the exact channel-5 connector pin remains unresolved without an MCU-ball-to-connector netlist or full schematic.

## Register decoding

Each eMIOS unified channel occupies `0x20` bytes. For channel `n`:

- counter/data A is at `n*0x20 + 0x00`;
- counter/data B is at `n*0x20 + 0x04`;
- status is at `n*0x20 + 0x10` in the decompiler's flattened view.

`init_emios_input_capture()` at `0x0004B6E0` selects mode `5`, configures edge selection/polarity, clears status, and assigns the channel's INTC source priority 3. The callbacks acknowledge status flag bit 0 after reading the captured A/B values.

## Channel 5: vehicle/wheel-speed period

`FUN_0004B8BC()` acknowledges the register at flattened offset `0xB0` (`5*0x20 + 0x10`) and reads offsets `0xA0/0xA4`, proving channel 5. It marks a fresh sample and stores the unsigned capture difference in `DAT_40001820`.

`watchdog_emios0_sensor_333ms()` runs in the 3.33 Hz task. If no new edge was received, it writes `0xFFFFFFFF`; otherwise it clears the fresh-sample marker for the next interval.

The decisive consumer is `car_speed_update_200hz()`. When coding bit `COD[1].bit9` selects the non-network source, it:

1. clamps `DAT_40001820` to 16 bits;
2. treats `0xFFFF` as missing;
3. divides tire circumference and a time constant by the captured period;
4. optionally divides by `CAL_ecu_abs_ring_teeth_count`;
5. smooths the result into `car_speed_u8` and `car_speed_x100`.

This identifies the signal as a vehicle/wheel-speed pulse period with high confidence. The mention of ABS ring-tooth count suggests a direct wheel/shaft pulse option for another coding variant, while the GT430 normally receives road speed through the network.

The Evora 400 connector page does not explicitly list “vehicle speed” or “wheel speed.” `RG2 ENGINE CRANK SIGNAL` is an output and is not a credible assignment. The annotated `TC +/-` pins are also insufficient evidence. A connector assignment should therefore not be guessed from this page alone.

## Channel 9: A/C compressor speed

`init_emios1()` at `0x0004B900` sets `siu_pcr[0xBC]=0xD00` and initializes eMIOS channel 9 for capture on the selected edge. `FUN_0004B964()` acknowledges the channel-9 status register and stores the A/B capture difference.

The variables currently named `fuel_level_sensor_data_raw` and `fuel_level_sensor_flag` are misleading. Their consumer `ac_evap_sensor_process()`:

- rejects a missing/oversize capture period;
- calculates `60,000,000 / period`;
- smooths the result into `DAT_400026E8`;
- feeds the A/C compressor diagnostic path.

That is an RPM/frequency conversion, not a fuel-level calculation. The connector page lists:

| Connector pin | Type | Function |
|---|---|---|
| `LC1` | Digital input | `AC COMP SPEED SIG` |

Channel 9 is therefore the A/C compressor-speed capture input with high semantic confidence. Assigning `siu_pcr[0xBC]` to connector `LC1` is strongly supported by the unique pinout function, but a formal ball/net mapping is still desirable.

Recommended renames:

| Current name | Recommended name |
|---|---|
| `init_emios1` | `init_ac_compressor_speed_capture` |
| `FUN_0004B964` | `emios9_ac_compressor_speed_isr` |
| `fuel_level_sensor_data_raw` | `ac_compressor_speed_capture_fresh` |
| `fuel_level_sensor_flag` | `ac_compressor_speed_period` |
| `ac_evap_sensor_process` | `ac_compressor_speed_process` |

## Channel 6 callback: dormant or repurposed

`FUN_0004B870()` increments `DAT_40001818` and acknowledges flattened status offset `0xD0`, which is channel 6. No other code reads `DAT_40001818`.

The live application later calls `init_eMIOS(6, DAT_40008744, 0, 0)` from electronic-throttle hardware initialization and drives that channel through `set_throttle_pwm()`. Mode `0x1A` is an output/PWM configuration, not the input-capture mode `5`.

Consequently, the callback side effects do not justify assigning a sensor name. Plausible explanations are:

- a vector entry retained from development/test firmware;
- an interrupt callback shared with another variant where channel 6 is an input;
- a harmless counter for an output-channel flag that is never enabled in this calibration.

The original binary/vector table is needed to distinguish “address present in a generic callback table” from “installed and enabled at runtime.” Until then, retain an explicitly uncertain name such as `emios6_flag_counter_isr_unused`.

## Pinout correlation limits

The supplied page is an ECU connector function index, not a full schematic. It supports semantic correlation but does not show:

- MPC5534 ball/pad numbers;
- SIU PCR index to package ball mapping;
- internal input-mux selection;
- connector-to-PCB net names;
- conditioning circuits or pull-ups.

Accordingly:

- `LC1 -> A/C compressor speed -> eMIOS9` is high confidence semantically and medium-high confidence electrically.
- eMIOS5 -> vehicle/wheel-speed period is high confidence in software, but its connector assignment is unresolved.
- eMIOS6 is the live throttle PWM output; the definition-only callback must not be presented as an unknown physical capture input.

## Next evidence

1. Recover the original INTC vector/table reference for all three callback addresses.
2. Export the SIU/eMIOS input mux and MPC5534 package-ball mapping.
3. Obtain the board schematic or netlist connecting `siu_pcr[0xBC]` and the channel-5 pad to connector cavities.
4. Compare coding variants where `COD[1].bit9` selects the hard-wired speed source.
5. Rename the channel-9 A/C variables after confirming no tooling depends on the legacy names.
