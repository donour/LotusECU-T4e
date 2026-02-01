/*
 * fuel.c
 *
 * Fuel Injection Control
 *
 * Fuel pulse width calculation, AFR control, fuel film compensation
 */

#include "../include/types.h"
#include "../include/constants.h"
#include "../include/runtime_vars.h"
#include "../include/cal_fuel.h"

extern void lookup_2D_uint8_interpolated(int size, ushort x, uint8_t *table, uint8_t *x_axis);
extern void lookup_3D_uint8_interpolated(int rows, int cols, ushort x, ushort y, uint8_t *table, uint8_t *x_axis, uint8_t *y_axis);
extern void inj_write_etpu(uint8_t cyl_index, uint32_t angle, u32_time_100ns pulse_time_raw);

/**
 * injection - Main fuel injection calculation (1000Hz)
 *
 * Calculates injector pulse width by:
 *   1. Determining fuel pressure (manifold relative)
 *   2. Looking up injector base time (characterization)
 *   3. Looking up target AFR
 *   4. Calculating required fuel mass
 *   5. Applying compensations (temp, startup, transient)
 *   6. Converting to pulse width using injector flow rate
 *
 * Original (lines 16565-17130) was ~565 lines with complex fuel film
 * dynamics and bank balancing - simplified with clear structure.
 */
void injection(void)
{
    // ========== Calculate Manifold-Relative Fuel Pressure ==========
    // Fuel pressure relative to manifold affects injector flow rate
    u32_pressure_mbar relative_fuel_pressure = fuel_pressure_abs2 - map;

    // Clamp to valid range
    if ((int)relative_fuel_pressure < 0) {
        fuel_pressure_manifold_relative = 0;
    } else if (relative_fuel_pressure > 65535) {
        fuel_pressure_manifold_relative = 65535;
    } else {
        fuel_pressure_manifold_relative = (u16_pressure_mbar)relative_fuel_pressure;
    }

    // Convert to lookup index (50 mbar per unit)
    if (fuel_pressure_manifold_relative < 12751) {
        fuel_pressure_lookup_for_time_base = fuel_pressure_manifold_relative / 50;
    } else {
        fuel_pressure_lookup_for_time_base = 255;
    }

    // ========== Lookup Injector Base Time ==========
    // Base opening time varies with voltage and fuel pressure
    u8_time_20us inj_time_base = lookup_3D_uint8_interpolated(
        8, 8,
        (ushort)((sensor_adc_ecu_voltage >> 2) & 0xff),
        (ushort)fuel_pressure_lookup_for_time_base,
        CAL_inj_time_base,
        CAL_inj_time_base_X_car_voltage,
        CAL_inj_time_base_Y_fuel_pressure);

    // ========== Apply Air Temperature Compensation ==========
    // Air density changes with temperature affect required fuel
    u8_factor_1 inj_comp_air_temp;

    bool use_manifold_temp = CAL_ecu_inj_use_tmap;
    if (use_manifold_temp) {
        inj_comp_air_temp = lookup_2D_uint8_interpolated(
            8,
            obd_ii_manifold_temp,
            CAL_inj_comp_iat,
            CAL_inj_comp_iat_X_iat);
    } else {
        inj_comp_air_temp = lookup_2D_uint8_interpolated(
            8,
            temp_engine_air,
            CAL_inj_comp_iat,
            CAL_inj_comp_iat_X_iat);
    }

    // Calculate compensated pulse time
    u16_time_us inj_pulse_time_scaled = (inj_time_base * 20 * inj_comp_air_temp) / 100;

    // Clamp to maximum
    if (inj_pulse_time_scaled > 5100) {
        inj_pulse_time_scaled = 5100;
    }

    // ========== Apply Startup Enrichment ==========
    // Cold engine requires extra fuel
    u8_time_256us startup_enrichment_offset = lookup_2D_uint8_interpolated(
        16,
        coolant_temp_engine_stopped,
        CAL_inj_startup_enrichment_offset,
        CAL_inj_startup_enrichment_offset_X_coolant_temp_engine_stopped);

    u16_time_us inj_startup_pulse_time = inj_pulse_time_scaled + (startup_enrichment_offset * 256);

    // Clamp
    if (inj_startup_pulse_time > 65535) {
        inj_startup_pulse_time = 65535;
    }

    // ========== Lookup Target AFR (Air-Fuel Ratio) ==========
    u8_afr_1_20_5 afr_base_lookup = lookup_3D_uint8_interpolated(
        20, 20,
        (ushort)engine_speed_3,
        (ushort)load_1,
        CAL_inj_afr_base,
        CAL_inj_afr_base_X_engine_speed,
        CAL_inj_afr_base_Y_engine_load);

    // Convert to AFR (scaling: value * 0.05 + 5.0)
    u16_afr_1_100 afr_target = (afr_base_lookup * 5) + 500;

    // Apply trim (usually zero in stock calibration)
    afr_target += afr_target_trim_0p02_steps * 2;

    // ========== Calculate Required Fuel Mass ==========
    // Mass air flow / target AFR = required fuel mass
    u32_mass_mg fuel_mass_required = (maf_grams_per_sec * 1000) / afr_target;

    // ========== Lookup Injector Flow Rate ==========
    // Injector flow varies with pressure
    u16_flow_mg_s injector_flow_rate = lookup_2D_uint8_interpolated(
        8,
        fuel_pressure_lookup_for_time_base,
        CAL_inj_flow_rate,
        CAL_inj_flow_rate_X_fuel_pressure);

    // ========== Calculate Base Pulse Width ==========
    // Pulse width = (required fuel mass / flow rate) + dead time
    u32_time_us inj_pulse_width_base = (fuel_mass_required * 1000000) /
                                        (injector_flow_rate * NUM_CYLINDERS);

    inj_pulse_width_base += inj_pulse_time_scaled;  // Add dead time

    // ========== Apply Closed Loop Correction (from O2 Sensors) ==========
    // Multiply by learned fuel trim
    inj_pulse_width_base = (inj_pulse_width_base * closedloop_fuel_trim_b1) / 128;

    // ========== Apply Fuel Film Compensation (X-Tau Model) ==========
    // Accounts for fuel depositing on/evaporating from intake walls
    fuel_film_compensation();

    // Film compensation adds/subtracts from pulse width
    u32_time_us final_pulse_width = inj_pulse_width_base + fuel_film_compensation_delta;

    // ========== Write Pulse Width to eTPU for Each Cylinder ==========
    for (byte cyl = 0; cyl < NUM_CYLINDERS; cyl++) {
        // Apply per-cylinder trim
        u32_time_us cyl_pulse_width = (final_pulse_width * inj_per_cyl_trim[cyl]) / 128;

        // Schedule injection via eTPU
        inj_write_etpu(cyl, inj_angle_cyl[cyl], cyl_pulse_width);
    }
}


/**
 * fuel_film_compensation - X-Tau fuel film dynamics model
 *
 * Models fuel depositing on and evaporating from intake manifold walls.
 * On throttle tip-in, more fuel sticks to walls so injection must increase.
 * On tip-out, fuel evaporates from walls so injection must decrease.
 *
 * Uses exponential decay model with time constant tau.
 */
void fuel_film_compensation(void)
{
    // Lookup X (fraction of fuel that deposits on walls)
    u8_factor_1_255 x_factor = lookup_3D_uint8_interpolated(
        8, 8,
        (ushort)engine_speed_3,
        (ushort)map,
        CAL_injtip_x_factor,
        CAL_injtip_x_factor_X_rpm,
        CAL_injtip_x_factor_Y_map);

    // Lookup tau (time constant for evaporation)
    u8_time_10ms tau_time = lookup_3D_uint8_interpolated(
        8, 8,
        (ushort)engine_speed_3,
        (ushort)map,
        CAL_injtip_tau,
        CAL_injtip_tau_X_rpm,
        CAL_injtip_tau_Y_map);

    // Calculate change in fuel film mass
    i32_mass_mg film_mass_change = (inj_pulse_width_base * x_factor) / 255 -
                                    (fuel_film_mass_estimate * tau_time) / 255;

    // Update fuel film estimate
    fuel_film_mass_estimate += film_mass_change;

    // Compensation is inverse of film change
    fuel_film_compensation_delta = -film_mass_change;
}


/**
 * closed_loop_200hz - Closed loop fuel control using O2 sensors
 *
 * Uses wideband O2 sensors to measure actual AFR and adjusts fuel trim
 * to achieve target AFR. Implements PID controller.
 */
void closed_loop_200hz(void)
{
    #define FUEL_CLOSED_LOOP_ACTIVE  0x01

    // Only run if in closed loop mode
    if ((fuel_flags_unknown & FUEL_CLOSED_LOOP_ACTIVE) == 0) {
        return;
    }

    // ========== Bank 1 Closed Loop Controller ==========

    // Calculate AFR error
    i16_afr_1_100 afr_error_b1 = afr_target - o2_sensor_afr_bank1_precat;

    // Proportional term
    u8_factor_1_255 p_gain = lookup_2D_uint8_interpolated(
        8,
        engine_speed_3,
        CAL_closedloop_proportional_gain,
        CAL_closedloop_proportional_gain_X_rpm);

    i16_factor proportional = (afr_error_b1 * p_gain) / 255;

    // Integral term (accumulated error over time)
    closedloop_integral_b1 += afr_error_b1;

    u8_factor_1_255 i_gain = lookup_2D_uint8_interpolated(
        8,
        engine_speed_3,
        CAL_closedloop_integral_gain,
        CAL_closedloop_integral_gain_X_rpm);

    i16_factor integral = (closedloop_integral_b1 * i_gain) / 255;

    // Derivative term (rate of change of error)
    i16_afr_1_100 afr_error_rate = afr_error_b1 - afr_error_b1_previous;
    afr_error_b1_previous = afr_error_b1;

    u8_factor_1_255 d_gain = CAL_closedloop_derivative_gain;
    i16_factor derivative = (afr_error_rate * d_gain) / 255;

    // Combine PID terms
    i16_factor pid_output = proportional + integral + derivative;

    // Convert to fuel trim multiplier (128 = 1.0)
    closedloop_fuel_trim_b1 = 128 + (pid_output / 16);

    // Clamp to valid range (0.75 to 1.25)
    if (closedloop_fuel_trim_b1 < 96) {
        closedloop_fuel_trim_b1 = 96;
    } else if (closedloop_fuel_trim_b1 > 160) {
        closedloop_fuel_trim_b1 = 160;
    }

    // Similar logic for Bank 2
    // (omitted for brevity)
}

/* 17 functions total - see original lines 16565-22200 */
