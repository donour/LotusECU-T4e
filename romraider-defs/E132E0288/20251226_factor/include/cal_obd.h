/*
 * cal_obd.h
 *
 * OBD-II Calibration Variables for Lotus T6e ECU Firmware (E132E0288)
 *
 * This file contains all OBD-II related calibration parameters including:
 * - DTC (Diagnostic Trouble Code) enable/threshold settings
 * - Monitor enable conditions
 * - Test limits and thresholds
 * - OBD-II system configuration
 *
 * Variable Naming Convention:
 *   CAL_obd_ii_P#### - DTC code P#### enable and threshold settings
 *   CAL_obd_ii_U#### - DTC code U#### (network) enable and threshold settings
 *
 * u8_obd2level_t6 Type Encoding (3 bits used):
 *   Bit 0 (0x01): Monitor enabled
 *   Bit 1 (0x02): Failure threshold
 *   Bit 2 (0x04): Pass threshold
 *   Value 0x07 (7) = All monitoring enabled
 */

#ifndef CAL_OBD_H
#define CAL_OBD_H

#include "types.h"

/* ========================================================================
 * OBD-II Diagnostic Trouble Code (DTC) Configuration
 * ======================================================================== */

u8_obd2level_t6 CAL_obd_ii_P1809;
u8_obd2level_t6 CAL_obd_ii_P0011;
u8_obd2level_t6 CAL_obd_ii_P0012;
u8_obd2level_t6 CAL_obd_ii_P0014;
u8_obd2level_t6 CAL_obd_ii_P0015;
u8_obd2level_t6 CAL_obd_ii_P0021;
u8_obd2level_t6 CAL_obd_ii_P0022;
u8_obd2level_t6 CAL_obd_ii_P0024;
u8_obd2level_t6 CAL_obd_ii_P0025;
u8_obd2level_t6 CAL_obd_ii_P0016;
u8_obd2level_t6 CAL_obd_ii_P0017;
u8_obd2level_t6 CAL_obd_ii_P0018;
u8_obd2level_t6 CAL_obd_ii_P0019;
u8_obd2level_t6 CAL_obd_ii_P0420;
u8_obd2level_t6 CAL_obd_ii_P0430;
uint8_t CAL_obd_ii_standards_supported;
uint8_t CAL_obd_ii_diag_unknown;
uint8_t[2] CAL_obd_ii_coolant_warmup_thresholds;
u8_obd2level_t6 CAL_obd_ii_P2135;
u8_obd2level_t6 CAL_obd_ii_P0122;
u8_obd2level_t6 CAL_obd_ii_P0123;
u8_obd2level_t6 CAL_obd_ii_P0222;
u8_obd2level_t6 CAL_obd_ii_P0223;
u8_obd2level_t6 CAL_obd_ii_P2119;
u8_obd2level_t6 CAL_obd_ii_P2173;
u8_obd2level_t6 CAL_obd_ii_P1104;
u8_obd2level_t6 CAL_obd_ii_P1106;
u8_obd2level_t6 CAL_obd_ii_P2104;
u8_obd2level_t6 CAL_obd_ii_P2105;
u8_obd2level_t6 CAL_obd_ii_P2107;
u8_obd2level_t6 CAL_obd_ii_P2106;
u8_obd2level_t6 CAL_obd_ii_P2100;
u8_obd2level_t6 CAL_obd_ii_P2102;
u8_obd2level_t6 CAL_obd_ii_P2103;
u8_obd2level_t6 CAL_obd_ii_P2108;
u8_obd2level_t6 CAL_obd_ii_P0638;
u8_obd2level_t6 CAL_obd_ii_P0441;
u8_obd2level_t6 CAL_obd_ii_P0446;
u8_obd2level_t6 CAL_obd_ii_P0500;
u8_obd2level_t6 CAL_obd_ii_P0335;
u8_obd2level_t6 CAL_obd_ii_P0341;
u8_obd2level_t6 CAL_obd_ii_P0346;
u8_obd2level_t6 CAL_obd_ii_P0366;
u8_obd2level_t6 CAL_obd_ii_P0391;
u8_obd2level_t6 CAL_obd_ii_P0174;
u8_obd2level_t6 CAL_obd_ii_P0175;
u8_obd2level_t6 CAL_obd_ii_P2191;
u8_obd2level_t6 CAL_obd_ii_P2193;
u8_obd2level_t6 CAL_obd_ii_P219A;
u8_obd2level_t6 CAL_obd_ii_P219B;
u8_obd2level_t6 CAL_obd_ii_P0171;
u8_obd2level_t6 CAL_obd_ii_P0172;
u8_obd2level_t6 CAL_obd_ii_P050A;
u8_obd2level_t6 CAL_obd_ii_P0506;
u8_obd2level_t6 CAL_obd_ii_P0507;
u8_obd2level_t6 CAL_obd_ii_P0442;
u8_obd2level_t6 CAL_obd_ii_P0456;
u8_obd2level_t6 CAL_obd_ii_P0455;
u8_obd2level_t6 CAL_obd_ii_P0700;
u8_obd2level_t6 CAL_obd_ii_P0601;
u8_obd2level_t6 CAL_obd_ii_P0606;
u8_obd2level_t6 CAL_obd_ii_P0630;
u8_obd2level_t6 CAL_obd_ii_P0610;
u8_obd2level_t6 CAL_obd_ii_P050B;
u8_obd2level_t6 CAL_obd_ii_P2336;
u8_obd2level_t6 CAL_obd_ii_P2337;
u8_obd2level_t6 CAL_obd_ii_P2338;
u8_obd2level_t6 CAL_obd_ii_P2339;
u8_obd2level_t6 CAL_obd_ii_P2340;
u8_obd2level_t6 CAL_obd_ii_P2341;
u8_obd2level_t6 CAL_obd_ii_P1302;
u8_obd2level_t6 CAL_obd_ii_P1301;
u8_obd2level_t6 CAL_obd_ii_P0301;
u8_obd2level_t6 CAL_obd_ii_P0302;
u8_obd2level_t6 CAL_obd_ii_P0303;
u8_obd2level_t6 CAL_obd_ii_P0304;
u8_obd2level_t6 CAL_obd_ii_P0305;
u8_obd2level_t6 CAL_obd_ii_P0306;
u8_obd2level_t6 CAL_obd_ii_P0300;
u8_obd2level_t6 CAL_obd_ii_P0134;
u8_obd2level_t6 CAL_obd_ii_P0154;
u8_obd2level_t6 CAL_obd_ii_P0140;
u8_obd2level_t6 CAL_obd_ii_P0160;
uint16_t CAL_obd_ii_o2_precat_diag_timer;
u8_obd2level_t6 CAL_obd_ii_P0133;
u8_obd2level_t6 CAL_obd_ii_P0153;
u8_obd2level_t6 CAL_obd_ii_P0139;
u8_obd2level_t6 CAL_obd_ii_P0159;
u8_obd2level_t6 CAL_obd_ii_P0076;
u8_obd2level_t6 CAL_obd_ii_P0077;
u8_obd2level_t6 CAL_obd_ii_P0079;
u8_obd2level_t6 CAL_obd_ii_P0080;
u8_obd2level_t6 CAL_obd_ii_P0082;
u8_obd2level_t6 CAL_obd_ii_P0083;
u8_obd2level_t6 CAL_obd_ii_P0085;
u8_obd2level_t6 CAL_obd_ii_P0086;
u8_obd2level_t6 CAL_obd_ii_P0646;
u8_obd2level_t6 CAL_obd_ii_P0647;
u8_obd2level_t6 CAL_obd_ii_P0444;
u8_obd2level_t6 CAL_obd_ii_P0445;
u8_obd2level_t6 CAL_obd_ii_P0447;
u8_obd2level_t6 CAL_obd_ii_P0448;
u8_obd2level_t6 CAL_obd_ii_P0261;
u8_obd2level_t6 CAL_obd_ii_P0262;
u8_obd2level_t6 CAL_obd_ii_P0264;
u8_obd2level_t6 CAL_obd_ii_P0265;
u8_obd2level_t6 CAL_obd_ii_P0267;
u8_obd2level_t6 CAL_obd_ii_P0268;
u8_obd2level_t6 CAL_obd_ii_P0270;
u8_obd2level_t6 CAL_obd_ii_P0271;
u8_obd2level_t6 CAL_obd_ii_P0273;
u8_obd2level_t6 CAL_obd_ii_P0274;
u8_obd2level_t6 CAL_obd_ii_P0276;
u8_obd2level_t6 CAL_obd_ii_P0277;
u8_obd2level_t6 CAL_obd_ii_P2754;
u8_obd2level_t6 CAL_obd_ii_P2755;
u8_obd2level_t6 CAL_obd_ii_P0351;
u8_obd2level_t6 CAL_obd_ii_P0352;
u8_obd2level_t6 CAL_obd_ii_P0353;
u8_obd2level_t6 CAL_obd_ii_P0354;
u8_obd2level_t6 CAL_obd_ii_P0355;
u8_obd2level_t6 CAL_obd_ii_P0356;
u8_obd2level_t6 CAL_obd_ii_U0141;
u8_obd2level_t6 CAL_obd_ii_P025C;
u8_obd2level_t6 CAL_obd_ii_P025D;
u8_obd2level_t6 CAL_obd_ii_P0480;
u8_obd2level_t6 CAL_obd_ii_P0482;
u8_obd2level_t6 CAL_obd_ii_P0135;
u8_obd2level_t6 CAL_obd_ii_P0155;
u8_obd2level_t6 CAL_obd_ii_P0141;
u8_obd2level_t6 CAL_obd_ii_P0161;
u8_obd2level_t6 CAL_obd_ii_P2602;
u8_obd2level_t6 CAL_obd_ii_P2603;
u8_obd2level_t6 CAL_obd_ii_P2612;
u8_obd2level_t6 CAL_obd_ii_P2613;
u8_obd2level_t6 CAL_obd_ii_P0616;
u8_obd2level_t6 CAL_obd_ii_P0617;
u8_obd2level_t6 CAL_obd_ii_P2170;
u8_obd2level_t6 CAL_obd_ii_P2171;
u8_obd2level_t6 CAL_obd_ii_P023B;
u8_obd2level_t6 CAL_obd_ii_P023C;
u8_obd2level_t6 CAL_obd_ii_P123B;
u8_obd2level_t6 CAL_obd_ii_P123C;
u8_obd2level_t6 CAL_obd_ii_P2138;
u8_obd2level_t6 CAL_obd_ii_P2122;
u8_obd2level_t6 CAL_obd_ii_P2123;
u8_obd2level_t6 CAL_obd_ii_P2127;
u8_obd2level_t6 CAL_obd_ii_P2128;
u16_time_100ms CAL_obd_ii_mode2f_timeout;
u8_obd2level_t6 CAL_obd_ii_P0328;
u8_obd2level_t6 CAL_obd_ii_P0332;
u8_obd2level_t6 CAL_obd_ii_P0333;
u8_obd2level_t6 CAL_obd_ii_P0462;
u8_obd2level_t6 CAL_obd_ii_P0463;
u8_obd2level_t6 CAL_obd_ii_P0522;
u8_obd2level_t6 CAL_obd_ii_P0523;
u8_obd2level_t6 CAL_obd_ii_P0524;
u8_obd2level_t6 CAL_obd_ii_P1109;
u8_obd2level_t6 CAL_obd_ii_P0562;
u8_obd2level_t6 CAL_obd_ii_P0563;
u8_obd2level_t6 CAL_obd_ii_P1562;
u8_obd2level_t6 CAL_obd_ii_P0685;
u8_obd2level_t6 CAL_obd_ii_P0564;
u8_obd2level_t6 CAL_obd_ii_P0571;
u8_obd2level_t6 CAL_obd_ii_P0806;
u8_obd2level_t6 CAL_obd_ii_P0807;
u8_obd2level_t6 CAL_obd_ii_P0808;
u8_obd2level_t6 CAL_obd_ii_P0826;
u8_obd2level_t6 CAL_obd_ii_P0827;
u8_obd2level_t6 CAL_obd_ii_P0828;
u16_voltage_5/1023v CAL_obd_ii_oil_pressure_switch_low_voltage;
u8_obd2level_t6 CAL_obd_ii_P0102;
u8_obd2level_t6 CAL_obd_ii_P0103;
u8_obd2level_t6 CAL_obd_ii_P0107;
u8_obd2level_t6 CAL_obd_ii_P0108;
u8_obd2level_t6 CAL_obd_ii_P0131;
u8_obd2level_t6 CAL_obd_ii_P0132;
u8_obd2level_t6 CAL_obd_ii_P0151;
u8_obd2level_t6 CAL_obd_ii_P0152;
u8_obd2level_t6 CAL_obd_ii_P0137;
u8_obd2level_t6 CAL_obd_ii_P0138;
u8_obd2level_t6 CAL_obd_ii_P0157;
u8_obd2level_t6 CAL_obd_ii_P0158;
u8_obd2level_t6 CAL_obd_ii_P0111;
u8_obd2level_t6 CAL_obd_ii_P0112;
u8_obd2level_t6 CAL_obd_ii_P0113;
u8_obd2level_t6 CAL_obd_ii_P0096;
u8_obd2level_t6 CAL_obd_ii_P0097;
u8_obd2level_t6 CAL_obd_ii_P0098;
u8_obd2level_t6 CAL_obd_ii_P0106;
u8_obd2level_t6 CAL_obd_ii_P0072;
u8_obd2level_t6 CAL_obd_ii_P0073;
u8_obd2level_t6 CAL_obd_ii_P0071;
u8_obd2level_t6 CAL_obd_ii_P0116;
u8_obd2level_t6 CAL_obd_ii_P0117;
u8_obd2level_t6 CAL_obd_ii_P0118;
u8_obd2level_t6 CAL_obd_ii_P0191;
u8_obd2level_t6 CAL_obd_ii_P0192;
u8_obd2level_t6 CAL_obd_ii_P0193;
u8_obd2level_t6 CAL_obd_ii_P1107;
u8_obd2level_t6 CAL_obd_ii_P1108;
u8_obd2level_t6 CAL_obd_ii_P0452;
u8_obd2level_t6 CAL_obd_ii_P0453;
u8_obd2level_t6 CAL_obd_ii_P0327;
u8_obd2level_t6 CAL_obd_ii_P0578;
u8_obd2level_t6 CAL_obd_ii_P0579;
u8_obd2level_t6 CAL_obd_ii_P0101_manual;
u8_obd2level_t6 CAL_obd_ii_P0101_ips;
u8_obd2level_t6 CAL_obd_ii_P0128;
u8_obd2level_t6 CAL_obd_ii_P0461;
u8_obd2level_t6 CAL_obd_ii_P0451;
uint8_t CAL_obd_ii_o2_sensors_present;
uint8_t CAL_obd_ii_fuel_type;
u16_torque_nm CAL_obd_ii_engine_reference_torque_manual;
u16_torque_nm CAL_obd_ii_engine_reference_torque_ips;
u8_obd2level_t6 CAL_obd_ii_P0537;
u8_obd2level_t6 CAL_obd_ii_P0538;
u8_obd2level_t6 CAL_obd_ii_B1422;
u8_obd2level_t6 CAL_obd_ii_U0101;
u8_obd2level_t6 CAL_obd_ii_U0122;
u8_obd2level_t6 CAL_obd_ii_U0123;
u8_obd2level_t6 CAL_obd_ii_U0513;
u8_obd2level_t6 CAL_obd_ii_U0155;
u8_obd2level_t6 CAL_obd_ii_U0302;
u8_obd2level_t6 CAL_obd_ii_U0316;
u8_obd2level_t6 CAL_obd_ii_U0416;
u8_obd2level_t6 CAL_obd_ii_P0627;
u8_obd2level_t6 CAL_obd_ii_U0109;
u8_obd2level_t6 CAL_obd_ii_P0087;
u8_obd2level_t6 CAL_obd_ii_P0088;
u8_obd2level_t6 CAL_obd_ii_P0712;
u8_obd2level_t6 CAL_obd_ii_P0713;
u8_obd2level_t6 CAL_obd_ii_P2797;
u8_obd2level_t6 CAL_obd_ii_P0897;
    obd_ii_o2_precat_diag_timer_bank1 = CAL_obd_ii_o2_precat_diag_timer;
    obd_ii_o2_precat_diag_timer_bank2 = CAL_obd_ii_o2_precat_diag_timer;
  obd_ii_o2_precat_diag_timer_bank2 = CAL_obd_ii_o2_precat_diag_timer;
  obd_ii_o2_precat_diag_timer_bank1 = CAL_obd_ii_o2_precat_diag_timer;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
    obd_ii_mode2f_timeout = CAL_obd_ii_mode2f_timeout;
  else if (oil_pressure_warning_switch_voltage < CAL_obd_ii_oil_pressure_switch_low_voltage) {
  obd_p101_config = CAL_obd_ii_P0101_manual;
    obd_p101_config = CAL_obd_ii_P0101_ips;
        obd_ii_response[bVar4] = CAL_obd_ii_o2_sensors_present;
        obd_ii_response[bVar4] = CAL_obd_ii_standards_supported;
        obd_ii_response[bVar4] = CAL_obd_ii_fuel_type;
    torque_divisor = CAL_obd_ii_engine_reference_torque_manual;
      torque_divisor = CAL_obd_ii_engine_reference_torque_ips;
  obd_ii_engine_reference_torque_nm = CAL_obd_ii_engine_reference_torque_manual;
    obd_ii_engine_reference_torque_nm = CAL_obd_ii_engine_reference_torque_ips;
        obd_ii_response[bVar1] = CAL_obd_ii_fuel_type;
  obd_p101_config = CAL_obd_ii_P0101_manual;
    obd_p101_config = CAL_obd_ii_P0101_ips;

#endif /* CAL_OBD_H */
