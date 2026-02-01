/*
 * cal_engine.h
 *
 * Engine Control Calibration Variables
 *
 * This file contains calibration parameters for core engine control:
 * - Torque management and limiters
 * - Rev limit control (soft and hard)
 * - VVT (Variable Valve Timing) control
 * - Idle speed control
 */

#ifndef CAL_ENGINE_H
#define CAL_ENGINE_H

#include "types.h"

/* ========================================================================
 * Engine Control Calibrations
 * ======================================================================== */

u8_rspeed_125/4+500rpm[2] CAL_torque_torque_to_tps_scaling_rpm_range;
bool CAL_vvt_low_load_ips_enable;
u16_rspeed_rpm CAL_revlimit_fuelcut_hysteresis;
u8_time_50ms CAL_revlimit_enforce_delay_after_start;
u16_factor_1/1023 CAL_idle_tps_max_opening;
uint8_t[8] CAL_idle_comp_accel_pedal_pos;
u8_rspeed_rpm[8] CAL_idle_comp_iat;
u8_temp_5/8-40c[8] CAL_idle_comp_iat_X_iat;
u8_speed_kph CAL_idle_car_moving_threshold;
u8_speed_1/10kph CAL_idle_clutch_antistall_speed_threshold;
u8_rspeed_4rpm[8] CAL_idle_comp_carspeed_ips;
u8_speed_kph[8] CAL_idle_comp_carspeed_ips_X_carspeed;
u8_rspeed_4rpm[8] CAL_idle_comp_carspeed_manual;
u8_speed_kph[8] CAL_idle_comp_carspeed_manual_X_carspeed;
uint16_t[8] CAL_idle_comp_vehicle_speed_ips;
uint16_t[8] CAL_idle_comp_vehicle_speed_manual;
u16_speed_1/100kph[8] CAL_idle_comp_vehicle_speed_ips_X_vehicle_speed;
u16_speed_1/100kph[8] CAL_idle_comp_vehicle_speed_manual_X_carspeed;
u8_rspeed_4+500rpm[16] CAL_idle_target_ips_coolant_fallback;
u8_rspeed_4+500rpm[16] CAL_idle_target_ips;
u8_rspeed_4+500rpm[16] CAL_idle_target_manual_tour;
u8_rspeed_4+500rpm[16] CAL_idle_target_manual_sport;
u8_temp_5/8-40c[16] CAL_idle_target_manual_tour_X_coolant_temp;
u8_temp_5/8-40c[16] CAL_idle_target_manual_sport_X_coolant_temp;
int16_t[8] CAL_idle_comp_baro2;
u16_pressure_mbar[8] CAL_idle_comp_baro2_X_ambiant_baro;
u16_flow_100mg/s[16] CAL_idle_comp_while_moving;
u16_rspeed_rpm[16] CAL_idle_comp_while_moving_X_rpm;
int16_t[8] CAL_idle_comp_ecu_voltage;
u16_voltage_18/1023v[8] CAL_idle_comp_ecu_voltage_X_voltage;
u8_temp_5/8-40c[16] CAL_idle_target_ips_X_coolant_temp;
u8_temp_5/8-40c[16] CAL_idle_target_ips_coolant_fallback_X_coolant_temp;
uint16_t[16] CAL_idle_error_correction_unknown_X_speed_error;
uint16_t[16] CAL_idle_error_correction_unknown;
uint8_t[4] CAL_idle_comp_steering;
uint8_t[4] CAL_idle_comp_steering_X_steering_load;
uint16_t[16] CAL_idle_air_control_proportional;
uint16_t[16] CAL_idle_air_control_proportional_X_speed_error;
u8_temp_5/8-40c CAL_idle_sensor_fault_coolant_temp;
u8_factor_1/255[64] CAL_idle_comp_tps_while_cranking;
u8_pressure_4mbar[4] CAL_idle_comp_tps_while_cranking_X_baro;
u8_temp_5/8-40c[16] CAL_idle_comp_tps_while_cranking_Y_coolant_temp;
u8_speed_kph CAL_idle_low_car_speed_enter;
u8_speed_kph CAL_idle_low_car_speed_exit;
uint16_t CAL_vvt_pwm_driver_divisor;
u8_time_100ms CAL_vvt_zero_target_timeout;
u8_rspeed_125/4+500rpm[6] CAL_vvt_intake_advance_base_low_load_X_engine_speed;
u8_load_4mg/stroke[6] CAL_vvt_intake_advance_base_low_load_Y_load;
u8_angle_1/4deg[36] CAL_vvt_exhaust_advance_base_low_load;
u8_rspeed_125/4+500rpm[6] CAL_vvt_exhaust_advance_base_low_load_X_engine_speed;
u8_load_4mg/stroke[6] CAL_vvt_exhaust_advance_base_low_load_Y_load;
u8_angle_1/4deg[16] CAL_vvt_exhaust_comp_temp;
u8_temp_5/8-40c[16] CAL_vvt_exhaust_comp_temp_X_coolant_temp;
u8_angle_1/4deg[36] CAL_vvt_intake_advance_base_low_load;
u8_temp_5/8-40c CAL_vvt_low_load_map_enable_temp;
u8_angle_1/4deg CAL_vvt_exhaust_park_position;
bool CAL_vvt_low_load_disable;
u16_factor_1/255 CAL_vvt_error_gain_startup;
u8_angle_1/4deg[256] CAL_vvt_intake_advance_base;
u8_rspeed_125/4+500rpm[16] CAL_vvt_intake_advance_base_X_engine_speed;
u8_load_4mg/stroke[16] CAL_vvt_intake_advance_base_Y_load;
u8_angle_1/4deg[256] CAL_vvt_exhaust_advance_base;
u8_angle_1/4deg[16] CAL_vvt_intake_advance_coolant_offset;
u8_rspeed_125/4+500rpm[16] CAL_vvt_exhaust_advance_base_X_engine_speed;
u8_temp_5/8-40c[16] CAL_vvt_intake_advance_coolant_offset_X_temp;
u8_load_4mg/stroke[16] CAL_vvt_exhaust_advance_base_Y_load;
u8_time_100ms[8] CAL_vvt_start_timer;
u8_temp_5/8-40c[8] CAL_vvt_start_timer_X_coolant_temp;
uint16_t CAL_vvt_integral_gain;
bool CAL_revlimit_throttle_clamp;
u8_torque_2nm[4] CAL_torque_limit_by_coolant;
u8_temp_5/8-40c[4] CAL_torque_limit_by_coolant_X_coolant;
u8_rspeed_125/4+500rpm[8] CAL_torque_limit_by_engine_speed_manual_X_engine_speed;
u8_torque_2nm[8] CAL_torque_limit_by_engine_speed_manual;
u8_torque_2nm[8] CAL_torque_limit_by_engine_speed_ips;
u8_rspeed_125/4+500rpm[8] CAL_torque_limit_by_engine_speed_ips_X_engine_speed;
u8_torque_2nm CAL_revlimit_torque_limit_confirmation_threshold;
u8_factor_1/255[256] CAL_torque_limit_base_factor;
u8_rspeed_125/4+500rpm[16] CAL_torque_limit_base_factor_X_rpm;
u8_load_4mg/stroke[16] CAL_torque_limit_base_factor_Y_load;
u8_torque_nm[400] CAL_torque_engine_friction_speed_component;
u8_rspeed_125/4+500rpm[20] CAL_torque_engine_friction_speed_component_X_engine_speed;
u8_load_1173mg/255stroke[20] CAL_torque_engine_friction_speed_component_Y_load;
u16_torque_nm[256] CAL_torque_load_to_torque;
u16_rspeed_rpm[16] CAL_torque_load_to_torque_X_engine_speed;
u16_load_mg/stroke[16] CAL_torque_load_to_torque_Y_load;
u8_rspeed_125/4+500rpm[16] CAL_torque_external_request_minimum_X_engine_speed;
u16_torque_nm[16] CAL_torque_torque_to_load_Y_torque;
u8_torque_4nm[16] CAL_torque_external_request_minimum_Y_torque;
u8_factor_1/100[256] CAL_torque_external_request_minimum;
u16_load_mg/stroke[256] CAL_torque_torque_to_load;
uint8_t[256] CAL_torque_factor_base_engine_speed_load;
u8_rspeed_125/4+500rpm[16] CAL_torque_factor_base_engine_speed_load_X_engine_speed;
u8_load_4mg/stroke[16] CAL_torque_factor_base_engine_speed_load_Y_load;
u8_angle_1/4-64deg[256] CAL_torque_ign_retard_base;
u8_rspeed_125/4+500rpm[16] CAL_torque_ign_retard_base_X_engine_speed;
u8_factor_1/255[16] CAL_torque_ign_retard_base_Y_torque_reduction_factor;
u8_factor_1/255[256] CAL_torque_factor_base_ign_intervention;
uint8_t[16] CAL_torque_factor_base_ign_intervention_X_engine_speed;
u8_angle_1/4deg[16] CAL_torque_factor_base_ign_intervention_Y_ign_adv;
u16_rspeed_rpm[16] CAL_torque_torque_to_load_X_engine_speed;
uint8_t[8] CAL_torque_engine_ac_load_scaler;
u8_rspeed_125/4+500rpm[8] CAL_torque_engine_ac_load_scaler_X_engine_speed;
u8_torque_nm[64] CAL_torque_engine_friction_temp_component;
u8_temp_5/8-40c[8] CAL_torque_engine_friction_temp_component_X_coolant;
u8_load_4mg/stroke[8] CAL_torque_engine_friction_temp_component_Y_load;
u8_torque_nm[16] CAL_torque_engine_ac_load_base;
uint8_t[16] CAL_torque_engine_ac_load_base_X_ac;
u8_factor_1/255[8] CAL_torque_limit_proportional;
uint8_t[8] CAL_torque_limit_proportional_X_load_error;
u16_factor_1/1023 CAL_torque_proportional_limit_positive;
u16_factor_1/1023 CAL_torque_proportional_limit_negative;
u8_factor_1/255[8] CAL_torque_limit_integral;
uint8_t[8] CAL_torque_limit_integral_X_load_error;
u16_factor_1/1023 CAL_torque_unknown_tps_clamp3;
u16_factor_1/1023 CAL_torque_unknown_tps_clamp4;
u8_torque_nm CAL_torque_hysteresis_threshold1;
u8_factor_1/255[7] CAL_revlimit_airflow_gain_from_rpm;
uint8_t[7] CAL_revlimit_airflow_gain_from_integrator_X_gear;
uint8_t[7] CAL_revlimit_airflow_gain_from_rpm_X_gear;
u16_temp_5/8-40c[4] CAL_revlimit_speedbase_manual_sport_X_coolant_temp;
u8_factor_1/100 CAL_revlimit_integrator_limit;
u16_time_5ms[4] CAL_revlimit_speedbase_manual_sport_Y_timer;
u16_temp_5/8-40c[4] CAL_revlimit_speedbase_manual_tour_X_coolant_temp;
u16_time_5ms[4] CAL_revlimit_speedbase_manual_tour_Y_timer;
uint16_t[4] CAL_revlimit_coldstart_rpm_envelope_X_index;
u16_rspeed_rpm CAL_revlimit_limp_mode;
u8_count CAL_revlimit_overrun_count_threshold;
u8_time_100ms CAL_revlimit_overspeed_time;
u8_mass_g CAL_revlimit_flow_proportional_term;
u8_mass_g CAL_revlimit_flow_unknown2;
u16_temp_5/8-40c[4] CAL_revlimit_speedbase_ips_sport_X_coolant_temp;
u8_temp_5/8-40c CAL_revlimit_coolant_coldstart_threshold;
u16_rspeed_rpm[4] CAL_revlimit_coldstart_rpm_envelope;
u16_temp_5/8-40c[4] CAL_revlimit_speedbase_ips_tour_X_coolant_temp;
u16_time_5ms[4] CAL_revlimit_speedbase_ips_tour_Y_timer;
u16_time_5ms[4] CAL_revlimit_speedbase_ips_sport_Y_timer;
uint8_t[7] CAL_revlimit_escalation_integrator_step;
uint8_t[7] CAL_revlimit_escalation_integrator_step_X_gear;
u8_rspeed_2rpm[7] CAL_revlimit_trim_per_gear;
u8_gear[7] CAL_revlimit_trim_per_gear_X_gear;
u8_time_250ms CAL_revlimit_startup_delay;
u16_rspeed_rpm CAL_revlimit_max_with_speedlimit;
u16_rspeed_rpm[16] CAL_revlimit_speedbase_ips_tour;
u16_rspeed_rpm[16] CAL_revlimit_speedbase_manual_tour;
u16_rspeed_rpm[16] CAL_revlimit_speedbase_ips_sport;
u16_rspeed_rpm[16] CAL_revlimit_speedbase_manual_sport;
u8_factor_1/255[7] CAL_revlimit_airflow_gain_from_rpm_delta;
uint8_t[7] CAL_revlimit_airflow_gain_from_rpm_delta_X_gear;
u8_factor_1/255[7] CAL_revlimit_airflow_gain_from_integrator;
u8_flow_2g/s[7] CAL_revlimit_airflow_threshold;
u8_count CAL_revlimit_startup_offset_decrement;
u8_gear[7] CAL_revlimit_airflow_threshold_X_gear;
u8_rspeed_25rpm CAL_revlimit_rpm_rate_limit;
uint8_t CAL_revlimit_maf_error_max_10g;
                     CAL_torque_torque_to_tps_scaling_rpm_range[0]) {
                   CAL_torque_torque_to_tps_scaling_rpm_range[0]) {
                    CAL_idle_comp_carspeed_manual_X_carspeed);
                         CAL_idle_target_ips_coolant_fallback_X_coolant_temp);
                         CAL_idle_target_ips_coolant_fallback_X_coolant_temp);
                         CAL_idle_target_ips_coolant_fallback_X_coolant_temp);
                       CAL_idle_target_manual_tour_X_coolant_temp);
                       CAL_idle_target_manual_tour_X_coolant_temp);
                       CAL_idle_target_manual_sport_X_coolant_temp);
                       CAL_idle_target_manual_sport_X_coolant_temp);
                  CAL_idle_comp_baro2_X_ambiant_baro);
                    CAL_idle_comp_vehicle_speed_ips_X_vehicle_speed);
                    CAL_idle_comp_vehicle_speed_manual_X_carspeed);
                  CAL_idle_comp_ecu_voltage_X_voltage);
                  CAL_idle_comp_tps_while_cranking_X_baro,
                  CAL_idle_comp_tps_while_cranking_Y_coolant_temp);
  if (car_speed_u8 < CAL_idle_car_moving_threshold) {
                     CAL_idle_air_control_proportional_X_speed_error);
                     CAL_idle_error_correction_unknown_X_speed_error);
  if (((((COD_base[1] >> 0x15 & 3) == 2) && (uVar6 < CAL_idle_clutch_antistall_speed_threshold)) &&
    if (((clutch_pos_sensor & 4) != 0) && (uVar6 < CAL_idle_clutch_antistall_speed_threshold)) {
  else if (idle_tps_calculated < CAL_idle_tps_max_opening) {
    idle_tps_requested = CAL_idle_tps_max_opening;
            (0x1c,2,(longlong)(int)(1000000 / CAL_vvt_pwm_driver_divisor),5000,1,0,10000000);
            (0xf,2,(longlong)(int)(1000000 / CAL_vvt_pwm_driver_divisor),5000,1,0,10000000);
  vvt_inlet_b1_zero_timer = CAL_vvt_zero_target_timeout;
  vvt_exhaust_b1_zero_timer = CAL_vvt_zero_target_timeout;
  vvt_inlet_b2_zero_timer = CAL_vvt_zero_target_timeout;
  vvt_exhaust_b2_zero_timer = CAL_vvt_zero_target_timeout;
                    // CAL_vvt_low_load_disable is true in the default config, so the low load
                    // Also CAL_vvt_low_load_ips_enable is False.
          (load_mass_per_stroke < CAL_vvt_intake_advance_base_low_load_Y_load[5])) &&
        ((engine_speed_3 < CAL_vvt_intake_advance_base_low_load_X_engine_speed[5] &&
                      CAL_vvt_intake_advance_base_low_load,
                      CAL_vvt_intake_advance_base_low_load_X_engine_speed,
                      CAL_vvt_intake_advance_base_low_load_Y_load);
                      CAL_vvt_intake_advance_base,CAL_vvt_intake_advance_base_X_engine_speed,
                      CAL_vvt_intake_advance_base_Y_load);
          (((load_mass_per_stroke < CAL_vvt_intake_advance_base_low_load_Y_load[5] &&
           (engine_speed_3 < CAL_vvt_intake_advance_base_low_load_X_engine_speed[5])))))) {
         (load_mass_per_stroke < CAL_vvt_exhaust_advance_base_low_load_Y_load[5])) &&
       (((engine_speed_3 < CAL_vvt_exhaust_advance_base_low_load_X_engine_speed[5] &&
                      CAL_vvt_exhaust_advance_base_low_load,
                      CAL_vvt_exhaust_advance_base_low_load_X_engine_speed,
                      CAL_vvt_exhaust_advance_base_low_load_Y_load);
                      CAL_vvt_exhaust_advance_base,CAL_vvt_exhaust_advance_base_X_engine_speed,
                      CAL_vvt_exhaust_advance_base_Y_load);
          (((load_mass_per_stroke < CAL_vvt_exhaust_advance_base_low_load_Y_load[5] &&
           (engine_speed_3 < CAL_vvt_exhaust_advance_base_low_load_X_engine_speed[5])))))) {
                  CAL_vvt_start_timer_X_coolant_temp);
                    CAL_vvt_intake_advance_coolant_offset_X_temp);
                      CAL_vvt_intake_advance_base,CAL_vvt_intake_advance_base_X_engine_speed,
                      CAL_vvt_intake_advance_base_Y_load);
                    CAL_vvt_exhaust_comp_temp_X_coolant_temp);
                      CAL_vvt_exhaust_advance_base,CAL_vvt_exhaust_advance_base_X_engine_speed,
                      CAL_vvt_exhaust_advance_base_Y_load);
    vvt_inlet_b1_zero_timer = CAL_vvt_zero_target_timeout;
    vvt_inlet_b2_zero_timer = CAL_vvt_zero_target_timeout;
    vvt_exhaust_b1_zero_timer = CAL_vvt_zero_target_timeout;
    vvt_exhaust_b2_zero_timer = CAL_vvt_zero_target_timeout;
                    // CAL_revlimit_torque_clamp is true in default calibration
                    CAL_torque_limit_by_engine_speed_ips_X_engine_speed);
                    CAL_torque_limit_by_engine_speed_manual_X_engine_speed);
                  CAL_torque_load_to_torque_X_engine_speed,CAL_torque_load_to_torque_Y_load);
                  CAL_torque_engine_friction_speed_component,
                  CAL_torque_engine_friction_speed_component_X_engine_speed,
                  CAL_torque_engine_friction_speed_component_Y_load);
                  CAL_torque_load_to_torque,CAL_torque_load_to_torque_X_engine_speed,
                  CAL_torque_load_to_torque_Y_load);
                    CAL_torque_external_request_minimum,
                    CAL_torque_external_request_minimum_X_engine_speed,
                    CAL_torque_external_request_minimum_Y_torque);
                    CAL_torque_torque_to_load,CAL_torque_torque_to_load_X_engine_speed,
                    CAL_torque_torque_to_load_Y_torque);
                  CAL_torque_factor_base_engine_speed_load,
                  CAL_torque_factor_base_engine_speed_load_X_engine_speed,
                  CAL_torque_factor_base_engine_speed_load_Y_load);
                    CAL_torque_ign_retard_base,CAL_torque_ign_retard_base_X_engine_speed,
                    CAL_torque_ign_retard_base_Y_torque_reduction_factor);
                  CAL_torque_factor_base_ign_intervention,
                  CAL_torque_factor_base_ign_intervention_X_engine_speed,
                  CAL_torque_factor_base_ign_intervention_Y_ign_adv);
                  CAL_torque_limit_base_factor,CAL_torque_limit_base_factor_X_rpm,
                  CAL_torque_limit_base_factor_Y_load);
                                CAL_torque_factor_base_ign_intervention,
                                CAL_torque_factor_base_ign_intervention_X_engine_speed,
                                CAL_torque_factor_base_ign_intervention_Y_ign_adv);
                  CAL_torque_engine_friction_speed_component,
                  CAL_torque_engine_friction_speed_component_X_engine_speed,
                  CAL_torque_engine_friction_speed_component_Y_load);
                     CAL_torque_engine_friction_temp_component,
                     CAL_torque_engine_friction_temp_component_X_coolant,
                     CAL_torque_engine_friction_temp_component_Y_load);
                     CAL_torque_engine_ac_load_base_X_ac);
                  CAL_torque_engine_ac_load_scaler_X_engine_speed);
                    CAL_torque_torque_to_load,CAL_torque_torque_to_load_X_engine_speed,
                    CAL_torque_torque_to_load_Y_torque);
                    CAL_torque_limit_proportional_X_load_error);
      tps_correction_proportional = CAL_torque_proportional_limit_positive;
                    CAL_torque_limit_integral_X_load_error);
        tps_correction_integral = CAL_torque_unknown_tps_clamp3;
        torque_cruise_request = torque_cruise_request + CAL_torque_hysteresis_threshold1;
// 0x0100: hard-capped to CAL_revlimit_max_engine_speed
  revlimit_max = CAL_revlimit_max_with_speedlimit;
                      CAL_revlimit_speedbase_ips_tour_X_coolant_temp,
                      CAL_revlimit_speedbase_ips_tour_Y_timer);
                      CAL_revlimit_speedbase_ips_tour_X_coolant_temp,
                      CAL_revlimit_speedbase_ips_tour_Y_timer);
                      CAL_revlimit_speedbase_manual_tour_X_coolant_temp,
                      CAL_revlimit_speedbase_manual_tour_Y_timer);
                      CAL_revlimit_speedbase_manual_tour_X_coolant_temp,
                      CAL_revlimit_speedbase_manual_tour_Y_timer);
                    CAL_revlimit_speedbase_ips_sport_X_coolant_temp,
                    CAL_revlimit_speedbase_ips_sport_Y_timer);
                    CAL_revlimit_speedbase_ips_sport_X_coolant_temp,
                    CAL_revlimit_speedbase_ips_sport_Y_timer);
                    CAL_revlimit_speedbase_manual_sport_X_coolant_temp,
                    CAL_revlimit_speedbase_manual_sport_Y_timer);
                    CAL_revlimit_speedbase_manual_sport_X_coolant_temp,
                    CAL_revlimit_speedbase_manual_sport_Y_timer);
     (coolant_temp_engine_stopped <= CAL_revlimit_coolant_coldstart_threshold)) {
                    CAL_revlimit_coldstart_rpm_envelope_X_index);
                    CAL_revlimit_coldstart_rpm_envelope_X_index);
      revlimit_hard = CAL_revlimit_limp_mode;
        revlimit_soft = CAL_revlimit_limp_mode - (_revlimit_hard - revlimit_soft);
                  CAL_revlimit_airflow_gain_from_rpm_delta_X_gear);
                  CAL_revlimit_airflow_gain_from_integrator_X_gear);
                  CAL_revlimit_airflow_gain_from_rpm_X_gear);
                    CAL_revlimit_escalation_integrator_step_X_gear);
                        CAL_revlimit_airflow_threshold_X_gear);
          (revlimit_fuelcut_count <= CAL_revlimit_overrun_count_threshold)))) {
          revlimit_maf_flow_raw = revlimit_maf_flow_raw + CAL_revlimit_maf_error_max_10g;
          revlimit_maf_flow_raw = revlimit_maf_flow_raw - CAL_revlimit_maf_error_max_10g;
      revlimit_startup_offset = revlimit_startup_offset - CAL_revlimit_startup_offset_decrement;
           revlimit_startup_max_offset - CAL_revlimit_startup_offset_decrement;

#endif /* CAL_ENGINE_H */
