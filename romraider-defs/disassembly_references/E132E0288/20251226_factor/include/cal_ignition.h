/*
 * cal_ignition.h
 *
 * Ignition and Knock Control Calibration Variables
 *
 * This file contains calibration parameters for:
 * - Base ignition timing maps
 * - Knock detection and control
 * - Octane adaptation
 * - Ignition dwell control
 * - MBT (Minimum advance for Best Torque) timing
 *
 * Common Table Structures:
 *   CAL_ign_base_*: Base ignition timing tables (20x20 typical)
 *   CAL_ign_base_*_X_engine_speed: X-axis (RPM)
 *   CAL_ign_base_*_Y_load: Y-axis (load)
 *
 *   CAL_knock_*: Knock detection thresholds and parameters
 */

#ifndef CAL_IGNITION_H
#define CAL_IGNITION_H

#include "types.h"

/* ========================================================================
 * Ignition Timing Calibrations
 * ======================================================================== */

uint8_t[256] CAL_knock_sampling_window;
i8_angle_1/4deg CAL_ign_comp_ac_compressor_active;
u8_rspeed_125/4+500rpm[20] CAL_ign_base_manual_X_engine_speed;
u8_load_1173mg/255stroke[20] CAL_ign_base_manual_Y_load;
u8_angle_1/4-10deg[400] CAL_ign_base_ips;
u8_angle_1/4-10deg[400] CAL_ign_base_manual;
u8_angle_1/4-10deg[400] CAL_ign_knock_safe;
u8_angle_1/4-10deg[400] CAL_ign_mbt_modeled;
u8_time_64us[64] CAL_ign_dwell_time;
u8_rspeed_125/4+500rpm[8] CAL_ign_dwell_time_X_rpm;
u8_voltage_72/1023v[8] CAL_ign_dwell_time_Y_ecu_voltage;
u8_rspeed_125/4+500rpm[20] CAL_ign_base_ips_X_engine_speed;
u8_load_1173mg/255stroke[20] CAL_ign_base_ips_Y_load;
u8_rspeed_125/4+500rpm[20] CAL_ign_knock_safe_X_engine_speed;
u8_load_1173mg/255stroke[20] CAL_ign_knock_safe_Y_load;
u8_rspeed_125/4+500rpm[20] CAL_ign_mbt_modeled_X_engine_speed;
u8_load_1173mg/255stroke[20] CAL_ign_mbt_modeled_Y_load;
u8_temp_5/8-40c CAL_ign_comp_coolant_engine_stopped_min;
u8_angle_1/4-20deg[256] CAL_ign_min;
u8_rspeed_125/4+500rpm[16] CAL_ign_min_X_engine_speed;
i8_angle_1/4deg[56] CAL_ign_comp_tps_ips;
u8_load_4mg/stroke[16] CAL_ign_min_Y_load;
u8_rspeed_125/4+500rpm[7] CAL_ign_comp_tps_ips_X_engine_speed;
u8_factor_1/255[8] CAL_ign_comp_tps_ips_Y_pedal_pos;
i8_angle_1/4deg[64] CAL_ign_comp_tps_manual;
u8_angle_1/4-10deg[8] CAL_ign_limit_first_gear_manual;
u8_rspeed_125/4+500rpm[8] CAL_ign_comp_tps_manual_X_engine_speed;
u8_rspeed_125/4+500rpm[8] CAL_ign_limit_first_gear_manual_X_engine_speed;
u8_factor_1/255[8] CAL_ign_comp_tps_manual_Y_accel_pedal;
u8_gear CAL_ign_low_gear_number;
i8_angle_1/4deg[64] CAL_ign_retard_recovery_step;
u8_rspeed_125/4+500rpm[8] CAL_ign_retard_recovery_step_X_engine_speed;
u8_load_4mg/stroke[8] CAL_ign_retard_recovery_step_Y_load;
i8_angle_1/4deg[64] CAL_ign_comp_maf_accum;
u8_mass_g[8] CAL_ign_comp_maf_accum_X_maf_accum;
u8_factor_1/255[8] CAL_ign_comp_maf_accum_Y_tps;
u8_angle_1/4-10deg[8] CAL_ign_comp_coldstart;
u8_angle_1/4deg[16] CAL_ign_comp_coolant_manual1;
u8_angle_1/4deg[16] CAL_ign_comp_coolant_manual_vvt_alt;
u8_temp_5/8-40c[16] CAL_ign_comp_coolant_manual1_X_coolant_temp;
u8_temp_5/8-40c[16] CAL_ign_comp_coolant_manual_vvt_alt_X_coolant_temp;
u8_angle_1/4deg[16] CAL_ign_comp_coolant_ips_noflags;
u8_temp_5/8-40c[16] CAL_ign_comp_coolant_ips_noflags_X_coolant_temp;
u8_factor_1/128[8] CAL_ign_comp_rpm_multiplier;
u8_angle_1/4deg[16] CAL_ign_comp_coolant_ips_flags;
u8_temp_5/8-40c[8] CAL_ign_comp_rpm_multiplier_X_coolant_temp;
u8_temp_5/8-40c[16] CAL_ign_comp_coolant_ips_flags_X_coolant_temp;
u8_angle_1/4-32deg[16] CAL_ign_comp_engine_air;
u8_temp_5/8-40c[16] CAL_ign_comp_engine_air_X_air_temp;
u8_angle_1/4-32deg[16] CAL_ign_comp_rpm;
u8_rspeed_125/4+500rpm[16] CAL_ign_comp_rpm_X_engine_speed;
i8_angle_1/4deg[8] CAL_ign_comp_tps_rate;
uint8_t[8] CAL_ign_comp_tps_rate_X_tps_rate;
u8_angle_1/4-32deg[192] CAL_ign_comp_manifold_temp;
u8_rspeed_125/4+500rpm[16] CAL_ign_comp_manifold_temp_X_engine_speed;
u8_temp_5/8-40c[12] CAL_ign_comp_manifold_temp_Y_manifold_temp;
u8_angle_1/4-32deg[16] CAL_ign_comp_idle_error1;
u8_angle_1/4-32deg[16] CAL_ign_comp_idle_error2;
u8_factor_1/128[192] CAL_ign_comp_manifold_temp_load_multiplier;
u8_rspeed_-128[16] CAL_ign_comp_idle_error1_X_rpm;
u8_rspeed_125/4+500rpm[16] CAL_ign_comp_manifold_temp_load_multiplier_X_engine_speed;
uint8_t[16] CAL_ign_comp_idle_error2_X_idle_speed_error;
i16_angle_1/4deg[8] CAL_ign_comp_startup_manual;
u8_load_4mg/stroke[12] CAL_ign_comp_manifold_temp_load_multiplier_Y_load;
u16_mass_mg[8] CAL_ign_comp_startup_manual_X_maf_accum;
i16_angle_1/4deg[40] CAL_ign_comp_startup_ips;
u16_temp_5/8-40c[4] CAL_ign_comp_startup_ips_X_coolant_temp_engine_stopped;
uint16_t[10] CAL_ign_comp_startup_ips_Y_maf_accumulated;
u8_angle_1/4-32deg[16] CAL_ign_comp_idle_error3;
uint8_t[16] CAL_ign_comp_idle_error3_X_rpm;
uint8_t[16] CAL_ign_comp_speed_variation_unknown;
uint8_t[16] CAL_ign_comp_speed_variation_unknown_X_rpm_delta;
u8_load_4mg/stroke CAL_ign_zero_load_threshold;
u8_rspeed_125/4+500rpm CAL_ign_zero_rpm_threshold;
u8_gear CAL_ign_zero_gear;
u8_angle_1/4-20deg[9] CAL_ign_min_engine_off;
u8_rspeed_125/4+500rpm[3] CAL_ign_min_engine_off_X_engine_speed;
u8_load_4mg/stroke[3] CAL_ign_min_engine_off_Y_load;
bool CAL_ign_enable_lea_knock_retard;
u8_temp_5/8-40c[8] CAL_ign_comp_coldstart_X_coolant_temp;
i8_angle_1/4deg[128] CAL_ign_comp_tps2;
u8_rspeed_125/4+500rpm[8] CAL_ign_comp_tps2_X_engine_speed;
u8_factor_1/255[16] CAL_ign_comp_tps2_Y_accel_pedal;
u8_angle_1/4deg[6] CAL_ign_trim_per_cyl;
u8_time_5ms CAL_ign_timer_unknown;
u8_factor_1/255[16] CAL_knock_inhibit_tps_max;
u8_rspeed_125/4+500rpm[16] CAL_knock_inhibit_tps_max_X_rpm;
u8_rspeed_125/4+500rpm[16] CAL_knock_sampling_window_X_rpm;
u8_load_4mg/stroke[16] CAL_knock_sampling_window_Y_load;
u8_rspeed_125/4+500rpm[16] CAL_knock_buffer_size_X_engine_speed;
u8_load_4mg/stroke[16] CAL_knock_buffer_size_Y_load;
uint8_t[256] CAL_knock_buffer_size;
u8_factor_1/255[64] CAL_knock_sensitivity;
uint8_t[64] CAL_knock_peak_threshold;
u8_load_4mg/stroke CAL_knock_detection_load_margin_debounce;
u8_load_4mg/stroke[8] CAL_knock_detection_load_threshold;
u8_rspeed_125/4+500rpm[8] CAL_knock_detection_load_threshold_X_rpm;
u8_load_4mg/stroke[8] CAL_knock_learning_load_threshold;
u8_rspeed_125/4+500rpm[8] CAL_knock_learning_load_threshold_X_rpm;
u8_angle_1/4deg CAL_knock_corr_limit;
u8_temp_5/8-40c CAL_knock_corr_temp_threshold;
u8_rspeed_125/4+500rpm[8] CAL_knock_sensitivity_X_engine_speed;
u8_load_4mg/stroke[8] CAL_knock_sensitivity_Y_load;
u8_rspeed_125/4+500rpm[8] CAL_knock_peak_threshold_X_engine_speed;
u8_load_4mg/stroke[8] CAL_knock_peak_threshold_Y_load;
u16_factor_1/1023 CAL_knock_inhibit_tps_rate1;
u8_angle_1/4deg CAL_knock_corr_octane_base;
u8_angle_1/4deg[8] CAL_knock_count_to_retard;
u8_time_5ms CAL_knock_inhibit_timer_tps_rate;
uint8_t[8] CAL_knock_count_to_retard_X_knock_count;
u8_rspeed_125/4+500rpm CAL_knock_detection_engine_speed_min;
u8_rspeed_125/4+500rpm CAL_knock_detection_engine_speed_max;
u8_rspeed_125/4+500rpm CAL_knock_detection_engine_speed_margin;
uint8_t CAL_knock_baseline_min_clamp;
uint8_t CAL_knock_baseline_filter_alpha;
uint8_t CAL_knock_retard_hold_time;
u8_count CAL_knock_octane_scaler_shortterm_decrement;
u8_count CAL_knock_octane_scaler_shortterm_multiplier;
u8_count CAL_knock_octane_scaler_increment;
u8_count CAL_knock_octane_scaler_decrement;
u8_angle_1/4deg CAL_knock_ign_retard_decay_rate;
u16_rspeed_rpm CAL_knock_threshold_obd_ii_check_enable_engine_speed;
u8_factor_1/100 CAL_knock_threshold_obd_ii_check_enable_load;
uint16_t CAL_knock_agc_scaling_threshold;
enum_knock_mode CAL_knock_mode;
u8_rspeed_125/4+500rpm[3] CAL_knock_agc_threshold;
u8_rspeed_125/4+500rpm CAL_knock_agc_hysteresis_band;
    *(uint8_t **)(puVar1 + 4) = CAL_knock_sampling_window + 0x2e;
  *param_2 = CAL_knock_sampling_window + 0x2e;
  puVar3 = CAL_knock_sampling_window + 46;
                    // at CAL_knock_mode 
                    CAL_ign_base_ips_X_engine_speed,CAL_ign_base_ips_Y_load);
                    CAL_ign_base_manual_X_engine_speed,CAL_ign_base_manual_Y_load);
                  CAL_ign_knock_safe_X_engine_speed,CAL_ign_knock_safe_Y_load);
                  CAL_ign_mbt_modeled_X_engine_speed,CAL_ign_mbt_modeled_Y_load);
  if ((((COD_base[0] >> 0xd & 7) == 0) && (car_current_gear <= CAL_ign_low_gear_number)) ||
                    CAL_ign_limit_first_gear_manual_X_engine_speed);
                  CAL_ign_retard_recovery_step_X_engine_speed,CAL_ign_retard_recovery_step_Y_load);
                    CAL_ign_comp_startup_ips_X_coolant_temp_engine_stopped,
                    CAL_ign_comp_startup_ips_Y_maf_accumulated);
                    CAL_ign_comp_startup_manual_X_maf_accum);
                    CAL_ign_comp_maf_accum_Y_tps);
                                CAL_ign_comp_tps_ips_Y_pedal_pos);
                                CAL_ign_comp_tps_manual_X_engine_speed,
                                CAL_ign_comp_tps_manual_Y_accel_pedal);
                    CAL_ign_comp_tps2_Y_accel_pedal);
                                CAL_ign_comp_tps_ips_Y_pedal_pos);
                                CAL_ign_comp_tps_manual_X_engine_speed,
                                CAL_ign_comp_tps_manual_Y_accel_pedal);
                    CAL_ign_comp_tps2_Y_accel_pedal);
                  CAL_ign_comp_coldstart_X_coolant_temp + 5);
                      CAL_ign_comp_coolant_ips_noflags_X_coolant_temp);
                      CAL_ign_comp_coolant_ips_flags_X_coolant_temp);
                    CAL_ign_comp_coolant_manual1_X_coolant_temp);
                    CAL_ign_comp_coolant_manual_vvt_alt_X_coolant_temp);
                  CAL_ign_comp_rpm_multiplier_X_coolant_temp);
                    CAL_ign_comp_manifold_temp_X_engine_speed,
                    CAL_ign_comp_manifold_temp_Y_manifold_temp);
                    CAL_ign_comp_manifold_temp,CAL_ign_comp_manifold_temp_X_engine_speed,
                    CAL_ign_comp_manifold_temp_Y_manifold_temp);
                  CAL_ign_comp_manifold_temp_load_multiplier,
                  CAL_ign_comp_manifold_temp_load_multiplier_X_engine_speed,
                  CAL_ign_comp_manifold_temp_load_multiplier_Y_load);
     (coolant_temp_engine_stopped < CAL_ign_comp_coolant_engine_stopped_min)) {
                    CAL_ign_comp_idle_error1,CAL_ign_comp_idle_error1_X_rpm);
                    CAL_ign_comp_idle_error2_X_idle_speed_error);
                    CAL_ign_comp_idle_error3,CAL_ign_comp_idle_error3_X_rpm);
    ign_idle_comp_recovery_timer_5ms = CAL_ign_timer_unknown;
                         CAL_ign_comp_speed_variation_unknown_X_rpm_delta);
                         CAL_ign_comp_speed_variation_unknown,
                         CAL_ign_comp_speed_variation_unknown_X_rpm_delta);
                         CAL_ign_comp_speed_variation_unknown_X_rpm_delta);
  if (((((COD_base[0] >> 0xd & 7) == 0) && (car_current_gear <= CAL_ign_zero_gear)) &&
      (engine_speed_3 < CAL_ign_zero_rpm_threshold)) &&
     (load_mass_per_stroke < CAL_ign_zero_load_threshold)) {
                              CAL_ign_min_engine_off,CAL_ign_min_engine_off_X_engine_speed,
                              CAL_ign_min_engine_off_Y_load);
                              CAL_ign_min_X_engine_speed,CAL_ign_min_Y_load);
                    // CAL_ign_enable_lea_knock_retard has value 1 in the default calibration
  puVar1 = CAL_knock_sampling_window + 0x2e;
  puVar1 = CAL_knock_sampling_window + 0x2e;
  puVar1 = CAL_knock_sampling_window + 0x2e;
  puVar1 = CAL_knock_sampling_window + 0x2e;
  if ((coolant_temp_engine_stopped < CAL_ign_comp_coolant_engine_stopped_min) &&
                    CAL_knock_sampling_window,CAL_knock_sampling_window_X_rpm,
                    CAL_knock_sampling_window_Y_load);
                    CAL_knock_buffer_size_X_engine_speed,CAL_knock_buffer_size_Y_load);
                  CAL_knock_sensitivity_X_engine_speed,CAL_knock_sensitivity_Y_load);
                  CAL_knock_peak_threshold_X_engine_speed,CAL_knock_peak_threshold_Y_load);
    knock_inhibit_timer_tps_rate = CAL_knock_inhibit_timer_tps_rate;
                  CAL_knock_detection_load_threshold_X_rpm);
           knock_detection_load_threshold - CAL_knock_detection_load_margin_debounce;
     (engine_speed_3 < CAL_knock_detection_engine_speed_max)) {
           CAL_knock_detection_engine_speed_max + CAL_knock_detection_engine_speed_margin;
    if (CAL_knock_detection_engine_speed_margin < CAL_knock_detection_engine_speed_min) {
           CAL_knock_detection_engine_speed_min - CAL_knock_detection_engine_speed_margin;
                  CAL_knock_learning_load_threshold_X_rpm);
           knock_learning_enable_threshold - CAL_knock_detection_load_margin_debounce;
  else if (((knock_flags & 0b00100000) == 0) || (coolant_temp <= CAL_knock_corr_temp_threshold)) {
                      CAL_knock_count_to_retard_X_knock_count);
        LEA_ign_knock_retard[cyl] = CAL_knock_corr_limit;
    knock_ign_retard_unknown[cur_cyl] = CAL_knock_retard_hold_time;
          LEA_ign_knock_retard[cyl] = LEA_ign_knock_retard[cyl] - CAL_knock_ign_retard_decay_rate;
                    // CAL_knock_mode is goertzel_32sample_x3 in the factory calibration.
     (((engine_speed_3 < CAL_knock_agc_threshold[0] ||
          (((engine_speed_3 < CAL_knock_agc_threshold[1] ||
          (((engine_speed_3 < CAL_knock_agc_threshold[2] ||

#endif /* CAL_IGNITION_H */
