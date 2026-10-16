# NA091 definition correction ledger

This review pairs the `B13200091` C export with `T6-V00BU_defs.xml` using the
symbol inventory's [CAL metadata](B13200091-symbols.csv#L3512). The baseline is
`donour/master_t6e` commit `90c318032c40e835ca077f076beef94c12f86cca`.
Conclusions below follow exported arithmetic and XML/CSV metadata; they are not
validation of an original executable, calibration image, or installed vehicle.

The patch changes presentation in 23 XML root entries. It preserves table
addresses, dimensions, ROM identities, stored axes and XML CRLF line endings.
Calibration offsets use RAM base `0x40008E24`; learned-data offsets use
[`LEA_base = 0x40002D40`](B13200091-symbols.csv#L2685).

## Applied corrections

Offsets are hexadecimal offsets within the indicated CAL or LEA image. The CSV
links establish exported addresses; several historical CSV types still disagree
with the arithmetic and must not override the corrected XML.

| Image / offsets | Correction | Exported evidence |
|---|---|---|
| CAL `0262` | Vehicle limit: `x` becomes `2*x km/h`. Document raw 255's no-limit context and conditional enforcement. | [C target multiplied by 200](B13200091.c#L55103), [CSV address](B13200091-symbols.csv#L3917) |
| CAL `45D4`, `45D5`, `45DA` | Advisory thresholds: `4*x+500` becomes `5*x+500 RPM`; manual/IPS five-cell arrays identify gears 2–6. | [C five-RPM arithmetic](B13200091.c#L56854), [gear-to-cell selection](B13200091.c#L56684), [CSV family](B13200091-symbols.csv#L4724) |
| CAL `45EF`, `45F0` | Downshift idle margin and RPM offset: generic counts become `5*x RPM` differences, without a 500 RPM bias. | [C differences](B13200091.c#L56920), [CSV addresses](B13200091-symbols.csv#L4740) |
| CAL `45E4`, `45E6` | Maximum candidate-gear RPM and manual speed offset gain direct RPM and km/h units, respectively. Values retain identity scaling. | [C RPM comparison](B13200091.c#L56863), [speed multiplied by 100](B13200091.c#L56827), [CSV addresses](B13200091-symbols.csv#L4730) |
| CAL `45B0`, `45BC`, `45C8` | Six gear ratios: generic counts become `x/10 rpm/(km/h)`; replace voltage axes with gears 1–6. | [C centikph-to-RPM equation](B13200091.c#L56836), [family selection](B13200091.c#L56678), [CSV family](B13200091-symbols.csv#L4721) |
| CAL `0206`, `452E`, `4532`, `4536` | Four airbox pairs identify lower/upper RPM boundaries. The primary Tour pair also gains RPM units. No electrical-polarity or physical-valve-position claim is added. | [C hysteresis and coding](B13200091.c#L22444), [Tour address](B13200091-symbols.csv#L3848), [remaining addresses](B13200091-symbols.csv#L4634) |
| CAL `005A` | Replace false voltage labels with six cylinder-array entries. Existing offset-binary quarter-degree scaling remains unchanged. | [C signed-XOR trim](B13200091.c#L18312), [CSV address/type](B13200091-symbols.csv#L3557) |
| CAL `01E8`, `01EA` | Fuel-learning STFT thresholds: `int16` / `x/20` becomes `uint16` / `(x-32768)/20 %`; inverse is `x*20+32768`. | [C signed word after XOR 0x8000](B13200091.c#L28237), [CSV addresses](B13200091-symbols.csv#L3829) |
| CAL `0083`, `0084`, `0085` | Remove one attribute-identical duplicate scaling record from each thermal filter. Preserve `/2560` conversion and alternative-unit records elsewhere. | [C filter arithmetic](B13200091.c#L17638), [CSV coefficients](B13200091-symbols.csv#L3589) |
| LEA `0576`, `0986` | Two A/C-on learned-idle corrections: unsigned raw mg/s becomes signed `x*100/1024 mg/s`, matching the existing off entry. | [C signed interpolation](B13200091.c#L29214), [fixed-point airflow use](B13200091.c#L29746), [hot address](B13200091-symbols.csv#L2701), [cold address](B13200091-symbols.csv#L2717) |

The [NA regression tests](../../../romraider-defs/tests/test_na091_definition.py)
check address metadata, independent bitwise encoding oracles, full 8-/16-bit
arithmetic domains, semantic axes, unchanged entry counts, alternative units and
CRLF preservation. Nine tests passed. An independent before/after comparison
confirmed unchanged addresses, dimensions, ROM identities and stored axes.

## Injector-guide reconciliation

The [guide's governing equation](TuningInjectors.md#L23) now states that LTFT and
STFT add to the same pre-trim pulse, with separate integer divisions in C.
Deadtime and the selected learned microsecond offset enter afterward. This
follows the [pulse composition](B13200091.c#L18904), rather than a product of two
successive trim factors.

The [learning section](TuningInjectors.md#L352) distinguishes a pre-update bound
test from post-update saturation. C checks the current offset and then adds or
subtracts a whole step, allowing up to `step-1` integer microseconds of overshoot
from an in-bounds state. Whether an equal learning limit and DTC threshold can be
crossed depends on the reachable update grid and monitor gates. See the
[learning update](B13200091.c#L28241) and [DTC conditions](B13200091.c#L28460).

The historical [duplicate CSV labels at RAM 0x40008EE1/2](B13200091-symbols.csv#L3642)
remain intact. Current XML maps CAL `00BD` to the injector-offset step and `00BE`
to `sensor: pps unknown1`. C has distinct consumers: the former changes learned
offsets in microseconds; the latter applies
`gain*(zero-measured)/256` to pedal-zero learning, subject to track-specific
floors. See [pedal-zero learning](B13200091.c#L38518). This resolves the C/XML
meaning, while the original instruction-to-address binding remains unverified.
Neither the ledger nor the updated guide establishes stock byte values.

The [pulse-limit discussion](TuningInjectors.md#L579) now describes the actual
160-microsecond minimum and approximately full-cycle-minus-250-microsecond
maximum. It no longer infers that a clamp is unreachable from example deadtime
values. See [pulse clamping and duty calculation](B13200091.c#L18919).

## Regeneration and remaining binary checks

After a fresh Ghidra export, use the reviewed metadata reconciliation workflow
in [the definition README](../../../romraider-defs/README.md) and
[`reconcile_reviewed_metadata.py`](../../../romraider-defs/reconcile_reviewed_metadata.py).
It restores an explicit allowlist by exact ROM identity and offset from canonical
XML; it does not modify CSV or establish machine-code correctness. Historical
CSV types and the BD/BE labels are not silently rewritten by this ledger.

Matching original binaries or analysis projects are still needed to verify:

- Absolute address/operand binding, especially the BD/BE historical labels and
  signed/unsigned loads behind offset-binary and learned-idle values.
- Actual calibration contents, axis ordering/monotonicity, file identity and the
  checksum/editing workflow. No calibration image was edited or validated.
- Ambiguous GSI duplicate labels/units, unrelated generated axes and generic
  gain/timer labels. The patch does not assign units by name alone.
- Active coding, installed wiring, actuator polarity/response and task timing,
  which require appropriate runtime or bench evidence as well as static review.

Aligning the Ghidra/exporter annotations remains useful: explicit five-RPM
threshold/difference types, the two-km/h limit, tenths-RPM-per-km/h ratios,
offset-binary STFT thresholds, signed learned-idle airflow and named
gear/cylinder/hysteresis axes would prevent regeneration drift. Preserve the
legitimate implicit ADC voltage grids; they are not generic placeholders merely
because they use static axes.
