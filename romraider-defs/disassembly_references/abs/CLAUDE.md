
# Firmware information

 - BOSCH ESP8 ABS and stability module
 - Lotus Evora 400, GT410, GT430, and GT

## CAN messages

  CAN ID 0xA2 - Front Wheel Speeds (7 bytes)

  Message Structure:
  Byte:    [0]      [1]       [2]    [3]     [4]     [5]     [6]
          |----RF----|--LF---|       |--LF---|---Car Speed---|Cnt+Chk|

  Signal Extraction:

  | Signal    | Formula                                                       | Bits   |
  |-----------|---------------------------------------------------------------|--------|
  | LF Wheel  | (byte[1] & 0x3F) << 8 | byte[3]                               | 14-bit |
  | RF Wheel  | (byte[1] & 0xC0) >> 6 | (byte[0] & 0x0F) << 10 | byte[1] << 2 | 14-bit |
  | Car Speed | (byte[0] & 0xF0) >> 4 | byte[4] << 4 | (byte[6] & 0x03) << 12 | 14-bit |
  | Counter   | (byte[6] & 0x3C) >> 2                                         | 4-bit  |
  | Checksum  | byte[6] = XOR(bytes 0-5)                                      | 8-bit  |

  Speed Scaling:
  wheel_speed = ((raw_value * 0x32) >> 3) * CAL_wheel_speed_multiplier / 1000
              = (raw_value * 50 / 8) * multiplier / 1000
              = raw_value * 6.25 * multiplier / 1000
  - Invalid value: 0x3FFF (16383) = wheel speed unavailable

  ---
  CAN ID 0xA4 - Rear Wheel Speeds (6 or 8 bytes)

  Signal Extraction:

  | Signal       | Formula                                                       | Bits   |
  |--------------|---------------------------------------------------------------|--------|
  | LR Wheel     | (byte[1] & 0x3F) << 8 | byte[3]                               | 14-bit |
  | RR Wheel     | (byte[1] & 0xC0) >> 6 | (byte[0] & 0x0F) << 10 | byte[1] << 2 | 14-bit |
  | Brake Switch | byte[4] & 0x03                                                | 2-bit  |
  | Counter      | (byte[0] & 0xF0) >> 4                                         | 4-bit  |
  | Checksum     | byte[5] = XOR(bytes 0-4)                                      | 8-bit  |

  If 8 bytes: bytes 6-7 contain additional data (abs_unused_field)

  ---
  CAN ID 0xA8 - ESP/ABS Status (6 bytes)

  | Signal          | Bit Position               | Description             |
  |-----------------|----------------------------|-------------------------|
  | ESP Active      | byte[1] bit 3              | ESP intervention active |
  | ABS Active      | byte[1] bit 5              | ABS intervention active |
  | Status flags    | byte[3] bit 6 (0x40000000) | ESP warning flag        |
  | Status flags    | byte[3] bit 4 (0x10000000) | Another flag            |
  | Brake pressure? | byte[2] bits 0-1           | Low bits status         |
  | abs_a8_flag2    | byte[2] & 0x07             | 3-bit field             |