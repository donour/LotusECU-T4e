# B13200091 eTPU microcode

The MPC5534's eTPU (enhanced Time Processing Unit) runs the crank/cam decoding, injector and
coil timing, and the PWM outputs. Its microcode is a separate 9 KB binary embedded in the
PowerPC flash. Ghidra cannot disassemble it, so `etpudis.py` (in this folder) decodes it from
the eTPU Reference Manual (ETPURM Rev 1, Table 9-45). `B13200091_etpu.lst` is the full
annotated listing.

**The image is byte-identical in B13200091, C132E0271, C132E0278 (GT430) and E132E0288**, so
everything below applies to all of those Evora variants. It was written by EFI Technology. It
is not the Freescale "Set 2" engine library, although the host-side loader follows Freescale's
`fs_etpu_init` API.

```
python etpudis.py ../B13200091.hex --offset 0xBDEB8 > B13200091_etpu.lst
python etpudis.py ../B13200091.hex --offset 0xBDEB8 --no-symbols   # raw names only
```

## Where it lives / how it is loaded

| Item | Flash | Notes |
|---|---|---|
| Code image (SCM) | `0x000BDEB8`, 0x2400 bytes | copied to SCM `0xC3FD0000` |
| Global data init | `0x000BDDA8`, 0x110 bytes | copied to SDM `0xC3FC8000` (all zero except a few bytes) |
| Engine config | RAM `0x40000190` (`.data` from flash `0x000C5AE8`) | 8 words, `fs_etpu_config_t` layout |

`init_etpu` → `FUN_00042290(config, code, 0x2400, globals, 0x110)` is `fs_etpu_init`. It
clears SCM, copies code and globals, and writes MCR/MISC/ECR/TBCR/REDCR. `init_dspib_2` sets
GTBE to start the time bases. Channel parameter RAM is allocated after the globals by
`etpu_param_alloc` (bump allocator at `0x4000182C`). The CPU reads and writes 24-bit
parameters through the sign-extended mirror at `0xC3FCC000` (`eTPU_write_param24`,
`eTPU_read_24bit`).

Engine A config:

| Reg | Value | Meaning |
|---|---|---|
| ECR_A | `0x0002C000` | ETB = 0 (entry table at SCM 0), FPSCK=2, CDFC=3 |
| TBCR_A | `0x3A008003` | **TCR1 = sysclk/2/4 = 10 MHz (100 ns)**. TCR2CTL = rising TCRCLK, **AM = 1 (angle mode)**, TCR2P = 0 |
| REDCR_A | `0xC000C000` | |

## Time bases

* **TCR1** = 10 MHz free-running time. Every "ticks" value the CPU writes for pulse widths
  (injector PW, dwell limit, PWM period) is in 100 ns units. `eTPU_init_pwm_channel` passes
  `10000000` as the clock.
* **TCR2** = engine angle clock (EAC, angle mode), driven by the crank channel. **100 ticks
  per tooth on a 36-2 wheel**: 3600 ticks/rev and **7200 ticks per 720° cycle (0.1°/tick)**.
  All angles in this firmware (spark, injection, cam edges, knock windows) are 0..7199 in
  0.1° units. The constant `0x1C20` = 7200 appears throughout as the wrap value.

## Function table

The entry table holds 9 functions at 64 bytes each (0x000–0x23F). Code runs from 0x400 to
0x1F37, and the rest of the image is zero.

| CFS | Name (mine) | Code | Channels in this firmware | CPU init helper |
|---|---|---|---|---|
| 0 | CRANK_36_2 | 0x51C–0xA94 | 0 | `FUN_00050754` |
| 1 | INJ_ANGLE_PULSE | 0xA98–0xBAC | 4–9 (injectors 1–6), 31 (knock window) | `FUN_000509b4` |
| 2 | INJ_ADV_UNUSED | 0xBB0–0x16AC | **none** | — |
| 3 | SPARK | 0x16B0–0x18C8 | 18–23 (coils 1–6), 17 (angle-synchronous interrupt) | `eTPU_spark_channel_init` |
| 4 | PWM (alt. entry encoding) | 0x18CC–0x19F8 | 15, 28 (VVT), 16 (A/C), 26 (exhaust flap), 27 (EVAP purge), 30 (knock DSP sample clock) | `eTPU_init_pwm_channel` |
| 5 | PERIOD_MEAS | 0x19FC–0x1AE4 | 3 | `FUN_00050adc` |
| 6 | DUAL_MATCH_PULSE | 0x1AE8–0x1C48 | 4–9 and 18–23 (temporarily, for test and priming pulses) | `eTPU_init_single_shot_pulse` (`FUN_00050c18`) |
| 7 | PULSE_ACCUM_UNUSED | 0x1C4C–0x1ECC | **none** | — |
| 8 | CAM_EDGE | 0x1ED0–0x1F34 | 2/1 inlet B1/B2, 13/14 exhaust B1/B2 | `FUN_00050880` |

The channel number is taken from the `CxCR` write: `prio<<28 | CFS<<16 | ETCS<<24 | CPBA`.
eTPU channel *n* interrupts on INTC source 68+*n* (`INTC_PSR[0x44+n]`).

Host service request (HSR) to entry mapping, standard encoding: HSR1 → e0–3, 2 → e4,
3 → e5, 4 → e6, 5 → e7, 6 → e8, 7 → e9.

### Shared subroutines (0x400–0x518)

* `0x0400 link_4_channels`: sends a channel link to each byte of P.
* `0x0418 unexpected_entry`: called from every unused entry. It builds a flag word in ERT_B
  (LSR/MRL/TDL bits | chan) and does nothing else.
* `0x044C angle_in_window(lo, hi, x)`: circular "is x between lo and hi", mod 7200.
* `0x04B8 angle_add_mod7200`, `0x04F0 angle_sub_mod7200`.

## F0 — crank, 36-2 (channel 0)

Globals (SDM byte offsets; the CPU reads them in `crank_trigger_process`):

| Off | Field | CPU name |
|---|---|---|
| 0x00 b0 | state 0..10 (dispatch index) | `DAT_400016b3` (`<4` ⇒ speed invalid) |
| 0x00 b1 | sync status: 0 lost, 1 first edge, 3 gap found, 4 full 720° sync | `DAT_400016b2` (`<4` ⇒ cam-phase search) |
| 0x00 b2 | **cam phase, written by the CPU** (1 or 2) | `etpu_sdm_write_u8(2, DAT_400016b1)` |
| 0x2C | tooth count 0..71 (the gap counts as 3) | `crank_tooth_counter` |
| 0x30 | last tooth period (TCR1) | `eTPU_crank_angle_speed_scaling` |
| 0x34 / 0x38 | previous periods | `DAT_400016bc` |
| 0x3C | last tooth TCR1 time | `DAT_400016b8` |

Channel params (from init `FUN_00050754(0,1,3,0, 0x196e6b,0,0,0x800000,0x100)`):

* `+0x00 stall_period` = 0x196E6B (166.7 ms). This is the seed period, and the stall timeout
  is measured from the last tooth.
* `+0x0C gap_ratio` = 0x800000 (0.5 as a 24-bit fraction). A period counts as the gap if it
  is greater than `prev × (1 + 0.5)`.
* `+0x04 / +0x14`: values that HSR1 forces into TCR2 and the tooth count (resync / test).

Behaviour:

1. HSR3 (e5) initialises: input-capture on the rising edge (`ipac:rise`, mode `m2_st`),
   TCR2 = −1, state 1.
2. On each tooth it captures ERT_A and computes `period = now − prev_edge`. It then loads
   **TRR = period × 5.12** (`×8 /100 ×64`, i.e. period·512/100: TRR fixed point divided by
   100 ticks/tooth). The angle hardware then interpolates 100 TCR2 ticks across the next
   tooth.
3. States 1–3 collect periods, then look for the gap with the 1.5× test. When it finds the
   gap: tooth count 0, TCR2 0, sync status 3.
4. Full sync needs engine phase, and the **eTPU does not decode the cam itself**. The cam
   channels (F8) interrupt the CPU, and `vvt_*_position_*` classifies the spacing of cam
   edges in tooth counts (the 3-tooth VVT-i wheel pattern). It writes global byte 2 = 1 or
   2. On the next gap the crank function sets TCR2 = 100 (first rev, phase 2) or 3700 =
   0x0E74 (second rev, phase 1) and sets sync status 4.
5. In sync, TPR is reprogrammed before each gap: at tooth 33 (0x21) `MISSCNT = 2`; at tooth
   69 (0x45) `MISSCNT = 2` and `LAST = 1`, so TCR2 wraps at 7200. Every gap is re-verified
   with the 1.5× test, and a failure drops to state 1, TCR2 = −1, sync 0, phase 0.
6. A match on `last_tooth_time + stall_period` with no edge means stall. The function resets,
   sets sync status 1 and raises an IRQ.

## F1 — angle-triggered pulse (injectors, knock window)

Params: `+0x00 start_angle` (b0 = state), `+0x04 pulse_width` (TCR1 ticks; b0 = enable
mode, 4 = enabled, 3 = disabled), plus latched copies at `+0x08/+0x0C`.

* Match1 = `start_angle` on TCR2 (equal). When it fires the pin goes high if mode = 4, and
  match2 = capture + `pulse_width` on TCR1.
* Match2 drives the pin low, re-arms match1 at the next cycle's start angle, and raises the
  channel IRQ.
* HSR1 = init, HSR2 = update angle/PW (`FUN_00050f40`, ch 4+cyl), HSR3 = disable (pin low),
  HSR4 = enable.

**Injection is "start-of-injection angle + time"**, not end-of-injection. The eTPU applies
both values to the next cycle as given, with no recalculation on the eTPU side.

Channel 31 uses the same function with width 1000 ticks (100 µs) for knock window timing
(`knock_schedule_next_window(0x1f, angle, 1000)`).

## F3 — spark (coils ch 18–23, plus ch 17)

Params: `+0x00 dwell_angle`, `+0x04 spark_angle`, `+0x08 max_dwell_time` (TCR1, 0 = off).

* Match1 at the dwell angle (TCR2) drives the pin **high** (coil charging). The next match1
  is at the spark angle with OPAC "low" (fire). If `max_dwell_time ≠ 0`, match2 =
  dwell-start + max dwell forces the pin low early (dwell limiter).
* At fire the IRQ goes to `etpu_cylN_fire_handler`. Pending angles are latched, and the next
  dwell start is armed.
* HSR2 (e4, `FUN_00050ed0`) is a **safe angle update**. `angle_in_window()` checks the new
  dwell/spark angles against the current TCR2 so that an update cannot skip or double-fire a
  spark. HSR3 parks the channel with the pin low (done right after init in `init_etpu`).
* Channel 17 runs F3 with `0 / 100` angles, and the CPU steps its angles through a table
  (`0x000BDD08`). It acts as an **angle-synchronous CPU interrupt** (`etpu_ch17_isr`) rather
  than driving a coil.

## F4 — PWM (alternate entry encoding, ETCS = 1)

Params: `+0x00 period` (b0 holds the flag copy), `+0x04 high_time`, `+0x08/+0x0C` new
period/high time. FM0 selects polarity and FM1 selects TCR1/TCR2.

* HSR 6/7 = init (the CPU uses 7).
* HSR 2/3 = immediate duty update. `eTPU_calculate_and_set_channel_value` writes
  `+0x04 = period × duty/10000` directly.
* HSR 4/5 = coherent period+duty change at the next period.

0% and 100% duty are handled by setting OPAC instead of generating a 0-width edge.

## F5 — period measurement (ch 3)

The function counts `edges_per_meas` edges (edge polarity comes from params b0 bit P24/P25),
stores the start and end TCR1 timestamps, and optionally fans out channel links (FM1).
Init: HSR7 (TCR1) or HSR6 (TCR2). `eTPU_update_period_and_frequency` (main loop) converts it
to `DAT_40001848 = 1e7 / period` (Hz) and `DAT_40001828 = period/10` (µs).
**Open question:** the CPU takes the period from param `+0x14`, which this microcode never
writes. The ch 3 physical signal and its consumer have not been identified.

## F6 — dual-match pulse (test / priming)

On HSR4, match1 = now + `delay1` and match2 = now + `delay2` (TCR1). The pin actions come from
params b0 (bits select high/low/toggle/none for each match). b0 bits P28/P29 enable an IRQ on
each edge. `eTPU_init_single_shot_pulse(ch, t)` temporarily reassigns an injector or coil
channel to F6 with OPAC config 0x34 (pin high at delay1 = 0, low at delay2 = t). This is used
for injector priming and the OBD mode-2F actuator tests.

## F8 — cam edge capture (ch 1, 2, 13, 14)

On any edge: `+0x00` = TCR2 (crank angle of the edge), `+0x04` = TCR1 time (b0 = edge counter
saturating at 4), `+0x09` = pin state, then the CPU IRQ. All VVT phase measurement and cam
sync logic runs on the CPU. Channel mapping (from which `vvt_*_position_*` handler reads
which channel): **ch 2 = inlet bank 1, ch 1 = inlet bank 2, ch 13 = exhaust bank 1,
ch 14 = exhaust bank 2.**

## Unused functions

* **F2 (0xBB0–0x16AC)** is a larger injector-style function. It keeps its own state in params
  +0x4C/+0x50, polls with a 0.5 ms (5000-tick) timer, uses MDU division by an rpm reference,
  and implements start/end/trim-pulse logic (`sub_0dc8` extends the pulse if the pulse width
  grows after start). No CPU code assigns CFS 2 in any Evora variant. It looks like a leftover
  of a more complex injection strategy.
* **F7 (0x1C4C–0x1ECC)** accumulates pulse width or period over N edges (`count_max`), then
  publishes the result to `+0x14` and raises an IRQ (Freescale PPA-like). Nothing assigns
  CFS 7.

## Disassembler notes and caveats

* The encoding comes from the preliminary ETPURM Rev 1 (2004). The MPC5534 has an eTPU1, so
  this is the right ISA. Decoding is self-consistent across the whole image: branch targets
  land on code, MDU busy-waits are correct, and the dispatch tables and delay slots make
  sense.
* `[delay]` marks branches and returns with FLS = 1. The following instruction always
  executes.
* `END` marks the end of a thread. `.8hi` marks an 8-bit access to the top byte of a
  parameter (where these functions keep state and flag bytes).
* Entry conditions (which event or flag combination selects which entry) are printed as
  `F#.e##`. Mapping entry numbers to events needs Table 7-1/7-2 of the manual (standard
  scheme for all functions except F4).
* The names in `T6_GLOBALS` / `T6_REGIONS` / `SUB_NAMES` in `etpudis.py` are my
  interpretation. Edit them as understanding improves.
