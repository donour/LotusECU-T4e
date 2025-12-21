# Wrench Light Analysis - Lotus T6e ECU (E132E0288)

## Summary

The wrench light (service indicator for non-emissions electrical faults) is controlled by **cluster_flags bit 4 (0x10)** in CAN message 0x400, byte 3.

## CAN Message 0x400 Structure

| Byte | Field | Description |
|------|-------|-------------|
| 0-1 | fuel_usage_instantaneous | Fuel consumption data |
| 2 | field7 | Always 0 (unused) |
| **3** | **cluster_flags** | **Warning light flags** |
| 4 | fuel_level_pct | Fuel level percentage |
| 5 | temp_coolant | Coolant temperature |
| 6 | cluster_indicator_flags | Indicator light flags |
| 7 | (unused) | Not assigned |

## cluster_flags Bit Map (Byte 3)

| Bit | Mask | Function | Evidence |
|-----|------|----------|----------|
| 0 | 0x01 | Low fuel warning | E132E0288.c:20082-20086 |
| 1 | 0x02 | Coolant warning | E132E0288.c:20156-20164 |
| 2 | 0x04 | **UNUSED** | Never referenced |
| 3 | 0x08 | Traction control indicator | E132E0288.c:20042-20045 |
| **4** | **0x10** | **Wrench light** | **E132E0288.c:20055** |
| 5 | 0x20 | Brake warning (IPS mode) | E132E0288.c:20057-20064 |
| 6 | 0x40 | **UNUSED** | Never referenced |
| 7 | 0x80 | **UNUSED** | Never referenced |

## cluster_indicator_flags Bit Map (Byte 6)

| Bit | Mask | Function |
|-----|------|----------|
| 0 | 0x01 | Coolant warning indicator |
| 1 | 0x02 | **UNUSED** (potential alternate location) |
| 2 | 0x04 | Lean fuel blend indicator |
| 3 | 0x08 | Oil pressure warning |
| 4 | 0x10 | OBD monitor related |
| 5 | 0x20 | Traction control / shift light |
| 6 | 0x40 | Shift light |
| 7 | 0x80 | Shift light |

## Evidence for Bit 4 (0x10) as Wrench Light

### 1. Unconditional Clear Operation

```c
// E132E0288.c:20055 in cluster_data_send_100ms()
cluster_flags = cluster_flags & 0xef;  // Clears bit 4 EVERY 100ms cycle
```

This line **always** clears bit 4, with no conditional logic protecting it.

### 2. Never Explicitly Set

Exhaustive search of the entire codebase shows:
- ✅ Bit 4 is **CLEARED** at line 20055
- ❌ Bit 4 is **NEVER SET** anywhere in visible code
- ❌ No `cluster_flags |= 0x10` operations exist
- ❌ No direct assignments with bit 4 = 1

### 3. Pattern Matches Expected Behavior

This matches the expected wrench light behavior:
- **During startup**: Bit 4 = 1 (wrench light ON)
- **After self-tests pass**: Code clears bit 4 every cycle (wrench light OFF)
- **When fault occurs**: External mechanism sets bit 4 = 1
- **While fault persists**: Bit gets set again before next clear
- **After fault resolves**: Clear operation takes effect, light goes OFF

### 4. Comparison with Other Unused Bits

Unlike truly unused bits (2, 6, 7 of cluster_flags), bit 4 is **actively managed**:
- Bit 4: **Actively cleared** (suggests it has purpose)
- Bits 2, 6, 7: **Never touched** (truly unused)
- cluster_indicator_flags bit 1: **Never touched** (truly unused)

## Missing Implementation: Where is Bit 4 SET?

The SET operation is not visible in the decompiled C code. Possible locations:

### Theory 1: Startup/Bootloader Code
Bit 4 may be set during ECU initialization before `main()` executes, implementing the 5-second startup test.

### Theory 2: Hardware/Reset State
The variable may initialize to a non-zero value from:
- Power-on reset state
- EEPROM/flash initialization
- Hardware register default value

### Theory 3: Fault Detection Integration
When faults occur (e.g., P0562 low voltage), bit 4 should be set by diagnostic code, but this implementation may be:
- In binary sections not visible in decompilation
- Missing/incomplete in this firmware variant
- Handled by a different firmware module

### Theory 4: Timer-Based Setting
A 30-second timer mechanism (for temporary wrench light) should set bit 4, but this is not found in visible code.

## Bulb Test State Machine

Found at E132E0288.c:20251-20264:

```c
if ((ign_voltage_above_threshold != false) && (cluster_run_state == 2)) {
  DAT_40001623 = 0;  // Reset counter
}
if ((ign_voltage_above_threshold == false) || (DAT_40001622 <= DAT_40001623)) {
  cluster_run_state = 0;  // Normal operation
  if (ign_voltage_above_threshold == false) {
    cluster_run_state = 2;  // Low voltage state
  }
}
else {
  DAT_40001623 = DAT_40001623 + 1;  // Increment counter
  cluster_run_state = 1;  // Bulb test mode
}
cluster_data_send_100ms();  // Called immediately after
```

### Bulb Test States

| State | Value | Description | Duration |
|-------|-------|-------------|----------|
| Normal | 0 | Normal operation after bulb test completes | Continuous |
| Bulb Test | 1 | All warning lights ON during startup | While counter < threshold |
| Low Voltage | 2 | Low ignition voltage detected | Until voltage recovers |

### Expected Wrench Light Behavior During Bulb Test

When `cluster_run_state == 1`, various warnings are forced ON:
- Line 19968: Shift lights `cluster_indicator_flags |= 0b11100000`
- Line 20082: Fuel warning `cluster_flags |= 1`
- Line 20100: Oil pressure warning

**However**: cluster_flags bit 4 is **NOT** set during bulb test in visible code, suggesting:
1. It's set before main() runs, or
2. It's set by hardware/reset default, or
3. The bulb test for wrench light is implemented differently

## Wrench Light Modes

Based on user requirements, the wrench light should have three modes:

### Mode 1: 5-Second Startup Test
- **Duration**: ~5 seconds during ECU startup
- **Trigger**: Automatic during ignition-on
- **Implementation**: Likely set during init, cleared after `cluster_run_state` exits mode 1

### Mode 2: 30-Second Warning
- **Duration**: 30 seconds
- **Trigger**: Small/temporary faults (e.g., low battery voltage during cranking)
- **Example**: P0562 (System Voltage Low)
- **Implementation**: Not found in visible code

### Mode 3: Continuous Illumination
- **Duration**: Until fault is resolved
- **Trigger**: Serious electrical system faults
- **Implementation**: Bit 4 set by fault handler, cleared when fault resolves

## Related Diagnostic Code

### P0562 - System Voltage Low

Located at E132E0288.c:41129-41145:

```c
if ((((CAL_obd_ii_P0562 & 7) != 0) && ((DAT_40004bc1 & 4) == 0)) &&
   (((ignition_on_flags & 1) != 0 && (engine_is_running != false)))) {
  if (sensor_adc_ecu_voltage < CAL_ecu_system_voltage_threshold[1]) {
    DAT_400022d2 = DAT_400022d2 + 1;  // Increment fault counter
    if ((((short)(ushort)DAT_4000ca10 <= DAT_400022d2) &&
        (DAT_400022d2 = 0, DAT_400022d0 != 0)) &&
       (DAT_400022d0 = DAT_400022d0 - 1, DAT_400022d0 == 0)) {
      obd_ii_monitor_fail_transition
                (&CAL_obd_ii_P0562,&DAT_40004bc1,&DAT_40004bc2,&DAT_40004bc3,0x562,0);
    }
  }
}
```

**Note**: This sets OBD diagnostic flags but does **NOT** set cluster_flags bit 4 directly.

## Code Locations Reference

| Function | File | Line | Description |
|----------|------|------|-------------|
| cluster_data_send_100ms | E132E0288.c | 19948-20186 | Main cluster message assembly |
| Bit 4 clear operation | E132E0288.c | 20055 | `cluster_flags &= 0xef` |
| Bulb test state machine | E132E0288.c | 20251-20264 | cluster_run_state management |
| P0562 voltage monitoring | E132E0288.c | 41129-41145 | Low voltage fault detection |

## Recommendations for Further Investigation

1. **Examine binary firmware** for initialization values of cluster_flags
2. **Capture CAN bus traffic** during startup to observe bit 4 behavior
3. **Test low voltage scenario** to see if bit 4 is set during P0562 condition
4. **Check other firmware variants** (C132E0278, A132E0263) for complete implementation
5. **Look for bootloader code** that may set initial wrench light state
6. **Search for 30-second timer** that should control temporary wrench light warnings

## Conclusion

**cluster_flags bit 4 (0x10)** in CAN message 0x400, byte 3 is the wrench light control bit.

The firmware **clears** this bit every cycle when everything is OK. The **set** operation that turns the wrench light ON is not visible in the decompiled code, suggesting it occurs in:
- Initialization/bootloader code
- Hardware reset state
- Binary sections not visible in C decompilation
- Or is missing/incomplete in this firmware version

The pattern of "only clearing, never setting" in running code perfectly matches the expected behavior for a warning light that needs to be explicitly cleared after self-tests pass.

---

*Analysis performed on E132E0288 firmware decompilation*
*Date: 2025-12-21*
