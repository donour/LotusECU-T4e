# Firmware Information

- **Module:** BOSCH ESP8 ABS and stability control
- **Platform:** Lotus Evora 400, GT410, GT430, and GT
- **Processor:** Texas Instruments TMS470 (ARM7TDMI core)
- **RTOS:** ETAS ERCOSEK 4.1.10 (real-time OS for automotive ECUs)
- **Instruction set:** ARM Thumb mode (instructions always little-endian per ARM spec)
- **Data endianness:** **BIG-ENDIAN** — confirmed by pointer table analysis: 32-bit values at 0x291A4–0x291B8 decode to valid RAM addresses (0x0040xxxx) only in big-endian byte order. The TMS470 ARM7TDMI is configured for big-endian data access (BE-32 mode).
- **Firmware ID:** `Bosch.CSDE.Lotus_ESP8.01.001`
- **Part number:** `A132J0314A` at 0x8064
- **Internal ID:** `68638V0201` (matches BB68638 V0201)
- **Build:** 2015-05-21 11:18:49, tool `CCC`, user `nol5kor`
- **Compiler:** TI TMS470 C/C++ compiler (ARM7TDMI target, ERCOSEK integration)
- **Wheelbase:** 2.575 m (Lotus Evora)
- **Yaw rate sensor:** External Bosch cluster, received on CAN 0x303
- **No hardware FPU:** All math is fixed-point integer. `__aeabi_idiv(a,b)` → quotient in r0.
  - **FIXED:** Run `FixEabiIdiv.py` to correct the Ghidra prototype from `long long` to `int`.
    This eliminates all `extraout_r1/r2/r3/r12` register artifacts in the decompilation.
    See Ghidra Project Workflow section for the headless command.

---

## Firmware File & Memory Layout

**File:** `PRJ_CodeBlock_BB68638_V0201_ECC_CSW_S.hex` (Intel HEX, 2.1 MB)
**Decompilation:** `PRJ_CodeBlock_BB68638_V0201_ECC_CSW_S.hex.c` (95,752 lines)
**Binary size:** 753,648 bytes (0xB7FF0)
**Address range:** 0x00008000 – 0x000BFFEF

### Memory Map

The firmware is a **single monolithic image** — no separation between program code and calibration data. All 12 × 64 KB segments are contiguous with zero 0xFF gaps:

```
0x00008000 – 0x0000FFFF  (32 KB)   Code / init / low-level helpers
0x00010000 – 0x0001FFFF  (64 KB)   Main code
0x00020000 – 0x0002FFFF  (64 KB)   Vehicle dynamics + yaw PI
0x00030000 – 0x0003FFFF  (64 KB)   ESP controller + mu estimator
0x00040000 – 0x0004FFFF  (64 KB)   ABS state machine + hydraulics
0x00050000 – 0x0005FFFF  (64 KB)   CAN subsystem + sensors
0x00060000 – 0x0006FFFF  (64 KB)   CAN TX scheduler + helpers
0x00070000 – 0x0007FFFF  (64 KB)   Additional code
0x00080000 – 0x0008FFFF  (64 KB)   Dynamics loop + CAN processing
0x00090000 – 0x0009FFFF  (64 KB)   Additional code
0x000A0000 – 0x000AFFFF  (64 KB)   Build metadata + diagnostic strings
0x000B0000 – 0x000BFFEF  (64 KB)   FW ID string + integrity data
```

### Firmware End Markers

```
0x000BFFD0: 3E 8A 99 2B  BA 9B 27 C3  AA 66 22 10
0x000BFFDC: 74 0A 8C 3B  C2 E2 C8 C2  2B BF 81 28  ← possible 192-bit signature
0x000BFFE8: B6 B6 B6 B6  B6 B6 B6 B6                    ← Bosch 0xB6 fill pattern
```

### Vector Table (Secondary)

The vector table at 0x8000 is a **secondary table** — all entries are ARM `B` (branch) instructions that redirect to the real exception handlers at addresses **below 0x8000** (outside this image). The primary bootloader + ERCOSEK kernel reside at 0x0000–0x7FFF, which is **not included** in this hex file.

### Calibration Regions (Embedded)

| Region | Address | Utilization |
|--------|---------|-------------|
| Wheel Slip Cal | 0x15000–0x16000 | 87% (3560/4096 bytes) |
| Traction/Stability Cal | 0x1B000–0x1C000 | 82% (3364/4096 bytes) |
| ABS Control Cal | 0x47000–0x48000 | 85% (3480/4096 bytes) |

Calibration is **not in a separate flash sector** — it is interleaved with code. Updating calibration alone requires either a partial reflash (if supported by the bootloader) or a full image rebuild.

---

## Reprogramming Architecture

### Bootloader

The bootloader is **NOT in this image**. It resides at addresses below 0x8000 (likely 0x0000–0x7FFF) in a protected flash sector. The bootloader handles:

- Power-on self-test (POST)
- Flash programming/erasing via UDS over CAN
- Integrity verification of the application image before launch
- Diagnostic session management (default → programming → extended)

### Diagnostic Protocol

| Layer | Standard |
|-------|----------|
| Physical | CAN bus (500 kbps) |
| Transport | ISO-TP (ISO 15765-2) |
| Diagnostic | UDS (ISO 14229-1) |
| Bootloader | UDS 0x10 (Programming Session) → 0x27 (SecurityAccess) → 0x34/0x36/0x37 (Flash Download) |
| CAN IDs | **0x7E2** (request), **0x7EA** (response) — ISO 15765-4 physical addressing for chassis/ABS. Functional broadcast: **0x7DF**. Engine ECU uses 0x7E0/0x7E8. **Needs experimental verification** — CAN IDs configured by ERCOSEK COM stack at build time, not visible in application code. |

### Integrity Verification

- **No CRC16/CRC32 polynomials** found in the application image
- Verification is handled by the **bootloader** (not in this image)
- The 24 bytes at 0xBFFD0–0xBFFE7 (before Bosch 0xB6 padding) are likely a **192-bit hash or digital signature** verified by the bootloader before launching the application
- The build string `68638V020100000000CCC` includes what appears to be a checksum/toolchain marker (`CCC`)

### Can Calibration Be Updated Separately?

**Probably not** in practice. Since calibration is interleaved with code (no separate flash sectors):
1. A full application reflash is the standard procedure
2. The bootloader *may* support partial flashing at known calibration offsets, but this requires the original toolchain (`CCC`) to recalculate the integrity signature
3. The build system produced a single `.hex` file containing both code and calibration

### Security Access for Reprogramming

The diagnostics security system protects programming operations. See the **Diagnostic Security Architecture** section below for full details. In brief:
- Enter programming session: `10 02`
- Request seed: `27 01` → fixed seed `11 22 33 44`
- Compute key via SBOX at `0xB8530`: `D0 BD 6D 67`
- Send key: `27 02 D0 BD 6D 67`
- Unlock confirmed: `67 02`
- Then use WriteMemoryByAddress (0x3D) or WriteDataByLocalId (0x3B) for calibration changes

---

## Diagnostic Security Architecture (KWP2000/UDS)

The ABS application firmware implements a KWP2000 (ISO 14230) diagnostic layer with SecurityAccess (0x27) protection. The reprogramming primitives (0x34/0x36/0x37) are **not in this image** — they live in the bootloader at <0x8000. The application handles session management, service dispatch, and security unlock.

### Service Dispatch Table

**SID table at `0xB90DC`** (15 supported services, terminated by `0xC0`):

```
Offset:  00  01  02  03  04  05  06  07  08  09  0A  0B  0C  0D  0E
Value:   10  1A  27  21  3B  17  18  31  32  33  14  3D  3E  23  2E
```

**Permission mask table at `0xB90EC`** (one mask byte per SID, same index):

| # | SID | Mask | Service | Session/Security Required |
|---|-----|------|---------|--------------------------|
| 0 | 0x10 | 0xFD | StartDiagnosticSession | All sessions |
| 1 | 0x1A | 0x7D | ReadEcuIdentification | Programming + Extended session |
| 2 | **0x27** | **0x5D** | **SecurityAccess** | **Programming session only** |
| 3 | 0x21 | 0xD7 | ReadDataByLocalId | Default + Programming, SecLevel1 |
| 4 | **0x3B** | **0x77** | **WriteDataByLocalId** | **Programming + Extended, SecLevel1** |
| 5 | 0x17 | 0x51 | ReadStatusOfDTC | Programming, SecLevel1 |
| 6 | 0x18 | 0xF1 | ReadDtcByStatus | All sessions, SecLevel1 |
| 7 | 0x31 | 0x50 | StartRoutineByLocalId | Programming, SecLevel1 |
| 8 | 0x32 | 0x82 | StopRoutineByLocalId | Default session |
| 9 | 0x33 | 0x83 | RequestRoutineResults | Default session |
| 10 | 0x14 | 0x84 | ClearDiagnosticInformation | Default session |
| 11 | 0x3D | 0x85 | WriteMemoryByAddress | Default session |
| 12 | 0x3E | 0x86 | TesterPresent | Default session |
| 13 | 0x23 | 0x90 | ReadMemoryByAddress | Default, SecLevel1 |
| 14 | 0x2E | 0x91 | WriteDataByCommonId | Default, SecLevel1 |

**Permission mask bit encoding** (typical Bosch convention):
- Bit 7 (0x80): Allowed in default session
- Bit 6 (0x40): Allowed in programming session (0x02)
- Bit 5 (0x20): Allowed in extended session (0x03)
- Bit 4 (0x10): Allowed in supplier session
- Bits 3–0: Required security level flags

**Key observations:**
- **SecurityAccess (0x27) is only available in the programming session** — you cannot unlock from the default session; send `10 02` first
- **WriteDataByLocalId (0x3B)**, used for Variant/Process Byte recoding, is available in programming and extended sessions **after** SecurityAccess unlock
- TesterPresent (0x3E) requires no security level — can be used to keep any session alive

### Diagnostic Handler Functions

The service handlers are referenced in a table at `0xB9164` (9 handlers, format: `{uint16 param, uint16 handler_addr_low}` — full address = `0x0005xxxx`):

| # | Handler | Address | Purpose (inferred) |
|---|---------|---------|-------------------|
| 0 | — | 0x56BBD | WriteDataByLocalId handler |
| 1 | — | 0x56BAF | Routine control handler |
| 2 | — | 0x56BA1 | ReadDataByLocalId handler |
| 3 | — | 0x56AC1 | ReadEcuIdentification handler |
| 4 | — | 0x56B35 | StartRoutineByLocalId handler |
| 5 | — | 0x56B27 | ReadDtcByStatus handler |
| 6 | — | 0x56AB3 | TesterPresent handler |
| 7 | — | 0x56BCB | SecurityAccess — sendKey handler |
| 8 | — | 0x56BE1 | SecurityAccess — requestSeed handler |

**Main diagnostic state machine:** `FUN_00052fec` @ 0x52FEC
**Security permission checker:** `FUN_00068306` @ 0x68306
**SecurityAccess sub-function dispatch:** area around 0x55AF4–0x55C20

### Session Configuration

Session type records at `0xB9150` define which diagnostic sessions are supported and their properties:

| Record | Session | Properties |
|--------|---------|------------|
| `02 00 01 01` | Type 0x02 | Default security level = 1 |
| `03 99 01 01` | Type 0x03 | Extended session variant |
| `02 50 01 01` | Type 0x02 | Programming session variant |

All three reference RAM address `0x400057F9` for session state.

### Negative Response Codes (NRCs) Used

The following KWP2000 NRCs are referenced as immediate values in the diagnostic code:

| NRC | Name | Used at |
|-----|------|---------|
| 0x10 | generalReject | 0x525D6, 0x530F3, 0x531F9, 0x53C81, 0x54B03, 0x56CDA, 0x56D8E |
| 0x11 | serviceNotSupported | (handled via SID table lookup failure) |
| 0x12 | subFunctionNotSupported | 0x539BF, 0x539C7, 0x54CEB, 0x556E7, 0x556F1 |
| 0x13 | incorrectMessageLength | 0x52D31, 0x5446D, 0x54487, 0x5598F, 0x5663B |
| 0x14 | responseTooLong | 0x52E9E, 0x52EA8 |
| 0x21 | busyRepeatRequest | 0x5572D, 0x5621D, 0x563BF |
| 0x22 | conditionsNotCorrect | 0x52DC2, 0x52DDE, 0x54C25, 0x556FD |
| 0x24 | requestSequenceError | 0x53031, 0x554EF, 0x556EF, 0x560B6 |
| 0x25 | noResponseFromSubnet | 0x550CD, 0x556E5 |
| **0x33** | **securityAccessDenied** | **0x52954, 0x53C6F** |
| **0x34** | **requiredTimeDelayNotExpired** | **0x5342F, 0x54C31, 0x54C6D, 0x55687, 0x556AD, 0x556C7, 0x55739, 0x55751, 0x557C1** |
| **0x35** | **invalidKey** | **0x52CDD, 0x54C5F, 0x5569F, 0x5570F, 0x55745, 0x557B5, 0x55825** |
| **0x36** | **exceedNumberOfAttempts** | **0x54C53, 0x55699, 0x55709, 0x5573F, 0x557AF, 0x5581F** |
| 0x37 | requiredTimeDelayNotExpired (alt) | 0x54CE7 |
| 0x78 | responsePending | 0x549D0, 0x54A92, 0x54AE0, 0x54C18, 0x5537C, 0x56E86, 0x56EF4, 0x56F96 |

The cluster of NRCs 0x33/0x34/0x35/0x36 near the SecurityAccess handler (0x54Cxx, 0x556xx, 0x557xx) confirms these areas implement the security state machine with:
- Attempt counter tracking (NRC 0x36 when max attempts exceeded)
- Delay timer enforcement (NRC 0x34 when too soon after failed attempt)
- Key validation (NRC 0x35 on mismatch, 0x67 on success)
- Access denial when security not unlocked (NRC 0x33)

### SecurityAccess Algorithm — SBOX at 0xB8530

A **256-byte permutation table** at `0xB8530` is the seed→key transformation:

```
SBOX[0x00]=0x00  SBOX[0x01]=0x1D  SBOX[0x02]=0x3A  SBOX[0x03]=0x27
SBOX[0x04]=0x74  SBOX[0x05]=0x69  SBOX[0x06]=0x4E  SBOX[0x07]=0x53
SBOX[0x08]=0xE8  SBOX[0x09]=0xF5  SBOX[0x0A]=0xD2  SBOX[0x0B]=0xCF
SBOX[0x0C]=0x9C  SBOX[0x0D]=0x81  SBOX[0x0E]=0xA6  SBOX[0x0F]=0xBB
SBOX[0x10]=0xCD  SBOX[0x11]=0xD0  SBOX[0x12]=0xF7  SBOX[0x13]=0xEA
...
SBOX[0xFC]=0xFE  SBOX[0xFD]=0xD9  SBOX[0xFE]=0xC4  SBOX[0xFF]=0xC4
```

**Properties:**
- Full permutation: all 256 byte values 0x00–0xFF appear exactly once
- **XOR-linear**: SBOX[a ⊕ b] = SBOX[a] ⊕ SBOX[b] for all a, b
- SBOX[0x00] = 0x00 (zero maps to zero)
- GF(2) basis: SBOX[0x01]=0x1D, SBOX[0x02]=0x3A, SBOX[0x04]=0x74, SBOX[0x08]=0xE8, SBOX[0x10]=0xCD, SBOX[0x20]=0x87, SBOX[0x40]=0x13, SBOX[0x80]=0x26

Since SBOX is XOR-linear, the transformation is equivalent to an 8×8 matrix multiplication over GF(2): **key_byte = M × seed_byte**, where the columns of M are the SBOX basis vectors above. The complete 256-byte table is available at this address — read `data[0xB8530 + seed_byte]` to get the key byte.

### Fixed Security Seed

At `0xB92F8` there is a SecurityAccess configuration record:

```
Offset:  F8  F9  FA  FB  FC  FD  FE  FF  00  01  02  03  04  05  06  07
Hex:     03  00  03  01  11  22  33  44  00  0B  92  FC  00  34  04  00
```

Structure interpretation:
- `0xB92F8–0xB92F9`: `03 00` — record header (length=3, flags=0)
- `0xB92FA–0xB92FB`: `03 01` — SecurityAccess Level 3, sub-function 1 (requestSeed)
- **`0xB92FC–0xB92FF`: `11 22 33 44`** — **fixed 4-byte seed** (byte sequence, big-endian as stored in flash)
- `0xB9300–0xB9303`: `00 0B 92 FC` — **self-referential pointer** back to the seed data

This means the ECU uses a **fixed seed** of `0x44332211` for SecurityAccess Level 3.

Applying the SBOX transformation to this seed:
- SBOX[0x11] = 0xD0
- SBOX[0x22] = 0xBD
- SBOX[0x33] = 0x6D
- SBOX[0x44] = 0x67

**Expected key: `D0 BD 6D 67`** (byte sequence as stored in flash / sent on CAN)

### Practical Unlock Sequence

```
Step 1: Enter programming session
  Send:  10 02
  Recv:  50 02 (or 50 02 xx xx xx xx with P2 timing)

Step 2: Request seed (SecurityAccess Level 1)
  Send:  27 01
  Recv:  67 01 11 22 33 44   ← fixed seed

Step 3: Compute key via SBOX
  key[0] = data[0xB8530 + seed[0]] = data[0xB8541] = 0xD0
  key[1] = data[0xB8530 + seed[1]] = data[0xB8552] = 0xBD
  key[2] = data[0xB8530 + seed[2]] = data[0xB8563] = 0x6D
  key[3] = data[0xB8530 + seed[3]] = data[0xB8574] = 0x67

Step 4: Send key
  Send:  27 02 D0 BD 6D 67
  Recv:  67 02                  ← security unlocked

Step 5: Protected operations (e.g., recoding)
  Send:  3B xx yy zz ...
```

### Security State Machine

The security subsystem tracks:

| RAM Address | Purpose |
|-------------|---------|
| `0x400068A8` | Security state — attempts counter, delay timer, current level |
| `0x400057C4` | Security level currently active (0 = locked, 1+ = unlocked) |
| `0x400067C2` | Diagnostic flags — referenced by SecurityAccess config record |
| `0x4000676F` | Diagnostic timer — used for inter-attempt delay enforcement |
| `0x400057F9` | Session configuration — current diagnostic session state |

The state machine enforces:
- **Maximum attempts**: After N consecutive invalid keys → NRC 0x36, must restart session
- **Delay timer**: After a failed attempt → NRC 0x34 if retried too quickly (~10 seconds typical)
- **Session gating**: SecurityAccess only accepted in programming session
- **Level escalation**: Higher security levels require successful unlock at lower levels first

### Security-Related Function Map

| Address | Function | Role |
|---------|----------|------|
| 0x52FEC | `diag_state_machine` | Main KWP2000 request dispatcher |
| 0x68306 | `security_permission_check` | Validates service against session + security level |
| 0x54BF6 | `security_access_handler` | Handles 0x27 — dispatches requestSeed/sendKey |
| 0x56BE1 | `security_request_seed` | Generates/fetches seed for SecurityAccess |
| 0x56BCB | `security_send_key` | Validates received key against expected |
| 0x55AF4 | `security_subfunc_dispatch` | Sub-function dispatch for 0x01 (seed) vs 0x02 (key) |
| 0x56AB2 | `write_data_by_local_id` | Handles 0x3B — Variant/Process Byte recoding |
| 0x54CB8 | `security_compute_expected_key` | Computes expected key from seed (SBOX algorithm) |

### Diagnostic RAM Layout

| Address | Size | Purpose |
|---------|------|---------|
| `0x4000C062` | — | Diagnostic state struct (main) |
| `0x4000CC57` | — | Diagnostic state struct (secondary) |
| `0x4000266A` | — | Diagnostic state struct (tertiary) |
| `0x400057F9` | — | Current session configuration |
| `0x400068A8` | — | Security access state (attempts, delay, level) |
| `0x400057C4` | — | Active security level |
| `0x4000676F` | — | Diagnostic timer/counter |
| `0x400067C2` | — | Diagnostic flags/status |
| `0x400061C2` | — | Variant/process byte data |
| `0x40006B22` | — | Bootloader/diagnostic interface data |

---

## ERCOSEK RTOS

The string `ERCOSEK V4.1.10 TMS_470 (c)ETAS Apr 27 2004` at 0x9833F reveals the firmware runs on **ETAS ERCOSEK**, an OSEK/VDX-compliant real-time operating system widely used in Bosch automotive ECUs.

### Implications

- **CAN driver:** ERCOSEK COM stack (I-PDU based, not user-visible CAN ID registers). This is why CAN mailbox configuration cannot be found in the application code — it's handled by the OS COM layer.
- **Task scheduling:** ERCOSEK alarms and events drive the multi-rate task structure.
- **SWI calls:** `software_interrupt(N)` calls are ERCOSEK OS service requests (ActivateTask, SetEvent, etc.), not direct CAN peripheral access.
- **Flashing:** Handled by the ERCOSEK FlashLoader or a Bosch-proprietary bootloader at <0x8000.

---

## CAN Messages

### CAN ID 0xA2 — Front Wheel Speeds (7 bytes)

**Direction:** ABS → ECU, Cluster | **Rate:** ~10 ms (100 Hz)
**Builder:** `can_tx_build_front_wheel_speeds_0xA2` @ 0x0005b7b0 *(likely)*

```
Byte:    [0]        [1]        [2]      [3]        [4]        [5]        [6]
      |------RF------||----LF----|        |----LF----||-----Car Speed-----||Cnt|Chk|
```

| Signal    | Formula                                                              | Bits   |
|-----------|----------------------------------------------------------------------|--------|
| LF Wheel  | `(byte[1] & 0x3F) << 8 \| byte[3]`                                  | 14-bit |
| RF Wheel  | `((byte[1] & 0xC0) >> 6) \| ((byte[0] & 0x0F) << 10) \| (byte[1] << 2)` | 14-bit |
| Car Speed | `((byte[0] & 0xF0) >> 4) \| (byte[4] << 4) \| ((byte[6] & 0x03) << 12)` | 14-bit |
| Counter   | `(byte[6] & 0x3C) >> 2`                                              | 4-bit  |
| Checksum  | `XOR(bytes[0:5])` — stored in byte[6] upper bits                     | 8-bit  |

Speed scaling (engine ECU receiver side — NOT an ABS parameter): `kph = ((raw * 0x32) >> 3) * CAL_wheel_speed_multiplier / 1000`
Invalid sentinel: `0x3FFF` (16383) = wheel speed unavailable

### CAN ID 0xA4 — Rear Wheel Speeds (6 or 8 bytes)

**Direction:** ABS → ECU, Cluster | **Rate:** ~10 ms (100 Hz)
**Builder:** `can_tx_build_rear_wheel_speeds_0xA4` @ 0x0005d9d0 *(confirmed)*

```
Byte:    [0]        [1]        [2]      [3]        [4]          [5]
      |------RR------||----LR----|        |----LR----|  |BrkSw|     |Checksum|
```

| Signal       | Formula                                                              | Bits   |
|--------------|----------------------------------------------------------------------|--------|
| LR Wheel     | `(byte[1] & 0x3F) << 8 \| byte[3]`                                  | 14-bit |
| RR Wheel     | `((byte[1] & 0xC0) >> 6) \| ((byte[0] & 0x0F) << 10) \| (byte[1] << 2)` | 14-bit |
| Brake Switch | `byte[4] & 0x03`                                                     | 2-bit  |
| Counter      | `(byte[0] & 0xF0) >> 4`                                              | 4-bit  |
| Checksum     | `XOR(bytes[0:4])` — stored in byte[5]                                | 8-bit  |

Brake switch: 0=released, 1=pressed, 2=fault, 3=reserved
8-byte variant: bytes[6:7] = additional data (`abs_unused_field`)

### CAN ID 0xA8 — ESP/ABS Status (6 bytes)

**Direction:** ABS → ECU, Cluster | **Rate:** ~10 ms (100 Hz)
**Builder:** `can_tx_build_esp_status_0xA8` @ 0x00062f0c *(likely)*
**Data prep:** `can_tx_prepare_slot7_esp_status` @ 0x0003ff90

| Signal              | Bit Position                    | Description                    |
|---------------------|---------------------------------|--------------------------------|
| ESP Active          | `byte[1]` bit 3                 | ESP intervention active        |
| ABS Active          | `byte[1]` bit 5                 | ABS intervention active        |
| ESP Warning         | `byte[3]` bit 6 (mask `0x40`)   | ESP warning/error flag         |
| Status Flag 2       | `byte[3]` bit 4 (mask `0x10`)   | Additional status indicator    |
| Brake Pressure Low  | `byte[2]` bits 0–1              | Hydraulic pressure status      |
| Flag Field 2        | `byte[2]` & 0x07                | 3-bit status field             |

### CAN ID 0x85 — Steering Angle Sensor (SAS)

**Direction:** SAS → ABS (receive) | **RX Handler:** `can_rx_steering_angle_dispatcher` @ 0x0005bce0
**TX Init:** `can_tx_init_steering_angle_0x85` @ 0x00060c16
**Data Processor:** `can_steering_angle_receive_handler` @ 0x00032658
**Slew Limiter:** `steering_angle_slew_rate_limiter` @ 0x0006ca94

RX dispatcher gate: `can_id_byte >= 0x84 && can_id_byte < 0x86` → handles CAN IDs 0x84 and 0x85.
Parser layout descriptor: `0x111`. Max message length: `0x140`.
Slew rate limit: ±0x42 per cycle, stored at `struct+0xa4`.

### CAN IDs Not Yet Located

| CAN ID | Source | Content | ABS Handler |
|--------|--------|---------|-------------|
| 0x102  | ECU    | Torque data (Alpha-N net, combustion Nm) | Unknown |
| 0x303  | Yaw Sensor | Yaw rate, lateral acceleration | Unknown (one of FUN_00066118 or FUN_0006f1e8) |
| 0x114  | ECU    | Tachometer, pedal, drivetrain mode | Not used by ABS? |

CAN mailbox configuration is handled by the ERCOSEK COM stack, not visible in application code.

---

## CAN Subsystem Architecture

### CAN RX Handlers

Three handlers call `can_message_parser`:

| Handler | Address | Parser Arg | CAN IDs |
|---------|---------|------------|---------|
| `can_rx_steering_angle_dispatcher` | 0x5bce0 | `0x111` | 0x84, 0x85 (confirmed) |
| `FUN_00066118` | 0x66118 | `DAT_00066194` | Unknown (sets status 0xA5) |
| `FUN_0006f1e8` | 0x6f1e8 | `0x111` | Unknown (same layout as steering) |

### CAN TX Scheduling

`can_tx_scheduler` @ 0x00063040 calls 9 slot preparation functions in sequence:

| Slot | Function | Address | Notes |
|------|----------|---------|-------|
| 1 | `can_tx_prepare_slot1` | 0x6c9fc | 2-word copy |
| 2 | `can_tx_prepare_slot2` | 0x693b8 | 4-channel data prep |
| 3 | `can_tx_prepare_slot3` | 0x5e8d4 | 2-channel data prep |
| 4 | `can_tx_prepare_slot4` | 0x665a0 | → FUN_000703e0 |
| 5 | `can_tx_prepare_slot5` | 0x65340 | |
| 6 | `can_tx_prepare_slot6` | 0x57424 | **STUB** — empty return |
| 7 | `can_tx_prepare_slot7_esp_status` | 0x3ff90 | ESP status → likely 0xA8 |
| 8 | `can_tx_prepare_slot8` | 0x65d90 | |
| 9 | `can_tx_prepare_slot9` | 0x67068 | |

### CAN Helper Functions

| Function | Address | Purpose |
|----------|---------|---------|
| `can_message_parser` | 0x6acb8 | Parse CAN message using bit-layout descriptor |
| `can_message_validity_check` | 0x6a6cc | Validate CAN message freshness/checksum |
| `can_message_checksum_verify` | 0x6a6be | XOR checksum verification |
| `can_signal_range_check` | 0x5bcc8 | Check CAN signal within valid range |
| `can_data_copy_prepare` | 0x5e2d8 | Copy data from ESP struct to CAN buffer |
| `can_tx_permission_check` | 0x6421c | Gate before CAN transmission |
| `pack_12bit_unsigned` | *(library)* | Pack unsigned value into bitfield |
| `pack_4bit_counter` | *(library)* | Pack 4-bit rolling counter |

CAN TX is triggered via `software_interrupt(7)` and `software_interrupt(6)` — ERCOSEK OS service calls that invoke the CAN COM stack.

---

## Key Functions (Ghidra-Named)

All names below are applied in the Ghidra project. See `apply_names.txt` and `apply_can_names.txt` for the full naming files.

### Vehicle Dynamics & ESP

| Name | Address | Role |
|------|---------|------|
| `vehicle_dynamics_model` | 0x28dcc | Bicycle model reference yaw rate + understeer gradient |
| `esp_yaw_stability_controller` | 0x32aa8 | Yaw error thresholding, brake correction outputs |
| `main_dynamics_loop` | 0x6486c | Main vehicle dynamics loop (calls all below) |
| `lateral_sensor_yaw_channel_update` | 0x460f0 | Yaw channel sensor data processing |
| `road_surface_mu_estimator` | 0x3cce4 | Road surface friction (mu) estimation (Q9 format) |
| `stability_flag_checker` | 0x5f194 | Stability condition / flag checker |
| `stability_flag_monitor` | 0x69718 | Stability flag monitoring |
| `stability_prefilter` | 0x6dbb8 | Stability pre-filter |
| `stability_calculation` | 0x4cf28 | Stability calculation helper |
| `yaw_channel_deviation_check` | 0x5af20 | Yaw channel deviation check |
| `steering_angle_slew_rate_limiter` | 0x6ca94 | Steering angle slew-rate limiter (±0x42/cycle) |
| `can_steering_angle_receive_handler` | 0x32658 | Process received steering angle data |
| `lookup_1d_linear_interpolation` | 0x6dcc8 | 1D linear interpolation (lookup table helper) |

### Dynamics Loop Call Order (`main_dynamics_loop` @ 0x6486c)

```
dynamics_pre_processing()              @ 0x3b7e0
lateral_sensor_yaw_channel_update()    @ 0x460f0
dynamics_unknown_helper()              @ 0x6ed78
vehicle_dynamics_model()               @ 0x28dcc   ← KEY
wheel_speed_confidence_weights()       @ 0x21ad4
dynamics_unknown2()                    @ 0x57fd2
wheel_axle_force_processing()          @ 0x38954
stability_flag_monitor()               @ 0x69718
yaw_channel_deviation_check()          @ 0x5af20
brake_pressure_distribution()          @ 0x2f8a4
stability_flag_checker()               @ 0x5f194
dynamics_stub()                        @ 0x72a1c   (empty return)
pre_controller_state_update()          @ 0x2a038
stability_prefilter()                  @ 0x6dbb8
esp_yaw_stability_controller()         @ 0x32aa8   ← KEY
electronic_differential_controller()   @ 0x3d458
pressure_distribution_manager()        @ 0x34714
wheel_differential_monitor()           @ 0x5fa3c
```

### ABS State Machine

| Name | Address | Role |
|------|---------|------|
| `abs_state_machine` | 0x476a4 | ABS state machine, 4-wheel channels |
| `abs_wheel_processing` | 0x475b8 | Per-wheel ABS processing |
| `abs_state_update` | 0x475e0 | ABS state transition update |
| `abs_common_processing` | 0x47674 | Common ABS processing |
| `abs_wheel_handler` | 0x47680 | Individual wheel handler |
| `abs_state_action` | 0x4c810 | ABS state action execution |
| `abs_initialization` | 0x4c970 | ABS initialization |
| `abs_finalization` | 0x4c984 | ABS finalization |
| `abs_completion` | 0x4ca18 | ABS completion |

### Wheel Speed & Slip

| Name | Address | Role |
|------|---------|------|
| `calculate_wheel_speed_differentials` | 0x147d8 | Differential speed calculation |
| `wheelslip` | 0x148ec | Wheel slip calculation |
| `validate_wheel_speed_sensors` | 0x14d40 | Sensor validity checking |
| `wheel_speed_aggregator` | 0x20358 | Cross-wheel speed statistics |
| `wheel_speed_confidence_weights` | 0x21ad4 | Sensor confidence weighting |
| `wheel_accel_calculate` | 0x6cb2c | Wheel acceleration calculation |
| `wheel_accel_update` | 0x6cb88 | Wheel acceleration update |
| `traction_or_stability_sense` | 0x1ae18 | Traction/stability mode selection |
| `electronic_differential_controller` | 0x3d458 | Electronic diff control |
| `pressure_distribution_manager` | 0x34714 | Brake pressure distribution |
| `calculate_wheel_brake_pressure` | 0x31254 | Per-wheel brake pressure calc |
| `esp_hydraulic_control_update` | 0x312e8 | Hydraulic control update |

### Helpers

| Name | Address | Role |
|------|---------|------|
| `comparator_with_deadband` | 0x1be10 | Hysteresis comparator |
| `saturate_add_byte` | 0x6c7b8 | Saturating byte addition |
| `enable_flag` | 0x41200 | Set flag bit |
| `clear_bit` | 0x4120c | Clear flag bit |
| `find_first_bitfield_zero` | 0x413ee | Find first zero in bitfield |
| `zero_out_ptr_fields` | 0x26170 | Initialize pointer fields to NULL |
| `initialize_two_16bit_arrays` | 0x2618e | Array initialization |
| `math_operation_helper` | 0x6e7a8 | Math helper |

---

## Vehicle Dynamics Model — Bicycle Model / Steering Gradient

**Function:** `vehicle_dynamics_model___` @ `0x28DCC` (line 33511), called from `main_dynamics_loop` @ `0x6486C` line 83052. **14 sequential phases**, fully traced from decompiled code. See `YAW_CONTROL_ANALYSIS.md` §2 for full variable/calibration map.

### Global Data Structures

| Symbol | Role |
|--------|------|
| `vehicle_state_ptr` (`DAT_000291a4`) | Main vehicle dynamics state vector |
| `yaw_pi_state_ptr` (`DAT_000291a8`) | Yaw PI integrator state array (short[22+]) |
| `calibration_param_block_ptr` (`DAT_000291ac`) | Pointer to calibration parameter block (RAM 0x400022C4) |
| `lateral_force_accumulator_ptr` (`DAT_000291b0`) | Lateral force accumulator (residual after steering subtraction) |
| `filtered_lateral_accel_ptr` (`DAT_000291b4`) | Filtered lateral acceleration (low-pass, τ≈4 samples) |
| `K_ref` (`DAT_000291b8`) | Reference stability gain (≈1.0 in Q-format, used directly as value) |
| `wheelbase_geometry_cal_table_ptr` (`DAT_000293dc`) | **Wheelbase L** = 2575 mm (0x0A0F), used as direct value |
| `wheelbase_comparison_value` (`DAT_000293d8`) | Wheelbase sign-check comparison value |
| `road_surface_coupling_coefficient` (`DAT_000293e0`) | Road surface coupling coefficient |
| `tire_lateral_stiffness` (`DAT_000293e4`) | Tire lateral stiffness for gain adaptation |
| `speed_offset_steering_gain_schedule` (`DAT_000293e8`) | Reference speed for steering gradient adaptation |
| `min_steering_angle_correction_limit` (`DAT_000293ec`) | Lower clamp for steering angle correction |
| `velocity_normalized_steering_rate_constant` (`DAT_000293f0`) | Velocity-normalized steering rate constant |
| `steering_angle_normalization_table` (`DAT_000293f4`) | Steering angle normalization table (8 entries) |
| `output_correction_table_base` (`DAT_000293f8`) | Output correction table: +0x2e=lateral force correction, +0x3a=steering correction |
| `yaw_rate_to_lateral_force_scale_factor` (`DAT_00029358`) | Yaw rate → lateral force scale factor |
| `yaw_measured_ptr` (`DAT_0002935c`) | Pointer to measured yaw rate (from CAN 0x303 sensor) |
| `yaw_filtered_bicycle_model_ptr` (`DAT_00029360`) | Pointer to filtered reference yaw rate |

### vehicle_state offsets (base = DAT_000291a4)

| Offset | Type | Content |
|--------|------|---------|
| +0x00 | int[4] | Lateral force accumulators ([0]=front raw, [1]=front ref, [2]=rear raw, [3]=rear ref) |
| +0x18 | ushort | Front lateral force neutral-steer reference |
| +0x19 | ushort | Rear lateral force neutral-steer reference |
| +0x1f | short | Normalized front output (Phase 14) |
| +0x20 | short | Normalized intermediate output (Phase 14) |
| +0x22 | short | **Steering angle δ** (from CAN 0x85, slew-rate limited) |
| +0x26 | int | **Effective steering angle** (tire-corrected, used in ψ_ref = v×δ/L) |
| +0x2a | short | **Yaw error output** (>0 = oversteer, <0 = understeer) |
| +0x2e | short | Lateral force correction (Phase 11 output) |
| +0x3a | short | Steering angle correction (Phase 12 output) |
| +0x5e | short | Lateral acceleration from sensors |
| +0x62 | ushort | Rear axle lateral force measured |
| +0x7a | short | Normalized output channel (Phase 14) |
| +0x7e | short | Normalized output channel (Phase 14) |
| +0x82 | short | Normalized output channel (Phase 14) |
| +0xa2 | short | Lateral path curvature **1/R** |
| +0xb6 | ushort | **Vehicle speed v** |
| +0xc4 | char | **Steering direction counter** (signed byte, −25…+24) |
| +0xd9 bit0 | — | Steering correction active flag |

### yaw_pi array channels (base = DAT_000291a8, short[])

| Index | Alias | Content |
|-------|-------|---------|
| [0] | — | Speed denominator: `speed_raw + 576` |
| [6] | `psVar8` | Front axle yaw PI integrator |
| [7] | `psVar9` | Rear axle yaw PI integrator |
| [8] | — | Sign-extended copy of [6] (9-bit) |
| [9] | `psVar10` | Reference yaw rate PI integrator |
| [10] | `puVar11` | Raw speed channel input |
| [0xc] | — | Normalized rear yaw output (Phase 14) |
| [0x15] | — | Status word 1 (ESP state flags) |
| [0x16] | — | **Status word 2 — mode gate flag for steering adaptation** |
| [0x17] | — | **Status byte — mode gate flag for steering adaptation** |
| [0x2b] | — | Flag byte: bit 6 = steering correction override |

### Calibration Block Offsets (base = *DAT_000291ac)

| Offset | Symbol | Physical Meaning |
|--------|--------|------------------|
| +0x04 | **Cf** | Front cornering stiffness |
| +0x06 | **Cr** | Rear cornering stiffness |
| +0x40 | Rear steer coeff | Steering angle → rear lateral force conversion |
| +0x170 | Front steer coeff | Steering angle → front lateral force conversion |
| +0x3a8 | Front tire stiffness | Tire cornering stiffness (front) |
| +0x3c4 | Front axle lateral cal | Lateral force calibration factor |
| +0x3d2 | **Max lateral force dev** | Clamp limit for lateral force deviation (≈978) |
| +0x1fa | Output scaling factor | Used in `FUN_0003dfb6` for axle differential output |

### Verified Phase-by-Phase Algorithm

**Phase 1** (lines 33604-33605) — Steering feed-forward subtraction from lateral force accumulators using cal[0x170] (front) and cal[0x40] (rear).

**Phase 2** (lines 33606-33607) — Lateral acceleration low-pass filter: `filtered += (raw − filtered) >> 2`, τ ≈ 4 samples.

**Phase 3** (lines 33608-33629) — Front & rear lateral force deviation from neutral reference, clamped to ±cal[0x3D2].

**Phase 4** (lines 33630-33639) — Front stability factor: `speed_gain = 589824 / (speed + 576)`, `Kus_f_v² = speed² / Cf`, `stab_gain_f = K_ref / ((Kus_f_v² + 4096) >> 16)`. Equivalent to `K_ref / (1 + Kus_f × v²)`.

**Phase 5** (lines 33640-33644) — Rear stability factor, identical using Cr.

**Phase 6** (lines 33645-33661) — Minimum gain floor from steering counter: 69 below |counter|=12, linear ramp `(|cnt|−12)×46/13 + 69` above.

**Phase 7** (lines 33662-33664) — Yaw error as lateral force residual: `yaw_err_force = scale × (yaw_measured − yaw_ref) / speed`.

**Phase 8** (lines 33665-33677) — Front PI update: `yaw_pi[6] += speed_gain × (stab_gain_f × scaled_front − yaw_pi[6]) >> 10`.

**Phase 9** (lines 33678-33692) — Rear PI update with effective wheelbase sign handling.

**Phase 10** (lines 33693-33709) — **Reference yaw rate**: `L_eff = 2575 − 101 = 2474 mm`, `ψ_ref = v × δ_eff / L_eff`, PI-filtered with gain 287/1024 (τ ≈ 36 ms). Path curvature and oversteer/understeer indicator output at `vehicle_state[+0x2a]`.

**Phase 11** (lines 33718-33737) — Speed-dependent gain adaptation: low speed uses average, high speed uses tire stiffness scaling. Outputs filtered lateral force correction at `output_correction_table+0x2e` and path curvature `1/R` at `vehicle_state[+0xa2]`.

**Phase 12** (lines 33738-33841) — **MODE-DEPENDENT steering gradient adaptation**:

**Gate** (line 33743): `if ((yaw_pi[0x17] | yaw_pi[0x16]) >> 5 & 1) == 0) goto skip;`

| Mode | Gate | Behavior |
|------|------|----------|
| **Tour** | Flag=0 → gate passes → adaptation **SKIPPED** | Conservative reference yaw, tighter understeer bias |
| **Sport** | Flag=1 → gate blocks → adaptation **RUNS** | Speed-dependent correction applied, more permissive |

When adaptation runs: `correction = ((v−v_ref)/32)² / 207 + 24`, clamped to 78. Updates steering correction at `output_correction_table+0x3a` and steering direction counter at `vehicle_state[+0xc4]` (−25…+24).

**Phase 13** (lines 33843-33846) — Diagnostic override: `yaw_pi[0x2b]` bit 6 resets steering counter and correction.

**Phase 14** (lines 33847-33863) — Normalize all PI channels by cornering stiffness using `steering_angle_normalization_table`, producing dimensionless outputs at `vehicle_state[+0x1f, +0x7a, +0x7e, +0x20, +0x82]` and `yaw_pi[0xc]`.

### Mode-Dependent Oversteer: Complete Chain

The bicycle model is the FIRST of three mode-dependent layers:

1. **Bicycle model (this section):** Steering gradient adaptation gated → Sport mode produces more permissive reference yaw rate
2. **`FUN_0003dfb6`:** Mode change swaps per-wheel calibration tables (EDL/slip parameters, not Cf/Cr)
3. **`esp_yaw_stability_controller`:** Mode gates sensor-based correction and torque reduction escalation

All three layers contribute to "more oversteer allowed in Sport mode."

---

## ESP Yaw Stability Controller — Oversteer/Understeer Thresholds

**IMPORTANT:** The oversteer threshold (+2004) and understeer threshold (−2003) are **hardcoded compile-time immediate values** in the code, not calibration constants. They cannot be changed without patching the firmware. However, the `sensor_based_correction_scaling` (0x32F5C), `negative_yaw_correction_limit` (0x32F64), and `positive_yaw_correction_limit` (0x32F68) are data values read from flash and COULD be patched. Even these are only used in **Tour mode** (mode==0) — they are skipped entirely in Sport/Race/TC_Off.

| Symbol | Role | Used When |
|--------|------|-----------|
| `yaw_sensor_state_struct` (`DAT_00032df8`) | Yaw sensor state structure base (contains mode at +0x16) | All modes |
| `yaw_measured_ch1_ptr` (`DAT_00032df0`) | Pointer to measured yaw rate channel 1 | All modes |
| `yaw_measured_ch2_ptr` (`DAT_00032df4`) | Pointer to measured yaw rate channel 2 | All modes |
| `yaw_correction_brake_pressure_output` (`DAT_00032e8c`) | Calibration/output array (brake pressure outputs) | All modes |
| `max_corrective_yaw_rate_numerator` (`DAT_00032e90`) | Max corrective yaw rate (numerator) | All modes |
| `DAT_00032e8c[0x17]` | Speed-normalized yaw limit divisor | All modes |
| `yaw_error_thresholds[0]` (`0x32F0C`) | **Oversteer** threshold = +2004 (hardcoded) | All modes |
| `yaw_error_thresholds[1]` (`0x32F10`) | **Understeer** threshold = −2003 (hardcoded) | All modes |
| `esp_intervention_permission_byte` (`DAT_00032f48`) | ESP intervention permission byte | All modes |
| `yaw_rate_magnitude_intervention_threshold` (`DAT_00032f58`) | Yaw rate magnitude intervention threshold (3391) | All modes |
| `sensor_based_correction_scaling` (`DAT_00032f5c`) | Scaling for sensor-based correction (1697) | **Tour only** |
| `negative_yaw_correction_limit` (`DAT_00032f64`) | Negative yaw correction limit (4714) | **Tour only** |
| `positive_yaw_correction_limit` (`DAT_00032f68`) | Positive yaw correction limit (6600) | **Tour only** |

Brake correction outputs:
- `puVar5[3]` = base brake pressure for yaw correction
- `puVar5[1]` = differential brake pressure between axles
- `_yaw_sensor_ + 0x1e` bit3 = stability correction counter exceeded (sustained intervention)

**ESP intervention gate** (line 41096):
```c
// Gate condition — intervention only if permission bit set AND yaw error large enough
if ((((uVar2 >> 1 | uVar2) & (*DAT_00032f48 >> 2)) >> 3 & 1) == 0) goto skip;
// Min yaw rate threshold:
*(short *)(DAT_00032f68 - 0x76)  // = DAT_00032f68 - 118 = min |yaw_err| for intervention
```
- `*DAT_00032f48` = permission byte; bit 5 must be set (after >> 2, bit 3 is tested)
- `DAT_00032f68 - 118` = minimum yaw rate error for intervention (calibration constant)

---

## Stability Control Gating

### Outer Gate — main_dynamics_loop (line 83035)

```c
// Run all vehicle dynamics only if:
//   bit 5 of (DAT_00064984 + 0x2b) == 0  (disable flag clear)
//   OR *DAT_0006497c < 0                   (diagnostic override active)
if (((*(byte *)(DAT_00064984 + 0x2b) >> 5 & 1) == 0) || (*DAT_0006497c < '\0')) {
    // Run full dynamics chain
}
```

| Symbol | Role |
|--------|------|
| `esp_main_state_struct_ptr` (`DAT_00064984`) | Pointer to main ESP state struct |
| `DAT_00064984 + 0x2b` bit 5 | Dynamics disable flag (1 = skip all dynamics) |
| `DAT_00064984 + 0x1a` | Short status (checked in "all inactive" condition) |
| `diagnostic_override_ptr` (`*DAT_0006497c`) | Diagnostic override char; if < 0 (bit 7 set), force-enable dynamics |
| `esp_status_flag_struct_ptr` (`DAT_00064980`) | Base pointer for status/flag struct |
| `DAT_00064980[0x14]` | Frame counter, 0–9 rollover (10-frame superloop) |
| `DAT_00064980[0x18]` bit 7 | "All channels inactive" flag — set when no active intervention |

"All inactive" conditions (all must be true):
- `pcVar1[0,1,4,5,0xb,0xc,0x12,0x16]` = 0 (8 flag bytes)
- `*(short *)(iVar2 + 0x1a) < 1`, `+0x1c < 1`, `+0x24 < 1`
- `*(short *)(iVar2 + 0x1e,0x20,0x22) >= 0` (3 signed values)

### Inner Gate — esp_yaw_stability_controller (line 41096)

Permission byte `*DAT_00032f48` bit 5 AND yaw rate exceeds `*(short *)(DAT_00032f68 - 118)`.

---

## Road Surface Mu (Friction) Estimator — `road_surface_mu_estimator` @ 0x3cce4

**Output** — `DAT_0003d048[0x17]` = mu in **Q9 format** (0x200 = 512 = 1.0 grip)

Fixed mu reference values:
| Hex | Q9 float | Condition |
|-----|----------|-----------|
| `0x6d` | ≈0.21 | Mode 1 (startup/init) |
| `0x31` | ≈0.096 | Minimum lower bound |
| `0x52` | ≈0.16 | Alternate lower bound |
| `0xda` | ≈0.43 | Mode 4 fixed (wet/damp) |
| `0x200` | 1.0 | Dry tarmac (no scaling) |

**Gate:** bit 2 of `*(byte *)(DAT_0003d04c + 0x3f)` — if clear, all outputs zeroed.

**Mode byte:** `*(char *)(DAT_0003d04c + 1)` (1–4):
- **Mode 1**: Fixed mu = 0x6d, lower bound = 0x21 (startup)
- **Mode 2**: Table lookup mu (normal); `DAT_0003d090` if slip detected
- **Mode 3**: Table lookup (different axle), `DAT_0003d090` if slip; `DAT_0003d08c` if large yaw
- **Mode 4**: Complex; 0xda or `DAT_0003d08c` or table lookup depending on gating

Slip detection: `*DAT_0003d060 * *DAT_0003d05c < 0` (longitudinal × lateral sign flip)

### Mu Calibration Constants

| Address | Role |
|---------|------|
| `mu_speed_lookup_table` (`DAT_0003d050`) | Speed-indexed mu lookup table (1D) |
| `mu_speed_index_input` (`DAT_0003d054`) | Speed index input for mu table |
| `low_surface_mu_fallback` (`DAT_0003d090`) | Low surface mu (fixed fallback when slip detected) — calibratable |
| `alternate_fixed_mu` (`DAT_0003d08c`) | Alternate fixed mu (used in modes 3/4) — calibratable |
| `mu_upper_limit` (`DAT_0003d078`) | Mu upper limit / ceiling |
| `lateral_accel_reference_lower_bound` (`DAT_0003d094`) | Lateral accel reference value for lower bound calculation |
| `mu_lower_bound_scaling_factor` (`DAT_0003d098`) | Scaling factor: lower_bound = 0x31 − \|Δaccel\| × DAT_0003d098 >> 10 |
| `mu_mode_threshold` (`DAT_0003d09c`) | Mode 2/4 threshold: if > 0 use 0x19a (410) else use DAT_0003d090 |
| `mu_longitudinal_factor_ptr` (`DAT_0003d060`) | Longitudinal factor for slip detection |
| `mu_lateral_factor_ptr` (`DAT_0003d05c`) | Lateral factor for slip detection |

---

## Wheel Speed Aggregator — `wheel_speed_aggregator` @ 0x20358

Reads 4 individual wheel state structs and computes cross-wheel statistics into a summary struct.

| Symbol | Role |
|--------|------|
| `wheel_state_ptr_LF/RF/LR/RR` (`DAT_00020b1c/20/24/28`) | Pointers to 4 wheel state structs |
| `wheel_summary_struct_ptr` (`DAT_00020b30`) | Summary/aggregate wheel speed struct |
| `wheel_speed_sentinel` (`DAT_00020b2c`) | Speed sentinel / invalid marker (0x1680 = 5760) |

Per-wheel speed fields (within each wheel struct):
- `+0x5b0` = one speed component
- `+0x5bc` = other speed component
- `+0x5a6`, `+0x5b4` = additional speed channels

Output in summary struct `DAT_00020b30` (short[]):
| Index | Content |
|-------|---------|
| `[0x16]` | Min of all 4 wheel speeds |
| `[0x17]` | Max of all 4 wheel speeds |
| `[0x18]` | Front lateral speed differential (\|LF − RF\|) |
| `[0x19]` | Rear lateral speed differential (\|LR − RR\|) |

Also sets `*(byte *)(wheel_struct + 0x3dd)` = `(+0x413 OR +0x271) >> 7` for each wheel (combined fault/status flag).

---

## Calibration Data Regions

The firmware is a monolithic image with code and calibration interleaved throughout. There are no pure calibration sections — the entire 0x8000–0xBFFF range is mixed. However, two regions contain structured calibration records:

### ABS Control Calibration (0x47000–0x47200)

Structured as 8-byte records: `[CalID:u16] [Param1:u16] [Param2:u16] [Param3:u16]`

CalID values use a 0x7xxx enumeration scheme. Key records identified:

| Offset | CalID | Param1 | Param2 | Param3 | Description |
|--------|-------|--------|--------|--------|-------------|
| 0x000 | `0x7C49` | 2680 | 4129 | 4416 | Wheel slip calibration |
| 0x008 | `0x794A` | 4728 | 2627 | 977 | ESP threshold calibration |
| **0x010** | **`0x7949`** | **320** | 8578 | 992 | **Axle differential clamp** |
| 0x018 | `0x217C` | 2080 | 2115 | 8308 | Speed threshold |
| 0x020 | `0x7648` | 120 | 8310 | 30280 | Minimum speed validation |
| 0x050 | `0x724D` | 10360 | 265 | 9171 | Additional threshold |
| 0x0A0 | `0x6349` | **320** | 24888 | — | Second axle diff reference |

The CalID enumeration descends through the table: 0x7C, 0x79, 0x76, 0x75, 0x74, 0x73, 0x72, 0x71, 0x70, 0x6F, 0x67, 0x5E, 0x5D, 0x5B, 0x5A, 0x59, 0x57, 0x56, 0x55, 0x54, 0x53, 0x52, 0x51, 0x50, 0x4F, 0x4E, 0x4D, 0x4C, 0x4B, 0x4A, 0x49, 0x48, 0x47, 0x46, 0x45, 0x42, 0x3F, 0x3E, 0x3C, 0x3B...

After 0x471A0 the structure changes to ID/value pairs: `[ID:u16] [Value:u16]`.

### Wheel Slip Calibration (0x15000–0x16000)

This region is primarily **code** (Thumb instructions), not pure calibration data. The "87% utilized" figure from earlier analysis reflects instruction density, not calibration entries. Some calibration constants are embedded as immediate values within the code.

### RAM Pointers (0x15300–0x15400)

A table of 32-bit pointers to runtime RAM structures at `0x4000xxxx`. These are populated by the bootloader's data initialization at startup. The actual calibration values at those RAM addresses are initialized from the structured records in the ABS Control Cal region via lookup by CalID.

### To Modify Calibration Values

The calibration records at 0x47000+ can be patched directly in the hex file:
- Each record is identified by its CalID (first u16)
- The three parameters follow
- Changing a parameter requires recalculating the firmware integrity signature (24 bytes at 0xBFFD0–0xBFFE7)

**Specific values for wheel size changes:**
- **0x47012**: Axle diff clamp = 320 → increase to 400–500 for more tolerance
- **0x470A4**: Second reference to 320 → may also need adjustment
- **0x46CF8**: Third reference to 320 (mode-dependent table)
- **0x46D04**: Fourth reference to 320 (mode-dependent table)
- **0x4700A**: 4728 (ESP yaw threshold)
- **0x4700E**: 977 (related ESP threshold)

---

## Drive Mode Processing

The ABS receives the drive mode (Tour/Sport/TC_Off/Race) from the ECU via CAN 0x114. **The oversteer/understeer detection thresholds (+2004/−2003) are hardcoded compile-time constants and do NOT change per mode.** Instead, the mode changes the **intervention response** — what the ESP does after the threshold is exceeded.

In Tour mode (mode == 0), the ESP applies a full intervention with sensor-based brake pressure correction and engine torque reduction escalation. In Sport/Race/TC_Off (mode != 0), that additional correction block is skipped — reducing brake pressure, disabling sustained torque cut, and allowing more driver-controlled slip.

**Full details in** `YAW_CONTROL_ANALYSIS.md` Appendix E.

### Mode Dispatcher — `FUN_0006d228` @ 0x6d228

Dispatches on a received CAN byte at `DAT_0006d2b4`:

| Byte | Mode | Action |
|------|------|--------|
| `0x10` (16) | Race | Calls `FUN_0003dfb6()`, stores 0x10, sets status bit 7 |
| `0x08` (8) | Sport | Calls `FUN_0003dfb6()`, stores 0x08, sets status bit 6 |
| `0x01` (1) | TC_Off | Calls `FUN_0003dfb6(arg)`, stores 0x01, sets status bit 5 |
| (none) | **Tour** | Mode = 0, no special processing → full ESP intervention |

### Mode in ESP State Struct

The ESP state struct at `PTR_DAT_00032df8` contains:
- **`+0x16`**: `mode` byte (uint8_t) — received drive mode
- **`+0x17`**: `field20_0x17` (uint8_t) — second mode byte

These are combined into a 16-bit value checked in `esp_yaw_stability_controller` @ 0x32AA8, line 41221:

```c
mode_16bit = (esp_obj_unknown->mode) | (esp_obj_unknown->field20_0x17 << 8);
if (mode_16bit == 0) {
    // TOUR MODE — Full ESP intervention:
    //   1. Sensor-based correction scaling (DAT_00032f5c=1697, 0x32F60, 0x32F64, 0x32F68)
    //   2. Additional brake pressure = speed_term + scaled_yaw + limit
    //   3. Intervention counter increments (1 or 2 per cycle)
    //   4. After 39 cycles (~390 ms): torque_request_flags |= 8 (sustained torque cut)
    //   5. ECU cuts throttle/retards ignition → aggressive oversteer suppression
}
// else: SPORT/RACE/TC_OFF — lines 41224-41266 SKIPPED entirely
//   → No extra brake pressure correction
//   → No counter escalation
//   → No sustained engine torque reduction (bit 3 never set)
//   → Only base brake intervention + mild torque flag (bit 0)
```

**Key insight:** The oversteer/understeer thresholds (+2004/−2003 at `int32_t_ARRAY_00032f0c`) are applied identically in ALL modes — they sit BEFORE the mode check in the code flow (lines 41059-41071). The mode only gates the additional correction block. In Tour mode, the ESP both brakes a wheel AND cuts engine power; in Sport mode, it only brakes a wheel. This is why Sport mode "allows more oversteer" — the driver keeps engine power through the slide.

### Torque Reduction Flags (Struct Offset +0x1e → CAN 0xA8)

| Bit | Set Condition | Mode-Dependent? | Effect |
|-----|---------------|-----------------|--------|
| 0 | `intervention_magnitude >= DAT_00032f58` (3391) | **No** — all modes | Mild torque reduction during ESP |
| 3 | Intervention counter > 39 cycles | **Yes** — Tour only | Aggressive torque cut |

### Mode-Dependent Threshold Processing — `FUN_000469f0` @ 0x469f0

Processes mode-specific data at struct `DAT_00046ca0`:
- `+0x276`: mode/status word — bit 2 (0x04) set when output > 11, bit 10 (0x0400) controls gating
- `+0x277`: additional flags — bit 7 enables alternate output
- `+0x248`: persistence counter (max 0x26 = 38 decimal)
- `+0xea`: primary processed output (ESP intervention magnitude modifier)
- `+0x104`: alternate output (used when +0x277 bit 7 set)
- `+0x15a`, `+0x160`, `+0xe`: speed-dependent scaling inputs

Called from `FUN_000720e8` @ 0x720E8 (part of a periodic task gated by `FUN_00069b78`).

### Axle Diff Clamp — Mode-Specific Locations

The value **320** (0x0140) appears at 4 calibration addresses, suggesting per-mode axle diff limits:

| Address | Context |
|---------|---------|
| `0x47012` | ABS Control Cal record `0x7949`, param 1 |
| `0x470A4` | ABS Control Cal record `0x6349`, param 1 |
| `0x46CF8` | Mode processing table (near `DAT_00046ca0`) |
| `0x46D04` | Mode processing table (near `DAT_00046ca0`) |

All four currently hold 320 — stock calibration uses the same limit for all modes. To add mode-dependent tolerance (e.g., more slip allowed in Sport/Race), adjust individual entries.

---

## Wheel Speed Fault Detection — Axle Differential Plausibility Check

This subsystem is the root cause of the ABS fault that triggers when rear tire diameter differs significantly from front. The ABS expects front and rear axles to rotate at approximately the same speed, and faults when the axle differential exceeds a calibrated threshold for too long.

### Fault Detection Chain

Called from `FUN_0001509c` (the main wheel speed validation coordinator), executed once per cycle:

```
FUN_0001509c:  Set up validation parameters & thresholds
  → calculate_wheel_speed_differentials @ 0x147d8   computes axle + side differentials
  → wheelslip @ 0x148ec                              computes slip ratio
  → FUN_00014978 @ 0x14978                          slip threshold check → sets +0x50 bit 6
  → FUN_000149e0 @ 0x149e0                          sensor plausibility → sets +0x50 bits 3-4
  → FUN_00014c18 @ 0x14c18                          speed-dependent checks
  → FUN_00014cb8 @ 0x14cb8                          fault persistence counter increment
  → validate_wheel_speed_sensors @ 0x14d40          per-wheel fault @ +0x412 bit 7
  → FUN_00014f8c @ 0x14f8c                          counter > threshold → global fault
```

### Axle Differential Calculation (`calculate_wheel_speed_differentials`)

Takes four wheel speed values from `DAT_00015358/5c/60/64` (LF, RF, LR, RR):

```c
axle_diff = ((LR_speed + RR_speed) - (LF_speed + RF_speed)) / 2;  // stored at DAT_00015354[0]
side_diff = ((RF_speed + RR_speed) - (LF_speed + LR_speed)) / 2;  // stored at DAT_00015354[1]
// Both clamped to ±0x140 (320 units)
```

Low-pass filtered (τ ≈ 32 samples) and stored at:
- `DAT_0001536c + 0x2e`: filtered axle differential
- `DAT_0001536c + 0x30`: filtered side differential

### Fault Register Layout (base = `DAT_0001536c`)

**`+0x50` — 16-bit fault flags:**
| Bit | Mask | Meaning |
|-----|------|---------|
| 0 | `0x0001` | Validation active |
| 3 | `0x0008` | Sensor plausibility fault |
| 4 | `0x0010` | Sensor mismatch fault |
| 5 | `0x0020` | **Global speed sensor fault** (ABS warning light) |
| 6 | `0x0040` | Slip/differential exceeds threshold |
| 11 | `0x0800` | ESC/ESP intervention active |
| 12 | `0x1000` | ABS intervention active |

**`+0x51` — byte fault register:**
| Bits | Mask | Meaning |
|------|------|---------|
| 7-6 | `0xC0` | `0xC0` = all sensors OK, `0x80` = partial fault, `0x40` = all matched |

**Per-wheel fault flags (4 wheel structs at DAT_00015334/38/3c/40):**
| Offset | Bit | Meaning |
|--------|-----|---------|
| `+0x410` | `0x100` | Sensor fault pending |
| `+0x410` | `0x2000` | Fault escalated (ABS warning) |
| `+0x410` | `0x8000` | Cleared each validation cycle |
| `+0x412` | `0x80` (bit 7) | **Sensor error** — set when fault confirmed |
| `+0x578` | `< 0` (negative) | Sensor invalid flag |
| `+0x40c` | `< 0x5a` (90) | Speed too low to validate |

### Fault Persistence Counter (`FUN_00014cb8` @ 0x14cb8)

```c
struct fault_counter {
    short count;         // DAT_00015380[0]  — persistence counter
    short field_1;       // DAT_00015380[1]
    ushort flags_0x12;   // DAT_00015380[0x12] — 0x4000=active, 0xC0=fault state
    // ...
};

// Counter logic:
if (fault_conditions_active) {
    if (flags_0x12 & 0xC0 == 0x80 || extra_flag) {
        count += 1;   // slow increment
    } else {
        count += 2;   // fast increment
    }
} else {
    if (count < 200) {
        count = 0;    // reset
    } else {
        count -= 200; // rapid decay
    }
}
```

### Fault Escalation (`FUN_00014f8c` @ 0x14f8c)

When `DAT_00015380[0]` (persistence counter) exceeds `DAT_0001538c` (threshold):
1. All 4 wheels: `+0x410 |= (((uVar2 | uVar2 >> 7) & 0x100) << 5)` → propagates to bit `0x2000`
2. If all 4 wheels have `0x2000` clear at `DAT_0001539c/a0/a4/a8`: set `+0x50 |= 0x20` → **ABS fault**

### What Causes the "Rear Tires Smaller" Fault

When rear tires have a smaller diameter than fronts:
1. Rear wheels rotate faster → `LR_speed + RR_speed > LF_speed + RF_speed`
2. `axle_diff = ((rear_sum) - (front_sum)) / 2` goes positive
3. If `|axle_diff| > threshold` consistently → `FUN_00014978` sets `+0x50 bit 6`
4. `FUN_00014cb8` increments persistence counter (`+1` or `+2` per cycle)
5. Counter exceeds `DAT_0001538c` → `FUN_00014f8c` escalates
6. `+0x50 bit 5 (0x20)` set → **ABS warning light on**

### Calibration Points for Wheel Size Changes

To prevent the fault with different tire diameters, modify these calibration values:

| Symbol | Address | Role |
|--------|---------|------|
| `DAT_00015370[3]` | calibration region | Slip threshold — compared against filtered slip at `+0x2a` |
| `DAT_00015370[4]` | calibration region | Minimum reference value for slip check |
| `DAT_00015370[5]` | calibration region | Secondary threshold for slip detection |
| `DAT_0001538c` | calibration region | **Fault counter threshold** — increase to require longer persistence before fault |
| `DAT_00015390` | calibration region | Minimum speed to enable validation |
| Axle diff clamp | code constant at `0x140` (320) in `calculate_wheel_speed_differentials` | Maximum axle differential — **increase this** to allow more variance |

### Speed Scaling Functions

**`FUN_00070fb8` @ 0x70fb8** — Raw sensor value filter:
```c
uint FUN_00070fb8(int raw_speed) {
    if (47 < raw_speed) {                        // minimum speed threshold
        return (uint)(raw_speed * DAT_00070fe4) >> 16;  // scaling factor
    }
    return 0;  // below minimum → invalid
}
```
- `DAT_00070fe4` (RAM at 0x70FE4): scaling factor — initialized at boot from flash data
- Minimum threshold: 47 (raw sensor units)

**`FUN_0007105a` @ 0x7105a** — Two-mode speed conversion:
```c
short FUN_0007105a(ushort raw) {
    if ((raw & 0xa0) == 0xa0) {
        return raw * 20 - 3200;   // mode 1: scaled
    } else {
        return raw * 200;         // mode 2: direct
    }
}
```

### Engine ECU Wheel Speed Calibration (Separate Module)

**This section is about the ENGINE ECU (EFI Technology, MPC5534), NOT the ABS.**
It is included here for cross-reference when diagnosing wheel-speed-related ABS faults.

The engine ECU has per-axle calibration for converting received CAN speed values to physical km/h:
- `CAL_wheel_speed_multiplier_front` @ ECU RAM `0x4000cb46`, type `u16_distance_mm_div2`
- `CAL_wheel_speed_multiplier_rear` @ ECU RAM `0x4000cb48`, type `u16_distance_mm_div2`
- Formula: `kph = multiplier * ((raw_CAN_value * 50) >> 3) / 1000`

These ECU calibrations should be updated proportionally when changing tire diameters:
```
new_multiplier = old_multiplier × (new_circumference / old_circumference)
```

---

## Ghidra Project Workflow

### Project Location

- **Ghidra:** `~/Desktop/lotus/lotus_t6e/ghidra_11.4.2_PUBLIC/`
- **Project:** `~/Desktop/lotus/lotus_t6e/lotus_ecu/` → "Lotus ECU" (shared project)
- **Program:** `/PRJ_CodeBlock_BB68638_V0201_ECC_CSW_S.hex`
- **Scripts:** `disassembly/ghidra_scripts/` (in this repo)
- **Workspace:** `disassembly/evora/abs/`

### __aeabi_idiv Fix (CRITICAL — run first!)

Ghidra models `__aeabi_idiv` with 0 parameters and `__stdcall` convention by default,
preventing the decompiler from tracking data flow through division calls.

**Fix:** Run `FixEabiIdiv.py` to:
1. Add `int numerator, int denominator` parameters
2. Set calling convention to `default` (ARM EABI)
3. Enable custom variable storage

```bash
GHIDRA="/c/Users/donour/Desktop/lotus/lotus_t6e/ghidra_11.4.2_PUBLIC/support/analyzeHeadless"
$GHIDRA "$PROJECT_DIR" "Lotus ECU" -process "$PROGRAM" \
  -scriptPath "$SCRIPT_DIR" -postScript FixEabiIdiv.py -noanalysis
```

**What this fixes:** `__aeabi_idiv()` calls now show their arguments —
`speed_gain² / Cf` becomes `__aeabi_idiv(iVar12*iVar12, *(short*)(cal+4))`.

**What remains (Ghidra ARM decompiler limitation):** Return values still flow through
`extraout_r1`/`extraout_r3` variables. The compiler emits `MOV r1, r0` between
consecutive `__aeabi_idiv` calls to set up the next denominator; Ghidra loses
track of this register move and attributes r1's value as a call output.
**`extraout_r1` after a division IS the quotient** — it got there via `MOV r1, r0`.

### Key Scripts

| Script | Purpose |
|--------|---------|
| `FixEabiIdiv.py` | **Run first** — fix __aeabi_idiv/uidiv signatures for clean decompilation |
| `ProbeProgram.py` | Dump program metadata (memory blocks, function count, etc.) |
| `ApplyNamesFile.py <file>` | Apply function/data names from a text file |
| `DumpFuncSigs.py <dir>` | Export function signatures for cross-variant matching |
| `DumpTypedLabels.py <file>` | Export user-defined data labels |
| `ExportC.py` | Full decompilation export to C |
| `FindCanIds.py` | Search for CAN ID immediate values in disassembly |
| `CreateAndDump.py <addrs>` | Create functions at addresses and decompile them |

### ApplyNames File Format

```
<hex_address> <name>  # comment
```

One `<address> <name>` per line. Address can be hex (e.g., `0006486c`) or an existing symbol name.
Lines starting with `#` are comments. Blank lines are ignored.

### Headless Workflow

```bash
# Read-only access (server connection error is non-fatal):
GHIDRA="/c/Users/donour/Desktop/lotus/lotus_t6e/ghidra_11.4.2_PUBLIC/support/analyzeHeadless"
$GHIDRA "$PROJECT_DIR" "Lotus ECU" -process "$PROGRAM" -readOnly \
  -scriptPath "$SCRIPT_DIR" -preScript ProbeProgram.py -noanalysis

# Apply names (writable — save succeeds locally even with server offline):
$GHIDRA "$PROJECT_DIR" "Lotus ECU" -process "$PROGRAM" \
  -scriptPath "$SCRIPT_DIR" -preScript ApplyNamesFile.py "$NAMES_FILE" -noanalysis
```

### Naming Files in This Workspace

| File | Contents |
|------|----------|
| `apply_names.txt` | 106 core function + data label names |
| `apply_can_names.txt` | 38 CAN subsystem names |
| `typed_labels.tsv` | User-defined data labels (exported) |

### Current Project Stats

- **Total functions:** 2,056
- **Named functions:** ~84 (non-FUN_ prefix)
- **Named data labels:** ~47
- **Instructions:** 127,647

---

## Supporting Files in This Workspace

| File | Description |
|------|-------------|
| `CLAUDE.md` | This file — firmware reference and analysis notes |
| `CAN_MESSAGES.md` | Detailed CAN message bit-level documentation |
| `CAN_ANALYSIS_STATUS.md` | CAN subsystem analysis status and next steps |
| `CAN_DIAGNOSTICS_GUIDE.md` | **Practical CAN diagnostics & security unlock guide** |
| `YAW_CONTROL_ANALYSIS.md` | Full mathematical analysis of yaw stability control |
| `apply_names.txt` | Core function/data label names for Ghidra |
| `apply_can_names.txt` | CAN subsystem names for Ghidra |
| `analyze_firmware.py` | Python script for firmware binary analysis |
| `PRJ_CodeBlock_BB68638_V0201_ECC_CSW_S.hex` | Original firmware (Intel HEX) |
| `PRJ_CodeBlock_BB68638_V0201_ECC_CSW_S.hex.c` | Full Ghidra decompilation export (May 2026) |
