/*
 * obd.c
 *
 * OBD-II Diagnostic Functions
 *
 * This file contains all OBD-II related functions including:
 * - DTC (Diagnostic Trouble Code) monitoring and management
 * - Freeze frame data capture
 * - Monitor completion status tracking
 * - Readiness monitors (catalyst, O2, EVAP, etc.)
 * - Mode 01-0A request processing
 * - Network/CAN diagnostics (U-codes)
 *
 * Function Count: ~123 functions
 * Original Lines: 18012-59943 (scattered throughout)
 *
 * Key Function Categories:
 *   - obd_ii_init_*: Initialization functions for each monitor
 *   - obd_ii_*_monitor*: Monitor update functions (called periodically)
 *   - obd_ii_mode*: OBD mode request handlers
 *   - obd_ii_dtc_*: DTC management functions
 *   - obd_ii_monitor_fail/pass: Generic monitor state transitions
 */

#include "../include/types.h"
#include "../include/constants.h"
#include "../include/hardware.h"
#include "../include/runtime_vars.h"
#include "../include/cal_obd.h"
#include "../include/cal_ignition.h"
#include "../include/cal_fuel.h"
#include "../include/cal_engine.h"
#include "../include/cal_vehicle.h"
#include "../include/cal_sensors.h"

/* ========================================================================
 * OBD-II Monitor State Management
 * ======================================================================== */

/**
 * obd_ii_monitor_pass - Mark a monitor as passing
 *
 * Called when a monitor test passes. Updates the monitor state and
 * increments pass counters.
 *
 * @obd2level: Pointer to OBD-II level configuration (enable/threshold bits)
 * @dtc_learned_flags: Pointer to learned DTC state flags
 */
void obd_ii_monitor_pass(u8_obd2level_t6 *obd2level, byte *dtc_learned_flags)
{
    // Check if monitor is enabled (bit 0 of obd2level)
    if ((*obd2level & OBD_MONITOR_ENABLE_MASK) != 0) {
        // Clear pending/confirmed bits, keep historical data
        *dtc_learned_flags = *dtc_learned_flags & ~(OBD_STATE_PENDING | OBD_STATE_CONFIRMED);
    }
}

/**
 * obd_ii_monitor_fail_transition - Handle monitor failure
 *
 * Called when a monitor detects a failure. Manages state transitions,
 * increments fail counters, and captures freeze frame data if needed.
 *
 * Original implementation had complex nested conditions - simplified here
 * with intermediate boolean variables for readability.
 */
void obd_ii_monitor_fail_transition(
    u8_obd2level_t6 *obd_config,
    byte *dtc_state,
    byte *fail_counter,
    byte *pass_counter,
    ushort dtc_code,
    char dtc_type)
{
    bool monitor_enabled;
    bool failure_threshold_met;
    bool should_set_pending;
    bool should_set_confirmed;

    // Check if this monitor is enabled
    monitor_enabled = (*obd_config & 0x01) != 0;
    if (!monitor_enabled) {
        return;
    }

    // Increment failure counter
    if (*fail_counter < UINT8_MAX_VALUE) {
        (*fail_counter)++;
    }

    // Check if failure threshold is met (bit 1 of obd_config)
    failure_threshold_met = (*fail_counter >= ((*obd_config >> 1) & 0x3F));

    // Determine if we should set pending or confirmed state
    should_set_pending = failure_threshold_met && ((*dtc_state & OBD_STATE_PENDING) == 0);
    should_set_confirmed = (*dtc_state & OBD_STATE_PENDING) != 0;

    if (should_set_pending) {
        *dtc_state |= OBD_STATE_PENDING;
        obd_ii_capture_freeze_frame_data(dtc_code, dtc_type);
    }

    if (should_set_confirmed) {
        *dtc_state |= OBD_STATE_CONFIRMED;
        *dtc_state |= OBD_STATE_MIL_ON;  // Turn on MIL (Check Engine Light)
    }

    // Reset pass counter on failure
    *pass_counter = 0;
}


/* ========================================================================
 * Freeze Frame Data Capture
 * ======================================================================== */

/**
 * obd_ii_capture_freeze_frame_data - Capture freeze frame on DTC trigger
 *
 * Stores current vehicle state when a DTC first triggers.
 * Data includes: RPM, load, coolant temp, fuel trim, etc.
 */
void obd_ii_capture_freeze_frame_data(ushort dtc_code, ulonglong dtc_type)
{
    // Store DTC code
    // Store current engine speed
    // Store current load
    // Store coolant temperature
    // Store fuel trims
    // Store other relevant parameters

    // Implementation details omitted - see original lines 24809-24836
}


/* ========================================================================
 * Monitor Initialization Functions
 * ======================================================================== */

void obd_ii_init_cat_efficiency_monitors(void)
{
    // Initialize catalyst efficiency monitors for both banks
    // Set initial state, clear counters
    // See original lines ~23424
}

void obd_ii_init_vvt_diagnostics(void)
{
    // Initialize VVT diagnostic monitors
    // See original lines ~23457
}

void obd_ii_init_o2_sensor_monitors(void)
{
    // Initialize O2 sensor heater and performance monitors
    // See original lines scattered 25000-35000
}

void obd_ii_init_evap_leak_monitors(void)
{
    // Initialize EVAP system leak detection monitors
    // P0442 (small leak), P0455 (large leak), P0456 (very small leak)
    // See original lines ~30012
}


/* ========================================================================
 * Periodic Monitor Update Functions (called at various rates)
 * ======================================================================== */

void obd_ii_cat_efficiency_eval(void)
{
    // Evaluate catalyst efficiency using O2 sensor switching
    // Called periodically when enable conditions are met
    // Checks pre-cat vs post-cat O2 sensor activity
    // See original lines ~23501
}

void obd_ii_vvt_cam_timing_monitors_update(void)
{
    // Monitor VVT cam position vs commanded position
    // Detect stuck VVT, slow response, over-advanced/retarded conditions
    // See original lines ~22925
}

void obd_ii_o2_sensor_monitors_100hz(void)
{
    // Update O2 sensor monitors at 100Hz
    // Check sensor heater, voltage range, response time
    // See original lines scattered 30000-35000
}


/* ========================================================================
 * OBD Mode Request Handlers
 * ======================================================================== */

void obd_ii_mode01_processing(void)
{
    // Process Mode 01 requests (current powertrain data)
    // Returns: MIL status, DTCs, freeze frame, etc.
    // See original lines ~24903
}

void obd_ii_mode03_processing(void)
{
    // Process Mode 03 requests (confirmed DTCs)
    // Returns list of stored DTCs
}

void obd_ii_mode07_processing(void)
{
    // Process Mode 07 requests (pending DTCs)
    // Returns list of pending DTCs
}

void obd_ii_mode0A_processing(void)
{
    // Process Mode 0A requests (permanent DTCs)
    // Returns DTCs that cannot be cleared until repaired
    // See original lines ~58461
}


/* ========================================================================
 * DTC Storage and Management
 * ======================================================================== */

void obd_ii_set_perm_dtc(uint16_t dtc)
{
    // Add a DTC to the permanent DTC list
    // These DTCs cannot be cleared until the fault is repaired
    // See original lines ~58493
}

void obd_ii_clear_dtcs(void)
{
    // Clear all DTCs (except permanent ones)
    // Reset freeze frames and monitor status
}


/* ========================================================================
 * EVAP System Monitors (P0441/P0442/P0455/P0456)
 * ======================================================================== */

/**
 * obd_ii_evap_leak_detection_monitor - EVAP leak detection state machine
 *
 * Monitors the evaporative emissions system for leaks by closing the
 * canister valve and monitoring pressure changes. Original implementation
 * (lines 25981-26260) had 8 levels of nested conditions - simplified here.
 *
 * Detection states:
 *   1. Small leak (P0442)
 *   2. Large leak (P0455)
 *   3. Very small leak (P0456)
 */
void obd_ii_evap_leak_detection_monitor(void)
{
    // ========== Enable Conditions Check ==========
    // Original: 8-level nested boolean expression (lines 25986-25994)

    bool evap_test_inactive = (flags_unknown & 0x400000) == 0;
    bool p0441_enabled = (CAL_obd_ii_P0441 & OBD_MONITOR_ENABLE_MASK) != 0;
    bool p0441_not_confirmed = (LEA_obd_ii_P0441_dtc_state & OBD_STATE_CONFIRMED) == 0;
    bool evap_valves_ok = (LEA_obd_ii_P0444_dtc_state & OBD_STATE_CONFIRMED) == 0 &&
                          (LEA_obd_ii_P0445_dtc_state & OBD_STATE_CONFIRMED) == 0;
    bool sufficient_runtime = ((uint)DAT_4000c9e2 * 20) < runtime_since_start;
    bool purge_valve_closed = (evap_status_flags & 2) == 0 &&
                              _obd_ii_commanded_evap_purge == 0;
    bool fuel_system_ready = (cl_state_flags_bank1 & 0x400) == 0 &&
                             (cl_state_flags_bank2 & 0x400) == 0;
    bool pressure_conditions_met = ((int)-(uint)DAT_4000c9e3 / 2 < (int)(short)obd_ii_evap_purge_pressure) ||
                                   ((flags_unknown & 0x800000) != 0);
    bool vehicle_conditions_ok = (flags_unknown & 0x20) == 0;

    bool enable_evap_leak_test = evap_test_inactive &&
                                 p0441_enabled &&
                                 p0441_not_confirmed &&
                                 evap_valves_ok &&
                                 sufficient_runtime &&
                                 purge_valve_closed &&
                                 fuel_system_ready &&
                                 pressure_conditions_met &&
                                 vehicle_conditions_ok;

    // ========== Leak Test State Machine ==========

    if (enable_evap_leak_test) {
        // Close canister vent valve to seal EVAP system
        evap_canister_close_command = 1;
        siu_gpdo[0xc3] = 1;  // Hardware output to close valve

        if (DAT_40001e75 == 0) {
            // Initialize leak test
            DAT_40001e75 = DAT_4000c9e4;  // Load test duration timer
            flags_unknown = (flags_unknown & 0xff5fffff) | 0x400000;  // Set test active flag
        } else {
            // Test in progress - decrement timer
            DAT_40001e75--;
            flags_unknown |= 0x800000;  // Set pressure stabilized flag

            // Check if pressure dropped (indicates leak)
            if ((int)(short)obd_ii_evap_purge_pressure < (int)-(uint)DAT_4000c9e3) {
                // Leak detected - reset timer and set leak flags
                DAT_40001e75 = DAT_4000c9e4;
                flags_unknown = (flags_unknown | 0xe00000) & 0xff7fffff;
            }
        }
    } else {
        // Disable leak test
        DAT_40001e75 = DAT_4000c9e4;
        flags_unknown &= 0xff7fffff;  // Clear test active flag
    }

    // ========== Purge Flow State Machine ==========
    // Original: Repeated pattern with magic state numbers (lines 26015-26065)
    // Simplified with constants and extracted logic

    #define EVAP_FLOW_STATE_THRESHOLD_1  1
    #define EVAP_FLOW_STATE_THRESHOLD_2  2
    #define EVAP_FLOW_STATE_THRESHOLD_3  3
    #define EVAP_FLOW_STATE_THRESHOLD_4  4

    bool purge_conditions_not_met = (DAT_40002322 < DAT_4000cb00) ||
                                    (_obd_ii_commanded_evap_purge < DAT_4000caf6);

    if (purge_conditions_not_met) {
        // Reset flow state machine
        evap_purge_flow_state_timer = DAT_4000cafc;
        DAT_40001e73 = 0;  // Clear confirmed state
        DAT_40001e72 = 0;  // Clear pending state
    } else {
        // Determine flow state based on pressure thresholds
        // Original used deeply nested if-else with repeated patterns

        byte target_state;
        if (-(int)DAT_4000caf8 < (int)(short)DAT_40002548) {
            if (-(int)DAT_4000cafa < (int)(short)DAT_40002548) {
                if (-(int)DAT_4000cb08 < (int)(short)DAT_40002548) {
                    target_state = EVAP_FLOW_STATE_THRESHOLD_1;
                } else {
                    target_state = EVAP_FLOW_STATE_THRESHOLD_2;
                }
            } else {
                target_state = EVAP_FLOW_STATE_THRESHOLD_3;
            }
        } else {
            target_state = EVAP_FLOW_STATE_THRESHOLD_4;
        }

        // State transition logic - wait for timer before confirming
        if (DAT_40001e72 == target_state) {
            // Already in target state - check if timer expired
            if (evap_purge_flow_state_timer == 0) {
                DAT_40001e73 = target_state;  // Confirm state
            }
        } else {
            // State change requested - reset timer
            evap_purge_flow_state_timer = DAT_4000cafc;
            DAT_40001e73 = 0;  // Clear confirmed state
            DAT_40001e72 = target_state;  // Set pending state
        }
    }

    // ========== Final State Updates ==========
    // Original: Complex nested conditions (lines 26066-26120)

    bool large_leak_check_disabled = ((evap_status_flags & 0x200) == 0) ||
                                     ((LEA_obd_ii_P0455_dtc_state & 4) != 0) ||
                                     ((flags_unknown & 0x10000) != 0);
    bool vapor_management_active = (flags_unknown & 0x2000) != 0;

    if (large_leak_check_disabled || !vapor_management_active) {
        flags_unknown &= 0xffffbfff;  // Clear leak detection flag
    } else {
        flags_unknown |= 0x4000;  // Set leak detection active

        // Check specific flow state conditions
        if (DAT_40001e73 == EVAP_FLOW_STATE_THRESHOLD_3) {
            bool purge_valve_stuck_open = (flags_unknown & 0x100) != 0;
            bool pressure_not_building = (flags_unknown & 0x200) == 0;

            if (purge_valve_stuck_open && pressure_not_building) {
                flags_unknown |= 0x24000;  // Set fault flags
            }

            DAT_40001e6a = DAT_40002548;  // Store pressure reading
            flags_unknown = (flags_unknown & 0xffffdfff) | 0x8000;
        }
        // Additional state checks for states 1 and 2 would follow...
    }
}


/**
 * obd_ii_throttle_actuator_monitor_200hz - Electronic throttle control monitor
 *
 * Monitors the electronic throttle actuator for proper response to commanded
 * position. Uses a filtered tracking algorithm with slew rate limiting.
 *
 * Original (lines 25739-25918) had complex bit-shifting arithmetic and nested
 * conditions - simplified with intermediate variables and comments.
 */
void obd_ii_throttle_actuator_monitor_200hz(void)
{
    // ========== Convert Commanded vs Actual Throttle Position to Percentage ==========
    // Original used complex bit manipulation: ((value * 20000) / 0xfff) with shifts

    uint commanded_percent;  // Commanded throttle position (0-20000 = 0-100%)
    uint actual_percent;     // Actual TPS reading (0-20000 = 0-100%)

    // Convert 12-bit commanded position to percentage
    commanded_percent = ((short)obd_ii_commanded_throttle_actuator * 20000) / 0xfff;

    // Get TPS feedback and convert to percentage
    u16_factor_1_1023 tps_raw = get_tps_feedback_pos();
    actual_percent = ((short)tps_raw * 20000) / 0xfff;

    // Initialize tracking filter on first run
    if ((short)uint16_t_40001668 == 0xffff) {
        uint16_t_40001668 = actual_percent;
    }

    // ========== Calculate Slew Rate Limited Tracking Error ==========
    // Implement asymmetric slew rate limits (different rates for opening vs closing)

    short tracking_error;
    int error_difference = commanded_percent - (int)(short)uint16_t_40001668;

    if ((int)(short)uint16_t_40001668 < commanded_percent) {
        // Throttle opening - use opening slew rate
        tracking_error = (DAT_4000cc4e * error_difference) / 200;

        // Clamp to maximum opening rate
        if (tracking_error > DAT_4000cc50) {
            tracking_error = DAT_4000cc50;
        }
    } else {
        // Throttle closing - use closing slew rate
        tracking_error = (DAT_4000cc4f * error_difference) / 200;

        // Clamp to maximum closing rate (negative limit)
        if (tracking_error < -(int)DAT_4000cc52) {
            tracking_error = -DAT_4000cc52;
        }
    }

    // ========== Adaptive Filtering Based on Error Magnitude ==========
    // Use different filter time constants depending on error size

    #define THROTTLE_ERROR_THRESHOLD  200  // Original: 0xc9

    bool large_error_detected;
    if ((DAT_40001e60 > 0 && DAT_40001e60 > tracking_error) ||
        (DAT_40001e60 < 0 && tracking_error > DAT_40001e60) ||
        (libc_abs((longlong)DAT_40001e60) < THROTTLE_ERROR_THRESHOLD)) {
        large_error_detected = false;
    } else {
        large_error_detected = true;
    }

    // Calculate change in tracking error
    short error_delta = tracking_error - DAT_40001e60;
    short error_delta_abs = libc_abs((longlong)error_delta);

    // Update filter state with asymmetric time constants
    if (tracking_error < DAT_40001e60) {
        // Error decreasing
        if (large_error_detected) {
            // Fast response for large errors
            short max_step = (ushort)DAT_4000cc56 * 2;
            if (error_delta_abs > max_step) {
                DAT_40001e60 -= max_step;
            } else {
                DAT_40001e60 -= error_delta_abs;
            }
        } else {
            // Slow response for small errors
            short max_step = (ushort)DAT_4000cc55 * 2;
            if (error_delta_abs > max_step) {
                DAT_40001e60 -= max_step;
            } else {
                DAT_40001e60 -= error_delta_abs;
            }
        }
    } else {
        // Error increasing
        if (large_error_detected) {
            // Fast response for large errors
            short max_step = (ushort)DAT_4000cc57 * 2;
            if (error_delta_abs > max_step) {
                DAT_40001e60 += max_step;
            } else {
                DAT_40001e60 += error_delta_abs;
            }
        } else {
            // Slow response for small errors
            short max_step = (ushort)DAT_4000cc54 * 2;
            if (error_delta_abs > max_step) {
                DAT_40001e60 += max_step;
            } else {
                DAT_40001e60 += error_delta_abs;
            }
        }
    }

    // ========== Update Filtered Position with Limiting ==========

    #define THROTTLE_MAX_POSITION  20001  // Original: 0x4e21

    int new_position = (int)(short)uint16_t_40001668 + (int)DAT_40001e60;

    if (new_position < THROTTLE_MAX_POSITION) {
        uint16_t_40001668 = uint16_t_40001668 + DAT_40001e60;

        // Clamp to zero if negative
        if (new_position < 0) {
            uint16_t_40001668 = 0;
        }
    } else {
        // Clamp to maximum
        uint16_t_40001668 = THROTTLE_MAX_POSITION - 1;
    }

    // Subsequent code would evaluate position error against thresholds
    // and set DTCs if throttle doesn't track commanded position properly
    // (lines 25820-25918 omitted for brevity)
}


/* ========================================================================
 * Knock Monitor Functions (P2336-P2341 - Per Cylinder)
 * ======================================================================== */

void obd_ii_knock_threshold_per_cylinder_100ms(void)
{
    bool knock_check_enabled;
    bool knock_detected;
    bool cyl0_retard_active;

    // P050B - Knock threshold exceeded on cold start
    if ((CAL_obd_ii_P050B & OBD_MONITOR_ENABLE_MASK) != 0) {
        // Check if ignition timing is being retarded due to knock
        // Simplified from original complex nested conditions
        // See original lines 30109-30136
    }

    // Check knock detection system is active
    if ((knock_flags & KNOCK_FLAG_ACTIVE) == 0) {
        knock_flags = knock_flags & ~KNOCK_FLAG_CONDITIONS;
    }

    // P2336 - Cylinder 1 knock threshold
    if ((CAL_obd_ii_P2336 & OBD_MONITOR_ENABLE_MASK) != 0) {
        knock_check_enabled = (knock_flags & KNOCK_FLAG_ACTIVE) != 0;

        if (knock_check_enabled) {
            cyl0_retard_active = (ign_adv_min < obd_ii_ign_adv_per_cylinder[CYLINDER_INDEX_0]) ||
                                (LEA_ign_knock_retard[CYLINDER_INDEX_0] == 0);

            // Simplified logic - see original lines 30155-30198
        }
    }

    // Similar logic for P2337-P2341 (cylinders 2-6)
    // See original lines 30200-30433
}


/*
 * ========================================================================
 * NOTE: This file contains representative samples of the 123 OBD functions.
 *
 * Complete function list to be extracted from original lines 18012-59943:
 *
 * INITIALIZATION FUNCTIONS (~30 functions):
 *   - obd_ii_init_timers
 *   - obd_ii_init_cat_efficiency_monitors
 *   - obd_ii_init_vvt_diagnostics
 *   - obd_ii_init_o2_sensor_monitors
 *   - obd_ii_init_evap_leak_monitors
 *   - obd_ii_init_ecu_diagnostics
 *   - obd_ii_init_fuel_system_monitors
 *   - obd_ii_init_misfire_monitors
 *   - obd_ii_init_can_network_monitors
 *   - obd_ii_init_thermostat_monitors
 *   - obd_ii_init_fuel_pump_diagnostics
 *   - (and ~20 more init functions...)
 *
 * PERIODIC MONITOR FUNCTIONS (~60 functions):
 *   - obd_ii_cat_efficiency_eval
 *   - obd_ii_vvt_cam_timing_monitors_update
 *   - obd_ii_o2_sensor_monitors_100hz
 *   - obd_ii_o2_heater_monitors
 *   - obd_ii_evap_leak_detection
 *   - obd_ii_fuel_system_monitors_100ms
 *   - obd_ii_misfire_detection_update
 *   - obd_ii_thermostat_rationality
 *   - obd_ii_knock_threshold_per_cylinder_100ms
 *   - obd_ii_module_coding_vin_monitors_update
 *   - obd_ii_can_network_monitors_100ms
 *   - (and ~50 more monitor functions...)
 *
 * MODE REQUEST HANDLERS (~10 functions):
 *   - obd_ii_mode01_processing
 *   - obd_ii_mode03_processing
 *   - obd_ii_mode07_processing
 *   - obd_ii_mode09_processing
 *   - obd_ii_mode0A_processing
 *   - (and ~5 more mode handlers...)
 *
 * UTILITY FUNCTIONS (~20 functions):
 *   - obd_ii_monitor_pass
 *   - obd_ii_monitor_fail_transition
 *   - obd_ii_capture_freeze_frame_data
 *   - obd_ii_set_perm_dtc
 *   - obd_ii_clear_dtcs
 *   - obdii_update_dtc_state
 *   - (and ~15 more utilities...)
 *
 * To complete this file, extract all functions matching pattern:
 *   grep -E "^(void|int|uint|undefined).*(obd|obdii)" E132E0288.c
 * ========================================================================
 */
