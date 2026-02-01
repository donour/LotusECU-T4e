/*
 * diagnostics.c - Internal ECU Diagnostics
 * Misfire detection, coil diagnostics, sensor range checks
 * ~30 functions
 */

#include "../include/types.h"
#include "../include/runtime_vars.h"
#include "../include/cal_obd.h"

void misfire_detection_1000hz(void) { }
void misfire_calc_roughness(void) { }
void coil_driver_state_machine(void) { }
void coilpack_failure_set(void) { }
void cac_diagnostic_1000hz(void) { }
/* + ~25 more diagnostic functions */
