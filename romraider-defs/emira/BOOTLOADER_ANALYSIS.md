# Lotus Emira ECU Bootloader Analysis

## Firmware Structure

The `emirabinary.hex` file contains the complete firmware for the 2022 Lotus Emira V6 ECU (MPC5777 controller).

### Memory Map

Based on analysis of the hex file, the firmware has the following major sections:

#### Security/Certificate Section (Segment 0x0000)
- **0x00080000-0x00082000**: Firmware metadata and version information
  - Contains serial numbers: "2104531", "8892597367"
  - Version identifiers and build info

- **0x00090000-0x00098000**: **Certificate/Signature Data** (256 bytes)
  - Contains cryptographic signature/certificate used for firmware verification
  - Starts at line 146 of hex file with data: `C3F256CF00440257ABD7308076144D4A...`
  - This is the security certificate that the bootloader verifies

#### Bootloader Section (**FOUND**)
- **Location**: Segment 0x0081 (0x00810000 - 0x0081FFFF)
- **Hex file location**: Starts at line 528515
- **Size**: ~64KB of code
- **Purpose**:
  - System initialization
  - Certificate/signature verification
  - Jumping to main firmware at 0x00a00100

#### Main Firmware
- **Location**: Segments 0x00A1-0x00A9 (0x00a10000 - 0x00a9FFFF)
- **Entry point**: 0x00a00100 (as documented in CLAUDE.md)
- **Hex file location**: Starts at line 659617

#### Additional Code Sections
- **Location**: Segments 0x00E5-0x00E9 (0x00e50000 - 0x00e9FFFF)

## Bootloader Code Analysis

### Boot Sequence

1. **Bootloader starts** at segment 0x00810000
2. **Certificate verification** - The bootloader contains code that reads and verifies the cryptographic certificate stored at 0x00090000
3. **Jump to main firmware** - If verification passes, bootloader jumps to 0x00a00100

### Security Mechanism

The bootloader implements a **certificate-based security verification system**:

- **Certificate Storage**: 256 bytes at 0x00090000-0x00098000
- **Verification Logic**: PowerPC code in bootloader segment performs cryptographic verification
- **Serial Number Binding**: Serial numbers stored at 0x00082000 likely tie the certificate to specific hardware

### Sample Bootloader Code (First Instructions)

```
Address        | Instruction Words
---------------|------------------
0x00810000     | 60008B6F 00C634C7 009B70E0 60008C6F
0x00810010     | 00C634C7 009C70E0 60008D6F 00C634C7
0x00810020     | 009D70E0 60008E6F 00C634C7 009E70E0
...
```

## Key Findings

1. ✅ **Bootloader Located**: 0x00810000 (Segment 0x0081)
2. ✅ **RSA Public Key**: 0x00000900 (128 bytes, 1024-bit RSA modulus)
3. ✅ **RSA Public Exponent**: 0x00000980 (value: 0x00010001 = 65537)
4. ✅ **Encrypted Signature**: 0x00F00004 (128 bytes, location TBD - may be RAM/calibration)
5. ✅ **Main Firmware Entry**: 0x00a00100
6. ✅ **Security**: RSA-1024 + SHA-1 signature verification confirmed

## Detailed Security Analysis

### Cryptographic Scheme: RSA-1024 with SHA-1

**Verification Function**: `signcheck()` at line 19804 in emira.c

**Algorithm**:
1. Computes SHA-1 hash of firmware regions:
   - CALROM (0x10000 bytes)
   - Header (0xa0 bytes from 0x00a00000)
   - Main firmware (0x27ff58 bytes from 0x00a000a8)

2. Loads 1024-bit RSA public key from flash (0x00000900)

3. Loads encrypted signature from 0x00F00004

4. Performs RSA decryption: `decrypt_cert_()` implements modular exponentiation

5. Compares decrypted signature with computed SHA-1 hash

6. Returns 1 (valid) or 0 (invalid)

### RSA Public Key Details

**Location**: 0x00000900 (Flash segment 0x0000, offset 0x0900)
**Size**: 128 bytes (1024-bit modulus)
**Modulus (N)**:
```
C3F256CF00440257ABD7308076144D4A
E877DE902CBD5A502DB4E17528E0B34F
943233B90398A30EC3F1CC6983F9DBFD
C02BF58864E8265F344F1063B545F1EB
5E543B62EA7F71EE4CB7E14DBEF38D09
CA341D60777F1790E7FAE59D9F1208DC
86F838B153E586218230FE9BF290F46C
5E550CAFFE31BE23D9FC255BC58DC5B7
```

**Public Exponent (e)**: 0x00010001 (65537) - Standard RSA exponent
**Location**: 0x00000980

## Security Implications

### Strengths
- **RSA-1024**: Industry-standard asymmetric cryptography
- **SHA-1 integrity check**: Covers multiple firmware regions
- **Hardware-embedded public key**: Stored in bootloader flash at 0x00000900
- **Signature verification**: Prevents unsigned firmware from running

### Weaknesses
- **SHA-1 is deprecated**: Considered weak by modern standards (though collision attacks don't apply here)
- **RSA-1024**: Smaller than current recommendations (2048-bit+)
- **Potential bypass**: If bootloader can be modified, signature check can be patched

### Tuning/Modification Implications

**To modify firmware, you would need to either:**

1. **Obtain private key** - Sign modified firmware with Lotus's RSA private key (extremely unlikely)

2. **Patch bootloader** - Disable signature verification:
   - Modify `signcheck()` to always return 1 (success)
   - Requires ability to reflash bootloader section at 0x00810000
   - May be protected by hardware write-protection

3. **Replace public key** - Install your own RSA key pair:
   - Generate new RSA-1024 keypair
   - Replace modulus at 0x00000900
   - Sign firmware with your private key
   - Requires bootloader write access

4. **Exploit cryptographic weakness** - Find SHA-1 collision or RSA vulnerability (highly advanced)

## Function Reference (from emira.c)

### Main Verification Functions

**`signcheck()`** (line 19804):
- Main signature verification routine
- Returns 1 if valid, 0 if invalid
- Called during boot sequence

**`decrypt_cert_()`** (line 19731):
- RSA modular exponentiation implementation
- Decrypts signature using public key
- Classic square-and-multiply algorithm

**`SHA1_Init()`** (line 19028):
- Initialize SHA-1 context

**`SHA1_Update()`** (line 19043):
- Add data to hash computation

**`SHA1_Final()`** (line 19076):
- Finalize hash and output digest

**`inverseEndian()`** (line 19785):
- Byte-swap utility for big/little endian conversion
- Reverses byte order for RSA values

## Recommendations for Further Analysis

1. ✅ **Bootloader location identified** - 0x00810000
2. ✅ **Crypto algorithm identified** - RSA-1024 + SHA-1
3. ✅ **Public key extracted** - See above
4. **Locate encrypted signature** - 0x00F00004 appears to be RAM/calibration space
5. **Test signature verification** - Try modifying firmware bytes and observe boot behavior
6. **Investigate bootloader protection** - Check if flash block 0x0081 is write-protected
7. **Analyze calibration area** - CALROM region may contain tunable parameters

## Tools Used

- ✅ Ghidra with PowerPC support (decompiled to emira.c)
- ✅ Python for hex file parsing
- ✅ Grep/bash for pattern searching

## Next Steps for Tuning

1. **Map calibration tables** - Find fuel, ignition, boost maps in CALROM
2. **Identify checksum locations** - May have additional checksums beyond RSA
3. **Test patch locations** - Small modifications to verify write protection
4. **Document memory map** - Complete map of all firmware sections
