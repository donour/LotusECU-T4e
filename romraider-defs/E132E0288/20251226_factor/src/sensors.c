/*
 * sensors.c - Sensor Processing
 * ADC, MAF, MAP, TPS, temperature sensors
 * ~50 functions
 */

#include "../include/types.h"
#include "../include/runtime_vars.h"
#include "../include/cal_sensors.h"

void adc_sample(void) { }
void adc_convert(void) { }
void adc_smooth_state_init(void) { }
void adc_buffer_copy_200hz(void) { }
void sensor_maf_process(void) { }
void sensor_map_process(void) { }
void sensor_coolant_temp_process(void) { }
void sensor_iat_process(void) { }
void accel_pedal_200hz(void) { }
/* + ~40 more sensor functions */
