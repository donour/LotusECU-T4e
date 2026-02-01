/*
 * cal_vehicle.h
 *
 * Vehicle System Calibration Variables
 *
 * This file contains calibration parameters for vehicle-level systems:
 * - Cooling system (fans, pumps, thermostats)
 * - Cruise control
 * - Traction control
 * - Transmission control
 * - Cluster/dashboard communication
 * - AC compressor control
 * - Exhaust flap control
 * - TPS (Throttle Position Sensor) smoothing
 */

#ifndef CAL_VEHICLE_H
#define CAL_VEHICLE_H

#include "types.h"

/* ========================================================================
 * Vehicle System Calibrations
 * ======================================================================== */

u8_count CAL_tps_delta_rate_window_size;
u8_factor_1/255[16] CAL_tps_rate_steadystate_threshold;
u8_rspeed_125/4+500rpm[4] CAL_tps_rate_steadystate_threshold_X_rpm;
u8_factor_1/255[4] CAL_tps_rate_steadystate_threshold_Y_tps;
u8_speed_kph CAL_cluster_brake_switch_max_speed_ips_unknown;
uint8_t CAL_cluster_oil_pressure_warning_light_mode;
uint8_t CAL_trans_cooler_temp_scaling;
u8_speed_kph CAL_vehicle_moving_speed_min;
u8_rspeed_125/4+500rpm[20] CAL_load_to_tps_mapping_X_rpm;
u8_rspeed_125/4+500rpm[20] CAL_load_alphaN_base_X_engine_speed;
u8_time_s[64] CAL_cooling_fan_afterrun;
u8_temp_5/8-40c[8] CAL_cooling_fan_afterrun_X_air_temp;
u8_temp_5/8-40c[8] CAL_cooling_fan_afterrun_Y_coolant_temp;
u8_time_s CAL_cooling_recirc_timer;
u8_temp_5/8-40c CAL_cooling_recirc_enable_airtemp;
u8_temp_5/8-40c CAL_cooling_recirc_airtemp_disable_engine_on;
u16_rspeed_rpm CAL_cooling_recirc_enginespeed_disable_engine_on;
u16_rspeed_rpm CAL_cooling_recirc_rpm_enable_engine_on;
u8_temp_5/8-40c CAL_cooling_recirc_reset_coolant_temp;
uint8_t[8] CAL_cooling_fan_scaling;
u8_factor_1/255[8] CAL_cooling_fan_scaling_X_dutycycle;
uint8_t[8] CAL_cooling_fan_duty_cycle_stopped;
u8_factor_1/255[36] CAL_cooling_fan_base_engine_on;
u8_temp_5/8-40c[6] CAL_cooling_fan_base_engine_on_X_coolant_temp;
u8_speed_kph[6] CAL_cooling_fan_base_engine_on_Y_carspeed;
u8_rspeed_4rpm[2] CAL_cooling_fan_low_rpm_hysteresis_threshold;
u8_speed_kph CAL_cooling_fan_speed_disable_speed;
u16_time_5ms CAL_cooling_fan_startup_time;
u8_factor_1/255[64] CAL_cooling_fan_ac_off;
u8_factor_1/255[36] CAL_cooling_fan_ac_on;
u8_temp_5/8-40c[6] CAL_cooling_fan_ac_on_X_air_temp;
uint8_t[6] CAL_cooling_fan_ac_on_Y_carspeed;
u8_temp_5/8-40c[8] CAL_cooling_fan_ac_off_X_air_temp;
uint8_t[8] CAL_cooling_fan_ac_off_Y_carspeed;
u8_temp_5/8-40c[8] CAL_cooling_fan_duty_cycle_stopped_X_coolant_temp;
u8_temp_5/8-40c CAL_cooling_fan_hotstart_temp;
u8_factor_1/255 CAL_cooling_fan_hotstart_dutycycle;
u8_factor_1/255 CAL_cooling_fan_engine_bay_radfan_threshold_enable;
u8_factor_1/255 CAL_cooling_fan_engine_bay_radfan_threshold_disable;
u8_temp_5/8-40c CAL_cooling_fan_engine_bay_airtemp_enable;
uint16_t CAL_cooling_engine_bay_fan_enable_delay;
u8_rspeed_125/4+500rpm[8] CAL_cluster_oil_pressure_warn_threshold;
u8_rspeed_125/4+500rpm[8] CAL_cluster_oil_pressure_warn_threshold_X_engine_speed;
bool CAL_cluster_test_enable???;
enum_traction_mode CAL_traction_mode;
u8_gear[8] CAL_cluster_shiftlight_rpm_offset_ips_X_gear;
u8_gear[8] CAL_cluster_shiftlight_rpm_offset_manual_X_gear;
u8_fuel_gal_x10[2] CAL_cluster_fuel_level_warning_threshold;
u8_temp_5/8-40c[2] CAL_cluster_coolant_warning;
u8_fuel_gal_x10 CAL_cluster_fuel_level_zero_clip_threshold;
u16_rspeed_rpm CAL_cluster_shift_light_deadband_rpm;
u8_time_100ms CAL_exhaust_flap_startup_threshold;
u16_rspeed_rpm CAL_exhaust_flap_RPM_threshold_open;
u8_load_4mg/stroke CAL_exhaust_flap_load_threshold_open;
uint8_t[64] CAL_exhaust_flap_state_control_tour;
u8_rspeed_50rpm[8] CAL_exhaust_flap_state_control_tour_X_rpm;
u8_factor_1/255[8] CAL_exhaust_flap_state_control_tour_Y_accel_pedal;
uint8_t[64] CAL_exhaust_flap_state_control_sport;
u16_rspeed_rpm CAL_exhaust_flap_RPM_threshold_close;
u8_rspeed_50rpm[8] CAL_exhaust_flap_state_control_sport_X_rpm;
u8_factor_1/255[8] CAL_exhaust_flap_state_control_sport_Y_accel_pedal;
u8_load_4mg/stroke CAL_exhaust_flap_load_threshold_close;
uint8_t[64] CAL_exhaust_flap_state_control_race;
u8_rspeed_50rpm[8] CAL_exhaust_flap_state_control_race_X_rpm;
u8_factor_1/255[8] CAL_exhaust_flap_state_control_race_Y_accel_pedal;
bool CAL_exhaust_flap_tour_mode_enable;
bool CAL_exhaust_flap_sport_mode_enable;
uint16_t CAL_traction_unknown_tire_circumference;
u8_count CAL_traction_abs_ring_teeth_count;
uint8_t CAL_wheel_speed_smoothing;
u16_rspeed_1/4rpm[2] CAL_roughness_enable_rpm;
u8_load_4mg/stroke[2] CAL_roughness_enable_load;
u8_angle_1/4deg CAL_roughness_ign_adv_min_sign_flipped;
u8_angle_1/4deg CAL_roughness_ign_adv_max;
u8_factor_1/100 CAL_roughness_delta_rpm_smoothing_factor;
u8_count CAL_roughness_cycle_count_threshold;
u8_count CAL_roughness_peak_valley_imblance_threshold;
uint8_t CAL_wheel_speed_timer1;
uint8_t CAL_wheel_speed_front_dvdt_scaling;
uint8_t[2] CAL_cluster_fuel_economy_factor_limit;
u8_time_100ms CAL_cluster_fuel_mileage_update_timer;
u8_time_100ms CAL_cluster_fuel_range_smoothing_interval;
uint8_t CAL_cluster_fuel_range_remaining_smoothing_factor;
undefined1 CAL_cluster_dte_min_distance_threshold;
uint8_t CAL_cluster_fuel_economy_factory_stepsize;
u8_time_100ms CAL_cluster_fuel_usage_reset_request_timer;
u8_load_1173mg/255stroke[400] CAL_load_alphaN_base;
u8_factor_1/255[16] CAL_load_source_selection_threshold_by_tps;
u8_rspeed_125/4+500rpm[16] CAL_load_source_selection_threshold_by_tps_X_rpm;
u8_factor_1/255[20] CAL_load_alphaN_base_Y_tps;
bool CAL_load_alphaN_use_tmap_density;
u8_load_4mg/stroke[16] CAL_load_alphaN_seed;
u8_factor_1/255[16] CAL_load_alphaN_seed_X_tps;
u8_factor_1/255[400] CAL_load_to_tps_mapping;
u8_load_1173mg/255stroke[20] CAL_load_to_tps_mapping_Y_load;
uint16_t[256] CAL_load_cylinder_efficiency;
u16_rspeed_1/4rpm[16] CAL_load_cylinder_efficiency_X_engine_speed;
u16_pressure_mbar[16] CAL_load_cylinder_efficiency_Y_map;
uint8_t[16] CAL_load_unused1;
u8_factor_1/255[16] CAL_tps_scaling_factor_rpm;
u8_rspeed_125/4+500rpm[16] CAL_load_unused1_X_rpm;
u8_rspeed_125/4+500rpm[16] CAL_tps_scaling_factor_rpm_X_rpm;
u8_factor_1/100[256] CAL_load_volumetric_efficiency;
u8_rspeed_125/4+500rpm[16] CAL_load_volumetric_efficiency_X_rpm;
u8_load_4mg/stroke[16] CAL_load_volumetric_efficiency_Y_load;
uint8_t[256] CAL_load_baro_gain;
u8_rspeed_125/4+500rpm[16] CAL_load_baro_gain_X_rpm;
u8_load_4mg/stroke[16] CAL_load_baro_gain_Y_load;
u8_load_4mg/stroke[16] CAL_load_reference_charge;
u8_rspeed_125/4+500rpm[16] CAL_load_reference_charge_X_rpm;
u16_volume_cc CAL_load_cylinder_volume;
u16_factor_1/1023 CAL_vehicle_standing_start_throttle_threshold;
u8_load_2mg/stroke[64] CAL_load_plausibility_test_delta;
u8_rspeed_125/4+500rpm[8] CAL_load_plausibility_test_delta_X_rpm;
u8_factor_1/255[8] CAL_load_plausibility_test_delta_Y_tps;
uint16_t CAL_wheel_speed_rate_min;
uint16_t CAL_wheel_speed_min;
char[32] CAL_prog_version;
char[16] CAL_misc_calid;
u8_factor_1/255[8] CAL_dca_tps_limit_ips;
u8_time_50ms[8] CAL_dca_tps_limit_ips_x_time;
uint8_t CAL_tps_brake_wheeldecel_tps_cut_threshold;
u8_speed_kph[2] CAL_dca_enable_carspeed;
u8_factor_1/1023 CAL_cruise_tps_accelerating_threshold;
u8_time_20ms CAL_dca_ramp_timer_unknown;
u8_factor_1/1023 CAL_dca_enable_tps_margin;
u8_time_100ms CAL_dca_stationary_wait_time;
u8_time_5ms CAL_dca_activate_timer;
u16_factor_1/1023 CAL_dca_activate_tps_threshold;
u8_factor_1/1023 CAL_tps_brake_safety_floor;
u8_factor_1/1023 CAL_cruise_accel_pedal_override_threshold_enter;
bool CAL_dca_enable_untested;
u8_factor_1/1023 CAL_cruise_accel_pedal_override_threshold_exit;
u8_time_50ms[8] CAL_dca_tps_limit_manual_X_time;
uint8_t CAL_dca_enable_steering_max;
u8_factor_1/255[8] CAL_dca_tps_limit_manual;
u8_factor_1/255[8] CAL_dca_unknown_ips_nolc;
u8_time_50ms[8] CAL_dca_unknown_ips_nolc_X_time;
u8_time_5ms CAL_tps_accel_pedal_zero_calibrate_timer;
u8_temp_5/8-40c CAL_cooling_thermostat_open;
uint8_t[8] CAL_cooling_thermostat_warmup_load_factor;
u8_load_4mg/stroke[8] CAL_cooling_thermostat_warmup_load_factor_X_load;
u8_factor_1/255 CAL_tps_commanded_during_fault;
u16_distance_mm_div2 CAL_wheel_speed_multiplier_front;
u16_distance_mm_div2 CAL_wheel_speed_multiplier_rear;
u8_factor_1/100 CAL_cruise_integral_term_limit;
u8_factor_1/100 CAL_cruise_derivative_term_limit;
u8_factor_1/100[4] CAL_cruise_integral_gain_manual_longbox;
u8_factor_1/100[4] CAL_cruise_integral_gain_manual_cr;
u8_factor_1/100[4] CAL_cruise_integral_gain_ips;
u8_gear[4] CAL_cruise_integral_gain_ips_X_gear;
u8_gear[4] CAL_cruise_integral_gain_manual_longbox_X_gear;
u8_gear[4] CAL_cruise_integral_gain_manual_cr_X_gear;
u8_speed_kph CAL_cruise_speed_deadband;
u8_speed_kph CAL_cruise_speed_error_limit;
u8_factor_1/255[4] CAL_cruise_proportional_gain_ips;
u8_gear[4] CAL_cruise_proportional_gain_ips_X_gear;
u8_factor_1/255[4] CAL_cruise_derivative_gain_ips;
u8_gear[4] CAL_cruise_derivative_gain_ips_X_gear;
u8_factor_1/255[4] CAL_cruise_proportional_gain_manual_longbox;
u8_gear[4] CAL_cruise_proportional_gain_manual_longbox_X_gear;
u8_factor_1/255[4] CAL_cruise_derivative_gain_manual_longbox;
u8_gear[4] CAL_cruise_derivative_gain_manual_longbox_X_gear;
uint8_t[4] CAL_cruise_proportional_gain_manual_cr;
u8_gear[4] CAL_cruise_proportional_gain_manual_cr_X_gear;
uint8_t[4] CAL_cruise_derivative_gain_manual_cr;
u8_gear[4] CAL_cruise_derivative_gain_manual_cr_X_gear;
u8_time_10ms CAL_cruise_resume_timer;
u8_speed_1/100kph CAL_cruise_speed_increment;
u8_speed_1/100kph CAL_cruise_speed_decrement;
u8_speed_kph[2] CAL_cruise_speed_limit;
u8_speed_1/10kph CAL_cruise_speed_increment2;
u16_time_10ms CAL_cruise_brake_cancel_time;
u16_time_5ms CAL_ac_compressor_runtime_min;
u8_factor_1/255 CAL_ac_compressor_max_throttle;
u8_factor_1/255 CAL_ac_compressor_max_coolant_temp_max;
u8_rspeed_125/4+500rpm CAL_ac_compressor_engine_speed_max;
u8_rspeed_125/4+500rpm[2] CAL_ac_compressor_engine_speed2;
u8_speed_kph[2] CAL_ac_compressor_deactivate_car_speed;
u8_rspeed_4rpm[2] CAL_ac_compressor_engine_speed3;
u8_factor_1/255 CAL_ac_compressor_max_coolant_temp_min;
u8_rspeed_125/4+500rpm CAL_ac_compressor_engine_speed_min;
u8_count CAL_ac_evap_timer_ticks_5ms;
uint16_t CAL_ac_output_pwm_freq;
uint8_t[4] CAL_ac_load_limit;
u8_rspeed_125/4+500rpm[4] CAL_ac_load_limit_X_rpm;
uint16_t[10] CAL_trans_gear_ratio_tour;
uint16_t[12] CAL_trans_gear_ratio_sport;
uint16_t[2] CAL_trans_gear_lookup_unknown2;
bool CAL_vehicle_speed_limit_enforce;
u8_speed_kph CAL_vehicle_speed_limit;
uint8_t CAL_vehicle_speed_limit_enforce_margin;
u8_rspeed_4+500rpm[5] CAL_traction_slip_threshold_per_gear_ips;
u8_rspeed_4+500rpm CAL_traction_slip_threshold_1st_Gear;
u8_rspeed_4+500rpm[5] CAL_traction_slip_threshold_per_gear_manual;
uint16_t[6] CAL_traction_gear_speed_ratios_ips;
uint16_t[6] CAL_traction_gear_speed_ratios_long;
uint16_t[6] CAL_traction_gear_speed_ratios_cr;
u8_factor_1/255 CAL_traction_inhibit_cornering_offset;
u8_factor_1/255 CAL_traction_inhibit_cornering_base;
u8_factor_1/255 CAL_traction_steering_increase_factor_min;
u8_factor_1/100 CAL_traction_steering_rate_factor;
uint16_t[4] CAL_traction_comp_maf_accum_manual;
u16_mass_mg[4] CAL_traction_comp_maf_accum_manual_X_maf_accum;
u16_angle_1/10deg CAL_traction_steering_angle_max_unknown;
u8_rspeed_4+500rpm CAL_traction_slip_threshold_hysteresis_offset;
u8_time_100ms CAL_traction_timer_per_gear_intervention;
u8_time_100ms CAL_traction_inhibit_accel_pedal_timer;
u8_speed_kph CAL_traction_enable_speed;
u8_temp_5/8-40c CAL_traction_coldstart_coolant_threshold;
uint8_t CAL_traction_timer_intervention2;
u16_factor_1/1023 CAL_traction_inhibit_accel_pedal_min;
u8_speed_kph CAL_traction_threshold_car_speed;
u8_gear CAL_traction_gear_offset_unknown;
u16_rspeed_rpm[8] CAL_traction_power_based_rpm_thresholds;
u16_power_1/100kw[8] CAL_traction_power_based_rpm_thresholds_X_power;
uint8_t CAL_traction_wheelspeed_front_accel_threshold;
u8_factor_1/255 CAL_traction_steering_angle_smooth_factor;
u8_temp_5/8-40c CAL_trans_fluid_temp_zone1_min;
u8_temp_5/8-40c CAL_trans_fluid_temp_zone2_threshold;
u8_temp_5/8-40c CAL_trans_fluid_temp_optimal_min;
u8_temp_5/8-40c CAL_trans_fluid_temp_optimal_max;
u8_temp_5/8-40c CAL_trans_pump_coolant_activate_min;
u8_temp_5/8-40c CAL_trans_fluid_temp_zone1_max;
u8_temp_5/8-40c CAL_trans_pump_coolant_activate_max;
u8_temp_5/8-40c CAL_trans_pump_coolant_deactivate_min;
u8_temp_5/8-40c CAL_trans_pump_coolant_deactivate_max;
u8_temp_5/8-40c CAL_trans_fluid_temp_overheat_hysteresis;
u8_speed_kph[2] CAL_trans_pump_speed_enable;
uint16_t[2] CAL_trans_temp_voltage_threshold;
u8_temp_5/8-40c CAL_trans_fluid_P2797_threshold;
    if (15 < CAL_tps_delta_rate_window_size) {
                    CAL_tps_rate_steadystate_threshold_X_rpm,
                    CAL_tps_rate_steadystate_threshold_Y_tps);
    if ((((car_speed_u8 < CAL_vehicle_moving_speed_min) || ((short)obd_ii_idle_speed_error___ < 1))
    LEA_load_alphaN_learned_trim_X_rpm[i] = CAL_load_alphaN_base_X_engine_speed[i];
    LEA_torque_torque_to_tps_scaling_X_engine_speed[i] = CAL_load_to_tps_mapping_X_rpm[i];
    if (LEA_load_alphaN_learned_trim_X_rpm[i] == CAL_load_alphaN_base_X_engine_speed[i]) {
    if (LEA_torque_torque_to_tps_scaling_X_engine_speed[i] == CAL_load_to_tps_mapping_X_rpm[i]) {
    LEA_load_alphaN_learned_trim_X_rpm[i] = CAL_load_alphaN_base_X_engine_speed[i];
    LEA_torque_torque_to_tps_scaling_X_engine_speed[i] = CAL_load_to_tps_mapping_X_rpm[i];
                         CAL_cooling_fan_afterrun_Y_coolant_temp,CAL_cooling_fan_afterrun);
                    CAL_cooling_fan_duty_cycle_stopped_X_coolant_temp);
    if (runtime_since_start < CAL_cooling_fan_startup_time) {
        radiator_fan_dc_hotstart = CAL_cooling_fan_hotstart_dutycycle;
                    CAL_cooling_fan_base_engine_on_X_coolant_temp,
                    CAL_cooling_fan_base_engine_on_Y_carspeed);
                      CAL_cooling_fan_ac_off_X_air_temp,CAL_cooling_fan_ac_off_Y_carspeed);
                      CAL_cooling_fan_ac_on_X_air_temp,CAL_cooling_fan_ac_on_Y_carspeed);
    else if (runtime_since_start < CAL_cooling_fan_startup_time) {
                  CAL_cooling_fan_scaling_X_dutycycle);
    else if (((radiator_fan_duty_cycle_target < CAL_cooling_fan_engine_bay_radfan_threshold_enable)
             || (temp_engine_air_cooling_control < CAL_cooling_fan_engine_bay_airtemp_enable)) ||
      if (radiator_fan_duty_cycle_target <= CAL_cooling_fan_engine_bay_radfan_threshold_disable) {
    if (TC_ENABLED < CAL_traction_mode) {
  if (((traction_intervention_flags & 0b01000000) != 0) && (TC_ENABLED < CAL_traction_mode)) {
  if (((fuel_level < CAL_cluster_fuel_level_zero_clip_threshold) ||
  if ((fuel_level < CAL_cluster_fuel_level_warning_threshold[0]) || (cluster_run_state == 1)) {
                  CAL_cluster_oil_pressure_warn_threshold_X_engine_speed);
    else if (coolant_temp < CAL_cluster_coolant_warning[1]) {
  if ((engine_speed_2 < CAL_exhaust_flap_RPM_threshold_open) ||
     (load_mass_per_stroke < CAL_exhaust_flap_load_threshold_open)) {
    if ((engine_speed_2 < CAL_exhaust_flap_RPM_threshold_close) ||
       (load_mass_per_stroke < CAL_exhaust_flap_load_threshold_close)) {
                           CAL_exhaust_flap_state_control_tour_X_rpm,
                           CAL_exhaust_flap_state_control_tour_Y_accel_pedal,
                           CAL_exhaust_flap_state_control_tour);
                           CAL_exhaust_flap_state_control_sport_X_rpm,
                           CAL_exhaust_flap_state_control_sport_Y_accel_pedal,
                           CAL_exhaust_flap_state_control_sport);
                         CAL_exhaust_flap_state_control_race_X_rpm,
                         CAL_exhaust_flap_state_control_race_Y_accel_pedal,
                         CAL_exhaust_flap_state_control_race);
       (obd_ii_engine_speed < CAL_roughness_enable_rpm[1])) &&
     (load_mass_per_stroke < CAL_roughness_enable_load[1])) {
    wheel_speed_timer1 = CAL_wheel_speed_timer1;
                    // CAL_cluster_dte_min_distance_threshold has value 1
    fuel_usage_timer1 = CAL_cluster_fuel_range_smoothing_interval;
    cluster_fuel_mileage_update_timer = CAL_cluster_fuel_mileage_update_timer;
    fuel_usage_reset_request_timer = CAL_cluster_fuel_usage_reset_request_timer;
                  CAL_load_cylinder_efficiency_X_engine_speed,CAL_load_cylinder_efficiency_Y_map);
                  CAL_load_source_selection_threshold_by_tps_X_rpm);
                  CAL_load_alphaN_base_X_engine_speed,CAL_load_alphaN_base_Y_tps);
                  CAL_load_to_tps_mapping_X_rpm,CAL_load_to_tps_mapping_Y_load);
                  CAL_load_baro_gain_X_rpm,CAL_load_baro_gain_Y_load);
                          CAL_load_volumetric_efficiency,CAL_load_volumetric_efficiency_X_rpm,
                          CAL_load_volumetric_efficiency_Y_load);
                    CAL_load_plausibility_test_delta_X_rpm,CAL_load_plausibility_test_delta_Y_tps);
    if ((car_speed_u8 < CAL_vehicle_moving_speed_min) || ((short)obd_ii_idle_speed_error___ < 0)) {
    obd_ii_response[3] = CAL_prog_version[0];
    obd_ii_response[4] = CAL_prog_version[1];
    obd_ii_response[3] = CAL_prog_version[4];
    obd_ii_response[4] = CAL_prog_version[5];
    obd_ii_response[3] = CAL_prog_version[8];
    obd_ii_response[4] = CAL_prog_version[9];
    obd_ii_response[3] = CAL_prog_version[0xc];
    obd_ii_response[4] = CAL_prog_version[0xd];
    obd_ii_response[3] = CAL_prog_version[0x10];
    obd_ii_response[4] = CAL_prog_version[0x11];
    obd_ii_response[3] = CAL_prog_version[0x14];
    obd_ii_response[4] = CAL_prog_version[0x15];
    obd_ii_response[3] = CAL_prog_version[0x18];
    obd_ii_response[4] = CAL_prog_version[0x19];
    obd_ii_response[3] = CAL_prog_version[0x1c];
    obd_ii_response[4] = CAL_prog_version[0x1d];
        obd_ii_response[bVar1] = CAL_misc_calid[j];
     (((ignition_on_flags & 1) != 0 && (car_speed_u8 < CAL_cooling_fan_speed_disable_speed)))) {
  if (accel_pedal_pos < CAL_cruise_accel_pedal_override_threshold_exit) {
        dca_accel_pedal = accel_pedal_pos + CAL_dca_enable_tps_margin;
                      CAL_dca_tps_limit_manual,CAL_dca_tps_limit_manual_X_time);
                      CAL_dca_unknown_ips_nolc,CAL_dca_unknown_ips_nolc_X_time);
                    CAL_cooling_thermostat_warmup_load_factor_X_load);
       (coolant_temp < CAL_cooling_thermostat_open)) {
                      CAL_cruise_proportional_gain_ips_X_gear);
                      CAL_cruise_integral_gain_ips_X_gear);
                      CAL_cruise_derivative_gain_ips_X_gear);
                      CAL_cruise_proportional_gain_manual_longbox_X_gear);
                      CAL_cruise_integral_gain_manual_longbox_X_gear);
                      CAL_cruise_derivative_gain_manual_longbox_X_gear);
                         CAL_cruise_proportional_gain_manual_cr_X_gear);
                      CAL_cruise_integral_gain_manual_cr_X_gear);
                      CAL_cruise_derivative_gain_manual_cr_X_gear);
           (car_speed_u8 < CAL_cruise_speed_limit[0])) {
                          CAL_load_to_tps_mapping,CAL_load_to_tps_mapping_X_rpm,
                          CAL_load_to_tps_mapping_Y_load);
                          CAL_load_to_tps_mapping_X_rpm,CAL_load_to_tps_mapping_Y_load);
                              CAL_cruise_integral_gain_ips_X_gear);
                              CAL_cruise_integral_gain_ips_X_gear);
        cruise_speed_target = cruise_speed_target + CAL_cruise_speed_increment;
        cruise_speed_target = cruise_speed_target - CAL_cruise_speed_decrement;
                  CAL_load_alphaN_base_X_engine_speed,CAL_load_alphaN_base_Y_tps);
                    CAL_load_to_tps_mapping,CAL_load_to_tps_mapping_X_rpm,
                    CAL_load_to_tps_mapping_Y_load);
                  CAL_load_to_tps_mapping_X_rpm,CAL_load_to_tps_mapping_Y_load);
        cruise_brake_cancel_timer = CAL_cruise_brake_cancel_time;
  else if (coolant_temp < CAL_ac_compressor_max_coolant_temp_min) {
  else if (engine_speed_3 < CAL_ac_compressor_engine_speed_min) {
  else if (((engine_speed_3 < CAL_ac_compressor_engine_speed2[1]) && (DAT_400028ea == 0)) ||
  else if (car_speed_u8 < CAL_ac_compressor_deactivate_car_speed[1]) {
          DAT_400028d7 = CAL_ac_evap_timer_ticks_5ms + 0xff;
      program_version[i] = CAL_prog_version[i];
      program_version[i] = CAL_prog_version[i];
    gear_lookup[0] = CAL_trans_gear_ratio_tour[0];
    gear_lookup[1] = CAL_trans_gear_ratio_tour[1];
    gear_lookup[2] = CAL_trans_gear_ratio_tour[2];
    gear_lookup[3] = CAL_trans_gear_ratio_tour[3];
    gear_lookup[4] = CAL_trans_gear_ratio_tour[4];
    gear_lookup[5] = CAL_trans_gear_ratio_tour[5];
    gear_lookup[6] = CAL_trans_gear_ratio_tour[6];
    gear_lookup[7] = CAL_trans_gear_ratio_tour[7];
    gear_lookup[8] = CAL_trans_gear_ratio_tour[8];
    gear_lookup[9] = CAL_trans_gear_ratio_tour[9];
    gear_lookup[10] = CAL_trans_gear_lookup_unknown2[0];
    gear_lookup[0xb] = CAL_trans_gear_lookup_unknown2[1];
    gear_lookup[0] = CAL_trans_gear_ratio_sport[0];
    gear_lookup[1] = CAL_trans_gear_ratio_sport[1];
    gear_lookup[2] = CAL_trans_gear_ratio_sport[2];
    gear_lookup[3] = CAL_trans_gear_ratio_sport[3];
    gear_lookup[4] = CAL_trans_gear_ratio_sport[4];
    gear_lookup[5] = CAL_trans_gear_ratio_sport[5];
    gear_lookup[6] = CAL_trans_gear_ratio_sport[6];
    gear_lookup[7] = CAL_trans_gear_ratio_sport[7];
    gear_lookup[8] = CAL_trans_gear_ratio_sport[8];
    gear_lookup[9] = CAL_trans_gear_ratio_sport[9];
    gear_lookup[10] = CAL_trans_gear_ratio_sport[10];
    gear_lookup[0xb] = CAL_trans_gear_ratio_sport[0xb];
             speed_limit_target_ramped - CAL_vehicle_speed_limit_enforce_margin;
             speed_limit_target_ramped + CAL_vehicle_speed_limit_enforce_margin;
                      CAL_load_to_tps_mapping_Y_load);
    LEA_traction_gear_speed_ratios[0] = CAL_traction_gear_speed_ratios_ips;
    LEA_traction_gear_speed_ratios[1] = CAL_traction_gear_speed_ratios_ips + 1;
    LEA_traction_gear_speed_ratios[2] = CAL_traction_gear_speed_ratios_ips + 2;
    LEA_traction_gear_speed_ratios[3] = CAL_traction_gear_speed_ratios_ips + 3;
    LEA_traction_gear_speed_ratios[4] = CAL_traction_gear_speed_ratios_ips + 4;
    LEA_traction_gear_speed_ratios[5] = CAL_traction_gear_speed_ratios_ips + 5;
    LEA_traction_slip_threshold_per_gear[1] = CAL_traction_slip_threshold_per_gear_ips;
    LEA_traction_slip_threshold_per_gear[2] = CAL_traction_slip_threshold_per_gear_ips + 1;
    LEA_traction_slip_threshold_per_gear[3] = CAL_traction_slip_threshold_per_gear_ips + 2;
    LEA_traction_slip_threshold_per_gear[4] = CAL_traction_slip_threshold_per_gear_ips + 3;
    LEA_traction_slip_threshold_per_gear[5] = CAL_traction_slip_threshold_per_gear_ips + 4;
    LEA_traction_gear_speed_ratios[0] = CAL_traction_gear_speed_ratios_long;
    LEA_traction_gear_speed_ratios[1] = CAL_traction_gear_speed_ratios_long + 1;
    LEA_traction_gear_speed_ratios[2] = CAL_traction_gear_speed_ratios_long + 2;
    LEA_traction_gear_speed_ratios[3] = CAL_traction_gear_speed_ratios_long + 3;
    LEA_traction_gear_speed_ratios[4] = CAL_traction_gear_speed_ratios_long + 4;
    LEA_traction_gear_speed_ratios[5] = CAL_traction_gear_speed_ratios_long + 5;
    LEA_traction_slip_threshold_per_gear[1] = CAL_traction_slip_threshold_per_gear_manual;
    LEA_traction_slip_threshold_per_gear[2] = CAL_traction_slip_threshold_per_gear_manual + 1;
    LEA_traction_slip_threshold_per_gear[3] = CAL_traction_slip_threshold_per_gear_manual + 2;
    LEA_traction_slip_threshold_per_gear[4] = CAL_traction_slip_threshold_per_gear_manual + 3;
    LEA_traction_slip_threshold_per_gear[5] = CAL_traction_slip_threshold_per_gear_manual + 4;
    LEA_traction_gear_speed_ratios[0] = CAL_traction_gear_speed_ratios_cr;
    LEA_traction_gear_speed_ratios[1] = CAL_traction_gear_speed_ratios_cr + 1;
    LEA_traction_gear_speed_ratios[2] = CAL_traction_gear_speed_ratios_cr + 2;
    LEA_traction_gear_speed_ratios[3] = CAL_traction_gear_speed_ratios_cr + 3;
    LEA_traction_gear_speed_ratios[4] = CAL_traction_gear_speed_ratios_cr + 4;
    LEA_traction_gear_speed_ratios[5] = CAL_traction_gear_speed_ratios_cr + 5;
    LEA_traction_slip_threshold_per_gear[1] = CAL_traction_slip_threshold_per_gear_manual;
    LEA_traction_slip_threshold_per_gear[2] = CAL_traction_slip_threshold_per_gear_manual + 1;
    LEA_traction_slip_threshold_per_gear[3] = CAL_traction_slip_threshold_per_gear_manual + 2;
    LEA_traction_slip_threshold_per_gear[4] = CAL_traction_slip_threshold_per_gear_manual + 3;
    LEA_traction_slip_threshold_per_gear[5] = CAL_traction_slip_threshold_per_gear_manual + 4;
    if (((coolant_temp_engine_stopped < CAL_traction_coldstart_coolant_threshold) &&
                      CAL_traction_comp_maf_accum_manual_X_maf_accum);
                    // CAL_traction_mode always has value TC_ENABLED in the OEM configuration.
        (TC_VARIABLE < CAL_traction_mode)))) {
                      CAL_traction_power_based_rpm_thresholds_X_power);
        traction_inhibit_accel_pedal_timer = CAL_traction_inhibit_accel_pedal_timer;
          traction_per_gear_timer100ms_intervention[i] = CAL_traction_timer_per_gear_intervention;
            CAL_traction_timer_per_gear_intervention) {
        if (traction_per_gear_timer100ms_intervention[i] < CAL_traction_timer_per_gear_intervention)
        tc_timer_unknown1 = CAL_traction_timer_per_gear_intervention;
        tc_intervention_timer = CAL_traction_timer_intervention2;
        tc_intervention_timer = CAL_traction_timer_intervention2;
        tc_timer_unknown1 = CAL_traction_timer_per_gear_intervention;
        tc_intervention_timer = CAL_traction_timer_intervention2;
        tc_timer_unknown1 = CAL_traction_timer_per_gear_intervention;
            tc_gear3_unknown = car_current_gear - CAL_traction_gear_offset_unknown;
          tc_gear3_unknown = car_current_gear + CAL_traction_gear_offset_unknown;
            traction_timer_intevention_gearchange = CAL_traction_timer_per_gear_intervention;
            traction_timer_intevention_gearchange = CAL_traction_timer_intervention2;
        traction_per_gear_timer100ms_intervention[i] = CAL_traction_timer_per_gear_intervention;
      tc_timer_unknown1 = CAL_traction_timer_per_gear_intervention;
      tc_intervention_timer = CAL_traction_timer_intervention2;
      traction_per_gear_timer100ms_intervention[i] = CAL_traction_timer_per_gear_intervention;
    tc_timer_unknown1 = CAL_traction_timer_per_gear_intervention;
    tc_intervention_timer = CAL_traction_timer_intervention2;
  if (car_speed_u8 < CAL_trans_pump_speed_enable[0]) {
     (trans_fluid_temp_u8 <= CAL_trans_fluid_temp_zone1_max)) {
    if ((trans_fluid_temp_u8 < CAL_trans_fluid_temp_optimal_min) ||
      if (trans_fluid_temp_u8 < CAL_trans_fluid_temp_overheat_hysteresis) {
     (coolant_temp <= CAL_trans_pump_coolant_activate_max)) {
  else if ((coolant_temp <= CAL_trans_pump_coolant_deactivate_min) ||
    if (trans_temp_voltage < CAL_trans_temp_voltage_threshold[1]) {

#endif /* CAL_VEHICLE_H */
