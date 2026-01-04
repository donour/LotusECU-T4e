/*
 * cal_fuel.h
 *
 * Fuel System and Injection Calibration Variables
 *
 * This file contains calibration parameters for:
 * - Fuel injection timing and pulse width
 * - Fuel film compensation
 * - Transient fuel enrichment
 * - Closed loop fuel control (O2 sensor feedback)
 * - Injector characterization
 *
 * Common Prefixes:
 *   CAL_inj_*: General injection parameters
 *   CAL_injtip_*: Injector tip-in compensation (fuel film)
 *   CAL_fuel_*: Fuel system parameters
 *   CAL_closedloop_*: Closed loop O2 control
 */

#ifndef CAL_FUEL_H
#define CAL_FUEL_H

#include "types.h"

/* ========================================================================
 * Fuel Injection Calibrations
 * ======================================================================== */

u8_factor_1/255[64] CAL_closedloop_integral_gain_table;
u8_factor_1/255[8] CAL_injtip_fuel_film_alpha_inc;
u8_factor_1/255[8] CAL_injtip_fuel_film_alpha_dec;
uint8_t[8] CAL_injtip_fuel_film_alpha_inc_X_mass_per_time;
uint8_t[8] CAL_injtip_fuel_film_alpha_dec_X_mass_per_time;
u8_time_5ms[64] CAL_injtip_transient_throttle_response_time;
u8_temp_5/8-40c[8] CAL_injtip_transient_throttle_response_time_X_coolant_tmp;
u8_rspeed_125/4+500rpm[8] CAL_injtip_transient_throttle_response_time_Y_rpm;
u16_factor_1/1023[2] CAL_injtip_out_threshold;
u16_factor_1/1023[2] CAL_injtip_in_threshold;
u8_factor_1/255[16] CAL_injtip_fuel_film_X_factor;
u8_load_4mg/stroke[16] CAL_injtip_fuel_film_X_factor_X_load;
uint8_t CAL_fuel_level_debounce_window_low???;
u8_fuel_gal_x10 CAL_fuel_level_debounce_window_high???;
u8_factor_1/64[192] CAL_inj_enrichment_factor_load_n_coolant_ips;
u8_factor_1/64[192] CAL_inj_enrichment_factor_load_n_coolant_manual;
u8_load_4mg/stroke[12] CAL_inj_enrichment_factor_load_n_coolant_ips_X_load;
u8_load_4mg/stroke[12] CAL_inj_enrichment_factor_load_n_coolant_manual_X_load;
u8_temp_5/8-40c[16] CAL_inj_enrichment_factor_load_n_coolant_ips_Y_coolant;
u8_temp_5/8-40c[16] CAL_inj_enrichment_factor_load_n_coolant_manual_Y_coolant;
u16_pressure_mbar[8] CAL_inj_flow_rate_X_fuel_pressure;
u8_temp_5/8-40c[8] CAL_inj_coldstart_enrichment_X_coolant_temp;
i16_factor_1/20percent CAL_inj_stft_limit;
uint16_t CAL_fuel_usage_to_flow_scaling;
u8_factor_1/100[8] CAL_inj_comp_iat;
u8_temp_5/8-40c[8] CAL_inj_comp_iat_X_iat;
u8_time_20us[64] CAL_inj_time_base;
u8_voltage_72/1023v[8] CAL_inj_time_base_X_car_voltage;
u8_pressure_50mbar[8] CAL_inj_time_base_Y_fuel_pressure;
u8_factor_1/255 CAL_inj_max_duty_cycle_limit;
uint8_t[128] CAL_inj_comp_air_temp2;
uint8_t[100] CAL_inj_comp_air_temp_startup;
u8_temp_5/8-40c[10] CAL_inj_comp_air_temp_startup_X_air_temp;
u8_load_4mg/stroke[8] CAL_inj_comp_air_temp2_X_load;
u8_temp_5/8-40c[16] CAL_inj_comp_air_temp2_Y_air_temp;
u8_mass_g[10] CAL_inj_comp_air_temp_startup_Y_maf_accum;
u8_angle_720/256deg[256] CAL_inj_angle;
u8_rspeed_125/4+500rpm[16] CAL_inj_angle_X_engine_speed;
u8_load_4mg/stroke[16] CAL_inj_angle_Y_load;
u8_time_256us[16] CAL_inj_startup_enrichment_offset;
u8_temp_5/8-40c[16] CAL_inj_startup_enrichment_offset_X_coolant_temp_engine_stopped;
u8_factor_1/200[400] CAL_inj_bank_balance;
u8_factor_1/100[8] CAL_inj_accel_enrichment_load_threshold;
u8_rspeed_125/4+500rpm[20] CAL_inj_bank_balance_X_engine_speed;
u8_rspeed_125/4+500rpm[8] CAL_inj_accel_enrichment_load_threshold_X_rpm;
u8_load_1173mg/255stroke[20] CAL_inj_bank_balance_Y_load;
u8_time_ms CAL_closedloop_entry_delay_time_cruise;
u8_time_ms CAL_closedloop_entry_delay_power_enrich;
u8_factor_1/100 CAL_inj_comp_power_enrich_from_ign_retard;
u16_factor_1/32[168] CAL_inj_cranking_enrichment_coolant_ips;
u16_temp_5/8-40c[12] CAL_inj_cranking_enrichment_coolant_ips_X_coolant_engine_stopped;
u16_afr_1/100 CAL_closedloop_afr;
u16_mass_mg[14] CAL_inj_cranking_enrichment_coolant_ips_Y_maf_accumulated;
u16_factor_1/32[168] CAL_inj_cranking_enrichment_coolant_manual;
u16_temp_5/8-40c[12] CAL_inj_cranking_enrichment_coolant_manual_X_coolant_engine_stopped;
u16_mass_mg[14] CAL_inj_cranking_enrichment_coolant_manual_Y_maf_accumulated;
u8_afr_1/20+5[400] CAL_inj_afr_base;
u8_rspeed_125/4+500rpm[20] CAL_inj_afr_base_X_engine_speed;
u8_factor_1/255[64] CAL_inj_cranking_enrichment_air_temp;
u8_load_1173mg/255stroke[20] CAL_inj_afr_base_Y_engine_load;
u8_temp_5/8-40c[8] CAL_inj_cranking_enrichment_air_temp_X_iat;
u8_temp_5/8-40c[8] CAL_inj_cranking_enrichment_air_temp_Y_coolant_temp_engine_stopped;
u8_factor_1/200[400] CAL_inj_efficiency;
u8_rspeed_125/4+500rpm[20] CAL_inj_efficiency_X_engine_speed;
u8_load_1173mg/255stroke[20] CAL_inj_efficiency_Y_engine_load;
u8_factor_1/255[6] CAL_inj_cranking_enrichment_load;
u8_load_4mg/stroke[6] CAL_inj_cranking_enrichment_load_X_load;
u16_flow_mg/s[8] CAL_inj_flow_rate;
u8_factor_1/255[10] CAL_inj_cranking_enrichment_unknown1;
uint8_t[10] CAL_inj_cranking_enrichment_unknown1_X_unknown;
u8_mass_8g[10] CAL_inj_cranking_enrichment_mass_accum_X_maf_accum;
uint8_t[10] CAL_inj_cranking_enrichment_mass_accum;
uint8_t[64] CAL_inj_coldstart_enrichment;
uint8_t[8] CAL_inj_coldstart_enrichment_Y_maf_accum;
uint8_t[6] CAL_injtip_in_adj_gears;
u8_speed_kph CAL_injtip_carspeed_unknown1;
u8_rspeed_10rpm[4] CAL_injtip_dfco_ips_unknown1;
u8_temp_5/8-40c[4] CAL_injtip_dfco_ips_unknown1_X_coolant_temp;
u8_rspeed_10rpm[4] CAL_injtip_dfco_manual_unknown1;
u8_temp_5/8-40c[4] CAL_injtip_dfco_manual_unknown1_X_coolant_temp;
uint8_t[16] CAL_injtip_comp_rpm1;
u8_rspeed_125/4+500rpm[16] CAL_injtip_comp_rpm1_X_engine_speed;
u16_time_5ms CAL_injtip_overrun_hysteresis_timer;
u8_factor_1/64[16] CAL_injtip_comp_temp1;
u8_temp_5/8-40c[16] CAL_injtip_comp_temp1_X_coolant;
u8_factor_1/1023 CAL_injtip_dfco_ips_min_accel_pedal;
uint8_t[16] CAL_injtip_comp_load1;
u8_load_4mg/stroke[16] CAL_injtip_comp_load1_X_load;
u16_time_5ms CAL_injtip_overrun_inhibit_timer;
uint8_t CAL_injtip_comp_base;
uint8_t[16] CAL_injtip_comp_step1;
u8_rspeed_125/4+500rpm[16] CAL_injtip_comp_step1_X_rpm;
u8_temp_5/8-40c CAL_injtip_dfco_enable_temp;
uint8_t CAL_injtip_in_adj_gears_6;
u8_factor_1/1023 CAL_injtip_dfco_enable_accel_pedal;
u8_rspeed_50rpm[4] CAL_injtip_dfco_enable_rpm_ips_firstgear;
u8_temp_5/8-40c[4] CAL_injtip_dfco_enable_rpm_ips_firstgear_X_coolant;
u8_temp_5/8-40c[4] CAL_injtip_dfco_enable_rpm_ips_default_X_coolant;
u8_rspeed_10rpm[4] CAL_injtip_dfco_enable_rpm_ips_default;
u8_rspeed_10rpm[4] CAL_injtip_dfco_enable_rpm_manual_default;
u8_temp_5/8-40c[4] CAL_injtip_dfco_enable_rpm_manual_default_X_coolant;
uint8_t[16] CAL_injtip_comp_negative_rpm;
u8_rspeed_125/4+500rpm[16] CAL_injtip_comp_negative_rpm_X_rpm;
u8_factor_1/64[16] CAL_injtip_comp_negative_temp;
u8_temp_5/8-40c[16] CAL_injtip_comp_negative_temp_X_coolant_temp;
uint8_t[16] CAL_injtip_comp_negative_load;
u8_load_4mg/stroke[16] CAL_injtip_comp_negative_load_X_load;
u8_factor_1/1023[16] CAL_injtip_step_unknown;
u8_rspeed_125/4+500rpm[16] CAL_injtip_step_unknown_X_rpm;
u8_speed_kph CAL_injtip_dfco_enable_speed;
u8_factor_1/255 CAL_injtip_accel_pedal_min_unknown;
u16_voltage_5/1023v CAL_closedloop_o2_sensor_threshold_rich;
u16_voltage_5/1023v CAL_closedloop_o2_sensor_threshold_lean;
u8_rspeed_125/4+500rpm[8] CAL_closedloop_proportional_gain_rich_table_X_rpm;
u8_rspeed_125/4+500rpm[8] CAL_closedloop_proportional_gain_lean_table_X_rpm;
u8_rspeed_125/4+500rpm[8] CAL_closedloop_integral_gain_table_X_rpm;
u8_rspeed_125/4+500rpm[8] CAL_closedloop_derivative_gain_table_X_rpm;
u8_time_10us CAL_closedloop_max_tipin_enrichment;
u8_time_10us CAL_closedloop_max_tipout_enleanment;
u8_time_5ms CAL_closedloop_stft_increment_period;
u16_voltage_5/1023v CAL_closedloop_o2_sensor_voltage_switch_rich;
u16_voltage_5/1023v CAL_closedloop_o2_sensor_voltage_switching_lean;
u8_factor_1/255 CAL_closedloop_integral_gain_scale_manual;
uint16_t CAL_closedloop_proportional_gain_rich_ips;
uint16_t CAL_closedloop_proportional_gain_lean_ips;
uint16_t CAL_closedloop_integral_gain_ips;
uint16_t CAL_closedloop_derivative_gain_ips;
int16_t CAL_closedloop_stft_idle_max_limit;
u8_load_4mg/stroke[8] CAL_closedloop_proportional_gain_rich_table_Y_load;
u8_factor_1/255[64] CAL_closedloop_proportional_gain_rich_table;
u8_load_4mg/stroke[8] CAL_closedloop_proportional_gain_lean_table_Y_load;
u8_factor_1/255[64] CAL_closedloop_proportional_gain_lean_table;
u8_load_4mg/stroke[8] CAL_closedloop_integral_gain_table_Y_load;
u8_load_4mg/stroke[8] CAL_closedloop_derivative_gain_table_Y_load;
u8_factor_1/255[64] CAL_closedloop_derivative_gain_table;
uint8_t[8] CAL_closedloop_o2_switch_threshold;
u8_rspeed_125/4+500rpm[8] CAL_closedloop_o2_switch_threshold_X_rpm;
u16_time_5ms CAL_closedloop_activate_timer_o2_check;
u8_time_s[16] CAL_closedloop_activate_engine_timer;
u8_time_hours CAL_closedloop_engine_run_learn_timer_unknown;
u8_rspeed_125/4+500rpm CAL_closedloop_lean_protect_max_rpm;
u8_factor_1/64 CAL_closedloop_proportional_gain_scale;
uint8_t CAL_closedloop_cross_bank_check_enable;
u8_temp_5/8-40c CAL_closedloop_fuel_learn_iat_max;
u8_temp_5/8-40c CAL_closedloop_fuel_learn_coolant_min;
u16_pressure_mbar CAL_closedloop_fuel_learn_baro_min;
uint8_t CAL_fuel_learn_time_step;
u8_pressure_50mbar[64] CAL_fuel_pressure_target;
u8_rspeed_125/4+500rpm[8] CAL_fuel_pressure_target_X_engine_speed;
u8_load_4mg/stroke[8] CAL_fuel_pressure_target_Y_load;
u8_pressure_50mbar CAL_fuel_pressure_max;
u8_pressure_50mbar CAL_fuel_pressure_target_max;
u8_pressure_50mbar CAL_fuel_pressure_target_min;
u16_factor_1/10000[64] CAL_fuel_pump_command;
u16_pressure_mbar[8] CAL_fuel_pump_command_X_pressure;
uint16_t[8] CAL_fuel_pump_command_Y_estimated_inj_flow;
u8_factor_1/255[8] CAL_fuel_pump_proportional_gain;
u8_pressure_50mbar[8] CAL_fuel_pump_proportional_gain_X_error;
u16_voltage_18/1023v CAL_fuel_pump_reference_voltage;
u8_factor_1/100[2] CAL_fuel_pump_proportional_limit;
bool CAL_fuel_pump_integral_enable;
u8_factor_1/100 CAL_fuel_pump_integral_gain;
bool CAL_fuel_pump_integral_hold_on_dfco;
u8_fuel_gal_x10 CAL_fuel_pump_integral_fuel_level_min;
    *(u8_factor_1_255 **)(puVar1 + 0x1a) = CAL_closedloop_integral_gain_table + 0x3e;
                      CAL_injtip_fuel_film_X_factor_X_load);
                        CAL_injtip_fuel_film_alpha_inc_X_mass_per_time);
                        CAL_injtip_fuel_film_alpha_dec_X_mass_per_time);
        tps_transient_magnitude_decay = CAL_injtip_in_threshold[0];
                      CAL_injtip_transient_throttle_response_time,
                      CAL_injtip_transient_throttle_response_time_X_coolant_tmp,
                      CAL_injtip_transient_throttle_response_time_Y_rpm);
// CAL_inj_flow_rate_X_fuel_pressure (u16_pressure_mbar[8])
// CAL_inj_flow_rate (u16_flow_mg/s[8])
// CAL_inj_efficiency (u8_factor_1/200[400]) with axes CAL_inj_efficiency_X_engine_speed,
// CAL_inj_efficiency_Y_engine_load
// CAL_inj_time_base (u8_time_20us[64]) with axes CAL_inj_time_base_X_car_voltage
// CAL_inj_time_base_Y_fuel_pressure (u8_pressure_50mbar[8])
// CAL_inj_bank_balance with axes CAL_inj_bank_balance_X_engine_speed, Y_load
// CAL_inj_comp_iat (+ variant using manifold temp)
// CAL_inj_startup_enrichment_offset (adds time offset at start)
// CAL_inj_afr_base (target AFR map)
// CAL_inj_flow_rate, CAL_inj_flow_rate_X_fuel_pressure (flow vs ΔP)
// CAL_inj_time_base, CAL_inj_time_base_{X_car_voltage, Y_fuel_pressure} (latency/dead time vs
// CAL_inj_efficiency (+ axes) as an overall scaling factor
// CAL_inj_bank_balance (+ axes) for bank split (if applicable to your setup)
                  CAL_inj_time_base_X_car_voltage,CAL_inj_time_base_Y_fuel_pressure);
                    CAL_inj_angle_X_engine_speed,CAL_inj_angle_Y_load);
                  CAL_inj_startup_enrichment_offset_X_coolant_temp_engine_stopped);
                  CAL_inj_afr_base_X_engine_speed,CAL_inj_afr_base_Y_engine_load);
                  CAL_inj_accel_enrichment_load_threshold_X_rpm);
     (closedloop_entry_delay_steps = CAL_closedloop_entry_delay_time_cruise,
    closedloop_entry_delay_steps = CAL_closedloop_entry_delay_power_enrich;
  if (_afr_target == CAL_closedloop_afr) {
    afr_target2 = CAL_closedloop_afr;
  if (afr_target2 < CAL_closedloop_afr) {
                  CAL_inj_efficiency_X_engine_speed,CAL_inj_efficiency_Y_engine_load);
                  CAL_inj_flow_rate_X_fuel_pressure);
                  CAL_inj_bank_balance_X_engine_speed,CAL_inj_bank_balance_Y_load);
                    CAL_inj_enrichment_factor_load_n_coolant_ips,
                    CAL_inj_enrichment_factor_load_n_coolant_ips_X_load,
                    CAL_inj_enrichment_factor_load_n_coolant_ips_Y_coolant);
                    CAL_inj_enrichment_factor_load_n_coolant_manual,
                    CAL_inj_enrichment_factor_load_n_coolant_manual_X_load,
                    CAL_inj_enrichment_factor_load_n_coolant_manual_Y_coolant);
                    CAL_inj_comp_air_temp2,CAL_inj_comp_air_temp2_X_load,
                    CAL_inj_comp_air_temp2_Y_air_temp);
                         CAL_inj_cranking_enrichment_coolant_ips,
                         CAL_inj_cranking_enrichment_coolant_ips_X_coolant_engine_stopped,
                         CAL_inj_cranking_enrichment_coolant_ips_Y_maf_accumulated);
                       CAL_inj_cranking_enrichment_coolant_manual,
                       CAL_inj_cranking_enrichment_coolant_manual_X_coolant_engine_stopped,
                       CAL_inj_cranking_enrichment_coolant_manual_Y_maf_accumulated);
                      CAL_inj_comp_air_temp_startup,CAL_inj_comp_air_temp_startup_X_air_temp,
                      CAL_inj_comp_air_temp_startup_Y_maf_accum);
                      CAL_inj_comp_air_temp_startup_X_air_temp,
                      CAL_inj_comp_air_temp_startup_Y_maf_accum);
                    CAL_inj_comp_air_temp_startup_X_air_temp,
                    CAL_inj_comp_air_temp_startup_Y_maf_accum);
                    CAL_inj_comp_air_temp_startup_X_air_temp,
                    CAL_inj_comp_air_temp_startup_Y_maf_accum);
                      CAL_inj_cranking_enrichment_air_temp,
                      CAL_inj_cranking_enrichment_air_temp_X_iat,
                      CAL_inj_cranking_enrichment_air_temp_Y_coolant_temp_engine_stopped);
                      CAL_inj_cranking_enrichment_air_temp,
                      CAL_inj_cranking_enrichment_air_temp_X_iat,
                      CAL_inj_cranking_enrichment_air_temp_Y_coolant_temp_engine_stopped);
                    CAL_inj_cranking_enrichment_load_X_load);
                    CAL_inj_cranking_enrichment_unknown1_X_unknown);
                    CAL_inj_cranking_enrichment_mass_accum,
                    CAL_inj_cranking_enrichment_mass_accum_X_maf_accum);
                       CAL_inj_coldstart_enrichment,CAL_inj_coldstart_enrichment_X_coolant_temp,
                       CAL_inj_coldstart_enrichment_Y_maf_accum);
    inj_pw_max_allowed = (int)(inj_pw_window_size * CAL_inj_max_duty_cycle_limit) / 0xff;
    inj_tip_in_adj_gear_current = CAL_injtip_in_adj_gears[0];
    inj_tip_in_adj_gear_current = CAL_injtip_in_adj_gears[1];
    inj_tip_in_adj_gear_current = CAL_injtip_in_adj_gears[2];
    inj_tip_in_adj_gear_current = CAL_injtip_in_adj_gears[3];
    inj_tip_in_adj_gear_current = CAL_injtip_in_adj_gears[4];
    inj_tip_in_adj_gear_current = CAL_injtip_in_adj_gears[5];
    inj_tip_in_adj_gear_current = CAL_injtip_in_adj_gears_6;
    inj_tip_in_adj_gear_current = CAL_injtip_in_adj_gears[0];
                  CAL_injtip_comp_negative_temp_X_coolant_temp);
                  CAL_injtip_comp_negative_load_X_load);
                           CAL_injtip_dfco_enable_rpm_ips_firstgear_X_coolant);
                             CAL_injtip_dfco_ips_unknown1_X_coolant_temp);
                             CAL_injtip_dfco_enable_rpm_ips_default_X_coolant);
                           CAL_injtip_dfco_manual_unknown1_X_coolant_temp);
                           CAL_injtip_dfco_enable_rpm_manual_default_X_coolant);
     (_inj_flags1 = inj_flags | 8, CAL_injtip_carspeed_unknown1 < car_speed_u8)) {
     (_inj_flags2 = inj_flags & 0b1111111111110111, car_speed_u8 < CAL_injtip_dfco_enable_speed)) {
    injtip_overrun_hysteresis_timer = CAL_injtip_overrun_hysteresis_timer;
            ((((car_speed_u8 <= CAL_injtip_carspeed_unknown1 && (car_speed_u8 != '\0')) ||
    injtip_overrun_inhibit_timer = CAL_injtip_overrun_inhibit_timer;
                            CAL_closedloop_proportional_gain_rich_table_X_rpm,
                            CAL_closedloop_proportional_gain_rich_table_Y_load,
                            CAL_closedloop_proportional_gain_rich_table);
                            CAL_closedloop_proportional_gain_lean_table_X_rpm,
                            CAL_closedloop_proportional_gain_lean_table_Y_load,
                            CAL_closedloop_proportional_gain_lean_table);
                            CAL_closedloop_integral_gain_table_X_rpm,
                            CAL_closedloop_integral_gain_table_Y_load,
                            CAL_closedloop_integral_gain_table);
                            CAL_closedloop_derivative_gain_table_X_rpm,
                            CAL_closedloop_derivative_gain_table_Y_load,
                            CAL_closedloop_derivative_gain_table);
                       CAL_closedloop_o2_switch_threshold_X_rpm);
    cl_proportional_gain_lean = CAL_closedloop_proportional_gain_rich_ips;
    cl_proportional_gain_rich = CAL_closedloop_proportional_gain_lean_ips;
    cl_integral_gain = CAL_closedloop_integral_gain_ips;
    cl_derivative_gain = CAL_closedloop_derivative_gain_ips;
  o2_threshold_lean = CAL_closedloop_o2_sensor_threshold_lean;
  o2_threshold_rich = CAL_closedloop_o2_sensor_threshold_rich;
    if ((obd_ii_o2_sensor1_voltage < CAL_closedloop_o2_sensor_voltage_switching_lean) ||
    if ((obd_ii_o2_sensor5_voltage < CAL_closedloop_o2_sensor_voltage_switching_lean) ||
    if ((obd_ii_o2_sensor2_voltage < CAL_closedloop_o2_sensor_voltage_switching_lean) ||
    if ((obd_ii_o2_sensor6_voltage < CAL_closedloop_o2_sensor_voltage_switching_lean) ||
    if ((runtime_since_start < closedloop_activate_time) || (afr_target2 != CAL_closedloop_afr)) {
      if (afr_target2 < CAL_closedloop_afr) {
       (afr_target2 != CAL_closedloop_afr)) {
      stft_increment_timer_bank1 = CAL_closedloop_stft_increment_period;
        stft_bank1 = CAL_closedloop_stft_idle_max_limit;
    if ((runtime_since_start < closedloop_activate_time) || (afr_target2 != CAL_closedloop_afr)) {
      if (afr_target2 < CAL_closedloop_afr) {
       (afr_target2 != CAL_closedloop_afr)) {
      stft_increment_timer_bank2 = CAL_closedloop_stft_increment_period;
        stft_bank2 = CAL_closedloop_stft_idle_max_limit;
  if (((engine_speed_3 < CAL_closedloop_lean_protect_max_rpm) &&
  if (stft_bank1 < CAL_inj_stft_limit) {
    stft_bank1 = CAL_inj_stft_limit;
  if (((engine_speed_3 < CAL_closedloop_lean_protect_max_rpm) &&
  if (stft_bank2 < CAL_inj_stft_limit) {
    stft_bank2 = CAL_inj_stft_limit;
        stft_bank1 = CAL_inj_stft_limit;
        stft_bank2 = CAL_inj_stft_limit;
    cl_cross_bank_check_enabled = CAL_closedloop_cross_bank_check_enable;
                     LEA_fuel_learn_unknkown_bank1 - CAL_fuel_learn_time_step;
            LEA_fuel_learn_unknkown_bank1 = LEA_fuel_learn_unknkown_bank1 + CAL_fuel_learn_time_step
                     LEA_fuel_learn_unknkown_bank2 - CAL_fuel_learn_time_step;
            LEA_fuel_learn_unknkown_bank2 = LEA_fuel_learn_unknkown_bank2 + CAL_fuel_learn_time_step
             (coolant_temp <= CAL_closedloop_fuel_learn_coolant_min)) ||
             (coolant_temp <= CAL_closedloop_fuel_learn_coolant_min)) || (engine_speed_2 == 0)) ||
          (car_speed_u8 != 0)) || (runtime_since_start < CAL_closedloop_activate_timer_o2_check)) {
         ((car_speed_u8 != '\0' || (runtime_since_start < CAL_closedloop_activate_timer_o2_check))))
  if (runtime_since_start < CAL_closedloop_activate_timer_o2_check) {
    rv = CAL_fuel_pressure_max;
                            CAL_fuel_pressure_target,CAL_fuel_pressure_target_X_engine_speed,
                            CAL_fuel_pressure_target_Y_load);
    fuel_pressure_target = CAL_fuel_pressure_target_max;
    if (fuel_pressure_target_raw < CAL_fuel_pressure_target_min) {
        fuel_pressure_target = CAL_fuel_pressure_target_min;
                      CAL_fuel_pump_command,CAL_fuel_pump_command_X_pressure,
                      CAL_fuel_pump_command_Y_estimated_inj_flow);
                      CAL_fuel_pump_proportional_gain_X_error);

#endif /* CAL_FUEL_H */
