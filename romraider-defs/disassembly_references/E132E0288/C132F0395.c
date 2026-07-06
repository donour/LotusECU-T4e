#define 22 0x16
#define 64 0x40
#define 7150 0x1bee
#define 30 0x1e
#define 30600 0x7788
#define 120 0x78
#define 955 0x3bb
#define 32767 0x7fff
#define 2560 0xa00
#define 3 0x3
#define 16 0x10
#define 23 0x17
#define 0 0x0
#define 15 0xf
#define 32 0x20
#define 1600 0x640
#define 1020 0x3fc
#define 255 0xff
#define 2400 0x960
#define -59 -0x3b
#define 660 0x294
#define 60 0x3c
#define 11111101b 0xfd
#define 00000000000000000000000000000010b 0x2
#define 112 0x70
#define 11111110b 0xfe
#define 01111111b 0x7f
#define 10000000b 0x80
#define 00000000000000000000000000001111b 0xf
#define 19 0x13
#define 291 0x123
#define 12 0xc
#define 00000000000000000000000000111111b 0x3f
#define 00000000000000000000000011111111b 0xff

typedef unsigned char   undefined;

typedef unsigned char    bool;
typedef unsigned char    byte;
typedef unsigned char    uchar;
typedef unsigned int    uint;
typedef unsigned long    ulong;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined4;
typedef unsigned long long    undefined8;
typedef unsigned short    ushort;
typedef unsigned short    wchar16;
typedef short int16_t;

typedef int int32_t;

typedef char int8_t;

typedef struct evp_pkey_ctx_st evp_pkey_ctx_st, *Pevp_pkey_ctx_st;

typedef struct evp_pkey_ctx_st EVP_PKEY_CTX;

struct evp_pkey_ctx_st {
};

typedef uchar uint8_t;

typedef uint8_t u8_angle_1/4deg;

typedef ushort uint16_t;

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

typedef struct struct_variant_coding_t6e struct_variant_coding_t6e, *Pstruct_variant_coding_t6e;

typedef uint uint32_t;

struct struct_variant_coding_t6e {
    uint32_t COD[2];
    char vin[17];
    byte unused[7];
    char model[32];
    uint16_t crc;
    byte unused2[2];
};

typedef uint8_t u8_torque_nm;

typedef uint8_t u8_rspeed_10rpm;

typedef uint8_t u8_temp_1/10C;

typedef uint8_t u8_count;

typedef uint8_t u8_angle_1/4-20deg;

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

typedef uint16_t u16_fuel_gal_x10;

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

typedef struct struct_hc08_config struct_hc08_config, *Pstruct_hc08_config;

struct struct_hc08_config {
    char name[8];
    uint32_t programming_magic_word;
    byte *firmware;
};

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

typedef uint16_t u16_current_mA;

typedef struct struct_ols_params struct_ols_params, *Pstruct_ols_params;

struct struct_ols_params {
    short slope_x100;
    short intercept;
    uint8_t padding[16];
    uint8_t sample_count;
};

typedef uint8_t u8_factor_1/100;

typedef uint8_t u8_torque_4nm;

typedef uint16_t u16_time_ms;

typedef uint8_t u8_time_s;

typedef uint8_t u8_mass_8g;

typedef uint8_t u8_rspeed_rpm;

typedef int16_t i16_accel_1/2550g;

typedef uint8_t u8_-127;

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

typedef enum enum_cruise_switch_pos {
    CRUISE_CANCEL=0,
    CRUISE_SET_COAST=1,
    CRUISE_RESUME_ACCEL=2,
    CRUISE_UNNOWN3=3,
    CRUISE_UKNOWN4=4,
    CRUISE_UKNOWN5=5,
    CRUISE_ON=6,
    CRUISE_INVALID=7
} enum_cruise_switch_pos;

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

typedef enum enum_slip_detect_mode {
    SLIP_DETECT_DISABLED=0,
    SLIP_DETECT_1=1,
    SLIP_DETECT_2=2,
    SLIP_DETECT_3=3
} enum_slip_detect_mode;

typedef struct struct_digital_input_cfg struct_digital_input_cfg, *Pstruct_digital_input_cfg;

struct struct_digital_input_cfg {
    uint8_t flags;
    uint8_t press_debounce_time;
    uint8_t release_debounce_time;
    uint8_t debounce_counter;
    uint8_t edge_latch;
};

typedef struct struct_segment_data struct_segment_data, *Pstruct_segment_data;

struct struct_segment_data {
    pointer src;
    pointer dest;
    uint size;
};

typedef uint16_t u16_accel_1/10g;

typedef uint8_t u8_rspeed_5rpm;

typedef uint8_t u8_mass_g;

typedef uint32_t u32_rspeed_1024rpm;

typedef uint8_t u8_pressure_5kpa;

typedef uint8_t checksum_8bit;

typedef uint8_t u8_time_5ms;

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
    NEUTRAL=0,
    GEAR_1=1,
    GEAR_2=2,
    GEAR_3=3,
    GEAR_4=4,
    GEAR_5=5,
    GEAR_6=6,
    GEAR_INVALID7=7,
    GEAR_INVALID8=8,
    GEAR_INVALID9=9,
    GEAR_REV=10
} enum_t6e_gear;

typedef uint16_t u16_accel_g_x10;

typedef uint8_t u8_factor_1/32;

typedef uint8_t u8_rspeed_30rpm;

typedef uint8_t u8_torque_2nm;

typedef uint8_t u8_flow_2g/s;

typedef uint16_t u16_factor_1/65536;

typedef uint32_t u32_mass_ug;

typedef uint8_t u8_accel_1/2550g;

typedef int16_t i16_accel_g_x10;

typedef enum enum_drive_cycle_assist {
    DCA_INACTIVE=0,
    DCA_READY=1,
    DCA_ACTIVE_HOLD=2,
    DCA_FREEREV=3
} enum_drive_cycle_assist;

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

typedef uint8_t u8_voltage_1/200v;

typedef uint16_t u16_time_5ms;

typedef uint8_t u8_angle_1/4-64deg;

typedef uint8_t u8_rspeed_25rpm;

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

typedef enum enum_exhaust_stationary_override {
    EXHAUST_STATIONARY_OVERRIDE_DISABLED=0,
    EXHAUST_STATIONARY_OVERRIDE_NON_RACE=1,
    EXHAUST_STATIONARY_OVERRIDE_RACE_ONLY=2,
    EXHAUST_STATIONARY_OVERRIDE_ALL=3
} enum_exhaust_stationary_override;

typedef uint8_t u8_time_100ms;

typedef uint32_t u32_speed_kph_x100;

typedef uint16_t u16_torque_1/4+400nm;

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

typedef struct astruct astruct, *Pastruct;

struct astruct {
    short field0_0x0;
    short field1_0x2;
    undefined field2_0x4;
    undefined field3_0x5;
    undefined field4_0x6;
    undefined field5_0x7;
    undefined field6_0x8;
    undefined field7_0x9;
    undefined field8_0xa;
    undefined field9_0xb;
    undefined field10_0xc;
    undefined field11_0xd;
    undefined field12_0xe;
    undefined field13_0xf;
    undefined field14_0x10;
    undefined field15_0x11;
    undefined field16_0x12;
    undefined field17_0x13;
    byte field18_0x14;
};



uint REG_FLASH_BIUAPR;
undefined DAT_00001770;
uint REG_FMPLL_SYNSR;
uint REG_SIU_SRCR;
undefined4 DAT_c3fd8b00;
undefined4 DAT_00088610;
undefined4 DAT_00088614;
uint REG_FMPLL_SYNCR;
undefined DAT_00009cc0;
pointer switchdataD_40000000;
undefined DAT_400093a8;
undefined SUB_4000f000;
undefined intc_setup_safe_write;
undefined4 DAT_000885f0;
undefined4 DAT_000885f4;
undefined4 DAT_000885f8;
undefined4 DAT_00088600;
undefined4 DAT_00088604;
undefined *PTR_DAT_00088608;
undefined4 DAT_00088618;
undefined4 DAT_00088620;
undefined4 DAT_00088624;
undefined4 DAT_00088628;
undefined4 DAT_00088630;
undefined4 DAT_00088634;
undefined *PTR_PTR_00088638;
undefined4 DAT_00088640;
undefined4 DAT_00088644;
undefined *PTR_DAT_00088648;
undefined4 DAT_00088650;
undefined *PTR_PTR_00088654;
undefined4 DAT_00088658;
undefined4 DAT_0008865c;
undefined4 DAT_00088660;
undefined4 DAT_00088668;
undefined4 DAT_0008866c;
undefined4 DAT_00088670;
undefined4 DAT_00088678;
undefined4 DAT_0008867c;
undefined4 DAT_00088680;
undefined4 DAT_00088688;
undefined4 DAT_0008868c;
undefined4 DAT_00088690;
undefined4 DAT_00088698;
undefined4 DAT_0008869c;
undefined4 DAT_000886a0;
undefined4 DAT_000886a8;
undefined4 DAT_000886ac;
undefined4 DAT_000886b0;
undefined4 DAT_000886b8;
undefined4 DAT_000886bc;
undefined4 DAT_000886c0;
undefined4 DAT_000886c4;
struct_segment_data[15] segment_data;
struct_segment_bss[4] segment_bss;
undefined *PTR_PTR_00091eec;
uint REG_INTC_MCR;
uint REG_INTC_IACKR;
int DAT_400014d0;
byte REG_INTC_SSCIR4;
uint REG_INTC_CPR;
uint REG_SIU_ECCR;
ushort REG_SIU_PCR229;
ushort REG_SIU_PCR214;
ushort REG_SIU_PCR0;
uint REG_EBI_MCR;
uint REG_EBI_BR0;
uint REG_EBI_OR0;
ushort REG_EQADC_CFCR0;
uint DAT_400014dc;
uint DAT_400014d8;
uint REG_EQADC_CFPR0;
ushort REG_EQADC_IDCR0;
uint REG_EQADC_RFPR0;
uint REG_EQADC_CFSR;
uint REG_EQADC_FISR0;
uint DAT_40001d10;
uint DAT_40001d60;
uint DAT_40001d24;
uint DAT_40001d4c;
uint DAT_40001d38;
uint DAT_40001d64;
uint DAT_40001d50;
uint DAT_40001d28;
uint DAT_40001d3c;
uint DAT_40001d14;
undefined2 DAT_40001d7e;
undefined2 DAT_40001d80;
undefined2 DAT_40001d82;
undefined2 DAT_40001d84;
undefined2 DAT_40001d86;
undefined2 DAT_40001d74;
undefined2 DAT_40001d76;
undefined2 DAT_40001d78;
undefined2 DAT_40001d7a;
undefined2 DAT_40001d7c;
uint DAT_400014e8;
uint DAT_400014e4;
undefined2 DAT_400014e2;
undefined2 DAT_400014e0;
uint REG_EQADC_RFPR1;
uint REG_EQADC_RFPR2;
uint REG_EQADC_RFPR3;
uint REG_EQADC_RFPR4;
uint REG_EQADC_FISR1;
uint REG_EQADC_FISR2;
uint REG_EQADC_FISR3;
uint REG_EQADC_FISR4;
undefined4 DAT_40002038;
undefined4 DAT_4000203c;
undefined4 DAT_40002040;
undefined4 DAT_40002044;
undefined4 DAT_40002048;
undefined4 DAT_4000204c;
ushort REG_EQADC_CFCR1;
ushort REG_EQADC_CFCR2;
ushort REG_EQADC_CFCR3;
ushort REG_EQADC_CFCR4;
ushort REG_EQADC_CFCR5;
ushort REG_EQADC_IDCR1;
ushort REG_EQADC_IDCR2;
ushort REG_EQADC_IDCR3;
ushort REG_EQADC_IDCR4;
ushort REG_EQADC_IDCR5;
uint REG_EQADC_MCR;
uint REG_EQADC_FISR5;
uint REG_EQADC_NMSFR;
uint REG_EQADC_ETDFR;
undefined4 DAT_400020f0;
undefined4 DAT_400020f4;
undefined4 DAT_400020f8;
undefined4 DAT_400020fc;
undefined4 DAT_40002100;
undefined4 DAT_40002104;
undefined4 DAT_40002108;
undefined4 DAT_40002050;
undefined4 DAT_40002054;
undefined4 DAT_40002058;
undefined4 DAT_4000205c;
undefined4 DAT_40002060;
undefined4 DAT_40002064;
undefined4 DAT_40002068;
undefined4 DAT_4000206c;
undefined4 DAT_40002070;
undefined4 DAT_40002074;
undefined4 DAT_40002078;
undefined4 DAT_4000207c;
undefined4 DAT_40002080;
undefined4 DAT_40002084;
undefined4 DAT_40002088;
undefined4 DAT_4000208c;
undefined4 DAT_40002090;
undefined4 DAT_40002094;
undefined4 DAT_40002098;
undefined4 DAT_4000209c;
undefined4 DAT_400020a0;
undefined4 DAT_400020a4;
undefined4 DAT_400020a8;
undefined4 DAT_400020ac;
undefined4 DAT_400020b0;
undefined4 DAT_400020b4;
undefined4 DAT_400020b8;
undefined4 DAT_400020bc;
undefined4 DAT_400020c0;
undefined4 DAT_400020c4;
undefined4 DAT_400020c8;
undefined4 DAT_400020cc;
undefined4 DAT_400020d0;
undefined4 DAT_400020d4;
undefined4 DAT_400020d8;
undefined4 DAT_400020dc;
undefined4 DAT_400020e0;
undefined4 DAT_400020e4;
undefined4 DAT_400020e8;
uint *DAT_400015e4;
undefined4 DAT_400015e0;
undefined4 DAT_400015dc;
undefined4 DAT_400015d0;
uint DAT_400015dc;
int DAT_400015e4;
uint DAT_400015d0;
uint DAT_400015d8;
int DAT_400015d4;
int DAT_400015dc;
ushort REG_SIU_PCR203;
ushort REG_SIU_PCR204;
ushort REG_SIU_PCR211;
ushort REG_SIU_PCR212;
undefined2 DAT_c3f90158;
undefined2 DAT_c3f9015a;
undefined2 DAT_c3f90150;
undefined2 DAT_c3f90152;
undefined2 DAT_c3f90154;
undefined2 DAT_c3f90156;
undefined2 DAT_c3f9014e;
ushort REG_SIU_PCR91;
ushort REG_SIU_PCR92;
ushort REG_SIU_PCR96;
ushort REG_SIU_PCR98;
ushort REG_SIU_PCR99;
ushort REG_SIU_PCR100;
ushort REG_SIU_PCR113;
ushort REG_SIU_PCR114;
ushort REG_SIU_PCR115;
ushort REG_SIU_PCR116;
ushort REG_SIU_PCR117;
ushort REG_SIU_PCR118;
ushort REG_SIU_PCR119;
ushort REG_SIU_PCR120;
ushort REG_SIU_PCR121;
ushort REG_SIU_PCR122;
ushort REG_SIU_PCR123;
ushort REG_SIU_PCR124;
ushort REG_SIU_PCR125;
ushort REG_SIU_PCR126;
ushort REG_SIU_PCR127;
ushort REG_SIU_PCR128;
ushort REG_SIU_PCR129;
ushort REG_SIU_PCR130;
ushort REG_SIU_PCR131;
ushort REG_SIU_PCR132;
ushort REG_SIU_PCR133;
ushort REG_SIU_PCR134;
ushort REG_SIU_PCR142;
ushort REG_SIU_PCR143;
ushort REG_SIU_PCR144;
ushort REG_SIU_PCR145;
ushort REG_SIU_PCR182;
ushort REG_SIU_PCR183;
ushort REG_SIU_PCR185;
ushort REG_SIU_PCR186;
ushort REG_SIU_PCR191;
ushort REG_SIU_PCR192;
ushort REG_SIU_PCR193;
ushort REG_SIU_PCR194;
ushort REG_SIU_PCR195;
ushort REG_SIU_PCR201;
undefined1 DAT_4000150b;
undefined1 DAT_4000150a;
undefined1 DAT_40001509;
undefined1 DAT_40001508;
undefined1 DAT_40001505;
undefined1 DAT_40001507;
undefined1 DAT_40001506;
undefined1 DAT_40001504;
undefined4 *DAT_400013a8;
undefined2 DAT_400014f2;
undefined DAT_40008e78;
undefined1 eeprom_flash_erase_pending_flags;
uint16_t calibration_verification_number;
bool tcu_unlocked;
char[4] CAL_tcu_unlock_magic;
undefined1 DAT_400014f9;
byte DAT_400019e8;
undefined2 DAT_40001538;
int DAT_400021d8;
undefined4 DAT_400015ec;
int DAT_4000150c;
int DAT_400021e8;
int DAT_400021ec;
char DAT_400017e8;
char DAT_400014fa;
int DAT_400021dc;
int DAT_400021e0;
int DAT_400021e4;
int DAT_400013b0;
int DAT_400021f0;
int DAT_400021f4;
undefined PTR_DAT_400013b4;
short DAT_40003446;
uint REG_SIU_RSR;
undefined1 *DAT_40001500;
undefined4 DAT_400014fc;
int *DAT_40001500;
char DAT_400014f8;
uint REG_EMIOS_UC22_CADR;
uint REG_EMIOS_UC22_CBDR;
byte REG_INTC_PSR208;
uint REG_EMIOS_UC22_CCNTR;
uint REG_EMIOS_UC22_CCR;
ushort DAT_40001538;
byte DAT_40001525;
ushort DAT_40003448;
undefined4 DAT_400022a8;
int DAT_4000227c;
int DAT_400022d4;
int DAT_40002224;
int DAT_400021ac;
char DAT_400013c6;
char DAT_40001519;
char DAT_4000151a;
char DAT_4000151b;
char DAT_4000151c;
char DAT_4000151d;
char DAT_4000151e;
char DAT_4000151f;
char DAT_40001520;
char DAT_40001521;
char DAT_40001522;
byte DAT_40001523;
char DAT_400013c5;
undefined4 DAT_400022ac;
undefined4 etpu_elapsed_min_ticks;
undefined4 DAT_40002254;
undefined4 etpu_elapsed_max_captured_ticks;
undefined4 DAT_400022b0;
byte DAT_40001526;
byte DAT_40001524;
short DAT_40003444;
byte DAT_40003442;
undefined1 DAT_40003443;
undefined4 DAT_40002258;
undefined4 DAT_40002250;
char DAT_40001518;
undefined4 DAT_400013b0;
char DAT_40001418;
byte DAT_40003480;
char DAT_400016b0;
undefined4 DAT_400022d8;
undefined4 DAT_40002280;
undefined4 DAT_400022dc;
undefined4 DAT_40002284;
undefined4 DAT_400022e0;
undefined4 DAT_40002288;
undefined4 DAT_400022e4;
char DAT_4000153a;
int DAT_40001540;
char DAT_4000153c;
char DAT_4000153b;
short DAT_400016a8;
short DAT_400016aa;
undefined4 DAT_4000228c;
undefined4 DAT_400022e8;
char DAT_400013be;
u16_rspeed_1/4rpm tach_rpm;
undefined4 DAT_400022b4;
char DAT_40001654;
uint8_t[2] driver_input_flags;
undefined4 DAT_4000225c;
undefined4 DAT_40002290;
u16_rspeed_1/4rpm CAL_rpm_engine_running;
undefined4 DAT_400022ec;
char DAT_400013bf;
undefined4 DAT_400022b8;
undefined4 DAT_40002260;
undefined4 DAT_40002294;
undefined4 DAT_400022f0;
char DAT_400013c0;
undefined4 DAT_400022bc;
undefined4 DAT_40002264;
undefined4 DAT_40002298;
undefined4 DAT_400022f4;
short DAT_400013bc;
undefined4 DAT_400022c0;
undefined2 DAT_40001664;
uint DAT_40001528;
short DAT_40001510;
ushort DAT_400015b8;
short DAT_40001512;
char DAT_40001632;
short DAT_40001674;
char DAT_40001a11;
char DAT_40001a12;
char DAT_400013c1;
undefined4 DAT_400022c4;
undefined4 DAT_4000226c;
char DAT_400013c2;
undefined4 DAT_400022c8;
undefined4 DAT_40002270;
char DAT_400013c3;
undefined4 DAT_400022cc;
undefined4 DAT_40002274;
char DAT_400013c4;
undefined4 DAT_400022d0;
undefined4 DAT_40002278;
undefined4 DAT_40002268;
undefined4 DAT_4000229c;
undefined4 DAT_400022f8;
short DAT_40001662;
int DAT_400013b8;
int DAT_40001514;
undefined4 DAT_400022a0;
undefined4 DAT_400022fc;
undefined4 DAT_400022a4;
undefined4 DAT_40002180;
undefined4 DAT_400021f8;
undefined1 engine_running;
uint REG_EMIOS_UC22_CSR;
byte REG_INTC_PSR68;
ushort DAT_40008ff4;
undefined DAT_00002710;
byte REG_INTC_PSR79;
byte REG_INTC_PSR80;
byte REG_INTC_PSR86;
byte REG_INTC_PSR87;
byte REG_INTC_PSR88;
byte REG_INTC_PSR89;
byte REG_INTC_PSR90;
byte REG_INTC_PSR91;
byte REG_INTC_PSR92;
byte REG_INTC_PSR93;
byte REG_INTC_PSR94;
byte REG_INTC_PSR95;
byte REG_INTC_PSR96;
byte REG_INTC_PSR97;
byte REG_INTC_PSR98;
undefined1 DAT_400013ca;
undefined1 DAT_4000235c;
undefined1 DAT_400013cb;
undefined1 DAT_40002340;
char DAT_40008fea;
ushort DAT_40001de8;
undefined2 DAT_40002394;
ushort DAT_40001dea;
undefined2 DAT_40002396;
ushort DAT_40001dec;
undefined2 DAT_40002398;
ushort DAT_40001dee;
undefined2 DAT_4000239a;
ushort DAT_40001df0;
undefined2 DAT_4000239c;
ushort DAT_40001df2;
undefined2 DAT_4000239e;
char DAT_40001548;
char DAT_400013ca;
char DAT_4000235c;
undefined *DAT_40002374;
char DAT_400013cb;
enum_t6e_gear shift_from_gear;
char DAT_40002340;
undefined *DAT_40002358;
char DAT_400013c8;
uint DAT_40001678;
ushort DAT_40008f7c;
char DAT_400013c9;
undefined2 DAT_40001566;
short DAT_40001564;
short DAT_40001562;
undefined2 DAT_40001560;
char DAT_4000156a;
char DAT_40001be0;
byte DAT_40001be1;
byte DAT_40009162;
byte DAT_400013cc;
undefined2 DAT_40001550;
undefined2 DAT_4000154e;
undefined2 DAT_4000154c;
char DAT_40009161;
undefined2 DAT_40001552;
char DAT_40009160;
char DAT_4000915e;
char DAT_40008ff7;
char DAT_40008f9e;
byte DAT_40008f68;
int DAT_40001558;
byte DAT_40008f69;
int DAT_40001554;
char DAT_40001c3a;
byte DAT_400013cd;
undefined1 DAT_4000154a;
undefined1 DAT_40001549;
ushort DAT_40008fde;
ushort DAT_40008fdc;
ushort DAT_400015bc;
short DAT_4000155e;
ushort DAT_400090ae;
ushort DAT_400090ac;
ushort DAT_400015be;
short DAT_4000155c;
pointer PTR_DAT_000886c8;
u16_rspeed_rpm input_shaft_rpm;
u16_rspeed_rpm output_shaft_rpm_sensor;
u16_rspeed_rpm output_shaft_rpm;
u16_rspeed_rpm[16] input_shaft_rpm_history;
u16_rspeed_rpm[16] output_shaft_rpm_history;
enum_t6e_gear gear_request;
undefined2 vehicle_speed_???;
undefined1 shift_torque_managed;
undefined1 shift_mode_word;
undefined1 DAT_400015b0;
byte REG_SIU_GPDO190;
ushort REG_SIU_PCR190;
ushort REG_SIU_PCR102;
ushort REG_SIU_PCR103;
ushort REG_SIU_PCR104;
uint REG_DSPI_C_MCR;
ushort REG_SIU_PCR107;
ushort REG_SIU_PCR108;
ushort REG_SIU_PCR109;
uint REG_DSPI_B_MCR;
ushort REG_SIU_PCR95;
uint REG_DSPI_B_CTAR0;
undefined1 DAT_4000237f;
undefined1 DAT_40002380;
uint REG_DSPI_C_SR;
uint REG_DSPI_B_SR;
uint REG_DSPI_B_PUSHR;
uint REG_DSPI_B_POPR;
undefined1 DAT_4000237d;
undefined1 DAT_4000237a;
undefined1 DAT_4000237c;
uint REG_DSPI_C_PUSHR;
uint REG_DSPI_C_POPR;
uint REG_DSPI_C_CTAR0;
byte DAT_400013d0;
char DAT_40001571;
byte DAT_40001570;
byte DAT_40002379;
uint REG_DSPI_C_CTAR1;
byte REG_EDMA_CPR15;
byte REG_EDMA_CPR16;
byte REG_EDMA_CPR17;
byte REG_EDMA_CPR18;
byte REG_EDMA_CPR19;
byte REG_EDMA_CPR20;
byte REG_EDMA_CPR21;
byte REG_EDMA_CPR22;
byte REG_EDMA_CPR23;
byte REG_EDMA_CPR24;
byte REG_EDMA_CPR25;
byte REG_EDMA_CPR26;
byte REG_EDMA_CPR27;
byte REG_EDMA_CPR28;
byte REG_EDMA_CPR29;
byte REG_EDMA_CPR30;
byte REG_EDMA_CPR31;
uint REG_EDMA_CR;
uint REG_EDMA_ERQRL;
uint REG_EDMA_EEIRL;
byte REG_EDMA_CPR0;
byte REG_EDMA_CPR1;
byte REG_EDMA_CPR2;
byte REG_EDMA_CPR3;
byte REG_EDMA_CPR4;
byte REG_EDMA_CPR5;
byte REG_EDMA_CPR6;
byte REG_EDMA_CPR7;
byte REG_EDMA_CPR8;
byte REG_EDMA_CPR9;
byte REG_EDMA_CPR10;
byte REG_EDMA_CPR11;
byte REG_EDMA_CPR12;
byte REG_EDMA_CPR13;
byte REG_EDMA_CPR14;
undefined2 DAT_fff45144;
undefined2 DAT_fff45154;
undefined2 DAT_fff45146;
undefined2 DAT_fff45156;
undefined4 DAT_fff45150;
undefined4 DAT_fff4514c;
undefined2 DAT_fff4515c;
undefined2 DAT_fff4515e;
undefined4 REG_EDMA_TCD10;
undefined4 DAT_fff45148;
undefined4 DAT_fff45158;
undefined2 DAT_fff450f4;
undefined4 DAT_fff45010;
undefined2 DAT_fff45004;
undefined2 DAT_fff450f6;
undefined2 DAT_fff45006;
undefined4 DAT_fff45008;
undefined4 DAT_fff450f0;
undefined4 DAT_fff4500c;
undefined2 DAT_fff45014;
undefined2 DAT_fff45016;
undefined4 DAT_fff45018;
undefined2 DAT_fff450fc;
undefined2 DAT_fff4501c;
undefined2 DAT_fff4501e;
undefined2 DAT_fff450fe;
undefined4 DAT_fff450f8;
undefined2 DAT_fff450e4;
undefined2 DAT_fff450e6;
undefined4 DAT_fff450ec;
undefined4 DAT_fff450e8;
undefined2 DAT_fff450d4;
undefined2 DAT_fff450d6;
undefined4 DAT_fff450d0;
undefined2 DAT_fff450dc;
undefined2 DAT_fff450de;
undefined4 DAT_fff450d8;
uint REG_EDMA_IRQRL;
undefined2 DAT_fff450c4;
undefined2 DAT_fff450c6;
undefined4 DAT_fff450cc;
undefined4 DAT_fff450c8;
undefined2 DAT_fff450b4;
undefined2 DAT_fff450b6;
undefined4 DAT_fff450b0;
undefined2 DAT_fff450bc;
undefined2 DAT_fff450be;
undefined4 DAT_fff450b8;
undefined2 DAT_fff450a4;
undefined4 REG_EDMA_TCD0;
undefined4 REG_EDMA_TCD1;
undefined2 DAT_fff450a6;
undefined4 REG_EDMA_TCD2;
undefined4 REG_EDMA_TCD3;
undefined4 REG_EDMA_TCD4;
undefined4 REG_EDMA_TCD5;
undefined4 REG_EDMA_TCD6;
undefined4 DAT_fff450ac;
undefined4 REG_EDMA_TCD7;
undefined4 REG_EDMA_TCD8;
undefined4 REG_EDMA_TCD9;
undefined4 DAT_fff450a8;
undefined4 REG_EDMA_TCD11;
undefined2 DAT_fff45094;
undefined2 DAT_fff45096;
undefined4 DAT_fff45090;
undefined2 DAT_fff4509c;
undefined2 DAT_fff4509e;
undefined4 DAT_fff45098;
undefined2 DAT_fff45084;
undefined2 DAT_fff45086;
undefined4 DAT_fff4508c;
undefined4 DAT_fff45088;
undefined2 DAT_fff45074;
undefined2 DAT_fff45174;
undefined2 DAT_fff45076;
undefined2 DAT_fff45176;
undefined4 DAT_fff45070;
undefined4 DAT_fff45170;
undefined2 DAT_fff4507c;
undefined2 DAT_fff4517c;
undefined2 DAT_fff4507e;
undefined2 DAT_fff4517e;
undefined4 DAT_fff45078;
undefined4 DAT_fff45178;
undefined2 DAT_fff45064;
undefined2 DAT_fff45164;
undefined2 DAT_fff45066;
undefined2 DAT_fff45166;
undefined4 DAT_fff4506c;
undefined4 DAT_fff4516c;
undefined4 DAT_fff45068;
undefined4 DAT_fff45168;
undefined2 DAT_fff45054;
undefined2 DAT_fff45056;
undefined4 DAT_fff45050;
undefined2 DAT_fff4505c;
undefined2 DAT_fff4505e;
undefined4 DAT_fff45058;
undefined2 DAT_fff45044;
undefined2 DAT_fff45046;
undefined4 DAT_fff4504c;
undefined4 DAT_fff45048;
undefined2 DAT_fff45034;
undefined2 DAT_fff45134;
undefined2 DAT_fff45036;
undefined2 DAT_fff45136;
undefined4 DAT_fff45030;
undefined4 DAT_fff45130;
undefined2 DAT_fff4503c;
undefined2 DAT_fff4513c;
undefined2 DAT_fff4503e;
undefined2 DAT_fff4513e;
undefined4 DAT_fff45038;
undefined4 DAT_fff45138;
undefined2 DAT_fff45024;
undefined2 DAT_fff45124;
undefined2 DAT_fff45026;
undefined2 DAT_fff45126;
undefined4 DAT_fff4502c;
undefined4 DAT_fff4512c;
undefined4 DAT_fff45028;
undefined4 DAT_fff45128;
undefined2 DAT_fff45114;
undefined2 DAT_fff45116;
undefined4 DAT_fff45110;
undefined2 DAT_fff4511c;
undefined2 DAT_fff4511e;
undefined4 DAT_fff45118;
undefined2 DAT_fff45104;
undefined2 DAT_fff45106;
undefined4 DAT_fff4510c;
undefined4 DAT_fff45108;
uint REG_EMIOS_MCR;
undefined DAT_000886e0;
uint REG_EMIOS_UC0_CCNTR;
uint REG_EMIOS_UC0_CCR;
byte REG_INTC_PSR0;
uint REG_EMIOS_UC0_CADR;
uint REG_EMIOS_UC0_CBDR;
uint REG_EMIOS_UC6_CSR;
ushort DAT_40001dd2;
undefined2 DAT_40001580;
uint REG_EMIOS_UC20_CSR;
undefined1 DAT_400015a4;
uint REG_EMIOS_UC5_CADR;
uint REG_EMIOS_UC5_CSR;
ushort REG_SIU_PCR179;
undefined1 DAT_400015a3;
uint DAT_400015ac;
uint REG_EMIOS_UC0_CSR;
byte DAT_4000158c;
byte DAT_400013dc;
int DAT_40001588;
byte DAT_40001582;
uint DAT_40001584;
undefined1 DAT_400013c8;
byte DAT_40008fb0;
char DAT_4000158d;
char DAT_4000158e;
undefined *PTR_DAT_400013d8;
ushort REG_SIU_PCR180;
undefined1 DAT_400015a2;
uint DAT_400015a8;
byte DAT_40001598;
uint REG_EMIOS_UC1_CADR;
byte DAT_400013e4;
uint REG_EMIOS_UC1_CBDR;
int DAT_40001594;
byte DAT_4000158f;
uint DAT_40001590;
uint REG_EMIOS_UC1_CSR;
undefined1 DAT_400013c9;
byte DAT_40008fb1;
char DAT_40001599;
char DAT_4000159a;
undefined *PTR_DAT_400013e0;
undefined1 DAT_40000028;
undefined1 discrete_input_state;
undefined DAT_40000029;
undefined DAT_4000002a;
undefined DAT_4000002b;
undefined4 DAT_4000002c;
undefined4 DAT_4000005c;
undefined DAT_40002388;
byte REG_SIU_GPDI0;
ushort DAT_40001dba;
undefined2 DAT_400015bc;
ushort DAT_40001dce;
undefined2 DAT_400015be;
ushort DAT_40001db4;
ushort DAT_400015ba;
ushort DAT_40001db6;
undefined2 DAT_400015c6;
ushort DAT_40001db8;
u16_voltage_5/1023v oil_temp_sensor_voltage;
undefined2 oil_temp_raw;
uint32_t oil_temp_iir_filter_state;
uint8_t CAL_oil_temp_fallback;
undefined1 oil_temp_unknown;
uint8_t CAL_trans_temp_filter_coeff;
uint8_t[32] CAL_sensor_oil_temp;
undefined *DAT_400015e0;
undefined *DAT_400015dc;
undefined *DAT_400015d8;
undefined *DAT_400015d4;
undefined4 DAT_40000068;
undefined *PTR_DAT_4000006c;
undefined REG_ETPU_SDM;
undefined *PTR_DAT_40000070;
undefined REG_ETPU_SCM;
undefined4 DAT_40000074;
undefined4 DAT_40000078;
undefined *PTR_DAT_4000007c;
undefined *PTR_DAT_40000080;
undefined4 DAT_40000084;
undefined DAT_00088740;
undefined DAT_00088850;
undefined DAT_c3fc89fc;
undefined DAT_c3fcc000;
uint REG_ETPU_MCR;
uint REG_ETPU_C0SCR_A;
undefined4 DAT_40002be0;
char DAT_400015f2;
undefined LEA_base;
uint DAT_40002be4;
undefined *DAT_40003450;
uint DAT_40003454;
undefined1 DAT_4000166a;
undefined DAT_000010a8;
ushort DAT_400015f4;
char DAT_400023b5;
char DAT_400023b6;
char DAT_400023b7;
char DAT_400023b8;
char DAT_400023b4;
char DAT_400023c2;
bool LEA_shift_adaptation_history_valid;
byte DAT_400023c3;
int DAT_40002be0;
uint16_t LEA_shift_adaptation_history_crc;
uint8_t[32] LEA_shift_adaptation_history;
undefined4 DAT_4000344c;
char DAT_40009029;
string s_TCU-V0W00_17/06/2019_DL_BJ2_br_0008ac50;
undefined1 shift_adapt_inhibit;
short DAT_400015f0;
byte DAT_40002cc2;
byte DAT_40002cc5;
byte DAT_40002cc8;
byte DAT_40002ccb;
byte DAT_40002cce;
byte DAT_40002cd1;
byte DAT_40002cd4;
byte DAT_40002cd7;
byte DAT_40002cda;
byte DAT_40002cdd;
byte DAT_40002ce0;
byte DAT_40002ce3;
byte DAT_40002ce6;
byte DAT_40002ce9;
byte DAT_40002cf2;
byte DAT_40002cfe;
byte DAT_40002d01;
byte DAT_40002d04;
byte DAT_40002d07;
byte DAT_40002d0a;
byte DAT_40002d0d;
byte DAT_40002d10;
byte DAT_40002d13;
byte DAT_40002d16;
byte DAT_40002d19;
byte DAT_40002d1c;
byte DAT_40002d1f;
byte DAT_40002d22;
byte DAT_40002d25;
byte DAT_40002d28;
byte DAT_40002d2b;
byte DAT_40002d2e;
byte DAT_40002d31;
byte DAT_40002d34;
byte DAT_40002d37;
byte DAT_40002d3a;
byte DAT_40002d3d;
byte DAT_40002d40;
byte DAT_40002d43;
byte DAT_40002d49;
byte DAT_40002d4c;
byte DAT_40002d4f;
byte DAT_40002da0;
byte DAT_40002d52;
byte DAT_40002da3;
byte DAT_40002d55;
byte DAT_40002d58;
byte DAT_40002d5b;
byte DAT_40002d5e;
byte DAT_40002d61;
byte DAT_40002d64;
byte DAT_40002d67;
byte DAT_40002d6a;
byte DAT_40002d6d;
byte DAT_40002d70;
byte DAT_40002d73;
byte DAT_40002d76;
byte DAT_40002d79;
byte DAT_40002da6;
byte DAT_40002da9;
byte DAT_40002d7c;
byte DAT_40002d7f;
byte DAT_40002d82;
byte DAT_40002dac;
byte DAT_40002daf;
byte DAT_40002d85;
byte DAT_40002d88;
byte DAT_40002d8b;
byte DAT_40002d8e;
byte DAT_40002d91;
byte DAT_40002d94;
byte DAT_40002d97;
byte DAT_40002d9a;
byte DAT_40002d9d;
byte DAT_40002db2;
byte DAT_40002db5;
byte DAT_40002db8;
byte DAT_40002dbb;
byte DAT_40002dbe;
byte DAT_40002dc1;
byte DAT_40002dc4;
byte DAT_40002dc7;
byte DAT_40002dca;
byte DAT_40002dcd;
byte DAT_40002dd0;
byte DAT_40002dd3;
byte DAT_40002dd6;
byte DAT_40002dd9;
undefined1 obd_P0717_dtc_state;
undefined1 obd_P0718_dtc_state;
undefined1 obd_P0721_dtc_state;
undefined1 obd_P0722_dtc_state;
undefined1 obd_P0723_dtc_state;
undefined1 obd_P0894_dtc_state;
undefined2 DAT_40002bd4;
undefined2 DAT_40002bd6;
undefined2 DAT_40002bd8;
undefined2 DAT_40002bda;
undefined1 DAT_40002bdc;
undefined1 DAT_40003442;
undefined2 DAT_40003444;
undefined1 slip_learn_status_flags_gear6;
undefined2 DAT_40003446;
undefined2 DAT_40003448;
undefined1 DAT_40002e6e;
undefined2 DAT_40003438;
undefined2 DAT_4000343a;
undefined4 DAT_40002e24;
undefined4 DAT_40002ddc;
undefined4 DAT_40002dec;
undefined4 DAT_40002e0c;
undefined1 DAT_40002e28;
u16_rspeed_rpm[8] u16_rspeed_rpm_ARRAY_40002e84;
undefined1 DAT_40002efc;
undefined2 DAT_40002efe;
undefined2 DAT_40002f24;
undefined2 DAT_40002fec;
undefined2 DAT_400030b4;
undefined1 DAT_4000317c;
undefined1 DAT_400031e0;
undefined1 DAT_40003244;
undefined2 DAT_400032a8;
undefined2 DAT_40003370;
undefined2 DAT_40002c82;
undefined2 DAT_40002c14;
undefined2 DAT_40002c16;
undefined2 DAT_40002be8;
undefined2 DAT_40002bfe;
undefined2 DAT_40002c38;
undefined1 DAT_40002c3c;
undefined1 DAT_40002c3d;
u16_rspeed_1/4rpm u16_rspeed_1/4rpm_40002c3e;
undefined1 DAT_40002c40;
undefined2 DAT_40002c42;
undefined2 DAT_40002c44;
undefined2 DAT_40002c46;
undefined1 DAT_40002c48;
undefined2 DAT_40002c4a;
u16_rspeed_1/4rpm u16_rspeed_1/4rpm_40002c4c;
undefined1 DAT_40002c50;
undefined2 DAT_40002c4e;
undefined1 DAT_40002c51;
undefined1 DAT_40002c52;
undefined1 DAT_40002c53;
undefined2 DAT_40002c54;
undefined2 DAT_40002c56;
undefined1 DAT_40002c58;
undefined1 DAT_40002c59;
undefined2 DAT_40002c5a;
undefined1 DAT_40002c3b;
undefined1 DAT_40002cc2;
undefined1 DAT_40002cc3;
undefined1 DAT_40002cc4;
undefined1 DAT_40002cc5;
undefined1 DAT_40002cc6;
undefined1 DAT_40002cc7;
undefined1 DAT_40002cc8;
undefined1 DAT_40002cc9;
undefined1 DAT_40002cca;
undefined1 DAT_40002ccb;
undefined1 DAT_40002ccc;
undefined1 DAT_40002ccd;
undefined1 DAT_40002cce;
undefined1 DAT_40002ccf;
undefined1 DAT_40002cd0;
undefined1 DAT_40002cd1;
undefined1 DAT_40002cd2;
undefined1 DAT_40002cd3;
undefined1 DAT_40002cd4;
undefined1 DAT_40002cd5;
undefined1 DAT_40002cd6;
undefined1 DAT_40002cd7;
undefined1 DAT_40002cd8;
undefined1 DAT_40002cd9;
undefined1 DAT_40002cda;
undefined1 DAT_40002cdb;
undefined1 DAT_40002cdc;
undefined1 DAT_40002cdd;
undefined1 DAT_40002cde;
undefined1 DAT_40002cdf;
undefined1 DAT_40002ce0;
undefined1 DAT_40002ce1;
undefined1 DAT_40002ce2;
undefined1 DAT_40002ce3;
undefined1 DAT_40002ce4;
undefined1 DAT_40002ce5;
undefined1 DAT_40002ce6;
undefined1 DAT_40002ce7;
undefined1 DAT_40002ce8;
undefined1 DAT_40002ce9;
undefined1 DAT_40002cea;
undefined1 DAT_40002ceb;
undefined1 DAT_40002ced;
undefined1 DAT_40002cee;
undefined1 DAT_40002cf0;
undefined1 DAT_40002cf1;
undefined1 DAT_40002cf2;
undefined1 DAT_40002cf3;
undefined1 DAT_40002cf4;
undefined1 DAT_40002cf6;
undefined1 DAT_40002cf7;
undefined1 DAT_40002cf9;
undefined1 DAT_40002cfa;
undefined1 DAT_40002cfc;
undefined1 DAT_40002cfd;
undefined1 DAT_40002cfe;
undefined1 DAT_40002cff;
undefined1 DAT_40002d00;
undefined1 DAT_40002d01;
undefined1 DAT_40002d02;
undefined1 DAT_40002d03;
undefined1 DAT_40002d04;
undefined1 DAT_40002d05;
undefined1 DAT_40002d06;
undefined1 DAT_40002d07;
undefined1 DAT_40002d08;
undefined1 DAT_40002d09;
undefined1 DAT_40002d0a;
undefined1 DAT_40002d0b;
undefined1 DAT_40002d0c;
undefined1 DAT_40002d0d;
undefined1 DAT_40002d0e;
undefined1 DAT_40002d0f;
undefined1 DAT_40002d10;
undefined1 DAT_40002d11;
undefined1 DAT_40002d12;
undefined1 DAT_40002d13;
undefined1 DAT_40002d14;
undefined1 DAT_40002d15;
undefined1 DAT_40002d16;
undefined1 DAT_40002d17;
undefined1 DAT_40002d18;
undefined1 DAT_40002d19;
undefined1 DAT_40002d1a;
undefined1 DAT_40002d1b;
undefined1 DAT_40002d1c;
undefined1 DAT_40002d1d;
undefined1 DAT_40002d1e;
undefined1 DAT_40002d1f;
undefined1 DAT_40002d20;
undefined1 DAT_40002d21;
undefined1 DAT_40002d22;
undefined1 DAT_40002d23;
undefined1 DAT_40002d24;
undefined1 DAT_40002d25;
undefined1 DAT_40002d26;
undefined1 DAT_40002d27;
undefined1 DAT_40002d28;
undefined1 DAT_40002d29;
undefined1 DAT_40002d2a;
undefined1 DAT_40002d2b;
undefined1 DAT_40002d2c;
undefined1 DAT_40002d2d;
undefined1 DAT_40002d2e;
undefined1 DAT_40002d2f;
undefined1 DAT_40002d30;
undefined1 DAT_40002d31;
undefined1 DAT_40002d32;
undefined1 DAT_40002d33;
undefined1 DAT_40002d34;
undefined1 DAT_40002d35;
undefined1 DAT_40002d36;
undefined1 DAT_40002d37;
undefined1 DAT_40002d38;
undefined1 DAT_40002d39;
undefined1 DAT_40002d3a;
undefined1 DAT_40002d3b;
undefined1 DAT_40002d3c;
undefined1 DAT_40002d3d;
undefined1 DAT_40002d3e;
undefined1 DAT_40002d3f;
undefined1 DAT_40002d40;
undefined1 DAT_40002d41;
undefined1 DAT_40002d42;
undefined1 DAT_40002d43;
undefined1 DAT_40002d44;
undefined1 DAT_40002d45;
undefined1 DAT_40002d47;
undefined1 DAT_40002d48;
undefined1 DAT_40002d49;
undefined1 DAT_40002d4a;
undefined1 DAT_40002d4b;
undefined1 DAT_40002d4c;
undefined1 DAT_40002d4d;
undefined1 DAT_40002d4e;
undefined1 DAT_40002d4f;
undefined1 DAT_40002d50;
undefined1 DAT_40002d51;
undefined1 DAT_40002da0;
undefined1 DAT_40002da1;
undefined1 DAT_40002da2;
undefined1 DAT_40002d52;
undefined1 DAT_40002d53;
undefined1 DAT_40002d54;
undefined1 DAT_40002da3;
undefined1 DAT_40002da4;
undefined1 DAT_40002da5;
undefined1 DAT_40002d55;
undefined1 DAT_40002d56;
undefined1 DAT_40002d57;
undefined1 DAT_40002d58;
undefined1 DAT_40002d59;
undefined1 DAT_40002d5a;
undefined1 DAT_40002d5b;
undefined1 DAT_40002d5c;
undefined1 DAT_40002d5d;
undefined1 DAT_40002d5e;
undefined1 DAT_40002d5f;
undefined1 DAT_40002d60;
undefined1 DAT_40002d61;
undefined1 DAT_40002d62;
undefined1 DAT_40002d63;
undefined1 DAT_40002d64;
undefined1 DAT_40002d65;
undefined1 DAT_40002d66;
undefined1 DAT_40002d67;
undefined1 DAT_40002d68;
undefined1 DAT_40002d69;
undefined1 DAT_40002d6a;
undefined1 DAT_40002d6b;
undefined1 DAT_40002d6c;
undefined1 DAT_40002d6d;
undefined1 DAT_40002d6e;
undefined1 DAT_40002d6f;
undefined1 DAT_40002d70;
undefined1 DAT_40002d71;
undefined1 DAT_40002d72;
undefined1 DAT_40002d73;
undefined1 DAT_40002d74;
undefined1 DAT_40002d75;
undefined1 DAT_40002d76;
undefined1 DAT_40002d77;
undefined1 DAT_40002d78;
undefined1 DAT_40002d79;
undefined1 DAT_40002d7a;
undefined1 DAT_40002d7b;
undefined1 DAT_40002da6;
undefined1 DAT_40002da7;
undefined1 DAT_40002da8;
undefined1 DAT_40002da9;
undefined1 DAT_40002daa;
undefined1 DAT_40002dab;
undefined1 DAT_40002dca;
undefined1 DAT_40002dcb;
undefined1 DAT_40002dcc;
undefined1 DAT_40002dcd;
undefined1 DAT_40002dce;
undefined1 DAT_40002dcf;
undefined1 DAT_40002dd0;
undefined1 DAT_40002dd1;
undefined1 DAT_40002dd2;
undefined1 DAT_40002dd3;
undefined1 DAT_40002dd4;
undefined1 DAT_40002dd5;
undefined1 DAT_40002dd6;
undefined1 DAT_40002dd7;
undefined1 DAT_40002dd8;
undefined1 DAT_40002dd9;
undefined1 DAT_40002dda;
undefined1 DAT_40002ddb;
undefined1 DAT_40002d7c;
undefined1 DAT_40002d7d;
undefined1 DAT_40002d7e;
undefined1 DAT_40002d7f;
undefined1 DAT_40002d80;
undefined1 DAT_40002d81;
undefined1 DAT_40002d82;
undefined1 DAT_40002d83;
undefined1 DAT_40002d84;
undefined1 DAT_40002dac;
undefined1 DAT_40002dad;
undefined1 DAT_40002dae;
undefined1 DAT_40002daf;
undefined1 DAT_40002db0;
undefined1 DAT_40002db1;
undefined1 DAT_40002d85;
undefined1 DAT_40002d86;
undefined1 DAT_40002d87;
undefined1 DAT_40002d88;
undefined1 DAT_40002d89;
undefined1 DAT_40002d8a;
undefined1 DAT_40002d8b;
undefined1 DAT_40002d8c;
undefined1 DAT_40002d8d;
undefined1 DAT_40002d8e;
undefined1 DAT_40002d8f;
undefined1 DAT_40002d90;
undefined1 DAT_40002d91;
undefined1 DAT_40002d92;
undefined1 DAT_40002d93;
undefined1 DAT_40002d94;
undefined1 DAT_40002d95;
undefined1 DAT_40002d96;
undefined1 DAT_40002d97;
undefined1 DAT_40002d98;
undefined1 DAT_40002d99;
undefined1 DAT_40002d9a;
undefined1 DAT_40002d9b;
undefined1 DAT_40002d9c;
undefined1 DAT_40002d9d;
undefined1 DAT_40002d9e;
undefined1 DAT_40002d9f;
undefined1 DAT_40002db2;
undefined1 DAT_40002db3;
undefined1 DAT_40002db4;
undefined1 DAT_40002db5;
undefined1 DAT_40002db6;
undefined1 DAT_40002db7;
undefined1 DAT_40002db8;
undefined1 DAT_40002db9;
undefined1 DAT_40002dba;
undefined1 DAT_40002dbb;
undefined1 DAT_40002dbc;
undefined1 DAT_40002dbd;
undefined1 DAT_40002dbe;
undefined1 DAT_40002dbf;
undefined1 DAT_40002dc0;
undefined1 DAT_40002dc1;
undefined1 DAT_40002dc2;
undefined1 DAT_40002dc3;
undefined1 DAT_40002dc4;
undefined1 DAT_40002dc5;
undefined1 DAT_40002dc6;
undefined1 DAT_40002dc7;
undefined1 DAT_40002dc8;
undefined1 DAT_40002dc9;
undefined1 DAT_40002c5c;
undefined2 DAT_40002c5e;
u16_rspeed_1/4rpm u16_rspeed_1/4rpm_40002c60;
undefined2 DAT_40002c62;
undefined2 DAT_40002c64;
undefined2 DAT_40002c66;
undefined2 DAT_40002c68;
undefined2 DAT_40002c6a;
undefined1 DAT_40002c6c;
undefined1 DAT_40002c6d;
undefined1 DAT_40002c6e;
undefined1 DAT_40002c6f;
undefined4 DAT_40002c70;
undefined2 DAT_40002c74;
undefined2 DAT_40002c76;
undefined2 DAT_40002c78;
undefined2 DAT_40002c7a;
undefined4 DAT_40002c7c;
undefined1 DAT_40002c80;
undefined4 DAT_40002c84;
undefined1 DAT_40002c81;
undefined2 DAT_40002c88;
uint DAT_40001628;
uint DAT_40001624;
uint DAT_40001620;
undefined1 DAT_4000162c;
undefined *DAT_00001cd0;
undefined4 DAT_400015f8;
int DAT_400004c4;
int DAT_4000161c;
int DAT_40001618;
pointer PTR_REG_FLASH_MCR_400004c0;
undefined DAT_400015fc;
undefined DAT_40001608;
undefined DAT_40001610;
undefined UNK_ffff8014;
undefined UNK_ffff8018;
undefined UNK_ffff8024;
undefined UNK_ffff8028;
undefined4 DAT_40001618;
undefined4 DAT_4000161c;
undefined4 DAT_40001614;
undefined *DAT_00001cdc;
undefined DAT_40001600;
undefined UNK_ffff8020;
uint REG_FLASH_LMLR;
uint REG_FLASH_HLR;
uint REG_FLASH_SLMLR;
uint REG_FLASH_LMSR;
uint REG_FLASH_HSR;
undefined1 DAT_00010000;
uint REG_FLASH_MCR;
char DAT_400090c0;
char DAT_40001653;
byte DAT_40001aca;
byte DAT_40001652;
byte DAT_40009155;
enum_t6e_gear ips_gear_cur;
ushort DAT_400015c6;
byte DAT_40008fb2;
char DAT_40002bdc;
char DAT_4000346e;
char DAT_40001ac4;
byte DAT_40001636;
uint DAT_40001840;
uint DAT_40001844;
char DAT_4000163e;
ushort DAT_4000163c;
byte REG_SIU_GPDO203;
char DAT_400013ea;
undefined DAT_400098ce;
uint8_t[8] s__400098d6;
uint8_t[8] s_ffffffff_400098de;
undefined1 DAT_40001630;
bool DAT_40001631;
byte DAT_400023a9;
byte DAT_40001656;
char DAT_40001631;
char DAT_40001633;
byte DAT_400013e9;
byte DAT_400013e8;
ushort DAT_40001dbc;
ushort DAT_40001dc2;
char DAT_400013eb;
char DAT_4000163a;
pointer CRC16_salt;
char DAT_40001c38;
undefined2 DAT_40001712;
byte DAT_40001ac5;
byte DAT_40001ac6;
char DAT_4000904a;
byte REG_SIU_GPDO192;
byte REG_SIU_GPDO194;
char DAT_40001c39;
short DAT_40001438;
short DAT_40002bda;
uint8_t[8] s_(<Px_4000d3f6;
uint8_t[8] s_22222222_4000d3fe;
uint8_t[8] s_(<Px_4000d406;
uint8_t[8] s__4000d40e;
u8_speed_kph vehicle_speed;
u16_rspeed_rpm revlimit_hard_from_ecu;
byte DAT_40001644;
ushort DAT_4000170a;
ushort DAT_40001708;
short DAT_40001646;
short DAT_40001648;
short DAT_40001642;
byte DAT_40009040;
short DAT_40001640;
byte DAT_40009041;
byte DAT_4000164a;
ushort DAT_4000164c;
byte DAT_40009082;
byte DAT_4000164e;
byte DAT_40001637;
undefined1 DAT_40003458;
undefined2 _load_signed;
ushort DAT_4000165c;
byte DAT_4000237c;
char DAT_400023a5;
byte DAT_4000171e;
undefined1 DAT_40001655;
int DAT_40001658;
char DAT_40001638;
uint DAT_4000344c;
undefined2 DAT_40001650;
byte DAT_40009090;
byte DAT_40001639;
byte DAT_4000164f;
byte DAT_400090b3;
byte DAT_400090d7;
uint DAT_40001540;
byte DAT_400090c1;
undefined1 DAT_40002b8e;
uint8_t LEA_shift_profile_adapt;
undefined DAT_400097dc;
u8_factor_1/255[8] CAL_driving_shift_aggressiveness_blend;
ushort DAT_40001666;
ushort DAT_40001664;
short DAT_4000167e;
byte DAT_4000e404;
ushort DAT_40001676;
char DAT_4000166b;
undefined1 DAT_40001671;
undefined1 DAT_40001672;
undefined1 DAT_40001669;
undefined1 DAT_400013f0;
undefined1 DAT_400013f1;
undefined1 DAT_400013f2;
undefined1 DAT_400013f3;
short DAT_40002c4a;
undefined1 DAT_40001670;
byte DAT_40001680;
byte DAT_40001681;
undefined2 DAT_40001688;
undefined2 DAT_4000166c;
byte DAT_40001684;
undefined2 DAT_4000168c;
undefined2 DAT_40001692;
byte DAT_40001682;
undefined2 DAT_4000168a;
undefined2 DAT_40001690;
byte DAT_40001683;
undefined2 DAT_4000168e;
undefined2 DAT_4000166e;
uint DAT_40002c84;
short DAT_40002c88;
ushort DAT_40001686;
string s__400013f4;
string s__400013fc;
string s__40001404;
string s__4000140c;
undefined2 DAT_40002c18;
undefined2 DAT_400054c8;
undefined2 DAT_400055c8;
undefined2 DAT_400056c8;
undefined1 CAL_obd_ii_standards_supported;
u16_rspeed_rpm shift_adaptation_learn_gate;
undefined1 trans_slip_status_flags;
undefined1 paddle_shift_flags;
ushort DAT_4000e25a;
byte DAT_40002c50;
byte DAT_4000e258;
char DAT_40001671;
char DAT_40002c51;
undefined1 DAT_40001660;
short DAT_4000e25c;
byte DAT_400016a0;
uint DAT_4000169c;
ushort DAT_40002c38;
byte DAT_40002c3a;
byte DAT_4000e256;
ushort DAT_40002c4a;
undefined1 DAT_40002c1a;
ushort DAT_40002c5e;
u8_speed_kph DAT_40002c80;
undefined1 DAT_40001569;
u8_factor_1/255 DAT_40002c6f;
undefined4 DAT_40001540;
u8_factor_1/255 tps;
u8_speed_kph DAT_40002c40;
short DAT_400015ba;
short DAT_40002c44;
u8_factor_1/255 DAT_40002c48;
char DAT_40001670;
char DAT_4000167d;
byte DAT_40002c3b;
byte DAT_40002c52;
byte DAT_4000e257;
char DAT_40001660;
byte DAT_4000e259;
char DAT_40001672;
char DAT_4000166a;
undefined1 DAT_40001694;
undefined DAT_00004e20;
undefined2 DAT_40003468;
undefined1 DAT_400016ac;
byte REG_SIU_GPDO206;
undefined1 DAT_4000153b;
ushort REG_SIU_PCR206;
byte REG_SIU_GPDO22;
byte REG_SIU_GPDO209;
ushort REG_SIU_PCR209;
ushort REG_SIU_PCR198;
ushort REG_SIU_PCR22;
ushort DAT_40003468;
undefined UNK_ffff7695;
char DAT_40009049;
uint REG_FLEXCAN_A_MB23_CS;
uint REG_FLEXCAN_A_MB23_ID;
uint REG_FLEXCAN_A_MB23_DATA0;
uint REG_FLEXCAN_C_MB13_CS;
uint REG_FLEXCAN_C_MB13_ID;
uint REG_FLEXCAN_C_MB13_DATA0;
uint REG_FLEXCAN_C_MB14_ID;
uint REG_FLEXCAN_C_MB14_DATA0;
uint REG_FLEXCAN_A_MB24_CS;
uint REG_FLEXCAN_A_MB24_ID;
uint REG_FLEXCAN_A_MB24_DATA0;
uint REG_FLEXCAN_C_MB14_CS;
undefined1 DAT_40003478;
undefined1 DAT_4000348c;
undefined1 DAT_4000348d;
byte DAT_4000348c;
byte DAT_4000348d;
undefined DAT_4000348e;
undefined DAT_4000348f;
undefined DAT_40003490;
undefined DAT_40003491;
undefined DAT_40003492;
undefined DAT_40003493;
undefined DAT_40003494;
undefined DAT_40003495;
undefined4 DAT_40003484;
undefined DAT_40003854;
undefined2 DAT_40003af4;
undefined2 DAT_40003af6;
undefined1 DAT_40003af8;
undefined1 DAT_40003af9;
undefined1 DAT_40003afa;
ushort DAT_400052e6;
byte *DAT_40003488;
undefined DAT_4000347c;
undefined1 DAT_40003481;
undefined1 DAT_40003479;
char DAT_4000347a;
undefined1 DAT_4000347b;
undefined4 DAT_4000347c;
undefined1 *DAT_40003488;
undefined4 *DAT_40003850;
undefined2 DAT_400052e6;
undefined4 DAT_40001578;
undefined1 DAT_40001420;
byte[8] obd_ii_request;
char DAT_4000348c;
undefined1 DAT_40001418;
int DAT_400016b8;
undefined2 obd_ii_response_length;
undefined1 isotp_block_counter;
uint REG_FLEXCAN_A_MB22_CS;
uint REG_FLEXCAN_A_MB22_ID;
uint REG_FLEXCAN_A_MB22_DATA0;
uint REG_FLEXCAN_A_MB22_DATA0+1;
undefined1 isotp_stmin;
bool isotp_fc_received;
bool obd_ii_tx_messages_pending;
byte[8] obd_ii_response;
undefined1 isotp_stmin_counter;
undefined1 isotp_flow_status;
undefined1 isotp_block_size;
uint REG_FLEXCAN_A_MCR;
uint REG_FLEXCAN_A_CR;
uint REG_FLEXCAN_A_RXGMASK;
uint REG_FLEXCAN_A_RX14MASK;
uint REG_FLEXCAN_A_RX15MASK;
uint REG_FLEXCAN_A_IMRH;
byte REG_INTC_PSR155;
uint REG_FLEXCAN_A_IMRL;
byte REG_INTC_PSR156;
uint REG_FLEXCAN_A_IFRH;
byte REG_INTC_PSR157;
uint REG_FLEXCAN_A_IFRL;
byte REG_INTC_PSR158;
uint REG_FLEXCAN_A_MB0_CS;
byte REG_INTC_PSR159;
uint REG_FLEXCAN_A_MB0_ID;
byte REG_INTC_PSR160;
byte REG_INTC_PSR161;
byte REG_INTC_PSR162;
uint REG_FLEXCAN_A_MB1_CS;
byte REG_INTC_PSR163;
uint REG_FLEXCAN_A_MB1_ID;
byte REG_INTC_PSR164;
byte REG_INTC_PSR165;
byte REG_INTC_PSR166;
uint REG_FLEXCAN_A_MB2_CS;
byte REG_INTC_PSR167;
uint REG_FLEXCAN_A_MB2_ID;
byte REG_INTC_PSR168;
byte REG_INTC_PSR169;
byte REG_INTC_PSR170;
uint REG_FLEXCAN_A_MB3_CS;
byte REG_INTC_PSR171;
uint REG_FLEXCAN_A_MB3_ID;
uint REG_FLEXCAN_A_MB4_CS;
uint REG_FLEXCAN_A_MB4_ID;
uint REG_FLEXCAN_A_MB5_CS;
uint REG_FLEXCAN_A_MB5_ID;
ushort REG_SIU_PCR83;
uint REG_FLEXCAN_A_MB6_CS;
ushort REG_SIU_PCR84;
uint REG_FLEXCAN_A_MB6_ID;
uint REG_FLEXCAN_A_MB8_CS;
uint REG_FLEXCAN_A_MB8_ID;
uint REG_FLEXCAN_A_MB9_CS;
uint REG_FLEXCAN_A_MB9_ID;
uint REG_FLEXCAN_A_MB10_CS;
uint REG_FLEXCAN_A_MB10_ID;
uint REG_FLEXCAN_A_MB11_CS;
uint REG_FLEXCAN_A_MB11_ID;
uint REG_FLEXCAN_A_MB12_CS;
uint REG_FLEXCAN_A_MB12_ID;
uint REG_FLEXCAN_A_MB13_CS;
uint REG_FLEXCAN_A_MB13_ID;
uint REG_FLEXCAN_A_MB14_CS;
uint REG_FLEXCAN_A_MB14_ID;
uint REG_FLEXCAN_A_MB15_CS;
uint REG_FLEXCAN_A_MB15_ID;
uint REG_FLEXCAN_A_MB16_CS;
uint REG_FLEXCAN_A_MB16_ID;
uint REG_FLEXCAN_A_MB17_CS;
uint REG_FLEXCAN_A_MB18_CS;
uint REG_FLEXCAN_A_MB18_ID;
uint REG_FLEXCAN_A_MB19_CS;
uint REG_FLEXCAN_A_MB19_ID;
uint REG_FLEXCAN_A_MB20_CS;
uint REG_FLEXCAN_A_MB20_ID;
uint REG_FLEXCAN_A_MB21_CS;
uint REG_FLEXCAN_A_MB21_ID;
undefined2 DAT_400016dc;
uint REG_FLEXCAN_A_TIMER;
byte DAT_40001454;
undefined2 DAT_40001718;
byte DAT_40001716;
byte DAT_40001715;
byte[64] COD_unknown;
uint REG_FLEXCAN_A_MB0_DATA0;
undefined1 CAL_revlimit_min;
uint REG_FLEXCAN_A_MB1_DATA0;
ushort DAT_40001450;
undefined1 DAT_4000191a;
undefined1 engine_flag_1;
undefined1 ips_calibration_flags;
undefined1 cruise_target_kph;
undefined1 cruise_status_flags;
bool auto_mode_active;
ushort DAT_4000172a;
uint REG_FLEXCAN_A_MB2_DATA0;
u16_torque_1/4+400nm torque_alphaN_raw;
byte DAT_40001455;
undefined1 DAT_40001428;
byte DAT_400016de;
byte DAT_400016df;
uint REG_FLEXCAN_A_MB3_DATA0+1;
byte DAT_400016e0;
undefined1 DAT_400016e1;
uint REG_FLEXCAN_A_MB3_DATA0;
byte DAT_40001453;
byte DAT_40001714;
short DAT_40001712;
short DAT_40001710;
short DAT_4000170e;
uint REG_FLEXCAN_A_MB4_DATA0;
uint REG_FLEXCAN_A_MB5_DATA0;
undefined1 DAT_40001702;
u8_factor_1/255 tps_commanded;
ushort DAT_4000174a;
ushort DAT_40001748;
ushort DAT_40001746;
ushort DAT_40001744;
undefined2 DAT_40001732;
undefined2 DAT_40001730;
undefined2 DAT_4000172e;
undefined2 DAT_4000172c;
undefined2 DAT_40001742;
undefined2 DAT_40001740;
undefined2 DAT_4000173e;
undefined2 DAT_4000173c;
undefined2 DAT_4000173a;
undefined2 DAT_40001738;
undefined2 DAT_40001736;
undefined2 DAT_40001734;
uint REG_FLEXCAN_A_MB6_DATA1+1;
uint REG_FLEXCAN_A_MB6_DATA1+2;
uint REG_FLEXCAN_A_MB6_DATA1+3;
uint REG_FLEXCAN_A_MB6_DATA0+1;
uint REG_FLEXCAN_A_MB6_DATA0+2;
uint REG_FLEXCAN_A_MB6_DATA0+3;
uint REG_FLEXCAN_A_MB6_DATA0;
uint REG_FLEXCAN_A_MB6_DATA1;
uint REG_FLEXCAN_A_MB9_DATA0;
uint REG_FLEXCAN_A_MB10_DATA0;
uint REG_FLEXCAN_A_MB11_DATA0;
undefined1 DAT_400016f0;
undefined1 DAT_400016f1;
undefined1 DAT_400016f2;
undefined1 DAT_400016f3;
undefined1 DAT_400016f4;
undefined1 DAT_400016f5;
undefined1 DAT_400016f6;
undefined1 DAT_400016f7;
uint REG_FLEXCAN_A_MB12_DATA0;
uint REG_FLEXCAN_A_MB12_DATA1;
uint REG_FLEXCAN_A_MB12_DATA1+1;
uint REG_FLEXCAN_A_MB12_DATA1+2;
uint REG_FLEXCAN_A_MB12_DATA1+3;
uint REG_FLEXCAN_A_MB12_DATA0+1;
uint REG_FLEXCAN_A_MB12_DATA0+2;
uint REG_FLEXCAN_A_MB12_DATA0+3;
undefined1 DAT_400016ec;
byte DAT_40001452;
ushort DAT_4000142a;
short DAT_40001430;
ushort DAT_4000142c;
short DAT_40001432;
ushort DAT_4000142e;
short DAT_40001434;
undefined1 DAT_40001723;
byte DAT_40001720;
short DAT_4000171c;
undefined1 DAT_40001722;
uint REG_FLEXCAN_A_MB13_DATA0;
undefined2 DAT_400016e4;
undefined2 DAT_400016e6;
undefined2 DAT_400016e2;
byte DAT_40001978;
undefined2 DAT_400016e8;
undefined2 DAT_400016ea;
undefined1 DAT_40001721;
byte DAT_4000171f;
uint REG_FLEXCAN_A_MB14_DATA0;
uint *DAT_400016fc;
uint *DAT_400016d0;
uint *DAT_400016f8;
ushort DAT_400016d8;
ushort DAT_400016da;
uint *DAT_400016d4;
uint REG_FLEXCAN_A_MB15_DATA0;
uint REG_FLEXCAN_A_MB15_DATA1;
uint REG_FLEXCAN_A_MB16_DATA0;
undefined1 *DAT_400016d0;
undefined1 DAT_400016c0;
uint REG_FLEXCAN_A_MB18_DATA0;
uint REG_FLEXCAN_A_MB18_DATA0+1;
uint REG_FLEXCAN_A_MB18_DATA0+2;
uint REG_FLEXCAN_A_ESR;
uint REG_FLEXCAN_A_MB21_DATA0;
uint REG_FLEXCAN_A_MB21_DATA1+1;
uint REG_FLEXCAN_A_MB21_DATA1;
uint REG_FLEXCAN_A_MB21_DATA1+2;
uint REG_FLEXCAN_A_MB21_DATA1+3;
uint REG_FLEXCAN_A_MB21_DATA0+1;
uint REG_FLEXCAN_A_MB21_DATA0+2;
uint REG_FLEXCAN_A_MB21_DATA0+3;
uint REG_FLEXCAN_A_MB20_DATA1+1;
uint REG_FLEXCAN_A_MB20_DATA1+2;
uint REG_FLEXCAN_A_MB20_DATA1+3;
uint REG_FLEXCAN_A_MB20_DATA0+1;
uint REG_FLEXCAN_A_MB20_DATA0+2;
uint REG_FLEXCAN_A_MB20_DATA0+3;
uint REG_FLEXCAN_A_MB20_DATA0;
uint REG_FLEXCAN_A_MB20_DATA1;
uint REG_FLEXCAN_A_MB11_DATA1+1;
uint REG_FLEXCAN_A_MB11_DATA1+2;
uint REG_FLEXCAN_A_MB11_DATA1+3;
uint REG_FLEXCAN_A_MB11_DATA0+1;
uint REG_FLEXCAN_A_MB11_DATA0+2;
uint REG_FLEXCAN_A_MB11_DATA0+3;
uint REG_FLEXCAN_A_MB11_DATA1;
byte DAT_40001428;
undefined1 DAT_400016de;
uint REG_FLEXCAN_C_MB7_CS;
uint REG_FLEXCAN_C_MB8_CS;
uint REG_FLEXCAN_C_MB9_CS;
uint REG_FLEXCAN_C_MB10_CS;
uint REG_FLEXCAN_C_MB11_CS;
uint REG_FLEXCAN_C_MB12_CS;
uint REG_FLEXCAN_C_MB12_ID;
uint REG_FLEXCAN_C_MCR;
uint REG_FLEXCAN_C_CR;
uint REG_FLEXCAN_C_RXGMASK;
uint REG_FLEXCAN_C_RX14MASK;
uint REG_FLEXCAN_C_RX15MASK;
uint REG_FLEXCAN_C_IMRH;
uint REG_FLEXCAN_C_MB15_CS;
uint REG_FLEXCAN_C_IMRL;
uint REG_FLEXCAN_C_IFRH;
uint REG_FLEXCAN_C_IFRL;
uint REG_FLEXCAN_C_MB0_CS;
uint REG_FLEXCAN_C_MB1_CS;
uint REG_FLEXCAN_C_MB2_CS;
uint REG_FLEXCAN_C_MB3_CS;
ushort REG_SIU_PCR87;
uint REG_FLEXCAN_C_MB4_CS;
ushort REG_SIU_PCR88;
byte REG_INTC_PSR188;
byte REG_INTC_PSR189;
byte REG_INTC_PSR190;
uint REG_FLEXCAN_C_MB5_CS;
uint REG_FLEXCAN_C_MB6_CS;
undefined2 DAT_40001750;
undefined1 DAT_40001758;
undefined1 DAT_40001759;
undefined1 DAT_4000175a;
undefined1 DAT_4000175b;
undefined1 DAT_4000175c;
undefined1 DAT_4000175d;
undefined1 DAT_4000175e;
undefined1 DAT_4000175f;
uint REG_FLEXCAN_C_MB12_DATA1+1;
uint REG_FLEXCAN_C_MB12_DATA1+2;
uint REG_FLEXCAN_C_MB12_DATA1+3;
uint REG_FLEXCAN_C_MB12_DATA0+1;
uint REG_FLEXCAN_C_MB12_DATA0+2;
uint REG_FLEXCAN_C_MB12_DATA0+3;
uint REG_FLEXCAN_C_MB12_DATA0;
uint REG_FLEXCAN_C_MB12_DATA1;
uint REG_FLEXCAN_C_TIMER;
uint REG_FLEXCAN_C_ESR;
byte DAT_4000176e;
ushort REG_ESCI_A_CR2;
uint REG_ESCI_A_SR;
uint REG_ESCI_A_LCR;
uint REG_ESCI_A_LPR;
ushort REG_SIU_PCR89;
ushort REG_SIU_PCR90;
byte REG_INTC_PSR146;
uint REG_ESCI_A_CR1;
char DAT_4000176e;
byte DAT_4000176f;
byte REG_INTC_PSR149;
undefined DAT_40005420;
byte DAT_40001770;
ushort REG_ESCI_A_DR+1;
byte DAT_4000176c;
undefined1 DAT_4000176d;
undefined1 DAT_40005400;
byte DAT_4000176d;
byte DAT_4000176a;
undefined1 DAT_4000176e;
undefined1 DAT_4000176f;
undefined1 DAT_40001770;
uint DAT_400015e8;
byte DAT_40001769;
byte DAT_400053e9;
undefined DAT_400053e8;
byte DAT_400053ea;
char DAT_4000176b;
undefined1 DAT_400016ad;
undefined1 DAT_400016ae;
char DAT_400053ea;
undefined1 DAT_400053eb;
undefined1 DAT_400053ec;
undefined1 DAT_4000346e;
undefined1 DAT_40003472;
undefined1 DAT_400053ed;
undefined1 DAT_40003473;
undefined1 DAT_400053ee;
undefined1 DAT_40003474;
undefined1 DAT_400053ef;
undefined1 DAT_40003475;
undefined1 DAT_400053f0;
undefined1 DAT_40003476;
undefined1 DAT_400053f1;
undefined2 DAT_4000346a;
undefined1 DAT_400053f2;
undefined1 DAT_4000346c;
undefined1 DAT_4000346d;
undefined1 DAT_400053f3;
undefined1 DAT_4000346f;
undefined1 DAT_400053f4;
undefined1 DAT_40003470;
undefined1 DAT_400053f5;
undefined1 DAT_400053f6;
byte DAT_40003471;
char DAT_40001768;
char DAT_40001bfc;
char DAT_4000346f;
char DAT_400016ac;
undefined DAT_000015cd;
undefined DAT_000038d4;
undefined DAT_00004013;
undefined DAT_00004335;
undefined DAT_00004ae5;
undefined DAT_0000728f;
undefined DAT_40005440;
undefined DAT_40005464;
ushort REG_SIU_PCR202;
undefined2 DAT_40008ff2;
ushort REG_SIU_PCR189;
ushort REG_SIU_PCR85;
ushort REG_SIU_PCR86;
ushort REG_SIU_PCR199;
ushort REG_SIU_PCR94;
undefined1 DAT_400017ca;
byte REG_SIU_GPDO189;
uint REG_EMIOS_UC20_CADR;
byte REG_SIU_GPDO202;
undefined1 DAT_4000177b;
undefined1 DAT_4000177c;
undefined1 DAT_4000177d;
undefined1 DAT_40001778;
undefined1 DAT_40001779;
undefined1 DAT_4000177a;
undefined1 DAT_400017ad;
undefined1 DAT_400017ac;
undefined1 DAT_400017ab;
uint REG_EMIOS_UC20_CBDR;
uint REG_EMIOS_UC20_CCNTR;
uint REG_EMIOS_UC20_CCR;
int DAT_400015ec;
short DAT_4000177e;
short DAT_40008ff2;
ushort DAT_40001780;
ushort DAT_40008ff8;
ushort DAT_40008ffa;
short DAT_4000178e;
short DAT_4000178c;
short DAT_4000178a;
short DAT_40001788;
uint DAT_40001790;
ushort DAT_40009000;
ushort DAT_40008ffc;
ushort DAT_40008ffe;
ushort DAT_40008ff2;
short DAT_4000143c;
ushort DAT_400017cc;
short DAT_400017c8;
uint DAT_400017c4;
int DAT_400017c0;
int DAT_400017bc;
uint DAT_400017b8;
undefined4 DAT_400017b4;
int DAT_400017b0;
short DAT_400017d2;
short DAT_40001794;
short DAT_40009006;
ushort DAT_40001796;
short DAT_400017d0;
ushort DAT_400017ce;
uint8_t[8] s__40009b22;
uint8_t[8] s_!%'_40009b2a;
uint8_t[8] s__40009b32;
uint8_t[8] s_!%'_40009b3a;
ushort DAT_400017a6;
ushort DAT_400017a8;
byte REG_SIU_GPDO86;
short DAT_4000179e;
undefined1 DAT_400017af;
char DAT_40001778;
char DAT_40001779;
char DAT_4000177a;
ushort DAT_4000179c;
byte REG_SIU_GPDO193;
ushort DAT_40001438;
short DAT_4000143e;
undefined1 DAT_400017a4;
byte DAT_400017a2;
byte DAT_400017a3;
ushort DAT_400017d2;
ushort DAT_400017d0;
byte DAT_40009005;
byte DAT_4000143a;
char DAT_40001bfe;
char DAT_40001c56;
short DAT_400017a0;
char DAT_40008ff6;
byte REG_SIU_GPDI85;
char DAT_400017ae;
byte DAT_40009013;
short DAT_40001798;
byte DAT_40009004;
short DAT_4000179a;
byte DAT_40009012;
undefined1 DAT_400017aa;
uint DAT_40001938;
byte REG_SIU_GPDI94;
byte DAT_40009009;
byte DAT_4000177b;
byte DAT_4000177d;
byte DAT_4000177c;
undefined1 DAT_40001866;
byte DAT_400017e8;
undefined2 DAT_40009050;
undefined2 DAT_40001c6e;
undefined2 DAT_40009052;
undefined2 DAT_40001c6c;
undefined2 DAT_40009054;
undefined2 DAT_40001c6a;
undefined2 DAT_40009056;
undefined2 DAT_40001c68;
undefined2 DAT_40009058;
undefined2 DAT_40001c66;
undefined2 DAT_4000905a;
undefined2 DAT_40001c64;
undefined2 DAT_4000905c;
undefined2 DAT_40001c62;
undefined2 DAT_4000905e;
undefined2 DAT_40001c60;
undefined2 DAT_40009060;
undefined2 DAT_40001c5e;
undefined2 DAT_40009062;
undefined2 DAT_40001c5c;
undefined2 DAT_40009064;
undefined2 DAT_40001c5a;
undefined2 DAT_40009066;
undefined2 DAT_40001c58;
undefined1 DAT_00001cf0;
undefined1 DAT_00001cf1;
undefined1 DAT_00001cf2;
undefined1 DAT_00001cf3;
undefined1 DAT_00001cf4;
undefined1 DAT_00001cf5;
undefined1 DAT_00001cf6;
undefined1 DAT_00001cf7;
char DAT_400017d8;
undefined DAT_400017e0;
undefined1 DAT_400017e9;
undefined1 DAT_400017f0;
undefined1 DAT_400017f1;
undefined1 DAT_400017f2;
undefined1 DAT_400017f3;
undefined1 DAT_400017f4;
undefined1 DAT_400017f5;
undefined1 DAT_400017f6;
undefined1 DAT_400017f7;
undefined1 DAT_400017f8;
undefined1 DAT_400017f9;
undefined1 DAT_400017fa;
undefined1 DAT_400017fb;
undefined1 DAT_400017fc;
undefined1 DAT_400017fd;
undefined1 DAT_400017fe;
undefined1 DAT_400017ff;
undefined1 DAT_40001800;
undefined1 DAT_40001801;
undefined1 DAT_40001802;
undefined1 DAT_40001803;
undefined1 DAT_40001804;
undefined1 DAT_40001805;
undefined1 DAT_40001806;
undefined1 DAT_40001807;
undefined1 DAT_40001808;
undefined1 DAT_40001809;
undefined1 DAT_4000180a;
undefined1 DAT_4000180b;
undefined1 DAT_4000180c;
undefined1 DAT_4000180d;
undefined1 DAT_4000180e;
undefined1 DAT_4000180f;
undefined1 DAT_40001810;
undefined1 DAT_40001811;
undefined1 DAT_40001812;
undefined1 DAT_40001813;
undefined1 DAT_40001814;
undefined1 DAT_40001815;
undefined1 DAT_40001816;
undefined1 DAT_40001817;
undefined1 DAT_40001818;
undefined1 DAT_40001819;
undefined1 DAT_4000181a;
undefined1 DAT_4000181b;
byte DAT_400017f0;
byte DAT_400017f1;
byte DAT_400017f2;
byte DAT_400017f3;
undefined DAT_00000800;
byte DAT_00000812;
byte DAT_00000813;
byte DAT_00000816;
byte DAT_00000817;
byte DAT_00000808;
byte DAT_00000809;
byte DAT_0000080a;
byte DAT_0000080b;
byte DAT_0000081b;
byte DAT_0000081c;
byte DAT_0000081d;
byte DAT_0000081e;
byte DAT_400017f4;
byte DAT_400017f5;
byte DAT_400017f6;
byte DAT_400017f7;
undefined4 DAT_400013b8;
undefined2 DAT_40001510;
undefined2 DAT_40001706;
undefined2 DAT_40001704;
undefined2 DAT_4000170a;
byte DAT_400017f8;
byte DAT_400017f9;
byte DAT_400017fa;
byte DAT_400017fb;
undefined2 DAT_40001708;
byte DAT_400017fc;
byte DAT_400017fd;
byte DAT_400017fe;
byte DAT_400017ff;
char DAT_400023a1;
char DAT_400023a2;
uint DAT_40002374;
uint DAT_40002358;
byte DAT_40001800;
byte DAT_40001801;
byte DAT_40001802;
byte DAT_40001803;
ushort DAT_40001dc0;
ushort DAT_40001dbe;
int DAT_40001a40;
byte DAT_400018bf;
byte DAT_40001ad2;
byte DAT_40001ad3;
byte DAT_4000148e;
byte DAT_4000148f;
byte DAT_40001804;
byte DAT_40001805;
byte DAT_40001806;
byte DAT_40001807;
byte DAT_400090cd;
byte DAT_400090cf;
undefined u16_rspeed_rpm_ARRAY_400090d0;
byte DAT_40001808;
byte DAT_40001809;
byte DAT_4000180a;
byte DAT_4000180b;
byte DAT_4000180c;
byte DAT_4000180d;
byte DAT_4000180e;
byte DAT_4000180f;
byte DAT_40001810;
byte DAT_40001811;
byte DAT_40001812;
byte DAT_40001813;
undefined4 DAT_40002de0;
undefined4 DAT_40002de4;
undefined4 DAT_40002de8;
undefined4 DAT_40002df0;
undefined4 DAT_40002df4;
undefined4 DAT_40002df8;
undefined4 DAT_40002dfc;
undefined4 DAT_40002e00;
undefined4 DAT_40002e04;
undefined4 DAT_40002e08;
undefined4 DAT_40002e10;
undefined4 DAT_40002e14;
undefined4 DAT_40002e18;
undefined4 DAT_40002e1c;
undefined4 DAT_40002e20;
byte DAT_40002e28;
byte DAT_40002e29;
byte DAT_40002e2a;
byte DAT_40002e2b;
undefined u16_rspeed_rpm_ARRAY_40002e84;
undefined2 DAT_40002e9c;
undefined2 DAT_40002ea8;
undefined2 DAT_40002eb4;
undefined2 DAT_40002ec0;
undefined2 DAT_40002ecc;
undefined2 DAT_40002ed8;
byte DAT_40001814;
byte DAT_40001815;
byte DAT_40001816;
byte DAT_40001817;
undefined2 DAT_40002ee4;
undefined2 DAT_40002ef0;
undefined2 DAT_40002e9e;
undefined2 DAT_40002eaa;
undefined2 DAT_40002eb6;
undefined2 DAT_40002ec2;
undefined2 DAT_40002ece;
undefined2 DAT_40002eda;
undefined2 DAT_40002ee6;
undefined2 DAT_40002ef2;
undefined DAT_40002e98;
byte DAT_40002ea4;
byte DAT_40002eb0;
byte DAT_40002ebc;
byte DAT_40002ec8;
byte DAT_40002ed4;
byte DAT_40002ee0;
byte DAT_40002eec;
byte DAT_40002ef8;
undefined4 DAT_40002e94;
undefined4 DAT_40002ea0;
undefined4 DAT_40002eac;
undefined4 DAT_40002eb8;
undefined4 DAT_40002ec4;
undefined4 DAT_40002ed0;
undefined4 DAT_40002edc;
undefined4 DAT_40002ee8;
byte DAT_40001818;
byte DAT_40001819;
byte DAT_4000181a;
byte DAT_4000181b;
undefined4 DAT_40002ef4;
byte DAT_40002efc;
undefined DAT_40002f00;
byte DAT_40002f04;
byte DAT_40002f08;
byte DAT_40002f0c;
byte DAT_40002f10;
byte DAT_40002f14;
byte DAT_40002f18;
byte DAT_40002f1c;
byte DAT_40002f20;
undefined2 DAT_40002f02;
undefined2 DAT_40002f06;
undefined2 DAT_40002f0a;
undefined2 DAT_40002f0e;
undefined2 DAT_40002f12;
undefined2 DAT_40002f16;
undefined2 DAT_40002f1a;
undefined2 DAT_40002f1e;
undefined2 DAT_40002f22;
uint16_t LEA_shift_adaptation;
undefined1 shift_adapt_phase_unknown2;
undefined1 input_shaft_load;
undefined1 selector_position_learned_status;
u16_torque_nm engine_torque;
char[64] CAL_version_string;
undefined2 solenoid_SL_dutycycle;
undefined2 solenoid_SL1_dutycycle;
undefined2 solenoid_SL2_dutycycle;
undefined2 solenoid_SL3_dutycycle;
undefined2 solenoid_SL4_dutycycle;
undefined2 solenoid_SLT_dutycycle;
undefined2 solenoid_SLU_dutycycle;
undefined2 solenoid_SL_demand;
undefined2 solenoid_SL1_demand;
undefined2 solenoid_SL2_demand;
undefined2 solenoid_SL3_demand;
undefined2 solenoid_SL4_demand;
undefined2 solenoid_SLT_demand;
undefined2 solenoid_SLU_demand;
undefined1 shift_position_request_bits;
undefined1 DAT_40001820;
undefined1 DAT_40001821;
undefined1 DAT_40001822;
undefined1 DAT_40001823;
undefined1 DAT_40001824;
undefined1 DAT_40001825;
undefined1 DAT_40001826;
undefined1 DAT_40001827;
undefined1 DAT_40001828;
undefined1 DAT_40001829;
undefined1 DAT_4000182a;
undefined1 DAT_4000182b;
byte DAT_40001820;
byte DAT_40001821;
byte DAT_40001822;
byte DAT_40001823;
byte DAT_40001878;
byte DAT_40001824;
byte DAT_40001825;
byte DAT_40001826;
byte DAT_40001827;
byte DAT_40001828;
byte DAT_40001829;
byte DAT_4000182a;
byte DAT_4000182b;
undefined1 DAT_40001830;
undefined1 DAT_40001831;
undefined1 DAT_40001832;
undefined1 DAT_40001833;
undefined1 DAT_40001834;
undefined1 DAT_40001835;
undefined1 DAT_40001836;
undefined1 DAT_40001837;
undefined1 DAT_40001838;
undefined1 DAT_40001839;
undefined1 DAT_4000183a;
undefined1 DAT_4000183b;
undefined1 DAT_4000184d;
undefined1 DAT_4000184e;
undefined1 DAT_4000184f;
undefined1 DAT_40001850;
undefined1 DAT_40001851;
undefined1 DAT_40001852;
undefined1 DAT_40001853;
undefined1 DAT_40001854;
undefined1 DAT_40001855;
undefined1 DAT_40001856;
undefined1 DAT_40001857;
undefined1 DAT_40001858;
undefined1 DAT_40001859;
undefined1 DAT_4000185a;
undefined1 DAT_4000185b;
undefined1 DAT_4000185c;
undefined1 DAT_4000185d;
undefined1 DAT_4000185e;
undefined1 DAT_4000185f;
undefined1 DAT_40001860;
byte DAT_4000184d;
byte DAT_4000184e;
byte DAT_4000184f;
byte DAT_40001850;
byte DAT_40001851;
byte DAT_40001852;
byte DAT_40001853;
byte DAT_40001854;
byte DAT_40001855;
byte DAT_40001856;
byte DAT_40001857;
byte DAT_40001858;
undefined2 DAT_4000e3de;
undefined2 DAT_40001862;
byte DAT_40001859;
byte DAT_4000185a;
byte DAT_4000185b;
byte DAT_4000185c;
undefined1 DAT_4000184c;
char DAT_40001bfd;
byte DAT_4000e3e0;
short DAT_40001874;
short DAT_40001872;
short DAT_4000186e;
short DAT_4000186c;
short DAT_4000186a;
short DAT_40001868;
char DAT_40001440;
byte DAT_4000185d;
byte DAT_4000185e;
byte DAT_4000185f;
byte DAT_40001860;
undefined2 obd_slu_test_demand;
char DAT_40001864;
undefined1 DAT_40001865;
undefined1 DAT_40001861;
undefined1 DAT_40001638;
bool LEA_shift_adaptation_reset;
char DAT_40001866;
char DAT_40001861;
short DAT_40001862;
undefined4 DAT_40001848;
byte DAT_40001879;
undefined4 DAT_40001678;
undefined4 DAT_40001938;
undefined1 DAT_40002c3a;
undefined2 DAT_40001666;
undefined1 DAT_40001898;
undefined1 DAT_400018b0;
undefined1 DAT_40001879;
char DAT_4000184c;
undefined1 DAT_40001880;
undefined1 DAT_40001881;
undefined1 DAT_40001882;
undefined1 DAT_40001883;
undefined1 DAT_40001884;
undefined1 DAT_40001885;
undefined1 DAT_40001886;
undefined1 DAT_40001887;
undefined1 DAT_40001888;
undefined1 DAT_40001889;
undefined1 DAT_4000188a;
undefined1 DAT_4000188b;
undefined1 DAT_4000188c;
undefined1 DAT_4000188d;
undefined1 DAT_4000188e;
undefined1 DAT_4000188f;
undefined1 DAT_40001890;
undefined1 DAT_40001891;
undefined1 DAT_40001892;
undefined1 DAT_40001893;
undefined1 DAT_40001894;
undefined1 DAT_40001895;
undefined1 DAT_40001896;
undefined1 DAT_40001897;
byte DAT_40001898;
undefined1 DAT_400018a0;
undefined1 DAT_400018a1;
undefined1 DAT_400018a2;
undefined1 DAT_400018a3;
undefined1 DAT_400018aa;
undefined1 DAT_400018ab;
undefined1 DAT_400018ac;
undefined1 DAT_400018ad;
byte DAT_400018aa;
byte DAT_400018ab;
byte DAT_400018ac;
byte DAT_400018ad;
byte DAT_400018b0;
byte DAT_4000e3fc;
byte DAT_4000e3fd;
byte DAT_400018dc;
char DAT_4000e403;
char DAT_400018d9;
byte DAT_400018c0;
short DAT_4000e400;
short DAT_4000e3fe;
byte REG_SIU_GPDI204;
byte DAT_4000e3f7;
char DAT_4000e3f9;
char DAT_400018da;
byte DAT_4000e3f8;
char DAT_400018db;
short DAT_4000e3fa;
char DAT_4000e422;
byte DAT_400018b8;
byte DAT_400018b9;
byte DAT_400018ba;
byte DAT_400018bb;
byte DAT_400018bc;
byte DAT_400018bd;
byte DAT_400018be;
undefined1 DAT_4000e268;
ushort DAT_4000e464;
byte DAT_4000e443;
short DAT_4000e444;
byte DAT_400018c3;
byte DAT_400018cc;
byte DAT_4000e44a;
byte DAT_400018cb;
byte DAT_4000e33a;
undefined1 DAT_4000e269;
byte DAT_400018d7;
ushort DAT_4000e454;
ushort DAT_4000e466;
char DAT_4000148d;
byte DAT_4000e451;
byte DAT_4000e44c;
byte DAT_400018d1;
byte DAT_400018f8;
uint8_t DAT_400018d2;
byte DAT_400018f9;
byte DAT_4000e44d;
byte DAT_400018d0;
undefined1 DAT_400018d4;
undefined1 DAT_400018d5;
undefined1 DAT_400018d3;
byte DAT_400018d6;
byte DAT_4000e452;
byte DAT_4000e33b;
byte DAT_400018c1;
undefined1 DAT_4000e26a;
ushort DAT_4000e456;
ushort DAT_4000e458;
byte DAT_4000e45a;
ushort DAT_4000239e;
ushort DAT_4000e45c;
byte DAT_400018d8;
short DAT_40001676;
byte DAT_4000e33c;
undefined1 DAT_4000e282;
byte DAT_400018c4;
byte DAT_4000e45e;
ushort DAT_4000e460;
ushort DAT_4000e462;
byte DAT_4000e405;
byte DAT_40001448;
char DAT_400018df;
byte DAT_400018de;
byte DAT_40002c8a;
byte DAT_4000e45f;
byte DAT_400018dd;
byte DAT_4000e354;
undefined1 DAT_4000e283;
ushort DAT_4000e468;
ushort DAT_4000e46a;
byte DAT_4000e46c;
ushort DAT_40002394;
ushort DAT_4000e46e;
byte DAT_400018e1;
byte DAT_400018e0;
byte DAT_4000e355;
undefined1 DAT_4000e284;
byte DAT_400018c5;
ushort DAT_4000e472;
ushort DAT_4000e474;
byte DAT_4000e470;
byte DAT_400018e3;
byte DAT_4000e471;
byte DAT_400018e2;
byte DAT_4000e356;
undefined1 DAT_4000e285;
ushort DAT_4000e47a;
ushort DAT_4000e47c;
byte DAT_4000e47e;
ushort DAT_40002396;
ushort DAT_4000e480;
byte DAT_400018e5;
byte DAT_400018e4;
byte DAT_4000e357;
undefined1 DAT_4000e286;
byte DAT_400018c6;
ushort DAT_4000e484;
ushort DAT_4000e486;
byte DAT_4000e482;
byte DAT_400018e7;
byte DAT_4000e483;
byte DAT_400018e6;
byte DAT_4000e358;
undefined1 DAT_4000e287;
ushort DAT_4000e48c;
ushort DAT_4000e48e;
byte DAT_4000e490;
ushort DAT_40002398;
ushort DAT_4000e492;
byte DAT_400018e9;
byte DAT_400018e8;
byte DAT_4000e359;
undefined1 DAT_4000e288;
byte DAT_400018c7;
ushort DAT_4000e496;
ushort DAT_4000e4ba;
byte DAT_4000e494;
byte DAT_400018eb;
byte DAT_4000e495;
byte DAT_400018ea;
byte DAT_4000e35a;
undefined1 DAT_4000e289;
ushort DAT_4000e49e;
ushort DAT_4000e4a0;
byte DAT_4000e4a2;
ushort DAT_4000239a;
ushort DAT_4000e4a4;
byte DAT_400018ed;
byte DAT_400018ec;
byte DAT_4000e35b;
undefined1 DAT_4000e291;
byte DAT_400018ef;
byte DAT_400018ee;
byte DAT_4000e363;
undefined1 DAT_4000e277;
byte DAT_400018c2;
byte DAT_400018cd;
byte DAT_400018f1;
byte DAT_400018f0;
byte DAT_4000e349;
undefined1 DAT_4000e278;
ushort DAT_4000e4aa;
ushort DAT_4000e4ac;
byte DAT_4000e4ae;
ushort DAT_4000239c;
ushort DAT_4000e4b0;
byte DAT_400018f3;
byte DAT_400018f2;
byte DAT_4000e34a;
undefined1 DAT_4000e279;
ushort DAT_4000e4b2;
byte DAT_4000e4b4;
byte DAT_400018f5;
byte DAT_400018f4;
byte DAT_4000e34b;
undefined1 DAT_4000e27a;
ushort DAT_4000e4bc;
byte DAT_4000e4be;
byte DAT_400018f7;
byte DAT_400018f6;
byte DAT_4000e34c;
undefined DAT_00001657;
undefined DAT_00002757;
undefined DAT_00002759;
undefined DAT_00002769;
undefined DAT_00002770;
undefined1 CAL_obd_P0894_cfg;
byte REG_SIU_GPDI127;
byte REG_SIU_GPDI128;
byte REG_SIU_GPDI129;
byte REG_SIU_GPDI130;
byte REG_SIU_GPDI131;
byte REG_SIU_GPDI132;
u16_rspeed_rpm u16_rspeed_rpm_400018fa;
byte DAT_4000e41e;
char DAT_400018ce;
byte DAT_4000e41f;
short DAT_4000e420;
char DAT_4000e41d;
char DAT_400018cf;
byte DAT_4000e446;
byte DAT_4000903d;
byte DAT_4000e453;
byte DAT_4000e447;
byte DAT_4000e44b;
byte DAT_4000e448;
byte DAT_4000e442;
byte DAT_4000e441;
byte DAT_4000e449;
undefined2 clutch_pressure_target;
enum_t6e_gear DAT_40001448;
char DAT_400018c0;
enum_t6e_gear DAT_400018dc;
enum_t6e_gear DAT_40001a44;
char DAT_40001910;
byte DAT_400018c8;
byte DAT_400018c9;
undefined1 DAT_400018df;
ushort DAT_4000e4c0;
short DAT_4000e4c2;
byte DAT_400018ca;
byte DAT_400018fc;
byte DAT_400018fd;
undefined1 gear_confirmed;
undefined1 gear_latched;
char DAT_400018fe;
enum_t6e_gear gear_candidate;
char DAT_400018ff;
byte DAT_4000190c;
byte DAT_4000190d;
byte DAT_4000190e;
byte DAT_4000190f;
byte DAT_40001900;
byte DAT_40001901;
char DAT_40001902;
char DAT_40001903;
byte DAT_40001904;
byte DAT_40001905;
char DAT_40001906;
char DAT_40001907;
byte DAT_40001908;
byte DAT_40001909;
byte DAT_4000190a;
byte DAT_4000190b;
byte DAT_40001911;
byte DAT_40001912;
enum_t6e_gear DAT_400018d3;
int DAT_40001a48;
byte DAT_4000e44e;
byte DAT_400018d5;
byte DAT_4000e44f;
byte DAT_400018d2;
byte DAT_400018d4;
byte DAT_4000e450;
undefined1 DAT_4000e33a;
undefined1 DAT_400018cb;
undefined1 DAT_4000e33b;
undefined1 DAT_400018d6;
undefined1 DAT_4000e33c;
undefined1 DAT_400018d7;
undefined1 DAT_4000e354;
undefined1 DAT_400018dd;
undefined1 DAT_4000e355;
undefined1 DAT_400018e0;
undefined1 DAT_4000e356;
undefined1 DAT_400018e2;
undefined1 DAT_4000e357;
undefined1 DAT_400018e4;
undefined1 DAT_4000e358;
undefined1 DAT_400018e6;
undefined1 DAT_4000e359;
undefined1 DAT_400018e8;
undefined1 DAT_4000e35a;
undefined1 DAT_400018ea;
undefined1 DAT_4000e35b;
undefined1 DAT_400018ec;
undefined1 DAT_4000e363;
undefined1 DAT_400018ee;
undefined1 DAT_4000e349;
undefined1 DAT_400018f0;
undefined1 DAT_4000e34a;
undefined1 DAT_400018f2;
undefined1 DAT_4000e34b;
undefined1 DAT_400018f4;
undefined1 DAT_4000e34c;
undefined1 DAT_400018f6;
undefined1 DAT_400018cc;
undefined1 DAT_400018cd;
undefined1 DAT_400018d0;
undefined1 DAT_400018d1;
undefined1 DAT_400018d2;
undefined1 DAT_400018d8;
undefined1 DAT_400018de;
undefined1 DAT_400018e1;
undefined1 DAT_400018e3;
undefined1 DAT_400018e5;
undefined1 DAT_400018e7;
undefined1 DAT_400018e9;
undefined1 DAT_400018eb;
undefined1 DAT_400018ed;
undefined1 DAT_400018ef;
undefined1 DAT_400018f1;
undefined1 DAT_400018f3;
undefined1 DAT_400018f5;
undefined1 DAT_400018f7;
undefined1 DAT_400018bf;
undefined1 DAT_400018ce;
undefined1 DAT_400018c1;
undefined1 DAT_400018c2;
undefined1 DAT_400018c3;
undefined1 DAT_400018c4;
undefined1 DAT_400018c5;
undefined1 DAT_400018c6;
undefined1 DAT_400018c7;
undefined1 DAT_400018c0;
undefined1 DAT_400018d9;
undefined1 DAT_400018da;
undefined1 DAT_400018db;
ushort DAT_40001512;
byte DAT_4000e4c6;
char DAT_4000e4c7;
char DAT_4000191e;
char DAT_4000e4c8;
char DAT_4000191f;
char DAT_4000e4ca;
char DAT_40001920;
char DAT_40001921;
char DAT_4000e498;
char DAT_40001922;
char DAT_4000e499;
char DAT_40001923;
char DAT_4000e49b;
char DAT_4000171f;
char DAT_4000e4cc;
char DAT_40001924;
char DAT_4000e4cd;
char DAT_40001925;
char DAT_4000e4ce;
char DAT_40001926;
char DAT_4000e4cf;
char DAT_40001927;
char DAT_4000e4d0;
char DAT_4000192a;
char DAT_4000192b;
char DAT_4000e49c;
byte DAT_4000e49d;
short DAT_4000192c;
byte DAT_4000e49a;
char DAT_4000e4d1;
char DAT_4000192f;
char DAT_40001456;
char DAT_4000e4d2;
char DAT_40001931;
undefined1 DAT_4000e2e8;
byte DAT_4000191b;
byte DAT_4000e3d6;
undefined1 DAT_4000e2ef;
char DAT_4000191a;
char DAT_40008f81;
byte DAT_4000191c;
byte DAT_4000e3dd;
undefined1 DAT_4000e2ed;
byte DAT_4000191d;
byte DAT_4000e3db;
undefined1 DAT_4000e2e9;
byte DAT_40001918;
byte DAT_4000e3d7;
undefined1 DAT_4000e2ea;
byte DAT_40001928;
byte DAT_4000e3d8;
undefined1 DAT_4000e2ee;
byte DAT_40001929;
byte DAT_4000e3dc;
undefined1 DAT_4000e2eb;
byte DAT_4000192e;
byte DAT_4000e3d9;
undefined1 DAT_4000e2ec;
byte DAT_40001930;
byte DAT_4000e3da;
undefined2 DAT_4000172a;
undefined1 DAT_4000171f;
undefined2 DAT_4000171c;
undefined1 DAT_40001716;
undefined1 DAT_40001715;
undefined2 DAT_40001710;
undefined2 DAT_4000170e;
undefined1 DAT_4000e3d6;
undefined1 DAT_4000191b;
undefined1 DAT_4000e3d7;
undefined1 DAT_40001918;
undefined1 DAT_4000e3d8;
undefined1 DAT_40001928;
undefined1 DAT_4000e3d9;
undefined1 DAT_4000192e;
undefined1 DAT_4000e3da;
undefined1 DAT_40001930;
undefined1 DAT_4000e3dd;
undefined1 DAT_4000191c;
undefined1 DAT_4000e3db;
undefined1 DAT_4000191d;
undefined1 DAT_4000e3dc;
undefined1 DAT_40001929;
undefined2 DAT_40001450;
undefined1 DAT_40001452;
undefined1 DAT_40001453;
undefined1 DAT_40001454;
undefined1 DAT_40001455;
undefined1 DAT_4000e4c7;
undefined1 DAT_4000191e;
undefined1 DAT_4000e4c8;
undefined1 DAT_4000191f;
undefined1 DAT_4000e4ca;
undefined1 DAT_40001920;
undefined1 DAT_4000e498;
undefined1 DAT_40001921;
undefined1 DAT_4000e499;
undefined1 DAT_40001922;
undefined1 DAT_4000e49b;
undefined1 DAT_40001923;
undefined1 DAT_4000e4cc;
undefined1 DAT_40001924;
undefined1 DAT_4000e4cd;
undefined1 DAT_40001925;
undefined1 DAT_4000e4ce;
undefined1 DAT_40001926;
undefined1 DAT_4000e4cf;
undefined1 DAT_40001927;
undefined1 DAT_4000e4d0;
undefined1 DAT_4000192a;
undefined1 DAT_4000e49c;
undefined1 DAT_4000192b;
undefined1 DAT_4000e4d1;
undefined1 DAT_4000192f;
undefined1 DAT_4000e4d2;
undefined1 DAT_40001931;
byte DAT_40001968;
undefined1 DAT_4000e28e;
byte DAT_4000e4f1;
byte DAT_4000e4f2;
byte DAT_4000193d;
byte DAT_4000193c;
byte DAT_4000e360;
string s_AAAAAAAA_4000e294;
char DAT_400017a4;
byte DAT_4000194d;
byte DAT_4000194c;
byte DAT_4000e366;
byte DAT_4000194f;
byte DAT_4000194e;
byte DAT_4000e367;
undefined1 DAT_4000e2b3;
byte DAT_4000193f;
byte DAT_4000193e;
byte DAT_4000e380;
byte DAT_40001951;
byte DAT_40001950;
byte DAT_4000e368;
byte DAT_40001953;
byte DAT_40001952;
byte DAT_4000e369;
undefined1 DAT_4000e2b4;
byte DAT_40001941;
byte DAT_40001940;
byte DAT_4000e381;
byte DAT_40001955;
byte DAT_40001954;
byte DAT_4000e36a;
byte DAT_40001957;
byte DAT_40001956;
byte DAT_4000e36b;
undefined1 DAT_4000e2b5;
byte DAT_40001943;
byte DAT_40001942;
byte DAT_4000e382;
byte DAT_40001959;
byte DAT_40001958;
byte DAT_4000e36c;
byte DAT_4000195b;
byte DAT_4000195a;
byte DAT_4000e36d;
undefined1 DAT_4000e2b6;
byte DAT_40001945;
byte DAT_40001944;
byte DAT_4000e383;
string s_AAAAAAAAAAAAAA_4000e2a0;
ushort DAT_4000e4c4;
char DAT_400017ad;
char DAT_400017ab;
ushort DAT_4000e4ea;
byte DAT_400017ca;
byte DAT_4000e4ed;
undefined2 DAT_4000195e;
ushort DAT_4000e4ee;
byte DAT_4000195d;
byte DAT_4000195c;
byte DAT_4000e373;
char DAT_400017ac;
byte DAT_40001961;
byte DAT_40001960;
byte DAT_4000e376;
byte DAT_40001963;
byte DAT_40001962;
byte DAT_4000e377;
byte DAT_4000e4f3;
byte DAT_4000e4f4;
byte DAT_40001965;
byte DAT_40001964;
byte DAT_4000e378;
byte DAT_4000e4f0;
byte DAT_40001967;
byte DAT_40001966;
byte DAT_4000e379;
byte DAT_4000194b;
byte DAT_4000194a;
byte DAT_4000e375;
undefined1 DAT_4000e2b7;
byte DAT_40001947;
byte DAT_40001946;
byte DAT_4000e384;
undefined1 DAT_4000e2b8;
byte DAT_40001949;
byte DAT_40001948;
byte DAT_4000e385;
undefined DAT_00001801;
undefined DAT_00001802;
undefined DAT_00001803;
undefined DAT_00001804;
undefined DAT_00001805;
undefined DAT_00001806;
undefined DAT_00001807;
undefined DAT_00001808;
undefined DAT_00001904;
undefined DAT_00001905;
undefined DAT_00001906;
undefined DAT_00001907;
undefined DAT_00001909;
undefined DAT_00001910;
undefined DAT_00001911;
undefined DAT_00001912;
undefined DAT_00001913;
undefined DAT_00001929;
undefined DAT_00001930;
undefined DAT_00001931;
undefined DAT_00002800;
undefined DAT_00002805;
undefined2 DAT_40001970;
byte DAT_4000e4ec;
uint DAT_4000196c;
short DAT_4000195e;
undefined1 DAT_4000e360;
undefined1 DAT_4000193c;
undefined1 DAT_4000e366;
undefined1 DAT_4000194c;
undefined1 DAT_4000e367;
undefined1 DAT_4000194e;
undefined1 DAT_4000e368;
undefined1 DAT_40001950;
undefined1 DAT_4000e369;
undefined1 DAT_40001952;
undefined1 DAT_4000e36a;
undefined1 DAT_40001954;
undefined1 DAT_4000e36b;
undefined1 DAT_40001956;
undefined1 DAT_4000e36c;
undefined1 DAT_40001958;
undefined1 DAT_4000e36d;
undefined1 DAT_4000195a;
undefined1 DAT_4000e380;
undefined1 DAT_4000193e;
undefined1 DAT_4000e381;
undefined1 DAT_40001940;
undefined1 DAT_4000e382;
undefined1 DAT_40001942;
undefined1 DAT_4000e383;
undefined1 DAT_40001944;
undefined1 DAT_4000e384;
undefined1 DAT_40001946;
undefined1 DAT_4000e385;
undefined1 DAT_40001948;
undefined1 DAT_4000e373;
undefined1 DAT_4000195c;
undefined1 DAT_4000e375;
undefined1 DAT_4000194a;
undefined1 DAT_4000e376;
undefined1 DAT_40001960;
undefined1 DAT_4000e377;
undefined1 DAT_40001962;
undefined1 DAT_4000e378;
undefined1 DAT_40001964;
undefined1 DAT_4000e379;
undefined1 DAT_40001966;
undefined1 DAT_4000193d;
undefined1 DAT_4000194d;
undefined1 DAT_4000194f;
undefined1 DAT_40001951;
undefined1 DAT_40001953;
undefined1 DAT_40001955;
undefined1 DAT_40001957;
undefined1 DAT_40001959;
undefined1 DAT_4000195b;
undefined1 DAT_4000193f;
undefined1 DAT_40001941;
undefined1 DAT_40001943;
undefined1 DAT_40001945;
undefined1 DAT_40001947;
undefined1 DAT_40001949;
undefined1 DAT_4000195d;
undefined1 DAT_4000194b;
undefined1 DAT_40001961;
undefined1 DAT_40001963;
undefined1 DAT_40001965;
undefined1 DAT_40001967;
undefined1 DAT_40001968;
u16_rspeed_rpm u16_rspeed_rpm_4000197a;
undefined1 DAT_4000e275;
byte DAT_4000e433;
byte DAT_4000e432;
byte DAT_4000197d;
byte DAT_4000197c;
byte DAT_4000e347;
undefined1 DAT_4000e25e;
byte DAT_4000e4d4;
byte DAT_4000197f;
byte DAT_4000e4d5;
byte DAT_4000197e;
char DAT_4000e4cb;
char DAT_4000167c;
byte DAT_4000e4d3;
byte DAT_4000e330;
undefined1 DAT_4000e2b0;
short DAT_4000e4d6;
ushort DAT_4000e4d8;
ushort DAT_4000e4da;
char DAT_4000e4dc;
char DAT_40001981;
byte DAT_4000e4dd;
char DAT_40001458;
byte DAT_40001980;
byte DAT_4000e391;
undefined1 DAT_4000e27d;
ushort DAT_4000e406;
byte DAT_40001983;
byte DAT_4000e40a;
byte DAT_40001982;
byte DAT_4000e34f;
undefined1 DAT_4000e27e;
ushort DAT_4000e408;
byte DAT_40001985;
byte DAT_4000e40b;
byte DAT_40001984;
byte DAT_4000e350;
undefined1 DAT_4000e25f;
ushort DAT_4000e412;
ushort DAT_4000e414;
byte DAT_40001987;
byte DAT_4000e439;
short DAT_4000198e;
ushort DAT_4000198c;
u16_voltage_5/1023v DAT_40001992;
u16_voltage_5/1023v DAT_40001990;
byte DAT_4000e41c;
ushort DAT_4000e40c;
char DAT_4000e410;
char DAT_40001988;
ushort DAT_4000e40e;
char DAT_40001989;
char DAT_4000e411;
char DAT_4000198a;
byte DAT_40001986;
byte DAT_4000e331;
ushort DAT_4000e4a6;
short DAT_4000e4a8;
undefined1 DAT_4000e28f;
undefined1 DAT_40001994;
byte DAT_40001995;
byte DAT_4000e361;
undefined1 DAT_4000e261;
byte DAT_40001996;
byte DAT_40001997;
byte DAT_4000e333;
undefined1 DAT_4000e262;
byte DAT_40001998;
byte DAT_40001999;
byte DAT_4000e334;
ushort DAT_4000e424;
byte DAT_4000199d;
byte DAT_4000e42a;
byte DAT_4000199e;
byte DAT_4000e336;
byte DAT_4000e419;
byte DAT_4000e41a;
char DAT_4000e418;
char DAT_4000199c;
byte DAT_4000199a;
byte DAT_4000e335;
undefined1 DAT_4000e27f;
byte DAT_4000199f;
byte DAT_4000e42b;
byte DAT_400019a0;
byte DAT_4000e351;
ushort DAT_4000e42e;
short DAT_400019a4;
ushort DAT_400019a6;
byte DAT_4000e42c;
undefined2 DAT_400019a8;
undefined2 DAT_400019aa;
byte DAT_4000e42d;
byte DAT_400019ac;
byte DAT_400019a1;
byte DAT_4000e430;
byte DAT_400019a2;
byte DAT_4000e352;
ushort DAT_4000e43a;
byte DAT_4000e43e;
byte DAT_4000e43f;
byte DAT_400019ad;
byte DAT_4000e353;
byte DAT_4000e437;
byte DAT_4000e438;
char DAT_4000e436;
char DAT_400019af;
byte DAT_400019ae;
byte DAT_4000e348;
undefined1 DAT_4000e265;
byte DAT_400019b0;
byte DAT_4000e440;
byte DAT_400019b1;
byte DAT_4000e337;
undefined1 DAT_4000e26b;
ushort DAT_400019b2;
byte DAT_4000e4de;
byte DAT_400019b4;
byte DAT_4000e33d;
undefined1 DAT_4000e26c;
ushort DAT_400019b6;
byte DAT_4000e4df;
byte DAT_400019b8;
byte DAT_4000e33e;
undefined1 DAT_4000e26d;
ushort DAT_400019ba;
byte DAT_4000e4e0;
byte DAT_400019bc;
byte DAT_4000e33f;
undefined1 DAT_4000e26f;
byte DAT_4000e4e6;
byte DAT_4000e4e2;
byte DAT_400019be;
byte DAT_400019bd;
byte DAT_4000e341;
undefined1 DAT_4000e270;
byte DAT_4000e4e3;
byte DAT_400019c0;
byte DAT_400019bf;
byte DAT_4000e342;
undefined1 DAT_4000e271;
byte DAT_4000e4e4;
byte DAT_400019c2;
byte DAT_400019c1;
byte DAT_4000e343;
undefined1 DAT_4000e272;
byte DAT_4000e4e5;
byte DAT_400019c4;
byte DAT_400019c3;
byte DAT_4000e344;
undefined1 DAT_4000e26e;
ushort DAT_400019c6;
byte DAT_4000e4e1;
byte DAT_400019c8;
byte DAT_4000e340;
undefined1 DAT_4000e273;
byte DAT_400019ca;
byte DAT_400019c9;
byte DAT_4000e345;
undefined1 DAT_4000e274;
byte DAT_400019cc;
byte DAT_400019cb;
byte DAT_4000e346;
char DAT_40001655;
undefined1 CAL_obd_P0717_cfg;
undefined1 CAL_obd_P0718_cfg;
undefined1 CAL_obd_P0721_cfg;
undefined1 CAL_obd_P0722_cfg;
undefined1 CAL_obd_P0723_cfg;
undefined1 speed_sensor_glitch_flags;
u16_rspeed_rpm CAL_input_shaft_speed_min;
u16_rspeed_rpm CAL_output_shaft_speed_gate;
u16_rspeed_rpm CAL_output_shaft_speed_min;
uint DAT_400019d0;
undefined1 DAT_400019d6;
uint DAT_400019dc;
undefined1 DAT_400019e2;
u16_rspeed_rpm input_shaft_rpm_inst;
u16_rspeed_rpm output_shaft_rpm_inst;
u16_rspeed_rpm input_shaft_rpm_smoothed;
u16_rspeed_rpm output_shaft_rpm_smoothed;
undefined1 CAL_input_speed_iir_coef;
undefined1 CAL_input_speed_glitch_tol_pct;
undefined1 CAL_output_speed_iir_coef;
undefined1 CAL_output_speed_glitch_tol_pct;
undefined1 DAT_4000e347;
undefined1 DAT_4000197c;
undefined1 DAT_4000e330;
undefined1 DAT_4000197e;
undefined1 DAT_4000e391;
undefined1 DAT_40001980;
undefined1 DAT_4000e34f;
undefined1 DAT_40001982;
undefined1 DAT_4000e350;
undefined1 DAT_40001984;
undefined1 DAT_4000e331;
undefined1 DAT_40001986;
undefined1 DAT_4000e361;
undefined1 DAT_40001995;
undefined1 DAT_4000e333;
undefined1 DAT_40001997;
undefined1 DAT_4000e334;
undefined1 DAT_40001999;
undefined1 DAT_4000e335;
undefined1 DAT_4000199a;
undefined1 DAT_4000e336;
undefined1 DAT_4000199e;
undefined1 DAT_4000e351;
undefined1 DAT_400019a0;
undefined1 DAT_4000e352;
undefined1 DAT_400019a2;
undefined1 DAT_4000e353;
undefined1 DAT_400019ad;
undefined1 DAT_4000e348;
undefined1 DAT_400019ae;
undefined1 DAT_4000e337;
undefined1 DAT_400019b1;
undefined1 DAT_4000e341;
undefined1 DAT_400019bd;
undefined1 DAT_4000e342;
undefined1 DAT_400019bf;
undefined1 DAT_4000e343;
undefined1 DAT_400019c1;
undefined1 DAT_4000e344;
undefined1 DAT_400019c3;
undefined1 DAT_4000e345;
undefined1 DAT_400019c9;
undefined1 DAT_4000e346;
undefined1 DAT_400019cb;
undefined1 DAT_4000197d;
undefined1 DAT_4000197f;
undefined1 DAT_40001983;
undefined1 DAT_40001985;
undefined1 DAT_40001988;
undefined1 DAT_40001989;
undefined1 DAT_40001996;
undefined1 DAT_40001998;
undefined1 DAT_4000199d;
undefined1 DAT_4000199f;
undefined1 DAT_400019a1;
undefined1 DAT_400019ac;
undefined1 DAT_400019b0;
undefined1 DAT_400019be;
undefined1 DAT_400019c0;
undefined1 DAT_400019c2;
undefined1 DAT_400019c4;
undefined1 DAT_400019ca;
undefined1 DAT_400019cc;
undefined1 DAT_40001987;
undefined1 DAT_4000e411;
undefined1 DAT_4000198a;
undefined2 DAT_4000e4a6;
undefined2 DAT_4000198c;
undefined2 DAT_4000e4a8;
undefined2 DAT_4000198e;
undefined2 DAT_40001990;
undefined2 DAT_40001992;
undefined1 DAT_4000e418;
undefined1 DAT_4000199c;
undefined1 DAT_4000e436;
undefined1 DAT_400019af;
ushort DAT_400019f8;
undefined PTR_DAT_4000e3e4;
ushort DAT_40001d8e;
ushort DAT_400019fa;
ushort DAT_40001d90;
ushort DAT_400019fe;
ushort DAT_40001d94;
ushort DAT_400019fc;
ushort DAT_40001d92;
ushort DAT_40001a00;
ushort DAT_40001dcc;
undefined1 DAT_4000e266;
undefined1 DAT_4000e27b;
undefined1 DAT_4000e267;
undefined1 DAT_4000e260;
byte DAT_400019eb;
byte DAT_400019ea;
byte DAT_4000e332;
undefined1 DAT_4000e28b;
byte DAT_400019ed;
byte DAT_4000e4f5;
byte DAT_400019ec;
byte DAT_4000e35d;
undefined1 DAT_4000e290;
byte DAT_4000e431;
undefined1 DAT_4000e292;
char DAT_400023a6;
ushort DAT_40002bda;
undefined1 DAT_4000e293;
byte DAT_40001bea;
byte DAT_40008f5d;
ushort DAT_4000e3ee;
ushort DAT_4000e3f0;
ushort DAT_4000e3f2;
byte DAT_400019ef;
byte DAT_400019ee;
byte DAT_4000e365;
byte DAT_40001bed;
byte DAT_40008f57;
byte DAT_400019f1;
byte DAT_400019f0;
byte DAT_4000e36e;
undefined1 DAT_4000e29d;
byte DAT_40001bee;
byte DAT_40008f55;
byte DAT_400019f3;
byte DAT_400019f2;
byte DAT_4000e36f;
undefined1 DAT_4000e29e;
byte DAT_40001beb;
byte DAT_40008f5b;
byte DAT_400019f5;
byte DAT_400019f4;
byte DAT_4000e370;
undefined1 DAT_4000e29f;
byte DAT_40001bec;
byte DAT_40008f59;
byte DAT_400019f7;
byte DAT_400019f6;
byte DAT_4000e371;
undefined1 DAT_4000e28a;
char DAT_40001639;
undefined1 DAT_4000e28d;
char DAT_400019e9;
char DAT_40001a07;
char DAT_40001a06;
char DAT_40001a05;
char DAT_40001a04;
char DAT_40001a03;
char DAT_40001a02;
byte DAT_4000e423;
undefined DAT_00001613;
undefined DAT_00001701;
undefined DAT_0000172a;
undefined DAT_00001780;
undefined DAT_00001790;
undefined DAT_00001812;
undefined DAT_0000181c;
undefined DAT_0000181d;
undefined DAT_00001853;
undefined DAT_0000185a;
undefined DAT_00001860;
undefined DAT_00001921;
undefined DAT_00001925;
undefined1 DAT_4000e332;
undefined1 DAT_400019ea;
undefined1 DAT_4000e35d;
undefined1 DAT_400019ec;
undefined1 DAT_4000e365;
undefined1 DAT_400019ee;
undefined1 DAT_4000e36e;
undefined1 DAT_400019f0;
undefined1 DAT_4000e36f;
undefined1 DAT_400019f2;
undefined1 DAT_4000e370;
undefined1 DAT_400019f4;
undefined1 DAT_4000e371;
undefined1 DAT_400019f6;
undefined1 DAT_4000e35f;
undefined1 DAT_400019e9;
undefined1 DAT_4000e37a;
undefined1 DAT_40001a07;
undefined1 DAT_4000e37b;
undefined1 DAT_40001a06;
undefined1 DAT_4000e37c;
undefined1 DAT_40001a05;
undefined1 DAT_4000e37d;
undefined1 DAT_40001a04;
undefined1 DAT_4000e37e;
undefined1 DAT_40001a03;
undefined1 DAT_4000e37f;
undefined1 DAT_40001a02;
undefined1 DAT_400019eb;
undefined1 DAT_400019ed;
undefined1 DAT_400019ef;
undefined1 DAT_400019f1;
undefined1 DAT_400019f3;
undefined1 DAT_400019f5;
undefined1 DAT_400019f7;
undefined2 DAT_400019f8;
undefined2 DAT_400019fa;
undefined2 DAT_400019fc;
undefined2 DAT_400019fe;
undefined2 DAT_40001a00;
byte DAT_40001a1c;
uint DAT_40001a18;
byte DAT_40009068;
char DAT_40001a09;
byte DAT_40001a08;
undefined PTR_DAT_4000906d;
byte DAT_40009077;
u8_speed_kph u8_speed_kph_40008f40;
char DAT_40001a21;
u16_torque_nm u16_torque_nm_40001a1e;
u16_torque_nm u16_torque_nm_40009072;
byte DAT_40009078;
byte DAT_40001a09;
byte DAT_40009076;
char DAT_40001a08;
byte DAT_4000907f;
byte DAT_4000907a;
short DAT_4000906a;
undefined1 driving_intensity_raw;
byte DAT_4000907b;
undefined4 driving_intensity_filtered;
byte DAT_40009083;
u8_factor_1/255 driving_style_index;
char DAT_40001a23;
undefined1 paddle_request;
u8_factor_1/255 shift_aggressiveness_blend;
char DAT_40009084;
byte DAT_40009085;
u8_factor_1/255[4] CAL_driving_shift_aggressiveness_blend_X_driving_intensity;
char DAT_4000906c;
char DAT_40001a22;
uint8_t CAL_driving_intensity_raw_multiplier;
undefined1 rpm_intensity_weight;
undefined1 intensity_event_flags;
u8_factor_1/255[4] CAL_driving_intensity_rpm_gain;
u8_rspeed_30rpm[4] CAL_driving_intensity_rpm_gain_X_rpm;
undefined1 paddle_request_prev;
u8_speed_kph vehicle_speed_kph_prev;
u16_torque_nm torque_delivered_post_tc;
u16_rspeed_1/4rpm overrev_shift_threshold;
byte DAT_40001a27;
byte DAT_40001a12;
byte DAT_40009091;
char DAT_40001a29;
u8_rspeed_10rpm CAL_overrev_shift_margin;
byte DAT_40009092;
short DAT_4000908a;
bool BOOL_40001a28;
enum_t6e_gear enum_t6e_gear_40001a0a;
byte DAT_4000908c;
byte DAT_40001a11;
byte DAT_400090b2;
byte DAT_40009093;
byte DAT_4000908f;
undefined1 DAT_40001461;
u16_rspeed_1/4rpm CAL_rpm_threshold_unknown2;
undefined1 downshift_debounce_counter;
bool downshift_armed;
bool paddle_shift_pending;
uint8_t[2] CAL_cruise_speed_target_unknown;
undefined1 DAT_40001637;
char DAT_40001a2a;
undefined1 DAT_40001a2b;
undefined DAT_4000d366;
undefined DAT_4000d36e;
undefined DAT_4000d375;
u8_factor_1/255[8] shift_sched_work_a_manual_X_throttle;
undefined DAT_4000d3ae;
uint8_t[8] shift_sched_work_a_manual;
undefined DAT_4000d3b6;
u8_factor_1/255[8] shift_sched_work_a_auto_X_throttle;
undefined DAT_4000d3bd;
uint8_t[8] shift_sched_work_a_auto;
undefined DAT_4000d726;
undefined DAT_4000d72e;
undefined DAT_4000d735;
undefined1 decel_magnitude;
ushort DAT_40001a3a;
ushort DAT_40001510;
ushort DAT_40003438;
undefined2 DAT_40001c4e;
undefined2 DAT_40001c52;
ushort DAT_0008d9b8;
undefined2 DAT_0008d9ba;
undefined2 DAT_0008d9bc;
undefined2 DAT_0008d9be;
undefined2 DAT_0008d9c0;
undefined2 DAT_0008d9c2;
undefined2 DAT_0008d9c4;
undefined2 DAT_0008d9c6;
undefined2 DAT_0008d9c8;
byte DAT_00001cf8;
undefined1 DAT_00001cf9;
undefined1 DAT_00001cfa;
undefined1 DAT_00001cfb;
undefined1 DAT_00001cfc;
undefined1 DAT_00001cfd;
undefined1 DAT_00001cfe;
int DAT_40002ddc;
int DAT_40002de0;
int DAT_40002de4;
int DAT_40002de8;
undefined DAT_40002e24;
char DAT_40001468;
u16_rspeed_rpm u16_rspeed_rpm_40001a30;
enum_t6e_gear DAT_40001a36;
u16_torque_nm DAT_40001a38;
byte DAT_40001a32;
uint DAT_400013b8;
undefined2 DAT_40001a34;
uint16_t CAL_gear_ratio_1;
uint16_t CAL_gear_ratio_2;
uint16_t CAL_gear_ratio_3;
uint16_t CAL_gear_ratio_4;
uint16_t CAL_gear_ratio_5;
uint16_t CAL_gear_ratio_6;
uint16_t CAL_gear_ratio_REV;
byte DAT_4000914d;
uint8_t[8] CAL_upshift_curve_blend_manual;
uint8_t[8] CAL_upshift_curve_blend_auto;
enum_t6e_gear gear_cur_uss;
u8_factor_1/255[8] shift_sched_work_b_manual_X_throttle;
uint8_t[8] shift_sched_work_b_manual;
u8_factor_1/255[8] shift_sched_work_b_auto_X_throttle;
uint8_t[8] shift_sched_work_b_auto;
u8_rspeed_25rpm CAL_shift_speed_2_3_manual;
u8_rspeed_25rpm CAL_shift_speed_3_4_manual;
u8_rspeed_25rpm CAL_shift_speed_4_5_manual;
u8_rspeed_25rpm CAL_shift_speed_5_6_manual;
uint8_t CAL_shift_speed_1_2_auto;
u8_rspeed_25rpm CAL_shift_speed_2_3_auto;
u8_rspeed_25rpm CAL_shift_speed_3_4_auto;
u8_rspeed_25rpm CAL_shift_speed_4_5_auto;
u8_rspeed_25rpm CAL_shift_speed_5_6_auto;
uint8_t[8] CAL_shift_speed_1_2_manual_X_oil_temp;
u8_rspeed_25rpm[8] CAL_shift_speed_1_2_manual;
uint8_t CAL_upshift_max_speed_manual;
uint8_t CAL_upshift_max_speed_auto;
uint8_t[8] CAL_upshift_throttle_axis_manual;
uint8_t[8] CAL_upshift_throttle_axis_auto;
uint8_t[8] CAL_downshift_throttle_axis_auto;
byte DAT_4000d307;
uint8_t[8] CAL_downshift_curve_blend_manual;
uint8_t[8] CAL_downshift_curve_blend_auto;
enum_t6e_gear gear_curr_dss;
undefined1 CAL_downshift_speed_hysteresis;
uint8_t[8] CAL_downshift_throttle_axis_manual;
undefined *DAT_40001a40;
ushort DAT_40001c6e;
ushort DAT_40001c6c;
undefined1 DAT_40001a44;
ushort DAT_40001c6a;
ushort DAT_40001c68;
ushort DAT_40001c66;
ushort DAT_40001c64;
ushort DAT_40001c62;
ushort DAT_40001c60;
ushort DAT_40001c5e;
ushort DAT_40001c5c;
ushort DAT_40001c5a;
ushort DAT_40001c58;
uint16_t DAT_40001a54;
undefined DAT_00001388;
byte DAT_40001a5a;
uint16_t uint16_t_40001a58;
u8_factor_1/255[8] CAL_limiter_overrev_aggression;
enum_t6e_gear enum_t6e_gear_40001a13;
uint8_t[8] CAL_limiter_overrev_aggression_X_load;
uint16_t rpm_revlimit_factor;
char DAT_40008f10;
u8_factor_1/255 u8_factor_1/255_40001a68;
short DAT_40001a76;
ushort DAT_40001a78;
int16_t throttle_rate_commanded;
byte DAT_40009170;
short DAT_40001a7a;
short DAT_40001a7e;
ushort DAT_40001a7c;
byte DAT_40009171;
byte DAT_40001a80;
u8_factor_1/255 CAL_throttle_rate_threshold_unknown1;
char DAT_40001a70;
ushort DAT_40001470;
byte DAT_400090c6;
short DAT_40001a72;
byte DAT_40008f17;
int DAT_40001a6c;
char DAT_400090c5;
char DAT_40001a74;
char DAT_40001a60;
char DAT_40008f1a;
byte DAT_400090c8;
int DAT_40001a64;
char DAT_40001ac5;
char DAT_40001ac6;
byte DAT_400090cc;
byte DAT_400090cb;
byte DAT_400090c3;
byte DAT_400090d6;
byte DAT_400090c9;
byte DAT_40001a71;
byte DAT_400090ca;
byte DAT_400090c7;
byte DAT_40001a61;
int DAT_40001a5c;
byte DAT_40001a2b;
undefined DAT_400057c8;
undefined DAT_40009e02;
undefined DAT_40009e22;
uint16_t[16] CAL_shift_schedule_unknown1;
uint16_t[16] CAL_shift_schedule_unknown1_X_carspeed;
undefined1 throttle_shift;
undefined1 CAL_tps_threshold_unknown1;
u16_rspeed_rpm rev_limit_working;
uint8_t[6] CAL_upshift_revlimit_offset_X_gear;
u8_rspeed_5rpm[6] CAL_upshift_revlimit_offset;
undefined2 upshift_speed_threshold;
enum_t6e_gear upshift_target_gear;
u8_factor_1/255 CAL_kickdown_decel_threshold;
undefined2 downshift_speed_threshold;
enum_t6e_gear downshift_target_gear;
char DAT_40001a9e;
char DAT_40009028;
char DAT_40001a96;
byte DAT_40001a98;
byte DAT_40001a8f;
char DAT_40001aab;
char DAT_40001a99;
byte DAT_40001a9a;
byte DAT_40008efc;
byte DAT_40001a93;
byte DAT_40008ef9;
byte DAT_40008ede;
byte DAT_40001a92;
undefined1 upshift_debounce_counter;
bool upshift_armed;
undefined2 DAT_40001aac;
char DAT_40001a90;
char DAT_40001ace;
undefined1 DAT_40001aaa;
undefined1 shift_lockout_timer;
undefined1 DAT_40001a88;
u16_rspeed_rpm downshift_max_input_shaft_rpm;
byte DAT_40001a95;
uint8_t CAL_shift_gears_per_shift;
byte DAT_40009034;
undefined1 CAL_shift_lockout_time;
ushort DAT_4000902e;
bool CAL_shift_auto_upshift_at_revlimit_enable;
byte DAT_40001a94;
undefined1 DAT_40001a89;
char DAT_40009031;
char DAT_40001a9b;
char DAT_40001ad5;
char DAT_40001ad6;
byte DAT_40008f4c;
char DAT_40001ad4;
char DAT_40001a8a;
undefined1 DAT_40008f5e;
undefined1 DAT_40001a8b;
undefined1 DAT_40001ac4;
undefined1 DAT_40001a8e;
char DAT_40008f7f;
char DAT_40008f61;
byte DAT_40008f4a;
undefined1 DAT_40001a9c;
undefined1 DAT_40001a9d;
byte DAT_40008ed4;
undefined1 DAT_40001a8d;
undefined1 DAT_40001a97;
byte DAT_40009037;
byte DAT_40008f4b;
uint DAT_4000916c;
byte DAT_400090a9;
char DAT_400023a3;
char DAT_400023a4;
char DAT_400023a7;
bool upshift_min_speed_inhibit;
undefined1 paddle_hold_counter;
undefined1 paddle_upshift_trigger_count;
undefined1 paddle_downshift_trigger_count;
undefined2 DAT_40001be8;
undefined2 DAT_40001be6;
undefined2 DAT_40001be4;
undefined2 DAT_40001be2;
byte DAT_40001aaa;
byte DAT_40001aa0;
char DAT_400090bd;
char DAT_40001aa1;
char DAT_40001bfa;
byte DAT_40001aa3;
char DAT_4000147c;
byte DAT_40001aa2;
undefined1 DAT_40008f54;
undefined1 DAT_40001bee;
undefined1 DAT_40008f56;
undefined1 DAT_40001bed;
undefined1 DAT_40008f58;
undefined1 DAT_40001bec;
undefined1 DAT_40008f5a;
undefined1 DAT_40001beb;
undefined1 DAT_40008f55;
undefined1 DAT_40008f57;
undefined1 DAT_40008f59;
undefined1 DAT_40008f5b;
u8_rspeed_rpm CAL_shift_speed_guard_margin.;
u8_rspeed_8rpm[8] CAL_shift_guard_rpm_unknown;
u8_factor_1/255[8] CAL_shift_guard_rpm_unknown_X_decel_magnitude;
undefined1 auto_shift_direction_state;
char DAT_4000902a;
undefined1 CAL_garage_engage_speed;
enum_t6e_gear DAT_40001461;
ushort DAT_4000915a;
undefined1 auto_shift_dwell_timer;
byte DAT_40008ea9;
char DAT_40001481;
char DAT_40001aae;
undefined1 DAT_40001aa9;
undefined1 DAT_40001bfc;
undefined1 DAT_40001c56;
undefined2 DAT_40001438;
char DAT_40001aaf;
undefined1 DAT_40001bfe;
char DAT_40001480;
short DAT_40001abc;
undefined2 DAT_40001ab0;
undefined2 DAT_40001ab2;
undefined2 DAT_40001ab4;
undefined1 DAT_40001bfd;
undefined2 DAT_40001bde;
undefined1 DAT_40001aab;
char DAT_40001aa9;
short DAT_40001ab6;
char DAT_40001ab8;
byte DAT_40008ec0;
char DAT_40008eb6;
char DAT_40009008;
byte DAT_40001ab9;
byte DAT_40008ed1;
ushort DAT_40001aac;
ushort DAT_40002bd8;
byte DAT_40008e8b;
ushort DAT_40001bde;
byte DAT_40008eac;
undefined PTR_DAT_40001482;
ushort DAT_40002bd6;
ushort DAT_40002bd4;
ushort DAT_4000900a;
ushort DAT_4000900c;
ushort DAT_4000900e;
ushort DAT_40009010;
ushort DAT_40001aba;
uint DAT_40001ae4;
byte DAT_40008f24;
short DAT_40001aea;
short DAT_40001ae8;
byte DAT_40008f52;
byte DAT_4000916a;
short DAT_40001c54;
byte DAT_40001c50;
short DAT_40001c52;
short DAT_4000149c;
ushort DAT_4000e488;
short DAT_4000e48a;
ushort DAT_40001aec;
ushort DAT_4000343a;
byte DAT_4000e4b5;
char DAT_4000904f;
undefined1 DAT_40001ba1;
undefined2 trans_slip_metric;
u16_rspeed_rpm CAL_slip_output_speed_min;
u16_rspeed_rpm CAL_slip_input_speed_min;
char DAT_40001afa;
enum_t6e_gear enum_t6e_gear_40001afd;
byte DAT_4000903a;
byte DAT_40009039;
byte DAT_40009030;
byte DAT_40009026;
char DAT_40001b95;
char DAT_40001af6;
short DAT_40001af4;
undefined1 DAT_4000148d;
char DAT_40001b94;
undefined1 DAT_40001b97;
byte DAT_4000149e;
short DAT_400014a0;
char DAT_40001b96;
bool shift_closed_loop_active;
undefined1 DAT_40001af7;
undefined1 DAT_40001af8;
undefined1 DAT_40001af9;
undefined1 DAT_40001c3a;
enum_t6e_gear DAT_40001ad4;
u16_rspeed_rpm DAT_4000170a;
u16_rspeed_rpm DAT_40001708;
u16_rspeed_rpm DAT_40001706;
u16_rspeed_rpm DAT_40001704;
ushort DAT_40001552;
undefined1 DAT_40001be1;
undefined1 DAT_40001b9e;
undefined1 DAT_40001b9f;
byte DAT_40001aee;
byte DAT_40001668;
undefined1 DAT_40001490;
undefined1 DAT_40001c71;
byte DAT_40008f81;
byte DAT_40001af1;
byte DAT_40001af3;
byte DAT_0008daf1;
byte DAT_0008daf2;
undefined1 DAT_0008dae8;
byte DAT_0008dae9;
char DAT_40001a44;
byte DAT_0008daed;
byte DAT_0008daeb;
byte DAT_40001af2;
char DAT_4000e4c9;
char DAT_40001afc;
byte DAT_40001afb;
undefined1 tc_k_factor;
byte DAT_40001ac7;
char DAT_40001aef;
char DAT_40001af0;
char DAT_40001a88;
undefined1 DAT_40001bfa;
undefined1 DAT_40008f2b;
undefined1 DAT_40008f66;
undefined1 DAT_40001bb0;
undefined1 shift_substage;
undefined1 CAL_shift_adapt_mode;
ushort DAT_400090aa;
byte DAT_40001c18;
undefined4 DAT_40002ba4;
byte DAT_4000148d;
undefined2 DAT_400058d0;
short DAT_40001c4e;
byte DAT_40002ba1;
byte DAT_40008f5c;
char DAT_40001b09;
byte DAT_40001aff;
char DAT_40001afe;
undefined1 DAT_40001ad5;
char DAT_40008f67;
char DAT_40001a8e;
char DAT_40001bb0;
undefined1 DAT_40001ad6;
char DAT_40001a8b;
char DAT_40001a8c;
byte DAT_40001b98;
undefined2 DAT_40001b00;
undefined2 DAT_40001b02;
undefined2 DAT_40001b04;
undefined2 DAT_40001b06;
char DAT_40001c82;
char DAT_40001c83;
char DAT_40001c78;
char DAT_400014a2;
byte DAT_4000902c;
byte DAT_40001b0a;
byte DAT_40001865;
undefined1 DAT_40001864;
undefined1 DAT_4000148e;
uint8_t DAT_4000148f;
byte DAT_400014a3;
char DAT_40001ad3;
char DAT_40001ad2;
byte DAT_40001ba1;
char DAT_40001b08;
char DAT_400014a4;
undefined1 DAT_40001bdd;
char DAT_40001b0b;
byte DAT_40001b0d;
char DAT_40001bdc;
undefined1 DAT_40005f5c;
undefined1 DAT_4000603c;
undefined1 DAT_4000611c;
undefined1 DAT_400061fc;
byte DAT_40001b0c;
ushort DAT_40001b0e;
ushort DAT_4000913e;
ushort DAT_40009002;
byte DAT_400023e4;
byte DAT_400024c4;
byte DAT_400025a4;
byte DAT_40002684;
byte DAT_40002764;
byte DAT_40002844;
byte DAT_40002924;
byte DAT_40002a04;
byte DAT_4000902b;
undefined1 DAT_400010bc;
undefined1 DAT_40001494;
undefined1 DAT_40001498;
undefined2 DAT_400023d0;
undefined2 DAT_400023d2;
undefined1 DAT_400023d6;
undefined DAT_400023d8;
undefined1 DAT_400023d9;
undefined2 DAT_400023ec;
undefined2 DAT_40002450;
undefined DAT_40005f48;
uint8_t[20] CAL_shift_profile_adapt_default;
pointer PTR_DAT_400010c8;
pointer PTR_PTR_400010e8;
pointer PTR_DAT_40001108;
pointer PTR_DAT_40001128;
undefined DAT_40005f4a;
undefined DAT_40005f60;
undefined DAT_40005fc4;
ushort DAT_400090f4;
byte DAT_400090f2;
char DAT_40001b10;
undefined2 DAT_400090fe;
undefined2 DAT_40009100;
undefined2 DAT_40009102;
undefined2 DAT_40009104;
byte DAT_40001b28;
byte DAT_400090f9;
ushort DAT_400090fa;
int DAT_40001b20;
byte DAT_400090f6;
byte DAT_400090f7;
int DAT_40001b1c;
int DAT_40001b14;
byte DAT_400090f3;
int DAT_40001b18;
undefined *DAT_40001b24;
ushort DAT_400090fc;
byte DAT_40001b29;
byte DAT_400090f8;
ushort DAT_40001b2a;
undefined2 DAT_40001b2c;
undefined DAT_00001f40;
byte DAT_400014a5;
enum_t6e_gear shift_to_gear;
undefined4 shift_slip_filter_accum;
undefined2 shift_slip_filtered;
undefined2 gear_state;
uint16_t[7] shift_count_0_1;
undefined2 shift_transition_code;
undefined2 shift_count_2_0;
undefined2 shift_count_2_1;
undefined2 shift_count_2_3;
undefined2 shift_count_2_4;
undefined2 shift_count_3_1;
undefined2 shift_count_3_2;
undefined2 shift_count_3_4;
undefined2 shift_count_3_5;
undefined2 shift_count_4_2;
undefined2 shift_count_4_3;
undefined2 shift_count_4_5;
undefined2 shift_count_4_6;
undefined2 shift_count_5_3;
undefined2 shift_count_5_4;
undefined2 shift_count_5_6;
undefined2 shift_count_6_5;
undefined2 shift_count_6_4;
undefined2 shift_count_9_1;
undefined2 shift_count_10_0;
undefined2 shift_count_10_1;
byte DAT_400090b5;
undefined1 shift_adapt_phase_unknown;
short DAT_400090d4;
undefined2 shift_adapt_state_unknown;
ushort DAT_40001b36;
ushort DAT_400090b6;
ushort DAT_40001b34;
ushort DAT_400090b8;
ushort DAT_400090d8;
byte DAT_400090be;
short DAT_40001b38;
ushort DAT_400090ba;
byte DAT_40009154;
ushort DAT_40009150;
ushort DAT_40009152;
ushort DAT_40009140;
ushort DAT_400090ee;
undefined2 DAT_400090f0;
uint16_t[6] CAL_clutch_unknown1;
ushort DAT_40001b40;
uint16_t[6] CAL_clutch_unknown1_X_throttle_rate;
ushort DAT_40001b3e;
byte DAT_40008f79;
byte DAT_400090a7;
ushort DAT_40001b42;
byte DAT_400090a6;
uint16_t[64] CAL_clutch_pressure_target_tour;
uint16_t[64] CAL_clutch_pressure_target_sport;
uint16_t[8] CAL_clutch_pressure_target_tour_X_load;
uint16_t[8] CAL_clutch_pressure_target_tour_Y_rpm;
uint16_t[8] CAL_clutch_pressure_target_sport_X_load;
uint16_t[8] CAL_clutch_pressure_target_sport_Y_rpm;
char DAT_40001b54;
uint8_t DAT_40001ad1;
ushort DAT_40001b50;
ushort DAT_40008f6a;
char DAT_40001b52;
ushort DAT_40001874;
ushort DAT_40008f74;
byte REG_SIU_GPDO135;
char DAT_40001a89;
byte REG_SIU_GPDO136;
ushort DAT_40008f76;
byte REG_SIU_GPDO137;
byte DAT_40008f72;
byte DAT_40008f73;
char DAT_40008ee8;
undefined1 DAT_40001b46;
char DAT_40009048;
undefined1 DAT_40001b4e;
undefined1 DAT_40001b4f;
u8_speed_kph CAL_tcc_coast_unlock_speed;
uint8_t CAL_tcc_coast_unlock_load;
byte DAT_40001509;
undefined2 CAL_tcc_slu_fixed_demand;
char DAT_40001b47;
undefined2 CAL_tcc_creep_lockup_min;
char DAT_40001b48;
undefined2 CAL_tcc_creep_lockup_max;
undefined1 CAL_tcc_creep_lockup_ramp_normal;
short DAT_40008f96;
byte DAT_40001b99;
undefined1 CAL_tcc_creep_lockup_ramp_loaded;
undefined1 CAL_tcc_creep_lockup_load_threshold;
byte DAT_4000150b;
undefined1 CAL_tcc_creep_lockup_engage_speed;
byte DAT_4000150a;
undefined1 CAL_tcc_creep_lockup_release_speed;
undefined1 tcc_creep_lockup_active;
short DAT_40008f98;
undefined2 tcc_slu_demand_staged;
undefined2 tcc_slu_demand_final;
short DAT_40008f9a;
undefined1 tcc_lockup_ramp_inhibit_timer;
short DAT_40008f9c;
short DAT_40008fb4;
byte DAT_40001b45;
ushort DAT_40009142;
char DAT_40008fda;
short DAT_40001b9c;
byte DAT_40001b9f;
undefined DAT_0000afc8;
pointer PTR_DAT_40001048;
pointer PTR_PTR_40001060;
pointer PTR_DAT_40001078;
u16_rspeed_1/4rpm CAL_rpm_clutch_apply;
pointer PTR_DAT_40001090;
undefined2 DAT_400058f0;
undefined2 DAT_400062c8;
undefined4 DAT_400062cc;
undefined4 DAT_400062d0;
undefined4 DAT_400062d4;
undefined2 DAT_400063dc;
uint8_t[8] s_'6Qu_4000978e;
uint8_t[8] s__40009796;
byte REG_SIU_GPDO191;
uint8_t[8] s__4000982e;
uint8_t[8] s__40009836;
u16_rspeed_1/4rpm CAL_rpm_clutch_release;
uint8_t[8] s__4000983e;
uint8_t[8] s__40009846;
uint8_t[8] s_'6Qu_400099e2;
uint8_t[8] s_Cu_400099ea;
uint8_t[64] s_///////_4444444_;;;;;;;_0000000_8_400099f2;
uint8_t[8] *PTR_DAT_4000d446;
uint8_t[8] s_pJ_4000d44e;
undefined DAT_ffffec78;
undefined1 input_shaft_speed;
uint8_t LEA_shift_adaptation_pi_feedback;
undefined1 torque_alphaN_raw_8bit;
undefined1 shift_profile_index;
byte REG_SIU_GPDO91;
byte REG_SIU_GPDO92;
byte REG_SIU_GPDO96;
byte REG_SIU_GPDO98;
byte REG_SIU_GPDO99;
byte REG_SIU_GPDO100;
byte DAT_40008f3f;
byte DAT_400014a6;
byte DAT_400014a7;
byte DAT_40001b55;
char DAT_40001b56;
int DAT_40005900;
int DAT_40005904;
int DAT_40005908;
int DAT_4000590c;
int DAT_40005910;
int DAT_40005914;
undefined2 DAT_40005918;
undefined2 DAT_40005a18;
undefined2 DAT_40005b18;
undefined2 DAT_40005c18;
undefined2 DAT_40005d18;
undefined2 DAT_40005e18;
char DAT_40009035;
char DAT_40001bb1;
char DAT_40001bb2;
byte DAT_40008f0d;
short DAT_4000172a;
short DAT_40001b5c;
short DAT_40001b5e;
uint DAT_40001b58;
byte DAT_40001b60;
char DAT_40009018;
undefined *PTR_DAT_0008ddf0;
undefined *PTR_DAT_0008de3c;
undefined *PTR_DAT_0008de88;
undefined DAT_0008ded4;
uint8_t[64] CAL_shift_slip_threshold_adaptive_1_2;
uint8_t[64] CAL_shift_slip_threshold_adaptive_2_3;
uint8_t[64] CAL_shift_slip_threshold_adaptive_3_4;
uint8_t[64] CAL_shift_slip_threshold_adaptive_4_5;
uint8_t[64] CAL_shift_slip_threshold_adaptive_5_6;
uint8_t[8] CAL_shift_slip_threshold_adaptive_1_2_X_load;
uint8_t[8] CAL_shift_slip_threshold_adaptive_2_3_X_load;
undefined1 slip_settle_timer;
uint8_t[8] CAL_shift_slip_threshold_adaptive_3_4_X_load;
uint8_t[8] CAL_shift_slip_threshold_adaptive_4_5_X_load;
uint8_t[8] CAL_shift_slip_threshold_adaptive_5_6_X_load;
uint8_t CAL_shift_slip_threshold_static_1_2;
uint8_t CAL_shift_slip_threshold_static_2_3;
uint8_t CAL_shift_slip_threshold_static_3_4;
uint8_t CAL_shift_slip_threshold_static_4_5;
uint8_t CAL_shift_slip_threshold_static_5_6;
uint8_t[8] CAL_shift_slip_threshold_adaptive_1_2_Y_input_speed;
uint8_t[8] CAL_shift_slip_threshold_adaptive_2_3_Y_input_speed;
uint8_t[8] CAL_shift_slip_threshold_adaptive_3_4_Y_input_speed;
uint8_t[8] CAL_shift_slip_threshold_adaptive_4_5_Y_input_speed;
uint8_t[8] CAL_shift_slip_threshold_adaptive_5_6_Y_input_speed;
bool downshift_sync_complete;
char DAT_40001b6b;
ushort DAT_40001b86;
byte DAT_40001b88;
byte DAT_40001b89;
undefined2 DAT_40001c48;
undefined2 DAT_40001c44;
ushort DAT_40001c4a;
byte DAT_40001c43;
byte DAT_40001c42;
byte DAT_40001bb2;
byte DAT_40001bb1;
char DAT_40001c3e;
char DAT_40001ba5;
char DAT_40001b8d;
char DAT_40001b81;
char DAT_40001b8e;
char DAT_40008fe1;
char DAT_40001ba0;
char DAT_40001b82;
undefined1 DAT_40001b80;
char DAT_40008f4d;
char DAT_40008f53;
char DAT_40008f9f;
byte DAT_40008fec;
byte DAT_40008fed;
byte DAT_400090b1;
byte DAT_4000914c;
byte DAT_400090b4;
byte DAT_40008fe7;
char DAT_40008f4e;
char DAT_40001bf8;
undefined2 DAT_40001bae;
char DAT_40008eb3;
char DAT_40008f38;
byte DAT_40001b84;
undefined1 DAT_40001b85;
byte DAT_4000903f;
byte DAT_40001b8c;
byte DAT_400014aa;
undefined1 DAT_4000915f;
undefined1 DAT_40009080;
char DAT_40009019;
undefined1 DAT_4000901a;
byte DAT_4000901b;
byte DAT_4000901c;
byte DAT_4000901d;
char DAT_40009020;
byte DAT_40009021;
undefined1 DAT_40009025;
undefined2 DAT_40001b6c;
undefined2 DAT_40001b6e;
char DAT_40008f7a;
char DAT_40001b9e;
char DAT_40001b9f;
char DAT_400014a9;
char DAT_40008f7b;
byte DAT_40008fef;
byte DAT_40008fe4;
short DAT_40001c7c;
short DAT_40001c7a;
undefined1 DAT_40001bf5;
byte DAT_40001b62;
short DAT_40002592;
short DAT_40002590;
undefined1 DAT_40001bf4;
byte DAT_40001b61;
byte DAT_40008e7a;
byte DAT_40008e84;
byte DAT_40008e8e;
byte DAT_40008e98;
byte DAT_40008f82;
byte DAT_40001491;
byte DAT_40008edb;
byte DAT_40008ee5;
char DAT_40009016;
undefined1 DAT_40008f06;
undefined1 DAT_40008f03;
char DAT_40009081;
char DAT_40009017;
byte DAT_40008ebd;
byte DAT_40008ea2;
undefined1 DAT_40001c4c;
ushort DAT_4000914a;
ushort DAT_40009146;
ushort DAT_40009148;
ushort DAT_40009144;
byte DAT_4000907c;
char DAT_40001a8d;
short DAT_40001560;
undefined DAT_0008d9dc;
undefined *PTR_DAT_0008da04;
undefined *PTR_DAT_0008da50;
undefined *PTR_DAT_0008db90;
undefined *PTR_DAT_0008dc74;
undefined *PTR_DAT_0008dcc0;
undefined *PTR_DAT_0008dd0c;
undefined *PTR_PTR_0008dd58;
undefined *PTR_PTR_0008dda4;
undefined DAT_0008df20;
undefined *PTR_DAT_0008df6c;
pointer PTR_DAT_0008dfb8;
undefined DAT_0008dfe9;
undefined DAT_400010a8;
undefined4 DAT_40002bbc;
undefined4 DAT_40005f18;
undefined DAT_40005f30;
undefined2 DAT_40006340;
undefined DAT_40009284;
undefined DAT_4000928c;
undefined DAT_400097ae;
undefined DAT_400097b6;
undefined DAT_4000981e;
undefined DAT_40009826;
undefined DAT_40009a32;
unicode u_PPPPJCCC_40009a42;
undefined DAT_40009ab2;
undefined DAT_40009aba;
undefined DAT_40009c82;
undefined DAT_40009c8a;
undefined DAT_40009c92;
undefined DAT_40009cd2;
pointer PTR_DAT_40009cda;
undefined DAT_40009ce2;
undefined DAT_40009d22;
undefined DAT_40009d2a;
undefined DAT_40009d32;
undefined DAT_40009d3a;
undefined DAT_40009d72;
undefined DAT_40009d7a;
undefined DAT_40009d82;
undefined DAT_4000d456;
undefined DAT_4000d45e;
undefined DAT_4000d466;
undefined DAT_4000d4a6;
undefined DAT_4000d4ae;
undefined DAT_4000d4b6;
pointer PTR_DAT_4000d4f6;
undefined DAT_4000d4fe;
undefined DAT_4000d506;
undefined DAT_4000d50e;
undefined DAT_4000d516;
undefined DAT_4000d51e;
undefined UNK_ffff8040;
undefined UNK_ffff8047;
undefined1 input_shaft_torque_8bit;
undefined4 shift_quality_measured;
undefined1 shift_adapt_control_flags;
undefined1 neutral_release_timer_from_drive;
undefined1 neutral_release_timer_from_reverse;
uint8_t[8] CAL_shift_neutral_release_timer_from_drive;
uint8_t[8] CAL_shift_neutral_release_timer_from_drive_rev;
uint8_t[8] CAL_shift_neutral_release_timer_from_drive_X_oil_temp;
uint8_t[8] CAL_shift_neutral_release_timer_from_drive_rev_X_oil_temp;
undefined4 shift_quality_accumulator;
undefined2 shift_phase_cycle_count;
uint8_t CAL_shift_quality_accum_bound;
u16_rspeed_rpm CAL_rpm_engage_min;
u16_rspeed_1/4rpm CAL_rpm_gear1_engage_min;
undefined1 shift_exec_init;
uchar[49] CAL_shift_profile_index;
uchar[49] shift_clutch_element;
uchar[49] CAL_shift_type;
uchar[11] CAL_gear_clutch_bitmask;
pointer32[19] CAL_shift_pressure_curve_ptr_a;
pointer32[19] CAL_shift_pressure_curve_ptr_b;
undefined1 clutch_idx_oncoming;
undefined1 clutch_idx_offgoing;
undefined2 shift_ramp_step;
undefined1 pressure_setpoint_oncoming;
undefined1 pressure_setpoint_offgoing;
undefined1 shift_phase2_started;
undefined1 clutch_elem_oncoming_id;
undefined1 clutch_elem_offgoing_id;
undefined1 clutch_elem_action;
undefined1 clutch_mask_target;
undefined1 clutch_pressure_base_a;
undefined1 clutch_pressure_base_b;
undefined1 clutch_pressure_base_c;
undefined1 shift_end_load_dn_light;
undefined1 shift_end_load_dn_heavy;
undefined1 shift_end_load_up_light;
undefined1 shift_end_load_up_heavy;
undefined2 torque_phase_pressure;
undefined4 torque_phase_pressure_pct;
undefined1 shift_torque_phase_hold;
undefined1 clutch_elem_ramp_step;
undefined1 clutch_elem_step_count;
undefined1 clutch_elem_fill_delay_reload;
undefined1 clutch_elem_fill_delay;
undefined1 clutch_elem_ramp_phase;
undefined2 slip_threshold;
undefined1 clutch_mask_current;
undefined2 shift_ramp_timer;
undefined4 clutch_elem_pressure_accum;
undefined4 clutch_elem_pressure_hold;
undefined2 clutch_elem_pressure_endpoint;
undefined2 clutch_elem_pressure_delta;
undefined2 clutch_elem_pressure_ref;
undefined2 clutch_elem_pressure_cmd;
undefined2 clutch_elem_prefill_pressure;
undefined4 clutch_elem_slip_error;
undefined2 clutch_elem_slip_ref;
byte DAT_40009159;
byte DAT_40008f41;
undefined1 DAT_40009033;
undefined1 DAT_40009032;
undefined1 DAT_4000915c;
char DAT_40008ff0;
undefined1 DAT_40001ad1;
u16_factor_1/255 u16_factor_1/255_4000e3f4;
undefined2 input_shaft_speedratio;
uint8_t[8] CAL_torque_model_k_factor;
u8_factor_1/255[8] CAL_torque_model_k_factor_X_speed_ratio;
u16_torque_nm torque_alphaN;
u16_torque_nm input_shaft_torque_alphaN;
undefined1 DAT_40001c39;
undefined2 DAT_40009002;
undefined1 DAT_40001cb8;
undefined2 DAT_400024b0;
undefined2 DAT_40002590;
undefined DAT_40002670;
undefined DAT_40002750;
undefined DAT_40002830;
undefined DAT_40002910;
undefined DAT_400029f0;
undefined1 DAT_40006408;
undefined UNK_fffe7960;
undefined4 shift_slip_tail_sum;
uint8_t CAL_adapt_inhibit_load;
short DAT_0008d9fc;
undefined DAT_0008e038;
pointer PTR_0008e039;
undefined1 DAT_400063a4;
undefined DAT_4000cc0e;
undefined DAT_4000cc5f;
undefined *PTR_4000ccb0;
undefined *PTR_DAT_4000cd00;
undefined DAT_4000cfb2;
undefined DAT_4000d2b6;
undefined4 shift_quality_ref_hi;
undefined4 shift_quality_ref_lo;
undefined1 shift_quality_error;
undefined2 shift_adapt_correction;
u8_factor_1/255[8] CAL_shift_adapt_gain_pos;
u8_factor_1/255[8] CAL_shift_adapt_gain_pos_X_shift_quality_error;
u8_factor_1/255[8] CAL_shift_adapt_gain_neg;
u8_factor_1/255[8] CAL_shift_adapt_gain_neg_X_shift_quality_error;
byte DAT_400090ce;
char DAT_40009089;
undefined1 DAT_40002c8a;
undefined2 DAT_40008f8c;
undefined2 DAT_4000244c;
undefined2 DAT_40008f8e;
undefined2 DAT_4000244e;
undefined2 DAT_40008f90;
undefined2 DAT_4000252c;
undefined2 DAT_40008f92;
undefined2 DAT_4000252e;
undefined2 DAT_40008f94;
undefined2 DAT_4000260c;
undefined2 DAT_40008fa0;
undefined2 DAT_4000260e;
undefined2 DAT_40008fa2;
undefined2 DAT_400026ec;
undefined2 DAT_40008fa4;
undefined2 DAT_400026ee;
undefined2 DAT_40008fa6;
undefined2 DAT_400027cc;
undefined2 DAT_40008fa8;
undefined2 DAT_400027ce;
undefined2 DAT_40008faa;
undefined2 DAT_400028ac;
undefined2 DAT_40008fac;
undefined2 DAT_400028ae;
undefined2 DAT_40008fae;
undefined2 DAT_4000298c;
undefined2 DAT_40009042;
undefined2 DAT_4000298e;
undefined2 DAT_40009044;
undefined2 DAT_40002a6c;
undefined2 DAT_40009046;
undefined2 DAT_40002a6e;
undefined1 DAT_400023d4;
undefined1 DAT_400023e4;
undefined1 DAT_400023e5;
undefined2 DAT_400023e6;
undefined2 DAT_400023e8;
undefined2 DAT_400023ea;
short DAT_400024b0;
byte DAT_40008fe2;
short DAT_400024b2;
byte DAT_40008fe3;
short DAT_40001c7e;
short DAT_40001c80;
pointer PTR_DAT_40001338;
undefined DAT_400014b0;
uint8_t DAT_40002ada;
uint8_t DAT_40002ae4;
uint8_t DAT_40002aee;
uint8_t DAT_40002af8;
uint8_t DAT_40002b02;
uint8_t DAT_40002b0c;
uint8_t DAT_40002b16;
uint8_t DAT_40002b20;
uint8_t DAT_40002b2a;
uint8_t DAT_40002b34;
uint8_t DAT_40002b3e;
uint8_t DAT_40002b48;
uint8_t DAT_40002b52;
uint8_t DAT_40002b5c;
uint8_t DAT_40002b66;
uint8_t DAT_40002b70;
uint8_t DAT_40002b7a;
uint8_t DAT_40002b84;
char DAT_40009014;
undefined1 DAT_40002ba1;
byte DAT_40008ff1;
byte DAT_40001c89;
char DAT_40001c8b;
byte DAT_40001c8a;
undefined1 DAT_0008dfe8;
undefined1 DAT_0008dfea;
undefined1 DAT_0008dfed;
ushort DAT_40001c8c;
byte DAT_4000903c;
byte DAT_400014ba;
short DAT_40001c96;
char DAT_40001c9c;
char DAT_400014bf;
undefined1 clutch_learn_state;
byte DAT_400014bd;
undefined1 clutch_learn_slip_target;
byte DAT_40008fe8;
undefined1 clutch_learn_settle_counter;
byte DAT_40008fe9;
byte DAT_400014bc;
undefined2 clutch_learn_saved_demand;
byte DAT_40001c94;
ushort DAT_40001c98;
undefined2 DAT_40001c9a;
byte DAT_400014c0;
byte DAT_40001ca8;
byte DAT_40001ca9;
byte DAT_400014bb;
char DAT_400014be;
int DAT_40001c90;
byte DAT_400014c1;
pointer PTR_DAT_40001348;
pointer PTR_DAT_40001368;
pointer PTR_DAT_40001388;
undefined DAT_40001ca0;
uint8_t[8] s__400097be;
uint8_t[8] s_',>K_400097c6;
uint8_t[8] s__400097fe;
uint8_t[8] s_!#.N_40009806;
pointer PTR_DAT_0008e060;
undefined1 CAL_shift_adapt_hysteresis_step;
byte DAT_4000904e;
ushort DAT_4000904c;
undefined DAT_40001c20;
undefined DAT_40001c28;
byte DAT_40009024;
undefined DAT_40001cb0;
byte DAT_40001bff;
byte DAT_400014b8;
undefined DAT_40001c30;
byte DAT_4000904b;
byte DAT_400014b9;
undefined DAT_4000244a;
undefined DAT_400024ae;
int DAT_40006428;
undefined4 DAT_40006420;
undefined4 DAT_40006424;
undefined4 DAT_40006428;
undefined *PTR_DAT_400014c8;
undefined DAT_fffffffe;

int init(EVP_PKEY_CTX *ctx)

{
  ulonglong uVar1;
  longlong lVar2;
  longlong in_r4;
  ulonglong uVar3;
  ulonglong in_MSR;
  char in_spr203;
  
  REG_FLASH_BIUAPR = 0xffffffff;
  if (in_spr203 != '\0') {
    enable_debug_tracing(in_MSR | 0x2000000);
  }
  init_hardware_timers();
  init_ram_pattern_fill();
  install_intc_vector___();
  init_spr();
  init_debug_core();
  init_r2_and_r13();
  data_segment_setup___();
  init_siu_ebi_segment();
  uVar1 = main();
  uVar3 = uVar1 & 0xfffffffffffffff1;
  lVar2 = uVar1 - uVar3;
  in_r4 = in_r4 + lVar2;
  do {
    dataCacheBlockStore(uVar3);
    sync(0);
    instructionCacheBlockInvalidate(uVar3);
    uVar3 = uVar3 + 8;
    in_r4 = in_r4 + -8;
  } while (-1 < in_r4);
  instructionSynchronize();
  return (int)lVar2;
}



void reset_data_cache(ulonglong param_1,longlong param_2)

{
  ulonglong uVar1;
  
  uVar1 = param_1 & 0xfffffffffffffff1;
  param_2 = param_2 + (param_1 - uVar1);
  do {
    dataCacheBlockStore(uVar1);
    sync(0);
    instructionCacheBlockInvalidate(uVar1);
    uVar1 = uVar1 + 8;
    param_2 = param_2 + -8;
  } while (-1 < param_2);
  instructionSynchronize();
  return;
}



// WARNING: Removing unreachable block (ram,0x000401c0)

void enable_debug_tracing(void)

{
                    // WARNING: Do nothing block with infinite loop
  do {
  } while( true );
}



void poll_until_ready__(void)

{
  uint uVar1;
  undefined *puVar2;
  
  puVar2 = &DAT_00001770;
  do {
    puVar2 = puVar2 + -1;
    if (puVar2 == (undefined *)0x0) {
      DAT_c3fd8b00 = 0x80000000;
      REG_SIU_SRCR = 0x80000000;
      return;
    }
    uVar1 = REG_FMPLL_SYNSR;
  } while ((uVar1 & 8) == 0);
  return;
}



void init_hardware_timers(void)

{
  undefined8 in_r0;
  ulonglong in_spr203;
  
  if ((in_spr203 & 0xff) != 0) {
    TLBRead();
    sync(0);
    in_r0 = TLBWrite(in_r0,in_r0,0);
    instructionSynchronize();
  }
  init_fmpll();
  if ((in_spr203 & 0xff) != 0) {
    sync(0);
    TLBWrite(in_r0,in_r0,0);
    instructionSynchronize();
  }
  return;
}



void init_fmpll(void)

{
  uint *puVar1;
  
  puVar1 = &REG_FMPLL_SYNCR;
  REG_FMPLL_SYNCR = 0x1040000;
  sync(0);
  REG_FMPLL_SYNCR = 0x3040000;
  sync(0);
  poll_until_ready__();
  *puVar1 = *puVar1 & 0xfffcffff | 0x6000;
  return;
}



void init_pll_high_speed(void)

{
  uint *puVar1;
  
  puVar1 = &REG_FMPLL_SYNCR;
  REG_FMPLL_SYNCR = 0x41140000;
  sync(0);
  REG_FMPLL_SYNCR = 0x41040000;
  sync(0);
  poll_until_ready__();
  *puVar1 = 0x43040000;
  sync(0);
  poll_until_ready__();
  *puVar1 = 0x46040000;
  sync(0);
  poll_until_ready__();
  *puVar1 = *puVar1 & 0xfffcffff | 0x6000;
  return;
}



void init_pll_low_speed(void)

{
  uint *puVar1;
  
  puVar1 = &REG_FMPLL_SYNCR;
  REG_FMPLL_SYNCR = 0x1040000;
  sync(0);
  REG_FMPLL_SYNCR = 0x2040000;
  sync(0);
  poll_until_ready__();
  *puVar1 = 0x12040000;
  sync(0);
  poll_until_ready__();
  *puVar1 = 0x17040000;
  sync(0);
  poll_until_ready__();
  *puVar1 = 0x1e840000;
  sync(0);
  poll_until_ready__();
  *puVar1 = *puVar1 & 0xfffcffff | 0x6000;
  return;
}



void init_ram_pattern_fill
               (undefined *param_1,undefined *param_2,undefined8 param_3,undefined *param_4,
               undefined *param_5,undefined *param_6,undefined *param_7,undefined *param_8)

{
  undefined *in_r0;
  undefined **ppuVar1;
  undefined *in_r11;
  undefined *in_r12;
  undefined *unaff_r14;
  undefined *unaff_r15;
  undefined *unaff_r16;
  undefined *unaff_r17;
  undefined *unaff_r18;
  undefined *unaff_r19;
  undefined *unaff_r20;
  undefined *unaff_r21;
  undefined *unaff_r22;
  undefined *unaff_r23;
  undefined *unaff_r24;
  undefined *unaff_r25;
  undefined *unaff_r26;
  undefined *unaff_r27;
  undefined *unaff_r28;
  undefined *unaff_r29;
  undefined *unaff_r30;
  undefined *unaff_r31;
  longlong lVar2;
  
  lVar2 = 0x200;
  ppuVar1 = &switchD_00043604::switchdataD_40000000;
  do {
    *ppuVar1 = in_r0;
    ppuVar1[1] = (undefined *)register0x0000000c;
    ppuVar1[2] = &DAT_00009cc0;
    ppuVar1[3] = param_1;
    ppuVar1[4] = param_2;
    ppuVar1[5] = (undefined *)ppuVar1;
    ppuVar1[6] = param_4;
    ppuVar1[7] = param_5;
    ppuVar1[8] = param_6;
    ppuVar1[9] = param_7;
    ppuVar1[10] = param_8;
    ppuVar1[0xb] = in_r11;
    ppuVar1[0xc] = in_r12;
    ppuVar1[0xd] = &DAT_400093a8;
    ppuVar1[0xe] = unaff_r14;
    ppuVar1[0xf] = unaff_r15;
    ppuVar1[0x10] = unaff_r16;
    ppuVar1[0x11] = unaff_r17;
    ppuVar1[0x12] = unaff_r18;
    ppuVar1[0x13] = unaff_r19;
    ppuVar1[0x14] = unaff_r20;
    ppuVar1[0x15] = unaff_r21;
    ppuVar1[0x16] = unaff_r22;
    ppuVar1[0x17] = unaff_r23;
    ppuVar1[0x18] = unaff_r24;
    ppuVar1[0x19] = unaff_r25;
    ppuVar1[0x1a] = unaff_r26;
    ppuVar1[0x1b] = unaff_r27;
    ppuVar1[0x1c] = unaff_r28;
    ppuVar1[0x1d] = unaff_r29;
    ppuVar1[0x1e] = unaff_r30;
    ppuVar1[0x1f] = unaff_r31;
    ppuVar1 = ppuVar1 + 0x20;
    lVar2 = lVar2 + -1;
  } while (lVar2 != 0);
  return;
}



void install_intc_vector___(void)

{
  undefined4 *dest;
  code *source;
  longlong lVar1;
  
  lVar1 = 3;
  source = intc_setup_safe_write;
  dest = (undefined4 *)&SUB_4000f000;
  do {
    *dest = *(undefined4 *)source;
    dest = dest + 1;
    source = source + 4;
    lVar1 = lVar1 + -1;
  } while (lVar1 != 0);
  (*(code *)&SUB_4000f000)();
  return;
}



// WARNING: Removing unreachable block (ram,0x000404d8)
// WARNING: Removing unreachable block (ram,0x00040508)

void init_debug_core(void)

{
  char in_spr203;
  ulonglong in_DBCR0;
  
  if (in_spr203 != '\0') {
    do {
    } while ((in_DBCR0 & 2) == 2);
    sync(0);
    instructionSynchronize();
    do {
    } while( true );
  }
  return;
}



void init_r2_and_r13(void)

{
  return;
}



void data_segment_setup___(void)

{
  undefined1 *puVar1;
  longlong lVar2;
  undefined1 *puVar3;
  
  lVar2 = 0x14cc;
  puVar3 = (undefined1 *)0x8e077;
  puVar1 = (undefined1 *)0x3fffffff;
  do {
    puVar3 = puVar3 + 1;
    puVar1 = puVar1 + 1;
    *puVar1 = *puVar3;
    lVar2 = lVar2 + -1;
  } while (lVar2 != 0);
  return;
}



undefined4 * init_spr(void)

{
  undefined8 in_r0;
  undefined8 uVar1;
  char in_spr203;
  
  uVar1 = TLBWrite(in_r0,in_r0,0);
  uVar1 = TLBWrite(uVar1,uVar1,0);
  sync(0);
  uVar1 = TLBWrite(uVar1,uVar1,0);
  instructionSynchronize();
  uVar1 = TLBWrite(uVar1,uVar1,0);
  uVar1 = TLBWrite(uVar1,uVar1,0);
  uVar1 = TLBWrite(uVar1,uVar1,0);
  uVar1 = TLBWrite(uVar1,uVar1,0);
  uVar1 = TLBWrite(uVar1,uVar1,0);
  uVar1 = TLBWrite(uVar1,uVar1,0);
  uVar1 = TLBWrite(uVar1,uVar1,0);
  uVar1 = TLBWrite(uVar1,uVar1,0);
  if (in_spr203 != '\0') {
    uVar1 = TLBWrite(uVar1,uVar1,0);
  }
  uVar1 = TLBWrite(uVar1,uVar1,0);
  TLBWrite(uVar1,uVar1,0);
  return &DAT_000886c4;
}



void init_segment_data(ulonglong param_1,ulonglong param_2,undefined8 param_3)

{
  if (((int)param_3 != 0) && ((param_1 & 0xffffffff) != (param_2 & 0xffffffff))) {
    libc_memcpy();
    reset_data_cache(param_1,param_3);
  }
  return;
}



void init_segment_bss(undefined8 param_1,undefined8 param_2)

{
  if ((int)param_2 == 0) {
    return;
  }
  memset_and_return(param_1,0,param_2);
  return;
}



void init_segment(void)

{
  struct_segment_data *data;
  struct_segment_bss *bss;
  
  for (data = segment_data;
      ((data->src != (undefined *)0x0 || (data->dest != (undefined *)0x0)) || (data->size != 0));
      data = data + 1) {
    init_segment_data(data->dest,data->src,data->size);
  }
  for (bss = segment_bss; (bss->dest != (undefined *)0x0 || (bss->size != 0)); bss = bss + 1) {
    init_segment_bss(bss->dest,bss->size);
  }
  return;
}



void libc_memcpy(uint param_1,uint param_2,int param_3)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  
  if (param_1 <= param_2) {
    puVar1 = (undefined1 *)(param_2 - 1);
    puVar2 = (undefined1 *)(param_1 - 1);
    param_3 = param_3 + 1;
    while( true ) {
      param_3 = param_3 + -1;
      if (param_3 == 0) break;
      puVar1 = puVar1 + 1;
      puVar2 = puVar2 + 1;
      *puVar2 = *puVar1;
    }
    return;
  }
  puVar1 = (undefined1 *)(param_2 + param_3);
  puVar2 = (undefined1 *)(param_1 + param_3);
  param_3 = param_3 + 1;
  while( true ) {
    param_3 = param_3 + -1;
    if (param_3 == 0) break;
    puVar1 = puVar1 + -1;
    puVar2 = puVar2 + -1;
    *puVar2 = *puVar1;
  }
  return;
}



void * memset(void *__s,int __c,size_t __n)

{
  int iVar1;
  uint uVar2;
  ulonglong uVar3;
  longlong lVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  uint uVar7;
  
  uVar5 = (ulonglong)(int)__n;
  uVar2 = __c & 0xff;
  uVar6 = (longlong)(int)__s - 1;
  uVar7 = uVar2;
  if (0x1f < __n) {
    uVar3 = ~uVar6 & 3;
    if (uVar3 != 0) {
      uVar5 = uVar5 - uVar3;
      do {
        uVar3 = uVar3 - 1;
        uVar6 = uVar6 + 1;
        *(undefined1 *)uVar6 = (char)__c;
      } while (uVar3 != 0);
    }
    uVar3 = (uVar5 << 0x20) >> 0x25;
    uVar7 = uVar2 | (__c & 0xffU) << 8 | __c << 0x18 | (__c & 0xffU) << 0x10;
    if (uVar2 == 0) {
      uVar7 = uVar2;
    }
    lVar4 = uVar6 - 3;
    for (; uVar3 != 0; uVar3 = uVar3 - 1) {
      iVar1 = (int)lVar4;
      *(uint *)(iVar1 + 4) = uVar7;
      *(uint *)(iVar1 + 8) = uVar7;
      *(uint *)(iVar1 + 0xc) = uVar7;
      *(uint *)(iVar1 + 0x10) = uVar7;
      *(uint *)(iVar1 + 0x14) = uVar7;
      *(uint *)(iVar1 + 0x18) = uVar7;
      *(uint *)(iVar1 + 0x1c) = uVar7;
      lVar4 = lVar4 + 0x20;
      *(uint *)lVar4 = uVar7;
    }
    for (uVar6 = (uVar5 << 0x20) >> 0x22 & 7; uVar6 != 0; uVar6 = uVar6 - 1) {
      lVar4 = lVar4 + 4;
      *(uint *)lVar4 = uVar7;
    }
    __s = (void *)lVar4;
    uVar6 = lVar4 + 3;
    uVar5 = uVar5 & 3;
  }
  if ((int)uVar5 != 0) {
    do {
      uVar5 = uVar5 - 1;
      uVar6 = uVar6 + 1;
      *(undefined1 *)uVar6 = (char)uVar7;
    } while (uVar5 != 0);
    return __s;
  }
  return __s;
}



undefined8 memset_and_return(undefined8 param_1,int param_2,size_t param_3)

{
  memset((void *)param_1,param_2,param_3);
  return param_1;
}



void FUN_00040a14(undefined4 *param_1,undefined4 *param_2)

{
  *param_2 = &DAT_00009cc0;
  *param_1 = &PTR_PTR_00091eec;
  return;
}



// Default/spurious INTC vector target: `b .` spin trap. Filled into all unused entries of
// INTC_vector_table.

void intc_default_isr(void)

{
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



void FUN_00040b04(void)

{
  return;
}



void intc_config_swvector(void)

{
  uint uVar1;
  
  uVar1 = REG_INTC_MCR;
  REG_INTC_MCR = uVar1 & 0xfffffffe;
  uVar1 = REG_INTC_MCR;
  REG_INTC_MCR = uVar1 & 0xffffffdf;
  REG_INTC_IACKR = 0x8f800;
  return;
}



void swint_isr_vec004(void)

{
  DAT_400014d0 = DAT_400014d0 + 1;
  REG_INTC_SSCIR4 = 1;
  return;
}



void intc_enable_external(void)

{
  uint uVar1;
  
  uVar1 = REG_INTC_CPR;
  REG_INTC_CPR = uVar1 & 0xfffffff0;
  WriteExternalEnableImmediate(1);
  return;
}



void init_intc(void)

{
  FUN_00040b04();
  intc_config_swvector();
  intc_enable_external();
  return;
}



void init_intc_1(void)

{
  uint uVar1;
  
  uVar1 = REG_INTC_MCR;
  REG_INTC_MCR = uVar1 & 0xfffffffe;
  uVar1 = REG_INTC_MCR;
  REG_INTC_MCR = uVar1 & 0xffffffdf;
  uVar1 = REG_INTC_CPR;
  REG_INTC_CPR = uVar1 & 0xfffffff0;
  WriteExternalEnableImmediate(1);
  return;
}



void set_spr_IVOR2(void)

{
  WriteExternalEnableImmediate(0);
  return;
}



void init_siu_ebi_segment(void)

{
  init_siu();
  init_siu_pcr();
  init_ebi_unknown();
  init_segment();
  return;
}



void init_siu(void)

{
  REG_SIU_PCR214 = 0;
  REG_SIU_PCR229 = 0x2c0;
  REG_SIU_ECCR = 0x3f01;
  return;
}



void init_siu_pcr(void)

{
  init_siu_pcr1(0x400,0,0,0x40,0,0,0,0,0);
  init_siu_pcr2(0x400,0,0,0x40,0,0,0,0,0,0);
  init_siu_pcr2(0x400,0,0,0x40,0,0,0,0,0,0x10);
  init_siu_pcr3(0x400,0,0,0x40,0,0,0,0,0,0x3e,2);
  init_siu_pcr3(0x400,0,0,0x40,0,0,0,2,1,0x40,4);
  init_siu_pcr3(0x400,0,0,0x40,0,0,0,2,1,0x44,2);
  init_siu_pcr3(0x400,0,0,0x40,0,0,0,2,1,0,4);
  return;
}



void init_ebi_unknown(void)

{
  FUN_00041224(0,0,0,0,0,0x800,0,0);
  FUN_0004124c(0,0x3ff80000,0,0x40,0,0,2,1);
  FUN_00041278(0,0xfffffffffff80000,0,0);
  FUN_0004124c(1,0x20000000,0,0,0,0,2,1);
  FUN_00041278(1,0xffffffffffc00000,0x40,0);
  FUN_0004124c(2,0x20800000,0,0x40,0,0,2,0);
  FUN_00041278(2,0xfffffffffff80000,0x40,2);
  FUN_0004124c(3,0x30000000,0,0x40,0,0,0,0);
  FUN_00041278(3,0xfffffffffff80000,0x40,2);
  return;
}



void init_siu_pcr1(ushort param_1,ushort param_2,ushort param_3,ushort param_4,ushort param_5,
                  ushort param_6,ushort param_7,ushort param_8,ushort param_9)

{
  byte bVar1;
  
  for (bVar1 = 4; bVar1 < 0x1c; bVar1 = bVar1 + 1) {
    (&REG_SIU_PCR0)[bVar1] =
         param_9 | param_8 | param_7 | param_6 | param_5 | param_4 | param_3 | param_1 | param_2;
  }
  return;
}



void init_siu_pcr2(ushort param_1,ushort param_2,ushort param_3,ushort param_4,ushort param_5,
                  ushort param_6,ushort param_7,ushort param_8,ushort param_9,byte param_10)

{
  uint uVar1;
  
  for (uVar1 = param_10 + 0x1c & 0xff; (uVar1 & 0xff) < param_10 + 0x2c; uVar1 = uVar1 + 1) {
    (&REG_SIU_PCR0)[uVar1 & 0xff] =
         param_9 | param_8 | param_7 | param_6 | param_5 | param_4 | param_3 | param_1 | param_2;
  }
  return;
}



void init_siu_pcr3(ushort param_1,ushort param_2,ushort param_3,ushort param_4,ushort param_5,
                  ushort param_6,ushort param_7,ushort param_8,ushort param_9,byte param_10,
                  byte param_11)

{
  uint uVar1;
  
  for (uVar1 = (uint)param_10; (uVar1 & 0xff) < (uint)param_10 + (uint)param_11; uVar1 = uVar1 + 1)
  {
    (&REG_SIU_PCR0)[uVar1 & 0xff] =
         param_9 | param_8 | param_7 | param_6 | param_5 | param_4 | param_3 | param_1 | param_2;
  }
  return;
}



void FUN_00041224(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6,
                 uint param_7,uint param_8)

{
  REG_EBI_MCR = param_8 | param_7 | param_6 | param_5 | param_4 | param_3 | param_1 | param_2;
  return;
}



void FUN_0004124c(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6,
                 uint param_7,uint param_8)

{
  (&REG_EBI_BR0)[(param_1 & 0xff) * 2] =
       param_8 | param_7 | param_6 | param_5 | param_4 | param_2 | param_3;
  return;
}



void FUN_00041278(uint param_1,uint param_2,uint param_3,uint param_4)

{
  (&REG_EBI_OR0)[(param_1 & 0xff) * 2] = param_4 | param_2 | param_3;
  return;
}



void init_eqADC3(void)

{
  uint uVar1;
  uint uVar2;
  ushort uVar3;
  
  uVar3 = REG_EQADC_CFCR0;
  REG_EQADC_CFCR0 = uVar3 & 0xff0f | 0x10;
  REG_EQADC_CFPR0 = 0x1000004;
  REG_EQADC_CFPR0 = 0x1000005;
  REG_EQADC_CFPR0 = 0x3000004;
  REG_EQADC_CFPR0 = 0x83000005;
  uVar3 = REG_EQADC_CFCR0;
  REG_EQADC_CFCR0 = uVar3 & 0xfbff | 0x400;
  do {
    uVar1 = REG_EQADC_FISR0;
  } while ((uVar1 >> 0x11 & 1) == 0);
  uVar1 = REG_EQADC_RFPR0;
  do {
    uVar2 = REG_EQADC_FISR0;
  } while ((uVar2 >> 0x11 & 1) == 0);
  uVar2 = REG_EQADC_RFPR0;
  DAT_400014dc = uVar1 << 0x10 | uVar2;
  do {
    uVar1 = REG_EQADC_FISR0;
  } while ((uVar1 >> 0x11 & 1) == 0);
  uVar1 = REG_EQADC_RFPR0;
  do {
    uVar2 = REG_EQADC_FISR0;
  } while ((uVar2 >> 0x11 & 1) == 0);
  uVar2 = REG_EQADC_RFPR0;
  DAT_400014d8 = uVar1 << 0x10 | uVar2;
  uVar1 = REG_EQADC_FISR0;
  REG_EQADC_FISR0 = uVar1 & 0xfffdffff | 0x20000;
  uVar3 = REG_EQADC_CFCR0;
  REG_EQADC_CFCR0 = uVar3 & 0xff0f;
  REG_EQADC_IDCR0 = 0;
  uVar1 = REG_EQADC_FISR0;
  REG_EQADC_FISR0 = uVar1 & 0xefffffff | 0x10000000;
  uVar3 = REG_EQADC_CFCR0;
  REG_EQADC_CFCR0 = uVar3 & 0xfdff | 0x200;
  do {
    uVar1 = REG_EQADC_CFSR;
  } while (uVar1 >> 0x1e != 0);
  return;
}



void FUN_00041408(uint param_1,uint param_2,undefined2 *param_3,undefined2 *param_4)

{
  *param_3 = (short)(0x10000000 / (int)((param_2 & 0xffff) - (param_1 & 0xffff)));
  *param_4 = (short)((int)(((param_2 & 0xffff) + ((param_1 & 0xffff) * 0x2000 - (param_1 & 0xffff)))
                          * 2) / (int)((param_1 & 0xffff) - (param_2 & 0xffff)));
  return;
}



undefined8 init_eqADC2(uint param_1)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  short local_20;
  short local_1e [15];
  
  uVar1 = REG_EQADC_CFCR0;
  REG_EQADC_CFCR0 = uVar1 & 0xff0f | 0x10;
  uVar1 = REG_EQADC_CFCR0;
  REG_EQADC_CFCR0 = uVar1 & 0xfbff | 0x400;
  DAT_40001d10 = 0;
  DAT_40001d60 = 0;
  DAT_40001d24 = 0;
  DAT_40001d4c = 0;
  DAT_40001d38 = 0;
  uVar2 = REG_EQADC_FISR0;
  REG_EQADC_FISR0 = uVar2 & 0xfffdffff | 0x20000;
  uVar2 = REG_EQADC_FISR1;
  REG_EQADC_FISR1 = uVar2 & 0xfffdffff | 0x20000;
  uVar2 = REG_EQADC_FISR2;
  REG_EQADC_FISR2 = uVar2 & 0xfffdffff | 0x20000;
  uVar2 = REG_EQADC_FISR3;
  REG_EQADC_FISR3 = uVar2 & 0xfffdffff | 0x20000;
  uVar2 = REG_EQADC_FISR4;
  REG_EQADC_FISR4 = uVar2 & 0xfffdffff | 0x20000;
  for (iVar7 = 0; iVar7 < 100; iVar7 = iVar7 + 1) {
    REG_EQADC_CFPR0 = param_1 * 0x2000000 + 0x42b00;
    REG_EQADC_CFPR0 = param_1 * 0x2000000 + 0x142c00;
    REG_EQADC_CFPR0 = param_1 * 0x2000000 + 0x242a00;
    REG_EQADC_CFPR0 = param_1 * 0x2000000 + 0x342900;
    REG_EQADC_CFPR0 = param_1 * 0x2000000 + 0x442800;
    do {
      uVar2 = REG_EQADC_FISR0;
    } while ((uVar2 >> 0x11 & 1) == 0);
    DAT_40001d64 = REG_EQADC_RFPR0;
    do {
      uVar2 = REG_EQADC_FISR1;
    } while ((uVar2 >> 0x11 & 1) == 0);
    DAT_40001d50 = REG_EQADC_RFPR1;
    do {
      uVar2 = REG_EQADC_FISR2;
    } while ((uVar2 >> 0x11 & 1) == 0);
    DAT_40001d28 = REG_EQADC_RFPR2;
    do {
      uVar2 = REG_EQADC_FISR3;
    } while ((uVar2 >> 0x11 & 1) == 0);
    DAT_40001d3c = REG_EQADC_RFPR3;
    do {
      uVar2 = REG_EQADC_FISR4;
    } while ((uVar2 >> 0x11 & 1) == 0);
    DAT_40001d14 = REG_EQADC_RFPR4;
    uVar2 = REG_EQADC_FISR0;
    REG_EQADC_FISR0 = uVar2 & 0xfffdffff | 0x20000;
    uVar2 = REG_EQADC_FISR1;
    REG_EQADC_FISR1 = uVar2 & 0xfffdffff | 0x20000;
    uVar2 = REG_EQADC_FISR2;
    REG_EQADC_FISR2 = uVar2 & 0xfffdffff | 0x20000;
    uVar2 = REG_EQADC_FISR3;
    REG_EQADC_FISR3 = uVar2 & 0xfffdffff | 0x20000;
    uVar2 = REG_EQADC_FISR4;
    REG_EQADC_FISR4 = uVar2 & 0xfffdffff | 0x20000;
    uVar2 = DAT_40001d64;
    if (DAT_40001d64 < DAT_40001d60) {
      uVar2 = DAT_40001d60;
    }
    uVar3 = DAT_40001d50;
    if (DAT_40001d50 < DAT_40001d4c) {
      uVar3 = DAT_40001d4c;
    }
    uVar4 = DAT_40001d28;
    if (DAT_40001d28 < DAT_40001d24) {
      uVar4 = DAT_40001d24;
    }
    uVar5 = DAT_40001d3c;
    if (DAT_40001d3c < DAT_40001d38) {
      uVar5 = DAT_40001d38;
    }
    uVar6 = DAT_40001d14;
    if (DAT_40001d14 < DAT_40001d10) {
      uVar6 = DAT_40001d10;
    }
    DAT_40001d10 = uVar6;
    DAT_40001d24 = uVar4;
    DAT_40001d38 = uVar5;
    DAT_40001d4c = uVar3;
    DAT_40001d60 = uVar2;
    FUN_00047ed4();
  }
  if ((param_1 & 0xffff) == 0) {
    DAT_40001d74 = (undefined2)(DAT_40001d38 >> 4);
    DAT_40001d76 = (undefined2)(DAT_40001d4c >> 4);
    DAT_40001d78 = (undefined2)(DAT_40001d24 >> 4);
    DAT_40001d7a = (undefined2)(DAT_40001d60 >> 4);
    DAT_40001d7c = (undefined2)(DAT_40001d10 >> 4);
  }
  else {
    DAT_40001d7e = (undefined2)(DAT_40001d38 >> 4);
    DAT_40001d80 = (undefined2)(DAT_40001d4c >> 4);
    DAT_40001d82 = (undefined2)(DAT_40001d24 >> 4);
    DAT_40001d84 = (undefined2)(DAT_40001d60 >> 4);
    DAT_40001d86 = (undefined2)(DAT_40001d10 >> 4);
  }
  FUN_00041408(DAT_40001d38 & 0xffff,DAT_40001d10 & 0xffff,local_1e,&local_20);
  DAT_400014e8 = (int)local_1e[0] & 0x7fff;
  DAT_400014e4 = (int)local_20 & 0x3fff;
  DAT_400014e2 = (short)DAT_400014e8;
  DAT_400014e0 = (short)DAT_400014e4;
  REG_EQADC_CFPR0 = DAT_400014e8 << 8 | 4 | param_1 << 0x19;
  REG_EQADC_CFPR0 = DAT_400014e4 << 8 | 5 | param_1 << 0x19;
  return 1;
}



void FUN_000419e8(void)

{
  DAT_40002038 = 2;
  DAT_4000203c = 3;
  DAT_40002040 = 0x800101;
  DAT_40002044 = 0x2000002;
  DAT_40002048 = 0x2000003;
  DAT_4000204c = 0x82800c01;
  return;
}



void init_eqADC(void)

{
  ushort uVar1;
  uint uVar2;
  
  uVar1 = REG_EQADC_CFCR0;
  REG_EQADC_CFCR0 = uVar1 & 0xff0f;
  REG_EQADC_IDCR0 = 0;
  uVar2 = REG_EQADC_FISR0;
  REG_EQADC_FISR0 = uVar2 & 0xefffffff | 0x10000000;
  uVar1 = REG_EQADC_CFCR0;
  REG_EQADC_CFCR0 = uVar1 & 0xfdff | 0x200;
  do {
    uVar2 = REG_EQADC_CFSR;
  } while (uVar2 >> 0x1e != 0);
  uVar2 = REG_EQADC_FISR0;
  REG_EQADC_FISR0 = uVar2 & 0xfffdffff | 0x20000;
  uVar1 = REG_EQADC_CFCR1;
  REG_EQADC_CFCR1 = uVar1 & 0xff0f;
  REG_EQADC_IDCR1 = 0;
  uVar2 = REG_EQADC_FISR1;
  REG_EQADC_FISR1 = uVar2 & 0xefffffff | 0x10000000;
  uVar1 = REG_EQADC_CFCR1;
  REG_EQADC_CFCR1 = uVar1 & 0xfdff | 0x200;
  do {
    uVar2 = REG_EQADC_CFSR;
  } while ((uVar2 >> 0x1c & 3) != 0);
  uVar2 = REG_EQADC_FISR1;
  REG_EQADC_FISR1 = uVar2 & 0xfffdffff | 0x20000;
  uVar1 = REG_EQADC_CFCR2;
  REG_EQADC_CFCR2 = uVar1 & 0xff0f;
  REG_EQADC_IDCR2 = 0;
  uVar2 = REG_EQADC_FISR2;
  REG_EQADC_FISR2 = uVar2 & 0xefffffff | 0x10000000;
  uVar1 = REG_EQADC_CFCR2;
  REG_EQADC_CFCR2 = uVar1 & 0xfdff | 0x200;
  do {
    uVar2 = REG_EQADC_CFSR;
  } while ((uVar2 >> 0x1a & 3) != 0);
  uVar2 = REG_EQADC_FISR2;
  REG_EQADC_FISR2 = uVar2 & 0xfffdffff | 0x20000;
  uVar1 = REG_EQADC_CFCR3;
  REG_EQADC_CFCR3 = uVar1 & 0xff0f;
  REG_EQADC_IDCR3 = 0;
  uVar2 = REG_EQADC_FISR3;
  REG_EQADC_FISR3 = uVar2 & 0xefffffff | 0x10000000;
  uVar1 = REG_EQADC_CFCR3;
  REG_EQADC_CFCR3 = uVar1 & 0xfdff | 0x200;
  do {
    uVar2 = REG_EQADC_CFSR;
  } while ((uVar2 >> 0x18 & 3) != 0);
  uVar2 = REG_EQADC_FISR3;
  REG_EQADC_FISR3 = uVar2 & 0xfffdffff | 0x20000;
  uVar1 = REG_EQADC_CFCR4;
  REG_EQADC_CFCR4 = uVar1 & 0xff0f;
  REG_EQADC_IDCR4 = 0;
  uVar2 = REG_EQADC_FISR4;
  REG_EQADC_FISR4 = uVar2 & 0xefffffff | 0x10000000;
  uVar1 = REG_EQADC_CFCR4;
  REG_EQADC_CFCR4 = uVar1 & 0xfdff | 0x200;
  do {
    uVar2 = REG_EQADC_CFSR;
  } while ((uVar2 >> 0x16 & 3) != 0);
  uVar2 = REG_EQADC_FISR4;
  REG_EQADC_FISR4 = uVar2 & 0xfffdffff | 0x20000;
  uVar1 = REG_EQADC_CFCR5;
  REG_EQADC_CFCR5 = uVar1 & 0xff0f;
  REG_EQADC_IDCR5 = 0;
  uVar2 = REG_EQADC_FISR5;
  REG_EQADC_FISR5 = uVar2 & 0xefffffff | 0x10000000;
  uVar1 = REG_EQADC_CFCR5;
  REG_EQADC_CFCR5 = uVar1 & 0xfdff | 0x200;
  do {
    uVar2 = REG_EQADC_CFSR;
  } while ((uVar2 >> 0x14 & 3) != 0);
  uVar2 = REG_EQADC_FISR5;
  REG_EQADC_FISR5 = uVar2 & 0xfffdffff | 0x20000;
  FUN_000419e8();
  REG_EQADC_MCR = 0;
  REG_EQADC_NMSFR = 0;
  REG_EQADC_ETDFR = 6;
  uVar1 = REG_EQADC_CFCR5;
  REG_EQADC_CFCR5 = uVar1 & 0xff0f | 0x10;
  REG_EQADC_IDCR5 = 0x300;
  uVar1 = REG_EQADC_CFCR5;
  REG_EQADC_CFCR5 = uVar1 & 0xfbff | 0x400;
  do {
    uVar2 = REG_EQADC_CFSR;
  } while ((uVar2 >> 0x14 & 3) != 2);
  uVar1 = REG_EQADC_CFCR5;
  REG_EQADC_CFCR5 = uVar1 & 0xff0f;
  REG_EQADC_IDCR5 = 0;
  uVar2 = REG_EQADC_FISR5;
  REG_EQADC_FISR5 = uVar2 & 0xefffffff | 0x10000000;
  uVar1 = REG_EQADC_CFCR5;
  REG_EQADC_CFCR5 = uVar1 & 0xfdff | 0x200;
  return;
}



void FUN_00041dcc(void)

{
  ushort uVar1;
  
  DAT_400020f0 = 0x1440700;
  DAT_400020f4 = 0x1440800;
  DAT_400020f8 = 0x1440900;
  DAT_400020fc = 0x1440a00;
  DAT_40002100 = 0x1440b00;
  DAT_40002104 = 0x1440c00;
  DAT_40002108 = 0x80440d00;
  uVar1 = REG_EQADC_CFCR4;
  REG_EQADC_CFCR4 = uVar1 & 0xff0f | 0x90;
  REG_EQADC_IDCR4 = 0x303;
  uVar1 = REG_EQADC_CFCR4;
  REG_EQADC_CFCR4 = uVar1 & 0xfbff | 0x400;
  return;
}



void init_eqADC5(void)

{
  ushort uVar1;
  
  DAT_40002038 = 0x3500000;
  DAT_4000203c = 0x3500100;
  DAT_40002040 = 0x3500200;
  DAT_40002044 = 0x3500300;
  DAT_40002048 = 0x3500400;
  DAT_4000204c = 0x3500500;
  DAT_40002050 = 0x3500600;
  DAT_40002054 = 0x3500700;
  DAT_40002058 = 0x3500800;
  DAT_4000205c = 0x3500900;
  DAT_40002060 = 0x3500a00;
  DAT_40002064 = 0x3500b00;
  DAT_40002068 = 0x3500c00;
  DAT_4000206c = 0x3500d00;
  DAT_40002070 = 0x3500e00;
  DAT_40002074 = 0x3500f00;
  DAT_40002078 = 0x3501000;
  DAT_4000207c = 0x3501100;
  DAT_40002080 = 0x3501200;
  DAT_40002084 = 0x3501300;
  DAT_40002088 = 0x3501400;
  DAT_4000208c = 0x3501500;
  DAT_40002090 = 0x3501600;
  DAT_40002094 = 0x3501700;
  DAT_40002098 = 0x3501800;
  DAT_4000209c = 0x3501900;
  DAT_400020a0 = 0x3501a00;
  DAT_400020a4 = 0x3501b00;
  DAT_400020a8 = 0x3501c00;
  DAT_400020ac = 0x3501d00;
  DAT_400020b0 = 0x3501e00;
  DAT_400020b4 = 0x3501f00;
  DAT_400020b8 = 0x3502000;
  DAT_400020bc = 0x3502100;
  DAT_400020c0 = 0x3502200;
  DAT_400020c4 = 0x3502300;
  DAT_400020c8 = 0x3502400;
  DAT_400020cc = 0x3502500;
  DAT_400020d0 = 0x3502600;
  DAT_400020d4 = 0x3502700;
  DAT_400020d8 = 0x2502900;
  DAT_400020dc = 0x2502c00;
  DAT_400020e0 = 0x2502a00;
  DAT_400020e4 = 0x2502b00;
  DAT_400020e8 = 0x82502800;
  uVar1 = REG_EQADC_CFCR5;
  REG_EQADC_CFCR5 = uVar1 & 0xff0f | 0x90;
  REG_EQADC_IDCR5 = 0x303;
  uVar1 = REG_EQADC_CFCR5;
  REG_EQADC_CFCR5 = uVar1 & 0xfbff | 0x400;
  return;
}



undefined8
FUN_00042240(uint *param_1,undefined8 param_2,longlong param_3,undefined8 param_4,undefined8 param_5
            )

{
  undefined8 uVar1;
  
  param_3 = (((ulonglong)(*DAT_400015e4 >> 0x10) & 0x1f) + 1) * 0x800 - param_3;
  if ((int)param_3 < 0) {
    uVar1 = 4;
  }
  else {
    DAT_400015e4[5] = DAT_400015e4[5] & 0xbfffffff | 0x40000000;
    DAT_400015e4[6] = DAT_400015e4[6] & 0xbfffffff | 0x40000000;
    *DAT_400015e4 = *DAT_400015e4 & 0xffffffbf | 0x40;
    uVar1 = FUN_00042494(DAT_400015e0);
    FUN_000424bc(uVar1,0,param_3);
    *DAT_400015e4 = *DAT_400015e4 & 0xffffffbf;
    DAT_400015e4[3] = param_1[1];
    *DAT_400015e4 = *param_1;
    DAT_400015e4[5] = param_1[2];
    DAT_400015e4[8] = param_1[3];
    DAT_400015e4[0xb] = param_1[4];
    DAT_400015e4[6] = param_1[5];
    DAT_400015e4[0x10] = param_1[6];
    DAT_400015e4[0x13] = param_1[7];
    DAT_400015d0 = FUN_00042494(DAT_400015dc,param_4,param_5);
    uVar1 = 0;
  }
  return uVar1;
}



longlong eTPU_channel_to_address(uint param_1)

{
  return (ulonglong)DAT_400015dc +
         ((ulonglong)*(uint *)(DAT_400015e4 + (param_1 & 0xff) * 0x10 + 0x400) & 0x7ff) * 8;
}



void clear_eTPU_channel(uint param_1)

{
  int iVar1;
  
  iVar1 = DAT_400015e4 + (param_1 & 0xff) * 0x10;
  *(uint *)(iVar1 + 0x400) = *(uint *)(iVar1 + 0x400) & 0xcfffffff;
  return;
}



void FUN_000423d8(void)

{
  *DAT_400015e4 = *DAT_400015e4 & 0xfffffffe | 1;
  return;
}



int FUN_000423f0(uint param_1)

{
  int iVar1;
  
  iVar1 = DAT_400015d0;
  DAT_400015d0 = DAT_400015d0 + ((int)((param_1 & 0xffff) + 7) >> 3) * 8;
  if (DAT_400015d8 < DAT_400015d0) {
    iVar1 = 0;
  }
  return iVar1;
}



uint eTPU_read_24bit(uint param_1,int param_2)

{
  return *(uint *)((*(uint *)(DAT_400015e4 + (param_1 & 0xff) * 0x10 + 0x400) & 0x7ff) * 8 +
                   param_2 + DAT_400015d4 + -1) & 0xffffff;
}



undefined1 eTPU_read_8bit(uint param_1,int param_2)

{
  return *(undefined1 *)
          ((*(uint *)(DAT_400015e4 + (param_1 & 0xff) * 0x10 + 0x400) & 0x7ff) * 8 +
          param_2 + DAT_400015dc);
}



void FUN_00042494(undefined4 *param_1,undefined4 *param_2,longlong param_3)

{
  undefined4 uVar1;
  int iVar3;
  ulonglong uVar2;
  
  uVar2 = (ulonglong)(param_3 << 0x20) >> 0x22;
  while (iVar3 = (int)uVar2, uVar2 = uVar2 - 1, iVar3 != 0) {
    uVar1 = *param_2;
    param_2 = param_2 + 1;
    *param_1 = uVar1;
    param_1 = param_1 + 1;
  }
  return;
}



void FUN_000424bc(undefined4 *param_1,undefined4 param_2,int param_3)

{
  bool bVar1;
  
  param_3 = param_3 >> 2;
  while( true ) {
    bVar1 = param_3 == 0;
    param_3 = param_3 + -1;
    if (bVar1) break;
    *param_1 = param_2;
    param_1 = param_1 + 1;
  }
  return;
}



undefined2 adc_smooth_lowpass(int *param_1,short param_2)

{
  *param_1 = param_1[1];
  param_1[1] = (int)param_2 - (int)(short)((int)*(short *)(param_1 + 5) * *param_1 >> 0xf);
  param_1[2] = param_1[3];
  param_1[3] = param_1[4];
  param_1[4] = (int)(short)((int)*(short *)((int)param_1 + 0x16) * param_1[1] +
                            (int)*(short *)(param_1 + 6) * *param_1 >> 0xf) -
               (int)(short)((int)*(short *)((int)param_1 + 0x1a) * param_1[3] +
                            (int)*(short *)(param_1 + 7) * param_1[2] >> 0xf);
  return (short)((int)*(short *)(param_1 + 8) * param_1[3] +
                 (int)*(short *)((int)param_1 + 0x22) * param_1[2] +
                 (int)*(short *)((int)param_1 + 0x1e) * param_1[4] >> 0xf);
}



void adc_smooth_state_init
               (undefined4 *param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
               undefined2 param_5,undefined2 param_6,undefined2 param_7,undefined2 param_8,
               undefined2 param_9)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  *(undefined2 *)(param_1 + 5) = param_2;
  *(undefined2 *)((int)param_1 + 0x16) = param_3;
  *(undefined2 *)(param_1 + 6) = param_4;
  *(undefined2 *)((int)param_1 + 0x1a) = param_5;
  *(undefined2 *)(param_1 + 7) = param_6;
  *(undefined2 *)((int)param_1 + 0x1e) = param_7;
  *(undefined2 *)(param_1 + 8) = param_8;
  *(undefined2 *)((int)param_1 + 0x22) = param_9;
  return;
}



void set_dbsr(void)

{
  TBLw = 0;
  TBUw = 0;
  return;
}



void FUN_0004263c(void)

{
  return;
}



void init_ivor(void)

{
  return;
}



undefined8 read_timebase_lower(void)

{
  undefined8 uVar1;
  
  uVar1 = TBLw;
  return uVar1;
}



void FUN_000427f0(void)

{
  init_flash_ctrl();
  return;
}



void FUN_00042810(void)

{
  REG_SIU_PCR113 = 0xd00;
  REG_SIU_PCR114 = 0xd00;
  REG_SIU_PCR115 = 0x100;
  REG_SIU_PCR116 = 0x100;
  REG_SIU_PCR117 = 0x100;
  REG_SIU_PCR118 = 0x100;
  REG_SIU_PCR119 = 0x100;
  REG_SIU_PCR120 = 0x100;
  REG_SIU_PCR121 = 0x100;
  REG_SIU_PCR122 = 0x100;
  REG_SIU_PCR123 = 0x100;
  REG_SIU_PCR124 = 0x100;
  REG_SIU_PCR125 = 0xd00;
  REG_SIU_PCR126 = 0xd00;
  REG_SIU_PCR91 = 0x284;
  REG_SIU_PCR92 = 0x284;
  REG_SIU_PCR96 = 0x284;
  REG_SIU_PCR98 = 0x284;
  REG_SIU_PCR99 = 0x284;
  REG_SIU_PCR100 = 0x284;
  REG_SIU_PCR127 = 0x100;
  REG_SIU_PCR128 = 0x100;
  REG_SIU_PCR129 = 0x100;
  REG_SIU_PCR130 = 0x100;
  REG_SIU_PCR131 = 0x100;
  REG_SIU_PCR132 = 0x100;
  REG_SIU_PCR204 = 0x100;
  REG_SIU_PCR191 = 0x284;
  REG_SIU_PCR192 = 0x284;
  REG_SIU_PCR193 = 0x284;
  REG_SIU_PCR194 = 0x284;
  DAT_c3f9014e = 0x284;
  DAT_c3f90150 = 0x284;
  DAT_c3f90152 = 0x284;
  DAT_c3f90154 = 0xe84;
  DAT_c3f90156 = 0xe84;
  DAT_c3f90158 = 0xe84;
  DAT_c3f9015a = 0xe84;
  REG_SIU_PCR142 = 0xe84;
  REG_SIU_PCR143 = 0xe84;
  REG_SIU_PCR133 = 0xe84;
  REG_SIU_PCR134 = 0xe84;
  REG_SIU_PCR186 = 0xe84;
  REG_SIU_PCR185 = 0xe84;
  REG_SIU_PCR144 = 0xe84;
  REG_SIU_PCR145 = 0xe84;
  REG_SIU_PCR201 = 0x284;
  REG_SIU_PCR182 = 0x284;
  REG_SIU_PCR183 = 0x284;
  REG_SIU_PCR195 = 0x2cc;
  REG_SIU_PCR203 = 0x284;
  REG_SIU_PCR211 = 0x2cc;
  REG_SIU_PCR212 = 0x2cc;
  return;
}



void copyCAL2RAM(void)

{
  undefined2 uVar1;
  undefined2 *puVar2;
  undefined *puVar3;
  undefined2 *src_addr;
  undefined2 *target_addr;
  longlong word_count;
  
  puVar3 = &DAT_00009cc0;
  DAT_4000150b = 0x80;
  DAT_4000150a = 0x80;
  DAT_40001509 = 0;
  DAT_40001508 = 0;
  DAT_40001505 = 0x80;
  DAT_40001507 = 0;
  DAT_40001506 = 0;
  DAT_40001504 = 0;
  target_addr = (undefined2 *)0x40008e56;
  src_addr = (undefined2 *)0x1fffe;
  word_count = 0x186a;
  do {
    puVar2 = src_addr + 1;
    src_addr = src_addr + 2;
    uVar1 = *src_addr;
    target_addr[1] = *puVar2;
    target_addr = target_addr + 2;
    *target_addr = uVar1;
    word_count = word_count + -1;
  } while (word_count != 0);
  init_intc_1();
  eeprom_flash_erase_pending_flags = eeprom_flash_erase_pending_flags | 2;
  copyCOD2RAM___();
  eeprom_flash_erase_pending_flags = eeprom_flash_erase_pending_flags & 0xfd;
  set_spr_IVOR2();
  calibration_verification_number =
       CRC16(&DAT_40008e78,*(ushort *)(puVar3 + -0x8000) - 0x22 & 0xffff);
  if ((((CAL_tcu_unlock_magic[0] == 'N') && (CAL_tcu_unlock_magic[1] == 'U')) &&
      (CAL_tcu_unlock_magic[2] == 'T')) && (CAL_tcu_unlock_magic[3] == 'S')) {
    tcu_unlocked = true;
  }
  else {
    tcu_unlocked = false;
  }
  DAT_400014f2 = (undefined2)*DAT_400013a8;
  init_performance_profiling_arrays();
  return;
}



void init_obd_ii_config(void)

{
  FUN_0005d574();
  FUN_0005db1c();
  FUN_00058798();
  FUN_0005db80();
  obd_ii_set_mode06_supported_pids();
  FUN_00060f48();
  FUN_00060f6c();
  return;
}



void init_hardware(void)

{
  copyCAL2RAM();
  FUN_00058440();
  init_obd_ii_config();
  FUN_0004263c();
  init_intc_1();
  eeprom_flash_erase_pending_flags = eeprom_flash_erase_pending_flags | 1;
  FUN_00048c94();
  eeprom_flash_erase_pending_flags = eeprom_flash_erase_pending_flags & 0xfe;
  set_spr_IVOR2();
  FUN_00042810();
  init_eDMA2();
  init_eDMA2_2();
  init_eqADC();
  init_pinmux_and_iosetup();
  init_eqADC2(1);
  init_eqADC2(0);
  init_eqADC3();
  init_eqADC5();
  FUN_00041dcc();
  init_emios_mcr();
  init_emios_uc4();
  init_ivor();
  set_dbsr();
  FUN_000457b0();
  init_etpu();
  setup_etpu_pwm_outputs();
  FUN_00044dc0();
  FUN_00052034();
  FUN_000561f0();
  reset_can_rx_timeouts();
  FUN_000482b8();
  FUN_000571cc();
  trans_control_init();
  age_shift_adapt_hysteresis();
  FUN_00047930();
  FUN_00047bb8();
  FUN_000506b8();
  clear_can_logging_buffer();
  init_intc();
  return;
}



void main(void)

{
  int iVar1;
  uint uVar2;
  
  DAT_400014f9 = 0;
  freeram_fill_0x55();
  init_hardware();
  uVar2 = REG_SIU_RSR;
  if ((uVar2 >> 0x1b & 1) == 1) {
    DAT_400019e8 = DAT_400019e8 | 2;
  }
  DAT_4000150b = 0x80;
  DAT_4000150a = 0x80;
  DAT_40001509 = 0;
  DAT_40001508 = 0;
  DAT_40001505 = 0x80;
  DAT_40001507 = 0;
  DAT_40001506 = 0;
  DAT_40001504 = 0;
  DAT_40001538 = 1000;
  do {
    DAT_400021d8 = *(int *)(DAT_400015e4 + 0x24);
    DAT_400015ec = read_timebase_lower();
    DAT_4000150c = DAT_4000150c + 1;
    FUN_00047ed4();
    read_serial_peripherals();
    DAT_400021e8 = *(int *)(DAT_400015e4 + 0x24);
    flexcan_diagnostics_tx();
    DAT_400021ec = *(int *)(DAT_400015e4 + 0x24);
    scale_analog_inputs();
    FUN_0004d1e4();
    obd_ii_task();
    read_atf_temperature();
    update_siu_gpio_outputs_c0c2();
    power_off_handler();
    detect_gear_from_ratio();
    FUN_0004907c();
    FUN_000507dc();
    read_decode_siu_gpio_c3f906cb();
    lowpass_filter_5_analog_inputs();
    if (DAT_400017e8 != '\0') {
      commit_coding_to_flash();
    }
    freeram_counter();
    if (DAT_400014fa != '\0') {
      DAT_400014fa = '\0';
      setup_etpu_pwm_outputs();
    }
    DAT_400021dc = *(int *)(DAT_400015e4 + 0x24);
    if (DAT_400021dc < DAT_400021d8) {
      iVar1 = 0xffffff - DAT_400021d8;
    }
    else {
      iVar1 = -DAT_400021d8;
    }
    DAT_400021e0 = DAT_400021dc + iVar1;
    if (DAT_400021e4 < DAT_400021e0) {
      DAT_400021e4 = DAT_400021e0;
    }
    if (DAT_400021e0 < DAT_400013b0) {
      DAT_400013b0 = DAT_400021e0;
    }
    if (DAT_400021ec < DAT_400021e8) {
      iVar1 = 0xffffff - DAT_400021e8;
    }
    else {
      iVar1 = -DAT_400021e8;
    }
    DAT_400021f0 = DAT_400021ec + iVar1;
    if (DAT_400021f4 < DAT_400021f0) {
      DAT_400021f4 = DAT_400021f0;
    }
    if (PTR_DAT_400013b4._0_2_ == -1) {
      PTR_DAT_400013b4._0_2_ = 0x12;
    }
    else if (PTR_DAT_400013b4._0_2_ == 0x12) {
      DAT_40001538 = 1000;
    }
    else if (DAT_40003446 != -1) {
      DAT_40003446 = DAT_40003446 + 1;
    }
  } while( true );
}



void freeram_fill_0x55(void)

{
  DAT_40001500 = &SUB_4000f000;
  DAT_400014fc = 0;
  memset_and_return(&SUB_4000f000,0x55555555,0xe00);
  return;
}



void freeram_counter(void)

{
  if ((((*DAT_40001500 == 0x55555555) && (DAT_40001500[1] == 0x55555555)) &&
      (DAT_40001500[2] == 0x55555555)) && (DAT_40001500[3] == 0x55555555)) {
    if (DAT_400014f8 == '\0') {
      DAT_40001500 = DAT_40001500 + 4;
    }
  }
  else {
    DAT_400014f8 = '\x01';
    DAT_40001500 = DAT_40001500 + -4;
  }
  DAT_400014fc = (int)(((0x40010000 - ZEXT48(DAT_40001500) & 0xffffff) * 0x100 -
                        (0x40010000 - ZEXT48(DAT_40001500)) & 0xffffffff) / 0x1000);
  return;
}



void init_emios_uc4(void)

{
  uint uVar1;
  
  REG_EMIOS_UC22_CBDR = 500;
  REG_EMIOS_UC22_CADR = 0xfa;
  uVar1 = REG_EMIOS_UC22_CCR;
  REG_EMIOS_UC22_CCR = uVar1 & 0xffffff80 | 0x18;
  uVar1 = REG_EMIOS_UC22_CCR;
  REG_EMIOS_UC22_CCR = uVar1 & 0xfffff9ff | 0x600;
  uVar1 = REG_EMIOS_UC22_CCR;
  REG_EMIOS_UC22_CCR = uVar1 & 0x7fffffff | 0x80000000;
  uVar1 = REG_EMIOS_UC22_CCR;
  REG_EMIOS_UC22_CCR = uVar1 & 0xfffdffff | 0x20000;
  uVar1 = REG_EMIOS_UC22_CCR;
  REG_EMIOS_UC22_CCR = uVar1 & 0xfdffffff | 0x2000000;
  REG_EMIOS_UC22_CCNTR = 0;
  REG_INTC_PSR208 = 1;
  return;
}



void interrupt_timer_2000hz(void)

{
  bool bVar1;
  uint uVar2;
  char cVar5;
  short sVar4;
  int iVar3;
  byte bVar6;
  
  if (((DAT_40001538 != 0) && (DAT_40001525 < 200)) &&
     (DAT_40001538 = DAT_40001538 - 1, DAT_40001538 < DAT_40003448)) {
    DAT_40003448 = DAT_40001538;
  }
  DAT_400022a8 = *(undefined4 *)(DAT_400015e4 + 0x24);
  DAT_4000227c = *(int *)(DAT_400015e4 + 0x24);
  if (DAT_4000227c < DAT_400022d4) {
    iVar3 = 0xffffff - DAT_400022d4;
  }
  else {
    iVar3 = -DAT_400022d4;
  }
  DAT_400021ac = DAT_4000227c + iVar3;
  if (DAT_40002224 < DAT_400021ac) {
    DAT_40002224 = DAT_400021ac;
  }
  if (DAT_400013c6 == '\0') {
    DAT_400013c6 = '\0';
    if (DAT_400021ac < etpu_elapsed_min_ticks) {
      etpu_elapsed_min_ticks = DAT_400021ac;
    }
    if (etpu_elapsed_max_captured_ticks < DAT_400021ac) {
      etpu_elapsed_max_captured_ticks = DAT_400021ac;
    }
  }
  else {
    DAT_400013c6 = DAT_400013c6 + -1;
  }
  DAT_400022d4 = *(undefined4 *)(DAT_400015e4 + 0x24);
  if ((DAT_40001519 != '\0') && (DAT_40001519 = DAT_40001519 + -1, DAT_40001519 == '\0')) {
    flexcan_counters_scheduler_tick(0);
  }
  if ((DAT_4000151a != '\0') && (DAT_4000151a = DAT_4000151a + -1, DAT_4000151a == '\0')) {
    flexcan_counters_scheduler_tick(1);
  }
  if ((DAT_4000151b != '\0') && (DAT_4000151b = DAT_4000151b + -1, DAT_4000151b == '\0')) {
    flexcan_counters_scheduler_tick(2);
  }
  if ((DAT_4000151c != '\0') && (DAT_4000151c = DAT_4000151c + -1, DAT_4000151c == '\0')) {
    flexcan_counters_scheduler_tick(3);
  }
  if ((DAT_4000151d != '\0') && (DAT_4000151d = DAT_4000151d + -1, DAT_4000151d == '\0')) {
    flexcan_counters_scheduler_tick(4);
  }
  if ((DAT_4000151e != '\0') && (DAT_4000151e = DAT_4000151e + -1, DAT_4000151e == '\0')) {
    flexcan_counters_scheduler_tick(5);
  }
  if ((DAT_4000151f != '\0') && (DAT_4000151f = DAT_4000151f + -1, DAT_4000151f == '\0')) {
    flexcan_counters_scheduler_tick(6);
  }
  if ((DAT_40001520 != '\0') && (DAT_40001520 = DAT_40001520 + -1, DAT_40001520 == '\0')) {
    flexcan_counters_scheduler_tick(7);
  }
  if ((DAT_40001521 != '\0') && (DAT_40001521 = DAT_40001521 + -1, DAT_40001521 == '\0')) {
    flexcan_counters_scheduler_tick(8);
  }
  if ((DAT_40001522 != '\0') && (DAT_40001522 = DAT_40001522 + -1, DAT_40001522 == '\0')) {
    flexcan_counters_scheduler_tick(9);
  }
  bVar1 = DAT_40001523 < 9;
  cVar5 = DAT_40001523 + 1;
  DAT_40001523 = '\0';
  if (bVar1) {
    DAT_40001523 = cVar5;
  }
  update_trans_signal_moving_avg();
  DAT_400013c5 = DAT_400013c5 + -1;
  if (DAT_400013c5 == '\0') {
    DAT_400022ac = *(undefined4 *)(DAT_400015e4 + 0x24);
    DAT_400013c5 = '\x02';
    FUN_00057b18();
    DAT_40002254 = *(undefined4 *)(DAT_400015e4 + 0x24);
  }
  DAT_400022b0 = *(undefined4 *)(DAT_400015e4 + 0x24);
  switch(DAT_40001523) {
  case 0:
    DAT_400022d8 = *(undefined4 *)(DAT_400015e4 + 0x24);
    DAT_40001524 = 0;
    DAT_40001526 = 0;
    FUN_00044ddc();
    DAT_40002280 = *(undefined4 *)(DAT_400015e4 + 0x24);
    break;
  case 1:
    DAT_400022dc = *(undefined4 *)(DAT_400015e4 + 0x24);
    DAT_40001526 = (byte)(-(ulonglong)DAT_40001524 >> 0x18) >> 7;
    DAT_40001524 = 1;
    shift_control_task();
    DAT_40002284 = *(undefined4 *)(DAT_400015e4 + 0x24);
    break;
  case 2:
    DAT_400022e0 = *(undefined4 *)(DAT_400015e4 + 0x24);
    DAT_40001526 = (byte)((byte)(1 - (ulonglong)DAT_40001524 >> 0x18) |
                         (byte)((ulonglong)DAT_40001524 - 1 >> 0x18)) >> 7;
    DAT_40001524 = 2;
    FUN_0004cf70();
    DAT_40002288 = *(undefined4 *)(DAT_400015e4 + 0x24);
    break;
  case 3:
    DAT_400022e4 = *(undefined4 *)(DAT_400015e4 + 0x24);
    DAT_40001526 = (byte)((byte)(2 - (ulonglong)DAT_40001524 >> 0x18) |
                         (byte)((ulonglong)DAT_40001524 - 2 >> 0x18)) >> 7;
    DAT_40001524 = 3;
    FUN_00066b14();
    FUN_0005f81c();
    bVar1 = DAT_4000153a == '\0';
    DAT_4000153a = DAT_4000153a + -1;
    if (bVar1) {
      DAT_4000153a = '\0';
    }
    if (CAL_rpm_engine_running < tach_rpm) {
      if (DAT_40001540 != -1) {
        DAT_40001540 = DAT_40001540 + 1;
      }
      engine_running = 1;
    }
    else {
      DAT_40001540 = 0;
      engine_running = 0;
    }
    bVar1 = DAT_4000153c == '\0';
    DAT_4000153c = DAT_4000153c + -1;
    if (bVar1) {
      DAT_4000153c = '\0';
    }
    bVar1 = DAT_4000153b == '\0';
    DAT_4000153b = DAT_4000153b + -1;
    if (bVar1) {
      DAT_4000153b = '\0';
    }
    bVar1 = DAT_400016a8 == 0;
    DAT_400016a8 = DAT_400016a8 + -1;
    if (bVar1) {
      DAT_400016a8 = 0;
    }
    bVar1 = DAT_400016aa == 0;
    DAT_400016aa = DAT_400016aa + -1;
    if (bVar1) {
      DAT_400016aa = 0;
    }
    DAT_4000228c = *(undefined4 *)(DAT_400015e4 + 0x24);
    break;
  case 4:
    DAT_400022e8 = *(undefined4 *)(DAT_400015e4 + 0x24);
    DAT_40001526 = (byte)((byte)(3 - (ulonglong)DAT_40001524 >> 0x18) |
                         (byte)((ulonglong)DAT_40001524 - 3 >> 0x18)) >> 7;
    DAT_40001524 = 4;
    DAT_400013be = DAT_400013be + -1;
    if (DAT_400013be == '\0') {
      DAT_400022b4 = *(undefined4 *)(DAT_400015e4 + 0x24);
      DAT_400013be = '\x02';
      DAT_40001519 = '\x02';
      DAT_4000151a = '\x04';
      FUN_000482b8();
      FUN_0004d204();
      update_shaft_speeds_and_glitch();
      FUN_0006b24c();
      bVar1 = DAT_40001654 == '\0';
      DAT_40001654 = DAT_40001654 + -1;
      if (bVar1) {
        DAT_40001654 = '\0';
      }
      DAT_4000225c = *(undefined4 *)(DAT_400015e4 + 0x24);
    }
    DAT_40002290 = *(undefined4 *)(DAT_400015e4 + 0x24);
    break;
  case 5:
    DAT_400022ec = *(undefined4 *)(DAT_400015e4 + 0x24);
    DAT_40001526 = (byte)((byte)(4 - (ulonglong)DAT_40001524 >> 0x18) |
                         (byte)((ulonglong)DAT_40001524 - 4 >> 0x18)) >> 7;
    DAT_40001524 = 5;
    DAT_400013bf = DAT_400013bf + -1;
    if (DAT_400013bf == '\0') {
      DAT_400022b8 = *(undefined4 *)(DAT_400015e4 + 0x24);
      DAT_400013bf = '\x04';
      DAT_4000151b = '\x06';
      DAT_4000151c = '\b';
      compute_clutch_pressure_targets();
      DAT_40002260 = *(undefined4 *)(DAT_400015e4 + 0x24);
    }
    DAT_40002294 = *(undefined4 *)(DAT_400015e4 + 0x24);
    break;
  case 6:
    DAT_400022f0 = *(undefined4 *)(DAT_400015e4 + 0x24);
    DAT_40001526 = (byte)((byte)(5 - (ulonglong)DAT_40001524 >> 0x18) |
                         (byte)((ulonglong)DAT_40001524 - 5 >> 0x18)) >> 7;
    DAT_40001524 = 6;
    DAT_400013c0 = DAT_400013c0 + -1;
    if (DAT_400013c0 == '\0') {
      DAT_400022bc = *(undefined4 *)(DAT_400015e4 + 0x24);
      DAT_400013c0 = '\n';
      DAT_4000151d = '\f';
      DAT_4000151e = '\x0e';
      DAT_40002264 = *(undefined4 *)(DAT_400015e4 + 0x24);
    }
    DAT_40002298 = *(undefined4 *)(DAT_400015e4 + 0x24);
    break;
  case 7:
    DAT_400022f4 = *(undefined4 *)(DAT_400015e4 + 0x24);
    DAT_40001526 = (byte)((byte)(6 - (ulonglong)DAT_40001524 >> 0x18) |
                         (byte)((ulonglong)DAT_40001524 - 6 >> 0x18)) >> 7;
    DAT_40001524 = 7;
    DAT_400013bc = DAT_400013bc + -1;
    if (DAT_400013bc < 1) {
      DAT_400022c0 = *(undefined4 *)(DAT_400015e4 + 0x24);
      DAT_400013bc = 0x14;
      DAT_4000151f = '\x1a';
      DAT_40001520 = '\x1c';
      FUN_00072944();
      estimate_driving_style();
      accumulate_trans_usage_stats();
      FUN_0004c4f8();
      DAT_40001664 = 0xffff;
      if (DAT_40001528 < 0x257fda8) {
        DAT_40001528 = DAT_40001528 + 1;
      }
      if (DAT_40001510 != -1) {
        DAT_40001510 = DAT_40001510 + 1;
      }
      if ((DAT_400015b8 & 1) == 0) {
        DAT_40001512 = 0;
      }
      else if (DAT_40001512 != -1) {
        DAT_40001512 = DAT_40001512 + 1;
      }
      bVar1 = DAT_40001632 == '\0';
      DAT_40001632 = DAT_40001632 + -1;
      if (bVar1) {
        DAT_40001632 = '\0';
      }
      bVar1 = DAT_40001674 == 0;
      DAT_40001674 = DAT_40001674 + -1;
      if (bVar1) {
        DAT_40001674 = 0;
      }
      bVar1 = DAT_40001a11 == '\0';
      DAT_40001a11 = DAT_40001a11 + -1;
      if (bVar1) {
        DAT_40001a11 = '\0';
      }
      if ((driver_input_flags[1] & 4) == 0) {
        DAT_40001a12 = '\0';
      }
      else if (DAT_40001a12 != -1) {
        DAT_40001a12 = DAT_40001a12 + '\x01';
      }
      FUN_0004cadc();
      DAT_400013c1 = DAT_400013c1 + -1;
      if (DAT_400013c1 == '\0') {
        DAT_400022c4 = *(undefined4 *)(DAT_400015e4 + 0x24);
        DAT_400013c1 = '\x02';
        update_actuator_pwm_outputs();
        DAT_4000226c = *(undefined4 *)(DAT_400015e4 + 0x24);
      }
      DAT_400013c2 = DAT_400013c2 + -1;
      if (DAT_400013c2 == '\0') {
        DAT_400022c8 = *(undefined4 *)(DAT_400015e4 + 0x24);
        DAT_400013c2 = '\x03';
        FUN_000478ec();
        FUN_00058524();
        DAT_40002270 = *(undefined4 *)(DAT_400015e4 + 0x24);
      }
      DAT_400013c3 = DAT_400013c3 + -1;
      if (DAT_400013c3 == '\0') {
        DAT_400022cc = *(undefined4 *)(DAT_400015e4 + 0x24);
        DAT_400013c3 = '\x05';
        DAT_40001521 = '$';
        DAT_40002274 = *(undefined4 *)(DAT_400015e4 + 0x24);
      }
      DAT_400013c4 = DAT_400013c4 + -1;
      if (DAT_400013c4 == '\0') {
        DAT_400022d0 = *(undefined4 *)(DAT_400015e4 + 0x24);
        DAT_400013c4 = '\n';
        adaptation_drift_monitor();
        DAT_40001522 = '&';
        DAT_40002278 = *(undefined4 *)(DAT_400015e4 + 0x24);
      }
      DAT_40002268 = *(undefined4 *)(DAT_400015e4 + 0x24);
    }
    DAT_4000229c = *(undefined4 *)(DAT_400015e4 + 0x24);
    break;
  case 8:
    DAT_400022f8 = *(undefined4 *)(DAT_400015e4 + 0x24);
    DAT_40001526 = (byte)((byte)(7 - (ulonglong)DAT_40001524 >> 0x18) |
                         (byte)((ulonglong)DAT_40001524 - 7 >> 0x18)) >> 7;
    DAT_40001524 = 8;
    sVar4 = DAT_40001662 + -1;
    if (DAT_40001662 == 0) {
      sVar4 = DAT_40001662;
    }
    iVar3 = DAT_400013b8 + -1;
    if (DAT_400013b8 == 0) {
      iVar3 = DAT_400013b8;
    }
    if (((DAT_400015b8 & 1) == 0) || (tach_rpm != 0)) {
      DAT_40001514 = 0;
    }
    else {
      DAT_40001514 = DAT_40001514 + 1;
    }
    DAT_400013b8 = iVar3;
    DAT_40001662 = sVar4;
    obd_ii_send_200hz();
    DAT_400022a0 = *(undefined4 *)(DAT_400015e4 + 0x24);
    break;
  case 9:
    DAT_400022fc = *(undefined4 *)(DAT_400015e4 + 0x24);
    DAT_40001526 = (byte)((byte)(8 - (ulonglong)DAT_40001524 >> 0x18) |
                         (byte)((ulonglong)DAT_40001524 - 8 >> 0x18)) >> 7;
    DAT_400022a4 = *(undefined4 *)(DAT_400015e4 + 0x24);
    break;
  default:
    DAT_40001526 = 1;
    DAT_40001523 = '\0';
    DAT_40001524 = 0;
  }
  if (DAT_40001526 == 0) {
    DAT_40001525 = 0;
  }
  else {
    if (DAT_40003444 != -1) {
      DAT_40003444 = DAT_40003444 + 1;
    }
    if (DAT_40001525 < 200) {
      DAT_40001525 = DAT_40001525 + 1;
      if (DAT_40003442 < DAT_40001525) {
        DAT_40003442 = DAT_40001525;
      }
    }
    else {
      DAT_40003443 = 1;
      DAT_40001523 = '\0';
      DAT_40001524 = 0;
    }
  }
  DAT_40002258 = *(undefined4 *)(DAT_400015e4 + 0x24);
  DAT_40002250 = *(undefined4 *)(DAT_400015e4 + 0x24);
  for (bVar6 = 0; cVar5 = DAT_40001418, bVar6 < 0x16; bVar6 = bVar6 + 1) {
    if (bVar6 != 0xb) {
      if ((int)(&DAT_40002250)[bVar6] < (int)(&DAT_400022a8)[bVar6]) {
        iVar3 = (0xffffff - (&DAT_400022a8)[bVar6]) + (&DAT_40002250)[bVar6];
      }
      else {
        iVar3 = (&DAT_40002250)[bVar6] - (&DAT_400022a8)[bVar6];
      }
      if ((int)(&DAT_400021f8)[bVar6] < iVar3) {
        (&DAT_400021f8)[bVar6] = iVar3;
      }
      (&DAT_40002250)[bVar6] = 0;
      (&DAT_400022a8)[bVar6] = 0;
      if (iVar3 != 0) {
        (&DAT_40002180)[bVar6] = iVar3;
      }
    }
    if (DAT_40001518 != '\0') {
      (&DAT_400021f8)[bVar6] = 0;
    }
  }
  if (DAT_40001518 != '\0') {
    etpu_elapsed_min_ticks = 0x7fffffff;
    etpu_elapsed_max_captured_ticks = 0;
    DAT_40002224 = 0;
    DAT_40001518 = '\0';
    DAT_400013b0 = 0x7fffffff;
  }
  uVar2 = REG_EMIOS_UC22_CSR;
  REG_EMIOS_UC22_CSR = uVar2 & 0xfffffffe | 1;
  DAT_40001418 = DAT_40001418 + -1;
  if ((cVar5 == '\0') && ((DAT_40003480 & 8) == 8)) {
    DAT_40003480 = DAT_40003480 & 0xf7;
    DAT_400016b0 = DAT_400016b0 + '\x01';
  }
  return;
}



void init_performance_profiling_arrays(void)

{
  byte bVar1;
  
  for (bVar1 = 0; bVar1 < 22; bVar1 = bVar1 + 1) {
    (&DAT_400022a8)[bVar1] = 0;
    (&DAT_40002250)[bVar1] = 0;
    (&DAT_400021f8)[bVar1] = 0;
  }
  etpu_elapsed_min_ticks = 0x7fffffff;
  etpu_elapsed_max_captured_ticks = 0;
  return;
}



void setup_etpu_pwm_outputs(void)

{
  DAT_4000150b = 0x80;
  DAT_4000150a = 0x80;
  DAT_40001509 = 0;
  DAT_40001508 = 0;
  DAT_40001505 = 0x80;
  DAT_40001507 = 0;
  DAT_40001506 = 0;
  DAT_40001504 = 0;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xfffffffe;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xfffff7ff;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xffffefff;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xfffdffff;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0x7fffffff;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xfffbffff;
  REG_INTC_PSR86 = 10;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xffdfffff;
  REG_INTC_PSR89 = 10;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xfff7ffff;
  REG_INTC_PSR87 = 10;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xffefffff;
  REG_INTC_PSR88 = 10;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xbfffffff;
  REG_INTC_PSR98 = 10;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xffbfffff;
  REG_INTC_PSR90 = 10;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xff7fffff;
  REG_INTC_PSR91 = 10;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xfeffffff;
  REG_INTC_PSR92 = 10;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xfdffffff;
  REG_INTC_PSR93 = 10;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xfbffffff;
  REG_INTC_PSR94 = 10;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xf7ffffff;
  REG_INTC_PSR95 = 10;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xefffffff;
  REG_INTC_PSR96 = 10;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xdfffffff;
  REG_INTC_PSR97 = 10;
  FUN_00048558(0,1,3,0,0x196e6b,0,0,0x800000,0x100);
  REG_INTC_PSR68 = 0xe;
  FUN_00048684(0xb,3,0,0,0,0,0);
  REG_INTC_PSR79 = 0xe;
  FUN_00048684(0xc,3,0,0,0,0,0);
  REG_INTC_PSR80 = 0xe;
  eTPU_init_pwm_channel(0x13,2,1000000 / DAT_40008ff4,0,0,0,10000000);
  eTPU_init_pwm_channel(0x14,2,1000000 / DAT_40008ff4,0,0,0,10000000);
  eTPU_init_pwm_channel(0x1e,2,1000000 / DAT_40008ff4,0,0,0,10000000);
  eTPU_init_pwm_channel(0x16,2,1000000 / DAT_40008ff4,&DAT_00002710,0,0,10000000);
  eTPU_init_pwm_channel(0x17,2,1000000 / DAT_40008ff4,&DAT_00002710,0,0,10000000);
  eTPU_init_pwm_channel(0x18,2,1000000 / DAT_40008ff4,&DAT_00002710,0,0,10000000);
  eTPU_init_pwm_channel(0x19,2,1000000 / DAT_40008ff4,&DAT_00002710,0,0,10000000);
  eTPU_init_pwm_channel(0x1a,2,1000000 / DAT_40008ff4,&DAT_00002710,0,0,10000000);
  eTPU_init_pwm_channel(0x1b,2,1000000 / DAT_40008ff4,&DAT_00002710,0,0,10000000);
  eTPU_init_pwm_channel(0x1c,2,1000000 / DAT_40008ff4,&DAT_00002710,0,0,10000000);
  eTPU_init_pwm_channel(0x1d,2,1000000 / DAT_40008ff4,&DAT_00002710,0,0,10000000);
  FUN_000488e0(0x11,3,0,0,0,0);
  *(undefined4 *)(DAT_400015e4 + 0x518) = 3;
  FUN_000487b8(0x1f,3,0,0,0);
  *(undefined4 *)(DAT_400015e4 + 0x5f8) = 3;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xfffffffe | 1;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xfffff7ff | 0x800;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xffffefff | 0x1000;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xffbfffff | 0x400000;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xff7fffff | 0x800000;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xfeffffff | 0x1000000;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xfdffffff | 0x2000000;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xfbffffff | 0x4000000;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xf7ffffff | 0x8000000;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xefffffff | 0x10000000;
  *(uint *)(DAT_400015e4 + 0x240) = *(uint *)(DAT_400015e4 + 0x240) & 0xdfffffff | 0x20000000;
  return;
}



void etpu_a_isr_vec068(void)

{
  return;
}



void etpu_a_isr_vec079(void)

{
  undefined1 uVar2;
  undefined8 uVar1;
  
  *(uint *)(DAT_400015e4 + 0x4b4) = *(uint *)(DAT_400015e4 + 0x4b4) & 0x7fffffff | 0x80000000;
  eTPU_read_8bit(0xb,4);
  uVar2 = eTPU_read_8bit(0xb,9);
  uVar1 = eTPU_read_24bit(0xb,5);
  eTPU_read_24bit(0xb,1);
  DAT_400013ca = 10;
  time_interval_processing_unknown(uVar2,uVar1,&DAT_4000235c);
  return;
}



void etpu_a_isr_vec080(void)

{
  undefined1 uVar2;
  undefined8 uVar1;
  
  *(uint *)(DAT_400015e4 + 0x4c4) = *(uint *)(DAT_400015e4 + 0x4c4) & 0x7fffffff | 0x80000000;
  eTPU_read_8bit(0xc,4);
  uVar2 = eTPU_read_8bit(0xc,9);
  uVar1 = eTPU_read_24bit(0xc,5);
  eTPU_read_24bit(0xc,1);
  DAT_400013cb = 10;
  time_interval_processing_unknown(uVar2,uVar1,&DAT_40002340);
  return;
}



void etpu_a_isr_vec086(void)

{
  *(uint *)(DAT_400015e4 + 0x524) = *(uint *)(DAT_400015e4 + 0x524) & 0x7fffffff | 0x80000000;
  return;
}



void etpu_a_isr_vec087(void)

{
  *(uint *)(DAT_400015e4 + 0x534) = *(uint *)(DAT_400015e4 + 0x534) & 0x7fffffff | 0x80000000;
  return;
}



void etpu_a_isr_vec088(void)

{
  *(uint *)(DAT_400015e4 + 0x544) = *(uint *)(DAT_400015e4 + 0x544) & 0x7fffffff | 0x80000000;
  return;
}



void etpu_a_isr_vec089(void)

{
  *(uint *)(DAT_400015e4 + 0x554) = *(uint *)(DAT_400015e4 + 0x554) & 0x7fffffff | 0x80000000;
  return;
}



void etpu_a_isr_vec090(void)

{
  *(uint *)(DAT_400015e4 + 0x564) = *(uint *)(DAT_400015e4 + 0x564) & 0x7fffffff | 0x80000000;
  return;
}



void etpu_a_isr_vec091(void)

{
  *(uint *)(DAT_400015e4 + 0x574) = *(uint *)(DAT_400015e4 + 0x574) & 0x7fffffff | 0x80000000;
  return;
}



void etpu_a_isr_vec092(void)

{
  *(uint *)(DAT_400015e4 + 0x584) = *(uint *)(DAT_400015e4 + 0x584) & 0x7fffffff | 0x80000000;
  if (DAT_40008fea == '\0') {
    DAT_40002394 = (undefined2)((int)(uint)DAT_40001de8 >> 4);
  }
  return;
}



void etpu_a_isr_vec093(void)

{
  *(uint *)(DAT_400015e4 + 0x594) = *(uint *)(DAT_400015e4 + 0x594) & 0x7fffffff | 0x80000000;
  if (DAT_40008fea == '\0') {
    DAT_40002396 = (undefined2)((int)(uint)DAT_40001dea >> 4);
  }
  return;
}



void etpu_a_isr_vec094(void)

{
  *(uint *)(DAT_400015e4 + 0x5a4) = *(uint *)(DAT_400015e4 + 0x5a4) & 0x7fffffff | 0x80000000;
  if (DAT_40008fea == '\0') {
    DAT_40002398 = (undefined2)((int)(uint)DAT_40001dec >> 4);
  }
  return;
}



void etpu_a_isr_vec095(void)

{
  *(uint *)(DAT_400015e4 + 0x5b4) = *(uint *)(DAT_400015e4 + 0x5b4) & 0x7fffffff | 0x80000000;
  if (DAT_40008fea == '\0') {
    DAT_4000239a = (undefined2)((int)(uint)DAT_40001dee >> 4);
  }
  return;
}



void etpu_a_isr_vec096(void)

{
  *(uint *)(DAT_400015e4 + 0x5c4) = *(uint *)(DAT_400015e4 + 0x5c4) & 0x7fffffff | 0x80000000;
  if (DAT_40008fea == '\0') {
    DAT_4000239c = (undefined2)((int)(uint)DAT_40001df0 >> 4);
  }
  return;
}



void etpu_a_isr_vec097(void)

{
  *(uint *)(DAT_400015e4 + 0x5d4) = *(uint *)(DAT_400015e4 + 0x5d4) & 0x7fffffff | 0x80000000;
  if (DAT_40008fea == '\0') {
    DAT_4000239e = (undefined2)((int)(uint)DAT_40001df2 >> 4);
  }
  return;
}



void FUN_00044dc0(void)

{
  DAT_4000235c = 1;
  DAT_40002340 = 1;
  return;
}



void FUN_00044ddc(void)

{
  short sVar1;
  int iVar2;
  uint16_t uVar4;
  byte bVar5;
  uint uVar3;
  
  DAT_40001548 = eTPU_read_8bit(0xb,9);
  if (DAT_400013ca == '\0') {
    if (((DAT_40001548 == '\0') || (DAT_4000235c != '\0')) &&
       ((DAT_40001548 != '\0' || (DAT_4000235c == '\0')))) {
      DAT_40002374 = (undefined *)0x0;
    }
    else {
      DAT_40002374 = &DAT_00002710;
    }
  }
  else {
    DAT_400013ca = DAT_400013ca + -1;
  }
  DAT_40001548 = eTPU_read_8bit(0xc,9);
  if (DAT_400013cb == '\0') {
    if (((DAT_40001548 == '\0') || (DAT_40002340 != '\0')) &&
       ((DAT_40001548 != '\0' || (DAT_40002340 == '\0')))) {
      DAT_40002358 = (undefined *)0x0;
    }
    else {
      DAT_40002358 = &DAT_00002710;
    }
  }
  else {
    DAT_400013cb = DAT_400013cb + -1;
  }
  if (DAT_400013c8 == '\0') {
    input_shaft_rpm = 0;
  }
  else {
    DAT_400013c8 = DAT_400013c8 + -1;
  }
  if ((DAT_40001678 & 4) == 0) {
    if (DAT_400013c9 == '\0') {
      output_shaft_rpm = 0;
    }
    else {
      output_shaft_rpm = output_shaft_rpm_sensor;
      DAT_400013c9 = DAT_400013c9 + -1;
    }
  }
  else if ((DAT_40001678 & 0x200) == 0) {
    output_shaft_rpm = (u16_rspeed_rpm)((int)((uint)vehicle_speed____ * (uint)DAT_40008f7c) / 10000)
    ;
  }
  else {
    output_shaft_rpm = 0;
  }
  if ((((output_shaft_rpm == 0) || (input_shaft_rpm == 0)) || (gear_request == NEUTRAL)) ||
     ((GEAR_6 < gear_request || (shift_from_gear == GEAR_REV)))) {
    DAT_40001566 = 0;
    DAT_40001564 = 0;
    DAT_40001562 = 100;
    DAT_40001560 = 0;
    DAT_40001552 = 0;
    DAT_40001be0 = DAT_40008ff7;
    DAT_4000156a = DAT_40008f9e;
  }
  else {
    DAT_40001566 = (undefined2)(((uint)input_shaft_rpm * 1000) / (uint)output_shaft_rpm);
    uVar4 = get_gear_ratio(gear_request);
    uVar3 = (uint)output_shaft_rpm * (uint)uVar4;
    DAT_40001564 = (short)((int)((uint)input_shaft_rpm * 100000) / ((int)uVar3 / 10));
    DAT_40001562 = DAT_40001564 + -1000;
    DAT_40001560 = int_abs((ulonglong)input_shaft_rpm -
                           ((longlong)((int)uVar3 / 1000 + ((int)uVar3 >> 0x1f)) +
                           (ulonglong)(uVar3 >> 0x1f)));
    if ((((shift_mode_word & 2) == 0) || (shift_torque_managed == '\0')) ||
       ((gear_request == GEAR_REV || (gear_request == NEUTRAL)))) {
      DAT_40001be1 = 0;
      DAT_40001552 = 0;
      DAT_40001be0 = DAT_40008ff7;
      if (DAT_40009160 != '\0') {
        DAT_40001be0 = DAT_4000915e;
      }
      DAT_4000156a = DAT_40008f9e;
      DAT_400013cc = DAT_40009162;
      if (GEAR_1 < gear_request) {
        DAT_400013cc = *(&PTR_DAT_000886c8)[gear_request - 2];
      }
      uVar4 = get_gear_ratio(gear_request - GEAR_1);
      DAT_40001550 = (undefined2)
                     ((int)((uint)DAT_400013cc * (uint)output_shaft_rpm * (uint)uVar4) / 0x1f400);
      uVar4 = get_gear_ratio(gear_request - GEAR_1);
      DAT_4000154e = (undefined2)
                     ((int)((uint)DAT_400013cc *
                           ((int)((uint)vehicle_speed____ * (uint)DAT_40008f7c) / 10000) *
                           (uint)uVar4) / 0x1f400);
      uVar4 = get_gear_ratio(gear_request - GEAR_1);
      DAT_4000154c = (undefined2)((int)((uint)output_shaft_rpm * (uint)uVar4) / 1000);
    }
    else if (DAT_4000156a == '\0') {
      DAT_40001be1 = 0;
      DAT_40001552 = 0;
    }
    else {
      if (DAT_40001be0 == '\0') {
        DAT_40001be1 = DAT_40001be1 & 0xfd | 1;
        DAT_4000156a = DAT_4000156a + -1;
      }
      else {
        DAT_40001be0 = DAT_40001be0 + -1;
        DAT_40001be1 = DAT_40001be1 & 0xfe | 2;
      }
      DAT_400013cc = DAT_40009162;
      if (gear_request != NEUTRAL) {
        DAT_400013cc = *(&PTR_DAT_000886c8)[gear_request - 1];
      }
      DAT_40001550 = (undefined2)((int)(uVar3 * DAT_400013cc) / 0x1f400);
      DAT_4000154e = (undefined2)
                     ((int)((uint)DAT_400013cc *
                           (uint)uVar4 *
                           ((int)((uint)vehicle_speed____ * (uint)DAT_40008f7c) / 10000)) / 0x1f400)
      ;
      DAT_4000154c = (undefined2)((int)uVar3 / 1000);
      DAT_40001552 = DAT_40001550;
      if ((((DAT_40001678 & 4) == 0) && ((DAT_40001678 & 0x200) == 0)) && (DAT_40009161 != '\0')) {
        DAT_40001552 = DAT_4000154e;
      }
    }
  }
  for (bVar5 = 0xf; bVar5 != 0; bVar5 = bVar5 - 1) {
    input_shaft_rpm_history[bVar5] = input_shaft_rpm_history[bVar5 - 1];
  }
  input_shaft_rpm_history[0] = input_shaft_rpm;
  uVar3 = (uint)DAT_40008f68;
  if (0xf < uVar3) {
    uVar3 = 0xf;
  }
  DAT_40001558 = (((int)(short)input_shaft_rpm - (int)(short)input_shaft_rpm_history[uVar3]) * 200)
                 / (int)uVar3;
  for (bVar5 = 0xf; bVar5 != 0; bVar5 = bVar5 - 1) {
    output_shaft_rpm_history[bVar5] = output_shaft_rpm_history[bVar5 - 1];
  }
  output_shaft_rpm_history[0] = output_shaft_rpm;
  uVar3 = (uint)DAT_40008f69;
  if (0xf < uVar3) {
    uVar3 = 0xf;
  }
  DAT_40001554 = (((int)(short)output_shaft_rpm - (int)(short)output_shaft_rpm_history[uVar3]) * 200
                 ) / (int)uVar3;
  if (DAT_40001c3a == '\0') {
    DAT_4000154a = 0;
    DAT_40001549 = 0;
  }
  else if ((int)((uint)DAT_400013cd * 10) < DAT_40001554) {
    DAT_4000154a = 1;
  }
  else if (DAT_40001554 < (int)((uint)DAT_400013cd * -10)) {
    DAT_40001549 = 1;
  }
  iVar2 = (uint)DAT_40008fde * ((uint)DAT_400015bc * 10 - (uint)DAT_40008fdc);
  sVar1 = (short)(iVar2 >> 0x1f);
  DAT_4000155e = ((short)(iVar2 / 10000) + sVar1) -
                 ((short)((short)(iVar2 / 0x27100000) + sVar1) >> 0xf);
  iVar2 = (uint)DAT_400090ae * ((uint)DAT_400015be * 10 - (uint)DAT_400090ac);
  sVar1 = (short)(iVar2 >> 0x1f);
  DAT_4000155c = ((short)(iVar2 / 10000) + sVar1) -
                 ((short)((short)(iVar2 / 0x27100000) + sVar1) >> 0xf);
  return;
}



void time_interval_processing_unknown(char param_1,uint param_2,char *param_3)

{
  if (((param_1 == '\0') || (*param_3 != '\0')) && ((param_1 != '\0' || (*param_3 == '\0')))) {
    *(uint *)(param_3 + 8) = param_2;
    if (*(uint *)(param_3 + 8) < *(uint *)(param_3 + 4)) {
      *(int *)(param_3 + 0x10) = 0x1000000 - (*(int *)(param_3 + 4) - *(int *)(param_3 + 8));
    }
    else {
      *(int *)(param_3 + 0x10) = *(int *)(param_3 + 8) - *(int *)(param_3 + 4);
    }
  }
  else {
    if (param_2 < *(uint *)(param_3 + 4)) {
      *(uint *)(param_3 + 0xc) = 0x1000000 - (*(int *)(param_3 + 4) - param_2);
    }
    else {
      *(uint *)(param_3 + 0xc) = param_2 - *(int *)(param_3 + 4);
    }
    *(uint *)(param_3 + 4) = param_2;
    if (param_2 < *(uint *)(param_3 + 8)) {
      *(uint *)(param_3 + 0x14) = 0x1000000 - (*(int *)(param_3 + 8) - param_2);
    }
    else {
      *(uint *)(param_3 + 0x14) = param_2 - *(int *)(param_3 + 8);
    }
    if (*(uint *)(param_3 + 0x14) < *(uint *)(param_3 + 0xc)) {
      *(int *)(param_3 + 0x10) = *(int *)(param_3 + 0xc) - *(int *)(param_3 + 0x14);
    }
    else {
      param_3[0x10] = '\0';
      param_3[0x11] = '\0';
      param_3[0x12] = '\0';
      param_3[0x13] = '\0';
    }
  }
  *(uint *)(param_3 + 0x18) = (uint)(*(int *)(param_3 + 0x10) * 10000) / *(uint *)(param_3 + 0xc);
  return;
}



void FUN_000457b0(void)

{
  REG_SIU_PCR102 = 0xecc;
  REG_SIU_PCR103 = 0xd00;
  REG_SIU_PCR104 = 0xecc;
  REG_DSPI_B_MCR = 0x803f0c00;
  REG_SIU_PCR109 = 0xacc;
  REG_SIU_PCR108 = 0x900;
  REG_SIU_PCR107 = 0xacc;
  REG_SIU_PCR95 = 0xacc;
  REG_DSPI_C_MCR = 0x803f0c00;
  DAT_400015b0 = 0xf;
  REG_SIU_PCR190 = 0x2cc;
  REG_SIU_GPDO190 = 1;
  return;
}



void init_dspib_1(uint param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = REG_DSPI_B_SR;
  REG_DSPI_B_SR = uVar1 | 0xffff0000;
  REG_DSPI_B_CTAR0 = 0x3a003023;
  do {
    uVar1 = REG_DSPI_C_SR;
  } while ((uVar1 >> 0x19 & 1) != 1);
  REG_DSPI_B_PUSHR = param_1 & 0xff | 0x84080000;
  do {
    uVar1 = REG_DSPI_C_SR;
  } while ((uVar1 >> 0x19 & 1) != 1);
  REG_DSPI_B_PUSHR = param_2 & 0xff | 0x8080000;
  do {
    do {
      uVar1 = REG_DSPI_B_SR;
    } while (-1 < (int)uVar1);
    uVar1 = REG_DSPI_B_SR;
  } while ((uVar1 >> 4 & 0xf) < 2);
  uVar1 = REG_DSPI_B_POPR;
  DAT_4000237f = (char)uVar1;
  uVar1 = REG_DSPI_B_POPR;
  DAT_40002380 = (char)uVar1;
  return;
}



void spi_read_dspib_driver_status(void)

{
  uint uVar1;
  
  uVar1 = REG_DSPI_B_SR;
  REG_DSPI_B_SR = uVar1 | 0xffff0000;
  REG_DSPI_B_CTAR0 = 0x3a003023;
  do {
    uVar1 = REG_DSPI_B_SR;
  } while ((uVar1 >> 0x19 & 1) != 1);
  REG_DSPI_B_PUSHR = 0x80010000;
  do {
    uVar1 = REG_DSPI_B_SR;
  } while ((uVar1 >> 0x19 & 1) != 1);
  REG_DSPI_B_PUSHR = 0x8010000;
  do {
    do {
      uVar1 = REG_DSPI_B_SR;
    } while (-1 < (int)uVar1);
    uVar1 = REG_DSPI_B_SR;
  } while ((uVar1 >> 4 & 0xf) < 2);
  uVar1 = REG_DSPI_B_POPR;
  DAT_4000237d = (char)uVar1;
  uVar1 = REG_DSPI_B_POPR;
  DAT_4000237a = (char)uVar1;
  return;
}



void FUN_000459d0(void)

{
  uint uVar1;
  
  uVar1 = REG_DSPI_C_SR;
  REG_DSPI_C_SR = uVar1 | 0xffff0000;
  REG_DSPI_C_CTAR0 = 0x3a003023;
  do {
    uVar1 = REG_DSPI_C_SR;
  } while ((uVar1 >> 0x19 & 1) != 1);
  REG_DSPI_C_PUSHR = 0x8200000;
  do {
    do {
      uVar1 = REG_DSPI_C_SR;
    } while (-1 < (int)uVar1);
    uVar1 = REG_DSPI_C_SR;
  } while ((uVar1 >> 4 & 0xf) == 0);
  uVar1 = REG_DSPI_C_POPR;
  DAT_4000237c = (char)uVar1;
  return;
}



void spi_read_tps_error_flags(void)

{
  uint uVar1;
  
  REG_DSPI_C_CTAR1 = 0x3a020023;
  uVar1 = REG_DSPI_C_SR;
  REG_DSPI_C_SR = uVar1 | 0xffff0000;
  do {
    uVar1 = REG_DSPI_C_SR;
  } while ((uVar1 >> 0x19 & 1) != 1);
  REG_DSPI_C_PUSHR = DAT_400013d0 | 0x18020000;
  do {
    do {
      uVar1 = REG_DSPI_C_SR;
    } while (-1 < (int)uVar1);
    uVar1 = REG_DSPI_C_SR;
  } while ((uVar1 >> 4 & 0xf) == 0);
  uVar1 = REG_DSPI_C_POPR;
  if (DAT_4000153a == '\0') {
    DAT_4000153a = '\n';
    if (DAT_40001571 == '\0') {
      DAT_400013d0 = 0x80;
      DAT_40001571 = '\x01';
    }
    else if (DAT_40001571 == '\x01') {
      DAT_400013d0 = 0x80;
      DAT_40001571 = '\x02';
    }
    else if (DAT_40001571 == '\x02') {
      DAT_400013d0 = 0x81;
      DAT_40001571 = '\0';
      DAT_40001570 = (byte)uVar1;
    }
    else {
      DAT_40001571 = '\0';
    }
  }
  DAT_40002379 = DAT_40001570 & 0xfd;
  return;
}



void read_serial_peripherals(void)

{
  init_dspib_1(0xff,DAT_400015b0);
  spi_read_dspib_driver_status();
  FUN_000459d0();
  spi_read_tps_error_flags();
  return;
}



void init_eDMA2(void)

{
  REG_EDMA_CR = 0xe400;
  REG_EDMA_ERQRL = 0;
  REG_EDMA_EEIRL = 0;
  REG_EDMA_CPR0 = 0;
  REG_EDMA_CPR1 = 1;
  REG_EDMA_CPR2 = 2;
  REG_EDMA_CPR3 = 3;
  REG_EDMA_CPR4 = 4;
  REG_EDMA_CPR5 = 5;
  REG_EDMA_CPR6 = 6;
  REG_EDMA_CPR7 = 7;
  REG_EDMA_CPR8 = 8;
  REG_EDMA_CPR9 = 9;
  REG_EDMA_CPR10 = 10;
  REG_EDMA_CPR11 = 0xb;
  REG_EDMA_CPR12 = 0xc;
  REG_EDMA_CPR13 = 0xd;
  REG_EDMA_CPR14 = 0xe;
  REG_EDMA_CPR15 = 0xf;
  REG_EDMA_CPR16 = 0;
  REG_EDMA_CPR17 = 1;
  REG_EDMA_CPR18 = 2;
  REG_EDMA_CPR19 = 3;
  REG_EDMA_CPR20 = 4;
  REG_EDMA_CPR21 = 5;
  REG_EDMA_CPR22 = 6;
  REG_EDMA_CPR23 = 7;
  REG_EDMA_CPR24 = 8;
  REG_EDMA_CPR25 = 9;
  REG_EDMA_CPR26 = 10;
  REG_EDMA_CPR27 = 0xb;
  REG_EDMA_CPR28 = 0xc;
  REG_EDMA_CPR29 = 0xc;
  REG_EDMA_CPR30 = 0xe;
  REG_EDMA_CPR31 = 0xf;
  return;
}



void init_eDMA2_2(void)

{
  ushort uVar1;
  
  REG_EDMA_TCD10 = 0x40002038;
  DAT_fff45150 = 0xfff80024;
  uVar1 = DAT_fff45144;
  DAT_fff45144 = uVar1 & 0x7ff;
  uVar1 = DAT_fff45144;
  DAT_fff45144 = uVar1 & 0xff07;
  uVar1 = DAT_fff45144;
  DAT_fff45144 = uVar1 & 0xfff8 | 2;
  uVar1 = DAT_fff45144;
  DAT_fff45144 = uVar1 & 0xf8ff | 0x200;
  DAT_fff45146 = 4;
  DAT_fff45148 = 4;
  DAT_fff4514c = 0xffffffdc;
  DAT_fff45156 = 0;
  DAT_fff45158 = 0;
  uVar1 = DAT_fff4515c;
  DAT_fff4515c = uVar1 & 0x7fff;
  uVar1 = DAT_fff4515c;
  DAT_fff4515c = uVar1 & 0x8000 | 6;
  uVar1 = DAT_fff45154;
  DAT_fff45154 = uVar1 & 0x7fff;
  uVar1 = DAT_fff45154;
  DAT_fff45154 = uVar1 & 0x8000 | 6;
  uVar1 = DAT_fff4515e;
  DAT_fff4515e = uVar1 & 0x3fff;
  uVar1 = DAT_fff4515e;
  DAT_fff4515e = uVar1 & 0xc0ff;
  uVar1 = DAT_fff4515e;
  DAT_fff4515e = uVar1 & 0xffdf;
  uVar1 = DAT_fff4515e;
  DAT_fff4515e = uVar1 & 0xff7f;
  uVar1 = DAT_fff4515e;
  DAT_fff4515e = uVar1 & 0xffbf;
  uVar1 = DAT_fff4515e;
  DAT_fff4515e = uVar1 & 0xffef;
  uVar1 = DAT_fff4515e;
  DAT_fff4515e = uVar1 & 0xfff7 | 8;
  uVar1 = DAT_fff4515e;
  DAT_fff4515e = uVar1 & 0xfffb;
  uVar1 = DAT_fff4515e;
  DAT_fff4515e = uVar1 & 0xfffd;
  uVar1 = DAT_fff4515e;
  DAT_fff4515e = uVar1 & 0xfffe;
  REG_EDMA_ERQRL = 0x400;
  return;
}



void init_pinmux_and_iosetup(void)

{
  ushort uVar1;
  uint uVar2;
  
  REG_EDMA_ERQRL = 0xf00;
  REG_EDMA_EEIRL = 0;
  REG_EDMA_IRQRL = 2;
  REG_EDMA_TCD0 = 0x40002160;
  DAT_fff45010 = 0xfff80010;
  uVar1 = DAT_fff45004;
  DAT_fff45004 = uVar1 & 0x7ff;
  uVar1 = DAT_fff45004;
  DAT_fff45004 = uVar1 & 0xff07;
  uVar1 = DAT_fff45004;
  DAT_fff45004 = uVar1 & 0xfff8 | 2;
  uVar1 = DAT_fff45004;
  DAT_fff45004 = uVar1 & 0xf8ff | 0x200;
  DAT_fff45006 = 4;
  DAT_fff45008 = 4;
  DAT_fff4500c = 0xfffffffc;
  uVar1 = DAT_fff45014;
  DAT_fff45014 = uVar1 & 0x7fff;
  uVar1 = DAT_fff45014;
  DAT_fff45014 = uVar1 & 0x8000 | 1;
  DAT_fff45016 = 0;
  DAT_fff45018 = 0;
  uVar1 = DAT_fff4501c;
  DAT_fff4501c = uVar1 & 0x7fff;
  uVar1 = DAT_fff4501c;
  DAT_fff4501c = uVar1 & 0x8000 | 1;
  uVar1 = DAT_fff4501e;
  DAT_fff4501e = uVar1 & 0x3fff;
  uVar1 = DAT_fff4501e;
  DAT_fff4501e = uVar1 & 0xc0ff;
  uVar1 = DAT_fff4501e;
  DAT_fff4501e = uVar1 & 0xffdf;
  uVar1 = DAT_fff4501e;
  DAT_fff4501e = uVar1 & 0xff7f;
  uVar1 = DAT_fff4501e;
  DAT_fff4501e = uVar1 & 0xffbf;
  uVar1 = DAT_fff4501e;
  DAT_fff4501e = uVar1 & 0xffef;
  uVar1 = DAT_fff4501e;
  DAT_fff4501e = uVar1 & 0xfff7;
  uVar1 = DAT_fff4501e;
  DAT_fff4501e = uVar1 & 0xfffb;
  uVar1 = DAT_fff4501e;
  DAT_fff4501e = uVar1 & 0xfffd;
  uVar1 = DAT_fff4501e;
  DAT_fff4501e = uVar1 & 0xfffe;
  REG_EDMA_TCD1 = 0xfff80032;
  DAT_fff45030 = 0x40001e38;
  uVar1 = DAT_fff45024;
  DAT_fff45024 = uVar1 & 0x7ff;
  uVar1 = DAT_fff45024;
  DAT_fff45024 = uVar1 & 0xff07;
  uVar1 = DAT_fff45024;
  DAT_fff45024 = uVar1 & 0xfff8 | 1;
  uVar1 = DAT_fff45024;
  DAT_fff45024 = uVar1 & 0xf8ff | 0x100;
  DAT_fff45026 = 0;
  DAT_fff45028 = 2;
  DAT_fff4502c = 0;
  DAT_fff45036 = 2;
  DAT_fff45038 = 0xffffffc0;
  uVar1 = DAT_fff4503c;
  DAT_fff4503c = uVar1 & 0x7fff;
  uVar1 = DAT_fff4503c;
  DAT_fff4503c = uVar1 & 0x8000 | 0x20;
  uVar1 = DAT_fff45034;
  DAT_fff45034 = uVar1 & 0x7fff;
  uVar1 = DAT_fff45034;
  DAT_fff45034 = uVar1 & 0x8000 | 0x20;
  uVar1 = DAT_fff4503e;
  DAT_fff4503e = uVar1 & 0x3fff;
  uVar1 = DAT_fff4503e;
  DAT_fff4503e = uVar1 & 0xc0ff;
  uVar1 = DAT_fff4503e;
  DAT_fff4503e = uVar1 & 0xffdf;
  uVar1 = DAT_fff4503e;
  DAT_fff4503e = uVar1 & 0xff7f;
  uVar1 = DAT_fff4503e;
  DAT_fff4503e = uVar1 & 0xffbf;
  uVar1 = DAT_fff4503e;
  DAT_fff4503e = uVar1 & 0xffef;
  uVar1 = DAT_fff4503e;
  DAT_fff4503e = uVar1 & 0xfff7;
  uVar1 = DAT_fff4503e;
  DAT_fff4503e = uVar1 & 0xfffb;
  uVar1 = DAT_fff4503e;
  DAT_fff4503e = uVar1 & 0xfffd | 2;
  uVar1 = DAT_fff4503e;
  DAT_fff4503e = uVar1 & 0xfffe;
  REG_EDMA_TCD2 = 0x40002150;
  DAT_fff45050 = 0xfff80014;
  uVar1 = DAT_fff45044;
  DAT_fff45044 = uVar1 & 0x7ff;
  uVar1 = DAT_fff45044;
  DAT_fff45044 = uVar1 & 0xff07;
  uVar1 = DAT_fff45044;
  DAT_fff45044 = uVar1 & 0xfff8 | 2;
  uVar1 = DAT_fff45044;
  DAT_fff45044 = uVar1 & 0xf8ff | 0x200;
  DAT_fff45046 = 4;
  DAT_fff45048 = 4;
  DAT_fff4504c = 0xfffffffc;
  uVar1 = DAT_fff45054;
  DAT_fff45054 = uVar1 & 0x7fff;
  uVar1 = DAT_fff45054;
  DAT_fff45054 = uVar1 & 0x8000 | 1;
  DAT_fff45056 = 0;
  DAT_fff45058 = 0;
  uVar1 = DAT_fff4505c;
  DAT_fff4505c = uVar1 & 0x7fff;
  uVar1 = DAT_fff4505c;
  DAT_fff4505c = uVar1 & 0x8000 | 1;
  uVar1 = DAT_fff4505e;
  DAT_fff4505e = uVar1 & 0x3fff;
  uVar1 = DAT_fff4505e;
  DAT_fff4505e = uVar1 & 0xc0ff;
  uVar1 = DAT_fff4505e;
  DAT_fff4505e = uVar1 & 0xffdf;
  uVar1 = DAT_fff4505e;
  DAT_fff4505e = uVar1 & 0xff7f;
  uVar1 = DAT_fff4505e;
  DAT_fff4505e = uVar1 & 0xffbf;
  uVar1 = DAT_fff4505e;
  DAT_fff4505e = uVar1 & 0xffef;
  uVar1 = DAT_fff4505e;
  DAT_fff4505e = uVar1 & 0xfff7;
  uVar1 = DAT_fff4505e;
  DAT_fff4505e = uVar1 & 0xfffb;
  uVar1 = DAT_fff4505e;
  DAT_fff4505e = uVar1 & 0xfffd;
  uVar1 = DAT_fff4505e;
  DAT_fff4505e = uVar1 & 0xfffe;
  REG_EDMA_TCD3 = 0xfff80036;
  DAT_fff45070 = 0x40001e28;
  uVar1 = DAT_fff45064;
  DAT_fff45064 = uVar1 & 0x7ff;
  uVar1 = DAT_fff45064;
  DAT_fff45064 = uVar1 & 0xff07;
  uVar1 = DAT_fff45064;
  DAT_fff45064 = uVar1 & 0xfff8 | 1;
  uVar1 = DAT_fff45064;
  DAT_fff45064 = uVar1 & 0xf8ff | 0x100;
  DAT_fff45066 = 0;
  DAT_fff45068 = 2;
  DAT_fff4506c = 0;
  DAT_fff45076 = 2;
  DAT_fff45078 = 0xfffffffc;
  uVar1 = DAT_fff4507c;
  DAT_fff4507c = uVar1 & 0x7fff;
  uVar1 = DAT_fff4507c;
  DAT_fff4507c = uVar1 & 0x8000 | 2;
  uVar1 = DAT_fff45074;
  DAT_fff45074 = uVar1 & 0x7fff;
  uVar1 = DAT_fff45074;
  DAT_fff45074 = uVar1 & 0x8000 | 2;
  uVar1 = DAT_fff4507e;
  DAT_fff4507e = uVar1 & 0x3fff;
  uVar1 = DAT_fff4507e;
  DAT_fff4507e = uVar1 & 0xc0ff;
  uVar1 = DAT_fff4507e;
  DAT_fff4507e = uVar1 & 0xffdf;
  uVar1 = DAT_fff4507e;
  DAT_fff4507e = uVar1 & 0xff7f;
  uVar1 = DAT_fff4507e;
  DAT_fff4507e = uVar1 & 0xffbf;
  uVar1 = DAT_fff4507e;
  DAT_fff4507e = uVar1 & 0xffef;
  uVar1 = DAT_fff4507e;
  DAT_fff4507e = uVar1 & 0xfff7;
  uVar1 = DAT_fff4507e;
  DAT_fff4507e = uVar1 & 0xfffb;
  uVar1 = DAT_fff4507e;
  DAT_fff4507e = uVar1 & 0xfffd;
  uVar1 = DAT_fff4507e;
  DAT_fff4507e = uVar1 & 0xfffe;
  REG_EDMA_TCD4 = 0x40002140;
  DAT_fff45090 = 0xfff80018;
  uVar1 = DAT_fff45084;
  DAT_fff45084 = uVar1 & 0x7ff;
  uVar1 = DAT_fff45084;
  DAT_fff45084 = uVar1 & 0xff07;
  uVar1 = DAT_fff45084;
  DAT_fff45084 = uVar1 & 0xfff8 | 2;
  uVar1 = DAT_fff45084;
  DAT_fff45084 = uVar1 & 0xf8ff | 0x200;
  DAT_fff45086 = 4;
  DAT_fff45088 = 0;
  DAT_fff4508c = 0xfffffffc;
  uVar1 = DAT_fff45094;
  DAT_fff45094 = uVar1 & 0x7fff;
  uVar1 = DAT_fff45094;
  DAT_fff45094 = uVar1 & 0x8000 | 1;
  DAT_fff45096 = 0;
  DAT_fff45098 = 0;
  uVar1 = DAT_fff4509c;
  DAT_fff4509c = uVar1 & 0x7fff;
  uVar1 = DAT_fff4509c;
  DAT_fff4509c = uVar1 & 0x8000 | 1;
  uVar1 = DAT_fff4509e;
  DAT_fff4509e = uVar1 & 0x3fff;
  uVar1 = DAT_fff4509e;
  DAT_fff4509e = uVar1 & 0xc0ff;
  uVar1 = DAT_fff4509e;
  DAT_fff4509e = uVar1 & 0xffdf;
  uVar1 = DAT_fff4509e;
  DAT_fff4509e = uVar1 & 0xff7f;
  uVar1 = DAT_fff4509e;
  DAT_fff4509e = uVar1 & 0xffbf;
  uVar1 = DAT_fff4509e;
  DAT_fff4509e = uVar1 & 0xffef;
  uVar1 = DAT_fff4509e;
  DAT_fff4509e = uVar1 & 0xfff7;
  uVar1 = DAT_fff4509e;
  DAT_fff4509e = uVar1 & 0xfffb;
  uVar1 = DAT_fff4509e;
  DAT_fff4509e = uVar1 & 0xfffd;
  uVar1 = DAT_fff4509e;
  DAT_fff4509e = uVar1 & 0xfffe;
  REG_EDMA_TCD5 = 0xfff8003a;
  DAT_fff450b0 = 0x40001e18;
  uVar1 = DAT_fff450a4;
  DAT_fff450a4 = uVar1 & 0x7ff;
  uVar1 = DAT_fff450a4;
  DAT_fff450a4 = uVar1 & 0xff07;
  uVar1 = DAT_fff450a4;
  DAT_fff450a4 = uVar1 & 0xfff8 | 1;
  uVar1 = DAT_fff450a4;
  DAT_fff450a4 = uVar1 & 0xf8ff | 0x100;
  DAT_fff450a6 = 0;
  DAT_fff450a8 = 2;
  DAT_fff450ac = 0;
  DAT_fff450b6 = 2;
  DAT_fff450b8 = 0xfffffffc;
  uVar1 = DAT_fff450bc;
  DAT_fff450bc = uVar1 & 0x7fff;
  uVar1 = DAT_fff450bc;
  DAT_fff450bc = uVar1 & 0x8000 | 2;
  uVar1 = DAT_fff450b4;
  DAT_fff450b4 = uVar1 & 0x7fff;
  uVar1 = DAT_fff450b4;
  DAT_fff450b4 = uVar1 & 0x8000 | 2;
  uVar1 = DAT_fff450be;
  DAT_fff450be = uVar1 & 0x3fff;
  uVar1 = DAT_fff450be;
  DAT_fff450be = uVar1 & 0xc0ff;
  uVar1 = DAT_fff450be;
  DAT_fff450be = uVar1 & 0xffdf;
  uVar1 = DAT_fff450be;
  DAT_fff450be = uVar1 & 0xff7f;
  uVar1 = DAT_fff450be;
  DAT_fff450be = uVar1 & 0xffbf;
  uVar1 = DAT_fff450be;
  DAT_fff450be = uVar1 & 0xffef;
  uVar1 = DAT_fff450be;
  DAT_fff450be = uVar1 & 0xfff7;
  uVar1 = DAT_fff450be;
  DAT_fff450be = uVar1 & 0xfffb;
  uVar1 = DAT_fff450be;
  DAT_fff450be = uVar1 & 0xfffd;
  uVar1 = DAT_fff450be;
  DAT_fff450be = uVar1 & 0xfffe;
  REG_EDMA_TCD6 = 0x40002130;
  DAT_fff450d0 = 0xfff8001c;
  uVar1 = DAT_fff450c4;
  DAT_fff450c4 = uVar1 & 0x7ff;
  uVar1 = DAT_fff450c4;
  DAT_fff450c4 = uVar1 & 0xff07;
  uVar1 = DAT_fff450c4;
  DAT_fff450c4 = uVar1 & 0xfff8 | 2;
  uVar1 = DAT_fff450c4;
  DAT_fff450c4 = uVar1 & 0xf8ff | 0x200;
  DAT_fff450c6 = 4;
  DAT_fff450c8 = 0;
  DAT_fff450cc = 0xfffffffc;
  uVar1 = DAT_fff450d4;
  DAT_fff450d4 = uVar1 & 0x7fff;
  uVar1 = DAT_fff450d4;
  DAT_fff450d4 = uVar1 & 0x8000 | 1;
  DAT_fff450d6 = 0;
  DAT_fff450d8 = 0;
  uVar1 = DAT_fff450dc;
  DAT_fff450dc = uVar1 & 0x7fff;
  uVar1 = DAT_fff450dc;
  DAT_fff450dc = uVar1 & 0x8000 | 1;
  uVar1 = DAT_fff450de;
  DAT_fff450de = uVar1 & 0x3fff;
  uVar1 = DAT_fff450de;
  DAT_fff450de = uVar1 & 0xc0ff;
  uVar1 = DAT_fff450de;
  DAT_fff450de = uVar1 & 0xffdf;
  uVar1 = DAT_fff450de;
  DAT_fff450de = uVar1 & 0xff7f;
  uVar1 = DAT_fff450de;
  DAT_fff450de = uVar1 & 0xffbf;
  uVar1 = DAT_fff450de;
  DAT_fff450de = uVar1 & 0xffef;
  uVar1 = DAT_fff450de;
  DAT_fff450de = uVar1 & 0xfff7;
  uVar1 = DAT_fff450de;
  DAT_fff450de = uVar1 & 0xfffb;
  uVar1 = DAT_fff450de;
  DAT_fff450de = uVar1 & 0xfffd;
  uVar1 = DAT_fff450de;
  DAT_fff450de = uVar1 & 0xfffe;
  REG_EDMA_TCD7 = 0xfff8003e;
  DAT_fff450f0 = 0x40001e08;
  uVar1 = DAT_fff450e4;
  DAT_fff450e4 = uVar1 & 0x7ff;
  uVar1 = DAT_fff450e4;
  DAT_fff450e4 = uVar1 & 0xff07;
  uVar1 = DAT_fff450e4;
  DAT_fff450e4 = uVar1 & 0xfff8 | 1;
  uVar1 = DAT_fff450e4;
  DAT_fff450e4 = uVar1 & 0xf8ff | 0x100;
  DAT_fff450e6 = 0;
  DAT_fff450e8 = 2;
  DAT_fff450ec = 0;
  DAT_fff450f6 = 2;
  DAT_fff450f8 = 0xfffffffc;
  uVar1 = DAT_fff450fc;
  DAT_fff450fc = uVar1 & 0x7fff;
  uVar1 = DAT_fff450fc;
  DAT_fff450fc = uVar1 & 0x8000 | 2;
  uVar1 = DAT_fff450f4;
  DAT_fff450f4 = uVar1 & 0x7fff;
  uVar1 = DAT_fff450f4;
  DAT_fff450f4 = uVar1 & 0x8000 | 2;
  uVar1 = DAT_fff450fe;
  DAT_fff450fe = uVar1 & 0x3fff;
  uVar1 = DAT_fff450fe;
  DAT_fff450fe = uVar1 & 0xc0ff;
  uVar1 = DAT_fff450fe;
  DAT_fff450fe = uVar1 & 0xffdf;
  uVar1 = DAT_fff450fe;
  DAT_fff450fe = uVar1 & 0xff7f;
  uVar1 = DAT_fff450fe;
  DAT_fff450fe = uVar1 & 0xffbf;
  uVar1 = DAT_fff450fe;
  DAT_fff450fe = uVar1 & 0xffef;
  uVar1 = DAT_fff450fe;
  DAT_fff450fe = uVar1 & 0xfff7;
  uVar1 = DAT_fff450fe;
  DAT_fff450fe = uVar1 & 0xfffb;
  uVar1 = DAT_fff450fe;
  DAT_fff450fe = uVar1 & 0xfffd;
  uVar1 = DAT_fff450fe;
  DAT_fff450fe = uVar1 & 0xfffe;
  REG_EDMA_TCD8 = 0x400020f0;
  DAT_fff45110 = 0xfff80020;
  uVar1 = DAT_fff45104;
  DAT_fff45104 = uVar1 & 0x7ff;
  uVar1 = DAT_fff45104;
  DAT_fff45104 = uVar1 & 0xff07;
  uVar1 = DAT_fff45104;
  DAT_fff45104 = uVar1 & 0xfff8 | 2;
  uVar1 = DAT_fff45104;
  DAT_fff45104 = uVar1 & 0xf8ff | 0x200;
  DAT_fff45106 = 4;
  DAT_fff45108 = 4;
  DAT_fff4510c = 0xffffffe4;
  uVar1 = DAT_fff45114;
  DAT_fff45114 = uVar1 & 0x7fff;
  uVar1 = DAT_fff45114;
  DAT_fff45114 = uVar1 & 0x8000 | 7;
  DAT_fff45116 = 0;
  DAT_fff45118 = 0;
  uVar1 = DAT_fff4511c;
  DAT_fff4511c = uVar1 & 0x7fff;
  uVar1 = DAT_fff4511c;
  DAT_fff4511c = uVar1 & 0x8000 | 7;
  uVar1 = DAT_fff4511e;
  DAT_fff4511e = uVar1 & 0x3fff;
  uVar1 = DAT_fff4511e;
  DAT_fff4511e = uVar1 & 0xc0ff;
  uVar1 = DAT_fff4511e;
  DAT_fff4511e = uVar1 & 0xffdf;
  uVar1 = DAT_fff4511e;
  DAT_fff4511e = uVar1 & 0xff7f;
  uVar1 = DAT_fff4511e;
  DAT_fff4511e = uVar1 & 0xffbf;
  uVar1 = DAT_fff4511e;
  DAT_fff4511e = uVar1 & 0xffef;
  uVar1 = DAT_fff4511e;
  DAT_fff4511e = uVar1 & 0xfff7;
  uVar1 = DAT_fff4511e;
  DAT_fff4511e = uVar1 & 0xfffb;
  uVar1 = DAT_fff4511e;
  DAT_fff4511e = uVar1 & 0xfffd;
  uVar1 = DAT_fff4511e;
  DAT_fff4511e = uVar1 & 0xfffe;
  REG_EDMA_TCD9 = 0xfff80042;
  DAT_fff45130 = 0x40001de8;
  uVar1 = DAT_fff45124;
  DAT_fff45124 = uVar1 & 0x7ff;
  uVar1 = DAT_fff45124;
  DAT_fff45124 = uVar1 & 0xff07;
  uVar1 = DAT_fff45124;
  DAT_fff45124 = uVar1 & 0xfff8 | 1;
  uVar1 = DAT_fff45124;
  DAT_fff45124 = uVar1 & 0xf8ff | 0x100;
  DAT_fff45126 = 0;
  DAT_fff45128 = 2;
  DAT_fff4512c = 0;
  DAT_fff45136 = 2;
  DAT_fff45138 = 0xfffffff2;
  uVar1 = DAT_fff4513c;
  DAT_fff4513c = uVar1 & 0x7fff;
  uVar1 = DAT_fff4513c;
  DAT_fff4513c = uVar1 & 0x8000 | 7;
  uVar1 = DAT_fff45134;
  DAT_fff45134 = uVar1 & 0x7fff;
  uVar1 = DAT_fff45134;
  DAT_fff45134 = uVar1 & 0x8000 | 7;
  uVar1 = DAT_fff4513e;
  DAT_fff4513e = uVar1 & 0x3fff;
  uVar1 = DAT_fff4513e;
  DAT_fff4513e = uVar1 & 0xc0ff;
  uVar1 = DAT_fff4513e;
  DAT_fff4513e = uVar1 & 0xffdf;
  uVar1 = DAT_fff4513e;
  DAT_fff4513e = uVar1 & 0xff7f;
  uVar1 = DAT_fff4513e;
  DAT_fff4513e = uVar1 & 0xffbf;
  uVar1 = DAT_fff4513e;
  DAT_fff4513e = uVar1 & 0xffef;
  uVar1 = DAT_fff4513e;
  DAT_fff4513e = uVar1 & 0xfff7;
  uVar1 = DAT_fff4513e;
  DAT_fff4513e = uVar1 & 0xfffb;
  uVar1 = DAT_fff4513e;
  DAT_fff4513e = uVar1 & 0xfffd;
  uVar1 = DAT_fff4513e;
  DAT_fff4513e = uVar1 & 0xfffe;
  REG_EDMA_TCD10 = 0x40002038;
  DAT_fff45150 = 0xfff80024;
  uVar1 = DAT_fff45144;
  DAT_fff45144 = uVar1 & 0x7ff;
  uVar1 = DAT_fff45144;
  DAT_fff45144 = uVar1 & 0xff07;
  uVar1 = DAT_fff45144;
  DAT_fff45144 = uVar1 & 0xfff8 | 2;
  uVar1 = DAT_fff45144;
  DAT_fff45144 = uVar1 & 0xf8ff | 0x200;
  DAT_fff45146 = 4;
  DAT_fff45148 = 4;
  DAT_fff4514c = 0xffffff4c;
  uVar1 = DAT_fff45154;
  DAT_fff45154 = uVar1 & 0x7fff;
  uVar1 = DAT_fff45154;
  DAT_fff45154 = uVar1 & 0x8000 | 0x2d;
  DAT_fff45156 = 0;
  DAT_fff45158 = 0;
  uVar1 = DAT_fff4515c;
  DAT_fff4515c = uVar1 & 0x7fff;
  uVar1 = DAT_fff4515c;
  DAT_fff4515c = uVar1 & 0x8000 | 0x2d;
  uVar1 = DAT_fff4515e;
  DAT_fff4515e = uVar1 & 0x3fff;
  uVar1 = DAT_fff4515e;
  DAT_fff4515e = uVar1 & 0xc0ff;
  uVar1 = DAT_fff4515e;
  DAT_fff4515e = uVar1 & 0xffdf;
  uVar1 = DAT_fff4515e;
  DAT_fff4515e = uVar1 & 0xff7f;
  uVar1 = DAT_fff4515e;
  DAT_fff4515e = uVar1 & 0xffbf;
  uVar1 = DAT_fff4515e;
  DAT_fff4515e = uVar1 & 0xffef;
  uVar1 = DAT_fff4515e;
  DAT_fff4515e = uVar1 & 0xfff7;
  uVar1 = DAT_fff4515e;
  DAT_fff4515e = uVar1 & 0xfffb;
  uVar1 = DAT_fff4515e;
  DAT_fff4515e = uVar1 & 0xfffd;
  uVar1 = DAT_fff4515e;
  DAT_fff4515e = uVar1 & 0xfffe;
  REG_EDMA_TCD11 = 0xfff80046;
  DAT_fff45170 = 0x40001d88;
  uVar1 = DAT_fff45164;
  DAT_fff45164 = uVar1 & 0x7ff;
  uVar1 = DAT_fff45164;
  DAT_fff45164 = uVar1 & 0xff07;
  uVar1 = DAT_fff45164;
  DAT_fff45164 = uVar1 & 0xfff8 | 1;
  uVar1 = DAT_fff45164;
  DAT_fff45164 = uVar1 & 0xf8ff | 0x100;
  DAT_fff45166 = 0;
  DAT_fff45168 = 2;
  DAT_fff4516c = 0;
  DAT_fff45176 = 2;
  DAT_fff45178 = 0xffffffa6;
  uVar1 = DAT_fff4517c;
  DAT_fff4517c = uVar1 & 0x7fff;
  uVar1 = DAT_fff4517c;
  DAT_fff4517c = uVar1 & 0x8000 | 0x2d;
  uVar1 = DAT_fff45174;
  DAT_fff45174 = uVar1 & 0x7fff;
  uVar1 = DAT_fff45174;
  DAT_fff45174 = uVar1 & 0x8000 | 0x2d;
  uVar1 = DAT_fff4517e;
  DAT_fff4517e = uVar1 & 0x3fff;
  uVar1 = DAT_fff4517e;
  DAT_fff4517e = uVar1 & 0xc0ff;
  uVar1 = DAT_fff4517e;
  DAT_fff4517e = uVar1 & 0xffdf;
  uVar1 = DAT_fff4517e;
  DAT_fff4517e = uVar1 & 0xff7f;
  uVar1 = DAT_fff4517e;
  DAT_fff4517e = uVar1 & 0xffbf;
  uVar1 = DAT_fff4517e;
  DAT_fff4517e = uVar1 & 0xffef;
  uVar1 = DAT_fff4517e;
  DAT_fff4517e = uVar1 & 0xfff7;
  uVar1 = DAT_fff4517e;
  DAT_fff4517e = uVar1 & 0xfffb;
  uVar1 = DAT_fff4517e;
  DAT_fff4517e = uVar1 & 0xfffd;
  uVar1 = DAT_fff4517e;
  DAT_fff4517e = uVar1 & 0xfffe;
  for (uVar2 = 0xc; uVar2 < 0x20; uVar2 = uVar2 + 1) {
    (&REG_EDMA_TCD0)[uVar2 * 8] = 0;
    (&DAT_fff45010)[uVar2 * 8] = 0;
    (&DAT_fff45004)[uVar2 * 0x10] = (&DAT_fff45004)[uVar2 * 0x10] & 0x7ff;
    (&DAT_fff45004)[uVar2 * 0x10] = (&DAT_fff45004)[uVar2 * 0x10] & 0xff07;
    (&DAT_fff45004)[uVar2 * 0x10] = (&DAT_fff45004)[uVar2 * 0x10] & 0xfff8;
    (&DAT_fff45004)[uVar2 * 0x10] = (&DAT_fff45004)[uVar2 * 0x10] & 0xf8ff;
    (&DAT_fff45006)[uVar2 * 0x10] = 0;
    (&DAT_fff45008)[uVar2 * 8] = 0;
    (&DAT_fff4500c)[uVar2 * 8] = 0;
    (&DAT_fff45016)[uVar2 * 0x10] = 0;
    (&DAT_fff45018)[uVar2 * 8] = 0;
    (&DAT_fff4501c)[uVar2 * 0x10] = (&DAT_fff4501c)[uVar2 * 0x10] & 0x7fff;
    (&DAT_fff4501c)[uVar2 * 0x10] = (&DAT_fff4501c)[uVar2 * 0x10] & 0x8000;
    (&DAT_fff45014)[uVar2 * 0x10] = (&DAT_fff45014)[uVar2 * 0x10] & 0x7fff;
    (&DAT_fff45014)[uVar2 * 0x10] = (&DAT_fff45014)[uVar2 * 0x10] & 0x8000;
    (&DAT_fff4501e)[uVar2 * 0x10] = (&DAT_fff4501e)[uVar2 * 0x10] & 0x3fff;
    (&DAT_fff4501e)[uVar2 * 0x10] = (&DAT_fff4501e)[uVar2 * 0x10] & 0xc0ff;
    (&DAT_fff4501e)[uVar2 * 0x10] = (&DAT_fff4501e)[uVar2 * 0x10] & 0xffdf;
    (&DAT_fff4501e)[uVar2 * 0x10] = (&DAT_fff4501e)[uVar2 * 0x10] & 0xff7f;
    (&DAT_fff4501e)[uVar2 * 0x10] = (&DAT_fff4501e)[uVar2 * 0x10] & 0xffbf;
    (&DAT_fff4501e)[uVar2 * 0x10] = (&DAT_fff4501e)[uVar2 * 0x10] & 0xffef;
    (&DAT_fff4501e)[uVar2 * 0x10] = (&DAT_fff4501e)[uVar2 * 0x10] & 0xfff7;
    (&DAT_fff4501e)[uVar2 * 0x10] = (&DAT_fff4501e)[uVar2 * 0x10] & 0xfffb;
    (&DAT_fff4501e)[uVar2 * 0x10] = (&DAT_fff4501e)[uVar2 * 0x10] & 0xfffd;
    (&DAT_fff4501e)[uVar2 * 0x10] = (&DAT_fff4501e)[uVar2 * 0x10] & 0xfffe;
  }
  return;
}



void init_emios_mcr(void)

{
  uint uVar1;
  
  uVar1 = REG_EMIOS_MCR;
  REG_EMIOS_MCR = uVar1 & 0xffff00ff | 0x4f00;
  uVar1 = REG_EMIOS_MCR;
  REG_EMIOS_MCR = uVar1 & 0xfbffffff | 0x4000000;
  uVar1 = REG_EMIOS_MCR;
  REG_EMIOS_MCR = uVar1 & 0xefffffff | 0x10000000;
  uVar1 = REG_EMIOS_MCR;
  REG_EMIOS_MCR = uVar1 & 0xdfffffff | 0x20000000;
  return;
}



void init_emios_input_capture(int param_1,uint param_2,uint param_3)

{
  (&REG_EMIOS_UC0_CCR)[param_1 * 8] = 0;
  (&REG_EMIOS_UC0_CCR)[param_1 * 8] = (&REG_EMIOS_UC0_CCR)[param_1 * 8] & 0xffffff80 | 5;
  (&REG_EMIOS_UC0_CCR)[param_1 * 8] = (&REG_EMIOS_UC0_CCR)[param_1 * 8] & 0xfffff9ff | 0x600;
  (&REG_EMIOS_UC0_CCR)[param_1 * 8] = (&REG_EMIOS_UC0_CCR)[param_1 * 8] & 0x7fffffff;
  (&REG_EMIOS_UC0_CCR)[param_1 * 8] =
       (param_3 & 1) << 0x11 | (&REG_EMIOS_UC0_CCR)[param_1 * 8] & 0xfffdffff;
  (&REG_EMIOS_UC0_CCR)[param_1 * 8] = (&REG_EMIOS_UC0_CCR)[param_1 * 8] & 0xfdffffff | 0x2000000;
  (&REG_EMIOS_UC0_CCR)[param_1 * 8] =
       (param_2 & 1) << 7 | (&REG_EMIOS_UC0_CCR)[param_1 * 8] & 0xffffff7f;
  (&REG_EMIOS_UC0_CCNTR)[param_1 * 8] = 0;
  (&REG_INTC_PSR0)[*(int *)(&DAT_000886e0 + param_1 * 4)] = 3;
  return;
}



void init_eMIOS(int param_1,uint param_2,uint param_3,uint param_4)

{
  (&REG_EMIOS_UC0_CBDR)[param_1 * 8] = param_2;
  (&REG_EMIOS_UC0_CADR)[param_1 * 8] = param_3;
  (&REG_EMIOS_UC0_CCR)[param_1 * 8] = (&REG_EMIOS_UC0_CCR)[param_1 * 8] & 0xffffff80 | 0x1a;
  (&REG_EMIOS_UC0_CCR)[param_1 * 8] = (&REG_EMIOS_UC0_CCR)[param_1 * 8] & 0xfffff9ff | 0x600;
  (&REG_EMIOS_UC0_CCR)[param_1 * 8] = (&REG_EMIOS_UC0_CCR)[param_1 * 8] & 0x7fffffff;
  (&REG_EMIOS_UC0_CCR)[param_1 * 8] =
       (param_4 & 1) << 0x11 | (&REG_EMIOS_UC0_CCR)[param_1 * 8] & 0xfffdffff;
  (&REG_EMIOS_UC0_CCR)[param_1 * 8] = (&REG_EMIOS_UC0_CCR)[param_1 * 8] & 0xfdffffff | 0x2000000;
  (&REG_EMIOS_UC0_CCNTR)[param_1 * 8] = 0;
  (&REG_INTC_PSR0)[*(int *)(&DAT_000886e0 + param_1 * 4)] = 3;
  return;
}



void emios_isr_vec057(void)

{
  uint uVar1;
  
  uVar1 = REG_EMIOS_UC6_CSR;
  REG_EMIOS_UC6_CSR = uVar1 & 0xfffffffe | 1;
  return;
}



void FUN_000478bc(void)

{
  uint uVar1;
  
  DAT_40001580 = (short)((int)(uint)DAT_40001dd2 >> 4);
  uVar1 = REG_EMIOS_UC20_CSR;
  REG_EMIOS_UC20_CSR = uVar1 & 0xfffffffe | 1;
  return;
}



void FUN_000478ec(void)

{
  DAT_400015a4 = 0;
  return;
}



void emios_isr_vec056(void)

{
  uint uVar1;
  
  uVar1 = REG_EMIOS_UC5_CSR;
  REG_EMIOS_UC5_CSR = uVar1 & 0xfffffffe | 1;
  DAT_400015a4 = 1;
  uVar1 = REG_EMIOS_UC5_CADR;
  return;
}



void FUN_00047930(void)

{
  REG_SIU_PCR179 = 0xd00;
  init_emios_input_capture(0,0,1);
  return;
}



void emios_isr_vec051(void)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = REG_EMIOS_UC0_CSR;
  REG_EMIOS_UC0_CSR = uVar1 & 0xfffffffe | 1;
  DAT_400015a3 = 1;
  uVar1 = REG_EMIOS_UC0_CADR;
  uVar2 = REG_EMIOS_UC0_CBDR;
  DAT_400015ac = uVar1 * 0x100 + uVar2 * -0x100 >> 8;
  if (DAT_4000158c == DAT_400013dc) {
    DAT_40001588 = DAT_40001588 + DAT_400015ac;
  }
  else if (DAT_40001588 != 0) {
    DAT_400015ac = DAT_400015ac + DAT_40001588;
    DAT_40001588 = 0;
  }
  if (DAT_40001588 == 0) {
    DAT_40001582 = DAT_40001582 + 1;
    DAT_40001584 = DAT_40001584 + DAT_400015ac;
    DAT_400013c8 = 100;
    if (DAT_40008fb0 <= DAT_40001582) {
      input_shaft_rpm =
           (u16_rspeed_rpm)
           ((ulonglong)((longlong)(int)(uint)DAT_40008fb0 * 1500000) / (ulonglong)DAT_40001584);
      DAT_40001584 = 0;
      DAT_40001582 = 0;
    }
  }
  if (DAT_4000158c < 0x28) {
    if ((DAT_4000158c == DAT_400013dc) &&
       (((DAT_4000158d == '\x02' || (DAT_4000158d == '\x04')) && (DAT_4000158e == '\0')))) {
      DAT_400013dc = DAT_400013dc + 1;
      DAT_4000158e = '\x01';
    }
    else {
      DAT_4000158e = '\0';
    }
    DAT_4000158c = DAT_4000158c + 1;
  }
  else if (DAT_4000158d == '\0') {
    DAT_400013dc = 0xff;
  }
  else {
    if ((byte)(DAT_4000158d - 1U) < 2) {
      DAT_400013dc = 6;
    }
    else if ((byte)(DAT_4000158d - 3U) < 2) {
      PTR_DAT_400013d8 = (undefined *)(((int)PTR_DAT_400013d8 * 0x7d) % 0x2aaaab);
      DAT_400013dc = (char)PTR_DAT_400013d8 + (char)(ZEXT48(PTR_DAT_400013d8) / 0x28) * -0x28 + 1;
    }
    else {
      DAT_400013dc = 0xff;
    }
    DAT_4000158c = 0;
  }
  return;
}



void FUN_00047bb8(void)

{
  REG_SIU_PCR180 = 0xd00;
  init_emios_input_capture(1,0,1);
  return;
}



void emios_isr_vec052(void)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = REG_EMIOS_UC1_CSR;
  REG_EMIOS_UC1_CSR = uVar1 & 0xfffffffe | 1;
  DAT_400015a2 = 1;
  uVar1 = REG_EMIOS_UC1_CADR;
  uVar2 = REG_EMIOS_UC1_CBDR;
  DAT_400015a8 = uVar1 * 0x100 + uVar2 * -0x100 >> 8;
  if (DAT_40001598 == DAT_400013e4) {
    DAT_40001594 = DAT_40001594 + DAT_400015a8;
  }
  else if (DAT_40001594 != 0) {
    DAT_400015a8 = DAT_400015a8 + DAT_40001594;
    DAT_40001594 = 0;
  }
  if (DAT_40001594 == 0) {
    DAT_4000158f = DAT_4000158f + 1;
    DAT_40001590 = DAT_40001590 + DAT_400015a8;
    DAT_400013c9 = 0x14;
    if (DAT_40008fb1 <= DAT_4000158f) {
      output_shaft_rpm_sensor =
           (u16_rspeed_rpm)
           ((ulonglong)((longlong)(int)(uint)DAT_40008fb1 * 0x14ceb4) / (ulonglong)DAT_40001590);
      DAT_40001590 = 0;
      DAT_4000158f = 0;
    }
  }
  if (DAT_40001598 < 0x2c) {
    if ((DAT_40001598 == DAT_400013e4) &&
       (((DAT_40001599 == '\x02' || (DAT_40001599 == '\x04')) && (DAT_4000159a == '\0')))) {
      DAT_400013e4 = DAT_400013e4 + 1;
      DAT_4000159a = '\x01';
    }
    else {
      DAT_4000159a = '\0';
    }
    DAT_40001598 = DAT_40001598 + 1;
  }
  else if (DAT_40001599 == '\0') {
    DAT_400013e4 = 0xff;
  }
  else {
    if ((byte)(DAT_40001599 - 1U) < 2) {
      DAT_400013e4 = 6;
    }
    else if ((byte)(DAT_40001599 - 3U) < 2) {
      PTR_DAT_400013e0 = (undefined *)(((int)PTR_DAT_400013e0 * 0x7d) % 0x2aaaab);
      DAT_400013e4 = (char)PTR_DAT_400013e0 + (char)(ZEXT48(PTR_DAT_400013e0) / 0x2c) * -0x2c + 1;
    }
    else {
      DAT_400013e4 = 0xff;
    }
    DAT_40001598 = 0;
  }
  return;
}



undefined1
lookup_3D_uint8(uint param_1,uint param_2,byte param_3,byte param_4,int param_5,int param_6,
               int param_7)

{
  short sVar1;
  short sVar2;
  
  sVar2 = 0;
  for (sVar1 = 0;
      (*(byte *)(param_5 + sVar1) < param_3 && ((int)sVar1 < (int)((param_1 & 0xff) - 1)));
      sVar1 = sVar1 + 1) {
  }
  for (; (*(byte *)(param_6 + sVar2) < param_4 && ((int)sVar2 < (int)((param_2 & 0xff) - 1)));
      sVar2 = sVar2 + 1) {
  }
  return *(undefined1 *)((param_1 & 0xff) * (int)sVar2 + param_7 + sVar1);
}



void FUN_00047ed4(void)

{
  return;
}



void FUN_00047ee0(void)

{
  return;
}



void FUN_00047eec(void)

{
  return;
}



void reset_can_rx_timeouts(void)

{
  byte bVar1;
  
  for (bVar1 = 0; bVar1 < 10; bVar1 = bVar1 + 1) {
    if (((&DAT_40000028)[(uint)bVar1 * 5] & 2) != 0) {
      (&discrete_input_state)[bVar1] = 0;
    }
  }
  return;
}



void read_debounced_input(uint param_1)

{
  byte bVar2;
  int iVar1;
  
  bVar2 = (&REG_SIU_GPDI0)[*(byte *)((int)&DAT_4000005c + (param_1 & 0xff))] ^
          (&DAT_40000028)[(param_1 & 0xff) * 5] & 1;
  if (bVar2 == 0) {
    if ((&DAT_40002388)[param_1 & 0xff] != '\0') {
      if (((&DAT_40000028)[(param_1 & 0xff) * 5] & 2) == 0) {
        (&DAT_4000002b)[(param_1 & 0xff) * 5] = (&DAT_4000002a)[(param_1 & 0xff) * 5];
      }
      else {
        (&DAT_4000002b)[(param_1 & 0xff) * 5] = 10;
      }
    }
    (&DAT_40002388)[param_1 & 0xff] = 0;
    if ((&DAT_4000002b)[(param_1 & 0xff) * 5] == '\0') {
      if (((&DAT_40000028)[(param_1 & 0xff) * 5] & 2) == 0) {
        (&discrete_input_state)[param_1 & 0xff] = 0;
      }
      *(undefined1 *)((int)&DAT_4000002c + (param_1 & 0xff) * 5) = 1;
    }
    else {
      iVar1 = (param_1 & 0xff) * 4 + (param_1 & 0xff);
      (&DAT_4000002b)[iVar1] = (&DAT_4000002b)[iVar1] + -1;
    }
  }
  else {
    if ((&DAT_40002388)[param_1 & 0xff] != bVar2) {
      if ((((&DAT_40000028)[(param_1 & 0xff) * 5] & 2) == 0) ||
         ((&discrete_input_state)[param_1 & 0xff] == '\0')) {
        (&DAT_4000002b)[(param_1 & 0xff) * 5] = (&DAT_40000029)[(param_1 & 0xff) * 5];
      }
      else {
        (&DAT_4000002b)[(param_1 & 0xff) * 5] = (&DAT_4000002a)[(param_1 & 0xff) * 5];
      }
    }
    (&DAT_40002388)[param_1 & 0xff] = bVar2;
    if ((&DAT_4000002b)[(param_1 & 0xff) * 5] == '\0') {
      if (((&DAT_40000028)[(param_1 & 0xff) * 5] & 2) == 0) {
        (&discrete_input_state)[param_1 & 0xff] = 1;
      }
      else if (*(char *)((int)&DAT_4000002c + (param_1 & 0xff) * 5) != '\0') {
        (&discrete_input_state)[param_1 & 0xff] = (&discrete_input_state)[param_1 & 0xff] ^ 1;
        *(undefined1 *)((int)&DAT_4000002c + (param_1 & 0xff) * 5) = 0;
      }
    }
    else {
      iVar1 = (param_1 & 0xff) * 4 + (param_1 & 0xff);
      (&DAT_4000002b)[iVar1] = (&DAT_4000002b)[iVar1] + -1;
    }
  }
  return;
}



void FUN_000482b8(void)

{
  byte bVar1;
  
  for (bVar1 = 0; bVar1 < 10; bVar1 = bVar1 + 1) {
    read_debounced_input(bVar1);
  }
  return;
}



void scale_analog_inputs(void)

{
  uint uVar1;
  
  DAT_400015bc = (short)((int)(uint)DAT_40001dba >> 4);
  DAT_400015be = (short)((int)(uint)DAT_40001dce >> 4);
  uVar1 = ((int)(uint)DAT_40001db4 >> 4) + ((uint)DAT_400015ba * 8 - (uint)DAT_400015ba);
  DAT_400015ba = (short)((int)uVar1 >> 3) + (ushort)((int)uVar1 < 0 && (uVar1 & 7) != 0);
  DAT_400015c6 = (short)((int)(uint)DAT_40001db6 >> 4);
  oil_temp_sensor_voltage = (u16_voltage_5_1023v)((int)(uint)DAT_40001db8 >> 4);
  return;
}



void read_atf_temperature(void)

{
  ushort uVar1;
  
  if ((DAT_40001678 & 0x10) == 0) {
    uVar1 = lookup_2D_uint8_interpolated_noaxis
                      (3,(uint8_t)oil_temp_sensor_voltage,CAL_sensor_oil_temp);
    oil_temp_raw = uVar1 & 0xff;
  }
  else {
    oil_temp_raw = (ushort)CAL_oil_temp_fallback;
  }
  if (((DAT_400015b8 & 0x10) == 0) && ((DAT_400015b8 & 1) != 0)) {
    oil_temp_iir_filter_state = (uint)oil_temp_raw * 0xa00;
    DAT_400015b8 = DAT_400015b8 | 0x10;
  }
  oil_temp_iir_filter_state =
       (int)((0xa00 - (uint)CAL_trans_temp_filter_coeff) * oil_temp_iir_filter_state) / 0xa00 +
       (uint)CAL_trans_temp_filter_coeff * (uint)oil_temp_raw;
  oil_temp_unknown = (char)((int)oil_temp_iir_filter_state / 2560);
  return;
}



void init_etpu(void)

{
  undefined4 local_20;
  undefined *local_1c;
  undefined *local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined *local_c;
  undefined *local_8;
  undefined4 local_4;
  
  DAT_400015e4 = &REG_ETPU_MCR;
  DAT_400015e0 = &REG_ETPU_SCM;
  DAT_400015dc = &REG_ETPU_SDM;
  DAT_400015d8 = &DAT_c3fc89fc;
  DAT_400015d4 = &DAT_c3fcc000;
  local_20 = DAT_40000068;
  local_1c = PTR_DAT_4000006c;
  local_18 = PTR_DAT_40000070;
  local_14 = DAT_40000074;
  local_10 = DAT_40000078;
  local_c = PTR_DAT_4000007c;
  local_8 = PTR_DAT_40000080;
  local_4 = DAT_40000084;
  FUN_00042240(&local_20,&DAT_00088850,0x2400,&DAT_00088740,0x110);
  FUN_000423d8();
  return;
}



undefined8
FUN_00048558(byte param_1,uint param_2,int param_3,uint param_4,undefined4 param_5,
            undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9)

{
  undefined4 *puVar1;
  
  *(undefined2 *)(&REG_ETPU_C0SCR_A + (uint)param_1 * 4) = 0xc0c0;
  clear_eTPU_channel(param_1);
  if ((*(uint *)(DAT_400015e4 + (uint)param_1 * 0x10 + 0x400) & 0x7ff) == 0) {
    puVar1 = (undefined4 *)FUN_000423f0(0x18);
    if (puVar1 == (undefined4 *)0x0) {
      return 1;
    }
  }
  else {
    puVar1 = (undefined4 *)eTPU_channel_to_address(param_1);
  }
  *puVar1 = param_5;
  puVar1[1] = param_6;
  puVar1[2] = param_7;
  puVar1[3] = param_8;
  puVar1[4] = param_9;
  puVar1[5] = param_2 & 0xff;
  *(uint *)(DAT_400015e4 + (uint)param_1 * 0x10 + 0x400) =
       param_3 * 0x10000000 + ((uint)((int)puVar1 - DAT_400015dc) >> 3);
  *(uint *)(DAT_400015e4 + (uint)param_1 * 0x10 + 0x404) = param_4 & 0xff;
  *(undefined4 *)(DAT_400015e4 + (uint)param_1 * 0x10 + 0x408) = 3;
  return 0;
}



undefined8
FUN_00048684(byte param_1,int param_2,uint param_3,undefined1 param_4,uint param_5,uint param_6,
            undefined1 param_7)

{
  uint *puVar1;
  
  *(undefined2 *)(&REG_ETPU_C0SCR_A + (uint)param_1 * 4) = 0xc0c0;
  clear_eTPU_channel(param_1);
  if ((*(uint *)(DAT_400015e4 + (uint)param_1 * 0x10 + 0x400) & 0x7ff) == 0) {
    puVar1 = (uint *)FUN_000423f0(0x10);
    if (puVar1 == (uint *)0x0) {
      return 1;
    }
  }
  else {
    puVar1 = (uint *)eTPU_channel_to_address(param_1);
  }
  *puVar1 = param_5 & 0xff;
  puVar1[1] = param_6 & 0xff;
  *(undefined1 *)puVar1 = param_4;
  *(undefined1 *)(puVar1 + 1) = param_7;
  *(undefined1 *)(puVar1 + 2) = 0;
  *(undefined1 *)((int)puVar1 + 9) = 0;
  *(uint *)(DAT_400015e4 + (uint)param_1 * 0x10 + 0x400) =
       param_2 * 0x10000000 + 0x80000 + ((uint)((int)puVar1 - DAT_400015dc) >> 3);
  *(uint *)(DAT_400015e4 + (uint)param_1 * 0x10 + 0x404) = param_3 & 0xff;
  *(undefined4 *)(DAT_400015e4 + (uint)param_1 * 0x10 + 0x408) = 1;
  return 0;
}



undefined8 FUN_000487b8(byte param_1,int param_2,uint param_3,undefined4 param_4,undefined4 param_5)

{
  undefined4 *puVar1;
  
  *(undefined2 *)(&REG_ETPU_C0SCR_A + (uint)param_1 * 4) = 0xc0c0;
  clear_eTPU_channel(param_1);
  if ((*(uint *)(DAT_400015e4 + (uint)param_1 * 0x10 + 0x400) & 0x7ff) == 0) {
    puVar1 = (undefined4 *)FUN_000423f0(0x10);
    if (puVar1 == (undefined4 *)0x0) {
      return 1;
    }
  }
  else {
    puVar1 = (undefined4 *)eTPU_channel_to_address(param_1);
  }
  *puVar1 = param_4;
  puVar1[1] = param_5;
  *(uint *)(DAT_400015e4 + (uint)param_1 * 0x10 + 0x400) =
       param_2 * 0x10000000 + 0x10000 + ((uint)((int)puVar1 - DAT_400015dc) >> 3);
  *(uint *)(DAT_400015e4 + (uint)param_1 * 0x10 + 0x404) = param_3 & 0xff;
  *(undefined4 *)(DAT_400015e4 + (uint)param_1 * 0x10 + 0x408) = 1;
  do {
  } while (*(int *)(DAT_400015e4 + (uint)param_1 * 0x10 + 0x408) != 0);
  return 0;
}



undefined8
FUN_000488e0(byte param_1,int param_2,uint param_3,undefined4 param_4,undefined4 param_5,
            undefined4 param_6)

{
  undefined4 *puVar1;
  
  *(undefined2 *)(&REG_ETPU_C0SCR_A + (uint)param_1 * 4) = 0xc0c0;
  clear_eTPU_channel(param_1);
  if ((*(uint *)(DAT_400015e4 + (uint)param_1 * 0x10 + 0x400) & 0x7ff) == 0) {
    puVar1 = (undefined4 *)FUN_000423f0(0x20);
    if (puVar1 == (undefined4 *)0x0) {
      return 1;
    }
  }
  else {
    puVar1 = (undefined4 *)eTPU_channel_to_address(param_1);
  }
  *puVar1 = param_4;
  puVar1[1] = param_5;
  puVar1[2] = param_6;
  *(uint *)(DAT_400015e4 + (uint)param_1 * 0x10 + 0x400) =
       param_2 * 0x10000000 + 0x30000 + ((uint)((int)puVar1 - DAT_400015dc) >> 3);
  *(uint *)(DAT_400015e4 + (uint)param_1 * 0x10 + 0x404) = param_3 & 0xff;
  *(undefined4 *)(DAT_400015e4 + (uint)param_1 * 0x10 + 0x408) = 1;
  do {
  } while (*(int *)(DAT_400015e4 + (uint)param_1 * 0x10 + 0x408) != 0);
  return 0;
}



undefined8
eTPU_init_pwm_channel
          (byte param_1,int param_2,ulonglong param_3,uint param_4,uint param_5,uint param_6,
          ulonglong param_7)

{
  int *piVar2;
  undefined8 uVar1;
  ulonglong uVar3;
  int iVar4;
  
  clear_eTPU_channel(param_1);
  if ((*(uint *)(DAT_400015e4 + (uint)param_1 * 0x10 + 0x400) & 0x7ff) == 0) {
    piVar2 = (int *)FUN_000423f0(0x18);
    if (piVar2 == (int *)0x0) {
      return 1;
    }
  }
  else {
    piVar2 = (int *)eTPU_channel_to_address(param_1);
  }
  uVar3 = (param_7 & 0xffffffff) / (param_3 & 0xffffffff);
  iVar4 = (int)uVar3;
  if ((iVar4 == 0) || (0x7fffff < uVar3)) {
    uVar1 = 2;
  }
  else {
    *piVar2 = iVar4;
    piVar2[1] = (int)(((longlong)iVar4 * (longlong)(int)(param_4 & 0xffff) & 0xffffffffU) / 10000);
    *(uint *)(DAT_400015e4 + (uint)param_1 * 0x10 + 0x400) =
         param_2 * 0x10000000 + 0x1040000 + ((uint)((int)piVar2 - DAT_400015dc) >> 3);
    *(uint *)(DAT_400015e4 + (uint)param_1 * 0x10 + 0x404) = (param_6 & 0xff) * 2 + (param_5 & 0xff)
    ;
    *(undefined4 *)(DAT_400015e4 + (uint)param_1 * 0x10 + 0x408) = 7;
    do {
    } while (*(int *)(DAT_400015e4 + (uint)param_1 * 0x10 + 0x408) != 0);
    uVar1 = 0;
  }
  return uVar1;
}



void eTPU_calculate_and_set_channel_value(undefined1 param_1,uint param_2)

{
  uint *puVar1;
  longlong lVar2;
  
  puVar1 = (uint *)eTPU_channel_to_address(param_1);
  lVar2 = (longlong)(int)(*puVar1 & 0xffffff) * (longlong)(int)(param_2 & 0xffff);
  u128_divide_to_u64((ulonglong)(*puVar1 & 0xffffff) * (ulonglong)(param_2 & 0xffff) >> 0x20,lVar2,0
                     ,&DAT_00002710);
  puVar1[1] = (uint)lVar2;
  return;
}



void FUN_00048bd0(void)

{
  uint16_t uVar1;
  
  DAT_40002be0 = 0x834;
  uVar1 = CRC16(&LEA_base,0x834);
  DAT_40002be4 = (uint)uVar1;
  if (DAT_400015f2 == '\x01') {
    DAT_40002be4 = uVar1 + 1;
  }
  FUN_0004fa50();
  DAT_40003450 = &DAT_000010a8;
  uVar1 = CRC16(&LEA_base,0x10a4);
  DAT_40003454 = (uint)uVar1;
  if (DAT_400015f2 == '\x02') {
    DAT_40003454 = uVar1 + 1;
  }
  DAT_4000166a = 0;
  WriteExternalEnableImmediate(0);
  EEPROM_write_learned_data(&LEA_base,0x10a8);
  return;
}



void FUN_00048c94(void)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  uint uVar4;
  uint uVar5;
  ushort uVar6;
  ushort uVar7;
  uint16_t uVar9;
  uint16_t uVar10;
  uint16_t uVar11;
  int iVar8;
  bool bVar12;
  bool bVar13;
  
  bVar3 = false;
  DAT_400015f4 = DAT_400015f4 | 1;
  load_saved_LEA(&LEA_base,&DAT_000010a8);
  uVar4 = DAT_40002be4;
  uVar9 = CRC16(&LEA_base,0x834);
  uVar5 = DAT_40003454;
  uVar10 = CRC16(&LEA_base,0x10a4);
  uVar11 = CRC16(LEA_shift_adaptation_history,0x40);
  if (uVar11 != LEA_shift_adaptation_history_crc) {
    LEA_shift_adaptation_history_valid = false;
  }
  uVar6 = DAT_400015f4 | 0x4000;
  if (uVar4 == uVar9) {
    uVar6 = DAT_400015f4;
  }
  uVar7 = uVar6 | 0x8000;
  if (uVar5 == uVar10) {
    uVar7 = uVar6;
  }
  bVar1 = false;
  if (((((DAT_400023b5 == '0') && (DAT_400023b6 == '5')) && (DAT_400023b7 == '0')) &&
      (DAT_400023b8 == '0')) || (DAT_400023b4 == 'D')) {
    bVar1 = true;
  }
  bVar13 = false;
  if (((DAT_400023b5 == '0') && (DAT_400023b6 == '9')) &&
     ((DAT_400023b7 == '0' && (DAT_400023b8 == '0')))) {
    bVar13 = true;
  }
  uVar6 = uVar7 | 0x1000;
  if (!bVar1) {
    uVar6 = uVar7;
  }
  DAT_400015f4 = uVar6 | 0x2000;
  if (!bVar13) {
    DAT_400015f4 = uVar6;
  }
  if ((DAT_400023c2 == '1') && (bVar3 = true, 0x33 < DAT_400023c3)) {
    bVar3 = false;
  }
  bVar2 = false;
  if ((uVar4 != uVar9) || (DAT_40002be0 != 0x834)) {
    bVar2 = true;
  }
  bVar12 = false;
  if ((uVar5 != uVar10) || (DAT_40003450 != &DAT_000010a8)) {
    bVar12 = true;
  }
  if ((bVar3) || (((bVar1 || (bVar2)) && (!bVar13)))) {
    FUN_000499b4();
    DAT_4000344c = 0;
  }
  else if (bVar12) {
    FUN_00049a78();
  }
  else {
    FUN_000490d0();
  }
  if (bVar13) {
    shift_adapt_inhibit = '\0';
  }
  iVar8 = libc_memcmp(s_TCU_V0W00_17_06_2019_DL_BJ2_br_0008ac50,&LEA_base,0x20);
  if (iVar8 == 0) {
    if ((bVar12) || (bVar2)) {
      DAT_400019e8 = DAT_400019e8 | 1;
    }
  }
  else {
    libc_memcpy(&LEA_base,s_TCU_V0W00_17_06_2019_DL_BJ2_br_0008ac50,0x20);
  }
  if (shift_adapt_inhibit == '\x03') {
    shift_adapt_inhibit = DAT_40009029;
  }
  return;
}



void FUN_0004907c(void)

{
  if (DAT_400015f0 == 0x5352) {
    reset_all_shift_adaptation();
    DAT_400015f0 = 0x4b4f;
  }
  return;
}



void FUN_000490b0(void)

{
  FUN_000499e8();
  return;
}



void FUN_000490d0(void)

{
  DAT_400015f4 = DAT_400015f4 | 2;
  DAT_40002cc2 = DAT_40002cc2 & 0xf7;
  DAT_40002cc5 = DAT_40002cc5 & 0xf7;
  DAT_40002cc8 = DAT_40002cc8 & 0xf7;
  DAT_40002ccb = DAT_40002ccb & 0xf7;
  DAT_40002cce = DAT_40002cce & 0xf7;
  DAT_40002cd1 = DAT_40002cd1 & 0xf7;
  DAT_40002cd4 = DAT_40002cd4 & 0xf7;
  DAT_40002cd7 = DAT_40002cd7 & 0xf7;
  DAT_40002cda = DAT_40002cda & 0xf7;
  DAT_40002cdd = DAT_40002cdd & 0xf7;
  DAT_40002ce0 = DAT_40002ce0 & 0xf7;
  DAT_40002ce3 = DAT_40002ce3 & 0xf7;
  DAT_40002ce6 = DAT_40002ce6 & 0xf7;
  DAT_40002ce9 = DAT_40002ce9 & 0xf7;
  obd_P0718_dtc_state = obd_P0718_dtc_state & 0xf7;
  obd_P0717_dtc_state = obd_P0717_dtc_state & 0xf7;
  DAT_40002cf2 = DAT_40002cf2 & 0xf7;
  obd_P0721_dtc_state = obd_P0721_dtc_state & 0xf7;
  obd_P0722_dtc_state = obd_P0722_dtc_state & 0xf7;
  obd_P0723_dtc_state = obd_P0723_dtc_state & 0xf7;
  DAT_40002cfe = DAT_40002cfe & 0xf7;
  DAT_40002d01 = DAT_40002d01 & 0xf7;
  DAT_40002d04 = DAT_40002d04 & 0xf7;
  DAT_40002d07 = DAT_40002d07 & 0xf7;
  DAT_40002d0a = DAT_40002d0a & 0xf7;
  DAT_40002d0d = DAT_40002d0d & 0xf7;
  DAT_40002d10 = DAT_40002d10 & 0xf7;
  DAT_40002d13 = DAT_40002d13 & 0xf7;
  DAT_40002d16 = DAT_40002d16 & 0xf7;
  DAT_40002d19 = DAT_40002d19 & 0xf7;
  DAT_40002d1c = DAT_40002d1c & 0xf7;
  DAT_40002d1f = DAT_40002d1f & 0xf7;
  DAT_40002d22 = DAT_40002d22 & 0xf7;
  DAT_40002d25 = DAT_40002d25 & 0xf7;
  DAT_40002d28 = DAT_40002d28 & 0xf7;
  DAT_40002d2b = DAT_40002d2b & 0xf7;
  DAT_40002d2e = DAT_40002d2e & 0xf7;
  DAT_40002d31 = DAT_40002d31 & 0xf7;
  DAT_40002d34 = DAT_40002d34 & 0xf7;
  DAT_40002d37 = DAT_40002d37 & 0xf7;
  DAT_40002d3a = DAT_40002d3a & 0xf7;
  DAT_40002d3d = DAT_40002d3d & 0xf7;
  DAT_40002d40 = DAT_40002d40 & 0xf7;
  DAT_40002d43 = DAT_40002d43 & 0xf7;
  obd_P0894_dtc_state = obd_P0894_dtc_state & 0xf7;
  DAT_40002d49 = DAT_40002d49 & 0xf7;
  DAT_40002d4c = DAT_40002d4c & 0xf7;
  DAT_40002d4f = DAT_40002d4f & 0xf7;
  DAT_40002da0 = DAT_40002da0 & 0xf7;
  DAT_40002d52 = DAT_40002d52 & 0xf7;
  DAT_40002da3 = DAT_40002da3 & 0xf7;
  DAT_40002d55 = DAT_40002d55 & 0xf7;
  DAT_40002d58 = DAT_40002d58 & 0xf7;
  DAT_40002d5b = DAT_40002d5b & 0xf7;
  DAT_40002d5e = DAT_40002d5e & 0xf7;
  DAT_40002d61 = DAT_40002d61 & 0xf7;
  DAT_40002d64 = DAT_40002d64 & 0xf7;
  DAT_40002d67 = DAT_40002d67 & 0xf7;
  DAT_40002d6a = DAT_40002d6a & 0xf7;
  DAT_40002d6d = DAT_40002d6d & 0xf7;
  DAT_40002d70 = DAT_40002d70 & 0xf7;
  DAT_40002d73 = DAT_40002d73 & 0xf7;
  DAT_40002d76 = DAT_40002d76 & 0xf7;
  DAT_40002d79 = DAT_40002d79 & 0xf7;
  DAT_40002da6 = DAT_40002da6 & 0xf7;
  DAT_40002da9 = DAT_40002da9 & 0xf7;
  DAT_40002d7c = DAT_40002d7c & 0xf7;
  DAT_40002d7f = DAT_40002d7f & 0xf7;
  DAT_40002d82 = DAT_40002d82 & 0xf7;
  DAT_40002dac = DAT_40002dac & 0xf7;
  DAT_40002daf = DAT_40002daf & 0xf7;
  DAT_40002d85 = DAT_40002d85 & 0xf7;
  DAT_40002d88 = DAT_40002d88 & 0xf7;
  DAT_40002d8b = DAT_40002d8b & 0xf7;
  DAT_40002d8e = DAT_40002d8e & 0xf7;
  DAT_40002d91 = DAT_40002d91 & 0xf7;
  DAT_40002d94 = DAT_40002d94 & 0xf7;
  DAT_40002d97 = DAT_40002d97 & 0xf7;
  DAT_40002d9a = DAT_40002d9a & 0xf7;
  DAT_40002d9d = DAT_40002d9d & 0xf7;
  DAT_40002db2 = DAT_40002db2 & 0xf7;
  DAT_40002db5 = DAT_40002db5 & 0xf7;
  DAT_40002db8 = DAT_40002db8 & 0xf7;
  DAT_40002dbb = DAT_40002dbb & 0xf7;
  DAT_40002dbe = DAT_40002dbe & 0xf7;
  DAT_40002dc1 = DAT_40002dc1 & 0xf7;
  DAT_40002dc4 = DAT_40002dc4 & 0xf7;
  DAT_40002dc7 = DAT_40002dc7 & 0xf7;
  DAT_40002dca = DAT_40002dca & 0xf7;
  DAT_40002dcd = DAT_40002dcd & 0xf7;
  DAT_40002dd0 = DAT_40002dd0 & 0xf7;
  DAT_40002dd3 = DAT_40002dd3 & 0xf7;
  DAT_40002dd6 = DAT_40002dd6 & 0xf7;
  DAT_40002dd9 = DAT_40002dd9 & 0xf7;
  return;
}



void FUN_000499b4(void)

{
  DAT_400015f4 = DAT_400015f4 | 0x10;
  FUN_000499e8();
  FUN_00049a78();
  return;
}



void FUN_000499e8(void)

{
  DAT_400015f4 = DAT_400015f4 | 0x20;
  shift_adapt_inhibit = 0;
  reset_all_shift_adaptation();
  DAT_40002bd4 = 0;
  DAT_40002bd6 = 0;
  DAT_40002bd8 = 0;
  DAT_40002bda = 0;
  DAT_40002bdc = 0;
  return;
}



void FUN_00049a78(void)

{
  byte bVar1;
  
  DAT_400015f4 = DAT_400015f4 | 0x40;
  FUN_00049b44();
  FUN_00049e1c();
  FUN_00049ea4();
  for (bVar1 = 0; bVar1 < 0x13; bVar1 = bVar1 + 1) {
    (&DAT_40002e6e)[bVar1] = 0;
  }
  DAT_40003442 = 0;
  DAT_40003443 = 0;
  DAT_40003444 = 0;
  DAT_40003446 = 0;
  DAT_40003448 = 0xffff;
  slip_learn_status_flags_gear6 = 0;
  return;
}



void FUN_00049b44(void)

{
  ulonglong uVar1;
  int iVar2;
  
  DAT_400015f4 = DAT_400015f4 | 0x200;
  for (iVar2 = 0; iVar2 < 10; iVar2 = iVar2 + 1) {
    u16_rspeed_rpm_ARRAY_40002e84[iVar2 * 6] = 0;
    u16_rspeed_rpm_ARRAY_40002e84[iVar2 * 6 + 1] = 0;
    *(undefined1 *)(u16_rspeed_rpm_ARRAY_40002e84 + iVar2 * 6 + 4) = 0;
    (u16_rspeed_rpm_ARRAY_40002e84 + iVar2 * 6 + 2)[0] = 0;
    (u16_rspeed_rpm_ARRAY_40002e84 + iVar2 * 6 + 2)[1] = 0;
  }
  for (iVar2 = 0; iVar2 < 10; iVar2 = iVar2 + 1) {
    (&DAT_40002efc)[iVar2 * 4] = 0;
    (&DAT_40002efe)[iVar2 * 2] = 0;
  }
  for (uVar1 = 0; iVar2 = (int)uVar1, iVar2 < 100; uVar1 = uVar1 + 1) {
    *(undefined2 *)((int)&DAT_40002f24 + (int)((uVar1 & 0xffffffff) << 1)) = 0;
    *(undefined2 *)((int)&DAT_40002fec + (int)((uVar1 & 0xffffffff) << 1)) = 0;
    (&DAT_4000317c)[iVar2] = 0;
    (&DAT_400031e0)[iVar2] = 0;
    *(undefined2 *)((int)&DAT_400030b4 + (int)((uVar1 & 0xffffffff) << 1)) = 0;
    (&DAT_40003244)[iVar2] = 0;
    *(undefined2 *)((int)&DAT_400032a8 + (int)((uVar1 & 0xffffffff) << 1)) = 0;
    *(undefined2 *)((int)&DAT_40003370 + (int)((uVar1 & 0xffffffff) << 1)) = 0;
  }
  DAT_40003438 = 0;
  DAT_4000343a = 0;
  for (iVar2 = 0; iVar2 < 4; iVar2 = iVar2 + 1) {
    (&DAT_40002ddc)[iVar2] = 0;
  }
  for (iVar2 = 0; iVar2 < 4; iVar2 = iVar2 + 1) {
    (&DAT_40002e28)[iVar2] = 0;
  }
  for (iVar2 = 0; iVar2 < 6; iVar2 = iVar2 + 1) {
    (&DAT_40002e0c)[iVar2] = 0;
  }
  for (iVar2 = 0; iVar2 < 8; iVar2 = iVar2 + 1) {
    (&DAT_40002dec)[iVar2] = 0;
  }
  for (iVar2 = 0; iVar2 < 0x20; iVar2 = iVar2 + 1) {
    (LEA_shift_adaptation_history + iVar2 * 2)[0] = '\0';
    (LEA_shift_adaptation_history + iVar2 * 2)[1] = '\0';
  }
  LEA_shift_adaptation_history_crc = CRC16(LEA_shift_adaptation_history,0x40);
  DAT_40002e24 = 0;
  return;
}



void FUN_00049e1c(void)

{
  int iVar1;
  
  DAT_400015f4 = DAT_400015f4 | 0x400;
  DAT_40002c82 = 0x3f5;
  for (iVar1 = 0; iVar1 < 0xb; iVar1 = iVar1 + 1) {
    (&DAT_40002be8)[iVar1] = 0;
    (&DAT_40002bfe)[iVar1] = 0;
  }
  DAT_40002c14 = 0;
  DAT_40002c16 = 0;
  return;
}



void FUN_00049ea4(void)

{
  DAT_400015f4 = DAT_400015f4 | 0x100;
  obd_ii_zero_perm_dtc();
  DAT_40002c38 = 0;
  DAT_40002c3c = 0;
  DAT_40002c3d = 0;
  u16_rspeed_1_4rpm_40002c3e = 0;
  DAT_40002c40 = 0;
  DAT_40002c42 = 0;
  DAT_40002c44 = 0;
  DAT_40002c46 = 0;
  DAT_40002c48 = 0;
  DAT_40002c4a = 0;
  u16_rspeed_1_4rpm_40002c4c = 0;
  DAT_40002c50 = 0;
  DAT_40002c4e = 0;
  DAT_40002c51 = 0;
  DAT_40002c52 = 0;
  DAT_40002c53 = 0;
  DAT_40002c54 = 0;
  DAT_40002c56 = 0;
  DAT_40002c58 = 0;
  DAT_40002c59 = 0;
  DAT_40002c5a = 0;
  DAT_40002c3b = 0;
  DAT_40002cc2 = 0;
  DAT_40002cc3 = 3;
  DAT_40002cc4 = 0x28;
  DAT_40002cc5 = 0;
  DAT_40002cc6 = 3;
  DAT_40002cc7 = 0x28;
  DAT_40002cc8 = 0;
  DAT_40002cc9 = 3;
  DAT_40002cca = 0x28;
  DAT_40002ccb = 0;
  DAT_40002ccc = 3;
  DAT_40002ccd = 0x28;
  DAT_40002cce = 0;
  DAT_40002ccf = 3;
  DAT_40002cd0 = 0x28;
  DAT_40002cd1 = 0;
  DAT_40002cd2 = 3;
  DAT_40002cd3 = 0x28;
  DAT_40002cd4 = 0;
  DAT_40002cd5 = 3;
  DAT_40002cd6 = 0x28;
  DAT_40002cd7 = 0;
  DAT_40002cd8 = 3;
  DAT_40002cd9 = 0x28;
  DAT_40002cda = 0;
  DAT_40002cdb = 3;
  DAT_40002cdc = 0x28;
  DAT_40002cdd = 0;
  DAT_40002cde = 3;
  DAT_40002cdf = 0x28;
  DAT_40002ce0 = 0;
  DAT_40002ce1 = 3;
  DAT_40002ce2 = 0x28;
  DAT_40002ce3 = 0;
  DAT_40002ce4 = 3;
  DAT_40002ce5 = 0x28;
  DAT_40002ce6 = 0;
  DAT_40002ce7 = 3;
  DAT_40002ce8 = 0x28;
  DAT_40002ce9 = 0;
  DAT_40002cea = 3;
  DAT_40002ceb = 0x28;
  obd_P0718_dtc_state = 0;
  DAT_40002ced = 3;
  DAT_40002cee = 0x28;
  obd_P0717_dtc_state = 0;
  DAT_40002cf0 = 3;
  DAT_40002cf1 = 0x28;
  DAT_40002cf2 = 0;
  DAT_40002cf3 = 3;
  DAT_40002cf4 = 0x28;
  obd_P0721_dtc_state = 0;
  DAT_40002cf6 = 3;
  DAT_40002cf7 = 0x28;
  obd_P0722_dtc_state = 0;
  DAT_40002cf9 = 3;
  DAT_40002cfa = 0x28;
  obd_P0723_dtc_state = 0;
  DAT_40002cfc = 3;
  DAT_40002cfd = 0x28;
  DAT_40002cfe = 0;
  DAT_40002cff = 3;
  DAT_40002d00 = 0x28;
  DAT_40002d01 = 0;
  DAT_40002d02 = 3;
  DAT_40002d03 = 0x28;
  DAT_40002d04 = 0;
  DAT_40002d05 = 3;
  DAT_40002d06 = 0x28;
  DAT_40002d07 = 0;
  DAT_40002d08 = 3;
  DAT_40002d09 = 0x28;
  DAT_40002d0a = 0;
  DAT_40002d0b = 3;
  DAT_40002d0c = 0x28;
  DAT_40002d0d = 0;
  DAT_40002d0e = 3;
  DAT_40002d0f = 0x28;
  DAT_40002d10 = 0;
  DAT_40002d11 = 3;
  DAT_40002d12 = 0x28;
  DAT_40002d13 = 0;
  DAT_40002d14 = 3;
  DAT_40002d15 = 0x28;
  DAT_40002d16 = 0;
  DAT_40002d17 = 3;
  DAT_40002d18 = 0x28;
  DAT_40002d19 = 0;
  DAT_40002d1a = 3;
  DAT_40002d1b = 0x28;
  DAT_40002d1c = 0;
  DAT_40002d1d = 3;
  DAT_40002d1e = 0x28;
  DAT_40002d1f = 0;
  DAT_40002d20 = 3;
  DAT_40002d21 = 0x28;
  DAT_40002d22 = 0;
  DAT_40002d23 = 3;
  DAT_40002d24 = 0x28;
  DAT_40002d25 = 0;
  DAT_40002d26 = 3;
  DAT_40002d27 = 0x28;
  DAT_40002d28 = 0;
  DAT_40002d29 = 3;
  DAT_40002d2a = 0x28;
  DAT_40002d2b = 0;
  DAT_40002d2c = 3;
  DAT_40002d2d = 0x28;
  DAT_40002d2e = 0;
  DAT_40002d2f = 3;
  DAT_40002d30 = 0x28;
  DAT_40002d31 = 0;
  DAT_40002d32 = 3;
  DAT_40002d33 = 0x28;
  DAT_40002d34 = 0;
  DAT_40002d35 = 3;
  DAT_40002d36 = 0x28;
  DAT_40002d37 = 0;
  DAT_40002d38 = 3;
  DAT_40002d39 = 0x28;
  DAT_40002d3a = 0;
  DAT_40002d3b = 3;
  DAT_40002d3c = 0x28;
  DAT_40002d3d = 0;
  DAT_40002d3e = 3;
  DAT_40002d3f = 0x28;
  DAT_40002d40 = 0;
  DAT_40002d41 = 3;
  DAT_40002d42 = 0x28;
  DAT_40002d43 = 0;
  DAT_40002d44 = 3;
  DAT_40002d45 = 0x28;
  obd_P0894_dtc_state = 0;
  DAT_40002d47 = 3;
  DAT_40002d48 = 0x28;
  DAT_40002d49 = 0;
  DAT_40002d4a = 3;
  DAT_40002d4b = 0x28;
  DAT_40002d4c = 0;
  DAT_40002d4d = 3;
  DAT_40002d4e = 0x28;
  DAT_40002d4f = 0;
  DAT_40002d50 = 3;
  DAT_40002d51 = 0x28;
  DAT_40002da0 = 0;
  DAT_40002da1 = 3;
  DAT_40002da2 = 0x28;
  DAT_40002d52 = 0;
  DAT_40002d53 = 3;
  DAT_40002d54 = 0x28;
  DAT_40002da3 = 0;
  DAT_40002da4 = 3;
  DAT_40002da5 = 0x28;
  DAT_40002d55 = 0;
  DAT_40002d56 = 3;
  DAT_40002d57 = 0x28;
  DAT_40002d58 = 0;
  DAT_40002d59 = 3;
  DAT_40002d5a = 0x28;
  DAT_40002d5b = 0;
  DAT_40002d5c = 3;
  DAT_40002d5d = 0x28;
  DAT_40002d5e = 0;
  DAT_40002d5f = 3;
  DAT_40002d60 = 0x28;
  DAT_40002d61 = 0;
  DAT_40002d62 = 3;
  DAT_40002d63 = 0x28;
  DAT_40002d64 = 0;
  DAT_40002d65 = 3;
  DAT_40002d66 = 0x28;
  DAT_40002d67 = 0;
  DAT_40002d68 = 3;
  DAT_40002d69 = 0x28;
  DAT_40002d6a = 0;
  DAT_40002d6b = 3;
  DAT_40002d6c = 0x28;
  DAT_40002d6d = 0;
  DAT_40002d6e = 3;
  DAT_40002d6f = 0x28;
  DAT_40002d70 = 0;
  DAT_40002d71 = 3;
  DAT_40002d72 = 0x28;
  DAT_40002d73 = 0;
  DAT_40002d74 = 3;
  DAT_40002d75 = 0x28;
  DAT_40002d76 = 0;
  DAT_40002d77 = 3;
  DAT_40002d78 = 0x28;
  DAT_40002d79 = 0;
  DAT_40002d7a = 3;
  DAT_40002d7b = 0x28;
  DAT_40002da6 = 0;
  DAT_40002da7 = 3;
  DAT_40002da8 = 0x28;
  DAT_40002da9 = 0;
  DAT_40002daa = 3;
  DAT_40002dab = 0x28;
  DAT_40002dca = 0;
  DAT_40002dcb = 3;
  DAT_40002dcc = 0x28;
  DAT_40002dcd = 0;
  DAT_40002dce = 3;
  DAT_40002dcf = 0x28;
  DAT_40002dd0 = 0;
  DAT_40002dd1 = 3;
  DAT_40002dd2 = 0x28;
  DAT_40002dd3 = 0;
  DAT_40002dd4 = 3;
  DAT_40002dd5 = 0x28;
  DAT_40002dd6 = 0;
  DAT_40002dd7 = 3;
  DAT_40002dd8 = 0x28;
  DAT_40002dd9 = 0;
  DAT_40002dda = 3;
  DAT_40002ddb = 0x28;
  DAT_40002d7c = 0;
  DAT_40002d7d = 3;
  DAT_40002d7e = 0x28;
  DAT_40002d7f = 0;
  DAT_40002d80 = 3;
  DAT_40002d81 = 0x28;
  DAT_40002d82 = 0;
  DAT_40002d83 = 3;
  DAT_40002d84 = 0x28;
  DAT_40002dac = 0;
  DAT_40002dad = 3;
  DAT_40002dae = 0x28;
  DAT_40002daf = 0;
  DAT_40002db0 = 3;
  DAT_40002db1 = 0x28;
  DAT_40002d85 = 0;
  DAT_40002d86 = 3;
  DAT_40002d87 = 0x28;
  DAT_40002d88 = 0;
  DAT_40002d89 = 3;
  DAT_40002d8a = 0x28;
  DAT_40002d8b = 0;
  DAT_40002d8c = 3;
  DAT_40002d8d = 0x28;
  DAT_40002d8e = 0;
  DAT_40002d8f = 3;
  DAT_40002d90 = 0x28;
  DAT_40002d91 = 0;
  DAT_40002d92 = 3;
  DAT_40002d93 = 0x28;
  DAT_40002d94 = 0;
  DAT_40002d95 = 3;
  DAT_40002d96 = 0x28;
  DAT_40002d97 = 0;
  DAT_40002d98 = 3;
  DAT_40002d99 = 0x28;
  DAT_40002d9a = 0;
  DAT_40002d9b = 3;
  DAT_40002d9c = 0x28;
  DAT_40002d9d = 0;
  DAT_40002d9e = 3;
  DAT_40002d9f = 0x28;
  DAT_40002db2 = 0;
  DAT_40002db3 = 3;
  DAT_40002db4 = 0x28;
  DAT_40002db5 = 0;
  DAT_40002db6 = 3;
  DAT_40002db7 = 0x28;
  DAT_40002db8 = 0;
  DAT_40002db9 = 3;
  DAT_40002dba = 0x28;
  DAT_40002dbb = 0;
  DAT_40002dbc = 3;
  DAT_40002dbd = 0x28;
  DAT_40002dbe = 0;
  DAT_40002dbf = 3;
  DAT_40002dc0 = 0x28;
  DAT_40002dc1 = 0;
  DAT_40002dc2 = 3;
  DAT_40002dc3 = 0x28;
  DAT_40002dc4 = 0;
  DAT_40002dc5 = 3;
  DAT_40002dc6 = 0x28;
  DAT_40002dc7 = 0;
  DAT_40002dc8 = 3;
  DAT_40002dc9 = 0x28;
  DAT_40002c5c = 0;
  DAT_40002c5e = 0;
  u16_rspeed_1_4rpm_40002c60 = 0;
  DAT_40002c62 = 0;
  DAT_40002c64 = 0;
  DAT_40002c66 = 0;
  DAT_40002c68 = 0;
  DAT_40002c6a = 0;
  DAT_40002c6c = 0;
  DAT_40002c6d = 0;
  DAT_40002c6e = 0;
  DAT_40002c6f = 0;
  DAT_40002c70 = 0;
  DAT_40002c74 = 0;
  DAT_40002c76 = 0;
  DAT_40002c78 = 0;
  DAT_40002c7a = 0;
  DAT_40002c7c = 0;
  DAT_40002c80 = 0;
  DAT_40002c84 = 0;
  DAT_40002c81 = 0;
  DAT_40002c88 = 0;
  return;
}



undefined8 flash_erase(uint param_1,uint param_2,uint param_3)

{
  undefined *puVar1;
  undefined8 uVar2;
  
  puVar1 = &DAT_00009cc0;
  DAT_4000162c = 0;
  DAT_40001620 = param_1;
  DAT_40001624 = param_2;
  DAT_40001628 = param_3;
  uVar2 = (*DAT_00001cd0)(&PTR_REG_FLASH_MCR_400004c0);
  if ((int)uVar2 == 0) {
    if ((DAT_40001620 == 0) || (DAT_40001624 == 0)) {
      if (DAT_40001628 == 0) {
        if (DAT_40001624 == 1) {
          uVar2 = (**(code **)(&UNK_ffff8024 + (int)puVar1))
                            (&PTR_REG_FLASH_MCR_400004c0,4,&DAT_400015fc,&DAT_400015f8);
          if ((int)uVar2 != 0) {
            return uVar2;
          }
          if ((DAT_40001624 == (DAT_40001624 & DAT_400015f8)) &&
             (uVar2 = (**(code **)(&UNK_ffff8028 + (int)puVar1))
                                (&PTR_REG_FLASH_MCR_400004c0,4,DAT_400015f8 & ~DAT_40001624,
                                 0xffffffffa1a11111), (int)uVar2 != 0)) {
            return uVar2;
          }
          uVar2 = (**(code **)(&UNK_ffff8024 + (int)puVar1))
                            (&PTR_REG_FLASH_MCR_400004c0,5,&DAT_400015fc,&DAT_400015f8);
          if ((int)uVar2 != 0) {
            return uVar2;
          }
          if ((DAT_40001624 == (DAT_40001624 & DAT_400015f8)) &&
             (uVar2 = (**(code **)(&UNK_ffff8028 + (int)puVar1))
                                (&PTR_REG_FLASH_MCR_400004c0,5,DAT_400015f8 & ~DAT_40001624,
                                 0xffffffffc3c33333), (int)uVar2 != 0)) {
            return uVar2;
          }
          DAT_4000161c = DAT_400004c4 + 0x40000;
          DAT_40001618 = 0;
        }
      }
      else {
        uVar2 = (**(code **)(&UNK_ffff8028 + (int)puVar1))
                          (&PTR_REG_FLASH_MCR_400004c0,0,1,0xffffffffa1a11111);
        if ((int)uVar2 != 0) {
          return uVar2;
        }
        uVar2 = (**(code **)(&UNK_ffff8028 + (int)puVar1))
                          (&PTR_REG_FLASH_MCR_400004c0,1,1,0xffffffffc3c33333);
        if ((int)uVar2 != 0) {
          return uVar2;
        }
        uVar2 = (**(code **)(&UNK_ffff8024 + (int)puVar1))
                          (&PTR_REG_FLASH_MCR_400004c0,2,&DAT_400015fc,&DAT_400015f8);
        if ((int)uVar2 != 0) {
          return uVar2;
        }
        if ((DAT_40001628 == (DAT_40001628 & DAT_400015f8)) &&
           (uVar2 = (**(code **)(&UNK_ffff8028 + (int)puVar1))
                              (&PTR_REG_FLASH_MCR_400004c0,2,DAT_400015f8 & ~DAT_40001628,
                               0xffffffffa1a11111), (int)uVar2 != 0)) {
          return uVar2;
        }
        uVar2 = (**(code **)(&UNK_ffff8024 + (int)puVar1))
                          (&PTR_REG_FLASH_MCR_400004c0,3,&DAT_400015fc,&DAT_400015f8);
        if ((int)uVar2 != 0) {
          return uVar2;
        }
        if ((DAT_40001628 == (DAT_40001628 & DAT_400015f8)) &&
           (uVar2 = (**(code **)(&UNK_ffff8028 + (int)puVar1))
                              (&PTR_REG_FLASH_MCR_400004c0,3,DAT_400015f8 & ~DAT_40001628,
                               0xffffffffc3c33333), (int)uVar2 != 0)) {
          return uVar2;
        }
        if (DAT_40001628 == 0x10) {
          DAT_4000161c = DAT_400004c4 + 0x20000;
          DAT_40001618 = 0x10000;
        }
        else if (DAT_40001628 == 8) {
          DAT_4000161c = DAT_400004c4 + 0x1c000;
          DAT_40001618 = 0x4000;
        }
        else if (DAT_40001628 == 4) {
          DAT_4000161c = DAT_400004c4 + 0x10000;
          DAT_40001618 = 0xc000;
        }
        else {
          DAT_4000161c = 0;
          DAT_40001618 = 0;
        }
      }
    }
    else {
      uVar2 = (**(code **)(&UNK_ffff8028 + (int)puVar1))
                        (&PTR_REG_FLASH_MCR_400004c0,0,1,0xffffffffa1a11111);
      if ((int)uVar2 != 0) {
        return uVar2;
      }
      uVar2 = (**(code **)(&UNK_ffff8028 + (int)puVar1))
                        (&PTR_REG_FLASH_MCR_400004c0,1,1,0xffffffffc3c33333);
      if ((int)uVar2 != 0) {
        return uVar2;
      }
      uVar2 = (**(code **)(&UNK_ffff8024 + (int)puVar1))
                        (&PTR_REG_FLASH_MCR_400004c0,6,&DAT_400015fc,&DAT_400015f8);
      if ((int)uVar2 != 0) {
        return uVar2;
      }
      if ((DAT_40001620 == (DAT_40001620 & DAT_400015f8)) &&
         (uVar2 = (**(code **)(&UNK_ffff8028 + (int)puVar1))
                            (&PTR_REG_FLASH_MCR_400004c0,6,DAT_400015f8 & ~DAT_40001620,
                             0xffffffffb2b22222), (int)uVar2 != 0)) {
        return uVar2;
      }
      uVar2 = (**(code **)(&UNK_ffff8024 + (int)puVar1))
                        (&PTR_REG_FLASH_MCR_400004c0,4,&DAT_400015fc,&DAT_400015f8);
      if ((int)uVar2 != 0) {
        return uVar2;
      }
      if ((DAT_40001624 == (DAT_40001624 & DAT_400015f8)) &&
         (uVar2 = (**(code **)(&UNK_ffff8028 + (int)puVar1))
                            (&PTR_REG_FLASH_MCR_400004c0,4,DAT_400015f8 & ~DAT_40001624,
                             0xffffffffa1a11111), (int)uVar2 != 0)) {
        return uVar2;
      }
      uVar2 = (**(code **)(&UNK_ffff8024 + (int)puVar1))
                        (&PTR_REG_FLASH_MCR_400004c0,5,&DAT_400015fc,&DAT_400015f8);
      if ((int)uVar2 != 0) {
        return uVar2;
      }
      if ((DAT_40001624 == (DAT_40001624 & DAT_400015f8)) &&
         (uVar2 = (**(code **)(&UNK_ffff8028 + (int)puVar1))
                            (&PTR_REG_FLASH_MCR_400004c0,5,DAT_400015f8 & ~DAT_40001624,
                             0xffffffffc3c33333), (int)uVar2 != 0)) {
        return uVar2;
      }
      DAT_4000161c = DAT_400004c4 + 0x40000;
      DAT_40001618 = 0x40000;
    }
    if (DAT_40001618 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = (**(code **)(&UNK_ffff8014 + (int)puVar1))
                        (&PTR_REG_FLASH_MCR_400004c0,DAT_4000162c,DAT_40001628,DAT_40001624,
                         DAT_40001620,0xffffffffffffffff);
      if (((int)uVar2 == 0) &&
         (uVar2 = (**(code **)(&UNK_ffff8018 + (int)puVar1))
                            (&PTR_REG_FLASH_MCR_400004c0,DAT_4000161c,DAT_40001618,&DAT_40001610,
                             &DAT_40001608,0xffffffffffffffff), (int)uVar2 == 0)) {
        uVar2 = 0;
      }
    }
  }
  return uVar2;
}



undefined8 flash_unlock_sectors(uint param_1,uint param_2,uint param_3)

{
  undefined *puVar1;
  undefined8 uVar2;
  
  puVar1 = &DAT_00009cc0;
  DAT_4000162c = 0;
  DAT_40001620 = param_1;
  DAT_40001624 = param_2;
  DAT_40001628 = param_3;
  uVar2 = (*DAT_00001cd0)(&PTR_REG_FLASH_MCR_400004c0);
  if ((int)uVar2 == 0) {
    if ((DAT_40001620 == 0) || (DAT_40001624 == 0)) {
      if (DAT_40001628 == 0) {
        if (DAT_40001624 == 1) {
          uVar2 = (**(code **)(&UNK_ffff8024 + (int)puVar1))
                            (&PTR_REG_FLASH_MCR_400004c0,4,&DAT_400015fc,&DAT_400015f8);
          if ((int)uVar2 != 0) {
            return uVar2;
          }
          if ((DAT_40001624 == (DAT_40001624 & DAT_400015f8)) &&
             (uVar2 = (**(code **)(&UNK_ffff8028 + (int)puVar1))
                                (&PTR_REG_FLASH_MCR_400004c0,4,DAT_400015f8 & ~DAT_40001624,
                                 0xffffffffa1a11111), (int)uVar2 != 0)) {
            return uVar2;
          }
          uVar2 = (**(code **)(&UNK_ffff8024 + (int)puVar1))
                            (&PTR_REG_FLASH_MCR_400004c0,5,&DAT_400015fc,&DAT_400015f8);
          if ((int)uVar2 != 0) {
            return uVar2;
          }
          if ((DAT_40001624 == (DAT_40001624 & DAT_400015f8)) &&
             (uVar2 = (**(code **)(&UNK_ffff8028 + (int)puVar1))
                                (&PTR_REG_FLASH_MCR_400004c0,5,DAT_400015f8 & ~DAT_40001624,
                                 0xffffffffc3c33333), (int)uVar2 != 0)) {
            return uVar2;
          }
          DAT_4000161c = DAT_400004c4 + 0x40000;
          DAT_40001618 = 0;
        }
      }
      else {
        uVar2 = (**(code **)(&UNK_ffff8028 + (int)puVar1))
                          (&PTR_REG_FLASH_MCR_400004c0,0,1,0xffffffffa1a11111);
        if ((int)uVar2 != 0) {
          return uVar2;
        }
        uVar2 = (**(code **)(&UNK_ffff8028 + (int)puVar1))
                          (&PTR_REG_FLASH_MCR_400004c0,1,1,0xffffffffc3c33333);
        if ((int)uVar2 != 0) {
          return uVar2;
        }
        uVar2 = (**(code **)(&UNK_ffff8024 + (int)puVar1))
                          (&PTR_REG_FLASH_MCR_400004c0,2,&DAT_400015fc,&DAT_400015f8);
        if ((int)uVar2 != 0) {
          return uVar2;
        }
        if ((DAT_40001628 == (DAT_40001628 & DAT_400015f8)) &&
           (uVar2 = (**(code **)(&UNK_ffff8028 + (int)puVar1))
                              (&PTR_REG_FLASH_MCR_400004c0,2,DAT_400015f8 & ~DAT_40001628,
                               0xffffffffa1a11111), (int)uVar2 != 0)) {
          return uVar2;
        }
        uVar2 = (**(code **)(&UNK_ffff8024 + (int)puVar1))
                          (&PTR_REG_FLASH_MCR_400004c0,3,&DAT_400015fc,&DAT_400015f8);
        if ((int)uVar2 != 0) {
          return uVar2;
        }
        if ((DAT_40001628 == (DAT_40001628 & DAT_400015f8)) &&
           (uVar2 = (**(code **)(&UNK_ffff8028 + (int)puVar1))
                              (&PTR_REG_FLASH_MCR_400004c0,3,DAT_400015f8 & ~DAT_40001628,
                               0xffffffffc3c33333), (int)uVar2 != 0)) {
          return uVar2;
        }
        if (DAT_40001628 == 0x10) {
          DAT_4000161c = DAT_400004c4 + 0x20000;
          DAT_40001618 = 0x10000;
        }
        else if (DAT_40001628 == 8) {
          DAT_4000161c = DAT_400004c4 + 0x1c000;
          DAT_40001618 = 0x4000;
        }
        else if (DAT_40001628 == 4) {
          DAT_4000161c = DAT_400004c4 + 0x10000;
          DAT_40001618 = 0xc000;
        }
        else {
          DAT_4000161c = 0;
          DAT_40001618 = 0;
        }
      }
    }
    else {
      uVar2 = (**(code **)(&UNK_ffff8028 + (int)puVar1))
                        (&PTR_REG_FLASH_MCR_400004c0,0,1,0xffffffffa1a11111);
      if ((int)uVar2 != 0) {
        return uVar2;
      }
      uVar2 = (**(code **)(&UNK_ffff8028 + (int)puVar1))
                        (&PTR_REG_FLASH_MCR_400004c0,1,1,0xffffffffc3c33333);
      if ((int)uVar2 != 0) {
        return uVar2;
      }
      uVar2 = (**(code **)(&UNK_ffff8024 + (int)puVar1))
                        (&PTR_REG_FLASH_MCR_400004c0,6,&DAT_400015fc,&DAT_400015f8);
      if ((int)uVar2 != 0) {
        return uVar2;
      }
      if ((DAT_40001620 == (DAT_40001620 & DAT_400015f8)) &&
         (uVar2 = (**(code **)(&UNK_ffff8028 + (int)puVar1))
                            (&PTR_REG_FLASH_MCR_400004c0,6,DAT_400015f8 & ~DAT_40001620,
                             0xffffffffb2b22222), (int)uVar2 != 0)) {
        return uVar2;
      }
      uVar2 = (**(code **)(&UNK_ffff8024 + (int)puVar1))
                        (&PTR_REG_FLASH_MCR_400004c0,4,&DAT_400015fc,&DAT_400015f8);
      if ((int)uVar2 != 0) {
        return uVar2;
      }
      if ((DAT_40001624 == (DAT_40001624 & DAT_400015f8)) &&
         (uVar2 = (**(code **)(&UNK_ffff8028 + (int)puVar1))
                            (&PTR_REG_FLASH_MCR_400004c0,4,DAT_400015f8 & ~DAT_40001624,
                             0xffffffffa1a11111), (int)uVar2 != 0)) {
        return uVar2;
      }
      uVar2 = (**(code **)(&UNK_ffff8024 + (int)puVar1))
                        (&PTR_REG_FLASH_MCR_400004c0,5,&DAT_400015fc,&DAT_400015f8);
      if ((int)uVar2 != 0) {
        return uVar2;
      }
      if ((DAT_40001624 == (DAT_40001624 & DAT_400015f8)) &&
         (uVar2 = (**(code **)(&UNK_ffff8028 + (int)puVar1))
                            (&PTR_REG_FLASH_MCR_400004c0,5,DAT_400015f8 & ~DAT_40001624,
                             0xffffffffc3c33333), (int)uVar2 != 0)) {
        return uVar2;
      }
      DAT_4000161c = DAT_400004c4 + 0x40000;
      DAT_40001618 = 0x40000;
    }
    uVar2 = 0;
  }
  return uVar2;
}



void flash_write(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined *puVar1;
  int iVar2;
  
  puVar1 = &DAT_00009cc0;
  DAT_40001614 = param_2;
  DAT_40001618 = param_3;
  DAT_4000161c = param_1;
  iVar2 = (*DAT_00001cdc)(&PTR_REG_FLASH_MCR_400004c0,param_1,param_3,param_2,0xffffffffffffffff);
  if (iVar2 == 0) {
    (**(code **)(&UNK_ffff8020 + (int)puVar1))
              (&PTR_REG_FLASH_MCR_400004c0,DAT_4000161c,DAT_40001618,DAT_40001614,&DAT_40001610,
               &DAT_40001608,&DAT_40001600,0xffffffffffffffff);
  }
  return;
}



undefined8 init_flash_cr(void)

{
  uint uVar1;
  uint uVar2;
  
  if (DAT_40001620 != 0) {
    uVar1 = REG_FLASH_HSR;
    uVar2 = REG_FLASH_HSR;
    REG_FLASH_HSR = uVar1 & 0xfffffff & ~DAT_40001620 | uVar2 & 0xf0000000;
    uVar1 = REG_FLASH_HLR;
    uVar2 = REG_FLASH_HLR;
    REG_FLASH_HLR = uVar1 & 0xfffffff | DAT_40001620 & 0xfffffff | uVar2 & 0xf0000000;
  }
  if (DAT_40001628 != 0) {
    uVar1 = REG_FLASH_LMSR;
    uVar2 = REG_FLASH_LMSR;
    REG_FLASH_LMSR = uVar1 & 0xffff & ~DAT_40001628 | uVar2 & 0xffff0000;
    uVar1 = REG_FLASH_LMLR;
    uVar2 = REG_FLASH_LMLR;
    REG_FLASH_LMLR = uVar1 & 0xffff | DAT_40001628 & 0xffff | uVar2 & 0xffff0000;
    uVar1 = REG_FLASH_SLMLR;
    uVar2 = REG_FLASH_SLMLR;
    REG_FLASH_SLMLR = uVar1 & 0xffff | DAT_40001628 & 0xffff | uVar2 & 0xffff0000;
  }
  if (DAT_40001624 != 0) {
    uVar1 = REG_FLASH_LMSR;
    uVar2 = REG_FLASH_LMSR;
    REG_FLASH_LMSR = (uVar1 >> 0x10 & 0xf & ~DAT_40001624) << 0x10 | uVar2 & 0xfff0ffff;
    uVar1 = REG_FLASH_LMLR;
    uVar2 = REG_FLASH_LMLR;
    REG_FLASH_LMLR = (uVar1 >> 0x10 & 0xf | DAT_40001624 & 0xf) << 0x10 | uVar2 & 0xfff0ffff;
    uVar1 = REG_FLASH_SLMLR;
    uVar2 = REG_FLASH_SLMLR;
    REG_FLASH_SLMLR = (uVar1 >> 0x10 & 0xf | DAT_40001624 & 0xf) << 0x10 | uVar2 & 0xfff0ffff;
  }
  return 0;
}



void busy_wait_50k(void)

{
  uint uVar1;
  
  for (uVar1 = 0; uVar1 < 50000; uVar1 = uVar1 + 1) {
    FUN_00047ed4();
  }
  return;
}



void EEPROM_write_learned_data(byte *data,size_t size)

{
  longlong lVar1;
  uint uVar2;
  uint uVar3;
  byte local_20 [32];
  
  FUN_00047eec();
  lVar1 = ((((ulonglong)size & 0xffff) << 0x20) >> 0x23) * 8;
  uVar3 = size & 7;
  FUN_00047ed4();
  flash_erase(0,0,4);
  FUN_00047ed4();
  flash_write(0x10000,data,lVar1);
  FUN_00047ed4();
  if ((size & 7) != 0) {
    for (uVar2 = 0; (uVar2 & 0xff) < uVar3; uVar2 = uVar2 + 1) {
      local_20[uVar2 & 0xff] = data[(uVar2 & 0xff) + (int)lVar1];
    }
    for (; (uVar3 & 0xff) < 8; uVar3 = uVar3 + 1) {
      local_20[uVar3 & 0xff] = 0xff;
    }
    flash_write(lVar1 + 0x10000,local_20,8);
    FUN_00047ed4();
  }
  init_flash_cr();
  busy_wait_50k();
  FUN_00047ee0();
  return;
}



void load_saved_LEA(undefined1 *param_1,short param_2)

{
  undefined1 uVar1;
  bool bVar2;
  undefined1 *puVar3;
  
  puVar3 = &DAT_00010000;
  FUN_00047ed4();
  while (bVar2 = param_2 != 0, param_2 = param_2 + -1, bVar2) {
    uVar1 = *puVar3;
    puVar3 = puVar3 + 1;
    *param_1 = uVar1;
    param_1 = param_1 + 1;
  }
  FUN_00047ed4();
  return;
}



void init_flash_ctrl(void)

{
  uint uVar1;
  
  FUN_00047eec();
  uVar1 = REG_FLASH_MCR;
  REG_FLASH_MCR = uVar1 | 0x8000;
  if ((eeprom_flash_erase_pending_flags & 1) != 0) {
    FUN_00047ed4();
    flash_erase(0,0,4);
  }
  if ((eeprom_flash_erase_pending_flags & 2) != 0) {
    FUN_00047ed4();
    flash_erase(0,0,8);
  }
  FUN_00047ed4();
  init_flash_cr();
  FUN_00047ee0();
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



void EEPROM_erase_coding(void)

{
  FUN_00047eec();
  flash_erase(0,0,8);
  FUN_00047ee0();
  return;
}



void flash_write_cod_data(uint param_1,int param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined1 local_20 [32];
  
  FUN_00047eec();
  uVar1 = param_1 & 0xfffffff8;
  if (((0x1bfff < param_1) && (param_1 < 0x20000)) && (param_1 == uVar1)) {
    WriteExternalEnableImmediate(0);
    flash_unlock_sectors(0,0,8);
    iVar2 = ((int)(param_3 & 0xffff) >> 3) * 8;
    param_3 = param_3 & 7;
    FUN_00047ed4();
    flash_write(uVar1,param_2,iVar2);
    FUN_00047ed4();
    if (param_3 != 0) {
      for (uVar3 = 0; (uVar3 & 0xff) < param_3; uVar3 = uVar3 + 1) {
        local_20[uVar3 & 0xff] = *(undefined1 *)((uVar3 & 0xff) + param_2 + iVar2);
      }
      for (; (param_3 & 0xff) < 8; param_3 = param_3 + 1) {
        local_20[param_3 & 0xff] = 0xff;
      }
      flash_write(uVar1 + iVar2,local_20,8);
      FUN_00047ed4();
    }
    init_flash_cr();
    WriteExternalEnableImmediate(1);
  }
  FUN_00047ee0();
  return;
}



void FUN_0004c4f8(void)

{
  if (DAT_400090c0 == '\x02') {
    if (DAT_40001653 == '\x01') {
      DAT_40001653 = '\x02';
    }
    else if (DAT_40001653 == '\x02') {
      DAT_40001aca = DAT_40001aca | 0x10;
      DAT_40001653 = '\x04';
      DAT_40001652 = 0;
    }
    else if (DAT_40001653 == '\x04') {
      if ((DAT_40001652 < DAT_40009155) && (ips_gear_cur != (GEAR_INVALID8|GEAR_INVALID7))) {
        DAT_40001652 = DAT_40001652 + 1;
      }
      else {
        DAT_40001652 = 0;
        DAT_40001aca = DAT_40001aca & 0xef;
        DAT_40001653 = '\0';
      }
    }
  }
  return;
}



void power_off_handler(void)

{
  bool bVar1;
  char cVar4;
  short sVar2;
  ushort uVar3;
  
  bVar1 = false;
  if (DAT_400015c6 < (ushort)((ushort)DAT_40008fb2 << 2)) {
    if ((((DAT_40002bdc == '\0') && (cVar4 = FUN_0004ca5c(), cVar4 == '\x01')) ||
        (((DAT_4000346e == '\x06' || ((DAT_40001678 & 1) != 0)) &&
         ((output_shaft_rpm == 0 && (cVar4 = FUN_0004ca5c(), cVar4 == '\x01')))))) ||
       ((DAT_4000346e != '\x06' &&
        ((DAT_40001ac4 != '\0' ||
         (((sVar2 = get_shift_lever_pos_raw___(), sVar2 == -1 || ((DAT_40001636 & 8) != 0)) &&
          (cVar4 = FUN_0004ca5c(), cVar4 == '\x01')))))))) {
      if ((DAT_40001636 & 1) == 0) {
        reset_can_rx_timeouts();
      }
      DAT_40001aca = DAT_40001aca & 0xf7;
      DAT_40001636 = DAT_40001636 & 0xed | 1;
      bVar1 = false;
      DAT_40001654 = -0x6a;
      if (((tach_rpm == 0) && (input_shaft_rpm == 0)) &&
         (((DAT_400013b8 == 0 || (DAT_40002bdc == '\0')) ||
          (((DAT_40001840 & 0x40000) != 0 && ((DAT_40001844 & 0x40000) != 0)))))) {
        if (DAT_4000163e == '\0') {
          FUN_00050794();
          FUN_00048bd0();
          DAT_4000163e = '\x01';
          WriteExternalEnableImmediate(1);
        }
        REG_SIU_GPDO203 = 0;
        FUN_000507a4();
      }
    }
    else if (DAT_400090c0 == '\x01') {
      bVar1 = true;
      if (DAT_40001654 == '\0') {
        DAT_40001636 = DAT_40001636 | 0x18;
        DAT_40001aca = DAT_40001aca | 8;
      }
      cVar4 = FUN_0004ca5c();
      if (cVar4 == '\x01') {
        DAT_40001636 = DAT_40001636 & 0xef;
        DAT_40001aca = DAT_40001aca & 0xf7;
      }
    }
    else if ((DAT_400090c0 == '\0') || (DAT_400090c0 == '\x02')) {
      if ((ips_gear_cur == NEUTRAL) &&
         (((DAT_40001678 & 0x20000) == 0 && ((DAT_40001636 & 4) == 0)))) {
        DAT_40001636 = DAT_40001636 & 0xfe | 2;
      }
      else if ((DAT_40001678 & 0x20000) != 0) {
        DAT_40001636 = DAT_40001636 & 0xfd;
      }
      bVar1 = true;
    }
    DAT_400015b8 = DAT_400015b8 & 0xffee;
  }
  else {
    DAT_400015b8 = DAT_400015b8 | 1;
    REG_SIU_GPDO203 = 1;
    bVar1 = true;
    DAT_40001654 = -0x6a;
    DAT_40001636 = DAT_40001636 & 4;
    DAT_40001aca = DAT_40001aca & 0xf7;
    if (tach_rpm != 0) {
      DAT_40001636 = 0;
    }
  }
  if (bVar1) {
    if (DAT_40001678 == 0) {
      uVar3 = lookup_3D_uint8(8,8,oil_temp_unknown,0,&DAT_400098ce,s__400098d6,s_ffffffff_400098de);
      DAT_4000163c = (uVar3 & 0xff) * 5;
    }
    else {
      DAT_4000163c = 1;
    }
    DAT_400013b8 = (uint)DAT_4000163c * 200;
    DAT_400013ea = 'd';
  }
  else if (DAT_400013ea == '\0') {
    DAT_400013b8 = 0;
  }
  return;
}



void read_decode_siu_gpio_c3f906cb(void)

{
  byte bVar1;
  
  bVar1 = REG_SIU_GPDO203;
  DAT_40001630 = (char)((ulonglong)(LZCOUNT(bVar1 - 1) << 0x20) >> 0x25);
  DAT_40001631 = (ushort)((ushort)DAT_40008fb2 << 2) <= DAT_400015c6;
  DAT_40001656 = (byte)(-(ulonglong)DAT_400023a9 >> 0x18) >> 7;
  return;
}



ulonglong FUN_0004ca5c(void)

{
  ulonglong uVar1;
  
  if (DAT_400090c0 == '\x01') {
    uVar1 = (-(ulonglong)DAT_40001656 << 0x20) >> 0x3f;
  }
  else if ((DAT_400090c0 == '\0') || (DAT_400090c0 == '\x02')) {
    uVar1 = FUN_00056148();
  }
  else {
    uVar1 = 3;
  }
  return uVar1;
}



void FUN_0004cadc(void)

{
  if ((DAT_40001631 != '\0') && (DAT_40001633 == '\x02')) {
    DAT_400013e9 = 0;
  }
  if ((DAT_40001631 == '\0') || (DAT_400013e8 <= DAT_400013e9)) {
    DAT_40001633 = 0;
    if (DAT_40001631 == '\0') {
      DAT_40001633 = 2;
    }
  }
  else {
    DAT_400013e9 = DAT_400013e9 + 1;
    DAT_40001633 = 1;
  }
  FUN_0004d338();
  if (DAT_400013ea != '\0') {
    if (((((uint)((int)(uint)DAT_40001dbc >> 4) < 0x200) && ((DAT_40002d28 & 4) == 0)) &&
        ((uint)((int)(uint)DAT_40001dc2 >> 4) < 0x200)) && ((DAT_40002d3a & 4) == 0)) {
      DAT_400013ea = DAT_400013ea + -1;
    }
    else {
      DAT_400013ea = 'd';
    }
  }
  if (DAT_400013eb == '\0') {
    if (DAT_4000163a == '\0') {
      DAT_4000163a = '\x01';
    }
  }
  else if (((uint)((int)(uint)DAT_40001dbc >> 4) < 0x200) && ((DAT_40002d28 & 4) == 0)) {
    DAT_400013eb = DAT_400013eb + -1;
  }
  else {
    DAT_400013eb = 'd';
  }
  return;
}



uint16_t CRC16(byte *data,size_t size)

{
  ulonglong uVar1;
  uint uVar2;
  
  uVar2 = 0;
  for (uVar1 = (ulonglong)(int)size; (uVar1 & 0xffff) != 0; uVar1 = uVar1 - 1) {
    FUN_00047ed4();
    uVar2 = (int)uVar2 >> 8 ^ (uint)*(ushort *)((int)&CRC16_salt + ((uVar2 ^ *data) & 0xff) * 2);
    data = data + 1;
  }
  return (uint16_t)uVar2;
}



void update_siu_gpio_outputs_c0c2(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  uVar1 = lookup_2D_uint8_interpolated(8,vehicle_speed,s_22222222_4000d3fe,s__<Px_4000d3f6);
  uVar2 = lookup_2D_uint8_interpolated(8,vehicle_speed,s__4000d40e,s__<Px_4000d406);
  if (((uint)tach_rpm < (uint)revlimit_hard_from_ecu << 2) && (DAT_40001c38 != '\x01')) {
    iVar3 = int_abs(DAT_40001712);
    if ((iVar3 < (int)(uVar1 & 0xff)) &&
       ((iVar3 = int_abs(DAT_40001712), iVar3 < (int)(uVar2 & 0xff) ||
        (((DAT_40001ac5 & 2) == 0 && ((DAT_40001ac6 & 2) == 0)))))) {
      if (DAT_40001632 == '\0') {
        DAT_40001ac5 = DAT_40001ac5 & 0xfd;
        DAT_40001ac6 = DAT_40001ac6 & 0xfd;
      }
    }
    else {
      DAT_40001ac5 = DAT_40001ac5 | 2;
      DAT_40001ac6 = DAT_40001ac6 | 2;
      DAT_40001632 = DAT_4000904a;
    }
  }
  else {
    DAT_40001ac5 = DAT_40001ac5 & 0xfd;
    DAT_40001ac6 = DAT_40001ac6 & 0xfd;
  }
  if ((((DAT_40001840 & 0x8000) == 0) || ((DAT_40001844 & 0x8000) == 0)) &&
     ((gear_request != GEAR_REV || ((DAT_40001678 & 1) != 0)))) {
    if ((DAT_40001844 & 0x8000) == 0) {
      REG_SIU_GPDO194 = 0;
    }
  }
  else {
    REG_SIU_GPDO194 = 1;
  }
  if ((((DAT_40001840 & 0x4000) == 0) || ((DAT_40001844 & 0x4000) == 0)) &&
     (((ushort)((ushort)DAT_40008fb2 << 2) <= DAT_400015c6 ||
      (((DAT_40001c39 == '\t' && (DAT_40001438 == DAT_40002bda)) && (DAT_4000346e != '\x06')))))) {
    if ((DAT_40001844 & 0x4000) == 0) {
      REG_SIU_GPDO192 = 0;
    }
  }
  else {
    REG_SIU_GPDO192 = 1;
  }
  return;
}



void FUN_0004cf70(void)

{
  bool bVar1;
  uint uVar2;
  ushort uVar3;
  byte bVar4;
  
  if (DAT_40001644 == '\0') {
    if ((DAT_4000170a == 0) || (DAT_40001708 == 0)) {
      DAT_40001646 = 0;
    }
    else {
      DAT_40001646 = (short)(((uint)DAT_4000170a + (uint)DAT_40001708 & 0xffff) / 0x14);
    }
    if ((DAT_40001648 == 0) || (DAT_40001646 == 0)) {
      DAT_40001642 = 0;
    }
    else {
      DAT_40001642 = DAT_40001646 - DAT_40001648;
    }
    uVar2 = (0x100 - (uint)DAT_40009040) * (int)DAT_40001640;
    DAT_40001640 = (short)(uVar2 >> 8) + (ushort)((int)uVar2 < 0 && (uVar2 & 0xff) != 0) +
                   (ushort)DAT_40009040 * DAT_40001642;
    _load_signed = (short)((DAT_40001640 * 0x3d09) / (int)((uint)DAT_40009041 * 0x113e8));
    DAT_40001648 = DAT_40001646;
    DAT_40001644 = DAT_40009041;
  }
  else {
    DAT_40001644 = DAT_40001644 - 1;
  }
  if (_load_signed < 0) {
    if (_load_signed < -100) {
      uVar3 = 100;
    }
    else {
      uVar3 = -_load_signed & 0xff;
    }
  }
  else {
    uVar3 = 0;
  }
  if (DAT_4000164a == '\0') {
    if (DAT_40009082 == 0) {
      (&DAT_40003458)[DAT_4000164e] = (char)DAT_4000164c;
    }
    else {
      (&DAT_40003458)[DAT_4000164e] = (char)(DAT_4000164c / DAT_40009082);
    }
    bVar1 = DAT_4000164e < 9;
    bVar4 = DAT_4000164e + 1;
    DAT_4000164e = 0;
    if (bVar1) {
      DAT_4000164e = bVar4;
    }
    DAT_40001637 = 0;
    for (bVar4 = 0; bVar4 < 10; bVar4 = bVar4 + 1) {
      if (DAT_40001637 < (byte)(&DAT_40003458)[bVar4]) {
        DAT_40001637 = (&DAT_40003458)[bVar4];
      }
    }
    DAT_4000164a = DAT_40009082;
    DAT_4000164c = 0;
  }
  else {
    DAT_4000164c = DAT_4000164c + uVar3;
    DAT_4000164a = DAT_4000164a - 1;
  }
  return;
}



void FUN_0004d1e4(void)

{
  DAT_4000165c = DAT_4000165c | ~(ushort)DAT_4000237c;
  return;
}



void FUN_0004d204(void)

{
  byte bVar1;
  
  bVar1 = DAT_4000171e & 0xbf;
  if (DAT_400023a5 == '\0') {
    bVar1 = DAT_4000171e | 0x40;
  }
  DAT_4000171e = bVar1;
  if ((bVar1 & 0xa2) == 0) {
    if ((bVar1 & 0x51) == 0) {
      DAT_40001655 = 0;
    }
    else {
      DAT_40001655 = 1;
    }
  }
  else if (((bVar1 & 0x80) == 0) && ((bVar1 & 0x20) == 0)) {
    if ((bVar1 & 0x40) == 0) {
      DAT_40001655 = 0;
      if ((DAT_40002cf2 & 8) == 0) {
        DAT_40001655 = 0xff;
      }
    }
    else if ((DAT_40002cfe & 8) == 0) {
      DAT_40001655 = 0xff;
    }
    else {
      DAT_40001655 = 1;
    }
  }
  else if ((bVar1 & 2) == 0) {
    if ((bVar1 & 1) == 0) {
      DAT_40001655 = 0;
    }
    else {
      DAT_40001655 = 1;
    }
  }
  else {
    DAT_40001655 = 0xff;
  }
  return;
}



void FUN_0004d338(void)

{
  int iVar1;
  
  if ((DAT_400015b8 & 1) == 0) {
    DAT_40001658 = 0;
  }
  else if (DAT_40001658 < 0xfffffff) {
    iVar1 = (int)((ulonglong)((longlong)(int)(uint)vehicle_speed____ * -0x49f49f49) >> 0x20) +
            (uint)vehicle_speed____;
    DAT_40001658 = DAT_40001658 + ((iVar1 >> 8) - (iVar1 >> 0x1f));
  }
  return;
}



void adaptation_drift_monitor(void)

{
  byte i;
  uint uVar1;
  byte bVar2;
  
  if (DAT_40001638 != '\0') {
    DAT_4000344c = 0;
    DAT_40001638 = '\0';
    for (i = 0; i < 0x13; i = i + 1) {
      slip_learn_status_flags_gear6 = 0xff;
      (&DAT_40002e6e)[i] = 0;
    }
  }
  uVar1 = lookup_2D_uint8_interpolated
                    (6,oil_temp_unknown,&DAT_400097dc,CAL_driving_shift_aggressiveness_blend + 4);
  uVar1 = (int)((uint)vehicle_speed * (uVar1 & 0xff)) >> 1;
  DAT_40001650 = (short)uVar1;
  if (0xffffffff - DAT_4000344c < uVar1) {
    DAT_4000344c = 0xffffffff;
  }
  else {
    DAT_4000344c = DAT_4000344c + uVar1;
  }
  if ((DAT_4000344c < (uint)DAT_40009090 * 3600000) || (DAT_40009090 == 0)) {
    DAT_40001639 = DAT_40001639 & 0xfe;
  }
  else {
    DAT_40001639 = DAT_40001639 | 1;
  }
  DAT_4000164f = 0;
  for (bVar2 = 0; bVar2 < 0x13; bVar2 = bVar2 + 1) {
    if (DAT_4000164f <
        (&LEA_shift_profile_adapt)[(uint)bVar2 * 10 + (uint)(byte)(&DAT_40002b8e)[bVar2]]) {
      DAT_4000164f = (&LEA_shift_profile_adapt)
                     [(uint)bVar2 * 10 + (uint)(byte)(&DAT_40002b8e)[bVar2]];
    }
  }
  if (((DAT_4000344c < (uint)DAT_400090b3 * 360000) || (DAT_4000164f <= DAT_400090d7)) ||
     (DAT_400090b3 == 0)) {
    DAT_40001639 = DAT_40001639 & 0xfd;
  }
  else {
    DAT_40001639 = DAT_40001639 | 2;
  }
  if (((DAT_40001639 == 0) || (DAT_40001540 == 0)) || ((uint)DAT_400090c1 * 200 < DAT_40001540)) {
    bVar2 = DAT_40001639 & 0xfb;
    if ((DAT_40001639 & 4) == 0) {
      bVar2 = DAT_40001639;
    }
  }
  else {
    bVar2 = DAT_40001639 | 4;
  }
  DAT_40001639 = bVar2;
  return;
}



ulonglong lookup_2D_uint8_interpolated(ushort x_size,byte x,byte *lut,byte *x_axis)

{
  short sVar1;
  short sVar2;
  ulonglong uVar3;
  
  sVar1 = (x_size & 0xff) - 1;
  sVar2 = 0;
  if (*x_axis < x) {
    if (x < x_axis[sVar1]) {
      for (; (x_axis[sVar2] < x && (sVar2 < sVar1)); sVar2 = sVar2 + 1) {
      }
      if (x == x_axis[sVar2]) {
        uVar3 = (ulonglong)lut[sVar2];
      }
      else if (x_axis[sVar2] == x_axis[sVar2 + -1]) {
        uVar3 = (ulonglong)lut[sVar2];
      }
      else {
        uVar3 = (ulonglong)lut[sVar2 + -1] +
                (longlong)
                ((int)((int)(short)((ushort)lut[sVar2] - (ushort)lut[sVar2 + -1]) *
                      ((uint)x - (uint)x_axis[sVar2 + -1])) /
                (int)((uint)x_axis[sVar2] - (uint)x_axis[sVar2 + -1])) & 0xff;
      }
    }
    else {
      uVar3 = (ulonglong)lut[sVar1];
    }
  }
  else {
    uVar3 = (ulonglong)*lut;
  }
  return uVar3;
}



ulonglong lookup_2D_uint16_interpolated
                    (ushort param_1,ushort param_2,ushort *param_3,ushort *param_4)

{
  short sVar1;
  short sVar2;
  ulonglong uVar3;
  
  sVar1 = (param_1 & 0xff) - 1;
  sVar2 = 0;
  if (*param_4 < param_2) {
    if (param_2 < param_4[sVar1]) {
      for (; (param_4[sVar2] < param_2 && (sVar2 < sVar1)); sVar2 = sVar2 + 1) {
      }
      if (param_2 == param_4[sVar2]) {
        uVar3 = (ulonglong)param_3[sVar2];
      }
      else if (param_4[sVar2] == param_4[sVar2 + -1]) {
        uVar3 = (ulonglong)param_3[sVar2];
      }
      else {
        uVar3 = (ulonglong)param_3[sVar2 + -1] +
                (longlong)
                ((int)((int)(short)(param_3[sVar2] - param_3[sVar2 + -1]) *
                      ((uint)param_2 - (uint)param_4[sVar2 + -1])) /
                (int)((uint)param_4[sVar2] - (uint)param_4[sVar2 + -1])) & 0xffff;
      }
    }
    else {
      uVar3 = (ulonglong)param_3[sVar1];
    }
  }
  else {
    uVar3 = (ulonglong)*param_3;
  }
  return uVar3;
}



ulonglong lookup_2D_uint8_interpolated_noaxis(uint8_t size,uint8_t val,uint8_t *lut)

{
  uint uVar1;
  uint uVar2;
  ulonglong uVar3;
  
  uVar3 = (ulonglong)(((int)(char)val & 0xffffU) << ((int)(char)size & 0x3fU)) & 0xffff;
  uVar2 = (uint)uVar3;
  uVar1 = uVar2 >> 8;
  if (lut[uVar2 >> 8] == lut[(uVar2 >> 8) + 1]) {
    uVar3 = (ulonglong)lut[uVar1];
  }
  else {
    uVar2 = (int)(short)((ushort)lut[uVar1 + 1] - (ushort)lut[uVar1]) *
            (uVar2 - (int)(short)(((uVar3 << 0x20) >> 0x28) << 8));
    uVar3 = (ulonglong)lut[uVar1] +
            (longlong)((int)uVar2 >> 8) + (ulonglong)((int)uVar2 < 0 && (uVar2 & 0xff) != 0) & 0xff;
  }
  return uVar3;
}



uint lookup_3D_uint8_interpolated
               (ushort param_1,ushort param_2,ushort param_3,ushort param_4,byte *param_5,
               byte *param_6,byte *param_7)

{
  byte bVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  short sVar5;
  uint uVar6;
  ushort uVar7;
  ushort uVar8;
  uint uVar9;
  
  param_1 = param_1 & 0xff;
  uVar2 = param_2 & 0xff;
  param_3 = param_3 & 0xff;
  param_4 = param_4 & 0xff;
  uVar3 = param_1 - 1;
  uVar4 = uVar2 - 1;
  uVar8 = 0;
  uVar7 = 0;
  if ((param_3 < *param_6) && (param_4 < *param_7)) {
    uVar6 = (uint)*param_5;
  }
  else if ((param_6[(short)uVar3] < param_3) && (param_7[(short)uVar4] < param_4)) {
    uVar6 = (uint)param_5[(int)(short)param_1 * (int)(short)uVar2 + -1];
  }
  else {
    for (; (param_7[(short)uVar7] < param_4 && ((short)uVar7 < (short)uVar4)); uVar7 = uVar7 + 1) {
    }
    if ((param_7[(short)uVar7] < param_4) && (uVar7 == uVar4)) {
      uVar7 = uVar7 + 1;
    }
    for (; (param_6[(short)uVar8] < param_3 && ((short)uVar8 < (short)uVar3)); uVar8 = uVar8 + 1) {
    }
    if ((param_6[(short)uVar8] < param_3) && (uVar8 == uVar3)) {
      uVar8 = uVar8 + 1;
    }
    if (((param_3 == param_6[(short)uVar8]) && (param_4 == param_7[(short)uVar7])) &&
       (uVar7 == (param_2 & 0xff))) {
      uVar6 = (uint)param_5[((short)uVar7 + -1) * (int)(short)param_1 + (int)(short)uVar8];
    }
    else if ((param_3 == param_6[(short)uVar8]) && (param_4 == param_7[(short)uVar7])) {
      uVar6 = (uint)param_5[(int)(short)uVar7 * (int)(short)param_1 + (int)(short)uVar8];
    }
    else if (((param_4 == param_7[(short)uVar7]) || (uVar7 == uVar2)) || (uVar7 == 0)) {
      if (uVar7 == uVar2) {
        uVar7 = uVar7 - 1;
      }
      if (uVar8 == param_1) {
        if (param_6[(short)uVar8 + -1] == param_6[(short)uVar8 + -2]) {
          bVar1 = param_5[((short)uVar7 + 1) * (int)(short)param_1 + -2];
        }
        else {
          bVar1 = param_5[((short)uVar7 + 1) * (int)(short)param_1 + -1];
        }
        uVar6 = (uint)bVar1;
      }
      else if (uVar8 == 0) {
        uVar6 = (uint)param_5[(int)(short)uVar7 * (int)(short)param_1];
      }
      else {
        sVar5 = uVar8 + uVar7 * param_1;
        if (param_6[(short)uVar8 + -1] == param_6[(short)uVar8]) {
          uVar6 = (uint)param_5[sVar5 + -1];
        }
        else {
          uVar6 = (uint)param_5[sVar5 + -1] +
                  (int)(((int)(short)param_3 - (uint)param_6[(short)uVar8 + -1]) *
                       ((uint)param_5[sVar5] - (uint)param_5[sVar5 + -1])) /
                  (int)((uint)param_6[(short)uVar8] - (uint)param_6[(short)uVar8 + -1]) & 0xff;
        }
      }
    }
    else if (((param_3 == param_6[(short)uVar8]) || (uVar8 == param_1)) || (uVar8 == 0)) {
      if (uVar8 == param_1) {
        uVar8 = uVar8 - 1;
      }
      sVar5 = uVar8 + uVar7 * param_1;
      if (uVar7 == uVar2) {
        if (param_7[(short)uVar7 + -2] == param_7[(short)uVar7 + -1]) {
          bVar1 = param_5[(int)sVar5 + (short)param_1 * -2];
        }
        else {
          bVar1 = param_5[(int)sVar5 - (int)(short)param_1];
        }
        uVar6 = (uint)bVar1;
      }
      else if (uVar7 == 0) {
        uVar6 = (uint)param_5[(short)uVar8];
      }
      else if (param_7[(short)uVar7 + -1] == param_7[(short)uVar7]) {
        uVar6 = (uint)param_5[(int)sVar5 - (int)(short)param_1];
      }
      else {
        uVar6 = (uint)param_5[(int)sVar5 - (int)(short)param_1] +
                (int)(((int)(short)param_4 - (uint)param_7[(short)uVar7 + -1]) *
                     ((uint)param_5[sVar5] - (uint)param_5[(int)sVar5 - (int)(short)param_1])) /
                (int)((uint)param_7[(short)uVar7] - (uint)param_7[(short)uVar7 + -1]) & 0xff;
      }
    }
    else {
      sVar5 = uVar8 + (uVar7 - 1) * param_1;
      if (param_6[(short)uVar8 + -1] == param_6[(short)uVar8]) {
        uVar6 = (uint)param_5[sVar5];
        uVar9 = (uint)param_5[(int)(short)param_1 + (int)sVar5];
      }
      else {
        uVar6 = (uint)param_5[sVar5 + -1] +
                (int)(((int)(short)param_3 - (uint)param_6[(short)uVar8 + -1]) *
                     ((uint)param_5[sVar5] - (uint)param_5[sVar5 + -1])) /
                (int)((uint)param_6[(short)uVar8] - (uint)param_6[(short)uVar8 + -1]) & 0xff;
        uVar9 = (uint)param_5[(int)(short)uVar3 + (int)sVar5] +
                (int)(((int)(short)param_3 - (uint)param_6[(short)uVar8 + -1]) *
                     ((uint)param_5[(int)(short)param_1 + (int)sVar5] -
                     (uint)param_5[(int)(short)uVar3 + (int)sVar5])) /
                (int)((uint)param_6[(short)uVar8] - (uint)param_6[(short)uVar8 + -1]) & 0xff;
      }
      uVar6 = uVar6 + (int)(((int)(short)param_4 - (uint)param_7[(short)uVar7 + -1]) *
                           (uVar9 - uVar6)) /
                      (int)((uint)param_7[(short)uVar7] - (uint)param_7[(short)uVar7 + -1]) & 0xff;
    }
  }
  return uVar6;
}



uint lookup_3D_uint32_interpolated
               (ulonglong param_1,uint param_2,uint param_3,uint param_4,ushort *param_5,
               ushort *param_6,ushort *param_7)

{
  ushort uVar1;
  uint uVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  uint uVar6;
  int iVar7;
  ulonglong uVar8;
  int iVar9;
  uint uVar10;
  
  uVar3 = param_1 & 0xff;
  uVar6 = param_2 & 0xff;
  param_3 = param_3 & 0xffff;
  param_4 = param_4 & 0xffff;
  uVar8 = uVar3 - 1;
  uVar10 = uVar6 - 1;
  uVar5 = 0;
  uVar2 = 0;
  if ((param_3 < *param_6) && (param_4 < *param_7)) {
    uVar6 = (uint)*param_5;
  }
  else {
    iVar9 = (int)uVar3;
    if ((*(ushort *)((int)param_6 + (int)((uVar8 & 0xffffffff) << 1)) < param_3) &&
       (param_7[uVar10] < param_4)) {
      uVar6 = (uint)param_5[iVar9 * uVar6 + -1];
    }
    else {
      for (; (param_7[uVar2] < param_4 && ((int)uVar2 < (int)uVar10)); uVar2 = uVar2 + 1) {
      }
      if ((param_7[uVar2] < param_4) && (uVar2 == uVar10)) {
        uVar2 = uVar2 + 1;
      }
      while( true ) {
        if ((param_3 <= *(ushort *)((int)param_6 + (int)((uVar5 & 0xffffffff) << 1))) ||
           ((int)uVar8 <= (int)uVar5)) break;
        uVar5 = uVar5 + 1;
      }
      if ((*(ushort *)((int)param_6 + (int)((uVar5 & 0xffffffff) << 1)) < param_3) &&
         ((int)uVar5 == (int)uVar8)) {
        uVar5 = uVar5 + 1;
      }
      if (((param_3 == *(ushort *)((int)param_6 + (int)((uVar5 & 0xffffffff) << 1))) &&
          (param_4 == param_7[uVar2])) && (uVar2 == (param_2 & 0xff))) {
        uVar6 = (uint)*(ushort *)
                       ((int)param_5 +
                       (int)((uVar5 + (longlong)(int)(uVar2 - 1) * (longlong)iVar9 & 0xffffffff) <<
                            1));
      }
      else if ((param_3 == *(ushort *)((int)param_6 + (int)((uVar5 & 0xffffffff) << 1))) &&
              (param_4 == param_7[uVar2])) {
        uVar6 = (uint)*(ushort *)
                       ((int)param_5 +
                       (int)((uVar5 + (longlong)(int)uVar2 * (longlong)iVar9 & 0xffffffff) << 1));
      }
      else {
        iVar7 = (int)uVar5;
        if (((param_4 == param_7[uVar2]) || (uVar2 == uVar6)) || (uVar2 == 0)) {
          if (uVar2 == uVar6) {
            uVar2 = uVar2 - 1;
          }
          if (iVar7 == iVar9) {
            if (*(short *)((int)param_6 + (int)((uVar5 - 1 & 0xffffffff) << 1)) ==
                *(short *)((int)param_6 + (int)((uVar5 - 2 & 0xffffffff) << 1))) {
              uVar1 = param_5[(uVar2 + 1) * iVar9 + -2];
            }
            else {
              uVar1 = param_5[(uVar2 + 1) * iVar9 + -1];
            }
            uVar6 = (uint)uVar1;
          }
          else if (iVar7 == 0) {
            uVar6 = (uint)param_5[uVar2 * iVar9];
          }
          else {
            uVar3 = uVar5 + (longlong)(int)uVar2 * (longlong)iVar9;
            if (*(short *)((int)param_6 + (int)((uVar5 - 1 & 0xffffffff) << 1)) ==
                *(short *)((int)param_6 + (int)((uVar5 & 0xffffffff) << 1))) {
              uVar6 = (uint)*(ushort *)((int)param_5 + (int)((uVar3 - 1 & 0xffffffff) << 1));
            }
            else {
              uVar6 = (uint)*(ushort *)((int)param_5 + (int)((uVar3 - 1 & 0xffffffff) << 1)) +
                      (int)((param_3 -
                            *(ushort *)((int)param_6 + (int)((uVar5 - 1 & 0xffffffff) << 1))) *
                           ((uint)*(ushort *)((int)param_5 + (int)((uVar3 & 0xffffffff) << 1)) -
                           (uint)*(ushort *)((int)param_5 + (int)((uVar3 - 1 & 0xffffffff) << 1))))
                      / (int)((uint)*(ushort *)((int)param_6 + (int)((uVar5 & 0xffffffff) << 1)) -
                             (uint)*(ushort *)((int)param_6 + (int)((uVar5 - 1 & 0xffffffff) << 1)))
                      & 0xffff;
            }
          }
        }
        else if (((param_3 == *(ushort *)((int)param_6 + (int)((uVar5 & 0xffffffff) << 1))) ||
                 (iVar7 == iVar9)) || (iVar7 == 0)) {
          if (iVar7 == iVar9) {
            uVar5 = uVar5 - 1;
          }
          uVar8 = uVar5 + (longlong)(int)uVar2 * (longlong)iVar9;
          if (uVar2 == uVar6) {
            if (param_7[uVar2 - 2] == param_7[uVar2 - 1]) {
              uVar1 = *(ushort *)
                       ((int)param_5 + (int)((uVar8 + (param_1 & 0xff) * -2 & 0xffffffff) << 1));
            }
            else {
              uVar1 = *(ushort *)((int)param_5 + (int)((uVar8 - uVar3 & 0xffffffff) << 1));
            }
            uVar6 = (uint)uVar1;
          }
          else if (uVar2 == 0) {
            uVar6 = (uint)*(ushort *)((int)param_5 + (int)((uVar5 & 0xffffffff) << 1));
          }
          else if (param_7[uVar2 - 1] == param_7[uVar2]) {
            uVar6 = (uint)*(ushort *)((int)param_5 + (int)((uVar8 - uVar3 & 0xffffffff) << 1));
          }
          else {
            uVar6 = (uint)*(ushort *)((int)param_5 + (int)((uVar8 - uVar3 & 0xffffffff) << 1)) +
                    (int)((param_4 - param_7[uVar2 - 1]) *
                         ((uint)*(ushort *)((int)param_5 + (int)((uVar8 & 0xffffffff) << 1)) -
                         (uint)*(ushort *)((int)param_5 + (int)((uVar8 - uVar3 & 0xffffffff) << 1)))
                         ) / (int)((uint)param_7[uVar2] - (uint)param_7[uVar2 - 1]) & 0xffff;
          }
        }
        else {
          uVar4 = uVar5 + (longlong)(int)(uVar2 - 1) * (longlong)iVar9;
          if (*(short *)((int)param_6 + (int)((uVar5 - 1 & 0xffffffff) << 1)) ==
              *(short *)((int)param_6 + (int)((uVar5 & 0xffffffff) << 1))) {
            uVar6 = (uint)*(ushort *)((int)param_5 + (int)((uVar4 & 0xffffffff) << 1));
            uVar10 = (uint)*(ushort *)((int)param_5 + (int)((uVar4 + uVar3 & 0xffffffff) << 1));
          }
          else {
            uVar6 = (uint)*(ushort *)((int)param_5 + (int)((uVar4 - 1 & 0xffffffff) << 1)) +
                    (int)((param_3 -
                          *(ushort *)((int)param_6 + (int)((uVar5 - 1 & 0xffffffff) << 1))) *
                         ((uint)*(ushort *)((int)param_5 + (int)((uVar4 & 0xffffffff) << 1)) -
                         (uint)*(ushort *)((int)param_5 + (int)((uVar4 - 1 & 0xffffffff) << 1)))) /
                    (int)((uint)*(ushort *)((int)param_6 + (int)((uVar5 & 0xffffffff) << 1)) -
                         (uint)*(ushort *)((int)param_6 + (int)((uVar5 - 1 & 0xffffffff) << 1))) &
                    0xffff;
            uVar10 = (uint)*(ushort *)((int)param_5 + (int)((uVar4 + uVar8 & 0xffffffff) << 1)) +
                     (int)((param_3 -
                           *(ushort *)((int)param_6 + (int)((uVar5 - 1 & 0xffffffff) << 1))) *
                          ((uint)*(ushort *)
                                  ((int)param_5 + (int)((uVar4 + uVar3 & 0xffffffff) << 1)) -
                          (uint)*(ushort *)((int)param_5 + (int)((uVar4 + uVar8 & 0xffffffff) << 1))
                          )) / (int)((uint)*(ushort *)
                                            ((int)param_6 + (int)((uVar5 & 0xffffffff) << 1)) -
                                    (uint)*(ushort *)
                                           ((int)param_6 + (int)((uVar5 - 1 & 0xffffffff) << 1))) &
                     0xffff;
          }
          uVar6 = uVar6 + (int)((param_4 - param_7[uVar2 - 1]) * (uVar10 - uVar6)) /
                          (int)((uint)param_7[uVar2] - (uint)param_7[uVar2 - 1]) & 0xffff;
        }
      }
    }
  }
  return uVar6;
}



uint lookup_2D_uint8_binlinear_noaxis
               (uint table_width,uint x_shift_component_,uint y_shift_component_,uint8_t x_val,
               uint8_t y_val,uint8_t *lut)

{
  short sVar2;
  short sVar3;
  short sVar4;
  uint uVar1;
  uint uVar5;
  short sVar6;
  uint uVar7;
  
  uVar7 = (uint)x_val << (x_shift_component_ & 0x3f);
  sVar2 = (short)uVar7;
  uVar1 = (uint)y_val << (y_shift_component_ & 0x3f);
  sVar3 = (short)(char)(uVar7 >> 8) + (ushort)(sVar2 < 0 && (uVar7 & 0xff) != 0);
  sVar4 = (short)(char)(uVar1 >> 8) + (ushort)((short)uVar1 < 0 && (uVar1 & 0xff) != 0);
  sVar6 = sVar3 + sVar4 * ((ushort)table_width & 0xff);
  uVar7 = ((int)sVar2 + sVar3 * -0x100) * ((uint)lut[sVar6 + 1] - (uint)lut[sVar6]);
  uVar7 = (uint)lut[sVar6] + ((int)uVar7 >> 8) + (uint)((int)uVar7 < 0 && (uVar7 & 0xff) != 0) &
          0xff;
  uVar5 = ((int)sVar2 + sVar3 * -0x100) *
          ((uint)lut[(int)sVar6 + (table_width & 0xff) + 1] -
          (uint)lut[(int)sVar6 + (table_width & 0xff)]);
  uVar1 = ((int)(short)uVar1 + sVar4 * -0x100) *
          (((uint)lut[(int)sVar6 + (table_width & 0xff)] +
            ((int)uVar5 >> 8) + (uint)((int)uVar5 < 0 && (uVar5 & 0xff) != 0) & 0xff) - uVar7);
  return uVar7 + ((int)uVar1 >> 8) + (uint)((int)uVar1 < 0 && (uVar1 & 0xff) != 0) & 0xff;
}



void obd_ii_task(void)

{
  char cVar1;
  ushort uVar2;
  ushort uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  int iVar6;
  char *pcVar7;
  byte bVar8;
  byte bVar9;
  
  bVar9 = 0;
  FUN_0005f9b0();
  if (((tach_rpm != 0) && ((DAT_40001666 & 2) == 0)) && ((DAT_40001666 & 4) == 0)) {
    uVar2 = DAT_40001666 & 1;
    uVar3 = DAT_40001666 & 0xfff7;
    DAT_40001666 = DAT_40001666 | 8;
    if (uVar2 == 0) {
      DAT_40001666 = uVar3;
    }
  }
  uVar2 = DAT_40001666;
  if ((((DAT_40001666 & 0x200) == 0) && ((trans_slip_status_flags & 2) == 0)) &&
     ((DAT_40001639 & 4) == 0)) {
    if ((DAT_40001666 & 0x80) == 0) {
      if ((DAT_40001666 & 0x400) == 0) {
        uVar2 = DAT_40001666 & 0xfeff;
      }
      else if ((DAT_40001664 & 1) != 0) {
        DAT_40001664 = DAT_40001664 & 0xfffe;
        DAT_4000167e = DAT_4000167e + 1;
        if ((0x1c < DAT_4000167e) && (uVar2 = DAT_40001666 | 0x100, 0x1d < DAT_4000167e)) {
          DAT_4000167e = 0;
          uVar2 = DAT_40001666 & 0xfeff;
        }
      }
    }
    else {
      uVar2 = DAT_40001666 | 0x100;
    }
  }
  else if ((DAT_40001664 & 1) != 0) {
    DAT_40001664 = DAT_40001664 & 0xfffe;
    DAT_4000167e = DAT_4000167e + 1;
    if (4 < DAT_4000167e) {
      DAT_4000167e = 0;
      uVar2 = DAT_40001666 ^ 0x100;
    }
  }
  DAT_40001666 = uVar2;
  if (((DAT_40001666 & 0x20) == 0) || (DAT_40001674 == 0)) {
    DAT_40001666 = DAT_40001666 & 0xffbf;
  }
  else {
    DAT_40001666 = DAT_40001666 | 0x40;
  }
  iVar6 = FUN_0004fecc();
  if (iVar6 != 0) {
    DAT_40001676 = (ushort)DAT_4000e404;
    if (DAT_4000166b != '\0') {
      DAT_4000166b = '\0';
      FUN_0005fa40();
      obd_ii_zero_perm_dtc();
    }
    uVar4 = 1;
    if ((paddle_shift_flags & 0x20) == 0) {
      uVar4 = DAT_40001671;
    }
    uVar5 = 1;
    if ((paddle_shift_flags & 0x40) == 0) {
      uVar5 = DAT_40001672;
    }
    DAT_40001669 = oil_temp_unknown;
    DAT_400013f0 = 0;
    DAT_400013f1 = 0;
    DAT_400013f2 = 0;
    DAT_400013f3 = 0;
    DAT_40001671 = uVar4;
    DAT_40001672 = uVar5;
    if (DAT_40002c4a != 0) {
      FUN_0004ef08();
    }
    uVar4 = 1;
    if (engine_running == '\0') {
      uVar4 = DAT_40001670;
    }
    DAT_40001670 = uVar4;
    if ((DAT_40001664 & 2) == 0) {
      if ((DAT_40001664 & 4) == 0) {
        if ((DAT_40001664 & 8) == 0) {
          if ((DAT_40001664 & 0x10) == 0) {
            if ((DAT_40001664 & 0x40) != 0) {
              DAT_40001664 = DAT_40001664 & 0xffbf;
              if ((DAT_40001666 & 1) == 0) {
                DAT_40001666 = DAT_40001666 & 0xffef;
              }
              else {
                if (engine_running != '\0') {
                  if ((DAT_40001666 & 0x10) == 0) {
                    DAT_40002c84 = 0;
                  }
                  iVar6 = (int)((ulonglong)
                                ((longlong)(int)(uint)shift_adaptation_learn_gate * -0x49f49f49) >>
                               0x20) + (uint)shift_adaptation_learn_gate;
                  DAT_40002c84 = DAT_40002c84 + ((iVar6 >> 8) - (iVar6 >> 0x1f));
                  if (0x270fd8f0 < DAT_40002c84) {
                    DAT_40002c84 = 0x270fd8f0;
                  }
                }
                DAT_40001666 = DAT_40001666 | 0x10;
              }
              if (((engine_running != '\0') && (DAT_40002c88 != -1)) &&
                 (iVar6 = (int)((ulonglong)
                                ((longlong)(int)(uint)shift_adaptation_learn_gate * -0x49f49f49) >>
                               0x20) + (uint)shift_adaptation_learn_gate,
                 DAT_40001686 = DAT_40001686 +
                                ((short)((uint)iVar6 >> 8) -
                                ((short)(char)((uint)iVar6 >> 0x18) >> 0xf)), 10000 < DAT_40001686))
              {
                DAT_40002c88 = DAT_40002c88 + 1;
                DAT_40001686 = 0;
              }
            }
          }
          else {
            DAT_40001664 = DAT_40001664 & 0xffef;
            FUN_00070960();
          }
        }
        else {
          DAT_40001664 = DAT_40001664 & 0xfff7;
          update_trans_fault_monitor();
          FUN_00068854();
        }
      }
      else {
        DAT_40001664 = DAT_40001664 & 0xfffb;
        FUN_000675b4();
      }
    }
    else {
      DAT_40001664 = DAT_40001664 & 0xfffd;
      obd_ii_monitor_trans_sensors();
      DAT_40001680 = DAT_40001680 + 1;
      if (9 < DAT_40001680) {
        DAT_40001680 = 0;
        DAT_40001681 = DAT_40001681 + 1;
        if (DAT_40001681 < 0x80) {
          if ((&DAT_400054c8)[DAT_40001681] == 0) {
            DAT_40001681 = 0;
          }
        }
        else {
          DAT_40001681 = 0;
        }
        pcVar7 = (char *)obd_ii_dtc_format((&DAT_400054c8)[DAT_40001681]);
        for (bVar8 = 0; bVar8 < 5; bVar8 = bVar8 + 1) {
          cVar1 = *pcVar7;
          pcVar7 = pcVar7 + 1;
          s__400013f4[bVar8] = cVar1;
        }
        DAT_40001688 = (&DAT_400054c8)[DAT_40001681];
        DAT_4000166c = obd_ii_dtc_unpack((&DAT_400054c8)[DAT_40001681]);
        bVar8 = DAT_40001684;
        if (CAL_obd_ii_standards_supported == '\x01') {
          while (((&DAT_40002c18)[(uint)DAT_40001684 * 2] == 0 && (DAT_40001684 < 8))) {
            DAT_40001684 = DAT_40001684 + 1;
            bVar9 = bVar9 + 1;
            if ((7 < DAT_40001684) && (bVar9 < 8)) {
              DAT_40001684 = 0;
            }
          }
          if (DAT_40001684 < 8) {
            pcVar7 = (char *)obd_ii_dtc_format((&DAT_40002c18)[(uint)DAT_40001684 * 2]);
            for (bVar9 = 0; bVar9 < 5; bVar9 = bVar9 + 1) {
              cVar1 = *pcVar7;
              pcVar7 = pcVar7 + 1;
              s__400013fc[bVar9] = cVar1;
            }
            DAT_4000168c = (&DAT_40002c18)[(uint)DAT_40001684 * 2];
            DAT_40001692 = obd_ii_dtc_unpack((&DAT_40002c18)[(uint)DAT_40001684 * 2]);
            DAT_40001684 = DAT_40001684 + 1;
          }
          else {
            for (bVar9 = 0; bVar9 < 5; bVar9 = bVar9 + 1) {
              s__400013fc[bVar9] = '\0';
            }
          }
          bVar8 = 0;
          if (DAT_40001684 < 8) {
            bVar8 = DAT_40001684;
          }
        }
        DAT_40001684 = bVar8;
        DAT_40001682 = DAT_40001682 + 1;
        if (DAT_40001682 < 0x80) {
          if ((&DAT_400056c8)[DAT_40001682] == 0) {
            DAT_40001682 = 0;
          }
        }
        else {
          DAT_40001682 = 0;
        }
        pcVar7 = (char *)obd_ii_dtc_format((&DAT_400056c8)[DAT_40001682]);
        for (bVar9 = 0; bVar9 < 5; bVar9 = bVar9 + 1) {
          cVar1 = *pcVar7;
          pcVar7 = pcVar7 + 1;
          s__40001404[bVar9] = cVar1;
        }
        DAT_4000168a = (&DAT_400056c8)[DAT_40001682];
        DAT_40001690 = obd_ii_dtc_unpack((&DAT_400056c8)[DAT_40001682]);
        DAT_40001683 = DAT_40001683 + 1;
        if (DAT_40001683 < 0x80) {
          if ((&DAT_400055c8)[DAT_40001683] == 0) {
            DAT_40001683 = 0;
          }
        }
        else {
          DAT_40001683 = 0;
        }
        pcVar7 = (char *)obd_ii_dtc_format((&DAT_400055c8)[DAT_40001683]);
        for (bVar9 = 0; bVar9 < 5; bVar9 = bVar9 + 1) {
          cVar1 = *pcVar7;
          pcVar7 = pcVar7 + 1;
          s__4000140c[bVar9] = cVar1;
        }
        DAT_4000168e = (&DAT_400055c8)[DAT_40001683];
        DAT_4000166e = obd_ii_dtc_unpack((&DAT_400055c8)[DAT_40001683]);
      }
    }
  }
  return;
}



void FUN_0004ef08(void)

{
  int iVar1;
  
  iVar1 = int_abs((ulonglong)tach_rpm - (ulonglong)u16_rspeed_1_4rpm_40002c4c);
  if (((iVar1 < (int)(uint)DAT_4000e25a) &&
      (iVar1 = int_abs(-(ulonglong)DAT_40002c50), iVar1 < (int)(uint)DAT_4000e258)) &&
     (DAT_40001671 == DAT_40002c51)) {
    if (DAT_40001662 == 0) {
      DAT_40001660 = 1;
    }
  }
  else {
    DAT_40001662 = DAT_4000e25c;
  }
  return;
}



void obd_ii_dtc_confirm_and_freeze
               (byte *param_1,byte *param_2,undefined1 *param_3,undefined1 *param_4,ushort param_5,
               short param_6)

{
  ushort uVar1;
  bool bVar2;
  ushort uVar3;
  byte bVar4;
  
  bVar2 = false;
  uVar1 = param_5 | param_6 << 0xe;
  if ((*param_1 & 0x10) != 0) {
    DAT_400016a0 = *param_1;
    DAT_4000169c = (uint)param_5;
    FUN_0004f88c(DAT_400016a0,DAT_4000169c);
  }
  bVar4 = 0;
  do {
    if (7 < bVar4) {
LAB_0004f060:
      if ((bVar2) && (bVar4 < 8)) {
        (&DAT_40002c1a)[(uint)bVar4 * 4] = 0;
      }
      if ((*param_1 & 7) == 1) {
        *param_2 = *param_2 | 0xc;
        if ((*param_1 & 0x70) != 0) {
          *param_2 = *param_2 | 1;
        }
        *param_3 = 0;
        *param_4 = 0;
        if ((*param_1 & 0x10) != 0) {
          DAT_40001666 = DAT_40001666 | 0x801;
          if ((CAL_obd_ii_standards_supported == '\x01') && (!bVar2)) {
            obd_ii_set_perm_dtc(uVar1);
          }
          if (((DAT_40001666 & 2) == 0) && (DAT_40002c38 == 0)) {
            DAT_40002c3a = *param_1 & 7;
            DAT_40002c38 = uVar1;
            FUN_0004f9b0();
          }
        }
        uVar3 = DAT_40001666 | 0x80;
        if ((*param_1 & 0x40) == 0) {
          uVar3 = DAT_40001666;
        }
        DAT_40001666 = uVar3;
        if (((*param_2 & 0x80) == 0) && ((*param_2 & 4) != 0)) {
          *param_2 = *param_2 | 0x80;
          if ((*param_1 & 0x10) == 0) {
            if ((*param_1 & 0x20) != 0) {
              DAT_40001666 = DAT_40001666 | 0x20;
              DAT_40001674 = (ushort)DAT_4000e256 * 10;
            }
            FUN_000616fc(uVar1);
          }
          else {
            FUN_0005f9d8(uVar1);
          }
        }
      }
      else if ((*param_1 & 7) == 2) {
        *param_2 = *param_2 | 0xc;
        *param_3 = 0;
        *param_4 = 0;
        if ((*param_2 & 0x10) == 0) {
          if (((*param_2 & 0x80) == 0) && ((*param_1 & 0x10) != 0)) {
            *param_2 = *param_2 | 0x80;
            FUN_00060f18(uVar1);
          }
        }
        else {
          if ((*param_1 & 0x70) != 0) {
            *param_2 = *param_2 | 1;
          }
          *param_2 = *param_2 & 0xef;
          if (DAT_40002c4a == 0) {
            DAT_40002c50 = 0;
            DAT_40002c4e = 0;
            u16_rspeed_1_4rpm_40002c4c = tach_rpm;
            DAT_40002c51 = DAT_40001671;
            DAT_40002c52 = DAT_40002c3b;
            DAT_40002c4a = uVar1;
          }
          if ((*param_1 & 0x10) != 0) {
            DAT_40001666 = DAT_40001666 | 0x801;
            if ((CAL_obd_ii_standards_supported == '\x01') && (!bVar2)) {
              obd_ii_set_perm_dtc(uVar1);
            }
            if ((DAT_40002c3a != 2) && (DAT_40002c3a != 4)) {
              DAT_40002c3a = *param_1 & 7;
              DAT_40002c38 = uVar1;
              FUN_0004f9b0();
            }
          }
          uVar3 = DAT_40001666 | 0x80;
          if ((*param_1 & 0x40) == 0) {
            uVar3 = DAT_40001666;
          }
          DAT_40001666 = uVar3;
          if ((*param_2 & 0x80) == 0) {
            *param_2 = *param_2 | 0x80;
            if ((*param_1 & 0x10) == 0) {
              if ((*param_1 & 0x20) != 0) {
                DAT_40001666 = DAT_40001666 | 0x20;
                DAT_40001674 = (ushort)DAT_4000e256 * 10;
              }
              FUN_000616fc(uVar1);
            }
            else {
              FUN_0005f9d8(uVar1);
            }
          }
        }
      }
      else if ((*param_1 & 7) == 3) {
        *param_2 = *param_2 | 0xc;
        *param_3 = 0;
        *param_4 = 0;
        if ((*param_2 & 0x10) == 0) {
          if (((*param_2 & 0x80) == 0) && ((*param_1 & 0x10) != 0)) {
            *param_2 = *param_2 | 0x80;
            FUN_00060f18(uVar1);
          }
        }
        else {
          if ((*param_1 & 0x70) != 0) {
            *param_2 = *param_2 | 1;
          }
          *param_2 = *param_2 & 0xef;
          if ((*param_1 & 0x10) != 0) {
            DAT_40001666 = DAT_40001666 | 0x801;
            if ((CAL_obd_ii_standards_supported == '\x01') && (!bVar2)) {
              obd_ii_set_perm_dtc(uVar1);
            }
            if (((DAT_40001666 & 2) == 0) && (DAT_40002c38 == 0)) {
              DAT_40002c3a = *param_1 & 7;
              DAT_40002c38 = uVar1;
              FUN_0004f9b0();
            }
          }
          uVar3 = DAT_40001666 | 0x80;
          if ((*param_1 & 0x40) == 0) {
            uVar3 = DAT_40001666;
          }
          DAT_40001666 = uVar3;
          if ((*param_2 & 0x80) == 0) {
            *param_2 = *param_2 | 0x80;
            if ((*param_1 & 0x10) == 0) {
              if ((*param_1 & 0x20) != 0) {
                DAT_40001666 = DAT_40001666 | 0x20;
                DAT_40001674 = (ushort)DAT_4000e256 * 10;
              }
              FUN_000616fc(uVar1);
            }
            else {
              FUN_0005f9d8(uVar1);
            }
          }
        }
      }
      else if ((*param_1 & 7) == 4) {
        *param_2 = *param_2 | 0xc;
        if ((*param_1 & 0x70) != 0) {
          *param_2 = *param_2 | 1;
        }
        *param_3 = 0;
        *param_4 = 0;
        uVar3 = DAT_40001666 | 0x200;
        if ((*param_1 & 0x40) == 0) {
          uVar3 = DAT_40001666;
        }
        DAT_40001666 = uVar3;
        if ((((*param_2 & 0x80) == 0) && ((*param_2 & 4) != 0)) &&
           (*param_2 = *param_2 | 0x80, (*param_1 & 0x10) == 0)) {
          uVar3 = DAT_40001666;
          if (((*param_1 & 0x20) == 0) && (uVar3 = DAT_40001666 | 0x80, (*param_1 & 0x40) == 0)) {
            uVar3 = DAT_40001666;
          }
          DAT_40001666 = uVar3;
          FUN_000616fc(uVar1);
        }
      }
      return;
    }
    if (uVar1 == (&DAT_40002c18)[(uint)bVar4 * 2]) {
      bVar2 = true;
      goto LAB_0004f060;
    }
    bVar4 = bVar4 + 1;
  } while( true );
}



void obd_ii_monitor_pass(byte *param_1,byte *param_2)

{
  if ((*param_1 & 7) == 1) {
    *param_2 = *param_2 | 8;
  }
  else if ((*param_1 & 7) == 2) {
    *param_2 = *param_2 | 8;
  }
  else if ((*param_1 & 7) == 3) {
    *param_2 = *param_2 | 8;
  }
  else if ((((*param_1 & 7) == 4) && (*param_2 = *param_2 | 8, (*param_2 & 1) != 0)) &&
          ((*param_1 & 0x40) != 0)) {
    DAT_40001666 = DAT_40001666 & 0xfdff | 0x80;
  }
  return;
}



void FUN_0004f88c(ushort param_1,short param_2)

{
  DAT_40002c5e = param_2 << 3 | param_1 & 7;
  u16_rspeed_1_4rpm_40002c60 = tach_rpm;
  DAT_40002c62 = 0;
  DAT_40002c80 = vehicle_speed;
  DAT_40002c64 = 0;
  DAT_40002c66 = 0;
  DAT_40002c68 = 0;
  DAT_40002c6a = 0;
  DAT_40002c6c = oil_temp_unknown;
  DAT_40002c6d = DAT_40001569;
  DAT_40002c6e = oil_temp_unknown;
  DAT_40002c6f = tps;
  DAT_40002c70 = DAT_40001540;
  DAT_40002c74 = 0;
  DAT_40002c76 = 0;
  DAT_40002c78 = 0;
  DAT_40002c7a = 0;
  return;
}



void FUN_0004f9b0(void)

{
  DAT_40002c3c = 0;
  DAT_40002c3d = DAT_40001669;
  u16_rspeed_1_4rpm_40002c3e = tach_rpm;
  DAT_40002c40 = vehicle_speed;
  DAT_40002c42 = (short)((ulonglong)DAT_40001540 / 200);
  DAT_40002c44 = DAT_400015ba * 0x12;
  DAT_40002c46 = 0;
  DAT_40002c48 = tps;
  return;
}



void FUN_0004fa50(void)

{
  DAT_4000167d = DAT_40001670;
  if (DAT_40001670 == '\x01') {
    DAT_40002c3b = DAT_40002c3b + 1;
  }
  if ((uint)DAT_40002c52 + (uint)DAT_4000e257 <= (uint)DAT_40002c3b) {
    DAT_40002c4a = 0;
    DAT_40002c50 = 0;
    DAT_40002c4e = 0;
    u16_rspeed_1_4rpm_40002c4c = 0;
    DAT_40002c51 = 0;
    DAT_40002c52 = 0;
  }
  FUN_00070078();
  FUN_00066674();
  FUN_00068618();
  FUN_0006b918();
  FUN_000723d8();
  return;
}



void obd_ii_dtc_aging_heal
               (byte *param_1,byte *param_2,byte *param_3,byte *param_4,ushort param_5,short param_6
               )

{
  byte bVar1;
  bool bVar2;
  byte bVar3;
  
  bVar2 = false;
  param_5 = param_5 | param_6 << 0xe;
  bVar3 = 0;
  do {
    if (7 < bVar3) {
LAB_0004fb90:
      if (((((DAT_4000167d != '\0') && ((*param_2 & 8) != 0)) && ((*param_2 & 4) == 0)) &&
          ((DAT_40002c4a != param_5 || ((DAT_40001660 != '\0' && (DAT_40002c4a == param_5)))))) &&
         (bVar1 = *param_3, *param_3 = bVar1 + 1, 2 < (byte)(bVar1 + 1))) {
        if (((bVar2) && ((*param_2 & 1) != 0)) && (bVar3 < 8)) {
          (&DAT_40002c18)[(uint)bVar3 * 2] = 0;
        }
        *param_2 = *param_2 & 0xfe;
      }
      if ((((DAT_40001671 != '\0') && ((*param_2 & 8) != 0)) && ((*param_2 & 4) == 0)) &&
         ((*param_4 = *param_4 + 1, DAT_4000e259 <= *param_4 &&
          (*param_2 = *param_2 & 0xfd, DAT_40002c38 == param_5)))) {
        DAT_40002c3c = 0;
        DAT_40002c3d = 0;
        u16_rspeed_1_4rpm_40002c3e = 0;
        DAT_40002c40 = 0;
        DAT_40002c42 = 0;
        DAT_40002c44 = 0;
        DAT_40002c46 = 0;
        DAT_40002c48 = 0;
      }
      if ((*param_2 & 4) == 0) {
        if (((*param_2 & 8) != 0) && ((*param_2 & 0x10) != 0)) {
          *param_2 = *param_2 & 0xed;
        }
      }
      else if (((*param_2 & 2) == 0) &&
              ((*param_2 = *param_2 | 2, (*param_1 & 7) == 2 || ((*param_1 & 7) == 3)))) {
        *param_2 = *param_2 | 0x10;
      }
      if ((bVar2) && (bVar3 < 8)) {
        (&DAT_40002c1a)[(uint)bVar3 * 4] = 1;
      }
      *param_2 = *param_2 & 0xfb;
      *param_2 = *param_2 & 0x7f;
      if ((((bVar3 < 8) && (bVar2)) && ((&DAT_40002c1a)[(uint)bVar3 * 4] != '\0')) &&
         (((*param_2 & 2) == 0 && (DAT_40001672 != '\0')))) {
        (&DAT_40002c18)[(uint)bVar3 * 2] = 0;
      }
      return;
    }
    if (param_5 == (&DAT_40002c18)[(uint)bVar3 * 2]) {
      bVar2 = true;
      goto LAB_0004fb90;
    }
    bVar3 = bVar3 + 1;
  } while( true );
}



undefined8 FUN_0004fecc(void)

{
  undefined8 uVar1;
  
  uVar1 = 0;
  switch(DAT_4000166a) {
  case '\0':
    DAT_4000166a = DAT_4000166a + '\x01';
    break;
  case '\x01':
    DAT_4000166a = DAT_4000166a + '\x01';
    break;
  case '\x02':
    FUN_0006f96c();
    DAT_4000166a = DAT_4000166a + '\x01';
    break;
  case '\x03':
    FUN_00066154();
    DAT_4000166a = DAT_4000166a + '\x01';
    break;
  case '\x04':
    FUN_000682ec();
    DAT_4000166a = DAT_4000166a + '\x01';
    break;
  case '\x05':
    FUN_0006b2b8();
    DAT_4000166a = DAT_4000166a + '\x01';
    break;
  case '\x06':
    FUN_00071ebc();
    DAT_4000166a = DAT_4000166a + '\x01';
    break;
  case '\a':
    DAT_4000166a = DAT_4000166a + '\x01';
    break;
  case '\b':
    DAT_4000166a = DAT_4000166a + '\x01';
    break;
  case '\t':
    DAT_4000166a = DAT_4000166a + '\x01';
    break;
  case '\n':
    DAT_4000166a = DAT_4000166a + '\x01';
    break;
  case '\v':
    DAT_4000166a = DAT_4000166a + '\x01';
    break;
  case '\f':
    DAT_4000166a = DAT_4000166a + '\x01';
    break;
  case '\r':
    DAT_4000166a = DAT_4000166a + '\x01';
    break;
  case '\x0e':
    DAT_4000166a = DAT_4000166a + '\x01';
    break;
  case '\x0f':
    DAT_4000166a = DAT_4000166a + '\x01';
    break;
  case '\x10':
    DAT_40001666 = DAT_40001666 | 0x10;
    DAT_4000166a = DAT_4000166a + '\x01';
    break;
  case '\x11':
    DAT_4000166a = DAT_4000166a + '\x01';
    break;
  case '\x12':
    DAT_4000166a = DAT_4000166a + '\x01';
    break;
  case '\x13':
    DAT_4000166a = DAT_4000166a + '\x01';
    break;
  case '\x14':
    DAT_4000166a = DAT_4000166a + '\x01';
    break;
  case '\x15':
    DAT_4000166a = DAT_4000166a + '\x01';
    break;
  case '\x16':
    DAT_4000166a = DAT_4000166a + '\x01';
    break;
  case '\x17':
    if ((DAT_40001666 & 0x20) != 0) {
      DAT_40001674 = (ushort)DAT_4000e256 * 10;
    }
    DAT_4000166a = DAT_4000166a + '\x01';
    break;
  default:
    uVar1 = 1;
  }
  return uVar1;
}



void obd_set_new_DTC(byte *param_1,byte *param_2,ushort param_3,short param_4)

{
  ushort uVar1;
  
  param_3 = param_3 | param_4 << 0xe;
  if ((*param_1 & 7) == 1) {
    uVar1 = DAT_40001666;
    if (((*param_1 & 0x10) != 0) && (uVar1 = DAT_40001666 | 1, (*param_2 & 1) == 0)) {
      uVar1 = DAT_40001666;
    }
    DAT_40001666 = uVar1;
    uVar1 = DAT_40001666;
    if (((*param_1 & 0x40) != 0) && (uVar1 = DAT_40001666 | 0x80, (*param_2 & 1) == 0)) {
      uVar1 = DAT_40001666;
    }
    DAT_40001666 = uVar1;
    uVar1 = DAT_40001666;
    if (((*param_1 & 0x20) != 0) && (uVar1 = DAT_40001666 | 0x20, (*param_2 & 1) == 0)) {
      uVar1 = DAT_40001666;
    }
    DAT_40001666 = uVar1;
    if ((*param_2 & 2) != 0) {
      *param_2 = *param_2 | 0x80;
      if ((*param_1 & 0x10) == 0) {
        FUN_000616fc(param_3);
      }
      else {
        FUN_0005f9d8(param_3);
      }
    }
  }
  else if ((*param_1 & 7) == 2) {
    uVar1 = DAT_40001666;
    if (((*param_1 & 0x10) != 0) && (uVar1 = DAT_40001666 | 1, (*param_2 & 1) == 0)) {
      uVar1 = DAT_40001666;
    }
    DAT_40001666 = uVar1;
    uVar1 = DAT_40001666;
    if (((*param_1 & 0x40) != 0) && (uVar1 = DAT_40001666 | 0x80, (*param_2 & 1) == 0)) {
      uVar1 = DAT_40001666;
    }
    DAT_40001666 = uVar1;
    uVar1 = DAT_40001666;
    if (((*param_1 & 0x20) != 0) && (uVar1 = DAT_40001666 | 0x20, (*param_2 & 1) == 0)) {
      uVar1 = DAT_40001666;
    }
    DAT_40001666 = uVar1;
    if (((*param_2 & 0x10) == 0) || ((*param_1 & 0x10) == 0)) {
      if ((*param_2 & 2) != 0) {
        *param_2 = *param_2 | 0x80;
        if ((*param_1 & 0x10) == 0) {
          FUN_000616fc(param_3);
        }
        else {
          FUN_0005f9d8(param_3);
        }
      }
    }
    else {
      FUN_00060f18(param_3);
    }
  }
  else if ((*param_1 & 7) == 3) {
    uVar1 = DAT_40001666;
    if (((*param_1 & 0x10) != 0) && (uVar1 = DAT_40001666 | 1, (*param_2 & 1) == 0)) {
      uVar1 = DAT_40001666;
    }
    DAT_40001666 = uVar1;
    uVar1 = DAT_40001666;
    if (((*param_1 & 0x40) != 0) && (uVar1 = DAT_40001666 | 0x80, (*param_2 & 1) == 0)) {
      uVar1 = DAT_40001666;
    }
    DAT_40001666 = uVar1;
    uVar1 = DAT_40001666;
    if (((*param_1 & 0x20) != 0) && (uVar1 = DAT_40001666 | 0x20, (*param_2 & 1) == 0)) {
      uVar1 = DAT_40001666;
    }
    DAT_40001666 = uVar1;
    if (((*param_2 & 0x10) == 0) || ((*param_1 & 0x10) == 0)) {
      if ((*param_2 & 2) != 0) {
        *param_2 = *param_2 | 0x80;
        if ((*param_1 & 0x10) == 0) {
          FUN_000616fc(param_3);
        }
        else {
          FUN_0005f9d8(param_3);
        }
      }
    }
    else {
      FUN_00060f18(param_3);
    }
  }
  else if ((*param_1 & 7) == 4) {
    uVar1 = DAT_40001666;
    if (((*param_1 & 0x40) != 0) && (uVar1 = DAT_40001666 | 0x40, (*param_2 & 1) == 0)) {
      uVar1 = DAT_40001666;
    }
    DAT_40001666 = uVar1;
    if (((*param_2 & 2) != 0) && (*param_2 = *param_2 | 0x80, (*param_1 & 0x40) != 0)) {
      FUN_000616fc(param_3);
    }
  }
  return;
}



undefined1 * obd_ii_dtc_format(uint param_1)

{
  uint uVar1;
  char cVar2;
  byte bVar3;
  uint uVar4;
  
  if ((param_1 & 0xffff) == 0) {
    for (bVar3 = 0; bVar3 < 5; bVar3 = bVar3 + 1) {
      (&DAT_40001694)[bVar3] = 0x20;
    }
  }
  else {
    if ((int)(param_1 & 0xc000) >> 0xe == 0) {
      DAT_40001694 = 0x50;
    }
    else if ((int)(param_1 & 0xc000) >> 0xe == 1) {
      DAT_40001694 = 0x43;
    }
    else if ((int)(param_1 & 0xc000) >> 0xe == 2) {
      DAT_40001694 = 0x42;
    }
    else if ((int)(param_1 & 0xc000) >> 0xe == 3) {
      DAT_40001694 = 0x55;
    }
    uVar4 = 0xc;
    for (bVar3 = 1; bVar3 < 5; bVar3 = bVar3 + 1) {
      uVar1 = (int)(param_1 & 0x3fff) >> (uVar4 & 0x3f) & 0xf;
      cVar2 = (char)uVar1;
      if (uVar1 < 10) {
        (&DAT_40001694)[bVar3] = cVar2 + '0';
      }
      else {
        (&DAT_40001694)[bVar3] = cVar2 + '7';
      }
      uVar4 = uVar4 - 4 & 0xff;
    }
  }
  return &DAT_40001694;
}



ulonglong obd_ii_dtc_unpack(uint param_1)

{
  ulonglong uVar1;
  ulonglong uVar2;
  
  if ((param_1 & 0xffff) == 0) {
    uVar2 = 0;
  }
  else {
    if ((int)(param_1 & 0xc000) >> 0xe == 1) {
      uVar2 = ZEXT48(&DAT_00002710);
    }
    else if ((int)(param_1 & 0xc000) >> 0xe == 2) {
      uVar2 = ZEXT48(&DAT_00004e20);
    }
    else {
      uVar2 = 0;
      if ((int)(param_1 & 0xc000) >> 0xe == 3) {
        uVar2 = 30000;
      }
    }
    uVar1 = (ulonglong)param_1 & 0x3fff;
    uVar2 = ((uVar2 + ((uVar1 << 0x20) >> 0x2c) * 1000 + ((uVar1 << 0x20) >> 0x28 & 0xf) * 100 &
             0xffff) + ((uVar1 << 0x20) >> 0x24 & 0xf) * 10 & 0xffff) + ((ulonglong)param_1 & 0xf) &
            0xffff;
  }
  return uVar2;
}



void FUN_000506b8(void)

{
  uint uVar1;
  int iVar2;
  
  init_esci_a();
  REG_SIU_PCR198 = 0x100;
  uVar1 = REG_SIU_ECCR;
  REG_SIU_ECCR = uVar1 & 0xffffc0ff | 0x200;
  REG_SIU_PCR214 = 0x200;
  REG_SIU_GPDO209 = 1;
  REG_SIU_PCR209 = 0x2cc;
  REG_SIU_GPDO206 = 0;
  REG_SIU_PCR206 = 0x2cc;
  REG_SIU_GPDO22 = 0;
  REG_SIU_PCR22 = 0x2cc;
  for (iVar2 = 0; iVar2 < 1000; iVar2 = iVar2 + 1) {
    FUN_00047ed4();
  }
  REG_SIU_GPDO206 = 1;
  DAT_40003468 = 0x7694;
  DAT_400016ac = 0;
  DAT_4000153b = 200;
  return;
}



void FUN_00050794(void)

{
  REG_SIU_GPDO206 = 0;
  return;
}



void FUN_000507a4(void)

{
  REG_SIU_GPDO206 = 1;
  return;
}



ulonglong FUN_000507b4(void)

{
  return (ulonglong)(LZCOUNT(&UNK_ffff7695 + DAT_40003468) << 0x20) >> 0x25;
}



void FUN_000507dc(void)

{
  if (DAT_400016aa == 0) {
    DAT_400016aa = 0x14;
    FUN_00056d20();
  }
  FUN_00056d90();
  return;
}



void FUN_00050814(undefined1 *param_1)

{
  undefined1 uVar1;
  uint uVar2;
  byte bVar3;
  uint *puVar4;
  
  if (DAT_40009049 == '\0') {
    puVar4 = &REG_FLEXCAN_A_MB23_DATA0;
    uVar2 = REG_FLEXCAN_A_MB23_CS;
    REG_FLEXCAN_A_MB23_CS = uVar2 & 0xf0ffffff | 0x8000000;
    uVar2 = REG_FLEXCAN_A_MB23_ID;
    REG_FLEXCAN_A_MB23_ID = uVar2 & 0xe003ffff | 0xd840000;
    for (bVar3 = 0; bVar3 < 8; bVar3 = bVar3 + 1) {
      uVar1 = *param_1;
      param_1 = param_1 + 1;
      *(undefined1 *)puVar4 = uVar1;
      puVar4 = (uint *)((int)puVar4 + 1);
    }
    uVar2 = REG_FLEXCAN_A_MB23_CS;
    REG_FLEXCAN_A_MB23_CS = uVar2 & 0xfff0ffff | 0x80000;
    uVar2 = REG_FLEXCAN_A_MB23_CS;
    REG_FLEXCAN_A_MB23_CS = uVar2 & 0xf0ffffff | 0xc000000;
  }
  else {
    puVar4 = &REG_FLEXCAN_C_MB13_DATA0;
    uVar2 = REG_FLEXCAN_C_MB13_CS;
    REG_FLEXCAN_C_MB13_CS = uVar2 & 0xf0ffffff | 0x8000000;
    uVar2 = REG_FLEXCAN_C_MB13_ID;
    REG_FLEXCAN_C_MB13_ID = uVar2 & 0xe003ffff | 0xd840000;
    for (bVar3 = 0; bVar3 < 8; bVar3 = bVar3 + 1) {
      uVar1 = *param_1;
      param_1 = param_1 + 1;
      *(undefined1 *)puVar4 = uVar1;
      puVar4 = (uint *)((int)puVar4 + 1);
    }
    uVar2 = REG_FLEXCAN_C_MB13_CS;
    REG_FLEXCAN_C_MB13_CS = uVar2 & 0xfff0ffff | 0x80000;
    uVar2 = REG_FLEXCAN_C_MB13_CS;
    REG_FLEXCAN_C_MB13_CS = uVar2 & 0xf0ffffff | 0xc000000;
  }
  return;
}



void FUN_00050930(undefined1 *param_1)

{
  undefined1 uVar1;
  uint uVar2;
  byte bVar3;
  uint *puVar4;
  
  if (DAT_40009049 == '\0') {
    puVar4 = &REG_FLEXCAN_A_MB24_DATA0;
    uVar2 = REG_FLEXCAN_A_MB24_CS;
    REG_FLEXCAN_A_MB24_CS = uVar2 & 0xf0ffffff | 0x8000000;
    uVar2 = REG_FLEXCAN_A_MB24_ID;
    REG_FLEXCAN_A_MB24_ID = uVar2 & 0xe003ffff | 0xd840000;
    for (bVar3 = 0; bVar3 < 8; bVar3 = bVar3 + 1) {
      uVar1 = *param_1;
      param_1 = param_1 + 1;
      *(undefined1 *)puVar4 = uVar1;
      puVar4 = (uint *)((int)puVar4 + 1);
    }
    uVar2 = REG_FLEXCAN_A_MB24_CS;
    REG_FLEXCAN_A_MB24_CS = uVar2 & 0xfff0ffff | 0x80000;
    uVar2 = REG_FLEXCAN_A_MB24_CS;
    REG_FLEXCAN_A_MB24_CS = uVar2 & 0xf0ffffff | 0xc000000;
  }
  else {
    puVar4 = &REG_FLEXCAN_C_MB14_DATA0;
    uVar2 = REG_FLEXCAN_C_MB14_CS;
    REG_FLEXCAN_C_MB14_CS = uVar2 & 0xf0ffffff | 0x8000000;
    uVar2 = REG_FLEXCAN_C_MB14_ID;
    REG_FLEXCAN_C_MB14_ID = uVar2 & 0xe003ffff | 0xd840000;
    for (bVar3 = 0; bVar3 < 8; bVar3 = bVar3 + 1) {
      uVar1 = *param_1;
      param_1 = param_1 + 1;
      *(undefined1 *)puVar4 = uVar1;
      puVar4 = (uint *)((int)puVar4 + 1);
    }
    uVar2 = REG_FLEXCAN_C_MB14_CS;
    REG_FLEXCAN_C_MB14_CS = uVar2 & 0xfff0ffff | 0x80000;
    uVar2 = REG_FLEXCAN_C_MB14_CS;
    REG_FLEXCAN_C_MB14_CS = uVar2 & 0xf0ffffff | 0xc000000;
  }
  return;
}



void FUN_00050a4c(void)

{
  FUN_00051bcc(&DAT_40003478);
  return;
}



void FUN_00050a74(void)

{
  DAT_4000348c = 0;
  DAT_4000348d = 0;
  return;
}



bool flexcan_build_telemetry_message___(undefined1 *param_1)

{
  bool bVar1;
  undefined1 uVar2;
  int iVar3;
  
  bVar1 = DAT_4000348c < 0x78;
  if (bVar1) {
    iVar3 = (((uint)DAT_4000348d + (uint)DAT_4000348c) % 0x78) * 8;
    uVar2 = param_1[1];
    (&DAT_4000348e)[iVar3] = *param_1;
    (&DAT_4000348f)[iVar3] = uVar2;
    uVar2 = param_1[3];
    (&DAT_40003490)[iVar3] = param_1[2];
    (&DAT_40003491)[iVar3] = uVar2;
    uVar2 = param_1[5];
    (&DAT_40003492)[iVar3] = param_1[4];
    (&DAT_40003493)[iVar3] = uVar2;
    uVar2 = param_1[7];
    (&DAT_40003494)[iVar3] = param_1[6];
    (&DAT_40003495)[iVar3] = uVar2;
    DAT_4000348c = DAT_4000348c + 1;
  }
  return bVar1;
}



undefined8 thunk_FUN_00050ba0(uint param_1,char param_2,undefined1 *param_3)

{
  bool bVar1;
  
  while( true ) {
    bVar1 = param_2 == '\0';
    param_2 = param_2 + -1;
    if (bVar1) break;
    *(undefined1 *)(&DAT_40003484)[param_1 & 0xff] = *param_3;
    (&DAT_40003484)[param_1 & 0xff] = (&DAT_40003484)[param_1 & 0xff] + 1;
    param_3 = param_3 + 1;
  }
  return 1;
}



undefined8 FUN_00050ba0(uint param_1,char param_2,undefined1 *param_3)

{
  bool bVar1;
  
  while( true ) {
    bVar1 = param_2 == '\0';
    param_2 = param_2 + -1;
    if (bVar1) break;
    *(undefined1 *)(&DAT_40003484)[param_1 & 0xff] = *param_3;
    (&DAT_40003484)[param_1 & 0xff] = (&DAT_40003484)[param_1 & 0xff] + 1;
    param_3 = param_3 + 1;
  }
  return 1;
}



void diag_stream_read(uint param_1,char param_2,undefined1 *param_3)

{
  bool bVar1;
  
  while( true ) {
    bVar1 = param_2 == '\0';
    param_2 = param_2 + -1;
    if (bVar1) break;
    *param_3 = *(undefined1 *)(&DAT_40003484)[param_1 & 0xff];
    param_3 = param_3 + 1;
    (&DAT_40003484)[param_1 & 0xff] = (&DAT_40003484)[param_1 & 0xff] + 1;
  }
  return;
}



void diag_stream_read(uint param_1,char param_2,undefined1 *param_3)

{
  bool bVar1;
  
  while( true ) {
    bVar1 = param_2 == '\0';
    param_2 = param_2 + -1;
    if (bVar1) break;
    *param_3 = *(undefined1 *)(&DAT_40003484)[param_1 & 0xff];
    param_3 = param_3 + 1;
    (&DAT_40003484)[param_1 & 0xff] = (&DAT_40003484)[param_1 & 0xff] + 1;
  }
  return;
}



undefined8 chlog_group_init(byte param_1)

{
  undefined8 uVar1;
  undefined1 *puVar2;
  
  if (param_1 < 10) {
    for (puVar2 = &DAT_40003854 + (uint)param_1 * 0x2a8;
        puVar2 < (undefined1 *)((uint)param_1 * 0x2a8 + 0x40003afc); puVar2 = puVar2 + 1) {
      *puVar2 = 0;
    }
    DAT_40003480 = DAT_40003480 | 2;
    FUN_00050a74();
    uVar1 = 0xc;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



undefined8 chlog_group_set_timing(byte param_1,undefined1 param_2,undefined1 param_3,short param_4)

{
  undefined8 uVar1;
  
  if (param_1 < 10) {
    (&DAT_40003af8)[(uint)param_1 * 0x2a8] = param_3;
    if (param_4 == 0) {
      param_4 = 1;
    }
    (&DAT_40003af4)[(uint)param_1 * 0x154] = param_4;
    (&DAT_40003af6)[(uint)param_1 * 0x154] = 1;
    (&DAT_40003af9)[(uint)param_1 * 0x2a8] = param_2;
    (&DAT_40003afa)[(uint)param_1 * 0x2a8] = 4;
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



bool FUN_00050d44(byte param_1)

{
  if (param_1 < 10) {
    (&DAT_40003afa)[(uint)param_1 * 0x2a8] = 1;
    DAT_40003480 = DAT_40003480 | 0x80;
  }
  return param_1 < 10;
}



void chlog_start_all(void)

{
  byte bVar1;
  
  for (bVar1 = 0; bVar1 < 10; bVar1 = bVar1 + 1) {
    if ((&DAT_40003afa)[(uint)bVar1 * 0x2a8] == '\x04') {
      (&DAT_40003afa)[(uint)bVar1 * 0x2a8] = 1;
    }
  }
  DAT_40003480 = DAT_40003480 | 0x80;
  return;
}



void chlog_group_stop(byte param_1)

{
  byte bVar1;
  
  if (param_1 < 10) {
    (&DAT_40003afa)[(uint)param_1 * 0x2a8] = 0;
    for (bVar1 = 0; bVar1 < 10; bVar1 = bVar1 + 1) {
      if (((&DAT_40003afa)[(uint)bVar1 * 0x2a8] & 1) != 0) {
        return;
      }
    }
    DAT_40003480 = DAT_40003480 & 0x7f;
  }
  return;
}



void chlog_stop_all(void)

{
  byte bVar1;
  
  for (bVar1 = 0; bVar1 < 10; bVar1 = bVar1 + 1) {
    (&DAT_40003afa)[(uint)bVar1 * 0x2a8] = 0;
  }
  DAT_40003480 = DAT_40003480 & 0x77;
  return;
}



undefined8 FUN_00050eec(undefined1 param_1,uint param_2,uint param_3)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  char cVar4;
  undefined4 *puVar5;
  int *piVar6;
  undefined8 uVar7;
  undefined1 local_20;
  undefined4 local_1f;
  undefined4 auStack_18 [6];
  
  uVar7 = 1;
  iVar2 = (param_2 & 0xff) * 0x2a8 + (param_3 & 0xff) * 0x38;
  piVar6 = (int *)(&DAT_40003854 + iVar2);
  puVar5 = &local_1f;
  do {
    if (((auStack_18 <= puVar5) || ((int *)(iVar2 + 0x40003894) <= piVar6)) || (*piVar6 == 0))
    goto LAB_00050fb8;
    puVar1 = (undefined4 *)*piVar6;
    uVar3 = (uint)*(byte *)(piVar6 + 1);
    if (uVar3 == 4) {
      *puVar5 = *puVar1;
    }
    else if (uVar3 == 2) {
      *(undefined2 *)puVar5 = *(undefined2 *)puVar1;
    }
    else {
      if (uVar3 != 1) {
        uVar7 = 0;
LAB_00050fb8:
        local_20 = param_1;
        cVar4 = flexcan_build_telemetry_message___(&local_20);
        if (cVar4 == '\0') {
          uVar7 = 0;
        }
        return uVar7;
      }
      *(undefined1 *)puVar5 = *(undefined1 *)puVar1;
    }
    puVar5 = (undefined4 *)((int)puVar5 + uVar3);
    piVar6 = piVar6 + 2;
  } while( true );
}



void flexcan_counters_scheduler_tick(char param_1)

{
  short sVar1;
  int iVar2;
  byte bVar3;
  char cVar4;
  byte bVar5;
  
  if ((DAT_40003480 & 0x80) != 0) {
    cVar4 = '\0';
    for (bVar5 = 0; bVar5 < 10; bVar5 = bVar5 + 1) {
      if ((((&DAT_40003afa)[(uint)bVar5 * 0x2a8] & 1) != 0) &&
         (param_1 == (&DAT_40003af8)[(uint)bVar5 * 0x2a8])) {
        sVar1 = (&DAT_40003af6)[(uint)bVar5 * 0x154];
        (&DAT_40003af6)[(uint)bVar5 * 0x154] = sVar1 + -1;
        if ((short)(sVar1 + -1) == 0) {
          (&DAT_40003af6)[(uint)bVar5 * 0x154] = (&DAT_40003af4)[(uint)bVar5 * 0x154];
          if ((int)(uint)(byte)(&DAT_40003af9)[(uint)bVar5 * 0x2a8] <
              (int)(0x78 - (uint)DAT_4000348c)) {
            for (bVar3 = 0; bVar3 <= (byte)(&DAT_40003af9)[(uint)bVar5 * 0x2a8]; bVar3 = bVar3 + 1)
            {
              iVar2 = FUN_00050eec(cVar4 + bVar3 | (&DAT_40003afa)[(uint)bVar5 * 0x2a8] & 0x80,bVar5
                                   ,bVar3);
              if (iVar2 == 0) {
                (&DAT_40003afa)[(uint)bVar5 * 0x2a8] = (&DAT_40003afa)[(uint)bVar5 * 0x2a8] | 0x80;
              }
              else {
                (&DAT_40003afa)[(uint)bVar5 * 0x2a8] = (&DAT_40003afa)[(uint)bVar5 * 0x2a8] & 0x7f;
              }
            }
          }
          else {
            (&DAT_40003afa)[(uint)bVar5 * 0x2a8] = (&DAT_40003afa)[(uint)bVar5 * 0x2a8] | 0x80;
          }
        }
      }
      cVar4 = cVar4 + '\f';
    }
    if (((DAT_40003480 & 8) == 0) && (DAT_4000348c != 0)) {
      DAT_40003480 = DAT_40003480 | 8;
      flexcan_a_tx_drain_sw_queue();
    }
  }
  return;
}



undefined8 diagnostic_tx_unknown(void)

{
  ushort uVar1;
  
  FUN_00051bf8();
  if (DAT_400052e6 != 0) {
    if (DAT_400052e6 < 0x100) {
      uVar1 = DAT_400052e6 & 0xff;
      DAT_400052e6 = 0;
    }
    else {
      uVar1 = 0;
      DAT_400052e6 = DAT_400052e6 - 0x100;
    }
    do {
      DAT_4000347c._0_2_ = DAT_4000347c._0_2_ + (ushort)*DAT_40003488;
      DAT_40003488 = DAT_40003488 + 1;
      uVar1 = uVar1 - 1;
    } while ((uVar1 & 0xff) != 0);
    if (DAT_400052e6 != 0) {
      return 1;
    }
    FUN_00050a4c();
  }
  return 0;
}



void FUN_00051358(char *param_1)

{
  char cVar2;
  undefined4 uVar1;
  
  if ((*param_1 == '\x01') || (*param_1 == '\x05')) {
    if (*(short *)(param_1 + 2) != 0) {
      if ((DAT_40003480 & 0x20) == 0) {
        return;
      }
      DAT_40003480 = DAT_40003480 & 0xdf | 0x10;
      return;
    }
    if (*param_1 == '\x01') {
      if (((DAT_40003480 & 0x20) == 0) && ((DAT_40003480 & 0x10) == 0)) {
        chlog_stop_all();
        DAT_40003481 = 0;
      }
      DAT_40003480 = DAT_40003480 & 0xef | 0x20;
    }
    DAT_40003478 = 0xff;
    DAT_40003479 = 0;
    DAT_4000347a = param_1[1];
    DAT_4000347b = 0xfe;
    DAT_4000347c = 0;
  }
  else {
    if ((DAT_40003480 & 0x20) == 0) {
      return;
    }
    DAT_40003478 = 0xff;
    DAT_40003479 = 0;
    DAT_4000347a = param_1[1];
    switch(*param_1) {
    default:
      DAT_40003479 = 0x30;
      break;
    case '\x02':
      if (param_1[2] == '\0') {
        uVar1 = FUN_00051bf0(param_1[3],*(undefined4 *)(param_1 + 4));
        (&DAT_40003484)[(byte)param_1[2]] = (undefined1 *)uVar1;
      }
      else {
        DAT_40003479 = 0x32;
      }
      break;
    case '\x03':
      cVar2 = thunk_FUN_00050ba0(0,param_1[2],param_1 + 3);
      if (cVar2 == '\x02') {
        return;
      }
      if ((cVar2 == '\0') || (cVar2 == '\x03')) {
        DAT_40003479 = 0x33;
      }
      break;
    case '\x04':
      diag_stream_read(0,param_1[2],&DAT_4000347b);
      break;
    case '\x06':
      if ((DAT_40003480 & 2) == 0) {
        DAT_40003479 = 0x22;
      }
      else if (param_1[2] == '\0') {
        chlog_group_stop(param_1[3]);
      }
      else if (param_1[2] == '\x01') {
        chlog_group_set_timing(param_1[3],param_1[4],param_1[5],*(undefined2 *)(param_1 + 6));
        FUN_00050d44(param_1[3]);
      }
      else if (param_1[2] == '\x02') {
        chlog_group_set_timing(param_1[3],param_1[4],param_1[5],*(undefined2 *)(param_1 + 6));
      }
      else {
        DAT_40003479 = 0x31;
      }
      break;
    case '\a':
      DAT_40003480 = DAT_40003480 & 0xdf;
      if (param_1[2] == '\0') {
        DAT_40003480 = DAT_40003480 | 0x10;
      }
      else {
        chlog_stop_all();
      }
      break;
    case '\b':
      if ((DAT_40003480 & 2) == 0) {
        DAT_40003479 = 0x22;
      }
      else if (param_1[2] == '\0') {
        chlog_stop_all();
      }
      else if (param_1[2] == '\x01') {
        chlog_start_all();
      }
      else {
        DAT_40003479 = 0x31;
      }
      break;
    case '\t':
      DAT_4000347b = 0;
      DAT_4000347c = DAT_40001578;
      break;
    case '\x0e':
      DAT_40003478 = 0xff;
      DAT_40003479 = 0;
      DAT_4000347b = 2;
      DAT_4000347c = 0;
      DAT_40003488 = DAT_40003484;
      DAT_400052e6 = *(undefined2 *)(param_1 + 4);
      return;
    case '\x0f':
      DAT_40003488 = (undefined1 *)FUN_00051bf0(param_1[3],*(undefined4 *)(param_1 + 4));
      diag_stream_read(1,param_1[2],&DAT_4000347b);
      break;
    case '\x11':
      FUN_00051b98(DAT_40003484);
      break;
    case '\x14':
      chlog_group_stop(param_1[2]);
      DAT_4000347b = chlog_group_init(param_1[2]);
      DAT_4000347c = CONCAT13(param_1[2] * '\f',DAT_4000347c._1_3_);
      break;
    case '\x15':
      if ((((byte)param_1[2] < 10) && ((byte)param_1[3] < 0xc)) && ((byte)param_1[4] < 8)) {
        DAT_40003850 = (undefined4 *)
                       (&DAT_40003854 +
                       (uint)(byte)param_1[2] * 0x2a8 + (uint)(byte)param_1[3] * 0x38 +
                       (uint)(byte)param_1[4] * 8);
      }
      else {
        DAT_40003479 = 0x31;
        DAT_40003850 = (undefined4 *)0x0;
      }
      break;
    case '\x16':
      if ((((param_1[2] == '\x01') || (param_1[2] == '\x02')) || (param_1[2] == '\x04')) &&
         (DAT_40003850 != (undefined4 *)0x0)) {
        uVar1 = FUN_00051bf0(param_1[3],*(undefined4 *)(param_1 + 4));
        *DAT_40003850 = uVar1;
        *(char *)(DAT_40003850 + 1) = param_1[2];
      }
      else {
        DAT_40003479 = 0x31;
      }
      break;
    case '\x17':
      for (DAT_4000347b = 0; (&DAT_40001420)[DAT_4000347b] != '\0'; DAT_4000347b = DAT_4000347b + 1)
      {
      }
      DAT_4000347c = 0x3008e;
      DAT_40003484 = &DAT_40001420;
      break;
    case '\x1b':
      DAT_4000347b = 2;
      DAT_4000347c = CONCAT13(1,DAT_4000347c._1_3_);
      break;
    case '#':
      cVar2 = thunk_FUN_00050ba0(0,6,param_1 + 2);
      if (cVar2 == '\x02') {
        return;
      }
      if ((cVar2 == '\0') || (cVar2 == '\x03')) {
        DAT_40003479 = 0x33;
      }
    }
  }
  FUN_00050a4c();
  return;
}



void clear_can_logging_buffer(void)

{
  byte *pbVar1;
  
  for (pbVar1 = &DAT_40003478; pbVar1 < obd_ii_request; pbVar1 = pbVar1 + 1) {
    *pbVar1 = 0;
  }
  return;
}



void flexcan_a_tx_drain_sw_queue(void)

{
  if (((DAT_40003480 & 0x80) != 0) && (DAT_4000348c != '\0')) {
    flexcan_tx_from_queue_helper(&DAT_4000348e + (uint)DAT_4000348d * 8);
    DAT_4000348d = DAT_4000348d + 1;
    if (0x77 < DAT_4000348d) {
      DAT_4000348d = 0;
    }
    DAT_4000348c = DAT_4000348c + -1;
    if (DAT_4000348c == '\0') {
      DAT_40003480 = DAT_40003480 & 0xf7;
    }
  }
  return;
}



void FUN_00051b98(undefined4 param_1)

{
  DAT_40001578 = param_1;
  return;
}



undefined8 flexcan_tx_from_queue_helper(void)

{
  FUN_00050814();
  DAT_40001418 = 4;
  return 1;
}



undefined8 FUN_00051bcc(void)

{
  FUN_00050930();
  return 1;
}



undefined8 FUN_00051bf0(undefined8 param_1,undefined8 param_2)

{
  return param_2;
}



void FUN_00051bf8(void)

{
  return;
}



void flexcan_diagnostics_tx(void)

{
  DAT_400016b8 = DAT_400016b8 + 1;
  diagnostic_tx_unknown();
  return;
}



void flexcan_a_obd_send_messages(void)

{
  uint uVar1;
  byte bVar3;
  uint uVar2;
  
  uVar1 = REG_FLEXCAN_A_MB22_CS;
  REG_FLEXCAN_A_MB22_CS = uVar1 & 0xf0ffffff | 0x8000000;
  uVar1 = REG_FLEXCAN_A_MB22_ID;
  REG_FLEXCAN_A_MB22_ID = uVar1 & 0xe003ffff | 0x1fa40000;
  if (obd_ii_tx_messages_pending) {
    if (obd_ii_tx_messages_pending < 2) {
      uVar1 = 0;
    }
    else {
      uVar1 = (obd_ii_tx_messages_pending - 1) * 7 & 0xffff;
    }
    REG_FLEXCAN_A_MB22_DATA0._0_1_ = obd_ii_tx_messages_pending & 0xfU | 0x20;
    if ((uVar1 & 0xff) + 0xd < (uint)obd_ii_response_length) {
      for (bVar3 = 0; bVar3 < 7; bVar3 = bVar3 + 1) {
        *(byte *)((int)&REG_FLEXCAN_A_MB22_DATA0 + bVar3 + 1) =
             obd_ii_response[(uVar1 & 0xff) + (uint)bVar3 + 6];
      }
      if (obd_ii_tx_messages_pending < 0xff) {
        obd_ii_tx_messages_pending = (bool)(obd_ii_tx_messages_pending + '\x01');
      }
      else {
        obd_ii_tx_messages_pending = false;
      }
    }
    else {
      for (uVar2 = 0; (int)(uVar2 & 0xff) < (int)((obd_ii_response_length - uVar1) + -6);
          uVar2 = uVar2 + 1) {
        *(byte *)((int)&REG_FLEXCAN_A_MB22_DATA0 + (uVar2 & 0xff) + 1) =
             obd_ii_response[(uVar1 & 0xff) + (uVar2 & 0xff) + 6];
      }
      for (uVar1 = (obd_ii_response_length - uVar1) - 6 & 0xff; (uVar1 & 0xff) < 7;
          uVar1 = uVar1 + 1) {
        *(undefined1 *)((int)&REG_FLEXCAN_A_MB22_DATA0 + (uVar1 & 0xff) + 1) = 0;
      }
      isotp_stmin = 0;
      isotp_block_counter = 0;
      isotp_fc_received = false;
      obd_ii_tx_messages_pending = false;
    }
  }
  else if (obd_ii_response_length < 8) {
    REG_FLEXCAN_A_MB22_DATA0._0_1_ = (char)obd_ii_response_length;
    for (uVar1 = 0; (uVar1 & 0xff) < (uint)obd_ii_response_length; uVar1 = uVar1 + 1) {
      *(byte *)((int)&REG_FLEXCAN_A_MB22_DATA0 + (uVar1 & 0xff) + 1) = obd_ii_response[uVar1 & 0xff]
      ;
    }
    for (uVar1 = obd_ii_response_length & 0xff; (uVar1 & 0xff) < 7; uVar1 = uVar1 + 1) {
      *(undefined1 *)((int)&REG_FLEXCAN_A_MB22_DATA0 + (uVar1 & 0xff) + 1) = 0;
    }
    obd_ii_tx_messages_pending = false;
  }
  else {
    REG_FLEXCAN_A_MB22_DATA0._0_1_ = (byte)(obd_ii_response_length >> 8) | 0x10;
    REG_FLEXCAN_A_MB22_DATA0._1_1_ = (char)obd_ii_response_length;
    for (bVar3 = 0; bVar3 < 6; bVar3 = bVar3 + 1) {
      *(byte *)((int)&REG_FLEXCAN_A_MB22_DATA0 + bVar3 + 2) = obd_ii_response[bVar3];
    }
    obd_ii_tx_messages_pending = true;
  }
  uVar1 = REG_FLEXCAN_A_MB22_CS;
  REG_FLEXCAN_A_MB22_CS = uVar1 & 0xfff0ffff | 0x80000;
  uVar1 = REG_FLEXCAN_A_MB22_CS;
  REG_FLEXCAN_A_MB22_CS = uVar1 & 0xf0ffffff | 0xc000000;
  return;
}



void obd_ii_send_200hz(void)

{
  if ((isotp_fc_received) && (obd_ii_tx_messages_pending)) {
    if (isotp_flow_status == '\0') {
      if (isotp_block_counter == '\0') {
        if (isotp_block_size == '\0') {
          isotp_block_counter = -1;
        }
        else {
          isotp_block_counter = isotp_block_size;
          isotp_block_size = '\0';
        }
      }
      if (isotp_block_counter != '\0') {
        if (isotp_stmin_counter == 0) {
          flexcan_a_obd_send_messages();
          isotp_block_counter = isotp_block_counter + -1;
          if (isotp_block_counter == '\0') {
            isotp_fc_received = false;
            isotp_stmin = 0;
            isotp_block_counter = '\0';
            isotp_block_size = '\0';
            isotp_flow_status = '\0';
          }
          if ((isotp_stmin & 0xf0) == 0xf0) {
            isotp_stmin_counter = 0;
          }
          else {
            isotp_stmin_counter = isotp_stmin / 5;
          }
        }
        else {
          isotp_stmin_counter = isotp_stmin_counter - 1;
        }
      }
    }
    else if (isotp_flow_status == '\x01') {
      isotp_fc_received = false;
    }
    else if (isotp_flow_status == '\x02') {
      isotp_fc_received = false;
      isotp_stmin = 0;
      isotp_block_counter = '\0';
      isotp_block_size = '\0';
      isotp_flow_status = '\0';
    }
  }
  return;
}



void FUN_00052034(void)

{
  ushort uVar1;
  byte bVar2;
  uint uVar3;
  
  uVar3 = REG_FLEXCAN_A_MCR;
  REG_FLEXCAN_A_MCR = uVar3 & 0xfdffffff | 0x2000000;
  do {
    uVar3 = REG_FLEXCAN_A_MCR;
  } while ((uVar3 >> 0x19 & 1) == 1);
  uVar3 = REG_FLEXCAN_A_MCR;
  REG_FLEXCAN_A_MCR = uVar3 & 0xefffffff | 0x10000000;
  do {
    uVar3 = REG_FLEXCAN_A_MCR;
  } while ((uVar3 & 0x9000000) != 0x9000000);
  REG_FLEXCAN_A_CR = 0x1510001;
  REG_FLEXCAN_A_MB0_CS = 0;
  uVar3 = REG_FLEXCAN_A_MB0_CS;
  REG_FLEXCAN_A_MB0_CS = uVar3 & 0xf0ffffff | 0x4000000;
  REG_FLEXCAN_A_MB0_ID = 0x2140000;
  uVar3 = REG_FLEXCAN_A_MB0_CS;
  REG_FLEXCAN_A_MB0_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_A_MB1_CS = 0;
  uVar3 = REG_FLEXCAN_A_MB1_CS;
  REG_FLEXCAN_A_MB1_CS = uVar3 & 0xf0ffffff | 0x4000000;
  REG_FLEXCAN_A_MB1_ID = 0x3480000;
  uVar3 = REG_FLEXCAN_A_MB1_CS;
  REG_FLEXCAN_A_MB1_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_A_MB2_CS = 0;
  uVar3 = REG_FLEXCAN_A_MB2_CS;
  REG_FLEXCAN_A_MB2_CS = uVar3 & 0xf0ffffff | 0x4000000;
  REG_FLEXCAN_A_MB2_ID = 0x4080000;
  uVar3 = REG_FLEXCAN_A_MB2_CS;
  REG_FLEXCAN_A_MB2_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_A_MB3_CS = 0;
  uVar3 = REG_FLEXCAN_A_MB3_CS;
  REG_FLEXCAN_A_MB3_CS = uVar3 & 0xf0ffffff | 0x4000000;
  REG_FLEXCAN_A_MB3_ID = 0x101c0000;
  uVar3 = REG_FLEXCAN_A_MB3_CS;
  REG_FLEXCAN_A_MB3_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_A_MB4_CS = 0;
  uVar3 = REG_FLEXCAN_A_MB4_CS;
  REG_FLEXCAN_A_MB4_CS = uVar3 & 0xf0ffffff | 0x4000000;
  REG_FLEXCAN_A_MB4_ID = 0xc0c0000;
  uVar3 = REG_FLEXCAN_A_MB4_CS;
  REG_FLEXCAN_A_MB4_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_A_MB5_CS = 0;
  uVar3 = REG_FLEXCAN_A_MB5_CS;
  REG_FLEXCAN_A_MB5_CS = uVar3 & 0xf0ffffff | 0x4000000;
  REG_FLEXCAN_A_MB5_ID = 0x4500000;
  uVar3 = REG_FLEXCAN_A_MB5_CS;
  REG_FLEXCAN_A_MB5_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_A_MB6_CS = 0;
  uVar3 = REG_FLEXCAN_A_MB6_CS;
  REG_FLEXCAN_A_MB6_CS = uVar3 & 0xf0ffffff | 0x4000000;
  REG_FLEXCAN_A_MB6_ID = 0xc400000;
  uVar3 = REG_FLEXCAN_A_MB6_CS;
  REG_FLEXCAN_A_MB6_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_A_MB8_CS = 0;
  uVar3 = REG_FLEXCAN_A_MB8_CS;
  REG_FLEXCAN_A_MB8_CS = uVar3 & 0xf0ffffff | 0x4000000;
  REG_FLEXCAN_A_MB8_ID = 0x2000000;
  uVar3 = REG_FLEXCAN_A_MB8_CS;
  REG_FLEXCAN_A_MB8_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_A_MB9_CS = 0;
  uVar3 = REG_FLEXCAN_A_MB9_CS;
  REG_FLEXCAN_A_MB9_CS = uVar3 & 0xf0ffffff | 0x4000000;
  REG_FLEXCAN_A_MB9_ID = 0x1f7c0000;
  uVar3 = REG_FLEXCAN_A_MB9_CS;
  REG_FLEXCAN_A_MB9_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_A_MB10_CS = 0;
  uVar3 = REG_FLEXCAN_A_MB10_CS;
  REG_FLEXCAN_A_MB10_CS = uVar3 & 0xf0ffffff | 0x4000000;
  REG_FLEXCAN_A_MB10_ID = 0x1f840000;
  uVar3 = REG_FLEXCAN_A_MB10_CS;
  REG_FLEXCAN_A_MB10_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_A_MB11_CS = 0;
  uVar3 = REG_FLEXCAN_A_MB11_CS;
  REG_FLEXCAN_A_MB11_CS = uVar3 & 0xf0ffffff | 0x4000000;
  REG_FLEXCAN_A_MB11_ID = 0x14100000;
  uVar3 = REG_FLEXCAN_A_MB11_CS;
  REG_FLEXCAN_A_MB11_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_A_MB12_CS = 0;
  uVar3 = REG_FLEXCAN_A_MB12_CS;
  REG_FLEXCAN_A_MB12_CS = uVar3 & 0xf0ffffff | 0x4000000;
  REG_FLEXCAN_A_MB12_ID = 0xd800000;
  uVar3 = REG_FLEXCAN_A_MB12_CS;
  REG_FLEXCAN_A_MB12_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_A_MB13_CS = 0;
  uVar3 = REG_FLEXCAN_A_MB13_CS;
  REG_FLEXCAN_A_MB13_CS = uVar3 & 0xf0ffffff | 0x4000000;
  REG_FLEXCAN_A_MB13_ID = 0x2dc0000;
  uVar3 = REG_FLEXCAN_A_MB13_CS;
  REG_FLEXCAN_A_MB13_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_A_MB14_CS = 0;
  uVar3 = REG_FLEXCAN_A_MB14_CS;
  REG_FLEXCAN_A_MB14_CS = uVar3 & 0xf0ffffff | 0x4000000;
  REG_FLEXCAN_A_MB14_ID = 0x2800000;
  uVar3 = REG_FLEXCAN_A_MB14_CS;
  REG_FLEXCAN_A_MB14_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_A_MB15_CS = 0;
  uVar3 = REG_FLEXCAN_A_MB15_CS;
  REG_FLEXCAN_A_MB15_CS = uVar3 & 0xf0ffffff | 0x4000000;
  REG_FLEXCAN_A_MB15_ID = 0x1800000;
  uVar3 = REG_FLEXCAN_A_MB15_CS;
  REG_FLEXCAN_A_MB15_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_A_MB16_CS = 0;
  uVar3 = REG_FLEXCAN_A_MB16_CS;
  REG_FLEXCAN_A_MB16_CS = uVar3 & 0xf0ffffff | 0x8000000;
  REG_FLEXCAN_A_MB16_ID = 0;
  uVar3 = REG_FLEXCAN_A_MB16_CS;
  REG_FLEXCAN_A_MB16_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_A_MB17_CS = 0;
  REG_FLEXCAN_A_MB18_CS = 0;
  uVar3 = REG_FLEXCAN_A_MB18_CS;
  REG_FLEXCAN_A_MB18_CS = uVar3 & 0xf0ffffff | 0x8000000;
  REG_FLEXCAN_A_MB18_ID = 0;
  uVar3 = REG_FLEXCAN_A_MB18_CS;
  REG_FLEXCAN_A_MB18_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_A_MB19_CS = 0;
  uVar3 = REG_FLEXCAN_A_MB19_CS;
  REG_FLEXCAN_A_MB19_CS = uVar3 & 0xf0ffffff | 0x8000000;
  REG_FLEXCAN_A_MB19_ID = 0;
  uVar3 = REG_FLEXCAN_A_MB19_CS;
  REG_FLEXCAN_A_MB19_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_A_MB20_CS = 0;
  uVar3 = REG_FLEXCAN_A_MB20_CS;
  REG_FLEXCAN_A_MB20_CS = uVar3 & 0xf0ffffff | 0x8000000;
  REG_FLEXCAN_A_MB20_ID = 0;
  uVar3 = REG_FLEXCAN_A_MB20_CS;
  REG_FLEXCAN_A_MB20_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_A_MB21_CS = 0;
  uVar3 = REG_FLEXCAN_A_MB21_CS;
  REG_FLEXCAN_A_MB21_CS = uVar3 & 0xf0ffffff | 0x8000000;
  REG_FLEXCAN_A_MB21_ID = 0;
  uVar3 = REG_FLEXCAN_A_MB21_CS;
  REG_FLEXCAN_A_MB21_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_A_MB22_CS = 0;
  uVar3 = REG_FLEXCAN_A_MB22_CS;
  REG_FLEXCAN_A_MB22_CS = uVar3 & 0xf0ffffff | 0x8000000;
  REG_FLEXCAN_A_MB22_ID = 0;
  uVar3 = REG_FLEXCAN_A_MB22_CS;
  REG_FLEXCAN_A_MB22_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_A_MB23_CS = 0;
  uVar3 = REG_FLEXCAN_A_MB23_CS;
  REG_FLEXCAN_A_MB23_CS = uVar3 & 0xf0ffffff | 0x8000000;
  REG_FLEXCAN_A_MB23_ID = 0xd840000;
  uVar3 = REG_FLEXCAN_A_MB23_CS;
  REG_FLEXCAN_A_MB23_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_A_MB24_CS = 0;
  uVar3 = REG_FLEXCAN_A_MB24_CS;
  REG_FLEXCAN_A_MB24_CS = uVar3 & 0xf0ffffff | 0x8000000;
  REG_FLEXCAN_A_MB24_ID = 0xd840000;
  uVar3 = REG_FLEXCAN_A_MB24_CS;
  REG_FLEXCAN_A_MB24_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_A_RXGMASK = 0x1ff3ffff;
  REG_FLEXCAN_A_RX14MASK = 0x1fc7ffff;
  REG_FLEXCAN_A_RX15MASK = 0x1fe3ffff;
  REG_FLEXCAN_A_IMRH = 0;
  REG_FLEXCAN_A_IMRL = 0;
  uVar3 = REG_FLEXCAN_A_IMRL;
  REG_FLEXCAN_A_IMRL = uVar3 & 0xfffffffe | 1;
  uVar3 = REG_FLEXCAN_A_IMRL;
  REG_FLEXCAN_A_IMRL = uVar3 & 0xfffffffd | 2;
  uVar3 = REG_FLEXCAN_A_IMRL;
  REG_FLEXCAN_A_IMRL = uVar3 & 0xfffffffb | 4;
  uVar3 = REG_FLEXCAN_A_IMRL;
  REG_FLEXCAN_A_IMRL = uVar3 & 0xfffffff7 | 8;
  uVar3 = REG_FLEXCAN_A_IMRL;
  REG_FLEXCAN_A_IMRL = uVar3 & 0xffffffef | 0x10;
  uVar3 = REG_FLEXCAN_A_IMRL;
  REG_FLEXCAN_A_IMRL = uVar3 & 0xffffffdf | 0x20;
  uVar3 = REG_FLEXCAN_A_IMRL;
  REG_FLEXCAN_A_IMRL = uVar3 & 0xffffffbf | 0x40;
  uVar3 = REG_FLEXCAN_A_IMRL;
  REG_FLEXCAN_A_IMRL = uVar3 & 0xffffff7f | 0x80;
  uVar3 = REG_FLEXCAN_A_IMRL;
  REG_FLEXCAN_A_IMRL = uVar3 & 0xfffffeff | 0x100;
  uVar3 = REG_FLEXCAN_A_IMRL;
  REG_FLEXCAN_A_IMRL = uVar3 & 0xfffffdff | 0x200;
  uVar3 = REG_FLEXCAN_A_IMRL;
  REG_FLEXCAN_A_IMRL = uVar3 & 0xfffffbff | 0x400;
  uVar3 = REG_FLEXCAN_A_IMRL;
  REG_FLEXCAN_A_IMRL = uVar3 & 0xfffff7ff | 0x800;
  uVar3 = REG_FLEXCAN_A_IMRL;
  REG_FLEXCAN_A_IMRL = uVar3 & 0xffffefff | 0x1000;
  uVar3 = REG_FLEXCAN_A_IMRL;
  REG_FLEXCAN_A_IMRL = uVar3 & 0xffffdfff | 0x2000;
  uVar3 = REG_FLEXCAN_A_IMRL;
  REG_FLEXCAN_A_IMRL = uVar3 & 0xffffbfff | 0x4000;
  if (tcu_unlocked) {
    uVar3 = REG_FLEXCAN_A_IMRL;
    REG_FLEXCAN_A_IMRL = uVar3 & 0xffff7fff | 0x8000;
  }
  else {
    uVar3 = REG_FLEXCAN_A_IMRL;
    REG_FLEXCAN_A_IMRL = uVar3 & 0xffff7fff;
  }
  uVar3 = REG_FLEXCAN_A_IMRL;
  REG_FLEXCAN_A_IMRL = uVar3 & 0xfffeffff | 0x10000;
  uVar3 = REG_FLEXCAN_A_IMRL;
  REG_FLEXCAN_A_IMRL = uVar3 & 0xfffbffff | 0x40000;
  uVar3 = REG_FLEXCAN_A_IMRL;
  REG_FLEXCAN_A_IMRL = uVar3 & 0xfff7ffff | 0x80000;
  uVar3 = REG_FLEXCAN_A_IMRL;
  REG_FLEXCAN_A_IMRL = uVar3 & 0xffefffff | 0x100000;
  uVar3 = REG_FLEXCAN_A_IMRL;
  REG_FLEXCAN_A_IMRL = uVar3 & 0xffdfffff | 0x200000;
  uVar3 = REG_FLEXCAN_A_IMRL;
  REG_FLEXCAN_A_IMRL = uVar3 & 0xffbfffff | 0x400000;
  uVar3 = REG_FLEXCAN_A_IMRL;
  REG_FLEXCAN_A_IMRL = uVar3 & 0xff7fffff | 0x800000;
  uVar3 = REG_FLEXCAN_A_IMRL;
  REG_FLEXCAN_A_IMRL = uVar3 & 0xfeffffff | 0x1000000;
  bVar2 = REG_INTC_PSR155;
  REG_INTC_PSR155 = bVar2 & 0xf0 | 2;
  bVar2 = REG_INTC_PSR156;
  REG_INTC_PSR156 = bVar2 & 0xf0 | 2;
  bVar2 = REG_INTC_PSR157;
  REG_INTC_PSR157 = bVar2 & 0xf0 | 2;
  bVar2 = REG_INTC_PSR158;
  REG_INTC_PSR158 = bVar2 & 0xf0 | 2;
  bVar2 = REG_INTC_PSR159;
  REG_INTC_PSR159 = bVar2 & 0xf0 | 2;
  bVar2 = REG_INTC_PSR160;
  REG_INTC_PSR160 = bVar2 & 0xf0 | 2;
  bVar2 = REG_INTC_PSR161;
  REG_INTC_PSR161 = bVar2 & 0xf0 | 2;
  bVar2 = REG_INTC_PSR162;
  REG_INTC_PSR162 = bVar2 & 0xf0 | 2;
  bVar2 = REG_INTC_PSR163;
  REG_INTC_PSR163 = bVar2 & 0xf0 | 2;
  bVar2 = REG_INTC_PSR164;
  REG_INTC_PSR164 = bVar2 & 0xf0 | 2;
  bVar2 = REG_INTC_PSR165;
  REG_INTC_PSR165 = bVar2 & 0xf0 | 2;
  bVar2 = REG_INTC_PSR166;
  REG_INTC_PSR166 = bVar2 & 0xf0 | 2;
  bVar2 = REG_INTC_PSR167;
  REG_INTC_PSR167 = bVar2 & 0xf0 | 2;
  bVar2 = REG_INTC_PSR168;
  REG_INTC_PSR168 = bVar2 & 0xf0 | 2;
  bVar2 = REG_INTC_PSR169;
  REG_INTC_PSR169 = bVar2 & 0xf0 | 2;
  bVar2 = REG_INTC_PSR170;
  REG_INTC_PSR170 = bVar2 & 0xf0 | 2;
  bVar2 = REG_INTC_PSR171;
  REG_INTC_PSR171 = bVar2 & 0xf0 | 2;
  uVar3 = REG_FLEXCAN_A_MCR;
  REG_FLEXCAN_A_MCR = uVar3 & 0xffffffc0 | 0x18;
  uVar1 = REG_SIU_PCR83;
  REG_SIU_PCR83 = uVar1 & 0xe3ff | 0x400;
  uVar1 = REG_SIU_PCR84;
  REG_SIU_PCR84 = uVar1 & 0xe3ff | 0x400;
  uVar3 = REG_FLEXCAN_A_MCR;
  REG_FLEXCAN_A_MCR = uVar3 & 0xefffffff;
  REG_FLEXCAN_A_IFRH = 0xffffffff;
  REG_FLEXCAN_A_IFRL = 0xffffffff;
  return;
}



void flexcan_a_rx_steering_85(void)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  byte i;
  byte local_10 [8];
  
  local_10[0] = 0;
  local_10[1] = 0;
  local_10[2] = 0;
  local_10[3] = 0;
  uVar3 = REG_FLEXCAN_A_IFRL;
  REG_FLEXCAN_A_IFRL = uVar3 & 0xfffffffe | 1;
  uVar3 = REG_FLEXCAN_A_MB0_CS;
  while ((uVar3 >> 0x18 & 1) != 0) {
    uVar3 = REG_FLEXCAN_A_MB0_CS;
  }
  uVar3 = REG_FLEXCAN_A_MB0_CS;
  if ((uVar3 >> 0x18 & 6) == 6) {
    uVar3 = REG_FLEXCAN_A_MB0_CS;
    REG_FLEXCAN_A_MB0_CS = uVar3 & 0xf0ffffff | 0x4000000;
    uVar3 = REG_FLEXCAN_A_TIMER;
    DAT_400016dc = (undefined2)uVar3;
  }
  else {
    uVar3 = REG_FLEXCAN_A_MB0_CS;
    if (((((uVar3 >> 0x18 & 2) == 2) && (((uint)COD_unknown._4_4_ >> 0xc & 1) != 0)) &&
        (uVar3 = REG_FLEXCAN_A_MB0_ID, (uVar3 >> 0x12 & 0x7ff) == 0x85)) &&
       (uVar3 = REG_FLEXCAN_A_MB0_CS, (uVar3 >> 0x10 & 0xf) == 5)) {
      DAT_40001454 = DAT_40001454 | 1;
      for (i = 0; i < 5; i = i + 1) {
        local_10[i] = *(byte *)((int)&REG_FLEXCAN_A_MB0_DATA0 + (uint)i);
      }
      DAT_40001718 = CONCAT11(local_10[1],local_10[0]);
      DAT_40001716 = local_10[2];
      bVar1 = DAT_40001715 | 1;
      if ((local_10._0_4_ & 1) == 0) {
        bVar1 = DAT_40001715 & 0xfe;
      }
      bVar2 = bVar1 | 2;
      if ((local_10._0_4_ & 2) == 0) {
        bVar2 = bVar1 & 0xfd;
      }
      DAT_40001715 = bVar2 | 4;
      if ((local_10._0_4_ & 4) == 0) {
        DAT_40001715 = bVar2 & 0xfb;
      }
    }
  }
  uVar3 = REG_FLEXCAN_A_MB0_CS;
  REG_FLEXCAN_A_MB0_CS = uVar3 & 0xf0ffffff;
  uVar3 = REG_FLEXCAN_A_MB0_ID;
  REG_FLEXCAN_A_MB0_ID = uVar3 & 0xe003ffff | 0x2140000;
  uVar3 = REG_FLEXCAN_A_MB0_CS;
  REG_FLEXCAN_A_MB0_CS = uVar3 & 0xf0ffffff | 0x4000000;
  return;
}



void flexcan_a_rx_ips_request_d2(void)

{
  uint uVar1;
  ushort uVar2;
  byte bVar3;
  byte local_10 [8];
  
  local_10[0] = 0;
  local_10[1] = 0;
  local_10[2] = 0;
  local_10[3] = 0;
  local_10[4] = 0;
  local_10[5] = 0;
  local_10[6] = 0;
  local_10[7] = 0;
  uVar1 = REG_FLEXCAN_A_IFRL;
  REG_FLEXCAN_A_IFRL = uVar1 & 0xfffffffd | 2;
  uVar1 = REG_FLEXCAN_A_MB1_CS;
  while ((uVar1 >> 0x18 & 1) != 0) {
    uVar1 = REG_FLEXCAN_A_MB1_CS;
  }
  uVar1 = REG_FLEXCAN_A_MB1_CS;
  if ((uVar1 >> 0x18 & 6) == 6) {
    uVar1 = REG_FLEXCAN_A_MB1_CS;
    REG_FLEXCAN_A_MB1_CS = uVar1 & 0xf0ffffff | 0x4000000;
    uVar1 = REG_FLEXCAN_A_TIMER;
    DAT_400016dc = (undefined2)uVar1;
  }
  else {
    uVar1 = REG_FLEXCAN_A_MB1_CS;
    if ((((uVar1 >> 0x18 & 2) == 2) &&
        (uVar1 = REG_FLEXCAN_A_MB1_ID, (uVar1 >> 0x12 & 0x7ff) == 0xd2)) &&
       (uVar1 = REG_FLEXCAN_A_MB1_CS, (uVar1 >> 0x10 & 0xf) == 8)) {
      uVar2 = DAT_40001450 & 0xbfff;
      DAT_40001450 = uVar2 | 0x40;
      for (bVar3 = 0; bVar3 < 8; bVar3 = bVar3 + 1) {
        local_10[bVar3] = *(byte *)((int)&REG_FLEXCAN_A_MB1_DATA0 + (uint)bVar3);
      }
      tps = local_10[0];
      engine_flag_1 = local_10[1];
      paddle_shift_flags = local_10[2];
      ips_calibration_flags = local_10[3];
      DAT_4000191a = 1;
      cruise_target_kph = local_10[4];
      cruise_status_flags = local_10[5];
      revlimit_hard_from_ecu = CONCAT11(local_10[7],local_10[6]);
      if ((revlimit_hard_from_ecu < (ushort)((ushort)CAL_revlimit_min * 30)) ||
         (7150 < revlimit_hard_from_ecu)) {
        revlimit_hard_from_ecu = 3000;
        DAT_40001450 = uVar2 | 0x4040;
      }
      if ((local_10._0_4_ & 0x1000) == 0) {
        DAT_40001ac5 = DAT_40001ac5 & 0xbf;
        DAT_40001ac6 = DAT_40001ac6 & 0xbf;
      }
      else {
        DAT_40001ac5 = DAT_40001ac5 | 0x40;
        DAT_40001ac6 = DAT_40001ac6 | 0x40;
      }
      auto_mode_active = (bool)((byte)(-((ulonglong)local_10[2] & 0x80) >> 0x18) >> 7);
    }
  }
  uVar1 = REG_FLEXCAN_A_MB1_CS;
  REG_FLEXCAN_A_MB1_CS = uVar1 & 0xf0ffffff;
  uVar1 = REG_FLEXCAN_A_MB1_ID;
  REG_FLEXCAN_A_MB1_ID = uVar1 & 0xe003ffff | 0x3480000;
  uVar1 = REG_FLEXCAN_A_MB1_CS;
  REG_FLEXCAN_A_MB1_CS = uVar1 & 0xf0ffffff | 0x4000000;
  return;
}



void flexcan_a_rx_ecu_torque_102(void)

{
  uint uVar1;
  ushort uVar2;
  uint uVar3;
  byte bVar4;
  undefined4 local_10;
  
  local_10 = 0;
  uVar3 = REG_FLEXCAN_A_IFRL;
  REG_FLEXCAN_A_IFRL = uVar3 & 0xfffffffb | 4;
  uVar3 = REG_FLEXCAN_A_MB2_CS;
  while ((uVar3 >> 0x18 & 1) != 0) {
    uVar3 = REG_FLEXCAN_A_MB2_CS;
  }
  uVar3 = REG_FLEXCAN_A_MB2_CS;
  if ((uVar3 >> 0x18 & 6) == 6) {
    uVar3 = REG_FLEXCAN_A_MB2_CS;
    REG_FLEXCAN_A_MB2_CS = uVar3 & 0xf0ffffff | 0x4000000;
    uVar3 = REG_FLEXCAN_A_TIMER;
    DAT_400016dc = (undefined2)uVar3;
  }
  else {
    uVar3 = REG_FLEXCAN_A_MB2_CS;
    if ((((uVar3 >> 0x18 & 2) == 2) &&
        (uVar3 = REG_FLEXCAN_A_MB2_ID, (uVar3 >> 0x12 & 0x7ff) == 0x102)) &&
       (uVar3 = REG_FLEXCAN_A_MB2_CS, (uVar3 >> 0x10 & 0xf) == 3)) {
      uVar2 = DAT_40001450 & 0xfeff;
      DAT_40001450 = uVar2 | 1;
      for (bVar4 = 0; bVar4 < 3; bVar4 = bVar4 + 1) {
        *(undefined1 *)((int)&local_10 + (uint)bVar4) =
             *(undefined1 *)((int)&REG_FLEXCAN_A_MB2_DATA0 + (uint)bVar4);
      }
      uVar1 = (local_10 >> 8 & 0xff) << 4;
      uVar3 = (int)(local_10._1_1_ & 0xf0) >> 4 | uVar1;
      if (uVar3 == 0x7ff) {
        DAT_40001450 = uVar2 | 0x101;
        DAT_4000172a = 0;
      }
      else {
        uVar2 = (ushort)uVar3;
        DAT_4000172a = uVar2 | 0xf000;
        if ((uVar1 & 0x800) == 0) {
          DAT_4000172a = uVar2;
        }
      }
      torque_alphaN_raw = (ushort)(((ulonglong)local_10._1_1_ & 0xf) << 8) | (ushort)local_10._0_1_;
      if ((((ulonglong)local_10._1_1_ & 0xf) << 8 | (ulonglong)local_10._0_1_) == 0xfff) {
        DAT_40001450 = DAT_40001450 | 0x100;
        torque_alphaN_raw = 0;
      }
    }
  }
  uVar3 = REG_FLEXCAN_A_MB2_CS;
  REG_FLEXCAN_A_MB2_CS = uVar3 & 0xf0ffffff;
  uVar3 = REG_FLEXCAN_A_MB2_ID;
  REG_FLEXCAN_A_MB2_ID = uVar3 & 0xe003ffff | 0x4080000;
  uVar3 = REG_FLEXCAN_A_MB2_CS;
  REG_FLEXCAN_A_MB2_CS = uVar3 & 0xf0ffffff | 0x4000000;
  return;
}



void flexcan_a_rx_isr_vec158(void)

{
  uint uVar1;
  byte bVar2;
  
  uVar1 = REG_FLEXCAN_A_IFRL;
  REG_FLEXCAN_A_IFRL = uVar1 & 0xfffffff7 | 8;
  uVar1 = REG_FLEXCAN_A_MB3_CS;
  while ((uVar1 >> 0x18 & 1) != 0) {
    uVar1 = REG_FLEXCAN_A_MB3_CS;
  }
  uVar1 = REG_FLEXCAN_A_MB3_CS;
  if ((uVar1 >> 0x18 & 6) == 6) {
    uVar1 = REG_FLEXCAN_A_MB3_CS;
    REG_FLEXCAN_A_MB3_CS = uVar1 & 0xf0ffffff | 0x4000000;
    uVar1 = REG_FLEXCAN_A_TIMER;
    DAT_400016dc = (undefined2)uVar1;
  }
  else {
    uVar1 = REG_FLEXCAN_A_MB3_CS;
    if ((((uVar1 >> 0x18 & 2) == 2) &&
        (uVar1 = REG_FLEXCAN_A_MB3_ID, (uVar1 >> 0x12 & 0x7ff) == 0x407)) &&
       (uVar1 = REG_FLEXCAN_A_MB3_CS, (uVar1 >> 0x10 & 0xf) == 8)) {
      DAT_40001455 = DAT_40001455 | 1;
      DAT_40001428 = REG_FLEXCAN_A_MB3_DATA0._0_1_;
      bVar2 = REG_FLEXCAN_A_MB3_DATA0._1_1_;
      DAT_400016de = bVar2 & 3;
      bVar2 = REG_FLEXCAN_A_MB3_DATA0._1_1_;
      DAT_400016df = (byte)(((ulonglong)bVar2 << 0x20) >> 0x22) & 3;
      bVar2 = REG_FLEXCAN_A_MB3_DATA0._1_1_;
      DAT_400016e0 = (byte)(((ulonglong)bVar2 << 0x20) >> 0x24) & 3;
      bVar2 = REG_FLEXCAN_A_MB3_DATA0._1_1_;
      DAT_400016e1 = (undefined1)(((ulonglong)bVar2 << 0x20) >> 0x26);
    }
  }
  uVar1 = REG_FLEXCAN_A_MB3_CS;
  REG_FLEXCAN_A_MB3_CS = uVar1 & 0xf0ffffff;
  uVar1 = REG_FLEXCAN_A_MB3_ID;
  REG_FLEXCAN_A_MB3_ID = uVar1 & 0xe003ffff | 0x101c0000;
  uVar1 = REG_FLEXCAN_A_MB3_CS;
  REG_FLEXCAN_A_MB3_CS = uVar1 & 0xf0ffffff | 0x4000000;
  return;
}



void flexcan_a_rx_yaw_303(void)

{
  uint uVar1;
  byte bVar3;
  int iVar2;
  byte bVar4;
  byte local_10 [8];
  
  local_10[0] = 0;
  local_10[1] = 0;
  local_10[2] = 0;
  local_10[3] = 0;
  local_10[4] = 0;
  local_10[5] = 0;
  local_10[6] = 0;
  local_10[7] = 0;
  uVar1 = REG_FLEXCAN_A_IFRL;
  REG_FLEXCAN_A_IFRL = uVar1 & 0xffffffef | 0x10;
  uVar1 = REG_FLEXCAN_A_MB4_CS;
  while ((uVar1 >> 0x18 & 1) != 0) {
    uVar1 = REG_FLEXCAN_A_MB4_CS;
  }
  uVar1 = REG_FLEXCAN_A_MB4_CS;
  if ((uVar1 >> 0x18 & 6) == 6) {
    uVar1 = REG_FLEXCAN_A_MB4_CS;
    REG_FLEXCAN_A_MB4_CS = uVar1 & 0xf0ffffff | 0x4000000;
    uVar1 = REG_FLEXCAN_A_TIMER;
    DAT_400016dc = (undefined2)uVar1;
  }
  else {
    uVar1 = REG_FLEXCAN_A_MB4_CS;
    if (((((uVar1 >> 0x18 & 2) == 2) && (((uint)COD_unknown._4_4_ >> 0xb & 1) != 0)) &&
        (uVar1 = REG_FLEXCAN_A_MB4_ID, (uVar1 >> 0x12 & 0x7ff) == 0x303)) &&
       (uVar1 = REG_FLEXCAN_A_MB4_CS, (uVar1 >> 0x10 & 0xf) == 7)) {
      bVar3 = DAT_40001453 & 0xfb;
      DAT_40001453 = bVar3 | 1;
      for (bVar4 = 0; bVar4 < 7; bVar4 = bVar4 + 1) {
        local_10[bVar4] = *(byte *)((int)&REG_FLEXCAN_A_MB4_DATA0 + (uint)bVar4);
      }
      DAT_40001714 = local_10[1];
      iVar2 = (int)(local_10[1] & 0xc) >> 2;
      if ((((longlong)(-((ulonglong)local_10[1] & 1) << 0x20) < 0) ||
          ((longlong)(-((ulonglong)local_10[1] & 2) << 0x20) < 0)) ||
         ((iVar2 == 1 || ((iVar2 == 2 || ((((int)(local_10[1] & 0x30) >> 4) + 0xffU & 0xff) < 2)))))
         ) {
        DAT_40001453 = bVar3 | 5;
      }
      iVar2 = (((int)(local_10[5] & 0xf0) >> 4 | ((uint)local_10._4_4_ >> 0x18) << 4) - 0x801) *
              0x4fa1;
      DAT_40001712 = ((short)(iVar2 / 100000) + (short)(iVar2 >> 0x1f)) -
                     (short)((longlong)iVar2 * 0x14f8b589 >> 0x3f);
      iVar2 = ((((uint)local_10._0_4_ >> 8 & 0xf) << 8 | local_10._0_4_ & 0xff) - 0x801) * 0x4fa1;
      DAT_40001710 = ((short)(iVar2 / 100000) + (short)(iVar2 >> 0x1f)) -
                     (short)((longlong)iVar2 * 0x14f8b589 >> 0x3f);
      DAT_4000170e = (((ushort)local_10[6] | (local_10[5] & 0xf) << 8) - 0x800) * 8;
    }
  }
  uVar1 = REG_FLEXCAN_A_MB4_CS;
  REG_FLEXCAN_A_MB4_CS = uVar1 & 0xf0ffffff;
  uVar1 = REG_FLEXCAN_A_MB4_ID;
  REG_FLEXCAN_A_MB4_ID = uVar1 & 0xe003ffff | 0xc0c0000;
  uVar1 = REG_FLEXCAN_A_MB4_CS;
  REG_FLEXCAN_A_MB4_CS = uVar1 & 0xf0ffffff | 0x4000000;
  return;
}



void flexcan_a_rx_ecu_tach_pedal_114(void)

{
  uint uVar1;
  ushort uVar2;
  undefined1 uVar3;
  byte bVar4;
  byte local_10 [8];
  
  local_10[0] = 0;
  local_10[1] = 0;
  local_10[2] = 0;
  local_10[3] = 0;
  local_10[4] = 0;
  local_10[5] = 0;
  local_10[6] = 0;
  local_10[7] = 0;
  uVar1 = REG_FLEXCAN_A_IFRL;
  REG_FLEXCAN_A_IFRL = uVar1 & 0xffffffdf | 0x20;
  uVar1 = REG_FLEXCAN_A_MB5_CS;
  while ((uVar1 >> 0x18 & 1) != 0) {
    uVar1 = REG_FLEXCAN_A_MB5_CS;
  }
  uVar1 = REG_FLEXCAN_A_MB5_CS;
  if ((uVar1 >> 0x18 & 6) == 6) {
    uVar1 = REG_FLEXCAN_A_MB5_CS;
    REG_FLEXCAN_A_MB5_CS = uVar1 & 0xf0ffffff | 0x4000000;
    uVar1 = REG_FLEXCAN_A_TIMER;
    DAT_400016dc = (undefined2)uVar1;
  }
  else {
    uVar1 = REG_FLEXCAN_A_MB5_CS;
    if ((((uVar1 >> 0x18 & 2) == 2) &&
        (uVar1 = REG_FLEXCAN_A_MB5_ID, (uVar1 >> 0x12 & 0x7ff) == 0x114)) &&
       (uVar1 = REG_FLEXCAN_A_MB5_CS, (uVar1 >> 0x10 & 0xf) == 6)) {
      uVar2 = DAT_40001450 & 0xfbff;
      DAT_40001450 = uVar2 | 4;
      for (bVar4 = 0; bVar4 < 6; bVar4 = bVar4 + 1) {
        local_10[bVar4] = *(byte *)((int)&REG_FLEXCAN_A_MB5_DATA0 + (uint)bVar4);
      }
      tach_rpm = CONCAT11(local_10[1],local_10[0]);
      if (CONCAT11(local_10[1],local_10[0]) == -1) {
        DAT_40001450 = uVar2 | 0x404;
        tach_rpm = 0;
      }
      if (local_10[3] == 0xff) {
        DAT_40001450 = DAT_40001450 | 0x400;
        tps_commanded = '\0';
      }
      else {
        tps_commanded = local_10[3];
      }
      driver_input_flags[1] = local_10[4];
      driver_input_flags[0] = local_10[5];
      uVar3 = DAT_40001702;
      if (((local_10._4_4_ & 0x100000) != 0) && (uVar3 = 1, (local_10._4_4_ & 0x80000) == 0)) {
        uVar3 = DAT_40001702;
      }
      DAT_40001702 = uVar3;
      if (((local_10._4_4_ & 0x10000) == 0) || ((local_10._4_4_ & 0x20000) == 0)) {
        if ((local_10._4_4_ & 0x10000) == 0) {
          DAT_4000171e = DAT_4000171e & 0xcf;
        }
        else {
          DAT_4000171e = DAT_4000171e & 0xdf | 0x10;
        }
      }
      else {
        DAT_4000171e = DAT_4000171e & 0xef | 0x20;
      }
    }
  }
  uVar1 = REG_FLEXCAN_A_MB5_CS;
  REG_FLEXCAN_A_MB5_CS = uVar1 & 0xf0ffffff;
  uVar1 = REG_FLEXCAN_A_MB5_ID;
  REG_FLEXCAN_A_MB5_ID = uVar1 & 0xe003ffff | 0x4500000;
  uVar1 = REG_FLEXCAN_A_MB5_CS;
  REG_FLEXCAN_A_MB5_CS = uVar1 & 0xf0ffffff | 0x4000000;
  return;
}



void flexcan_a_rx_isr_vec161(void)

{
  uint uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  undefined1 uVar9;
  
  uVar1 = REG_FLEXCAN_A_IFRL;
  REG_FLEXCAN_A_IFRL = uVar1 & 0xffffffbf | 0x40;
  uVar1 = REG_FLEXCAN_A_MB6_CS;
  while ((uVar1 >> 0x18 & 1) != 0) {
    uVar1 = REG_FLEXCAN_A_MB6_CS;
  }
  uVar1 = REG_FLEXCAN_A_MB6_CS;
  if ((uVar1 >> 0x18 & 6) == 6) {
    uVar1 = REG_FLEXCAN_A_MB6_CS;
    REG_FLEXCAN_A_MB6_CS = uVar1 & 0xf0ffffff | 0x4000000;
    uVar1 = REG_FLEXCAN_A_TIMER;
    DAT_400016dc = (undefined2)uVar1;
  }
  else {
    uVar1 = REG_FLEXCAN_A_MB6_CS;
    if ((uVar1 >> 0x18 & 2) == 2) {
      uVar1 = REG_FLEXCAN_A_MB6_ID;
      if ((((uVar1 >> 0x12 & 0x7ff) == 0x310) ||
          (uVar1 = REG_FLEXCAN_A_MB6_ID, (uVar1 >> 0x12 & 0x7ff) == 0x311)) ||
         (uVar1 = REG_FLEXCAN_A_MB6_ID, (uVar1 >> 0x12 & 0x7ff) == 0x312)) {
        uVar2 = REG_FLEXCAN_A_MB6_DATA0._0_1_;
        uVar3 = REG_FLEXCAN_A_MB6_DATA0._1_1_;
        uVar4 = REG_FLEXCAN_A_MB6_DATA0._2_1_;
        uVar5 = REG_FLEXCAN_A_MB6_DATA0._3_1_;
        uVar6 = REG_FLEXCAN_A_MB6_DATA1._0_1_;
        uVar7 = REG_FLEXCAN_A_MB6_DATA1._1_1_;
        uVar8 = REG_FLEXCAN_A_MB6_DATA1._2_1_;
        uVar9 = REG_FLEXCAN_A_MB6_DATA1._3_1_;
        uVar1 = REG_FLEXCAN_A_MB6_ID;
        if ((uVar1 >> 0x12 & 0x7ff) == 0x310) {
          DAT_4000174a = CONCAT11(uVar2,uVar3);
          DAT_40001748 = CONCAT11(uVar4,uVar5);
          DAT_40001746 = CONCAT11(uVar6,uVar7);
          DAT_40001744 = CONCAT11(uVar8,uVar9);
          DAT_40001732 = (undefined2)((int)((uint)DAT_4000174a * 10) >> 2);
          DAT_40001730 = (undefined2)((int)((uint)DAT_40001748 * 10) >> 2);
          DAT_4000172e = (undefined2)((int)((uint)DAT_40001746 * 10) >> 2);
          DAT_4000172c = (undefined2)((int)((uint)DAT_40001744 * 10) >> 2);
        }
        else {
          uVar1 = REG_FLEXCAN_A_MB6_ID;
          if ((uVar1 >> 0x12 & 0x7ff) == 0x311) {
            DAT_40001732 = CONCAT11(uVar2,uVar3);
            DAT_40001730 = CONCAT11(uVar4,uVar5);
            DAT_4000172e = CONCAT11(uVar6,uVar7);
            DAT_4000172c = CONCAT11(uVar8,uVar9);
            DAT_4000173c = DAT_4000172c;
            DAT_4000173e = DAT_4000172e;
            DAT_40001740 = DAT_40001730;
            DAT_40001742 = DAT_40001732;
          }
          else {
            DAT_4000173a = CONCAT11(uVar2,uVar3);
            DAT_40001738 = CONCAT11(uVar4,uVar5);
            DAT_40001736 = CONCAT11(uVar6,uVar7);
            DAT_40001734 = CONCAT11(uVar8,uVar9);
          }
        }
        uVar1 = REG_FLEXCAN_A_MB6_CS;
        REG_FLEXCAN_A_MB6_CS = uVar1 & 0xf0ffffff | 0x4000000;
      }
      else {
        uVar1 = REG_FLEXCAN_A_MB6_CS;
        REG_FLEXCAN_A_MB6_CS = uVar1 & 0xf0ffffff | 0x4000000;
        uVar1 = REG_FLEXCAN_A_TIMER;
        DAT_400016dc = (undefined2)uVar1;
      }
    }
  }
  return;
}



void FUN_00053b84(void)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_A_IFRL;
  REG_FLEXCAN_A_IFRL = uVar1 & 0xffffff7f | 0x80;
  return;
}



void FUN_00053b9c(void)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_A_IFRL;
  REG_FLEXCAN_A_IFRL = uVar1 & 0xfffffeff | 0x100;
  return;
}



void flexcan_a_rx_obd_7df(void)

{
  uint uVar1;
  byte bVar2;
  
  uVar1 = REG_FLEXCAN_A_IFRL;
  REG_FLEXCAN_A_IFRL = uVar1 & 0xfffffdff | 0x200;
  uVar1 = REG_FLEXCAN_A_MB9_CS;
  while ((uVar1 >> 0x18 & 1) != 0) {
    uVar1 = REG_FLEXCAN_A_MB9_CS;
  }
  uVar1 = REG_FLEXCAN_A_MB9_CS;
  if ((uVar1 >> 0x18 & 6) == 6) {
    uVar1 = REG_FLEXCAN_A_MB9_CS;
    REG_FLEXCAN_A_MB9_CS = uVar1 & 0xf0ffffff | 0x4000000;
    uVar1 = REG_FLEXCAN_A_TIMER;
    DAT_400016dc = (undefined2)uVar1;
  }
  else {
    uVar1 = REG_FLEXCAN_A_MB9_CS;
    if (((uVar1 >> 0x18 & 2) == 2) &&
       (uVar1 = REG_FLEXCAN_A_MB9_ID, (uVar1 >> 0x12 & 0x7ff) == 0x7df)) {
      for (bVar2 = 0; bVar2 < 8; bVar2 = bVar2 + 1) {
        obd_ii_request[bVar2] = *(byte *)((int)&REG_FLEXCAN_A_MB9_DATA0 + (uint)bVar2);
      }
      uVar1 = REG_FLEXCAN_A_MB9_CS;
      REG_FLEXCAN_A_MB9_CS = uVar1 & 0xf0ffffff | 0x4000000;
      obd_ii_processing();
    }
  }
  uVar1 = REG_FLEXCAN_A_MB9_CS;
  REG_FLEXCAN_A_MB9_CS = uVar1 & 0xf0ffffff;
  uVar1 = REG_FLEXCAN_A_MB9_ID;
  REG_FLEXCAN_A_MB9_ID = uVar1 & 0xe003ffff | 0x1f7c0000;
  uVar1 = REG_FLEXCAN_A_MB9_CS;
  REG_FLEXCAN_A_MB9_CS = uVar1 & 0xf0ffffff | 0x4000000;
  return;
}



void flexcan_a_rx_obd_7e1_tcu(void)

{
  uint uVar1;
  byte bVar2;
  
  uVar1 = REG_FLEXCAN_A_IFRL;
  REG_FLEXCAN_A_IFRL = uVar1 & 0xfffffbff | 0x400;
  uVar1 = REG_FLEXCAN_A_MB10_CS;
  while ((uVar1 >> 0x18 & 1) != 0) {
    uVar1 = REG_FLEXCAN_A_MB10_CS;
  }
  uVar1 = REG_FLEXCAN_A_MB10_CS;
  if ((uVar1 >> 0x18 & 6) == 6) {
    uVar1 = REG_FLEXCAN_A_MB10_CS;
    REG_FLEXCAN_A_MB10_CS = uVar1 & 0xf0ffffff | 0x4000000;
    uVar1 = REG_FLEXCAN_A_TIMER;
    DAT_400016dc = (undefined2)uVar1;
  }
  else {
    uVar1 = REG_FLEXCAN_A_MB10_CS;
    if (((uVar1 >> 0x18 & 2) == 2) &&
       (uVar1 = REG_FLEXCAN_A_MB10_ID, (uVar1 >> 0x12 & 0x7ff) == 0x7e1)) {
      for (bVar2 = 0; bVar2 < 8; bVar2 = bVar2 + 1) {
        obd_ii_request[bVar2] = *(byte *)((int)&REG_FLEXCAN_A_MB10_DATA0 + (uint)bVar2);
      }
      uVar1 = REG_FLEXCAN_A_MB10_CS;
      REG_FLEXCAN_A_MB10_CS = uVar1 & 0xf0ffffff | 0x4000000;
      obd_ii_processing();
    }
  }
  uVar1 = REG_FLEXCAN_A_MB10_CS;
  REG_FLEXCAN_A_MB10_CS = uVar1 & 0xf0ffffff;
  uVar1 = REG_FLEXCAN_A_MB10_ID;
  REG_FLEXCAN_A_MB10_ID = uVar1 & 0xe003ffff | 0x1f840000;
  uVar1 = REG_FLEXCAN_A_MB10_CS;
  REG_FLEXCAN_A_MB10_CS = uVar1 & 0xf0ffffff | 0x4000000;
  return;
}



void flexcan_a_rx_504(void)

{
  uint uVar1;
  byte bVar2;
  undefined4 local_10;
  undefined4 local_c;
  
  local_10 = 0;
  local_c = 0;
  uVar1 = REG_FLEXCAN_A_MB11_CS;
  if ((uVar1 >> 0x18 & 0xf) == 8) {
    uVar1 = REG_FLEXCAN_A_MB11_CS;
    REG_FLEXCAN_A_MB11_CS = uVar1 & 0xf0ffffff;
    uVar1 = REG_FLEXCAN_A_MB11_ID;
    REG_FLEXCAN_A_MB11_ID = uVar1 & 0xe003ffff | 0x14100000;
    uVar1 = REG_FLEXCAN_A_MB11_CS;
    REG_FLEXCAN_A_MB11_CS = uVar1 & 0xf0ffffff | 0x4000000;
    uVar1 = REG_FLEXCAN_A_IFRL;
    REG_FLEXCAN_A_IFRL = uVar1 & 0xfffff7ff | 0x800;
  }
  uVar1 = REG_FLEXCAN_A_MB11_CS;
  while ((uVar1 >> 0x18 & 1) != 0) {
    uVar1 = REG_FLEXCAN_A_MB11_CS;
  }
  uVar1 = REG_FLEXCAN_A_MB11_CS;
  if ((uVar1 >> 0x18 & 6) == 6) {
    uVar1 = REG_FLEXCAN_A_IFRL;
    REG_FLEXCAN_A_IFRL = uVar1 & 0xfffff7ff | 0x800;
    uVar1 = REG_FLEXCAN_A_MB11_CS;
    REG_FLEXCAN_A_MB11_CS = uVar1 & 0xf0ffffff | 0x4000000;
    uVar1 = REG_FLEXCAN_A_TIMER;
    DAT_400016dc = (undefined2)uVar1;
  }
  else {
    uVar1 = REG_FLEXCAN_A_MB11_CS;
    if ((uVar1 >> 0x18 & 2) == 2) {
      uVar1 = REG_FLEXCAN_A_IFRL;
      REG_FLEXCAN_A_IFRL = uVar1 & 0xfffff7ff | 0x800;
      uVar1 = REG_FLEXCAN_A_MB11_ID;
      if ((uVar1 >> 0x12 & 0x7ff) == 0x504) {
        for (bVar2 = 0; bVar2 < 8; bVar2 = bVar2 + 1) {
          *(undefined1 *)((int)&local_10 + (uint)bVar2) =
               *(undefined1 *)((int)&REG_FLEXCAN_A_MB11_DATA0 + (uint)bVar2);
        }
        FUN_000582fc(&local_10,0);
      }
      else {
        uVar1 = REG_FLEXCAN_A_MB11_CS;
        REG_FLEXCAN_A_MB11_CS = uVar1 & 0xf0ffffff;
        uVar1 = REG_FLEXCAN_A_MB11_ID;
        REG_FLEXCAN_A_MB11_ID = uVar1 & 0xe003ffff | 0x14100000;
      }
      uVar1 = REG_FLEXCAN_A_MB11_CS;
      REG_FLEXCAN_A_MB11_CS = uVar1 & 0xf0ffffff | 0x4000000;
    }
  }
  return;
}



void flexcan_a_rx_360(void)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_A_IFRL;
  REG_FLEXCAN_A_IFRL = uVar1 & 0xffffefff | 0x1000;
  uVar1 = REG_FLEXCAN_A_MB12_CS;
  while ((uVar1 >> 0x18 & 1) != 0) {
    uVar1 = REG_FLEXCAN_A_MB12_CS;
  }
  uVar1 = REG_FLEXCAN_A_MB12_CS;
  if ((uVar1 >> 0x18 & 6) == 6) {
    uVar1 = REG_FLEXCAN_A_MB12_CS;
    REG_FLEXCAN_A_MB12_CS = uVar1 & 0xf0ffffff | 0x4000000;
    uVar1 = REG_FLEXCAN_A_TIMER;
    DAT_400016dc = (undefined2)uVar1;
  }
  else {
    uVar1 = REG_FLEXCAN_A_MB12_CS;
    if ((uVar1 >> 0x18 & 2) == 2) {
      uVar1 = REG_FLEXCAN_A_MB12_ID;
      if ((uVar1 >> 0x12 & 0x7ff) == 0x360) {
        DAT_400016f0 = REG_FLEXCAN_A_MB12_DATA0._0_1_;
        DAT_400016f1 = REG_FLEXCAN_A_MB12_DATA0._1_1_;
        DAT_400016f2 = REG_FLEXCAN_A_MB12_DATA0._2_1_;
        DAT_400016f3 = REG_FLEXCAN_A_MB12_DATA0._3_1_;
        DAT_400016f4 = REG_FLEXCAN_A_MB12_DATA1._0_1_;
        DAT_400016f5 = REG_FLEXCAN_A_MB12_DATA1._1_1_;
        DAT_400016f6 = REG_FLEXCAN_A_MB12_DATA1._2_1_;
        DAT_400016f7 = REG_FLEXCAN_A_MB12_DATA1._3_1_;
        uVar1 = REG_FLEXCAN_A_MB12_CS;
        REG_FLEXCAN_A_MB12_CS = uVar1 & 0xf0ffffff | 0x4000000;
        uVar1 = REG_FLEXCAN_A_TIMER;
        DAT_400016dc = (undefined2)uVar1;
        FUN_00051358(&DAT_400016f0);
      }
      else {
        uVar1 = REG_FLEXCAN_A_MB12_CS;
        REG_FLEXCAN_A_MB12_CS = uVar1 & 0xf0ffffff | 0x4000000;
        uVar1 = REG_FLEXCAN_A_TIMER;
        DAT_400016dc = (undefined2)uVar1;
      }
    }
    else {
      uVar1 = REG_FLEXCAN_A_MB12_CS;
      REG_FLEXCAN_A_MB12_CS = uVar1 & 0xf0ffffff | 0x4000000;
      uVar1 = REG_FLEXCAN_A_TIMER;
      DAT_400016dc = (undefined2)uVar1;
    }
  }
  return;
}



void flexcan_a_rx_b7(void)

{
  bool bVar1;
  uint uVar2;
  short sVar3;
  byte bVar4;
  byte bVar5;
  undefined4 local_10;
  undefined4 local_c;
  
  local_10 = 0;
  local_c = 0;
  uVar2 = REG_FLEXCAN_A_IFRL;
  REG_FLEXCAN_A_IFRL = uVar2 & 0xffffdfff | 0x2000;
  uVar2 = REG_FLEXCAN_A_MB13_CS;
  while ((uVar2 >> 0x18 & 1) != 0) {
    uVar2 = REG_FLEXCAN_A_MB13_CS;
  }
  uVar2 = REG_FLEXCAN_A_MB13_CS;
  if ((uVar2 >> 0x18 & 6) == 6) {
    uVar2 = REG_FLEXCAN_A_MB13_CS;
    REG_FLEXCAN_A_MB13_CS = uVar2 & 0xf0ffffff | 0x4000000;
    uVar2 = REG_FLEXCAN_A_TIMER;
    DAT_400016dc = (undefined2)uVar2;
  }
  else {
    uVar2 = REG_FLEXCAN_A_MB13_CS;
    if ((uVar2 >> 0x18 & 2) == 2) {
      if ((((uint)COD_unknown._4_4_ >> 9 & 1) == 0) || (((uint)COD_unknown._0_4_ >> 0x16 & 7) == 0))
      {
        DAT_40001722 = 0;
        DAT_40001723 = 0;
        DAT_40001720 = DAT_40001720 & 0xfc;
        DAT_4000171c = 0x38f;
      }
      else {
        uVar2 = REG_FLEXCAN_A_MB13_ID;
        if (((uVar2 >> 0x12 & 0x7ff) == 0xb7) &&
           (((uVar2 = REG_FLEXCAN_A_MB13_CS, (uVar2 >> 0x10 & 0xf) == 7 &&
             ((DAT_400090c0 == '\x01' || (DAT_400090c0 == '\x02')))) ||
            ((uVar2 = REG_FLEXCAN_A_MB13_CS, (uVar2 >> 0x10 & 0xf) == 5 && (DAT_400090c0 == '\0'))))
           )) {
          uVar2 = REG_FLEXCAN_A_MB13_CS;
          bVar1 = (uVar2 >> 0x10 & 0xf) != 7;
          if (bVar1) {
            bVar5 = 5;
          }
          else {
            bVar5 = 7;
          }
          DAT_400016ec = !bVar1;
          DAT_40001452 = DAT_40001452 | 0x40;
          for (bVar4 = 0; bVar4 < bVar5; bVar4 = bVar4 + 1) {
            *(undefined1 *)((int)&local_10 + (uint)bVar4) =
                 *(undefined1 *)((int)&REG_FLEXCAN_A_MB13_DATA0 + (uint)bVar4);
          }
          DAT_4000142a = (local_10._1_1_ & 0xf) << 8 | (ushort)local_10._0_1_;
          if (DAT_4000142a < 0x800) {
            sVar3 = (short)DAT_4000142a >> 2;
          }
          else {
            sVar3 = ((short)(DAT_4000142a | 0xf800) >> 2) +
                    (ushort)((short)(DAT_4000142a | 0xf800) < 0 && (local_10 & 0x3000000) != 0);
          }
          DAT_40001430 = sVar3 + 400;
          uVar2 = (int)(local_10._1_1_ & 0xf0) >> 4;
          DAT_4000142c = (ushort)local_10._2_1_ << 4 | (ushort)uVar2;
          if (DAT_4000142c < 0x800) {
            sVar3 = (short)DAT_4000142c >> 2;
          }
          else {
            sVar3 = ((short)(DAT_4000142c | 0xf800) >> 2) +
                    (ushort)((short)(DAT_4000142c | 0xf800) < 0 && (uVar2 & 3) != 0);
          }
          DAT_40001432 = sVar3 + 400;
          if ((bool)DAT_400016ec) {
            DAT_4000142e = (local_c._1_1_ & 0xf) << 8 | (ushort)local_c._0_1_;
            if (DAT_4000142e < 0x800) {
              DAT_40001434 = ((short)DAT_4000142e >> 2) + 400;
            }
            else {
              DAT_40001434 = ((short)(DAT_4000142e | 0xf800) >> 2) +
                             (ushort)((short)(DAT_4000142e | 0xf800) < 0 &&
                                     (local_c & 0x3000000) != 0) + 400;
            }
          }
          else {
            DAT_4000142e = 0x7ff;
          }
          if (((local_10 & 1) == 0) || ((local_10 & 2) != 0)) {
            if (((local_10 & 2) == 0) || ((local_10 & 1) != 0)) {
              DAT_40001723 = 0;
              DAT_40001722 = 0;
              DAT_40001720 = DAT_40001720 & 0xfc;
              DAT_4000171c = 0x38f;
            }
            else {
              DAT_40001722 = 1;
              DAT_40001720 = DAT_40001720 | 1;
              DAT_4000171c = DAT_40001432;
            }
          }
          else {
            DAT_40001723 = 1;
            DAT_40001720 = DAT_40001720 | 2;
            DAT_4000171c = DAT_40001430;
          }
        }
      }
    }
  }
  uVar2 = REG_FLEXCAN_A_MB13_CS;
  REG_FLEXCAN_A_MB13_CS = uVar2 & 0xf0ffffff;
  uVar2 = REG_FLEXCAN_A_MB13_ID;
  REG_FLEXCAN_A_MB13_ID = uVar2 & 0xe003ffff | 0x2dc0000;
  uVar2 = REG_FLEXCAN_A_MB13_CS;
  REG_FLEXCAN_A_MB13_CS = uVar2 & 0xf0ffffff | 0x4000000;
  return;
}



void flexcan_a_rx_wheelspeed_status(void)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  undefined4 byte_8_;
  uint local_c;
  
  byte_8_ = 0;
  local_c = 0;
  uVar1 = REG_FLEXCAN_A_IFRL;
  REG_FLEXCAN_A_IFRL = uVar1 & 0xffffbfff | 0x4000;
  uVar1 = REG_FLEXCAN_A_MB14_CS;
  while ((uVar1 >> 0x18 & 1) != 0) {
    uVar1 = REG_FLEXCAN_A_MB14_CS;
  }
  uVar1 = REG_FLEXCAN_A_MB14_CS;
  if ((uVar1 >> 0x18 & 6) == 6) {
    uVar1 = REG_FLEXCAN_A_MB14_CS;
    REG_FLEXCAN_A_MB14_CS = uVar1 & 0xf0ffffff | 0x4000000;
    uVar1 = REG_FLEXCAN_A_TIMER;
    DAT_400016dc = (undefined2)uVar1;
  }
  else {
    uVar1 = REG_FLEXCAN_A_MB14_CS;
    if (((uVar1 >> 0x18 & 2) == 2) && (((uint)COD_unknown._4_4_ >> 9 & 1) != 0)) {
      uVar1 = REG_FLEXCAN_A_MB14_ID;
      if (((uVar1 >> 0x12 & 0x7ff) == 0xa2) &&
         (uVar1 = REG_FLEXCAN_A_MB14_CS, (uVar1 >> 0x10 & 0xf) == 7)) {
        DAT_40001452 = DAT_40001452 | 1;
        for (bVar2 = 0; bVar2 < 7; bVar2 = bVar2 + 1) {
          *(undefined1 *)((int)&byte_8_ + (uint)bVar2) =
               *(undefined1 *)((int)&REG_FLEXCAN_A_MB14_DATA0 + (uint)bVar2);
        }
        uVar1 = (byte_8_._1_1_ & 0x3f) << 8 | byte_8_ >> 0x18;
        if (uVar1 < 0x1681) {
          DAT_400016e4 = (undefined2)((int)(uVar1 * 0x32) >> 3);
        }
        else {
          DAT_400016e4 = 0x3fff;
        }
        uVar1 = (int)(byte_8_._1_1_ & 0xc0) >> 6 |
                (byte_8_ & 0xf) << 10 | (byte_8_ >> 8 & 0xff) << 2;
        if (uVar1 < 0x1681) {
          DAT_400016e6 = (undefined2)((int)(uVar1 * 0x32) >> 3);
        }
        else {
          DAT_400016e6 = 0x3fff;
        }
        uVar1 = (int)(byte_8_ & 0xf0) >> 4 | (local_c >> 0x10 & 3) << 0xc | (local_c >> 0x18) << 4;
        if (uVar1 < 0x1681) {
          DAT_400016e2 = (undefined2)((int)(uVar1 * 0x32) >> 3);
          DAT_40001978 = DAT_40001978 & 0xfb;
        }
        else {
          DAT_400016e2 = 0x3fff;
          DAT_40001978 = DAT_40001978 | 4;
        }
      }
      else {
        uVar1 = REG_FLEXCAN_A_MB14_ID;
        if (((uVar1 >> 0x12 & 0x7ff) == 0xa4) &&
           (uVar1 = REG_FLEXCAN_A_MB14_CS, (uVar1 >> 0x10 & 0xf) == 8)) {
          DAT_40001452 = DAT_40001452 | 4;
          for (bVar2 = 0; bVar2 < 8; bVar2 = bVar2 + 1) {
            *(undefined1 *)((int)&byte_8_ + (uint)bVar2) =
                 *(undefined1 *)((int)&REG_FLEXCAN_A_MB14_DATA0 + (uint)bVar2);
          }
          uVar1 = (byte_8_._1_1_ & 0x3f) << 8 | byte_8_ >> 0x18;
          if (uVar1 < 0x1681) {
            DAT_400016e8 = (undefined2)((int)(uVar1 * 0x32) >> 3);
          }
          else {
            DAT_400016e8 = 0x3fff;
          }
          uVar1 = (int)(byte_8_._1_1_ & 0xc0) >> 6 |
                  (byte_8_ & 0xf) << 10 | (byte_8_ >> 8 & 0xff) << 2;
          if (uVar1 < 0x1681) {
            DAT_400016ea = (undefined2)((int)(uVar1 * 0x32) >> 3);
          }
          else {
            DAT_400016ea = 0x3fff;
          }
          if (((local_c & 0x1000000) == 0) || ((local_c & 0x2000000) == 0)) {
            if ((local_c & 0x1000000) == 0) {
              DAT_4000171e = DAT_4000171e & 0xfc;
            }
            else {
              DAT_4000171e = DAT_4000171e & 0xfd | 1;
            }
          }
          else {
            DAT_4000171e = DAT_4000171e & 0xfe | 2;
          }
        }
        else {
          uVar1 = REG_FLEXCAN_A_MB14_ID;
          if (((uVar1 >> 0x12 & 0x7ff) == 0xa8) &&
             (((uVar1 = REG_FLEXCAN_A_MB14_CS, (uVar1 >> 0x10 & 0xf) == 3 &&
               ((DAT_400090c0 == '\x01' || (DAT_400090c0 == '\x02')))) ||
              ((uVar1 = REG_FLEXCAN_A_MB14_CS, (uVar1 >> 0x10 & 0xf) == 2 && (DAT_400090c0 == '\0'))
              )))) {
            DAT_40001452 = DAT_40001452 | 0x10;
            if ((DAT_400090c0 == '\x01') || (DAT_400090c0 == '\x02')) {
              bVar2 = 3;
            }
            else {
              bVar2 = 2;
            }
            for (bVar3 = 0; bVar3 < bVar2; bVar3 = bVar3 + 1) {
              *(undefined1 *)((int)&byte_8_ + (uint)bVar3) =
                   *(undefined1 *)((int)&REG_FLEXCAN_A_MB14_DATA0 + (uint)bVar3);
            }
            if ((((uint)COD_unknown._0_4_ >> 0x16 & 7) == 3) && ((byte_8_ & 0x40000000) != 0)) {
              DAT_40001720 = DAT_40001720 | 4;
              DAT_40001721 = 1;
            }
            else {
              DAT_40001720 = DAT_40001720 & 0xfb;
              DAT_40001721 = 0;
            }
            if ((byte_8_ & 0x100000) == 0) {
              DAT_40001ac5 = DAT_40001ac5 & 0xfe;
              DAT_40001ac6 = DAT_40001ac6 & 0xfe;
            }
            else {
              DAT_40001ac5 = DAT_40001ac5 | 1;
              DAT_40001ac6 = DAT_40001ac6 | 1;
            }
            DAT_4000171f = byte_8_._1_1_ & 3;
            bVar2 = DAT_40001720 & 0xf7;
            DAT_40001720 = DAT_40001720 | 8;
            if ((byte_8_ & 0x10000000) == 0) {
              DAT_40001720 = bVar2;
            }
          }
        }
      }
    }
  }
  uVar1 = REG_FLEXCAN_A_MB14_CS;
  REG_FLEXCAN_A_MB14_CS = uVar1 & 0xf0ffffff;
  uVar1 = REG_FLEXCAN_A_MB14_ID;
  REG_FLEXCAN_A_MB14_ID = uVar1 & 0xe003ffff | 0x2800000;
  uVar1 = REG_FLEXCAN_A_MB14_CS;
  REG_FLEXCAN_A_MB14_CS = uVar1 & 0xf0ffffff | 0x4000000;
  return;
}



void FUN_00054c90(void)

{
  undefined1 uVar1;
  byte bVar2;
  undefined2 uVar3;
  uint uVar4;
  short sVar5;
  ushort uVar6;
  
  uVar4 = REG_FLEXCAN_A_MB15_CS;
  while ((uVar4 >> 0x18 & 1) != 0) {
    uVar4 = REG_FLEXCAN_A_MB15_CS;
  }
  uVar4 = REG_FLEXCAN_A_MB15_CS;
  if ((uVar4 >> 0x18 & 6) == 6) {
    uVar4 = REG_FLEXCAN_A_MB15_CS;
    REG_FLEXCAN_A_MB15_CS = uVar4 & 0xf0ffffff | 0x4000000;
    uVar4 = REG_FLEXCAN_A_TIMER;
    DAT_400016dc = (undefined2)uVar4;
    goto LAB_00055908;
  }
  uVar4 = REG_FLEXCAN_A_MB15_CS;
  if (((uVar4 >> 0x18 & 2) != 2) || (!tcu_unlocked)) goto LAB_00055908;
  DAT_400016fc = &REG_FLEXCAN_A_MB15_DATA0;
  uVar4 = REG_FLEXCAN_A_MB15_ID;
  if ((uVar4 >> 0x12 & 0x7ff) == 0x60) {
    uVar4 = REG_FLEXCAN_A_MB15_CS;
    if (((uVar4 >> 0x10 & 0xf) == 4) &&
       (((uVar4 = REG_FLEXCAN_A_MB15_DATA0, 0x3fffffff < uVar4 &&
         (uVar4 = REG_FLEXCAN_A_MB15_DATA0, uVar4 < 0x4000fffd)) ||
        (uVar4 = REG_FLEXCAN_A_MB15_DATA0, uVar4 < 0xffffd)))) {
      DAT_400016d0 = (uint *)REG_FLEXCAN_A_MB15_DATA0;
      uVar4 = REG_FLEXCAN_A_MB15_CS;
      REG_FLEXCAN_A_MB15_CS = uVar4 & 0xf0ffffff | 0x4000000;
      uVar4 = REG_FLEXCAN_A_TIMER;
      DAT_400016dc = (undefined2)uVar4;
      DAT_400016f8 = &REG_FLEXCAN_A_MB16_DATA0;
      uVar4 = REG_FLEXCAN_A_MB16_CS;
      REG_FLEXCAN_A_MB16_CS = uVar4 & 0xf0ffffff | 0x8000000;
      uVar4 = REG_FLEXCAN_A_MB16_ID;
      REG_FLEXCAN_A_MB16_ID = uVar4 & 0xe003ffff | 0x1ec00000;
      REG_FLEXCAN_A_MB16_DATA0 = *DAT_400016d0;
      uVar4 = REG_FLEXCAN_A_MB16_CS;
      REG_FLEXCAN_A_MB16_CS = uVar4 & 0xfff0ffff | 0x40000;
      uVar4 = REG_FLEXCAN_A_MB16_CS;
      REG_FLEXCAN_A_MB16_CS = uVar4 & 0xf0ffffff | 0xc000000;
    }
    else {
      uVar4 = REG_FLEXCAN_A_MB15_CS;
      REG_FLEXCAN_A_MB15_CS = uVar4 & 0xf0ffffff | 0x4000000;
      uVar4 = REG_FLEXCAN_A_TIMER;
      DAT_400016dc = (undefined2)uVar4;
    }
    goto LAB_00055908;
  }
  uVar4 = REG_FLEXCAN_A_MB15_ID;
  if ((uVar4 >> 0x12 & 0x7ff) == 0x61) {
    uVar4 = REG_FLEXCAN_A_MB15_CS;
    if (((uVar4 >> 0x10 & 0xf) == 4) &&
       (((uVar4 = REG_FLEXCAN_A_MB15_DATA0, 0x3fffffff < uVar4 &&
         (uVar4 = REG_FLEXCAN_A_MB15_DATA0, uVar4 < 0x4000ffff)) ||
        (uVar4 = REG_FLEXCAN_A_MB15_DATA0, uVar4 < 0xfffff)))) {
      DAT_400016d0 = (uint *)REG_FLEXCAN_A_MB15_DATA0;
      uVar4 = REG_FLEXCAN_A_MB15_CS;
      REG_FLEXCAN_A_MB15_CS = uVar4 & 0xf0ffffff | 0x4000000;
      uVar4 = REG_FLEXCAN_A_TIMER;
      DAT_400016dc = (undefined2)uVar4;
      DAT_400016f8 = &REG_FLEXCAN_A_MB16_DATA0;
      uVar4 = REG_FLEXCAN_A_MB16_CS;
      REG_FLEXCAN_A_MB16_CS = uVar4 & 0xf0ffffff | 0x8000000;
      uVar4 = REG_FLEXCAN_A_MB16_ID;
      REG_FLEXCAN_A_MB16_ID = uVar4 & 0xe003ffff | 0x1ec00000;
      REG_FLEXCAN_A_MB16_DATA0._0_2_ = *(undefined2 *)DAT_400016d0;
      uVar4 = REG_FLEXCAN_A_MB16_CS;
      REG_FLEXCAN_A_MB16_CS = uVar4 & 0xfff0ffff | 0x20000;
      uVar4 = REG_FLEXCAN_A_MB16_CS;
      REG_FLEXCAN_A_MB16_CS = uVar4 & 0xf0ffffff | 0xc000000;
    }
    else {
      uVar4 = REG_FLEXCAN_A_MB15_CS;
      REG_FLEXCAN_A_MB15_CS = uVar4 & 0xf0ffffff | 0x4000000;
      uVar4 = REG_FLEXCAN_A_TIMER;
      DAT_400016dc = (undefined2)uVar4;
    }
    goto LAB_00055908;
  }
  uVar4 = REG_FLEXCAN_A_MB15_ID;
  if ((uVar4 >> 0x12 & 0x7ff) == 0x62) {
    uVar4 = REG_FLEXCAN_A_MB15_CS;
    if (((uVar4 >> 0x10 & 0xf) == 4) &&
       (((uVar4 = REG_FLEXCAN_A_MB15_DATA0, 0x3fffffff < uVar4 &&
         (uVar4 = REG_FLEXCAN_A_MB15_DATA0, uVar4 < 0x40010000)) ||
        (uVar4 = REG_FLEXCAN_A_MB15_DATA0, uVar4 < 0x100000)))) {
      DAT_400016d0 = (uint *)REG_FLEXCAN_A_MB15_DATA0;
      uVar4 = REG_FLEXCAN_A_MB15_CS;
      REG_FLEXCAN_A_MB15_CS = uVar4 & 0xf0ffffff | 0x4000000;
      uVar4 = REG_FLEXCAN_A_TIMER;
      DAT_400016dc = (undefined2)uVar4;
      DAT_400016f8 = &REG_FLEXCAN_A_MB16_DATA0;
      uVar4 = REG_FLEXCAN_A_MB16_CS;
      REG_FLEXCAN_A_MB16_CS = uVar4 & 0xf0ffffff | 0x8000000;
      uVar4 = REG_FLEXCAN_A_MB16_ID;
      REG_FLEXCAN_A_MB16_ID = uVar4 & 0xe003ffff | 0x1ec00000;
      REG_FLEXCAN_A_MB16_DATA0._0_1_ = *(undefined1 *)DAT_400016d0;
      uVar4 = REG_FLEXCAN_A_MB16_CS;
      REG_FLEXCAN_A_MB16_CS = uVar4 & 0xfff0ffff | 0x10000;
      uVar4 = REG_FLEXCAN_A_MB16_CS;
      REG_FLEXCAN_A_MB16_CS = uVar4 & 0xf0ffffff | 0xc000000;
    }
    else {
      uVar4 = REG_FLEXCAN_A_MB15_CS;
      REG_FLEXCAN_A_MB15_CS = uVar4 & 0xf0ffffff | 0x4000000;
      uVar4 = REG_FLEXCAN_A_TIMER;
      DAT_400016dc = (undefined2)uVar4;
    }
    goto LAB_00055908;
  }
  uVar4 = REG_FLEXCAN_A_MB15_ID;
  if ((uVar4 >> 0x12 & 0x7ff) != 99) {
    uVar4 = REG_FLEXCAN_A_MB15_ID;
    if ((uVar4 >> 0x12 & 0x7ff) == 100) {
      uVar4 = REG_FLEXCAN_A_MB15_CS;
      if ((((uVar4 >> 0x10 & 0xf) == 8) && (uVar4 = REG_FLEXCAN_A_MB15_DATA0, 0x3fffffff < uVar4))
         && (uVar4 = REG_FLEXCAN_A_MB15_DATA0, uVar4 < 0x4000fffd)) {
        DAT_400016fc = &REG_FLEXCAN_A_MB15_DATA1;
        DAT_400016d4 = (uint *)REG_FLEXCAN_A_MB15_DATA0;
        uVar4 = REG_FLEXCAN_A_MB15_CS;
        REG_FLEXCAN_A_MB15_CS = uVar4 & 0xf0ffffff | 0x4000000;
        uVar4 = REG_FLEXCAN_A_TIMER;
        DAT_400016dc = (undefined2)uVar4;
        uVar4 = REG_FLEXCAN_A_MB15_DATA1;
        *DAT_400016d4 = uVar4;
      }
      else {
        uVar4 = REG_FLEXCAN_A_MB15_CS;
        REG_FLEXCAN_A_MB15_CS = uVar4 & 0xf0ffffff | 0x4000000;
        uVar4 = REG_FLEXCAN_A_TIMER;
        DAT_400016dc = (undefined2)uVar4;
      }
    }
    else {
      uVar4 = REG_FLEXCAN_A_MB15_ID;
      if ((uVar4 >> 0x12 & 0x7ff) == 0x65) {
        uVar4 = REG_FLEXCAN_A_MB15_CS;
        if ((((uVar4 >> 0x10 & 0xf) == 6) && (uVar4 = REG_FLEXCAN_A_MB15_DATA0, 0x3fffffff < uVar4))
           && (uVar4 = REG_FLEXCAN_A_MB15_DATA0, uVar4 < 0x4000ffff)) {
          DAT_400016fc = &REG_FLEXCAN_A_MB15_DATA1;
          DAT_400016d4 = (uint *)REG_FLEXCAN_A_MB15_DATA0;
          uVar4 = REG_FLEXCAN_A_MB15_CS;
          REG_FLEXCAN_A_MB15_CS = uVar4 & 0xf0ffffff | 0x4000000;
          uVar4 = REG_FLEXCAN_A_TIMER;
          DAT_400016dc = (undefined2)uVar4;
          uVar3 = REG_FLEXCAN_A_MB15_DATA1._0_2_;
          *(undefined2 *)DAT_400016d4 = uVar3;
        }
        else {
          uVar4 = REG_FLEXCAN_A_MB15_CS;
          REG_FLEXCAN_A_MB15_CS = uVar4 & 0xf0ffffff | 0x4000000;
          uVar4 = REG_FLEXCAN_A_TIMER;
          DAT_400016dc = (undefined2)uVar4;
        }
      }
      else {
        uVar4 = REG_FLEXCAN_A_MB15_ID;
        if ((uVar4 >> 0x12 & 0x7ff) == 0x66) {
          uVar4 = REG_FLEXCAN_A_MB15_CS;
          if ((((uVar4 >> 0x10 & 0xf) == 5) &&
              (uVar4 = REG_FLEXCAN_A_MB15_DATA0, 0x3fffffff < uVar4)) &&
             (uVar4 = REG_FLEXCAN_A_MB15_DATA0, uVar4 < 0x40010000)) {
            DAT_400016fc = &REG_FLEXCAN_A_MB15_DATA1;
            DAT_400016d4 = (uint *)REG_FLEXCAN_A_MB15_DATA0;
            uVar4 = REG_FLEXCAN_A_MB15_CS;
            REG_FLEXCAN_A_MB15_CS = uVar4 & 0xf0ffffff | 0x4000000;
            uVar4 = REG_FLEXCAN_A_TIMER;
            DAT_400016dc = (undefined2)uVar4;
            uVar1 = REG_FLEXCAN_A_MB15_DATA1._0_1_;
            *(undefined1 *)DAT_400016d4 = uVar1;
          }
          else {
            uVar4 = REG_FLEXCAN_A_MB15_CS;
            REG_FLEXCAN_A_MB15_CS = uVar4 & 0xf0ffffff | 0x4000000;
            uVar4 = REG_FLEXCAN_A_TIMER;
            DAT_400016dc = (undefined2)uVar4;
          }
        }
        else {
          uVar4 = REG_FLEXCAN_A_MB15_ID;
          if ((uVar4 >> 0x12 & 0x7ff) == 0x67) {
            if (DAT_400016d8 == 0) {
              uVar4 = REG_FLEXCAN_A_MB15_CS;
              if (((uVar4 >> 0x10 & 0xf) == 5) &&
                 (uVar4 = REG_FLEXCAN_A_MB15_DATA0, 0x3fffffff < uVar4)) {
                uVar4 = REG_FLEXCAN_A_MB15_DATA0;
                bVar2 = REG_FLEXCAN_A_MB15_DATA1._0_1_;
                if (uVar4 <= 0x40010000 - bVar2) {
                  DAT_400016fc = &REG_FLEXCAN_A_MB15_DATA1;
                  DAT_400016d4 = (uint *)REG_FLEXCAN_A_MB15_DATA0;
                  bVar2 = REG_FLEXCAN_A_MB15_DATA1._0_1_;
                  DAT_400016d8 = (ushort)bVar2;
                  uVar4 = REG_FLEXCAN_A_MB15_CS;
                  REG_FLEXCAN_A_MB15_CS = uVar4 & 0xf0ffffff | 0x4000000;
                  uVar4 = REG_FLEXCAN_A_TIMER;
                  DAT_400016dc = (undefined2)uVar4;
                  goto LAB_00055908;
                }
              }
              uVar4 = REG_FLEXCAN_A_MB15_CS;
              REG_FLEXCAN_A_MB15_CS = uVar4 & 0xf0ffffff | 0x4000000;
              uVar4 = REG_FLEXCAN_A_TIMER;
              DAT_400016dc = (undefined2)uVar4;
            }
            else {
              uVar4 = REG_FLEXCAN_A_MB15_CS;
              for (uVar4 = uVar4 >> 0x10 & 0xf; (uVar4 & 0xffff) != 0; uVar4 = uVar4 - 1) {
                uVar1 = *(undefined1 *)DAT_400016fc;
                DAT_400016fc = (uint *)((int)DAT_400016fc + 1);
                *(undefined1 *)DAT_400016d4 = uVar1;
                DAT_400016d4 = (uint *)((int)DAT_400016d4 + 1);
                DAT_400016d8 = DAT_400016d8 - 1;
              }
              uVar4 = REG_FLEXCAN_A_MB15_CS;
              REG_FLEXCAN_A_MB15_CS = uVar4 & 0xf0ffffff | 0x4000000;
              uVar4 = REG_FLEXCAN_A_TIMER;
              DAT_400016dc = (undefined2)uVar4;
            }
          }
          else {
            uVar4 = REG_FLEXCAN_A_MB15_CS;
            REG_FLEXCAN_A_MB15_CS = uVar4 & 0xf0ffffff | 0x4000000;
            uVar4 = REG_FLEXCAN_A_TIMER;
            DAT_400016dc = (undefined2)uVar4;
          }
        }
      }
    }
    goto LAB_00055908;
  }
  uVar4 = REG_FLEXCAN_A_MB15_CS;
  if ((uVar4 >> 0x10 & 0xf) == 5) {
    uVar4 = REG_FLEXCAN_A_MB15_DATA0;
    if (uVar4 < 0x40000000) {
LAB_0005512c:
      uVar4 = REG_FLEXCAN_A_MB15_DATA0;
      bVar2 = REG_FLEXCAN_A_MB15_DATA1._0_1_;
      if (0x100000 - bVar2 < uVar4) goto LAB_000552b8;
    }
    else {
      uVar4 = REG_FLEXCAN_A_MB15_DATA0;
      bVar2 = REG_FLEXCAN_A_MB15_DATA1._0_1_;
      if (0x40010000 - bVar2 < uVar4) goto LAB_0005512c;
    }
    DAT_400016d8 = 0;
    DAT_400016fc = &REG_FLEXCAN_A_MB15_DATA1;
    DAT_400016d0 = (uint *)REG_FLEXCAN_A_MB15_DATA0;
    bVar2 = REG_FLEXCAN_A_MB15_DATA1._0_1_;
    DAT_400016da = (ushort)bVar2;
    uVar4 = REG_FLEXCAN_A_MB15_CS;
    REG_FLEXCAN_A_MB15_CS = uVar4 & 0xf0ffffff | 0x4000000;
    uVar4 = REG_FLEXCAN_A_TIMER;
    DAT_400016dc = (undefined2)uVar4;
    DAT_400016f8 = &REG_FLEXCAN_A_MB16_DATA0;
    uVar4 = REG_FLEXCAN_A_MB16_CS;
    REG_FLEXCAN_A_MB16_CS = uVar4 & 0xf0ffffff | 0x8000000;
    uVar4 = REG_FLEXCAN_A_MB16_ID;
    REG_FLEXCAN_A_MB16_ID = uVar4 & 0xe003ffff | 0x1ec00000;
    uVar6 = DAT_400016da;
    if (DAT_400016da < 9) {
      for (; uVar6 != 0; uVar6 = uVar6 - 1) {
        uVar1 = *(undefined1 *)DAT_400016d0;
        DAT_400016d0 = (uint *)((int)DAT_400016d0 + 1);
        *(undefined1 *)DAT_400016f8 = uVar1;
        DAT_400016f8 = (uint *)((int)DAT_400016f8 + 1);
      }
      uVar4 = REG_FLEXCAN_A_MB16_CS;
      REG_FLEXCAN_A_MB16_CS = (DAT_400016da & 0xf) << 0x10 | uVar4 & 0xfff0ffff;
      uVar4 = REG_FLEXCAN_A_MB16_CS;
      REG_FLEXCAN_A_MB16_CS = uVar4 & 0xf0ffffff | 0xc000000;
      DAT_400016da = 0;
    }
    else {
      for (sVar5 = 8; sVar5 != 0; sVar5 = sVar5 + -1) {
        uVar1 = *(undefined1 *)DAT_400016d0;
        DAT_400016d0 = (uint *)((int)DAT_400016d0 + 1);
        *(undefined1 *)DAT_400016f8 = uVar1;
        DAT_400016f8 = (uint *)((int)DAT_400016f8 + 1);
      }
      uVar4 = REG_FLEXCAN_A_MB16_CS;
      REG_FLEXCAN_A_MB16_CS = uVar4 & 0xfff0ffff | 0x80000;
      uVar4 = REG_FLEXCAN_A_MB16_CS;
      REG_FLEXCAN_A_MB16_CS = uVar4 & 0xf0ffffff | 0xc000000;
      DAT_400016da = DAT_400016da - 8;
    }
    goto LAB_00055908;
  }
LAB_000552b8:
  uVar4 = REG_FLEXCAN_A_MB15_CS;
  if ((uVar4 >> 0x10 & 0xf) == 6) {
    uVar4 = REG_FLEXCAN_A_MB15_DATA0;
    if (uVar4 < 0x40000000) {
LAB_000552fc:
      uVar4 = REG_FLEXCAN_A_MB15_DATA0;
      uVar6 = REG_FLEXCAN_A_MB16_CS._0_2_;
      if (0x100000 - uVar6 < uVar4) goto LAB_00055488;
    }
    else {
      uVar4 = REG_FLEXCAN_A_MB15_DATA0;
      uVar6 = REG_FLEXCAN_A_MB16_CS._0_2_;
      if (0x40010000 - uVar6 < uVar4) goto LAB_000552fc;
    }
    DAT_400016d8 = 0;
    DAT_400016fc = &REG_FLEXCAN_A_MB15_DATA1;
    DAT_400016d0 = (uint *)REG_FLEXCAN_A_MB15_DATA0;
    DAT_400016da = REG_FLEXCAN_A_MB15_DATA1._0_2_;
    uVar4 = REG_FLEXCAN_A_MB15_CS;
    REG_FLEXCAN_A_MB15_CS = uVar4 & 0xf0ffffff | 0x4000000;
    uVar4 = REG_FLEXCAN_A_TIMER;
    DAT_400016dc = (undefined2)uVar4;
    DAT_400016f8 = &REG_FLEXCAN_A_MB16_DATA0;
    uVar4 = REG_FLEXCAN_A_MB16_CS;
    REG_FLEXCAN_A_MB16_CS = uVar4 & 0xf0ffffff | 0x8000000;
    uVar4 = REG_FLEXCAN_A_MB16_ID;
    REG_FLEXCAN_A_MB16_ID = uVar4 & 0xe003ffff | 0x1ec00000;
    uVar6 = DAT_400016da;
    if (DAT_400016da < 9) {
      for (; uVar6 != 0; uVar6 = uVar6 - 1) {
        uVar1 = *(undefined1 *)DAT_400016d0;
        DAT_400016d0 = (uint *)((int)DAT_400016d0 + 1);
        *(undefined1 *)DAT_400016f8 = uVar1;
        DAT_400016f8 = (uint *)((int)DAT_400016f8 + 1);
      }
      uVar4 = REG_FLEXCAN_A_MB16_CS;
      REG_FLEXCAN_A_MB16_CS = (DAT_400016da & 0xf) << 0x10 | uVar4 & 0xfff0ffff;
      uVar4 = REG_FLEXCAN_A_MB16_CS;
      REG_FLEXCAN_A_MB16_CS = uVar4 & 0xf0ffffff | 0xc000000;
      DAT_400016da = 0;
    }
    else {
      for (sVar5 = 8; sVar5 != 0; sVar5 = sVar5 + -1) {
        uVar1 = *(undefined1 *)DAT_400016d0;
        DAT_400016d0 = (uint *)((int)DAT_400016d0 + 1);
        *(undefined1 *)DAT_400016f8 = uVar1;
        DAT_400016f8 = (uint *)((int)DAT_400016f8 + 1);
      }
      uVar4 = REG_FLEXCAN_A_MB16_CS;
      REG_FLEXCAN_A_MB16_CS = uVar4 & 0xfff0ffff | 0x80000;
      uVar4 = REG_FLEXCAN_A_MB16_CS;
      REG_FLEXCAN_A_MB16_CS = uVar4 & 0xf0ffffff | 0xc000000;
      DAT_400016da = DAT_400016da - 8;
    }
  }
  else {
LAB_00055488:
    uVar4 = REG_FLEXCAN_A_MB15_CS;
    if ((uVar4 >> 0x10 & 0xf) == 4) {
      DAT_400016d0 = (uint *)REG_FLEXCAN_A_MB15_DATA0;
      uVar4 = REG_FLEXCAN_A_MB15_CS;
      REG_FLEXCAN_A_MB15_CS = uVar4 & 0xf0ffffff | 0x4000000;
      uVar4 = REG_FLEXCAN_A_TIMER;
      DAT_400016dc = (undefined2)uVar4;
      DAT_400016f8 = &REG_FLEXCAN_A_MB16_DATA0;
      uVar4 = REG_FLEXCAN_A_MB16_CS;
      REG_FLEXCAN_A_MB16_CS = uVar4 & 0xf0ffffff | 0x8000000;
      uVar4 = REG_FLEXCAN_A_MB16_ID;
      REG_FLEXCAN_A_MB16_ID = uVar4 & 0xe003ffff | 0x1ec00000;
      REG_FLEXCAN_A_MB16_DATA0 = 0x8ac7c;
      uVar4 = REG_FLEXCAN_A_MB16_CS;
      REG_FLEXCAN_A_MB16_CS = uVar4 & 0xfff0ffff | 0x40000;
      uVar4 = REG_FLEXCAN_A_MB16_CS;
      REG_FLEXCAN_A_MB16_CS = uVar4 & 0xf0ffffff | 0xc000000;
    }
    else {
      uVar4 = REG_FLEXCAN_A_MB15_CS;
      REG_FLEXCAN_A_MB15_CS = uVar4 & 0xf0ffffff | 0x4000000;
      uVar4 = REG_FLEXCAN_A_TIMER;
      DAT_400016dc = (undefined2)uVar4;
    }
  }
LAB_00055908:
  uVar4 = REG_FLEXCAN_A_IFRL;
  REG_FLEXCAN_A_IFRL = uVar4 & 0xffff7fff | 0x8000;
  return;
}



void flexcan_a_interrupt(void)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_A_IFRL;
  if ((uVar1 >> 0x10 & 1) == 1) {
    flexcan_a_tx_7b0();
  }
  uVar1 = REG_FLEXCAN_A_IFRL;
  if ((uVar1 >> 0x11 & 1) == 1) {
    FUN_00055b54();
  }
  uVar1 = REG_FLEXCAN_A_IFRL;
  if ((uVar1 >> 0x12 & 1) == 1) {
    FUN_00055b80();
  }
  uVar1 = REG_FLEXCAN_A_IFRL;
  if ((uVar1 >> 0x13 & 1) == 1) {
    FUN_00055bac();
  }
  uVar1 = REG_FLEXCAN_A_IFRL;
  if ((uVar1 >> 0x14 & 1) == 1) {
    FUN_00055bd8();
  }
  uVar1 = REG_FLEXCAN_A_IFRL;
  if ((uVar1 >> 0x15 & 1) == 1) {
    FUN_00055c04();
  }
  uVar1 = REG_FLEXCAN_A_IFRL;
  if ((uVar1 >> 0x16 & 1) == 1) {
    FUN_00055c30();
  }
  uVar1 = REG_FLEXCAN_A_IFRL;
  if ((uVar1 >> 0x17 & 1) == 1) {
    FUN_00055c5c();
  }
  uVar1 = REG_FLEXCAN_A_IFRL;
  if ((uVar1 >> 0x18 & 1) == 1) {
    FUN_00055c90();
  }
  return;
}



void flexcan_a_tx_7b0(void)

{
  undefined1 uVar1;
  uint uVar2;
  short sVar3;
  ushort uVar4;
  
  uVar2 = REG_FLEXCAN_A_IFRL;
  REG_FLEXCAN_A_IFRL = uVar2 & 0xfffeffff | 0x10000;
  if (DAT_400016da != 0) {
    DAT_400016f8 = &REG_FLEXCAN_A_MB16_DATA0;
    uVar2 = REG_FLEXCAN_A_MB16_CS;
    REG_FLEXCAN_A_MB16_CS = uVar2 & 0xf0ffffff | 0x8000000;
    uVar2 = REG_FLEXCAN_A_MB16_ID;
    REG_FLEXCAN_A_MB16_ID = uVar2 & 0xe003ffff | 0x1ec00000;
    uVar4 = DAT_400016da;
    if (DAT_400016da < 9) {
      for (; uVar4 != 0; uVar4 = uVar4 - 1) {
        uVar1 = *DAT_400016d0;
        DAT_400016d0 = DAT_400016d0 + 1;
        *(undefined1 *)DAT_400016f8 = uVar1;
        DAT_400016f8 = (uint *)((int)DAT_400016f8 + 1);
      }
      uVar2 = REG_FLEXCAN_A_MB16_CS;
      REG_FLEXCAN_A_MB16_CS = (DAT_400016da & 0xf) << 0x10 | uVar2 & 0xfff0ffff;
      uVar2 = REG_FLEXCAN_A_MB16_CS;
      REG_FLEXCAN_A_MB16_CS = uVar2 & 0xf0ffffff | 0xc000000;
      DAT_400016da = 0;
    }
    else {
      for (sVar3 = 8; sVar3 != 0; sVar3 = sVar3 + -1) {
        uVar1 = *DAT_400016d0;
        DAT_400016d0 = DAT_400016d0 + 1;
        *(undefined1 *)DAT_400016f8 = uVar1;
        DAT_400016f8 = (uint *)((int)DAT_400016f8 + 1);
      }
      uVar2 = REG_FLEXCAN_A_MB16_CS;
      REG_FLEXCAN_A_MB16_CS = uVar2 & 0xfff0ffff | 0x80000;
      uVar2 = REG_FLEXCAN_A_MB16_CS;
      REG_FLEXCAN_A_MB16_CS = uVar2 & 0xf0ffffff | 0xc000000;
      DAT_400016da = DAT_400016da - 8;
    }
  }
  return;
}



void FUN_00055b54(void)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_A_MB17_CS;
  if ((uVar1 >> 0x18 & 0xf) == 8) {
    uVar1 = REG_FLEXCAN_A_IFRL;
    REG_FLEXCAN_A_IFRL = uVar1 & 0xfffdffff | 0x20000;
  }
  return;
}



void FUN_00055b80(void)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_A_MB18_CS;
  if ((uVar1 >> 0x18 & 0xf) == 8) {
    uVar1 = REG_FLEXCAN_A_IFRL;
    REG_FLEXCAN_A_IFRL = uVar1 & 0xfffbffff | 0x40000;
  }
  return;
}



void FUN_00055bac(void)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_A_MB19_CS;
  if ((uVar1 >> 0x18 & 0xf) == 8) {
    uVar1 = REG_FLEXCAN_A_IFRL;
    REG_FLEXCAN_A_IFRL = uVar1 & 0xfff7ffff | 0x80000;
  }
  return;
}



void FUN_00055bd8(void)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_A_MB20_CS;
  if ((uVar1 >> 0x18 & 0xf) == 8) {
    uVar1 = REG_FLEXCAN_A_IFRL;
    REG_FLEXCAN_A_IFRL = uVar1 & 0xffefffff | 0x100000;
  }
  return;
}



void FUN_00055c04(void)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_A_MB21_CS;
  if ((uVar1 >> 0x18 & 0xf) == 8) {
    uVar1 = REG_FLEXCAN_A_IFRL;
    REG_FLEXCAN_A_IFRL = uVar1 & 0xffdfffff | 0x200000;
  }
  return;
}



void FUN_00055c30(void)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_A_MB22_CS;
  if ((uVar1 >> 0x18 & 0xf) == 8) {
    uVar1 = REG_FLEXCAN_A_IFRL;
    REG_FLEXCAN_A_IFRL = uVar1 & 0xffbfffff | 0x400000;
  }
  return;
}



void FUN_00055c5c(void)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_A_IFRL;
  REG_FLEXCAN_A_IFRL = uVar1 & 0xff7fffff | 0x800000;
  flexcan_a_tx_drain_sw_queue();
  return;
}



void FUN_00055c90(void)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_A_IFRL;
  REG_FLEXCAN_A_IFRL = uVar1 & 0xfeffffff | 0x1000000;
  return;
}



void obd_ii_processing(void)

{
  if ((obd_ii_request[0] & 0xf0) == 0x30) {
    isotp_flow_status = obd_ii_request[0] & 0xf;
    isotp_block_size = obd_ii_request[1];
    isotp_stmin = obd_ii_request[2];
    isotp_fc_received = true;
  }
  else {
    obd_ii_tx_messages_pending = false;
    switch(obd_ii_request[1]) {
    default:
      break;
    case 1:
      obd_ii_mode01_processing();
      break;
    case 3:
      obd_ii_mode03_processing();
      break;
    case 4:
      obd_ii_mode04_processing();
      break;
    case 7:
      obd_ii_mode07_processing();
      break;
    case 9:
      obd_ii_mode09_processing();
      break;
    case 10:
      if (CAL_obd_ii_standards_supported == '\x01') {
        obd_ii_mode10_processing();
      }
      break;
    case 0x11:
      obd_ii_mode11_processing();
      break;
    case 0x13:
      obd_ii_mode13_processing();
      break;
    case 0x14:
      obd_ii_mode14_processing();
      break;
    case 0x22:
      obd_ii_mode22_processing();
      break;
    case 0x2f:
      obd_ii_mode2f_processing();
    }
  }
  DAT_400016c0 = 0;
  return;
}



void FUN_00055de4(int param_1)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_A_MB18_CS;
  REG_FLEXCAN_A_MB18_CS = uVar1 & 0xf0ffffff | 0x8000000;
  uVar1 = REG_FLEXCAN_A_MB18_ID;
  REG_FLEXCAN_A_MB18_ID = uVar1 & 0xe003ffff | 0x8080000;
  REG_FLEXCAN_A_MB18_DATA0._0_1_ = *(undefined1 *)(param_1 + 3);
  REG_FLEXCAN_A_MB18_DATA0._1_1_ = *(undefined1 *)(param_1 + 2);
  REG_FLEXCAN_A_MB18_DATA0._2_1_ = *(undefined1 *)(param_1 + 1);
  uVar1 = REG_FLEXCAN_A_MB18_CS;
  REG_FLEXCAN_A_MB18_CS = uVar1 & 0xfff0ffff | 0x30000;
  uVar1 = REG_FLEXCAN_A_MB18_CS;
  REG_FLEXCAN_A_MB18_CS = uVar1 & 0xf0ffffff | 0xc000000;
  return;
}



void flexcan_a_isr_vec152(void)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_A_ESR;
  REG_FLEXCAN_A_ESR = uVar1 & 0xfffffffb | 4;
  return;
}



void flexcan_a_isr_vec153(void)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_A_ESR;
  REG_FLEXCAN_A_ESR = uVar1 & 0xfffffffd | 2;
  return;
}



void flexcan_a_tx_c7(undefined1 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
                    undefined1 param_5,undefined1 param_6,undefined1 param_7,undefined1 param_8)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_A_MB21_CS;
  REG_FLEXCAN_A_MB21_CS = uVar1 & 0xf0ffffff | 0x8000000;
  uVar1 = REG_FLEXCAN_A_MB21_ID;
  REG_FLEXCAN_A_MB21_ID = uVar1 & 0xe003ffff | 0x31c0000;
  REG_FLEXCAN_A_MB21_DATA0._0_1_ = param_1;
  REG_FLEXCAN_A_MB21_DATA0._1_1_ = param_2;
  REG_FLEXCAN_A_MB21_DATA0._2_1_ = param_3;
  REG_FLEXCAN_A_MB21_DATA0._3_1_ = param_4;
  REG_FLEXCAN_A_MB21_DATA1._0_1_ = param_5;
  REG_FLEXCAN_A_MB21_DATA1._1_1_ = param_6;
  REG_FLEXCAN_A_MB21_DATA1._2_1_ = param_7;
  REG_FLEXCAN_A_MB21_DATA1._3_1_ = param_8;
  uVar1 = REG_FLEXCAN_A_MB21_CS;
  REG_FLEXCAN_A_MB21_CS = uVar1 & 0xfff0ffff | 0x80000;
  uVar1 = REG_FLEXCAN_A_MB21_CS;
  REG_FLEXCAN_A_MB21_CS = uVar1 & 0xf0ffffff | 0xc000000;
  return;
}



void flexcan_a_tx_250(undefined1 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
                     undefined1 param_5,undefined1 param_6,undefined1 param_7,undefined1 param_8)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_A_MB20_CS;
  REG_FLEXCAN_A_MB20_CS = uVar1 & 0xf0ffffff | 0x8000000;
  uVar1 = REG_FLEXCAN_A_MB20_ID;
  REG_FLEXCAN_A_MB20_ID = uVar1 & 0xe003ffff | 0x9400000;
  REG_FLEXCAN_A_MB20_DATA0._0_1_ = param_1;
  REG_FLEXCAN_A_MB20_DATA0._1_1_ = param_2;
  REG_FLEXCAN_A_MB20_DATA0._2_1_ = param_3;
  REG_FLEXCAN_A_MB20_DATA0._3_1_ = param_4;
  REG_FLEXCAN_A_MB20_DATA1._0_1_ = param_5;
  REG_FLEXCAN_A_MB20_DATA1._1_1_ = param_6;
  REG_FLEXCAN_A_MB20_DATA1._2_1_ = param_7;
  REG_FLEXCAN_A_MB20_DATA1._3_1_ = param_8;
  uVar1 = REG_FLEXCAN_A_MB20_CS;
  REG_FLEXCAN_A_MB20_CS = uVar1 & 0xfff0ffff | 0x80000;
  uVar1 = REG_FLEXCAN_A_MB20_CS;
  REG_FLEXCAN_A_MB20_CS = uVar1 & 0xf0ffffff | 0xc000000;
  return;
}



void FUN_00055ff8(void)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_A_MB11_CS;
  REG_FLEXCAN_A_MB11_CS = uVar1 & 0xf0ffffff | 0x8000000;
  uVar1 = REG_FLEXCAN_A_MB11_ID;
  REG_FLEXCAN_A_MB11_ID = uVar1 & 0xe003ffff | 0x14140000;
  REG_FLEXCAN_A_MB11_DATA0._0_1_ = COD_unknown[3];
  REG_FLEXCAN_A_MB11_DATA0._1_1_ = COD_unknown[2];
  REG_FLEXCAN_A_MB11_DATA0._2_1_ = COD_unknown[1];
  REG_FLEXCAN_A_MB11_DATA0._3_1_ = COD_unknown[0];
  REG_FLEXCAN_A_MB11_DATA1._0_1_ = COD_unknown[7];
  REG_FLEXCAN_A_MB11_DATA1._1_1_ = COD_unknown[6];
  REG_FLEXCAN_A_MB11_DATA1._2_1_ = COD_unknown[5];
  REG_FLEXCAN_A_MB11_DATA1._3_1_ = COD_unknown[4];
  uVar1 = REG_FLEXCAN_A_MB11_CS;
  REG_FLEXCAN_A_MB11_CS = uVar1 & 0xfff0ffff | 0x80000;
  uVar1 = REG_FLEXCAN_A_MB11_CS;
  REG_FLEXCAN_A_MB11_CS = uVar1 & 0xf0ffffff | 0xc000000;
  return;
}



uint FUN_00056108(void)

{
  uint uVar1;
  
  if ((DAT_40001455 & 2) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = ((uint)DAT_40001428 * 10000) / 0x3205 & 0xff;
  }
  return uVar1;
}



undefined1 FUN_00056148(void)

{
  undefined1 uVar1;
  
  uVar1 = DAT_400016de;
  if ((DAT_40001455 & 2) == 0) {
    uVar1 = 3;
  }
  return uVar1;
}



undefined2 FUN_00056164(void)

{
  undefined2 uVar1;
  
  uVar1 = DAT_400016e2;
  if ((DAT_40001452 & 2) == 0) {
    uVar1 = 0;
  }
  return uVar1;
}



undefined2 FUN_00056180(void)

{
  undefined2 uVar1;
  
  uVar1 = DAT_400016e4;
  if ((DAT_40001452 & 2) == 0) {
    uVar1 = 0;
  }
  return uVar1;
}



undefined2 FUN_0005619c(void)

{
  undefined2 uVar1;
  
  uVar1 = DAT_400016e6;
  if ((DAT_40001452 & 2) == 0) {
    uVar1 = 0;
  }
  return uVar1;
}



undefined2 FUN_000561b8(void)

{
  undefined2 uVar1;
  
  uVar1 = DAT_400016e8;
  if ((DAT_40001452 & 8) == 0) {
    uVar1 = 0;
  }
  return uVar1;
}



undefined2 FUN_000561d4(void)

{
  undefined2 uVar1;
  
  uVar1 = DAT_400016ea;
  if ((DAT_40001452 & 8) == 0) {
    uVar1 = 0;
  }
  return uVar1;
}



void FUN_000561f0(void)

{
  ushort uVar1;
  byte bVar2;
  uint uVar3;
  
  uVar3 = REG_FLEXCAN_C_MCR;
  REG_FLEXCAN_C_MCR = uVar3 & 0xfdffffff | 0x2000000;
  do {
    uVar3 = REG_FLEXCAN_C_MCR;
  } while ((uVar3 >> 0x19 & 1) == 1);
  uVar3 = REG_FLEXCAN_C_MCR;
  REG_FLEXCAN_C_MCR = uVar3 & 0xefffffff | 0x10000000;
  do {
    uVar3 = REG_FLEXCAN_C_MCR;
  } while ((uVar3 & 0x9000000) != 0x9000000);
  REG_FLEXCAN_C_CR = 0x510001;
  REG_FLEXCAN_C_MB0_CS = 0;
  REG_FLEXCAN_C_MB1_CS = 0;
  REG_FLEXCAN_C_MB2_CS = 0;
  REG_FLEXCAN_C_MB3_CS = 0;
  REG_FLEXCAN_C_MB4_CS = 0;
  REG_FLEXCAN_C_MB5_CS = 0;
  REG_FLEXCAN_C_MB6_CS = 0;
  REG_FLEXCAN_C_MB7_CS = 0;
  REG_FLEXCAN_C_MB8_CS = 0;
  REG_FLEXCAN_C_MB9_CS = 0;
  REG_FLEXCAN_C_MB10_CS = 0;
  REG_FLEXCAN_C_MB11_CS = 0;
  REG_FLEXCAN_C_MB12_CS = 0;
  uVar3 = REG_FLEXCAN_C_MB12_CS;
  REG_FLEXCAN_C_MB12_CS = uVar3 & 0xf0ffffff | 0x4000000;
  REG_FLEXCAN_C_MB12_ID = 0xd800000;
  uVar3 = REG_FLEXCAN_C_MB12_CS;
  REG_FLEXCAN_C_MB12_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_C_MB13_CS = 0;
  uVar3 = REG_FLEXCAN_C_MB13_CS;
  REG_FLEXCAN_C_MB13_CS = uVar3 & 0xf0ffffff | 0x8000000;
  REG_FLEXCAN_C_MB13_ID = 0xd840000;
  uVar3 = REG_FLEXCAN_C_MB13_CS;
  REG_FLEXCAN_C_MB13_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_C_MB14_CS = 0;
  uVar3 = REG_FLEXCAN_C_MB14_CS;
  REG_FLEXCAN_C_MB14_CS = uVar3 & 0xf0ffffff | 0x8000000;
  REG_FLEXCAN_C_MB14_ID = 0xd840000;
  uVar3 = REG_FLEXCAN_C_MB14_CS;
  REG_FLEXCAN_C_MB14_CS = uVar3 & 0xffff0000;
  REG_FLEXCAN_C_MB15_CS = 0;
  REG_FLEXCAN_C_RXGMASK = 0x1fffffff;
  REG_FLEXCAN_C_RX14MASK = 0x1fffffff;
  REG_FLEXCAN_C_RX15MASK = 0x1fffffff;
  REG_FLEXCAN_C_IMRH = 0;
  REG_FLEXCAN_C_IMRL = 0;
  uVar3 = REG_FLEXCAN_C_IMRL;
  REG_FLEXCAN_C_IMRL = uVar3 & 0xffffefff | 0x1000;
  uVar3 = REG_FLEXCAN_C_IMRL;
  REG_FLEXCAN_C_IMRL = uVar3 & 0xffffdfff | 0x2000;
  uVar3 = REG_FLEXCAN_C_IMRL;
  REG_FLEXCAN_C_IMRL = uVar3 & 0xffffbfff | 0x4000;
  bVar2 = REG_INTC_PSR188;
  REG_INTC_PSR188 = bVar2 & 0xf0 | 3;
  bVar2 = REG_INTC_PSR189;
  REG_INTC_PSR189 = bVar2 & 0xf0 | 3;
  bVar2 = REG_INTC_PSR190;
  REG_INTC_PSR190 = bVar2 & 0xf0 | 3;
  uVar1 = REG_SIU_PCR87;
  REG_SIU_PCR87 = uVar1 & 0xe3ff | 0x400;
  uVar1 = REG_SIU_PCR88;
  REG_SIU_PCR88 = uVar1 & 0xe3ff | 0x400;
  uVar3 = REG_FLEXCAN_C_MCR;
  REG_FLEXCAN_C_MCR = uVar3 & 0xefffffff;
  REG_FLEXCAN_C_IFRH = 0xffffffff;
  REG_FLEXCAN_C_IFRL = 0xffffffff;
  return;
}



void FUN_000564c8(void)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_C_IFRL;
  REG_FLEXCAN_C_IFRL = uVar1 & 0xffffffdf | 0x20;
  return;
}



void FUN_000564e0(void)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_C_IFRL;
  REG_FLEXCAN_C_IFRL = uVar1 & 0xffffff7f | 0x80;
  return;
}



void FUN_000564f8(void)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_C_IFRL;
  REG_FLEXCAN_C_IFRL = uVar1 & 0xfffffeff | 0x100;
  return;
}



void FUN_00056510(void)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_C_IFRL;
  REG_FLEXCAN_C_IFRL = uVar1 & 0xfffffdff | 0x200;
  return;
}



void flexcan_a_rx_360_2(void)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_C_IFRL;
  REG_FLEXCAN_C_IFRL = uVar1 & 0xffffefff | 0x1000;
  uVar1 = REG_FLEXCAN_C_MB12_CS;
  while ((uVar1 >> 0x18 & 1) != 0) {
    uVar1 = REG_FLEXCAN_C_MB12_CS;
  }
  uVar1 = REG_FLEXCAN_C_MB12_CS;
  if ((uVar1 >> 0x18 & 6) == 6) {
    uVar1 = REG_FLEXCAN_C_MB12_CS;
    REG_FLEXCAN_C_MB12_CS = uVar1 & 0xf0ffffff | 0x4000000;
    uVar1 = REG_FLEXCAN_C_TIMER;
    DAT_40001750 = (undefined2)uVar1;
  }
  else {
    uVar1 = REG_FLEXCAN_C_MB12_CS;
    if ((uVar1 >> 0x18 & 2) == 2) {
      uVar1 = REG_FLEXCAN_C_MB12_ID;
      if ((uVar1 >> 0x12 & 0x7ff) == 0x360) {
        DAT_40001758 = REG_FLEXCAN_C_MB12_DATA0._0_1_;
        DAT_40001759 = REG_FLEXCAN_C_MB12_DATA0._1_1_;
        DAT_4000175a = REG_FLEXCAN_C_MB12_DATA0._2_1_;
        DAT_4000175b = REG_FLEXCAN_C_MB12_DATA0._3_1_;
        DAT_4000175c = REG_FLEXCAN_C_MB12_DATA1._0_1_;
        DAT_4000175d = REG_FLEXCAN_C_MB12_DATA1._1_1_;
        DAT_4000175e = REG_FLEXCAN_C_MB12_DATA1._2_1_;
        DAT_4000175f = REG_FLEXCAN_C_MB12_DATA1._3_1_;
        uVar1 = REG_FLEXCAN_C_MB12_CS;
        REG_FLEXCAN_C_MB12_CS = uVar1 & 0xf0ffffff | 0x4000000;
        uVar1 = REG_FLEXCAN_C_TIMER;
        DAT_40001750 = (undefined2)uVar1;
        FUN_00051358(&DAT_40001758);
      }
      else {
        uVar1 = REG_FLEXCAN_C_MB12_CS;
        REG_FLEXCAN_C_MB12_CS = uVar1 & 0xf0ffffff | 0x4000000;
        uVar1 = REG_FLEXCAN_C_TIMER;
        DAT_40001750 = (undefined2)uVar1;
      }
    }
    else {
      uVar1 = REG_FLEXCAN_C_MB12_CS;
      REG_FLEXCAN_C_MB12_CS = uVar1 & 0xf0ffffff | 0x4000000;
      uVar1 = REG_FLEXCAN_C_TIMER;
      DAT_40001750 = (undefined2)uVar1;
    }
  }
  return;
}



void FUN_0005670c(void)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_C_IFRL;
  REG_FLEXCAN_C_IFRL = uVar1 & 0xffffdfff | 0x2000;
  flexcan_a_tx_drain_sw_queue();
  return;
}



void FUN_00056758(void)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_C_ESR;
  REG_FLEXCAN_C_ESR = uVar1 & 0xfffffffb | 4;
  return;
}



void FUN_00056770(void)

{
  uint uVar1;
  
  uVar1 = REG_FLEXCAN_C_ESR;
  REG_FLEXCAN_C_ESR = uVar1 & 0xfffffffd | 2;
  return;
}



ulonglong FUN_00056788(void)

{
  return (-(ulonglong)DAT_4000176e << 0x20) >> 0x3f;
}



void init_esci_a(void)

{
  uint uVar1;
  ushort uVar2;
  
  REG_ESCI_A_SR = 0xffffffff;
  REG_ESCI_A_CR1 = 0;
  uVar1 = REG_ESCI_A_CR1;
  REG_ESCI_A_CR1 = uVar1 & 0xfffffff7 | 8;
  uVar1 = REG_ESCI_A_CR1;
  REG_ESCI_A_CR1 = uVar1 & 0xfffffffb | 4;
  uVar1 = REG_ESCI_A_CR1;
  REG_ESCI_A_CR1 = uVar1 & 0xe000ffff | 0x4000000;
  uVar1 = REG_ESCI_A_CR1;
  REG_ESCI_A_CR1 = uVar1 & 0xffffffdf | 0x20;
  REG_ESCI_A_CR2 = 0x2000;
  uVar2 = REG_ESCI_A_CR2;
  REG_ESCI_A_CR2 = uVar2 & 0xdfff | 0x2000;
  REG_ESCI_A_LCR = 0;
  REG_ESCI_A_LPR = 0xc5990000;
  REG_SIU_PCR89 = 0x400;
  REG_SIU_PCR90 = 0x400;
  REG_INTC_PSR146 = 5;
  return;
}



undefined1 esci_circular_buffer_dequeue(void)

{
  uint uVar1;
  
  do {
  } while (DAT_4000176e == '\0');
  REG_INTC_PSR149 = 0;
  uVar1 = (uint)DAT_4000176f;
  DAT_4000176e = DAT_4000176e + -1;
  DAT_4000176f = DAT_4000176f + 1 & 0x1f;
  REG_INTC_PSR149 = 2;
  return (&DAT_40005420)[uVar1];
}



void FUN_000568cc(void)

{
  undefined1 uVar1;
  uint uVar2;
  
  uVar2 = REG_ESCI_A_SR;
  if ((uVar2 >> 0x1d & 1) != 0) {
    uVar1 = REG_ESCI_A_DR._1_1_;
    uVar2 = REG_ESCI_A_SR;
    REG_ESCI_A_SR = uVar2 & 0xdfffffff | 0x20000000;
    if (DAT_4000176e < 0x20) {
      (&DAT_40005420)[DAT_40001770] = uVar1;
      DAT_40001770 = DAT_40001770 + 1 & 0x1f;
      DAT_4000176e = DAT_4000176e + 1;
    }
  }
  return;
}



void esci_tx_unknown(int param_1,byte param_2)

{
  uint uVar1;
  byte bVar2;
  
  uVar1 = REG_ESCI_A_CR1;
  REG_ESCI_A_CR1 = uVar1 & 0xffffff7f;
  uVar1 = REG_ESCI_A_SR;
  REG_ESCI_A_SR = uVar1 & 0x7fffffff | 0x80000000;
  for (bVar2 = 0; bVar2 < param_2; bVar2 = bVar2 + 1) {
    (&DAT_40005400)[bVar2] = *(undefined1 *)(param_1 + (uint)bVar2);
  }
  DAT_4000176c = param_2;
  REG_ESCI_A_DR._1_1_ = DAT_40005400;
  DAT_4000176d = 1;
  if (1 < param_2) {
    uVar1 = REG_ESCI_A_CR1;
    REG_ESCI_A_CR1 = uVar1 & 0xffffff7f | 0x80;
  }
  return;
}



void FUN_000569fc(void)

{
  uint uVar1;
  
  uVar1 = REG_ESCI_A_CR1;
  if (((uVar1 >> 7 & 1) == 1) && (uVar1 = REG_ESCI_A_SR, (int)uVar1 < 0)) {
    REG_ESCI_A_DR._1_1_ = (&DAT_40005400)[DAT_4000176d];
    DAT_4000176d = DAT_4000176d + 1;
    uVar1 = REG_ESCI_A_SR;
    REG_ESCI_A_SR = uVar1 & 0x7fffffff | 0x80000000;
    if (DAT_4000176d == DAT_4000176c) {
      uVar1 = REG_ESCI_A_CR1;
      REG_ESCI_A_CR1 = uVar1 & 0xffffff7f;
    }
  }
  return;
}



void esci_a_isr_vec146(void)

{
  FUN_000568cc();
  FUN_000569fc();
  return;
}



undefined8 FUN_00056ab0(byte param_1)

{
  if (DAT_4000176a < 0x14) {
    if (DAT_4000153c == '\0') {
      DAT_4000176a = 0;
    }
    DAT_4000153c = '\x06';
    DAT_400015e8 = (uint)DAT_4000176a;
    if (DAT_4000176a == 0) {
      if (param_1 == 0xaa) {
        DAT_400053e8 = 0xaa;
        DAT_4000176a = '\x01';
        DAT_40001769 = 0xaa;
      }
      else {
        DAT_4000176e = 0;
        DAT_4000176f = 0;
        DAT_40001770 = 0;
        DAT_4000176a = '\0';
      }
    }
    else if (DAT_4000176a == 1) {
      DAT_4000176a = '\x02';
      DAT_40001769 = DAT_40001769 + param_1;
      DAT_400053e9 = param_1;
    }
    else if (DAT_4000176a == 2) {
      DAT_4000176a = '\x03';
      DAT_40001769 = DAT_40001769 + param_1;
      DAT_400053ea = param_1;
    }
    else if (DAT_400053e9 + 1 < (uint)DAT_4000176a) {
      if ((uint)DAT_4000176a == DAT_400053e9 + 2) {
        (&DAT_400053e8)[DAT_4000176a] = param_1;
        DAT_4000176a = '\0';
        if (param_1 == (byte)~DAT_40001769) {
          DAT_4000176a = 0;
          return 1;
        }
      }
      else {
        DAT_4000176a = '\0';
      }
    }
    else {
      (&DAT_400053e8)[DAT_4000176a] = param_1;
      DAT_4000176a = DAT_4000176a + 1;
      DAT_40001769 = DAT_40001769 + param_1;
    }
  }
  else {
    DAT_4000176e = 0;
    DAT_4000176f = 0;
    DAT_40001770 = 0;
    DAT_4000176a = '\0';
  }
  return 0;
}



void FUN_00056c74(char *param_1,byte param_2)

{
  char cVar1;
  int iVar2;
  byte *pbVar3;
  char *pcVar4;
  
  *param_1 = -0x56;
  param_1[1] = param_2 + 1;
  DAT_4000176b = DAT_4000176b + '\x01';
  param_1[param_2 + 2] = DAT_4000176b;
  pbVar3 = (byte *)(param_1 + param_2 + 3);
  *pbVar3 = 0;
  pcVar4 = param_1;
  for (iVar2 = 0; iVar2 <= (int)(param_2 + 2); iVar2 = iVar2 + 1) {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    *pbVar3 = *pbVar3 + cVar1;
  }
  *pbVar3 = ~*pbVar3;
  esci_tx_unknown(param_1,param_2 + 4);
  return;
}



void FUN_00056d20(void)

{
  undefined1 auStack_10 [2];
  undefined1 local_e;
  
  FUN_00057008();
  local_e = 0x81;
  FUN_00056c74(auStack_10,4);
  return;
}



void FUN_00056d90(void)

{
  int iVar1;
  undefined1 uVar2;
  
  while (iVar1 = FUN_00056788(), iVar1 != 0) {
    uVar2 = esci_circular_buffer_dequeue();
    iVar1 = FUN_00056ab0(uVar2);
    if (iVar1 != 0) {
      DAT_4000153b = -0x39;
      if (DAT_400053ea == -0x80) {
        DAT_40003468 = CONCAT11(DAT_400053eb,DAT_400053ec);
      }
      else if (DAT_400053ea == -0x7f) {
        DAT_4000346e = DAT_400053eb;
        DAT_40003472 = DAT_400053ec;
        DAT_40003473 = DAT_400053ed;
        DAT_40003474 = DAT_400053ee;
        DAT_40003475 = DAT_400053ef;
        DAT_40003476 = DAT_400053f0;
        DAT_4000346a = CONCAT11(DAT_400053f1,DAT_400053f2);
        DAT_4000346c = DAT_400053f1;
        DAT_4000346d = DAT_400053f2;
        DAT_4000346f = DAT_400053f3;
        DAT_40003470 = DAT_400053f4;
        DAT_40003468 = CONCAT11(DAT_400053f5,DAT_400053f6);
        iVar1 = FUN_000507b4();
        if (iVar1 == 0) {
          DAT_40003471 = DAT_40003471 | 1;
        }
      }
    }
  }
  if (DAT_4000153b == '\0') {
    DAT_40003471 = DAT_40003471 | 4;
    DAT_4000176e = 0;
    DAT_4000176f = 0;
    DAT_40001770 = 0;
  }
  return;
}



void FUN_00057008(void)

{
  char cVar1;
  
  if (DAT_40001768 == '\0') {
    if (DAT_40002bdc == '\0') {
      DAT_40001768 = '\x02';
      cVar1 = DAT_40001768;
    }
    else {
      DAT_40001768 = '\x04';
      cVar1 = DAT_40001768;
    }
  }
  else {
    cVar1 = DAT_40001768;
    if (DAT_40001768 == '\x02') {
      if (((DAT_40002bdc != '\0') && (DAT_40001bfc == '\0')) || (DAT_4000346f == '\f')) {
        DAT_40001768 = '\x04';
        cVar1 = DAT_40001768;
      }
    }
    else if (((DAT_40001768 == '\x04') && (DAT_40001bfc != '\0')) &&
            (cVar1 = '\x02', DAT_4000346f == '\f')) {
      cVar1 = DAT_40001768;
    }
  }
  DAT_40001768 = cVar1;
  DAT_400016ac = DAT_40001768;
  DAT_400016ad = 0;
  if ((DAT_400015b8 & 1) == 0) {
    DAT_400016ae = 0;
  }
  else {
    DAT_400016ae = 0x80;
  }
  return;
}



void FUN_00057110(void)

{
  adc_smooth_state_init
            (&DAT_40005464,&DAT_000015cd,&DAT_00004ae5,&DAT_00004ae5,&DAT_00004013,&DAT_000038d4,
             &DAT_00004335,&DAT_0000728f,&DAT_00004335);
  adc_smooth_state_init
            (&DAT_40005440,&DAT_000015cd,&DAT_00004ae5,&DAT_00004ae5,&DAT_00004013,&DAT_000038d4,
             &DAT_00004335,&DAT_0000728f,&DAT_00004335);
  return;
}



void FUN_000571cc(void)

{
  REG_SIU_PCR199 = 0xe84;
  REG_SIU_PCR202 = 0x2cc;
  REG_SIU_PCR86 = 0x2cc;
  REG_SIU_PCR189 = 0x2cc;
  init_eMIOS(0x14,DAT_40008ff2,0,1);
  REG_SIU_PCR94 = 0x100;
  REG_SIU_PCR85 = 0x100;
  FUN_00057110();
  return;
}



void FUN_00057254(void)

{
  REG_EMIOS_UC20_CADR = 0;
  DAT_400017ca = 0;
  REG_SIU_GPDO202 = 1;
  REG_SIU_GPDO189 = 0;
  return;
}



void FUN_00057284(void)

{
  DAT_4000177b = 0;
  DAT_4000177c = 0;
  DAT_4000177d = 0;
  DAT_40001778 = 0;
  DAT_40001779 = 0;
  DAT_4000177a = 0;
  DAT_400017ad = 0;
  DAT_400017ac = 0;
  DAT_400017ab = 0;
  return;
}



void FUN_000572d0(uint param_1)

{
  uint uVar1;
  
  WriteExternalEnableImmediate(0);
  if (param_1 != 0) {
    param_1 = param_1 - 1;
  }
  uVar1 = REG_EMIOS_UC20_CBDR;
  if (param_1 < uVar1) {
    if (param_1 < 3) {
      uVar1 = REG_EMIOS_UC20_CBDR;
      REG_EMIOS_UC20_CADR = uVar1;
      uVar1 = REG_EMIOS_UC20_CCR;
      REG_EMIOS_UC20_CCR = uVar1 & 0xffffdfff | 0x2000;
    }
    else {
      uVar1 = REG_EMIOS_UC20_CCNTR;
      if (uVar1 < param_1 + 2) {
        REG_EMIOS_UC20_CADR = param_1;
      }
      else {
        REG_EMIOS_UC20_CADR = param_1;
        uVar1 = REG_EMIOS_UC20_CCR;
        REG_EMIOS_UC20_CCR = uVar1 & 0xffffdfff | 0x2000;
      }
    }
  }
  else {
    REG_EMIOS_UC20_CADR = 0;
    uVar1 = REG_EMIOS_UC20_CCR;
    REG_EMIOS_UC20_CCR = uVar1 & 0xffffefff | 0x1000;
  }
  return;
}



void FUN_0005738c(ulonglong param_1)

{
  DAT_400015ec = DAT_400015ec + 1;
  if (DAT_4000177e != DAT_40008ff2) {
    init_eMIOS(0x14,DAT_40008ff2,param_1,1);
    DAT_4000177e = DAT_40008ff2;
    DAT_40001780 = (ushort)param_1;
  }
  if ((ulonglong)DAT_40001780 != (param_1 & 0xffffffff)) {
    FUN_000572d0(param_1);
    DAT_40001780 = (ushort)param_1;
  }
  return;
}



void FUN_00057430(short param_1,short param_2,char param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  ushort uVar4;
  ushort uVar5;
  uint uVar6;
  ushort uVar7;
  short sVar8;
  ushort uVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  
  uVar5 = DAT_40008ffa;
  uVar4 = DAT_40008ff8;
  uVar11 = (uint)DAT_40008ffa;
  uVar6 = (uint)DAT_40001db4;
  if (param_3 == '\0') {
    DAT_4000178e = DAT_4000178c;
    DAT_4000178c = DAT_4000178a;
    DAT_4000178a = DAT_40001788;
  }
  else {
    DAT_40001790 = 0;
    DAT_4000178a = param_2;
    DAT_4000178c = param_2;
    DAT_4000178e = param_2;
  }
  uVar7 = param_1 - param_2;
  uVar9 = DAT_40009000;
  if (((int)(short)uVar7 <= (int)(uint)DAT_40009000) &&
     (uVar9 = uVar7, (int)(short)uVar7 < (int)-(uint)DAT_40009000)) {
    uVar9 = -DAT_40009000;
  }
  DAT_40001788 = param_2;
  sVar8 = adc_smooth_lowpass(&DAT_40005440,DAT_4000178e - param_2);
  iVar2 = (int)((uint)DAT_40008ffc * (int)sVar8) / 10;
  iVar3 = (int)((uint)DAT_40008ffe * (int)(short)uVar9) / 100;
  DAT_40001790 = DAT_40001790 + (int)(short)uVar9;
  uVar10 = (int)(uVar4 * DAT_40001790) / 10000;
  if (((int)(uint)uVar5 < (int)uVar10) || ((int)uVar10 < (int)-(uint)uVar5)) {
    if ((int)uVar10 < 1) {
      uVar10 = -uVar11;
      DAT_40001790 = (int)((uint)uVar5 * -10000) / (int)(uint)uVar4;
    }
    else {
      DAT_40001790 = ((uint)uVar5 * 10000) / (uint)uVar4;
      uVar10 = uVar11;
    }
  }
  iVar12 = iVar3 + uVar10 + iVar2;
  iVar1 = (iVar12 * 0x3ff) / ((int)uVar6 >> 4);
  REG_SIU_GPDO189 = 1;
  if (iVar1 < 0) {
    uVar6 = -((int)(iVar1 * (uint)DAT_40008ff2) / 0x3ff);
    REG_SIU_GPDO202 = 1;
  }
  else {
    uVar6 = (int)(iVar1 * (uint)DAT_40008ff2) / 0x3ff;
    REG_SIU_GPDO202 = 0;
  }
  uVar6 = uVar6 & 0xffff;
  if (((uint)DAT_40008ff2 * 0x32) / 100 < uVar6) {
    if (DAT_4000143c != 0) {
      DAT_4000143c = DAT_4000143c + -1;
    }
  }
  else {
    DAT_4000143c = 100;
  }
  if (DAT_4000143c == 0) {
    uVar6 = ((uint)DAT_40008ff2 * 0x32) / 100;
  }
  FUN_0005738c(uVar6);
  DAT_400017cc = uVar9;
  DAT_400017ca = (char)((uVar6 * 100) / (uint)DAT_40008ff2);
  DAT_400017c8 = sVar8;
  DAT_400017c4 = DAT_40001790;
  DAT_400017c0 = iVar2;
  DAT_400017bc = iVar3;
  DAT_400017b8 = uVar10;
  DAT_400017b4 = 0;
  DAT_400017b0 = iVar12;
  return;
}



void ramp_selector_position(void)

{
  short sVar1;
  int iVar2;
  byte bVar3;
  byte bVar4;
  ulonglong uVar5;
  short sVar6;
  
  sVar6 = DAT_400017d2;
  sVar1 = DAT_40001438;
  iVar2 = int_abs((longlong)DAT_400017d2 - (longlong)DAT_40001438);
  bVar3 = lookup_2D_uint8_interpolated(8,iVar2 >> 2 & 0xff,s_____40009b3a,s__40009b32);
  if (bVar3 == 0) {
    bVar3 = 1;
  }
  bVar4 = lookup_2D_uint8_interpolated(8,iVar2 >> 2 & 0xff,s_____40009b2a,s__40009b22);
  if (bVar4 == 0) {
    bVar4 = 1;
  }
  if (((bVar4 == 0xff) && (sVar6 < sVar1)) || ((bVar3 == 0xff && (sVar1 < sVar6)))) {
    DAT_40001794 = 0;
    uVar5 = 0;
    sVar6 = sVar1;
  }
  else {
    DAT_40001794 = DAT_40001794 + -1;
    if (DAT_40001794 < 1) {
      DAT_40001794 = DAT_40009006;
      if (sVar6 < sVar1) {
        if ((int)(uint)bVar4 < (int)sVar1 - (int)sVar6) {
          uVar5 = 1;
          DAT_40001796 = 1;
          sVar6 = sVar6 + (ushort)bVar4;
          if (0x3ff < sVar6) {
            sVar6 = 0x3ff;
          }
        }
        else {
          uVar5 = 0;
          sVar6 = sVar1;
        }
      }
      else if (sVar1 < sVar6) {
        if ((int)(uint)bVar3 < (int)sVar6 - (int)sVar1) {
          uVar5 = 1;
          DAT_40001796 = 2;
          sVar6 = sVar6 - (ushort)bVar3;
          if (sVar6 < 0) {
            sVar6 = 0;
          }
        }
        else {
          uVar5 = 0;
          sVar6 = sVar1;
        }
      }
      else {
        uVar5 = 0;
        sVar6 = sVar1;
      }
    }
    else {
      uVar5 = (-(ulonglong)DAT_40001796 << 0x20) >> 0x3f;
    }
  }
  if (uVar5 == 0) {
    DAT_40001796 = 0;
  }
  DAT_400017d0 = sVar1;
  DAT_400017d2 = sVar6;
  DAT_400017ce = DAT_40001796;
  return;
}



void FUN_00057a04(void)

{
  uint uVar1;
  
  REG_SIU_GPDO189 = 1;
  REG_SIU_GPDO86 = 1;
  DAT_400017a6 = DAT_400017a6 + 1;
  if (1999 < DAT_400017a6) {
    DAT_400017a8 = DAT_400017a8 ^ 1;
    DAT_400017a6 = 0;
  }
  if (DAT_400017a8 == 0) {
    REG_SIU_GPDO202 = 1;
  }
  else {
    REG_SIU_GPDO202 = 0;
  }
  uVar1 = ((uint)DAT_40008ff2 * 0x19) / 100;
  FUN_0005738c(uVar1);
  DAT_400017ca = (char)((uVar1 * 100) / (uint)DAT_40008ff2);
  return;
}



void FUN_00057b18(void)

{
  bool bVar1;
  byte bVar2;
  byte bVar3;
  short sVar5;
  undefined2 uVar6;
  uint uVar4;
  
  sVar5 = get_shift_lever_pos_raw___();
  if (sVar5 == -1) {
    DAT_4000179e = 0;
  }
  DAT_400017af = (undefined1)DAT_4000179e;
  DAT_40001778 = '\0';
  DAT_40001779 = '\0';
  DAT_4000177a = '\0';
  if (DAT_4000179e == 0) {
    FUN_00057254();
    if (DAT_4000179c == 0) {
      DAT_4000179c = DAT_40001438;
    }
    if ((DAT_4000143e == 0) || (DAT_40001438 != DAT_4000179c)) {
      REG_SIU_GPDO193 = 0;
      DAT_4000179c = 0;
      if ((((DAT_40001438 == 0xffff) || (sVar5 = get_shift_lever_pos_raw___(), sVar5 == -1)) ||
          (((((uVar4 = get_shift_lever_pos_raw___(),
              (uVar4 & 0xffff) <= (uint)DAT_40001438 + (uint)DAT_40009005 &&
              (uVar4 = get_shift_lever_pos_raw___(),
              (int)((uint)DAT_40001438 - (uint)DAT_40009005) <= (int)(uVar4 & 0xffff))) &&
             (DAT_4000143a == 3)) && ((DAT_40001bfe == '\0' && (DAT_40001c56 == '\0')))) ||
           ((driver_input_flags[1] & 1) != 0)))) || (DAT_400017a3 != 0)) {
        if ((DAT_40001840 & 0x2000) != 0) {
          DAT_4000179e = 5;
        }
      }
      else {
        DAT_400017a0 = 100;
        DAT_4000179e = 1;
        DAT_40001c56 = '\0';
        DAT_400017a4 = 0;
      }
    }
    else {
      if (DAT_4000143e == 1) {
        DAT_400017a4 = 1;
        if (DAT_400017a2 == DAT_40001438) {
          DAT_400017a3 = DAT_400017a3 | 0xf;
        }
        DAT_40001438 = get_shift_lever_pos_raw___();
        DAT_400017d0 = DAT_40001438;
        DAT_400017d2 = DAT_40001438;
      }
      DAT_4000143e = DAT_4000143e + -1;
    }
  }
  else if (DAT_4000179e == 1) {
    DAT_400017a0 = DAT_400017a0 + -1;
    if (DAT_400017a0 < 1) {
      if (DAT_40008ff6 == '\x02') {
        DAT_4000179e = 4;
      }
      else {
        DAT_4000179e = 2;
      }
    }
  }
  else if (DAT_4000179e == 4) {
    FUN_00057a04();
    bVar3 = REG_SIU_GPDI94;
    bVar2 = REG_SIU_GPDI85;
    DAT_4000143a = bVar3 << 1 | bVar2;
    if (DAT_4000143a == 2) {
      DAT_40001778 = '\x01';
    }
    if (DAT_4000143a == 1) {
      DAT_40001779 = '\x01';
    }
    if (DAT_4000143a == 0) {
      DAT_4000177a = '\x01';
    }
    sVar5 = 0;
    if (DAT_4000143a == 3) {
      sVar5 = DAT_4000179e;
    }
    DAT_4000179e = sVar5;
    if (DAT_400017ae != '\0') {
      DAT_400017ae = '\0';
      DAT_40001778 = '\0';
      DAT_40001779 = '\0';
      DAT_4000177a = '\0';
    }
  }
  else if (DAT_4000179e == 5) {
    if ((DAT_40001840 & 0x2000) == 0) {
      DAT_4000179e = 0;
    }
    else if ((DAT_40001844 & 0x2000) == 0) {
      REG_SIU_GPDO193 = 0;
    }
    else {
      REG_SIU_GPDO193 = 1;
    }
  }
  else if (DAT_4000179e == 2) {
    ramp_selector_position();
    uVar6 = get_shift_lever_pos_raw___();
    FUN_00057430(DAT_400017d2,uVar6,1);
    DAT_4000179e = 3;
    DAT_40001798 = (ushort)DAT_40009013 * 0x28;
    DAT_4000179a = (ushort)DAT_40009004 * 0x28;
  }
  else if (DAT_4000179e == 3) {
    ramp_selector_position();
    uVar6 = get_shift_lever_pos_raw___();
    FUN_00057430(DAT_400017d2,uVar6,0);
    uVar4 = get_shift_lever_pos_raw___();
    if (((uVar4 & 0xffff) < (uint)DAT_40001438 + (uint)DAT_40009012) &&
       (uVar4 = get_shift_lever_pos_raw___(),
       (int)((uint)DAT_40001438 - (uint)DAT_40009012) < (int)(uVar4 & 0xffff))) {
      bVar1 = DAT_40001798 == 0;
      DAT_40001798 = DAT_40001798 + -1;
      if (bVar1) {
        DAT_40001798 = 0;
      }
      DAT_4000179a = (ushort)DAT_40009004 * 0x28;
    }
    else {
      DAT_40001798 = (ushort)DAT_40009013 * 0x28;
      if (DAT_4000179a == 0) {
        DAT_400017aa = 1;
        DAT_4000179e = 6;
        DAT_40001938 = DAT_40001938 | 1;
      }
      else {
        DAT_4000179a = DAT_4000179a + -1;
      }
    }
    if ((DAT_40001798 == 0) && (DAT_40001bfe == '\0')) {
      DAT_4000179e = 0;
      DAT_4000143e = (ushort)DAT_40009009 * 4 + (ushort)DAT_40009009;
      DAT_400017a2 = (byte)DAT_40001438;
      REG_SIU_GPDO193 = 1;
    }
    bVar3 = REG_SIU_GPDI94;
    bVar2 = REG_SIU_GPDI85;
    DAT_4000143a = bVar3 << 1 | bVar2;
    if (DAT_4000143a == 2) {
      DAT_4000177b = DAT_4000177b + 1;
      if (9 < DAT_4000177b) {
        DAT_4000177b = 0;
        DAT_40001778 = '\x01';
        DAT_400017ad = 1;
      }
    }
    else {
      DAT_4000177b = 0;
    }
    if (DAT_4000143a == 1) {
      DAT_4000177d = DAT_4000177d + 1;
      if (9 < DAT_4000177d) {
        DAT_4000177d = 0;
        DAT_40001779 = '\x01';
        DAT_400017ac = 1;
      }
    }
    else {
      DAT_4000177d = 0;
    }
    if (DAT_4000143a == 0) {
      DAT_4000177c = DAT_4000177c + 1;
      if (9 < DAT_4000177c) {
        DAT_4000177c = 0;
        DAT_4000177a = '\x01';
        DAT_400017ab = 1;
      }
    }
    else {
      DAT_4000177c = 0;
    }
    if ((DAT_4000143a != 3) &&
       (((DAT_40001778 != '\0' || (DAT_40001779 != '\0')) || (DAT_4000177a != '\0')))) {
      DAT_4000179e = 0;
    }
    if (DAT_400017ae != '\0') {
      DAT_400017ae = '\0';
      DAT_40001778 = '\0';
      DAT_40001779 = '\0';
      DAT_4000177a = '\0';
    }
  }
  else if (DAT_4000179e == 6) {
    FUN_00057254();
  }
  DAT_40001866 = (char)((ulonglong)(LZCOUNT(DAT_4000179e + -5) << 0x20) >> 0x25);
  return;
}



void copyCOD2RAM___(void)

{
  byte bVar1;
  
  for (bVar1 = 0; bVar1 < 64; bVar1 = bVar1 + 1) {
    COD_unknown[bVar1] = *(byte *)(bVar1 + 0x1c000);
  }
  return;
}



void commit_coding_to_flash(void)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  
  if (tach_rpm == 0) {
    bVar1 = REG_INTC_PSR170;
    bVar3 = REG_INTC_PSR171;
    bVar2 = REG_INTC_PSR170;
    REG_INTC_PSR170 = bVar2 & 0xf0;
    bVar2 = REG_INTC_PSR171;
    REG_INTC_PSR171 = bVar2 & 0xf0;
    EEPROM_erase_coding();
    if ((DAT_400017e8 & 8) == 0) {
      flash_write_cod_data(0x1c000,COD_unknown,64);
    }
    bVar2 = REG_INTC_PSR170;
    REG_INTC_PSR170 = bVar1 & 0xf | bVar2 & 0xf0;
    bVar1 = REG_INTC_PSR171;
    REG_INTC_PSR171 = bVar3 & 0xf | bVar1 & 0xf0;
    if ((DAT_400017e8 & 1) != 0) {
      FUN_00055ff8();
    }
    DAT_400017e8 = 0;
  }
  return;
}



void FUN_000582fc(byte *param_1,char param_2)

{
  if (tach_rpm == 0) {
    if (param_2 == '\0') {
      COD_unknown[3] = *param_1;
      COD_unknown[2] = param_1[1];
      COD_unknown[1] = param_1[2];
      COD_unknown[0] = param_1[3];
      COD_unknown[7] = param_1[4];
      COD_unknown[6] = param_1[5];
      COD_unknown[5] = param_1[6];
      COD_unknown[4] = param_1[7];
    }
    else {
      COD_unknown[3] = param_1[7];
      COD_unknown[2] = param_1[6];
      COD_unknown[1] = param_1[5];
      COD_unknown[0] = param_1[4];
      COD_unknown[7] = param_1[3];
      COD_unknown[6] = param_1[2];
      COD_unknown[5] = param_1[1];
      COD_unknown[4] = *param_1;
    }
    DAT_400017e8 = DAT_400017e8 | 1;
    FUN_00058440();
  }
  return;
}



void FUN_00058440(void)

{
  FUN_000586bc();
  DAT_40001c6e = DAT_40009050;
  DAT_40001c6c = DAT_40009052;
  DAT_40001c6a = DAT_40009054;
  DAT_40001c68 = DAT_40009056;
  DAT_40001c66 = DAT_40009058;
  DAT_40001c64 = DAT_4000905a;
  DAT_40001c62 = DAT_4000905c;
  DAT_40001c60 = DAT_4000905e;
  DAT_40001c5e = DAT_40009060;
  DAT_40001c5c = DAT_40009062;
  DAT_40001c5a = DAT_40009064;
  DAT_40001c58 = DAT_40009066;
  init_obd_ii_config();
  return;
}



void FUN_00058524(void)

{
  byte bVar1;
  undefined1 local_10;
  undefined1 local_f;
  undefined1 local_e;
  undefined1 local_d;
  undefined1 local_c;
  undefined1 local_b;
  undefined1 local_a;
  undefined1 local_9;
  
  local_10 = DAT_00001cf0;
  local_f = DAT_00001cf1;
  local_e = DAT_00001cf2;
  local_d = DAT_00001cf3;
  local_c = DAT_00001cf4;
  local_b = DAT_00001cf5;
  local_a = DAT_00001cf6;
  local_9 = DAT_00001cf7;
  if (tcu_unlocked) {
    if (DAT_400017d8 == '\x01') {
      DAT_400017d8 = '\0';
      FUN_000582fc(&DAT_400017e0,1);
    }
    else if (DAT_400017d8 == '\x02') {
      DAT_400017d8 = '\0';
      FUN_000582fc(&local_10,1);
    }
    else if (DAT_400017d8 == '\x03') {
      DAT_400017d8 = '\0';
      for (bVar1 = 0; bVar1 < 0x11; bVar1 = bVar1 + 1) {
        COD_unknown[bVar1 + 8] = 0xff;
      }
      DAT_400017e8 = DAT_400017e8 | 2;
    }
    else if (DAT_400017d8 == '\x04') {
      DAT_400017d8 = '\0';
      for (bVar1 = 0; bVar1 < 0x20; bVar1 = bVar1 + 1) {
        COD_unknown[bVar1 + 0x20] = 0xff;
      }
      DAT_400017e8 = DAT_400017e8 | 4;
    }
    else if (DAT_400017d8 == '\x05') {
      DAT_400017d8 = '\0';
      DAT_400017e8 = DAT_400017e8 | 8;
    }
  }
  else {
    DAT_400017d8 = '\0';
  }
  return;
}



void FUN_000586bc(void)

{
  if (((((((uint)COD_unknown._4_4_ >> 0xe & 1) == 0) || (((uint)COD_unknown._0_4_ >> 0xd & 7) != 1))
       || (((uint)COD_unknown._4_4_ >> 9 & 1) == 0)) ||
      ((((uint)COD_unknown._0_4_ >> 0x16 & 7) != 3 || (((uint)COD_unknown._4_4_ >> 0x15 & 3) != 0)))
      ) || ((((uint)COD_unknown._0_4_ >> 0x10 & 1) != 0 ||
            ((((uint)COD_unknown._4_4_ >> 0xb & 1) == 0 ||
             (((uint)COD_unknown._4_4_ >> 0xc & 1) == 0)))))) {
    DAT_400017e9 = 0;
    DAT_400019e8 = DAT_400019e8 | 8;
  }
  else {
    DAT_400017e9 = 1;
  }
  return;
}



void FUN_00058798(void)

{
  DAT_400017f0 = 0;
  DAT_400017f1 = 7;
  DAT_400017f2 = 0x80;
  DAT_400017f3 = 0x1f;
  DAT_400017f4 = 0xf0;
  DAT_400017f5 = 0x88;
  DAT_400017f6 = 0;
  DAT_400017f7 = 0xf;
  DAT_400017f8 = 0x80;
  DAT_400017f9 = 0;
  DAT_400017fa = 0;
  DAT_400017fb = 0xb;
  DAT_400017fc = 0xb0;
  DAT_400017fd = 0x40;
  DAT_400017fe = 0x8f;
  DAT_400017ff = 0xff;
  DAT_40001800 = 0xff;
  DAT_40001801 = 0xff;
  DAT_40001802 = 0xff;
  DAT_40001803 = 0xff;
  DAT_40001804 = 0xfe;
  DAT_40001805 = 0;
  DAT_40001806 = 0xff;
  DAT_40001807 = 0;
  DAT_40001808 = 0;
  DAT_40001809 = 0;
  DAT_4000180a = 0;
  DAT_4000180b = 0;
  DAT_4000180c = 0;
  DAT_4000180d = 0;
  DAT_4000180e = 0;
  DAT_4000180f = 0;
  DAT_40001810 = 0xff;
  DAT_40001811 = 0xff;
  DAT_40001812 = 0xff;
  DAT_40001813 = 0xff;
  DAT_40001814 = 0xff;
  DAT_40001815 = 0xff;
  DAT_40001816 = 0xff;
  DAT_40001817 = 0xff;
  DAT_40001818 = 0xff;
  DAT_40001819 = 0xff;
  DAT_4000181a = 0xfc;
  DAT_4000181b = 0;
  return;
}



void obd_ii_mode22_processing(void)

{
  ulonglong uVar1;
  undefined2 uVar2;
  ushort uVar3;
  
  obd_ii_response[0] = 0x62;
  obd_ii_response[1] = obd_ii_request[2];
  uVar3 = 3;
  obd_ii_response[2] = obd_ii_request[3];
  switch((ushort)obd_ii_request[2] * 0x100 + (ushort)obd_ii_request[3]) {
  case 0x200:
    obd_ii_response[3] = DAT_400017f0;
    obd_ii_response[4] = DAT_400017f1;
    obd_ii_response[5] = DAT_400017f2;
    uVar3 = 7;
    obd_ii_response[6] = DAT_400017f3;
    break;
  case 0x20e:
    obd_ii_response[3] = DAT_00000800._0_1_;
    obd_ii_response[4] = DAT_00000800._1_1_;
    obd_ii_response[5] = DAT_00000800._2_1_;
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_00000800;
    break;
  case 0x20f:
    obd_ii_response[3] = DAT_00000812;
    obd_ii_response[4] = DAT_00000813;
    obd_ii_response[5] = DAT_00000816;
    uVar3 = 7;
    obd_ii_response[6] = DAT_00000817;
    break;
  case 0x210:
    obd_ii_response[3] = DAT_00000808;
    obd_ii_response[4] = DAT_00000809;
    obd_ii_response[5] = DAT_0000080a;
    uVar3 = 7;
    obd_ii_response[6] = DAT_0000080b;
    break;
  case 0x211:
    obd_ii_response[3] = DAT_0000081b;
    obd_ii_response[4] = DAT_0000081c;
    obd_ii_response[5] = DAT_0000081d;
    uVar3 = 7;
    obd_ii_response[6] = DAT_0000081e;
    break;
  case 0x21c:
    obd_ii_response[3] = CAL_version_string[0x20];
    obd_ii_response[4] = CAL_version_string[0x21];
    obd_ii_response[5] = CAL_version_string[0x22];
    uVar3 = 7;
    obd_ii_response[6] = CAL_version_string[0x23];
    break;
  case 0x21d:
    obd_ii_response[3] = CAL_version_string[0x24];
    obd_ii_response[4] = CAL_version_string[0x25];
    obd_ii_response[5] = CAL_version_string[0x26];
    uVar3 = 7;
    obd_ii_response[6] = CAL_version_string[0x27];
    break;
  case 0x21e:
    obd_ii_response[3] = CAL_version_string[0x28];
    obd_ii_response[4] = CAL_version_string[0x29];
    obd_ii_response[5] = CAL_version_string[0x2a];
    uVar3 = 7;
    obd_ii_response[6] = CAL_version_string[0x2b];
    break;
  case 0x21f:
    obd_ii_response[3] = CAL_version_string[0x2c];
    obd_ii_response[4] = CAL_version_string[0x2d];
    obd_ii_response[5] = CAL_version_string[0x2e];
    uVar3 = 7;
    obd_ii_response[6] = CAL_version_string[0x2f];
    break;
  case 0x220:
    obd_ii_response[3] = DAT_400017f4;
    obd_ii_response[4] = DAT_400017f5;
    obd_ii_response[5] = DAT_400017f6;
    uVar3 = 7;
    obd_ii_response[6] = DAT_400017f7;
    break;
  case 0x221:
    obd_ii_response[3] = CAL_version_string[0x30];
    obd_ii_response[4] = CAL_version_string[0x31];
    obd_ii_response[5] = CAL_version_string[0x32];
    uVar3 = 7;
    obd_ii_response[6] = CAL_version_string[0x33];
    break;
  case 0x222:
    obd_ii_response[3] = CAL_version_string[0x34];
    obd_ii_response[4] = CAL_version_string[0x35];
    obd_ii_response[5] = CAL_version_string[0x36];
    uVar3 = 7;
    obd_ii_response[6] = CAL_version_string[0x37];
    break;
  case 0x223:
    obd_ii_response[3] = CAL_version_string[0x38];
    obd_ii_response[4] = CAL_version_string[0x39];
    obd_ii_response[5] = CAL_version_string[0x3a];
    uVar3 = 7;
    obd_ii_response[6] = CAL_version_string[0x3b];
    break;
  case 0x224:
    obd_ii_response[3] = CAL_version_string[0x3c];
    obd_ii_response[4] = CAL_version_string[0x3d];
    obd_ii_response[5] = CAL_version_string[0x3e];
    uVar3 = 7;
    obd_ii_response[6] = CAL_version_string[0x3f];
    break;
  case 0x229:
    obd_ii_response[3] = (byte)((uint)DAT_400013b8 >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_400013b8 >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_400013b8 >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_400013b8;
    break;
  case 0x22d:
    obd_ii_response[3] = (byte)((ushort)DAT_40001510 >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40001510;
    break;
  case 0x23d:
    obd_ii_response[3] = (byte)((ushort)DAT_40001706 >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40001706;
    break;
  case 0x23e:
    obd_ii_response[3] = (byte)((ushort)DAT_40001704 >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40001704;
    break;
  case 0x23f:
    obd_ii_response[3] = (byte)((ushort)DAT_4000170a >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_4000170a;
    break;
  case 0x240:
    obd_ii_response[3] = DAT_400017f8;
    obd_ii_response[4] = DAT_400017f9;
    obd_ii_response[5] = DAT_400017fa;
    uVar3 = 7;
    obd_ii_response[6] = DAT_400017fb;
    break;
  case 0x241:
    obd_ii_response[3] = (byte)((ushort)DAT_40001708 >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40001708;
    break;
  case 0x25d:
                    // sport_button???
    if (((uint)COD_unknown._4_4_ >> 0x17 & 1) == 0) {
      uVar3 = 4;
      obd_ii_response[3] = 3;
    }
    else if ((paddle_shift_flags & 0x80) == 0) {
      uVar3 = 4;
      obd_ii_response[3] = 0;
    }
    else {
      uVar3 = 4;
      obd_ii_response[3] = 1;
    }
    break;
  case 0x25f:
                    // brake_switch
    if ((DAT_4000171e & 0x80) == 0) {
      if ((DAT_4000171e & 0x40) == 0) {
        uVar3 = 4;
        obd_ii_response[3] = 0;
      }
      else {
        uVar3 = 4;
        obd_ii_response[3] = 1;
      }
    }
    else {
      uVar3 = 4;
      obd_ii_response[3] = 2;
    }
    break;
  case 0x260:
    obd_ii_response[3] = DAT_400017fc;
    obd_ii_response[4] = DAT_400017fd;
    obd_ii_response[5] = DAT_400017fe;
    uVar3 = 7;
    obd_ii_response[6] = DAT_400017ff;
    break;
  case 0x261:
                    // cruise_status??
    if (((uint)COD_unknown._0_4_ >> 0x19 & 7) == 0) {
      uVar3 = 4;
      obd_ii_response[3] = 4;
    }
    else if ((driver_input_flags[1] & 0xc) == 4) {
      uVar3 = 4;
      obd_ii_response[3] = 1;
    }
    else if ((driver_input_flags[1] & 0xc) == 8) {
      uVar3 = 4;
      obd_ii_response[3] = 2;
    }
    else if ((driver_input_flags[1] & 0xc) == 0xc) {
      uVar3 = 4;
      obd_ii_response[3] = 3;
    }
    else {
      uVar3 = 4;
      obd_ii_response[3] = 0;
    }
    break;
  case 0x263:
    obd_ii_response[3] = COD_unknown[7];
    obd_ii_response[4] = COD_unknown[6];
    obd_ii_response[5] = COD_unknown[5];
    uVar3 = 7;
    obd_ii_response[6] = COD_unknown[4];
    break;
  case 0x264:
    obd_ii_response[3] = COD_unknown[3];
    obd_ii_response[4] = COD_unknown[2];
    obd_ii_response[5] = COD_unknown[1];
    uVar3 = 7;
    obd_ii_response[6] = COD_unknown[0];
    break;
  case 0x26a:
    obd_ii_response[3] = (byte)(engine_torque >> 8);
    obd_ii_response[4] = (byte)engine_torque;
    uVar3 = 5;
    break;
  case 0x271:
    uVar3 = 4;
    obd_ii_response[3] = selector_position_learned_status;
    break;
  case 0x275:
    uVar3 = 4;
    obd_ii_response[3] = oil_temp_unknown;
    break;
  case 0x276:
    uVar3 = 4;
    obd_ii_response[3] = ips_gear_cur;
    break;
  case 0x277:
    obd_ii_response[3] = (byte)(tach_rpm >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)tach_rpm;
    break;
  case 0x278:
                    // gear request
    uVar3 = 4;
    obd_ii_response[3] = gear_request;
    break;
  case 0x279:
    obd_ii_response[3] = (byte)(input_shaft_rpm >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)input_shaft_rpm;
    break;
  case 0x27a:
    obd_ii_response[3] = (byte)(output_shaft_rpm >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)output_shaft_rpm;
    break;
  case 0x27b:
    if ((DAT_40001678 & 0x40) == 0) {
      if (discrete_input_state == '\0') {
        uVar3 = 4;
        obd_ii_response[3] = 0;
      }
      else {
        uVar3 = 4;
        obd_ii_response[3] = 1;
      }
    }
    else {
      uVar3 = 4;
      obd_ii_response[3] = 2;
    }
    break;
  case 0x27c:
    if ((DAT_40001678 & 0x80) == 0) {
      if (DAT_400023a1 == '\0') {
        uVar3 = 4;
        obd_ii_response[3] = 0;
      }
      else {
        uVar3 = 4;
        obd_ii_response[3] = 1;
      }
    }
    else {
      uVar3 = 4;
      obd_ii_response[3] = 2;
    }
    break;
  case 0x27d:
    if ((DAT_40001678 & 0x100) == 0) {
      if (DAT_400023a2 == '\0') {
        uVar3 = 4;
        obd_ii_response[3] = 0;
      }
      else {
        uVar3 = 4;
        obd_ii_response[3] = 1;
      }
    }
    else {
      uVar3 = 4;
      obd_ii_response[3] = 2;
    }
    break;
  case 0x27e:
    if (DAT_40002374 < 0x10000) {
      obd_ii_response[3] = (byte)(DAT_40002374 >> 8);
      uVar3 = 5;
      obd_ii_response[4] = (byte)DAT_40002374;
    }
    else {
      obd_ii_response[3] = 0xff;
      uVar3 = 5;
      obd_ii_response[4] = 0xff;
    }
    break;
  case 0x27f:
    if (DAT_40002358 < 0x10000) {
      obd_ii_response[3] = (byte)(DAT_40002358 >> 8);
      uVar3 = 5;
      obd_ii_response[4] = (byte)DAT_40002358;
    }
    else {
      obd_ii_response[3] = 0xff;
      uVar3 = 5;
      obd_ii_response[4] = 0xff;
    }
    break;
  case 0x280:
    obd_ii_response[3] = DAT_40001800;
    obd_ii_response[4] = DAT_40001801;
    obd_ii_response[5] = DAT_40001802;
    uVar3 = 7;
    obd_ii_response[6] = DAT_40001803;
    break;
  case 0x281:
                    // current dura position
    uVar1 = get_shift_lever_pos_raw___();
    obd_ii_response[3] = (byte)((uVar1 & 0xffff) >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)(uVar1 & 0xffff);
    break;
  case 0x282:
    obd_ii_response[3] = (byte)((ushort)DAT_40002bda >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40002bda;
    break;
  case 0x283:
    obd_ii_response[3] = (byte)((ushort)DAT_40002bd8 >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40002bd8;
    break;
  case 0x284:
    obd_ii_response[3] = (byte)((ushort)DAT_40002bd6 >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40002bd6;
    break;
  case 0x285:
    obd_ii_response[3] = (byte)((ushort)DAT_40002bd4 >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40002bd4;
    break;
  case 0x286:
    if ((shift_position_request_bits & 0x10) == 0) {
      if ((shift_position_request_bits & 1) == 0) {
        uVar3 = 4;
        obd_ii_response[3] = 0;
      }
      else {
        uVar3 = 4;
        obd_ii_response[3] = 1;
      }
    }
    else {
      uVar3 = 4;
      obd_ii_response[3] = 2;
    }
    break;
  case 0x287:
    if ((shift_position_request_bits & 0x20) == 0) {
      if ((shift_position_request_bits & 2) == 0) {
        uVar3 = 4;
        obd_ii_response[3] = 0;
      }
      else {
        uVar3 = 4;
        obd_ii_response[3] = 1;
      }
    }
    else {
      uVar3 = 4;
      obd_ii_response[3] = 2;
    }
    break;
  case 0x288:
    if ((shift_position_request_bits & 0x40) == 0) {
      if ((shift_position_request_bits & 4) == 0) {
        uVar3 = 4;
        obd_ii_response[3] = 0;
      }
      else {
        uVar3 = 4;
        obd_ii_response[3] = 1;
      }
    }
    else {
      uVar3 = 4;
      obd_ii_response[3] = 2;
    }
    break;
  case 0x289:
    if ((shift_position_request_bits & 0x80) == 0) {
      if ((shift_position_request_bits & 8) == 0) {
        uVar3 = 4;
        obd_ii_response[3] = 0;
      }
      else {
        uVar3 = 4;
        obd_ii_response[3] = 1;
      }
    }
    else {
      uVar3 = 4;
      obd_ii_response[3] = 2;
    }
    break;
  case 0x28a:
                    // park switch
    if (((DAT_40002d28 & 8) == 0) || ((DAT_40002d28 & 4) == 0)) {
      if ((uint)((int)(uint)DAT_40001dbc >> 4) < 0x200) {
        uVar3 = 4;
        obd_ii_response[3] = 1;
      }
      else {
        uVar3 = 4;
        obd_ii_response[3] = 0;
      }
    }
    else {
      uVar3 = 4;
      obd_ii_response[3] = 2;
    }
    break;
  case 0x28b:
                    // reverse switch
    if (((DAT_40002d22 & 8) == 0) || ((DAT_40002d22 & 4) == 0)) {
      if ((uint)((int)(uint)DAT_40001dc0 >> 4) < 0x200) {
        uVar3 = 4;
        obd_ii_response[3] = 1;
      }
      else {
        uVar3 = 4;
        obd_ii_response[3] = 0;
      }
    }
    else {
      uVar3 = 4;
      obd_ii_response[3] = 2;
    }
    break;
  case 0x28c:
                    // neutral switch
    if (((DAT_40002d2b & 8) == 0) || ((DAT_40002d2b & 4) == 0)) {
      if ((uint)((int)(uint)DAT_40001dbe >> 4) < 0x200) {
        uVar3 = 4;
        obd_ii_response[3] = 1;
      }
      else {
        uVar3 = 4;
        obd_ii_response[3] = 0;
      }
    }
    else {
      uVar3 = 4;
      obd_ii_response[3] = 2;
    }
    break;
  case 0x28d:
                    // drive switch
    if (((DAT_40002d3a & 8) == 0) || ((DAT_40002d3a & 4) == 0)) {
      if ((uint)((int)(uint)DAT_40001dc2 >> 4) < 0x200) {
        uVar3 = 4;
        obd_ii_response[3] = 1;
      }
      else {
        uVar3 = 4;
        obd_ii_response[3] = 0;
      }
    }
    else {
      uVar3 = 4;
      obd_ii_response[3] = 2;
    }
    break;
  case 0x28e:
                    // gear ratio
    if (DAT_40001a40 < 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = (undefined2)DAT_40001a40;
      if (0xffff < DAT_40001a40) {
        uVar2 = 0xffff;
      }
    }
    obd_ii_response[3] = (byte)((ushort)uVar2 >> 8);
    obd_ii_response[4] = (byte)uVar2;
    uVar3 = 5;
    break;
  case 0x28f:
    if ((DAT_400018bf & 2) == 0) {
      if ((DAT_400018bf & 1) == 0) {
        uVar3 = 4;
        obd_ii_response[3] = 0;
      }
      else {
        uVar3 = 4;
        obd_ii_response[3] = 1;
      }
    }
    else {
      uVar3 = 4;
      obd_ii_response[3] = 2;
    }
    break;
  case 0x290:
    uVar3 = 4;
    obd_ii_response[3] = shift_adapt_inhibit;
    break;
  case 0x291:
    uVar3 = 4;
    obd_ii_response[3] = slip_learn_status_flags_gear6;
    break;
  case 0x292:
    uVar3 = 4;
    obd_ii_response[3] = DAT_40001ad2;
    break;
  case 0x293:
    uVar3 = 4;
    obd_ii_response[3] = DAT_40001ad3;
    break;
  case 0x294:
    uVar3 = 4;
    obd_ii_response[3] = input_shaft_load;
    break;
  case 0x295:
    uVar3 = 4;
    obd_ii_response[3] = DAT_4000148e;
    break;
  case 0x296:
    uVar3 = 4;
    obd_ii_response[3] = DAT_4000148f;
    break;
  case 0x297:
                    // torque converter slip
    uVar1 = int_abs((ulonglong)(uint)((int)(uint)tach_rpm >> 2) - (ulonglong)input_shaft_rpm);
    obd_ii_response[3] = (byte)((uVar1 & 0xffff) >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)(uVar1 & 0xffff);
    break;
  case 0x298:
    obd_ii_response[3] = (byte)((ushort)solenoid_SL_dutycycle >> 8);
    obd_ii_response[4] = (byte)solenoid_SL_dutycycle;
    uVar3 = 5;
    break;
  case 0x299:
    obd_ii_response[3] = (byte)((ushort)solenoid_SL1_dutycycle >> 8);
    obd_ii_response[4] = (byte)solenoid_SL1_dutycycle;
    uVar3 = 5;
    break;
  case 0x29a:
    obd_ii_response[3] = (byte)((ushort)solenoid_SL2_dutycycle >> 8);
    obd_ii_response[4] = (byte)solenoid_SL2_dutycycle;
    uVar3 = 5;
    break;
  case 0x29b:
    obd_ii_response[3] = (byte)((ushort)solenoid_SL3_dutycycle >> 8);
    obd_ii_response[4] = (byte)solenoid_SL3_dutycycle;
    uVar3 = 5;
    break;
  case 0x29c:
    obd_ii_response[3] = (byte)((ushort)solenoid_SL4_dutycycle >> 8);
    obd_ii_response[4] = (byte)solenoid_SL4_dutycycle;
    uVar3 = 5;
    break;
  case 0x29d:
    obd_ii_response[3] = (byte)((ushort)solenoid_SLT_dutycycle >> 8);
    obd_ii_response[4] = (byte)solenoid_SLT_dutycycle;
    uVar3 = 5;
    break;
  case 0x29e:
    obd_ii_response[3] = (byte)((ushort)solenoid_SLU_dutycycle >> 8);
    obd_ii_response[4] = (byte)solenoid_SLU_dutycycle;
    uVar3 = 5;
    break;
  case 0x29f:
    obd_ii_response[3] = (byte)((ushort)solenoid_SL_demand >> 8);
    obd_ii_response[4] = (byte)solenoid_SL_demand;
    uVar3 = 5;
    break;
  case 0x2a0:
    obd_ii_response[3] = DAT_40001804;
    obd_ii_response[4] = DAT_40001805;
    obd_ii_response[5] = DAT_40001806;
    uVar3 = 7;
    obd_ii_response[6] = DAT_40001807;
    break;
  case 0x2a1:
    obd_ii_response[3] = (byte)((ushort)solenoid_SL1_demand >> 8);
    obd_ii_response[4] = (byte)solenoid_SL1_demand;
    uVar3 = 5;
    break;
  case 0x2a2:
    obd_ii_response[3] = (byte)((ushort)solenoid_SL2_demand >> 8);
    obd_ii_response[4] = (byte)solenoid_SL2_demand;
    uVar3 = 5;
    break;
  case 0x2a3:
    obd_ii_response[3] = (byte)((ushort)solenoid_SL3_demand >> 8);
    obd_ii_response[4] = (byte)solenoid_SL3_demand;
    uVar3 = 5;
    break;
  case 0x2a4:
    obd_ii_response[3] = (byte)((ushort)solenoid_SL4_demand >> 8);
    obd_ii_response[4] = (byte)solenoid_SL4_demand;
    uVar3 = 5;
    break;
  case 0x2a5:
    obd_ii_response[3] = (byte)((ushort)solenoid_SLT_demand >> 8);
    obd_ii_response[4] = (byte)solenoid_SLT_demand;
    uVar3 = 5;
    break;
  case 0x2a6:
    obd_ii_response[3] = (byte)((ushort)solenoid_SLU_demand >> 8);
    obd_ii_response[4] = (byte)solenoid_SLU_demand;
    uVar3 = 5;
    break;
  case 0x2a7:
    obd_ii_response[3] = FUN_0004ca5c();
    uVar3 = 4;
    break;
  case 0x2b0:
    uVar3 = 4;
    obd_ii_response[3] = LEA_shift_adaptation_history_valid;
    break;
  case 0x2b1:
    obd_ii_response[3] = (byte)(LEA_shift_adaptation >> 8);
    obd_ii_response[4] = (byte)LEA_shift_adaptation;
    uVar3 = 5;
    break;
  case 0x2b2:
    uVar3 = 4;
    obd_ii_response[3] = shift_adapt_phase_unknown2;
    break;
  case 0x2b4:
    uVar3 = 4;
    obd_ii_response[3] = DAT_400090cd;
    break;
  case 0x2b5:
    uVar3 = 4;
    obd_ii_response[3] = DAT_400090cf;
    break;
  case 0x2b6:
    obd_ii_response[3] = (byte)(u16_rspeed_rpm_ARRAY_400090d0[0] / 100);
    uVar3 = 4;
    break;
  case 0x2b7:
    obd_ii_response[3] = (byte)(u16_rspeed_rpm_ARRAY_400090d0[1] / 100);
    uVar3 = 4;
    break;
  case 0x2c0:
    obd_ii_response[3] = DAT_40001808;
    obd_ii_response[4] = DAT_40001809;
    obd_ii_response[5] = DAT_4000180a;
    uVar3 = 7;
    obd_ii_response[6] = DAT_4000180b;
    break;
  case 0x2e0:
    obd_ii_response[3] = DAT_4000180c;
    obd_ii_response[4] = DAT_4000180d;
    obd_ii_response[5] = DAT_4000180e;
    uVar3 = 7;
    obd_ii_response[6] = DAT_4000180f;
    break;
  case 0x300:
    obd_ii_response[3] = 0;
    obd_ii_response[4] = 0;
    obd_ii_response[5] = 0;
    uVar3 = 7;
    obd_ii_response[6] = 1;
    break;
  case 800:
    obd_ii_response[3] = 0;
    obd_ii_response[4] = 0;
    obd_ii_response[5] = 0;
    uVar3 = 7;
    obd_ii_response[6] = 1;
    break;
  case 0x340:
    obd_ii_response[3] = 0;
    obd_ii_response[4] = 0;
    obd_ii_response[5] = 0;
    uVar3 = 7;
    obd_ii_response[6] = 1;
    break;
  case 0x360:
    obd_ii_response[3] = 0;
    obd_ii_response[4] = 0;
    obd_ii_response[5] = 0;
    uVar3 = 7;
    obd_ii_response[6] = 1;
    break;
  case 0x380:
    obd_ii_response[3] = 0;
    obd_ii_response[4] = 0;
    obd_ii_response[5] = 0;
    uVar3 = 7;
    obd_ii_response[6] = 1;
    break;
  case 0x3a0:
    obd_ii_response[3] = 0;
    obd_ii_response[4] = 0;
    obd_ii_response[5] = 0;
    uVar3 = 7;
    obd_ii_response[6] = 1;
    break;
  case 0x3c0:
    obd_ii_response[3] = 0;
    obd_ii_response[4] = 0;
    obd_ii_response[5] = 0;
    uVar3 = 7;
    obd_ii_response[6] = 1;
    break;
  case 0x3e0:
    obd_ii_response[3] = 0;
    obd_ii_response[4] = 0;
    obd_ii_response[5] = 0;
    uVar3 = 7;
    obd_ii_response[6] = 1;
    break;
  case 0x400:
    obd_ii_response[3] = DAT_40001810;
    obd_ii_response[4] = DAT_40001811;
    obd_ii_response[5] = DAT_40001812;
    uVar3 = 7;
    obd_ii_response[6] = DAT_40001813;
    break;
  case 0x401:
    obd_ii_response[3] = (byte)((uint)DAT_40002ddc >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002ddc >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002ddc >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002ddc;
    break;
  case 0x402:
    obd_ii_response[3] = (byte)((uint)DAT_40002de0 >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002de0 >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002de0 >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002de0;
    break;
  case 0x403:
    obd_ii_response[3] = (byte)((uint)DAT_40002de4 >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002de4 >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002de4 >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002de4;
    break;
  case 0x404:
    obd_ii_response[3] = (byte)((uint)DAT_40002de8 >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002de8 >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002de8 >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002de8;
    break;
  case 0x405:
    obd_ii_response[3] = (byte)((uint)DAT_40002dec >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002dec >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002dec >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002dec;
    break;
  case 0x406:
    obd_ii_response[3] = (byte)((uint)DAT_40002df0 >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002df0 >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002df0 >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002df0;
    break;
  case 0x407:
    obd_ii_response[3] = (byte)((uint)DAT_40002df4 >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002df4 >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002df4 >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002df4;
    break;
  case 0x408:
    obd_ii_response[3] = (byte)((uint)DAT_40002df8 >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002df8 >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002df8 >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002df8;
    break;
  case 0x409:
    obd_ii_response[3] = (byte)((uint)DAT_40002dfc >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002dfc >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002dfc >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002dfc;
    break;
  case 0x40a:
    obd_ii_response[3] = (byte)((uint)DAT_40002e00 >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002e00 >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002e00 >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002e00;
    break;
  case 0x40b:
    obd_ii_response[3] = (byte)((uint)DAT_40002e04 >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002e04 >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002e04 >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002e04;
    break;
  case 0x40c:
    obd_ii_response[3] = (byte)((uint)DAT_40002e08 >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002e08 >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002e08 >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002e08;
    break;
  case 0x40d:
    obd_ii_response[3] = (byte)((uint)DAT_40002e0c >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002e0c >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002e0c >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002e0c;
    break;
  case 0x40e:
    obd_ii_response[3] = (byte)((uint)DAT_40002e10 >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002e10 >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002e10 >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002e10;
    break;
  case 0x40f:
    obd_ii_response[3] = (byte)((uint)DAT_40002e14 >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002e14 >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002e14 >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002e14;
    break;
  case 0x410:
    obd_ii_response[3] = (byte)((uint)DAT_40002e18 >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002e18 >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002e18 >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002e18;
    break;
  case 0x411:
    obd_ii_response[3] = (byte)((uint)DAT_40002e1c >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002e1c >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002e1c >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002e1c;
    break;
  case 0x412:
    obd_ii_response[3] = (byte)((uint)DAT_40002e20 >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002e20 >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002e20 >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002e20;
    break;
  case 0x413:
    obd_ii_response[3] = (byte)((uint)DAT_40002e24 >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002e24 >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002e24 >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002e24;
    break;
  case 0x414:
    uVar3 = 4;
    obd_ii_response[3] = DAT_40002e28;
    break;
  case 0x415:
    uVar3 = 4;
    obd_ii_response[3] = DAT_40002e29;
    break;
  case 0x416:
    uVar3 = 4;
    obd_ii_response[3] = DAT_40002e2a;
    break;
  case 0x417:
    uVar3 = 4;
    obd_ii_response[3] = DAT_40002e2b;
    break;
  case 0x418:
    obd_ii_response[3] = (byte)(u16_rspeed_rpm_ARRAY_40002e84[0] >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)u16_rspeed_rpm_ARRAY_40002e84[0];
    break;
  case 0x419:
    obd_ii_response[3] = (byte)(u16_rspeed_rpm_ARRAY_40002e84[6] >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)u16_rspeed_rpm_ARRAY_40002e84[6];
    break;
  case 0x41a:
    obd_ii_response[3] = (byte)((ushort)DAT_40002e9c >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40002e9c;
    break;
  case 0x41b:
    obd_ii_response[3] = (byte)((ushort)DAT_40002ea8 >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40002ea8;
    break;
  case 0x41c:
    obd_ii_response[3] = (byte)((ushort)DAT_40002eb4 >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40002eb4;
    break;
  case 0x41d:
    obd_ii_response[3] = (byte)((ushort)DAT_40002ec0 >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40002ec0;
    break;
  case 0x41e:
    obd_ii_response[3] = (byte)((ushort)DAT_40002ecc >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40002ecc;
    break;
  case 0x41f:
    obd_ii_response[3] = (byte)((ushort)DAT_40002ed8 >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40002ed8;
    break;
  case 0x420:
    obd_ii_response[3] = DAT_40001814;
    obd_ii_response[4] = DAT_40001815;
    obd_ii_response[5] = DAT_40001816;
    uVar3 = 7;
    obd_ii_response[6] = DAT_40001817;
    break;
  case 0x421:
    obd_ii_response[3] = (byte)((ushort)DAT_40002ee4 >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40002ee4;
    break;
  case 0x422:
    obd_ii_response[3] = (byte)((ushort)DAT_40002ef0 >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40002ef0;
    break;
  case 0x423:
    obd_ii_response[3] = (byte)(u16_rspeed_rpm_ARRAY_40002e84[1] >> 8);
    obd_ii_response[4] = (byte)u16_rspeed_rpm_ARRAY_40002e84[1];
    uVar3 = 5;
    break;
  case 0x424:
    obd_ii_response[3] = (byte)(u16_rspeed_rpm_ARRAY_40002e84[7] >> 8);
    obd_ii_response[4] = (byte)u16_rspeed_rpm_ARRAY_40002e84[7];
    uVar3 = 5;
    break;
  case 0x425:
    obd_ii_response[3] = (byte)((ushort)DAT_40002e9e >> 8);
    obd_ii_response[4] = (byte)DAT_40002e9e;
    uVar3 = 5;
    break;
  case 0x426:
    obd_ii_response[3] = (byte)((ushort)DAT_40002eaa >> 8);
    obd_ii_response[4] = (byte)DAT_40002eaa;
    uVar3 = 5;
    break;
  case 0x427:
    obd_ii_response[3] = (byte)((ushort)DAT_40002eb6 >> 8);
    obd_ii_response[4] = (byte)DAT_40002eb6;
    uVar3 = 5;
    break;
  case 0x428:
    obd_ii_response[3] = (byte)((ushort)DAT_40002ec2 >> 8);
    obd_ii_response[4] = (byte)DAT_40002ec2;
    uVar3 = 5;
    break;
  case 0x429:
    obd_ii_response[3] = (byte)((ushort)DAT_40002ece >> 8);
    obd_ii_response[4] = (byte)DAT_40002ece;
    uVar3 = 5;
    break;
  case 0x42a:
    obd_ii_response[3] = (byte)((ushort)DAT_40002eda >> 8);
    obd_ii_response[4] = (byte)DAT_40002eda;
    uVar3 = 5;
    break;
  case 0x42b:
    obd_ii_response[3] = (byte)((ushort)DAT_40002ee6 >> 8);
    obd_ii_response[4] = (byte)DAT_40002ee6;
    uVar3 = 5;
    break;
  case 0x42c:
    obd_ii_response[3] = (byte)((ushort)DAT_40002ef2 >> 8);
    obd_ii_response[4] = (byte)DAT_40002ef2;
    uVar3 = 5;
    break;
  case 0x42d:
    uVar3 = 4;
    obd_ii_response[3] = u16_rspeed_rpm_ARRAY_40002e84[4]._0_1_;
    break;
  case 0x42e:
    uVar3 = 4;
    obd_ii_response[3] = DAT_40002e98._0_1_;
    break;
  case 0x42f:
    uVar3 = 4;
    obd_ii_response[3] = DAT_40002ea4;
    break;
  case 0x430:
    uVar3 = 4;
    obd_ii_response[3] = DAT_40002eb0;
    break;
  case 0x431:
    uVar3 = 4;
    obd_ii_response[3] = DAT_40002ebc;
    break;
  case 0x432:
    uVar3 = 4;
    obd_ii_response[3] = DAT_40002ec8;
    break;
  case 0x433:
    uVar3 = 4;
    obd_ii_response[3] = DAT_40002ed4;
    break;
  case 0x434:
    uVar3 = 4;
    obd_ii_response[3] = DAT_40002ee0;
    break;
  case 0x435:
    uVar3 = 4;
    obd_ii_response[3] = DAT_40002eec;
    break;
  case 0x436:
    uVar3 = 4;
    obd_ii_response[3] = DAT_40002ef8;
    break;
  case 0x437:
    obd_ii_response[3] = SUB41(u16_rspeed_rpm_ARRAY_40002e84._4_4_,3);
    obd_ii_response[4] = SUB41(u16_rspeed_rpm_ARRAY_40002e84._4_4_,2);
    obd_ii_response[5] = SUB41(u16_rspeed_rpm_ARRAY_40002e84._4_4_,1);
    uVar3 = 7;
    obd_ii_response[6] = (byte)u16_rspeed_rpm_ARRAY_40002e84._4_4_;
    break;
  case 0x438:
    obd_ii_response[3] = (byte)((uint)DAT_40002e94 >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002e94 >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002e94 >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002e94;
    break;
  case 0x439:
    obd_ii_response[3] = (byte)((uint)DAT_40002ea0 >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002ea0 >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002ea0 >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002ea0;
    break;
  case 0x43a:
    obd_ii_response[3] = (byte)((uint)DAT_40002eac >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002eac >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002eac >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002eac;
    break;
  case 0x43b:
    obd_ii_response[3] = (byte)((uint)DAT_40002eb8 >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002eb8 >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002eb8 >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002eb8;
    break;
  case 0x43c:
    obd_ii_response[3] = (byte)((uint)DAT_40002ec4 >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002ec4 >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002ec4 >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002ec4;
    break;
  case 0x43d:
    obd_ii_response[3] = (byte)((uint)DAT_40002ed0 >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002ed0 >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002ed0 >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002ed0;
    break;
  case 0x43e:
    obd_ii_response[3] = (byte)((uint)DAT_40002edc >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002edc >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002edc >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002edc;
    break;
  case 0x43f:
    obd_ii_response[3] = (byte)((uint)DAT_40002ee8 >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002ee8 >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002ee8 >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002ee8;
    break;
  case 0x440:
    obd_ii_response[3] = DAT_40001818;
    obd_ii_response[4] = DAT_40001819;
    obd_ii_response[5] = DAT_4000181a;
    uVar3 = 7;
    obd_ii_response[6] = DAT_4000181b;
    break;
  case 0x441:
    obd_ii_response[3] = (byte)((uint)DAT_40002ef4 >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_40002ef4 >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_40002ef4 >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_40002ef4;
    break;
  case 0x442:
    uVar3 = 4;
    obd_ii_response[3] = DAT_40002efc;
    break;
  case 0x443:
    uVar3 = 4;
    obd_ii_response[3] = DAT_40002f00._0_1_;
    break;
  case 0x444:
    uVar3 = 4;
    obd_ii_response[3] = DAT_40002f04;
    break;
  case 0x445:
    uVar3 = 4;
    obd_ii_response[3] = DAT_40002f08;
    break;
  case 0x446:
    uVar3 = 4;
    obd_ii_response[3] = DAT_40002f0c;
    break;
  case 0x447:
    uVar3 = 4;
    obd_ii_response[3] = DAT_40002f10;
    break;
  case 0x448:
    uVar3 = 4;
    obd_ii_response[3] = DAT_40002f14;
    break;
  case 0x449:
    uVar3 = 4;
    obd_ii_response[3] = DAT_40002f18;
    break;
  case 0x44a:
    uVar3 = 4;
    obd_ii_response[3] = DAT_40002f1c;
    break;
  case 1099:
    uVar3 = 4;
    obd_ii_response[3] = DAT_40002f20;
    break;
  case 0x44c:
    obd_ii_response[3] = (byte)((ushort)DAT_40002efe >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40002efe;
    break;
  case 0x44d:
    obd_ii_response[3] = (byte)((ushort)DAT_40002f02 >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40002f02;
    break;
  case 0x44e:
    obd_ii_response[3] = (byte)((ushort)DAT_40002f06 >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40002f06;
    break;
  case 0x44f:
    obd_ii_response[3] = (byte)((ushort)DAT_40002f0a >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40002f0a;
    break;
  case 0x450:
    obd_ii_response[3] = (byte)((ushort)DAT_40002f0e >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40002f0e;
    break;
  case 0x451:
    obd_ii_response[3] = (byte)((ushort)DAT_40002f12 >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40002f12;
    break;
  case 0x452:
    obd_ii_response[3] = (byte)((ushort)DAT_40002f16 >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40002f16;
    break;
  case 0x453:
    obd_ii_response[3] = (byte)((ushort)DAT_40002f1a >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40002f1a;
    break;
  case 0x454:
    obd_ii_response[3] = (byte)((ushort)DAT_40002f1e >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40002f1e;
    break;
  case 0x455:
    obd_ii_response[3] = (byte)((ushort)DAT_40002f22 >> 8);
    uVar3 = 5;
    obd_ii_response[4] = (byte)DAT_40002f22;
    break;
  case 0x456:
    obd_ii_response[3] = (byte)((uint)DAT_4000344c >> 0x18);
    obd_ii_response[4] = (byte)((uint)DAT_4000344c >> 0x10);
    obd_ii_response[5] = (byte)((uint)DAT_4000344c >> 8);
    uVar3 = 7;
    obd_ii_response[6] = (byte)DAT_4000344c;
  }
  if (uVar3 < 4) {
    DAT_400016c0 = 1;
  }
  else {
    obd_ii_response_length = uVar3;
    flexcan_a_obd_send_messages();
  }
  return;
}



void FUN_0005d574(void)

{
  DAT_40001820 = 0xc0;
  DAT_40001821 = 0;
  DAT_40001822 = 0;
  DAT_40001823 = 0x13;
  DAT_40001824 = 0;
  DAT_40001825 = 0;
  DAT_40001826 = 0;
  DAT_40001827 = 1;
  DAT_40001828 = 0x40;
  DAT_40001829 = 0;
  DAT_4000182a = 0;
  DAT_4000182b = 0;
  return;
}



// WARNING: Removing unreachable block (ram,0x0005d640)

void obd_ii_mode01_processing(void)

{
  byte bVar1;
  uint i;
  byte resp_len;
  
  resp_len = 1;
  obd_ii_response[0] = 0x41;
  i = 2;
  while (((i & 0xff) < obd_ii_request[0] + 1 && (resp_len < 0x7c))) {
    bVar1 = obd_ii_request[i & 0xff];
    if (bVar1 == 0x1f) {
      obd_ii_response[resp_len] = obd_ii_request[i & 0xff];
      bVar1 = resp_len + 2;
      obd_ii_response[(byte)(resp_len + 1)] = (byte)((ulonglong)DAT_40001540 / 200 >> 8);
      resp_len = resp_len + 3;
      obd_ii_response[bVar1] = (byte)((ulonglong)DAT_40001540 / 200);
    }
    else if (bVar1 < 0x1f) {
      if (bVar1 == 2) {
        obd_ii_response[resp_len] = obd_ii_request[i & 0xff];
        bVar1 = resp_len + 2;
        obd_ii_response[(byte)(resp_len + 1)] = (byte)((ushort)DAT_40002c38 >> 8);
        resp_len = resp_len + 3;
        obd_ii_response[bVar1] = (byte)DAT_40002c38;
      }
      else if (bVar1 < 2) {
        if (bVar1 == 0) {
          obd_ii_response[resp_len] = obd_ii_request[i & 0xff];
          obd_ii_response[(byte)(resp_len + 1)] = DAT_40001820;
          obd_ii_response[(byte)(resp_len + 2)] = DAT_40001821;
          bVar1 = resp_len + 4;
          obd_ii_response[(byte)(resp_len + 3)] = DAT_40001822;
          resp_len = resp_len + 5;
          obd_ii_response[bVar1] = DAT_40001823;
        }
        else {
          obd_ii_response[resp_len] = obd_ii_request[i & 0xff];
          obd_ii_response[(byte)(resp_len + 1)] = DAT_40001878;
          obd_ii_response[(byte)(resp_len + 2)] = 4;
          bVar1 = resp_len + 4;
          obd_ii_response[(byte)(resp_len + 3)] = 0;
          resp_len = resp_len + 5;
          obd_ii_response[bVar1] = 0;
        }
      }
      else if (bVar1 == 0x1c) {
        bVar1 = resp_len + 1;
        obd_ii_response[resp_len] = obd_ii_request[i & 0xff];
        resp_len = resp_len + 2;
        obd_ii_response[bVar1] = CAL_obd_ii_standards_supported;
      }
    }
    else if (bVar1 != 0x41) {
      if (bVar1 < 0x41) {
        if (bVar1 < 0x40) {
          if (bVar1 < 0x21) {
            obd_ii_response[resp_len] = obd_ii_request[i & 0xff];
            obd_ii_response[(byte)(resp_len + 1)] = DAT_40001824;
            obd_ii_response[(byte)(resp_len + 2)] = DAT_40001825;
            bVar1 = resp_len + 4;
            obd_ii_response[(byte)(resp_len + 3)] = DAT_40001826;
            resp_len = resp_len + 5;
            obd_ii_response[bVar1] = DAT_40001827;
          }
        }
        else {
          obd_ii_response[resp_len] = obd_ii_request[i & 0xff];
          obd_ii_response[(byte)(resp_len + 1)] = DAT_40001828;
          obd_ii_response[(byte)(resp_len + 2)] = DAT_40001829;
          bVar1 = resp_len + 4;
          obd_ii_response[(byte)(resp_len + 3)] = DAT_4000182a;
          resp_len = resp_len + 5;
          obd_ii_response[bVar1] = DAT_4000182b;
        }
      }
      else if (bVar1 < 0x43) {
        obd_ii_response[resp_len] = obd_ii_request[i & 0xff];
        bVar1 = resp_len + 2;
        obd_ii_response[(byte)(resp_len + 1)] = (byte)((uint)DAT_400015ba * 0x12 >> 8);
        resp_len = resp_len + 3;
        obd_ii_response[bVar1] = (char)DAT_400015ba * '\x12';
      }
    }
    i = i + 1;
  }
  if (resp_len < 2) {
    DAT_400016c0 = 1;
  }
  else {
    obd_ii_response_length = (ushort)resp_len;
    flexcan_a_obd_send_messages();
  }
  return;
}



void FUN_0005db1c(void)

{
  DAT_40001830 = 0x40;
  DAT_40001831 = 0;
  DAT_40001832 = 0;
  DAT_40001833 = 1;
  DAT_40001834 = 0;
  DAT_40001835 = 0;
  DAT_40001836 = 0;
  DAT_40001837 = 1;
  DAT_40001838 = 0;
  DAT_40001839 = 0;
  DAT_4000183a = 0;
  DAT_4000183b = 0;
  return;
}



void FUN_0005db80(void)

{
  DAT_4000184d = 0;
  DAT_4000184e = 0;
  DAT_4000184f = 0;
  DAT_40001850 = 1;
  DAT_40001851 = 0;
  DAT_40001852 = 0;
  DAT_40001853 = 0;
  DAT_40001854 = 1;
  DAT_40001855 = 2;
  DAT_40001856 = 0;
  DAT_40001857 = 0;
  DAT_40001858 = 1;
  DAT_40001859 = 0;
  DAT_4000185a = 0;
  DAT_4000185b = 0xff;
  DAT_4000185c = 0xff;
  DAT_4000185d = 0xf0;
  DAT_4000185e = 0;
  DAT_4000185f = 0;
  DAT_40001860 = 0;
  return;
}



void obd_ii_mode2f_processing(void)

{
  ushort uVar1;
  byte bVar2;
  char cVar4;
  uint uVar3;
  uint uVar5;
  ushort uVar6;
  
  bVar2 = obd_ii_request[4];
  uVar5 = (uint)obd_ii_request[4];
  uVar6 = 1;
  obd_ii_response[0] = 0x6f;
  uVar1 = CONCAT11(obd_ii_request[2],obd_ii_request[3]);
  if (uVar1 == 0x177) {
    if (((((tach_rpm == 0) && ((DAT_40001450 & 8) != 0)) && ((DAT_40001450 & 0x400) == 0)) &&
        ((input_shaft_rpm == 0 && (output_shaft_rpm == 0)))) &&
       ((ips_gear_cur == GEAR_INVALID9 || (ips_gear_cur == NEUTRAL)))) {
      DAT_40001874 = (short)((uVar5 * 10000) / 0xff);
      uVar5 = DAT_40001844 & 0xffffffbf;
      DAT_40001844 = DAT_40001844 | 0x40;
      if (DAT_40001874 == 0) {
        DAT_40001844 = uVar5;
      }
      DAT_40001840 = DAT_40001840 | 0x40;
      obd_ii_response[1] = obd_ii_request[2];
      obd_ii_response[2] = obd_ii_request[3];
      uVar6 = 4;
      obd_ii_response[3] = obd_ii_request[4];
    }
    else {
      obd_ii_mode_3F_processing();
      DAT_40001844 = DAT_40001844 & 0xffffffbf;
      DAT_40001840 = DAT_40001840 & 0xffffffbf;
      DAT_40001874 = 0;
    }
    DAT_40001862 = DAT_4000e3de;
  }
  else if (uVar1 < 0x177) {
    if (uVar1 == 0x160) {
      obd_ii_response[1] = obd_ii_request[2];
      obd_ii_response[2] = obd_ii_request[3];
      obd_ii_response[3] = DAT_40001859;
      obd_ii_response[4] = DAT_4000185a;
      obd_ii_response[5] = DAT_4000185b;
      uVar6 = 7;
      obd_ii_response[6] = DAT_4000185c;
    }
    else if (uVar1 < 0x160) {
      if (uVar1 == 0x140) {
        obd_ii_response[1] = obd_ii_request[2];
        obd_ii_response[2] = obd_ii_request[3];
        obd_ii_response[3] = DAT_40001855;
        obd_ii_response[4] = DAT_40001856;
        obd_ii_response[5] = DAT_40001857;
        uVar6 = 7;
        obd_ii_response[6] = DAT_40001858;
      }
      else if (uVar1 < 0x140) {
        if (uVar1 == 0x120) {
          obd_ii_response[1] = obd_ii_request[2];
          obd_ii_response[2] = obd_ii_request[3];
          obd_ii_response[3] = DAT_40001851;
          obd_ii_response[4] = DAT_40001852;
          obd_ii_response[5] = DAT_40001853;
          uVar6 = 7;
          obd_ii_response[6] = DAT_40001854;
        }
        else if ((uVar1 < 0x120) && (uVar1 == 0x100)) {
          obd_ii_response[1] = obd_ii_request[2];
          obd_ii_response[2] = obd_ii_request[3];
          obd_ii_response[3] = DAT_4000184d;
          obd_ii_response[4] = DAT_4000184e;
          obd_ii_response[5] = DAT_4000184f;
          uVar6 = 7;
          obd_ii_response[6] = DAT_40001850;
        }
      }
      else if (uVar1 == 0x147) {
        if (tach_rpm == 0) {
          uVar5 = DAT_40001844 & 0xfff7ffff;
          DAT_40001844 = DAT_40001844 | 0x80000;
          if (obd_ii_request[4] == 0) {
            DAT_40001844 = uVar5;
          }
          DAT_40001840 = DAT_40001840 | 0x80000;
          obd_ii_response[1] = obd_ii_request[2];
          obd_ii_response[2] = obd_ii_request[3];
          uVar6 = 4;
          obd_ii_response[3] = obd_ii_request[4];
        }
        else {
          DAT_40001840 = DAT_40001840 & 0xfff7ffff;
          DAT_40001844 = DAT_40001844 & 0xfff7ffff;
          obd_ii_mode_3F_processing();
        }
        DAT_40001862 = DAT_4000e3de;
      }
    }
    else if (uVar1 == 0x173) {
      if (tach_rpm == 0) {
        uVar3 = DAT_40001844 | 4;
        DAT_40001844 = DAT_40001844 & 0xfffffffb;
        if (uVar5 == 0xff) {
          DAT_40001844 = uVar3;
        }
        DAT_40001840 = DAT_40001840 | 4;
        obd_ii_response[1] = obd_ii_request[2];
        obd_ii_response[2] = obd_ii_request[3];
        uVar6 = 4;
        obd_ii_response[3] = obd_ii_request[4];
      }
      else {
        obd_ii_mode_3F_processing();
        DAT_40001844 = DAT_40001844 & 0xfffffffb;
        DAT_40001840 = DAT_40001840 & 0xfffffffb;
      }
      DAT_40001862 = DAT_4000e3de;
    }
    else if (uVar1 < 0x173) {
      if (uVar1 == 0x171) {
        cVar4 = check_selector_learn_allowed();
        if (((cVar4 == '\0') || (DAT_40001bfd != '\0')) &&
           (((cVar4 = check_selector_learn_allowed(), cVar4 == '\0' || (DAT_40001bfd == '\0')) ||
            (((DAT_40001844 & 2) == 0 && (bVar2 != 0)))))) {
          DAT_40001840 = DAT_40001840 & 0xfffffffd;
          DAT_40001844 = DAT_40001844 & 0xfffffffd;
          obd_ii_mode_3F_processing();
        }
        else {
          uVar3 = DAT_40001844 | 2;
          DAT_40001844 = DAT_40001844 & 0xfffffffd;
          if (uVar5 == 0xff) {
            DAT_40001844 = uVar3;
          }
          DAT_40001840 = DAT_40001840 | 2;
          obd_ii_response[1] = obd_ii_request[2];
          obd_ii_response[2] = obd_ii_request[3];
          uVar6 = 4;
          obd_ii_response[3] = bVar2;
        }
        DAT_40001862 = DAT_4000e3de;
      }
      else if (uVar1 < 0x171) {
        if (0x16f < uVar1) {
          DAT_4000184c = 1;
          obd_ii_response[1] = obd_ii_request[2];
          obd_ii_response[2] = obd_ii_request[3];
          uVar6 = 4;
          obd_ii_response[3] = obd_ii_request[4];
        }
      }
      else {
        if (oil_temp_unknown < DAT_4000e3e0) {
          uVar3 = DAT_40001844 | 1;
          DAT_40001844 = DAT_40001844 & 0xfffffffe;
          if (uVar5 == 0xff) {
            DAT_40001844 = uVar3;
          }
          DAT_40001840 = DAT_40001840 | 1;
          obd_ii_response[1] = obd_ii_request[2];
          obd_ii_response[2] = obd_ii_request[3];
          uVar6 = 4;
          obd_ii_response[3] = obd_ii_request[4];
        }
        else {
          obd_ii_mode_3F_processing();
          DAT_40001844 = DAT_40001844 & 0xfffffffe;
          DAT_40001840 = DAT_40001840 & 0xfffffffe;
        }
        DAT_40001862 = DAT_4000e3de;
      }
    }
    else if (uVar1 == 0x175) {
      if (tach_rpm == 0) {
        uVar3 = DAT_40001844 | 0x10;
        DAT_40001844 = DAT_40001844 & 0xffffffef;
        if (uVar5 == 0xff) {
          DAT_40001844 = uVar3;
        }
        DAT_40001840 = DAT_40001840 | 0x10;
        obd_ii_response[1] = obd_ii_request[2];
        obd_ii_response[2] = obd_ii_request[3];
        uVar6 = 4;
        obd_ii_response[3] = obd_ii_request[4];
      }
      else {
        obd_ii_mode_3F_processing();
        DAT_40001844 = DAT_40001844 & 0xffffffef;
        DAT_40001840 = DAT_40001840 & 0xffffffef;
      }
      DAT_40001862 = DAT_4000e3de;
    }
    else if (uVar1 < 0x175) {
      if (tach_rpm == 0) {
        uVar3 = DAT_40001844 | 8;
        DAT_40001844 = DAT_40001844 & 0xfffffff7;
        if (uVar5 == 0xff) {
          DAT_40001844 = uVar3;
        }
        DAT_40001840 = DAT_40001840 | 8;
        obd_ii_response[1] = obd_ii_request[2];
        obd_ii_response[2] = obd_ii_request[3];
        uVar6 = 4;
        obd_ii_response[3] = obd_ii_request[4];
      }
      else {
        obd_ii_mode_3F_processing();
        DAT_40001844 = DAT_40001844 & 0xfffffff7;
        DAT_40001840 = DAT_40001840 & 0xfffffff7;
      }
      DAT_40001862 = DAT_4000e3de;
    }
    else {
      if (tach_rpm == 0) {
        uVar3 = DAT_40001844 | 0x20;
        DAT_40001844 = DAT_40001844 & 0xffffffdf;
        if (uVar5 == 0xff) {
          DAT_40001844 = uVar3;
        }
        DAT_40001840 = DAT_40001840 | 0x20;
        obd_ii_response[1] = obd_ii_request[2];
        obd_ii_response[2] = obd_ii_request[3];
        uVar6 = 4;
        obd_ii_response[3] = obd_ii_request[4];
      }
      else {
        obd_ii_mode_3F_processing();
        DAT_40001844 = DAT_40001844 & 0xffffffdf;
        DAT_40001840 = DAT_40001840 & 0xffffffdf;
      }
      DAT_40001862 = DAT_4000e3de;
    }
  }
  else if (uVar1 == 0x180) {
    obd_ii_response[1] = obd_ii_request[2];
    obd_ii_response[2] = obd_ii_request[3];
    obd_ii_response[3] = DAT_4000185d;
    obd_ii_response[4] = DAT_4000185e;
    obd_ii_response[5] = DAT_4000185f;
    uVar6 = 7;
    obd_ii_response[6] = DAT_40001860;
  }
  else if (uVar1 < 0x180) {
    if (uVar1 == 0x17c) {
      if (((((tach_rpm == 0) && ((DAT_40001450 & 8) != 0)) && ((DAT_40001450 & 0x400) == 0)) &&
          ((input_shaft_rpm == 0 && (output_shaft_rpm == 0)))) &&
         ((ips_gear_cur == GEAR_INVALID9 || (ips_gear_cur == NEUTRAL)))) {
        DAT_4000186a = (short)((uVar5 * 10000) / 0xff);
        uVar5 = DAT_40001844 & 0xfffff7ff;
        DAT_40001844 = DAT_40001844 | 0x800;
        if (DAT_4000186a == 0) {
          DAT_40001844 = uVar5;
        }
        DAT_40001840 = DAT_40001840 | 0x800;
        obd_ii_response[1] = obd_ii_request[2];
        obd_ii_response[2] = obd_ii_request[3];
        uVar6 = 4;
        obd_ii_response[3] = obd_ii_request[4];
      }
      else {
        obd_ii_mode_3F_processing();
        DAT_40001844 = DAT_40001844 & 0xfffff7ff;
        DAT_40001840 = DAT_40001840 & 0xfffff7ff;
        DAT_4000186a = 0;
      }
      DAT_40001862 = DAT_4000e3de;
    }
    else if (uVar1 < 0x17c) {
      if (uVar1 == 0x17a) {
        if (((((tach_rpm == 0) && ((DAT_40001450 & 8) != 0)) && ((DAT_40001450 & 0x400) == 0)) &&
            ((input_shaft_rpm == 0 && (output_shaft_rpm == 0)))) &&
           ((ips_gear_cur == GEAR_INVALID9 || (ips_gear_cur == NEUTRAL)))) {
          DAT_4000186e = (short)((uVar5 * 10000) / 0xff);
          uVar5 = DAT_40001844 & 0xfffffdff;
          DAT_40001844 = DAT_40001844 | 0x200;
          if (DAT_4000186e == 0) {
            DAT_40001844 = uVar5;
          }
          DAT_40001840 = DAT_40001840 | 0x200;
          obd_ii_response[1] = obd_ii_request[2];
          obd_ii_response[2] = obd_ii_request[3];
          uVar6 = 4;
          obd_ii_response[3] = obd_ii_request[4];
        }
        else {
          obd_ii_mode_3F_processing();
          DAT_40001844 = DAT_40001844 & 0xfffffdff;
          DAT_40001840 = DAT_40001840 & 0xfffffdff;
          DAT_4000186e = 0;
        }
        DAT_40001862 = DAT_4000e3de;
      }
      else if (uVar1 < 0x17a) {
        if (uVar1 < 0x179) {
          if (((tach_rpm == 0) && ((DAT_40001450 & 8) != 0)) &&
             ((((DAT_40001450 & 0x400) == 0 && ((input_shaft_rpm == 0 && (output_shaft_rpm == 0))))
              && ((ips_gear_cur == GEAR_INVALID9 || (ips_gear_cur == NEUTRAL)))))) {
            DAT_40001872 = (short)((uVar5 * 10000) / 0xff);
            uVar5 = DAT_40001844 & 0xffffff7f;
            DAT_40001844 = DAT_40001844 | 0x80;
            if (DAT_40001872 == 0) {
              DAT_40001844 = uVar5;
            }
            DAT_40001840 = DAT_40001840 | 0x80;
            obd_ii_response[1] = obd_ii_request[2];
            obd_ii_response[2] = obd_ii_request[3];
            uVar6 = 4;
            obd_ii_response[3] = obd_ii_request[4];
          }
          else {
            obd_ii_mode_3F_processing();
            DAT_40001844 = DAT_40001844 & 0xffffff7f;
            DAT_40001840 = DAT_40001840 & 0xffffff7f;
            DAT_40001872 = 0;
          }
          DAT_40001862 = DAT_4000e3de;
        }
        else {
          if ((((tach_rpm == 0) && ((DAT_40001450 & 8) != 0)) && ((DAT_40001450 & 0x400) == 0)) &&
             (((input_shaft_rpm == 0 && (output_shaft_rpm == 0)) &&
              ((ips_gear_cur == GEAR_INVALID9 || (ips_gear_cur == NEUTRAL)))))) {
            obd_slu_test_demand = (short)((uVar5 * 10000) / 0xff);
            uVar5 = DAT_40001844 & 0xfffffeff;
            DAT_40001844 = DAT_40001844 | 0x100;
            if (obd_slu_test_demand == 0) {
              DAT_40001844 = uVar5;
            }
            DAT_40001840 = DAT_40001840 | 0x100;
            obd_ii_response[1] = obd_ii_request[2];
            obd_ii_response[2] = obd_ii_request[3];
            uVar6 = 4;
            obd_ii_response[3] = obd_ii_request[4];
          }
          else {
            obd_ii_mode_3F_processing();
            DAT_40001844 = DAT_40001844 & 0xfffffeff;
            DAT_40001840 = DAT_40001840 & 0xfffffeff;
            obd_slu_test_demand = 0;
          }
          DAT_40001862 = DAT_4000e3de;
        }
      }
      else {
        if ((((tach_rpm == 0) && ((DAT_40001450 & 8) != 0)) &&
            (((DAT_40001450 & 0x400) == 0 && ((input_shaft_rpm == 0 && (output_shaft_rpm == 0))))))
           && ((ips_gear_cur == GEAR_INVALID9 || (ips_gear_cur == NEUTRAL)))) {
          DAT_4000186c = (short)((uVar5 * 10000) / 0xff);
          uVar5 = DAT_40001844 & 0xfffffbff;
          DAT_40001844 = DAT_40001844 | 0x400;
          if (DAT_4000186c == 0) {
            DAT_40001844 = uVar5;
          }
          DAT_40001840 = DAT_40001840 | 0x400;
          obd_ii_response[1] = obd_ii_request[2];
          obd_ii_response[2] = obd_ii_request[3];
          uVar6 = 4;
          obd_ii_response[3] = obd_ii_request[4];
        }
        else {
          obd_ii_mode_3F_processing();
          DAT_40001844 = DAT_40001844 & 0xfffffbff;
          DAT_40001840 = DAT_40001840 & 0xfffffbff;
          DAT_4000186c = 0;
        }
        DAT_40001862 = DAT_4000e3de;
      }
    }
    else if (uVar1 == 0x17e) {
      if (((tach_rpm == 0) && ((DAT_40001450 & 8) != 0)) &&
         (((DAT_40001450 & 0x400) == 0 && ((input_shaft_rpm == 0 && (DAT_40001440 != '\0')))))) {
        uVar3 = DAT_40001844 | 0x2000;
        DAT_40001844 = DAT_40001844 & 0xffffdfff;
        if (uVar5 == 0xff) {
          DAT_40001844 = uVar3;
        }
        DAT_40001840 = DAT_40001840 | 0x2000;
        obd_ii_response[1] = obd_ii_request[2];
        obd_ii_response[2] = obd_ii_request[3];
        uVar6 = 4;
        obd_ii_response[3] = obd_ii_request[4];
      }
      else {
        obd_ii_mode_3F_processing();
        DAT_40001844 = DAT_40001844 & 0xffffdfff;
        DAT_40001840 = DAT_40001840 & 0xffffdfff;
      }
      DAT_40001862 = DAT_4000e3de;
    }
    else if (uVar1 < 0x17e) {
      if ((((tach_rpm == 0) && ((DAT_40001450 & 8) != 0)) &&
          (((DAT_40001450 & 0x400) == 0 && ((input_shaft_rpm == 0 && (output_shaft_rpm == 0)))))) &&
         ((ips_gear_cur == GEAR_INVALID9 || (ips_gear_cur == NEUTRAL)))) {
        DAT_40001868 = (short)((uVar5 * 10000) / 0xff);
        uVar5 = DAT_40001844 & 0xffffefff;
        DAT_40001844 = DAT_40001844 | 0x1000;
        if (DAT_40001868 == 0) {
          DAT_40001844 = uVar5;
        }
        DAT_40001840 = DAT_40001840 | 0x1000;
        obd_ii_response[1] = obd_ii_request[2];
        obd_ii_response[2] = obd_ii_request[3];
        uVar6 = 4;
        obd_ii_response[3] = obd_ii_request[4];
      }
      else {
        obd_ii_mode_3F_processing();
        DAT_40001844 = DAT_40001844 & 0xffffefff;
        DAT_40001840 = DAT_40001840 & 0xffffefff;
        DAT_40001868 = 0;
      }
      DAT_40001862 = DAT_4000e3de;
    }
    else {
      if ((((tach_rpm == 0) && ((DAT_40001450 & 8) != 0)) && ((DAT_40001450 & 0x400) == 0)) &&
         ((input_shaft_rpm == 0 && (ips_gear_cur == GEAR_INVALID9)))) {
        uVar3 = DAT_40001844 | 0x4000;
        DAT_40001844 = DAT_40001844 & 0xffffbfff;
        if (uVar5 == 0xff) {
          DAT_40001844 = uVar3;
        }
        DAT_40001840 = DAT_40001840 | 0x4000;
        obd_ii_response[1] = obd_ii_request[2];
        obd_ii_response[2] = obd_ii_request[3];
        uVar6 = 4;
        obd_ii_response[3] = obd_ii_request[4];
      }
      else {
        obd_ii_mode_3F_processing();
        DAT_40001844 = DAT_40001844 & 0xffffbfff;
        DAT_40001840 = DAT_40001840 & 0xffffbfff;
      }
      DAT_40001862 = DAT_4000e3de;
    }
  }
  else if (uVar1 != 0x185) {
    if (uVar1 < 0x185) {
      if (uVar1 == 0x183) {
        if (tach_rpm == 0) {
          uVar5 = DAT_40001844 & 0xfffdffff;
          DAT_40001844 = DAT_40001844 | 0x20000;
          if (obd_ii_request[4] == 0) {
            DAT_40001844 = uVar5;
          }
          DAT_40001840 = DAT_40001840 | 0x20000;
          obd_ii_response[1] = obd_ii_request[2];
          obd_ii_response[2] = obd_ii_request[3];
          uVar6 = 4;
          obd_ii_response[3] = obd_ii_request[4];
        }
        else {
          DAT_40001840 = DAT_40001840 & 0xfffdffff;
          DAT_40001844 = DAT_40001844 & 0xfffdffff;
          obd_ii_mode_3F_processing();
        }
        DAT_40001862 = DAT_4000e3de;
      }
      else if (uVar1 < 0x183) {
        if (uVar1 < 0x182) {
          if (tach_rpm == 0) {
            uVar3 = DAT_40001844 | 0x8000;
            DAT_40001844 = DAT_40001844 & 0xffff7fff;
            if (uVar5 == 0xff) {
              DAT_40001844 = uVar3;
            }
            DAT_40001840 = DAT_40001840 | 0x8000;
            obd_ii_response[1] = obd_ii_request[2];
            obd_ii_response[2] = obd_ii_request[3];
            uVar6 = 4;
            obd_ii_response[3] = obd_ii_request[4];
          }
          else {
            obd_ii_mode_3F_processing();
            DAT_40001844 = DAT_40001844 & 0xffff7fff;
            DAT_40001840 = DAT_40001840 & 0xffff7fff;
          }
          DAT_40001862 = DAT_4000e3de;
        }
        else {
          if (uVar5 == 0xff) {
            if (DAT_40001864 == '\0') {
              DAT_40001865 = 0xf0;
            }
            DAT_40001844 = DAT_40001844 | 0x10000;
          }
          else {
            DAT_40001844 = DAT_40001844 & 0xfffeffff;
          }
          DAT_40001840 = DAT_40001840 | 0x10000;
          obd_ii_response[1] = obd_ii_request[2];
          obd_ii_response[2] = obd_ii_request[3];
          uVar6 = 4;
          obd_ii_response[3] = obd_ii_request[4];
          DAT_40001862 = DAT_4000e3de;
        }
      }
      else {
        if ((((DAT_400015b8 & 1) == 0) && (tach_rpm == 0)) && (input_shaft_rpm == 0)) {
          if (obd_ii_request[4] == 0) {
            DAT_40001844 = DAT_40001844 & 0xffebffff;
            DAT_40001861 = 0;
          }
          else {
            DAT_40001861 = 100;
            DAT_40001844 = DAT_40001844 | 0x100000;
          }
          DAT_40001840 = DAT_40001840 | 0x40000;
          obd_ii_response[1] = obd_ii_request[2];
          obd_ii_response[2] = obd_ii_request[3];
          uVar6 = 4;
          obd_ii_response[3] = obd_ii_request[4];
        }
        else {
          DAT_40001840 = DAT_40001840 & 0xfffbffff;
          DAT_40001844 = DAT_40001844 & 0xffebffff;
          obd_ii_mode_3F_processing();
        }
        DAT_40001862 = DAT_4000e3de;
      }
    }
    else if (uVar1 == 0x187) {
      if (uVar5 == 0xff) {
        DAT_40001638 = 1;
        DAT_40001844 = DAT_40001844 | 0x400000;
      }
      else {
        DAT_40001844 = DAT_40001844 & 0xffbfffff;
      }
      DAT_40001840 = DAT_40001840 | 0x400000;
      obd_ii_response[1] = obd_ii_request[2];
      obd_ii_response[2] = obd_ii_request[3];
      uVar6 = 4;
      obd_ii_response[3] = obd_ii_request[4];
      DAT_40001862 = DAT_4000e3de;
    }
    else if (uVar1 < 0x187) {
      if (uVar5 != 0xff) {
        DAT_40001844 = DAT_40001844 & 0xffdfffff;
      }
      else {
        DAT_40001844 = DAT_40001844 | 0x200000;
      }
      LEA_shift_adaptation_reset = uVar5 == 0xff;
      DAT_40001840 = DAT_40001840 | 0x200000;
      obd_ii_response[1] = obd_ii_request[2];
      obd_ii_response[2] = obd_ii_request[3];
      uVar6 = 4;
      obd_ii_response[3] = obd_ii_request[4];
      DAT_40001862 = DAT_4000e3de;
    }
  }
  if (uVar6 < 2) {
    DAT_400016c0 = 1;
  }
  else {
    obd_ii_response_length = uVar6;
    flexcan_a_obd_send_messages();
  }
  return;
}



void obd_ii_mode_3F_processing(void)

{
  obd_ii_response[0] = 0x7f;
  obd_ii_response[1] = obd_ii_request[1];
  obd_ii_response[2] = 0x22;
  obd_ii_response_length = 3;
  flexcan_a_obd_send_messages();
  return;
}



void FUN_0005f81c(void)

{
  if (DAT_40001440 != '\0') {
    if ((DAT_40001840 & 0x2000) == 0) {
      DAT_40001440 = 'd';
    }
    else if (DAT_40001866 == '\0') {
      DAT_40001440 = DAT_40001440 + -1;
    }
  }
  if ((DAT_40001844 & 0x100000) != 0) {
    if (DAT_40001861 == '\0') {
      DAT_40001844 = DAT_40001844 | 0x40000;
    }
    else {
      DAT_40001861 = DAT_40001861 + -1;
    }
  }
  if (DAT_40001862 == 0) {
    DAT_40001840 = 0;
    DAT_40001844 = 0;
    DAT_40001848 = 0;
  }
  else {
    DAT_40001862 = DAT_40001862 + -1;
  }
  return;
}



void obd_ii_mode03_processing(void)

{
  byte bVar1;
  byte bVar2;
  
  obd_ii_response[0] = 0x43;
  obd_ii_response[1] = DAT_40001879;
  bVar1 = 0;
  for (bVar2 = 2; (bVar1 < DAT_40001879 && (bVar2 < 0x7f)); bVar2 = bVar2 + 2) {
    obd_ii_response[bVar2] = (byte)((ushort)(&DAT_400054c8)[bVar1] >> 8);
    obd_ii_response[(byte)(bVar2 + 1)] = (byte)(&DAT_400054c8)[bVar1];
    bVar1 = bVar1 + 1;
  }
  obd_ii_response_length = (ushort)bVar2;
  flexcan_a_obd_send_messages();
  return;
}



void FUN_0005f9b0(void)

{
  DAT_40001878 = DAT_40001879 | 0x80;
  if ((DAT_40001666 & 3) == 0) {
    DAT_40001878 = DAT_40001879;
  }
  return;
}



void FUN_0005f9d8(undefined2 param_1)

{
  if (DAT_40001879 < 0x7f) {
    (&DAT_400054c8)[DAT_40001879] = param_1;
    DAT_40001879 = DAT_40001879 + 1;
  }
  return;
}



void obd_ii_mode04_processing(void)

{
  obd_ii_response[0] = 0x44;
  obd_ii_response_length = 1;
  FUN_0005fa40();
  flexcan_a_obd_send_messages();
  return;
}



void FUN_0005fa40(void)

{
  byte bVar1;
  
  DAT_40001678 = 0;
  DAT_40001938 = 0;
  DAT_40002c5c = 0;
  DAT_40002c38 = 0;
  DAT_40002c3a = 0;
  DAT_40002c3c = 0;
  DAT_40002c3d = 0;
  u16_rspeed_1_4rpm_40002c3e = 0;
  DAT_40002c40 = 0;
  DAT_40002c42 = 0;
  DAT_40002c44 = 0;
  DAT_40002c46 = 0;
  DAT_40002c48 = 0;
  DAT_40001660 = 0;
  DAT_40001666 = 0;
  DAT_40002c81 = 0;
  DAT_40002c88 = 0;
  DAT_40002cc2 = 0;
  DAT_40002cc3 = 3;
  DAT_40002cc4 = 0x28;
  DAT_40002cc5 = 0;
  DAT_40002cc6 = 3;
  DAT_40002cc7 = 0x28;
  DAT_40002cc8 = 0;
  DAT_40002cc9 = 3;
  DAT_40002cca = 0x28;
  DAT_40002ccb = 0;
  DAT_40002ccc = 3;
  DAT_40002ccd = 0x28;
  DAT_40002cce = 0;
  DAT_40002ccf = 3;
  DAT_40002cd0 = 0x28;
  DAT_40002cd1 = 0;
  DAT_40002cd2 = 3;
  DAT_40002cd3 = 0x28;
  DAT_40002cd4 = 0;
  DAT_40002cd5 = 3;
  DAT_40002cd6 = 0x28;
  DAT_40002cd7 = 0;
  DAT_40002cd8 = 3;
  DAT_40002cd9 = 0x28;
  DAT_40002cda = 0;
  DAT_40002cdb = 3;
  DAT_40002cdc = 0x28;
  DAT_40002cdd = 0;
  DAT_40002cde = 3;
  DAT_40002cdf = 0x28;
  DAT_40002ce0 = 0;
  DAT_40002ce1 = 3;
  DAT_40002ce2 = 0x28;
  DAT_40002ce3 = 0;
  DAT_40002ce4 = 3;
  DAT_40002ce5 = 0x28;
  DAT_40002ce6 = 0;
  DAT_40002ce7 = 3;
  DAT_40002ce8 = 0x28;
  DAT_40002ce9 = 0;
  DAT_40002cea = 3;
  DAT_40002ceb = 0x28;
  obd_P0718_dtc_state = 0;
  DAT_40002ced = 3;
  DAT_40002cee = 0x28;
  obd_P0717_dtc_state = 0;
  DAT_40002cf0 = 3;
  DAT_40002cf1 = 0x28;
  DAT_40002cf2 = 0;
  DAT_40002cf3 = 3;
  DAT_40002cf4 = 0x28;
  obd_P0721_dtc_state = 0;
  DAT_40002cf6 = 3;
  DAT_40002cf7 = 0x28;
  obd_P0722_dtc_state = 0;
  DAT_40002cf9 = 3;
  DAT_40002cfa = 0x28;
  obd_P0723_dtc_state = 0;
  DAT_40002cfc = 3;
  DAT_40002cfd = 0x28;
  DAT_40002cfe = 0;
  DAT_40002cff = 3;
  DAT_40002d00 = 0x28;
  DAT_40002d01 = 0;
  DAT_40002d02 = 3;
  DAT_40002d03 = 0x28;
  DAT_40002d04 = 0;
  DAT_40002d05 = 3;
  DAT_40002d06 = 0x28;
  DAT_40002d07 = 0;
  DAT_40002d08 = 3;
  DAT_40002d09 = 0x28;
  DAT_40002d0a = 0;
  DAT_40002d0b = 3;
  DAT_40002d0c = 0x28;
  DAT_40002d0d = 0;
  DAT_40002d0e = 3;
  DAT_40002d0f = 0x28;
  DAT_40002d10 = 0;
  DAT_40002d11 = 3;
  DAT_40002d12 = 0x28;
  DAT_40002d13 = 0;
  DAT_40002d14 = 3;
  DAT_40002d15 = 0x28;
  DAT_40002d16 = 0;
  DAT_40002d17 = 3;
  DAT_40002d18 = 0x28;
  DAT_40002d19 = 0;
  DAT_40002d1a = 3;
  DAT_40002d1b = 0x28;
  DAT_40002d1c = 0;
  DAT_40002d1d = 3;
  DAT_40002d1e = 0x28;
  DAT_40002d1f = 0;
  DAT_40002d20 = 3;
  DAT_40002d21 = 0x28;
  DAT_40002d22 = 0;
  DAT_40002d23 = 3;
  DAT_40002d24 = 0x28;
  DAT_40002d25 = 0;
  DAT_40002d26 = 3;
  DAT_40002d27 = 0x28;
  DAT_40002d28 = 0;
  DAT_40002d29 = 3;
  DAT_40002d2a = 0x28;
  DAT_40002d2b = 0;
  DAT_40002d2c = 3;
  DAT_40002d2d = 0x28;
  DAT_40002d2e = 0;
  DAT_40002d2f = 3;
  DAT_40002d30 = 0x28;
  DAT_40002d31 = 0;
  DAT_40002d32 = 3;
  DAT_40002d33 = 0x28;
  DAT_40002d34 = 0;
  DAT_40002d35 = 3;
  DAT_40002d36 = 0x28;
  DAT_40002d37 = 0;
  DAT_40002d38 = 3;
  DAT_40002d39 = 0x28;
  DAT_40002d3a = 0;
  DAT_40002d3b = 3;
  DAT_40002d3c = 0x28;
  DAT_40002d3d = 0;
  DAT_40002d3e = 3;
  DAT_40002d3f = 0x28;
  DAT_40002d40 = 0;
  DAT_40002d41 = 3;
  DAT_40002d42 = 0x28;
  DAT_40002d43 = 0;
  DAT_40002d44 = 3;
  DAT_40002d45 = 0x28;
  obd_P0894_dtc_state = 0;
  DAT_40002d47 = 3;
  DAT_40002d48 = 0x28;
  DAT_40002d49 = 0;
  DAT_40002d4a = 3;
  DAT_40002d4b = 0x28;
  DAT_40002d4c = 0;
  DAT_40002d4d = 3;
  DAT_40002d4e = 0x28;
  DAT_40002d4f = 0;
  DAT_40002d50 = 3;
  DAT_40002d51 = 0x28;
  DAT_40002d52 = 0;
  DAT_40002da1 = 3;
  DAT_40002da2 = 0x28;
  DAT_40002da0 = 0;
  DAT_40002da4 = 3;
  DAT_40002da5 = 0x28;
  DAT_40002da3 = 0;
  DAT_40002d53 = 3;
  DAT_40002d54 = 0x28;
  DAT_40002d55 = 0;
  DAT_40002d56 = 3;
  DAT_40002d57 = 0x28;
  DAT_40002d58 = 0;
  DAT_40002d59 = 3;
  DAT_40002d5a = 0x28;
  DAT_40002d5b = 0;
  DAT_40002d5c = 3;
  DAT_40002d5d = 0x28;
  DAT_40002d5e = 0;
  DAT_40002d5f = 3;
  DAT_40002d60 = 0x28;
  DAT_40002d61 = 0;
  DAT_40002d62 = 3;
  DAT_40002d63 = 0x28;
  DAT_40002d64 = 0;
  DAT_40002d65 = 3;
  DAT_40002d66 = 0x28;
  DAT_40002d67 = 0;
  DAT_40002d68 = 3;
  DAT_40002d69 = 0x28;
  DAT_40002d6a = 0;
  DAT_40002d6b = 3;
  DAT_40002d6c = 0x28;
  DAT_40002d6d = 0;
  DAT_40002d6e = 3;
  DAT_40002d6f = 0x28;
  DAT_40002d70 = 0;
  DAT_40002d71 = 3;
  DAT_40002d72 = 0x28;
  DAT_40002d73 = 0;
  DAT_40002d74 = 3;
  DAT_40002d75 = 0x28;
  DAT_40002d76 = 0;
  DAT_40002d77 = 3;
  DAT_40002d78 = 0x28;
  DAT_40002d79 = 0;
  DAT_40002d7a = 3;
  DAT_40002d7b = 0x28;
  DAT_40002da6 = 0;
  DAT_40002da7 = 3;
  DAT_40002da8 = 0x28;
  DAT_40002da9 = 0;
  DAT_40002daa = 3;
  DAT_40002dab = 0x28;
  DAT_40002d7c = 0;
  DAT_40002d7d = 3;
  DAT_40002d7e = 0x28;
  DAT_40002d7f = 0;
  DAT_40002d80 = 3;
  DAT_40002d81 = 0x28;
  DAT_40002d82 = 0;
  DAT_40002d83 = 3;
  DAT_40002d84 = 0x28;
  DAT_40002dac = 0;
  DAT_40002dad = 3;
  DAT_40002dae = 0x28;
  DAT_40002daf = 0;
  DAT_40002db0 = 3;
  DAT_40002db1 = 0x28;
  DAT_40002d85 = 0;
  DAT_40002d86 = 3;
  DAT_40002d87 = 0x28;
  DAT_40002d88 = 0;
  DAT_40002d89 = 3;
  DAT_40002d8a = 0x28;
  DAT_40002d8b = 0;
  DAT_40002d8c = 3;
  DAT_40002d8d = 0x28;
  DAT_40002d8e = 0;
  DAT_40002d8f = 3;
  DAT_40002d90 = 0x28;
  DAT_40002d91 = 0;
  DAT_40002d92 = 3;
  DAT_40002d93 = 0x28;
  DAT_40002d94 = 0;
  DAT_40002d95 = 3;
  DAT_40002d96 = 0x28;
  DAT_40002d97 = 0;
  DAT_40002d98 = 3;
  DAT_40002d99 = 0x28;
  DAT_40002d9a = 0;
  DAT_40002d9b = 3;
  DAT_40002d9c = 0x28;
  DAT_40002d9d = 0;
  DAT_40002d9e = 3;
  DAT_40002d9f = 0x28;
  DAT_40002db2 = 0;
  DAT_40002db3 = 3;
  DAT_40002db4 = 0x28;
  DAT_40002db5 = 0;
  DAT_40002db6 = 3;
  DAT_40002db7 = 0x28;
  DAT_40002db8 = 0;
  DAT_40002db9 = 3;
  DAT_40002dba = 0x28;
  DAT_40002dbb = 0;
  DAT_40002dbc = 3;
  DAT_40002dbd = 0x28;
  DAT_40002dbe = 0;
  DAT_40002dbf = 3;
  DAT_40002dc0 = 0x28;
  DAT_40002dc1 = 0;
  DAT_40002dc2 = 3;
  DAT_40002dc3 = 0x28;
  DAT_40002dc4 = 0;
  DAT_40002dc5 = 3;
  DAT_40002dc6 = 0x28;
  DAT_40002dc7 = 0;
  DAT_40002dc8 = 3;
  DAT_40002dc9 = 0x28;
  DAT_40002dca = 0;
  DAT_40002dcb = 3;
  DAT_40002dcc = 0x28;
  DAT_40002dcd = 0;
  DAT_40002dce = 3;
  DAT_40002dcf = 0x28;
  DAT_40002dd0 = 0;
  DAT_40002dd1 = 3;
  DAT_40002dd2 = 0x28;
  DAT_40002dd3 = 0;
  DAT_40002dd4 = 3;
  DAT_40002dd5 = 0x28;
  DAT_40002dd6 = 0;
  DAT_40002dd7 = 3;
  DAT_40002dd8 = 0x28;
  DAT_40002dd9 = 0;
  DAT_40002dda = 3;
  DAT_40002ddb = 0x28;
  DAT_40001898 = 0;
  DAT_400018b0 = 0;
  DAT_40001879 = 0;
  for (bVar1 = 0; bVar1 < 0x80; bVar1 = bVar1 + 1) {
    (&DAT_400055c8)[bVar1] = 0;
    (&DAT_400056c8)[bVar1] = 0;
    (&DAT_400054c8)[bVar1] = 0;
  }
  DAT_4000166a = 1;
  FUN_0004fecc();
  DAT_40002c84 = 0;
  if (DAT_4000184c != '\0') {
    obd_ii_zero_perm_dtc();
  }
  return;
}



void obd_ii_set_mode06_supported_pids(void)

{
  DAT_40001880 = 0;
  DAT_40001881 = 0;
  DAT_40001882 = 0;
  DAT_40001883 = 0;
  DAT_40001884 = 0;
  DAT_40001885 = 0;
  DAT_40001886 = 0;
  DAT_40001887 = 0;
  DAT_40001888 = 0;
  DAT_40001889 = 0;
  DAT_4000188a = 0;
  DAT_4000188b = 0;
  DAT_4000188c = 0;
  DAT_4000188d = 0;
  DAT_4000188e = 0;
  DAT_4000188f = 0;
  DAT_40001890 = 0;
  DAT_40001891 = 0;
  DAT_40001892 = 0;
  DAT_40001893 = 0;
  DAT_40001894 = 0;
  DAT_40001895 = 0;
  DAT_40001896 = 0;
  DAT_40001897 = 0;
  return;
}



void obd_ii_mode07_processing(void)

{
  byte bVar1;
  byte bVar2;
  
  obd_ii_response[0] = 0x47;
  obd_ii_response[1] = DAT_40001898;
  bVar1 = 0;
  for (bVar2 = 2; (bVar1 < DAT_40001898 && (bVar2 < 0x7f)); bVar2 = bVar2 + 2) {
    obd_ii_response[bVar2] = (byte)((ushort)(&DAT_400055c8)[bVar1] >> 8);
    obd_ii_response[(byte)(bVar2 + 1)] = (byte)(&DAT_400055c8)[bVar1];
    bVar1 = bVar1 + 1;
  }
  obd_ii_response_length = (ushort)bVar2;
  flexcan_a_obd_send_messages();
  return;
}



void FUN_00060f18(undefined2 param_1)

{
  if (DAT_40001898 < 0x7f) {
    (&DAT_400055c8)[DAT_40001898] = param_1;
    DAT_40001898 = DAT_40001898 + 1;
  }
  return;
}



void FUN_00060f48(void)

{
  DAT_400018a0 = 0;
  DAT_400018a1 = 0;
  DAT_400018a2 = 0;
  DAT_400018a3 = 0;
  return;
}



void FUN_00060f6c(void)

{
  DAT_400018aa = 0x14;
  DAT_400018ab = 0x40;
  DAT_400018ac = 0;
  DAT_400018ad = 0;
  return;
}



void obd_ii_mode09_processing(void)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  
  bVar2 = 1;
  obd_ii_response[0] = 0x49;
  obd_ii_response_length = obd_ii_response_length + 1;
  uVar1 = 2;
  while (((uVar1 & 0xff) < obd_ii_request[0] + 1 && (bVar2 < 0x6b))) {
    if (obd_ii_request[uVar1 & 0xff] == 0) {
      obd_ii_response[bVar2] = obd_ii_request[uVar1 & 0xff];
      obd_ii_response[(byte)(bVar2 + 1)] = DAT_400018aa;
      obd_ii_response[(byte)(bVar2 + 2)] = DAT_400018ab;
      bVar3 = bVar2 + 4;
      obd_ii_response[(byte)(bVar2 + 3)] = DAT_400018ac;
      bVar2 = bVar2 + 5;
      obd_ii_response[bVar3] = DAT_400018ad;
    }
    else if (obd_ii_request[uVar1 & 0xff] == 4) {
      obd_ii_response[bVar2] = obd_ii_request[uVar1 & 0xff];
      obd_ii_response[(byte)(bVar2 + 1)] = 1;
      bVar2 = bVar2 + 2;
      for (bVar3 = 0; bVar3 < 0x10; bVar3 = bVar3 + 1) {
        obd_ii_response[bVar2] = CAL_version_string[bVar3];
        bVar2 = bVar2 + 1;
      }
    }
    else if (obd_ii_request[uVar1 & 0xff] == 6) {
      obd_ii_response[bVar2] = obd_ii_request[uVar1 & 0xff];
      obd_ii_response[(byte)(bVar2 + 1)] = 1;
      obd_ii_response[(byte)(bVar2 + 2)] = 0;
      obd_ii_response[(byte)(bVar2 + 3)] = 0;
      bVar3 = bVar2 + 5;
      obd_ii_response[(byte)(bVar2 + 4)] = (byte)(calibration_verification_number >> 8);
      bVar2 = bVar2 + 6;
      obd_ii_response[bVar3] = (byte)calibration_verification_number;
    }
    else if (obd_ii_request[uVar1 & 0xff] == 10) {
      obd_ii_response[bVar2] = obd_ii_request[uVar1 & 0xff];
      obd_ii_response[(byte)(bVar2 + 1)] = 1;
      obd_ii_response[(byte)(bVar2 + 2)] = 0x54;
      obd_ii_response[(byte)(bVar2 + 3)] = 0x43;
      obd_ii_response[(byte)(bVar2 + 4)] = 0x4d;
      obd_ii_response[(byte)(bVar2 + 5)] = 0;
      obd_ii_response[(byte)(bVar2 + 6)] = 0x2d;
      obd_ii_response[(byte)(bVar2 + 7)] = 0x54;
      obd_ii_response[(byte)(bVar2 + 8)] = 0x72;
      obd_ii_response[(byte)(bVar2 + 9)] = 0x61;
      obd_ii_response[(byte)(bVar2 + 10)] = 0x6e;
      obd_ii_response[(byte)(bVar2 + 0xb)] = 0x73;
      obd_ii_response[(byte)(bVar2 + 0xc)] = 0x6d;
      obd_ii_response[(byte)(bVar2 + 0xd)] = 0x69;
      obd_ii_response[(byte)(bVar2 + 0xe)] = 0x73;
      obd_ii_response[(byte)(bVar2 + 0xf)] = 0x43;
      obd_ii_response[(byte)(bVar2 + 0x10)] = 0x74;
      obd_ii_response[(byte)(bVar2 + 0x11)] = 0x72;
      obd_ii_response[(byte)(bVar2 + 0x12)] = 0x6c;
      obd_ii_response[(byte)(bVar2 + 0x13)] = 0;
      bVar3 = bVar2 + 0x15;
      obd_ii_response[(byte)(bVar2 + 0x14)] = 0;
      bVar2 = bVar2 + 0x16;
      obd_ii_response[bVar3] = 0;
    }
    uVar1 = uVar1 + 1;
  }
  if (bVar2 < 2) {
    DAT_400016c0 = 1;
  }
  else {
    obd_ii_response_length = (ushort)bVar2;
    flexcan_a_obd_send_messages();
  }
  return;
}



void obd_ii_mode11_processing(void)

{
  obd_ii_response[0] = 0x51;
  obd_ii_response_length = 1;
  FUN_00061534();
  flexcan_a_obd_send_messages();
  return;
}



void FUN_00061534(void)

{
  FUN_000490b0();
  return;
}



void obd_ii_mode13_processing(void)

{
  byte bVar1;
  byte bVar2;
  
  if ((obd_ii_request[0] == 1) ||
     (((obd_ii_request[0] == 3 && (obd_ii_request[2] == 0xff)) && (obd_ii_request[3] == 0)))) {
    obd_ii_response[0] = 0x53;
    bVar1 = 0;
    for (bVar2 = 1; (bVar1 < DAT_40001879 && (bVar2 < 0x7f)); bVar2 = bVar2 + 2) {
      obd_ii_response[bVar2] = (byte)((ushort)(&DAT_400054c8)[bVar1] >> 8);
      obd_ii_response[(byte)(bVar2 + 1)] = (byte)(&DAT_400054c8)[bVar1];
      bVar1 = bVar1 + 1;
    }
    bVar1 = 0;
    for (; (bVar1 < DAT_400018b0 && (bVar2 < 0x7f)); bVar2 = bVar2 + 2) {
      obd_ii_response[bVar2] = (byte)((ushort)(&DAT_400056c8)[bVar1] >> 8);
      obd_ii_response[(byte)(bVar2 + 1)] = (byte)(&DAT_400056c8)[bVar1];
      bVar1 = bVar1 + 1;
    }
    obd_ii_response_length = (ushort)bVar2;
    flexcan_a_obd_send_messages();
  }
  return;
}



void FUN_000616fc(undefined2 param_1)

{
  if (DAT_400018b0 < 0x7f) {
    (&DAT_400056c8)[DAT_400018b0] = param_1;
    DAT_400018b0 = DAT_400018b0 + 1;
  }
  return;
}



void obd_ii_mode14_processing(void)

{
  if ((obd_ii_request[0] == 1) || (obd_ii_request[2] == 0xff)) {
    FUN_0005fa40();
    obd_ii_response[0] = 0x54;
    obd_ii_response_length = 1;
    flexcan_a_obd_send_messages();
  }
  return;
}



void update_trans_fault_monitor(void)

{
  bool bVar1;
  ushort uVar2;
  char cVar3;
  byte bVar4;
  byte bVar5;
  int iVar6;
  
  FUN_00064a68();
  if (DAT_40001c38 == '\x01') {
    if ((((int)solenoid_SLU_demand / 100 & 0xffU) < (uint)DAT_4000e3fc) ||
       ((uint)DAT_4000e3fd < ((int)solenoid_SL_demand / 100 & 0xffU))) {
      DAT_400018dc = 2;
    }
    else {
      DAT_400018dc = 1;
    }
    DAT_400018d9 = DAT_4000e403;
  }
  else if ((DAT_400018c0 & 2) == 0) {
    if ((short)engine_torque < DAT_4000e400) {
      if ((short)engine_torque < DAT_4000e3fe) {
        DAT_400018d9 = DAT_4000e403;
        DAT_400018dc = 2;
      }
    }
    else {
      cVar3 = DAT_400018d9 + -1;
      if (DAT_400018d9 == '\0') {
        cVar3 = DAT_400018d9;
      }
      DAT_400018d9 = cVar3;
      if (cVar3 == '\0') {
        DAT_400018dc = 1;
      }
      else {
        DAT_400018dc = 2;
      }
    }
  }
  else {
    DAT_400018d9 = DAT_4000e403;
    DAT_400018dc = 2;
  }
  iVar6 = int_abs(DAT_40001712);
  if ((int)(uint)DAT_4000e3f7 <= iVar6) {
    DAT_400018c0 = DAT_400018c0 | 1;
    DAT_400018da = DAT_4000e3f9;
  }
  if ((DAT_400018c0 & 1) != 0) {
    iVar6 = int_abs(DAT_40001712);
    if (iVar6 < (int)(uint)DAT_4000e3f8) {
      bVar1 = DAT_400018da == '\0';
      DAT_400018da = DAT_400018da + -1;
      if (bVar1) {
        DAT_400018da = '\0';
      }
      if (ips_gear_cur == (GEAR_INVALID8|GEAR_INVALID7)) {
        DAT_400018db = '\x01';
      }
      if ((DAT_400018da == '\0') &&
         (((short)engine_torque <= DAT_4000e3fa || (DAT_400018db != '\0')))) {
        DAT_400018c0 = DAT_400018c0 & 0xfe;
        DAT_400018db = '\0';
      }
    }
    else {
      DAT_400018da = DAT_4000e422;
      DAT_400018db = '\0';
    }
  }
  gear_plausibility_monitor();
  DAT_400018b8 = REG_SIU_GPDI127;
  DAT_400018b9 = REG_SIU_GPDI128;
  DAT_400018ba = REG_SIU_GPDI129;
  DAT_400018bb = REG_SIU_GPDI130;
  DAT_400018bc = REG_SIU_GPDI131;
  DAT_400018bd = REG_SIU_GPDI132;
  DAT_400018be = REG_SIU_GPDI204;
  if ((((((((DAT_4000e268 & 7) != 0) && ((DAT_40001678 & 2) == 0)) && ((DAT_40001678 & 1) == 0)) &&
        (((DAT_40001678 & 0x40000) == 0 && ((DAT_40001678 & 0x10) == 0)))) &&
       ((DAT_40001678 & 0x200) == 0)) &&
      ((((DAT_40001678 & 0x3c00) == 0 && ((DAT_40001678 & 0x8000) == 0)) &&
       (((DAT_40001678 & 8) == 0 &&
        ((((DAT_400015b8 & 1) != 0 && (engine_running != '\0')) && (DAT_4000e464 <= input_shaft_rpm)
         ))))))) &&
     ((((byte)(ips_gear_cur - GEAR_2) < 7 &&
       ((uint)DAT_4000e443 <= (vehicle_speed____ / 100 & 0xff))) &&
      (DAT_4000e444 <= (short)engine_torque)))) {
    if ((DAT_400018c3 & 1) == 0) {
      if ((DAT_400018c3 & 0x10) != 0) {
        DAT_400018cc = 0;
        if (DAT_400018cb < DAT_4000e33a) {
          DAT_400018cb = DAT_400018cb + 1;
        }
        obd_ii_monitor_pass(&DAT_4000e268,&DAT_40002d01);
      }
    }
    else {
      DAT_400018cc = DAT_400018cc + 1;
      if (DAT_4000e44a < DAT_400018cc) {
        DAT_400018cc = 0;
        bVar4 = DAT_400018cb - 1;
        if (DAT_400018cb == 0) {
          bVar4 = DAT_400018cb;
        }
        DAT_400018cb = bVar4;
        if (bVar4 == 0) {
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e268,&DAT_40002d01,&DAT_40002d02,&DAT_40002d03,0x741,0);
        }
      }
    }
  }
  if ((((((DAT_4000e269 & 7) != 0) && ((DAT_40001678 & 2) == 0)) &&
       (((DAT_40001678 & 1) == 0 &&
        ((((DAT_40001678 & 0x10) == 0 && ((DAT_40001678 & 0x200) == 0)) && ((DAT_40001678 & 8) == 0)
         ))))) && (((DAT_40001678 & 4) == 0 && ((DAT_40001678 & 0x40000) == 0)))) &&
     ((DAT_400018d7 != 0 &&
      ((((DAT_400015b8 & 1) != 0 && (engine_running != '\0')) &&
       ((DAT_4000e454 <= input_shaft_rpm &&
        ((((DAT_4000e466 <= output_shaft_rpm && (DAT_4000148d == -1)) &&
          ((byte)(ips_gear_cur - GEAR_1) < 6)) &&
         (((uint)DAT_4000e451 <= (vehicle_speed____ / 100 & 0xff) &&
          (DAT_4000e44c < oil_temp_unknown)))))))))))) {
    DAT_400018f8 = count_set_bits(DAT_400018d1);
    DAT_400018f9 = count_set_bits(DAT_400018d2);
    if ((((DAT_400018d1 & 0xe) == 0) ||
        (((DAT_400018d1 & 0x60) == 0 || (DAT_400018f8 < DAT_4000e44d)))) &&
       ((((DAT_400018d0 & 8) == 0 || ((DAT_400018d0 & 4) == 0)) ||
        (((DAT_400018d0 & 2) == 0 && ((DAT_400018d0 & 1) == 0)))))) {
      if (DAT_4000e452 <= DAT_400018f9) {
        if (DAT_400018d6 < DAT_4000e33b) {
          DAT_400018d6 = DAT_400018d6 + 1;
        }
        obd_ii_monitor_pass(&DAT_4000e269,&DAT_40002d04);
      }
    }
    else {
      DAT_400018d1 = 0;
      DAT_400018d2 = '\0';
      DAT_400018d4 = 0;
      DAT_400018d5 = 0;
      DAT_400018d3 = 0;
      bVar4 = DAT_400018d6 - 1;
      if (DAT_400018d6 == 0) {
        bVar4 = DAT_400018d6;
      }
      DAT_400018d6 = bVar4;
      if (bVar4 == 0) {
        DAT_400018d6 = 0;
        obd_ii_dtc_confirm_and_freeze
                  (&DAT_4000e269,&DAT_40002d04,&DAT_40002d05,&DAT_40002d06,0x746,0);
      }
    }
  }
  bVar4 = DAT_400018c1 & 0xf3;
  if (((((DAT_4000e26a & 7) != 0) && ((DAT_40001678 & 2) == 0)) && ((DAT_40001678 & 0x20) == 0)) &&
     ((DAT_400015b8 & 1) != 0)) {
    if (DAT_4000e456 <= DAT_400015ba) {
      if (DAT_400018bd == 0) {
        bVar4 = bVar4 | 0x40;
      }
      else {
        bVar4 = DAT_400018c1 & 0xb3 | 4;
      }
    }
    DAT_400018c1 = bVar4;
    if (((DAT_400018bd == 0) && (DAT_4000e458 <= DAT_400015ba)) &&
       ((uint)DAT_4000e45a <= ((int)solenoid_SLT_demand / 100 & 0xffU))) {
      if (DAT_4000239e < DAT_4000e45c) {
        DAT_400018c1 = DAT_400018c1 & 0x7f | 8;
      }
      else {
        DAT_400018c1 = DAT_400018c1 | 0x80;
      }
    }
    bVar4 = DAT_400018c1;
    if (((DAT_400018c1 & 4) == 0) && ((DAT_400018c1 & 8) == 0)) {
      if (((DAT_400018c1 & 0x40) != 0) || ((DAT_400018c1 & 0x80) != 0)) {
        DAT_400018d8 = 0;
        if (DAT_400018d7 < DAT_4000e33c) {
          DAT_400018d7 = DAT_400018d7 + 1;
        }
        obd_ii_monitor_pass(&DAT_4000e26a,&DAT_40002d07);
        bVar4 = DAT_400018c1;
      }
    }
    else {
      DAT_400018d8 = DAT_400018d8 + 1;
      if (DAT_40001676 < (short)(ushort)DAT_400018d8) {
        DAT_400018d8 = 0;
        bVar5 = DAT_400018d7 - 1;
        if (DAT_400018d7 == 0) {
          bVar5 = DAT_400018d7;
        }
        DAT_400018d7 = bVar5;
        if (bVar5 == 0) {
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e26a,&DAT_40002d07,&DAT_40002d08,&DAT_40002d09,0x748,0);
          bVar4 = DAT_400018c1;
        }
      }
    }
  }
  DAT_400018c1 = bVar4;
  if ((((((((DAT_4000e282 & 7) == 0) || ((DAT_40001678 & 2) != 0)) || ((DAT_40001678 & 1) != 0)) ||
        ((((DAT_40001678 & 0x400) != 0 || ((DAT_40001678 & 0x10) != 0)) ||
         (((DAT_40001678 & 8) != 0 || (((DAT_40001678 & 4) != 0 || ((DAT_40001678 & 0x40000) != 0)))
          ))))) ||
       ((DAT_400018c0 != 0 ||
        (((((DAT_400018c4 & 0x80) == 0 || ((DAT_400018c4 & 0x40) == 0)) ||
          (oil_temp_unknown <= DAT_4000e45e)) || ((DAT_4000148d != -1 || ((DAT_400015b8 & 1) == 0)))
         ))))) || (engine_running == '\0')) ||
     ((((input_shaft_rpm < DAT_4000e460 || (output_shaft_rpm < DAT_4000e462)) ||
       (((vehicle_speed____ / 100 & 0xff) < (uint)DAT_4000e405 ||
        ((DAT_40001448 < DAT_400018dc || (DAT_40001448 == 0xf)))))) && (DAT_400018df == '\0')))) {
    DAT_400018de = 0;
  }
  else if (((DAT_400018c4 & 1) == 0) && ((DAT_400018c4 & 2) == 0)) {
    if (((DAT_400018c4 & 0x10) != 0) || ((DAT_400018c4 & 0x20) != 0)) {
      DAT_400018de = 0;
      if (DAT_400018dd < DAT_4000e354) {
        DAT_400018dd = DAT_400018dd + 1;
      }
      obd_ii_monitor_pass(&DAT_4000e282,&DAT_40002d0a);
    }
  }
  else {
    DAT_400018de = DAT_400018de + 1;
    if (DAT_40002c8a < DAT_400018de) {
      DAT_40002c8a = DAT_400018de;
    }
    if (DAT_4000e45f < DAT_400018de) {
      DAT_400018de = 0;
      bVar4 = DAT_400018dd - 1;
      if (DAT_400018dd == 0) {
        bVar4 = DAT_400018dd;
      }
      DAT_400018dd = bVar4;
      if ((bVar4 == 0) &&
         (obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e282,&DAT_40002d0a,&DAT_40002d0b,&DAT_40002d0c,0x751,0),
         (DAT_400018c4 & 1) != 0)) {
        DAT_400018d0 = DAT_400018d0 | 8;
      }
    }
  }
  bVar4 = DAT_400018c4 & 0xf3;
  if (((((DAT_4000e283 & 7) != 0) && ((DAT_40001678 & 2) == 0)) && ((DAT_40001678 & 1) == 0)) &&
     ((((DAT_40001678 & 0x20) == 0 && (DAT_4000346e != '\x06')) && ((DAT_400015b8 & 1) != 0)))) {
    if (DAT_4000e468 < DAT_400015ba) {
      if (DAT_400018b8 == 0) {
        bVar4 = bVar4 | 0x40;
      }
      else {
        bVar4 = DAT_400018c4 & 0xb3 | 4;
      }
    }
    DAT_400018c4 = bVar4;
    if ((DAT_4000e46a <= DAT_400015ba) &&
       ((uint)DAT_4000e46c <= ((int)solenoid_SL1_demand / 100 & 0xffU))) {
      if (DAT_40002394 < DAT_4000e46e) {
        DAT_400018c4 = DAT_400018c4 & 0x7f | 8;
      }
      else {
        DAT_400018c4 = DAT_400018c4 | 0x80;
      }
    }
    bVar4 = DAT_400018c4;
    if (((DAT_400018c4 & 4) == 0) && ((DAT_400018c4 & 8) == 0)) {
      if (((DAT_400018c4 & 0x40) != 0) || ((DAT_400018c4 & 0x80) != 0)) {
        DAT_400018e1 = 0;
        if (DAT_400018e0 < DAT_4000e355) {
          DAT_400018e0 = DAT_400018e0 + 1;
        }
        obd_ii_monitor_pass(&DAT_4000e283,&DAT_40002d0d);
        bVar4 = DAT_400018c4;
      }
    }
    else {
      DAT_400018e1 = DAT_400018e1 + 1;
      if (DAT_40001676 < (short)(ushort)DAT_400018e1) {
        DAT_400018e1 = 0;
        bVar5 = DAT_400018e0 - 1;
        if (DAT_400018e0 == 0) {
          bVar5 = DAT_400018e0;
        }
        DAT_400018e0 = bVar5;
        if (bVar5 == 0) {
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e283,&DAT_40002d0d,&DAT_40002d0e,&DAT_40002d0f,0x753,0);
          bVar4 = DAT_400018c4;
        }
      }
    }
  }
  DAT_400018c4 = bVar4;
  if (((((((DAT_4000e284 & 7) != 0) && ((DAT_40001678 & 2) == 0)) && ((DAT_40001678 & 1) == 0)) &&
       ((((DAT_40001678 & 0x800) == 0 && ((DAT_40001678 & 0x10) == 0)) &&
        (((DAT_40001678 & 8) == 0 && (((DAT_40001678 & 4) == 0 && ((DAT_40001678 & 0x40000) == 0))))
        )))) && (DAT_400018c0 == 0)) &&
     ((((((((DAT_400018c5 & 0x80) != 0 && ((DAT_400018c5 & 0x40) != 0)) && ((DAT_400015b8 & 1) != 0)
          ) && ((engine_running != '\0' && (DAT_4000e472 <= input_shaft_rpm)))) &&
        (DAT_4000e474 <= output_shaft_rpm)) &&
       ((DAT_4000148d == -1 && ((uint)DAT_4000e405 <= (vehicle_speed____ / 100 & 0xff))))) &&
      ((DAT_4000e470 < oil_temp_unknown && ((DAT_400018dc <= DAT_40001448 && (DAT_40001448 != 0xf)))
       ))))) {
    if (((DAT_400018c5 & 1) == 0) && ((DAT_400018c5 & 2) == 0)) {
      if (((DAT_400018c5 & 0x10) != 0) || ((DAT_400018c5 & 0x20) != 0)) {
        DAT_400018e3 = 0;
        if (DAT_400018e2 < DAT_4000e356) {
          DAT_400018e2 = DAT_400018e2 + 1;
        }
        obd_ii_monitor_pass(&DAT_4000e284,&DAT_40002d10);
      }
    }
    else {
      DAT_400018e3 = DAT_400018e3 + 1;
      if (DAT_4000e471 < DAT_400018e3) {
        DAT_400018e3 = 0;
        bVar4 = DAT_400018e2 - 1;
        if (DAT_400018e2 == 0) {
          bVar4 = DAT_400018e2;
        }
        DAT_400018e2 = bVar4;
        if ((bVar4 == 0) &&
           (obd_ii_dtc_confirm_and_freeze
                      (&DAT_4000e284,&DAT_40002d10,&DAT_40002d11,&DAT_40002d12,0x756,0),
           (DAT_400018c5 & 1) != 0)) {
          DAT_400018d0 = DAT_400018d0 | 4;
        }
      }
    }
  }
  bVar4 = DAT_400018c5 & 0xf3;
  if (((((DAT_4000e285 & 7) != 0) && ((DAT_40001678 & 2) == 0)) && ((DAT_40001678 & 1) == 0)) &&
     (((DAT_40001678 & 0x20) == 0 && ((DAT_400015b8 & 1) != 0)))) {
    if (DAT_4000e47a < DAT_400015ba) {
      if (DAT_400018b9 == 0) {
        bVar4 = bVar4 | 0x40;
      }
      else {
        bVar4 = DAT_400018c5 & 0xb3 | 4;
      }
    }
    DAT_400018c5 = bVar4;
    if ((DAT_4000e47c <= DAT_400015ba) &&
       ((uint)DAT_4000e47e <= ((int)solenoid_SL2_demand / 100 & 0xffU))) {
      if (DAT_40002396 < DAT_4000e480) {
        DAT_400018c5 = DAT_400018c5 & 0x7f | 8;
      }
      else {
        DAT_400018c5 = DAT_400018c5 | 0x80;
      }
    }
    bVar4 = DAT_400018c5;
    if (((DAT_400018c5 & 4) == 0) && ((DAT_400018c5 & 8) == 0)) {
      if (((DAT_400018c5 & 0x40) != 0) || ((DAT_400018c5 & 0x80) != 0)) {
        DAT_400018e5 = 0;
        if (DAT_400018e4 < DAT_4000e357) {
          DAT_400018e4 = DAT_400018e4 + 1;
        }
        obd_ii_monitor_pass(&DAT_4000e285,&DAT_40002d13);
        bVar4 = DAT_400018c5;
      }
    }
    else {
      DAT_400018e5 = DAT_400018e5 + 1;
      if (DAT_40001676 < (short)(ushort)DAT_400018e5) {
        DAT_400018e5 = 0;
        bVar5 = DAT_400018e4 - 1;
        if (DAT_400018e4 == 0) {
          bVar5 = DAT_400018e4;
        }
        DAT_400018e4 = bVar5;
        if (bVar5 == 0) {
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e285,&DAT_40002d13,&DAT_40002d14,&DAT_40002d15,0x758,0);
          bVar4 = DAT_400018c5;
        }
      }
    }
  }
  DAT_400018c5 = bVar4;
  if ((((((DAT_4000e286 & 7) != 0) && ((DAT_40001678 & 2) == 0)) && ((DAT_40001678 & 1) == 0)) &&
      ((((DAT_40001678 & 0x1000) == 0 && ((DAT_40001678 & 0x10) == 0)) &&
       (((DAT_40001678 & 8) == 0 && (((DAT_40001678 & 4) == 0 && ((DAT_40001678 & 0x40000) == 0)))))
       ))) && (((DAT_400018c0 == 0 &&
                (((((((DAT_400018c6 & 0x80) != 0 && ((DAT_400018c6 & 0x40) != 0)) &&
                    ((DAT_400015b8 & 1) != 0)) &&
                   ((engine_running != '\0' && (DAT_4000e484 <= input_shaft_rpm)))) &&
                  ((DAT_4000e486 <= output_shaft_rpm &&
                   ((DAT_4000148d == -1 && ((uint)DAT_4000e405 <= (vehicle_speed____ / 100 & 0xff)))
                   )))) && (DAT_4000e482 < oil_temp_unknown)))) &&
               ((DAT_400018dc <= DAT_40001448 && (DAT_40001448 != 0xf)))))) {
    if (((DAT_400018c6 & 1) == 0) && ((DAT_400018c6 & 2) == 0)) {
      if (((DAT_400018c6 & 0x10) != 0) || ((DAT_400018c6 & 0x20) != 0)) {
        DAT_400018e7 = 0;
        if (DAT_400018e6 < DAT_4000e358) {
          DAT_400018e6 = DAT_400018e6 + 1;
        }
        obd_ii_monitor_pass(&DAT_4000e286,&DAT_40002d16);
      }
    }
    else {
      DAT_400018e7 = DAT_400018e7 + 1;
      if (DAT_4000e483 < DAT_400018e7) {
        DAT_400018e7 = 0;
        bVar4 = DAT_400018e6 - 1;
        if (DAT_400018e6 == 0) {
          bVar4 = DAT_400018e6;
        }
        DAT_400018e6 = bVar4;
        if ((bVar4 == 0) &&
           (obd_ii_dtc_confirm_and_freeze
                      (&DAT_4000e286,&DAT_40002d16,&DAT_40002d17,&DAT_40002d18,0x761,0),
           (DAT_400018c6 & 1) != 0)) {
          DAT_400018d0 = DAT_400018d0 | 2;
        }
      }
    }
  }
  bVar4 = DAT_400018c6 & 0xf3;
  if (((((DAT_4000e287 & 7) != 0) && ((DAT_40001678 & 2) == 0)) && ((DAT_40001678 & 1) == 0)) &&
     (((DAT_40001678 & 0x20) == 0 && ((DAT_400015b8 & 1) != 0)))) {
    if (DAT_4000e48c < DAT_400015ba) {
      if (DAT_400018ba == 0) {
        bVar4 = bVar4 | 0x40;
      }
      else {
        bVar4 = DAT_400018c6 & 0xb3 | 4;
      }
    }
    DAT_400018c6 = bVar4;
    if ((DAT_4000e48e <= DAT_400015ba) &&
       ((uint)DAT_4000e490 <= ((int)solenoid_SL3_demand / 100 & 0xffU))) {
      if (DAT_40002398 < DAT_4000e492) {
        DAT_400018c6 = DAT_400018c6 & 0x7f | 8;
      }
      else {
        DAT_400018c6 = DAT_400018c6 | 0x80;
      }
    }
    bVar4 = DAT_400018c6;
    if (((DAT_400018c6 & 4) == 0) && ((DAT_400018c6 & 8) == 0)) {
      if (((DAT_400018c6 & 0x40) != 0) || ((DAT_400018c6 & 0x80) != 0)) {
        DAT_400018e9 = 0;
        if (DAT_400018e8 < DAT_4000e359) {
          DAT_400018e8 = DAT_400018e8 + 1;
        }
        obd_ii_monitor_pass(&DAT_4000e287,&DAT_40002d19);
        bVar4 = DAT_400018c6;
      }
    }
    else {
      DAT_400018e9 = DAT_400018e9 + 1;
      if (DAT_40001676 < (short)(ushort)DAT_400018e9) {
        DAT_400018e9 = 0;
        bVar5 = DAT_400018e8 - 1;
        if (DAT_400018e8 == 0) {
          bVar5 = DAT_400018e8;
        }
        DAT_400018e8 = bVar5;
        if (bVar5 == 0) {
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e287,&DAT_40002d19,&DAT_40002d1a,&DAT_40002d1b,0x763,0);
          bVar4 = DAT_400018c6;
        }
      }
    }
  }
  DAT_400018c6 = bVar4;
  if (((((((DAT_4000e288 & 7) != 0) && ((DAT_40001678 & 2) == 0)) && ((DAT_40001678 & 1) == 0)) &&
       ((((DAT_40001678 & 0x2000) == 0 && ((DAT_40001678 & 0x10) == 0)) &&
        (((DAT_40001678 & 8) == 0 && (((DAT_40001678 & 4) == 0 && ((DAT_40001678 & 0x40000) == 0))))
        )))) && ((DAT_400018c0 == 0 &&
                 (((((DAT_400018c7 & 0x80) != 0 && ((DAT_400018c7 & 0x40) != 0)) &&
                   ((DAT_400015b8 & 1) != 0)) &&
                  ((engine_running != '\0' && (DAT_4000e496 <= input_shaft_rpm)))))))) &&
     ((((DAT_4000e4ba <= output_shaft_rpm &&
        ((DAT_4000148d == -1 && ((uint)DAT_4000e405 <= (vehicle_speed____ / 100 & 0xff))))) &&
       (DAT_4000e494 < oil_temp_unknown)) &&
      ((DAT_400018dc <= DAT_40001448 && (DAT_40001448 != 0xf)))))) {
    if (((DAT_400018c7 & 1) == 0) && ((DAT_400018c7 & 2) == 0)) {
      if (((DAT_400018c7 & 0x10) != 0) || ((DAT_400018c7 & 0x20) != 0)) {
        DAT_400018eb = 0;
        if (DAT_400018ea < DAT_4000e35a) {
          DAT_400018ea = DAT_400018ea + 1;
        }
        obd_ii_monitor_pass(&DAT_4000e288,&DAT_40002d1c);
      }
    }
    else {
      DAT_400018eb = DAT_400018eb + 1;
      if (DAT_4000e495 < DAT_400018eb) {
        DAT_400018eb = 0;
        bVar4 = DAT_400018ea - 1;
        if (DAT_400018ea == 0) {
          bVar4 = DAT_400018ea;
        }
        DAT_400018ea = bVar4;
        if ((bVar4 == 0) &&
           (obd_ii_dtc_confirm_and_freeze
                      (&DAT_4000e288,&DAT_40002d1c,&DAT_40002d1d,&DAT_40002d1e,0x766,0),
           (DAT_400018c7 & 1) != 0)) {
          DAT_400018d0 = DAT_400018d0 | 1;
        }
      }
    }
  }
  bVar4 = DAT_400018c7 & 0xf3;
  if (((((DAT_4000e289 & 7) != 0) && ((DAT_40001678 & 2) == 0)) && ((DAT_40001678 & 1) == 0)) &&
     (((DAT_40001678 & 0x20) == 0 && ((DAT_400015b8 & 1) != 0)))) {
    if (DAT_4000e49e < DAT_400015ba) {
      if (DAT_400018bb == 0) {
        bVar4 = bVar4 | 0x40;
      }
      else {
        bVar4 = DAT_400018c7 & 0xb3 | 4;
      }
    }
    DAT_400018c7 = bVar4;
    if ((DAT_4000e4a0 <= DAT_400015ba) &&
       ((uint)DAT_4000e4a2 <= ((int)solenoid_SL4_demand / 100 & 0xffU))) {
      if (DAT_4000239a < DAT_4000e4a4) {
        DAT_400018c7 = DAT_400018c7 & 0x7f | 8;
      }
      else {
        DAT_400018c7 = DAT_400018c7 | 0x80;
      }
    }
    bVar4 = DAT_400018c7;
    if (((DAT_400018c7 & 4) == 0) && ((DAT_400018c7 & 8) == 0)) {
      if (((DAT_400018c7 & 0x40) != 0) || ((DAT_400018c7 & 0x80) != 0)) {
        DAT_400018ed = 0;
        if (DAT_400018ec < DAT_4000e35b) {
          DAT_400018ec = DAT_400018ec + 1;
        }
        obd_ii_monitor_pass(&DAT_4000e289,&DAT_40002d1f);
        bVar4 = DAT_400018c7;
      }
    }
    else {
      DAT_400018ed = DAT_400018ed + 1;
      if (DAT_40001676 < (short)(ushort)DAT_400018ed) {
        DAT_400018ed = 0;
        bVar5 = DAT_400018ec - 1;
        if (DAT_400018ec == 0) {
          bVar5 = DAT_400018ec;
        }
        DAT_400018ec = bVar5;
        if (bVar5 == 0) {
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e289,&DAT_40002d1f,&DAT_40002d20,&DAT_40002d21,0x768,0);
          bVar4 = DAT_400018c7;
        }
      }
    }
  }
  DAT_400018c7 = bVar4;
  if (((((((CAL_obd_P0894_cfg & 7) == 0) || ((DAT_40001678 & 2) != 0)) || ((DAT_40001678 & 1) != 0))
       || ((((DAT_40001678 & 0x10) != 0 || ((DAT_40001678 & 8) != 0)) ||
           (((DAT_40001678 & 4) != 0 || ((DAT_400018c0 != 0 || ((DAT_400015b8 & 1) == 0)))))))) ||
      (engine_running == '\0')) || ((trans_slip_status_flags & 1) == 0)) {
    obd_ii_monitor_pass(&CAL_obd_P0894_cfg,&obd_P0894_dtc_state);
  }
  else {
    obd_ii_dtc_confirm_and_freeze
              (&CAL_obd_P0894_cfg,&obd_P0894_dtc_state,&DAT_40002d47,&DAT_40002d48,0x894,0);
    trans_slip_status_flags = trans_slip_status_flags & 0xfe;
  }
  uVar2 = DAT_4000165c & 0xc;
  if (((DAT_4000e291 & 7) != 0) &&
     (((DAT_400015b8 & 1) != 0 || (bVar4 = REG_SIU_GPDO192, bVar4 != 0)))) {
    if ((uVar2 == 8) || ((uVar2 == 0xc || (uVar2 == 4)))) {
      DAT_400018ef = DAT_400018ef + 1;
      if ((DAT_40001676 <= (short)(ushort)DAT_400018ef) &&
         ((DAT_400018ef = 0, DAT_400018ee != 0 &&
          (DAT_400018ee = DAT_400018ee - 1, DAT_400018ee == 0)))) {
        obd_ii_dtc_confirm_and_freeze
                  (&DAT_4000e291,&DAT_40002d4f,&DAT_40002d50,&DAT_40002d51,&DAT_00001657,0);
      }
    }
    else {
      DAT_400018ef = 0;
      obd_ii_monitor_pass(&DAT_4000e291,&DAT_40002d4f);
      if (DAT_400018ee < DAT_4000e363) {
        DAT_400018ee = DAT_400018ee + 1;
      }
    }
  }
  DAT_4000165c = DAT_4000165c & 0xfff3;
  if ((((((((DAT_4000e277 & 7) != 0) && ((DAT_40001678 & 2) == 0)) && ((DAT_40001678 & 1) == 0)) &&
        (((DAT_40001678 & 0x40000) == 0 && ((DAT_40001678 & 0x10) == 0)))) &&
       ((DAT_40001678 & 0x200) == 0)) &&
      (((((DAT_40001678 & 0x3c00) == 0 && ((DAT_40001678 & 0x4000) == 0)) &&
        (((DAT_40001678 & 8) == 0 &&
         ((((DAT_400015b8 & 1) != 0 && (engine_running != '\0')) &&
          (DAT_4000e464 <= input_shaft_rpm)))))) &&
       (((byte)(ips_gear_cur - GEAR_2) < 7 &&
        ((uint)DAT_4000e443 <= (vehicle_speed____ / 100 & 0xff))))))) &&
     (DAT_4000e444 <= (short)engine_torque)) {
    bVar4 = DAT_400018c2;
    if ((((DAT_40002d40 & 8) != 0) && ((DAT_40002d40 & 4) == 0)) &&
       ((DAT_400023a2 != '\0' &&
        ((((DAT_400018bf & 2) != 0 && ((DAT_400018bf & 4) != 0)) &&
         (bVar4 = DAT_400018c2 | 2, (DAT_400018bf & 0x10) == 0)))))) {
      bVar4 = DAT_400018c2;
    }
    DAT_400018c2 = bVar4;
    if (((DAT_400018c2 & 1) == 0) && ((DAT_400018c2 & 2) == 0)) {
      if (((DAT_400018c2 & 0x10) != 0) || ((DAT_400018c2 & 0x20) != 0)) {
        DAT_400018cd = 0;
        DAT_400018f1 = 0;
        if (DAT_400018f0 < DAT_4000e349) {
          DAT_400018f0 = DAT_400018f0 + 1;
        }
        obd_ii_monitor_pass(&DAT_4000e277,&DAT_40002d8e);
      }
    }
    else {
      if ((DAT_400018c2 & 1) == 0) {
        DAT_400018cd = 0;
      }
      else if (DAT_400018cd != 0xff) {
        DAT_400018cd = DAT_400018cd + 1;
      }
      if ((DAT_400018c2 & 2) == 0) {
        DAT_400018f1 = 0;
      }
      else if (DAT_400018f1 != 0xff) {
        DAT_400018f1 = DAT_400018f1 + 1;
      }
      if ((DAT_4000e44a < DAT_400018cd) || (DAT_4000e44a < DAT_400018f1)) {
        DAT_400018cd = 0;
        DAT_400018f1 = 0;
        bVar4 = DAT_400018f0 - 1;
        if (DAT_400018f0 == 0) {
          bVar4 = DAT_400018f0;
        }
        DAT_400018f0 = bVar4;
        if (bVar4 == 0) {
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e277,&DAT_40002d8e,&DAT_40002d8f,&DAT_40002d90,&DAT_00002757,0);
        }
      }
    }
  }
  bVar4 = DAT_400018c2 & 0xf3;
  if (((((DAT_4000e278 & 7) != 0) && ((DAT_40001678 & 2) == 0)) && ((DAT_40001678 & 1) == 0)) &&
     (((DAT_40001678 & 0x20) == 0 && ((DAT_400015b8 & 1) != 0)))) {
    if (DAT_4000e4aa < DAT_400015ba) {
      if (DAT_400018bc == 0) {
        bVar4 = bVar4 | 0x40;
      }
      else {
        bVar4 = DAT_400018c2 & 0xb3 | 4;
      }
    }
    DAT_400018c2 = bVar4;
    if ((DAT_4000e4ac <= DAT_400015ba) &&
       ((uint)DAT_4000e4ae <= ((int)solenoid_SLU_demand / 100 & 0xffU))) {
      if (DAT_4000239c < DAT_4000e4b0) {
        DAT_400018c2 = DAT_400018c2 & 0x7f | 8;
      }
      else {
        DAT_400018c2 = DAT_400018c2 | 0x80;
      }
    }
    bVar4 = DAT_400018c2;
    if (((DAT_400018c2 & 4) == 0) && ((DAT_400018c2 & 8) == 0)) {
      if (((DAT_400018c2 & 0x40) != 0) || ((DAT_400018c2 & 0x80) != 0)) {
        DAT_400018f3 = 0;
        if (DAT_400018f2 < DAT_4000e34a) {
          DAT_400018f2 = DAT_400018f2 + 1;
        }
        obd_ii_monitor_pass(&DAT_4000e278,&DAT_40002d91);
        bVar4 = DAT_400018c2;
      }
    }
    else {
      DAT_400018f3 = DAT_400018f3 + 1;
      if (DAT_40001676 < (short)(ushort)DAT_400018f3) {
        DAT_400018f3 = 0;
        bVar5 = DAT_400018f2 - 1;
        if (DAT_400018f2 == 0) {
          bVar5 = DAT_400018f2;
        }
        DAT_400018f2 = bVar5;
        if (bVar5 == 0) {
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e278,&DAT_40002d91,&DAT_40002d92,&DAT_40002d93,&DAT_00002759,0);
          bVar4 = DAT_400018c2;
        }
      }
    }
  }
  DAT_400018c2 = bVar4;
  bVar4 = DAT_400018c3 & 0xfb;
  if (((((DAT_4000e279 & 7) != 0) && ((DAT_40001678 & 2) == 0)) && ((DAT_40001678 & 1) == 0)) &&
     ((((DAT_40001678 & 0x20) == 0 && ((DAT_400015b8 & 1) != 0)) &&
      ((DAT_4000e4b2 < DAT_400015ba &&
       ((uint)DAT_4000e4b4 <= ((int)solenoid_SL_demand / 100 & 0xffU))))))) {
    if (DAT_400018be == 0) {
      DAT_400018c3 = DAT_400018c3 & 0xbb | 4;
      DAT_400018f5 = DAT_400018f5 + 1;
      bVar4 = DAT_400018c3;
      if (DAT_40001676 < (short)(ushort)DAT_400018f5) {
        DAT_400018f5 = 0;
        bVar5 = DAT_400018f4 - 1;
        if (DAT_400018f4 == 0) {
          bVar5 = DAT_400018f4;
        }
        DAT_400018f4 = bVar5;
        if (bVar5 == 0) {
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e279,&DAT_40002d94,&DAT_40002d95,&DAT_40002d96,&DAT_00002769,0);
          bVar4 = DAT_400018c3;
        }
      }
    }
    else {
      DAT_400018c3 = bVar4 | 0x40;
      DAT_400018f5 = 0;
      if (DAT_400018f4 < DAT_4000e34b) {
        DAT_400018f4 = DAT_400018f4 + 1;
      }
      obd_ii_monitor_pass(&DAT_4000e279,&DAT_40002d94);
      bVar4 = DAT_400018c3;
    }
  }
  DAT_400018c3 = bVar4;
  bVar4 = DAT_400018c3 & 0xf7;
  if ((((DAT_4000e27a & 7) != 0) && ((DAT_40001678 & 2) == 0)) &&
     ((((DAT_40001678 & 1) == 0 &&
       ((((DAT_40001678 & 0x20) == 0 && ((DAT_400015b8 & 1) != 0)) && (DAT_4000e4bc < DAT_400015ba))
       )) && ((DAT_4000346e != '\x06' &&
              (((int)solenoid_SL_demand / 100 & 0xffU) <= (uint)DAT_4000e4be)))))) {
    if (DAT_400018be == 0) {
      DAT_400018f7 = 0;
      DAT_400018c3 = bVar4 | 0x80;
      if (DAT_400018f6 < DAT_4000e34c) {
        DAT_400018f6 = DAT_400018f6 + 1;
      }
      obd_ii_monitor_pass(&DAT_4000e27a,&DAT_40002d97);
      bVar4 = DAT_400018c3;
    }
    else {
      DAT_400018c3 = DAT_400018c3 & 0x77 | 8;
      DAT_400018f7 = DAT_400018f7 + 1;
      bVar4 = DAT_400018c3;
      if (DAT_40001676 < (short)(ushort)DAT_400018f7) {
        DAT_400018f7 = 0;
        bVar5 = DAT_400018f6 - 1;
        if (DAT_400018f6 == 0) {
          bVar5 = DAT_400018f6;
        }
        DAT_400018f6 = bVar5;
        if (bVar5 == 0) {
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e27a,&DAT_40002d97,&DAT_40002d98,&DAT_40002d99,&DAT_00002770,0);
          bVar4 = DAT_400018c3;
        }
      }
    }
  }
  DAT_400018c3 = bVar4;
  if (((((DAT_40002d0a & 8) == 0) || ((DAT_40002d0a & 4) == 0)) || ((DAT_40002d0a & 1) == 0)) &&
     ((((DAT_40002d0d & 8) == 0 || ((DAT_40002d0d & 4) == 0)) || ((DAT_40002d0d & 1) == 0)))) {
    DAT_40001678 = DAT_40001678 & 0xfffffbff;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x400;
  }
  if (((((DAT_40002d10 & 8) == 0) || ((DAT_40002d10 & 4) == 0)) || ((DAT_40002d10 & 1) == 0)) &&
     ((((DAT_40002d13 & 8) == 0 || ((DAT_40002d13 & 4) == 0)) || ((DAT_40002d13 & 1) == 0)))) {
    DAT_40001678 = DAT_40001678 & 0xfffff7ff;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x800;
  }
  if (((((DAT_40002d16 & 8) == 0) || ((DAT_40002d16 & 4) == 0)) || ((DAT_40002d16 & 1) == 0)) &&
     ((((DAT_40002d19 & 8) == 0 || ((DAT_40002d19 & 4) == 0)) || ((DAT_40002d19 & 1) == 0)))) {
    DAT_40001678 = DAT_40001678 & 0xffffefff;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x1000;
  }
  if (((((DAT_40002d1c & 8) == 0) || ((DAT_40002d1c & 4) == 0)) || ((DAT_40002d1c & 1) == 0)) &&
     ((((DAT_40002d1f & 8) == 0 || ((DAT_40002d1f & 4) == 0)) || ((DAT_40002d1f & 1) == 0)))) {
    DAT_40001678 = DAT_40001678 & 0xffffdfff;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x2000;
  }
  if (((((DAT_40002d8e & 8) == 0) || ((DAT_40002d8e & 4) == 0)) || ((DAT_40002d8e & 1) == 0)) &&
     ((((DAT_40002d91 & 8) == 0 || ((DAT_40002d91 & 4) == 0)) || ((DAT_40002d91 & 1) == 0)))) {
    DAT_40001678 = DAT_40001678 & 0xffffbfff;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x4000;
  }
  if ((((((DAT_40002d01 & 8) == 0) || ((DAT_40002d01 & 4) == 0)) || ((DAT_40002d01 & 1) == 0)) &&
      ((((DAT_40002d94 & 8) == 0 || ((DAT_40002d94 & 4) == 0)) || ((DAT_40002d94 & 1) == 0)))) &&
     ((((DAT_40002d97 & 8) == 0 || ((DAT_40002d97 & 4) == 0)) || ((DAT_40002d97 & 1) == 0)))) {
    DAT_40001678 = DAT_40001678 & 0xffff7fff;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x8000;
  }
  if (((((DAT_40002d04 & 8) == 0) || ((DAT_40002d04 & 4) == 0)) || ((DAT_40002d04 & 1) == 0)) &&
     ((((DAT_40002d07 & 8) == 0 || ((DAT_40002d07 & 4) == 0)) || ((DAT_40002d07 & 1) == 0)))) {
    DAT_40001678 = DAT_40001678 & 0xfffeffff;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x10000;
  }
  if ((((DAT_40002d4f & 8) == 0) || ((DAT_40002d4f & 4) == 0)) || ((DAT_40002d4f & 1) == 0)) {
    DAT_40001678 = DAT_40001678 & 0xfffdffff;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x20000;
  }
  return;
}



void FUN_00064a68(void)

{
  bool bVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  int iVar5;
  
  if (((DAT_40001678 & 8) == 0) && ((DAT_40001678 & 0x40000) == 0)) {
    u16_rspeed_rpm_400018fa =
         int_abs((ulonglong)(uint)((int)(uint)tach_rpm >> 2) - (ulonglong)input_shaft_rpm);
  }
  else {
    u16_rspeed_rpm_400018fa = 0;
  }
  DAT_400018c2 = DAT_400018c2 & 0xec;
  DAT_400018c3 = DAT_400018c3 & 0xee;
  iVar5 = int_abs(DAT_40001712);
  if ((int)(uint)DAT_4000e41e <= iVar5) {
    DAT_400018bf = DAT_400018bf | 0x80;
    DAT_400018ce = DAT_4000e422;
  }
  if ((DAT_400018bf & 0x80) != 0) {
    iVar5 = int_abs(DAT_40001712);
    if (iVar5 < (int)(uint)DAT_4000e41f) {
      bVar1 = DAT_400018ce == '\0';
      DAT_400018ce = DAT_400018ce + -1;
      if (bVar1) {
        DAT_400018ce = '\0';
      }
      if ((DAT_400018ce == '\0') && ((short)engine_torque <= DAT_4000e420)) {
        DAT_400018bf = DAT_400018bf & 0x7f;
      }
    }
    else {
      DAT_400018ce = DAT_4000e422;
    }
  }
  if (ips_gear_cur == (GEAR_INVALID8|GEAR_INVALID7)) {
    DAT_400018bf = DAT_400018bf | 0x40;
    DAT_400018cf = DAT_4000e41d;
  }
  if ((DAT_400018bf & 0x40) != 0) {
    if ((byte)(ips_gear_cur - GEAR_1) < 8) {
      cVar2 = DAT_400018cf + -1;
      if (DAT_400018cf == '\0') {
        cVar2 = DAT_400018cf;
      }
      DAT_400018cf = cVar2;
      if (cVar2 == '\0') {
        DAT_400018bf = DAT_400018bf & 0xbf;
      }
    }
    else {
      DAT_400018cf = DAT_4000e41d;
    }
  }
  bVar3 = DAT_400018bf & 0xf0;
  if ((((((DAT_400015b8 & 1) != 0) && (engine_running != '\0')) &&
       ((byte)(ips_gear_cur - GEAR_2) < 7)) &&
      (((uint)DAT_4000e443 <= (vehicle_speed____ / 100 & 0xff) &&
       (DAT_4000e444 <= (short)engine_torque)))) &&
     (((DAT_400018bf & 0x80) == 0 && ((DAT_400018bf & 0x40) == 0)))) {
    if ((((input_shaft_load < DAT_4000e446) &&
         (clutch_pressure_target <= (ushort)((ushort)DAT_4000903d * 100))) &&
        ((vehicle_speed____ / 100 & 0xff) < (uint)DAT_4000e453)) &&
       (LEA_shift_adaptation_history_valid != false)) {
      if (DAT_4000e447 < u16_rspeed_rpm_400018fa) {
        bVar3 = bVar3 | 0x22;
        if (((uint)DAT_4000e44b <= ((int)solenoid_SL_demand / 100 & 0xffU)) &&
           ((DAT_400018bf & 0x10) != 0)) {
          DAT_400018c2 = DAT_400018c2 | 0x20;
        }
      }
      else {
        bVar3 = DAT_400018bf & 0xd0 | 2;
        DAT_400018c2 = DAT_400018c2 & 0xdf;
      }
    }
    else if ((((DAT_4000e448 <= input_shaft_load) && (LEA_shift_adaptation_history_valid != false))
             || (DAT_4000e442 <= input_shaft_load)) &&
            (((uint)DAT_4000e441 < (vehicle_speed____ / 100 & 0xff) &&
             ((uint)DAT_4000e44b <= ((int)solenoid_SL_demand / 100 & 0xffU))))) {
      if (u16_rspeed_rpm_400018fa < DAT_4000e449) {
        bVar3 = bVar3 | 0x11;
        DAT_400018c2 = DAT_400018c2 | 0x10;
        DAT_400018c3 = DAT_400018c3 | 0x10;
      }
      else {
        bVar3 = DAT_400018bf & 0xe0 | 1;
        if (DAT_4000e447 < u16_rspeed_rpm_400018fa) {
          bVar4 = DAT_400018c3 | 1;
          if (DAT_400023a2 == '\0') {
            bVar4 = DAT_400018c3;
          }
          DAT_400018c3 = bVar4;
          if (DAT_400023a2 == '\0') {
            DAT_400018c2 = DAT_400018c2 | 1;
          }
        }
      }
    }
  }
  DAT_400018bf = bVar3;
  bVar3 = DAT_400018bf | 8;
  if (u16_rspeed_rpm_400018fa < DAT_4000e449) {
    bVar3 = DAT_400018bf | 4;
  }
  DAT_400018bf = bVar3;
  return;
}



void gear_plausibility_monitor(void)

{
  enum_t6e_gear eVar1;
  
  FUN_00065c4c();
  FUN_00065f4c();
  DAT_40001448 = ips_gear_cur;
  if (((((DAT_400015b8 & 1) == 0) || (engine_running == '\0')) || (DAT_400018c0 != '\0')) ||
     (((vehicle_speed____ / 100 & 0xff) < (uint)DAT_4000e405 || (ips_gear_cur < DAT_400018dc)))) {
    if (((((DAT_400015b8 & 1) == 0) || ((engine_running == '\0' || (DAT_400018c0 != '\0')))) ||
        (vehicle_speed____ != 0)) ||
       ((((output_shaft_rpm != 0 || (ips_gear_cur != GEAR_1)) || (input_shaft_rpm < DAT_4000e4c0))
        || (DAT_4000e4c2 < (short)engine_torque)))) {
      DAT_400018df = 0;
      DAT_400018c8 = 0;
      DAT_400018c9 = 0;
      gear_latched = ~NEUTRAL;
      if ((((byte)(ips_gear_cur - GEAR_1) < 6) && (gear_request == ips_gear_cur)) &&
         (DAT_40001a44 == ips_gear_cur)) {
        gear_candidate = ips_gear_cur;
      }
      else {
        gear_candidate = ~NEUTRAL;
      }
    }
    else {
      DAT_400018df = 1;
      gear_confirmed = NEUTRAL;
      gear_latched = ~NEUTRAL;
      gear_candidate = ~NEUTRAL;
      DAT_400018c8 = expected_ratio_for_gear(GEAR_1);
      DAT_400018c9 = expected_ratio_for_gear(gear_confirmed);
    }
  }
  else {
    if (DAT_4000148d == -1) {
      gear_confirmed = DAT_40001a44;
      DAT_40001910 = '\0';
      eVar1 = gear_confirmed;
    }
    else if (DAT_40001910 == '\0') {
      DAT_40001910 = '\x01';
      if ((ips_gear_cur == DAT_40001a44) && ((byte)(ips_gear_cur - GEAR_1) < 6)) {
        gear_confirmed = ips_gear_cur;
        eVar1 = gear_confirmed;
      }
      else {
        gear_confirmed = ~NEUTRAL;
        eVar1 = gear_confirmed;
      }
    }
    else {
      eVar1 = gear_confirmed;
      if ((ips_gear_cur != (GEAR_INVALID8|GEAR_INVALID7)) &&
         (eVar1 = ~NEUTRAL, ips_gear_cur == gear_confirmed)) {
        eVar1 = gear_confirmed;
      }
    }
    gear_confirmed = eVar1;
    if (ips_gear_cur == (GEAR_INVALID8|GEAR_INVALID7)) {
      if (gear_candidate == ~NEUTRAL) {
        if (gear_confirmed == ~NEUTRAL) {
          gear_latched = ~NEUTRAL;
        }
      }
      else {
        gear_latched = gear_candidate;
      }
      gear_candidate = ~NEUTRAL;
    }
    else if (((byte)(ips_gear_cur - GEAR_1) < 6) && ((byte)(gear_confirmed - GEAR_1) < 6)) {
      DAT_400018c8 = expected_ratio_for_gear(ips_gear_cur);
      DAT_400018c9 = expected_ratio_for_gear(gear_confirmed);
      gear_candidate = gear_confirmed;
    }
    else if (((byte)(ips_gear_cur - GEAR_1) < 6) && (gear_confirmed == NEUTRAL)) {
      DAT_400018c8 = expected_ratio_for_gear(ips_gear_cur);
      DAT_400018c9 = 0;
      gear_candidate = gear_confirmed;
    }
    else {
      DAT_400018c8 = 0;
      DAT_400018c9 = 0;
    }
    DAT_400018df = 0;
  }
  DAT_400018ca = DAT_400018c8 ^ DAT_400018c9;
  if (DAT_400018ca == 0) {
    FUN_00065ddc(gear_confirmed);
    DAT_400018fc = 0;
    DAT_400018fd = 0;
    DAT_400018fe = '\0';
    DAT_400018ff = '\0';
    DAT_40001900 = 0;
    DAT_40001901 = 0;
    DAT_40001902 = '\0';
    DAT_40001903 = '\0';
    DAT_40001904 = 0;
    DAT_40001905 = 0;
    DAT_40001906 = '\0';
    DAT_40001907 = '\0';
    DAT_40001908 = 0;
    DAT_40001909 = 0;
    DAT_4000190a = 0;
    DAT_4000190b = 0;
    DAT_4000190c = 0;
    DAT_4000190d = 0;
    DAT_4000190e = 0;
    DAT_4000190f = 0;
  }
  else {
    DAT_400018fc = ~DAT_400018c9 & DAT_400018c8;
    DAT_400018fd = ~DAT_400018c8 & DAT_400018c9;
    DAT_400018fe = FUN_00065bd0(DAT_400018fc);
    DAT_400018ff = FUN_00065bd0(DAT_400018fd);
    if (((DAT_400018fe == '\x01') && (DAT_400018ff == '\0')) ||
       ((DAT_400018ff == '\x01' && (DAT_400018fe == '\0')))) {
      FUN_00065ca0(DAT_400018fe,DAT_400018ff,DAT_400018fc,DAT_400018fd);
      DAT_4000190c = 0;
      DAT_4000190d = 0;
      DAT_4000190e = 0;
      DAT_4000190f = 0;
      DAT_40001900 = 0;
      DAT_40001901 = 0;
      DAT_40001902 = '\0';
      DAT_40001903 = '\0';
      DAT_40001904 = 0;
      DAT_40001905 = 0;
      DAT_40001906 = '\0';
      DAT_40001907 = '\0';
      DAT_40001908 = 0;
      DAT_40001909 = 0;
      DAT_4000190a = 0;
      DAT_4000190b = 0;
    }
    else {
      if (((gear_latched == ~NEUTRAL) || (5 < (byte)(gear_latched - GEAR_1))) ||
         (((uint)DAT_400018d1 & 1 << (gear_latched & 0x3f)) != 0)) {
        DAT_40001900 = DAT_400018fc;
        DAT_40001901 = DAT_400018fd;
        DAT_40001902 = DAT_400018fe;
        DAT_40001903 = DAT_400018ff;
      }
      else {
        DAT_4000190e = FUN_00065ab0(gear_latched);
        DAT_4000190f = FUN_00065b40(gear_latched);
        DAT_40001900 = DAT_400018fc & ~DAT_4000190e;
        DAT_40001901 = DAT_400018fd & ~DAT_4000190f;
        DAT_40001902 = FUN_00065bd0(DAT_40001900);
        DAT_40001903 = FUN_00065bd0(DAT_40001901);
      }
      if (((DAT_40001902 == '\x01') && (DAT_40001903 == '\0')) ||
         ((DAT_40001903 == '\x01' && (DAT_40001902 == '\0')))) {
        FUN_00065ca0(DAT_40001902,DAT_40001903,DAT_40001900,DAT_40001901);
        DAT_4000190c = 0;
        DAT_4000190d = 0;
        DAT_40001904 = 0;
        DAT_40001905 = 0;
        DAT_40001906 = '\0';
        DAT_40001907 = '\0';
        DAT_40001908 = 0;
        DAT_40001909 = 0;
        DAT_4000190a = 0;
        DAT_4000190b = 0;
      }
      else {
        if ((gear_confirmed == ~NEUTRAL) || (5 < (byte)(gear_confirmed - GEAR_1))) {
          DAT_40001904 = DAT_40001900;
          DAT_40001905 = DAT_40001901;
          DAT_40001906 = DAT_40001902;
          DAT_40001907 = DAT_40001903;
        }
        else {
          DAT_4000190c = FUN_00065ab0(gear_confirmed);
          DAT_4000190d = FUN_00065b40(gear_confirmed);
          if ((DAT_40001902 == '\0') && (DAT_40001903 == '\0')) {
            DAT_40001900 = DAT_400018fc;
            DAT_40001901 = DAT_400018fd;
          }
          DAT_40001904 = DAT_40001900 & DAT_4000190d;
          DAT_40001905 = DAT_40001901 & DAT_4000190c;
          DAT_40001906 = FUN_00065bd0(DAT_40001904);
          DAT_40001907 = FUN_00065bd0(DAT_40001905);
        }
        if (((DAT_40001906 == '\x01') && (DAT_40001907 == '\0')) ||
           ((DAT_40001907 == '\x01' && (DAT_40001906 == '\0')))) {
          FUN_00065ca0(DAT_40001906,DAT_40001907,DAT_40001904,DAT_40001905);
          DAT_40001908 = 0;
          DAT_40001909 = 0;
          DAT_4000190a = 0;
          DAT_4000190b = 0;
        }
        else {
          if ((DAT_40001906 == '\0') && (DAT_40001907 == '\0')) {
            DAT_40001908 = DAT_40001900;
            DAT_40001909 = DAT_40001901;
          }
          else {
            DAT_40001908 = DAT_40001904;
            DAT_40001909 = DAT_40001905;
          }
          if ((DAT_400018c8 & 8) == 0) {
            if (discrete_input_state == '\0') {
              if ((DAT_40002d2e & 4) == 0) {
                DAT_40001909 = DAT_40001909 & 0xf7;
              }
            }
            else if ((DAT_40002d31 & 4) == 0) {
              DAT_40001909 = DAT_40001909 & 0xf8;
            }
          }
          else if (discrete_input_state == '\0') {
            if ((DAT_40002d2e & 4) == 0) {
              DAT_40001908 = DAT_40001908 & 0xf8;
            }
          }
          else if ((DAT_40002d31 & 4) == 0) {
            DAT_40001908 = DAT_40001908 & 0xf7;
          }
          if ((DAT_400018c8 & 4) == 0) {
            if (DAT_400023a1 == '\0') {
              if ((DAT_40002d34 & 4) == 0) {
                DAT_40001909 = DAT_40001909 & 0xfb;
              }
            }
            else if ((DAT_40002d37 & 4) == 0) {
              DAT_40001909 = DAT_40001909 & 0xf4;
            }
          }
          else if (DAT_400023a1 == '\0') {
            if ((DAT_40002d34 & 4) == 0) {
              DAT_40001908 = DAT_40001908 & 0xf4;
            }
          }
          else if ((DAT_40002d37 & 4) == 0) {
            DAT_40001908 = DAT_40001908 & 0xfb;
          }
          DAT_4000190a = FUN_00065bd0(DAT_40001908);
          DAT_4000190b = FUN_00065bd0(DAT_40001909);
          if ((uint)DAT_4000190a + (uint)DAT_4000190b == 0) {
            FUN_00065ca0(DAT_40001906,DAT_40001907,DAT_40001904,DAT_40001905);
          }
          else {
            FUN_00065ca0(DAT_4000190a,DAT_4000190b,DAT_40001908,DAT_40001909);
          }
        }
      }
    }
  }
  return;
}



undefined8 expected_ratio_for_gear(enum_t6e_gear param_1)

{
  undefined8 ratio;
  
  if (param_1 == GEAR_1) {
    ratio = 8;
  }
  else if (param_1 == GEAR_2) {
    ratio = 10;
  }
  else if (param_1 == GEAR_3) {
    ratio = 9;
  }
  else if (param_1 == GEAR_4) {
    ratio = 12;
  }
  else if (param_1 == GEAR_5) {
    ratio = 5;
  }
  else {
    ratio = 0;
    if (param_1 == GEAR_6) {
      ratio = 6;
    }
  }
  return ratio;
}



undefined8 FUN_00065ab0(char param_1)

{
  undefined8 uVar1;
  
  if (param_1 == '\0') {
    uVar1 = 0;
  }
  else if (param_1 == '\x01') {
    uVar1 = 8;
  }
  else if (param_1 == '\x02') {
    uVar1 = 10;
  }
  else if (param_1 == '\x03') {
    uVar1 = 9;
  }
  else if (param_1 == '\x04') {
    uVar1 = 0xc;
  }
  else if (param_1 == '\x05') {
    uVar1 = 5;
  }
  else {
    uVar1 = 0;
    if (param_1 == '\x06') {
      uVar1 = 6;
    }
  }
  return uVar1;
}



undefined8 FUN_00065b40(char param_1)

{
  undefined8 uVar1;
  
  if (param_1 == '\0') {
    uVar1 = 0;
  }
  else if (param_1 == '\x01') {
    uVar1 = 7;
  }
  else if (param_1 == '\x02') {
    uVar1 = 5;
  }
  else if (param_1 == '\x03') {
    uVar1 = 4;
  }
  else if (param_1 == '\x04') {
    uVar1 = 0;
  }
  else if (param_1 == '\x05') {
    uVar1 = 8;
  }
  else {
    uVar1 = 0;
    if (param_1 == '\x06') {
      uVar1 = 9;
    }
  }
  return uVar1;
}



longlong FUN_00065bd0(ulonglong param_1)

{
  return ((-((longlong)(-(param_1 & 4) << 0x20) >> 0x3f) -
          ((longlong)(-(param_1 & 8) << 0x20) >> 0x3f)) -
         ((longlong)(-(param_1 & 2) << 0x20) >> 0x3f)) -
         ((longlong)(-(param_1 & 1) << 0x20) >> 0x3f);
}



void FUN_00065c4c(void)

{
  DAT_400018c4 = DAT_400018c4 & 0xcc;
  DAT_400018c5 = DAT_400018c5 & 0xcc;
  DAT_400018c6 = DAT_400018c6 & 0xcc;
  DAT_400018c7 = DAT_400018c7 & 0xcc;
  return;
}



void FUN_00065ca0(char param_1,char param_2,ulonglong param_3,ulonglong param_4)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  
  bVar1 = DAT_400018c7;
  if (param_1 != '\0') {
    bVar1 = DAT_400018c4 | 1;
    if ((param_3 & 8) == 0) {
      bVar1 = DAT_400018c4;
    }
    bVar2 = DAT_400018c5 | 1;
    if ((param_3 & 4) == 0) {
      bVar2 = DAT_400018c5;
    }
    bVar3 = DAT_400018c6 | 1;
    if ((param_3 & 2) == 0) {
      bVar3 = DAT_400018c6;
    }
    DAT_400018c4 = bVar1;
    DAT_400018c5 = bVar2;
    DAT_400018c6 = bVar3;
    bVar1 = DAT_400018c7 | 1;
    if ((param_3 & 1) == 0) {
      bVar1 = DAT_400018c7;
    }
  }
  DAT_400018c7 = bVar1;
  bVar1 = DAT_400018c7;
  if (param_2 != '\0') {
    bVar1 = DAT_400018c4 | 2;
    if ((param_4 & 8) == 0) {
      bVar1 = DAT_400018c4;
    }
    bVar2 = DAT_400018c5 | 2;
    if ((param_4 & 4) == 0) {
      bVar2 = DAT_400018c5;
    }
    bVar3 = DAT_400018c6 | 2;
    if ((param_4 & 2) == 0) {
      bVar3 = DAT_400018c6;
    }
    DAT_400018c4 = bVar1;
    DAT_400018c5 = bVar2;
    DAT_400018c6 = bVar3;
    bVar1 = DAT_400018c7 | 2;
    if ((param_4 & 1) == 0) {
      bVar1 = DAT_400018c7;
    }
  }
  DAT_400018c7 = bVar1;
  return;
}



void FUN_00065ddc(char param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  
  if ((byte)(param_1 - 1U) < 6) {
    DAT_40001911 = FUN_00065ab0(param_1);
    DAT_40001912 = FUN_00065b40(param_1);
    bVar1 = DAT_400018c4 | 0x10;
    if ((DAT_40001911 & 8) == 0) {
      bVar1 = DAT_400018c4;
    }
    bVar2 = DAT_400018c5 | 0x10;
    if ((DAT_40001911 & 4) == 0) {
      bVar2 = DAT_400018c5;
    }
    bVar3 = DAT_400018c6 | 0x10;
    if ((DAT_40001911 & 2) == 0) {
      bVar3 = DAT_400018c6;
    }
    bVar4 = DAT_400018c7 | 0x10;
    if ((DAT_40001911 & 1) == 0) {
      bVar4 = DAT_400018c7;
    }
    DAT_400018c4 = bVar1 | 0x20;
    if ((DAT_40001912 & 8) == 0) {
      DAT_400018c4 = bVar1;
    }
    DAT_400018c5 = bVar2 | 0x20;
    if ((DAT_40001912 & 4) == 0) {
      DAT_400018c5 = bVar2;
    }
    DAT_400018c6 = bVar3 | 0x20;
    if ((DAT_40001912 & 2) == 0) {
      DAT_400018c6 = bVar3;
    }
    DAT_400018c7 = bVar4 | 0x20;
    if ((DAT_40001912 & 1) == 0) {
      DAT_400018c7 = bVar4;
    }
  }
  return;
}



void FUN_00065f4c(void)

{
  if (((((DAT_400015b8 & 1) != 0) && (engine_running != '\0')) &&
      ((byte)(ips_gear_cur - GEAR_1) < 6)) &&
     (((uint)DAT_4000e451 <= (vehicle_speed____ / 100 & 0xff) && (DAT_4000148d == -1)))) {
    if (ips_gear_cur == DAT_400018d3) {
      if (DAT_40001a48 < (int)(uint)DAT_4000e44e) {
        DAT_400018d5 = 0;
      }
      else {
        if (DAT_400018d5 != 0xff) {
          DAT_400018d5 = DAT_400018d5 + 1;
        }
        if (DAT_4000e44f <= DAT_400018d5) {
          DAT_400018d1 = DAT_400018d1 | (byte)(1 << (ips_gear_cur & 0x3f));
          DAT_400018d2 = DAT_400018d2 & ~(byte)(1 << (ips_gear_cur & 0x3f));
        }
      }
      if (DAT_400018d4 != 0xff) {
        DAT_400018d4 = DAT_400018d4 + 1;
      }
    }
    else {
      if (((DAT_400018d3 != NEUTRAL) && (((uint)DAT_400018d1 & 1 << (DAT_400018d3 & 0x3f)) == 0)) &&
         (DAT_4000e450 <= DAT_400018d4)) {
        DAT_400018d1 = 0;
        DAT_400018d2 = DAT_400018d2 | (byte)(1 << (DAT_400018d3 & 0x3f));
      }
      DAT_400018d5 = 0;
      DAT_400018d4 = 0;
    }
    DAT_400018d3 = ips_gear_cur;
  }
  return;
}



uint8_t count_set_bits(uint8_t flags)

{
  uint8_t uVar1;
  uint8_t count;
  uint i;
  
  count = '\0';
  for (i = 0; (i & 0b11111111) < 8; i = i + 1) {
    uVar1 = count + '\x01';
    if (((uint)flags & 1 << (i & 0b00111111)) == 0) {
      uVar1 = count;
    }
    count = uVar1;
  }
  return count;
}



void FUN_00066154(void)

{
  DAT_400018cb = DAT_4000e33a;
  DAT_400018d6 = DAT_4000e33b;
  DAT_400018d7 = DAT_4000e33c;
  DAT_400018dd = DAT_4000e354;
  DAT_400018e0 = DAT_4000e355;
  DAT_400018e2 = DAT_4000e356;
  DAT_400018e4 = DAT_4000e357;
  DAT_400018e6 = DAT_4000e358;
  DAT_400018e8 = DAT_4000e359;
  DAT_400018ea = DAT_4000e35a;
  DAT_400018ec = DAT_4000e35b;
  DAT_400018ee = DAT_4000e363;
  DAT_400018f0 = DAT_4000e349;
  DAT_400018f2 = DAT_4000e34a;
  DAT_400018f4 = DAT_4000e34b;
  DAT_400018f6 = DAT_4000e34c;
  DAT_400018cc = 0;
  DAT_400018cd = 0;
  DAT_400018d0 = 0;
  DAT_400018d1 = 0;
  DAT_400018d2 = 0;
  DAT_400018d3 = 0;
  DAT_400018d4 = 0;
  DAT_400018d5 = 0;
  DAT_400018d8 = 0;
  DAT_400018de = 0;
  DAT_400018e1 = 0;
  DAT_400018e3 = 0;
  DAT_400018e5 = 0;
  DAT_400018e7 = 0;
  DAT_400018e9 = 0;
  DAT_400018eb = 0;
  DAT_400018ed = 0;
  DAT_400018ef = 0;
  DAT_400018f1 = 0;
  DAT_400018f3 = 0;
  DAT_400018f5 = 0;
  DAT_400018f7 = 0;
  DAT_400018bf = 0;
  DAT_400018ce = 0;
  DAT_400018c1 = 0;
  DAT_400018c2 = 0;
  DAT_400018c3 = 0;
  DAT_400018c4 = 0;
  DAT_400018c5 = 0;
  DAT_400018c6 = 0;
  DAT_400018c7 = 0;
  DAT_400018c0 = 0;
  DAT_400018d9 = 0;
  DAT_400018da = 0;
  DAT_400018db = 0;
  obd_set_new_DTC(&DAT_4000e268,&DAT_40002d01,0x741,0);
  obd_set_new_DTC(&DAT_4000e269,&DAT_40002d04,0x746,0);
  obd_set_new_DTC(&DAT_4000e26a,&DAT_40002d07,0x748,0);
  obd_set_new_DTC(&DAT_4000e282,&DAT_40002d0a,0x751,0);
  obd_set_new_DTC(&DAT_4000e283,&DAT_40002d0d,0x753,0);
  obd_set_new_DTC(&DAT_4000e284,&DAT_40002d10,0x756,0);
  obd_set_new_DTC(&DAT_4000e285,&DAT_40002d13,0x758,0);
  obd_set_new_DTC(&DAT_4000e286,&DAT_40002d16,0x761,0);
  obd_set_new_DTC(&DAT_4000e287,&DAT_40002d19,0x763,0);
  obd_set_new_DTC(&DAT_4000e288,&DAT_40002d1c,0x766,0);
  obd_set_new_DTC(&DAT_4000e289,&DAT_40002d1f,0x768,0);
  obd_set_new_DTC(&CAL_obd_P0894_cfg,&obd_P0894_dtc_state,0x894,0);
  obd_set_new_DTC(&DAT_4000e291,&DAT_40002d4f,&DAT_00001657,0);
  obd_set_new_DTC(&DAT_4000e277,&DAT_40002d8e,&DAT_00002757,0);
  obd_set_new_DTC(&DAT_4000e278,&DAT_40002d91,&DAT_00002759,0);
  obd_set_new_DTC(&DAT_4000e279,&DAT_40002d94,&DAT_00002769,0);
  obd_set_new_DTC(&DAT_4000e27a,&DAT_40002d97,&DAT_00002770,0);
  return;
}



void FUN_00066674(void)

{
  obd_ii_dtc_aging_heal(&DAT_4000e268,&DAT_40002d01,&DAT_40002d02,&DAT_40002d03,0x741,0);
  obd_ii_dtc_aging_heal(&DAT_4000e269,&DAT_40002d04,&DAT_40002d05,&DAT_40002d06,0x746,0);
  obd_ii_dtc_aging_heal(&DAT_4000e26a,&DAT_40002d07,&DAT_40002d08,&DAT_40002d09,0x748,0);
  obd_ii_dtc_aging_heal(&DAT_4000e282,&DAT_40002d0a,&DAT_40002d0b,&DAT_40002d0c,0x751,0);
  obd_ii_dtc_aging_heal(&DAT_4000e283,&DAT_40002d0d,&DAT_40002d0e,&DAT_40002d0f,0x753,0);
  obd_ii_dtc_aging_heal(&DAT_4000e284,&DAT_40002d10,&DAT_40002d11,&DAT_40002d12,0x756,0);
  obd_ii_dtc_aging_heal(&DAT_4000e285,&DAT_40002d13,&DAT_40002d14,&DAT_40002d15,0x758,0);
  obd_ii_dtc_aging_heal(&DAT_4000e286,&DAT_40002d16,&DAT_40002d17,&DAT_40002d18,0x761,0);
  obd_ii_dtc_aging_heal(&DAT_4000e287,&DAT_40002d19,&DAT_40002d1a,&DAT_40002d1b,0x763,0);
  obd_ii_dtc_aging_heal(&DAT_4000e288,&DAT_40002d1c,&DAT_40002d1d,&DAT_40002d1e,0x766,0);
  obd_ii_dtc_aging_heal(&DAT_4000e289,&DAT_40002d1f,&DAT_40002d20,&DAT_40002d21,0x768,0);
  obd_ii_dtc_aging_heal(&CAL_obd_P0894_cfg,&obd_P0894_dtc_state,&DAT_40002d47,&DAT_40002d48,0x894,0)
  ;
  obd_ii_dtc_aging_heal(&DAT_4000e291,&DAT_40002d4f,&DAT_40002d50,&DAT_40002d51,&DAT_00001657,0);
  obd_ii_dtc_aging_heal(&DAT_4000e277,&DAT_40002d8e,&DAT_40002d8f,&DAT_40002d90,&DAT_00002757,0);
  obd_ii_dtc_aging_heal(&DAT_4000e278,&DAT_40002d91,&DAT_40002d92,&DAT_40002d93,&DAT_00002759,0);
  obd_ii_dtc_aging_heal(&DAT_4000e279,&DAT_40002d94,&DAT_40002d95,&DAT_40002d96,&DAT_00002769,0);
  obd_ii_dtc_aging_heal(&DAT_4000e27a,&DAT_40002d97,&DAT_40002d98,&DAT_40002d99,&DAT_00002770,0);
  return;
}



void FUN_00066b14(void)

{
  bool bVar1;
  short sVar3;
  int iVar2;
  
  if ((((DAT_400015b8 & 1) == 0) || (DAT_40001512 <= DAT_4000e4c6)) ||
     ((driver_input_flags[1] & 1) != 0)) {
    DAT_40001450 = 0x8a;
    DAT_4000191e = DAT_4000e4c7;
    DAT_4000191f = DAT_4000e4c8;
    DAT_40001920 = DAT_4000e4ca;
    DAT_40001921 = DAT_4000e498;
    DAT_40001922 = DAT_4000e499;
    DAT_40001923 = DAT_4000e49b;
  }
  else {
    if ((DAT_40001450 & 1) == 0) {
      bVar1 = DAT_4000191e == '\0';
      DAT_4000191e = DAT_4000191e + -1;
      if (bVar1) {
        DAT_40001450 = DAT_40001450 & 0xfffd;
        DAT_4000191e = DAT_4000e4c7;
        FUN_0006814c();
      }
    }
    else {
      DAT_40001450 = DAT_40001450 & 0xfffe | 2;
      DAT_4000191e = DAT_4000e4c7;
    }
    if ((DAT_40001450 & 4) == 0) {
      bVar1 = DAT_4000191f == '\0';
      DAT_4000191f = DAT_4000191f + -1;
      if (bVar1) {
        DAT_40001450 = DAT_40001450 & 0xfff7;
        DAT_4000191f = DAT_4000e4c8;
        FUN_00068160();
      }
    }
    else {
      DAT_40001450 = DAT_40001450 & 0xfffb | 8;
      DAT_4000191f = DAT_4000e4c8;
    }
    if ((DAT_40001450 & 0x40) == 0) {
      bVar1 = DAT_40001920 == '\0';
      DAT_40001920 = DAT_40001920 + -1;
      if (bVar1) {
        DAT_40001450 = DAT_40001450 & 0xff7f;
        DAT_40001920 = DAT_4000e4ca;
        FUN_000681a4();
      }
    }
    else {
      DAT_40001450 = DAT_40001450 & 0xffbf | 0x80;
      DAT_40001920 = DAT_4000e4ca;
    }
    if ((DAT_40001450 & 0x100) == 0) {
      DAT_40001450 = DAT_40001450 & 0xfdff;
      DAT_40001921 = DAT_4000e498;
    }
    else {
      bVar1 = DAT_40001921 == '\0';
      DAT_40001921 = DAT_40001921 + -1;
      if (bVar1) {
        DAT_40001450 = DAT_40001450 | 0x200;
        DAT_40001921 = DAT_4000e498;
      }
    }
    if ((DAT_40001450 & 0x400) == 0) {
      DAT_40001450 = DAT_40001450 & 0xf7ff;
      DAT_40001922 = DAT_4000e499;
    }
    else {
      bVar1 = DAT_40001922 == '\0';
      DAT_40001922 = DAT_40001922 + -1;
      if (bVar1) {
        DAT_40001450 = DAT_40001450 | 0x800;
        DAT_40001922 = DAT_4000e499;
      }
    }
    if ((DAT_40001450 & 0x4000) == 0) {
      DAT_40001450 = DAT_40001450 & 0x7fff;
      DAT_40001923 = DAT_4000e49b;
    }
    else {
      bVar1 = DAT_40001923 == '\0';
      DAT_40001923 = DAT_40001923 + -1;
      if (bVar1) {
        DAT_40001450 = DAT_40001450 | 0x8000;
        DAT_40001923 = DAT_4000e49b;
      }
    }
  }
  if ((((DAT_400015b8 & 1) == 0) || (DAT_4000171f == '\x02')) ||
     ((engine_running == '\0' && ((DAT_40002db2 & 4) == 0)))) {
    DAT_40001452 = 0xaa;
    DAT_40001924 = DAT_4000e4cc;
    DAT_40001925 = DAT_4000e4cd;
    DAT_40001926 = DAT_4000e4ce;
    DAT_40001927 = DAT_4000e4cf;
    DAT_40001453 = 2;
    DAT_4000192a = DAT_4000e4d0;
    DAT_4000192b = DAT_4000e49c;
    DAT_4000192c = (ushort)DAT_4000e49a * 0x14;
    DAT_40001454 = 2;
    DAT_4000192f = DAT_4000e4d1;
  }
  else {
    if (((uint)COD_unknown._4_4_ >> 9 & 1) == 0) {
      DAT_40001452 = 0;
      DAT_40001924 = '\0';
      DAT_40001925 = '\0';
      DAT_40001926 = '\0';
      DAT_40001927 = '\0';
    }
    else {
      if ((DAT_40001452 & 1) == 0) {
        bVar1 = DAT_40001924 == '\0';
        DAT_40001924 = DAT_40001924 + -1;
        if (bVar1) {
          DAT_40001452 = DAT_40001452 & 0xfd;
          DAT_40001924 = DAT_4000e4cc;
        }
      }
      else {
        DAT_40001452 = DAT_40001452 & 0xfe | 2;
        DAT_40001924 = DAT_4000e4cc;
      }
      if ((DAT_40001452 & 4) == 0) {
        bVar1 = DAT_40001925 == '\0';
        DAT_40001925 = DAT_40001925 + -1;
        if (bVar1) {
          DAT_40001452 = DAT_40001452 & 0xf7;
          DAT_40001925 = DAT_4000e4cd;
          FUN_00068210();
        }
      }
      else {
        DAT_40001452 = DAT_40001452 & 0xfb | 8;
        DAT_40001925 = DAT_4000e4cd;
      }
      if ((DAT_40001452 & 0x10) == 0) {
        bVar1 = DAT_40001926 == '\0';
        DAT_40001926 = DAT_40001926 + -1;
        if (bVar1) {
          DAT_40001452 = DAT_40001452 & 0xdf;
          DAT_40001926 = DAT_4000e4ce;
          FUN_00068224();
        }
      }
      else {
        DAT_40001452 = DAT_40001452 & 0xef | 0x20;
        DAT_40001926 = DAT_4000e4ce;
      }
      if ((DAT_40001452 & 0x40) == 0) {
        bVar1 = DAT_40001927 == '\0';
        DAT_40001927 = DAT_40001927 + -1;
        if (bVar1) {
          DAT_40001452 = DAT_40001452 & 0x7f;
          DAT_40001927 = DAT_4000e4cf;
          FUN_00068278();
        }
      }
      else {
        DAT_40001452 = DAT_40001452 & 0xbf | 0x80;
        DAT_40001927 = DAT_4000e4cf;
      }
    }
    if (((uint)COD_unknown._4_4_ >> 0xb & 1) == 0) {
      DAT_40001453 = 0;
      DAT_4000192a = '\0';
      DAT_4000192b = '\0';
      DAT_4000192c = 0;
    }
    else {
      if ((DAT_40001453 & 1) == 0) {
        bVar1 = DAT_4000192a == '\0';
        DAT_4000192a = DAT_4000192a + -1;
        if (bVar1) {
          DAT_40001453 = DAT_40001453 & 0xfd;
          DAT_4000192a = DAT_4000e4d0;
        }
      }
      else {
        DAT_40001453 = DAT_40001453 & 0xfe | 2;
        DAT_4000192a = DAT_4000e4d0;
      }
      if ((DAT_40001453 & 4) == 0) {
        DAT_40001453 = DAT_40001453 & 0xf7;
        DAT_4000192b = DAT_4000e49c;
      }
      else {
        bVar1 = DAT_4000192b == '\0';
        DAT_4000192b = DAT_4000192b + -1;
        if (bVar1) {
          DAT_40001453 = DAT_40001453 | 8;
          DAT_4000192b = DAT_4000e49c;
          FUN_000682d0();
        }
      }
      if ((((DAT_40001453 & 2) == 0) || ((DAT_40001452 & 2) == 0)) ||
         (((DAT_40001678 & 4) != 0 ||
          ((((sVar3 = FUN_00056164(), sVar3 == 0x3fff || ((DAT_40001453 & 4) != 0)) ||
            (vehicle_speed____ != 0)) || (output_shaft_rpm != 0)))))) {
        DAT_4000192c = (ushort)DAT_4000e49a * 0x14;
      }
      else {
        iVar2 = int_abs(DAT_40001712);
        if ((int)(uint)DAT_4000e49d < iVar2) {
          bVar1 = DAT_4000192c == 0;
          DAT_4000192c = DAT_4000192c + -1;
          if (bVar1) {
            DAT_40001453 = DAT_40001453 | 0x10;
            DAT_4000192c = (ushort)DAT_4000e49a * 0x14;
          }
        }
        else {
          DAT_40001453 = DAT_40001453 & 0xef;
          DAT_4000192c = (ushort)DAT_4000e49a * 0x14;
        }
      }
    }
    if (((uint)COD_unknown._4_4_ >> 0xc & 1) == 0) {
      DAT_40001454 = 0;
      DAT_4000192f = '\0';
    }
    else if ((DAT_40001454 & 1) == 0) {
      bVar1 = DAT_4000192f == '\0';
      DAT_4000192f = DAT_4000192f + -1;
      if (bVar1) {
        DAT_40001454 = DAT_40001454 & 0xfd;
        DAT_4000192f = DAT_4000e4d1;
        FUN_000682b4();
      }
    }
    else {
      DAT_40001454 = DAT_40001454 & 0xfe | 2;
      DAT_4000192f = DAT_4000e4d1;
    }
  }
  if (((DAT_400015b8 & 1) == 0) || ((tach_rpm == 0 && ((DAT_40002db2 & 4) == 0)))) {
    DAT_40001455 = 2;
    DAT_40001931 = DAT_4000e4d2;
  }
  else {
    DAT_40001456 = DAT_40001456 + -1;
    if (DAT_40001456 == '\0') {
      DAT_40001456 = '2';
      if (((uint)COD_unknown._4_4_ >> 10 & 1) == 0) {
        DAT_40001455 = 0;
        DAT_40001931 = '\0';
      }
      else if ((DAT_40001455 & 1) == 0) {
        bVar1 = DAT_40001931 == '\0';
        DAT_40001931 = DAT_40001931 + -1;
        if (bVar1) {
          DAT_40001455 = DAT_40001455 & 0xfd;
          DAT_40001931 = DAT_4000e4d2;
        }
      }
      else {
        DAT_40001455 = DAT_40001455 & 0xfe | 2;
        DAT_40001931 = DAT_4000e4d2;
      }
    }
  }
  return;
}



void FUN_000675b4(void)

{
  if (((DAT_400015b8 & 1) != 0) && (DAT_4000e4c6 < DAT_40001512)) {
    if ((DAT_4000e2e8 & 7) != 0) {
      if ((((DAT_40001450 & 2) == 0) || ((DAT_40001450 & 8) == 0)) || ((DAT_40001450 & 0x80) == 0))
      {
        if ((DAT_4000191b != 0) && (DAT_4000191b = DAT_4000191b - 1, DAT_4000191b == 0)) {
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e2e8,&DAT_40002db2,&DAT_40002db3,&DAT_40002db4,0x100,3);
        }
      }
      else {
        obd_ii_monitor_pass(&DAT_4000e2e8,&DAT_40002db2);
        if (DAT_4000191b < DAT_4000e3d6) {
          DAT_4000191b = DAT_4000191b + 1;
        }
      }
    }
    if ((DAT_4000e2ef & 7) != 0) {
      if ((((DAT_40001450 & 0x80) == 0) || (DAT_4000191a == '\0')) ||
         (ips_calibration_flags == (byte)(DAT_40008f81 << 4 | 6U))) {
        if (ips_calibration_flags == (byte)(DAT_40008f81 << 4 | 6U)) {
          obd_ii_monitor_pass(&DAT_4000e2ef,&DAT_40002dc1);
          if (DAT_4000191c < DAT_4000e3dd) {
            DAT_4000191c = DAT_4000191c + 1;
          }
        }
      }
      else if ((DAT_4000191c != 0) && (DAT_4000191c = DAT_4000191c - 1, DAT_4000191c == 0)) {
        obd_ii_dtc_confirm_and_freeze
                  (&DAT_4000e2ef,&DAT_40002dc1,&DAT_40002dc2,&DAT_40002dc3,0x301,3);
      }
    }
    if ((DAT_4000e2ed & 7) != 0) {
      if ((((DAT_40001450 & 0x200) == 0) && ((DAT_40001450 & 0x800) == 0)) &&
         ((DAT_40001450 & 0x8000) == 0)) {
        if ((DAT_40001450 & 0x4500) == 0) {
          obd_ii_monitor_pass(&DAT_4000e2ed,&DAT_40002dc4);
          if (DAT_4000191d < DAT_4000e3db) {
            DAT_4000191d = DAT_4000191d + 1;
          }
        }
      }
      else if ((DAT_4000191d != 0) && (DAT_4000191d = DAT_4000191d - 1, DAT_4000191d == 0)) {
        obd_ii_dtc_confirm_and_freeze
                  (&DAT_4000e2ed,&DAT_40002dc4,&DAT_40002dc5,&DAT_40002dc6,0x401,3);
      }
    }
    if ((tach_rpm != 0) || ((DAT_40002db2 & 4) != 0)) {
      if ((((uint)COD_unknown._4_4_ >> 9 & 1) != 0) && ((DAT_4000e2e9 & 7) != 0)) {
        if (((((DAT_40001452 & 2) == 0) || ((DAT_40001452 & 8) == 0)) ||
            ((DAT_40001452 & 0x20) == 0)) || ((DAT_40001452 & 0x80) == 0)) {
          if ((DAT_40001918 != 0) && (DAT_40001918 = DAT_40001918 - 1, DAT_40001918 == 0)) {
            obd_ii_dtc_confirm_and_freeze
                      (&DAT_4000e2e9,&DAT_40002db5,&DAT_40002db6,&DAT_40002db7,0x122,3);
          }
        }
        else {
          obd_ii_monitor_pass(&DAT_4000e2e9,&DAT_40002db5);
          if (DAT_40001918 < DAT_4000e3d7) {
            DAT_40001918 = DAT_40001918 + 1;
          }
        }
      }
      if ((((uint)COD_unknown._4_4_ >> 0xb & 1) != 0) && ((DAT_4000e2ea & 7) != 0)) {
        if ((DAT_40001453 & 2) == 0) {
          if ((DAT_40001928 != 0) && (DAT_40001928 = DAT_40001928 - 1, DAT_40001928 == 0)) {
            obd_ii_dtc_confirm_and_freeze
                      (&DAT_4000e2ea,&DAT_40002db8,&DAT_40002db9,&DAT_40002dba,291,3);
          }
        }
        else {
          obd_ii_monitor_pass(&DAT_4000e2ea,&DAT_40002db8);
          if (DAT_40001928 < DAT_4000e3d8) {
            DAT_40001928 = DAT_40001928 + 1;
          }
        }
      }
      if ((((uint)COD_unknown._4_4_ >> 0xb & 1) != 0) && ((DAT_4000e2ee & 7) != 0)) {
        if (((DAT_40001453 & 8) == 0) && ((DAT_40001453 & 0x10) == 0)) {
          obd_ii_monitor_pass(&DAT_4000e2ee,&DAT_40002dc7);
          if (DAT_40001929 < DAT_4000e3dc) {
            DAT_40001929 = DAT_40001929 + 1;
          }
        }
        else if ((DAT_40001929 != 0) && (DAT_40001929 = DAT_40001929 - 1, DAT_40001929 == 0)) {
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e2ee,&DAT_40002dc7,&DAT_40002dc8,&DAT_40002dc9,0x513,3);
        }
      }
      if ((((uint)COD_unknown._4_4_ >> 0xc & 1) != 0) && ((DAT_4000e2eb & 7) != 0)) {
        if ((DAT_40001454 & 2) == 0) {
          if ((DAT_4000192e != 0) && (DAT_4000192e = DAT_4000192e - 1, DAT_4000192e == 0)) {
            obd_ii_dtc_confirm_and_freeze
                      (&DAT_4000e2eb,&DAT_40002dbb,&DAT_40002dbc,&DAT_40002dbd,0x126,3);
          }
        }
        else {
          obd_ii_monitor_pass(&DAT_4000e2eb,&DAT_40002dbb);
          if (DAT_4000192e < DAT_4000e3d9) {
            DAT_4000192e = DAT_4000192e + 1;
          }
        }
      }
      if ((((uint)COD_unknown._4_4_ >> 10 & 1) != 0) && ((DAT_4000e2ec & 7) != 0)) {
        if ((DAT_40001455 & 2) == 0) {
          if ((DAT_40001930 != 0) && (DAT_40001930 = DAT_40001930 - 1, DAT_40001930 == 0)) {
            obd_ii_dtc_confirm_and_freeze
                      (&DAT_4000e2ec,&DAT_40002dbe,&DAT_40002dbf,&DAT_40002dc0,0x155,3);
          }
        }
        else {
          obd_ii_monitor_pass(&DAT_4000e2ec,&DAT_40002dbe);
          if (DAT_40001930 < DAT_4000e3da) {
            DAT_40001930 = DAT_40001930 + 1;
          }
        }
      }
    }
  }
  if ((((((DAT_40002db2 & 8) == 0) || ((DAT_40002db2 & 4) == 0)) || ((DAT_40002db2 & 1) == 0)) &&
      ((((DAT_40002dc1 & 8) == 0 || ((DAT_40002dc1 & 4) == 0)) || ((DAT_40002dc1 & 1) == 0)))) &&
     ((((DAT_40002dc4 & 8) == 0 || ((DAT_40002dc4 & 4) == 0)) || ((DAT_40002dc4 & 1) == 0)))) {
    DAT_40001678 = DAT_40001678 & 0xfffbffff;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x40000;
  }
  if ((((DAT_40002db5 & 8) == 0) || ((DAT_40002db5 & 4) == 0)) || ((DAT_40002db5 & 1) == 0)) {
    DAT_40001678 = DAT_40001678 & 0xfff7ffff;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x80000;
  }
  if (((((DAT_40002db8 & 8) == 0) || ((DAT_40002db8 & 4) == 0)) || ((DAT_40002db8 & 1) == 0)) &&
     ((((DAT_40002dc7 & 8) == 0 || ((DAT_40002dc7 & 4) == 0)) || ((DAT_40002dc7 & 1) == 0)))) {
    DAT_40001678 = DAT_40001678 & 0xffefffff;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x100000;
  }
  if ((((DAT_40002dbb & 8) == 0) || ((DAT_40002dbb & 4) == 0)) || ((DAT_40002dbb & 1) == 0)) {
    DAT_40001678 = DAT_40001678 & 0xffdfffff;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x200000;
  }
  if ((((DAT_40002dbe & 8) == 0) || ((DAT_40002dbe & 4) == 0)) || ((DAT_40002dbe & 1) == 0)) {
    DAT_40001678 = DAT_40001678 & 0xffbfffff;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x400000;
  }
  return;
}



void FUN_0006814c(void)

{
  DAT_4000172a = 0;
  torque_alphaN_raw = 0;
  return;
}



void FUN_00068160(void)

{
  tach_rpm = 0;
  tps_commanded = '\0';
  DAT_4000171e = DAT_4000171e & 0xef | 0x20;
  driver_input_flags[1] = '\0';
  driver_input_flags[0] = '\0';
  return;
}



void FUN_000681a4(void)

{
  tps = '\0';
  engine_flag_1 = 0;
  paddle_shift_flags = 0;
  auto_mode_active = false;
  ips_calibration_flags = 0;
  DAT_4000191a = 0;
  cruise_target_kph = 0;
  cruise_status_flags = 0;
  revlimit_hard_from_ecu = 3000;
  DAT_40001ac5 = DAT_40001ac5 & 0xbf;
  DAT_40001ac6 = DAT_40001ac6 & 0xbf;
  return;
}



void FUN_00068210(void)

{
  DAT_4000171e = DAT_4000171e | 2;
  return;
}



void FUN_00068224(void)

{
  DAT_40001720 = DAT_40001720 & 0xf3;
  DAT_40001721 = 0;
  DAT_40001ac5 = DAT_40001ac5 & 0xfe;
  DAT_40001ac6 = DAT_40001ac6 & 0xfe;
  DAT_4000171f = 0;
  return;
}



void FUN_00068278(void)

{
  DAT_40001722 = 0;
  DAT_40001723 = 0;
  DAT_40001720 = DAT_40001720 & 0xfc;
  DAT_4000171c = 0x38f;
  return;
}



void FUN_000682b4(void)

{
  DAT_40001718 = 0;
  DAT_40001716 = 0;
  DAT_40001715 = 0;
  return;
}



void FUN_000682d0(void)

{
  DAT_40001712 = 0;
  DAT_40001710 = 0;
  DAT_4000170e = 0;
  return;
}



void FUN_000682ec(void)

{
  DAT_4000191b = DAT_4000e3d6;
  DAT_40001918 = DAT_4000e3d7;
  DAT_40001928 = DAT_4000e3d8;
  DAT_4000192e = DAT_4000e3d9;
  DAT_40001930 = DAT_4000e3da;
  DAT_4000191c = DAT_4000e3dd;
  DAT_4000191d = DAT_4000e3db;
  DAT_40001929 = DAT_4000e3dc;
  ips_calibration_flags = 0;
  DAT_4000191a = 0;
  DAT_40001450 = 0x8a;
  DAT_40001452 = 0xaa;
  DAT_40001453 = 2;
  DAT_40001454 = 2;
  DAT_40001455 = 2;
  DAT_4000191e = DAT_4000e4c7;
  DAT_4000191f = DAT_4000e4c8;
  DAT_40001920 = DAT_4000e4ca;
  DAT_40001921 = DAT_4000e498;
  DAT_40001922 = DAT_4000e499;
  DAT_40001923 = DAT_4000e49b;
  DAT_40001924 = DAT_4000e4cc;
  DAT_40001925 = DAT_4000e4cd;
  DAT_40001926 = DAT_4000e4ce;
  DAT_40001927 = DAT_4000e4cf;
  DAT_4000192a = DAT_4000e4d0;
  DAT_4000192b = DAT_4000e49c;
  DAT_4000192c = (ushort)DAT_4000e49a * 0x14;
  DAT_4000192f = DAT_4000e4d1;
  DAT_40001931 = DAT_4000e4d2;
  obd_set_new_DTC(&DAT_4000e2e8,&DAT_40002db2,0x100,3);
  obd_set_new_DTC(&DAT_4000e2e9,&DAT_40002db5,0x122,3);
  obd_set_new_DTC(&DAT_4000e2ea,&DAT_40002db8,0x123,3);
  obd_set_new_DTC(&DAT_4000e2eb,&DAT_40002dbb,0x126,3);
  obd_set_new_DTC(&DAT_4000e2ec,&DAT_40002dbe,0x155,3);
  obd_set_new_DTC(&DAT_4000e2ef,&DAT_40002dc1,0x301,3);
  obd_set_new_DTC(&DAT_4000e2ed,&DAT_40002dc4,0x401,3);
  obd_set_new_DTC(&DAT_4000e2ee,&DAT_40002dc7,0x513,3);
  return;
}



void FUN_00068618(void)

{
  obd_ii_dtc_aging_heal(&DAT_4000e2e8,&DAT_40002db2,&DAT_40002db3,&DAT_40002db4,0x100,3);
  obd_ii_dtc_aging_heal(&DAT_4000e2e9,&DAT_40002db5,&DAT_40002db6,&DAT_40002db7,0x122,3);
  obd_ii_dtc_aging_heal(&DAT_4000e2ea,&DAT_40002db8,&DAT_40002db9,&DAT_40002dba,0x123,3);
  obd_ii_dtc_aging_heal(&DAT_4000e2eb,&DAT_40002dbb,&DAT_40002dbc,&DAT_40002dbd,0x126,3);
  obd_ii_dtc_aging_heal(&DAT_4000e2ec,&DAT_40002dbe,&DAT_40002dbf,&DAT_40002dc0,0x155,3);
  obd_ii_dtc_aging_heal(&DAT_4000e2ef,&DAT_40002dc1,&DAT_40002dc2,&DAT_40002dc3,0x301,3);
  obd_ii_dtc_aging_heal(&DAT_4000e2ed,&DAT_40002dc4,&DAT_40002dc5,&DAT_40002dc6,0x401,3);
  obd_ii_dtc_aging_heal(&DAT_4000e2ee,&DAT_40002dc7,&DAT_40002dc8,&DAT_40002dc9,0x513,3);
  return;
}



void FUN_00068854(void)

{
  short sVar2;
  int iVar1;
  ushort uVar3;
  
  DAT_40001968 = DAT_40001968 & 0xfe;
  if (((((DAT_4000e28e & 7) != 0) && ((DAT_400015b8 & 1) != 0)) && ((DAT_40001678 & 1) == 0)) &&
     (((DAT_40001c39 == '\t' || (DAT_40001c39 == '\n')) ||
      ((DAT_40001c39 == '\0' || (DAT_40001c39 == -2)))))) {
    if ((DAT_40002374 < (uint)DAT_4000e4f1 * 100) && ((uint)DAT_4000e4f2 * 100 < DAT_40002374)) {
      DAT_40001968 = DAT_40001968 | 1;
      DAT_4000193d = 0;
      obd_ii_monitor_pass(&DAT_4000e28e,&DAT_40002cdd);
      if (DAT_4000193c < DAT_4000e360) {
        DAT_4000193c = DAT_4000193c + 1;
      }
    }
    else {
      DAT_4000193d = DAT_4000193d + 1;
      if ((DAT_40001676 <= (short)(ushort)DAT_4000193d) &&
         ((DAT_4000193d = 0, DAT_4000193c != 0 &&
          (DAT_4000193c = DAT_4000193c - 1, DAT_4000193c == 0)))) {
        obd_ii_dtc_confirm_and_freeze
                  (&DAT_4000e28e,&DAT_40002cdd,&DAT_40002cde,&DAT_40002cdf,0x705,0);
      }
    }
  }
  if (((((((s_AAAAAAAA_4000e294[0] & 7U) != 0) && ((DAT_40001678 & 1) == 0)) &&
        ((DAT_400015b8 & 1) != 0)) && ((DAT_40001c39 == '\t' && (DAT_40002bdc != '\0')))) &&
      (sVar2 = get_shift_lever_pos_raw___(), sVar2 != -1)) &&
     (((DAT_40001938 & 1) == 0 && (DAT_400017a4 != '\0')))) {
    if (shift_position_request_bits == 0) {
      DAT_4000194d = DAT_4000194d + 1;
      if (((DAT_40001676 <= (short)(ushort)DAT_4000194d) && (DAT_4000194d = 0, DAT_4000194c != 0))
         && (DAT_4000194c = DAT_4000194c - 1, DAT_4000194c == 0)) {
        shift_position_request_bits = 0x10;
        obd_ii_dtc_confirm_and_freeze
                  (s_AAAAAAAA_4000e294,&DAT_40002d58,&DAT_40002d59,&DAT_40002d5a,&DAT_00001801,0);
      }
    }
    else {
      DAT_4000194d = 0;
      obd_ii_monitor_pass(s_AAAAAAAA_4000e294,&DAT_40002d58);
      if (DAT_4000194c < DAT_4000e366) {
        DAT_4000194c = DAT_4000194c + 1;
      }
    }
  }
  if ((((((s_AAAAAAAA_4000e294[1] & 7U) != 0) && ((DAT_40001678 & 1) == 0)) &&
       (((DAT_400015b8 & 1) != 0 && ((DAT_40001c39 != '\t' && (DAT_40002bdc != '\0')))))) &&
      (sVar2 = get_shift_lever_pos_raw___(), sVar2 != -1)) &&
     (((DAT_40001938 & 1) == 0 && (DAT_400017a4 != '\0')))) {
    if ((((shift_position_request_bits & 0xf0) == 0) && ((shift_position_request_bits & 1) != 0)) &&
       ((((shift_position_request_bits & 2) != 0 || ((shift_position_request_bits & 4) != 0)) ||
        ((shift_position_request_bits & 8) != 0)))) {
      DAT_4000194f = DAT_4000194f + 1;
      if (((DAT_40001676 <= (short)(ushort)DAT_4000194f) && (DAT_4000194f = 0, DAT_4000194e != 0))
         && (DAT_4000194e = DAT_4000194e - 1, DAT_4000194e == 0)) {
        shift_position_request_bits = shift_position_request_bits | 0x10;
        obd_ii_dtc_confirm_and_freeze
                  (s_AAAAAAAA_4000e294 + 1,&DAT_40002d5b,&DAT_40002d5c,&DAT_40002d5d,&DAT_00001802,0
                  );
      }
    }
    else {
      DAT_4000194f = 0;
      obd_ii_monitor_pass(s_AAAAAAAA_4000e294 + 1,&DAT_40002d5b);
      if (DAT_4000194e < DAT_4000e367) {
        DAT_4000194e = DAT_4000194e + 1;
      }
    }
  }
  if ((((DAT_4000e2b3 & 7) == 0) || ((DAT_40001678 & 1) != 0)) ||
     (((DAT_400015b8 & 1) == 0 ||
      ((((DAT_40001c39 != '\t' || (DAT_40002bdc == '\0')) ||
        (sVar2 = get_shift_lever_pos_raw___(), sVar2 == -1)) ||
       (((DAT_40001938 & 1) != 0 || (DAT_400017a4 == '\0')))))))) {
    DAT_4000193f = 0;
    DAT_400017a3 = DAT_400017a3 & 0xfe;
  }
  else if (((shift_position_request_bits == 2) || (shift_position_request_bits == 4)) ||
          (shift_position_request_bits == 8)) {
    DAT_4000193f = DAT_4000193f + 1;
    if (DAT_40001676 <= (short)(ushort)DAT_4000193f) {
      DAT_4000193f = 0;
      DAT_400017a3 = DAT_400017a3 & 0xfe;
      if ((DAT_4000193e != 0) && (DAT_4000193e = DAT_4000193e - 1, DAT_4000193e == 0)) {
        obd_ii_dtc_confirm_and_freeze
                  (&DAT_4000e2b3,&DAT_40002dca,&DAT_40002dcb,&DAT_40002dcc,&DAT_00001904,0);
      }
    }
  }
  else {
    DAT_4000193f = 0;
    DAT_400017a3 = DAT_400017a3 & 0xfe;
    obd_ii_monitor_pass(&DAT_4000e2b3,&DAT_40002dca);
    if (DAT_4000193e < DAT_4000e380) {
      DAT_4000193e = DAT_4000193e + 1;
    }
  }
  if (((((s_AAAAAAAA_4000e294[2] & 7U) != 0) && ((DAT_40001678 & 1) == 0)) &&
      ((DAT_400015b8 & 1) != 0)) &&
     (((DAT_40001c39 == '\n' && (DAT_40002bdc != '\0')) &&
      ((sVar2 = get_shift_lever_pos_raw___(), sVar2 != -1 &&
       (((DAT_40001938 & 1) == 0 && (DAT_400017a4 != '\0')))))))) {
    if (shift_position_request_bits == 0) {
      DAT_40001951 = DAT_40001951 + 1;
      if (((DAT_40001676 <= (short)(ushort)DAT_40001951) && (DAT_40001951 = 0, DAT_40001950 != 0))
         && (DAT_40001950 = DAT_40001950 - 1, DAT_40001950 == 0)) {
        shift_position_request_bits = 0x20;
        obd_ii_dtc_confirm_and_freeze
                  (s_AAAAAAAA_4000e294 + 2,&DAT_40002d5e,&DAT_40002d5f,&DAT_40002d60,&DAT_00001803,0
                  );
      }
    }
    else {
      DAT_40001951 = 0;
      obd_ii_monitor_pass(s_AAAAAAAA_4000e294 + 2,&DAT_40002d5e);
      if (DAT_40001950 < DAT_4000e368) {
        DAT_40001950 = DAT_40001950 + 1;
      }
    }
  }
  if (((((s_AAAAAAAA_4000e294[3] & 7U) != 0) && ((DAT_40001678 & 1) == 0)) &&
      (((DAT_400015b8 & 1) != 0 && ((DAT_40001c39 != '\n' && (DAT_40002bdc != '\0')))))) &&
     ((sVar2 = get_shift_lever_pos_raw___(), sVar2 != -1 &&
      (((DAT_40001938 & 1) == 0 && (DAT_400017a4 != '\0')))))) {
    if ((((shift_position_request_bits & 0xf0) == 0) && ((shift_position_request_bits & 2) != 0)) &&
       ((((shift_position_request_bits & 1) != 0 || ((shift_position_request_bits & 4) != 0)) ||
        ((shift_position_request_bits & 8) != 0)))) {
      DAT_40001953 = DAT_40001953 + 1;
      if (((DAT_40001676 <= (short)(ushort)DAT_40001953) && (DAT_40001953 = 0, DAT_40001952 != 0))
         && (DAT_40001952 = DAT_40001952 - 1, DAT_40001952 == 0)) {
        shift_position_request_bits = shift_position_request_bits | 0x20;
        obd_ii_dtc_confirm_and_freeze
                  (s_AAAAAAAA_4000e294 + 3,&DAT_40002d61,&DAT_40002d62,&DAT_40002d63,&DAT_00001804,0
                  );
      }
    }
    else {
      DAT_40001953 = 0;
      obd_ii_monitor_pass(s_AAAAAAAA_4000e294 + 3,&DAT_40002d61);
      if (DAT_40001952 < DAT_4000e369) {
        DAT_40001952 = DAT_40001952 + 1;
      }
    }
  }
  if ((((DAT_4000e2b4 & 7) == 0) || ((DAT_40001678 & 1) != 0)) ||
     (((DAT_400015b8 & 1) == 0 ||
      ((((DAT_40001c39 != '\n' || (DAT_40002bdc == '\0')) ||
        (sVar2 = get_shift_lever_pos_raw___(), sVar2 == -1)) ||
       (((DAT_40001938 & 1) != 0 || (DAT_400017a4 == '\0')))))))) {
    DAT_40001941 = 0;
    DAT_400017a3 = DAT_400017a3 & 0xfd;
  }
  else if (((shift_position_request_bits == 1) || (shift_position_request_bits == 4)) ||
          (shift_position_request_bits == 8)) {
    DAT_40001941 = DAT_40001941 + 1;
    if (DAT_40001676 <= (short)(ushort)DAT_40001941) {
      DAT_40001941 = 0;
      DAT_400017a3 = DAT_400017a3 & 0xfd;
      if ((DAT_40001940 != 0) && (DAT_40001940 = DAT_40001940 - 1, DAT_40001940 == 0)) {
        obd_ii_dtc_confirm_and_freeze
                  (&DAT_4000e2b4,&DAT_40002dcd,&DAT_40002dce,&DAT_40002dcf,&DAT_00001905,0);
      }
    }
  }
  else {
    DAT_40001941 = 0;
    DAT_400017a3 = DAT_400017a3 & 0xfd;
    obd_ii_monitor_pass(&DAT_4000e2b4,&DAT_40002dcd);
    if (DAT_40001940 < DAT_4000e381) {
      DAT_40001940 = DAT_40001940 + 1;
    }
  }
  if (((((s_AAAAAAAA_4000e294[4] & 7U) != 0) && ((DAT_40001678 & 1) == 0)) &&
      ((DAT_400015b8 & 1) != 0)) &&
     (((DAT_40001c39 == '\0' && (DAT_40002bdc != '\0')) &&
      ((sVar2 = get_shift_lever_pos_raw___(), sVar2 != -1 &&
       (((DAT_40001938 & 1) == 0 && (DAT_400017a4 != '\0')))))))) {
    if (shift_position_request_bits == 0) {
      DAT_40001955 = DAT_40001955 + 1;
      if (((DAT_40001676 <= (short)(ushort)DAT_40001955) && (DAT_40001955 = 0, DAT_40001954 != 0))
         && (DAT_40001954 = DAT_40001954 - 1, DAT_40001954 == 0)) {
        shift_position_request_bits = 0x40;
        obd_ii_dtc_confirm_and_freeze
                  (s_AAAAAAAA_4000e294 + 4,&DAT_40002d64,&DAT_40002d65,&DAT_40002d66,&DAT_00001805,0
                  );
      }
    }
    else {
      DAT_40001955 = 0;
      obd_ii_monitor_pass(s_AAAAAAAA_4000e294 + 4,&DAT_40002d64);
      if (DAT_40001954 < DAT_4000e36a) {
        DAT_40001954 = DAT_40001954 + 1;
      }
    }
  }
  if ((((s_AAAAAAAA_4000e294[5] & 7U) != 0) && ((DAT_40001678 & 1) == 0)) &&
     ((((DAT_400015b8 & 1) != 0 && ((DAT_40001c39 != '\0' && (DAT_40002bdc != '\0')))) &&
      ((sVar2 = get_shift_lever_pos_raw___(), sVar2 != -1 &&
       (((DAT_40001938 & 1) == 0 && (DAT_400017a4 != '\0')))))))) {
    if ((((shift_position_request_bits & 0xf0) == 0) && ((shift_position_request_bits & 4) != 0)) &&
       ((((shift_position_request_bits & 1) != 0 || ((shift_position_request_bits & 2) != 0)) ||
        ((shift_position_request_bits & 8) != 0)))) {
      DAT_40001957 = DAT_40001957 + 1;
      if (((DAT_40001676 <= (short)(ushort)DAT_40001957) && (DAT_40001957 = 0, DAT_40001956 != 0))
         && (DAT_40001956 = DAT_40001956 - 1, DAT_40001956 == 0)) {
        shift_position_request_bits = shift_position_request_bits | 0x40;
        obd_ii_dtc_confirm_and_freeze
                  (s_AAAAAAAA_4000e294 + 5,&DAT_40002d67,&DAT_40002d68,&DAT_40002d69,&DAT_00001806,0
                  );
      }
    }
    else {
      DAT_40001957 = 0;
      obd_ii_monitor_pass(s_AAAAAAAA_4000e294 + 5,&DAT_40002d67);
      if (DAT_40001956 < DAT_4000e36b) {
        DAT_40001956 = DAT_40001956 + 1;
      }
    }
  }
  if ((((DAT_4000e2b5 & 7) == 0) || ((DAT_40001678 & 1) != 0)) ||
     (((DAT_400015b8 & 1) == 0 ||
      ((((DAT_40001c39 != '\0' || (DAT_40002bdc == '\0')) ||
        (sVar2 = get_shift_lever_pos_raw___(), sVar2 == -1)) ||
       (((DAT_40001938 & 1) != 0 || (DAT_400017a4 == '\0')))))))) {
    DAT_40001943 = 0;
    DAT_400017a3 = DAT_400017a3 & 0xfb;
  }
  else if (((shift_position_request_bits == 1) || (shift_position_request_bits == 2)) ||
          (shift_position_request_bits == 8)) {
    DAT_40001943 = DAT_40001943 + 1;
    if (DAT_40001676 <= (short)(ushort)DAT_40001943) {
      DAT_40001943 = 0;
      DAT_400017a3 = DAT_400017a3 & 0xfb;
      if ((DAT_40001942 != 0) && (DAT_40001942 = DAT_40001942 - 1, DAT_40001942 == 0)) {
        obd_ii_dtc_confirm_and_freeze
                  (&DAT_4000e2b5,&DAT_40002dd0,&DAT_40002dd1,&DAT_40002dd2,&DAT_00001906,0);
      }
    }
  }
  else {
    DAT_40001943 = 0;
    DAT_400017a3 = DAT_400017a3 & 0xfb;
    obd_ii_monitor_pass(&DAT_4000e2b5,&DAT_40002dd0);
    if (DAT_40001942 < DAT_4000e382) {
      DAT_40001942 = DAT_40001942 + 1;
    }
  }
  if (((((s_AAAAAAAA_4000e294[6] & 7U) != 0) && ((DAT_40001678 & 1) == 0)) &&
      ((DAT_400015b8 & 1) != 0)) &&
     (((DAT_40001c39 == -2 && (DAT_40002bdc != '\0')) &&
      ((sVar2 = get_shift_lever_pos_raw___(), sVar2 != -1 &&
       (((DAT_40001938 & 1) == 0 && (DAT_400017a4 != '\0')))))))) {
    if (shift_position_request_bits == 0) {
      DAT_40001959 = DAT_40001959 + 1;
      if (((DAT_40001676 <= (short)(ushort)DAT_40001959) && (DAT_40001959 = 0, DAT_40001958 != 0))
         && (DAT_40001958 = DAT_40001958 - 1, DAT_40001958 == 0)) {
        shift_position_request_bits = 0x80;
        obd_ii_dtc_confirm_and_freeze
                  (s_AAAAAAAA_4000e294 + 6,&DAT_40002d6a,&DAT_40002d6b,&DAT_40002d6c,&DAT_00001807,0
                  );
      }
    }
    else {
      DAT_40001959 = 0;
      obd_ii_monitor_pass(s_AAAAAAAA_4000e294 + 6,&DAT_40002d6a);
      if (DAT_40001958 < DAT_4000e36c) {
        DAT_40001958 = DAT_40001958 + 1;
      }
    }
  }
  if (((((s_AAAAAAAA_4000e294[7] & 7U) != 0) && ((DAT_40001678 & 1) == 0)) &&
      (((DAT_400015b8 & 1) != 0 && ((DAT_40001c39 != -2 && (DAT_40002bdc != '\0')))))) &&
     ((sVar2 = get_shift_lever_pos_raw___(), sVar2 != -1 &&
      (((DAT_40001938 & 1) == 0 && (DAT_400017a4 != '\0')))))) {
    if ((((shift_position_request_bits & 0xf0) == 0) && ((shift_position_request_bits & 8) != 0)) &&
       ((((shift_position_request_bits & 1) != 0 || ((shift_position_request_bits & 2) != 0)) ||
        ((shift_position_request_bits & 4) != 0)))) {
      DAT_4000195b = DAT_4000195b + 1;
      if (((DAT_40001676 <= (short)(ushort)DAT_4000195b) && (DAT_4000195b = 0, DAT_4000195a != 0))
         && (DAT_4000195a = DAT_4000195a - 1, DAT_4000195a == 0)) {
        shift_position_request_bits = shift_position_request_bits | 0x80;
        obd_ii_dtc_confirm_and_freeze
                  (s_AAAAAAAA_4000e294 + 7,&DAT_40002d6d,&DAT_40002d6e,&DAT_40002d6f,&DAT_00001808,0
                  );
      }
    }
    else {
      DAT_4000195b = 0;
      obd_ii_monitor_pass(s_AAAAAAAA_4000e294 + 7,&DAT_40002d6d);
      if (DAT_4000195a < DAT_4000e36d) {
        DAT_4000195a = DAT_4000195a + 1;
      }
    }
  }
  if ((((DAT_4000e2b6 & 7) == 0) || ((DAT_40001678 & 1) != 0)) ||
     (((DAT_400015b8 & 1) == 0 ||
      ((((DAT_40001c39 != -2 || (DAT_40002bdc == '\0')) ||
        (sVar2 = get_shift_lever_pos_raw___(), sVar2 == -1)) ||
       (((DAT_40001938 & 1) != 0 || (DAT_400017a4 == '\0')))))))) {
    DAT_40001945 = 0;
    DAT_400017a3 = DAT_400017a3 & 0xf7;
  }
  else if (((shift_position_request_bits == 1) || (shift_position_request_bits == 2)) ||
          (shift_position_request_bits == 4)) {
    DAT_40001945 = DAT_40001945 + 1;
    if (DAT_40001676 <= (short)(ushort)DAT_40001945) {
      DAT_40001945 = 0;
      DAT_400017a3 = DAT_400017a3 & 0xf7;
      if ((DAT_40001944 != 0) && (DAT_40001944 = DAT_40001944 - 1, DAT_40001944 == 0)) {
        obd_ii_dtc_confirm_and_freeze
                  (&DAT_4000e2b6,&DAT_40002dd3,&DAT_40002dd4,&DAT_40002dd5,&DAT_00001907,0);
      }
    }
  }
  else {
    DAT_40001945 = 0;
    DAT_400017a3 = DAT_400017a3 & 0xf7;
    obd_ii_monitor_pass(&DAT_4000e2b6,&DAT_40002dd3);
    if (DAT_40001944 < DAT_4000e383) {
      DAT_40001944 = DAT_40001944 + 1;
    }
  }
  if ((((s_AAAAAAAAAAAAAA_4000e2a0[0] & 7U) != 0) && ((DAT_400015b8 & 1) != 0)) &&
     (DAT_4000e4c4 < DAT_400015ba)) {
    if ((DAT_400017ad == '\0') && (DAT_400017ab == '\0')) {
      obd_ii_monitor_pass(s_AAAAAAAAAAAAAA_4000e2a0,&DAT_40002d7c);
    }
    else {
      DAT_400017ad = '\0';
      DAT_400017ab = '\0';
      obd_ii_dtc_confirm_and_freeze
                (s_AAAAAAAAAAAAAA_4000e2a0,&DAT_40002d7c,&DAT_40002d7d,&DAT_40002d7e,&DAT_00001910,0
                );
    }
  }
  if ((((s_AAAAAAAAAAAAAA_4000e2a0[1] & 7U) != 0) && ((DAT_400015b8 & 1) != 0)) &&
     (((DAT_40001678 & 0x20000000) == 0 && (DAT_4000e4ea < DAT_400015ba)))) {
    if ((DAT_400017ca < DAT_4000e4ed) ||
       (iVar1 = int_abs(DAT_4000195e), (int)(uint)DAT_4000e4ee <= iVar1)) {
      DAT_4000195d = 0;
      obd_ii_monitor_pass(s_AAAAAAAAAAAAAA_4000e2a0 + 1,&DAT_40002d7f);
      if (DAT_4000195c < DAT_4000e373) {
        DAT_4000195c = DAT_4000195c + 1;
      }
    }
    else {
      DAT_4000195d = DAT_4000195d + 1;
      if (((DAT_40001676 <= (short)(ushort)DAT_4000195d) && (DAT_4000195d = 0, DAT_4000195c != 0))
         && (DAT_4000195c = DAT_4000195c - 1, DAT_4000195c == 0)) {
        obd_ii_dtc_confirm_and_freeze
                  (s_AAAAAAAAAAAAAA_4000e2a0 + 1,&DAT_40002d7f,&DAT_40002d80,&DAT_40002d81,
                   &DAT_00001912,0);
      }
    }
  }
  if (((s_AAAAAAAAAAAAAA_4000e2a0[2] & 7U) != 0) && ((DAT_400015b8 & 1) != 0)) {
    if (DAT_400017ac == '\0') {
      obd_ii_monitor_pass(s_AAAAAAAAAAAAAA_4000e2a0 + 2,&DAT_40002d82);
    }
    else {
      DAT_400017ac = '\0';
      obd_ii_dtc_confirm_and_freeze
                (s_AAAAAAAAAAAAAA_4000e2a0 + 2,&DAT_40002d82,&DAT_40002d83,&DAT_40002d84,
                 &DAT_00001913,0);
    }
  }
  uVar3 = DAT_4000165c & 0x30;
  if (((s_AAAAAAAAAAAAAA_4000e2a0[4] & 7U) != 0) && ((DAT_400015b8 & 1) != 0)) {
    if ((uVar3 == 0x20) || (uVar3 == 0x30)) {
      DAT_40001961 = DAT_40001961 + 1;
      if (((DAT_40001676 <= (short)(ushort)DAT_40001961) && (DAT_40001961 = 0, DAT_40001960 != 0))
         && (DAT_40001960 = DAT_40001960 - 1, DAT_40001960 == 0)) {
        obd_ii_dtc_confirm_and_freeze
                  (s_AAAAAAAAAAAAAA_4000e2a0 + 4,&DAT_40002d88,&DAT_40002d89,&DAT_40002d8a,
                   &DAT_00001930,0);
      }
    }
    else {
      DAT_40001961 = 0;
      obd_ii_monitor_pass(s_AAAAAAAAAAAAAA_4000e2a0 + 4,&DAT_40002d88);
      if (DAT_40001960 < DAT_4000e376) {
        DAT_40001960 = DAT_40001960 + 1;
      }
    }
  }
  if (((s_AAAAAAAAAAAAAA_4000e2a0[5] & 7U) != 0) && ((DAT_400015b8 & 1) != 0)) {
    if (uVar3 == 0x10) {
      DAT_40001963 = DAT_40001963 + 1;
      if (((DAT_40001676 <= (short)(ushort)DAT_40001963) && (DAT_40001963 = 0, DAT_40001962 != 0))
         && (DAT_40001962 = DAT_40001962 - 1, DAT_40001962 == 0)) {
        obd_ii_dtc_confirm_and_freeze
                  (s_AAAAAAAAAAAAAA_4000e2a0 + 5,&DAT_40002d8b,&DAT_40002d8c,&DAT_40002d8d,
                   &DAT_00001931,0);
      }
    }
    else {
      DAT_40001963 = 0;
      obd_ii_monitor_pass(s_AAAAAAAAAAAAAA_4000e2a0 + 5,&DAT_40002d8b);
      if (DAT_40001962 < DAT_4000e377) {
        DAT_40001962 = DAT_40001962 + 1;
      }
    }
  }
  DAT_4000165c = DAT_4000165c & 0xffcf;
  DAT_40001968 = DAT_40001968 & 0xef;
  if (((((s_AAAAAAAAAAAAAA_4000e2a0[6] & 7U) != 0) && ((DAT_400015b8 & 1) != 0)) &&
      ((DAT_40001678 & 1) == 0)) &&
     (((DAT_40001c39 == '\t' || (DAT_40001c39 == '\n')) ||
      ((DAT_40001c39 == '\0' || (DAT_40001c39 == -2)))))) {
    if ((DAT_40002358 < (uint)DAT_4000e4f3 * 100) && ((uint)DAT_4000e4f4 * 100 < DAT_40002358)) {
      DAT_40001968 = DAT_40001968 | 0x10;
      DAT_40001965 = 0;
      obd_ii_monitor_pass(s_AAAAAAAAAAAAAA_4000e2a0 + 6,&DAT_40002d9a);
      if (DAT_40001964 < DAT_4000e378) {
        DAT_40001964 = DAT_40001964 + 1;
      }
    }
    else {
      DAT_40001965 = DAT_40001965 + 1;
      if ((DAT_40001676 <= (short)(ushort)DAT_40001965) &&
         ((DAT_40001965 = 0, DAT_40001964 != 0 &&
          (DAT_40001964 = DAT_40001964 - 1, DAT_40001964 == 0)))) {
        obd_ii_dtc_confirm_and_freeze
                  (s_AAAAAAAAAAAAAA_4000e2a0 + 6,&DAT_40002d9a,&DAT_40002d9b,&DAT_40002d9c,
                   &DAT_00002800,0);
      }
    }
  }
  if (((((s_AAAAAAAAAAAAAA_4000e2a0[7] & 7U) != 0) && ((DAT_400015b8 & 1) != 0)) &&
      ((DAT_40001678 & 0x800000) == 0)) && ((DAT_40001678 & 0x1000000) == 0)) {
    uVar3 = int_abs(&DAT_00002710 + (-DAT_40002358 - DAT_40002374));
    if (((((DAT_40001c39 == '\t') || (DAT_40001c39 == '\n')) ||
         ((DAT_40001c39 == '\0' || (DAT_40001c39 == -2)))) &&
        (((DAT_40001968 & 1) != 0 && ((DAT_40001968 & 0x10) != 0)))) &&
       ((ushort)((ushort)DAT_4000e4f0 * 10) <= uVar3)) {
      DAT_40001967 = DAT_40001967 + 1;
      if (((DAT_40001676 <= (short)(ushort)DAT_40001967) && (DAT_40001967 = 0, DAT_40001966 != 0))
         && (DAT_40001966 = DAT_40001966 - 1, DAT_40001966 == 0)) {
        obd_ii_dtc_confirm_and_freeze
                  (s_AAAAAAAAAAAAAA_4000e2a0 + 7,&DAT_40002d9d,&DAT_40002d9e,&DAT_40002d9f,
                   &DAT_00002805,0);
      }
    }
    else {
      DAT_40001967 = 0;
      obd_ii_monitor_pass(s_AAAAAAAAAAAAAA_4000e2a0 + 7,&DAT_40002d9d);
      if (DAT_40001966 < DAT_4000e379) {
        DAT_40001966 = DAT_40001966 + 1;
      }
    }
  }
  if (((((s_AAAAAAAAAAAAAA_4000e2a0[3] & 7U) == 0) || ((DAT_40001678 & 1) != 0)) ||
      (((DAT_400015b8 & 1) == 0 ||
       ((DAT_40002bdc == '\0' || (sVar2 = get_shift_lever_pos_raw___(), sVar2 == -1)))))) ||
     (((DAT_40001938 & 1) != 0 || (DAT_400017a4 == '\0')))) {
    DAT_4000194b = 0;
  }
  else if ((DAT_40001938 & 4) == 0) {
    if ((DAT_40001938 & 8) == 0) {
      DAT_4000194b = 0;
      obd_ii_monitor_pass(s_AAAAAAAAAAAAAA_4000e2a0 + 3,&DAT_40002d85);
      if (DAT_4000194a < DAT_4000e375) {
        DAT_4000194a = DAT_4000194a + 1;
      }
    }
  }
  else {
    DAT_4000194b = DAT_4000194b + 1;
    if (DAT_40001676 <= (short)(ushort)DAT_4000194b) {
      DAT_4000194b = 0;
      DAT_40001938 = DAT_40001938 & 0xfffffffb;
      if ((DAT_4000194a != 0) && (DAT_4000194a = DAT_4000194a - 1, DAT_4000194a == 0)) {
        obd_ii_dtc_confirm_and_freeze
                  (s_AAAAAAAAAAAAAA_4000e2a0 + 3,&DAT_40002d85,&DAT_40002d86,&DAT_40002d87,
                   &DAT_00001929,0);
      }
    }
  }
  if ((((DAT_4000e2b7 & 7) == 0) || ((DAT_400015b8 & 1) == 0)) || (DAT_40002bdc == '\0')) {
    DAT_40001947 = 0;
  }
  else if ((DAT_40001938 & 1) == 0) {
    DAT_40001947 = 0;
    obd_ii_monitor_pass(&DAT_4000e2b7,&DAT_40002dd6);
    if (DAT_40001946 < DAT_4000e384) {
      DAT_40001946 = DAT_40001946 + 1;
    }
  }
  else {
    DAT_40001947 = DAT_40001947 + 1;
    if (((DAT_40001676 <= (short)(ushort)DAT_40001947) && (DAT_40001947 = 0, DAT_40001946 != 0)) &&
       (DAT_40001946 = DAT_40001946 - 1, DAT_40001946 == 0)) {
      obd_ii_dtc_confirm_and_freeze
                (&DAT_4000e2b7,&DAT_40002dd6,&DAT_40002dd7,&DAT_40002dd8,&DAT_00001909,0);
    }
  }
  if ((((DAT_4000e2b8 & 7) == 0) || ((DAT_400015b8 & 1) == 0)) || (DAT_40002bdc == '\0')) {
    DAT_40001949 = 0;
  }
  else if ((DAT_40001938 & 0x10) == 0) {
    if ((DAT_40001938 & 0x20) == 0) {
      DAT_40001949 = 0;
      obd_ii_monitor_pass(&DAT_4000e2b8,&DAT_40002dd9);
      if (DAT_40001948 < DAT_4000e385) {
        DAT_40001948 = DAT_40001948 + 1;
      }
    }
  }
  else {
    DAT_40001949 = DAT_40001949 + 1;
    if (DAT_40001676 <= (short)(ushort)DAT_40001949) {
      DAT_40001938 = DAT_40001938 & 0xffffffef;
      DAT_40001949 = 0;
      if ((DAT_40001948 != 0) && (DAT_40001948 = DAT_40001948 - 1, DAT_40001948 == 0)) {
        obd_ii_dtc_confirm_and_freeze
                  (&DAT_4000e2b8,&DAT_40002dd9,&DAT_40002dda,&DAT_40002ddb,&DAT_00001911,0);
      }
    }
  }
  if ((((DAT_40002cdd & 8) == 0) || ((DAT_40002cdd & 4) == 0)) || ((DAT_40002cdd & 1) == 0)) {
    DAT_40001678 = DAT_40001678 & 0xff7fffff;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x800000;
  }
  if ((((((((DAT_40002d58 & 8) == 0) || ((DAT_40002d58 & 4) == 0)) || ((DAT_40002d58 & 1) == 0)) &&
        ((((DAT_40002d5b & 8) == 0 || ((DAT_40002d5b & 4) == 0)) || ((DAT_40002d5b & 1) == 0)))) &&
       ((((((DAT_40002d5e & 8) == 0 || ((DAT_40002d5e & 4) == 0)) || ((DAT_40002d5e & 1) == 0)) &&
         ((((DAT_40002d61 & 8) == 0 || ((DAT_40002d61 & 4) == 0)) || ((DAT_40002d61 & 1) == 0)))) &&
        (((((DAT_40002d64 & 8) == 0 || ((DAT_40002d64 & 4) == 0)) || ((DAT_40002d64 & 1) == 0)) &&
         ((((DAT_40002d67 & 8) == 0 || ((DAT_40002d67 & 4) == 0)) || ((DAT_40002d67 & 1) == 0)))))))
       ) && ((((DAT_40002d6a & 8) == 0 || ((DAT_40002d6a & 4) == 0)) || ((DAT_40002d6a & 1) == 0))))
     && ((((DAT_40002d6d & 8) == 0 || ((DAT_40002d6d & 4) == 0)) || ((DAT_40002d6d & 1) == 0)))) {
    DAT_40001678 = DAT_40001678 & 0xfbffffff;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x4000000;
  }
  if (((((((((((DAT_40002dca & 8) == 0) || ((DAT_40002dca & 4) == 0)) || ((DAT_40002dca & 1) == 0))
           && ((((DAT_40002dcd & 8) == 0 || ((DAT_40002dcd & 4) == 0)) || ((DAT_40002dcd & 1) == 0))
              )) && ((((DAT_40002dd0 & 8) == 0 || ((DAT_40002dd0 & 4) == 0)) ||
                     ((DAT_40002dd0 & 1) == 0)))) &&
         ((((DAT_40002dd3 & 8) == 0 || ((DAT_40002dd3 & 4) == 0)) || ((DAT_40002dd3 & 1) == 0)))) &&
        ((((DAT_40002dd6 & 8) == 0 || ((DAT_40002dd6 & 4) == 0)) || ((DAT_40002dd6 & 1) == 0)))) &&
       (((((DAT_40002d7c & 8) == 0 || ((DAT_40002d7c & 4) == 0)) || ((DAT_40002d7c & 1) == 0)) &&
        ((((DAT_40002dd9 & 8) == 0 || ((DAT_40002dd9 & 4) == 0)) || ((DAT_40002dd9 & 1) == 0))))))
      && ((((DAT_40002d7f & 8) == 0 || ((DAT_40002d7f & 4) == 0)) || ((DAT_40002d7f & 1) == 0)))) &&
     ((((DAT_40002d82 & 8) == 0 || ((DAT_40002d82 & 4) == 0)) || ((DAT_40002d82 & 1) == 0)))) {
    DAT_40001678 = DAT_40001678 & 0xefffffff;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x10000000;
  }
  if ((((((DAT_40002d85 & 8) == 0) || ((DAT_40002d85 & 4) == 0)) || ((DAT_40002d85 & 1) == 0)) &&
      ((((DAT_40002d88 & 8) == 0 || ((DAT_40002d88 & 4) == 0)) || ((DAT_40002d88 & 1) == 0)))) &&
     ((((DAT_40002d8b & 8) == 0 || ((DAT_40002d8b & 4) == 0)) || ((DAT_40002d8b & 1) == 0)))) {
    DAT_40001678 = DAT_40001678 & 0xdfffffff;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x20000000;
  }
  if ((((DAT_40002d9a & 8) == 0) || ((DAT_40002d9a & 4) == 0)) || ((DAT_40002d9a & 1) == 0)) {
    DAT_40001678 = DAT_40001678 & 0xfeffffff;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x1000000;
  }
  if ((((DAT_40002d9d & 8) == 0) || ((DAT_40002d9d & 4) == 0)) || ((DAT_40002d9d & 1) == 0)) {
    DAT_40001678 = DAT_40001678 & 0xfdffffff;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x2000000;
  }
  return;
}



void FUN_0006b24c(void)

{
  uint uVar1;
  
  DAT_40001970 = (short)((int)(uint)DAT_40001dd2 >> 4);
  uVar1 = (0x100 - (uint)DAT_4000e4ec) * DAT_4000196c;
  DAT_4000196c = ((int)uVar1 >> 8) + (uint)((int)uVar1 < 0 && (uVar1 & 0xff) != 0) +
                 (uint)DAT_4000e4ec * ((int)(uint)DAT_40001dd2 >> 4);
  DAT_4000195e = (short)(DAT_4000196c >> 8) +
                 (ushort)((int)DAT_4000196c < 0 && (DAT_4000196c & 0xff) != 0);
  return;
}



void FUN_0006b2b8(void)

{
  DAT_4000193c = DAT_4000e360;
  DAT_4000194c = DAT_4000e366;
  DAT_4000194e = DAT_4000e367;
  DAT_40001950 = DAT_4000e368;
  DAT_40001952 = DAT_4000e369;
  DAT_40001954 = DAT_4000e36a;
  DAT_40001956 = DAT_4000e36b;
  DAT_40001958 = DAT_4000e36c;
  DAT_4000195a = DAT_4000e36d;
  DAT_4000193e = DAT_4000e380;
  DAT_40001940 = DAT_4000e381;
  DAT_40001942 = DAT_4000e382;
  DAT_40001944 = DAT_4000e383;
  DAT_40001946 = DAT_4000e384;
  DAT_40001948 = DAT_4000e385;
  DAT_4000195c = DAT_4000e373;
  DAT_4000194a = DAT_4000e375;
  DAT_40001960 = DAT_4000e376;
  DAT_40001962 = DAT_4000e377;
  DAT_40001964 = DAT_4000e378;
  DAT_40001966 = DAT_4000e379;
  DAT_4000193d = 0;
  DAT_4000194d = 0;
  DAT_4000194f = 0;
  DAT_40001951 = 0;
  DAT_40001953 = 0;
  DAT_40001955 = 0;
  DAT_40001957 = 0;
  DAT_40001959 = 0;
  DAT_4000195b = 0;
  DAT_4000193f = 0;
  DAT_40001941 = 0;
  DAT_40001943 = 0;
  DAT_40001945 = 0;
  DAT_40001947 = 0;
  DAT_40001949 = 0;
  DAT_4000195d = 0;
  DAT_4000194b = 0;
  DAT_40001961 = 0;
  DAT_40001963 = 0;
  DAT_40001965 = 0;
  DAT_40001967 = 0;
  shift_position_request_bits = shift_position_request_bits & 0xf;
  DAT_40001968 = 0;
  DAT_40001938 = DAT_40001938 | 0x28;
  FUN_00057284();
  obd_set_new_DTC(&DAT_4000e28e,&DAT_40002cdd,0x705,0);
  obd_set_new_DTC(s_AAAAAAAA_4000e294,&DAT_40002d58,&DAT_00001801,0);
  obd_set_new_DTC(s_AAAAAAAA_4000e294 + 1,&DAT_40002d5b,&DAT_00001802,0);
  obd_set_new_DTC(s_AAAAAAAA_4000e294 + 2,&DAT_40002d5e,&DAT_00001803,0);
  obd_set_new_DTC(s_AAAAAAAA_4000e294 + 3,&DAT_40002d61,&DAT_00001804,0);
  obd_set_new_DTC(s_AAAAAAAA_4000e294 + 4,&DAT_40002d64,&DAT_00001805,0);
  obd_set_new_DTC(s_AAAAAAAA_4000e294 + 5,&DAT_40002d67,&DAT_00001806,0);
  obd_set_new_DTC(s_AAAAAAAA_4000e294 + 6,&DAT_40002d6a,&DAT_00001807,0);
  obd_set_new_DTC(s_AAAAAAAA_4000e294 + 7,&DAT_40002d6d,&DAT_00001808,0);
  obd_set_new_DTC(&DAT_4000e2b3,&DAT_40002dca,&DAT_00001904,0);
  obd_set_new_DTC(&DAT_4000e2b4,&DAT_40002dcd,&DAT_00001905,0);
  obd_set_new_DTC(&DAT_4000e2b5,&DAT_40002dd0,&DAT_00001906,0);
  obd_set_new_DTC(&DAT_4000e2b6,&DAT_40002dd3,&DAT_00001907,0);
  obd_set_new_DTC(&DAT_4000e2b7,&DAT_40002dd6,&DAT_00001909,0);
  obd_set_new_DTC(&DAT_4000e2b8,&DAT_40002dd9,&DAT_00001911,0);
  obd_set_new_DTC(s_AAAAAAAAAAAAAA_4000e2a0,&DAT_40002d7c,&DAT_00001910,0);
  obd_set_new_DTC(s_AAAAAAAAAAAAAA_4000e2a0 + 1,&DAT_40002d7f,&DAT_00001912,0);
  obd_set_new_DTC(s_AAAAAAAAAAAAAA_4000e2a0 + 2,&DAT_40002d82,&DAT_00001913,0);
  obd_set_new_DTC(s_AAAAAAAAAAAAAA_4000e2a0 + 3,&DAT_40002d85,&DAT_00001929,0);
  obd_set_new_DTC(s_AAAAAAAAAAAAAA_4000e2a0 + 4,&DAT_40002d88,&DAT_00001930,0);
  obd_set_new_DTC(s_AAAAAAAAAAAAAA_4000e2a0 + 5,&DAT_40002d8b,&DAT_00001931,0);
  obd_set_new_DTC(s_AAAAAAAAAAAAAA_4000e2a0 + 6,&DAT_40002d9a,&DAT_00002800,0);
  obd_set_new_DTC(s_AAAAAAAAAAAAAA_4000e2a0 + 7,&DAT_40002d9d,&DAT_00002805,0);
  return;
}



void FUN_0006b918(void)

{
  obd_ii_dtc_aging_heal(&DAT_4000e28e,&DAT_40002cdd,&DAT_40002cde,&DAT_40002cdf,0x705,0);
  obd_ii_dtc_aging_heal
            (s_AAAAAAAA_4000e294,&DAT_40002d58,&DAT_40002d59,&DAT_40002d5a,&DAT_00001801,0);
  obd_ii_dtc_aging_heal
            (s_AAAAAAAA_4000e294 + 1,&DAT_40002d5b,&DAT_40002d5c,&DAT_40002d5d,&DAT_00001802,0);
  obd_ii_dtc_aging_heal
            (s_AAAAAAAA_4000e294 + 2,&DAT_40002d5e,&DAT_40002d5f,&DAT_40002d60,&DAT_00001803,0);
  obd_ii_dtc_aging_heal
            (s_AAAAAAAA_4000e294 + 3,&DAT_40002d61,&DAT_40002d62,&DAT_40002d63,&DAT_00001804,0);
  obd_ii_dtc_aging_heal
            (s_AAAAAAAA_4000e294 + 4,&DAT_40002d64,&DAT_40002d65,&DAT_40002d66,&DAT_00001805,0);
  obd_ii_dtc_aging_heal
            (s_AAAAAAAA_4000e294 + 5,&DAT_40002d67,&DAT_40002d68,&DAT_40002d69,&DAT_00001806,0);
  obd_ii_dtc_aging_heal
            (s_AAAAAAAA_4000e294 + 6,&DAT_40002d6a,&DAT_40002d6b,&DAT_40002d6c,&DAT_00001807,0);
  obd_ii_dtc_aging_heal
            (s_AAAAAAAA_4000e294 + 7,&DAT_40002d6d,&DAT_40002d6e,&DAT_40002d6f,&DAT_00001808,0);
  obd_ii_dtc_aging_heal(&DAT_4000e2b3,&DAT_40002dca,&DAT_40002dcb,&DAT_40002dcc,&DAT_00001904,0);
  obd_ii_dtc_aging_heal(&DAT_4000e2b4,&DAT_40002dcd,&DAT_40002dce,&DAT_40002dcf,&DAT_00001905,0);
  obd_ii_dtc_aging_heal(&DAT_4000e2b5,&DAT_40002dd0,&DAT_40002dd1,&DAT_40002dd2,&DAT_00001906,0);
  obd_ii_dtc_aging_heal(&DAT_4000e2b6,&DAT_40002dd3,&DAT_40002dd4,&DAT_40002dd5,&DAT_00001907,0);
  obd_ii_dtc_aging_heal(&DAT_4000e2b7,&DAT_40002dd6,&DAT_40002dd7,&DAT_40002dd8,&DAT_00001909,0);
  obd_ii_dtc_aging_heal(&DAT_4000e2b8,&DAT_40002dd9,&DAT_40002dda,&DAT_40002ddb,&DAT_00001911,0);
  obd_ii_dtc_aging_heal
            (s_AAAAAAAAAAAAAA_4000e2a0,&DAT_40002d7c,&DAT_40002d7d,&DAT_40002d7e,&DAT_00001910,0);
  obd_ii_dtc_aging_heal
            (s_AAAAAAAAAAAAAA_4000e2a0 + 1,&DAT_40002d7f,&DAT_40002d80,&DAT_40002d81,&DAT_00001912,0
            );
  obd_ii_dtc_aging_heal
            (s_AAAAAAAAAAAAAA_4000e2a0 + 2,&DAT_40002d82,&DAT_40002d83,&DAT_40002d84,&DAT_00001913,0
            );
  obd_ii_dtc_aging_heal
            (s_AAAAAAAAAAAAAA_4000e2a0 + 3,&DAT_40002d85,&DAT_40002d86,&DAT_40002d87,&DAT_00001929,0
            );
  obd_ii_dtc_aging_heal
            (s_AAAAAAAAAAAAAA_4000e2a0 + 4,&DAT_40002d88,&DAT_40002d89,&DAT_40002d8a,&DAT_00001930,0
            );
  obd_ii_dtc_aging_heal
            (s_AAAAAAAAAAAAAA_4000e2a0 + 5,&DAT_40002d8b,&DAT_40002d8c,&DAT_40002d8d,&DAT_00001931,0
            );
  obd_ii_dtc_aging_heal
            (s_AAAAAAAAAAAAAA_4000e2a0 + 6,&DAT_40002d9a,&DAT_40002d9b,&DAT_40002d9c,&DAT_00002800,0
            );
  obd_ii_dtc_aging_heal
            (s_AAAAAAAAAAAAAA_4000e2a0 + 7,&DAT_40002d9d,&DAT_40002d9e,&DAT_40002d9f,&DAT_00002805,0
            );
  return;
}



void obd_ii_monitor_trans_sensors(void)

{
  uint uVar1;
  short sVar2;
  char cVar5;
  int iVar3;
  uint uVar4;
  byte bVar6;
  
  if (((DAT_40001678 & 8) == 0) && ((DAT_40001678 & 0x40000) == 0)) {
    u16_rspeed_rpm_4000197a =
         int_abs((ulonglong)(uint)((int)(uint)tach_rpm >> 2) - (ulonglong)input_shaft_rpm);
  }
  else {
    u16_rspeed_rpm_4000197a = 0;
  }
  if ((((DAT_4000e275 & 7) != 0) && ((DAT_40001678 & 0x400000) == 0)) && ((DAT_400015b8 & 1) != 0))
  {
    bVar6 = FUN_00056108();
    if ((DAT_4000e433 < bVar6) || (bVar6 = FUN_00056108(), bVar6 < DAT_4000e432)) {
      DAT_4000197d = DAT_4000197d + 1;
      if ((DAT_40001676 <= (short)(ushort)DAT_4000197d) &&
         ((DAT_4000197d = 0, DAT_4000197c != 0 &&
          (DAT_4000197c = DAT_4000197c - 1, DAT_4000197c == 0)))) {
        obd_ii_dtc_confirm_and_freeze
                  (&DAT_4000e275,&DAT_40002cc2,&DAT_40002cc3,&DAT_40002cc4,0x71,0);
      }
    }
    else {
      DAT_4000197d = 0;
      obd_ii_monitor_pass(&DAT_4000e275,&DAT_40002cc2);
      if (DAT_4000197c < DAT_4000e347) {
        DAT_4000197c = DAT_4000197c + 1;
      }
    }
  }
  if (((((DAT_4000e25e & 7) != 0) && ((DAT_40001678 & 0x10) == 0)) && (engine_running != '\0')) &&
     ((DAT_400015b8 & 1) != 0)) {
    if (DAT_4000e4d4 < oil_temp_unknown) {
      DAT_4000197f = DAT_4000197f + 1;
      if (((DAT_4000e4d5 <= DAT_4000197f) && (DAT_4000197f = 0, DAT_4000197e != 0)) &&
         (DAT_4000197e = DAT_4000197e - 1, DAT_4000197e == 0)) {
        cVar5 = '\x01';
        if (DAT_4000e4cb == '\0') {
          cVar5 = DAT_4000167c;
        }
        DAT_4000167c = cVar5;
        obd_ii_dtc_confirm_and_freeze
                  (&DAT_4000e25e,&DAT_40002cc5,&DAT_40002cc6,&DAT_40002cc7,0x218,0);
      }
    }
    else if (oil_temp_unknown < DAT_4000e4d3) {
      DAT_4000197f = 0;
      DAT_4000167c = '\0';
      obd_ii_monitor_pass(&DAT_4000e25e,&DAT_40002cc5);
      if (DAT_4000197e < DAT_4000e330) {
        DAT_4000197e = DAT_4000197e + 1;
      }
    }
  }
  if ((((DAT_4000e2b0 & 7) == 0) || ((DAT_40001678 & 0x40000) != 0)) ||
     ((((DAT_40001678 & 0x80000) != 0 ||
       ((((DAT_40001678 & 0x200) != 0 || (engine_running == '\0')) || ((DAT_40001678 & 8) != 0))))
      || ((DAT_400015b8 & 1) == 0)))) {
    DAT_40001458 = '\x05';
    DAT_40001981 = DAT_4000e4dc;
  }
  else {
    if (((DAT_4000e4d6 < (short)engine_torque) || (input_shaft_rpm < DAT_4000e4d8)) ||
       (DAT_4000e4da < input_shaft_rpm)) {
      DAT_40001981 = DAT_4000e4dc;
    }
    else if (vehicle_speed____ / 100 < (uint)DAT_4000e4dd) {
      if (DAT_40001981 != '\0') {
        DAT_40001981 = DAT_40001981 + -1;
      }
    }
    else {
      DAT_40001981 = DAT_4000e4dc;
    }
    if (DAT_40001981 == '\0') {
      DAT_40001978 = DAT_40001978 | 2;
      DAT_40001981 = DAT_4000e4dc;
    }
    else {
      DAT_40001978 = DAT_40001978 & 0xfd;
    }
    if ((DAT_40001978 & 4) == 0) {
      DAT_40001458 = '\x05';
    }
    else if (DAT_40001458 == '\0') {
      DAT_40001978 = DAT_40001978 | 1;
      DAT_40001458 = '\x05';
    }
    else {
      DAT_40001458 = DAT_40001458 + -1;
    }
    if (((DAT_40001978 & 2) == 0) && ((DAT_40001978 & 1) == 0)) {
      if (((uint)DAT_4000e4dd <= vehicle_speed____ / 100) &&
         (obd_ii_monitor_pass(&DAT_4000e2b0,&DAT_40002cc8), DAT_40001980 < DAT_4000e391)) {
        DAT_40001980 = DAT_40001980 + 1;
      }
    }
    else if (DAT_40001980 != 0) {
      DAT_40001980 = DAT_40001980 - 1;
      if (DAT_40001980 == 0) {
        obd_ii_dtc_confirm_and_freeze
                  (&DAT_4000e2b0,&DAT_40002cc8,&DAT_40002cc9,&DAT_40002cca,0x500,0);
      }
      else {
        DAT_40001978 = DAT_40001978 & 0xfc;
      }
    }
  }
  if (((((DAT_4000e27d & 7) != 0) && ((DAT_40001678 & 0x40000) == 0)) && (engine_running != '\0'))
     && ((DAT_400015b8 & 1) != 0)) {
    if (DAT_400015ba < DAT_4000e406) {
      DAT_40001983 = DAT_40001983 + 1;
      if (((DAT_4000e40a <= DAT_40001983) && (DAT_40001983 = 0, DAT_40001982 != 0)) &&
         (DAT_40001982 = DAT_40001982 - 1, DAT_40001982 == 0)) {
        obd_ii_dtc_confirm_and_freeze
                  (&DAT_4000e27d,&DAT_40002ccb,&DAT_40002ccc,&DAT_40002ccd,0x562,0);
      }
    }
    else {
      DAT_40001983 = 0;
      obd_ii_monitor_pass(&DAT_4000e27d,&DAT_40002ccb);
      if (DAT_40001982 < DAT_4000e34f) {
        DAT_40001982 = DAT_40001982 + 1;
      }
    }
  }
  if ((((DAT_4000e27e & 7) != 0) && ((DAT_40001678 & 0x40000) == 0)) &&
     ((engine_running != '\0' && ((DAT_400015b8 & 1) != 0)))) {
    if (DAT_4000e408 < DAT_400015ba) {
      DAT_40001985 = DAT_40001985 + 1;
      if (((DAT_4000e40b <= DAT_40001985) && (DAT_40001985 = 0, DAT_40001984 != 0)) &&
         (DAT_40001984 = DAT_40001984 - 1, DAT_40001984 == 0)) {
        obd_ii_dtc_confirm_and_freeze
                  (&DAT_4000e27e,&DAT_40002cce,&DAT_40002ccf,&DAT_40002cd0,0x563,0);
      }
    }
    else {
      DAT_40001985 = 0;
      obd_ii_monitor_pass(&DAT_4000e27e,&DAT_40002cce);
      if (DAT_40001984 < DAT_4000e350) {
        DAT_40001984 = DAT_40001984 + 1;
      }
    }
  }
  if ((((DAT_4000e25f & 7) != 0) && ((DAT_40001678 & 0x10) == 0)) &&
     (((DAT_400015b8 & 1) != 0 &&
      ((DAT_4000e412 <= oil_temp_sensor_voltage && (oil_temp_sensor_voltage <= DAT_4000e414)))))) {
    if (((DAT_40001987 & 0x20) == 0) && ((DAT_40001980 != 0 && (oil_temp_unknown < DAT_4000e439))))
    {
      sVar2 = DAT_4000198e;
      if ((DAT_4000198e != 0) && (sVar2 = DAT_4000198e + -1, 7 < (byte)(ips_gear_cur - GEAR_1))) {
        sVar2 = DAT_4000198e;
      }
      DAT_4000198e = sVar2;
      if (DAT_4000198c != 0) {
        iVar3 = (int)((ulonglong)((longlong)(int)(uint)vehicle_speed____ * -0x49f49f49) >> 0x20) +
                (uint)vehicle_speed____;
        if ((iVar3 >> 8) - (iVar3 >> 0x1f) < (int)(uint)DAT_4000198c) {
          iVar3 = (int)((ulonglong)((longlong)(int)(uint)vehicle_speed____ * -0x49f49f49) >> 0x20) +
                  (uint)vehicle_speed____;
          DAT_4000198c = DAT_4000198c -
                         ((short)((uint)iVar3 >> 8) - ((short)(char)((uint)iVar3 >> 0x18) >> 0xf));
        }
        else {
          DAT_4000198c = 0;
        }
      }
      if (oil_temp_sensor_voltage < DAT_40001992) {
        DAT_40001992 = oil_temp_sensor_voltage;
      }
      if (DAT_40001990 < oil_temp_sensor_voltage) {
        DAT_40001990 = oil_temp_sensor_voltage;
      }
      if ((int)(uint)DAT_4000e41c < (int)((uint)DAT_40001990 - (uint)DAT_40001992)) {
        DAT_40001987 = DAT_40001987 & 0xef | 0x20;
      }
      if ((DAT_4000198e == 0) && (DAT_4000198c == 0)) {
        DAT_40001987 = DAT_40001987 | 0x30;
      }
    }
    if (oil_temp_sensor_voltage < DAT_4000e40c) {
      DAT_40001988 = DAT_4000e410;
      bVar6 = DAT_40001987 | 1;
      if ((DAT_40001987 & 2) != 0) {
        bVar6 = DAT_40001987 & 0xfd | 5;
      }
    }
    else {
      cVar5 = DAT_40001988 + -1;
      if (DAT_40001988 == '\0') {
        cVar5 = DAT_40001988;
      }
      bVar6 = DAT_40001987;
      DAT_40001988 = cVar5;
      if (cVar5 == '\0') {
        bVar6 = DAT_40001987 & 0xfe;
      }
    }
    DAT_40001987 = bVar6;
    if (DAT_4000e40e < oil_temp_sensor_voltage) {
      DAT_40001989 = DAT_4000e410;
      bVar6 = DAT_40001987 | 2;
      if ((DAT_40001987 & 1) != 0) {
        bVar6 = DAT_40001987 & 0xfe | 10;
      }
    }
    else {
      cVar5 = DAT_40001989 + -1;
      if (DAT_40001989 == '\0') {
        cVar5 = DAT_40001989;
      }
      bVar6 = DAT_40001987;
      DAT_40001989 = cVar5;
      if (cVar5 == '\0') {
        bVar6 = DAT_40001987 & 0xfd;
      }
    }
    DAT_40001987 = bVar6;
    if ((DAT_40001987 & 0xc) == 0) {
      if (DAT_40001986 < DAT_4000e331) {
        cVar5 = DAT_4000198a + -1;
        if (DAT_4000198a == '\0') {
          cVar5 = DAT_4000198a;
        }
        DAT_4000198a = cVar5;
        if (cVar5 == '\0') {
          DAT_4000198a = DAT_4000e411;
          DAT_40001986 = DAT_40001986 + 1;
        }
      }
    }
    else {
      DAT_40001987 = DAT_40001987 & 0xf3;
      DAT_4000198a = DAT_4000e411;
      if (DAT_40001986 != 0) {
        DAT_40001986 = DAT_40001986 - 1;
      }
    }
    if ((DAT_40001986 == 0) || ((DAT_40001987 & 0x10) != 0)) {
      obd_ii_dtc_confirm_and_freeze(&DAT_4000e25f,&DAT_40002ce0,&DAT_40002ce1,&DAT_40002ce2,0x710,0)
      ;
    }
    if (((((DAT_40001987 & 0x20) != 0) && ((DAT_40001987 & 0x10) == 0)) &&
        ((DAT_40001987 & 0xc) == 0)) && (DAT_40001986 == DAT_4000e331)) {
      obd_ii_monitor_pass(&DAT_4000e25f,&DAT_40002ce0);
    }
    if (((DAT_4000e25f & 8) != 0) && ((DAT_40001987 & 0x20) != 0)) {
      DAT_40001987 = DAT_40001987 & 0xcf;
      DAT_4000198c = DAT_4000e4a6;
      DAT_4000198e = DAT_4000e4a8;
      DAT_40001990 = 0;
      DAT_40001992 = 0x3ff;
    }
  }
  if (((DAT_4000e28f & 7) != 0) && ((DAT_400015b8 & 1) != 0)) {
    DAT_40001994 = 0;
    if (DAT_40001995 < DAT_4000e361) {
      DAT_40001995 = DAT_40001995 + 1;
    }
    obd_ii_monitor_pass(&DAT_4000e28f,&DAT_40002ce3);
  }
  if (((DAT_4000e261 & 7) != 0) && ((DAT_400015b8 & 1) != 0)) {
    if (oil_temp_sensor_voltage < DAT_4000e412) {
      DAT_40001996 = DAT_40001996 + 1;
      if (DAT_40001676 <= (short)(ushort)DAT_40001996) {
        DAT_40001996 = 0;
        bVar6 = DAT_40001997 - 1;
        if (DAT_40001997 == 0) {
          bVar6 = DAT_40001997;
        }
        DAT_40001997 = bVar6;
        if (bVar6 == 0) {
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e261,&DAT_40002ce6,&DAT_40002ce7,&DAT_40002ce8,0x712,0);
        }
      }
    }
    else {
      DAT_40001996 = 0;
      if (DAT_40001997 < DAT_4000e333) {
        DAT_40001997 = DAT_40001997 + 1;
      }
      obd_ii_monitor_pass(&DAT_4000e261,&DAT_40002ce6);
    }
  }
  if (((DAT_4000e262 & 7) != 0) && ((DAT_400015b8 & 1) != 0)) {
    if (DAT_4000e414 < oil_temp_sensor_voltage) {
      DAT_40001998 = DAT_40001998 + 1;
      if (DAT_40001676 <= (short)(ushort)DAT_40001998) {
        DAT_40001998 = 0;
        bVar6 = DAT_40001999 - 1;
        if (DAT_40001999 == 0) {
          bVar6 = DAT_40001999;
        }
        DAT_40001999 = bVar6;
        if (bVar6 == 0) {
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e262,&DAT_40002ce9,&DAT_40002cea,&DAT_40002ceb,0x713,0);
        }
      }
    }
    else {
      DAT_40001998 = 0;
      if (DAT_40001999 < DAT_4000e334) {
        DAT_40001999 = DAT_40001999 + 1;
      }
      obd_ii_monitor_pass(&DAT_4000e262,&DAT_40002ce9);
    }
  }
  if ((((((CAL_obd_P0717_cfg & 7) != 0) && ((DAT_40001678 & 2) == 0)) && ((DAT_40001678 & 1) == 0))
      && (((((DAT_40001678 & 0x20) == 0 && ((DAT_40001678 & 0x3c00) == 0)) &&
           (((DAT_40001678 & 4) == 0 &&
            (((DAT_40001678 & 8) == 0 && ((DAT_40001678 & 0x40000) == 0)))))) &&
          (engine_running != '\0')))) &&
     (((DAT_4000e424 < DAT_400015ba && ((DAT_400015b8 & 1) != 0)) &&
      (CAL_output_shaft_speed_gate <= output_shaft_rpm)))) {
    if (input_shaft_rpm < CAL_input_shaft_speed_min) {
      DAT_4000199d = DAT_4000199d + 1;
      if (DAT_4000e42a <= DAT_4000199d) {
        DAT_4000199d = 0;
        bVar6 = DAT_4000199e - 1;
        if (DAT_4000199e == 0) {
          bVar6 = DAT_4000199e;
        }
        DAT_4000199e = bVar6;
        if (bVar6 == 0) {
          obd_ii_dtc_confirm_and_freeze
                    (&CAL_obd_P0717_cfg,&obd_P0717_dtc_state,&DAT_40002cf0,&DAT_40002cf1,0x717,0);
        }
      }
    }
    else {
      DAT_4000199d = 0;
      if (DAT_4000199e < DAT_4000e336) {
        DAT_4000199e = DAT_4000199e + 1;
      }
      obd_ii_monitor_pass(&CAL_obd_P0717_cfg,&obd_P0717_dtc_state);
    }
  }
  if ((((CAL_obd_P0718_cfg & 7) == 0) || ((DAT_40001678 & 2) != 0)) ||
     ((((((DAT_40001678 & 1) != 0 ||
         (((DAT_40001678 & 0x3c00) != 0 || ((DAT_40001678 & 0x8000) != 0)))) ||
        ((DAT_40001678 & 0x4000) != 0)) ||
       (((((((DAT_40001678 & 0x200) != 0 || ((DAT_40001678 & 8) != 0)) ||
           ((DAT_40001678 & 0x40000) != 0)) ||
          ((engine_running == '\0' || ((DAT_400015b8 & 1) == 0)))) ||
         (DAT_40001540 <= (uint)DAT_4000e419 * 0x14)) ||
        ((7 < (byte)(ips_gear_cur - GEAR_1) && (ips_gear_cur != GEAR_REV)))))) ||
      (vehicle_speed____ / 100 < (uint)DAT_4000e41a)))) {
    speed_sensor_glitch_flags = speed_sensor_glitch_flags & 0xfe;
  }
  else if ((speed_sensor_glitch_flags & 1) == 0) {
    if (DAT_4000199a < DAT_4000e335) {
      cVar5 = DAT_4000199c + -1;
      if (DAT_4000199c == '\0') {
        cVar5 = DAT_4000199c;
      }
      DAT_4000199c = cVar5;
      if (cVar5 == '\0') {
        DAT_4000199c = DAT_4000e418;
        DAT_4000199a = DAT_4000199a + 1;
      }
    }
    obd_ii_monitor_pass(&CAL_obd_P0718_cfg,&obd_P0718_dtc_state);
  }
  else {
    speed_sensor_glitch_flags = speed_sensor_glitch_flags & 0xfe;
    DAT_4000199c = DAT_4000e418;
    bVar6 = DAT_4000199a - 1;
    if (DAT_4000199a == 0) {
      bVar6 = DAT_4000199a;
    }
    DAT_4000199a = bVar6;
    if (bVar6 == 0) {
      obd_ii_dtc_confirm_and_freeze
                (&CAL_obd_P0718_cfg,&obd_P0718_dtc_state,&DAT_40002ced,&DAT_40002cee,0x718,0);
    }
  }
  if (((((DAT_4000e27f & 7) != 0) && ((DAT_40001678 & 0x40000) == 0)) &&
      ((DAT_4000171e & 0x20) == 0)) && (((DAT_400015b8 & 1) != 0 && ((DAT_4000171e & 0x10) != 0))))
  {
    if ((DAT_4000171e & 0x40) == 0) {
      DAT_4000199f = DAT_4000199f + 1;
      if (DAT_4000e42b <= DAT_4000199f) {
        DAT_4000199f = 0;
        bVar6 = DAT_400019a0 - 1;
        if (DAT_400019a0 == 0) {
          bVar6 = DAT_400019a0;
        }
        DAT_400019a0 = bVar6;
        if (bVar6 == 0) {
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e27f,&DAT_40002cf2,&DAT_40002cf3,&DAT_40002cf4,0x719,0);
        }
      }
    }
    else {
      DAT_4000199f = 0;
      if (DAT_400019a0 < DAT_4000e351) {
        DAT_400019a0 = DAT_400019a0 + 1;
      }
      obd_ii_monitor_pass(&DAT_4000e27f,&DAT_40002cf2);
    }
  }
  if ((((((CAL_obd_P0721_cfg & 7) != 0) && ((obd_P0722_dtc_state & 8) != 0)) &&
       (((obd_P0722_dtc_state & 4) == 0 &&
        ((((DAT_40001678 & 2) == 0 && ((DAT_40001678 & 1) == 0)) && ((DAT_40001678 & 0x200) == 0))))
       )) && (((DAT_40001678 & 4) == 0 && ((DAT_40001678 & 0x3c00) == 0)))) &&
     ((engine_running != '\0' && ((DAT_400015b8 & 1) != 0)))) {
    uVar4 = (int)((uint)vehicle_speed____ * (uint)DAT_4000e42e) / 10000;
    DAT_400019a4 = (short)uVar4;
    if (DAT_400019a4 != 0) {
      uVar1 = ((uint)output_shaft_rpm * 100) / (uVar4 & 0xffff);
      DAT_400019a6 = (ushort)uVar1;
      DAT_400019a8 = (undefined2)
                     (((longlong)(int)(100 - (uint)DAT_4000e42c) * (longlong)(int)(uVar4 & 0xffff) &
                      0xffffffffU) / 100);
      DAT_400019aa = (undefined2)
                     ((ulonglong)
                      ((longlong)(int)(DAT_4000e42c + 100) * (longlong)(int)(uVar4 & 0xffff)) / 100)
      ;
      if (vehicle_speed____ / 100 < (uint)DAT_4000e42d) {
        DAT_400019a8 = 0;
        DAT_400019aa = 0;
        DAT_400019a6 = 0;
      }
      else if ((DAT_400019a6 < (ushort)(DAT_4000e42c + 100)) &&
              (100 - DAT_4000e42c < (uVar1 & 0xffff))) {
        DAT_400019a1 = 0;
        if (DAT_400019a2 < DAT_4000e352) {
          DAT_400019a2 = DAT_400019a2 + 1;
        }
        obd_ii_monitor_pass(&CAL_obd_P0721_cfg,&obd_P0721_dtc_state);
      }
      else {
        if (DAT_400019ac == 0) {
          DAT_400019a1 = DAT_400019a1 + 1;
        }
        if (DAT_4000e430 <= DAT_400019a1) {
          DAT_400019a1 = 0;
          bVar6 = DAT_400019a2 - 1;
          if (DAT_400019a2 == 0) {
            bVar6 = DAT_400019a2;
          }
          DAT_400019a2 = bVar6;
          if (bVar6 == 0) {
            obd_ii_dtc_confirm_and_freeze
                      (&CAL_obd_P0721_cfg,&obd_P0721_dtc_state,&DAT_40002cf6,&DAT_40002cf7,0x721,0);
          }
        }
      }
    }
  }
  if (((((((CAL_obd_P0722_cfg & 7) != 0) && ((DAT_40001678 & 2) == 0)) && ((DAT_40001678 & 1) == 0))
       && (((DAT_40001678 & 0x200) == 0 && ((DAT_40001678 & 0x20) == 0)))) &&
      (((DAT_40001678 & 4) == 0 && (((DAT_40001678 & 0x40000) == 0 && (engine_running != '\0'))))))
     && (((DAT_400015b8 & 1) != 0 &&
         ((DAT_4000e43a < DAT_400015ba && ((uint)DAT_4000e43e <= vehicle_speed____ / 100)))))) {
    if (output_shaft_rpm < CAL_output_shaft_speed_min) {
      DAT_400019ac = DAT_400019ac + 1;
      if (DAT_4000e43f <= DAT_400019ac) {
        DAT_400019ac = 0;
        bVar6 = DAT_400019ad - 1;
        if (DAT_400019ad == 0) {
          bVar6 = DAT_400019ad;
        }
        DAT_400019ad = bVar6;
        if (bVar6 == 0) {
          obd_ii_dtc_confirm_and_freeze
                    (&CAL_obd_P0722_cfg,&obd_P0722_dtc_state,&DAT_40002cf9,&DAT_40002cfa,0x722,0);
        }
      }
    }
    else {
      DAT_400019ac = 0;
      if (DAT_400019ad < DAT_4000e353) {
        DAT_400019ad = DAT_400019ad + 1;
      }
      obd_ii_monitor_pass(&CAL_obd_P0722_cfg,&obd_P0722_dtc_state);
    }
  }
  if ((((((CAL_obd_P0723_cfg & 7) == 0) || ((obd_P0722_dtc_state & 8) == 0)) ||
       ((obd_P0722_dtc_state & 4) != 0)) ||
      ((((DAT_40001678 & 2) != 0 || ((DAT_40001678 & 1) != 0)) ||
       (((DAT_40001678 & 0x200) != 0 ||
        (((DAT_40001678 & 4) != 0 || ((DAT_40001678 & 0x3c00) != 0)))))))) ||
     (((((DAT_40001678 & 0x40000) != 0 ||
        (((engine_running == '\0' || ((DAT_400015b8 & 1) == 0)) ||
         (DAT_40001540 <= (uint)DAT_4000e437 * 0x14)))) ||
       (((7 < (byte)(ips_gear_cur - GEAR_1) && (ips_gear_cur != GEAR_REV)) &&
        (ips_gear_cur != NEUTRAL)))) || (vehicle_speed____ / 100 < (uint)DAT_4000e438)))) {
    speed_sensor_glitch_flags = speed_sensor_glitch_flags & 0xfd;
  }
  else if ((speed_sensor_glitch_flags & 2) == 0) {
    if (DAT_400019ae < DAT_4000e348) {
      cVar5 = DAT_400019af + -1;
      if (DAT_400019af == '\0') {
        cVar5 = DAT_400019af;
      }
      DAT_400019af = cVar5;
      if (cVar5 == '\0') {
        DAT_400019af = DAT_4000e436;
        DAT_400019ae = DAT_400019ae + 1;
      }
    }
    obd_ii_monitor_pass(&CAL_obd_P0723_cfg,&obd_P0723_dtc_state);
  }
  else {
    speed_sensor_glitch_flags = speed_sensor_glitch_flags & 0xfd;
    DAT_400019af = DAT_4000e436;
    bVar6 = DAT_400019ae - 1;
    if (DAT_400019ae == 0) {
      bVar6 = DAT_400019ae;
    }
    DAT_400019ae = bVar6;
    if (bVar6 == 0) {
      obd_ii_dtc_confirm_and_freeze
                (&CAL_obd_P0723_cfg,&obd_P0723_dtc_state,&DAT_40002cfc,&DAT_40002cfd,0x723,0);
    }
  }
  if ((((DAT_4000e265 & 7) != 0) && ((DAT_40001678 & 0x40000) == 0)) &&
     (((DAT_4000171e & 0x20) == 0 && (((DAT_400015b8 & 1) != 0 && ((DAT_4000171e & 0x10) == 0))))))
  {
    if ((DAT_4000171e & 0x40) == 0) {
      DAT_400019b0 = 0;
      if (DAT_400019b1 < DAT_4000e337) {
        DAT_400019b1 = DAT_400019b1 + 1;
      }
      obd_ii_monitor_pass(&DAT_4000e265,&DAT_40002cfe);
    }
    else {
      DAT_400019b0 = DAT_400019b0 + 1;
      if (DAT_4000e440 <= DAT_400019b0) {
        DAT_400019b0 = 0;
        bVar6 = DAT_400019b1 - 1;
        if (DAT_400019b1 == 0) {
          bVar6 = DAT_400019b1;
        }
        DAT_400019b1 = bVar6;
        if (bVar6 == 0) {
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e265,&DAT_40002cfe,&DAT_40002cff,&DAT_40002d00,0x724,0);
        }
      }
    }
  }
  if (((DAT_4000e26b & 7) != 0) && ((DAT_400015b8 & 1) != 0)) {
    if ((uint)((int)(uint)DAT_40001dc0 >> 4) < 0x200) {
      DAT_400019b2 = DAT_400019b2 + 1;
      if ((ushort)((ushort)DAT_4000e4de * 10) <= DAT_400019b2) {
        DAT_400019b2 = 0;
        bVar6 = DAT_400019b4 - 1;
        if (DAT_400019b4 == 0) {
          bVar6 = DAT_400019b4;
        }
        DAT_400019b4 = bVar6;
        if (bVar6 == 0) {
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e26b,&DAT_40002d22,&DAT_40002d23,&DAT_40002d24,0x812,0);
        }
      }
    }
    else {
      DAT_400019b2 = 0;
      if (DAT_400019b4 < DAT_4000e33d) {
        DAT_400019b4 = DAT_400019b4 + 1;
      }
      obd_ii_monitor_pass(&DAT_4000e26b,&DAT_40002d22);
    }
  }
  if (((DAT_4000e26c & 7) != 0) && ((DAT_400015b8 & 1) != 0)) {
    if ((uint)((int)(uint)DAT_40001dbc >> 4) < 0x200) {
      DAT_400019b6 = DAT_400019b6 + 1;
      if ((ushort)((ushort)DAT_4000e4df * 10) <= DAT_400019b6) {
        DAT_400019b6 = 0;
        bVar6 = DAT_400019b8 - 1;
        if (DAT_400019b8 == 0) {
          bVar6 = DAT_400019b8;
        }
        DAT_400019b8 = bVar6;
        if (bVar6 == 0) {
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e26c,&DAT_40002d28,&DAT_40002d29,&DAT_40002d2a,0x81c,0);
        }
      }
    }
    else {
      DAT_400019b6 = 0;
      if (DAT_400019b8 < DAT_4000e33e) {
        DAT_400019b8 = DAT_400019b8 + 1;
      }
      obd_ii_monitor_pass(&DAT_4000e26c,&DAT_40002d28);
    }
  }
  if (((DAT_4000e26d & 7) != 0) && ((DAT_400015b8 & 1) != 0)) {
    if ((uint)((int)(uint)DAT_40001dbe >> 4) < 0x200) {
      DAT_400019ba = DAT_400019ba + 1;
      if ((ushort)((ushort)DAT_4000e4e0 * 10) <= DAT_400019ba) {
        DAT_400019ba = 0;
        bVar6 = DAT_400019bc - 1;
        if (DAT_400019bc == 0) {
          bVar6 = DAT_400019bc;
        }
        DAT_400019bc = bVar6;
        if (bVar6 == 0) {
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e26d,&DAT_40002d2b,&DAT_40002d2c,&DAT_40002d2d,0x81d,0);
        }
      }
    }
    else {
      DAT_400019ba = 0;
      if (DAT_400019bc < DAT_4000e33f) {
        DAT_400019bc = DAT_400019bc + 1;
      }
      obd_ii_monitor_pass(&DAT_4000e26d,&DAT_40002d2b);
    }
  }
  if (((((((DAT_4000e26f & 7) != 0) && ((DAT_40001678 & 2) == 0)) && ((DAT_40001678 & 1) == 0)) &&
       (((DAT_40001678 & 4) == 0 && ((DAT_40001678 & 8) == 0)))) &&
      (((DAT_40001678 & 0x3c00) == 0 &&
       (((DAT_40001678 & 0x200) == 0 && ((DAT_40001678 & 0x40000) == 0)))))) &&
     (((DAT_40001678 & 0x10) == 0 &&
      (((((DAT_400015b8 & 1) != 0 && (engine_running != '\0')) && (DAT_4000148d == -1)) &&
       ((((byte)(gear_request - GEAR_1) < 4 && ((uint)DAT_4000e4e6 <= vehicle_speed____ / 100)) &&
        ((DAT_40001a44 == gear_request &&
         ((uint)DAT_4000e4e2 <= ((int)solenoid_SL1_demand / 100 & 0xffU))))))))))) {
    if (discrete_input_state == '\0') {
      DAT_400019be = DAT_400019be + 1;
      if (DAT_40001676 < (short)(ushort)DAT_400019be) {
        DAT_400019be = 0;
        bVar6 = DAT_400019bd - 1;
        if (DAT_400019bd == 0) {
          bVar6 = DAT_400019bd;
        }
        DAT_400019bd = bVar6;
        if (bVar6 == 0) {
          DAT_400019bd = 0;
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e26f,&DAT_40002d2e,&DAT_40002d2f,&DAT_40002d30,0x842,0);
        }
      }
    }
    else {
      DAT_400019be = 0;
      if (DAT_400019bd < DAT_4000e341) {
        DAT_400019bd = DAT_400019bd + 1;
      }
      obd_ii_monitor_pass(&DAT_4000e26f,&DAT_40002d2e);
    }
  }
  if (((((DAT_4000e270 & 7) != 0) && ((DAT_40001678 & 2) == 0)) &&
      (((DAT_40001678 & 1) == 0 &&
       ((((DAT_40001678 & 4) == 0 && ((DAT_40001678 & 8) == 0)) && ((DAT_40001678 & 0x3c00) == 0))))
      )) && ((((((DAT_40001678 & 0x200) == 0 && ((DAT_40001678 & 0x40000) == 0)) &&
               ((DAT_40001678 & 0x10) == 0)) &&
              (((DAT_400015b8 & 1) != 0 && (engine_running != '\0')))) &&
             ((DAT_4000148d == -1 &&
              ((((byte)(gear_request - GEAR_5) < 2 && (DAT_40001a44 == gear_request)) &&
               (((int)solenoid_SL1_demand / 100 & 0xffU) <= (uint)DAT_4000e4e3)))))))) {
    if (discrete_input_state == '\x01') {
      DAT_400019c0 = DAT_400019c0 + 1;
      if (DAT_40001676 < (short)(ushort)DAT_400019c0) {
        DAT_400019c0 = 0;
        bVar6 = DAT_400019bf - 1;
        if (DAT_400019bf == 0) {
          bVar6 = DAT_400019bf;
        }
        DAT_400019bf = bVar6;
        if (bVar6 == 0) {
          DAT_400019bf = 0;
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e270,&DAT_40002d31,&DAT_40002d32,&DAT_40002d33,0x843,0);
        }
      }
    }
    else {
      DAT_400019c0 = 0;
      if (DAT_400019bf < DAT_4000e342) {
        DAT_400019bf = DAT_400019bf + 1;
      }
      obd_ii_monitor_pass(&DAT_4000e270,&DAT_40002d31);
    }
  }
  if ((((DAT_4000e271 & 7) != 0) && ((DAT_40001678 & 2) == 0)) &&
     (((((DAT_40001678 & 1) == 0 && (((DAT_40001678 & 4) == 0 && ((DAT_40001678 & 8) == 0)))) &&
       ((DAT_40001678 & 0x3c00) == 0)) &&
      (((((((DAT_40001678 & 0x200) == 0 && ((DAT_40001678 & 0x40000) == 0)) &&
          ((DAT_40001678 & 0x10) == 0)) && (((DAT_400015b8 & 1) != 0 && (engine_running != '\0'))))
        && (DAT_4000148d == -1)) &&
       ((((byte)(gear_request - GEAR_4) < 3 && (DAT_40001a44 == gear_request)) &&
        ((uint)DAT_4000e4e4 <= ((int)solenoid_SL2_demand / 100 & 0xffU))))))))) {
    if (DAT_400023a1 == '\0') {
      DAT_400019c2 = DAT_400019c2 + 1;
      if (DAT_40001676 < (short)(ushort)DAT_400019c2) {
        DAT_400019c2 = 0;
        bVar6 = DAT_400019c1 - 1;
        if (DAT_400019c1 == 0) {
          bVar6 = DAT_400019c1;
        }
        DAT_400019c1 = bVar6;
        if (bVar6 == 0) {
          DAT_400019c1 = 0;
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e271,&DAT_40002d34,&DAT_40002d35,&DAT_40002d36,0x847,0);
        }
      }
    }
    else {
      DAT_400019c2 = 0;
      if (DAT_400019c1 < DAT_4000e343) {
        DAT_400019c1 = DAT_400019c1 + 1;
      }
      obd_ii_monitor_pass(&DAT_4000e271,&DAT_40002d34);
    }
  }
  if ((((((DAT_4000e272 & 7) != 0) && ((DAT_40001678 & 2) == 0)) && ((DAT_40001678 & 1) == 0)) &&
      ((((DAT_40001678 & 4) == 0 && ((DAT_40001678 & 8) == 0)) &&
       (((DAT_40001678 & 0x3c00) == 0 &&
        (((DAT_40001678 & 0x200) == 0 && ((DAT_40001678 & 0x40000) == 0)))))))) &&
     (((DAT_40001678 & 0x10) == 0 &&
      ((((((DAT_400015b8 & 1) != 0 && (engine_running != '\0')) && (DAT_4000148d == -1)) &&
        (((byte)(gear_request - GEAR_1) < 3 && (DAT_40001a44 == gear_request)))) &&
       (((int)solenoid_SL2_demand / 100 & 0xffU) <= (uint)DAT_4000e4e5)))))) {
    if (DAT_400023a1 == '\x01') {
      DAT_400019c4 = DAT_400019c4 + 1;
      if (DAT_40001676 < (short)(ushort)DAT_400019c4) {
        DAT_400019c4 = 0;
        bVar6 = DAT_400019c3 - 1;
        if (DAT_400019c3 == 0) {
          bVar6 = DAT_400019c3;
        }
        DAT_400019c3 = bVar6;
        if (bVar6 == 0) {
          DAT_400019c3 = 0;
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e272,&DAT_40002d37,&DAT_40002d38,&DAT_40002d39,0x848,0);
        }
      }
    }
    else {
      DAT_400019c4 = 0;
      if (DAT_400019c3 < DAT_4000e344) {
        DAT_400019c3 = DAT_400019c3 + 1;
      }
      obd_ii_monitor_pass(&DAT_4000e272,&DAT_40002d37);
    }
  }
  if (((DAT_4000e26e & 7) != 0) && ((DAT_400015b8 & 1) != 0)) {
    if ((uint)((int)(uint)DAT_40001dc2 >> 4) < 0x200) {
      DAT_400019c6 = DAT_400019c6 + 1;
      if ((ushort)((ushort)DAT_4000e4e1 * 10) <= DAT_400019c6) {
        DAT_400019c6 = 0;
        bVar6 = DAT_400019c8 - 1;
        if (DAT_400019c8 == 0) {
          bVar6 = DAT_400019c8;
        }
        DAT_400019c8 = bVar6;
        if (bVar6 == 0) {
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e26e,&DAT_40002d3a,&DAT_40002d3b,&DAT_40002d3c,0x853,0);
        }
      }
    }
    else {
      DAT_400019c6 = 0;
      if (DAT_400019c8 < DAT_4000e340) {
        DAT_400019c8 = DAT_400019c8 + 1;
      }
      obd_ii_monitor_pass(&DAT_4000e26e,&DAT_40002d3a);
    }
  }
  if (((((((DAT_4000e273 & 7) != 0) && ((DAT_40001678 & 2) == 0)) && ((DAT_40001678 & 1) == 0)) &&
       (((DAT_40001678 & 4) == 0 && ((DAT_40001678 & 8) == 0)))) &&
      (((DAT_40001678 & 0x3c00) == 0 &&
       (((DAT_40001678 & 0x200) == 0 && ((DAT_40001678 & 0x10) == 0)))))) &&
     ((((DAT_40001678 & 0x4000) == 0 &&
       ((((DAT_40001678 & 0x40000) == 0 && ((DAT_400015b8 & 1) != 0)) && (engine_running != '\0'))))
      && (((DAT_400018bf & 1) != 0 && ((DAT_400018bf & 0x10) != 0)))))) {
    if (DAT_400023a2 == '\0') {
      DAT_400019ca = DAT_400019ca + 1;
      if (DAT_40001676 < (short)(ushort)DAT_400019ca) {
        DAT_400019ca = 0;
        bVar6 = DAT_400019c9 - 1;
        if (DAT_400019c9 == 0) {
          bVar6 = DAT_400019c9;
        }
        DAT_400019c9 = bVar6;
        if (bVar6 == 0) {
          DAT_400019c9 = 0;
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e273,&DAT_40002d3d,&DAT_40002d3e,&DAT_40002d3f,0x872,0);
        }
      }
    }
    else {
      DAT_400019ca = 0;
      if (DAT_400019c9 < DAT_4000e345) {
        DAT_400019c9 = DAT_400019c9 + 1;
      }
      obd_ii_monitor_pass(&DAT_4000e273,&DAT_40002d3d);
    }
  }
  if (((((DAT_4000e274 & 7) != 0) && ((DAT_40001678 & 2) == 0)) &&
      (((DAT_40001678 & 1) == 0 &&
       ((((DAT_40001678 & 4) == 0 && ((DAT_40001678 & 8) == 0)) && ((DAT_40001678 & 0x3c00) == 0))))
      )) && ((((DAT_40001678 & 0x200) == 0 && ((DAT_40001678 & 0x10) == 0)) &&
             (((DAT_40001678 & 0x4000) == 0 &&
              (((DAT_40001678 & 0x40000) == 0 && ((DAT_400015b8 & 1) != 0)))))))) {
    if (DAT_400023a2 == '\x01') {
      if ((((engine_running != '\0') && ((DAT_400018bf & 2) != 0)) && ((DAT_400018bf & 0x20) != 0))
         && (((DAT_400018c2 & 0x20) != 0 &&
             (DAT_400019cc = DAT_400019cc + 1, DAT_40001676 < (short)(ushort)DAT_400019cc)))) {
        DAT_400019cc = 0;
        bVar6 = DAT_400019cb - 1;
        if (DAT_400019cb == 0) {
          bVar6 = DAT_400019cb;
        }
        DAT_400019cb = bVar6;
        if (bVar6 == 0) {
          DAT_400019cb = 0;
          obd_ii_dtc_confirm_and_freeze
                    (&DAT_4000e274,&DAT_40002d40,&DAT_40002d41,&DAT_40002d42,0x873,0);
        }
      }
    }
    else {
      DAT_400019cc = 0;
      if (DAT_400019cb < DAT_4000e346) {
        DAT_400019cb = DAT_400019cb + 1;
      }
      obd_ii_monitor_pass(&DAT_4000e274,&DAT_40002d40);
    }
  }
  if ((((DAT_40002cc5 & 8) == 0) || ((DAT_40002cc5 & 4) == 0)) ||
     (((DAT_40002cc5 & 1) == 0 && (DAT_4000167c == '\0')))) {
    DAT_40001678 = DAT_40001678 & 0xbfffffff;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x40000000;
  }
  if (((((DAT_40002ce0 & 8) == 0) || ((DAT_40002ce0 & 4) == 0)) || ((DAT_40002ce0 & 1) == 0)) &&
     (((((DAT_40002ce3 & 8) == 0 || ((DAT_40002ce3 & 4) == 0)) || ((DAT_40002ce3 & 1) == 0)) &&
      (((((DAT_40002ce6 & 8) == 0 || ((DAT_40002ce6 & 4) == 0)) || ((DAT_40002ce6 & 1) == 0)) &&
       ((((DAT_40002ce9 & 8) == 0 || ((DAT_40002ce9 & 4) == 0)) || ((DAT_40002ce9 & 1) == 0))))))))
  {
    DAT_40001678 = DAT_40001678 & 0xffffffef;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x10;
  }
  if (((((DAT_40002cc8 & 8) == 0) || ((DAT_40002cc8 & 4) == 0)) || ((DAT_40002cc8 & 1) == 0)) &&
     ((DAT_40001678 & 0x80000) == 0)) {
    DAT_40001678 = DAT_40001678 & 0xfffffdff;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x200;
  }
  if (((((DAT_40002ccb & 8) == 0) || ((DAT_40002ccb & 4) == 0)) || ((DAT_40002ccb & 1) == 0)) &&
     ((((DAT_40002cce & 8) == 0 || ((DAT_40002cce & 4) == 0)) || ((DAT_40002cce & 1) == 0)))) {
    DAT_40001678 = DAT_40001678 & 0xffffffdf;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x20;
  }
  if (((((obd_P0717_dtc_state & 8) == 0) || ((obd_P0717_dtc_state & 4) == 0)) ||
      ((obd_P0717_dtc_state & 1) == 0)) &&
     ((((obd_P0718_dtc_state & 8) == 0 || ((obd_P0718_dtc_state & 4) == 0)) ||
      ((obd_P0718_dtc_state & 1) == 0)))) {
    DAT_40001678 = DAT_40001678 & 0xfffffff7;
  }
  else {
    DAT_40001678 = DAT_40001678 | 8;
  }
  if ((((((obd_P0721_dtc_state & 8) == 0) || ((obd_P0721_dtc_state & 4) == 0)) ||
       ((obd_P0721_dtc_state & 1) == 0)) &&
      ((((obd_P0722_dtc_state & 8) == 0 || ((obd_P0722_dtc_state & 4) == 0)) ||
       ((obd_P0722_dtc_state & 1) == 0)))) &&
     ((((obd_P0723_dtc_state & 8) == 0 || ((obd_P0723_dtc_state & 4) == 0)) ||
      ((obd_P0723_dtc_state & 1) == 0)))) {
    DAT_40001678 = DAT_40001678 & 0xfffffffb;
  }
  else {
    DAT_40001678 = DAT_40001678 | 4;
  }
  if (((((DAT_40002d2e & 8) == 0) || ((DAT_40002d2e & 4) == 0)) || ((DAT_40002d2e & 1) == 0)) &&
     ((((DAT_40002d31 & 8) == 0 || ((DAT_40002d31 & 4) == 0)) || ((DAT_40002d31 & 1) == 0)))) {
    DAT_40001678 = DAT_40001678 & 0xffffffbf;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x40;
  }
  if (((((DAT_40002d34 & 8) == 0) || ((DAT_40002d34 & 4) == 0)) || ((DAT_40002d34 & 1) == 0)) &&
     ((((DAT_40002d37 & 8) == 0 || ((DAT_40002d37 & 4) == 0)) || ((DAT_40002d37 & 1) == 0)))) {
    DAT_40001678 = DAT_40001678 & 0xffffff7f;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x80;
  }
  if (((((DAT_40002d3d & 8) == 0) || ((DAT_40002d3d & 4) == 0)) || ((DAT_40002d3d & 1) == 0)) &&
     ((((DAT_40002d40 & 8) == 0 || ((DAT_40002d40 & 4) == 0)) || ((DAT_40002d40 & 1) == 0)))) {
    DAT_40001678 = DAT_40001678 & 0xfffffeff;
  }
  else {
    DAT_40001678 = DAT_40001678 | 0x100;
  }
  if ((((DAT_4000e27f & 7) == 0) || ((DAT_40002cf2 & 4) == 0)) &&
     (((DAT_4000e265 & 7) == 0 || ((DAT_40002cfe & 4) == 0)))) {
    DAT_4000171e = DAT_4000171e & 0x7f;
  }
  else {
    DAT_4000171e = DAT_4000171e | 0x80;
  }
  uVar4 = DAT_40001678 & 0x7fffffff;
  if (DAT_40001655 == -1) {
    uVar4 = DAT_40001678 | 0x80000000;
  }
  DAT_40001678 = uVar4;
  return;
}



void update_shaft_speeds_and_glitch(void)

{
  uint uVar2;
  ulonglong uVar1;
  
  if ((DAT_400015ac == 0) || (DAT_400015ac == 0xfffff)) {
    input_shaft_rpm_inst = 0;
  }
  else {
    input_shaft_rpm_inst = (u16_rspeed_rpm)(1500000 / (ulonglong)DAT_400015ac);
  }
  uVar2 = (0x100 - (uint)CAL_input_speed_iir_coef) * DAT_400019d0;
  DAT_400019d0 = ((int)uVar2 >> 8) + (uint)((int)uVar2 < 0 && (uVar2 & 0xff) != 0) +
                 (uint)CAL_input_speed_iir_coef * (uint)input_shaft_rpm_inst;
  input_shaft_rpm_smoothed =
       (short)(DAT_400019d0 >> 8) + (ushort)((int)DAT_400019d0 < 0 && (DAT_400019d0 & 0xff) != 0);
  if ((input_shaft_rpm_smoothed != 0) &&
     ((uVar1 = ((ulonglong)input_shaft_rpm_inst * 100) / (ulonglong)input_shaft_rpm_smoothed,
      DAT_400019d6 = (undefined1)uVar1,
      (ulonglong)CAL_input_speed_glitch_tol_pct + 100 <= (uVar1 & 0xff) ||
      ((uVar1 & 0xff) <= (100 - (ulonglong)CAL_input_speed_glitch_tol_pct & 0xffffffff))))) {
    speed_sensor_glitch_flags = speed_sensor_glitch_flags | 1;
  }
  if ((DAT_400015a8 == 0) || (DAT_400015a8 == 0xfffff)) {
    output_shaft_rpm_inst = 0;
  }
  else {
    output_shaft_rpm_inst = (u16_rspeed_rpm)(0x14ceb4 / (ulonglong)DAT_400015a8);
  }
  uVar2 = (0x100 - (uint)CAL_output_speed_iir_coef) * DAT_400019dc;
  DAT_400019dc = ((int)uVar2 >> 8) + (uint)((int)uVar2 < 0 && (uVar2 & 0xff) != 0) +
                 (uint)CAL_output_speed_iir_coef * (uint)output_shaft_rpm_inst;
  output_shaft_rpm_smoothed =
       (short)(DAT_400019dc >> 8) + (ushort)((int)DAT_400019dc < 0 && (DAT_400019dc & 0xff) != 0);
  if ((output_shaft_rpm_smoothed != 0) &&
     ((uVar1 = ((ulonglong)output_shaft_rpm_inst * 100) / (ulonglong)output_shaft_rpm_smoothed,
      DAT_400019e2 = (undefined1)uVar1,
      (ulonglong)CAL_output_speed_glitch_tol_pct + 100 <= (uVar1 & 0xff) ||
      ((uVar1 & 0xff) <= (100 - (ulonglong)CAL_output_speed_glitch_tol_pct & 0xffffffff))))) {
    speed_sensor_glitch_flags = speed_sensor_glitch_flags | 2;
  }
  return;
}



void FUN_0006f96c(void)

{
  DAT_4000197c = DAT_4000e347;
  DAT_4000197e = DAT_4000e330;
  DAT_40001980 = DAT_4000e391;
  DAT_40001982 = DAT_4000e34f;
  DAT_40001984 = DAT_4000e350;
  DAT_40001986 = DAT_4000e331;
  DAT_40001995 = DAT_4000e361;
  DAT_40001997 = DAT_4000e333;
  DAT_40001999 = DAT_4000e334;
  DAT_4000199a = DAT_4000e335;
  DAT_4000199e = DAT_4000e336;
  DAT_400019a0 = DAT_4000e351;
  DAT_400019a2 = DAT_4000e352;
  DAT_400019ad = DAT_4000e353;
  DAT_400019ae = DAT_4000e348;
  DAT_400019b1 = DAT_4000e337;
  DAT_400019bd = DAT_4000e341;
  DAT_400019bf = DAT_4000e342;
  DAT_400019c1 = DAT_4000e343;
  DAT_400019c3 = DAT_4000e344;
  DAT_400019c9 = DAT_4000e345;
  DAT_400019cb = DAT_4000e346;
  DAT_4000197d = 0;
  DAT_4000197f = 0;
  DAT_40001983 = 0;
  DAT_40001985 = 0;
  DAT_40001988 = 0;
  DAT_40001989 = 0;
  DAT_40001994 = 0;
  DAT_40001996 = 0;
  DAT_40001998 = 0;
  DAT_4000199d = 0;
  DAT_4000199f = 0;
  DAT_400019a1 = 0;
  DAT_400019ac = 0;
  DAT_400019b0 = 0;
  DAT_400019be = 0;
  DAT_400019c0 = 0;
  DAT_400019c2 = 0;
  DAT_400019c4 = 0;
  DAT_400019ca = 0;
  DAT_400019cc = 0;
  DAT_40001987 = 0;
  DAT_4000198a = DAT_4000e411;
  DAT_4000198c = DAT_4000e4a6;
  DAT_4000198e = DAT_4000e4a8;
  DAT_40001990 = 0;
  DAT_40001992 = 0x3ff;
  speed_sensor_glitch_flags = 0;
  DAT_4000199c = DAT_4000e418;
  DAT_400019af = DAT_4000e436;
  u16_rspeed_rpm_4000197a = 0;
  obd_set_new_DTC(&DAT_4000e275,&DAT_40002cc2,0x71,0);
  obd_set_new_DTC(&DAT_4000e25e,&DAT_40002cc5,0x218,0);
  obd_set_new_DTC(&DAT_4000e2b0,&DAT_40002cc8,0x500,0);
  obd_set_new_DTC(&DAT_4000e27d,&DAT_40002ccb,0x562,0);
  obd_set_new_DTC(&DAT_4000e27e,&DAT_40002cce,0x563,0);
  obd_set_new_DTC(&DAT_4000e25f,&DAT_40002ce0,0x710,0);
  obd_set_new_DTC(&DAT_4000e28f,&DAT_40002ce3,0x711,0);
  obd_set_new_DTC(&DAT_4000e261,&DAT_40002ce6,0x712,0);
  obd_set_new_DTC(&DAT_4000e262,&DAT_40002ce9,0x713,0);
  obd_set_new_DTC(&CAL_obd_P0718_cfg,&obd_P0718_dtc_state,0x718,0);
  obd_set_new_DTC(&CAL_obd_P0717_cfg,&obd_P0717_dtc_state,0x717,0);
  obd_set_new_DTC(&DAT_4000e27f,&DAT_40002cf2,0x719,0);
  obd_set_new_DTC(&CAL_obd_P0721_cfg,&obd_P0721_dtc_state,0x721,0);
  obd_set_new_DTC(&CAL_obd_P0722_cfg,&obd_P0722_dtc_state,0x722,0);
  obd_set_new_DTC(&CAL_obd_P0723_cfg,&obd_P0723_dtc_state,0x723,0);
  obd_set_new_DTC(&DAT_4000e265,&DAT_40002cfe,0x724,0);
  obd_set_new_DTC(&DAT_4000e26b,&DAT_40002d22,0x812,0);
  obd_set_new_DTC(&DAT_4000e26c,&DAT_40002d28,0x81c,0);
  obd_set_new_DTC(&DAT_4000e26d,&DAT_40002d2b,0x81d,0);
  obd_set_new_DTC(&DAT_4000e26f,&DAT_40002d2e,0x842,0);
  obd_set_new_DTC(&DAT_4000e270,&DAT_40002d31,0x843,0);
  obd_set_new_DTC(&DAT_4000e271,&DAT_40002d34,0x847,0);
  obd_set_new_DTC(&DAT_4000e272,&DAT_40002d37,0x848,0);
  obd_set_new_DTC(&DAT_4000e26e,&DAT_40002d3a,0x853,0);
  obd_set_new_DTC(&DAT_4000e273,&DAT_40002d3d,0x872,0);
  obd_set_new_DTC(&DAT_4000e274,&DAT_40002d40,0x873,0);
  return;
}



void FUN_00070078(void)

{
  obd_ii_dtc_aging_heal(&DAT_4000e275,&DAT_40002cc2,&DAT_40002cc3,&DAT_40002cc4,0x71,0);
  obd_ii_dtc_aging_heal(&DAT_4000e25e,&DAT_40002cc5,&DAT_40002cc6,&DAT_40002cc7,0x218,0);
  obd_ii_dtc_aging_heal(&DAT_4000e2b0,&DAT_40002cc8,&DAT_40002cc9,&DAT_40002cca,0x500,0);
  obd_ii_dtc_aging_heal(&DAT_4000e27d,&DAT_40002ccb,&DAT_40002ccc,&DAT_40002ccd,0x562,0);
  obd_ii_dtc_aging_heal(&DAT_4000e27e,&DAT_40002cce,&DAT_40002ccf,&DAT_40002cd0,0x563,0);
  obd_ii_dtc_aging_heal(&DAT_4000e25f,&DAT_40002ce0,&DAT_40002ce1,&DAT_40002ce2,0x710,0);
  obd_ii_dtc_aging_heal(&DAT_4000e28f,&DAT_40002ce3,&DAT_40002ce4,&DAT_40002ce5,0x711,0);
  obd_ii_dtc_aging_heal(&DAT_4000e261,&DAT_40002ce6,&DAT_40002ce7,&DAT_40002ce8,0x712,0);
  obd_ii_dtc_aging_heal(&DAT_4000e262,&DAT_40002ce9,&DAT_40002cea,&DAT_40002ceb,0x713,0);
  obd_ii_dtc_aging_heal(&CAL_obd_P0718_cfg,&obd_P0718_dtc_state,&DAT_40002ced,&DAT_40002cee,0x718,0)
  ;
  obd_ii_dtc_aging_heal(&CAL_obd_P0717_cfg,&obd_P0717_dtc_state,&DAT_40002cf0,&DAT_40002cf1,0x717,0)
  ;
  obd_ii_dtc_aging_heal(&DAT_4000e27f,&DAT_40002cf2,&DAT_40002cf3,&DAT_40002cf4,0x719,0);
  obd_ii_dtc_aging_heal(&CAL_obd_P0721_cfg,&obd_P0721_dtc_state,&DAT_40002cf6,&DAT_40002cf7,0x721,0)
  ;
  obd_ii_dtc_aging_heal(&CAL_obd_P0722_cfg,&obd_P0722_dtc_state,&DAT_40002cf9,&DAT_40002cfa,0x722,0)
  ;
  obd_ii_dtc_aging_heal(&CAL_obd_P0723_cfg,&obd_P0723_dtc_state,&DAT_40002cfc,&DAT_40002cfd,0x723,0)
  ;
  obd_ii_dtc_aging_heal(&DAT_4000e265,&DAT_40002cfe,&DAT_40002cff,&DAT_40002d00,0x724,0);
  obd_ii_dtc_aging_heal(&DAT_4000e26b,&DAT_40002d22,&DAT_40002d23,&DAT_40002d24,0x812,0);
  obd_ii_dtc_aging_heal(&DAT_4000e26c,&DAT_40002d28,&DAT_40002d29,&DAT_40002d2a,0x81c,0);
  obd_ii_dtc_aging_heal(&DAT_4000e26d,&DAT_40002d2b,&DAT_40002d2c,&DAT_40002d2d,0x81d,0);
  obd_ii_dtc_aging_heal(&DAT_4000e26f,&DAT_40002d2e,&DAT_40002d2f,&DAT_40002d30,0x842,0);
  obd_ii_dtc_aging_heal(&DAT_4000e270,&DAT_40002d31,&DAT_40002d32,&DAT_40002d33,0x843,0);
  obd_ii_dtc_aging_heal(&DAT_4000e271,&DAT_40002d34,&DAT_40002d35,&DAT_40002d36,0x847,0);
  obd_ii_dtc_aging_heal(&DAT_4000e272,&DAT_40002d37,&DAT_40002d38,&DAT_40002d39,0x848,0);
  obd_ii_dtc_aging_heal(&DAT_4000e26e,&DAT_40002d3a,&DAT_40002d3b,&DAT_40002d3c,0x853,0);
  obd_ii_dtc_aging_heal(&DAT_4000e273,&DAT_40002d3d,&DAT_40002d3e,&DAT_40002d3f,0x872,0);
  obd_ii_dtc_aging_heal(&DAT_4000e274,&DAT_40002d40,&DAT_40002d41,&DAT_40002d42,0x873,0);
  return;
}



void lowpass_filter_5_analog_inputs(void)

{
  int iVar1;
  
  iVar1 = (uint)DAT_400019f8 * (uint)PTR_DAT_4000e3e4._0_1_ +
          (0xff - (uint)PTR_DAT_4000e3e4._0_1_) * ((int)(uint)DAT_40001d8e >> 4);
  DAT_400019f8 = ((short)(iVar1 / 0xff) + (short)(iVar1 >> 0x1f)) -
                 (short)((longlong)iVar1 * 0x80808081 >> 0x3f);
  iVar1 = (uint)DAT_400019fa * (uint)PTR_DAT_4000e3e4._0_1_ +
          (0xff - (uint)PTR_DAT_4000e3e4._0_1_) * ((int)(uint)DAT_40001d90 >> 4);
  DAT_400019fa = ((short)(iVar1 / 0xff) + (short)(iVar1 >> 0x1f)) -
                 (short)((longlong)iVar1 * 0x80808081 >> 0x3f);
  iVar1 = (uint)DAT_400019fe * (uint)PTR_DAT_4000e3e4._0_1_ +
          (0xff - (uint)PTR_DAT_4000e3e4._0_1_) * ((int)(uint)DAT_40001d94 >> 4);
  DAT_400019fe = ((short)(iVar1 / 0xff) + (short)(iVar1 >> 0x1f)) -
                 (short)((longlong)iVar1 * 0x80808081 >> 0x3f);
  iVar1 = (uint)DAT_400019fc * (uint)PTR_DAT_4000e3e4._0_1_ +
          (0xff - (uint)PTR_DAT_4000e3e4._0_1_) * ((int)(uint)DAT_40001d92 >> 4);
  DAT_400019fc = ((short)(iVar1 / 0xff) + (short)(iVar1 >> 0x1f)) -
                 (short)((longlong)iVar1 * 0x80808081 >> 0x3f);
  iVar1 = (uint)DAT_40001a00 * (uint)PTR_DAT_4000e3e4._0_1_ +
          (0xff - (uint)PTR_DAT_4000e3e4._0_1_) * ((int)(uint)DAT_40001dcc >> 4);
  DAT_40001a00 = ((short)(iVar1 / 0xff) + (short)(iVar1 >> 0x1f)) -
                 (short)((longlong)iVar1 * 0x80808081 >> 0x3f);
  return;
}



void FUN_00070960(void)

{
  ushort uVar1;
  uint uVar2;
  byte bVar3;
  char cVar4;
  
  if ((DAT_4000e266 & 7) != 0) {
    if ((DAT_400019e8 & 1) == 0) {
      obd_ii_monitor_pass(&DAT_4000e266,&DAT_40002cd1);
    }
    else {
      DAT_400019e8 = DAT_400019e8 & 0xfe;
      obd_ii_dtc_confirm_and_freeze(&DAT_4000e266,&DAT_40002cd1,&DAT_40002cd2,&DAT_40002cd3,0x601,0)
      ;
    }
  }
  if ((DAT_4000e27b & 7) != 0) {
    cVar4 = '\0';
    for (bVar3 = 0; bVar3 < 8; bVar3 = bVar3 + 1) {
      if (COD_unknown[bVar3] == 0xff) {
        cVar4 = cVar4 + '\x01';
      }
    }
    bVar3 = DAT_400019e8 | 0x18;
    DAT_400019e8 = DAT_400019e8 & 0xef;
    if (cVar4 == '\b') {
      DAT_400019e8 = bVar3;
    }
    if ((DAT_400019e8 & 8) == 0) {
      obd_ii_monitor_pass(&DAT_4000e27b,&DAT_40002cd7);
    }
    else {
      DAT_400019e8 = DAT_400019e8 & 0xf7;
      obd_ii_dtc_confirm_and_freeze(&DAT_4000e27b,&DAT_40002cd7,&DAT_40002cd8,&DAT_40002cd9,0x610,0)
      ;
    }
  }
  if ((DAT_4000e267 & 7) != 0) {
    if ((DAT_400019e8 & 2) == 0) {
      obd_ii_monitor_pass(&DAT_4000e267,&DAT_40002cda);
    }
    else {
      DAT_400019e8 = DAT_400019e8 & 0xfd;
      obd_ii_dtc_confirm_and_freeze(&DAT_4000e267,&DAT_40002cda,&DAT_40002cdb,&DAT_40002cdc,0x613,0)
      ;
    }
  }
  uVar1 = DAT_4000165c & 0xc0;
  if (((DAT_4000e260 & 7) != 0) && ((DAT_400015b8 & 1) != 0)) {
    if ((uVar1 == 0x80) || ((uVar1 == 0xc0 || (uVar1 == 0x40)))) {
      DAT_400019eb = DAT_400019eb + 1;
      if ((DAT_40001676 <= (short)(ushort)DAT_400019eb) &&
         ((DAT_400019eb = 0, DAT_400019ea != 0 &&
          (DAT_400019ea = DAT_400019ea - 1, DAT_400019ea == 0)))) {
        obd_ii_dtc_confirm_and_freeze
                  (&DAT_4000e260,&DAT_40002d25,&DAT_40002d26,&DAT_40002d27,0x813,0);
      }
    }
    else {
      DAT_400019eb = 0;
      obd_ii_monitor_pass(&DAT_4000e260,&DAT_40002d25);
      if (DAT_400019ea < DAT_4000e332) {
        DAT_400019ea = DAT_400019ea + 1;
      }
    }
  }
  DAT_4000165c = DAT_4000165c & 0xff3f;
  if ((DAT_4000e28b & 7) != 0) {
    if ((DAT_400013b8 == 0) && (DAT_400015ba != 0)) {
      DAT_400019ed = DAT_400019ed + 1;
      if (((DAT_4000e4f5 <= DAT_400019ed) && (DAT_400019ed = 0, DAT_400019ec != 0)) &&
         (DAT_400019ec = DAT_400019ec - 1, DAT_400019ec == 0)) {
        obd_ii_dtc_confirm_and_freeze
                  (&DAT_4000e28b,&DAT_40002d43,&DAT_40002d44,&DAT_40002d45,0x886,0);
      }
    }
    else {
      DAT_400019ed = 0;
      obd_ii_monitor_pass(&DAT_4000e28b,&DAT_40002d43);
      if (DAT_400019ec < DAT_4000e35d) {
        DAT_400019ec = DAT_400019ec + 1;
      }
    }
  }
  if ((DAT_4000e290 & 7) != 0) {
    if ((((((((DAT_40001678 & 4) != 0) && ((DAT_40001678 & 0x200) != 0)) ||
           (((DAT_40001678 & 0x20) != 0 ||
            (((DAT_40001678 & 8) != 0 || ((DAT_40001678 & 0x10000) != 0)))))) ||
          ((DAT_40001678 & 0x3c00) != 0)) ||
         (((((DAT_40001678 & 0x4000) != 0 || ((DAT_40001678 & 0x8000) != 0)) ||
           ((DAT_40001678 & 0x8000000) != 0)) ||
          (((DAT_40001678 & 0x40000) != 0 || ((DAT_40001678 & 0x80000) != 0)))))) ||
        ((DAT_40001678 & 0x100000) != 0)) &&
       ((tps_commanded <= DAT_4000e431 &&
        (((vehicle_speed != '\0' || (ips_gear_cur == GEAR_INVALID9)) || (ips_gear_cur == NEUTRAL))))
       )) {
      DAT_40001678 = DAT_40001678 | 2;
    }
    if ((DAT_40001678 & 2) == 0) {
      obd_ii_monitor_pass(&DAT_4000e290,&DAT_40002d4c);
    }
    else {
      obd_ii_dtc_confirm_and_freeze
                (&DAT_4000e290,&DAT_40002d4c,&DAT_40002d4d,&DAT_40002d4e,&DAT_00001613,0);
    }
  }
  if ((DAT_4000e292 & 7) != 0) {
    if ((((((DAT_40001678 & 0x800000) != 0) && ((DAT_40001678 & 0x1000000) != 0)) ||
         ((DAT_40001678 & 0x2000000) != 0)) ||
        (((DAT_40001678 & 0x4000000) != 0 || ((DAT_40001678 & 0x10000000) != 0)))) ||
       ((DAT_40001678 & 0x80000000) != 0)) {
      if (((((DAT_40002d5b & 8) == 0) || ((DAT_40002d5b & 4) != 0)) || (DAT_400023a6 == '\0')) &&
         (((shift_position_request_bits & 0xf) != 1 &&
          ((((DAT_40001678 & 0x2000000) != 0 ||
            ((((DAT_40001678 & 0x800000) != 0 && ((DAT_40001678 & 0x1000000) != 0)) ||
             (uVar2 = get_shift_lever_pos_raw___(),
             (int)(uVar2 & 0xffff) < (int)((uint)DAT_40002bda - (uint)DAT_40009012))))) ||
           (uVar2 = get_shift_lever_pos_raw___(),
           (uint)DAT_40002bda + (uint)DAT_40009012 < (uVar2 & 0xffff))))))) {
        DAT_40001678 = DAT_40001678 | 1;
      }
      else {
        DAT_400017a4 = 1;
      }
    }
    if ((DAT_40001678 & 1) == 0) {
      obd_ii_monitor_pass(&DAT_4000e292,&DAT_40002d52);
    }
    else {
      obd_ii_dtc_confirm_and_freeze
                (&DAT_4000e292,&DAT_40002d52,&DAT_40002d53,&DAT_40002d54,&DAT_0000172a,0);
    }
  }
  if (((DAT_4000e293 & 7) != 0) && ((DAT_400015b8 & 1) != 0)) {
    if (((DAT_40008f5d < DAT_40001bea) || (DAT_40001a00 <= DAT_4000e3ee)) &&
       ((DAT_40001a00 <= DAT_4000e3f0 && (DAT_4000e3f2 <= DAT_40001a00)))) {
      DAT_400019ef = 0;
      obd_ii_monitor_pass(&DAT_4000e293,&DAT_40002d55);
      if (DAT_400019ee < DAT_4000e365) {
        DAT_400019ee = DAT_400019ee + 1;
      }
    }
    else {
      DAT_400019ef = DAT_400019ef + 1;
      if ((DAT_40001676 <= (short)(ushort)DAT_400019ef) &&
         ((DAT_400019ef = 0, DAT_400019ee != 0 &&
          (DAT_400019ee = DAT_400019ee - 1, DAT_400019ee == 0)))) {
        obd_ii_dtc_confirm_and_freeze
                  (&DAT_4000e293,&DAT_40002d55,&DAT_40002d56,&DAT_40002d57,&DAT_00001790,0);
      }
    }
  }
  if (((s_AAAAAAAA_4000e294[8] & 7U) != 0) && ((DAT_400015b8 & 1) != 0)) {
    if (((DAT_40008f57 < DAT_40001bed) || (DAT_400019fa <= DAT_4000e3ee)) &&
       ((DAT_400019fa <= DAT_4000e3f0 && (DAT_4000e3f2 <= DAT_400019fa)))) {
      DAT_400019f1 = 0;
      obd_ii_monitor_pass(s_AAAAAAAA_4000e294 + 8,&DAT_40002d70);
      if (DAT_400019f0 < DAT_4000e36e) {
        DAT_400019f0 = DAT_400019f0 + 1;
      }
    }
    else {
      DAT_400019f1 = DAT_400019f1 + 1;
      if ((DAT_40001676 <= (short)(ushort)DAT_400019f1) &&
         ((DAT_400019f1 = 0, DAT_400019f0 != 0 &&
          (DAT_400019f0 = DAT_400019f0 - 1, DAT_400019f0 == 0)))) {
        obd_ii_dtc_confirm_and_freeze
                  (s_AAAAAAAA_4000e294 + 8,&DAT_40002d70,&DAT_40002d71,&DAT_40002d72,&DAT_00001812,0
                  );
      }
    }
  }
  if (((DAT_4000e29d & 7) != 0) && ((DAT_400015b8 & 1) != 0)) {
    if (((DAT_40008f55 < DAT_40001bee) || (DAT_400019f8 <= DAT_4000e3ee)) &&
       ((DAT_400019f8 <= DAT_4000e3f0 && (DAT_4000e3f2 <= DAT_400019f8)))) {
      DAT_400019f3 = 0;
      obd_ii_monitor_pass(&DAT_4000e29d,&DAT_40002d73);
      if (DAT_400019f2 < DAT_4000e36f) {
        DAT_400019f2 = DAT_400019f2 + 1;
      }
    }
    else {
      DAT_400019f3 = DAT_400019f3 + 1;
      if ((DAT_40001676 <= (short)(ushort)DAT_400019f3) &&
         ((DAT_400019f3 = 0, DAT_400019f2 != 0 &&
          (DAT_400019f2 = DAT_400019f2 - 1, DAT_400019f2 == 0)))) {
        obd_ii_dtc_confirm_and_freeze
                  (&DAT_4000e29d,&DAT_40002d73,&DAT_40002d74,&DAT_40002d75,&DAT_0000181c,0);
      }
    }
  }
  if (((DAT_4000e29e & 7) != 0) && ((DAT_400015b8 & 1) != 0)) {
    if (((DAT_40008f5b < DAT_40001beb) || (DAT_400019fe <= DAT_4000e3ee)) &&
       ((DAT_400019fe <= DAT_4000e3f0 && (DAT_4000e3f2 <= DAT_400019fe)))) {
      DAT_400019f5 = 0;
      obd_ii_monitor_pass(&DAT_4000e29e,&DAT_40002d76);
      if (DAT_400019f4 < DAT_4000e370) {
        DAT_400019f4 = DAT_400019f4 + 1;
      }
    }
    else {
      DAT_400019f5 = DAT_400019f5 + 1;
      if ((DAT_40001676 <= (short)(ushort)DAT_400019f5) &&
         ((DAT_400019f5 = 0, DAT_400019f4 != 0 &&
          (DAT_400019f4 = DAT_400019f4 - 1, DAT_400019f4 == 0)))) {
        obd_ii_dtc_confirm_and_freeze
                  (&DAT_4000e29e,&DAT_40002d76,&DAT_40002d77,&DAT_40002d78,&DAT_0000181d,0);
      }
    }
  }
  if (((DAT_4000e29f & 7) != 0) && ((DAT_400015b8 & 1) != 0)) {
    if (((DAT_40008f59 < DAT_40001bec) || (DAT_400019fc <= DAT_4000e3ee)) &&
       ((DAT_400019fc <= DAT_4000e3f0 && (DAT_4000e3f2 <= DAT_400019fc)))) {
      DAT_400019f7 = 0;
      obd_ii_monitor_pass(&DAT_4000e29f,&DAT_40002d79);
      if (DAT_400019f6 < DAT_4000e371) {
        DAT_400019f6 = DAT_400019f6 + 1;
      }
    }
    else {
      DAT_400019f7 = DAT_400019f7 + 1;
      if ((DAT_40001676 <= (short)(ushort)DAT_400019f7) &&
         ((DAT_400019f7 = 0, DAT_400019f6 != 0 &&
          (DAT_400019f6 = DAT_400019f6 - 1, DAT_400019f6 == 0)))) {
        obd_ii_dtc_confirm_and_freeze
                  (&DAT_4000e29f,&DAT_40002d79,&DAT_40002d7a,&DAT_40002d7b,&DAT_00001853,0);
      }
    }
  }
  if (((DAT_4000e28a & 7) == 0) || (DAT_40001639 == '\0')) {
    obd_ii_monitor_pass(&DAT_4000e28a,&DAT_40002d49);
  }
  else {
    obd_ii_dtc_confirm_and_freeze(&DAT_4000e28a,&DAT_40002d49,&DAT_40002d4a,&DAT_40002d4b,0x897,0);
  }
  if (((DAT_4000e28d & 7) != 0) && (DAT_400019e9 != '\0')) {
    if ((DAT_40003471 & 1) == 0) {
      obd_ii_monitor_pass(&DAT_4000e28d,&DAT_40002cd4);
    }
    else {
      DAT_400019e9 = '\0';
      obd_ii_dtc_confirm_and_freeze(&DAT_4000e28d,&DAT_40002cd4,&DAT_40002cd5,&DAT_40002cd6,0x60a,0)
      ;
    }
  }
  if (((s_AAAAAAAAAAAAAA_4000e2a0[8] & 7U) != 0) && (DAT_40001a07 != '\0')) {
    if (DAT_400016ac == '\x01') {
      DAT_40001a07 = '\0';
      obd_ii_dtc_confirm_and_freeze
                (s_AAAAAAAAAAAAAA_4000e2a0 + 8,&DAT_40002da0,&DAT_40002da1,&DAT_40002da2,
                 &DAT_00001701,0);
    }
    else {
      obd_ii_monitor_pass(s_AAAAAAAAAAAAAA_4000e2a0 + 8,&DAT_40002da0);
    }
  }
  if (((s_AAAAAAAAAAAAAA_4000e2a0[9] & 7U) != 0) && (DAT_40001a06 != '\0')) {
    if (DAT_4000346f == '\x03') {
      DAT_40001a06 = '\0';
      obd_ii_dtc_confirm_and_freeze
                (s_AAAAAAAAAAAAAA_4000e2a0 + 9,&DAT_40002da3,&DAT_40002da4,&DAT_40002da5,
                 &DAT_00001780,0);
    }
    else {
      obd_ii_monitor_pass(s_AAAAAAAAAAAAAA_4000e2a0 + 9,&DAT_40002da3);
    }
  }
  if (((s_AAAAAAAAAAAAAA_4000e2a0[10] & 7U) != 0) && (DAT_40001a05 != '\0')) {
    if (((DAT_40003471 & 2) == 0) && ((DAT_40003471 & 4) == 0)) {
      obd_ii_monitor_pass(s_AAAAAAAAAAAAAA_4000e2a0 + 10,&DAT_40002da6);
    }
    else {
      DAT_40001a05 = '\0';
      obd_ii_dtc_confirm_and_freeze
                (s_AAAAAAAAAAAAAA_4000e2a0 + 10,&DAT_40002da6,&DAT_40002da7,&DAT_40002da8,
                 &DAT_0000185a,0);
    }
  }
  if (((s_AAAAAAAAAAAAAA_4000e2a0[0xb] & 7U) != 0) && (DAT_40001a04 != '\0')) {
    if (DAT_4000346f == '\n') {
      DAT_40001a04 = '\0';
      obd_ii_dtc_confirm_and_freeze
                (s_AAAAAAAAAAAAAA_4000e2a0 + 0xb,&DAT_40002da9,&DAT_40002daa,&DAT_40002dab,
                 &DAT_00001860,0);
    }
    else {
      obd_ii_monitor_pass(s_AAAAAAAAAAAAAA_4000e2a0 + 0xb,&DAT_40002da9);
    }
  }
  if (((s_AAAAAAAAAAAAAA_4000e2a0[0xc] & 7U) != 0) && (DAT_40001a03 != '\0')) {
    if (DAT_4000346f == '\x01') {
      DAT_40001a03 = '\0';
      obd_ii_dtc_confirm_and_freeze
                (s_AAAAAAAAAAAAAA_4000e2a0 + 0xc,&DAT_40002dac,&DAT_40002dad,&DAT_40002dae,
                 &DAT_00001921,0);
    }
    else {
      obd_ii_monitor_pass(s_AAAAAAAAAAAAAA_4000e2a0 + 0xc,&DAT_40002dac);
    }
  }
  if (((s_AAAAAAAAAAAAAA_4000e2a0[0xd] & 7U) != 0) && (DAT_40001a02 != '\0')) {
    if (DAT_4000346f == '\x02') {
      DAT_40001a02 = '\0';
      obd_ii_dtc_confirm_and_freeze
                (s_AAAAAAAAAAAAAA_4000e2a0 + 0xd,&DAT_40002daf,&DAT_40002db0,&DAT_40002db1,
                 &DAT_00001925,0);
    }
    else {
      obd_ii_monitor_pass(s_AAAAAAAAAAAAAA_4000e2a0 + 0xd,&DAT_40002daf);
    }
  }
  if ((((DAT_40002cd7 & 8) == 0) || ((DAT_40002cd7 & 4) == 0)) || ((DAT_40002cd7 & 1) == 0)) {
    DAT_40001678 = DAT_40001678 & 0xf7ffffff;
  }
  else if ((uint)DAT_4000e423 <= vehicle_speed____ / 100) {
    DAT_40001678 = DAT_40001678 | 0x8000000;
  }
  return;
}



void FUN_00071ebc(void)

{
  DAT_400019ea = DAT_4000e332;
  DAT_400019ec = DAT_4000e35d;
  DAT_400019ee = DAT_4000e365;
  DAT_400019f0 = DAT_4000e36e;
  DAT_400019f2 = DAT_4000e36f;
  DAT_400019f4 = DAT_4000e370;
  DAT_400019f6 = DAT_4000e371;
  DAT_400019e9 = DAT_4000e35f;
  DAT_40001a07 = DAT_4000e37a;
  DAT_40001a06 = DAT_4000e37b;
  DAT_40001a05 = DAT_4000e37c;
  DAT_40001a04 = DAT_4000e37d;
  DAT_40001a03 = DAT_4000e37e;
  DAT_40001a02 = DAT_4000e37f;
  DAT_400019eb = 0;
  DAT_400019ed = 0;
  DAT_400019ef = 0;
  DAT_400019f1 = 0;
  DAT_400019f3 = 0;
  DAT_400019f5 = 0;
  DAT_400019f7 = 0;
  obd_set_new_DTC(&DAT_4000e266,&DAT_40002cd1,0x601,0);
  obd_set_new_DTC(&DAT_4000e27b,&DAT_40002cd7,0x610,0);
  obd_set_new_DTC(&DAT_4000e267,&DAT_40002cda,0x613,0);
  obd_set_new_DTC(&DAT_4000e260,&DAT_40002d25,0x813,0);
  obd_set_new_DTC(&DAT_4000e28a,&DAT_40002d49,0x897,0);
  obd_set_new_DTC(&DAT_4000e28b,&DAT_40002d43,0x886,0);
  obd_set_new_DTC(&DAT_4000e290,&DAT_40002d4c,&DAT_00001613,0);
  obd_set_new_DTC(&DAT_4000e292,&DAT_40002d52,&DAT_0000172a,0);
  obd_set_new_DTC(&DAT_4000e293,&DAT_40002d55,&DAT_00001790,0);
  obd_set_new_DTC(s_AAAAAAAA_4000e294 + 8,&DAT_40002d70,&DAT_00001812,0);
  obd_set_new_DTC(&DAT_4000e29d,&DAT_40002d73,&DAT_0000181c,0);
  obd_set_new_DTC(&DAT_4000e29e,&DAT_40002d76,&DAT_0000181d,0);
  obd_set_new_DTC(&DAT_4000e29f,&DAT_40002d79,&DAT_00001853,0);
  obd_set_new_DTC(&DAT_4000e28d,&DAT_40002cd4,0x60a,0);
  obd_set_new_DTC(s_AAAAAAAAAAAAAA_4000e2a0 + 8,&DAT_40002da0,&DAT_00001701,0);
  obd_set_new_DTC(s_AAAAAAAAAAAAAA_4000e2a0 + 9,&DAT_40002da3,&DAT_00001780,0);
  obd_set_new_DTC(s_AAAAAAAAAAAAAA_4000e2a0 + 10,&DAT_40002da6,&DAT_0000185a,0);
  obd_set_new_DTC(s_AAAAAAAAAAAAAA_4000e2a0 + 0xb,&DAT_40002da9,&DAT_00001860,0);
  obd_set_new_DTC(s_AAAAAAAAAAAAAA_4000e2a0 + 0xc,&DAT_40002dac,&DAT_00001921,0);
  obd_set_new_DTC(s_AAAAAAAAAAAAAA_4000e2a0 + 0xd,&DAT_40002daf,&DAT_00001925,0);
  DAT_400019f8 = (short)((int)(uint)DAT_40001d8e >> 4);
  DAT_400019fa = (short)((int)(uint)DAT_40001d90 >> 4);
  DAT_400019fc = (short)((int)(uint)DAT_40001d92 >> 4);
  DAT_400019fe = (short)((int)(uint)DAT_40001d94 >> 4);
  DAT_40001a00 = (short)((int)(uint)DAT_40001dcc >> 4);
  return;
}



void FUN_000723d8(void)

{
  obd_ii_dtc_aging_heal(&DAT_4000e266,&DAT_40002cd1,&DAT_40002cd2,&DAT_40002cd3,0x601,0);
  obd_ii_dtc_aging_heal(&DAT_4000e27b,&DAT_40002cd7,&DAT_40002cd8,&DAT_40002cd9,0x610,0);
  obd_ii_dtc_aging_heal(&DAT_4000e267,&DAT_40002cda,&DAT_40002cdb,&DAT_40002cdc,0x613,0);
  obd_ii_dtc_aging_heal(&DAT_4000e260,&DAT_40002d25,&DAT_40002d26,&DAT_40002d27,0x813,0);
  obd_ii_dtc_aging_heal(&DAT_4000e28b,&DAT_40002d43,&DAT_40002d44,&DAT_40002d45,0x886,0);
  obd_ii_dtc_aging_heal(&DAT_4000e28a,&DAT_40002d49,&DAT_40002d4a,&DAT_40002d4b,0x897,0);
  obd_ii_dtc_aging_heal(&DAT_4000e290,&DAT_40002d4c,&DAT_40002d4d,&DAT_40002d4e,&DAT_00001613,0);
  obd_ii_dtc_aging_heal(&DAT_4000e292,&DAT_40002d52,&DAT_40002d53,&DAT_40002d54,&DAT_0000172a,0);
  obd_ii_dtc_aging_heal(&DAT_4000e293,&DAT_40002d55,&DAT_40002d56,&DAT_40002d57,&DAT_00001790,0);
  obd_ii_dtc_aging_heal
            (s_AAAAAAAA_4000e294 + 8,&DAT_40002d70,&DAT_40002d71,&DAT_40002d72,&DAT_00001812,0);
  obd_ii_dtc_aging_heal(&DAT_4000e29d,&DAT_40002d73,&DAT_40002d74,&DAT_40002d75,&DAT_0000181c,0);
  obd_ii_dtc_aging_heal(&DAT_4000e29e,&DAT_40002d76,&DAT_40002d77,&DAT_40002d78,&DAT_0000181d,0);
  obd_ii_dtc_aging_heal(&DAT_4000e29f,&DAT_40002d79,&DAT_40002d7a,&DAT_40002d7b,&DAT_00001853,0);
  obd_ii_dtc_aging_heal(&DAT_4000e28d,&DAT_40002cd4,&DAT_40002cd5,&DAT_40002cd6,0x60a,0);
  obd_ii_dtc_aging_heal
            (s_AAAAAAAAAAAAAA_4000e2a0 + 8,&DAT_40002da0,&DAT_40002da1,&DAT_40002da2,&DAT_00001701,0
            );
  obd_ii_dtc_aging_heal
            (s_AAAAAAAAAAAAAA_4000e2a0 + 9,&DAT_40002da3,&DAT_40002da4,&DAT_40002da5,&DAT_00001780,0
            );
  obd_ii_dtc_aging_heal
            (s_AAAAAAAAAAAAAA_4000e2a0 + 10,&DAT_40002da6,&DAT_40002da7,&DAT_40002da8,&DAT_0000185a,
             0);
  obd_ii_dtc_aging_heal
            (s_AAAAAAAAAAAAAA_4000e2a0 + 0xb,&DAT_40002da9,&DAT_40002daa,&DAT_40002dab,&DAT_00001860
             ,0);
  obd_ii_dtc_aging_heal
            (s_AAAAAAAAAAAAAA_4000e2a0 + 0xc,&DAT_40002dac,&DAT_40002dad,&DAT_40002dae,&DAT_00001921
             ,0);
  obd_ii_dtc_aging_heal
            (s_AAAAAAAAAAAAAA_4000e2a0 + 0xd,&DAT_40002daf,&DAT_40002db0,&DAT_40002db1,&DAT_00001925
             ,0);
  return;
}



void FUN_00072944(void)

{
  uint uVar1;
  u8_factor_1_255 uVar2;
  ulonglong uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  ulonglong uVar7;
  
  uVar2 = tps_commanded;
  uVar7 = (ulonglong)tps_commanded;
  uVar3 = (ulonglong)DAT_40001a1c;
  iVar6 = int_abs(uVar7 - DAT_40001a1c);
  uVar1 = (iVar6 * 1000) / 0xff;
  uVar4 = DAT_40001a18 * (0x100 - (uint)DAT_40009068);
  uVar5 = 0xff;
  if ((int)uVar1 < 0xff) {
    uVar5 = uVar1 & 0xff;
  }
  DAT_40001a18 = ((int)uVar4 >> 8) + (uint)((int)uVar4 < 0 && (uVar4 & 0xff) != 0) +
                 uVar5 * DAT_40009068;
  DAT_40001a09 = (char)(DAT_40001a18 >> 8) + ((int)DAT_40001a18 < 0 && (DAT_40001a18 & 0xff) != 0);
  DAT_40001a1c = uVar2;
  DAT_40001a08 = (byte)(uVar7 - uVar3 >> 0x18) >> 7;
  return;
}



void estimate_driving_style(void)

{
  byte bVar1;
  uint uVar2;
  u16_torque_nm _torque_input;
  ulonglong _tach_30rpm;
  byte _paddle_request;
  u8_speed_kph _speed;
  u8_factor_1_255 _tps;
  
  _paddle_request = paddle_request;
  _torque_input = torque_delivered_post_tc;
  _speed = vehicle_speed;
  _tps = tps_commanded;
  uVar2 = 0;
                    // some kind of overspeed error?
                    // 30601 is 7650 rpm
  if (tach_rpm < 30601) {
    _tach_30rpm = (ulonglong)tach_rpm / 120 & 0xff;
  }
  else {
    _tach_30rpm = 0xff;
  }
  rpm_intensity_weight =
       lookup_2D_uint8_interpolated
                 (4,_tach_30rpm,CAL_driving_intensity_rpm_gain,CAL_driving_intensity_rpm_gain_X_rpm)
  ;
  if (_speed < PTR_DAT_4000906d._0_1_) {
    intensity_event_flags = intensity_event_flags & 0b11111110;
  }
  else if ((((paddle_request_prev & 2) == 0) && ((_paddle_request & 2) != 0)) ||
          (((paddle_request_prev & 1) == 0 && ((_paddle_request & 1) != 0)))) {
    intensity_event_flags = intensity_event_flags | 1;
    uVar2 = (uint)DAT_40009077;
  }
  else {
    intensity_event_flags = intensity_event_flags & 0b11111110;
  }
  bVar1 = intensity_event_flags | 0b10000000;
  intensity_event_flags = intensity_event_flags & 0b01111111;
  if (u8_speed_kph_40008f40 < _speed) {
    intensity_event_flags = bVar1;
  }
  if ((vehicle_speed_kph_prev < 15) && (0b00001110 < _speed)) {
    DAT_40001a21 = -0x6a;
    u16_torque_nm_40001a1e = 0;
  }
  else {
    intensity_event_flags = intensity_event_flags & 0b11111101;
    if (DAT_40001a21 != '\0') {
      if ((short)_torque_input < (short)u16_torque_nm_40001a1e) {
        _torque_input = u16_torque_nm_40001a1e;
      }
      u16_torque_nm_40001a1e = _torque_input;
      if ((short)_torque_input < (short)u16_torque_nm_40009072) {
        DAT_40001a21 = DAT_40001a21 + -1;
      }
      else {
        intensity_event_flags = intensity_event_flags | 2;
        uVar2 = uVar2 + DAT_40009078;
        DAT_40001a21 = '\0';
      }
    }
  }
  if ((_speed < 5) ||
     (((DAT_40001a09 < DAT_40009076 || (DAT_40001a08 != '\0')) &&
      ((DAT_40001a09 < DAT_4000907f || (DAT_40001a08 != '\x01')))))) {
    intensity_event_flags = intensity_event_flags & 0xf7;
  }
  else {
    intensity_event_flags = intensity_event_flags | 8;
    uVar2 = uVar2 + DAT_4000907a;
  }
  if (_load_signed < DAT_4000906a) {
    intensity_event_flags = intensity_event_flags & 0xef;
  }
  else {
    intensity_event_flags = intensity_event_flags | 0x10;
    uVar2 = uVar2 + DAT_4000907b;
  }
  if ((_tps < DAT_40009083) || (_speed < 0xf)) {
    DAT_40001a23 = '\0';
    intensity_event_flags = intensity_event_flags & 0xdf;
  }
  else {
    intensity_event_flags = intensity_event_flags & 0xdf;
    if (DAT_40001a23 == '\0') {
      DAT_40001a23 = DAT_40009084;
      intensity_event_flags = intensity_event_flags | 0x20;
      uVar2 = uVar2 + DAT_40009085;
    }
    else {
      DAT_40001a23 = DAT_40001a23 + -1;
    }
  }
  vehicle_speed_kph_prev = _speed;
  paddle_request_prev = _paddle_request;
  if (intensity_event_flags == 0) {
    if (DAT_40001a22 == '\0') {
      DAT_40001a22 = DAT_4000906c;
      if ((driving_intensity_raw != 0) && (0xe < _speed)) {
        driving_intensity_raw = driving_intensity_raw - 1;
      }
    }
    else {
      DAT_40001a22 = DAT_40001a22 + -1;
    }
  }
  else {
    if (0xff < uVar2) {
      uVar2 = 0xff;
    }
    if ((uint)driving_intensity_raw + ((int)(uVar2 * rpm_intensity_weight) >> 8) < 0xff) {
      driving_intensity_raw = driving_intensity_raw + (char)(uVar2 * rpm_intensity_weight >> 8);
    }
    else {
      driving_intensity_raw = 0xff;
    }
    DAT_40001a22 = DAT_4000906c;
  }
  uVar2 = driving_intensity_filtered * (0x100 - (uint)CAL_driving_intensity_raw_multiplier);
                    // IIR(raw, filtered, cal baseline)
  driving_intensity_filtered =
       ((int)uVar2 >> 8) + (uint)((int)uVar2 < 0 && (uVar2 & 0xff) != 0) +
       (uint)driving_intensity_raw * (uint)CAL_driving_intensity_raw_multiplier;
  driving_style_index =
       (char)(driving_intensity_filtered >> 8) +
       ((int)driving_intensity_filtered < 0 && (driving_intensity_filtered & 0xff) != 0);
  shift_aggressiveness_blend =
       lookup_2D_uint8_interpolated
                 (4,driving_style_index,CAL_driving_shift_aggressiveness_blend,
                  CAL_driving_shift_aggressiveness_blend_X_driving_intensity);
  return;
}



void cruise_shift_control(void)

{
  if (vehicle_speed____ / 100 < (uint)cruise_target_kph) {
    DAT_40001a27 = cruise_target_kph - (char)(vehicle_speed____ / 100);
  }
  else {
    DAT_40001a27 = 0;
  }
  if (((((driver_input_flags[1] & 4) == 0) || ((driver_input_flags[1] & 8) != 0)) ||
      (((cruise_status_flags & 8) != 0 && ((DAT_40001a12 < DAT_40009091 && (DAT_40001a29 == '\0'))))
      )) || (((DAT_40009092 < DAT_40001a27 &&
              ((_load_signed < DAT_4000908a && (CAL_cruise_speed_target_unknown[0] < DAT_40001a12)))
              ) || ((((cruise_status_flags & 4) != 0 || (tach_rpm <= CAL_rpm_threshold_unknown2)) ||
                    (((downshift_debounce_counter == '\n' && (downshift_armed)) &&
                     (paddle_shift_pending != true)))))))) {
    DAT_40001ac6 = DAT_40001ac6 & 0xef;
  }
  else {
    DAT_40001ac6 = DAT_40001ac6 | 0x10;
  }
  if ((((driver_input_flags[1] & 4) != 0) &&
      ((downshift_debounce_counter != '\n' || (!BOOL_40001a28)))) &&
     ((paddle_shift_pending != true && ((cruise_status_flags & 4) == 0)))) {
    if (((_load_signed < DAT_4000908a) && (CAL_cruise_speed_target_unknown[0] < DAT_40001a12)) &&
       (gear_request < enum_t6e_gear_40001a0a)) {
      DAT_40001a11 = DAT_4000908c;
    }
    else if (gear_request != enum_t6e_gear_40001a0a) {
      DAT_40001a11 = DAT_400090b2;
    }
  }
  if (((((cruise_status_flags & 8) != 0) && (gear_request < enum_t6e_gear_40001a0a)) &&
      (DAT_40001a27 < DAT_40009093)) && (DAT_40001a29 != -1)) {
    DAT_40001a29 = DAT_40001a29 + '\x01';
  }
  if ((cruise_status_flags & 8) == 0) {
    DAT_40001a29 = '\0';
  }
  if ((((CAL_cruise_speed_target_unknown[0] < DAT_40001a12) &&
       (cruise_target_kph < CAL_cruise_speed_target_unknown[1])) &&
      (_load_signed < (short)(ushort)DAT_4000908f)) || ((cruise_status_flags & 4) != 0)) {
    DAT_40001461 = 3;
  }
  else {
    DAT_40001461 = 4;
  }
  enum_t6e_gear_40001a0a = gear_request;
  BOOL_40001a28 = downshift_armed;
  overrev_shift_threshold = (revlimit_hard_from_ecu + (ushort)CAL_overrev_shift_margin * -10) * 4;
  if (overrev_shift_threshold < tach_rpm) {
    DAT_40001a11 = 0;
  }
  if ((DAT_40001a11 == 0) &&
     (((DAT_400090b2 <= DAT_40001a12 || ((driver_input_flags[1] & 4) == 0)) ||
      (overrev_shift_threshold <= tach_rpm)))) {
    DAT_40001ac5 = DAT_40001ac5 & 0xef;
  }
  else {
    DAT_40001ac5 = DAT_40001ac5 | 0x10;
  }
  return;
}



void compute_clutch_pressure_targets(void)

{
  enum_t6e_gear eVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  eVar1 = ips_gear_cur;
  if (_load_signed < 0) {
    if (-(int)_load_signed < 0x100) {
      decel_magnitude = (undefined1)-(int)_load_signed;
    }
    else {
      decel_magnitude = 0xff;
    }
  }
  else {
    decel_magnitude = 0;
  }
  if (((byte)(ips_gear_cur - GEAR_3) < 6) && (DAT_40001c38 == -2)) {
    if ((auto_mode_active) &&
       (((driver_input_flags[1] & 4) == 0 || ((cruise_status_flags & 4) != 0)))) {
      DAT_40001a2a = lookup_3D_uint8_interpolated
                               (8,7,ips_gear_cur - GEAR_1,DAT_40001637,&DAT_4000d375,&DAT_4000d366,
                                &DAT_4000d36e);
    }
    else {
      uVar3 = lookup_3D_uint8_interpolated
                        (8,7,ips_gear_cur - GEAR_1,DAT_40001637,&DAT_4000d3bd,&DAT_4000d3ae,
                         &DAT_4000d3b6);
      uVar4 = lookup_3D_uint8_interpolated
                        (8,7,eVar1 - GEAR_1,DAT_40001637,&DAT_4000d735,&DAT_4000d726,&DAT_4000d72e);
      iVar2 = (0xff - (uint)shift_aggressiveness_blend) * (uVar4 & 0xff);
      DAT_40001a2a = (char)(((uint)shift_aggressiveness_blend * (uVar3 & 0xff)) / 0xff) +
                     (((char)(iVar2 / 0xff) + (char)(iVar2 >> 0x1f)) -
                     (char)((longlong)iVar2 * 0x80808081 >> 0x3f));
    }
    if ((auto_mode_active == false) ||
       (((driver_input_flags[1] & 4) != 0 && ((cruise_status_flags & 4) == 0)))) {
      DAT_40001a2b = lookup_2D_uint8_interpolated
                               (8,DAT_40001a2a,shift_sched_work_a_manual_X_throttle,
                                shift_sched_work_a_manual);
    }
    else {
      DAT_40001a2b = lookup_2D_uint8_interpolated
                               (8,DAT_40001a2a,shift_sched_work_a_auto_X_throttle,
                                shift_sched_work_a_auto);
    }
  }
  else {
    DAT_40001a2a = '\0';
  }
  return;
}



void record_shift_diag_sample(void)

{
  if (0x13 < (int)((uint)DAT_40001510 - (uint)DAT_40001a3a)) {
    if (99 < DAT_40003438) {
      DAT_40003438 = 0;
    }
    (&DAT_40002f24)[DAT_40003438] = (ushort)vehicle_speed;
    (&DAT_40002fec)[DAT_40003438] = DAT_40001712;
    (&DAT_4000317c)[DAT_40003438] = oil_temp_unknown;
    (&DAT_400031e0)[DAT_40003438] = ips_gear_cur;
    (&DAT_400030b4)[DAT_40003438] = DAT_40001c4e;
    (&DAT_40003244)[DAT_40003438] = input_shaft_load;
    (&DAT_400032a8)[DAT_40003438] = _load_signed;
    (&DAT_40003370)[DAT_40003438] = DAT_40001c52;
    DAT_40003438 = DAT_40003438 + 1;
    DAT_40001a3a = DAT_40001510;
  }
  return;
}



void accumulate_trans_usage_stats(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  bool bVar7;
  int iVar8;
  uint uVar9;
  byte bVar10;
  byte local_2c [5];
  undefined1 local_27;
  undefined1 local_26;
  ushort local_18 [4];
  undefined2 local_10;
  undefined2 local_e;
  undefined2 local_c;
  undefined2 local_a;
  undefined2 local_8;
  
  local_18[0] = DAT_0008d9b8;
  local_18[1] = DAT_0008d9ba;
  local_18[2] = DAT_0008d9bc;
  local_18[3] = DAT_0008d9be;
  local_10 = DAT_0008d9c0;
  local_e = DAT_0008d9c2;
  local_c = DAT_0008d9c4;
  local_a = DAT_0008d9c6;
  local_8 = DAT_0008d9c8;
  local_2c[0] = DAT_00001cf8;
  local_2c[1] = DAT_00001cf9;
  local_2c[2] = DAT_00001cfa;
  local_2c[3] = DAT_00001cfb;
  local_2c[4] = DAT_00001cfc;
  local_27 = DAT_00001cfd;
  local_26 = DAT_00001cfe;
  if (tach_rpm != 0) {
    if ((auto_mode_active) && (DAT_40001c38 == '\x01')) {
      DAT_40002ddc = DAT_40002ddc + 1;
    }
    else if (auto_mode_active) {
      DAT_40002de0 = DAT_40002de0 + 1;
    }
    else if (DAT_40001c38 == '\x01') {
      DAT_40002de4 = DAT_40002de4 + 1;
    }
    else {
      DAT_40002de8 = DAT_40002de8 + 1;
    }
    for (bVar10 = 0; bVar10 < 8; bVar10 = bVar10 + 1) {
      if ((local_18[bVar10] < input_shaft_rpm) && (input_shaft_rpm <= local_18[bVar10 + 1])) {
        (&DAT_40002dec)[bVar10] = (&DAT_40002dec)[bVar10] + 1;
      }
    }
    for (bVar10 = 0; bVar10 < 6; bVar10 = bVar10 + 1) {
      if ((local_2c[bVar10] < oil_temp_unknown) && (oil_temp_unknown <= local_2c[bVar10 + 1])) {
        (&DAT_40002e0c)[bVar10] = (&DAT_40002e0c)[bVar10] + 1;
      }
    }
  }
  bVar7 = false;
  for (bVar10 = 0; bVar10 < 8; bVar10 = bVar10 + 1) {
    if ((&DAT_40002dec)[bVar10] == -2) {
      bVar7 = true;
    }
  }
  if (bVar7) {
    for (bVar10 = 0; bVar10 < 8; bVar10 = bVar10 + 1) {
      (&DAT_40002dec)[bVar10] = 0;
    }
  }
  bVar7 = false;
  for (bVar10 = 0; bVar10 < 6; bVar10 = bVar10 + 1) {
    if ((&DAT_40002e0c)[bVar10] == -2) {
      bVar7 = true;
    }
  }
  if (bVar7) {
    for (bVar10 = 0; bVar10 < 6; bVar10 = bVar10 + 1) {
      (&DAT_40002e0c)[bVar10] = 0;
    }
  }
  if (tach_rpm != 0) {
    if (DAT_40002e24 < 0xffffffff) {
      DAT_40002e24 = DAT_40002e24 + 1;
    }
    else {
      DAT_40002e24 = 0;
    }
  }
  if ((DAT_40001468 != '\0') &&
     (DAT_40001468 = DAT_40001468 + -1, u16_rspeed_rpm_40001a30 < input_shaft_rpm)) {
    u16_rspeed_rpm_40001a30 = input_shaft_rpm;
    DAT_40001a36 = gear_request;
    DAT_40001a38 = engine_torque;
  }
  if (DAT_40001468 == '\0') {
    DAT_40001468 = '2';
    if (u16_rspeed_rpm_ARRAY_40002e84[0] < u16_rspeed_rpm_40001a30) {
      u16_rspeed_rpm_ARRAY_40002e84[0] = u16_rspeed_rpm_40001a30;
      u16_rspeed_rpm_ARRAY_40002e84[1] = DAT_40001a38;
      u16_rspeed_rpm_ARRAY_40002e84[4]._0_1_ = DAT_40001a36;
      u16_rspeed_rpm_ARRAY_40002e84[2] = DAT_40002e24._0_2_;
      u16_rspeed_rpm_ARRAY_40002e84[3] = DAT_40002e24._2_2_;
      for (bVar10 = 0; bVar10 < 9; bVar10 = bVar10 + 1) {
        if (u16_rspeed_rpm_ARRAY_40002e84[(bVar10 + 1) * 6] <
            u16_rspeed_rpm_ARRAY_40002e84[(uint)bVar10 * 6]) {
          iVar8 = bVar10 + 1;
          uVar3 = *(undefined4 *)(u16_rspeed_rpm_ARRAY_40002e84 + iVar8 * 6);
          uVar4 = *(undefined4 *)(u16_rspeed_rpm_ARRAY_40002e84 + iVar8 * 6 + 2);
          uVar5 = *(undefined4 *)(u16_rspeed_rpm_ARRAY_40002e84 + iVar8 * 6 + 4);
          uVar9 = (uint)bVar10;
          iVar8 = bVar10 + 1;
          uVar6 = *(undefined4 *)(u16_rspeed_rpm_ARRAY_40002e84 + uVar9 * 6 + 2);
          *(undefined4 *)(u16_rspeed_rpm_ARRAY_40002e84 + iVar8 * 6) =
               *(undefined4 *)(u16_rspeed_rpm_ARRAY_40002e84 + uVar9 * 6);
          *(undefined4 *)(u16_rspeed_rpm_ARRAY_40002e84 + iVar8 * 6 + 2) = uVar6;
          *(undefined4 *)(u16_rspeed_rpm_ARRAY_40002e84 + iVar8 * 6 + 4) =
               *(undefined4 *)(u16_rspeed_rpm_ARRAY_40002e84 + uVar9 * 6 + 4);
          uVar9 = (uint)bVar10;
          *(undefined4 *)(u16_rspeed_rpm_ARRAY_40002e84 + uVar9 * 6) = uVar3;
          *(undefined4 *)(u16_rspeed_rpm_ARRAY_40002e84 + uVar9 * 6 + 2) = uVar4;
          *(undefined4 *)(u16_rspeed_rpm_ARRAY_40002e84 + uVar9 * 6 + 4) = uVar5;
        }
      }
    }
    u16_rspeed_rpm_40001a30 = 0;
  }
  if ((DAT_40001a32 < oil_temp_unknown) && (0x32 < DAT_400013b8)) {
    DAT_40001a32 = oil_temp_unknown;
    DAT_40001a34 = vehicle_speed____;
  }
  if ((DAT_400013b8 < 0x32) && (DAT_40001a32 != 0)) {
    if (DAT_40002efc < DAT_40001a32) {
      DAT_40002efc = DAT_40001a32;
      DAT_40002efe = DAT_40001a34;
    }
    for (bVar10 = 0; bVar10 < 9; bVar10 = bVar10 + 1) {
      if ((&DAT_40002efc)[(bVar10 + 1) * 4] < (&DAT_40002efc)[(uint)bVar10 * 4]) {
        uVar1 = *(undefined2 *)(&DAT_40002efc + (bVar10 + 1) * 4);
        uVar2 = (&DAT_40002efe)[(bVar10 + 1) * 2];
        *(undefined2 *)(&DAT_40002efc + (bVar10 + 1) * 4) =
             *(undefined2 *)(&DAT_40002efc + (uint)bVar10 * 4);
        (&DAT_40002efe)[(bVar10 + 1) * 2] = (&DAT_40002efe)[(uint)bVar10 * 2];
        *(undefined2 *)(&DAT_40002efc + (uint)bVar10 * 4) = uVar1;
        (&DAT_40002efe)[(uint)bVar10 * 2] = uVar2;
      }
    }
    DAT_40001a34 = 0;
    DAT_40001a32 = 0;
  }
  return;
}



void write_solenoid_adapt_config(char param_1,byte param_2)

{
  if (param_1 == '\x01') {
    if (DAT_40002e28 < param_2) {
      DAT_40002e28 = param_2;
    }
  }
  else if (param_1 == '\x02') {
    if (DAT_40002e29 < param_2) {
      DAT_40002e29 = param_2;
    }
  }
  else if (param_1 == '\x03') {
    if (DAT_40002e2a < param_2) {
      DAT_40002e2a = param_2;
    }
  }
  else if ((param_1 == '\x04') && (DAT_40002e2b < param_2)) {
    DAT_40002e2b = param_2;
  }
  return;
}



void obd_ii_mode10_processing(void)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  uint uVar4;
  undefined2 local_10 [8];
  
  bVar3 = 0;
  for (bVar2 = 0; bVar2 < 8; bVar2 = bVar2 + 1) {
    if ((&DAT_40002c18)[(uint)bVar2 * 2] != 0) {
      local_10[bVar3] = (&DAT_40002c18)[(uint)bVar2 * 2];
      bVar3 = bVar3 + 1;
    }
  }
  obd_ii_response[0] = 0x4a;
  uVar4 = 2;
  obd_ii_response[1] = bVar3;
  for (bVar2 = 0; bVar2 < bVar3; bVar2 = bVar2 + 1) {
    uVar1 = uVar4 + 1;
    obd_ii_response[uVar4 & 0xff] = (byte)((ushort)local_10[bVar2] >> 8);
    uVar4 = uVar4 + 2;
    obd_ii_response[uVar1 & 0xff] = (byte)local_10[bVar2];
  }
  obd_ii_response_length = (ushort)uVar4 & 0xff;
  flexcan_a_obd_send_messages();
  return;
}



void obd_ii_set_perm_dtc(undefined2 param_1)

{
  byte bVar1;
  
  bVar1 = 0;
  while( true ) {
    if (7 < bVar1) {
      return;
    }
    if ((&DAT_40002c18)[(uint)bVar1 * 2] == 0) break;
    bVar1 = bVar1 + 1;
  }
  (&DAT_40002c18)[(uint)bVar1 * 2] = param_1;
  (&DAT_40002c1a)[(uint)bVar1 * 4] = 0;
  return;
}



void obd_ii_zero_perm_dtc(void)

{
  byte bVar1;
  
  for (bVar1 = 0; bVar1 < 8; bVar1 = bVar1 + 1) {
    (&DAT_40002c18)[(uint)bVar1 * 2] = 0;
    (&DAT_40002c1a)[(uint)bVar1 * 4] = 0;
  }
  return;
}



uint16_t get_gear_ratio(enum_t6e_gear gear)

{
  uint16_t uVar1;
  
  switch(gear) {
  case NEUTRAL:
    uVar1 = 0;
    break;
  case GEAR_1:
    uVar1 = CAL_gear_ratio_1;
    break;
  case GEAR_2:
    uVar1 = CAL_gear_ratio_2;
    break;
  case GEAR_3:
    uVar1 = CAL_gear_ratio_3;
    break;
  case GEAR_4:
    uVar1 = CAL_gear_ratio_4;
    break;
  case GEAR_5:
    uVar1 = CAL_gear_ratio_5;
    break;
  case GEAR_6:
    uVar1 = CAL_gear_ratio_6;
    break;
  default:
    uVar1 = 0;
    break;
  case GEAR_REV:
    uVar1 = CAL_gear_ratio_REV;
  }
  return uVar1;
}



void build_upshift_schedule(void)

{
  uint uVar1;
  uint16_t _ratio_cur;
  uint16_t uVar2;
  uint16_t uVar3;
  byte j;
  byte i;
  byte bStack_21;
  u8_rspeed_25rpm _shift_speed_1_2;
  u8_rspeed_25rpm local_1f [4];
  
  gear_cur_uss = ips_gear_cur;
  if (ips_gear_cur == (GEAR_INVALID8|GEAR_INVALID7)) {
    gear_cur_uss = gear_request;
  }
  _shift_speed_1_2 =
       lookup_2D_uint8_interpolated
                 (8,oil_temp_unknown,CAL_shift_speed_1_2_manual,
                  CAL_shift_speed_1_2_manual_X_oil_temp);
  local_1f[0] = CAL_shift_speed_2_3_manual;
  local_1f[1] = CAL_shift_speed_3_4_manual;
  local_1f[2] = CAL_shift_speed_4_5_manual;
  local_1f[3] = CAL_shift_speed_5_6_manual;
  for (j = 0; j < 8; j = j + 1) {
    if ((byte)(gear_cur_uss - GEAR_1) < 5) {
      uVar2 = get_gear_ratio(gear_cur_uss + GEAR_1);
      _ratio_cur = get_gear_ratio(gear_cur_uss);
      uVar1 = (((uint)(&bStack_21)[gear_cur_uss] +
               ((uint)shift_aggressiveness_blend * (uint)DAT_4000914d) / 0xff) * 0x19 *
              (uint)_ratio_cur) / (uint)uVar2 & 0xffff;
      shift_sched_work_b_manual_X_throttle[j] = CAL_upshift_throttle_axis_manual[j];
      uVar1 = uVar1 + (int)((uint)CAL_upshift_curve_blend_manual[j] *
                           (((uint)CAL_upshift_max_speed_manual * 0x19 + 1000) - uVar1)) / 0xff &
              0xffff;
      if (uVar1 < 0x3e9) {
        shift_sched_work_b_manual[j] = '\0';
      }
      else {
        shift_sched_work_b_manual[j] = (uint8_t)((int)(uVar1 - 1000) / 0x19);
      }
    }
  }
  _shift_speed_1_2 = CAL_shift_speed_1_2_auto;
  local_1f[0] = CAL_shift_speed_2_3_auto;
  local_1f[1] = CAL_shift_speed_3_4_auto;
  local_1f[2] = CAL_shift_speed_4_5_auto;
  local_1f[3] = CAL_shift_speed_5_6_auto;
  for (i = 0; i < 8; i = i + 1) {
    if ((byte)(gear_cur_uss - GEAR_1) < 5) {
      uVar2 = get_gear_ratio(gear_cur_uss + GEAR_1);
      uVar3 = get_gear_ratio(gear_cur_uss);
      uVar1 = ((uint)(&bStack_21)[gear_cur_uss] * 0x19 * (uint)uVar3) / (uint)uVar2 & 0xffff;
      shift_sched_work_b_auto_X_throttle[i] = CAL_upshift_throttle_axis_auto[i];
      uVar1 = uVar1 + (int)((uint)CAL_upshift_curve_blend_auto[i] *
                           (((uint)CAL_upshift_max_speed_auto * 0x19 + 1000) - uVar1)) / 0xff &
              0xffff;
      if (uVar1 < 0x3e9) {
        shift_sched_work_b_auto[i] = '\0';
      }
      else {
        shift_sched_work_b_auto[i] = (uint8_t)((int)(uVar1 - 1000) / 0x19);
      }
    }
  }
  return;
}



void build_downshift_schedule(void)

{
  byte bVar1;
  uint uVar2;
  uint16_t uVar3;
  uint16_t uVar4;
  byte i;
  byte j;
  byte abStack_23 [3];
  u8_rspeed_25rpm local_20 [4];
  
  gear_curr_dss = ips_gear_cur;
  if (ips_gear_cur == (GEAR_INVALID8|GEAR_INVALID7)) {
    gear_curr_dss = gear_request;
  }
  local_20[0] = CAL_shift_speed_2_3_manual;
  local_20[1] = CAL_shift_speed_3_4_manual;
  local_20[2] = CAL_shift_speed_4_5_manual;
  local_20[3] = CAL_shift_speed_5_6_manual;
  for (i = 0; i < 8; i = i + 1) {
    if ((byte)(gear_curr_dss - GEAR_3) < 4) {
      uVar2 = (((uint)abStack_23[gear_curr_dss] - (uint)CAL_downshift_speed_hysteresis) +
              ((uint)shift_aggressiveness_blend * (uint)DAT_4000914d) / 0xff) * 0x19 & 0xffff;
      bVar1 = CAL_downshift_curve_blend_manual[i];
      shift_sched_work_a_manual_X_throttle[i] = CAL_downshift_throttle_axis_manual[i];
      uVar3 = get_gear_ratio(gear_curr_dss - GEAR_1);
      uVar4 = get_gear_ratio(gear_curr_dss);
      uVar2 = uVar2 + (int)((uint)bVar1 *
                           ((int)((((uint)CAL_upshift_max_speed_manual - (uint)DAT_4000d307) * 0x19
                                  + 1000) * (uint)uVar4) / (int)(uint)uVar3 - uVar2)) / 0xff;
      if (uVar2 < 0x1f5) {
        shift_sched_work_a_manual[i] = '\0';
      }
      else {
        shift_sched_work_a_manual[i] = (uint8_t)((ulonglong)(uVar2 - 500) / 0x19);
      }
    }
  }
  local_20[0] = CAL_shift_speed_2_3_auto;
  local_20[1] = CAL_shift_speed_3_4_auto;
  local_20[2] = CAL_shift_speed_4_5_auto;
  local_20[3] = CAL_shift_speed_5_6_auto;
  for (j = 0; j < 8; j = j + 1) {
    if ((byte)(gear_curr_dss - GEAR_3) < 4) {
      uVar2 = ((uint)abStack_23[gear_curr_dss] - (uint)CAL_downshift_speed_hysteresis) * 0x19 &
              0xffff;
      bVar1 = CAL_downshift_curve_blend_auto[j];
      shift_sched_work_a_auto_X_throttle[j] = CAL_downshift_throttle_axis_auto[j];
      uVar3 = get_gear_ratio(gear_curr_dss - GEAR_1);
      uVar4 = get_gear_ratio(gear_curr_dss);
      uVar2 = uVar2 + (int)((uint)bVar1 *
                           ((int)((((uint)CAL_upshift_max_speed_auto - (uint)DAT_4000d307) * 0x19 +
                                  1000) * (uint)uVar4) / (int)(uint)uVar3 - uVar2)) / 0xff;
      if (uVar2 < 0x1f5) {
        shift_sched_work_a_auto[j] = '\0';
      }
      else {
        shift_sched_work_a_auto[j] = (uint8_t)((ulonglong)(uVar2 - 500) / 0x19);
      }
    }
  }
  return;
}



void detect_gear_from_ratio(void)

{
  undefined *puVar1;
  
  if (output_shaft_rpm == 0) {
    DAT_40001a40 = (undefined *)0x0;
  }
  else {
    DAT_40001a40 = (undefined *)(((uint)input_shaft_rpm * 1000) / (uint)output_shaft_rpm);
  }
  if (DAT_40001a40 == (undefined *)0x0) {
    DAT_40001a44 = 0;
  }
  else if ((DAT_40001a40 < (undefined *)(uint)DAT_40001c6e) ||
          ((undefined *)(uint)DAT_40001c6c < DAT_40001a40)) {
    if ((DAT_40001a40 < (undefined *)(uint)DAT_40001c6a) ||
       ((undefined *)(uint)DAT_40001c68 < DAT_40001a40)) {
      if ((DAT_40001a40 < (undefined *)(uint)DAT_40001c66) ||
         ((undefined *)(uint)DAT_40001c64 < DAT_40001a40)) {
        if ((DAT_40001a40 < (undefined *)(uint)DAT_40001c62) ||
           ((undefined *)(uint)DAT_40001c60 < DAT_40001a40)) {
          if ((DAT_40001a40 < (undefined *)(uint)DAT_40001c5e) ||
             ((undefined *)(uint)DAT_40001c5c < DAT_40001a40)) {
            if ((DAT_40001a40 < (undefined *)(uint)DAT_40001c5a) ||
               ((undefined *)(uint)DAT_40001c58 < DAT_40001a40)) {
              DAT_40001a44 = 0;
            }
            else {
              DAT_40001a44 = 6;
            }
          }
          else {
            DAT_40001a44 = 5;
          }
        }
        else {
          DAT_40001a44 = 4;
        }
      }
      else {
        DAT_40001a44 = 3;
      }
    }
    else {
      DAT_40001a44 = 2;
    }
  }
  else {
    DAT_40001a44 = 1;
  }
  if ((byte)(gear_request - GEAR_1) < 6) {
    DAT_40001a54 = get_gear_ratio(gear_request);
    if (DAT_40001a54 != 0) {
      puVar1 = DAT_40001a40;
      if (5000 < (int)DAT_40001a40) {
        puVar1 = &DAT_00001388;
      }
      DAT_40001a48 = (int)(((int)puVar1 - (uint)DAT_40001a54) * 1000) / (int)(uint)DAT_40001a54;
    }
  }
  else {
    DAT_40001a54 = 0;
    DAT_40001a48 = 0;
  }
  return;
}



void compute_min_gear_limit(void)

{
  ulonglong _load_unknown;
  uint16_t uVar1;
  enum_t6e_gear _gear;
  
  if (_load_signed < 0x80) {
    _load_unknown = (longlong)_load_signed + 0x7fU & 0xff;
    if (_load_signed < -0x7f) {
      _load_unknown = 0;
    }
  }
  else {
    _load_unknown = 0xff;
  }
  DAT_40001a5a = lookup_2D_uint8_interpolated
                           (8,_load_unknown,CAL_limiter_overrev_aggression,
                            CAL_limiter_overrev_aggression_X_load);
  if (revlimit_hard_from_ecu == 0) {
    rpm_revlimit_factor = (uint16_t)(((uint)shift_adaptation_learn_gate * 100) / 3000);
  }
  else {
    rpm_revlimit_factor =
         (uint16_t)(((uint)shift_adaptation_learn_gate * 100) / (uint)revlimit_hard_from_ecu);
  }
  _gear = NEUTRAL;
  while (_gear < GEAR_6) {
    uVar1 = get_gear_ratio(_gear + GEAR_1);
    uint16_t_40001a58 =
         (uint16_t)
         (((longlong)(int)(uint)DAT_40001a5a *
           (longlong)(int)(1000000000 / ((uint)DAT_40008f7c * (uint)uVar1)) & 0xffffffffU) / 0xff);
    if (uint16_t_40001a58 < rpm_revlimit_factor) {
      if (_gear == GEAR_5) {
        enum_t6e_gear_40001a13 = _gear + GEAR_1;
      }
      _gear = _gear + GEAR_1;
    }
    else {
      enum_t6e_gear_40001a13 = _gear + GEAR_1;
      _gear = GEAR_6;
    }
  }
  return;
}



void compute_shift_schedule(void)

{
  bool bVar1;
  u8_factor_1_255 *puVar2;
  int iVar4;
  ulonglong uVar3;
  short sVar5;
  uint16_t uVar7;
  uint16_t uVar8;
  int _throttle_rate_commanded;
  uint uVar6;
  int iVar9;
  int iVar10;
  uint x_val;
  uint _rpm_unknown6;
  u8_factor_1_255 _tps_commanded;
  uint8_t *lut;
  
  _tps_commanded = tps_commanded;
  _rpm_unknown6 = (uint)input_shaft_rpm;
  if (DAT_40008f10 == '\0') {
    _rpm_unknown6 = (uint)(tach_rpm >> 2);
  }
  throttle_rate_commanded = (ushort)tps_commanded - (ushort)u8_factor_1_255_40001a68;
  u8_factor_1_255_40001a68 = tps_commanded;
  iVar4 = (int)((uint)(tach_rpm >> 2) * (int)(short)engine_torque) / 955;
  if (iVar4 < 32768) {
    DAT_40001a76 = (short)iVar4;
    if (iVar4 < -0x8000) {
      DAT_40001a76 = -0x8000;
    }
  }
  else {
    DAT_40001a76 = 0x7fff;
  }
  DAT_40001a78 = lookup_2D_uint16_interpolated
                           (16,vehicle_speed____,CAL_shift_schedule_unknown1,
                            CAL_shift_schedule_unknown1_X_carspeed);
  if (_load_signed < 0x80) {
    uVar6 = (int)_load_signed + 0x7fU & 0xff;
    if (_load_signed < -0x7f) {
      uVar6 = 0;
    }
  }
  else {
    uVar6 = 0xff;
  }
  iVar4 = (uint)DAT_40001a78 +
          (int)((uint)DAT_40009170 *
               ((((int)((uint)vehicle_speed____ * (uVar6 - 0x7f)) / 100) * 0xaa5) / 100)) / 10000;
  if (iVar4 < 0x8000) {
    DAT_40001a7a = (short)iVar4;
    if (iVar4 < -0x8000) {
      DAT_40001a7a = -0x8000;
    }
  }
  else {
    DAT_40001a7a = 0x7fff;
  }
  iVar4 = (int)DAT_40001a7a - (int)DAT_40001a76;
  if (iVar4 < 0x8000) {
    DAT_40001a7e = (short)iVar4;
    if (iVar4 < -0x8000) {
      DAT_40001a7e = -0x8000;
    }
  }
  else {
    DAT_40001a7e = 0x7fff;
  }
  if ((byte)(ips_gear_cur - GEAR_1) < 6) {
    uVar7 = get_gear_ratio(ips_gear_cur);
    uVar8 = get_gear_ratio(ips_gear_cur + GEAR_1);
    uVar6 = (int)((uint)tach_rpm * (uint)uVar8) / (int)(uint)uVar7;
    DAT_40001a7c = lookup_2D_uint16_interpolated
                             (0x10,(longlong)((int)uVar6 >> 2) +
                                   (ulonglong)((int)uVar6 < 0 && (uVar6 & 3) != 0) & 0xffff,
                              &DAT_40009e22,&DAT_40009e02);
  }
  uVar3 = (longlong)DAT_40001a7e ^ (ulonglong)DAT_40001a7c + (ulonglong)DAT_40009171;
  DAT_40001a80 = (byte)((longlong)((int)uVar3 >> 1) - (uVar3 & (longlong)DAT_40001a7e) >> 0x18) >> 7
  ;
  if (_rpm_unknown6 < 0x1f5) {
    iVar4 = 0;
  }
  else {
    iVar4 = (int)(_rpm_unknown6 - 500) / 0x19;
    if (0xff < iVar4) {
      iVar4 = 0xff;
    }
  }
  if (_rpm_unknown6 < 0x3e9) {
    iVar10 = 0;
  }
  else {
    iVar10 = (int)(_rpm_unknown6 - 1000) / 0x19;
    if (0xff < iVar10) {
      iVar10 = 0xff;
    }
  }
  DAT_40001a70 = DAT_40001a70 + -1;
  if (DAT_40001a70 == '\0') {
    DAT_40001a70 = '\n';
    if (((DAT_4000171e & 1) == 0) || ((DAT_4000171e & 0xa2) != 0)) {
      if ((_tps_commanded == '\0') ||
         ((_tps_commanded < CAL_tps_threshold_unknown1 && (DAT_40001470 == 0)))) {
        if (DAT_40001470 != 0) {
          DAT_40001470 = DAT_40001470 - 1;
        }
      }
      else {
        DAT_40001470 = (ushort)DAT_400090c6;
      }
    }
    else {
      DAT_40001470 = 0;
    }
    if ((((_tps_commanded == '\0') && (ips_gear_cur != (GEAR_INVALID8|GEAR_INVALID7))) &&
        ((DAT_4000171e & 0x40) != 0)) && ((DAT_4000171e & 0xa2) == 0)) {
      if (DAT_40001a72 < 0) {
        *(ushort *)(&DAT_400057c8 + (DAT_40001a72 + 100) * 2) = vehicle_speed____;
        DAT_40001a72 = DAT_40001a72 + 1;
      }
      else {
        *(ushort *)(&DAT_400057c8 + DAT_40001a72 * 2) = vehicle_speed____;
        bVar1 = DAT_40001a72 < 99;
        sVar5 = DAT_40001a72 + 1;
        DAT_40001a72 = 0;
        if (bVar1) {
          DAT_40001a72 = sVar5;
        }
      }
      if (-1 < DAT_40001a72) {
        iVar9 = (int)DAT_40001a72 - (uint)DAT_40008f17;
        if (iVar9 < 0) {
          iVar9 = iVar9 + 100;
        }
        DAT_40001a6c = (uint)vehicle_speed____ - (uint)*(ushort *)(&DAT_400057c8 + iVar9 * 2);
        if (DAT_400090c5 * 10 < DAT_40001a6c) {
          if (DAT_40001a74 == '\0') {
            DAT_40001a60 = '\x01';
          }
          else {
            DAT_40001a74 = DAT_40001a74 + -1;
          }
        }
        else {
          DAT_40001a74 = DAT_40008f1a;
        }
      }
    }
    else {
      DAT_40001a60 = '\0';
      DAT_40001a74 = DAT_40008f1a;
      DAT_40001a72 = -(ushort)DAT_40008f17;
    }
  }
  if ((throttle_shift < _tps_commanded) ||
     ((vehicle_speed < DAT_400090c8 && (_tps_commanded == '\0')))) {
    DAT_40001a64 = (uint)_tps_commanded * 0xa00;
  }
  else {
    _throttle_rate_commanded = int_abs(throttle_rate_commanded);
    if (((_throttle_rate_commanded < (int)(uint)CAL_throttle_rate_threshold_unknown1) &&
        (_tps_commanded != '\0')) &&
       ((DAT_40001ac5 == '\0' && ((DAT_40001ac6 == '\0' || (DAT_40001ac6 == '\x10')))))) {
      if (((driver_input_flags[1] & 4) == 0) || ((cruise_status_flags & 4) != 0)) {
        if (auto_mode_active == false) {
          uVar6 = ((uint)shift_aggressiveness_blend * (uint)DAT_400090c3) / 0xff +
                  (int)((0xff - (uint)shift_aggressiveness_blend) * (uint)DAT_400090d6) / 0xff &
                  0xff;
          DAT_40001a64 = (int)((0xa00 - uVar6) * DAT_40001a64) / 0xa00 + uVar6 * _tps_commanded;
        }
        else {
          DAT_40001a64 = (int)((0xa00 - (uint)DAT_400090cb) * DAT_40001a64) / 0xa00 +
                         (uint)DAT_400090cb * (uint)_tps_commanded;
        }
      }
      else {
        DAT_40001a64 = (int)((0xa00 - (uint)DAT_400090cc) * DAT_40001a64) / 0xa00 +
                       (uint)DAT_400090cc * (uint)_tps_commanded;
      }
    }
    else if (_tps_commanded == '\0') {
      if ((auto_mode_active == false) ||
         (((driver_input_flags[1] & 4) != 0 && ((cruise_status_flags & 4) == 0)))) {
        puVar2 = shift_sched_work_a_manual_X_throttle;
      }
      else {
        puVar2 = shift_sched_work_a_auto_X_throttle;
      }
      uVar6 = lookup_2D_uint8_interpolated(8,throttle_shift,puVar2 + 8,puVar2);
      if (iVar4 < (int)((uint)DAT_400090c9 + (uVar6 & 0xff))) {
        uVar6 = iVar4 - (uint)DAT_400090c9;
        if ((int)uVar6 < 0) {
          uVar6 = 0;
        }
        DAT_40001a71 = lookup_2D_uint8_interpolated(8,uVar6 & 0xff,puVar2,puVar2 + 8);
        DAT_40001a64 = (uint)DAT_40001a71 * 0xa00;
      }
      else {
        if ((auto_mode_active == false) ||
           (((driver_input_flags[1] & 4) != 0 && ((cruise_status_flags & 4) == 0)))) {
          puVar2 = shift_sched_work_b_manual_X_throttle;
        }
        else {
          puVar2 = shift_sched_work_b_auto_X_throttle;
        }
        uVar6 = lookup_2D_uint8_interpolated(8,throttle_shift,puVar2 + 8,puVar2);
        if ((int)((uVar6 & 0xff) - (uint)DAT_400090ca) < iVar10) {
          uVar6 = iVar10 + (uint)DAT_400090ca;
          if (0xff < (int)uVar6) {
            uVar6 = 0xff;
          }
          DAT_40001a71 = lookup_2D_uint8_interpolated(8,uVar6 & 0xff,puVar2,puVar2 + 8);
          DAT_40001a64 = (uint)DAT_40001a71 * 0xa00;
        }
      }
    }
  }
  if (DAT_40001a60 == '\0') {
    if ((DAT_40001470 == 0) && (DAT_400090c8 <= vehicle_speed)) {
      DAT_40001a5c = (uint)DAT_40001a2b * 0xa00;
    }
    else {
      DAT_40001a5c = 0;
    }
  }
  else {
    if ((auto_mode_active == false) ||
       (((driver_input_flags[1] & 4) != 0 && ((cruise_status_flags & 4) == 0)))) {
      lut = shift_sched_work_a_manual_X_throttle;
      puVar2 = lut;
    }
    else {
      puVar2 = shift_sched_work_a_auto_X_throttle;
    }
    x_val = iVar4 + (uint)DAT_400090c7;
    if (0xff < (int)x_val) {
      x_val = 0xff;
    }
    DAT_40001a61 = lookup_2D_uint8_interpolated(8,x_val & 0xff,puVar2,puVar2 + 8);
    DAT_40001a5c = (uint)DAT_40001a61 * 0xa00;
  }
  if (DAT_40001a64 < DAT_40001a5c) {
    DAT_40001a64 = DAT_40001a5c;
  }
  throttle_shift = (char)(DAT_40001a64 / 0xa00);
  return;
}



void compute_upshift_gear(void)

{
  uint uVar1;
  ushort uVar2;
  uint16_t uVar3;
  enum_t6e_gear gear;
  uint _rpm_unknown1;
  
  if ((auto_mode_active) && (((driver_input_flags[1] & 4) == 0 || ((cruise_status_flags & 4) != 0)))
     ) {
    uVar2 = lookup_2D_uint8_interpolated
                      (8,throttle_shift,shift_sched_work_b_auto,shift_sched_work_b_auto_X_throttle);
  }
  else {
    uVar2 = lookup_2D_uint8_interpolated
                      (8,throttle_shift,shift_sched_work_b_manual,
                       shift_sched_work_b_manual_X_throttle);
  }
  upshift_speed_threshold = (uVar2 & 0xff) * 0x19 + 1000;
  uVar2 = lookup_2D_uint8_interpolated
                    (6,ips_gear_cur,CAL_upshift_revlimit_offset,CAL_upshift_revlimit_offset_X_gear);
  rev_limit_working = revlimit_hard_from_ecu + (uVar2 & 0xff) * -5;
  if (rev_limit_working < upshift_speed_threshold) {
    upshift_speed_threshold = rev_limit_working;
  }
  _rpm_unknown1 = (uint)shift_adaptation_learn_gate;
  uVar1 = (uint)upshift_speed_threshold;
  gear = NEUTRAL;
  while (gear < GEAR_6) {
    uVar3 = get_gear_ratio(gear + GEAR_1);
    if ((1000000000U / (ulonglong)((longlong)(int)(uint)DAT_40008f7c * (longlong)(int)(uint)uVar3) &
        0xffff) < ((ulonglong)((_rpm_unknown1 * 100) / uVar1) & 0xffff)) {
      if (gear == GEAR_5) {
        upshift_target_gear = gear + GEAR_1;
      }
      gear = gear + GEAR_1;
    }
    else {
      upshift_target_gear = gear + GEAR_1;
      gear = GEAR_6;
    }
  }
  return;
}



void compute_downshift_gear(void)

{
  uint uVar1;
  uint uVar2;
  ushort uVar3;
  uint16_t uVar4;
  enum_t6e_gear gear;
  
  if ((auto_mode_active) && (((driver_input_flags[1] & 4) == 0 || ((cruise_status_flags & 4) != 0)))
     ) {
    uVar3 = lookup_2D_uint8_interpolated
                      (8,throttle_shift,shift_sched_work_a_auto,shift_sched_work_a_auto_X_throttle);
  }
  else {
    uVar3 = lookup_2D_uint8_interpolated
                      (8,throttle_shift,shift_sched_work_a_manual,
                       shift_sched_work_a_manual_X_throttle);
  }
  uVar3 = (uVar3 & 0xff) * 0x19 + 500;
  downshift_speed_threshold = 500;
  if (500 < uVar3) {
    downshift_speed_threshold = uVar3;
  }
  uVar1 = (uint)vehicle_speed;
  uVar2 = (uint)downshift_speed_threshold;
  gear = GEAR_6;
  while (gear != NEUTRAL) {
    uVar4 = get_gear_ratio(gear);
    if (((ulonglong)((uVar1 * 10000) / uVar2) & 0xffff) <
        (1000000000U / (ulonglong)((longlong)(int)(uint)DAT_40008f7c * (longlong)(int)(uint)uVar4) &
        0xffff)) {
      if (gear == GEAR_1) {
        downshift_target_gear = GEAR_2;
      }
      gear = gear - GEAR_1;
    }
    else {
      downshift_target_gear = gear;
      if (gear < GEAR_2) {
        downshift_target_gear = GEAR_2;
      }
      gear = NEUTRAL;
    }
  }
                    // CAL_kickdown_decel_threshold has a value of 0xFF. This is curious. Does it
                    // disable decel kickdown?
  if ((((CAL_kickdown_decel_threshold < decel_magnitude) && (auto_mode_active != false)) &&
      ((DAT_4000171e & 1) != 0)) && ((DAT_4000171e & 0xa2) == 0)) {
    downshift_target_gear = enum_t6e_gear_40001a13;
  }
  else if (downshift_target_gear < upshift_target_gear) {
    downshift_target_gear = upshift_target_gear;
  }
  return;
}



enum_t6e_gear select_target_gear(void)

{
  bool bVar1;
  undefined1 uVar2;
  byte bVar3;
  u16_rspeed_rpm uVar4;
  
  if (DAT_40001a9e == '\0') {
    DAT_40001a96 = DAT_40009028;
    DAT_40001a9e = '\x01';
  }
  decode_gear_lever_analog___();
  decode_paddle_shift_request();
  bVar1 = shift_lockout_timer == '\0';
  shift_lockout_timer = shift_lockout_timer + -1;
  if (bVar1) {
    shift_lockout_timer = 0;
  }
  if (((DAT_40001450 & 8) == 0) || ((DAT_40001450 & 0x400) != 0)) {
    if ((DAT_40001678 & 8) == 0) {
      bVar1 = false;
      uVar4 = input_shaft_rpm;
    }
    else {
      uVar4 = 0;
      bVar1 = true;
    }
  }
  else {
    bVar1 = false;
    uVar4 = tach_rpm;
  }
  if (((DAT_40001c38 == -2) || (DAT_40001c38 == '\x01')) || (ips_gear_cur == GEAR_REV)) {
    if (uVar4 == 0) {
      if ((DAT_400015b8 & 1) == 0) {
        DAT_40001a98 = 0;
      }
      else if (((byte)(DAT_40001a98 + 0x80) < 0x7f) && (!bVar1)) {
        DAT_40001a98 = DAT_40001a98 + 1;
      }
    }
    else if (DAT_40001a98 == 0xff) {
      DAT_40001a98 = 0;
    }
    else if (DAT_40001a98 < 0x80) {
      DAT_40001a98 = DAT_40001a98 + 1;
    }
    else {
      DAT_40001a98 = 0x80;
    }
  }
  else {
    DAT_40001a98 = 0;
  }
  if ((((((DAT_40001a8f & 2) == 0) && (DAT_40001aab == '\0')) &&
       (((DAT_400015b8 & 1) != 0 || (((DAT_40001636 & 2) != 0 || ((DAT_40001678 & 4) != 0)))))) &&
      ((DAT_40001a99 != '\x01' || (DAT_40008efc <= DAT_40001a9a)))) ||
     (((((DAT_40001a93 != 0 && ((DAT_400015b8 & 1) != 0)) || (vehicle_speed != '\0')) ||
       ((DAT_40008ef9 <= output_shaft_rpm || ((DAT_40001678 & 1) != 0)))) ||
      (DAT_4000346e == '\x06')))) {
    if ((((DAT_40001a8f & 2) != 0) || (DAT_40001a99 == '\x01')) && (DAT_40001c39 != '\t')) {
      DAT_40001a8f = DAT_40001a8f & 0xfd;
      DAT_40001a88 = 0xff;
    }
    bVar3 = DAT_40001a92 - 1;
    if (DAT_40001a92 == 0) {
      bVar3 = DAT_40001a92;
    }
    DAT_40001a99 = '\0';
    DAT_40001a9a = 0;
    DAT_40001a92 = bVar3;
  }
  else if (output_shaft_rpm < DAT_40008ede) {
    if (DAT_40001a92 < 10) {
      DAT_40001a92 = DAT_40001a92 + 1;
    }
    else {
      DAT_40001aab = '\0';
      if (DAT_40001c39 != '\t') {
        DAT_400017a4 = '\0';
        DAT_40001aac = get_shift_lever_pos_raw___();
      }
      DAT_40001c39 = '\t';
      DAT_40001a90 = '\0';
      DAT_40001ace = '\0';
      DAT_40001aaa = 1;
      DAT_40001a99 = '\0';
      DAT_40001a9a = 0;
    }
  }
  else if (DAT_40001a92 < 10) {
    DAT_40001a92 = DAT_40001a92 + 1;
  }
  else {
    DAT_40001a99 = '\x01';
    DAT_40001a9a = DAT_40001a9a + 1;
  }
  if ((((((DAT_400015b8 & 1) == 0) || ((DAT_40001a8f & 8) == 0)) || (DAT_40001a93 != 0)) ||
      (((DAT_40001a92 != 0 || (DAT_40001a95 != 0)) ||
       ((DAT_40009034 <= vehicle_speed || (DAT_4000902e <= uVar4)))))) ||
     (((DAT_40001655 != '\x01' && (DAT_40001c38 != -2)) ||
      (((GEAR_1 < gear_request && (gear_request != GEAR_INVALID9)) ||
       ((((DAT_40001678 & 1) != 0 || (DAT_4000346e == '\x06')) || (shift_adapt_inhibit == '\x03'))))
      )))) {
    if (((DAT_40001a8f & 8) != 0) && (DAT_40001c39 != '\n')) {
      DAT_40001a8f = DAT_40001a8f & 0xf7;
      if ((DAT_40001653 == '\0') && ((vehicle_speed < DAT_40009034 && (DAT_400090c0 == '\x02')))) {
        if (DAT_40001655 != '\x01') {
          DAT_40001653 = '\x01';
        }
      }
      else {
        DAT_40001a88 = 0xff;
      }
    }
    bVar3 = DAT_40001a94 - 1;
    if (DAT_40001a94 == 0) {
      bVar3 = DAT_40001a94;
    }
  }
  else if (DAT_40001a94 < 10) {
    bVar3 = DAT_40001a94 + 1;
  }
  else {
    if (DAT_40001c39 != '\n') {
      DAT_400017a4 = '\0';
      DAT_40001a89 = 1;
      DAT_40001aac = get_shift_lever_pos_raw___();
    }
    DAT_40001c39 = '\n';
    DAT_40001a90 = '\0';
    DAT_40001ace = '\0';
    DAT_40001aaa = 2;
    bVar3 = DAT_40001a94;
  }
  DAT_40001a94 = bVar3;
  if ((ips_gear_cur == GEAR_REV) || (DAT_40001c39 != '\n')) {
    if (DAT_40001a9b == '\0') {
      DAT_40001a89 = 0;
    }
    else {
      DAT_40001a9b = DAT_40001a9b + -1;
    }
  }
  else {
    DAT_40001a9b = DAT_40009031;
  }
  if (((((DAT_400015b8 & 1) == 0) ||
       ((((DAT_40001a8f & 0x20) == 0 && (DAT_40001ad5 == '\0')) && (DAT_40001a98 != 0xff)))) ||
      ((((DAT_40001655 != '\x01' && (DAT_40001c38 != -2)) && (DAT_40001c38 != '\x01')) &&
       (gear_request != GEAR_REV)))) &&
     (((((DAT_400015b8 & 1) != 0 || (vehicle_speed == '\0')) || (DAT_40001c39 == '\t')) &&
      ((DAT_40001678 & 1) == 0)))) {
    if ((((DAT_40001a8f & 0x20) != 0) || (DAT_40001ad5 != '\0')) && (DAT_40001c39 != '\0')) {
      DAT_40001a8f = DAT_40001a8f & 0xdf;
      DAT_40001a88 = 0xff;
    }
    bVar3 = DAT_40001a93 - 1;
    if (DAT_40001a93 == 0) {
      bVar3 = DAT_40001a93;
    }
  }
  else if (DAT_40001a93 < 10) {
    bVar3 = DAT_40001a93 + 1;
  }
  else {
    if ((((DAT_400015b8 & 1) == 0) && (vehicle_speed != '\0')) || (DAT_40001a98 == 0xff)) {
      DAT_40001636 = DAT_40001636 | 4;
    }
    if (DAT_40001c39 != '\0') {
      DAT_400017a4 = '\0';
      DAT_40001aac = get_shift_lever_pos_raw___();
    }
    DAT_40001c39 = '\0';
    DAT_40001a90 = '\0';
    DAT_40001ace = '\0';
    DAT_40001aaa = 4;
    bVar3 = DAT_40001a93;
  }
  DAT_40001a93 = bVar3;
  if ((((((((DAT_400015b8 & 1) == 0) || (((DAT_40001a8f & 0x80) == 0 && (DAT_40001ad6 == '\0')))) ||
         (DAT_40001a93 != 0)) || ((DAT_40001a92 != 0 || (DAT_40001a94 != 0)))) ||
       ((((DAT_40001655 != '\x01' && (gear_request != GEAR_REV)) ||
         ((DAT_40009034 <= vehicle_speed || (DAT_4000902e <= uVar4)))) &&
        (((gear_request != NEUTRAL || ((vehicle_speed <= DAT_40008f4c || (DAT_40001ad4 == '\n'))))
         && (DAT_40001ace == '\0')))))) &&
      (((DAT_40001a8a != '\0' || (DAT_40001ace == '\0')) || (DAT_40001c39 != -2)))) ||
     (((DAT_40001678 & 1) != 0 || (DAT_4000346e == '\x06')))) {
    if ((((DAT_40001a8f & 0x80) != 0) || (DAT_40001ad6 != '\0')) && (DAT_40001c39 != -2)) {
      DAT_40001a8f = DAT_40001a8f & 0x7f;
      if (((DAT_40001655 == '\x01') || (gear_request == GEAR_REV)) || (DAT_400090c0 != '\x02')) {
        DAT_40001a88 = 0xff;
      }
      else if (DAT_40001653 == '\0') {
        DAT_40001653 = '\x01';
      }
    }
    bVar3 = DAT_40001a95 - 1;
    if (DAT_40001a95 == 0) {
      bVar3 = DAT_40001a95;
    }
  }
  else if (DAT_40001a95 < 10) {
    bVar3 = DAT_40001a95 + 1;
  }
  else {
    if (DAT_40001c39 != -2) {
      DAT_400017a4 = '\0';
      DAT_40001aac = get_shift_lever_pos_raw___();
    }
    DAT_40001c39 = -2;
    DAT_40001a90 = '\0';
    if (DAT_40001ace != '\0') {
      DAT_40001a8b = DAT_40008f5e;
    }
    DAT_40001ace = '\0';
    DAT_40001aaa = 8;
    bVar3 = DAT_40001a95;
  }
  DAT_40001a95 = bVar3;
  if (((DAT_40001c39 == '\t') && (DAT_400017a4 == '\x01')) && (DAT_40002bdc != '\0')) {
    DAT_40001ac4 = 1;
  }
  else {
    DAT_40001ac4 = 0;
  }
  if (DAT_40001c38 == -2) {
    if (((paddle_request & 1) != 0) && (upshift_armed == true)) {
      DAT_40001ace = '\x01';
      DAT_40001a8e = 1;
    }
    if (((paddle_request & 2) != 0) && (downshift_armed == true)) {
      DAT_40001ace = '\x02';
    }
  }
  if ((paddle_request & 1) == 0) {
    if (upshift_debounce_counter == 0) {
      upshift_armed = true;
    }
    else {
      upshift_debounce_counter = upshift_debounce_counter - 1;
    }
    DAT_40001a8e = 0;
  }
  else {
    DAT_40001a8a = DAT_40008f61;
    if (auto_mode_active != false) {
      DAT_40001a8a = DAT_40008f7f;
    }
    if (upshift_debounce_counter < 10) {
      upshift_debounce_counter = upshift_debounce_counter + 1;
    }
  }
  if ((paddle_request & 2) == 0) {
    if (downshift_debounce_counter == 0) {
      downshift_armed = true;
    }
    else {
      downshift_debounce_counter = downshift_debounce_counter - 1;
    }
  }
  else {
    DAT_40001a8a = DAT_40008f61;
    if (auto_mode_active != false) {
      DAT_40001a8a = DAT_40008f7f;
    }
    if (downshift_debounce_counter < 10) {
      downshift_debounce_counter = downshift_debounce_counter + 1;
    }
  }
  cruise_shift_control();
  compute_min_gear_limit();
  build_upshift_schedule();
  build_downshift_schedule();
  compute_shift_schedule();
  compute_upshift_gear();
  compute_downshift_gear();
  compute_shift_speed_guards();
  uVar2 = DAT_40001a9c;
  if ((vehicle_speed < DAT_40008f4a) && (uVar2 = 1, 3 < (byte)(gear_request - GEAR_3))) {
    uVar2 = DAT_40001a9c;
  }
  DAT_40001a9c = uVar2;
  if ((((vehicle_speed < DAT_40008f4a) && (gear_request == GEAR_2)) &&
      (ips_gear_cur == (GEAR_INVALID8|GEAR_INVALID7))) && (GEAR_2 < shift_from_gear)) {
    DAT_40001a9d = 1;
  }
  if ((vehicle_speed == '\0') || (DAT_40008f4a < vehicle_speed)) {
    DAT_40001a9d = 0;
    DAT_40001a9c = 0;
  }
  if ((((vehicle_speed < DAT_40008f4a) && ((byte)(gear_request - GEAR_3) < 4)) ||
      ((vehicle_speed < DAT_40008f4a &&
       (((gear_request == GEAR_2 && (ips_gear_cur == (GEAR_INVALID8|GEAR_INVALID7))) &&
        (GEAR_2 < shift_from_gear)))))) ||
     (((vehicle_speed == '\0' && (output_shaft_rpm < DAT_40008ed4)) &&
      (((ips_gear_cur == (GEAR_INVALID8|GEAR_INVALID7) && ((byte)(shift_from_gear - GEAR_3) < 4)) ||
       ((byte)(gear_request - GEAR_2) < 5)))))) {
    DAT_40001a8d = 1;
    gear_request = GEAR_1;
    DAT_40001a97 = 1;
  }
  else if ((DAT_40001ace == '\0') && (DAT_40001a90 == '\0')) {
    if ((((DAT_400023a6 == '\0') && (DAT_400023a3 == '\0')) && (DAT_400023a4 == '\0')) &&
       (DAT_400023a7 == '\0')) {
      if (DAT_40001a96 == '\0') {
        if (DAT_40001c39 == -1) {
          DAT_40001c39 = '\0';
          DAT_40001aaa = 4;
        }
        else {
          gear_request = NEUTRAL;
          DAT_40001a97 = 0;
          DAT_40001c38 = '\0';
        }
      }
      else {
        DAT_40001a96 = DAT_40001a96 + -1;
      }
    }
    else {
      DAT_40001a96 = DAT_40009028;
      if (DAT_400023a6 == '\0') {
        if (DAT_400023a7 == '\0') {
          if ((DAT_400023a4 == '\0') || (DAT_40001c39 == '\n')) {
            if ((DAT_400023a3 == '\0') || ((DAT_40001c39 != '\n' && (gear_request != ~NEUTRAL)))) {
              if (gear_request == ~NEUTRAL) {
                DAT_40001c39 = '\0';
                DAT_40001aaa = 4;
              }
              gear_request = NEUTRAL;
              DAT_40001a97 = 0;
              DAT_40001c38 = '\0';
            }
            else {
              if (gear_request == ~NEUTRAL) {
                DAT_40001c39 = '\n';
                DAT_40001aaa = 2;
              }
              gear_request = GEAR_REV;
              DAT_40001c38 = '\0';
            }
          }
          else {
            if (gear_request == ~NEUTRAL) {
              DAT_40001c39 = -2;
              DAT_40001aaa = 8;
            }
            if ((DAT_40001c39 == -2) &&
               (DAT_40001c38 = -2, ips_gear_cur != (GEAR_INVALID8|GEAR_INVALID7))) {
              auto_select_gear();
            }
          }
        }
        else {
          if (gear_request == ~NEUTRAL) {
            DAT_40001c39 = '\0';
            DAT_40001aaa = 4;
          }
          gear_request = NEUTRAL;
          DAT_40001a97 = 0;
          DAT_40001c38 = '\0';
        }
      }
      else {
        if (gear_request == ~NEUTRAL) {
          DAT_40001c39 = '\t';
          DAT_40001aaa = 1;
        }
        gear_request = GEAR_INVALID9;
        DAT_40001a97 = 9;
        DAT_40001c38 = '\0';
      }
    }
  }
  else {
    DAT_40001aaa = 0;
    DAT_40001c38 = '\x01';
    if (DAT_40001ace == '\x01') {
      upshift_armed = false;
      DAT_40001ace = '\x02';
    }
    if (ips_gear_cur == (GEAR_INVALID8|GEAR_INVALID7)) {
      if (((upshift_debounce_counter == 10) && (upshift_armed == true)) &&
         (shift_lockout_timer == '\0')) {
        paddle_shift_pending = true;
      }
      else if ((downshift_debounce_counter == 10) && (downshift_armed == true)) {
        paddle_shift_pending = true;
      }
    }
    else {
      if ((((gear_request <= enum_t6e_gear_40001a13) ||
           ((DAT_40001ac6 != '\0' && (DAT_40001ac6 != '@')))) && (paddle_shift_pending == true)) ||
         (((DAT_40001ac5 != '\0' && (DAT_40001ac5 != '@')) && (paddle_shift_pending == true)))) {
        paddle_shift_pending = false;
      }
      if (((((upshift_debounce_counter == 10) && (upshift_armed == true)) ||
           (paddle_shift_pending == true)) &&
          (((DAT_40001ac5 == '\0' || (DAT_40001ac5 == '@')) ||
           (gear_request < enum_t6e_gear_40001a13)))) &&
         ((upshift_min_speed_inhibit == false && (shift_lockout_timer == '\0')))) {
        upshift_armed = false;
        paddle_shift_pending = false;
        if ((uint)gear_request + (uint)CAL_shift_gears_per_shift < 7) {
          gear_request = gear_request + CAL_shift_gears_per_shift;
        }
      }
      if ((((auto_mode_active == false) &&
           ((uint)rev_limit_working < (uint)((int)(uint)tach_rpm >> 2))) && (rev_limit_working != 0)
          ) && (CAL_shift_auto_upshift_at_revlimit_enable != false)) {
        upshift_armed = false;
        paddle_shift_pending = false;
        if ((uint)gear_request + (uint)CAL_shift_gears_per_shift < 7) {
          gear_request = gear_request + CAL_shift_gears_per_shift;
        }
        shift_lockout_timer = CAL_shift_lockout_time;
      }
      if (((((downshift_debounce_counter == 10) && (downshift_armed == true)) ||
           (paddle_shift_pending == true)) && ((DAT_40001ac6 == '\0' || (DAT_40001ac6 == '@')))) ||
         ((input_shaft_rpm < downshift_max_input_shaft_rpm &&
          ((vehicle_speed < DAT_40009037 || (GEAR_2 < gear_request)))))) {
        if ((enum_t6e_gear_40001a13 < gear_request) &&
           (((GEAR_2 < gear_request ||
             ((((gear_request == GEAR_2 && (vehicle_speed < DAT_40008f4b)) &&
               (input_shaft_load < 0x18)) && ((DAT_40001678 & DAT_4000916c) == 0)))) ||
            (((gear_request == GEAR_2 && (vehicle_speed < DAT_400090a9)) && (23 < input_shaft_load))
            )))) {
          downshift_armed = false;
          paddle_shift_pending = false;
          if (0 < (int)((uint)gear_request - (uint)CAL_shift_gears_per_shift)) {
            gear_request = gear_request - CAL_shift_gears_per_shift;
          }
        }
        else if ((downshift_max_input_shaft_rpm <= input_shaft_rpm) ||
                ((DAT_40009037 <= vehicle_speed && (gear_request < GEAR_3)))) {
          paddle_shift_pending = false;
        }
      }
    }
  }
  shift_selector_supervisor();
  debounce_shift_lever();
  return gear_request;
}



void decode_paddle_shift_request(void)

{
  if ((paddle_shift_flags & 4) == 0) {
    if ((paddle_shift_flags & 8) == 0) {
      if (((paddle_shift_flags & 1) == 0) || (paddle_hold_counter == 0)) {
        if (((paddle_shift_flags & 2) == 0) || (paddle_hold_counter == 0)) {
          if ((paddle_shift_flags & 0xf) == 0) {
            paddle_hold_counter = 0x96;
            paddle_request = 0;
          }
          else {
            paddle_request = 0;
          }
        }
        else {
          if (paddle_downshift_trigger_count < paddle_hold_counter) {
            paddle_hold_counter = paddle_hold_counter - 1;
          }
          if (paddle_hold_counter == paddle_downshift_trigger_count) {
            paddle_request = 2;
          }
        }
      }
      else {
        if (paddle_hold_counter < paddle_upshift_trigger_count) {
          paddle_hold_counter = paddle_hold_counter + 1;
        }
        if (paddle_hold_counter == paddle_upshift_trigger_count) {
          paddle_request = 1;
        }
      }
    }
    else {
      paddle_hold_counter = 0;
      paddle_request = 8;
    }
  }
  else {
    paddle_hold_counter = 0x96;
    paddle_request = 0;
    if (DAT_40001c38 == '\x01') {
      DAT_40001c38 = -2;
    }
  }
  return;
}



void pack_shift_position_request_bits(void)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = shift_position_request_bits | 1;
  if (DAT_400023a6 == '\0') {
    bVar1 = shift_position_request_bits & 0xfe;
  }
  bVar2 = bVar1 | 2;
  if (DAT_400023a3 == '\0') {
    bVar2 = bVar1 & 0xfd;
  }
  bVar1 = bVar2 | 4;
  if (DAT_400023a7 == '\0') {
    bVar1 = bVar2 & 0xfb;
  }
  shift_position_request_bits = bVar1 | 8;
  if (DAT_400023a4 == '\0') {
    shift_position_request_bits = bVar1 & 0xf7;
  }
  return;
}



void pwm_set_dutycycle(uint param_1,ulonglong param_2)

{
  int iVar1;
  
  WriteExternalEnableImmediate(0);
  if (param_1 < *(uint *)((int)&REG_EMIOS_UC0_CBDR + (int)((param_2 & 0xff) << 5))) {
    if (param_1 < 3) {
      *(undefined4 *)((int)&REG_EMIOS_UC0_CADR + (int)((param_2 & 0xff) << 5)) =
           *(undefined4 *)((int)&REG_EMIOS_UC0_CBDR + (int)((param_2 & 0xff) << 5));
      iVar1 = (int)((param_2 & 0xff) << 5);
      *(uint *)((int)&REG_EMIOS_UC0_CCR + iVar1) =
           *(uint *)((int)&REG_EMIOS_UC0_CCR + iVar1) & 0xffffdfff | 0x2000;
    }
    else if (*(uint *)((int)&REG_EMIOS_UC0_CCNTR + (int)((param_2 & 0xff) << 5)) < param_1 + 2) {
      *(uint *)((int)&REG_EMIOS_UC0_CADR + (int)((param_2 & 0xff) << 5)) = param_1;
    }
    else {
      *(uint *)((int)&REG_EMIOS_UC0_CADR + (int)((param_2 & 0xff) << 5)) = param_1;
      iVar1 = (int)((param_2 & 0xff) << 5);
      *(uint *)((int)&REG_EMIOS_UC0_CCR + iVar1) =
           *(uint *)((int)&REG_EMIOS_UC0_CCR + iVar1) & 0xffffdfff | 0x2000;
    }
  }
  else {
    *(undefined4 *)((int)&REG_EMIOS_UC0_CADR + (int)((param_2 & 0xff) << 5)) = 0;
    iVar1 = (int)((param_2 & 0xff) << 5);
    *(uint *)((int)&REG_EMIOS_UC0_CCR + iVar1) =
         *(uint *)((int)&REG_EMIOS_UC0_CCR + iVar1) & 0xffffefff | 0x1000;
  }
  return;
}



void decode_gear_lever_analog___(void)

{
  byte bVar1;
  
  DAT_40001be8 = (short)((int)(uint)DAT_40001dbc >> 4);
  DAT_40001be6 = (short)((int)(uint)DAT_40001dc0 >> 4);
  DAT_40001be4 = (short)((int)(uint)DAT_40001dbe >> 4);
  DAT_40001be2 = (short)((int)(uint)DAT_40001dc2 >> 4);
  if ((uint)((int)(uint)DAT_40001dbe >> 4) < 0x200) {
    if ((DAT_40001a8f & 0x10) != 0) {
      DAT_40001a8f = DAT_40001a8f & 0x75 | 0x20;
    }
    DAT_40001a8f = DAT_40001a8f & 0xef;
  }
  else {
    bVar1 = DAT_40001a8f & 0xdf | 0x10;
    if ((uint)((int)(uint)DAT_40001dbc >> 4) < 0x200) {
      if (((DAT_40001a8f & 1) != 0) && ((DAT_40001a8f & 0x8a) == 0)) {
        bVar1 = DAT_40001a8f & 0xdf | 0x12;
      }
      DAT_40001a8f = bVar1;
      DAT_40001a8f = DAT_40001a8f & 0xfe;
    }
    else {
      DAT_40001a8f = DAT_40001a8f & 0xdd | 0x11;
    }
    if ((uint)((int)(uint)DAT_40001dc0 >> 4) < 0x200) {
      if (((DAT_40001a8f & 4) != 0) && ((DAT_40001a8f & 0xaa) == 0)) {
        DAT_40001a8f = DAT_40001a8f | 8;
      }
      DAT_40001a8f = DAT_40001a8f & 0xfb;
    }
    else {
      DAT_40001a8f = DAT_40001a8f & 0xf7 | 4;
    }
    if ((uint)((int)(uint)DAT_40001dc2 >> 4) < 0x200) {
      if (((DAT_40001a8f & 0x40) != 0) && ((DAT_40001a8f & 0xaa) == 0)) {
        DAT_40001a8f = DAT_40001a8f | 0x80;
      }
      DAT_40001a8f = DAT_40001a8f & 0xbf;
    }
    else {
      DAT_40001a8f = DAT_40001a8f & 0x7f | 0x40;
    }
  }
  return;
}



void debounce_shift_lever(void)

{
  bool bVar1;
  byte bVar3;
  byte bVar4;
  short sVar2;
  byte bVar5;
  
  if ((DAT_40001678 & 1) == 0) {
    if ((DAT_40001840 & 0x3c) == 0) {
      sVar2 = get_shift_lever_pos_raw___();
      if (sVar2 == -1) {
        if ((shift_position_request_bits & 0xf) == 1) {
          bVar5 = 1;
        }
        else if ((shift_position_request_bits & 0xf) == 2) {
          bVar5 = 2;
        }
        else if ((shift_position_request_bits & 0xf) == 4) {
          bVar5 = 4;
        }
        else {
          bVar5 = 0;
          if ((shift_position_request_bits & 0xf) == 8) {
            bVar5 = 8;
          }
        }
        bVar1 = true;
      }
      else {
        bVar5 = DAT_40001aaa;
        if (DAT_40001aaa == 0x10) {
          bVar1 = true;
        }
        else {
          bVar1 = false;
        }
      }
    }
    else {
      bVar5 = 0;
      if (((DAT_40001840 & 4) != 0) && (bVar5 = 1, (DAT_40001844 & 4) == 0)) {
        bVar5 = 0;
      }
      bVar3 = bVar5;
      if (((DAT_40001840 & 8) != 0) && (bVar3 = bVar5 | 2, (DAT_40001844 & 8) == 0)) {
        bVar3 = bVar5;
      }
      bVar4 = bVar3;
      if (((DAT_40001840 & 0x10) != 0) && (bVar4 = bVar3 | 4, (DAT_40001844 & 0x10) == 0)) {
        bVar4 = bVar3;
      }
      bVar5 = bVar4;
      if (((DAT_40001840 & 0x20) != 0) && (bVar5 = bVar4 | 8, (DAT_40001844 & 0x20) == 0)) {
        bVar5 = bVar4;
      }
      bVar1 = true;
    }
  }
  else {
    bVar1 = true;
    bVar5 = 4;
  }
  DAT_40001aa0 = bVar5;
  if (bVar1) {
    DAT_40001aa1 = DAT_400090bd;
  }
  else if ((((((bVar5 == 1) && (DAT_40001bfa != '\t')) || ((bVar5 == 2 && (DAT_40001bfa != '\n'))))
            || ((bVar5 == 4 && (DAT_40001bfa != '\0')))) || ((bVar5 == 8 && (DAT_40001bfa != -2))))
          || (DAT_40001bfa == -1)) {
    if (DAT_40001aa3 != bVar5) {
      DAT_40001aa1 = DAT_400090bd;
    }
    bVar1 = DAT_40001aa1 == '\0';
    DAT_40001aa1 = DAT_40001aa1 + -1;
    if (bVar1) {
      DAT_40001aa1 = '\0';
    }
    if (DAT_40001aa1 == '\0') {
      if (DAT_40001bfa == '\t') {
        DAT_40001aa0 = 1;
      }
      else if (DAT_40001bfa == '\n') {
        DAT_40001aa0 = 2;
      }
      else if (DAT_40001bfa == '\0') {
        DAT_40001aa0 = 4;
      }
      else if (DAT_40001bfa == -2) {
        DAT_40001aa0 = 8;
      }
      else {
        DAT_40001aa0 = 0;
      }
    }
  }
  else {
    DAT_40001aa1 = DAT_400090bd;
  }
  DAT_40001aa3 = bVar5;
  if (DAT_40001aa0 == 0x10) {
    DAT_4000147c = DAT_4000147c + -1;
    if (DAT_4000147c == '\0') {
      DAT_4000147c = 'd';
      DAT_40001aa2 = DAT_40001aa2 ^ 1;
    }
    if (DAT_40001aa2 == 0) {
      DAT_40001bee = DAT_40008f55;
      DAT_40001bed = DAT_40008f57;
      DAT_40001bec = DAT_40008f59;
      DAT_40001beb = DAT_40008f5b;
    }
    else {
      DAT_40001bee = DAT_40008f54;
      DAT_40001bed = DAT_40008f56;
      DAT_40001bec = DAT_40008f58;
      DAT_40001beb = DAT_40008f5a;
    }
  }
  else {
    DAT_40001bee = DAT_40008f55;
    if ((DAT_40001aa0 & 1) != 0) {
      DAT_40001bee = DAT_40008f54;
    }
    DAT_40001bed = DAT_40008f57;
    if ((DAT_40001aa0 & 2) != 0) {
      DAT_40001bed = DAT_40008f56;
    }
    DAT_40001beb = DAT_40008f5b;
    if ((DAT_40001aa0 & 4) != 0) {
      DAT_40001beb = DAT_40008f5a;
    }
    DAT_40001bec = DAT_40008f59;
    if ((DAT_40001aa0 & 8) != 0) {
      DAT_40001bec = DAT_40008f58;
    }
  }
  return;
}



void compute_shift_speed_guards(void)

{
  ushort uVar1;
  uint16_t ratio;
  u32_rspeed_rpm rpm;
  
  uVar1 = lookup_2D_uint8_interpolated
                    (8,decel_magnitude,CAL_shift_guard_rpm_unknown,
                     CAL_shift_guard_rpm_unknown_X_decel_magnitude);
  downshift_max_input_shaft_rpm = (uVar1 & 0xff) << 3;
  if ((byte)(gear_request - GEAR_2) < 4) {
    ratio = get_gear_ratio(gear_request + GEAR_1);
    rpm = (int)((uint)ratio * ((int)((uint)vehicle_speed____ * (uint)DAT_40008f7c) / 10000)) / 1000;
  }
  else {
    rpm = 0;
  }
  if ((rpm == 0) ||
     (((uint)downshift_max_input_shaft_rpm + (uint)CAL_shift_speed_guard_margin_ & 0xffff) <= rpm))
  {
    upshift_min_speed_inhibit = false;
  }
  else {
    upshift_min_speed_inhibit = true;
  }
  return;
}



void auto_select_gear(void)

{
  if (auto_shift_direction_state == '\0') {
    auto_shift_dwell_timer = DAT_4000902a;
    auto_shift_direction_state = '\x01';
  }
  if ((((ips_gear_cur == NEUTRAL) || (ips_gear_cur == GEAR_INVALID9)) || (ips_gear_cur == GEAR_REV))
     || ((ips_gear_cur == ~NEUTRAL || (vehicle_speed < CAL_garage_engage_speed)))) {
    if ((gear_request == ~NEUTRAL) || (CAL_garage_engage_speed <= vehicle_speed)) {
      gear_request = downshift_target_gear;
    }
    else {
      gear_request = GEAR_1;
    }
    auto_shift_direction_state = '\x01';
  }
  else if ((((byte)(ips_gear_cur - GEAR_1) < 5) &&
           ((ips_gear_cur < upshift_target_gear && (DAT_40001ac5 == '\0')))) ||
          (((uint)rev_limit_working < (uint)((int)(uint)tach_rpm >> 2) && (rev_limit_working != 0)))
          ) {
    if ((auto_shift_direction_state == '\x02') ||
       ((uint)rev_limit_working < (uint)((int)(uint)tach_rpm >> 2))) {
      if ((auto_shift_dwell_timer == '\0') ||
         ((uint)rev_limit_working < (uint)((int)(uint)tach_rpm >> 2))) {
        gear_request = ips_gear_cur + GEAR_1;
      }
      else {
        auto_shift_dwell_timer = auto_shift_dwell_timer + -1;
      }
    }
    else {
      auto_shift_dwell_timer = DAT_4000902a;
    }
    auto_shift_direction_state = '\x02';
  }
  else if (((((byte)(ips_gear_cur - GEAR_4) < 3) && (downshift_target_gear + 1 < (uint)ips_gear_cur)
            ) && (DAT_40001ac6 == '\0')) &&
          (((driver_input_flags[1] & 4) == 0 || (DAT_40001461 + 1 < (uint)ips_gear_cur)))) {
    if (auto_shift_direction_state == '\x03') {
      if (auto_shift_dwell_timer == '\0') {
        gear_request = ips_gear_cur - GEAR_2;
      }
      else {
        auto_shift_dwell_timer = auto_shift_dwell_timer + -1;
      }
    }
    else {
      auto_shift_dwell_timer = DAT_4000902a;
    }
    auto_shift_direction_state = '\x03';
  }
  else if (((((byte)(ips_gear_cur - GEAR_3) < 4) &&
            ((downshift_target_gear < ips_gear_cur && (DAT_40001ac6 == '\0')))) &&
           (((driver_input_flags[1] & 4) == 0 || (DAT_40001461 < ips_gear_cur)))) ||
          (((((byte)(ips_gear_cur - GEAR_3) < 4 && (downshift_target_gear < ips_gear_cur)) &&
            (DAT_40001ac6 != '\0')) && (input_shaft_rpm < DAT_4000915a)))) {
    if (auto_shift_direction_state == '\x04') {
      if (auto_shift_dwell_timer == '\0') {
        gear_request = ips_gear_cur - GEAR_1;
      }
      else {
        auto_shift_dwell_timer = auto_shift_dwell_timer + -1;
      }
    }
    else {
      auto_shift_dwell_timer = DAT_4000902a;
    }
    auto_shift_direction_state = '\x04';
  }
  else {
    auto_shift_dwell_timer = DAT_4000902a;
  }
  return;
}



undefined8 check_selector_learn_allowed(void)

{
  char cVar2;
  undefined8 uVar1;
  
  if ((((((tach_rpm == 0) && ((DAT_40001450 & 8) != 0)) && ((DAT_40001450 & 0x400) == 0)) &&
       ((input_shaft_rpm == 0 && (vehicle_speed == '\0')))) &&
      (((DAT_40001678 & 0x20000000) == 0 &&
       ((cVar2 = FUN_0004ca5c(), cVar2 == '\x01' || (DAT_40001655 == '\x01')))))) &&
     ((ushort)((ushort)DAT_40008ea9 << 2) < DAT_400015ba)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



undefined8 learn_selector_positions(char param_1)

{
  char cVar1;
  undefined8 uVar2;
  
  uVar2 = 0;
  DAT_40001aaa = 0x10;
  DAT_40001481 = DAT_40001481 + -1;
  if (DAT_40001481 == '\0') {
    DAT_40001481 = '\x14';
    cVar1 = check_selector_learn_allowed();
    if (((cVar1 == '\0') || (param_1 == '\0')) && ((DAT_40001678 & 0x20000000) == 0)) {
      reset_selector_move_state();
      DAT_40001aae = '\0';
    }
    else {
      uVar2 = 1;
      cVar1 = '\a';
      if ((DAT_40001678 & 0x20000000) == 0) {
        cVar1 = DAT_40001aae;
      }
      DAT_40001aae = cVar1;
      switch(cVar1) {
      case '\0':
        DAT_40001bfc = 1;
        DAT_40001aae = cVar1 + '\x01';
        DAT_40002bdc = 0;
        DAT_400017a4 = '\0';
        DAT_40001c56 = 1;
        break;
      case '\x01':
        DAT_40001438 = 500;
        if (DAT_400017a4 != '\0') {
          DAT_40001aae = cVar1 + '\x01';
        }
        break;
      case '\x02':
        cVar1 = move_selector_to_position(0xfe);
        if (cVar1 == -1) {
          DAT_40001aae = '\a';
        }
        else if (cVar1 == '\x02') {
          DAT_40001aae = DAT_40001aae + '\x01';
        }
        break;
      case '\x03':
        cVar1 = move_selector_to_position(0);
        if (cVar1 == -1) {
          DAT_40001aae = '\a';
        }
        else if (cVar1 == '\x02') {
          DAT_40001aae = DAT_40001aae + '\x01';
        }
        break;
      case '\x04':
        cVar1 = move_selector_to_position(10);
        if (cVar1 == -1) {
          DAT_40001aae = '\a';
        }
        else if (cVar1 == '\x02') {
          DAT_40001aae = DAT_40001aae + '\x01';
        }
        break;
      case '\x05':
        cVar1 = move_selector_to_position(9);
        if (cVar1 == -1) {
          DAT_40001aae = '\a';
        }
        else if (cVar1 == '\x02') {
          DAT_40001aae = DAT_40001aae + '\x01';
        }
        break;
      case '\x06':
        DAT_40001aa9 = 0;
        reset_selector_move_state();
        DAT_40001aae = '\0';
        DAT_40002bdc = 1;
        uVar2 = 2;
        break;
      case '\a':
        DAT_40001aa9 = 0;
        reset_selector_move_state();
        DAT_40001aae = '\0';
        uVar2 = 0xff;
        break;
      default:
        DAT_40001aa9 = 0;
        reset_selector_move_state();
        DAT_40001aae = '\0';
      }
    }
  }
  return uVar2;
}



undefined8 move_selector_to_position(char param_1)

{
  bool bVar2;
  short sVar1;
  undefined8 uVar3;
  
  uVar3 = 1;
  if (((((DAT_40001aaf == '\x01') || (DAT_40001aaf == '\x03')) || ((byte)(DAT_40001aaf - 5U) < 2))
      && (((((param_1 == -2 && ((shift_position_request_bits & 0xf) == 8)) ||
            ((param_1 == '\0' && ((shift_position_request_bits & 0xf) == 4)))) ||
           ((param_1 == '\n' && ((shift_position_request_bits & 0xf) == 2)))) ||
          ((param_1 == '\t' && ((shift_position_request_bits & 0xf) == 1)))))) ||
     ((DAT_40001aaf == '\x02' ||
      ((DAT_40001aaf == '\x04' && ((shift_position_request_bits & 0xf) == 0)))))) {
    bVar2 = true;
  }
  else {
    bVar2 = false;
  }
  if (param_1 == -1) {
    DAT_40001aaf = '\0';
  }
  else {
    if (DAT_40001aaf == '\0') {
      DAT_40001bfe = 1;
      DAT_400017a4 = '\0';
      DAT_40001480 = '\x14';
      if (param_1 == -2) {
        DAT_40001480 = -0x14;
      }
      DAT_40001aaf = '\x01';
    }
    else if (DAT_40001aaf == '\x01') {
      if (bVar2) {
        if ((param_1 == -2) || ((byte)(param_1 - 9U) < 2)) {
          DAT_40001abc = (ushort)DAT_40009009 << 1;
          DAT_40001aaf = '\x06';
        }
        else {
          DAT_40001480 = -DAT_40001480;
          DAT_40001aaf = '\x02';
        }
      }
    }
    else if (DAT_40001aaf == '\x02') {
      if (bVar2) {
        DAT_40001480 = '\x05';
        DAT_40001aaf = '\x03';
      }
    }
    else if (DAT_40001aaf == '\x03') {
      if (bVar2) {
        DAT_40001ab0 = get_shift_lever_pos_raw___();
        DAT_40001aaf = DAT_40001aaf + '\x01';
      }
    }
    else if (DAT_40001aaf == '\x04') {
      if (bVar2) {
        DAT_40001ab2 = get_shift_lever_pos_raw___();
        DAT_40001480 = -DAT_40001480;
        DAT_40001aaf = DAT_40001aaf + '\x01';
      }
    }
    else if (DAT_40001aaf == '\x05') {
      if (bVar2) {
        DAT_40001ab4 = get_shift_lever_pos_raw___();
        DAT_40001abc = (ushort)DAT_40009009 << 1;
        DAT_40001aaf = DAT_40001aaf + '\x01';
      }
    }
    else if (DAT_40001aaf == '\x06') {
      DAT_40001bfe = 0;
      if (DAT_400017a4 == '\0') {
        if (DAT_40001abc == 0) {
          uVar3 = 0xff;
        }
        else {
          DAT_40001abc = DAT_40001abc + -1;
        }
      }
      else if (bVar2) {
        sVar1 = get_shift_lever_pos_raw___();
        if (sVar1 == -1) {
          uVar3 = 0xff;
        }
        else if (param_1 == '\t') {
          DAT_40002bda = get_shift_lever_pos_raw___();
          uVar3 = 2;
          DAT_40001aaf = '\0';
          DAT_40001bfd = 1;
        }
        else {
          if (param_1 == -2) {
            DAT_40002bd4 = get_shift_lever_pos_raw___();
          }
          else if (param_1 == '\0') {
            DAT_40002bd6 = get_shift_lever_pos_raw___();
          }
          else if (param_1 == '\n') {
            DAT_40001bde = get_shift_lever_pos_raw___();
            DAT_40002bd8 = DAT_40001bde;
          }
          uVar3 = 2;
          DAT_40001aaf = '\0';
          DAT_40001bfd = 1;
        }
      }
      else {
        uVar3 = 0xff;
      }
    }
    else {
      uVar3 = 0xff;
    }
    if (DAT_40001aaf != '\x06') {
      if ((int)((uint)DAT_40001438 + (int)DAT_40001480) < 100) {
        DAT_40001438 = 100;
        uVar3 = 0xff;
      }
      else if ((int)((uint)DAT_40001438 + (int)DAT_40001480) < 0x385) {
        DAT_40001438 = DAT_40001438 + (short)DAT_40001480;
      }
      else {
        DAT_40001438 = 900;
        uVar3 = 0xff;
      }
    }
  }
  return uVar3;
}



void reset_selector_move_state(void)

{
  DAT_40001bfe = 0;
  DAT_40001aab = 1;
  DAT_40001bfc = 0;
  move_selector_to_position(0xff);
  return;
}



void shift_selector_supervisor(void)

{
  bool bVar1;
  undefined8 uVar2;
  ulonglong uVar3;
  int iVar4;
  
  bVar1 = false;
  if (((DAT_40001844 & 2) != 0) && ((DAT_40001840 & 2) != 0)) {
    bVar1 = true;
  }
  if (((DAT_40001aa9 != '\0') || (DAT_40001bfc != '\0')) || ((bVar1 && (DAT_40001bfd == '\0')))) {
    uVar2 = 0;
    if ((bVar1) || (DAT_40001aa9 != '\0')) {
      uVar2 = 1;
    }
    selector_position_learned_status = learn_selector_positions(uVar2);
  }
  else {
    if (DAT_400017a4 == '\0') {
      if (DAT_40001ab8 == '\0') {
        DAT_40001ab6 = (ushort)DAT_40008ec0 << 3;
      }
    }
    else if ((DAT_40001ab6 != 0) && (DAT_40001ab6 != -1)) {
      DAT_40001ab6 = DAT_40001ab6 + -1;
    }
    if (((DAT_40001938 == 0) && ((ushort)((ushort)DAT_40008ea9 << 2) < DAT_400015ba)) &&
       (DAT_40008eb6 != '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if (DAT_40002bdc == '\x01') {
      if (DAT_40009008 == '\0') {
        if (DAT_40001c39 == -1) {
          DAT_40001438 = 0xffff;
          DAT_40001ab8 = '\0';
        }
        else if (DAT_40001c39 == '\t') {
          DAT_40001438 = DAT_40002bda;
          DAT_40001ab8 = '\0';
          if ((DAT_40001ab6 == 0) && (shift_position_request_bits == '\x01')) {
            if (bVar1) {
              DAT_40002bda = get_shift_lever_pos_raw___();
            }
            DAT_40001ab6 = -1;
          }
        }
        else if (DAT_40001c39 == '\n') {
          if (DAT_40001ab8 == '\0') {
            DAT_40001438 = DAT_40002bd8;
            DAT_40001ab8 = '\0';
          }
          else {
            if ((DAT_400017a4 != '\0') && (DAT_40001ab8 = DAT_40001ab8 + -1, DAT_40001ab8 == '\0'))
            {
              uVar3 = get_shift_lever_pos_raw___();
              DAT_40001ab9 = int_abs((uVar3 & 0xffff) - (ulonglong)DAT_40001438);
              if (DAT_40001ab9 < DAT_40008ed1) {
                DAT_40001938 = DAT_40001938 | 0xc;
              }
              else {
                DAT_40001938 = DAT_40001938 & 0xfffffff7;
              }
            }
            if ((DAT_40001aac < DAT_40001438) && ((uint)DAT_40002bd8 + (uint)DAT_40008e8b < 900)) {
              DAT_40001438 = DAT_40002bd8 + DAT_40008e8b;
            }
            else if ((DAT_40001438 < DAT_40001aac) &&
                    (100 < (int)((uint)DAT_40001bde - (uint)DAT_40008e8b))) {
              DAT_40001438 = DAT_40001bde - DAT_40008e8b;
            }
          }
          if ((DAT_40001ab6 == 0) && (shift_position_request_bits == '\x02')) {
            if (bVar1) {
              if (DAT_40001aac < DAT_40001438) {
                DAT_40002bd8 = get_shift_lever_pos_raw___();
              }
              else {
                DAT_40001bde = get_shift_lever_pos_raw___();
              }
            }
            DAT_40001ab6 = -1;
            iVar4 = int_abs((ulonglong)DAT_40002bd8 - (ulonglong)DAT_40001bde);
            if ((int)(uint)DAT_40008eac < iVar4) {
              DAT_40001938 = DAT_40001938 | 0x30;
            }
            else {
              DAT_40001938 = DAT_40001938 & 0xffffffdf;
            }
            DAT_40001ab8 = PTR_DAT_40001482._0_1_;
            DAT_400017a4 = '\0';
            DAT_40001c56 = 1;
          }
        }
        else if (DAT_40001c39 == '\0') {
          DAT_40001438 = DAT_40002bd6;
          DAT_40001ab8 = '\0';
          if ((DAT_40001ab6 == 0) && (shift_position_request_bits == '\x04')) {
            if (bVar1) {
              DAT_40002bd6 = get_shift_lever_pos_raw___();
            }
            DAT_40001ab6 = -1;
          }
        }
        else {
          DAT_40001438 = DAT_40002bd4;
          DAT_40001ab8 = '\0';
          if ((DAT_40001ab6 == 0) && (shift_position_request_bits == '\b')) {
            if (bVar1) {
              DAT_40002bd4 = get_shift_lever_pos_raw___();
            }
            DAT_40001ab6 = -1;
          }
        }
      }
      else if (DAT_40009008 == '\x01') {
        DAT_40001438 = DAT_4000900a;
      }
      else if (DAT_40009008 == '\x02') {
        DAT_40001438 = DAT_4000900c;
      }
      else if (DAT_40009008 == '\x03') {
        DAT_40001438 = DAT_4000900e;
      }
      else {
        DAT_40001438 = DAT_4000900e;
        if (DAT_40009008 == '\x04') {
          DAT_40001438 = DAT_40009010;
        }
      }
    }
  }
  return;
}



ulonglong get_shift_lever_pos_raw___(void)

{
  ulonglong uVar1;
  
  if (((DAT_40001678 & 0x1000000) == 0) && ((DAT_40001678 & 0x2000000) == 0)) {
    DAT_40001aba = 1000 - (short)((ulonglong)DAT_40002358 / 10);
    uVar1 = (ulonglong)DAT_40001aba;
  }
  else if (((DAT_40001678 & 0x800000) == 0) && ((DAT_40001678 & 0x2000000) == 0)) {
    uVar1 = (ulonglong)DAT_40002374 / 10 & 0xffff;
  }
  else {
    uVar1 = 0xffff;
  }
  return uVar1;
}



undefined8 shift_lever_pos_decoder___(void)

{
  ushort uVar2;
  undefined8 uVar1;
  
  uVar2 = get_shift_lever_pos_raw___();
  if (uVar2 == 0xffff) {
    uVar1 = 0xff;
  }
  else {
    if ((shift_position_request_bits & 0xf) == 1) {
      if (((int)((uint)DAT_40002bda - (uint)DAT_40009012) <= (int)(uint)uVar2) &&
         ((uint)uVar2 <= (uint)DAT_40002bda + (uint)DAT_40009012)) {
        return 9;
      }
    }
    else if ((shift_position_request_bits & 0xf) == 2) {
      if (((int)((uint)DAT_40002bd8 - (uint)DAT_40009012) <= (int)(uint)uVar2) &&
         ((uint)uVar2 <= (uint)DAT_40002bd8 + (uint)DAT_40009012)) {
        return 10;
      }
    }
    else if ((shift_position_request_bits & 0xf) == 4) {
      if (((int)((uint)DAT_40002bd6 - (uint)DAT_40009012) <= (int)(uint)uVar2) &&
         ((uint)uVar2 <= (uint)DAT_40002bd6 + (uint)DAT_40009012)) {
        return 0;
      }
    }
    else if ((((shift_position_request_bits & 0xf) == 8) &&
             ((int)((uint)DAT_40002bd4 - (uint)DAT_40009012) <= (int)(uint)uVar2)) &&
            ((uint)uVar2 <= (uint)DAT_40002bd4 + (uint)DAT_40009012)) {
      return 0xfe;
    }
    if (((int)(uint)uVar2 < (int)((uint)DAT_40002bda - (uint)DAT_40009012)) ||
       ((uint)DAT_40002bda + (uint)DAT_40009012 < (uint)uVar2)) {
      if (((int)(uint)uVar2 < (int)((uint)DAT_40002bd8 - (uint)DAT_40009012)) ||
         ((uint)DAT_40002bd8 + (uint)DAT_40009012 < (uint)uVar2)) {
        if (((int)(uint)uVar2 < (int)((uint)DAT_40002bd6 - (uint)DAT_40009012)) ||
           ((uint)DAT_40002bd6 + (uint)DAT_40009012 < (uint)uVar2)) {
          if (((int)(uint)uVar2 < (int)((uint)DAT_40002bd4 - (uint)DAT_40009012)) ||
             ((uint)DAT_40002bd4 + (uint)DAT_40009012 < (uint)uVar2)) {
            uVar1 = 0xff;
          }
          else {
            uVar1 = 0xfe;
          }
        }
        else {
          uVar1 = 0;
        }
      }
      else {
        uVar1 = 10;
      }
    }
    else {
      uVar1 = 9;
    }
  }
  return uVar1;
}



ulonglong detect_torque_transient(u16_torque_nm torque)

{
  uint uVar2;
  ulonglong uVar1;
  
  uVar2 = DAT_40001ae4 * (0x100 - (uint)DAT_40008f24);
  DAT_40001ae4 = ((int)uVar2 >> 8) + (uint)((int)uVar2 < 0 && (uVar2 & 0xff) != 0) +
                 (int)(short)torque * (uint)DAT_40008f24;
  DAT_40001aea = (short)(DAT_40001ae4 >> 8) +
                 (ushort)((int)DAT_40001ae4 < 0 && (DAT_40001ae4 & 0xff) != 0);
  DAT_40001ae8 = int_abs((longlong)DAT_40001aea - (longlong)(short)torque);
  uVar1 = (longlong)DAT_40001ae8 ^ (ulonglong)DAT_40008f52;
  return ((longlong)((int)uVar1 >> 1) - (uVar1 & (longlong)DAT_40001ae8) << 0x20) >> 0x3f;
}



void detect_trans_slip(void)

{
  byte bVar1;
  short sVar2;
  longlong lVar3;
  int iVar4;
  
  if (((((ips_gear_cur == (GEAR_INVALID8|GEAR_INVALID7)) || (4 < (byte)(ips_gear_cur - GEAR_2))) ||
       (DAT_4000148d != -1)) ||
      ((output_shaft_rpm < CAL_slip_output_speed_min || (input_shaft_rpm < CAL_slip_input_speed_min)
       ))) || (input_shaft_load <= DAT_4000916a)) {
    DAT_40001c54 = 0;
  }
  else {
    lVar3 = (longlong)trans_slip_metric + (longlong)DAT_40001c54 * 0x31;
    iVar4 = (int)lVar3;
    bVar1 = DAT_40001c50 + (char)lVar3 + (char)(iVar4 / 0x32) * -0x32;
    sVar2 = (short)((ulonglong)lVar3 >> 0x10) >> 0xf;
    DAT_40001c54 = (((short)(iVar4 / 0x32) + sVar2) -
                   ((short)((short)(iVar4 / 0x320000) + sVar2) >> 0xf)) + bVar1 / 0x32;
    DAT_40001c50 = bVar1 % 0x32;
    if (trans_slip_metric < DAT_40001c52) {
      DAT_4000149c = 3;
    }
    else if (DAT_4000149c == 0) {
      DAT_40001c52 = trans_slip_metric;
    }
    else {
      DAT_4000149c = DAT_4000149c + -1;
    }
    if ((((int)(uint)DAT_4000e488 < (int)DAT_40001c54) ||
        (sVar2 = int_abs(DAT_40001c52), DAT_4000e48a < sVar2)) && (DAT_40001aec == 0)) {
      record_shift_diag_sample();
      DAT_4000343a = DAT_4000343a + 1;
      DAT_40001aec = 400;
    }
    if (DAT_4000e4b5 <= DAT_4000343a) {
      trans_slip_status_flags = trans_slip_status_flags | 1;
      DAT_4000343a = 0;
    }
  }
  if ((DAT_40001aec < 2) || (DAT_4000904f == '\0')) {
    if (DAT_40001aec != 0) {
      DAT_40001ba1 = 10;
      trans_slip_status_flags = trans_slip_status_flags & 0xf9;
      DAT_40001aec = DAT_40001aec - 1;
      DAT_40001c52 = 0;
    }
  }
  else {
    if (DAT_4000904f == '\x01') {
      trans_slip_status_flags = trans_slip_status_flags | 4;
    }
    else if (DAT_4000904f == '\x02') {
      trans_slip_status_flags = trans_slip_status_flags | 2;
    }
    DAT_40001aec = DAT_40001aec - 1;
  }
  return;
}



void shift_control_task(void)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  byte bVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  enum_t6e_gear eVar9;
  uint uVar8;
  char cVar12;
  short sVar11;
  int iVar10;
  longlong lVar13;
  uint local_20 [8];
  
  local_20[0] = 0;
  local_20[1] = 0;
  DAT_40001afa = detect_torque_transient(engine_torque);
  detect_trans_slip();
  enum_t6e_gear_40001afd = ips_gear_cur;
  if ((((((DAT_4000903a < input_shaft_load) && (input_shaft_load < DAT_40009039)) &&
        (10 < vehicle_speed)) && (DAT_40001afa == '\0')) &&
      (((CAL_shift_adapt_mode == '\x01' || (CAL_shift_adapt_mode == '\x03')) &&
       ((DAT_40009030 < oil_temp_unknown &&
        ((oil_temp_unknown < DAT_40009026 && ((DAT_40001678 & 2) == 0)))))))) &&
     (((DAT_40001678 & 1) == 0 &&
      (((shift_adapt_phase_unknown2 == '\x05' || (shift_adapt_phase_unknown2 == '\x01')) &&
       (shift_closed_loop_active == false)))))) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  DAT_40001b95 = '\0';
  if ((bVar1) || (DAT_40001af6 != '\0')) {
    DAT_40001b95 = '\x01';
  }
  bVar1 = DAT_40001af4 == 0;
  DAT_40001af4 = DAT_40001af4 + -1;
  if (bVar1) {
    DAT_40001af4 = 0;
  }
  if ((gear_request == ips_gear_cur) && (DAT_40001b95 == '\0')) {
    bVar4 = DAT_4000149e;
    if (((DAT_4000148d == 0xff) && (DAT_40001b94 == '\0')) &&
       (DAT_4000148d = select_slip_learn_element
                                 (ips_gear_cur,slip_learn_status_flags_gear6,DAT_40001b97,
                                  DAT_40001af4,input_shaft_load), bVar4 = DAT_4000148d,
       DAT_4000148d == 0xff)) {
      bVar4 = DAT_4000149e;
    }
    DAT_4000149e = bVar4;
    lVar13 = 0;
  }
  else {
    DAT_40001b94 = -1;
    lVar13 = 1;
  }
  if (DAT_4000148d == 0xff) {
    cVar12 = DAT_40001b94 + -1;
    if (DAT_40001b94 == '\0') {
      cVar12 = DAT_40001b94;
    }
  }
  else {
    sVar11 = DAT_400014a0;
    if ((DAT_4000148d & 0x10) == 0) {
      sVar11 = DAT_40001af4;
    }
    DAT_40001af4 = sVar11;
    learn_clutch_slip_point(&DAT_4000148d,lVar13);
    if ((DAT_4000148d == 0xff) || (lVar13 != 0)) {
      DAT_40001b96 = '2';
    }
    DAT_40001af7 = 0;
    DAT_40001af8 = 0;
    DAT_40001af9 = 1;
    DAT_40001c3a = 0;
    cVar12 = DAT_40001b94;
  }
  DAT_40001b94 = cVar12;
  eVar9 = gear_request;
  bVar1 = DAT_40001b96 == '\0';
  DAT_40001b96 = DAT_40001b96 + -1;
  if (bVar1) {
    DAT_40001b96 = '\0';
  }
  gear_request = select_target_gear();
  if (eVar9 == gear_request) {
    eVar9 = DAT_40001ad4;
  }
  DAT_40001ad4 = eVar9;
  compute_shift_slip();
  if (((DAT_40001b96 == '\0') && ((DAT_40001678 & 2) == 0)) && ((DAT_40001678 & 1) == 0)) {
    shift_gear_state_machine(gear_request);
  }
  actuator_output_controller();
  if (((DAT_40001678 & 0x200) == 0) && ((DAT_400015b8 & 1) != 0)) {
    sVar11 = FUN_00056164();
    if (sVar11 != 0x3fff) {
      vehicle_speed____ = FUN_00056164();
    }
    sVar11 = FUN_00056180();
    if ((sVar11 == 0x3fff) || (sVar11 = FUN_0005619c(), sVar11 == 0x3fff)) {
      DAT_40001708 = 0;
      DAT_4000170a = 0;
    }
    else {
      DAT_4000170a = FUN_00056180();
      DAT_40001708 = FUN_0005619c();
    }
    DAT_40001706 = FUN_000561b8();
    DAT_40001704 = FUN_000561d4();
    if (vehicle_speed____ / 100 < 0x100) {
      vehicle_speed = (u8_speed_kph)(vehicle_speed____ / 100);
    }
    else {
      vehicle_speed = 0xff;
    }
    shift_adaptation_learn_gate = vehicle_speed____;
  }
  else {
    if ((DAT_40001678 & 4) == 0) {
      uVar2 = ((uint)output_shaft_rpm * 10000) / (uint)DAT_40008f7c;
      shift_adaptation_learn_gate = (u16_rspeed_rpm)uVar2;
      if (shift_adaptation_learn_gate < 0x639d) {
        vehicle_speed = (u8_speed_kph)((uVar2 & 0xffff) / 100);
      }
      else {
        vehicle_speed = 0xff;
      }
    }
    else {
      vehicle_speed = '\0';
    }
    DAT_4000170a = shift_adaptation_learn_gate;
    DAT_40001708 = shift_adaptation_learn_gate;
    DAT_40001706 = shift_adaptation_learn_gate;
    DAT_40001704 = shift_adaptation_learn_gate;
  }
  vehicle_speed____ = shift_adaptation_learn_gate;
  if (DAT_40002bdc == '\0') {
    flexcan_a_tx_c7((int)(uint)DAT_40001552 >> 8,DAT_40001552 & 0xff,(int)(uint)input_shaft_rpm >> 8
                    ,input_shaft_rpm & 0xff,DAT_40001be1,0xff,DAT_40001b9e,DAT_40001b9f);
  }
  else {
    flexcan_a_tx_c7((int)(uint)DAT_40001552 >> 8,DAT_40001552 & 0xff,(int)(uint)input_shaft_rpm >> 8
                    ,input_shaft_rpm & 0xff,DAT_40001be1,gear_request,DAT_40001b9e,DAT_40001b9f);
  }
  DAT_40001aee = DAT_40001aee ^ 1;
  if (DAT_40001aee == 0) {
    if ((DAT_40001678 & 1) == 0) {
      sVar11 = get_shift_lever_pos_raw___();
      if (sVar11 == -1) {
        DAT_40001af1 = 0xf;
        if ((shift_position_request_bits & 0xf) == 1) {
          DAT_40001af3 = DAT_0008daf1;
        }
        else if ((shift_position_request_bits & 0xf) == 2) {
          DAT_40001af3 = DAT_0008daf2;
        }
        else if ((shift_position_request_bits & 0xf) == 4) {
          DAT_40001af3 = DAT_0008dae8;
        }
        else if ((shift_position_request_bits & 0xf) == 8) {
          DAT_40001af3 = DAT_0008dae9;
        }
        else {
          DAT_40001af3 = 0xf;
        }
      }
      else if ((DAT_40001678 & 2) == 0) {
        if (((byte)(ips_gear_cur - GEAR_1) < 8) ||
           (((ips_gear_cur == NEUTRAL && (DAT_40001c39 == '\0')) ||
            ((byte)(ips_gear_cur - GEAR_INVALID9) < 2)))) {
          DAT_40001af1 = (&DAT_0008dae8)[ips_gear_cur];
          DAT_40001af3 = DAT_40001af1;
        }
        else if ((ips_gear_cur == (GEAR_INVALID8|GEAR_INVALID7)) &&
                (((byte)(gear_request - GEAR_1) < 8 || (gear_request == GEAR_REV)))) {
          if ((((((shift_mode_word & 0xf) == 5) || ((shift_mode_word & 0xf) == 10)) &&
               (shift_substage == '\x01')) || (shift_mode_word == 0)) &&
             (((byte)(shift_from_gear - GEAR_1) < 8 && (gear_request != GEAR_REV)))) {
            DAT_40001af1 = (&DAT_0008dae8)[shift_from_gear];
            DAT_40001af3 = DAT_40001af1;
            if (DAT_40001ace != '\0') {
              DAT_40001af3 = (&DAT_0008dae8)[gear_request];
            }
          }
          else if ((byte)(shift_from_gear - GEAR_1) < 8) {
            DAT_40001af1 = (&DAT_0008dae8)[shift_from_gear];
            DAT_40001af3 = (&DAT_0008dae8)[gear_request];
          }
          else {
            cVar12 = shift_lever_pos_decoder___();
            if ((cVar12 == -2) || (cVar12 = shift_lever_pos_decoder___(), cVar12 == '\n')) {
              DAT_40001af1 = (&DAT_0008dae8)[gear_request];
              DAT_40001af3 = (&DAT_0008dae8)[gear_request];
            }
            else {
              DAT_40001af1 = (&DAT_0008dae8)[shift_from_gear];
              DAT_40001af3 = (&DAT_0008dae8)[gear_request];
            }
          }
        }
        else if (ips_gear_cur == NEUTRAL) {
          if (DAT_40001c39 == '\t') {
            DAT_40001af1 = DAT_0008daf1;
          }
          else if (DAT_40001c39 == '\n') {
            DAT_40001af1 = DAT_0008daf2;
          }
          else if ((byte)(gear_request - GEAR_1) < 8) {
            DAT_40001af1 = (&DAT_0008dae8)[gear_request];
          }
          DAT_40001af3 = DAT_40001af1;
        }
      }
      else {
        if (DAT_40001c39 == '\t') {
          if (gear_request == GEAR_INVALID9) {
            DAT_40001af1 = DAT_0008daf1;
          }
        }
        else if (DAT_40001c39 == '\n') {
          if (gear_request == GEAR_REV) {
            DAT_40001af1 = DAT_0008daf2;
          }
        }
        else if (DAT_40001c39 == '\0') {
          if (gear_request == NEUTRAL) {
            DAT_40001af1 = DAT_0008dae8;
          }
        }
        else {
          DAT_40001af1 = DAT_0008daeb;
          if (DAT_40001a44 == '\x05') {
            DAT_40001af1 = DAT_0008daed;
          }
        }
        DAT_40001af3 = DAT_40001af1;
      }
    }
    else {
      DAT_40001af1 = 0xf;
      DAT_40001af3 = 2;
    }
    uVar5 = DAT_40001af1 & 0xf;
    uVar6 = ((&DAT_0008dae8)[gear_request] & 0xf) << 4;
    uVar2 = (uint)(((ulonglong)(LZCOUNT(ips_gear_cur - 0xf) << 0x20) >> 0x25) << 8);
    uVar7 = (DAT_40001af3 & 0xf) << 9;
    if (((paddle_request & 1) == 0) || (DAT_40001ace == '\0')) {
      if (((paddle_request & 2) == 0) || (DAT_40001ace == '\0')) {
        DAT_40001af2 = 0;
      }
      else {
        DAT_40001af2 = 2;
      }
    }
    else {
      DAT_40001af2 = 1;
    }
    uVar3 = (uint)DAT_40001af2 << 0xd;
    uVar8 = uVar3 | uVar7 | uVar2 | uVar6 | uVar5 | local_20[0] & 0xffff8000;
    if (((((DAT_40001840 & 0x20000) == 0) || ((DAT_40001844 & 0x20000) == 0)) &&
        ((DAT_40001666 & 0x100) == 0)) && (DAT_40001633 != '\x01')) {
      if (DAT_4000167c == '\x01') {
        bVar1 = DAT_40001afc == '\0';
        DAT_40001afc = DAT_40001afc + -1;
        if (bVar1) {
          DAT_40001afc = '\0';
        }
        if (DAT_40001afc == '\0') {
          DAT_40001afb = DAT_40001afb ^ 1;
          DAT_40001afc = DAT_4000e4c9;
        }
        if (DAT_40001afb == 0) {
          if ((DAT_40001844 & 0x20000) == 0) {
            uVar8 = uVar3 | uVar7 | uVar2 | uVar6 | uVar5 | local_20[0] & 0xffff0000;
          }
        }
        else {
          uVar8 = uVar3 | uVar7 | uVar2 | uVar6 | uVar5 | local_20[0] & 0xffff0000 | 0x8000;
        }
      }
      else {
        if ((DAT_40001844 & 0x20000) == 0) {
          uVar8 = uVar3 | uVar7 | uVar2 | uVar6 | uVar5 | local_20[0] & 0xffff0000;
        }
        local_20[0] = uVar8;
        DAT_40001afc = DAT_4000e4c9;
        uVar8 = local_20[0];
      }
    }
    else {
      DAT_40001afc = DAT_4000e4c9;
      uVar8 = uVar3 | uVar7 | uVar2 | uVar6 | uVar5 | local_20[0] & 0xffff0000 | 0x8000;
    }
    local_20[0] = uVar8;
    if (DAT_4000167c == '\0') {
      local_20[0] = local_20[0] & 0xffefffff;
    }
    else {
      local_20[0] = local_20[0] & 0xffefffff | 0x100000;
    }
    if ((DAT_40001636 & 0x10) == 0) {
      local_20[0] = local_20[0] & 0xff7fffff;
    }
    else {
      local_20[0] = local_20[0] & 0xff7fffff | 0x800000;
    }
    local_20[0] = local_20[0] & 0xfff8ffff;
    if ((((DAT_40001ac7 & 1) == 0) && ((DAT_40001678 & 1) == 0)) &&
       (sVar11 = get_shift_lever_pos_raw___(), sVar11 != -1)) {
      local_20[0] = local_20[0] & 0xfff7ffff;
    }
    else {
      local_20[0] = local_20[0] & 0xfff7ffff | 0x80000;
    }
    iVar10 = 0;
    if (DAT_40001c38 == '\x01') {
      iVar10 = 2;
    }
    local_20[0] = iVar10 << 0x15 | local_20[0] & 0xff9fffff;
    FUN_00055de4(local_20);
  }
  else {
    if (((DAT_40001678 & 0x40000000) == 0) && ((DAT_40001678 & 0x10) == 0)) {
      DAT_40001aca = DAT_40001aca & 0xfe;
    }
    else {
      DAT_40001aca = DAT_40001aca | 1;
    }
    if (((DAT_40001666 & 8) == 0) &&
       (((DAT_40001840 & 0x80000) == 0 || ((DAT_40001844 & 0x80000) == 0)))) {
      if ((DAT_40001844 & 0x80000) == 0) {
        DAT_40001668 = DAT_40001668 & 0xfe;
      }
    }
    else {
      DAT_40001668 = DAT_40001668 | 1;
    }
    bVar4 = DAT_40001668 | 2;
    if ((DAT_40001666 & 0x40) == 0) {
      bVar4 = DAT_40001668 & 0xfd;
    }
    DAT_40001668 = bVar4 | 4;
    if ((DAT_40001666 & 0x800) == 0) {
      DAT_40001668 = bVar4 & 0xfb;
    }
    flexcan_a_tx_250(DAT_40001aca,DAT_40001490,DAT_40001668,DAT_40001c71,
                     ((ulonglong)DAT_40008f81 & 0xf) << 4 | 6,oil_temp_unknown,tc_k_factor,0);
  }
  if (DAT_40001aef != '\0') {
    reset_shift_counters();
    DAT_40001aef = '\0';
  }
  if (DAT_40001af0 != '\0') {
    reset_shift_profile_adapt_service();
    DAT_40001af0 = '\0';
  }
  if (DAT_40001a88 == '\0') {
    DAT_40001ac7 = DAT_40001ac7 & 0xfe;
  }
  else {
    DAT_40001ac7 = DAT_40001ac7 | 1;
    DAT_40001a88 = DAT_40001a88 + -1;
  }
  pack_shift_position_request_bits();
  DAT_40001bfa = shift_lever_pos_decoder___();
  if ((paddle_request != 1) && (DAT_40001bb0 = DAT_40008f66, DAT_40001c38 == '\0')) {
    DAT_40001bb0 = DAT_40008f2b;
  }
  return;
}



void update_slip_learn_status_flags(void)

{
  int iVar1;
  byte bVar2;
  
  iVar1 = 0;
  for (bVar2 = 0; bVar2 < 6; bVar2 = bVar2 + 1) {
    iVar1 = iVar1 + (&DAT_40002ba4)[bVar2];
  }
  if (iVar1 == (iVar1 / (int)(uint)DAT_400090aa) * (uint)DAT_400090aa) {
    slip_learn_status_flags_gear6 = DAT_40001c18 ^ 0xff;
  }
  return;
}



void update_actuator_pwm_outputs(void)

{
  bool bVar1;
  short sVar4;
  uint uVar2;
  byte bVar5;
  int iVar3;
  short sVar14;
  ulonglong uVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  ulonglong uVar9;
  ulonglong uVar10;
  ulonglong uVar11;
  ulonglong uVar12;
  ulonglong uVar13;
  char cVar15;
  byte bVar16;
  
  bVar16 = DAT_4000148d;
  DAT_400058d0 = DAT_40001712;
  sVar14 = DAT_40001712;
  sVar4 = DAT_40001712;
  for (bVar5 = 0xe; bVar5 != 0; bVar5 = bVar5 - 1) {
    (&DAT_400058d0)[bVar5] = (&DAT_400058d0)[bVar5 - 1];
    if (sVar4 < (&DAT_400058d0)[bVar5]) {
      sVar4 = (&DAT_400058d0)[bVar5];
    }
    if ((&DAT_400058d0)[bVar5] < sVar14) {
      sVar14 = (&DAT_400058d0)[bVar5];
    }
  }
  DAT_40001c4e = sVar4 - sVar14;
  DAT_40001c18 = DAT_40001c18 | DAT_40002ba1 | slip_learn_status_flags_gear6;
  update_slip_learn_status_flags();
  if (((DAT_4000163a == '\x01') && (shift_adapt_inhibit != '\0')) && (tach_rpm == 0)) {
    shift_adapt_inhibit = '\x03';
    DAT_4000163a = '\x02';
    cVar15 = DAT_4000163a;
  }
  else {
    cVar15 = DAT_4000163a;
    if ((DAT_4000163a == '\x01') && (cVar15 = '\x02', tach_rpm == 0)) {
      cVar15 = DAT_4000163a;
    }
  }
  DAT_4000163a = cVar15;
  DAT_40001bea = DAT_40008f5d;
  if ((paddle_shift_flags & 0x80) != 0) {
    DAT_40001bea = DAT_40008f5c;
  }
  if (auto_mode_active == false) {
    cVar15 = '\0';
    if (DAT_40001b09 == '\0') {
      cVar15 = DAT_40001a8a;
    }
    DAT_40001b09 = 0;
    DAT_40001a8a = cVar15;
    if ((((driver_input_flags[1] & 4) != 0) && (overrev_shift_threshold < tach_rpm)) &&
       ((cruise_status_flags & 4) == 0)) {
      DAT_40001a8a = '\0';
    }
    if (((cruise_status_flags & 8) != 0) && ((DAT_40001aff & 8) == 0)) {
      DAT_40001a8a = '\x05';
    }
  }
  else {
    if ((DAT_40001b09 == '\0') && (DAT_40001a8a != '\0')) {
      DAT_40001a8a = DAT_40008f7f;
    }
    DAT_40001b09 = 1;
  }
  if ((((DAT_40008f61 != -1) && (auto_mode_active == false)) ||
      ((DAT_40008f7f != -1 && (auto_mode_active != false)))) &&
     ((DAT_40001a8a != '\0' && (shift_adapt_inhibit == '\0')))) {
    DAT_40001a8a = DAT_40001a8a + -1;
  }
  DAT_40001aff = cruise_status_flags;
  if (paddle_request == '\b') {
    if (DAT_40001afe == '\0') {
      DAT_40001ad5 = 1;
    }
    else {
      DAT_40001afe = DAT_40001afe + -1;
    }
  }
  else {
    DAT_40001ad5 = 0;
    DAT_40001afe = DAT_40008f67;
  }
  if ((paddle_request == '\x01') && (DAT_40001a8e == '\0')) {
    if (DAT_40001bb0 == '\0') {
      DAT_40001ad6 = 1;
      upshift_armed = false;
    }
    else {
      DAT_40001bb0 = DAT_40001bb0 + -1;
    }
  }
  else {
    DAT_40001ad6 = 0;
  }
  bVar1 = DAT_40001a8b == '\0';
  DAT_40001a8b = DAT_40001a8b + -1;
  if (bVar1) {
    DAT_40001a8b = '\0';
  }
  bVar1 = DAT_40001a8c == '\0';
  DAT_40001a8c = DAT_40001a8c + -1;
  if (bVar1) {
    DAT_40001a8c = '\0';
  }
  eTPU_calculate_and_set_channel_value(0x13,((uint)DAT_40001bee * 10000) / 0xff);
  eTPU_calculate_and_set_channel_value(0x14,((uint)DAT_40001bed * 10000) / 0xff);
  uVar2 = (uint)DAT_40009002 * (0xff - (uint)DAT_40001bec);
  pwm_set_dutycycle((longlong)((int)uVar2 / 0xff + ((int)uVar2 >> 0x1f)) +
                    (ulonglong)(uVar2 >> 0x1f),7);
  uVar2 = (uint)DAT_40009002 * (0xff - (uint)DAT_40001beb);
  pwm_set_dutycycle((longlong)((int)uVar2 / 0xff + ((int)uVar2 >> 0x1f)) +
                    (ulonglong)(uVar2 >> 0x1f),6);
  eTPU_calculate_and_set_channel_value(0x1e,(int)((uint)DAT_40001bea * 10000) >> 8);
  DAT_40001b98 = DAT_40002ba1;
  DAT_40001b00 = DAT_40002bd4;
  DAT_40001b02 = DAT_40002bd6;
  DAT_40001b04 = DAT_40002bd8;
  DAT_40001b06 = DAT_40002bda;
  bVar1 = DAT_40001c82 == '\0';
  DAT_40001c82 = DAT_40001c82 + -1;
  if (bVar1) {
    DAT_40001c82 = '\0';
  }
  bVar1 = DAT_40001c83 == '\0';
  DAT_40001c83 = DAT_40001c83 + -1;
  if (bVar1) {
    DAT_40001c83 = '\0';
  }
  bVar1 = DAT_40001c78 == '\0';
  DAT_40001c78 = DAT_40001c78 + -1;
  if (bVar1) {
    DAT_40001c78 = '\0';
  }
  DAT_400014a2 = DAT_400014a2 + -1;
  if (DAT_400014a2 == '\0') {
    DAT_400014a2 = '\n';
    for (bVar5 = 0; bVar5 < 4; bVar5 = bVar5 + 1) {
      if ((int)(short)(&solenoid_SL_demand)[bVar5 + 1] == (int)((uint)DAT_4000902c * 10000) >> 8) {
        if ((engine_running == '\0') && ((&DAT_40001498)[bVar5] != -1)) {
          (&DAT_40001498)[bVar5] = (&DAT_40001498)[bVar5] + '\x01';
        }
        if ((&DAT_40001494)[bVar5] != -1) {
          (&DAT_40001494)[bVar5] = (&DAT_40001494)[bVar5] + '\x01';
        }
      }
    }
  }
  if (DAT_40001b0a != 0) {
    if ((DAT_40001b0a & 0xf0) != 0) {
      DAT_40002ba1 = DAT_40002ba1 | 0xf0;
      slip_learn_status_flags_gear6 = slip_learn_status_flags_gear6 | 0xf0;
      shift_adapt_inhibit = DAT_40009029;
    }
    if ((DAT_40001b0a & 0xf) != 0) {
      DAT_40002ba1 = DAT_40002ba1 | 0xf;
      slip_learn_status_flags_gear6 = slip_learn_status_flags_gear6 | 0xf;
      shift_adapt_inhibit = DAT_40009029;
    }
    DAT_40001b0a = 0;
  }
  if (DAT_40001865 != 0) {
    if ((DAT_40001865 & 0xf0) != 0) {
      if (DAT_40009029 == '\x01') {
        shift_adapt_inhibit = '\x01';
        DAT_40002ba1 = DAT_40002ba1 | 0xf0;
        slip_learn_status_flags_gear6 = slip_learn_status_flags_gear6 | 0xf0;
      }
      else if (DAT_40009029 == '\x02') {
        shift_adapt_inhibit = '\x02';
      }
      else {
        shift_adapt_inhibit = '\x01';
        DAT_40002ba1 = DAT_40002ba1 | 0xf0;
        slip_learn_status_flags_gear6 = slip_learn_status_flags_gear6 | 0xf0;
      }
    }
    DAT_40001865 = 0;
    DAT_40001864 = 1;
  }
  if (shift_adapt_inhibit == '\x01') {
    if ((DAT_40009030 < oil_temp_unknown) && (oil_temp_unknown < DAT_40009026)) {
      if (bVar16 == 0xff) {
        if (DAT_40001b94 == '\0') {
          DAT_4000148e = 0xff;
          DAT_4000148f = 0xff;
          if (ips_gear_cur == GEAR_2) {
            if (DAT_40001b08 == '\0') {
              DAT_40001b08 = DAT_400014a4;
              if (DAT_40001ba1 == 3) {
                DAT_40001ba1 = 4;
              }
              else {
                DAT_40001ba1 = 3;
              }
            }
          }
          else if (ips_gear_cur == GEAR_3) {
            if (((slip_learn_status_flags_gear6 & 1) == 0) ||
               ((slip_learn_status_flags_gear6 & 0xf8) == 0)) {
              if ((slip_learn_status_flags_gear6 & 0xf8) == 0) {
                if (DAT_40001b08 == '\0') {
                  DAT_40001b08 = DAT_400014a4;
                  if (DAT_40001ba1 == 5) {
                    DAT_40001ba1 = 6;
                  }
                  else {
                    DAT_40001ba1 = 5;
                  }
                }
              }
              else if (DAT_40001b08 == '\0') {
                DAT_40001b08 = DAT_400014a4;
                if (DAT_40001ba1 == 3) {
                  DAT_40001ba1 = 4;
                }
                else {
                  DAT_40001ba1 = 3;
                }
              }
            }
            else if (DAT_40001b08 == '\0') {
              DAT_40001b08 = DAT_400014a4;
              if (DAT_40001ba1 == 1) {
                DAT_40001ba1 = 2;
              }
              else {
                DAT_40001ba1 = 1;
              }
            }
          }
          else if (ips_gear_cur == GEAR_4) {
            if (((slip_learn_status_flags_gear6 & 0xe0) == 0) ||
               ((slip_learn_status_flags_gear6 & 7) == 0)) {
              if ((slip_learn_status_flags_gear6 & 0xe0) == 0) {
                if (DAT_40001b08 == '\0') {
                  DAT_40001b08 = DAT_400014a4;
                  if (DAT_40001ba1 == 5) {
                    DAT_40001ba1 = 6;
                  }
                  else {
                    DAT_40001ba1 = 5;
                  }
                }
              }
              else if (DAT_40001b08 == '\0') {
                DAT_40001b08 = DAT_400014a4;
                if (DAT_40001ba1 == 3) {
                  DAT_40001ba1 = 4;
                }
                else {
                  DAT_40001ba1 = 3;
                }
              }
            }
            else if (DAT_40001b08 == '\0') {
              DAT_40001b08 = DAT_400014a4;
              if (DAT_40001ba1 == 1) {
                DAT_40001ba1 = 2;
              }
              else {
                DAT_40001ba1 = 1;
              }
            }
          }
          else if (ips_gear_cur == GEAR_5) {
            if (((slip_learn_status_flags_gear6 & 0x80) == 0) ||
               ((slip_learn_status_flags_gear6 & 0x1f) == 0)) {
              if ((slip_learn_status_flags_gear6 & 0x80) == 0) {
                if (DAT_40001b08 == '\0') {
                  DAT_40001b08 = DAT_400014a4;
                  if (DAT_40001ba1 == 5) {
                    DAT_40001ba1 = 6;
                  }
                  else {
                    DAT_40001ba1 = 5;
                  }
                }
              }
              else if (DAT_40001b08 == '\0') {
                DAT_40001b08 = DAT_400014a4;
                if (DAT_40001ba1 == 3) {
                  DAT_40001ba1 = 4;
                }
                else {
                  DAT_40001ba1 = 3;
                }
              }
            }
            else if (DAT_40001b08 == '\0') {
              DAT_40001b08 = DAT_400014a4;
              if (DAT_40001ba1 == 1) {
                DAT_40001ba1 = 2;
              }
              else {
                DAT_40001ba1 = 1;
              }
            }
          }
          else if (ips_gear_cur == GEAR_6) {
            if (DAT_40001b08 == '\0') {
              DAT_40001b08 = DAT_400014a4;
              if (DAT_40001ba1 == 5) {
                DAT_40001ba1 = 6;
              }
              else {
                DAT_40001ba1 = 5;
              }
            }
          }
          else if (DAT_40001b08 == '\0') {
            DAT_40001b08 = DAT_400014a4;
            if (DAT_40001ba1 == 3) {
              DAT_40001ba1 = 4;
            }
            else {
              DAT_40001ba1 = 3;
            }
          }
        }
        else {
          DAT_4000148e = 0xff;
          DAT_4000148f = 0xff;
          if (vehicle_speed < 3) {
            DAT_40001ba1 = 0;
          }
          else if ((DAT_4000903a < input_shaft_load) && (10 < vehicle_speed)) {
            if (DAT_40009039 <= input_shaft_load) {
              DAT_40001ba1 = 8;
            }
          }
          else {
            DAT_40001ba1 = 7;
          }
        }
      }
      else {
        if ((byte)(&DAT_400023d6)[(uint)bVar16 * 0xe0] < CAL_shift_profile_adapt_default[0]) {
          bVar5 = 0x28;
          DAT_4000148e = (&DAT_400023d6)[(uint)bVar16 * 0xe0];
          DAT_4000148f = CAL_shift_profile_adapt_default[0];
        }
        else if (bVar16 < 5) {
          bVar5 = 0x48;
          DAT_4000148e = (&DAT_400023d8)[(uint)bVar16 * 0xe0];
          DAT_4000148f = CAL_shift_profile_adapt_default[0] + 0xff;
        }
        else {
          bVar5 = 0x58;
          DAT_4000148e = (&DAT_400023d9)[(uint)bVar16 * 0xe0];
          DAT_4000148f = CAL_shift_profile_adapt_default[0];
        }
        DAT_40001ad3 = bVar5 + DAT_400014a3;
        DAT_40001ad2 = bVar5 - DAT_400014a3;
        if ((uint)bVar5 + (uint)DAT_400014a3 < (uint)input_shaft_load) {
          DAT_40001ba1 = 8;
        }
        else if ((int)(uint)input_shaft_load < (int)((uint)bVar5 - (uint)DAT_400014a3)) {
          DAT_40001ba1 = 7;
        }
        else {
          DAT_40001ba1 = 9;
        }
      }
    }
    else {
      DAT_4000148e = 0xff;
      DAT_4000148f = 0xff;
      DAT_40001ba1 = 0;
    }
    if (DAT_40001b08 != '\0') {
      DAT_40001b08 = DAT_40001b08 + -1;
    }
  }
  else if (shift_adapt_inhibit == '\x02') {
    switch(DAT_40001bdd) {
    case 0:
      init_clutch_slip_adaptation();
      DAT_40002ba1 = 0xff;
      slip_learn_status_flags_gear6 = 0xff;
      if (ips_gear_cur == GEAR_2) {
        DAT_40001b0b = '\0';
        DAT_40001bdd = 1;
      }
      else {
        if (GEAR_2 < ips_gear_cur) {
          DAT_40001b0b = '\x02';
        }
        if (ips_gear_cur < GEAR_2) {
          DAT_40001b0b = '\x01';
        }
      }
      break;
    case 1:
      if ((ips_gear_cur == GEAR_3) && (2 < DAT_400023e4)) {
        DAT_40001b0b = '\0';
        DAT_40001bdd = 2;
      }
      else if ((ips_gear_cur == GEAR_2) && (DAT_400023e4 < 3)) {
        DAT_40001b0b = '\0';
      }
      else {
        if (GEAR_3 < ips_gear_cur) {
          DAT_40001b0b = '\x02';
        }
        if (ips_gear_cur < GEAR_3) {
          DAT_40001b0b = '\x01';
        }
      }
      break;
    case 2:
      if (((ips_gear_cur == GEAR_4) && (2 < DAT_400024c4)) && (2 < DAT_400025a4)) {
        DAT_40001b0b = '\0';
        DAT_40001bdd = 3;
      }
      else if ((ips_gear_cur == GEAR_3) && ((DAT_400024c4 < 3 || (DAT_400025a4 < 3)))) {
        DAT_40001b0b = '\0';
      }
      else {
        if (GEAR_4 < ips_gear_cur) {
          DAT_40001b0b = '\x02';
        }
        if (ips_gear_cur < GEAR_4) {
          DAT_40001b0b = '\x01';
        }
      }
      break;
    case 3:
      if (((ips_gear_cur == GEAR_5) && (2 < DAT_40002684)) && (2 < DAT_40002764)) {
        DAT_40001b0b = '\0';
        DAT_40001bdd = 4;
      }
      else if ((ips_gear_cur == GEAR_4) && ((DAT_40002684 < 3 || (DAT_40002764 < 3)))) {
        DAT_40001b0b = '\0';
      }
      else {
        if (GEAR_5 < ips_gear_cur) {
          DAT_40001b0b = '\x02';
        }
        if (ips_gear_cur < GEAR_5) {
          DAT_40001b0b = '\x01';
        }
      }
      break;
    case 4:
      if (((ips_gear_cur == GEAR_6) && (2 < DAT_40002844)) && (2 < DAT_40002924)) {
        DAT_40001b0b = '\0';
        DAT_40001bdd = 5;
      }
      else if ((ips_gear_cur == GEAR_5) && ((DAT_40002844 < 3 || (DAT_40002924 < 3)))) {
        DAT_40001b0b = '\0';
      }
      else {
        if (GEAR_6 < ips_gear_cur) {
          DAT_40001b0b = '\x02';
        }
        if (ips_gear_cur < GEAR_6) {
          DAT_40001b0b = '\x01';
        }
      }
      break;
    case 5:
      if (2 < DAT_40002a04) {
        DAT_40001bdd = 6;
      }
      break;
    case 6:
      for (bVar16 = 0; bVar16 < 8; bVar16 = bVar16 + 1) {
        if ((&DAT_40002450)[(uint)bVar16 * 0x70] != 0x1964) {
          iVar3 = (uint)(ushort)(&DAT_400023ec)[(uint)bVar16 * 0x70] *
                  (int)(short)(&DAT_400023d0)[(uint)bVar16 * 0x70];
          sVar4 = (short)(&DAT_400023d0)[(uint)bVar16 * 0x70] >> 0xf;
          (&DAT_400023d2)[(uint)bVar16 * 0x70] =
               (&DAT_400023d2)[(uint)bVar16 * 0x70] +
               ((&DAT_40002450)[(uint)bVar16 * 0x70] -
               ((&DAT_400023d2)[(uint)bVar16 * 0x70] +
               (((short)(iVar3 / 100) + sVar4) - ((short)((short)(iVar3 / 0x640000) + sVar4) >> 0xf)
               )));
          reset_element_slip_adaptation(bVar16);
        }
      }
      DAT_40001bdd = 7;
      break;
    case 7:
      shift_adapt_inhibit = '\0';
    }
    if (DAT_40001b0b == '\x01') {
      if (DAT_40001b08 == '\0') {
        DAT_40001b08 = DAT_400014a4;
        if (DAT_40001ba1 == 3) {
          DAT_40001ba1 = 4;
        }
        else {
          DAT_40001ba1 = 3;
        }
      }
    }
    else if (DAT_40001b0b == '\x02') {
      if (DAT_40001b08 == '\0') {
        DAT_40001b08 = DAT_400014a4;
        if (DAT_40001ba1 == 5) {
          DAT_40001ba1 = 6;
        }
        else {
          DAT_40001ba1 = 5;
        }
      }
    }
    else {
      DAT_40001ba1 = 0;
    }
    if (DAT_40001b08 != '\0') {
      DAT_40001b08 = DAT_40001b08 + -1;
    }
  }
  else if (shift_adapt_inhibit == '\x03') {
    DAT_40001aaa = 0x10;
    if ((output_shaft_rpm == 0) && (tps_commanded == '\0')) {
      DAT_40001b0d = 0;
    }
    else {
      DAT_40001b0d = DAT_40001b0d + 1;
    }
    if (2 < DAT_40001b0d) {
      DAT_40001b0d = 0;
      DAT_40001bdc = '\x06';
    }
    if (DAT_40001bdc == '\x06') {
      for (bVar16 = 0; bVar16 < 6; bVar16 = bVar16 + 1) {
        (&solenoid_SL_demand)[bVar16] = 0;
      }
      if (ips_gear_cur == GEAR_INVALID9) {
        shift_adapt_inhibit = DAT_40009029;
      }
    }
    else if (DAT_40001bdc == '\0') {
      if (ips_gear_cur == GEAR_1) {
        DAT_40001bdc = '\x01';
      }
    }
    else if (DAT_40001bdc == '\x01') {
      DAT_40005f5c = 0;
      DAT_4000603c = 0;
      DAT_4000611c = 0;
      DAT_400061fc = 0;
      DAT_40001bdc = '\x02';
    }
    else if (DAT_40001bdc == '\x02') {
      if (ips_gear_cur == GEAR_1) {
        cVar15 = learn_clutch_fill_pressure
                           (DAT_40001b0c + 1,input_shaft_load,input_shaft_rpm,0,
                            &DAT_40005f48 + (uint)DAT_40001b0c * 0xe0);
        if (cVar15 == '\x06') {
          DAT_40001b0c = DAT_40001b0c + 1;
          DAT_40001b0e = 0;
          if (DAT_40001b0c == 4) {
            DAT_40001b0c = 0;
            DAT_40001bdc = '\x03';
          }
        }
        if ((cVar15 == '\x03') && (DAT_40001b0e = DAT_40001b0e + 1, DAT_4000913e < DAT_40001b0e)) {
          DAT_40001bdc = '\x06';
          DAT_40001b0e = 0;
        }
      }
      else {
        DAT_40001bdc = '\x06';
        learn_clutch_fill_pressure(0,0,0,1,&DAT_40005f48);
      }
    }
    else if (DAT_40001bdc == '\x03') {
      init_clutch_slip_adaptation();
      uVar6 = accumulate_element_model_sample(2,0);
      uVar7 = accumulate_element_model_sample(3,1);
      uVar8 = accumulate_element_model_sample(0,2);
      uVar9 = accumulate_element_model_sample(1,3);
      uVar10 = accumulate_element_model_sample(0,4);
      uVar11 = accumulate_element_model_sample(3,5);
      uVar12 = accumulate_element_model_sample(1,6);
      uVar13 = accumulate_element_model_sample(2,7);
      for (bVar16 = 0; bVar16 < 6; bVar16 = bVar16 + 1) {
        (&solenoid_SL_demand)[bVar16] = 0;
      }
      if ((uVar6 & 1 & uVar7 & uVar8 & uVar9 & uVar10 & uVar11 & uVar12 & uVar13) == 0) {
        init_clutch_slip_adaptation();
        DAT_40001bdc = '\x06';
      }
      else {
        for (bVar16 = 0; bVar16 < 8; bVar16 = bVar16 + 1) {
          reset_element_slip_adaptation(bVar16);
        }
        DAT_40001bdc = '\x04';
      }
    }
    else if (DAT_40001bdc == '\x04') {
      cVar15 = ramp_solenoid_demand_up(1,(int)((uint)DAT_4000902b * 10000) >> 8);
      if (cVar15 != '\0') {
        DAT_40001bdc = '\x05';
      }
    }
    else if (DAT_40001bdc == '\x05') {
      DAT_40001aaa = 8;
      shift_adapt_inhibit = '\0';
      slip_learn_status_flags_gear6 = 0xff;
      DAT_40002ba1 = 0;
    }
    if (DAT_40001bdc == '\x06') {
      DAT_40001ba1 = 0;
    }
    else {
      if (DAT_40001b08 == '\0') {
        DAT_40001b08 = DAT_400014a4;
        bVar1 = DAT_40001ba1 == 0;
        DAT_40001ba1 = 0;
        if (bVar1) {
          DAT_40001ba1 = 10;
        }
      }
      if (DAT_40001b08 != '\0') {
        DAT_40001b08 = DAT_40001b08 + -1;
      }
    }
  }
  else {
    DAT_4000148e = 0xff;
    DAT_4000148f = 0xff;
    DAT_40001ba1 = 0;
    if ((trans_slip_status_flags & 4) == 0) {
      DAT_40001ba1 = 10;
    }
  }
  DAT_40001c71 = (&DAT_400010bc)[DAT_40001ba1];
  return;
}



undefined8 accumulate_element_model_sample(byte param_1,byte param_2)

{
  short sVar1;
  undefined8 uVar2;
  int iVar3;
  
  uVar2 = 1;
  if (((((param_1 < 4) && (param_2 < 8)) &&
       (500 < *(ushort *)(&DAT_40005fc4 + (uint)param_1 * 0xe0))) &&
      ((((0x17 < *(ushort *)(&DAT_40005f60 + (uint)param_1 * 0xe0) &&
         (*(ushort *)(&DAT_40005fc4 + (uint)param_1 * 0xe0) < 8000)) &&
        ((*(ushort *)(&DAT_40005f60 + (uint)param_1 * 0xe0) < 0xff &&
         ((*(short *)(&PTR_DAT_40001108)[param_1] < 0x9c4 &&
          (*(short *)(&PTR_DAT_40001128)[param_1] < 0x9c4)))))) &&
       (*(short *)(&PTR_DAT_400010c8)[param_2] < 0x9c4)))) &&
     ((((*(short *)(&PTR_PTR_400010e8)[param_2] < 1000 &&
        (0x32 < *(short *)(&PTR_DAT_40001108)[param_1])) &&
       (1 < *(short *)(&PTR_DAT_40001128)[param_1])) &&
      ((10 < *(short *)(&PTR_DAT_400010c8)[param_2] &&
       (-1000 < *(short *)(&PTR_PTR_400010e8)[param_2])))))) {
    iVar3 = (uint)*(ushort *)(&DAT_40005f60 + (uint)param_1 * 0xe0) *
            (int)*(short *)(&PTR_DAT_40001108)[param_1];
    sVar1 = *(short *)(&PTR_DAT_40001108)[param_1] >> 0xf;
    *(short *)(&DAT_40005f4a + (uint)param_1 * 0xe0) =
         (*(short *)(&DAT_40005fc4 + (uint)param_1 * 0xe0) -
         (*(short *)(&PTR_DAT_40001128)[param_1] +
         (((short)(iVar3 / 100) + sVar1) - ((short)((short)(iVar3 / 0x640000) + sVar1) >> 0xf)))) +
         *(short *)(&PTR_DAT_40001128)[param_1];
    *(undefined2 *)(&DAT_40005f48 + (uint)param_1 * 0xe0) =
         *(undefined2 *)(&PTR_DAT_40001108)[param_1];
    iVar3 = (((int)*(short *)(&PTR_DAT_400010c8)[param_2] *
             (int)*(short *)(&DAT_40005f48 + (uint)param_1 * 0xe0)) / 1000 & 0xffffU) *
            (uint)*(ushort *)(&DAT_40005f60 + (uint)param_1 * 0xe0);
    sVar1 = (short)(iVar3 >> 0x1f);
    (&DAT_400023d2)[(uint)param_2 * 0x70] =
         (&DAT_400023d2)[(uint)param_2 * 0x70] +
         ((*(short *)(&PTR_PTR_400010e8)[param_2] + *(short *)(&DAT_40005f4a + (uint)param_1 * 0xe0)
          + (((short)(iVar3 / 100) + sVar1) - ((short)((short)(iVar3 / 0x640000) + sVar1) >> 0xf)))
         - ((&DAT_400023d2)[(uint)param_2 * 0x70] +
           (short)((int)((uint)*(ushort *)(&DAT_40005f60 + (uint)param_1 * 0xe0) *
                        (int)(short)(&DAT_400023d0)[(uint)param_2 * 0x70]) / 100)));
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



undefined8 ramp_solenoid_demand_up(byte param_1,ushort param_2)

{
  undefined8 uVar1;
  
  uVar1 = 1;
  if ((param_1 < 7) && (param_2 < 0x2711)) {
    if ((int)(short)(&solenoid_SL_demand)[param_1] < (int)(uint)DAT_400090f4) {
      uVar1 = 0;
      (&solenoid_SL_demand)[param_1] = DAT_400090f4;
    }
    else if ((int)(short)(&solenoid_SL_demand)[param_1] < (int)(uint)param_2) {
      uVar1 = 0;
      (&solenoid_SL_demand)[param_1] = (&solenoid_SL_demand)[param_1] + (ushort)DAT_400090f2;
    }
  }
  return uVar1;
}



char learn_clutch_fill_pressure(byte param_1,ushort param_2,uint param_3,char param_4,int param_5)

{
  ulonglong uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  char cVar5;
  byte bVar6;
  ulonglong uVar7;
  
  iVar2 = 0;
  uVar7 = 1;
  if ((param_4 != '\0') || (3 < (byte)(param_1 - 1))) {
    DAT_40001b10 = '\x06';
  }
  if (DAT_40001b10 == '\0') {
    for (bVar6 = 0; bVar6 < 6; bVar6 = bVar6 + 1) {
      (&solenoid_SL_demand)[bVar6] = 0;
    }
    DAT_40001b10 = '\x01';
  }
  else if (DAT_40001b10 == '\x01') {
    if (param_1 == 1) {
      uVar7 = ramp_solenoid_demand_up(1,DAT_400090fe);
      uVar7 = uVar7 & 1;
    }
    else if (param_1 == 2) {
      uVar1 = ramp_solenoid_demand_up(2,DAT_40009100);
      uVar7 = ramp_solenoid_demand_up(3,(int)((uint)DAT_4000902b * 10000) >> 8);
      uVar7 = uVar1 & 1 & uVar7;
    }
    else if (param_1 == 3) {
      uVar1 = ramp_solenoid_demand_up(2,(int)((uint)DAT_4000902b * 10000) >> 8);
      uVar7 = ramp_solenoid_demand_up(3,DAT_40009102);
      uVar7 = uVar1 & 1 & uVar7;
    }
    else if (param_1 == 4) {
      uVar1 = ramp_solenoid_demand_up(2,(int)((uint)DAT_4000902b * 10000) >> 8);
      uVar7 = ramp_solenoid_demand_up(4,DAT_40009104);
      uVar7 = uVar1 & 1 & uVar7;
    }
    if (uVar7 != 0) {
      DAT_40001b10 = '\x02';
    }
  }
  else if (DAT_40001b10 == '\x02') {
    DAT_40001b28 = DAT_40001b28 + 1;
    if (DAT_400090f9 <= DAT_40001b28) {
      DAT_40001b28 = 0;
      DAT_40001b10 = '\x03';
    }
  }
  else if (DAT_40001b10 == '\x03') {
    DAT_40001b20 = (param_3 & 0xffff) - (uint)DAT_400090fa;
    if (DAT_40001b20 != 0) {
      iVar2 = int_abs(DAT_40001b20);
      iVar2 = DAT_40001b20 / iVar2;
    }
    DAT_40001b1c = (int)((uint)DAT_400090f6 * DAT_40001b20) >> (DAT_400090f7 & 0x3f);
    DAT_40001b14 = DAT_40001b14 +
                   ((int)((uint)DAT_400090f3 * DAT_40001b20) >> (DAT_400090f7 & 0x3f));
    uVar3 = int_abs(DAT_40001b20);
    DAT_40001b18 = DAT_40001b18 + iVar2 * ((1 << (DAT_400090f7 & 0x3f)) - 1U & uVar3);
    iVar4 = int_abs(DAT_40001b18);
    DAT_40001b14 = DAT_40001b14 + iVar2 * (iVar4 >> (DAT_400090f7 & 0x3f));
    iVar4 = int_abs(DAT_40001b18);
    DAT_40001b18 = DAT_40001b18 -
                   iVar2 * ((iVar4 >> (DAT_400090f7 & 0x3f)) << (DAT_400090f7 & 0x3f));
    if (DAT_40001b14 < 0x7d1) {
      if (DAT_40001b14 < -2000) {
        DAT_40001b14 = -2000;
      }
    }
    else {
      DAT_40001b14 = 2000;
    }
    DAT_40001b24 = (undefined *)(DAT_40001b1c + DAT_40001b14 + 2000);
    if ((int)DAT_40001b24 < 0) {
      DAT_40001b24 = (undefined *)0x0;
    }
    else if (8000 < (int)DAT_40001b24) {
      DAT_40001b24 = &DAT_00001f40;
    }
    (&solenoid_SL_demand)[param_1] = (short)DAT_40001b24;
    iVar2 = int_abs(DAT_40001b20);
    bVar6 = DAT_40001b29 + 1;
    DAT_40001b29 = 0;
    if (iVar2 < (int)(uint)DAT_400090fc) {
      DAT_40001b29 = bVar6;
    }
    if (DAT_400090f8 < DAT_40001b29) {
      DAT_40001b29 = 0;
      DAT_40001b10 = '\x04';
    }
  }
  else if (DAT_40001b10 == '\x04') {
    DAT_40001b2a = param_2 & 0xff;
    DAT_40001b2c = SUB42(DAT_40001b24,0);
    DAT_40001b10 = '\x06';
    if (*(byte *)(param_5 + 0x14) < 0x32) {
      *(ushort *)(param_5 + (uint)*(byte *)(param_5 + 0x14) * 2 + 0x18) = DAT_40001b2a;
      *(undefined2 *)(param_5 + (uint)*(byte *)(param_5 + 0x14) * 2 + 0x7c) = DAT_40001b2c;
      *(char *)(param_5 + 0x14) = *(char *)(param_5 + 0x14) + '\x01';
    }
  }
  else if (DAT_40001b10 == '\x05') {
    cVar5 = ramp_solenoid_demand_up(param_1,(int)((uint)DAT_4000902b * 10000) >> 8);
    if (cVar5 != '\0') {
      DAT_40001b28 = 0;
      DAT_40001b10 = '\x06';
    }
  }
  else if (DAT_40001b10 == '\x06') {
    DAT_40001b14 = 0;
    DAT_40001b1c = 0;
    DAT_40001b20 = 0;
    DAT_40001b24 = (undefined *)0x0;
    DAT_40001b29 = 0;
    DAT_40001b28 = 0;
    for (bVar6 = 0; bVar6 < 6; bVar6 = bVar6 + 1) {
      (&solenoid_SL_demand)[bVar6] = 0;
    }
    DAT_40001b10 = '\0';
  }
  return DAT_40001b10;
}



void compute_shift_slip(void)

{
  uint uVar1;
  
  trans_slip_metric = DAT_40001562;
  if (shift_to_gear < shift_from_gear) {
    trans_slip_metric = -DAT_40001562;
  }
  uVar1 = shift_slip_filter_accum * (0x100 - (uint)DAT_400014a5);
  shift_slip_filter_accum =
       ((int)uVar1 >> 8) + (uint)((int)uVar1 < 0 && (uVar1 & 0xff) != 0) +
       (int)trans_slip_metric * (uint)DAT_400014a5;
  shift_slip_filtered =
       (short)(shift_slip_filter_accum >> 8) +
       (ushort)((int)shift_slip_filter_accum < 0 && (shift_slip_filter_accum & 0xff) != 0);
  return;
}



void shift_gear_state_machine(enum_t6e_gear gear_requested)

{
  char cVar1;
  ushort _gear_state;
  
  _gear_state = gear_state;
  switch(gear_state) {
  case 0:
    switch(gear_requested) {
    case NEUTRAL:
      shift_from_gear = NEUTRAL;
      shift_to_gear = NEUTRAL;
      break;
    case GEAR_1:
      gear_state = 0xf;
      shift_from_gear = NEUTRAL;
      shift_to_gear = GEAR_1;
      shift_count_0_1[0] = shift_count_0_1[0] + 1;
      _gear_state = gear_state;
      break;
    case GEAR_2:
      gear_state = 0xf;
      shift_from_gear = NEUTRAL;
      shift_to_gear = GEAR_2;
      _gear_state = gear_state;
      break;
    case GEAR_3:
      gear_state = 0xf;
      shift_from_gear = NEUTRAL;
      shift_to_gear = GEAR_3;
      _gear_state = gear_state;
      break;
    case GEAR_4:
      gear_state = 0xf;
      shift_from_gear = NEUTRAL;
      shift_to_gear = GEAR_4;
      _gear_state = gear_state;
      break;
    case GEAR_5:
      gear_state = 0xf;
      shift_from_gear = NEUTRAL;
      shift_to_gear = GEAR_5;
      _gear_state = gear_state;
      break;
    case GEAR_6:
      gear_state = 0xf;
      shift_from_gear = NEUTRAL;
      shift_to_gear = GEAR_6;
      _gear_state = gear_state;
      break;
    case GEAR_INVALID9:
      gear_state = 0xf;
      shift_from_gear = NEUTRAL;
      shift_to_gear = GEAR_INVALID9;
      _gear_state = gear_state;
      break;
    case GEAR_REV:
      gear_state = 0xf;
      shift_from_gear = NEUTRAL;
      shift_to_gear = GEAR_REV;
      shift_count_0_1[1] = shift_count_0_1[1] + 1;
      _gear_state = gear_state;
    }
    break;
  case 1:
    switch(gear_requested) {
    case NEUTRAL:
      gear_state = 0xf;
      shift_from_gear = GEAR_1;
      shift_to_gear = NEUTRAL;
      shift_count_0_1[2] = shift_count_0_1[2] + 1;
      _gear_state = gear_state;
      break;
    case GEAR_1:
      shift_from_gear = GEAR_1;
      shift_to_gear = GEAR_1;
      break;
    case GEAR_2:
      gear_state = 0xf;
      shift_from_gear = GEAR_1;
      shift_to_gear = GEAR_2;
      shift_count_0_1[3] = shift_count_0_1[3] + 1;
      _gear_state = gear_state;
      break;
    case GEAR_3:
      gear_state = 0xf;
      shift_from_gear = GEAR_1;
      shift_to_gear = GEAR_3;
      shift_count_0_1[4] = shift_count_0_1[4] + 1;
      _gear_state = gear_state;
      break;
    case GEAR_4:
      gear_state = 0xf;
      shift_from_gear = GEAR_1;
      shift_to_gear = GEAR_4;
      _gear_state = gear_state;
      break;
    case GEAR_5:
      gear_state = 0xf;
      shift_from_gear = GEAR_1;
      shift_to_gear = GEAR_5;
      _gear_state = gear_state;
      break;
    case GEAR_6:
      gear_state = 0xf;
      shift_from_gear = GEAR_1;
      shift_to_gear = GEAR_6;
      shift_transition_code = 0x106;
      _gear_state = gear_state;
      break;
    case GEAR_INVALID9:
      gear_state = 0xf;
      shift_from_gear = GEAR_1;
      shift_to_gear = GEAR_INVALID9;
      shift_count_0_1[5] = shift_count_0_1[5] + 1;
      _gear_state = gear_state;
      break;
    case GEAR_REV:
      gear_state = 0xf;
      shift_from_gear = GEAR_1;
      shift_to_gear = GEAR_REV;
      shift_count_0_1[6] = shift_count_0_1[6] + 1;
      _gear_state = gear_state;
    }
    break;
  case 2:
    switch(gear_requested) {
    case NEUTRAL:
      gear_state = 0xf;
      shift_from_gear = GEAR_2;
      shift_to_gear = NEUTRAL;
      shift_count_2_0 = shift_count_2_0 + 1;
      _gear_state = gear_state;
      break;
    case GEAR_1:
      gear_state = 0xf;
      shift_from_gear = GEAR_2;
      shift_to_gear = GEAR_1;
      shift_count_2_1 = shift_count_2_1 + 1;
      _gear_state = gear_state;
      break;
    case GEAR_2:
      shift_from_gear = GEAR_2;
      shift_to_gear = GEAR_2;
      break;
    case GEAR_3:
      gear_state = 0xf;
      shift_from_gear = GEAR_2;
      shift_to_gear = GEAR_3;
      shift_count_2_3 = shift_count_2_3 + 1;
      _gear_state = gear_state;
      break;
    case GEAR_4:
      gear_state = 0xf;
      shift_from_gear = GEAR_2;
      shift_to_gear = GEAR_4;
      shift_count_2_4 = shift_count_2_4 + 1;
      _gear_state = gear_state;
      break;
    case GEAR_5:
      gear_state = 0xf;
      shift_from_gear = GEAR_2;
      shift_to_gear = GEAR_5;
      _gear_state = gear_state;
      break;
    case GEAR_6:
      gear_state = 0xf;
      shift_from_gear = GEAR_2;
      shift_to_gear = GEAR_6;
      _gear_state = gear_state;
      break;
    case GEAR_INVALID9:
      gear_state = 0xf;
      shift_from_gear = GEAR_2;
      shift_to_gear = GEAR_INVALID9;
      _gear_state = gear_state;
      break;
    case GEAR_REV:
      gear_state = 0xf;
      shift_from_gear = GEAR_2;
      shift_to_gear = GEAR_REV;
      _gear_state = gear_state;
    }
    break;
  case 3:
    switch(gear_requested) {
    case NEUTRAL:
      gear_state = 0xf;
      shift_from_gear = GEAR_3;
      shift_to_gear = NEUTRAL;
      _gear_state = gear_state;
      break;
    case GEAR_1:
      gear_state = 0xf;
      shift_from_gear = GEAR_3;
      shift_to_gear = GEAR_1;
      shift_count_3_1 = shift_count_3_1 + 1;
      _gear_state = gear_state;
      break;
    case GEAR_2:
      gear_state = 0xf;
      shift_from_gear = GEAR_3;
      shift_to_gear = GEAR_2;
      shift_count_3_2 = shift_count_3_2 + 1;
      _gear_state = gear_state;
      break;
    case GEAR_3:
      shift_from_gear = GEAR_3;
      shift_to_gear = GEAR_3;
      break;
    case GEAR_4:
      gear_state = 0xf;
      shift_from_gear = GEAR_3;
      shift_to_gear = GEAR_4;
      shift_count_3_4 = shift_count_3_4 + 1;
      _gear_state = gear_state;
      break;
    case GEAR_5:
      gear_state = 0xf;
      shift_from_gear = GEAR_3;
      shift_to_gear = GEAR_5;
      shift_count_3_5 = shift_count_3_5 + 1;
      _gear_state = gear_state;
      break;
    case GEAR_6:
      gear_state = 0xf;
      shift_from_gear = GEAR_3;
      shift_to_gear = GEAR_6;
      _gear_state = gear_state;
      break;
    case GEAR_INVALID9:
      gear_state = 0xf;
      shift_from_gear = GEAR_3;
      shift_to_gear = GEAR_INVALID9;
      _gear_state = gear_state;
      break;
    case GEAR_REV:
      gear_state = 0xf;
      shift_from_gear = GEAR_3;
      shift_to_gear = GEAR_REV;
      _gear_state = gear_state;
    }
    break;
  case 4:
    switch(gear_requested) {
    case NEUTRAL:
      gear_state = 0xf;
      shift_from_gear = GEAR_4;
      shift_to_gear = NEUTRAL;
      _gear_state = gear_state;
      break;
    case GEAR_1:
      gear_state = 0xf;
      shift_from_gear = GEAR_4;
      shift_to_gear = GEAR_1;
      _gear_state = gear_state;
      break;
    case GEAR_2:
      gear_state = 0xf;
      shift_from_gear = GEAR_4;
      shift_to_gear = GEAR_2;
      shift_count_4_2 = shift_count_4_2 + 1;
      _gear_state = gear_state;
      break;
    case GEAR_3:
      gear_state = 0xf;
      shift_from_gear = GEAR_4;
      shift_to_gear = GEAR_3;
      shift_count_4_3 = shift_count_4_3 + 1;
      _gear_state = gear_state;
      break;
    case GEAR_4:
      shift_from_gear = GEAR_4;
      shift_to_gear = GEAR_4;
      break;
    case GEAR_5:
      gear_state = 0xf;
      shift_from_gear = GEAR_4;
      shift_to_gear = GEAR_5;
      shift_count_4_5 = shift_count_4_5 + 1;
      _gear_state = gear_state;
      break;
    case GEAR_6:
      gear_state = 0xf;
      shift_from_gear = GEAR_4;
      shift_to_gear = GEAR_6;
      shift_count_4_6 = shift_count_4_6 + 1;
      _gear_state = gear_state;
      break;
    case GEAR_INVALID9:
      shift_transition_code = 0x409;
      break;
    case GEAR_REV:
      shift_transition_code = 0x40a;
    }
    break;
  case 5:
    switch(gear_requested) {
    case NEUTRAL:
      gear_state = 0xf;
      shift_from_gear = GEAR_5;
      shift_to_gear = NEUTRAL;
      _gear_state = gear_state;
      break;
    case GEAR_1:
      gear_state = 0xf;
      shift_from_gear = GEAR_5;
      shift_to_gear = GEAR_1;
      _gear_state = gear_state;
      break;
    case GEAR_2:
      gear_state = 0xf;
      shift_from_gear = GEAR_5;
      shift_to_gear = GEAR_2;
      _gear_state = gear_state;
      break;
    case GEAR_3:
      gear_state = 0xf;
      shift_from_gear = GEAR_5;
      shift_to_gear = GEAR_3;
      shift_count_5_3 = shift_count_5_3 + 1;
      _gear_state = gear_state;
      break;
    case GEAR_4:
      gear_state = 0xf;
      shift_from_gear = GEAR_5;
      shift_to_gear = GEAR_4;
      shift_count_5_4 = shift_count_5_4 + 1;
      _gear_state = gear_state;
      break;
    case GEAR_5:
      shift_from_gear = GEAR_5;
      shift_to_gear = GEAR_5;
      break;
    case GEAR_6:
      gear_state = 0xf;
      shift_from_gear = GEAR_5;
      shift_to_gear = GEAR_6;
      shift_count_5_6 = shift_count_5_6 + 1;
      _gear_state = gear_state;
      break;
    case GEAR_INVALID9:
      shift_transition_code = 0x509;
      break;
    case GEAR_REV:
      shift_transition_code = 0x50a;
    }
    break;
  case 6:
    switch(gear_requested) {
    case NEUTRAL:
      gear_state = 0xf;
      shift_from_gear = GEAR_6;
      shift_to_gear = NEUTRAL;
      _gear_state = gear_state;
      break;
    case GEAR_1:
      gear_state = 0xf;
      shift_from_gear = GEAR_6;
      shift_to_gear = GEAR_1;
      shift_transition_code = 0x601;
      _gear_state = gear_state;
      break;
    case GEAR_2:
      gear_state = 0xf;
      shift_from_gear = GEAR_6;
      shift_to_gear = GEAR_2;
      _gear_state = gear_state;
      break;
    case GEAR_3:
      gear_state = 0xf;
      shift_from_gear = GEAR_6;
      shift_to_gear = GEAR_3;
      _gear_state = gear_state;
      break;
    case GEAR_4:
      gear_state = 0xf;
      shift_from_gear = GEAR_6;
      shift_to_gear = GEAR_4;
      shift_count_6_4 = shift_count_6_4 + 1;
      _gear_state = gear_state;
      break;
    case GEAR_5:
      gear_state = 0xf;
      shift_from_gear = GEAR_6;
      shift_to_gear = GEAR_5;
      shift_count_6_5 = shift_count_6_5 + 1;
      _gear_state = gear_state;
      break;
    case GEAR_6:
      shift_from_gear = GEAR_6;
      shift_to_gear = GEAR_6;
      break;
    case GEAR_INVALID9:
      shift_transition_code = 0x609;
      break;
    case GEAR_REV:
      shift_transition_code = 0x60a;
    }
    break;
  case 9:
    switch(gear_requested) {
    case NEUTRAL:
      gear_state = 0xf;
      shift_from_gear = GEAR_INVALID9;
      shift_to_gear = NEUTRAL;
      _gear_state = gear_state;
      break;
    case GEAR_1:
      gear_state = 0xf;
      shift_from_gear = GEAR_INVALID9;
      shift_to_gear = GEAR_1;
      shift_count_9_1 = shift_count_9_1 + 1;
      _gear_state = gear_state;
      break;
    case GEAR_2:
      gear_state = 0xf;
      shift_from_gear = GEAR_INVALID9;
      shift_to_gear = GEAR_2;
      _gear_state = gear_state;
      break;
    case GEAR_3:
      gear_state = 0xf;
      shift_from_gear = GEAR_INVALID9;
      shift_to_gear = GEAR_3;
      _gear_state = gear_state;
      break;
    case GEAR_4:
      shift_transition_code = 0x904;
      break;
    case GEAR_5:
      shift_transition_code = 0x905;
      break;
    case GEAR_6:
      shift_transition_code = 0x906;
      break;
    case GEAR_INVALID9:
      shift_from_gear = GEAR_INVALID9;
      shift_to_gear = GEAR_INVALID9;
      break;
    case GEAR_REV:
      gear_state = 0xf;
      shift_from_gear = GEAR_INVALID9;
      shift_to_gear = GEAR_REV;
      _gear_state = gear_state;
    }
    break;
  case 10:
    switch(gear_requested) {
    case NEUTRAL:
      gear_state = 0xf;
      shift_from_gear = GEAR_REV;
      shift_to_gear = NEUTRAL;
      shift_count_10_0 = shift_count_10_0 + 1;
      _gear_state = gear_state;
      break;
    case GEAR_1:
      gear_state = 0xf;
      shift_from_gear = GEAR_REV;
      shift_to_gear = GEAR_1;
      shift_count_10_1 = shift_count_10_1 + 1;
      _gear_state = gear_state;
      break;
    case GEAR_2:
      gear_state = 0xf;
      shift_from_gear = GEAR_REV;
      shift_to_gear = GEAR_2;
      _gear_state = gear_state;
      break;
    case GEAR_3:
      gear_state = 0xf;
      shift_from_gear = GEAR_REV;
      shift_to_gear = GEAR_3;
      _gear_state = gear_state;
      break;
    case GEAR_4:
      shift_transition_code = 0xa04;
      break;
    case GEAR_5:
      shift_transition_code = 0xa05;
      break;
    case GEAR_6:
      shift_transition_code = 0xa06;
      break;
    case GEAR_INVALID9:
      gear_state = 0xf;
      shift_from_gear = GEAR_REV;
      shift_to_gear = GEAR_INVALID9;
      _gear_state = gear_state;
      break;
    case GEAR_REV:
      shift_from_gear = GEAR_REV;
      shift_to_gear = GEAR_REV;
    }
    break;
  case 0xf:
    cVar1 = execute_shift(shift_from_gear,shift_to_gear);
    _gear_state = (ushort)shift_to_gear;
    if (cVar1 == '\0') {
      _gear_state = gear_state;
    }
  }
  gear_state = _gear_state;
  ips_gear_cur = (enum_t6e_gear)gear_state & (GEAR_INVALID8|GEAR_INVALID7);
  return;
}



char shift_adaptation_controller
               (u16_rspeed_rpm gate_rpm,byte input_shaft_load,ushort pi_feedback,
               ushort *learned_correction,byte *correction_history,byte hist_size,
               uint16_t *history_crc,byte oil_temp,bool learn_enable,bool learn_reset,char bool)

{
  ushort uVar1;
  bool bVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  byte bVar8;
  uint16_t uVar7;
  
  bVar2 = false;
  if (learn_reset) {
    shift_adapt_phase_unknown = '\0';
    *learned_correction = 0;
  }
  uVar1 = (ushort)DAT_400090b5;
  if (((((u16_rspeed_rpm_ARRAY_400090d0[0] < gate_rpm) &&
        (gate_rpm < u16_rspeed_rpm_ARRAY_400090d0[1])) && (DAT_400090cd < input_shaft_load)) &&
      ((input_shaft_load < DAT_400090cf && (oil_temp < DAT_40009026)))) &&
     ((DAT_40009030 < oil_temp && (bVar2 = true, !learn_enable)))) {
    bVar2 = false;
  }
  if ((!learn_enable) && (shift_adapt_phase_unknown != '\x05')) {
    *learned_correction = shift_adapt_state_unknown;
    shift_adapt_phase_unknown = '\0';
  }
  if (shift_adapt_phase_unknown == '\0') {
    shift_adapt_state_unknown = *learned_correction;
    DAT_40001b36 = *learned_correction - DAT_400090d4;
    if (((int)(uint)DAT_400090b6 < (int)(short)DAT_40001b36) ||
       ((int)(short)DAT_40001b36 < -(int)(short)DAT_400090b6)) {
      DAT_40001b36 = 0;
      *learned_correction = 0;
    }
    shift_adapt_phase_unknown = '\x01';
  }
  else if (shift_adapt_phase_unknown == '\x01') {
    DAT_40001b34 = DAT_40001b34 + 1;
    if (!bVar2) {
      DAT_40001b34 = 0;
    }
    if (DAT_400090b8 < DAT_40001b34) {
      shift_adapt_phase_unknown = '\x02';
    }
  }
  else if (shift_adapt_phase_unknown == '\x02') {
    *learned_correction = DAT_40001b36;
    DAT_40001b34 = DAT_40001b34 + 1;
    if (((uint)DAT_400090b8 + (uint)DAT_400090d8 < (uint)DAT_40001b34) && (bVar2)) {
      shift_adapt_phase_unknown = '\x03';
    }
    else if (bVar2) {
      shift_adapt_phase_unknown = '\x02';
    }
    else {
      DAT_40001b34 = 0;
      *learned_correction = shift_adapt_state_unknown;
      shift_adapt_phase_unknown = '\x01';
    }
  }
  else if (shift_adapt_phase_unknown == '\x03') {
    sVar5 = (uVar1 - (pi_feedback & 0xff)) * (ushort)DAT_400090be;
    sVar3 = sVar5 >> 0xf;
    sVar6 = DAT_40001b38 +
            sVar5 + ((sVar5 / 1000 + sVar3) -
                    ((short)((short)((int)sVar5 / 0x3e80000) + sVar3) >> 0xf)) * -1000;
    sVar4 = sVar6 >> 0xf;
    DAT_40001b36 = DAT_40001b36 +
                   ((sVar5 / 1000 + sVar3) -
                   ((short)((short)((int)sVar5 / 0x3e80000) + sVar3) >> 0xf)) +
                   ((sVar6 / 1000 + sVar4) -
                   ((short)((short)((int)sVar6 / 0x3e80000) + sVar4) >> 0xf));
    DAT_40001b38 = sVar6 + ((sVar6 / 1000 + sVar4) -
                           ((short)((short)((int)sVar6 / 0x3e80000) + sVar4) >> 0xf)) * -1000;
    DAT_40001b34 = DAT_40001b34 + 1;
    if ((int)(uint)DAT_400090b6 < (int)(short)DAT_40001b36) {
      DAT_40001b36 = DAT_400090b6;
    }
    if ((int)(short)DAT_40001b36 < (int)-(uint)DAT_400090b6) {
      DAT_40001b36 = -DAT_400090b6;
    }
    *learned_correction = DAT_40001b36;
    if ((DAT_400090ba < DAT_40001b34) && (bVar2)) {
      shift_adapt_phase_unknown = '\x04';
    }
    else if (bVar2) {
      shift_adapt_phase_unknown = '\x03';
    }
    else {
      DAT_40001b34 = 0;
      *learned_correction = shift_adapt_state_unknown;
      shift_adapt_phase_unknown = '\x01';
    }
  }
  else if (shift_adapt_phase_unknown == '\x04') {
    for (bVar8 = hist_size - 1; bVar8 != 0; bVar8 = bVar8 - 1) {
      *(undefined2 *)(correction_history + (uint)bVar8 * 2) =
           *(undefined2 *)(correction_history + (bVar8 - 1) * 2);
    }
    *(ushort *)correction_history = DAT_40001b36 + DAT_400090d4;
    if ((hist_size < 5) || (bool == '\0')) {
      *learned_correction = DAT_40001b36 + DAT_400090d4;
      for (bVar8 = 0; bVar8 < hist_size; bVar8 = bVar8 + 1) {
        *(ushort *)(correction_history + (uint)bVar8 * 2) = DAT_40001b36 + DAT_400090d4;
      }
    }
    else {
      *learned_correction = 0;
      for (bVar8 = 0; bVar8 < 4; bVar8 = bVar8 + 1) {
        *learned_correction = *learned_correction + *(short *)(correction_history + (uint)bVar8 * 2)
        ;
      }
      uVar1 = *learned_correction;
      *learned_correction = ((short)uVar1 >> 2) + (ushort)((short)uVar1 < 0 && (uVar1 & 3) != 0);
    }
    uVar7 = CRC16(correction_history,(uint)hist_size << 1);
    *history_crc = uVar7;
    shift_adapt_phase_unknown = '\x05';
  }
  else if (shift_adapt_phase_unknown == '\x05') {
    shift_adapt_phase_unknown = '\x05';
  }
  return shift_adapt_phase_unknown;
}



uint compute_clutch_pressure_ramp
               (char state,uint8_t _load_unknown,u16_rspeed_rpm rpm,bool sport,int param_5,
               enum_t6e_gear gear)

{
  undefined *puVar1;
  uint uVar2;
  int iVar3;
  ushort uVar4;
  byte bVar5;
  int16_t _throttle_rate_commanded;
  undefined *puVar6;
  undefined4 local_30;
  undefined4 local_2c;
  
  local_30 = 0;
  local_2c = 0;
  uVar2 = (uint)DAT_40009154;
  if (sport) {
    clutch_pressure_target =
         lookup_3D_uint32_interpolated
                   (8,8,_load_unknown,rpm,CAL_clutch_pressure_target_sport,
                    CAL_clutch_pressure_target_sport_X_load,CAL_clutch_pressure_target_sport_Y_rpm);
    if ((gear == (GEAR_INVALID8|GEAR_INVALID7)) && (DAT_40009150 < clutch_pressure_target)) {
      clutch_pressure_target = DAT_40009150;
    }
  }
  else {
    clutch_pressure_target =
         lookup_3D_uint32_interpolated
                   (8,8,_load_unknown,rpm,CAL_clutch_pressure_target_tour,
                    CAL_clutch_pressure_target_tour_X_load,CAL_clutch_pressure_target_tour_Y_rpm);
    if ((gear == (GEAR_INVALID8|GEAR_INVALID7)) && (DAT_40009152 < clutch_pressure_target)) {
      clutch_pressure_target = DAT_40009152;
    }
  }
  if (((((state == '\x03') || (state == '\x02')) ||
       (iVar3 = int_abs((longlong)(int)(((uint)_load_unknown * 0x294) / 0xff) + -0x3c),
       (int)((uVar2 * 0x294) / 0xff - 0x3c) <= iVar3)) ||
      (bVar5 = DAT_40009154, clutch_pressure_target < DAT_40009140)) &&
     (bVar5 = _load_unknown, _load_unknown < 0x17)) {
    bVar5 = 0x2e - _load_unknown;
  }
  local_30 = 0x1700ff;
  local_2c = CONCAT22(DAT_400090ee,DAT_400090f0);
  DAT_40001b40 = lookup_2D_uint16_interpolated(2,bVar5,&local_2c,&local_30);
  if (clutch_pressure_target < DAT_40001b3e) {
    if (DAT_40008f79 < DAT_40001b3e) {
      DAT_40001b3e = DAT_40001b3e - DAT_40008f79;
    }
    if (DAT_40001b3e < clutch_pressure_target) {
      DAT_40001b3e = clutch_pressure_target;
    }
  }
  else {
    DAT_40001b3e = DAT_40001b3e + DAT_40008f79;
    if (clutch_pressure_target < DAT_40001b3e) {
      DAT_40001b3e = clutch_pressure_target;
    }
  }
  _throttle_rate_commanded = 0;
  if (0 < throttle_rate_commanded) {
    _throttle_rate_commanded = throttle_rate_commanded;
  }
  if ((ushort)((ushort)DAT_400090a7 * 10 + 10000) < DAT_40001b3e) {
    uVar4 = lookup_2D_uint16_interpolated
                      (6,_throttle_rate_commanded,CAL_clutch_unknown1,
                       CAL_clutch_unknown1_X_throttle_rate);
    if (uVar4 <= DAT_40001b42) {
      if (DAT_400090a6 < DAT_40001b42) {
        uVar4 = DAT_40001b42 - DAT_400090a6;
      }
      else {
        DAT_40001b42 = 0;
        uVar4 = DAT_40001b42;
      }
    }
  }
  else {
    DAT_40001b42 = 0;
    uVar4 = DAT_40001b42;
  }
  DAT_40001b42 = uVar4;
  if (gear == (GEAR_INVALID8|GEAR_INVALID7)) {
    DAT_40001b42 = 0;
  }
  puVar6 = (undefined *)
           ((int)((uint)DAT_40001b3e * ((uint)DAT_40001b40 - (uint)DAT_400090ee)) / 10000 +
           (uint)DAT_40001b42 + (uint)DAT_400090ee);
  if (&DAT_00002710 < puVar6) {
    puVar6 = &DAT_00002710;
  }
  puVar1 = (undefined *)((uint)DAT_40001b40 + param_5);
  if (1 < (byte)(state - 2U)) {
    puVar1 = puVar6 + (short)param_5;
  }
  return (uint)puVar1 & 0xffff;
}



void actuator_output_controller(void)

{
  bool bVar1;
  int iVar2;
  short sVar3;
  undefined *puVar4;
  uint uVar5;
  bool _shift_adaptation_learn_enable;
  ushort uVar6;
  uint8_t _load_unknown;
  uint uVar7;
  byte bVar8;
  byte _input_shaft_load;
  
  _input_shaft_load = input_shaft_load;
  _load_unknown = torque_alphaN_raw_8bit;
  if (DAT_40001b54 == '\0') {
    _load_unknown = DAT_40001ad1;
  }
  shift_transition_code = 0;
  compute_input_torque();
  if ((((((DAT_40001ac5 & 3) == 0) && ((DAT_40001ac6 & 3) == 0)) && ((DAT_40001678 & 2) == 0)) &&
      ((((DAT_40001678 & 1) == 0 && ((DAT_40001678 & 0x10) == 0)) &&
       (((DAT_40001678 & 0x20) == 0 && (((DAT_40001678 & 0x3c00) == 0 && ((DAT_40001678 & 4) == 0)))
        ))))) &&
     (((DAT_40001678 & 8) == 0 &&
      (((DAT_40001678 & 0x40000) == 0 && (shift_closed_loop_active == false)))))) {
    _shift_adaptation_learn_enable = true;
  }
  else {
    _shift_adaptation_learn_enable = false;
  }
  if (LEA_shift_adaptation_reset != false) {
    LEA_shift_adaptation_history_valid = false;
  }
  shift_adapt_phase_unknown2 =
       shift_adaptation_controller
                 (shift_adaptation_learn_gate,_input_shaft_load,
                  (ushort)LEA_shift_adaptation_pi_feedback,&LEA_shift_adaptation,
                  LEA_shift_adaptation_history,32,&LEA_shift_adaptation_history_crc,oil_temp_unknown
                  ,_shift_adaptation_learn_enable,LEA_shift_adaptation_reset,
                  LEA_shift_adaptation_history_valid);
  LEA_shift_adaptation_reset = false;
  if (shift_adapt_phase_unknown2 == '\x05') {
    LEA_shift_adaptation_history_valid = true;
  }
                    // (driver_input_flags[1] & 4) is a SPORT || RACE check
  if ((auto_mode_active == false) ||
     (((driver_input_flags[1] & 4) != 0 && ((cruise_status_flags & 4) == 0)))) {
    DAT_40001b50 = compute_clutch_pressure_ramp
                             (shift_adapt_phase_unknown2,_load_unknown,shift_adaptation_learn_gate,
                              false,(int)(short)LEA_shift_adaptation,ips_gear_cur);
  }
  else {
    DAT_40001b50 = compute_clutch_pressure_ramp
                             (shift_adapt_phase_unknown2,_load_unknown,shift_adaptation_learn_gate,
                              true,(int)(short)LEA_shift_adaptation,ips_gear_cur);
  }
  iVar2 = (int)((ulonglong)((longlong)(int)(uint)input_shaft_rpm * -0x77777777) >> 0x20) +
          (uint)input_shaft_rpm;
  iVar2 = (iVar2 >> 4) - (iVar2 >> 0x1f);
  input_shaft_speed = (undefined1)iVar2;
  if (0xff < iVar2) {
    input_shaft_speed = 0xff;
  }
  if (DAT_40008f6a == 0) {
    if ((DAT_40001840 & 0x40) == 0) {
      if ((shift_from_gear == GEAR_REV) && (shift_to_gear != GEAR_REV)) {
        DAT_40001b52 = '\0';
        solenoid_SL_demand = DAT_40008f74;
      }
      else if ((shift_from_gear == GEAR_INVALID9) &&
              (((DAT_40001c39 == '\0' && (shift_position_request_bits != '\x04')) ||
               ((DAT_40001c39 == -2 && (shift_position_request_bits != -2)))))) {
        solenoid_SL_demand = DAT_40008f74;
        DAT_40001b52 = '\0';
      }
      else if ((byte)(gear_request - GEAR_1) < 6) {
        if (((gear_request == GEAR_1) || (ips_gear_cur == GEAR_1)) &&
           (CAL_rpm_clutch_apply < tach_rpm)) {
          solenoid_SL_demand = DAT_40008f76;
          DAT_40001b52 = '\x01';
        }
        else if ((DAT_40008f72 < vehicle_speed) &&
                ((uint)CAL_rpm_clutch_apply < (uint)input_shaft_rpm << 2)) {
          solenoid_SL_demand = DAT_40008f74;
          DAT_40001b52 = '\x01';
        }
        else if ((vehicle_speed < DAT_40008f73) ||
                ((uint)input_shaft_rpm << 2 < (uint)CAL_rpm_clutch_release)) {
          solenoid_SL_demand = DAT_40008f76;
          DAT_40001b52 = '\0';
        }
      }
      else if (DAT_40001a89 == '\x01') {
        solenoid_SL_demand = DAT_40008f74;
        DAT_40001b52 = '\0';
      }
      else {
        solenoid_SL_demand = DAT_40008f76;
        DAT_40001b52 = '\0';
      }
    }
    else {
      solenoid_SL_demand = DAT_40001874;
      DAT_40001b52 = '\x01';
    }
  }
  else {
    solenoid_SL_demand = DAT_40008f6a;
    DAT_40001b52 = '\x01';
  }
  if ((int)(uint)DAT_40008f76 < (int)(short)solenoid_SL_demand) {
    tcc_lockup_ramp_inhibit_timer = DAT_40008ee8;
  }
  else {
    bVar1 = tcc_lockup_ramp_inhibit_timer == '\0';
    tcc_lockup_ramp_inhibit_timer = tcc_lockup_ramp_inhibit_timer + -1;
    if (bVar1) {
      tcc_lockup_ramp_inhibit_timer = '\0';
    }
  }
  DAT_40001b46 = 0;
  if ((DAT_40001840 & 0x100) == 0) {
    if (((DAT_40001844 & 1) == 0) || ((DAT_40001840 & 1) == 0)) {
      if (CAL_tcc_slu_fixed_demand == 0) {
        if (((((ips_gear_cur == (GEAR_INVALID8|GEAR_INVALID7)) && (shift_torque_managed != '\0')) &&
             (DAT_40009048 != '\0')) || ((ips_gear_cur == GEAR_REV || (gear_request == GEAR_REV))))
           || (((int)_load_signed < (int)-(uint)CAL_tcc_coast_unlock_load &&
               (vehicle_speed < CAL_tcc_coast_unlock_speed)))) {
          solenoid_SLU_demand = 0;
          tcc_slu_demand_staged = 0;
          tcc_creep_lockup_active = '\0';
        }
        else {
          DAT_40001b4e = 0;
          if (((((ips_gear_cur == (GEAR_INVALID8|GEAR_INVALID7)) && (gear_request == GEAR_1)) &&
               ((shift_mode_word & 0xf) == 10)) || (ips_gear_cur == GEAR_1)) &&
             (((int)(short)solenoid_SL_demand == (uint)DAT_40008f76 && (DAT_40001b52 != '\0')))) {
            tcc_creep_lockup_active = '\x01';
            if (vehicle_speed < CAL_tcc_creep_lockup_engage_speed) {
              if (tcc_lockup_ramp_inhibit_timer == '\0') {
                if ((CAL_tcc_creep_lockup_load_threshold < _input_shaft_load) ||
                   ((shift_torque_managed != '\0' && (gear_request == GEAR_1)))) {
                  uVar6 = (ushort)CAL_tcc_creep_lockup_ramp_loaded;
                }
                else {
                  uVar6 = (ushort)CAL_tcc_creep_lockup_ramp_normal;
                }
              }
              else {
                uVar6 = 0;
              }
              if ((int)(short)solenoid_SLU_demand < (int)(uint)CAL_tcc_creep_lockup_min) {
                solenoid_SLU_demand = CAL_tcc_creep_lockup_min;
              }
              else if ((int)(short)solenoid_SLU_demand < (int)(uint)CAL_tcc_creep_lockup_max) {
                solenoid_SLU_demand = solenoid_SLU_demand + uVar6;
              }
              else {
                solenoid_SLU_demand = CAL_tcc_creep_lockup_max;
              }
            }
            else if (CAL_tcc_creep_lockup_release_speed < vehicle_speed) {
              solenoid_SLU_demand = 0;
            }
          }
          else {
            tcc_creep_lockup_active = '\0';
            if (solenoid_SL_demand == 0) {
              tcc_slu_demand_staged = 0;
            }
            else {
              tcc_slu_demand_staged = DAT_40001b50;
              if (DAT_40001b52 == '\0') {
                tcc_slu_demand_staged = 0;
              }
            }
          }
        }
        tcc_slu_demand_final = tcc_slu_demand_staged;
        if (tcc_slu_demand_staged == 0) {
          tcc_slu_demand_final = 0;
        }
        if (tcc_creep_lockup_active == '\0') {
          solenoid_SLU_demand = tcc_slu_demand_final;
        }
      }
      else {
        solenoid_SLU_demand = CAL_tcc_slu_fixed_demand;
        tcc_slu_demand_staged = CAL_tcc_slu_fixed_demand;
      }
    }
    else {
      solenoid_SL_demand = DAT_40008f76;
      solenoid_SLU_demand = 0;
    }
  }
  else {
    solenoid_SLU_demand = obd_slu_test_demand;
  }
  for (bVar8 = 0; bVar8 < 4; bVar8 = bVar8 + 1) {
    if ((int)((uint)DAT_4000902c * 10000) >> 8 < (int)(short)(&solenoid_SL_demand)[bVar8 + 1]) {
      (&DAT_40001494)[bVar8] = 0;
      (&DAT_40001498)[bVar8] = 0;
    }
  }
  if (((((DAT_40001509 < 6) || ((DAT_40001b47 != '\x01' && (DAT_40001b48 != '\x01')))) &&
       (DAT_40008f96 == 0)) && ((DAT_40001840 & 0x200) == 0)) || (shift_adapt_inhibit == '\x03')) {
    DAT_40001b99 = DAT_40001b99 | 0x11;
  }
  else {
    DAT_40001b99 = DAT_40001b99 & 0xee;
    if (DAT_40008f96 == 0) {
      if ((DAT_40001840 & 0x200) == 0) {
        if (DAT_40001b47 == '\x01') {
          solenoid_SL1_demand = (short)((uint)DAT_4000150b * 3000 >> 8) + 0x5dc;
        }
        else {
          solenoid_SL1_demand = (short)((uint)DAT_4000150a * 3000 >> 8) + 0x5dc;
        }
      }
      else {
        solenoid_SL1_demand = DAT_4000186e;
      }
    }
    else {
      solenoid_SL1_demand = DAT_40008f96;
    }
  }
  if ((((DAT_40001509 < 6) || ((DAT_40001b47 != '\x02' && (DAT_40001b48 != '\x02')))) &&
      ((DAT_40008f98 == 0 && ((DAT_40001840 & 0x400) == 0)))) || (shift_adapt_inhibit == '\x03')) {
    DAT_40001b99 = DAT_40001b99 | 0x22;
  }
  else {
    DAT_40001b99 = DAT_40001b99 & 0xdd;
    if (DAT_40008f98 == 0) {
      if ((DAT_40001840 & 0x400) == 0) {
        if (DAT_40001b47 == '\x02') {
          solenoid_SL2_demand = (short)((uint)DAT_4000150b * 3000 >> 8) + 0x5dc;
        }
        else {
          solenoid_SL2_demand = (short)((uint)DAT_4000150a * 3000 >> 8) + 0x5dc;
        }
      }
      else {
        solenoid_SL2_demand = DAT_4000186c;
      }
    }
    else {
      solenoid_SL2_demand = DAT_40008f98;
    }
  }
  if ((((DAT_40001509 < 6) || ((DAT_40001b47 != '\x03' && (DAT_40001b48 != '\x03')))) &&
      ((DAT_40008f9a == 0 && ((DAT_40001840 & 0x800) == 0)))) || (shift_adapt_inhibit == '\x03')) {
    DAT_40001b99 = DAT_40001b99 | 0x44;
  }
  else {
    DAT_40001b99 = DAT_40001b99 & 0xbb;
    if (DAT_40008f9a == 0) {
      if ((DAT_40001840 & 0x800) == 0) {
        if (DAT_40001b47 == '\x03') {
          solenoid_SL3_demand = (short)((uint)DAT_4000150b * 3000 >> 8) + 0x5dc;
        }
        else {
          solenoid_SL3_demand = (short)((uint)DAT_4000150a * 3000 >> 8) + 0x5dc;
        }
      }
      else {
        solenoid_SL3_demand = DAT_4000186a;
      }
    }
    else {
      solenoid_SL3_demand = DAT_40008f9a;
    }
  }
  if (((((DAT_40001509 < 6) || ((DAT_40001b47 != '\x04' && (DAT_40001b48 != '\x04')))) &&
       (DAT_40008f9c == 0)) && ((DAT_40001840 & 0x1000) == 0)) || (shift_adapt_inhibit == '\x03')) {
    DAT_40001b99 = DAT_40001b99 | 0x88;
  }
  else {
    DAT_40001b99 = DAT_40001b99 & 0x77;
    if (DAT_40008f9c == 0) {
      if ((DAT_40001840 & 0x1000) == 0) {
        if (DAT_40001b47 == '\x04') {
          solenoid_SL4_demand = (short)((uint)DAT_4000150b * 3000 >> 8) + 0x5dc;
        }
        else {
          solenoid_SL4_demand = (short)((uint)DAT_4000150a * 3000 >> 8) + 0x5dc;
        }
      }
      else {
        solenoid_SL4_demand = DAT_40001868;
      }
    }
    else {
      solenoid_SL4_demand = DAT_40008f9c;
    }
  }
  if (DAT_40008fb4 == 0) {
    if ((DAT_40001840 & 0x80) == 0) {
      if (tach_rpm == 0) {
        solenoid_SLT_demand = 0;
      }
      else {
        iVar2 = (int)((ulonglong)((longlong)(int)(uint)tach_rpm * -0x77777777) >> 0x20) +
                (uint)tach_rpm;
        uVar5 = (iVar2 >> 6) - (iVar2 >> 0x1f);
        if ((int)uVar5 < 0x100) {
          uVar7 = uVar5 & 0xff;
          if ((int)uVar5 < 0) {
            uVar7 = 0;
          }
        }
        else {
          uVar7 = 0xff;
        }
        DAT_40001b45 = lookup_2D_uint8_interpolated(8,input_shaft_load,s__40009796,s__6Qu_4000978e);
        uVar5 = lookup_3D_uint8_interpolated
                          (8,8,input_shaft_load,uVar7,s_________4444444_________0000000_8_400099f2,
                           s__6Qu_400099e2,s_Cu_400099ea);
        iVar2 = ((int)((uVar5 & 0xff) * 4000) >> 8) + 0x9c4;
        if (gear_state == 0xf) {
          if (shift_closed_loop_active == false) {
            uVar5 = (int)(iVar2 * (DAT_40001b45 + 0x40)) >> 6;
          }
          else {
            uVar5 = (uint)DAT_40009142;
          }
        }
        else {
          uVar5 = lookup_2D_uint8_interpolated(8,oil_temp_unknown,s_pJ_4000d44e,&PTR_DAT_4000d446);
          uVar5 = (((int)((uVar5 & 0xff) * 1000) >> 8) + iVar2) - 500;
        }
        if ((int)uVar5 < 0x2711) {
          if ((int)uVar5 < 0) {
            solenoid_SLT_demand = 0;
          }
          else {
            solenoid_SLT_demand = (short)uVar5;
          }
        }
        else {
          solenoid_SLT_demand = 10000;
        }
      }
    }
    else {
      solenoid_SLT_demand = DAT_40001872;
    }
  }
  else {
    solenoid_SLT_demand = DAT_40008fb4;
  }
  if (DAT_40008fda == '\0') {
    for (bVar8 = 0; bVar8 < 7; bVar8 = bVar8 + 1) {
      (&solenoid_SL_dutycycle)[bVar8] = (&solenoid_SL_demand)[bVar8];
    }
  }
  else {
    solenoid_SL_dutycycle = solenoid_SL_demand;
    for (bVar8 = 0; bVar8 < 6; bVar8 = bVar8 + 1) {
      (&DAT_400063dc)[bVar8] =
           (short)((int)(((uint)(ushort)(&DAT_40002394)[bVar8] -
                         (uint)*(ushort *)(&PTR_PTR_40001060)[bVar8]) * 10000) /
                  (int)((uint)*(ushort *)(&PTR_DAT_40001048)[bVar8] -
                       (uint)*(ushort *)(&PTR_PTR_40001060)[bVar8]));
      sVar3 = (&solenoid_SL_demand)[bVar8 + 1] - (&DAT_400063dc)[bVar8];
      (&DAT_400058f0)[bVar8] = sVar3;
      (&DAT_400062c8)[(uint)bVar8 * 8] =
           (sVar3 / 10 + (sVar3 >> 0xf)) -
           ((short)((short)((int)sVar3 / 0xa0000) + (sVar3 >> 0xf)) >> 0xf);
      if ((short)(&DAT_400062c8)[(uint)bVar8 * 8] < 0xc9) {
        if ((short)(&DAT_400062c8)[(uint)bVar8 * 8] < -200) {
          (&DAT_400062c8)[(uint)bVar8 * 8] = 0xff38;
        }
      }
      else {
        (&DAT_400062c8)[(uint)bVar8 * 8] = 200;
      }
      uVar5 = lookup_2D_uint8_interpolated(8,oil_temp_unknown,s__40009836,s__4000982e);
      (&DAT_400062cc)[(uint)bVar8 * 4] =
           (int)((uVar5 & 0xff) *
                (uint)(byte)*(&PTR_DAT_40001078)[bVar8] *
                (int)(short)(&DAT_400062c8)[(uint)bVar8 * 8]) / 0xff;
      uVar5 = lookup_2D_uint8_interpolated(8,oil_temp_unknown,s__40009846,s__4000983e);
      iVar2 = (uVar5 & 0xff) *
              (uint)(byte)*(&PTR_DAT_40001090)[bVar8] * (int)(short)(&DAT_400062c8)[(uint)bVar8 * 8]
      ;
      (&DAT_400062d4)[(uint)bVar8 * 4] = (&DAT_400062d4)[(uint)bVar8 * 4] + iVar2 % 0x13ec;
      iVar2 = (int)(&DAT_400062d4)[(uint)bVar8 * 4] / 0x13ec +
              iVar2 / 0x13ec + (&DAT_400062d0)[(uint)bVar8 * 4];
      (&DAT_400062d4)[(uint)bVar8 * 4] = (int)(&DAT_400062d4)[(uint)bVar8 * 4] % 0x13ec;
      if (iVar2 < 0x1389) {
        if (iVar2 < -5000) {
          (&DAT_400062d0)[(uint)bVar8 * 4] = &DAT_ffffec78;
        }
        else {
          (&DAT_400062d0)[(uint)bVar8 * 4] = iVar2;
        }
      }
      else {
        (&DAT_400062d0)[(uint)bVar8 * 4] = &DAT_00001388;
      }
      puVar4 = &DAT_00001388 + (&DAT_400062cc)[(uint)bVar8 * 4] + (&DAT_400062d0)[(uint)bVar8 * 4];
      if ((int)puVar4 < 0x2711) {
        if ((int)puVar4 < 0) {
          (&solenoid_SL_dutycycle)[bVar8 + 1] = 0;
        }
        else {
          (&solenoid_SL_dutycycle)[bVar8 + 1] = (short)puVar4;
        }
      }
      else {
        (&solenoid_SL_dutycycle)[bVar8 + 1] = 10000;
      }
    }
  }
  if ((DAT_40001678 & 1) == 0) {
    if ((DAT_40001678 & 2) == 0) {
      if ((int)(short)solenoid_SL_dutycycle < (int)(uint)DAT_40008f74) {
        if ((int)(short)solenoid_SL_dutycycle <= (int)(uint)DAT_40008f74) {
          REG_SIU_GPDO191 = 0;
        }
      }
      else {
        REG_SIU_GPDO191 = 1;
      }
    }
    else {
      REG_SIU_GPDO191 = 0;
    }
  }
  else if (((((DAT_40002d61 & 8) == 0) || ((DAT_40002d61 & 4) != 0)) || (DAT_400023a3 == '\0')) &&
          ((((DAT_40001678 & 0x2000000) != 0 ||
            (((DAT_40001678 & 0x800000) != 0 && ((DAT_40001678 & 0x1000000) != 0)))) ||
           ((uVar5 = get_shift_lever_pos_raw___(),
            (int)(uVar5 & 0xffff) < (int)((uint)DAT_40002bd8 - (uint)DAT_40009012) ||
            (uVar5 = get_shift_lever_pos_raw___(),
            (uint)DAT_40002bd8 + (uint)DAT_40009012 < (uVar5 & 0xffff))))))) {
    REG_SIU_GPDO191 = 0;
  }
  else {
    REG_SIU_GPDO191 = 1;
  }
  REG_SIU_GPDO91 = 1;
  REG_SIU_GPDO92 = 1;
  REG_SIU_GPDO96 = 1;
  REG_SIU_GPDO98 = 1;
  REG_SIU_GPDO99 = 1;
  REG_SIU_GPDO100 = 1;
  REG_SIU_GPDO135 = 1;
  REG_SIU_GPDO86 = 1;
  if (((DAT_40001678 & 1) == 0) && ((DAT_40001678 & 2) == 0)) {
    REG_SIU_GPDO136 = 1;
  }
  else {
    REG_SIU_GPDO136 = 0;
  }
  if (((DAT_40001678 & 2) == 0) || ((DAT_40001678 & 1) != 0)) {
    REG_SIU_GPDO137 = 1;
  }
  else {
    REG_SIU_GPDO137 = 0;
  }
  if ((DAT_40001678 & 1) == 0) {
    if ((DAT_40001678 & 2) == 0) {
      eTPU_calculate_and_set_channel_value(0x18,10000 - solenoid_SL1_dutycycle);
      eTPU_calculate_and_set_channel_value(0x19,10000 - solenoid_SL2_dutycycle);
      eTPU_calculate_and_set_channel_value(0x1a,10000 - solenoid_SL3_dutycycle);
      eTPU_calculate_and_set_channel_value(0x1b,10000 - solenoid_SL4_dutycycle);
      eTPU_calculate_and_set_channel_value(0x1c,10000 - solenoid_SLU_dutycycle);
      eTPU_calculate_and_set_channel_value(0x1d,10000 - solenoid_SLT_dutycycle);
    }
    else {
      eTPU_calculate_and_set_channel_value(0x18,&DAT_00002710);
      eTPU_calculate_and_set_channel_value(0x19,&DAT_00002710);
      eTPU_calculate_and_set_channel_value(0x1a,&DAT_00002710);
      eTPU_calculate_and_set_channel_value(0x1b,&DAT_00002710);
      eTPU_calculate_and_set_channel_value(0x1c,&DAT_00002710);
      eTPU_calculate_and_set_channel_value(0x1d,&DAT_00002710);
    }
  }
  else {
    eTPU_calculate_and_set_channel_value(0x18,&DAT_00002710);
    eTPU_calculate_and_set_channel_value(0x19,&DAT_00002710);
    eTPU_calculate_and_set_channel_value(0x1a,&DAT_00002710);
    eTPU_calculate_and_set_channel_value(0x1b,&DAT_00002710);
    eTPU_calculate_and_set_channel_value(0x1c,&DAT_00002710);
    eTPU_calculate_and_set_channel_value(0x1d,&DAT_0000afc8);
  }
  if ((shift_profile_index < 0x13) && (ips_gear_cur == (GEAR_INVALID8|GEAR_INVALID7))) {
    compute_shift_target_speed(shift_profile_index,input_shaft_speed);
    if (DAT_40001b9c == 0x7ff) {
      DAT_40001b9e = 0xff;
      DAT_40001b9f = 7;
    }
    else {
      DAT_40001b9e = (undefined1)DAT_40001b9c;
      DAT_40001b9f = (byte)((ushort)DAT_40001b9c >> 8) | 0x80;
    }
  }
  else {
    DAT_40001b9e = 0xff;
    DAT_40001b9f = 7;
  }
  if ((ips_gear_cur == (GEAR_INVALID8|GEAR_INVALID7)) &&
     (((shift_from_gear == GEAR_INVALID9 || (shift_from_gear == NEUTRAL)) ||
      (shift_from_gear == GEAR_REV)))) {
    DAT_40001aca = DAT_40001aca | 4;
  }
  else {
    DAT_40001aca = DAT_40001aca & 0xfb;
  }
  return;
}



void update_trans_signal_moving_avg(void)

{
  DAT_400014a6 = DAT_40008f3f;
  if (DAT_40008fea != '\0') {
    if (0x80 < DAT_40008f3f) {
      DAT_400014a6 = 0x80;
    }
    if (DAT_400014a6 != DAT_400014a7) {
      DAT_40001b55 = 0;
      DAT_40001b56 = '\0';
      DAT_40005900 = 0;
      DAT_40005904 = 0;
      DAT_40005908 = 0;
      DAT_4000590c = 0;
      DAT_40005910 = 0;
      DAT_40005914 = 0;
    }
    if (DAT_40001b56 != '\0') {
      DAT_40005900 = DAT_40005900 - (uint)(ushort)(&DAT_40005918)[DAT_40001b55];
      DAT_40005904 = DAT_40005904 - (uint)(ushort)(&DAT_40005a18)[DAT_40001b55];
      DAT_40005908 = DAT_40005908 - (uint)(ushort)(&DAT_40005b18)[DAT_40001b55];
      DAT_4000590c = DAT_4000590c - (uint)(ushort)(&DAT_40005c18)[DAT_40001b55];
      DAT_40005910 = DAT_40005910 - (uint)(ushort)(&DAT_40005d18)[DAT_40001b55];
      DAT_40005914 = DAT_40005914 - (uint)(ushort)(&DAT_40005e18)[DAT_40001b55];
    }
    DAT_400014a7 = DAT_400014a6;
    (&DAT_40005918)[DAT_40001b55] = (short)((int)(uint)DAT_40001de8 >> 4);
    (&DAT_40005a18)[DAT_40001b55] = (short)((int)(uint)DAT_40001dea >> 4);
    (&DAT_40005b18)[DAT_40001b55] = (short)((int)(uint)DAT_40001dec >> 4);
    (&DAT_40005c18)[DAT_40001b55] = (short)((int)(uint)DAT_40001dee >> 4);
    (&DAT_40005d18)[DAT_40001b55] = (short)((int)(uint)DAT_40001df0 >> 4);
    (&DAT_40005e18)[DAT_40001b55] = (short)((int)(uint)DAT_40001df2 >> 4);
    DAT_40005900 = DAT_40005900 + (uint)(ushort)(&DAT_40005918)[DAT_40001b55];
    DAT_40005904 = DAT_40005904 + (uint)(ushort)(&DAT_40005a18)[DAT_40001b55];
    DAT_40005908 = DAT_40005908 + (uint)(ushort)(&DAT_40005b18)[DAT_40001b55];
    DAT_4000590c = DAT_4000590c + (uint)(ushort)(&DAT_40005c18)[DAT_40001b55];
    DAT_40005910 = DAT_40005910 + (uint)(ushort)(&DAT_40005d18)[DAT_40001b55];
    DAT_40005914 = DAT_40005914 + (uint)(ushort)(&DAT_40005e18)[DAT_40001b55];
    DAT_40001b55 = DAT_40001b55 + 1;
    if ((DAT_400014a6 <= DAT_40001b55) && (DAT_40001b55 = 0, DAT_40001b56 == '\0')) {
      DAT_40001b56 = '\x01';
    }
    if (DAT_40001b56 != '\0') {
      DAT_40002394 = (undefined2)(DAT_40005900 / (int)(uint)DAT_400014a6);
      DAT_40002396 = (undefined2)(DAT_40005904 / (int)(uint)DAT_400014a6);
      DAT_40002398 = (undefined2)(DAT_40005908 / (int)(uint)DAT_400014a6);
      DAT_4000239a = (undefined2)(DAT_4000590c / (int)(uint)DAT_400014a6);
      DAT_4000239c = (undefined2)(DAT_40005910 / (int)(uint)DAT_400014a6);
      DAT_4000239e = (undefined2)(DAT_40005914 / (int)(uint)DAT_400014a6);
    }
  }
  return;
}



void compute_shift_target_speed(byte param_1,undefined1 param_2)

{
  byte bVar1;
  bool bVar2;
  short sVar3;
  uint uVar4;
  short sVar5;
  
  if (((shift_mode_word & 0xf) == 6) && (slip_settle_timer == '\0')) {
    downshift_sync_complete = true;
  }
  if (shift_closed_loop_active) {
    if ((shift_from_gear == GEAR_1) && (shift_to_gear == GEAR_2)) {
      uVar4 = lookup_3D_uint8_interpolated
                        (8,8,input_shaft_load,input_shaft_speed,
                         CAL_shift_slip_threshold_adaptive_1_2,
                         CAL_shift_slip_threshold_adaptive_1_2_X_load,
                         CAL_shift_slip_threshold_adaptive_1_2_Y_input_speed);
    }
    else if ((shift_from_gear == GEAR_2) && (shift_to_gear == GEAR_3)) {
      uVar4 = lookup_3D_uint8_interpolated
                        (8,8,input_shaft_load,input_shaft_speed,
                         CAL_shift_slip_threshold_adaptive_2_3,
                         CAL_shift_slip_threshold_adaptive_2_3_X_load,
                         CAL_shift_slip_threshold_adaptive_2_3_Y_input_speed);
    }
    else if ((shift_from_gear == GEAR_3) && (shift_to_gear == GEAR_4)) {
      uVar4 = lookup_3D_uint8_interpolated
                        (8,8,input_shaft_load,input_shaft_speed,
                         CAL_shift_slip_threshold_adaptive_3_4,
                         CAL_shift_slip_threshold_adaptive_3_4_X_load,
                         CAL_shift_slip_threshold_adaptive_3_4_Y_input_speed);
    }
    else if ((shift_from_gear == GEAR_4) && (shift_to_gear == GEAR_5)) {
      uVar4 = lookup_3D_uint8_interpolated
                        (8,8,input_shaft_load,input_shaft_speed,
                         CAL_shift_slip_threshold_adaptive_4_5,
                         CAL_shift_slip_threshold_adaptive_4_5_X_load,
                         CAL_shift_slip_threshold_adaptive_4_5_Y_input_speed);
    }
    else {
      uVar4 = lookup_3D_uint8_interpolated
                        (8,8,input_shaft_load,input_shaft_speed,
                         CAL_shift_slip_threshold_adaptive_5_6,
                         CAL_shift_slip_threshold_adaptive_5_6_X_load,
                         CAL_shift_slip_threshold_adaptive_5_6_Y_input_speed);
    }
  }
  else if ((shift_from_gear == GEAR_1) && (shift_to_gear == GEAR_2)) {
    uVar4 = (uint)CAL_shift_slip_threshold_static_1_2;
  }
  else if ((shift_from_gear == GEAR_2) && (shift_to_gear == GEAR_3)) {
    uVar4 = (uint)CAL_shift_slip_threshold_static_2_3;
  }
  else if ((shift_from_gear == GEAR_3) && (shift_to_gear == GEAR_4)) {
    uVar4 = (uint)CAL_shift_slip_threshold_static_3_4;
  }
  else if ((shift_from_gear == GEAR_4) && (shift_to_gear == GEAR_5)) {
    uVar4 = (uint)CAL_shift_slip_threshold_static_4_5;
  }
  else {
    uVar4 = (uint)CAL_shift_slip_threshold_static_5_6;
  }
  if (((((shift_mode_word & 0xf) == 5) &&
       (((((shift_substage == '\x02' && (DAT_40009035 == '\0')) ||
          ((shift_substage == '\x02' &&
           (((int)((uVar4 & 0xff) << 1) < (int)trans_slip_metric && (DAT_40009035 == '\x01')))))) ||
         ((gear_state == 0xf && (DAT_40009035 == '\x02')))) ||
        (((gear_state == 0xf && (DAT_40001bb1 == DAT_40001bb2)) && (DAT_40009035 == '\x03')))))) ||
      ((((shift_mode_word & 0xf) == 6 && (trans_slip_metric < (short)(ushort)DAT_40008f0d)) &&
       (downshift_sync_complete == false)))) && (param_1 != 0)) {
    bVar2 = false;
    if (DAT_40001b9c == 0x7ff) {
      if (DAT_40001b5c < DAT_4000172a) {
        DAT_40001b5e = DAT_4000172a;
        DAT_40001b58 = (int)DAT_4000172a << 8;
        DAT_40001b9c = DAT_4000172a;
      }
      else {
        DAT_40001b5e = DAT_40001b5c;
        DAT_40001b58 = (int)DAT_40001b5c << 8;
        DAT_40001b9c = DAT_40001b5c;
      }
    }
    else {
      DAT_40001b5e = DAT_40001b5c;
    }
  }
  else {
    bVar2 = true;
    if (param_1 < 0x13) {
      DAT_40001b60 = lookup_2D_uint8_interpolated
                               (8,param_2,ZEXT48((&PTR_DAT_0008ddf0)[param_1]) + 8,
                                (&PTR_DAT_0008ddf0)[param_1]);
      sVar5 = (ushort)**(byte **)(&DAT_0008ded4 + (uint)param_1 * 4) << 1;
    }
    else {
      DAT_40001b60 = 0xff;
      sVar5 = 0;
    }
    uVar4 = (int)(short)torque_delivered_post_tc * (uint)DAT_40001b60;
    sVar3 = (short)(uVar4 >> 8) + (ushort)((int)uVar4 < 0 && (uVar4 & 0xff) != 0);
    if (sVar3 < sVar5) {
      sVar3 = sVar5;
    }
    DAT_40001b5c = (sVar3 + -400) * 4;
    if ((int)DAT_40001b9c < (short)torque_alphaN_raw + -0x640) {
      DAT_40001b5e = torque_alphaN_raw - 0x640;
    }
    else {
      DAT_40001b5e = 0x7ff;
      DAT_40001b58 = 0x7ff00;
      DAT_40001b9c = 0x7ff;
    }
  }
  if ((DAT_40009018 != '\0') && (DAT_40001b9c < 0x7ff)) {
    if (bVar2) {
      bVar1 = *(&PTR_DAT_0008de88)[param_1];
    }
    else {
      bVar1 = *(&PTR_DAT_0008de3c)[param_1];
    }
    uVar4 = DAT_40001b58 * (0x100 - (uint)bVar1);
    DAT_40001b58 = ((int)uVar4 >> 8) + (uint)((int)uVar4 < 0 && (uVar4 & 0xff) != 0) +
                   (int)DAT_40001b5e * (uint)bVar1;
    DAT_40001b9c = (short)(DAT_40001b58 >> 8) +
                   (ushort)((int)DAT_40001b58 < 0 && (DAT_40001b58 & 0xff) != 0);
  }
  return;
}



uint clutch_torque_to_pressure(byte element_id,uint torque_demand)

{
  uint uVar1;
  
  uVar1 = 0;
  if (element_id < 8) {
    uVar1 = (int)(short)(&DAT_400023d2)[(uint)element_id * 112] +
            (int)((torque_demand & 0xff) * (int)(short)(&DAT_400023d0)[(uint)element_id * 0x70]) /
            100 & 0xffff;
  }
  return uVar1;
}



// WARNING: Removing unreachable block (ram,0x00083278)
// U660E 6-speed automatic (Aisin) clutch-to-clutch shift controller (param_1=from gear, param_2=to;
// torque converter w/ lock-up). On shift_exec_init loads per-gear-pair cal
// (CAL_shift_profile_index/clutch_element/type, CAL_gear_clutch_bitmask) + per-profile pressure
// curves (CAL_shift_pressure_curve_ptr_a/b, 0x8d9xx-0x8dfxx family). Each cycle loops the friction
// elements computing on-coming/off-going pressures into solenoid_SL_demand[] (SL1=C1, SL2=C2,
// SL3=B1, SL4=C3; SLT=line, SLU=lock-up). Engaged elements accumulate in clutch_mask_current;
// RETURNS 1 when clutch_mask_current == clutch_mask_target (shift complete) else 0.

bool execute_shift(byte param_1,byte param_2)

{
  bool bVar1;
  byte bVar2;
  undefined1 uVar3;
  undefined8 uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  byte bVar10;
  undefined1 uVar11;
  char cVar12;
  ushort uVar9;
  int iVar8;
  uint uVar13;
  byte bVar14;
  byte j;
  uint uVar15;
  
  uVar3 = input_shaft_speed;
  uVar4 = 0x400009cc0;
  uVar15 = (uint)input_shaft_load;
  bVar1 = DAT_40001b6b == '\0';
  DAT_40001b6b = DAT_40001b6b + -1;
  if (bVar1) {
    DAT_40001b6b = '\0';
  }
  uVar13 = uVar15;
  if (uVar15 < 0x17) {
    uVar13 = 0x2e - uVar15 & 0xff;
  }
  clutch_pressure_base_a =
       lookup_2D_uint8_interpolated(8,input_shaft_speed,&DAT_400097b6,&DAT_400097ae);
  clutch_pressure_base_b = lookup_2D_uint8_interpolated(8,uVar3,&DAT_40009d3a,&DAT_40009d32);
  clutch_pressure_base_c = lookup_2D_uint8_interpolated(8,uVar3,&DAT_40009d2a,&DAT_40009d22);
  shift_end_load_dn_light = clutch_pressure_base_a + clutch_pressure_base_c;
  if (0xff < (uint)clutch_pressure_base_a + (uint)clutch_pressure_base_c) {
    shift_end_load_dn_light = 0xff;
  }
  shift_end_load_dn_heavy = 0;
  if (clutch_pressure_base_c < clutch_pressure_base_a) {
    shift_end_load_dn_heavy = clutch_pressure_base_a - clutch_pressure_base_c;
  }
  shift_end_load_up_light = clutch_pressure_base_b + clutch_pressure_base_c;
  if (0xff < (uint)clutch_pressure_base_b + (uint)clutch_pressure_base_c) {
    shift_end_load_up_light = 0xff;
  }
  shift_end_load_up_heavy = 0;
  if (clutch_pressure_base_c < clutch_pressure_base_b) {
    shift_end_load_up_heavy = clutch_pressure_base_b - clutch_pressure_base_c;
  }
  if (shift_exec_init != '\0') {
    DAT_40001b86 = 0;
    DAT_40001b88 = 0;
    DAT_40001b89 = 0;
    if (shift_exec_init == '\x01') {
      shift_phase2_started = '\0';
      shift_torque_phase_hold = '\0';
    }
    DAT_40001c48 = 0;
    shift_phase_cycle_count = 0;
    DAT_40001c44 = 0;
    DAT_40001c4a = 0;
    DAT_40001c43 = 0;
    DAT_40001c42 = 0;
    clutch_mask_target = CAL_gear_clutch_bitmask[param_2];
    DAT_40001bb2 = 0;
    DAT_40001bb1 = 0;
    shift_quality_accumulator = 0;
    shift_adapt_control_flags = 0;
    shift_quality_measured = 0;
    DAT_40001c3e = '\0';
    DAT_40001ba5 = '\0';
    downshift_sync_complete = false;
    clutch_idx_offgoing = 0xff;
    clutch_idx_oncoming = 0xff;
    DAT_40001b8d = '\0';
    DAT_40001b81 = '\0';
    DAT_40001b8e = '\0';
    DAT_40001ba0 = DAT_40008fe1;
    DAT_40001b82 = '\0';
    bVar14 = 2;
    if (param_1 < param_2) {
      bVar14 = 1;
    }
    if ((((bVar14 & 1) == 0) || (uVar15 <= clutch_pressure_base_b)) &&
       (((bVar14 & 2) == 0 || (uVar15 <= clutch_pressure_base_a)))) {
      shift_mode_word = bVar14 | 8;
    }
    else {
      shift_mode_word = bVar14 | 4;
    }
    if (((shift_mode_word & 1) == 0) || (4 < (byte)(param_1 - 1))) {
      DAT_40001b80 = 100;
    }
    else {
      DAT_40001b80 = (&UNK_ffff8047)[(uint)param_1 + (int)uVar4];
    }
    bVar1 = shift_closed_loop_active;
    if (((DAT_40008f4d != '\0') && (shift_adapt_inhibit == '\0')) &&
       ((((DAT_40008f53 != '\0' && (DAT_40001c38 != '\x01')) ||
         (((auto_mode_active != false && (DAT_40001c38 == '\x01')) ||
          ((auto_mode_active == false && ((DAT_40001c38 == '\x01' && (DAT_40008f9f != '\0'))))))))
        && ((CAL_shift_type[(uint)param_2 + (uint)param_1 * 7] == '\x02' &&
            (bVar1 = true, (shift_mode_word | 4) == 0)))))) {
      bVar1 = shift_closed_loop_active;
    }
    shift_closed_loop_active = bVar1;
    if ((param_1 < 7) && (param_2 < 7)) {
      shift_profile_index = CAL_shift_profile_index[(uint)param_2 + (uint)param_1 * 7];
      clutch_elem_offgoing_id = shift_clutch_element[(uint)param_2 + (uint)param_1 * 7];
      clutch_elem_oncoming_id = shift_clutch_element[(uint)param_1 + (uint)param_2 * 7];
    }
    else if (param_2 == 10) {
      shift_profile_index = 0;
      clutch_elem_offgoing_id = 0xff;
      clutch_elem_oncoming_id = 0xff;
    }
    else if ((((byte)(param_1 - 9) < 2) && (param_2 < 2)) || (param_2 == 9)) {
      shift_profile_index = CAL_shift_profile_index[1];
      clutch_elem_offgoing_id = shift_clutch_element[1];
      clutch_elem_oncoming_id = shift_clutch_element[7];
    }
    else {
      shift_profile_index = 0xff;
      clutch_elem_offgoing_id = 0xff;
      clutch_elem_oncoming_id = 0xff;
    }
    if (((shift_closed_loop_active == false) || ((shift_mode_word & 1) == 0)) ||
       (0x12 < shift_profile_index)) {
      pressure_setpoint_oncoming = DAT_40008fec;
      pressure_setpoint_offgoing = DAT_40008fed;
    }
    else {
      pressure_setpoint_oncoming =
           lookup_2D_uint8_interpolated
                     (8,uVar15,ZEXT48(CAL_shift_pressure_curve_ptr_a[shift_profile_index]) + 8,
                      CAL_shift_pressure_curve_ptr_a[shift_profile_index]);
      pressure_setpoint_offgoing =
           lookup_2D_uint8_interpolated
                     (8,uVar15,ZEXT48(CAL_shift_pressure_curve_ptr_b[shift_profile_index]) + 8,
                      CAL_shift_pressure_curve_ptr_b[shift_profile_index]);
    }
    if ((((shift_mode_word & 0xf) == 5) || ((shift_mode_word & 0xf) == 10)) ||
       (((shift_mode_word & 0xf) == 9 && (4 < (byte)(gear_request - GEAR_2))))) {
      shift_substage = '\x01';
      shift_ramp_timer = 10000;
    }
    else {
      shift_substage = '\0';
    }
    iVar5 = int_abs((ulonglong)param_2 - (ulonglong)param_1);
    bVar14 = shift_mode_word | 0x20;
    shift_mode_word = shift_mode_word | 0x10;
    if (1 < iVar5) {
      shift_mode_word = bVar14;
    }
    if ((((DAT_40001c38 == '\x01') && (auto_mode_active != false)) ||
        (((DAT_40001c38 != '\x01' && ((auto_mode_active != false && (DAT_400090b1 <= DAT_40001637)))
          ) || ((auto_mode_active == false &&
                ((DAT_4000914c < shift_aggressiveness_blend &&
                 ((DAT_400090b4 <= DAT_40001637 || (CAL_rpm_engage_min < tach_rpm >> 2)))))))))) &&
       (((DAT_40001678 & DAT_4000916c) == 0 &&
        (((((((shift_mode_word & 0xf) == 10 && (shift_adapt_inhibit == '\0')) &&
            (input_shaft_torque_8bit < clutch_pressure_base_a)) &&
           (((ushort)((ushort)DAT_40008fe7 * 0x28) < input_shaft_rpm && (shift_profile_index < 0x13)
            ))) && ((shift_exec_init != -1 && (DAT_40008f4a < vehicle_speed)))) &&
         (((CAL_rpm_gear1_engage_min < tach_rpm && (gear_request == GEAR_1)) ||
          (GEAR_1 < gear_request)))))))) {
      shift_torque_managed = (&DAT_400010a8)[shift_profile_index];
      if ((gear_request == GEAR_1) && (DAT_40008f4e == '\0')) {
        shift_torque_managed = '\0';
      }
      else if (DAT_40009160 != '\0') {
        DAT_40001bf8 = '\x01';
      }
    }
    else {
      shift_torque_managed = '\0';
    }
    for (bVar14 = 0; bVar14 < 6; bVar14 = bVar14 + 1) {
      (&clutch_elem_pressure_accum)[bVar14] = 0;
      bVar2 = (&UNK_ffff8040)[(uint)bVar14 + (int)uVar4];
      if (((bVar2 & clutch_mask_current) == 0) && ((bVar2 & clutch_mask_target) != 0)) {
        DAT_40001bb2 = DAT_40001bb2 + 1;
        clutch_idx_offgoing = bVar14;
        (&clutch_elem_action)[bVar14] = 2;
      }
      else if (((bVar2 & clutch_mask_current) == 0) || ((bVar2 & clutch_mask_target) != 0)) {
        if (((bVar2 & clutch_mask_current) == 0) || ((bVar2 & clutch_mask_target) == 0)) {
          if (((bVar2 & clutch_mask_current) == 0) && ((bVar2 & clutch_mask_target) == 0)) {
            (&clutch_elem_action)[bVar14] = 0;
            if ((bVar14 != 0) && (bVar14 < 5)) {
              (&solenoid_SL_demand)[bVar14] = (short)((uint)DAT_4000902c * 10000 >> 8);
            }
          }
          else {
            (&clutch_elem_action)[bVar14] = 0;
          }
        }
        else {
          (&clutch_elem_action)[bVar14] = 0;
          if ((bVar14 != 0) && (bVar14 < 5)) {
            (&solenoid_SL_demand)[bVar14] = (short)((uint)DAT_4000902b * 10000 >> 8);
          }
        }
      }
      else {
        DAT_40001bb2 = DAT_40001bb2 + 1;
        clutch_idx_oncoming = bVar14;
        (&clutch_elem_action)[bVar14] = 1;
      }
      if ((&clutch_elem_action)[bVar14] != '\0') {
        if (shift_profile_index < 0x13) {
          DAT_40001bae = *(undefined2 *)(&DAT_0008d9dc + (uint)shift_profile_index * 2);
        }
        else {
          DAT_40001bae = 0;
        }
        (&DAT_40006340)[bVar14] = DAT_40001bae;
        (&clutch_elem_slip_ref)[bVar14] = DAT_40001bae;
        bVar2 = (&clutch_elem_action)[bVar14];
        if (shift_profile_index < 0x13) {
          if (shift_torque_managed == '\0') {
            if ((shift_substage == '\0') && ((&clutch_elem_action)[bVar14] != '\x01')) {
              if (shift_exec_init == -1) {
                (&clutch_elem_ramp_phase)[bVar14] = 1;
              }
              else {
                (&clutch_elem_ramp_phase)[bVar14] = 2;
              }
            }
            else {
              cVar12 = DAT_40008eb3;
              if ((param_2 != 10) && (cVar12 = DAT_40008f38, param_1 != 10)) {
                if (((shift_mode_word & 0xf) == 10) && (DAT_40001ace != '\0')) {
                  cVar12 = '\0';
                }
                else if (((shift_mode_word & 0xf) == 5) &&
                        ((shift_closed_loop_active != false &&
                         ((&clutch_elem_action)[bVar14] == '\x02')))) {
                  cVar12 = '\0';
                }
                else if (((shift_mode_word & 0xf) == 5) &&
                        ((shift_closed_loop_active != false &&
                         ((&clutch_elem_action)[bVar14] == '\x01')))) {
                  DAT_40001b8d = lookup_2D_uint8_interpolated
                                           (8,uVar15,ZEXT48((&PTR_DAT_0008dcc0)[shift_profile_index]
                                                           ) + 8,
                                            (&PTR_DAT_0008dcc0)[shift_profile_index]);
                  cVar12 = '\0';
                }
                else {
                  cVar12 = *(&PTR_DAT_0008da50)
                            [((uint)LZCOUNT(bVar2 - 2) >> 5) * 0x13 + (uint)shift_profile_index];
                }
              }
              if ((cVar12 == '\0') || (shift_exec_init == -1)) {
                (&clutch_elem_ramp_phase)[bVar14] = 1;
              }
              else {
                (&clutch_elem_ramp_phase)[bVar14] = cVar12;
              }
            }
            if ((ulonglong)(LZCOUNT(bVar2 - 2) << 0x20) >> 0x25 == 1) {
              if ((shift_profile_index == 2) || (param_2 == 10)) {
                DAT_40001b84 = 3;
              }
              else if (shift_profile_index == 1) {
                DAT_40001b84 = 2;
              }
              else if (shift_profile_index == 0) {
                DAT_40001b84 = 0;
              }
              else if (clutch_elem_oncoming_id < 8) {
                DAT_40001b84 = (&DAT_0008dfe9)[(uint)clutch_elem_oncoming_id * 10] - 1;
              }
              else {
                DAT_40001b84 = 0xff;
              }
              if (DAT_40001b84 < 4) {
                DAT_40001b85 = (&DAT_40001494)[DAT_40001b84];
                uVar9 = lookup_2D_uint8_interpolated
                                  (8,DAT_40001b85,ZEXT48((&PTR_DAT_0008dfb8)[DAT_40001b84]) + 8,
                                   (&PTR_DAT_0008dfb8)[DAT_40001b84]);
                DAT_40001b86 = uVar9 & 0xff;
                DAT_40001b85 = (&DAT_40001498)[DAT_40001b84];
                uVar9 = lookup_2D_uint8_interpolated
                                  (8,DAT_40001b85,
                                   (ulonglong)*(uint *)((uint)DAT_40001b84 * 4 + 0x8dfc8) + 8,
                                   *(undefined4 *)((uint)DAT_40001b84 * 4 + 0x8dfc8));
                DAT_40001b86 = DAT_40001b86 + (uVar9 & 0xff);
                DAT_40001b88 = lookup_2D_uint8_interpolated
                                         (8,oil_temp_unknown,
                                          (ulonglong)*(uint *)((uint)DAT_40001b84 * 4 + 0x8dfd8) + 8
                                          ,*(undefined4 *)((uint)DAT_40001b84 * 4 + 0x8dfd8));
              }
              else {
                DAT_40001b86 = 0;
                DAT_40001b88 = 0;
              }
              if (shift_torque_phase_hold == '\0') {
                if (param_2 == 10) {
                  uVar7 = get_profile_learned_value(4);
                  uVar7 = uVar7 & 0xff;
                }
                else {
                  if (((((shift_mode_word & 0xf) == 10) && (DAT_40001b84 < 4)) &&
                      ((&DAT_40002e6e)[shift_profile_index] != -1)) &&
                     ((&DAT_40002e6e)[shift_profile_index] != '\0')) {
                    DAT_40001b89 = DAT_4000903f;
                  }
                  else {
                    DAT_40001b89 = 0;
                  }
                  DAT_40001b8c = lookup_2D_uint8_interpolated
                                           (8,uVar15,ZEXT48((&PTR_DAT_0008da04)[shift_profile_index]
                                                           ) + 8,
                                            (&PTR_DAT_0008da04)[shift_profile_index]);
                  uVar7 = get_profile_learned_value(shift_profile_index);
                  uVar7 = (uint)DAT_40001b8c +
                          (((uint)DAT_40001b88 + (uint)DAT_40001b86 + (uVar7 & 0xff)) -
                          (uint)DAT_40001b89);
                }
                if ((int)uVar7 < 0x100) {
                  if ((int)uVar7 < 0) {
                    (&clutch_elem_fill_delay)[bVar14] = 0;
                  }
                  else {
                    (&clutch_elem_fill_delay)[bVar14] = (char)uVar7;
                    (&clutch_elem_fill_delay_reload)[bVar14] = (char)uVar7;
                  }
                }
                else {
                  (&clutch_elem_fill_delay)[bVar14] = 0xff;
                }
                if ((&clutch_elem_fill_delay)[bVar14] == '\0') {
                  (&clutch_elem_fill_delay)[bVar14] = 1;
                }
                (&clutch_elem_prefill_pressure)[bVar14] =
                     *(undefined2 *)(&PTR_DAT_0008db90)[shift_profile_index];
              }
              else {
                (&clutch_elem_fill_delay)[bVar14] = 1;
                (&clutch_elem_prefill_pressure)[bVar14] = 0;
              }
              if (*(&PTR_DAT_0008dc74)[shift_profile_index] == '\0') {
                (&clutch_elem_step_count)[bVar14] = 1;
              }
              else {
                (&clutch_elem_step_count)[bVar14] = *(&PTR_DAT_0008dc74)[shift_profile_index];
              }
            }
            else {
              (&clutch_elem_fill_delay)[bVar14] = 0;
              (&clutch_elem_prefill_pressure)[bVar14] = 0;
              (&clutch_elem_step_count)[bVar14] = 1;
            }
            uVar9 = lookup_2D_uint8_interpolated
                              (8,uVar15,ZEXT48((&PTR_DAT_0008dd0c)[shift_profile_index]) + 8,
                               (&PTR_DAT_0008dd0c)[shift_profile_index]);
            slip_threshold = uVar9 & 0xff;
          }
          else {
            (&clutch_elem_step_count)[bVar14] = 1;
            slip_threshold = (ushort)DAT_400014aa;
            (&clutch_elem_ramp_step)[bVar14] = 0;
            if ((&clutch_elem_action)[bVar14] == '\x01') {
              (&clutch_elem_ramp_phase)[bVar14] = 1;
              (&clutch_elem_fill_delay)[bVar14] = 0;
              (&clutch_elem_prefill_pressure)[bVar14] = 0;
              (&clutch_elem_pressure_endpoint)[bVar14] = 0;
              (&clutch_elem_pressure_cmd)[bVar14] = 0;
            }
            else {
              if (DAT_40001bf8 == '\0') {
                (&clutch_elem_ramp_phase)[bVar14] = DAT_40009080;
              }
              else {
                (&clutch_elem_ramp_phase)[bVar14] = DAT_4000915f;
              }
              (&clutch_elem_fill_delay)[bVar14] = 0;
              if ((&clutch_elem_fill_delay)[bVar14] == '\0') {
                (&clutch_elem_fill_delay)[bVar14] = 1;
              }
              (&clutch_elem_prefill_pressure)[bVar14] = 0;
              uVar7 = lookup_2D_uint8_interpolated
                                (8,oil_temp_unknown,
                                 ZEXT48((&PTR_PTR_0008dda4)[shift_profile_index]) + 8,
                                 (&PTR_PTR_0008dda4)[shift_profile_index]);
              uVar6 = clutch_torque_to_pressure(clutch_elem_oncoming_id,0x17);
              (&clutch_elem_pressure_cmd)[bVar14] =
                   (short)((((uVar7 & 0xff) + 0xff) * (uVar6 & 0xffff)) / 0xff);
            }
          }
        }
        else {
          if (DAT_40009019 == '\0') {
            (&clutch_elem_ramp_phase)[bVar14] = 1;
          }
          else {
            (&clutch_elem_ramp_phase)[bVar14] = DAT_40009019;
          }
          if ((&clutch_elem_action)[bVar14] == '\x02') {
            (&clutch_elem_fill_delay)[bVar14] = DAT_4000901a;
            (&clutch_elem_prefill_pressure)[bVar14] = (short)((uint)DAT_4000901b * 10000 >> 8);
            (&clutch_elem_pressure_cmd)[bVar14] = (short)((uint)DAT_4000901c * 10000 >> 8);
            (&clutch_elem_pressure_endpoint)[bVar14] = (short)((uint)DAT_4000902b * 10000 >> 8);
          }
          else {
            (&clutch_elem_fill_delay)[bVar14] = 0;
            (&clutch_elem_prefill_pressure)[bVar14] = 0;
            (&clutch_elem_pressure_cmd)[bVar14] = (short)((uint)DAT_4000901d * 10000 >> 8);
            (&clutch_elem_pressure_endpoint)[bVar14] = (short)((uint)DAT_4000902c * 10000 >> 8);
          }
          if (DAT_40009020 == '\0') {
            (&clutch_elem_step_count)[bVar14] = 1;
          }
          else {
            (&clutch_elem_step_count)[bVar14] = DAT_40009020;
          }
          slip_threshold = (ushort)DAT_40009021;
          (&clutch_elem_ramp_step)[bVar14] = DAT_40009025;
          DAT_40001b6c = 0;
          DAT_40001b6e = 0;
        }
      }
    }
    DAT_40001b6b = DAT_40008f7a;
    shift_exec_init = '\0';
  }
  if (((((((((shift_end_load_dn_light < uVar15) && ((shift_mode_word & 2) != 0)) &&
           ((shift_mode_word & 8) != 0)) ||
          (((uVar15 < shift_end_load_dn_heavy && ((shift_mode_word & 2) != 0)) &&
           ((shift_mode_word & 4) != 0)))) ||
         ((((shift_end_load_up_light < uVar15 && ((shift_mode_word & 1) != 0)) &&
           ((shift_mode_word & 8) != 0)) ||
          (((uVar15 < shift_end_load_up_heavy && ((shift_mode_word & 1) != 0)) &&
           ((shift_mode_word & 4) != 0)))))) &&
        ((((shift_torque_managed == '\0' && (DAT_40001b9e == -1)) &&
          ((DAT_40001b9f == '\a' && (param_2 != 10)))) &&
         ((param_2 != 1 || (((param_1 != 0 && (param_1 != 10)) && (param_1 != 9)))))))) &&
       (((param_2 != 0 && (param_2 != 9)) || ((param_1 != 10 && (param_1 != 1)))))) &&
      ((param_2 != 1 || (param_1 != 2)))) &&
     ((((clutch_idx_offgoing != 0xff && ((&clutch_elem_fill_delay)[clutch_idx_offgoing] == '\0')) ||
       (shift_torque_phase_hold == '\0')) && (DAT_40001c3e == '\0')))) {
    if (((shift_phase2_started == '\0') ||
        (((uVar15 < shift_end_load_dn_heavy && ((shift_mode_word & 2) != 0)) &&
         ((shift_mode_word & 4) != 0)))) ||
       (((shift_end_load_up_light < uVar15 && ((shift_mode_word & 1) != 0)) &&
        ((shift_mode_word & 8) != 0)))) {
      shift_exec_init = -1;
    }
    shift_phase2_started = '\x01';
  }
  bVar1 = DAT_400014a9 == '\0';
  DAT_400014a9 = DAT_400014a9 + -1;
  if (bVar1) {
    DAT_400014a9 = '\t';
  }
  if (((trans_slip_metric < (short)slip_threshold) &&
      (-(int)(short)slip_threshold < (int)trans_slip_metric)) && (DAT_40001b6b == '\0')) {
    cVar12 = slip_settle_timer + -1;
    if (slip_settle_timer == '\0') {
      cVar12 = '\0';
    }
    slip_settle_timer = cVar12;
    if (((paddle_shift_pending == true) && (2 < param_2)) &&
       (slip_settle_timer = '\0', shift_torque_managed == '\0')) {
      slip_settle_timer = cVar12;
    }
    if ((paddle_shift_pending == true) && (1 < param_1)) {
      slip_settle_timer = '\0';
    }
  }
  else {
    slip_settle_timer = DAT_40008f7b;
    if (shift_profile_index < 0x13) {
      slip_settle_timer = **(char **)(&DAT_0008df20 + (uint)shift_profile_index * 4);
    }
  }
  for (bVar14 = 0; iVar5 = (int)uVar4, bVar14 < 6; bVar14 = bVar14 + 1) {
    if ((&clutch_elem_action)[bVar14] != '\0') {
      bVar2 = (&UNK_ffff8040)[(uint)bVar14 + iVar5];
      if (shift_profile_index < 0x13) {
        DAT_40001b6c = 0;
        DAT_40001b6e = 0;
        if (shift_torque_managed == '\0') {
          if ((&clutch_elem_action)[bVar14] == '\x02') {
            if (((((shift_mode_word & 0xf) == 5) || ((shift_mode_word & 0xf) == 10)) &&
                ((&clutch_elem_fill_delay)[bVar14] == '\x01')) && (DAT_40001b81 == '\0')) {
              DAT_40001b81 = '\x01';
              if ((param_1 == 1) && (param_2 == 2)) {
                shift_ramp_timer = 0;
              }
              else {
                if (shift_closed_loop_active == false) {
                  uVar9 = lookup_2D_uint8_interpolated(8,uVar15,&DAT_4000928c,&DAT_40009284);
                }
                else {
                  uVar9 = lookup_2D_uint8_interpolated(8,uVar15,&DAT_40009826,&DAT_4000981e);
                }
                shift_ramp_timer = (uVar9 & 0xff) * 0x27;
              }
            }
            if (param_2 == 10) {
              uVar7 = lookup_2D_uint8_interpolated
                                (8,oil_temp_unknown,&DAT_4000d4fe,&PTR_DAT_4000d4f6);
              if (tps_commanded < DAT_40008fef) {
                iVar5 = (uint)DAT_40008fe4 +
                        (int)(((uVar7 & 0xff) + 0xff) *
                             ((int)DAT_40001c7c + (DAT_40001c7a * 0x17) / 100)) / 0xff;
              }
              else {
                iVar5 = (uint)DAT_40008fe4 +
                        (int)(((uVar7 & 0xff) + 0xff) *
                             ((int)DAT_40001c7c + (int)(uVar13 * (int)DAT_40001c7a) / 100)) / 0xff;
              }
              if ((int)((uint)DAT_4000902b * 10000) >> 8 < iVar5) {
                (&clutch_elem_pressure_cmd)[bVar14] = (short)((uint)DAT_4000902b * 10000 >> 8);
              }
              else if (iVar5 < 0) {
                (&clutch_elem_pressure_cmd)[bVar14] = 0;
              }
              else {
                (&clutch_elem_pressure_cmd)[bVar14] = (short)iVar5;
              }
              uVar7 = lookup_2D_uint8_interpolated(8,uVar15,&DAT_4000d50e,&DAT_4000d506);
              (&clutch_elem_pressure_endpoint)[bVar14] = (short)((uVar7 & 0xff) * 10000 >> 8);
            }
            else {
              if (((((shift_mode_word & 0xf) == 5) || ((shift_mode_word & 0xf) == 10)) &&
                  (shift_ramp_timer == 0)) ||
                 ((((shift_mode_word & 0xf) == 6 || ((shift_mode_word & 0xf) == 9)) &&
                  (((int)trans_slip_metric < -(int)(short)slip_threshold || (DAT_40001b82 != '\0')))
                  ))) {
                if (DAT_40001b82 == '\0') {
                  uVar7 = lookup_3D_uint8_interpolated
                                    (8,8,uVar15,uVar3,
                                     ZEXT48((&PTR_DAT_0008df6c)[shift_profile_index]) + 0x10,
                                     (&PTR_DAT_0008df6c)[shift_profile_index],
                                     ZEXT48((&PTR_DAT_0008df6c)[shift_profile_index]) + 8);
                  torque_phase_pressure = (short)(((uVar7 & 0xff) * 0x294) / 0xff);
                  DAT_40001b82 = '\x01';
                }
                if ((((shift_closed_loop_active == false) || (DAT_40001ba0 == '\0')) ||
                    ((shift_mode_word & 0xf) != 5)) || (shift_profile_index == 1)) {
                  torque_phase_pressure_pct =
                       ((torque_phase_pressure + 0x3c) * 0xff) / 0x294 + -0x17;
                }
                else {
                  DAT_40001ba0 = DAT_40001ba0 + -1;
                  torque_phase_pressure_pct = 0xff;
                }
              }
              else {
                torque_phase_pressure_pct = 0;
              }
              uVar7 = uVar13;
              if (((shift_profile_index != 0) && (shift_profile_index != 3)) &&
                 (shift_profile_index != 6)) {
                uVar7 = (int)((uVar13 - 0x17) * ((int)&DAT_00002710 - (uint)shift_ramp_timer)) /
                        (int)((uint)pressure_setpoint_offgoing * 0x27) + torque_phase_pressure_pct +
                        0x17;
              }
              DAT_40001bf5 = (undefined1)uVar7;
              bVar10 = lookup_2D_uint8_interpolated
                                 (8,oil_temp_unknown,
                                  ZEXT48((&PTR_PTR_0008dda4)[shift_profile_index]) + 8,
                                  (&PTR_PTR_0008dda4)[shift_profile_index]);
              DAT_40001b62 = bVar10;
              if (shift_profile_index == 0) {
                if (uVar13 < 0x2a) {
                  iVar5 = (bVar10 + 0xff) * ((int)DAT_40002592 + (DAT_40002590 * 0x2a) / 100);
                }
                else {
                  iVar5 = (bVar10 + 0xff) *
                          ((int)DAT_40002592 + (int)(uVar13 * (int)DAT_40002590) / 100);
                }
                iVar5 = iVar5 / 0xff;
                if ((int)((uint)DAT_4000902b * 10000) >> 8 < iVar5) {
                  (&clutch_elem_pressure_cmd)[bVar14] = (short)((uint)DAT_4000902b * 10000 >> 8);
                }
                else if (iVar5 < 0) {
                  (&clutch_elem_pressure_cmd)[bVar14] = 0;
                }
                else {
                  (&clutch_elem_pressure_cmd)[bVar14] = (short)iVar5;
                }
              }
              else if (((clutch_elem_oncoming_id == 0xff) || ((int)uVar7 < 0x18)) ||
                      (((short)torque_delivered_post_tc < 0 && ((shift_mode_word & 0xf) == 9)))) {
                if ((int)uVar7 < 0x100) {
                  if ((int)uVar7 < 0) {
                    uVar7 = 0;
                  }
                }
                else {
                  uVar7 = 0xff;
                }
                uVar7 = clutch_torque_to_pressure(clutch_elem_oncoming_id,uVar7 & 0xff);
                (&clutch_elem_pressure_cmd)[bVar14] =
                     (short)(((bVar10 + 0xff) * (uVar7 & 0xffff)) / 0xff);
              }
              else {
                iVar5 = (int)((bVar10 + 0xff) *
                             ((int)(short)(&DAT_400023d2)[(uint)clutch_elem_oncoming_id * 0x70] +
                             (int)(uVar7 * (int)(short)(&DAT_400023d0)
                                                       [(uint)clutch_elem_oncoming_id * 0x70]) / 100
                             )) / 0xff;
                if (((byte)(param_1 - 1) < 6) &&
                   (*(int *)(&DAT_40005f30 + (param_1 - 1) * 4) < iVar5)) {
                  *(int *)(&DAT_40005f30 + (param_1 - 1) * 4) = iVar5;
                }
                if ((int)((uint)DAT_4000902b * 10000) >> 8 < iVar5) {
                  (&clutch_elem_pressure_cmd)[bVar14] = (short)((uint)DAT_4000902b * 10000 >> 8);
                }
                else if (iVar5 < 0) {
                  (&clutch_elem_pressure_cmd)[bVar14] = 0;
                }
                else {
                  (&clutch_elem_pressure_cmd)[bVar14] = (short)iVar5;
                }
              }
              (&clutch_elem_pressure_endpoint)[bVar14] = (short)((uint)DAT_4000902b * 10000 >> 8);
            }
          }
          else {
            uVar7 = uVar13;
            if (((shift_profile_index != 0) && (shift_profile_index != 3)) &&
               (shift_profile_index != 6)) {
              if (((shift_mode_word & 0xf) == 6) || ((shift_mode_word & 0xf) == 10)) {
                pressure_setpoint_oncoming = 0xff;
              }
              uVar7 = (int)((uVar13 - 0x17) * (uint)shift_ramp_timer) /
                      (int)((uint)pressure_setpoint_oncoming * 0x27) + 0x17;
              if ((int)uVar7 < 0x100) {
                if ((int)uVar7 < 0) {
                  uVar7 = 0;
                }
              }
              else {
                uVar7 = 0xff;
              }
            }
            DAT_40001bf4 = (undefined1)uVar7;
            bVar10 = lookup_2D_uint8_interpolated
                               (8,oil_temp_unknown,
                                ZEXT48((&PTR_PTR_0008dd58)[shift_profile_index]) + 8,
                                (&PTR_PTR_0008dd58)[shift_profile_index]);
            if ((shift_ramp_timer == 0) || ((shift_mode_word & 0xf) == 9)) {
              if (clutch_idx_oncoming == 1) {
                uVar6 = (int)((uint)DAT_40008e7a * 10000) >> 8;
              }
              else if (clutch_idx_oncoming == 2) {
                uVar6 = (int)((uint)DAT_40008e84 * 10000) >> 8;
              }
              else if (clutch_idx_oncoming == 3) {
                uVar6 = (int)((uint)DAT_40008e8e * 10000) >> 8;
              }
              else {
                uVar6 = (int)((uint)DAT_40008e98 * 10000) >> 8;
              }
            }
            else {
              uVar6 = 0;
            }
            DAT_40001b61 = bVar10;
            if (param_1 == 10) {
              uVar7 = lookup_2D_uint8_interpolated(8,uVar15,&DAT_4000d51e,&DAT_4000d516);
              (&clutch_elem_pressure_endpoint)[bVar14] = (short)((uVar7 & 0xff) * 10000 >> 8);
              uVar7 = 0;
            }
            else {
              (&clutch_elem_pressure_endpoint)[bVar14] = (short)((uint)DAT_4000902c * 10000 >> 8);
              uVar7 = clutch_torque_to_pressure(clutch_elem_offgoing_id,uVar7 & 0xff);
              uVar7 = ((bVar10 + 0xff) * (uVar7 & 0xffff)) / 0xff;
            }
            if (uVar6 < uVar7) {
              (&clutch_elem_pressure_cmd)[bVar14] = (short)uVar7 - (short)uVar6;
            }
            else {
              (&clutch_elem_pressure_cmd)[bVar14] = 0;
            }
          }
        }
      }
      uVar7 = (int)trans_slip_metric - (int)(short)(&clutch_elem_slip_ref)[bVar14];
      if ((int)(uint)CAL_shift_quality_accum_bound < (int)uVar7) {
        uVar7 = (uint)CAL_shift_quality_accum_bound;
      }
      else if ((int)uVar7 < (int)-(uint)CAL_shift_quality_accum_bound) {
        uVar7 = -(uint)CAL_shift_quality_accum_bound;
      }
      (&clutch_elem_slip_error)[bVar14] = uVar7;
      if ((((ushort)((ushort)DAT_40008f82 << 3) < DAT_40001c4a) && (DAT_40001c3e == '\0')) &&
         (DAT_40001c3e = '\x01', shift_torque_phase_hold != '\0')) {
        (&clutch_elem_ramp_phase)[bVar14] = 0;
        (&clutch_elem_fill_delay)[bVar14] = 0;
      }
      if ((((byte)(param_1 - 1) < 8) && ((byte)(param_2 - 1) < 8)) &&
         ((((shift_torque_phase_hold != '\0' || (shift_substage == '\0')) ||
           ((param_1 == 2 && (param_2 == 1)))) && ((&clutch_elem_fill_delay)[bVar14] == '\0')))) {
        DAT_40001ba5 = '\x01';
      }
      if (((((shift_mode_word & 0xf) == 5) || ((shift_mode_word & 0xf) == 10)) ||
          ((shift_substage == '\0' &&
           (((shift_mode_word & 0xf) == 6 || ((shift_mode_word & 0xf) == 9)))))) &&
         ((((int)(&clutch_elem_slip_error)[bVar14] < (int)-(uint)DAT_40001491 &&
           (shift_torque_managed == '\0')) ||
          (((clutch_idx_offgoing != 0xff && ((&clutch_elem_step_count)[clutch_idx_offgoing] == '\0')
            ) && (shift_torque_managed != '\0')))))) {
        if ((shift_substage == '\0') && ((&clutch_elem_action)[bVar14] == '\x02')) {
          (&clutch_elem_ramp_phase)[bVar14] = 1;
        }
        shift_substage = '\x02';
      }
      if ((((shift_profile_index < 0x13) && (shift_torque_managed == '\0')) &&
          (((shift_mode_word & 0xf) == 6 || ((shift_mode_word & 0xf) == 9)))) &&
         ((clutch_idx_offgoing != 0xff && ((&clutch_elem_step_count)[clutch_idx_offgoing] != '\0')))
         ) {
        uVar7 = lookup_3D_uint8_interpolated
                          (8,8,uVar15,uVar3,ZEXT48((&PTR_DAT_0008df6c)[shift_profile_index]) + 0x10,
                           (&PTR_DAT_0008df6c)[shift_profile_index],
                           ZEXT48((&PTR_DAT_0008df6c)[shift_profile_index]) + 8);
        torque_phase_pressure = (short)(((uVar7 & 0xff) * 0x294) / 0xff);
        torque_phase_pressure_pct = (uint)((torque_phase_pressure + 0x3c) * 0xff) / 0x294 - 0x17;
        iVar5 = ((int)(((uVar13 - torque_phase_pressure_pct) + -0x17) * 0xff) / (int)(uVar13 - 0x17)
                ) * 0x27;
        if (iVar5 < 0x2711) {
          shift_ramp_timer = 1;
          if (0 < iVar5) {
            shift_ramp_timer = (ushort)iVar5;
          }
        }
        else {
          shift_ramp_timer = 10000;
        }
      }
      if ((&clutch_elem_ramp_phase)[bVar14] == '\x01') {
        if (((&clutch_elem_prefill_pressure)[bVar14] == 0) || (shift_torque_phase_hold != '\0')) {
          (&solenoid_SL_demand)[bVar14] = (&clutch_elem_pressure_cmd)[bVar14];
          (&clutch_elem_fill_delay)[bVar14] = 0;
        }
        else {
          (&solenoid_SL_demand)[bVar14] = (&clutch_elem_prefill_pressure)[bVar14];
          shift_torque_phase_hold = '\x01';
        }
        (&clutch_elem_ramp_phase)[bVar14] = 0;
        (&DAT_40002ba4)[bVar14] = (&DAT_40002ba4)[bVar14] + 1;
      }
      else if ((&clutch_elem_ramp_phase)[bVar14] == '\0') {
        if ((&clutch_elem_fill_delay)[bVar14] == '\x01') {
          (&solenoid_SL_demand)[bVar14] = (&clutch_elem_pressure_cmd)[bVar14];
          (&clutch_elem_fill_delay)[bVar14] = 0;
        }
        else if ((&clutch_elem_fill_delay)[bVar14] == '\0') {
          if ((&clutch_elem_step_count)[bVar14] == '\0') {
            if ((bVar2 & clutch_mask_target) != (bVar2 & clutch_mask_current)) {
              if ((&clutch_elem_action)[bVar14] == '\x01') {
                if (shift_profile_index < 0x13) {
                  if (shift_torque_managed == '\0') {
                    if (DAT_40001c3e == '\0') {
                      if (DAT_40001ba5 == '\0') {
                        if (shift_profile_index == 0) {
                          if (param_2 == 10) {
                            uVar11 = lookup_3D_uint8_interpolated
                                               (8,8,uVar15,uVar3,&DAT_4000d4b6,&DAT_4000d4a6,
                                                &DAT_4000d4ae);
                            (&clutch_elem_ramp_step)[bVar14] = uVar11;
                          }
                          else {
                            uVar11 = lookup_3D_uint8_interpolated
                                               (8,8,uVar15,uVar3,&DAT_40009ce2,&DAT_40009cd2,
                                                &PTR_DAT_40009cda);
                            (&clutch_elem_ramp_step)[bVar14] = uVar11;
                          }
                        }
                        else {
                          (&clutch_elem_ramp_step)[bVar14] = 0;
                        }
                      }
                      else if (((shift_mode_word & 0xf) == 10) && (DAT_40001ace != '\0')) {
                        (&clutch_elem_ramp_step)[bVar14] = DAT_40008f06;
                      }
                      else if (((shift_mode_word & 0xf) == 5) && (engine_flag_1 != '\0')) {
                        (&clutch_elem_ramp_step)[bVar14] = DAT_40008f03;
                      }
                      else {
                        uVar11 = lookup_3D_uint8_interpolated
                                           (8,8,uVar15,decel_magnitude,&DAT_40009d82,&DAT_40009d72,
                                            &DAT_40009d7a);
                        (&clutch_elem_ramp_step)[bVar14] = uVar11;
                      }
                    }
                    else {
                      (&clutch_elem_ramp_step)[bVar14] = DAT_40009016;
                    }
                  }
                }
                else if (DAT_40001c3e != '\0') {
                  (&clutch_elem_ramp_step)[bVar14] = DAT_40009016;
                }
                if ((DAT_400014a9 == '\0') &&
                   ((((DAT_40001bb1 == DAT_40001bb2 &&
                      (((shift_mode_word & 0xf) == 5 || ((shift_mode_word & 0xf) == 10)))) ||
                     ((shift_mode_word & 0xf) == 6)) || ((shift_mode_word & 0xf) == 9)))) {
                  (&clutch_elem_pressure_accum)[bVar14] =
                       (&clutch_elem_pressure_accum)[bVar14] +
                       (uint)(byte)(&clutch_elem_ramp_step)[bVar14];
                }
              }
              else {
                DAT_40001b8e = '\0';
                if (shift_profile_index < 0x13) {
                  if (shift_torque_managed == '\0') {
                    if (DAT_40001c3e == '\0') {
                      if (DAT_40001ba5 == '\0') {
                        if (shift_profile_index == 0) {
                          if (param_2 == 10) {
                            uVar11 = lookup_3D_uint8_interpolated
                                               (8,8,uVar15,uVar3,&DAT_4000d466,&DAT_4000d456,
                                                &DAT_4000d45e);
                            (&clutch_elem_ramp_step)[bVar14] = uVar11;
                          }
                          else {
                            uVar11 = lookup_3D_uint8_interpolated
                                               (8,8,uVar15,uVar3,&DAT_40009c92,&DAT_40009c82,
                                                &DAT_40009c8a);
                            (&clutch_elem_ramp_step)[bVar14] = uVar11;
                          }
                        }
                        else {
                          (&clutch_elem_ramp_step)[bVar14] = 0;
                        }
                      }
                      else if (((shift_mode_word & 0xf) == 10) && (DAT_40001ace != '\0')) {
                        (&clutch_elem_ramp_step)[bVar14] = DAT_40008f06;
                      }
                      else if (((shift_mode_word & 0xf) == 5) && (engine_flag_1 != '\0')) {
                        (&clutch_elem_ramp_step)[bVar14] = DAT_40008f03;
                      }
                      else {
                        uVar11 = lookup_3D_uint8_interpolated
                                           (8,8,uVar15,decel_magnitude,&DAT_40009d82,&DAT_40009d72,
                                            &DAT_40009d7a);
                        (&clutch_elem_ramp_step)[bVar14] = uVar11;
                      }
                    }
                    else {
                      (&clutch_elem_ramp_step)[bVar14] = DAT_40009016;
                    }
                  }
                  else if (DAT_40001bf8 == '\0') {
                    (&clutch_elem_ramp_step)[bVar14] = DAT_40009016 * DAT_40009081;
                  }
                  else {
                    cVar12 = lookup_2D_uint8_interpolated(8,uVar3,&DAT_40009aba,&DAT_40009ab2);
                    (&clutch_elem_ramp_step)[bVar14] = DAT_40009016 * cVar12;
                  }
                }
                else if (DAT_40001c3e != '\0') {
                  (&clutch_elem_ramp_step)[bVar14] = DAT_40009016;
                }
                if (DAT_400014a9 == '\0') {
                  (&clutch_elem_pressure_accum)[bVar14] =
                       (&clutch_elem_pressure_accum)[bVar14] -
                       (uint)(byte)(&clutch_elem_ramp_step)[bVar14];
                }
              }
              if (shift_profile_index < 0x13) {
                uVar9 = lookup_2D_uint8_interpolated
                                  (8,uVar15,ZEXT48((&PTR_DAT_0008dd0c)[shift_profile_index]) + 8,
                                   (&PTR_DAT_0008dd0c)[shift_profile_index]);
                slip_threshold = uVar9 & 0xff;
              }
              if ((DAT_40009017 == '\0') || (shift_torque_managed != '\0')) {
                (&clutch_elem_pressure_delta)[bVar14] = 0;
              }
              else {
                (&clutch_elem_pressure_delta)[bVar14] =
                     (&clutch_elem_pressure_cmd)[bVar14] - (&clutch_elem_pressure_ref)[bVar14];
              }
              if (((param_1 == 0) || (param_1 == 9)) && ((param_2 == 1 || (param_2 == 10)))) {
                (&solenoid_SL_demand)[bVar14] =
                     (&clutch_elem_pressure_delta)[bVar14] +
                     ((short)(&clutch_elem_pressure_hold)[bVar14] -
                     (short)(&clutch_elem_pressure_accum)[bVar14]);
              }
              else if (((param_1 == 1) || (param_1 == 10)) && ((param_2 == 0 || (param_2 == 9)))) {
                if (((((DAT_4000171e & 1) == 0) || ((DAT_4000171e & 0x10) == 0)) ||
                    ((DAT_4000171e & 0x40) == 0)) ||
                   (((DAT_40008ebd <= output_shaft_rpm || (DAT_40008ea2 <= input_shaft_rpm)) ||
                    (tach_rpm == 0)))) {
                  (&solenoid_SL_demand)[bVar14] = 0;
                }
                else if ((param_1 == 1) && (neutral_release_timer_from_drive != '\0')) {
                  (&solenoid_SL_demand)[bVar14] = 1;
                  neutral_release_timer_from_drive = neutral_release_timer_from_drive + -1;
                }
                else if ((param_1 == 10) && (neutral_release_timer_from_reverse != '\0')) {
                  (&solenoid_SL_demand)[bVar14] = 1;
                  neutral_release_timer_from_reverse = neutral_release_timer_from_reverse + -1;
                }
                else {
                  (&solenoid_SL_demand)[bVar14] = (short)((uint)DAT_4000902b * 10000 >> 8);
                }
              }
              else {
                if ((((((shift_mode_word & 0xf) == 5) || ((shift_mode_word & 0xf) == 10)) &&
                     ((int)(&clutch_elem_slip_error)[bVar14] < (int)-(uint)DAT_40001491)) &&
                    (DAT_40001bb1 == DAT_40001bb2)) && ((param_1 != 0 || (param_2 != 1)))) {
                  DAT_40001c4c = 1;
                }
                if ((DAT_40001b8e == '\x01') && ((&clutch_elem_action)[bVar14] == '\x01')) {
                  (&solenoid_SL_demand)[bVar14] = (short)((uint)DAT_4000902c * 10000 >> 8);
                }
                else {
                  (&solenoid_SL_demand)[bVar14] =
                       (&clutch_elem_pressure_delta)[bVar14] +
                       ((short)(&clutch_elem_pressure_hold)[bVar14] -
                       (short)(&clutch_elem_pressure_accum)[bVar14]);
                }
              }
              if ((int)((uint)DAT_4000902b * 10000) >> 8 < (int)(short)(&solenoid_SL_demand)[bVar14]
                 ) {
                (&solenoid_SL_demand)[bVar14] = (short)((uint)DAT_4000902b * 10000 >> 8);
              }
              else if ((int)(short)(&solenoid_SL_demand)[bVar14] <
                       (int)((uint)DAT_4000902c * 10000) >> 8) {
                (&solenoid_SL_demand)[bVar14] = (short)((uint)DAT_4000902c * 10000 >> 8);
              }
              if ((shift_mode_word & 0xf) == 9) {
                shift_ramp_step = DAT_4000914a;
              }
              else if ((shift_mode_word & 0xf) == 5) {
                if (shift_closed_loop_active == false) {
                  shift_ramp_step = DAT_40009146;
                }
                else {
                  shift_ramp_step =
                       lookup_2D_uint16_interpolated
                                 (8,input_shaft_load,u_PPPPJCCC_40009a42,&DAT_40009a32);
                }
              }
              else {
                shift_ramp_step = DAT_40009144;
                if ((shift_mode_word & 0xf) == 10) {
                  shift_ramp_step = DAT_40009148;
                }
              }
              if (((((&clutch_elem_step_count)[bVar14] == '\0') &&
                   ((&clutch_elem_action)[bVar14] == '\x02')) && (shift_ramp_timer != 0)) &&
                 (uVar7 = (uint)shift_ramp_timer,
                 shift_ramp_timer = (ushort)(uVar7 - shift_ramp_step),
                 (int)(uVar7 - shift_ramp_step) < 0)) {
                shift_ramp_timer = 0;
              }
              if ((((((((&clutch_elem_action)[bVar14] == '\x01') && (shift_ramp_timer == 0)) &&
                     (((shift_mode_word & 0xf) == 10 || ((shift_mode_word & 0xf) == 5)))) ||
                    (((((&clutch_elem_action)[bVar14] == '\x01' &&
                       ((short)(&solenoid_SL_demand)[bVar14] <=
                        (short)(&clutch_elem_pressure_endpoint)[bVar14])) &&
                      (shift_torque_managed == '\0')) &&
                     ((DAT_40001b8e == '\0' &&
                      (((((clutch_idx_offgoing != 0xff &&
                          ((short)(&clutch_elem_pressure_endpoint)[clutch_idx_offgoing] <=
                           (short)(&solenoid_SL_demand)[clutch_idx_offgoing])) &&
                         ((&clutch_elem_fill_delay)[clutch_idx_offgoing] == '\0')) ||
                        (((shift_mode_word & 0xf) == 5 || ((shift_mode_word & 0xf) == 10)))) ||
                       (clutch_idx_offgoing == 0xff)))))))) ||
                   ((((&clutch_elem_action)[bVar14] == '\x02' &&
                     ((short)(&clutch_elem_pressure_endpoint)[bVar14] <=
                      (short)(&solenoid_SL_demand)[bVar14])) &&
                    ((shift_torque_managed == '\0' &&
                     ((4 < (byte)(param_1 - 2) || (4 < (byte)(param_2 - 2))))))))) ||
                  (((slip_settle_timer == '\0' && (shift_torque_managed == '\0')) &&
                   ((((shift_mode_word & 0xf) == 5 || ((shift_mode_word & 0xf) == 10)) ||
                    ((((shift_mode_word & 0xf) == 6 || ((shift_mode_word & 0xf) == 9)) &&
                     (shift_ramp_timer == 0)))))))) ||
                 (((shift_torque_managed != '\0' && ((shift_mode_word & 0xf) == 10)) &&
                  ((slip_settle_timer == '\0' || (DAT_4000156a == '\0')))))) {
                DAT_40001c43 = DAT_40001c43 & ~bVar2;
                bVar10 = DAT_40001c42 - 1;
                if (DAT_40001c42 == 0) {
                  bVar10 = DAT_40001c42;
                }
                DAT_40001c42 = bVar10;
                if ((&clutch_elem_action)[bVar14] == '\x02') {
                  (&solenoid_SL_demand)[bVar14] = (short)((uint)DAT_4000902b * 10000 >> 8);
                }
                else {
                  (&solenoid_SL_demand)[bVar14] = (short)((uint)DAT_4000902c * 10000 >> 8);
                  if ((DAT_4000907c < uVar15) &&
                     (((shift_mode_word & 0xf) == 5 || ((shift_mode_word & 0xf) == 10)))) {
                    shift_substage = '\x02';
                  }
                }
                bVar10 = clutch_mask_current & ~bVar2;
                clutch_mask_current = clutch_mask_current | bVar2;
                if ((bVar2 & clutch_mask_target) == 0) {
                  clutch_mask_current = bVar10;
                }
              }
            }
          }
          else {
            DAT_40001b8e = '\0';
            if ((&clutch_elem_step_count)[bVar14] == '\x01') {
              if (((shift_mode_word & 0xf) == 5) || ((shift_mode_word & 0xf) == 10)) {
                (&clutch_elem_step_count)[bVar14] = 0;
              }
              else if ((&clutch_elem_action)[bVar14] == '\x01') {
                (&clutch_elem_step_count)[bVar14] = 0;
              }
              else if (((((shift_mode_word & 0xf) == 9) &&
                        (trans_slip_metric < (short)(ushort)DAT_40008edb)) ||
                       (((shift_mode_word & 0xf) == 6 &&
                        (trans_slip_metric < (short)(ushort)DAT_40008ee5)))) ||
                      ((DAT_40001bb2 < 2 || (0x12 < shift_profile_index)))) {
                (&clutch_elem_step_count)[bVar14] = 0;
                shift_substage = '\x01';
              }
            }
            else {
              (&clutch_elem_step_count)[bVar14] = (&clutch_elem_step_count)[bVar14] + -1;
            }
            if ((&clutch_elem_step_count)[bVar14] == '\0') {
              (&clutch_elem_pressure_ref)[bVar14] = (&clutch_elem_pressure_cmd)[bVar14];
              (&solenoid_SL_demand)[bVar14] = (&clutch_elem_pressure_cmd)[bVar14];
              (&clutch_elem_pressure_hold)[bVar14] = (int)(short)(&solenoid_SL_demand)[bVar14];
              DAT_40001c43 = DAT_40001c43 | bVar2;
              if (DAT_40001c42 != 0xff) {
                DAT_40001c42 = DAT_40001c42 + 1;
              }
              DAT_40001bb1 = DAT_40001bb1 + 1;
            }
          }
        }
        else {
          if (((&clutch_elem_fill_delay)[bVar14] == DAT_40001b8d) && (shift_torque_managed == '\0'))
          {
            DAT_40001b8e = '\x01';
          }
          (&clutch_elem_fill_delay)[bVar14] = (&clutch_elem_fill_delay)[bVar14] + -1;
        }
      }
      else if ((shift_substage != '\0') || ((&clutch_elem_action)[bVar14] == '\x01')) {
        (&clutch_elem_ramp_phase)[bVar14] = (&clutch_elem_ramp_phase)[bVar14] + -1;
      }
      accumulate_shift_quality(bVar14,clutch_pressure_base_a,clutch_pressure_base_b);
    }
  }
  if (DAT_40001a8d != '\0') {
    for (bVar14 = 1; bVar14 < 6; bVar14 = bVar14 + 1) {
      (&solenoid_SL_demand)[bVar14] = 0;
    }
    solenoid_SL1_demand = (undefined2)((uint)DAT_4000902b * 10000 >> 8);
    clutch_mask_target = 0x10;
    clutch_mask_current = 0x10;
    param_1 = 1;
    param_2 = 1;
    DAT_40001a8d = '\0';
  }
  if ((gear_request == NEUTRAL) &&
     (((DAT_40008ebd < output_shaft_rpm || (DAT_40008ea2 < input_shaft_rpm)) ||
      ((ips_gear_cur == (GEAR_INVALID8|GEAR_INVALID7) && (param_2 != 0)))))) {
    for (bVar14 = 0; bVar14 < 6; bVar14 = bVar14 + 1) {
      (&solenoid_SL_demand)[bVar14] = 0;
    }
    clutch_mask_current = clutch_mask_target;
  }
  bVar1 = clutch_mask_current == clutch_mask_target;
  if (bVar1) {
    finalize_shift_quality(shift_profile_index);
    post_shift_adaptation_grader
              (param_1,param_2,clutch_elem_oncoming_id,clutch_elem_offgoing_id,DAT_40001b86,
               DAT_40001b88,DAT_40001b89);
    set_gear_hold_pressures(param_2);
    shift_closed_loop_active = false;
    DAT_40001bf8 = '\0';
    shift_exec_init = '\x01';
    DAT_40001c4c = 0;
    DAT_40001ba0 = DAT_40008fe1;
    shift_mode_word = 0;
    shift_torque_managed = '\0';
    shift_profile_index = 0xff;
    shift_substage = '\0';
    neutral_release_timer_from_drive =
         lookup_2D_uint8_interpolated
                   (8,oil_temp_unknown,CAL_shift_neutral_release_timer_from_drive,
                    CAL_shift_neutral_release_timer_from_drive_X_oil_temp);
    neutral_release_timer_from_reverse =
         lookup_2D_uint8_interpolated
                   (8,oil_temp_unknown,CAL_shift_neutral_release_timer_from_drive_rev,
                    CAL_shift_neutral_release_timer_from_drive_rev_X_oil_temp);
  }
  for (j = 0; j < 6; j = j + 1) {
    if ((((&UNK_ffff8040)[(uint)j + iVar5] & DAT_40001c43) != 0) && (DAT_40001c42 != 0)) {
      uVar15 = (uint)DAT_40001c42;
      iVar8 = (int)DAT_40001560;
      (&DAT_40005f18)[j] = (&DAT_40005f18)[j] + ((int)DAT_40001560 / (int)(uint)DAT_40001c42) % 1000
      ;
      (&DAT_40002bbc)[j] =
           (int)(&DAT_40005f18)[j] / 1000 + (&DAT_40002bbc)[j] + (iVar8 / (int)uVar15) / 1000;
      (&DAT_40005f18)[j] = (int)(&DAT_40005f18)[j] % 1000;
    }
  }
  if (DAT_40001c4a != 0xffff) {
    DAT_40001c4a = DAT_40001c4a + 1;
  }
  return bVar1;
}



void set_gear_hold_pressures(char param_1)

{
  uchar uVar1;
  uchar uVar2;
  uchar uVar3;
  uchar uVar4;
  undefined2 uVar5;
  byte bVar6;
  byte bVar7;
  
  uVar4 = shift_clutch_element[0x2f];
  uVar3 = shift_clutch_element[0x27];
  uVar2 = shift_clutch_element[0x1f];
  uVar1 = shift_clutch_element[0x17];
  bVar7 = DAT_40009159;
  if (DAT_40009160 == '\0') {
    bVar7 = 0;
  }
  bVar6 = DAT_40008f41;
  if (DAT_40008f4d == '\0') {
    bVar6 = 0;
  }
  if (param_1 == '\x01') {
    solenoid_SL1_demand = (undefined2)((uint)DAT_4000902b * 10000 >> 8);
  }
  else if (param_1 == '\x02') {
    solenoid_SL1_demand = (undefined2)((uint)DAT_4000902b * 10000 >> 8);
    if ((bVar6 & 1) == 0) {
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)shift_clutch_element[0x17] * 10]] =
           (short)((uint)DAT_4000902c * 10000 >> 8);
    }
    else {
      uVar5 = clutch_torque_to_pressure(shift_clutch_element[0x17],DAT_40009033);
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)uVar1 * 10]] = uVar5;
    }
    uVar1 = shift_clutch_element[0x11];
    if ((bVar6 & 2) != 0) {
      uVar5 = clutch_torque_to_pressure(shift_clutch_element[0x11],DAT_40009032);
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)uVar1 * 10]] = uVar5;
    }
    uVar1 = shift_clutch_element[0xf];
    if (((bVar7 & 2) != 0) && ((bVar6 & 2) == 0)) {
      uVar5 = clutch_torque_to_pressure(shift_clutch_element[0xf],DAT_4000915c);
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)uVar1 * 10]] = uVar5;
    }
    if (((bVar7 & 2) == 0) && ((bVar6 & 2) == 0)) {
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)shift_clutch_element[0x11] * 10]] =
           (short)((uint)DAT_4000902b * 10000 >> 8);
    }
  }
  else if (param_1 == '\x03') {
    if ((bVar6 & 1) == 0) {
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)shift_clutch_element[0x1f] * 10]] =
           (short)((uint)DAT_4000902c * 10000 >> 8);
    }
    else {
      uVar5 = clutch_torque_to_pressure(shift_clutch_element[0x1f],DAT_40009033);
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)uVar2 * 10]] = uVar5;
    }
    uVar1 = shift_clutch_element[0x19];
    if ((bVar6 & 2) == 0) {
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)shift_clutch_element[0x1a] * 10]] =
           (short)((uint)DAT_4000902b * 10000 >> 8);
    }
    else {
      uVar5 = clutch_torque_to_pressure(shift_clutch_element[0x19],DAT_40009032);
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)uVar1 * 10]] = uVar5;
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)shift_clutch_element[0x1a] * 10]] =
           (short)((uint)DAT_4000902b * 10000 >> 8);
    }
    uVar1 = shift_clutch_element[0x17];
    if (((bVar7 & 2) != 0) && ((bVar6 & 2) == 0)) {
      uVar5 = clutch_torque_to_pressure(shift_clutch_element[0x17],DAT_4000915c);
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)uVar1 * 10]] = uVar5;
    }
    if (((bVar7 & 2) == 0) && ((bVar6 & 2) == 0)) {
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)shift_clutch_element[0x17] * 10]] =
           (short)((uint)DAT_4000902b * 10000 >> 8);
    }
  }
  else if (param_1 == '\x04') {
    if ((bVar6 & 1) == 0) {
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)shift_clutch_element[0x27] * 10]] =
           (short)((uint)DAT_4000902c * 10000 >> 8);
    }
    else {
      uVar5 = clutch_torque_to_pressure(shift_clutch_element[0x27],DAT_40009033);
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)uVar3 * 10]] = uVar5;
    }
    uVar1 = shift_clutch_element[0x21];
    if ((bVar6 & 2) == 0) {
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)shift_clutch_element[0x21] * 10]] =
           (short)((uint)DAT_4000902b * 10000 >> 8);
    }
    else {
      uVar5 = clutch_torque_to_pressure(shift_clutch_element[0x21],DAT_40009032);
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)uVar1 * 10]] = uVar5;
    }
    uVar1 = shift_clutch_element[0x1f];
    if ((bVar7 & 2) == 0) {
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)shift_clutch_element[0x1f] * 10]] =
           (short)((uint)DAT_4000902b * 10000 >> 8);
    }
    else {
      uVar5 = clutch_torque_to_pressure(shift_clutch_element[0x1f],DAT_4000915c);
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)uVar1 * 10]] = uVar5;
    }
  }
  else if (param_1 == '\x05') {
    if ((bVar6 & 1) == 0) {
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)shift_clutch_element[0x2f] * 10]] =
           (short)((uint)DAT_4000902c * 10000 >> 8);
    }
    else {
      uVar5 = clutch_torque_to_pressure(shift_clutch_element[0x2f],DAT_40009033);
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)uVar4 * 10]] = uVar5;
    }
    uVar1 = shift_clutch_element[0x29];
    if ((bVar6 & 2) != 0) {
      uVar5 = clutch_torque_to_pressure(shift_clutch_element[0x29],DAT_40009032);
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)uVar1 * 10]] = uVar5;
    }
    uVar1 = shift_clutch_element[0x27];
    if ((bVar7 & 2) == 0) {
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)shift_clutch_element[0x26] * 10]] =
           (short)((uint)DAT_4000902b * 10000 >> 8);
    }
    else {
      if ((bVar6 & 2) == 0) {
        uVar5 = clutch_torque_to_pressure(shift_clutch_element[0x27],DAT_4000915c);
        (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)uVar1 * 10]] = uVar5;
      }
      uVar1 = shift_clutch_element[0x26];
      uVar5 = clutch_torque_to_pressure(shift_clutch_element[0x26],DAT_4000915c);
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)uVar1 * 10]] = uVar5;
    }
    if (((bVar7 & 2) == 0) && ((bVar6 & 2) == 0)) {
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)shift_clutch_element[0x29] * 10]] =
           (short)((uint)DAT_4000902b * 10000 >> 8);
    }
  }
  else if (param_1 == '\x06') {
    solenoid_SL2_demand = (undefined2)((uint)DAT_4000902b * 10000 >> 8);
    if ((bVar7 & 2) == 0) {
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)shift_clutch_element[0x2f] * 10]] =
           (short)((uint)DAT_4000902b * 10000 >> 8);
    }
    else {
      uVar5 = clutch_torque_to_pressure(shift_clutch_element[0x2f],DAT_4000915c);
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(uint)uVar4 * 10]] = uVar5;
    }
  }
  return;
}



void compute_input_torque(void)

{
  uint _torque_tmp;
  uint uVar1;
  uint tc_speed_ratio;
  
  _torque_tmp = (int)(short)torque_alphaN_raw - 1600;
  torque_alphaN =
       (short)((int)_torque_tmp >> 2) + (ushort)((int)_torque_tmp < 0 && (_torque_tmp & 3) != 0) +
       400;
  if ((((DAT_40001b9e == -1) && (DAT_40001b9f == '\a')) || (DAT_40008ff0 == '\0')) ||
     (((shift_mode_word & 0xf) == 9 ||
      (engine_torque = torque_alphaN, (shift_mode_word & 0xf) == 10)))) {
    engine_torque =
         ((short)DAT_4000172a >> 2) + (ushort)((short)DAT_4000172a < 0 && (DAT_4000172a & 3) != 0) +
         400;
  }
  DAT_40001ad1 = (undefined1)((((short)engine_torque + 0x3c) * 0xff) / 0x294);
  if (tach_rpm == 0) {
    tc_speed_ratio = 0xff;
    input_shaft_speedratio = 0xff;
  }
  else {
    tc_speed_ratio = ((uint)input_shaft_rpm * 1020) / (uint)tach_rpm;
    input_shaft_speedratio = (undefined2)tc_speed_ratio;
  }
  if (tc_speed_ratio < 256) {
    LEA_shift_adaptation_pi_feedback = (uint8_t)tc_speed_ratio;
    DAT_400018c0 = DAT_400018c0 & 0b11111101;
  }
  else {
    LEA_shift_adaptation_pi_feedback = 0xff;
    if (u16_factor_1_255_4000e3f4 < tc_speed_ratio) {
      DAT_400018c0 = DAT_400018c0 | 0b00000010;
    }
  }
  tc_k_factor = lookup_2D_uint8_interpolated
                          (8,LEA_shift_adaptation_pi_feedback,CAL_torque_model_k_factor,
                           CAL_torque_model_k_factor_X_speed_ratio);
  uVar1 = (int)(short)engine_torque * (uint)tc_k_factor;
  torque_delivered_post_tc =
       (short)((int)uVar1 >> 7) + (ushort)((int)uVar1 < 0 && (uVar1 & 0x7f) != 0);
  uVar1 = (int)(short)torque_alphaN * (uint)tc_k_factor;
  input_shaft_torque_alphaN =
       (short)((int)uVar1 >> 7) + (ushort)((int)uVar1 < 0 && (uVar1 & 0x7f) != 0);
  if ((short)torque_delivered_post_tc < -59) {
    input_shaft_load = 0;
  }
  else if ((short)torque_delivered_post_tc < 600) {
    input_shaft_load = (undefined1)((((short)torque_delivered_post_tc + 0x3c) * 0xff) / 0x294);
  }
  else {
    input_shaft_load = 0xff;
  }
  if ((short)torque_alphaN_raw < 2400) {
    torque_alphaN_raw_8bit = (undefined1)((((short)torque_alphaN_raw + 0xf0) * 0xff) / 0xa50);
  }
  else {
    torque_alphaN_raw_8bit = 0xff;
  }
  if ((short)input_shaft_torque_alphaN < -59) {
    input_shaft_torque_8bit = 0;
  }
  else if ((short)input_shaft_torque_alphaN < 600) {
    input_shaft_torque_8bit = (undefined1)((((short)input_shaft_torque_alphaN + 60) * 0xff) / 660);
  }
  else {
    input_shaft_torque_8bit = 0xff;
  }
  return;
}



// Perform OLS regression

void cal_trend_ols(struct_ols_params *p)

{
  uint uVar1;
  ulonglong i;
  short sVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  byte samples;
  
  sVar2 = 0;
  iVar3 = 0;
  iVar4 = 0;
  iVar5 = 0;
  samples = p->sample_count;
  for (i = 0; (i & 0xff) < (ulonglong)samples; i = i + 1) {
    sVar2 = sVar2 + *(short *)(p[1].padding + (int)((i & 0xff) << 1) + -1);
    iVar3 = iVar3 + (uint)*(ushort *)(p[5].padding + (int)((i & 0xff) << 1) + 0xf);
    iVar4 = iVar4 + (uint)*(ushort *)(p[1].padding + (int)((i & 0xff) << 1) + -1) *
                    (uint)*(ushort *)(p[1].padding + (int)((i & 0xff) << 1) + -1);
    iVar5 = iVar5 + (uint)*(ushort *)(p[1].padding + (int)((i & 0xff) << 1) + -1) *
                    (uint)*(ushort *)(p[5].padding + (int)((i & 0xff) << 1) + 0xf);
  }
  iVar4 = ((iVar5 - (int)(((longlong)(int)sVar2 * (longlong)iVar3 & 0xffffffffU) /
                         (ulonglong)samples)) * 100) /
          (iVar4 - ((int)sVar2 * (int)sVar2) / (int)(uint)samples);
  uVar1 = iVar4 * ((sVar2 * 100) / (int)(uint)samples & 0xffffU);
  i = (longlong)((iVar3 * 100) / (int)(uint)samples) -
      ((longlong)((int)uVar1 / 100 + ((int)uVar1 >> 0x1f)) + (ulonglong)(uVar1 >> 0x1f)) &
      0xffffffff;
  if (iVar4 < 0x7d01) {
    if (iVar4 < -32000) {
      p->slope_x100 = -32000;
    }
    else {
      p->slope_x100 = (short)iVar4;
    }
  }
  else {
    p->slope_x100 = 32000;
  }
  uVar1 = (uint)(i / 100);
  if (uVar1 < 0x7d01) {
    if ((int)uVar1 < -32000) {
      p->intercept = -32000;
    }
    else {
      p->intercept = (short)(i / 100);
    }
  }
  else {
    p->intercept = 32000;
  }
  return;
}



void trans_control_init(void)

{
  byte i;
  
  if (DAT_40002bdc == '\0') {
    DAT_40001aa9 = 1;
  }
  REG_SIU_GPDO91 = 1;
  REG_SIU_GPDO92 = 1;
  REG_SIU_GPDO96 = 1;
  REG_SIU_GPDO98 = 1;
  REG_SIU_GPDO99 = 1;
  REG_SIU_GPDO100 = 1;
  DAT_40001c39 = 0xff;
  DAT_40001bee = DAT_40008f55;
  DAT_40001bed = DAT_40008f57;
  DAT_40001bec = DAT_40008f59;
  DAT_40001beb = DAT_40008f5b;
  init_eMIOS(7,DAT_40009002,0,0);
  init_eMIOS(6,DAT_40009002,0,0);
  select_target_gear();
  for (i = 0; i < 6; i = i + 1) {
    (&solenoid_SL_demand)[i] = 0;
    slip_settle_timer = 0x14;
  }
  solenoid_SLT_demand = 5000;
  init_adaptive_arrays();
  load_active_shift_adapt();
  for (i = 0; i < 8; i = i + 1) {
    count_element_adapt_samples(i);
    (&DAT_40001cb8)[i] = 0;
  }
  slip_learn_status_flags_gear6 = slip_learn_status_flags_gear6 | DAT_40002ba1;
  DAT_40001bde = DAT_40002bd8;
  LEA_shift_adaptation_reset = false;
  shift_closed_loop_active = false;
  shift_lockout_timer = 0;
  return;
}



void init_adaptive_arrays(void)

{
  cal_trend_ols((struct_ols_params *)&DAT_400023d0);
  cal_trend_ols((struct_ols_params *)&DAT_400024b0);
  derive_clutch_pressure_model(8);
  cal_trend_ols((struct_ols_params *)&DAT_40002590);
  derive_clutch_pressure_model(9);
  cal_trend_ols((struct_ols_params *)&DAT_40002670);
  cal_trend_ols((struct_ols_params *)&DAT_40002750);
  cal_trend_ols((struct_ols_params *)&DAT_40002830);
  cal_trend_ols((struct_ols_params *)&DAT_40002910);
  cal_trend_ols((struct_ols_params *)&DAT_400029f0);
  return;
}



void load_active_shift_adapt(void)

{
  byte bVar1;
  
  for (bVar1 = 0; bVar1 < 0x13; bVar1 = bVar1 + 1) {
    (&DAT_40006408)[bVar1] =
         (&LEA_shift_profile_adapt)[(uint)bVar1 * 10 + (uint)(byte)(&DAT_40002b8e)[bVar1]];
  }
  return;
}



void age_shift_adapt_hysteresis(void)

{
  byte bVar1;
  
  for (bVar1 = 0; bVar1 < 0x13; bVar1 = bVar1 + 1) {
    if ((&DAT_40002e6e)[bVar1] == -1) {
      (&DAT_40002e6e)[bVar1] = (&DAT_40002e6e)[bVar1] + -1;
    }
  }
  return;
}



void accumulate_shift_quality(byte param_1,byte param_2,byte param_3)

{
  if (((shift_mode_word & 0xf) == 5) || ((shift_mode_word & 0xf) == 10)) {
    if (shift_substage == '\x01') {
      shift_phase_cycle_count = shift_phase_cycle_count + 1;
      if ((param_1 == clutch_idx_offgoing) && ((&solenoid_SL_demand)[param_1] != 0)) {
        if ((int)(&clutch_elem_slip_error)[param_1] < 0) {
          shift_slip_tail_sum = shift_slip_tail_sum + (&clutch_elem_slip_error)[param_1];
        }
        else {
          shift_slip_tail_sum = 0;
        }
        if ((((shift_mode_word & 0xf) == 5) && (param_2 < input_shaft_load)) ||
           (((shift_mode_word & 0xf) == 10 && (input_shaft_load < param_3)))) {
          if ((shift_quality_accumulator < (int)(100000 - (uint)CAL_shift_quality_accum_bound)) &&
             ((int)(&UNK_fffe7960 + CAL_shift_quality_accum_bound) < shift_quality_accumulator)) {
            shift_quality_accumulator =
                 shift_quality_accumulator + (&clutch_elem_slip_error)[param_1];
          }
          if (CAL_adapt_inhibit_load < input_shaft_load) {
            shift_adapt_control_flags = shift_adapt_control_flags | 1;
          }
        }
        else {
          shift_adapt_control_flags = shift_adapt_control_flags | 3;
        }
      }
    }
    else {
      if (((clutch_idx_oncoming != 0xff) && ((&solenoid_SL_demand)[clutch_idx_oncoming] == 0)) &&
         (shift_adapt_control_flags == 0)) {
        shift_quality_accumulator = shift_quality_accumulator - shift_slip_tail_sum;
      }
      shift_slip_tail_sum = 0;
    }
  }
  else if ((((shift_substage == '\x01') && ((shift_mode_word & 0xf) == 6)) ||
           ((shift_substage == '\x01' && ((shift_mode_word & 0xf) == 9)))) &&
          (param_1 == clutch_idx_offgoing)) {
    shift_phase_cycle_count = shift_phase_cycle_count + 1;
    if (trans_slip_metric < 0) {
      shift_quality_accumulator = shift_quality_accumulator - trans_slip_metric;
    }
  }
  return;
}



void finalize_shift_quality(byte param_1)

{
  if (param_1 < 0x13) {
    shift_quality_measured =
         (shift_quality_accumulator * DAT_0008d9fc) /
         (int)*(short *)(&DAT_0008d9dc + (uint)param_1 * 2);
  }
  return;
}



// WARNING: Unable to use type for symbol _input_shaft_speed
// WARNING: Unable to use type for symbol _input_shaft_load

void post_shift_adaptation_grader
               (byte param_1,byte param_2,undefined8 param_3,undefined8 param_4,short param_5,
               char param_6,undefined1 param_7)

{
  int iVar1;
  ulonglong _paddle_profile;
  int iVar2;
  byte bVar5;
  ulonglong uVar3;
  ushort uVar4;
  undefined1 uVar6;
  undefined **lut;
  uint8_t *lut_00;
  uint8_t _input_shaft_speed;
  uint8_t _input_shaft_load;
  
  _input_shaft_speed = input_shaft_speed;
  _input_shaft_load = input_shaft_load;
  if ((param_1 < 7) && (param_2 < 7)) {
    _paddle_profile = (ulonglong)CAL_shift_profile_index[(uint)param_2 + (uint)param_1 * 7];
  }
  else {
    _paddle_profile = 0xff;
  }
  if (((((shift_torque_managed == '\0') && (_paddle_profile != 0)) && (_paddle_profile != 0xff)) &&
      (((shift_mode_word & 0x20) == 0 && (30 < vehicle_speed)))) &&
     (((shift_adapt_inhibit == '\0' && ((shift_phase2_started == '\0' && (param_5 == 0)))) &&
      (param_6 == '\0')))) {
    if ((shift_mode_word & 0xf) == 5) {
      lut = (undefined **)&DAT_4000cc0e;
      lut_00 = &DAT_4000cc5f;
    }
    else if ((shift_mode_word & 0xf) == 9) {
      lut = &PTR_4000ccb0;
      lut_00 = (uint8_t *)((int)&PTR_DAT_4000cd00 + 1);
    }
    else if ((shift_mode_word & 0xf) == 6) {
      lut = (undefined **)&DAT_4000cfb2;
      lut_00 = (uint8_t *)0x4000d004;
    }
    else {
      lut = (undefined **)&DAT_4000d2b6;
      lut_00 = (uint8_t *)0x4000d308;
    }
    bVar5 = lookup_2D_uint8_binlinear_noaxis
                      (9,3,3,input_shaft_speed,input_shaft_load,(uint8_t *)lut);
    shift_quality_ref_hi = (char)(bVar5 ^ 0x80) * 0x14;
    bVar5 = lookup_2D_uint8_binlinear_noaxis(9,3,3,_input_shaft_speed,_input_shaft_load,lut_00);
    shift_quality_ref_lo = (char)(bVar5 ^ 0x80) * 0x14;
    if ((shift_quality_ref_hi < (int)shift_quality_measured) ||
       ((int)shift_quality_measured < shift_quality_ref_lo)) {
      iVar1 = (shift_quality_ref_hi + shift_quality_ref_lo) / 2;
      if (iVar1 < (int)shift_quality_measured) {
        uVar3 = (ulonglong)shift_quality_measured - (longlong)iVar1;
        iVar2 = ((int)((uVar3 & 0xffffffff) << 8) - (int)uVar3) /
                ((shift_quality_ref_hi - iVar1) * 10);
      }
      else {
        uVar3 = (longlong)iVar1 - (ulonglong)shift_quality_measured;
        iVar2 = ((int)((uVar3 & 0xffffffff) << 8) - (int)uVar3) /
                ((iVar1 + (char)(bVar5 ^ 0x80) * -0x14) * 10);
      }
      if (iVar2 < 256) {
        shift_quality_error = (undefined1)iVar2;
        if (iVar2 < 0) {
          shift_quality_error = 0;
        }
      }
      else {
        shift_quality_error = 0xff;
      }
      if (iVar1 < (int)shift_quality_measured) {
        uVar4 = lookup_2D_uint8_interpolated
                          (8,shift_quality_error,CAL_shift_adapt_gain_pos,
                           CAL_shift_adapt_gain_pos_X_shift_quality_error);
      }
      else {
        uVar4 = lookup_2D_uint8_interpolated
                          (8,shift_quality_error,CAL_shift_adapt_gain_neg,
                           CAL_shift_adapt_gain_neg_X_shift_quality_error);
      }
      shift_adapt_correction = uVar4 & 0xff;
      if ((int)shift_quality_measured <= iVar1) {
        shift_adapt_correction = -shift_adapt_correction;
      }
    }
    else {
      shift_adapt_correction = 0;
    }
  }
  else {
    shift_adapt_correction = 0x7fff;
  }
  if ((((((shift_mode_word & 0xf) != 6) && ((shift_mode_word & 0xf) != 9)) &&
       ((_paddle_profile + 0xfe & 0xff) < 0x11)) &&
      (((clutch_elem_offgoing_id < 8 && (clutch_elem_oncoming_id < 8)) &&
       ((CAL_shift_adapt_mode == '\x02' || (CAL_shift_adapt_mode == '\x03')))))) &&
     (((DAT_40009030 < oil_temp_unknown && (oil_temp_unknown < DAT_40009026)) &&
      (shift_adapt_correction != 0x7fff)))) {
    if ((shift_adapt_control_flags & 1) == 0) {
      commit_shift_adaptation(_paddle_profile,shift_adapt_correction,param_7);
      if ((&DAT_0008e038)[(int)(_paddle_profile << 1)] != -1) {
        uVar6 = get_profile_learned_value(_paddle_profile);
        store_profile_learned_value((&DAT_0008e038)[(int)(_paddle_profile << 1)],uVar6);
      }
      if (*(char *)((int)&PTR_0008e039 + (int)(_paddle_profile << 1)) != -1) {
        uVar6 = get_profile_learned_value(_paddle_profile);
        store_profile_learned_value((&DAT_0008e038)[(int)(_paddle_profile << 1)],uVar6);
      }
    }
    iVar1 = (int)_paddle_profile;
    if (((short)shift_adapt_correction < 1) || ((shift_adapt_control_flags & 2) != 0)) {
      (&DAT_400063a4)[iVar1] = 0;
    }
    else {
      (&DAT_400063a4)[iVar1] = (&DAT_400063a4)[iVar1] + '\x01';
    }
    escalate_shift_relearn();
  }
  return;
}



void mark_shift_for_relearn(enum_t6e_gear gear_cur,enum_t6e_gear gear_next)

{
  byte bVar1;
  
  bVar1 = shift_clutch_element[(uint)gear_next + ((uint)gear_cur * 8 - (uint)gear_cur)];
  if (bVar1 < 8) {
    if (((uint)DAT_40001c18 & 1 << (bVar1 & 0x3f)) == 0) {
      slip_learn_status_flags_gear6 = slip_learn_status_flags_gear6 | (byte)(1 << (bVar1 & 0x3f));
    }
    if (CAL_shift_profile_index[(uint)gear_next + ((uint)gear_cur * 8 - (uint)gear_cur)] < 0x13) {
      (&DAT_40002e6e)
      [CAL_shift_profile_index[(uint)gear_next + ((uint)gear_cur * 8 - (uint)gear_cur)]] = 0xfe;
    }
  }
  return;
}



void escalate_shift_relearn(void)

{
  byte i;
  
  for (i = 0; i < 19; i = i + 1) {
    if (DAT_400090ce <= (byte)(&DAT_400063a4)[i]) {
      if (i == 4) {
        mark_shift_for_relearn(GEAR_2,GEAR_3);
        mark_shift_for_relearn(GEAR_3,GEAR_2);
        if (DAT_40009089 != '\0') {
          mark_shift_for_relearn(GEAR_4,GEAR_5);
          mark_shift_for_relearn(GEAR_5,GEAR_6);
        }
      }
      else if (i == 8) {
        mark_shift_for_relearn(GEAR_3,GEAR_4);
        mark_shift_for_relearn(GEAR_4,GEAR_3);
        mark_shift_for_relearn(GEAR_3,GEAR_5);
        if (DAT_40009089 != '\0') {
          mark_shift_for_relearn(GEAR_5,GEAR_6);
        }
      }
      else if (i == 0xf) {
        mark_shift_for_relearn(GEAR_5,GEAR_4);
        mark_shift_for_relearn(GEAR_4,GEAR_5);
        mark_shift_for_relearn(GEAR_5,GEAR_3);
        if (DAT_40009089 != '\0') {
          mark_shift_for_relearn(GEAR_2,GEAR_3);
        }
      }
      else if (i == 0x10) {
        mark_shift_for_relearn(GEAR_5,GEAR_6);
        mark_shift_for_relearn(GEAR_6,GEAR_5);
        if (DAT_40009089 != '\0') {
          mark_shift_for_relearn(GEAR_3,GEAR_2);
          mark_shift_for_relearn(GEAR_2,GEAR_3);
        }
      }
      (&DAT_400063a4)[i] = 0;
    }
  }
  return;
}



void reset_shift_counters(void)

{
  DAT_40002c8a = 0;
  shift_count_0_1[0] = 0;
  shift_count_0_1[1] = 0;
  shift_count_0_1[2] = 0;
  shift_count_0_1[3] = 0;
  shift_count_0_1[4] = 0;
  shift_count_0_1[5] = 0;
  shift_count_0_1[6] = 0;
  shift_count_2_0 = 0;
  shift_count_2_1 = 0;
  shift_count_2_3 = 0;
  shift_count_2_4 = 0;
  shift_count_3_1 = 0;
  shift_count_3_2 = 0;
  shift_count_3_4 = 0;
  shift_count_3_5 = 0;
  shift_count_4_2 = 0;
  shift_count_4_3 = 0;
  shift_count_4_5 = 0;
  shift_count_4_6 = 0;
  shift_count_5_3 = 0;
  shift_count_5_4 = 0;
  shift_count_5_6 = 0;
  shift_count_6_5 = 0;
  shift_count_6_4 = 0;
  shift_count_9_1 = 0;
  shift_count_10_0 = 0;
  shift_count_10_1 = 0;
  return;
}



void reset_shift_adaptation_history(void)

{
  LEA_shift_adaptation_history_valid = false;
  LEA_shift_adaptation = 0;
  LEA_shift_adaptation_history_crc = 0;
  return;
}



void init_clutch_slip_adaptation(void)

{
  byte bVar1;
  byte bVar2;
  
  for (bVar1 = 0; bVar1 < 8; bVar1 = bVar1 + 1) {
    for (bVar2 = 0; bVar2 < 0x32; bVar2 = bVar2 + 1) {
      (&DAT_400023e8)[(uint)bVar2 + (uint)bVar1 * 0x70] = 0xff;
      (&DAT_4000244c)[(uint)bVar2 + (uint)bVar1 * 0x70] = 0x1964;
    }
    for (bVar2 = 0; bVar2 < 0x10; bVar2 = bVar2 + 1) {
      (&DAT_400023d4)[(uint)bVar1 * 0xe0 + (uint)bVar2] = 0;
    }
    (&DAT_400023e4)[(uint)bVar1 * 0xe0] = 2;
    (&DAT_400023e5)[(uint)bVar1 * 0xe0] = 0;
    (&DAT_400023e8)[(uint)bVar1 * 0x70] = 0x20;
    (&DAT_400023d6)[(uint)bVar1 * 0xe0] = (&DAT_400023d6)[(uint)bVar1 * 0xe0] + '\x01';
    (&DAT_400023e5)[(uint)bVar1 * 0xe0] = (&DAT_400023e5)[(uint)bVar1 * 0xe0] | 4;
    (&DAT_400023ea)[(uint)bVar1 * 0x70] = 0x5f;
    (&DAT_400023d9)[(uint)bVar1 * 0xe0] = (&DAT_400023d9)[(uint)bVar1 * 0xe0] + '\x01';
    (&DAT_400023e5)[(uint)bVar1 * 0xe0] = (&DAT_400023e5)[(uint)bVar1 * 0xe0] | 0x20;
    (&DAT_400023e6)[(uint)bVar1 * 0x70] = 0;
  }
  DAT_4000244c = DAT_40008f8c;
  DAT_4000244e = DAT_40008f8e;
  DAT_4000252c = DAT_40008f90;
  DAT_4000252e = DAT_40008f92;
  DAT_4000260c = DAT_40008f94;
  DAT_4000260e = DAT_40008fa0;
  DAT_400026ec = DAT_40008fa2;
  DAT_400026ee = DAT_40008fa4;
  DAT_400027cc = DAT_40008fa6;
  DAT_400027ce = DAT_40008fa8;
  DAT_400028ac = DAT_40008faa;
  DAT_400028ae = DAT_40008fac;
  DAT_4000298c = DAT_40008fae;
  DAT_4000298e = DAT_40009042;
  DAT_40002a6c = DAT_40009044;
  DAT_40002a6e = DAT_40009046;
  init_adaptive_arrays();
  return;
}



void reset_element_slip_adaptation(uint param_1)

{
  byte bVar1;
  int iVar2;
  
  for (bVar1 = 2; bVar1 < 0x32; bVar1 = bVar1 + 1) {
    (&DAT_400023e8)[(uint)bVar1 + (param_1 & 0xff) * 0x70] = 0xff;
    (&DAT_4000244c)[(uint)bVar1 + (param_1 & 0xff) * 0x70] = 0x1964;
  }
  for (bVar1 = 0; bVar1 < 0x10; bVar1 = bVar1 + 1) {
    (&DAT_400023d4)[(param_1 & 0xff) * 0xe0 + (uint)bVar1] = 0;
  }
  (&DAT_400023e4)[(param_1 & 0xff) * 0xe0] = 2;
  (&DAT_400023e5)[(param_1 & 0xff) * 0xe0] = 0;
  (&DAT_400023e8)[(param_1 & 0xff) * 0x70] = 0x20;
  (&DAT_4000244c)[(param_1 & 0xff) * 0x70] =
       (&DAT_400023d2)[(param_1 & 0xff) * 0x70] +
       (short)((int)((uint)(ushort)(&DAT_400023e8)[(param_1 & 0xff) * 0x70] *
                    (int)(short)(&DAT_400023d0)[(param_1 & 0xff) * 0x70]) / 100);
  iVar2 = (param_1 & 0xff) * 0xe0;
  (&DAT_400023d6)[iVar2] = (&DAT_400023d6)[iVar2] + '\x01';
  iVar2 = (param_1 & 0xff) * 0xe0;
  (&DAT_400023e5)[iVar2] = (&DAT_400023e5)[iVar2] | 4;
  (&DAT_400023ea)[(param_1 & 0xff) * 0x70] = 0x5f;
  (&DAT_4000244e)[(param_1 & 0xff) * 0x70] =
       (&DAT_400023d2)[(param_1 & 0xff) * 0x70] +
       (short)((int)((uint)(ushort)(&DAT_400023ea)[(param_1 & 0xff) * 0x70] *
                    (int)(short)(&DAT_400023d0)[(param_1 & 0xff) * 0x70]) / 100);
  iVar2 = (param_1 & 0xff) * 0xe0;
  (&DAT_400023d9)[iVar2] = (&DAT_400023d9)[iVar2] + '\x01';
  iVar2 = (param_1 & 0xff) * 0xe0;
  (&DAT_400023e5)[iVar2] = (&DAT_400023e5)[iVar2] | 0x20;
  return;
}



void derive_clutch_pressure_model(byte param_1)

{
  short sVar1;
  int iVar2;
  
  if (param_1 < 4) {
    iVar2 = (int)(short)(&DAT_400023d0)[(uint)(byte)(&DAT_400014b0)[param_1] * 0x70] *
            (int)*(short *)(&PTR_DAT_40001338)[param_1];
    sVar1 = (short)(iVar2 >> 0x1f);
    (&DAT_400023d0)[(uint)param_1 * 0x70] =
         ((short)(iVar2 / 100) + sVar1) - ((short)((short)(iVar2 / 0x640000) + sVar1) >> 0xf);
    iVar2 = (100 - *(short *)(&PTR_DAT_40001338)[param_1]) *
            (int)(short)(&DAT_400023d0)[(uint)(byte)(&DAT_400014b0)[param_1] * 0x70] * 0x17;
    sVar1 = (short)(iVar2 >> 0x1f);
    (&DAT_400023d2)[(uint)param_1 * 0x70] =
         (&DAT_400023d2)[(uint)(byte)(&DAT_400014b0)[param_1] * 0x70] +
         (((short)(iVar2 / 10000) + sVar1) - ((short)((short)(iVar2 / 0x27100000) + sVar1) >> 0xf));
  }
  else if (param_1 == 8) {
    DAT_40001c7a = ((short)((int)((int)DAT_400024b0 * (uint)DAT_40008fe2) / 100) +
                   (DAT_400024b0 >> 0xf)) -
                   ((short)((short)((int)((int)DAT_400024b0 * (uint)DAT_40008fe2) / 0x640000) +
                           (DAT_400024b0 >> 0xf)) >> 0xf);
    iVar2 = (100 - (uint)DAT_40008fe2) * (int)DAT_400024b0 * 0x17;
    sVar1 = (short)(iVar2 >> 0x1f);
    DAT_40001c7c = DAT_400024b2 +
                   (((short)(iVar2 / 10000) + sVar1) -
                   ((short)((short)(iVar2 / 0x27100000) + sVar1) >> 0xf));
  }
  else if (param_1 == 9) {
    DAT_40001c7e = ((short)((int)((int)DAT_40002590 * (uint)DAT_40008fe3) / 100) +
                   (DAT_40002590 >> 0xf)) -
                   ((short)((short)((int)((int)DAT_40002590 * (uint)DAT_40008fe3) / 0x640000) +
                           (DAT_40002590 >> 0xf)) >> 0xf);
    iVar2 = (100 - (uint)DAT_40008fe3) * (int)DAT_40002590 * 0x17;
    sVar1 = (short)(iVar2 >> 0x1f);
    DAT_40001c80 = DAT_40002592 +
                   (((short)(iVar2 / 10000) + sVar1) -
                   ((short)((short)(iVar2 / 0x27100000) + sVar1) >> 0xf));
  }
  return;
}



void reset_shift_profile_adaptation(void)

{
  byte i;
  byte bVar1;
  
  LEA_shift_profile_adapt = CAL_shift_profile_adapt_default[1];
  DAT_40002ada = CAL_shift_profile_adapt_default[2];
  DAT_40002ae4 = CAL_shift_profile_adapt_default[3];
  DAT_40002aee = CAL_shift_profile_adapt_default[4];
  DAT_40002af8 = CAL_shift_profile_adapt_default[5];
  DAT_40002b02 = CAL_shift_profile_adapt_default[6];
  DAT_40002b0c = CAL_shift_profile_adapt_default[7];
  DAT_40002b16 = CAL_shift_profile_adapt_default[8];
  DAT_40002b20 = CAL_shift_profile_adapt_default[9];
  DAT_40002b2a = CAL_shift_profile_adapt_default[10];
  DAT_40002b34 = CAL_shift_profile_adapt_default[0xb];
  DAT_40002b3e = CAL_shift_profile_adapt_default[0xc];
  DAT_40002b48 = CAL_shift_profile_adapt_default[0xd];
  DAT_40002b52 = CAL_shift_profile_adapt_default[0xe];
  DAT_40002b5c = CAL_shift_profile_adapt_default[0xf];
  DAT_40002b66 = CAL_shift_profile_adapt_default[0x10];
  DAT_40002b70 = CAL_shift_profile_adapt_default[0x11];
  DAT_40002b7a = CAL_shift_profile_adapt_default[0x12];
  DAT_40002b84 = CAL_shift_profile_adapt_default[0x13];
  for (i = 0; i < 0x13; i = i + 1) {
    (&DAT_40002b8e)[i] = 0;
    for (bVar1 = 1; bVar1 < 10; bVar1 = bVar1 + 1) {
      (&LEA_shift_profile_adapt)[(uint)i * 10 + (uint)bVar1] = '\0';
    }
  }
  return;
}



void reset_all_shift_adaptation(void)

{
  init_shift_adapt_config();
  init_clutch_slip_adaptation();
  reset_shift_profile_adaptation();
  reset_shift_adaptation_history();
  return;
}



void reset_shift_profile_adapt_service(void)

{
  reset_shift_profile_adaptation();
  return;
}



void init_shift_adapt_config(void)

{
  if (DAT_40009029 == '\x01') {
    shift_adapt_inhibit = 1;
  }
  else if (DAT_40009029 == '\x02') {
    shift_adapt_inhibit = 2;
  }
  else {
    shift_adapt_inhibit = 0;
  }
  if (DAT_40009014 == '\0') {
    DAT_40002ba1 = 0xf0;
    slip_learn_status_flags_gear6 = 0xf0;
  }
  else {
    DAT_40002ba1 = 0xff;
    slip_learn_status_flags_gear6 = 0xff;
  }
  return;
}



undefined8 check_adapt_temp_match(byte param_1,byte param_2)

{
  short sVar1;
  undefined8 uVar2;
  
  uVar2 = 1;
  if (((param_1 < 8) && ((&DAT_40001cb8)[param_1] != '\0')) && (0x17 < param_2)) {
    sVar1 = int_abs((ulonglong)param_2 - (ulonglong)(byte)(&DAT_40001cb8)[param_1]);
    uVar2 = 1;
    if ((int)sVar1 < (int)(DAT_40008ff1 - 0x17)) {
      uVar2 = 0;
    }
  }
  return uVar2;
}



ulonglong select_slip_learn_element
                    (byte param_1,uint param_2,uint param_3,short param_4,undefined1 param_5)

{
  uint uVar1;
  byte bVar2;
  char cVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  
  uVar4 = 0xff;
  DAT_40001c89 = 0;
  for (uVar5 = 0; (uVar5 & 0xff) < 8; uVar5 = uVar5 + 1) {
    uVar1 = (uint)uVar5;
    if (param_1 == (&DAT_0008dfe8)[(uVar1 & 0xff) * 10]) {
      DAT_40001c8b = check_adapt_temp_match(uVar5 & 0xff,param_5);
      if (((((param_2 & 0xff & 1 << (uVar1 & 0x3f)) != 0) &&
           (((uint)DAT_40002ba1 & 1 << (uVar1 & 0x3f)) == 0)) && (DAT_40001c8b == '\x01')) ||
         ((((param_2 & 0xff & 1 << (uVar1 & 0x3f)) != 0 &&
           (((uint)DAT_40002ba1 & 1 << (uVar1 & 0x3f)) != 0)) &&
          (cVar3 = check_adapt_sample_count(uVar5 & 0xff,param_5), cVar3 == '\x01')))) {
        if (DAT_40001c8a == DAT_40001c89) {
          uVar4 = uVar5;
        }
        DAT_40001c89 = DAT_40001c89 + 1;
        if ((param_2 & 0xff & 1 << (uVar1 & 0x3f)) == 0) {
          uVar4 = uVar4 & 0xff | 0x40;
        }
      }
      if (param_4 == 0) {
        if ((param_3 & 0xff & 1 << ((byte)(&DAT_0008dfea)[(uVar1 & 0xff) * 10] - 1 & 0x3f)) != 0) {
          if (DAT_40001c8a == DAT_40001c89) {
            uVar4 = uVar5 & 0xff | 0x10;
          }
          DAT_40001c89 = DAT_40001c89 + 1;
        }
        if ((param_3 & 0xff & 1 << ((byte)(&DAT_0008dfed)[(uVar1 & 0xff) * 10] - 1 & 0x3f)) != 0) {
          if (DAT_40001c8a == DAT_40001c89) {
            uVar4 = uVar5 & 0xff | 0x30;
          }
          DAT_40001c89 = DAT_40001c89 + 1;
        }
      }
    }
    else if (param_1 < (byte)(&DAT_0008dfe8)[(uVar1 & 0xff) * 10]) {
      uVar5 = 8;
    }
  }
  bVar2 = DAT_40001c8a;
  if (DAT_40001c89 != 0) {
    if ((int)(uint)DAT_40001c8a < (int)(DAT_40001c89 - 1)) {
      bVar2 = DAT_40001c8a + 1;
      if (shift_adapt_inhibit == '\x01') {
        bVar2 = DAT_40001c8a;
      }
    }
    else {
      DAT_40001c8a = 0;
      bVar2 = DAT_40001c8a;
    }
  }
  DAT_40001c8a = bVar2;
  return uVar4;
}



byte check_adapt_sample_count(byte param_1,ulonglong param_2)

{
  ulonglong uVar1;
  
  uVar1 = 0;
  DAT_40001c8c = (ushort)(((param_2 & 0xff) << 4) >> 8);
  if (param_1 < 8) {
    uVar1 = (ulonglong)(byte)(&DAT_400023d4)[(uint)param_1 * 0xe0 + (uint)DAT_40001c8c];
  }
  DAT_400014ba = (byte)(((ulonglong)DAT_4000903c | ~uVar1) -
                        ((DAT_4000903c - uVar1 << 0x20) >> 0x21) >> 0x18) >> 7;
  return DAT_400014ba;
}



void learn_clutch_slip_point(byte *param_1,char param_2)

{
  short sVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  short sVar5;
  undefined1 uVar7;
  short sVar6;
  longlong lVar8;
  int iVar9;
  ulonglong uVar10;
  
  bVar2 = input_shaft_load;
  if (clutch_learn_state == 0xff) {
    DAT_40001c96 = 0;
    DAT_40001c9c = '\x01';
    DAT_40001c78 = DAT_400014bf;
    clutch_learn_state = 0xfe;
    clutch_learn_slip_target = DAT_400014bd;
    clutch_learn_settle_counter = -0x38;
    clutch_learn_saved_demand = (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(*param_1 & 0xf) * 10]];
  }
  (&DAT_40001ca0)[*param_1 & 0xf] = 0;
  if (clutch_learn_state == 0) {
    if (clutch_learn_saved_demand != 0) {
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(*param_1 & 0xf) * 10]] =
           clutch_learn_saved_demand;
    }
    clutch_learn_saved_demand = 0;
    clutch_learn_state = 0xff;
    *param_1 = 0xff;
  }
  else {
    if (((int)((uint)clutch_learn_slip_target - (uint)DAT_40008fe8) < (int)shift_slip_filtered) &&
       ((int)shift_slip_filtered < (int)((uint)clutch_learn_slip_target + (uint)DAT_40008fe8))) {
      if (clutch_learn_settle_counter != '\0') {
        clutch_learn_settle_counter = clutch_learn_settle_counter + -1;
      }
    }
    else {
      clutch_learn_settle_counter = -0x38;
    }
    if (clutch_learn_state == 0xfe) {
      if ((*param_1 & 0x40) == 0) {
        if (((int)-(uint)DAT_40008fe8 < (int)shift_slip_filtered) &&
           (shift_slip_filtered < (short)(ushort)DAT_40008fe8)) {
          DAT_400014bc = *(&PTR_DAT_40001348)[*param_1 & 0xf];
        }
        else {
          DAT_400014bc = *(&PTR_DAT_40001368)[*param_1 & 0xf];
        }
        if ((clutch_learn_settle_counter == '\0') || (param_2 != '\0')) {
          clutch_learn_slip_target = DAT_40001c94;
          clutch_learn_settle_counter = -0x38;
          clutch_learn_state = 0xfd;
        }
      }
      else {
        if ((short)(ushort)DAT_40008fe9 < shift_slip_filtered) {
          (&DAT_40001ca0)[*param_1 & 0xf] = 1;
        }
        if (param_2 == '\0') {
          if ((&DAT_40001ca0)[*param_1 & 0xf] == '\0') {
            if (DAT_40001c78 == '\0') {
              clutch_learn_state = 0;
            }
          }
          else {
            slip_learn_status_flags_gear6 =
                 slip_learn_status_flags_gear6 | (byte)(1 << (*param_1 & 0xf));
            clutch_learn_state = 0;
          }
        }
        else {
          clutch_learn_state = 0;
        }
      }
    }
    else if (clutch_learn_state == 0xfd) {
      DAT_400014bc = *(&PTR_DAT_40001368)[*param_1 & 0xf];
      if (param_2 == '\0') {
        if (clutch_learn_settle_counter == '\0') {
          clutch_learn_state = 0;
          DAT_40001c98 = (ushort)bVar2;
          DAT_40001c9a = (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(*param_1 & 0xf) * 10]];
          record_clutch_adapt_sample(*param_1 & 0xf,DAT_40001c98,DAT_40001c9a);
        }
      }
      else {
        clutch_learn_state = 0;
      }
    }
    if ((*param_1 & 0x40) == 0) {
      iVar3 = (int)((longlong)trans_slip_metric - (ulonglong)clutch_learn_slip_target);
      if ((int)(uint)DAT_400014c0 < iVar3) {
        uVar10 = (ulonglong)DAT_400014c0;
      }
      else {
        uVar10 = (longlong)trans_slip_metric - (ulonglong)clutch_learn_slip_target;
        if (iVar3 < (int)-(uint)DAT_400014c0) {
          uVar10 = -(ulonglong)DAT_400014c0;
        }
      }
      uVar7 = int_abs(uVar10);
      DAT_40001ca8 = lookup_2D_uint8_interpolated(8,uVar7,s___>K_400097c6,s__400097be);
      uVar7 = int_abs(uVar10);
      DAT_40001ca9 = lookup_2D_uint8_interpolated(8,uVar7,s____N_40009806,s__400097fe);
      DAT_400014bb = *(&PTR_DAT_40001388)[*param_1 & 0xf];
      iVar3 = (uint)DAT_40001ca8 * (int)uVar10 * (uint)DAT_400014bb;
      sVar5 = (short)(iVar3 >> 0x1f);
      sVar5 = ((short)(iVar3 / 0x19) + sVar5) - ((short)((short)(iVar3 / 0x190000) + sVar5) >> 0xf);
      DAT_40001c9c = DAT_40001c9c + -1;
      if (DAT_40001c9c == '\0') {
        DAT_40001c9c = DAT_400014be;
        uVar4 = (uint)DAT_40001ca9 * (uint)DAT_400014bc * (int)uVar10;
        lVar8 = (longlong)((int)uVar4 / 0x19 + ((int)uVar4 >> 0x1f)) + (ulonglong)(uVar4 >> 0x1f);
        iVar9 = (int)lVar8;
        sVar1 = (short)((ulonglong)lVar8 >> 0x10) >> 0xf;
        iVar3 = DAT_40001c90 + iVar9 % 1000;
        sVar6 = (short)(iVar3 >> 0x1f);
        DAT_40001c96 = DAT_40001c96 +
                       (((short)(iVar3 / 1000) + sVar6) -
                       ((short)((short)(iVar3 / 0x3e80000) + sVar6) >> 0xf)) +
                       (((short)(iVar9 / 1000) + sVar1) -
                       ((short)((short)(iVar9 / 0x3e80000) + sVar1) >> 0xf));
        DAT_40001c90 = iVar3 % 1000;
      }
    }
    else {
      sVar5 = 0;
    }
    sVar6 = clutch_torque_to_pressure(*param_1 & 0xf,bVar2);
    sVar5 = (ushort)DAT_400014c1 + DAT_40001c96 + sVar5 + sVar6;
    if (((int)sVar5 < (int)((uint)DAT_4000902b * 10000) >> 8) &&
       ((int)((uint)DAT_4000902c * 10000) >> 8 < (int)sVar5)) {
      (&solenoid_SL_demand)[(byte)(&DAT_0008dfe9)[(*param_1 & 0xf) * 10]] = sVar5;
    }
    else {
      clutch_learn_state = 0;
    }
  }
  if ((clutch_learn_state != 0) && (clutch_learn_state < 0xfd)) {
    clutch_learn_state = clutch_learn_state - 1;
  }
  return;
}



void commit_shift_adaptation(byte param_1,short param_2,char param_3)

{
  undefined1 uVar1;
  uint uVar2;
  ushort uVar3;
  ushort uVar4;
  
  uVar1 = (&DAT_0008dfe9)[(uint)*(byte *)((int)&PTR_DAT_0008e060 + (uint)param_1) * 10];
  if (CAL_shift_adapt_hysteresis_step == 0xff) {
    uVar2 = 0xfe;
  }
  else {
    uVar2 = (uint)CAL_shift_adapt_hysteresis_step;
  }
  if (param_1 < 0x13) {
    if (param_2 < 0) {
      if ((&DAT_40002e6e)[param_1] != -1) {
        if ((int)(0xff - uVar2) < (int)(uint)(byte)(&DAT_40002e6e)[param_1]) {
          (&DAT_40002e6e)[param_1] = (&DAT_40002e6e)[param_1] + -1;
        }
        else if ((&DAT_40002e6e)[param_1] != '\0') {
          (&DAT_40002e6e)[param_1] = 0xfe;
        }
      }
    }
    else {
      (&DAT_40002e6e)[param_1] = 0xff;
    }
    if ((((((&DAT_40002e6e)[param_1] == '\0') ||
          ((int)(uint)(byte)(&DAT_40002e6e)[param_1] <= (int)(0xff - uVar2))) && (param_2 < 0)) ||
        (0 < param_2)) && (param_3 == '\0')) {
      uVar3 = get_profile_learned_value(param_1);
      uVar3 = param_2 + (uVar3 & 0xff);
      if ((short)uVar3 < 0) {
        uVar4 = 0;
      }
      else {
        uVar4 = uVar3 & 0xff;
        if (0xff < (short)uVar3) {
          uVar4 = 0xff;
        }
      }
      write_solenoid_adapt_config(uVar1,uVar4);
      store_profile_learned_value(param_1,uVar4);
    }
  }
  return;
}



void store_profile_learned_value(uint param_1,uint8_t param_2)

{
  if ((byte)(&DAT_40002b8e)[param_1 & 0xff] < 9) {
    (&DAT_40002b8e)[param_1 & 0xff] = (&DAT_40002b8e)[param_1 & 0xff] + '\x01';
  }
  else {
    (&DAT_40002b8e)[param_1 & 0xff] = 0;
  }
  (&LEA_shift_profile_adapt)[(param_1 & 0xff) * 10 + (uint)(byte)(&DAT_40002b8e)[param_1 & 0xff]] =
       param_2;
  (&DAT_40006408)[param_1 & 0xff] = param_2;
  return;
}



ulonglong get_profile_learned_value(ulonglong param_1)

{
  uint uVar1;
  
  if ((param_1 & 0xff) < 0x13) {
    uVar1 = (uint)param_1;
    (&LEA_shift_profile_adapt)[(uVar1 & 0xff) * 10 + (uint)(byte)(&DAT_40002b8e)[uVar1 & 0xff]] =
         (&DAT_40006408)[uVar1 & 0xff];
    param_1 = (ulonglong)
              (&LEA_shift_profile_adapt)
              [(uVar1 & 0xff) * 10 + (uint)(byte)(&DAT_40002b8e)[uVar1 & 0xff]];
  }
  return param_1;
}



void count_element_adapt_samples(uint param_1)

{
  byte bVar1;
  
  (&DAT_40001c28)[param_1 & 0xff] = 0;
  for (bVar1 = 0; bVar1 < 0x10; bVar1 = bVar1 + 1) {
    if (DAT_4000904e <= (byte)(&DAT_400023d4)[(param_1 & 0xff) * 0xe0 + (uint)bVar1]) {
      (&DAT_40001c28)[param_1 & 0xff] = (&DAT_40001c28)[param_1 & 0xff] + '\x01';
    }
  }
  (&DAT_40001c20)[param_1 & 0xff] = 0;
  for (bVar1 = 0; bVar1 < 0x10; bVar1 = bVar1 + 1) {
    if (DAT_4000904c <= (byte)(&DAT_400023d4)[(param_1 & 0xff) * 0xe0 + (uint)bVar1]) {
      (&DAT_40001c20)[param_1 & 0xff] = (&DAT_40001c20)[param_1 & 0xff] + '\x01';
    }
  }
  return;
}



void compact_element_adapt_table(byte param_1)

{
  int iVar1;
  byte bVar2;
  byte local_10 [16];
  
  if (((&DAT_400023e5)[(uint)param_1 * 0xe0] != -1) &&
     (((DAT_40009024 <= (byte)(&DAT_40001c28)[param_1] ||
       (((CAL_shift_profile_adapt_default[0] <= (byte)(&DAT_400023d6)[(uint)param_1 * 0xe0] &&
         ((((int)(CAL_shift_profile_adapt_default[0] - 1) <=
            (int)(uint)(byte)(&DAT_400023d8)[(uint)param_1 * 0xe0] && (param_1 < 5)) ||
          ((CAL_shift_profile_adapt_default[0] <= (byte)(&DAT_400023d9)[(uint)param_1 * 0xe0] &&
           (4 < param_1)))))) && (shift_adapt_inhibit != '\0')))) &&
      (2 < (byte)(&DAT_400023e4)[(uint)param_1 * 0xe0])))) {
    (&DAT_40001cb0)[param_1] = 0;
    local_10[0] = 2;
    local_10[1] = 5;
    for (bVar2 = 0; bVar2 < 2; bVar2 = bVar2 + 1) {
      if ((1 << (local_10[bVar2] & 0x3f) & (uint)(byte)(&DAT_400023e5)[(uint)param_1 * 0xe0]) != 0)
      {
        iVar1 = (uint)local_10[bVar2] + (uint)param_1 * 0xe0;
        (&LEA_base)[iVar1 + 0x24] = (&LEA_base)[iVar1 + 0x24] + -1;
        (&DAT_40001cb0)[param_1] = (&DAT_40001cb0)[param_1] + '\x01';
      }
    }
    if ((&DAT_40001cb0)[param_1] != '\0') {
      for (bVar2 = (&DAT_40001cb0)[param_1]; bVar2 < 0x32; bVar2 = bVar2 + 1) {
        (&DAT_400023e8)[((uint)bVar2 - (uint)(byte)(&DAT_40001cb0)[param_1]) + (uint)param_1 * 0x70]
             = (&DAT_400023e8)[(uint)bVar2 + (uint)param_1 * 0x70];
        (&DAT_4000244c)[((uint)bVar2 - (uint)(byte)(&DAT_40001cb0)[param_1]) + (uint)param_1 * 0x70]
             = (&DAT_4000244c)[(uint)bVar2 + (uint)param_1 * 0x70];
      }
      for (bVar2 = 0; bVar2 < (byte)(&DAT_40001cb0)[param_1]; bVar2 = bVar2 + 1) {
        (&DAT_400023e8)[(0x32 - (bVar2 + 1)) + (uint)param_1 * 0x70] = 0xff;
        (&DAT_4000244c)[(0x32 - (bVar2 + 1)) + (uint)param_1 * 0x70] = 0x1964;
      }
      (&DAT_400023e4)[(uint)param_1 * 0xe0] =
           (&DAT_400023e4)[(uint)param_1 * 0xe0] - (&DAT_40001cb0)[param_1];
    }
    (&DAT_400023e5)[(uint)param_1 * 0xe0] = 0xff;
  }
  return;
}



void check_element_adapt_drift(uint param_1,byte param_2,ulonglong param_3)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = (uint)param_2 * (int)(short)(&DAT_400023d0)[(param_1 & 0xff) * 0x70];
  iVar2 = int_abs((param_3 & 0xffff) -
                  ((longlong)(short)(&DAT_400023d2)[(param_1 & 0xff) * 0x70] +
                  (longlong)((int)uVar1 / 100 + ((int)uVar1 >> 0x1f)) + (ulonglong)(uVar1 >> 0x1f)))
  ;
  DAT_40001bff = (byte)iVar2;
  if (0xff < iVar2) {
    DAT_40001bff = 0xff;
  }
  (&DAT_40001cb8)[param_1 & 0xff] = param_2;
  if (DAT_40008fe9 < DAT_40001bff) {
    if ((&DAT_40001c30)[param_1 & 0xff] != -1) {
      (&DAT_40001c30)[param_1 & 0xff] = (&DAT_40001c30)[param_1 & 0xff] + '\x01';
    }
  }
  else {
    (&DAT_40001c30)[param_1 & 0xff] = 0;
  }
  if ((byte)(&DAT_40001c30)[param_1 & 0xff] < DAT_400014b8) {
    if ((&DAT_40001c30)[param_1 & 0xff] == '\0') {
      slip_learn_status_flags_gear6 = slip_learn_status_flags_gear6 & ~(byte)(1 << (param_1 & 0x3f))
      ;
      (&DAT_40001cb8)[param_1 & 0xff] = 0;
    }
  }
  else {
    reset_element_slip_adaptation(param_1 & 0xff);
    DAT_40002ba1 = DAT_40002ba1 | (byte)(1 << (param_1 & 0x3f));
    (&DAT_40001c30)[param_1 & 0xff] = 0;
    (&DAT_40001cb8)[param_1 & 0xff] = 0;
  }
  return;
}



void finalize_element_adaptation(uint param_1)

{
  if (((&DAT_400023e5)[(param_1 & 0xff) * 0xe0] == -1) &&
     ((DAT_4000904b <= (byte)(&DAT_40001c20)[param_1 & 0xff] || (shift_adapt_inhibit != '\0')))) {
    if ((3 < (param_1 & 0xff)) &&
       ((shift_adapt_inhibit == '\x01' &&
        ((byte)(&DAT_400023e4)[(uint)(byte)(&DAT_400014b0)[param_1 & 0xff] * 0xe0] < DAT_400014b9)))
       ) {
      derive_clutch_pressure_model((&DAT_400014b0)[param_1 & 0xff]);
      reset_element_slip_adaptation((&DAT_400014b0)[param_1 & 0xff]);
    }
    DAT_40002ba1 = DAT_40002ba1 & ~(byte)(1 << (param_1 & 0x3f));
    slip_learn_status_flags_gear6 = slip_learn_status_flags_gear6 & ~(byte)(1 << (param_1 & 0x3f));
    (&DAT_400023e6)[(param_1 & 0xff) * 0x70] = (&DAT_400023e6)[(param_1 & 0xff) * 0x70] + 1;
    if ((shift_adapt_inhibit != '\0') && (slip_learn_status_flags_gear6 == 0)) {
      shift_adapt_inhibit = '\0';
      DAT_40002ba1 = 0xff;
      slip_learn_status_flags_gear6 = 0xff;
    }
  }
  return;
}



void record_clutch_adapt_sample(uint clutch_element_id,byte load,undefined2 learned_val)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  byte bVar5;
  
  bVar4 = false;
  if (0x17 < load) {
    bVar5 = (&DAT_400023e4)[(clutch_element_id & 0xff) * 0xe0];
    if (bVar5 < 0x32) {
      (&DAT_400023e8)[(uint)bVar5 + (clutch_element_id & 0xff) * 0x70] = (ushort)load;
      (&DAT_4000244c)[(uint)bVar5 + (clutch_element_id & 0xff) * 0x70] = learned_val;
      iVar2 = (clutch_element_id & 0xff) * 0xe0;
      (&DAT_400023e4)[iVar2] = (&DAT_400023e4)[iVar2] + '\x01';
    }
    else {
      bVar5 = 0;
      uVar1 = 0;
      for (uVar3 = 0; (uVar3 & 0xff) < 0x10; uVar3 = uVar3 + 1) {
        if (bVar5 < (byte)(&DAT_400023d4)[(clutch_element_id & 0xff) * 0xe0 + (uVar3 & 0xff)]) {
          bVar5 = (&DAT_400023d4)[(clutch_element_id & 0xff) * 0xe0 + (uVar3 & 0xff)];
          uVar1 = uVar3;
        }
      }
      iVar2 = (uVar1 & 0xff) + (clutch_element_id & 0xff) * 0xe0;
      (&LEA_base)[iVar2 + 0x24] = (&LEA_base)[iVar2 + 0x24] + -1;
      if (((((uVar1 & 0xff) == 2) || ((uVar1 & 0xff) == 5)) &&
          ((&DAT_400023e5)[(clutch_element_id & 0xff) * 0xe0] != -1)) &&
         ((&DAT_400023e5)[(clutch_element_id & 0xff) * 0xe0] != '\0')) {
        iVar2 = (clutch_element_id & 0xff) * 0xe0;
        (&DAT_400023e5)[iVar2] = (&DAT_400023e5)[iVar2] & ~(byte)(1 << (uVar1 & 0x3f));
      }
      for (bVar5 = 0; bVar5 < 0x32; bVar5 = bVar5 + 1) {
        if (bVar4) {
          (&DAT_400023e8)[(bVar5 - 1) + (clutch_element_id & 0xff) * 0x70] =
               (&DAT_400023e8)[(uint)bVar5 + (clutch_element_id & 0xff) * 0x70];
          (&DAT_4000244c)[(bVar5 - 1) + (clutch_element_id & 0xff) * 0x70] =
               (&DAT_4000244c)[(uint)bVar5 + (clutch_element_id & 0xff) * 0x70];
        }
        else if (((int)((uVar1 & 0xff) << 8) >> 4 & 0xffU) <=
                 (uint)(ushort)(&DAT_400023e8)[(uint)bVar5 + (clutch_element_id & 0xff) * 0x70]) {
          if ((uint)(ushort)(&DAT_400023e8)[(uint)bVar5 + (clutch_element_id & 0xff) * 0x70] <
              ((int)(((uVar1 & 0xff) + 1) * 0x100) >> 4 & 0xffU)) {
            bVar4 = true;
          }
        }
      }
      *(ushort *)(&DAT_4000244a + (clutch_element_id & 0xff) * 0xe0) = (ushort)load;
      *(undefined2 *)(&DAT_400024ae + (clutch_element_id & 0xff) * 0xe0) = learned_val;
    }
    iVar2 = ((int)((uint)load << 4) >> 8) + (clutch_element_id & 0xff) * 0xe0;
    (&LEA_base)[iVar2 + 0x24] = (&LEA_base)[iVar2 + 0x24] + '\x01';
    count_element_adapt_samples(clutch_element_id & 0xff);
    compact_element_adapt_table(clutch_element_id & 0xff);
    if (shift_adapt_inhibit != '\x02') {
      cal_trend_ols((struct_ols_params *)(&DAT_400023d0 + (clutch_element_id & 0xff) * 0x70));
    }
    if (((uint)DAT_40002ba1 & 1 << (clutch_element_id & 0x3f)) == 0) {
      check_element_adapt_drift(clutch_element_id & 0xff,load,learned_val);
    }
    else {
      finalize_element_adaptation(clutch_element_id & 0xff);
    }
    if ((clutch_element_id & 0xff) == 1) {
      derive_clutch_pressure_model(8);
    }
    else if ((clutch_element_id & 0xff) == 2) {
      derive_clutch_pressure_model(9);
    }
  }
  return;
}



undefined8 FUN_00088210(undefined4 param_1,undefined4 param_2)

{
  if (DAT_40006428 == 0) {
    DAT_40006420 = param_1;
    DAT_40006424 = param_2;
    DAT_40006428 = 1;
    return 0;
  }
  return 0xffffffffffffffff;
}



void FUN_00088244(int param_1)

{
  if (param_1 != 0) {
    return;
  }
  DAT_40006420 = 0;
  DAT_40006424 = 0;
  DAT_40006428 = 0;
  return;
}



longlong u128_divide_to_u64(uint param_1,uint param_2,ulonglong param_3,ulonglong param_4)

{
  uint uVar1;
  longlong lVar2;
  uint uVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  ulonglong uVar9;
  longlong lVar10;
  uint uVar12;
  ulonglong uVar11;
  bool bVar13;
  bool bVar14;
  
  lVar2 = LZCOUNT(param_1);
  if (param_1 == 0) {
    lVar2 = LZCOUNT(param_2) + 0x20;
  }
  lVar10 = LZCOUNT((int)param_3);
  if ((int)param_3 == 0) {
    lVar10 = LZCOUNT((int)param_4) + 0x20;
  }
  if ((uint)lVar2 <= (uint)lVar10) {
    lVar10 = 0x40 - (lVar10 + 1);
    uVar3 = (uint)lVar2 + (int)lVar10;
    lVar10 = (0x40 - lVar2) - lVar10;
    uVar12 = (uint)lVar10;
    if ((int)uVar12 < 0x20) {
      uVar1 = param_2 >> (uVar12 & 0x3f) | param_1 << (0x20 - uVar12 & 0x3f);
      uVar6 = (ulonglong)(param_1 >> (uVar12 & 0x3f));
    }
    else {
      uVar1 = param_1 >> (uVar12 - 0x20 & 0x3f);
      uVar6 = 0;
    }
    uVar8 = (ulonglong)uVar1;
    if ((int)uVar3 < 0x20) {
      uVar12 = param_1 << (uVar3 & 0x3f) | param_2 >> (0x20 - uVar3 & 0x3f);
      uVar5 = (ulonglong)(param_2 << (uVar3 & 0x3f));
    }
    else {
      uVar12 = param_2 << (uVar3 - 0x20 & 0x3f);
      uVar5 = 0;
    }
    uVar4 = (ulonglong)uVar12;
    bVar13 = false;
    do {
      bVar14 = CARRY8(uVar5,(ulonglong)bVar13) || CARRY8(uVar5,uVar5 + bVar13);
      uVar5 = uVar5 * 2 + (ulonglong)bVar13;
      uVar7 = (ulonglong)bVar14;
      bVar13 = CARRY8(uVar4,uVar7) || CARRY8(uVar4,uVar4 + uVar7);
      uVar4 = uVar4 * 2 + (ulonglong)bVar14;
      uVar7 = (ulonglong)bVar13;
      uVar9 = uVar8 * 2 + (ulonglong)bVar13;
      uVar7 = uVar6 * 2 + (ulonglong)(CARRY8(uVar8,uVar7) || CARRY8(uVar8,uVar8 + uVar7));
      uVar11 = uVar7 - (param_3 + (uVar9 < param_4));
      uVar6 = uVar7;
      uVar8 = uVar9;
      if (-1 < (longlong)uVar11) {
        uVar6 = uVar11;
        uVar8 = uVar9 - param_4;
      }
      bVar13 = -1 < (longlong)uVar11 ||
               param_3 <= uVar7 && (ulonglong)(uVar9 < param_4) <= uVar7 - param_3;
      lVar10 = lVar10 + -1;
    } while (lVar10 != 0);
    return uVar4 * 2 + (ulonglong)(CARRY8(uVar5,(ulonglong)bVar13) || CARRY8(uVar5,uVar5 + bVar13));
  }
  return 0;
}



void FUN_00088358(void)

{
  undefined4 local_10;
  undefined4 local_c [3];
  
  if (PTR_DAT_400014c8 == &DAT_fffffffe) {
    FUN_00040a14(&local_10,local_c);
    PTR_DAT_400014c8 = (undefined *)FUN_00088210(local_10,local_c[0]);
  }
  return;
}



void FUN_0008839c(void)

{
  if (PTR_DAT_400014c8 != &DAT_fffffffe) {
    FUN_00088244();
    PTR_DAT_400014c8 = &DAT_fffffffe;
  }
  return;
}



longlong int_abs(longlong param_1)

{
  if ((int)param_1 < 0) {
    param_1 = -param_1;
  }
  return param_1;
}



undefined8 libc_memcmp(int param_1,int param_2,longlong param_3)

{
  undefined8 uVar1;
  byte *pbVar2;
  byte *pbVar3;
  
  pbVar3 = (byte *)(param_1 + -1);
  pbVar2 = (byte *)(param_2 + -1);
  param_3 = param_3 + 1;
  do {
    param_3 = param_3 + -1;
    if (param_3 == 0) {
      return 0;
    }
    pbVar3 = pbVar3 + 1;
    pbVar2 = pbVar2 + 1;
  } while (*pbVar3 == *pbVar2);
  uVar1 = 1;
  if (*pbVar3 < *pbVar2) {
    uVar1 = 0xffffffffffffffff;
  }
  return uVar1;
}



void intc_setup_safe_write(void)

{
  undefined4 *in_r6;
  undefined4 in_r7;
  
  *in_r6 = in_r7;
  instructionSynchronize();
  return;
}


