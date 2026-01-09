/*
 * types.h
 * 
 * Type Definitions for Lotus T6e ECU Firmware (E132E0288)
 * 
 * This file contains all type definitions extracted from the Ghidra disassembly.
 * The types use a naming convention that encodes both the data type and physical units.
 *
 * Naming Convention:
 *   - u8_  = unsigned 8-bit
 *   - u16_ = unsigned 16-bit  
 *   - u32_ = unsigned 32-bit
 *   - i8_  = signed 8-bit
 *   - i16_ = signed 16-bit
 *   - i32_ = signed 32-bit
 *
 * Unit Encoding Examples:
 *   - u8_temp_5/8-40c: Temperature = (value * 5/8) - 40°C
 *   - u16_rspeed_rpm: Engine speed in RPM (direct value)
 *   - u8_angle_1/4deg: Angle in 1/4 degree increments
 *   - u8_pressure_50mbar: Pressure in 50 millibar increments
 */

#ifndef TYPES_H
#define TYPES_H

/* ========================================================================
 * Section 1: Base Types (Ghidra-generated)
 * ======================================================================== */

typedef unsigned char   undefined;

typedef unsigned char    bool;
typedef unsigned char    byte;
typedef long long    longlong;
typedef unsigned char    uchar;
typedef unsigned int    uint;
typedef unsigned long    ulong;
typedef unsigned long long    ulonglong;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined3;
typedef unsigned int    undefined4;
typedef unsigned long long    undefined5;
typedef unsigned long long    undefined8;
typedef unsigned short    ushort;
typedef unsigned short    wchar16;
typedef ushort uint16_t;

typedef uint16_t u16_factor_1/32;

typedef short int16_t;

typedef char int8_t;

typedef int int32_t;

typedef uchar uint8_t;

typedef uint8_t u8_angle_1/4deg;

typedef uint16_t u16_flow_10mg/s;

typedef uint8_t u8_pressure_50mbar;

typedef uint8_t u8_speed_1/100kph;

typedef struct wheelspeeds_short wheelspeeds_short, *Pwheelspeeds_short;

struct wheelspeeds_short {
    short LR;
    short RR;
    short LF;
    short RF;
};

typedef uint8_t u8_load_1173mg/255stroke;

typedef uint16_t u16_factor_1/1023;

typedef uint8_t u8_factor_1/2560;

typedef uint16_t u16_rspeed_rpm;

typedef uint16_t u16_voltage_5/1023v;

typedef uint16_t u16_flow_100mg/s;

typedef uint16_t u16_time_us;

typedef uint8_t u8_torque_nm;

typedef uint8_t u8_rspeed_10rpm;

typedef uint8_t u8_temp_1/10C;

typedef uint8_t u8_count;

typedef uint8_t u8_angle_1/4-20deg;

typedef uint uint32_t;

typedef uint32_t u32_angle_1/10deg;

typedef uint8_t u8_factor_1/1023;

typedef uint8_t u8_dt_factor_1/100/5ms;

typedef enum enum_launch_mode {
    LC_INACTIVE=0,
    LC_READY=1,
    LC_ACTIVE_HOLD=2,
    LC_FREEREV=3
} enum_launch_mode;

typedef uint8_t u8_angle_1/4-10deg;

typedef uint16_t u16_power_1/100kw;

typedef uint8_t u8_angle_1/4-32deg;

typedef uint8_t u8_load_4mg/stroke;

typedef uint16_t u16_speed_kph_x100;

typedef uint8_t u8_factor_1/200;

typedef uint8_t u8_afr_1/20+5;

typedef uint16_t u16_volume_cc;

typedef int16_t i16_angle_1/4deg;

typedef uint16_t u16_factor_1/4095;

typedef uint16_t u16_pressure_mbar;

typedef enum enum_ips_shift_state {
    normal=0,
    pre-shift=1,
    speed-match=2,
    re-engage=3,
    recovery=4
} enum_ips_shift_state;

typedef struct struct_dspi_mmio struct_dspi_mmio, *Pstruct_dspi_mmio;

struct struct_dspi_mmio {
    uint32_t mcr;
    int32_t reserved1;
    uint32_t tcr;
    uint32_t ctar[8];
    uint32_t sr;
    uint32_t rser;
    uint32_t pushr;
    uint32_t popr;
    uint32_t txfr[4];
    byte reserved2[48];
    uint32_t rxfr[4];
    byte reverved3[48];
    uint32_t dsicr;
    uint32_t sdr;
    uint32_t asdr;
    uint32_t compr;
    uint32_t ddr;
};

typedef uint8_t u8_rspeed_8rpm;

typedef uint8_t u8_rspeed_2rpm;

typedef uint32_t u32_pressure_mbar;

typedef enum enum_ign_mode {
    IGN_COLD_START=0,
    IGN_FIXED=1,
    IGN_IDLE_AC=2,
    IGN_IDLE=3,
    IGN_NOMRAL_STARTUP=4,
    IGN_NORMAL=5,
    IGN_CRUISE_AC=6,
    IGN_CRUISE=7
} enum_ign_mode;

typedef uint16_t u16_flow_kg/h;

typedef uint8_t u8_time_ms;

typedef uint8_t u8_factor_1;

typedef uint32_t u32_angle_1/4deg;

typedef uint16_t u16_load_mg/stroke;

typedef uint16_t u16_temp_5/8-40c;

typedef struct struct_segment_bss struct_segment_bss, *Pstruct_segment_bss;

struct struct_segment_bss {
    pointer dest;
    uint size;
};

typedef uint8_t u8_distance_km;

typedef uint8_t u8_time_10ms;

typedef uint16_t u16_afr_1/100;

typedef uint8_t u8_afr_1/100;

typedef uint32_t u32_time_100ns;

typedef struct struct_tps_shaping_flags struct_tps_shaping_flags, *Pstruct_tps_shaping_flags;

struct struct_tps_shaping_flags {
    uint8_t current_input;
    uint8_t state;
    byte debounce;
    uint8_t decrement_rate;
    uint32_t increment_rate;
    uint32_t accum_timer;
    uint16_t curr_threshold;
    uint16_t threshold_0;
    uint16_t threshold_2;
};

typedef uint32_t u32_time_100ms;

typedef uint8_t u8_rspeed_4rpm;

typedef uint8_t u8_factor_1/100;

typedef uint8_t u8_torque_4nm;

typedef uint16_t u16_time_ms;

typedef uint8_t u8_time_s;

typedef uint8_t u8_mass_8g;

typedef uint8_t u8_rspeed_rpm;

typedef int16_t i16_accel_1/2550g;

typedef uint8_t u8_obd2level_t6;

typedef uint16_t u16_torque_nm;

typedef uint8_t u8_angle_720/256deg;

typedef struct cluster_data cluster_data, *Pcluster_data;

typedef uint8_t u8_temp_5/8-40c;

struct cluster_data {
    uint16_t fuel_usage_instantaneous;
    byte cluster_flags;
    byte fuel_level_pct;
    u8_temp_5/8-40c temp_coolant;
    byte cluster_indicator_flags;
    byte field6;
    byte field7;
};

typedef int8_t i8_angle_1/4deg;

typedef uint8_t u8_rspeed_4+500rpm;

typedef uint16_t u16_temp_1/10C;

typedef uint16_t u16_factor_1/255;

typedef uint8_t u8_factor_1/128;

typedef uint8_t u8_voltage_72/1023v;

typedef uint16_t u16_rspeed_1/4rpm;

typedef uint8_t u8_time_us;

typedef struct o2_narrowband_threshold o2_narrowband_threshold, *Po2_narrowband_threshold;

struct o2_narrowband_threshold { // o2_narrowband_threshold
    u16_voltage_5/1023v lean;
    u16_voltage_5/1023v rich;
};

typedef uint32_t u32_angle_1/10defg;

typedef uint32_t u32_temp_5/8-40__2560C;

typedef uint16_t u16_time_10ms;

typedef uint8_t u8_speed_1/10kph;

typedef uint8_t u8_time_20us;

typedef enum enum_throttle_system_state {
    THROTTLE_NORMAL0=0,
    THROTTLE_NORMAL1=1,
    THROTTLE_NORMAL2=2,
    THROTTLE_NORMAL3=3,
    THROTTLE_ESP_INTERVENTION=4,
    THROTTLE_EXT_TRQLIMIT=5,
    THROTTLE_CRUISE_ACTIVE=6,
    THROTTLE_CRUISE_INACTIVE=7,
    THROTTLE_TPS_FAULT=8,
    THROTTLE_SEVERE_FAULT1=9,
    THROTTLE_SEVERE_FAULT2=10,
    THROTTLE_SEVERE_FAULT3=11
} enum_throttle_system_state;

typedef uint16_t u16_flow_mg/s;

typedef uint8_t u8_temp_-40c;

typedef uint16_t u16_load_1173mg/255stroke;

typedef uint16_t u16_rspeed_4rpm;

typedef enum enum_accel_pedal_mode { // accel_pedal_mapping_mode
    unknown=0,
    low_gear=1,
    shifting=2,
    unknown3=3,
    high_gear=4
} enum_accel_pedal_mode;

typedef enum enum_knock_mode {
    NONE=0,
    goertzel_64sample=1,
    goertzel_2window=2,
    spectral_128window=3,
    goertzel_32sample_x3=4
} enum_knock_mode;

typedef int16_t i16_factor_1/20percent;

typedef uint8_t u8_pressure_4mbar;

typedef uint8_t u8_factor_1/255;

typedef uint8_t u8_time_256us;

typedef uint16_t u16_angle_1/10deg;

typedef struct struct_adc_smoothing_state struct_adc_smoothing_state, *Pstruct_adc_smoothing_state;

struct struct_adc_smoothing_state {
    int32_t x_prev;
    int32_t s1;
    int32_t s2;
    int32_t s3;
    int32_t s4;
    int16_t k0;
    int16_t b0;
    int16_t b1;
    int16_t a1;
    int16_t a2;
    int16_t c2;
    int16_t c0;
    int16_t c1;
};

typedef struct struct_emios_unified_channel_register struct_emios_unified_channel_register, *Pstruct_emios_unified_channel_register;

struct struct_emios_unified_channel_register {
    byte uc[256];
};

typedef uint8_t u8_factor_1/64;

typedef uint8_t u8_rspeed_50rpm;

typedef uint8_t u8_rspeed_125/4rpm;

typedef uint16_t u16_accel_1/10g;

typedef uint8_t u8_mass_g;

typedef uint32_t u32_rspeed_1024rpm;

typedef uint8_t u8_pressure_5kpa;

typedef uint8_t checksum_8bit;

typedef uint8_t u8_time_5ms;

typedef struct struct_segment_data struct_segment_data, *Pstruct_segment_data;

struct struct_segment_data {
    pointer src;
    pointer dest;
    uint size;
};

typedef uint16_t u16_flow_g/s;

typedef uint32_t u32_load_mg/stroke;

typedef uint8_t u8_time_64us;

typedef uint32_t u32_volume_1/11200_liter;

typedef int16_t i16_time_us;

typedef struct struct_dma_transfer_control_descriptor struct_dma_transfer_control_descriptor, *Pstruct_dma_transfer_control_descriptor;

struct struct_dma_transfer_control_descriptor {
    uint32_t saddr;
    uint32_t cfg;
    uint32_t nbytes;
    uint32_t daddr;
    uint32_t u1;
};

typedef uint16_t u16_factor_1/10000;

typedef enum enum_t6e_gear {
    NO_GEAR=0,
    GEAR_1=1,
    GEAR_2=2,
    GEAR_3=3,
    GEAR_4=4,
    GEAR_5=5,
    GEAR_6=6
} enum_t6e_gear;

typedef uint16_t u16_accel_g_x10;

typedef uint8_t u8_factor_1/32;

typedef uint8_t u8_torque_2nm;

typedef uint8_t u8_flow_2g/s;

typedef uint16_t u16_factor_1/65536;

typedef uint32_t u32_mass_ug;

typedef uint8_t u8_accel_1/2550g;

typedef int16_t i16_accel_g_x10;

typedef uint8_t u8_rspeed_125/4+500rpm;

typedef uint16_t u16_mass_mg;

typedef uint8_t u8_percent_100/128-100;

typedef enum enum_vehicle_mode {
    VM_TOUR=0,
    VM_SPORT=1,
    VM_TC_OFF=2,
    VM_RACE=3,
    VM_LAUNCH=4,
    VM_LAUNCH_SUB1=5,
    VM_LAUNCH_FALLBACK=6
} enum_vehicle_mode;

typedef uint32_t u32_time_us;

typedef uint16_t u16_time_50ms;

typedef uint16_t u16_time_s;

typedef uint8_t u8_rspeed_-128;

typedef uint16_t u16_time_4us;

typedef uint8_t u8_gear;

typedef int32_t i32_accel_1/2550g;

typedef uint32_t u32_distance_1/112500km;

typedef uint16_t u16_angle_deg_x2;

typedef uint16_t u16_time_5ms;

typedef uint8_t u8_angle_1/4-64deg;

typedef uint8_t u8_load_2mg/stroke;

typedef uint8_t u8_fuel_gal_x10;

typedef uint8_t u8_time_20ms;

typedef uint16_t u16_distance_mm_div2;

typedef enum enum_etc_state {
    ETB_INIT=0,
    ETB_INIT_DELAY=1,
    ETB_CALIBRATE_START=2,
    ETB_CALIBRATE_MONITOR=3,
    ETB_CALIBRATE_RANGE=4,
    ETB_CALIBRATE_DEFAULT=5,
    ETB_FIRST_CYCLE=6,
    ETB_NORMAL=7,
    ETB_FAULT=8
} enum_etc_state;

typedef uint16_t u16_flow_50mg/s;

typedef uint8_t u8_rspeed_4-512rpm;

typedef uint16_t u16_temp_K;

typedef uint16_t u16_voltage_18/1023v;

typedef enum enum_idle_strategy {
    IDLE_IPS_FALLBACK=1,
    IDLE_IPS_NORMAL=2,
    IDLE_MANUAL_TOUR=3,
    IDLE_MANUAL_SPORT=4
} enum_idle_strategy;

typedef enum enum_vin_type {
    VT_NONE=0,
    VT_2010-2011=1,
    VT_2011-2021=2
} enum_vin_type;

typedef uint16_t u16_press_kpa;

typedef uint16_t u16_ratio_mbar/5v;

typedef uint16_t u16_mass_g;

typedef uint8_t u8_rspeed_25rpm;

typedef struct flexcan_msg_buffer flexcan_msg_buffer, *Pflexcan_msg_buffer;

struct flexcan_msg_buffer {
    uint code_and_timestamp;
    uint32_t arb_id;
    byte data[8];
};

typedef uint8_t u8_rspeed_10+6000rpm;

typedef uint16_t u16_speed_1/100kph;

typedef uint8_t u8_time_250ms;

typedef uint8_t u8_time_50ms;

typedef uint8_t u8_speed_kph;

typedef uint32_t u32_distance_km;

typedef uint8_t u8_voltage_5/255v;

typedef uint8_t u8_dutycycle_100/255;

typedef uint16_t u16_mass_100ug;

typedef uint8_t u8_flow_100mg/s;

typedef uint16_t u16_angle_1/4deg;

typedef uint32_t u32_time_50ms;

typedef uint16_t u16_distance_km;

typedef int16_t i16_accel_1/10g;

typedef int16_t i16_pressure_mbar;

typedef struct wheelspeeds_int wheelspeeds_int, *Pwheelspeeds_int;

struct wheelspeeds_int {
    int LR;
    int RR;
    int LF;
    int RF;
};

typedef uint8_t u8_time_hours;

typedef uint16_t u16_time_100ms;

typedef enum enum_traction_mode {
    TC_DISABLED=0,
    TC_EXTERNAL_ONLY=1,
    TC_ENABLED=2,
    TC_VARIABLE=3
} enum_traction_mode;

typedef struct struct_esci_control_registers struct_esci_control_registers, *Pstruct_esci_control_registers;

struct struct_esci_control_registers {
    uint32_t cr1;
    uint16_t cr2;
    uint16_t dr;
    uint32_t sr;
    uint32_t lcr;
    uint32_t ltr;
    uint32_t lrr;
    uint32_t lpr;
};

typedef int16_t i16_factor_1/10pct;

typedef uint32_t u32_torque_nm;

typedef uint8_t u8_time_100ms;

typedef uint32_t u32_speed_kph_x100;

typedef uint8_t u8_percent_-125;

typedef uint32_t u32_rspeed_rpm;

typedef uint32_t u32_speed_kph_1/100kph;

typedef enum enum_tps_smooth_step_flag {
    TPS_SMOOTH_NO_STEP=0,
    TPS_SMOOTH_STEP_UP=1,
    TPS_SMOOTH_STEP_DOWN=2
} enum_tps_smooth_step_flag;

typedef uint32_t u32_time_5ms;

typedef uint8_t u8_time_10us;

typedef ulong size_t;

typedef struct evp_pkey_ctx_st evp_pkey_ctx_st, *Pevp_pkey_ctx_st;

typedef struct evp_pkey_ctx_st EVP_PKEY_CTX;

struct evp_pkey_ctx_st {
};

typedef ulonglong uint64_t;


#endif /* TYPES_H */
