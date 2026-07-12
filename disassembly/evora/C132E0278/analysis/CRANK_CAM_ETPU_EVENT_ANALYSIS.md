# Crank, Cam, and eTPU Event Analysis

## Confirmed interrupt map

| INTC vector | Handler | eTPU channel / role | Priority |
|---:|---:|---|---:|
| `0x44` | `0x000462C8` | Channel 0 crank/injection event, `inj_interrupt` | 14 |
| `0x45` | `0x00046FC4` | Channel 1 intake cam bank 2 | 14 |
| `0x46` | `0x00046C9C` | Channel 2 intake cam bank 1 | 14 |
| `0x47` | `0x00048870` | Channel 3 auxiliary crank sync/reference event | 2 |
| `0x48..0x4D` | `0x00047934..0x000484EC` | Ignition channels 4..9 | configured event priority |
| `0x51` | `0x000475E8` | Channel 13 exhaust cam bank 1 | 14 |
| `0x52` | `0x000472D8` | Channel 14 exhaust cam bank 2 | 14 |
| `0x55` | `0x00048740` | Channel 17 synchronized MAF/MAP event | 14 |
| `0x62` | `0x000ADC0C` | Channel 30 knock ADC sampling | 15 |
| `0x63` | `0x000ADB38` | Channel 31 knock-window boundary | 14 |

The raw knock pointers are at flash `0x000D5188` and `0x000D518C`. The combination of vector-table pointer, eTPU-channel acknowledge, PRAM access, and PSR configuration makes the channel/address mapping high confidence.

## Crank channel and synchronization

The channel-0 event ISR reads these eTPU parameter-RAM values:

| PRAM field | Runtime use |
|---|---|
| Byte 0 | eTPU crank state (`DAT_400017DB`) |
| Byte 1 | synchronization state (`DAT_400017DA`) |
| 24-bit field `0x2D` | crank-cycle position `0..0x47` |
| Field `0x31` | crank angle/speed scaling |
| Fields `0x35/0x3D` | event timestamps/interval sources |

State below 4 invalidates the usable engine-speed result. Synchronization state 4 performs the engine-running transition and arms the synchronized consumers: ignition, injection, channel 17, and knock-window channel 31.

`crank_trigger_process___()` and the channel-0 ISR then perform three related but distinct tasks:

### Cylinder interval/misfire capture

At crank-cycle positions:

```text
04, 10, 1C, 28, 34, 40 hex
```

the event maps to cylinders:

```text
4, 5, 0, 1, 2, 3
```

and calls `misfire_record_cylinder_interval()` at `0x0007B2C8`. That routine retains current and prior 24-bit intervals per cylinder for the 200 Hz misfire detector.

Engine-period samples are taken at positions `08, 14, 20, 2C, 38, 44` hex.

### Sequence-confidence monitor

`crank_event_sequence_monitor()` at `0x0004561C` recognizes positions:

```text
07, 13, 1F, 2B, 37, 43 hex
```

The expected predecessor chain is `5 -> 0 -> 1 -> 2 -> 3 -> 4 -> 5`. Each correct transition sets the corresponding bit in the six-bit sequence-validity field at `DAT_40002052`.

Those per-position validity bits are consumed by per-cylinder O2/fault qualification. They are not themselves a direct engine shutdown command.

### Channel-3 sync/reference callback

The original vector table resolves `FUN_00048870()` as vector `0x47`, eTPU channel 3. The callback:

- acknowledges channel 3 through the channel status location;
- increments `DAT_400017F4`;
- writes `0xFF` to the sequence predecessor (`DAT_4000174C`).

Resetting the predecessor guarantees that the next qualifying sequence position cannot be accepted as continuous with the old sequence. This behavior is consistent with an auxiliary crank synchronization/reference or synchronization-loss event.

Recommended name: `etpu_crank_sync_aux_event_isr`. “Synchronization-loss callback” is plausible but should remain medium-high confidence until the proprietary eTPU microfunction assigned to channel 3 is identified. The callback alone does not disable fuel or spark; engine-stop/fault behavior follows from the main eTPU state falling below synchronized state, speed invalidation, watchdogs, and subsequent diagnostic logic.

## Cam acquisition and sync contribution

Before crank synchronization reaches state 4, all four cam ISRs classify edge spacing and polarity. Recovered edge-distance classes are approximately:

- 4..7 crank events;
- 8..13 crank events;
- 14..19 crank events.

The resulting phase/direction state is written back to channel-2 PRAM byte 2 with `eTPU_pram_write_byte(2, DAT_400017D9)`, allowing the crank/sync microcode to consume cam phase information.

After state 4, the same ISRs calculate wrapped positions over the 720-degree engine cycle and refresh individual cam activity/zero-learning timers. Their confirmed mappings are:

| Handler | Address | eTPU channel |
|---|---:|---:|
| `vvt_cam_edge_isr_intake_bank2` | `0x00046FC4` | 1 |
| `vvt_cam_edge_isr_intake_bank1` | `0x00046C9C` | 2 |
| `vvt_cam_edge_isr_exhaust_bank1` | `0x000475E8` | 13 |
| `vvt_cam_edge_isr_exhaust_bank2` | `0x000472D8` | 14 |

Cam timeouts and invalid phase eventually suppress the appropriate VVT loops and feed P0341/P0346/P0366/P0391 diagnostics. The crank-sensor path feeds P0335 and engine-speed validity.

## Knock-window event chain

The knock path uses two adjacent eTPU channels with deliberately different priorities.

### Channel 31: angle-window boundaries

`FUN_000ADB38()` is definitively vector `0x63`, channel 31. It toggles `DAT_4000157B`; on every alternate invocation, when the previous toggle was nonzero, it sets `knock_sampling_active=true`.

Channel 31 is initialized as a timed crank-angle event and scheduled with:

```text
knock_schedule_next_window(0x1F, center_angle[cylinder], 1000)
```

The callback therefore represents alternating start/end boundaries for successive knock acquisition windows. Which physical boundary occurs first after initialization is not completely explicit in the C export, but the alternating behavior is high confidence.

Recommended name: `etpu_knock_window_boundary_isr`.

### Channel 30: ADC sample processing

`knock_interrupt_adc_process()` at `0x000ADC0C` is vector `0x62`, channel 30, priority 15. It samples eQADC result `0x34` for odd-index cylinders and `0x35` for even-index cylinders while the window is active.

At 64, 128, or the configured sample count it:

1. stops the active sampling window;
2. advances the cylinder index `0..5`;
3. schedules the next channel-31 angle window;
4. sets `knock_sensor_new_data_available` for foreground spectral/Goertzel processing.

Channel 30 was initialized as an eTPU PWM/timing source at `CAL_knock_agc_scaling_threshold` with 50% duty. The priority-15 ADC handler therefore owns time-critical sample collection; the priority-14 channel-31 handler only gates/schedules the windows.

`FUN_000ADB38()` should not be renamed as a knock ADC ISR or per-cylinder knock processor. It neither reads ADC data nor selects the cylinder.

## Synchronization-loss and fault propagation

```text
cam/crank edges
    -> eTPU microcode sync state and crank-cycle position
    -> channel-0 event ISR updates speed, timestamps, and cylinder events
    -> channel-3 auxiliary sync/reference event invalidates sequence continuity
    -> state below 4 invalidates speed and prevents synchronized scheduling
    -> engine-state watchdogs and crank/cam monitors mature failures
    -> fuel/spark/VVT/knock consumers fall back or are inhibited
    -> P0335/P034x/P0366/P0391 and related failure flags
```

This is safer and more accurate than treating channel 3 as a one-call shutdown. The eTPU synchronization state is the authoritative operational gate; software callbacks expose its events and propagate evidence into application-level state.

## Remaining work

1. Extract and identify the proprietary eTPU microfunction/channel assignment table, especially channels 0, 2, 3, 30, and 31.
2. Determine the exact channel-3 event condition: reference edge, stall, sync loss, or another microfunction HSR/state event.
3. Establish which channel-31 boundary is first after reset and how the 1000-unit width maps to crank angle/time.
4. Correct `DumpVectorTable.py` to discover or accept the C132E0278 vector-table base `0xD5000`.
5. Preserve the recovered historical blob hash in tooling/documentation so future vector analysis is reproducible without restoring deleted firmware to the repository.

Confidence is high for all vector, handler, priority, and channel mappings; high for crank/misfire positions and knock alternation; medium-high for the semantic name of channel 3; and medium for first-edge polarity of the knock window.
