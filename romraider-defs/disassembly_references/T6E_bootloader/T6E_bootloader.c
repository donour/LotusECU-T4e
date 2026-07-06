#define 0 0x0
#define 16 0x10
#define 32 0x20
#define 1 0x1
#define 4 0x4
#define 8 0x8
#define 13 0xd
#define 256 0x100
#define 31 0x1f
#define 80 0x50
#define 18 0x12
#define 7 0x7
#define 6 0x6
#define 9 0x9
#define 64 0x40
#define 1024 0x400
#define 24 0x18
#define 00000000000000000000000000010000b 0x10
#define 0xF 0xf
#define -0x1 -0x1
#define 70 0x46
#define 716 0x2cc
#define 198 0xc6
#define 10176 0x27c0
#define 146 0x92
#define 00011000b 0x18

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
typedef unsigned int    undefined4;
typedef unsigned long long    undefined8;
typedef unsigned short    ushort;
typedef unsigned short    word;
typedef unsigned short    wchar16;
typedef ushort sa_family_t;

typedef struct addrinfo addrinfo, *Paddrinfo;

typedef uint __socklen_t;

typedef __socklen_t socklen_t;

typedef struct sockaddr sockaddr, *Psockaddr;

struct addrinfo {
    int ai_flags;
    int ai_family;
    int ai_socktype;
    int ai_protocol;
    socklen_t ai_addrlen;
    struct sockaddr *ai_addr;
    char *ai_canonname;
    struct addrinfo *ai_next;
};

struct sockaddr {
    sa_family_t sa_family;
    char sa_data[14];
};

typedef ulong size_t;

typedef short int16_t;

typedef char int8_t;

typedef int int32_t;

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

typedef struct struct_segment_data struct_segment_data, *Pstruct_segment_data;

struct struct_segment_data {
    pointer src;
    pointer dest;
    uint size;
};

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

typedef uint16_t u16_rspeed_rpm_x4;

typedef uint8_t u8_time_10ms;

typedef uint16_t u16_afr_1/100;

typedef uint8_t u8_afr_1/100;

typedef uint8_t u8_load_150_pct;

typedef uint16_t u16_factor_1/1023;

typedef struct struct_tps_shaping_flags struct_tps_shaping_flags, *Pstruct_tps_shaping_flags;

typedef enum enum_tps_shaping_current_input {
    TS_IN_RANGE=0,
    TS_LOW=1,
    TS_HIGH=2
} enum_tps_shaping_current_input;

typedef enum enum_tps_shaping_state {
    TS_NO_FAULT=0,
    TS_UNKNOWN1=1,
    TS_CONFIRMED_FAULT=2
} enum_tps_shaping_state;

struct struct_tps_shaping_flags {
    enum enum_tps_shaping_current_input current_input;
    enum enum_tps_shaping_state state;
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

typedef uint8_t u8_voltage_5/255v;

typedef uint8_t u8_factor_1/100;

typedef uint8_t u8_torque_4nm;

typedef uint16_t u16_time_ms;

typedef uint8_t u8_time_s;

typedef uint8_t u8_mass_8g;

typedef uint8_t u8_rspeed_rpm;

typedef int32_t i32_accel_1/255g;

typedef uint8_t u8_obd2level_t6;

typedef uint16_t u16_torque_nm;

typedef uint8_t u8_rspeed_-128;

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

typedef uint8_t u8_factor_1/128;

typedef uint8_t u8_voltage_72/1023v;

typedef uint16_t u16_rspeed_1/4rpm;

typedef uint16_t u16_factor_1/255;

typedef uint8_t u8_time_us;

typedef struct o2_narrowband_threshold o2_narrowband_threshold, *Po2_narrowband_threshold;

struct o2_narrowband_threshold { // o2_narrowband_threshold
    u16_voltage_5/1023v lean;
    u16_voltage_5/1023v rich;
};

typedef enum enum_ac_compressor_state {
    AC_OFF=0,
    AC_START=1,
    AC_RUNNING=2,
    AC_SHUTDOWN=3,
    AC_FAIL=4
} enum_ac_compressor_state;

typedef uint32_t u32_speed_1/100kph;

typedef uint32_t u32_angle_1/10defg;

typedef uint8_t u8_pressure_4mbar;

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

typedef uint16_t u16_accel_1/10g;

typedef uint8_t u8_mass_g;

typedef uint32_t u32_rspeed_1024rpm;

typedef uint8_t u8_pressure_5kpa;

typedef uint8_t u8_fuel_3liter;

typedef uint8_t checksum_8bit;

typedef uint8_t u8_time_5ms;

typedef uint16_t u16_flow_g/s;

typedef uint32_t u32_load_mg/stroke;

typedef enum enum_bootloader_protocol_state {
    BOOTLOADER_PROTOCOL_INIT=0,
    BOOTLOADER_PROTOCOL_UNLOCK=1,
    BOOTLOADER_PROTOCOL_DOWNLOAD=2,
    BOOTLOADER_PROTOCOL_WRITE=3,
    BOOTLOADER_PROTOCOL_DONE=4
} enum_bootloader_protocol_state;

typedef uint8_t u8_time_64us;

typedef int16_t i16_time_us;

typedef uint16_t u16_load_1173mg/255stroke;

typedef struct struct_dma_transfer_control_descriptor struct_dma_transfer_control_descriptor, *Pstruct_dma_transfer_control_descriptor;

struct struct_dma_transfer_control_descriptor {
    uint32_t saddr;
    uint32_t cfg;
    uint32_t nbytes;
    uint32_t daddr;
    uint32_t u1;
};

typedef uint16_t u16_factor_1/10000;

typedef uint8_t u8_pressure_mbar;

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

typedef uint8_t u8_flow_g/s;

typedef uint8_t u8_torque_2nm;

typedef uint8_t u8_flow_2g/s;

typedef uint16_t u16_factor_1/65536;

typedef uint32_t u32_mass_ug;

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

typedef int16_t i16_factor_1/20;

typedef uint16_t u16_time_50ms;

typedef uint16_t u16_time_s;

typedef uint8_t u8_gain_(x-104)/26;

typedef uint16_t u16_volume_1/10gallon;

typedef uint16_t u16_time_4us;

typedef uint8_t u8_volume_liter;

typedef uint8_t u8_gear;

typedef uint16_t u16_angle_deg_x2;

typedef uint16_t u16_time_5ms;

typedef uint8_t u8_angle_1/4-64deg;

typedef uint8_t u8_load_2mg/stroke;

typedef uint16_t u16_distance_mm_div2;

typedef uint8_t u8_time_250ms;

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

typedef uint16_t u16_pressure_kpa_x10;

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

typedef uint8_t u8_volume_1/10gallon;

typedef uint8_t u8_temp_c_minus40;

typedef enum enum_throttle_actuator_state {
    TSL_INIT=0,
    TSL_MODE_1=1,
    TSL_MODE_2=2,
    TSL_MODE_3=3,
    TSL_MONITOR_4=4,
    TSL_MONITOR_5=5,
    TSL_MONITOR_6=6,
    TSL_REARM=7,
    TSL_RUN=8,
    TSL_FAULT=9,
    TSL_SHUTDOWN=10
} enum_throttle_actuator_state;

typedef struct flexcan_msg_buffer flexcan_msg_buffer, *Pflexcan_msg_buffer;

struct flexcan_msg_buffer {
    uint code_and_timestamp;
    uint32_t arb_id;
    byte data[8];
};

typedef uint8_t u8_rspeed_10+6000rpm;

typedef uint16_t u16_speed_1/100kph;

typedef uint8_t u8_time_50ms;

typedef struct struct_decrypted_header struct_decrypted_header, *Pstruct_decrypted_header;

struct struct_decrypted_header {
    undefined field0_0x0;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    undefined field4_0x4;
    undefined field5_0x5;
    undefined field6_0x6;
    undefined field7_0x7;
    uint32_t payload_size;
    char ecu_type[31];
    undefined field10_0x2b;
    uint32_t region_id;
    uint32_t total_size;
    byte *start_addr;
    byte *end_addr;
};

typedef int16_t i16_angle_1/4;

typedef uchar u8_temp_5/8-40c.conflict;

typedef uint8_t u8_pressure_kpa/5;

typedef uint8_t u8_speed_kph;

typedef uint8_t u8_dutycycle_100/255;

typedef uint8_t u8_accel_1/255g;

typedef uint8_t u8_flow_100mg/s;

typedef uint16_t u16_angle_1/4deg;

typedef uint32_t u32_time_50ms;

typedef struct struct_dtc_state struct_dtc_state, *Pstruct_dtc_state;

struct struct_dtc_state {
    uint8_t dtc_state;
    uint8_t fail_counter;
    uint8_t pass_counter;
};

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

typedef int16_t i16_accel_1/255g;

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

typedef enum enum_p0316_eval_tc_request_state {
    P0316_TC_STATE_INIT=-1,
    P0316_TC_STATE_PASS=0,
    P0316_TC_STATE_FAIL=1
} enum_p0316_eval_tc_request_state;

typedef uint32_t u32_fuel_3liter;

typedef struct evp_pkey_ctx_st evp_pkey_ctx_st, *Pevp_pkey_ctx_st;

typedef struct evp_pkey_ctx_st EVP_PKEY_CTX;

struct evp_pkey_ctx_st {
};

typedef struct str_list str_list, *Pstr_list;

typedef struct str_mlist str_mlist, *Pstr_mlist;

struct str_list {
    int sl_nmods;
    struct str_mlist *sl_modlist;
};

struct str_mlist {
    char l_name[9];
};



struct_segment_bss[4] bootloader_bss_segment;
struct_segment_data[14] bootloader_data_segment;
undefined *PTR_PTR_000084c8;
undefined4 DAT_c3f80000;
undefined4 DAT_c3f80004;
undefined4 DAT_c3f8801c;
struct_hc08_config HC08CODE_base;
uint8_t bootloader_session_flags;
undefined4 DAT_fff48010;
uint DAT_400017c4;
int DAT_400017c4;
undefined DAT_400017c0;
uint32_t fca_buffer[15].arb_id;
uint fca_buffer[3].code_and_timestamp;
uint fca_buffer[7].code_and_timestamp;
uint fca_buffer[11].code_and_timestamp;
undefined4 DAT_fffc002c;
uint16_t siu_pcr[84];
undefined4 DAT_fffc0028;
uint32_t flexcan_a_interrupt_reg_flag_low;
undefined4 DAT_fffc0024;
uint fca_buffer[2].code_and_timestamp;
uint fca_buffer[6].code_and_timestamp;
uint fca_buffer[10].code_and_timestamp;
uint fca_buffer[14].code_and_timestamp;
undefined1 DAT_fff480ea;
uint16_t siu_pcr[83];
undefined4 DAT_fffc0018;
undefined4 DAT_fffc0014;
uint32_t fca_buffer[1].arb_id;
undefined4 DAT_fffc0010;
uint fca_buffer[1].code_and_timestamp;
uint fca_buffer[5].code_and_timestamp;
uint fca_buffer[9].code_and_timestamp;
uint fca_buffer[13].code_and_timestamp;
undefined4 DAT_fffc0004;
flexcan_msg_buffer[64] fca_buffer;
uint32_t fca_buffer[0].arb_id;
undefined4 DAT_fffc0000;
uint fca_buffer[4].code_and_timestamp;
uint fca_buffer[8].code_and_timestamp;
uint fca_buffer[12].code_and_timestamp;
uint dev_mode_log_request;
struct_decrypted_header cleartext_header;
uint32_t flexcan_a_timer;
undefined2 rx_msg_total_bytes;
undefined2 can_response_frame_id;
undefined2 can_tx_frame_length;
undefined2 can_tx_frame_offset;
byte[8] bootloader_can_tx_buffer;
undefined4 DAT_40001878;
undefined2 rx_msg_sequence_expected;
undefined2 rx_msg_flags;
undefined1 can_rsvd_ae;
undefined1 can_rsvd_c6;
undefined1 tx_retry_count;
undefined4 download_block_count;
enum_bootloader_protocol_state bootloader_protocol_state;
undefined DAT_400017ec;
byte[4] crypto_flags;
undefined4 header_alignment_padding;
undefined4 remaining_data_size;
undefined2 xtea_unencrypted_trailer_bytes;
undefined DAT_00000804;
byte[16] BYTE_ARRAY_00000878;
undefined DAT_40001c9c;
undefined1 DAT_40001cb8;
undefined DAT_400020ed;
undefined4 payload_remainder_bits;
undefined1 payload_remainder_buffer;
undefined4 header_region_id;
undefined4 flash_target_base;
undefined1 flash_staging_buffer;
undefined4 flash_write_pointer;
char[32] flash_0838_identifier;
struct_variant_coding_t6e EEPROM_variant_coding;
string ecu_model_number;
char[31] ECU_type;
undefined1 bootloader_flash_programming_addr;
undefined1 decrypted_payload_data;
undefined4 header_payload_size;
struct_decrypted_header decrypted_header;
undefined2 trailer_byte_count_saved;
undefined xtea_encrypted_block_size;
byte DAT_400017f2;
undefined DAT_00007cc8;
undefined1 rx_crc8_previous;
undefined1 rx_crc8_accumulator;
undefined1 unlock_sequence_step;
undefined DAT_40001878;
undefined1 address_response_retry_count;
undefined1 rx_crc8_previous_saved;
undefined1 bootloader_error_flags;
undefined1 DAT_40001c99;
undefined1 DAT_40001c9a;
undefined1 DAT_40001c9b;
uint32_t[4] bootloader_xtea_key;
undefined4 xtea_cbc_iv_low;
undefined4 xtea_cbc_iv_high;
undefined4 xtea_decrypted_block_low;
undefined4 xtea_decrypted_block_high;
undefined1 xtea_ciphertext_block_low;
undefined1 _xtea_ciphertext_block_high;
size_t DAT_40001858;
byte *DAT_40001854;
byte *DAT_40001850;
undefined1 DAT_4000185c;
undefined *DAT_40001798;
undefined DAT_400017b0;
undefined DAT_400017ac;
undefined4 DAT_40001828;
int DAT_40001774;
int DAT_4000184c;
int DAT_40001848;
undefined *DAT_4000179c;
undefined *DAT_400017a0;
undefined2 DAT_40001770;
undefined4 DAT_4000182c;
undefined4 DAT_40001838;
undefined4 DAT_40001840;
undefined4 DAT_4000184c;
undefined4 DAT_40001844;
undefined4 DAT_40001848;
undefined DAT_400017a4;
undefined DAT_400017a8;
undefined4 DAT_40001830;
undefined4 DAT_c3f88008;
uint DAT_40001850;
uint DAT_40001858;
undefined4 DAT_c3f8800c;
uint DAT_40001854;
undefined4 DAT_c3f88010;
undefined4 DAT_c3f88004;
undefined4 DAT_c3f88014;
undefined4 DAT_40001860;
uint DAT_40001860;
uint8_t uint8_t_ARRAY_c3f906c6;
uint8_t uint8_t_ARRAY_c3f908c6;
uint8_t uint8_t_ARRAY_c3f906ce;
undefined4 SIU_ISEL2;
uint16_t siu_pcr[214];
byte *DAT_40001864;
uint8_t uint8_t_ARRAY_c3f906d1;
uint8_t uint8_t_ARRAY_c3f90616;
byte DAT_40001870;
byte[16] mpc5534_reserved;
undefined UNK_fffe800a;
int DAT_40001864;
pointer PTR_00000bb8;
undefined *PTR_0000dc00;
undefined UNK_ffff2400;
undefined DAT_40001868;
uint16_t[343] siu_pcr;
undefined1 DAT_40000000;
undefined DAT_400024d0;
undefined4 DAT_400024c8;
undefined4 DAT_400024cc;
undefined *PTR_DAT_400017b8;
undefined DAT_fffffffe;
undefined DAT_ffffffff;
undefined4 DAT_c3f90004;

void bootloader_enable_spe
               (undefined8 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  uint in_MSR;
  
  bootloader_interrupt_init
            (in_MSR | 0x2000000,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}



void bootloader_cache_flush(byte *addr,size_t size)

{
  longlong lVar1;
  ulonglong uVar2;
  
  uVar2 = (longlong)(int)addr & 0xfffffffffffffff1;
  lVar1 = (longlong)(int)size + ((longlong)(int)addr - uVar2);
  do {
    dataCacheBlockStore(uVar2);
    sync(0);
    instructionCacheBlockInvalidate(uVar2);
    uVar2 = uVar2 + 8;
    lVar1 = lVar1 + -8;
  } while (-1 < lVar1);
  instructionSynchronize();
  return;
}



void bootloader_interrupt_init
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  bootloader_init_default_interrupt_frames
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  bootloader__fini();
  bootloader_intc_set_vtba_and_enable();
  return;
}



void _bootloader_c_runtime_start
               (undefined8 param_1,ulonglong param_2,size_t param_3,undefined4 param_4,
               undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  undefined8 uVar1;
  ulonglong uVar2;
  undefined4 uVar3;
  size_t sVar4;
  
  uVar3 = (undefined4)param_2;
  sVar4 = param_3;
  uVar1 = bootloader_offset_reg_set();
  bootloader_enable_spe(uVar1,uVar3,sVar4,param_4,param_5,param_6,param_7,param_8);
  bootloader_init_segment();
  booloader_noop4();
  bootloader_main();
  uVar2 = bootloader_elevator_to_nowhere();
  if ((param_3 != 0) && ((uVar2 & 0xffffffff) != (param_2 & 0xffffffff))) {
    memmove((byte *)uVar2,(byte *)param_2,param_3);
    bootloader_cache_flush((byte *)uVar2,param_3);
  }
  return;
}



void bootloader_init_segment_data(byte *dest,byte *src,size_t size)

{
  if ((size != 0) && (dest != src)) {
    memmove(dest,src,size);
    bootloader_cache_flush(dest,size);
  }
  return;
}



void bootloader_init_segment_bss(byte *addr,size_t size)

{
  if (size != 0) {
    bootloader_memset(addr,0,size);
  }
  return;
}



void bootloader_offset_reg_set(void)

{
                    // resulting r2 is 0x40009870
                    // resulting r13 is 0x40009798
  return;
}



void bootloader_init_segment(void)

{
  struct_segment_bss *boot_bss_seg;
  struct_segment_data *boot_data_seg;
  
  for (boot_data_seg = bootloader_data_segment;
      ((boot_data_seg->src != (undefined *)0x0 || (boot_data_seg->dest != (undefined *)0x0)) ||
      (boot_data_seg->size != 0)); boot_data_seg = boot_data_seg + 1) {
    bootloader_init_segment_data(boot_data_seg->dest,boot_data_seg->src,boot_data_seg->size);
  }
  for (boot_bss_seg = bootloader_bss_segment;
      (boot_bss_seg->dest != (undefined *)0x0 || (boot_bss_seg->size != 0));
      boot_bss_seg = boot_bss_seg + 1) {
    bootloader_init_segment_bss(boot_bss_seg->dest,boot_bss_seg->size);
  }
  return;
}



void memmove(byte *dest,byte *rc,size_t size)

{
  byte *pbVar1;
  int iVar2;
  byte *pbVar3;
  
  if (dest <= rc) {
    pbVar1 = rc + -1;
    pbVar3 = dest + -1;
    iVar2 = size + 1;
    while( true ) {
      iVar2 = iVar2 + -1;
      if (iVar2 == 0) break;
      pbVar1 = pbVar1 + 1;
      pbVar3 = pbVar3 + 1;
      *pbVar3 = *pbVar1;
    }
    return;
  }
  pbVar1 = rc + size;
  pbVar3 = dest + size;
  iVar2 = size + 1;
  while( true ) {
    iVar2 = iVar2 + -1;
    if (iVar2 == 0) break;
    pbVar1 = pbVar1 + -1;
    pbVar3 = pbVar3 + -1;
    *pbVar3 = *pbVar1;
  }
  return;
}



void bootloader_memset(byte *dst,byte val,size_t size)

{
  int iVar1;
  ulonglong uVar2;
  longlong lVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  uint uVar6;
  
  uVar4 = (ulonglong)(int)size;
  uVar6 = (uint)val;
  uVar5 = (longlong)(int)dst - 1;
  if (31 < size) {
    uVar2 = ~uVar5 & 3;
    if (uVar2 != 0) {
      uVar4 = uVar4 - uVar2;
      do {
        uVar2 = uVar2 - 1;
        uVar5 = uVar5 + 1;
        *(byte *)uVar5 = val;
      } while (uVar2 != 0);
    }
    if (val != 0) {
      uVar6 = (uint)CONCAT11(val,val) | uVar6 << 0x18 | uVar6 << 0x10;
    }
    lVar3 = uVar5 - 3;
    for (uVar5 = (uVar4 << 0x20) >> 0x25; uVar5 != 0; uVar5 = uVar5 - 1) {
      iVar1 = (int)lVar3;
      *(uint *)(iVar1 + 4) = uVar6;
      *(uint *)(iVar1 + 8) = uVar6;
      *(uint *)(iVar1 + 0xc) = uVar6;
      *(uint *)(iVar1 + 0x10) = uVar6;
      *(uint *)(iVar1 + 0x14) = uVar6;
      *(uint *)(iVar1 + 0x18) = uVar6;
      *(uint *)(iVar1 + 0x1c) = uVar6;
      lVar3 = lVar3 + 0x20;
      *(uint *)lVar3 = uVar6;
    }
    for (uVar5 = (uVar4 << 0x20) >> 0x22 & 7; uVar5 != 0; uVar5 = uVar5 - 1) {
      lVar3 = lVar3 + 4;
      *(uint *)lVar3 = uVar6;
    }
    uVar5 = lVar3 + 3;
    uVar4 = uVar4 & 3;
  }
  if ((int)uVar4 != 0) {
    do {
      uVar4 = uVar4 - 1;
      uVar5 = uVar5 + 1;
      *(undefined1 *)uVar5 = (char)uVar6;
    } while (uVar4 != 0);
    return;
  }
  return;
}



byte * bootloader_memset(byte *addr,byte val,size_t size)

{
  bootloader_memset(addr,val,size);
  return addr;
}



void bootloader_flash_c55fmc_get_context(undefined4 *param_1,undefined4 *param_2)

{
  *param_2 = 0x40009870;
  *param_1 = &PTR_PTR_000084c8;
  return;
}



void bootloader_halt_catchfire(void)

{
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



void bootloader_fmpll_init_clock(void)

{
  uint uVar1;
  uint uVar2;
  
  DAT_c3f80000 = 0x3080030;
  do {
    uVar1 = DAT_c3f80004;
  } while ((uVar1 >> 3 & 1) != 1);
  DAT_c3f80000 = 0x3080430;
  do {
    uVar1 = DAT_c3f80004;
  } while ((uVar1 >> 3 & 1) != 1);
  uVar1 = DAT_c3f80004;
  uVar2 = uVar1 >> 1 & 1;
  uVar1 = DAT_c3f80004;
  if ((int)(1 - uVar2 | uVar2 - 1) < 0 || (int)(1 - (uVar1 & 1) | (uVar1 & 1) - 1) < 0) {
    bootloader_halt_catchfire();
  }
  DAT_c3f80000 = 0x3000430;
  return;
}



// // bootloader_session_flags (DAT_400017fb) bit definitions
// //
// //  bit 0  0x01  erase_pending    — flash erase requested; cleared when erase executes (→
// erase_done set)
// //  bit 1  0x02  write_pending    — decrypted data ready to write to flash
// //  bit 2  0x04  erase_done       — flash erase complete; required before write_pending is
// serviced
// //  bit 3  0x08  authenticated    — unlock/seed-key exchange succeeded; checked by
// bootload_active_check()
// //  bit 4  0x10  session_active   — CAN session live; set each main() iteration, cleared on
// idle
// //
// //  bootload_active_check() returns (flags & 0x18) != 0  → authenticated OR session_active
// //  bootloader_init() preserves only session_active:     flags &= 0x10
// //
// //  Normal programming sequence:
// //    session_active set (0x10)
// //    → authenticated set (0x18)
// //    → write_pending set (0x02)          dl_request returns 2
// //    → erase_pending + write_pending (0x03)  dl_request returns 3
// //    → erase executes: erase_pending cleared, erase_done set (0x06)
// //    → write executes: write_pending + erase_done cleared (0x00)

void bootloader_main(void)

{
  uint uVar1;
  bool _is_active;
  
  uVar1 = DAT_c3f8801c;
  DAT_c3f8801c = uVar1 & 0xfffffffe | 1;
  bootloader_fmpll_init_clock();
  do {
    bootloader_session_flags = bootloader_session_flags | 0b00010000;
    _is_active = bootloader_active_check();
    if (_is_active) {
      bootloader_comm_loop();
    }
    if (((HC08CODE_base.name._0_4_ == 0x48433038) && (HC08CODE_base.name._4_4_ == 0x434f4445)) &&
       ((HC08CODE_base.programming_magic_word == 0xaaaaaaaa ||
        ((HC08CODE_base.programming_magic_word == 0x88888888 ||
         (HC08CODE_base.programming_magic_word == 0xbbbbbbbb)))))) {
      bootloader_noop3();
      bootloader_hc08_firmware_program();
    }
    WriteExternalEnableImmediate(0);
                    // does not return
    func_0x00040100();
  } while( true );
}



void booloader_noop4(void)

{
  return;
}



void bootloader_elevator_to_nowhere(void)

{
  bootloader_END();
  return;
}



void bootloader__fini(void)

{
  return;
}



void bootloader_intc_set_vtba_and_enable(void)

{
  WriteExternalEnableImmediate(1);
  DAT_fff48010 = 0x40000000;
  return;
}



uint32_t timebase_read_safe(void)

{
  uint32_t _tblr;
  undefined8 _tb_ur;
  undefined8 tblr;
  undefined8 tbur;
  
  do {
    tbur = TBUr;
    tblr = TBLr;
    _tb_ur = TBUr;
  } while ((uint32_t)_tb_ur != (uint32_t)tbur);
  _tblr = (uint32_t)tblr;
                    // WARNING: this result is unused
  u64_div_int((uint32_t)tbur,_tblr,0,80);
  return _tblr;
}



void timebase_reset_and_clear_dbsr(void)

{
  TBUw = 0;
  TBLw = 0;
  return;
}



bool bootloader_timeout_expired(void)

{
  uint32_t _timebase;
  
  _timebase = timebase_read_safe();
  return DAT_400017c4 <= _timebase;
}



void bootloader_watchdog_set(u32_time_us ticks)

{
  uint32_t uVar1;
  
  uVar1 = timebase_read_safe();
  DAT_400017c4 = ticks + uVar1;
  return;
}



void bootloader_noop(void)

{
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

bool bootloader_rx_timer_expired(void)

{
  uint32_t uVar1;
  
  uVar1 = timebase_read_safe();
  return _DAT_400017c0 <= uVar1;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void bootloader_rx_timer_set(int param_1)

{
  uint32_t _timebase;
  
  _timebase = timebase_read_safe();
  _DAT_400017c0 = param_1 + _timebase;
  return;
}



void bootloader_flexcan_a_init(void)

{
  uint16_t uVar1;
  byte bVar2;
  uint uVar3;
  
  uVar3 = DAT_fffc0000;
  DAT_fffc0000 = uVar3 & 0xfdffffff | 0x2000000;
  do {
    uVar3 = DAT_fffc0000;
  } while ((uVar3 >> 0x19 & 1) == 1);
  uVar3 = DAT_fffc0000;
  DAT_fffc0000 = uVar3 & 0xefffffff | 0x10000000;
  do {
    uVar3 = DAT_fffc0000;
  } while ((uVar3 & 0x9000000) != 0x9000000);
  DAT_fffc0004 = 0x1510001;
  fca_buffer[0].code_and_timestamp = 0;
  uVar3 = fca_buffer[0].code_and_timestamp;
  fca_buffer[0].code_and_timestamp = uVar3 & 0xf0ffffff | 0x8000000;
  fca_buffer[0].arb_id = 0;
  uVar3 = fca_buffer[0].code_and_timestamp;
  fca_buffer[0].code_and_timestamp = uVar3 & 0xffff0000;
  fca_buffer[1].code_and_timestamp = 0;
  uVar3 = fca_buffer[1].code_and_timestamp;
  fca_buffer[1].code_and_timestamp = uVar3 & 0xf0ffffff | 0x8000000;
  fca_buffer[1].arb_id = 0;
  uVar3 = fca_buffer[1].code_and_timestamp;
  fca_buffer[1].code_and_timestamp = uVar3 & 0xffff0000;
  fca_buffer[2].code_and_timestamp = 0;
  fca_buffer[3].code_and_timestamp = 0;
  fca_buffer[4].code_and_timestamp = 0;
  fca_buffer[5].code_and_timestamp = 0;
  fca_buffer[6].code_and_timestamp = 0;
  fca_buffer[7].code_and_timestamp = 0;
  fca_buffer[8].code_and_timestamp = 0;
  fca_buffer[9].code_and_timestamp = 0;
  fca_buffer[10].code_and_timestamp = 0;
  fca_buffer[0xb].code_and_timestamp = 0;
  fca_buffer[0xc].code_and_timestamp = 0;
  fca_buffer[0xd].code_and_timestamp = 0;
  fca_buffer[0xe].code_and_timestamp = 0;
  fca_buffer[0xf].code_and_timestamp = 0;
  uVar3 = fca_buffer[0xf].code_and_timestamp;
  fca_buffer[0xf].code_and_timestamp = uVar3 & 0xf0ffffff | 0x4000000;
  fca_buffer[0xf].arb_id = 0x1400000;
  uVar3 = fca_buffer[0xf].code_and_timestamp;
  fca_buffer[0xf].code_and_timestamp = uVar3 & 0xffff0000;
  DAT_fffc0010 = 0x1fffffff;
  DAT_fffc0014 = 0x1fffffff;
  DAT_fffc0018 = 0x1fe3ffff;
  DAT_fffc0024 = 0;
  DAT_fffc0028 = 0;
  bVar2 = DAT_fff480ea;
  DAT_fff480ea = bVar2 & 0xf0;
  uVar1 = siu_pcr[0x53];
  siu_pcr[0x53] = uVar1 & 0xe3ff | 0x400;
  uVar1 = siu_pcr[0x54];
  siu_pcr[0x54] = uVar1 & 0xe3ff | 0x400;
  uVar3 = DAT_fffc0000;
  DAT_fffc0000 = uVar3 & 0xefffffff;
  DAT_fffc002c = 0;
  flexcan_a_interrupt_reg_flag_low = 0;
  return;
}



void bootloader_flexcan_a_rx_50_51(void)

{
  uint32_t uVar1;
  uint datalen;
  int iVar2;
  byte *data_cur;
  byte *can_data;
  uint i;
  uint uVar3;
  uint32_t _arb_id;
  byte tmp;
  
  uVar3 = fca_buffer[0xf].code_and_timestamp;
  while ((uVar3 >> 0x18 & 1) != 0) {
    uVar3 = fca_buffer[0xf].code_and_timestamp;
  }
  uVar3 = fca_buffer[0xf].code_and_timestamp;
  if ((uVar3 >> 0x18 & 6) == 6) {
    uVar3 = fca_buffer[0xf].code_and_timestamp;
    fca_buffer[0xf].code_and_timestamp = uVar3 & 0xf0ffffff | 0x4000000;
    uVar1 = flexcan_a_timer;
  }
  else {
    uVar3 = fca_buffer[0xf].code_and_timestamp;
    if ((uVar3 >> 0x18 & 2) == 2) {
      can_data = fca_buffer[0xf].data;
      _arb_id = fca_buffer[0xf].arb_id;
      if ((_arb_id >> 0x12 == 0x51) || (_arb_id >> 0x12 == 0x50)) {
        uVar3 = fca_buffer[0xf].code_and_timestamp;
        datalen = uVar3 >> 0x10 & 0xf;
        iVar2 = (int)rx_msg_total_bytes;
        for (i = 0; (i & 0xff) < datalen; i = i + 1) {
          if (rx_msg_total_bytes < 1024) {
            tmp = *can_data;
            can_data = can_data + 1;
            cleartext_header.ecu_type[rx_msg_total_bytes + -4] = tmp;
            rx_msg_total_bytes = rx_msg_total_bytes + 1;
          }
          else {
            rx_msg_total_bytes = 0x401;
          }
        }
        uVar3 = fca_buffer[0xf].code_and_timestamp;
        fca_buffer[0xf].code_and_timestamp = uVar3 & 0xf0ffffff | 0x4000000;
        data_cur = (byte *)(cleartext_header.ecu_type + iVar2 + -4);
        for (uVar3 = 0; (uVar3 & 0xff) < datalen; uVar3 = uVar3 + 1) {
          bootloader_running_crc8(data_cur);
          data_cur = data_cur + 1;
        }
        bootloader_watchdog_restart(80000);
      }
      else {
        uVar3 = fca_buffer[0xf].code_and_timestamp;
        fca_buffer[0xf].code_and_timestamp = uVar3 & 0xf0ffffff | 0x4000000;
        uVar1 = flexcan_a_timer;
      }
    }
  }
  return;
}



void bootloader_flexcan_a_tx_response(void)

{
  uint32_t uVar1;
  uint uVar2;
  byte *pbVar3;
  uint i;
  uint len;
  
  uVar2 = fca_buffer[0].code_and_timestamp;
  if ((uVar2 >> 0x18 & 0xf) == 8) {
    uVar1 = flexcan_a_interrupt_reg_flag_low;
    flexcan_a_interrupt_reg_flag_low = uVar1 & 0xfffffffe | 1;
    pbVar3 = fca_buffer[0].data;
                    // This is 0x7A1 in bootloader setup
    fca_buffer[0].arb_id = (uint)can_response_frame_id << 18;
    len = (int)can_tx_frame_length - (int)can_tx_frame_offset;
    if (8 < (int)len) {
      len = 8;
    }
    if (0 < (int)len) {
      for (i = 0; (int)(i & 0xff) < (int)len; i = i + 1) {
        *pbVar3 = bootloader_can_tx_buffer[i & 0xff];
        pbVar3 = pbVar3 + 1;
      }
      uVar2 = fca_buffer[0].code_and_timestamp;
      fca_buffer[0].code_and_timestamp = (len & 0xf) << 0x10 | uVar2 & 0xfff0ffff;
      uVar2 = fca_buffer[0].code_and_timestamp;
      fca_buffer[0].code_and_timestamp = uVar2 & 0xf0ffffff | 0xc000000;
      can_tx_frame_offset = can_tx_frame_offset + (short)len;
    }
  }
  return;
}



void bootloader_flexcan_a_tx(int arb_id,uint8_t datalen)

{
  uint32_t uVar1;
  uint uVar2;
  ushort uVar3;
  byte *pbVar4;
  ushort i;
  
  uVar3 = (ushort)(char)datalen;
  uVar2 = fca_buffer[1].code_and_timestamp;
  if ((uVar2 >> 24 & 0xf) == 8) {
    uVar1 = flexcan_a_interrupt_reg_flag_low;
    flexcan_a_interrupt_reg_flag_low = uVar1 & 0xfffffffd | 2;
    pbVar4 = fca_buffer[1].data;
    fca_buffer[1].arb_id = arb_id << 18;
    if (8 < datalen) {
      uVar3 = 8;
    }
    for (i = 0; i < (uVar3 & 0xff); i = i + 1) {
      *pbVar4 = *(byte *)((int)&DAT_40001878 + (uint)i);
      pbVar4 = pbVar4 + 1;
    }
    uVar2 = fca_buffer[1].code_and_timestamp;
    fca_buffer[1].code_and_timestamp = (uint)(uVar3 & 0xf) << 16 | uVar2 & 0xfff0ffff;
    uVar2 = fca_buffer[1].code_and_timestamp;
    fca_buffer[1].code_and_timestamp = uVar2 & 0xf0ffffff | 0xc000000;
  }
  return;
}



void bootloader_can_session_init(void)

{
  rx_msg_sequence_expected = 1;
  rx_msg_total_bytes = 0;
  rx_msg_flags = 0;
  can_rsvd_ae = 0;
  can_response_frame_id = 0x7a1;
  can_tx_frame_length = 0;
  can_tx_frame_offset = 0;
  can_rsvd_c6 = 0;
  bootloader_flexcan_a_init();
  return;
}



bool bootloader_timeout_expired_2(void)

{
  bool rv;
  
  rv = bootloader_timeout_expired();
  return rv;
}



bool bootloader_rx_ready_or_timeout(void)

{
  bool bVar1;
  
  if (rx_msg_total_bytes == 8) {
    bVar1 = true;
  }
  else {
    bVar1 = bootloader_timeout_expired();
  }
  return bVar1;
}



undefined2 bootloader_rx_msg_len(void)

{
  return rx_msg_total_bytes;
}



void bootloader_tx_ack(void)

{
  bootloader_can_tx_buffer[0] = 10;
  bootloader_can_tx_buffer[1] = 1;
  bootloader_can_tx_buffer[2] = 0;
  bootloader_can_tx_buffer[3] = 0;
  bootloader_can_tx_buffer[4] = 0;
  bootloader_can_tx_buffer[5] = 0;
  bootloader_can_tx_buffer[6] = 0;
  bootloader_can_tx_buffer[7] = bootloader_crc8(bootloader_can_tx_buffer,7);
  can_tx_frame_length = 8;
  can_tx_frame_offset = 0;
  bootloader_flexcan_a_tx();
  bootloader_watchdog_restart(100000);
  bootloader_rx_window_set(100000);
  rx_msg_total_bytes = 0;
  rx_msg_flags = 0;
  return;
}



void bootloader_tx_retry(byte param_1)

{
  if (tx_retry_count < 3) {
    bootloader_can_tx_buffer[0] = 4;
    bootloader_can_tx_buffer[1] = 1;
    bootloader_can_tx_buffer[2] = 0;
    bootloader_can_tx_buffer[3] = 0;
    bootloader_can_tx_buffer[4] = 0;
    bootloader_can_tx_buffer[6] = 0;
    tx_retry_count = tx_retry_count + 1;
    bootloader_can_tx_buffer[5] = param_1;
    bootloader_can_tx_buffer[7] = bootloader_crc8(bootloader_can_tx_buffer,7);
    can_tx_frame_length = 8;
    can_tx_frame_offset = 0;
    bootloader_flexcan_a_tx();
    bootloader_watchdog_restart(100000);
    rx_msg_total_bytes = 0;
    rx_msg_flags = 0;
  }
  else {
    tx_retry_count = tx_retry_count + 1;
    bootloader_tx_abort(0x82);
  }
  return;
}



void bootloader_tx_address_response(void)

{
  bootloader_can_tx_buffer[0] = 1;
  bootloader_can_tx_buffer[1] = 1;
  bootloader_can_tx_buffer[2] = 0;
  bootloader_can_tx_buffer[3] = 4;
  bootloader_can_tx_buffer[4] = 0;
  bootloader_can_tx_buffer[5] = (byte)((uint)download_block_count >> 8);
  bootloader_can_tx_buffer[6] = (byte)download_block_count;
  bootloader_can_tx_buffer[7] = bootloader_crc8(bootloader_can_tx_buffer,'\a');
  can_tx_frame_length = 8;
  can_tx_frame_offset = 0;
  bootloader_flexcan_a_tx();
  bootloader_watchdog_restart(100000);
  rx_msg_total_bytes = 0;
  rx_msg_flags = 0;
  return;
}



void bootloader_tx_abort(byte param_1)

{
  bootloader_can_tx_buffer[0] = 5;
  bootloader_can_tx_buffer[1] = 1;
  bootloader_can_tx_buffer[2] = 0;
  bootloader_can_tx_buffer[3] = 0;
  bootloader_can_tx_buffer[4] = 0;
  bootloader_can_tx_buffer[6] = 0;
  bootloader_can_tx_buffer[5] = param_1;
  bootloader_can_tx_buffer[7] = bootloader_crc8(bootloader_can_tx_buffer,'\a');
  can_tx_frame_length = 8;
  can_tx_frame_offset = 0;
  bootloader_flexcan_a_tx();
  bootloader_watchdog_restart(100000);
  rx_msg_total_bytes = 0;
  rx_msg_flags = 0;
  bootloader_protocol_state = BOOTLOADER_PROTOCOL_DONE;
  return;
}



void bootloader_tx_hc08_error(byte param_1)

{
  bootloader_can_tx_buffer[0] = 5;
  bootloader_can_tx_buffer[1] = 1;
  bootloader_can_tx_buffer[2] = 0;
  bootloader_can_tx_buffer[3] = 0;
  bootloader_can_tx_buffer[4] = 0;
  bootloader_can_tx_buffer[6] = 0;
  bootloader_can_tx_buffer[5] = param_1;
  bootloader_can_tx_buffer[7] = bootloader_crc8(bootloader_can_tx_buffer,7);
  can_tx_frame_length = 8;
  can_tx_frame_offset = 0;
  bootloader_flexcan_a_tx();
  return;
}



void bootloader_retransmit_last(void)

{
  can_tx_frame_offset = 0;
  bootloader_flexcan_a_tx();
  bootloader_watchdog_restart(100000);
  rx_msg_total_bytes = 0;
  rx_msg_flags = 0;
  return;
}



undefined8 bootloader_rx_set_target_address(void)

{
  undefined8 uVar1;
  
  if ((cleartext_header.payload_size._0_1_ == '\a') &&
     ((ushort)cleartext_header.payload_size._1_1_ == (rx_msg_sequence_expected & 0xff))) {
    DAT_400017ec._2_2_ =
         (ushort)(byte)cleartext_header.payload_size * 0x100 +
         (ushort)(byte)cleartext_header.ecu_type[0];
    DAT_400017ec._0_2_ =
         (ushort)(byte)cleartext_header.ecu_type[1] * 0x100 +
         (ushort)(byte)cleartext_header.ecu_type[2];
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



undefined8 bootloader_rx_enter_flash_mode(void)

{
  undefined8 uVar1;
  
  if ((cleartext_header.payload_size._0_1_ == 8) && (cleartext_header.payload_size._1_1_ == 0)) {
    rx_msg_total_bytes = 0;
    rx_msg_flags = 0;
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



undefined8 bootloader_rx_end_session(void)

{
  undefined8 uVar1;
  
  if ((cleartext_header.payload_size._0_1_ == 9) && (cleartext_header.payload_size._1_1_ == 0)) {
    rx_msg_total_bytes = 0;
    rx_msg_flags = 0;
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



void bootloader_tx_program_start(void)

{
  bootloader_can_tx_buffer[0] = 2;
  bootloader_can_tx_buffer[1] = 1;
  bootloader_can_tx_buffer[2] = 0;
  bootloader_can_tx_buffer[3] = 0;
  bootloader_can_tx_buffer[4] = 0;
  bootloader_can_tx_buffer[5] = 0;
  bootloader_can_tx_buffer[6] = 0;
  bootloader_can_tx_buffer[7] = bootloader_crc8(bootloader_can_tx_buffer,'\a');
  can_tx_frame_length = 8;
  can_tx_frame_offset = 0;
  bootloader_flexcan_a_tx();
  bootloader_watchdog_restart(100000);
  rx_msg_total_bytes = 0;
  rx_msg_flags = 0;
  return;
}



void bootloader_tx_hc08_prog_done(undefined *param1)

{
  bootloader_can_tx_buffer[0] = 0xc;
  bootloader_can_tx_buffer[1] = 1;
  bootloader_can_tx_buffer[2] = (byte)((uint)param1 >> 8);
  bootloader_can_tx_buffer[3] = (byte)param1;
  bootloader_can_tx_buffer[4] = 0;
  bootloader_can_tx_buffer[5] = 0;
  bootloader_can_tx_buffer[6] = 0;
  bootloader_can_tx_buffer[7] = bootloader_crc8(bootloader_can_tx_buffer,'\a');
  can_tx_frame_length = 8;
  can_tx_frame_offset = 0;
  bootloader_flexcan_a_tx();
  return;
}



void bootloader_tx_hc08_prog_start(undefined4 param_1)

{
  bootloader_can_tx_buffer[0] = 0xb;
  bootloader_can_tx_buffer[1] = 1;
  bootloader_can_tx_buffer[2] = (byte)((uint)param_1 >> 8);
  bootloader_can_tx_buffer[3] = (byte)param_1;
  bootloader_can_tx_buffer[4] = 0;
  bootloader_can_tx_buffer[5] = 0;
  bootloader_can_tx_buffer[6] = 0;
  bootloader_can_tx_buffer[7] = bootloader_crc8(bootloader_can_tx_buffer,'\a');
  can_tx_frame_length = 8;
  can_tx_frame_offset = 0;
  bootloader_flexcan_a_tx();
  return;
}



void bootloader_tx_hc08_erase_start(undefined4 param_1)

{
  bootloader_can_tx_buffer[0] = 13;
  bootloader_can_tx_buffer[1] = 1;
  bootloader_can_tx_buffer[2] = (byte)((uint)param_1 >> 8);
  bootloader_can_tx_buffer[3] = (byte)param_1;
  bootloader_can_tx_buffer[4] = 0;
  bootloader_can_tx_buffer[5] = 0;
  bootloader_can_tx_buffer[6] = 0;
  bootloader_can_tx_buffer[7] = bootloader_crc8(bootloader_can_tx_buffer,'\a');
  can_tx_frame_length = 8;
  can_tx_frame_offset = 0;
  bootloader_flexcan_a_tx();
  return;
}



undefined8 bootloader_rx_handle_retransmit(void)

{
  undefined8 uVar1;
  
  if ((cleartext_header.payload_size._0_1_ == 4) &&
     ((ushort)cleartext_header.payload_size._1_1_ == (rx_msg_sequence_expected & 0xff))) {
    bootloader_retransmit_last();
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



undefined8 bootloader_dl_request_handler(void)

{
  undefined8 uVar1;
  
                    // incoming download requests start with  0x6?
  if (cleartext_header.payload_size._0_1_ == 6) {
                    // validate sequence number
    if (((uint)cleartext_header.payload_size._1_1_ * 0x100 +
         (uint)cleartext_header.payload_size._2_1_ & 0xffff) == download_block_count) {
                    // validate data len
      if (((uint)(byte)cleartext_header.payload_size * 0x100 +
           (uint)(byte)cleartext_header.ecu_type[0] & 0xffff) == (int)rx_msg_total_bytes - 6U) {
                    // check for buffer overrun
        if ((download_block_count == 0) ||
           ((rx_msg_total_bytes + -6) - header_alignment_padding <=
            (int)(remaining_data_size - (uint)xtea_unencrypted_trailer_bytes))) {
          if (crypto_flags == (byte  [4])0xffffffff) {
            uVar1 = bootloader_download_handler_cleartext();
          }
          else {
            uVar1 = bootloader_process_encrypted_header();
          }
        }
        else {
          uVar1 = 0x99;
        }
      }
      else {
        uVar1 = 0x99;
      }
    }
    else {
      uVar1 = 0x98;
    }
  }
  else {
    uVar1 = 0x89;
  }
  return uVar1;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 bootloader_download_handler_cleartext(void)

{
  uint uVar1;
  longlong lVar2;
  int start_addr;
  longlong lVar3;
  int end_addr;
  longlong lVar4;
  uint region_id;
  int signature_difference;
  undefined8 uVar5;
  ulonglong uVar6;
  size_t _data_buf_size2;
  int iVar7;
  ulonglong _data_buf_size;
  size_t size;
  
  if (download_block_count == 0) {
    lVar2 = bytes_to_int32((byte *)((int)&cleartext_header.start_addr + 1));
    lVar3 = bytes_to_int32((byte *)((int)&cleartext_header.end_addr + 1));
    lVar4 = bytes_to_int32((byte *)((int)&cleartext_header.region_id + 1));
    header_region_id = (int)lVar4;
    lVar4 = bytes_to_int32((byte *)((int)&cleartext_header.total_size + 1));
    remaining_data_size = (uint)lVar4;
                    // 0x40000 is program base
                    // 0x20000 is calibration base
    if (header_region_id == 1) {
      flash_target_base = 0x800;
    }
    else if (header_region_id == 2) {
      flash_target_base = 0x808;
    }
    else if (header_region_id == 3) {
      flash_target_base = 0x838;
    }
    else if (header_region_id == 4) {
      flash_target_base = 0x40000;
    }
    else if (header_region_id == 5) {
      flash_target_base = 0x20000;
    }
    else if (header_region_id == 7) {
      flash_target_base = 0x1c000;
    }
    else if (header_region_id == 8) {
      flash_target_base = 0x1c000;
    }
    else if (header_region_id == 9) {
      flash_target_base = 0x1c020;
    }
    else if (header_region_id == 10) {
      flash_target_base = 0x858;
    }
    else if (header_region_id == 0xb) {
      flash_target_base = 0x878;
    }
    else {
      flash_target_base = -1;
    }
    signature_difference = bootloader_strncmp(cleartext_header.ecu_type + 1,ECU_type,31);
    if (signature_difference == 0) {
      signature_difference = (int)lVar3;
      iVar7 = (int)lVar2;
      if (_bootloader_flash_programming_addr < 1) {
        if ((((flash_target_base == 0x800) && (iVar7 == signature_difference)) && (0 < iVar7)) &&
           (rx_msg_total_bytes == 70)) {
          flash_write_pointer = flash_target_base;
          memmove(&flash_staging_buffer,(byte *)((int)&cleartext_header.start_addr + 1),4);
          memmove(&DAT_40001c9c,&DAT_00000804,4);
          cleartext_header._0_2_ = 8;
          cleartext_header._2_2_ = 0;
          rx_msg_flags = 0;
          rx_msg_total_bytes = 0;
          uVar5 = 3;
        }
        else {
          uVar5 = 0x8a;
        }
      }
      else if (((iVar7 < 1) && (signature_difference < 1)) ||
              ((iVar7 <= _bootloader_flash_programming_addr &&
               (_bootloader_flash_programming_addr <= signature_difference)))) {
        if ((((((flash_target_base == 0x40000) && ((int)remaining_data_size < 0xc0001)) ||
              ((flash_target_base == 0x20000 && ((int)remaining_data_size < 0x10001)))) ||
             ((((flash_target_base == 0x808 && (remaining_data_size == 4)) &&
               (crypto_flags == (byte  [4])0xffffffff)) ||
              (((flash_target_base == 0x858 && (remaining_data_size == 0x20)) &&
               (uVar6 = check_array_0xff(ecu_model_number,0x20), (uVar6 & 0xff) == 1)))))) ||
            (((flash_target_base == 0x878 && (remaining_data_size == 0x20)) &&
             (uVar6 = check_array_0xff((char *)BYTE_ARRAY_00000878,0x20), (uVar6 & 0xff) == 1)))) ||
           (((flash_target_base == 0x838 && (remaining_data_size == 0x20)) &&
            (uVar6 = check_array_0xff(flash_0838_identifier,0x20), (uVar6 & 0xff) == 1)))) {
          flash_write_pointer = flash_target_base;
          if (rx_msg_total_bytes < 0x47) {
            uVar5 = 1;
          }
          else {
            if (remaining_data_size == (int)rx_msg_total_bytes - 0x46U) {
              memmove(&flash_staging_buffer,&DAT_400020ed,(int)rx_msg_total_bytes - 70);
              cleartext_header._0_2_ = rx_msg_total_bytes + -0x46;
              uVar1 = (int)remaining_data_size >> 0x1f;
              if ((uVar1 * 8 | remaining_data_size * 0x20000000 + uVar1 >> 0x1d) != uVar1) {
                uVar6 = ((ulonglong)remaining_data_size & 7) * 0x20000000 -
                        (ulonglong)(remaining_data_size >> 0x1f);
                for (lVar2 = ((uVar6 & 0x1fffffff) << 3 | (uVar6 << 0x20) >> 0x3d) +
                             (ulonglong)(remaining_data_size >> 0x1f); (int)lVar2 < 8;
                    lVar2 = lVar2 + 1) {
                  (&flash_staging_buffer)[(short)cleartext_header._0_2_] = 0xff;
                  cleartext_header._0_2_ = cleartext_header._0_2_ + 1;
                }
              }
            }
            else {
              _data_buf_size = (longlong)rx_msg_total_bytes - 70;
              _data_buf_size2 = (size_t)(_data_buf_size & 0xfff8);
              memmove(&flash_staging_buffer,&DAT_400020ed,_data_buf_size2);
              cleartext_header._0_2_ = SUB82(_data_buf_size & 0xfff8,0);
              uVar6 = (_data_buf_size & 7) * 0x20000000 +
                      ((longlong)(_data_buf_size << 0x20) >> 0x3f);
              payload_remainder_bits =
                   ((uint)((uVar6 & 0xffffffff) << 3) | (uint)uVar6 >> 0x1d) -
                   ((int)_data_buf_size >> 0x1f);
              for (signature_difference = 0; signature_difference < (int)payload_remainder_bits;
                  signature_difference = signature_difference + 1) {
                (&payload_remainder_buffer)[signature_difference] =
                     (&DAT_400020ed)[_data_buf_size2 + signature_difference];
              }
            }
            cleartext_header._2_2_ = 0;
            rx_msg_flags = 0;
            rx_msg_total_bytes = 0;
            uVar5 = 3;
          }
        }
        else if (((flash_target_base == 0x1c000) && (header_region_id == 8)) &&
                ((remaining_data_size == 0x20 &&
                 (uVar6 = check_array_0xff((char *)&EEPROM_variant_coding,0x20), (uVar6 & 0xff) == 1
                 )))) {
          flash_write_pointer = flash_target_base;
          memmove(&flash_staging_buffer,(byte *)&EEPROM_variant_coding,0x40);
          memmove(&flash_staging_buffer,&DAT_400020ed,(int)rx_msg_total_bytes - 0x46);
          cleartext_header._0_2_ = 0x40;
          cleartext_header._2_2_ = 0;
          rx_msg_flags = 0;
          rx_msg_total_bytes = 0;
          uVar5 = 3;
        }
        else if ((((flash_target_base == 0x1c000) && (header_region_id == 7)) &&
                 (remaining_data_size == 0x20)) &&
                ((iVar7 == signature_difference && (iVar7 == _bootloader_flash_programming_addr))))
        {
          flash_write_pointer = flash_target_base;
          memmove(&flash_staging_buffer,(byte *)&EEPROM_variant_coding,0x40);
          memmove(&flash_staging_buffer,&DAT_400020ed,(int)rx_msg_total_bytes - 0x46);
          cleartext_header._0_2_ = 0x40;
          cleartext_header._2_2_ = 0;
          rx_msg_flags = 0;
          rx_msg_total_bytes = 0;
          uVar5 = 3;
        }
        else if ((flash_target_base == 0x1c020) &&
                (((remaining_data_size == 0x20 && (iVar7 == signature_difference)) &&
                 (iVar7 == _bootloader_flash_programming_addr)))) {
          flash_write_pointer = 0x1c000;
          memmove(&flash_staging_buffer,(byte *)&EEPROM_variant_coding,0x40);
          memmove(&DAT_40001cb8,&DAT_400020ed,(int)rx_msg_total_bytes - 0x46);
          cleartext_header._0_2_ = 0x40;
          cleartext_header._2_2_ = 0;
          rx_msg_flags = 0;
          rx_msg_total_bytes = 0;
          uVar5 = 3;
        }
        else if (((((flash_target_base == 0x800) && (iVar7 == signature_difference)) &&
                  ((0 < iVar7 &&
                   ((rx_msg_total_bytes == 0x46 && (0 < _bootloader_flash_programming_addr)))))) ||
                 ((((flash_target_base == 0x858 &&
                    ((remaining_data_size == 0x20 &&
                     (uVar6 = check_array_0xff(ecu_model_number,0x20), (uVar6 & 0xff) == 0)))) ||
                   ((flash_target_base == 0x878 &&
                    ((remaining_data_size == 0x20 &&
                     (uVar6 = check_array_0xff((char *)BYTE_ARRAY_00000878,0x20),
                     (uVar6 & 0xff) == 0)))))) ||
                  ((((flash_target_base == 0x1c000 &&
                     ((remaining_data_size == 0x20 &&
                      (uVar6 = check_array_0xff((char *)&EEPROM_variant_coding,0x20),
                      (uVar6 & 0xff) == 0)))) ||
                    ((flash_target_base == 0x1c020 &&
                     ((remaining_data_size == 0x20 &&
                      (uVar6 = check_array_0xff(EEPROM_variant_coding.model,0x20),
                      (uVar6 & 0xff) == 0)))))) ||
                   ((flash_target_base == 0x838 &&
                    ((remaining_data_size == 0x20 &&
                     (uVar6 = check_array_0xff(flash_0838_identifier,0x20), (uVar6 & 0xff) == 0)))))
                   ))))) ||
                ((flash_target_base == 0x808 &&
                 ((remaining_data_size == 4 && (crypto_flags != (byte  [4])0xffffffff)))))) {
          uVar5 = 0x8f;
        }
        else {
          uVar5 = 0x8d;
        }
      }
      else {
        uVar5 = 0x8c;
      }
    }
    else {
      uVar5 = 0x8b;
    }
  }
  else {
    if (payload_remainder_bits != 0) {
      memmove(&flash_staging_buffer,&payload_remainder_buffer,payload_remainder_bits);
    }
    cleartext_header._0_2_ = SUB42(payload_remainder_bits,0);
    size = (((int)rx_msg_total_bytes + payload_remainder_bits) - 6 & 0xfff8) -
           payload_remainder_bits;
    if ((int)size < 0) {
      size = 0;
    }
    else {
      memmove(&flash_staging_buffer + (short)cleartext_header._0_2_,
              (byte *)(cleartext_header.ecu_type + 1),size);
      cleartext_header._0_2_ = cleartext_header._0_2_ + (short)size;
    }
    payload_remainder_bits = (rx_msg_total_bytes + -6) - size;
    for (signature_difference = 0; signature_difference < (int)payload_remainder_bits;
        signature_difference = signature_difference + 1) {
      (&payload_remainder_buffer)[signature_difference] =
           cleartext_header.ecu_type[size + signature_difference + 1];
    }
    if (remaining_data_size == (int)(short)cleartext_header._0_2_ + payload_remainder_bits) {
      memmove(&flash_staging_buffer + (short)cleartext_header._0_2_,&payload_remainder_buffer,
              payload_remainder_bits);
      cleartext_header._0_2_ = cleartext_header._0_2_ + (short)payload_remainder_bits;
      uVar6 = ((longlong)(short)cleartext_header._0_2_ & 7U) * 0x20000000 +
              (((longlong)(short)cleartext_header._0_2_ << 0x20) >> 0x3f);
      if (((uint)((uVar6 & 0xffffffff) << 3) | (uint)uVar6 >> 0x1d) !=
          (int)(short)cleartext_header._0_2_ >> 0x1f) {
        lVar2 = ((longlong)(short)cleartext_header._0_2_ << 0x20) >> 0x3f;
        uVar6 = ((longlong)(short)cleartext_header._0_2_ & 7U) * 0x20000000 + lVar2;
        lVar2 = 8 - (((uVar6 & 0x1fffffff) << 3 | (uVar6 << 0x20) >> 0x3d) - lVar2);
        signature_difference = (int)lVar2;
        bootloader_memset(&flash_staging_buffer + (short)cleartext_header._0_2_,0xff,
                          signature_difference);
        cleartext_header._0_2_ = cleartext_header._0_2_ + (short)lVar2;
        remaining_data_size = remaining_data_size + signature_difference;
      }
    }
    cleartext_header._2_2_ = 0;
    rx_msg_flags = 0;
    rx_msg_total_bytes = 0;
    uVar5 = 2;
  }
  return uVar5;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 bootloader_process_encrypted_header(void)

{
  ulonglong uVar1;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  ulonglong _decrypted_hdr_payload_size;
  int iVar6;
  undefined8 uVar5;
  ulonglong uVar7;
  ushort uVar8;
  int iVar9;
  
  if (download_block_count == 0) {
    bootloader_download_decrypt_and_align
              ((byte *)&decrypted_header,(byte *)(cleartext_header.ecu_type + 1),
               (int)rx_msg_total_bytes - 6U & 0xffff);
    lVar2 = bytes_to_int32((byte *)&decrypted_header.start_addr);
    lVar3 = bytes_to_int32((byte *)&decrypted_header.end_addr);
    lVar4 = bytes_to_int32((byte *)&decrypted_header.region_id);
    header_region_id = (int)lVar4;
    lVar4 = bytes_to_int32((byte *)&decrypted_header.total_size);
    remaining_data_size = (int)lVar4;
    _decrypted_hdr_payload_size = bytes_to_int32((byte *)&decrypted_header.payload_size);
    header_payload_size = (uint)_decrypted_hdr_payload_size;
    if (header_region_id == 1) {
      flash_target_base = 0x800;
    }
    else if (header_region_id == 2) {
      flash_target_base = 0x808;
    }
    else if (header_region_id == 3) {
      flash_target_base = 0x838;
    }
    else if (header_region_id == 4) {
      flash_target_base = 0x40000;
    }
    else if (header_region_id == 5) {
      flash_target_base = 0x20000;
    }
    else if (header_region_id == 7) {
      flash_target_base = 0x1c000;
    }
    else if (header_region_id == 8) {
      flash_target_base = 0x1c000;
    }
    else if (header_region_id == 9) {
      flash_target_base = 0x1c020;
    }
    else if (header_region_id == 10) {
      flash_target_base = 0x858;
    }
    else if (header_region_id == 0xb) {
      flash_target_base = 0x878;
    }
    else {
      flash_target_base = -1;
    }
    uVar7 = (_decrypted_hdr_payload_size & 0xffffffff) + 0xc;
    uVar1 = (uVar7 & 7) * 0x20000000 + ((longlong)(uVar7 << 0x20) >> 0x3f);
    if (((uint)((uVar1 & 0xffffffff) << 3) | (uint)uVar1 >> 0x1d) == (int)uVar7 >> 0x1f) {
      header_alignment_padding = 0;
    }
    else {
      uVar1 = (_decrypted_hdr_payload_size & 0xffffffff) + 0xc;
      uVar7 = (uVar1 & 7) * 0x20000000 + ((longlong)(uVar1 << 0x20) >> 0x3f);
      header_alignment_padding =
           8 - (((uint)((uVar7 & 0xffffffff) << 3) | (uint)uVar7 >> 0x1d) - ((int)uVar1 >> 0x1f));
    }
    iVar6 = bootloader_strncmp(decrypted_header.ecu_type,ECU_type,31);
    if (iVar6 == 0) {
      iVar6 = (int)lVar3;
      iVar9 = (int)lVar2;
      if (_bootloader_flash_programming_addr < 1) {
        if ((((flash_target_base == 0x800) && (iVar9 == iVar6)) && (0 < iVar9)) &&
           ((int)rx_msg_total_bytes == header_alignment_padding + 0x52)) {
          flash_write_pointer = flash_target_base;
          memmove(&flash_staging_buffer,(byte *)&decrypted_header.end_addr,4);
          memmove(&DAT_40001c9c,&DAT_00000804,4);
          cleartext_header._0_2_ = 8;
          cleartext_header._2_2_ = 0;
          rx_msg_flags = 0;
          rx_msg_total_bytes = 0;
          uVar5 = 3;
        }
        else {
          uVar5 = 0x8a;
        }
      }
      else if (((iVar9 < 1) && (iVar6 < 1)) ||
              ((iVar9 <= _bootloader_flash_programming_addr &&
               (_bootloader_flash_programming_addr <= iVar6)))) {
        if (((((flash_target_base == 0x40000) && (remaining_data_size < 0xc0001)) ||
             (((flash_target_base == 0x20000 && (remaining_data_size < 0x10001)) ||
              ((((flash_target_base == 0x808 && (remaining_data_size == 4)) &&
                (crypto_flags == (byte  [4])0xffffffff)) ||
               (((flash_target_base == 0x858 && (remaining_data_size == 0x20)) &&
                (uVar1 = check_array_0xff(ecu_model_number,0x20), (uVar1 & 0xff) == 1)))))))) ||
            (((flash_target_base == 0x878 && (remaining_data_size == 0x20)) &&
             (uVar1 = check_array_0xff((char *)BYTE_ARRAY_00000878,0x20), (uVar1 & 0xff) == 1)))) ||
           (((flash_target_base == 0x838 && (remaining_data_size == 0x20)) &&
            (uVar1 = check_array_0xff(flash_0838_identifier,32), (uVar1 & 0xff) == 1)))) {
          flash_write_pointer = flash_target_base;
          if ((int)header_payload_size < 0x41) {
            uVar5 = 1;
          }
          else {
            uVar8 = (ushort)(byte)cleartext_header.payload_size * 0x100 +
                    (ushort)(byte)cleartext_header.ecu_type[0];
            if ((int)((uVar8 - 0xc) - header_alignment_padding) < (int)header_payload_size) {
              uVar8 = (uVar8 - 0x4c) - xtea_unencrypted_trailer_bytes;
              _xtea_encrypted_block_size = uVar8 & 0xfff8;
              payload_remainder_bits = uVar8 & 7;
              for (iVar6 = 0; iVar6 < (int)payload_remainder_bits; iVar6 = iVar6 + 1) {
                (&payload_remainder_buffer)[iVar6] =
                     (&decrypted_payload_data)[(uint)_xtea_encrypted_block_size + iVar6];
              }
            }
            else {
              uVar7 = (ulonglong)header_payload_size - 0x40;
              uVar1 = (uVar7 & 7) * 0x20000000 + ((longlong)(uVar7 << 0x20) >> 0x3f);
              if (((uint)((uVar1 & 0xffffffff) << 3) | (uint)uVar1 >> 0x1d) == (int)uVar7 >> 0x1f) {
                _xtea_encrypted_block_size = (short)header_payload_size - 0x40;
              }
              else {
                lVar2 = (longlong)((ulonglong)header_payload_size - 0x40 << 0x20) >> 0x3f;
                uVar1 = ((ulonglong)header_payload_size - 0x40 & 7) * 0x20000000 + lVar2;
                iVar6 = 0;
                for (lVar2 = ((uVar1 & 0x1fffffff) << 3 | (uVar1 << 0x20) >> 0x3d) - lVar2;
                    (int)lVar2 < 8; lVar2 = lVar2 + 1) {
                  decrypted_header.ecu_type[header_payload_size + iVar6] = -1;
                  iVar6 = iVar6 + 1;
                }
                _xtea_encrypted_block_size = ((short)header_payload_size + (short)iVar6) - 0x40;
              }
            }
            memmove(&flash_staging_buffer,&decrypted_payload_data,(uint)_xtea_encrypted_block_size);
            cleartext_header._0_2_ = _xtea_encrypted_block_size;
            cleartext_header._2_2_ = 0;
            memmove((byte *)&decrypted_header,
                    (byte *)((int)&cleartext_header +
                            ((int)rx_msg_total_bytes - (uint)xtea_unencrypted_trailer_bytes) + 7),
                    (uint)xtea_unencrypted_trailer_bytes);
            trailer_byte_count_saved = xtea_unencrypted_trailer_bytes;
            rx_msg_flags = 0;
            rx_msg_total_bytes = 0;
            uVar5 = 3;
          }
        }
        else if (((flash_target_base == 0x1c000) && (header_region_id == 8)) &&
                ((header_payload_size == 0x60 &&
                 (uVar1 = check_array_0xff((char *)&EEPROM_variant_coding,0x20), (uVar1 & 0xff) == 1
                 )))) {
          flash_write_pointer = flash_target_base;
          memmove(&flash_staging_buffer,(byte *)&EEPROM_variant_coding,64);
          memmove(&flash_staging_buffer,&decrypted_payload_data,header_payload_size - 64);
          cleartext_header._0_2_ = 0x40;
          cleartext_header._2_2_ = 0;
          rx_msg_flags = 0;
          rx_msg_total_bytes = 0;
          uVar5 = 3;
        }
        else if ((((flash_target_base == 0x1c000) && (header_region_id == 7)) &&
                 (header_payload_size == 0x60)) &&
                ((iVar9 == iVar6 && (iVar9 == _bootloader_flash_programming_addr)))) {
          flash_write_pointer = flash_target_base;
          memmove(&flash_staging_buffer,(byte *)&EEPROM_variant_coding,64);
          memmove(&flash_staging_buffer,&decrypted_payload_data,header_payload_size - 64);
          cleartext_header._0_2_ = 64;
          cleartext_header._2_2_ = 0;
          rx_msg_flags = 0;
          rx_msg_total_bytes = 0;
          uVar5 = 3;
        }
        else if ((flash_target_base == 0x1c020) &&
                (((header_payload_size == 0x60 && (iVar9 == iVar6)) &&
                 (iVar9 == _bootloader_flash_programming_addr)))) {
          flash_write_pointer = 0x1c000;
          memmove(&flash_staging_buffer,(byte *)&EEPROM_variant_coding,0x40);
          memmove(&DAT_40001cb8,&decrypted_payload_data,header_payload_size - 0x40);
          cleartext_header._0_2_ = 0x40;
          cleartext_header._2_2_ = 0;
          rx_msg_flags = 0;
          rx_msg_total_bytes = 0;
          uVar5 = 3;
        }
        else if ((((flash_target_base == 0x800) && (iVar9 == iVar6)) &&
                 ((0 < iVar9 &&
                  (((int)rx_msg_total_bytes == header_alignment_padding + 0x52 &&
                   (0 < _bootloader_flash_programming_addr)))))) ||
                ((((flash_target_base == 0x838 &&
                   ((header_payload_size == 0x60 &&
                    (uVar1 = check_array_0xff(flash_0838_identifier,0x20), (uVar1 & 0xff) == 0))))
                  || ((flash_target_base == 0x858 &&
                      ((header_payload_size == 0x60 &&
                       (uVar1 = check_array_0xff(ecu_model_number,32), (uVar1 & 0xff) == 0)))))) ||
                 (((flash_target_base == 0x878 &&
                   ((header_payload_size == 0x60 &&
                    (uVar1 = check_array_0xff((char *)BYTE_ARRAY_00000878,32), (uVar1 & 0xff) == 0))
                   )) || ((flash_target_base == 0x1c000 &&
                          ((header_payload_size == 0x60 &&
                           (uVar1 = check_array_0xff((char *)&EEPROM_variant_coding,32),
                           (uVar1 & 0xff) == 0)))))))))) {
          uVar5 = 0x8f;
        }
        else {
          uVar5 = 0x8d;
        }
      }
      else {
        uVar5 = 0x8c;
      }
    }
    else {
      uVar5 = 0x8b;
    }
  }
  else {
    memmove((byte *)(decrypted_header.ecu_type + (short)trailer_byte_count_saved + -0xc),
            (byte *)(cleartext_header.ecu_type + 1),(int)rx_msg_total_bytes - 6);
    trailer_byte_count_saved = (rx_msg_total_bytes + trailer_byte_count_saved) - 6;
    memmove(&flash_staging_buffer,&payload_remainder_buffer,payload_remainder_bits);
    cleartext_header._0_2_ = SUB42(payload_remainder_bits,0);
    bootloader_download_decrypt_and_align
              (&flash_staging_buffer + (short)cleartext_header._0_2_,(byte *)&decrypted_header,
               (uint)trailer_byte_count_saved);
    cleartext_header._0_2_ = cleartext_header._0_2_ + _xtea_encrypted_block_size;
    trailer_byte_count_saved = xtea_unencrypted_trailer_bytes;
    memmove((byte *)&decrypted_header,
            (byte *)((int)&cleartext_header +
                    ((int)rx_msg_total_bytes - (uint)xtea_unencrypted_trailer_bytes) + 7),
            (uint)xtea_unencrypted_trailer_bytes);
    uVar1 = ((longlong)(short)cleartext_header._0_2_ & 7U) * 0x20000000 +
            (((longlong)(short)cleartext_header._0_2_ << 0x20) >> 0x3f);
    payload_remainder_bits =
         ((uint)((uVar1 & 0xffffffff) << 3) | (uint)uVar1 >> 0x1d) -
         ((int)(short)cleartext_header._0_2_ >> 0x1f);
    cleartext_header._0_2_ = cleartext_header._0_2_ & 0xfff8;
    for (iVar6 = 0; iVar6 < (int)payload_remainder_bits; iVar6 = iVar6 + 1) {
      (&payload_remainder_buffer)[iVar6] =
           (&flash_staging_buffer)[(short)cleartext_header._0_2_ + iVar6];
    }
    if (remaining_data_size <=
        (int)(((int)(short)cleartext_header._0_2_ + payload_remainder_bits) -
             (int)(short)header_alignment_padding)) {
      cleartext_header._0_2_ =
           (cleartext_header._0_2_ + (short)payload_remainder_bits) -
           (short)header_alignment_padding;
      uVar1 = ((longlong)(short)cleartext_header._0_2_ & 7U) * 0x20000000 +
              (((longlong)(short)cleartext_header._0_2_ << 0x20) >> 0x3f);
      if (((uint)((uVar1 & 0xffffffff) << 3) | (uint)uVar1 >> 0x1d) !=
          (int)(short)cleartext_header._0_2_ >> 0x1f) {
        lVar2 = ((longlong)(short)cleartext_header._0_2_ << 0x20) >> 0x3f;
        uVar1 = ((longlong)(short)cleartext_header._0_2_ & 7U) * 0x20000000 + lVar2;
        iVar6 = 0;
        for (lVar2 = 8 - (((uVar1 & 0x1fffffff) << 3 | (uVar1 << 0x20) >> 0x3d) - lVar2);
            0 < (int)lVar2; lVar2 = lVar2 + -1) {
          (&flash_staging_buffer)[(short)cleartext_header._0_2_ + iVar6] = 0xff;
          iVar6 = iVar6 + 1;
        }
        cleartext_header._0_2_ = cleartext_header._0_2_ + (short)iVar6;
      }
    }
    cleartext_header._2_2_ = 0;
    rx_msg_flags = 0;
    rx_msg_total_bytes = 0;
    uVar5 = 2;
  }
  return uVar5;
}



void bootloader_tx_erase_start(void)

{
  bootloader_can_tx_buffer[0] = 3;
  bootloader_can_tx_buffer[1] = 1;
  bootloader_can_tx_buffer[2] = 0;
  bootloader_can_tx_buffer[3] = 0x4e;
  bootloader_can_tx_buffer[4] = 0x20;
  bootloader_can_tx_buffer[5] = 0;
  bootloader_can_tx_buffer[6] = 0;
  bootloader_can_tx_buffer[7] = bootloader_crc8(bootloader_can_tx_buffer,'\a');
  can_tx_frame_length = 8;
  can_tx_frame_offset = 0;
  bootloader_flexcan_a_tx();
  bootloader_watchdog_restart(100000);
  rx_msg_total_bytes = 0;
  rx_msg_flags = 0;
  return;
}



longlong bytes_to_int32(byte *v)

{
  return (ulonglong)*v * 0x1000000 + (ulonglong)v[1] * 0x10000 + (ulonglong)v[2] * 0x100 +
         (ulonglong)v[3];
}



undefined8 check_array_0xff(char *data,byte size)

{
  byte count;
  char value;
  
  count = 0;
  while( true ) {
    if (size <= count) {
      return 1;
    }
    value = *data;
    data = data + 1;
    if (value != -1) break;
    count = count + 1;
  }
  return 0;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void bootloader_download_decrypt_and_align
               (byte *plaintext_output,byte *ciphertext_input,size_t size)

{
  xtea_unencrypted_trailer_bytes = (ushort)(((ulonglong)size & 7) * 0x20000000 >> 0x10) >> 0xd;
  _xtea_encrypted_block_size = (short)size - xtea_unencrypted_trailer_bytes;
  bootloader_download_decrypt(plaintext_output,ciphertext_input,_xtea_encrypted_block_size);
  return;
}



// return true if there is active session

bool bootloader_active_check(void)

{
  return (bootloader_session_flags & 0b00011000) != 0;
}



uint8_t bootloader_crc8(byte *data,uint8_t size)

{
  byte bVar1;
  int i;
  
  DAT_400017f2 = 0;
  for (i = 0; i < (char)size; i = i + 1) {
    bVar1 = *data;
    data = data + 1;
    DAT_400017f2 = (&DAT_00007cc8)[bVar1 ^ DAT_400017f2];
  }
  return DAT_400017f2;
}



undefined8 bootloader_rx_frame_valid(void)

{
  undefined8 uVar1;
  
  if ((rx_msg_total_bytes < 6) ||
     (rx_crc8_previous != cleartext_header.ecu_type[rx_msg_total_bytes + -5])) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



void bootloader_running_crc8(byte *v)

{
  rx_crc8_previous = rx_crc8_accumulator;
  rx_crc8_accumulator = (&DAT_00007cc8)[*v ^ rx_crc8_accumulator];
  return;
}



void bootloader_comm_loop(void)

{
  bool active;
  
  while (active = bootloader_active_check(), active) {
    bootloader_comm_loop_hook();
    bootloader_can_rx();
    bootloader_protocol_tick();
    bootloader_flexcan_a_tx();
  }
  bootloader_hw_cleanup();
  return;
}



void bootloader_can_rx(void)

{
  bootloader_flexcan_a_rx_50_51();
  return;
}



void bootloader_flexcan_a_tx(void)

{
  bootloader_flexcan_a_tx_response();
  return;
}



// WARNING: Removing unreachable block (ram,0x00004418)
// 
//   - State 0: FUN_0000446c - Initialization → State 1
//   - State 1: FUN_000044d0 - Wait for unlock → State 2
//   - State 2: FUN_00004654 - Command processing → State 3
//   - State 3: FUN_0000496c - Flash programming operations
//   - State 4: FUN_00004ab4 - Terminal/exit (does nothing)
// 

void bootloader_protocol_tick(void)

{
  if (bootloader_protocol_state == BOOTLOADER_PROTOCOL_DOWNLOAD) {
    bootloader_diag_frame_handler();
  }
  else if (bootloader_protocol_state < BOOTLOADER_PROTOCOL_DOWNLOAD) {
    if (bootloader_protocol_state == BOOTLOADER_PROTOCOL_INIT) {
      bootloader_init();
    }
    else {
      bootloader_state1_unlock();
    }
  }
  else if (bootloader_protocol_state == BOOTLOADER_PROTOCOL_DONE) {
    bootloader_state_terminate();
  }
  else if (bootloader_protocol_state < BOOTLOADER_PROTOCOL_DONE) {
    bootloader_comm_protocol_handler();
  }
  else {
    bootloader_protocol_state = BOOTLOADER_PROTOCOL_INIT;
  }
  return;
}



void bootloader_init(void)

{
  bootloader_can_session_init();
  bootloader_download_state_reset();
  bootloader_timebase_reset();
  bootloader_xtea_cbc_reset();
  bootloader_session_flags = bootloader_session_flags & 0x10;
  download_block_count = 0;
  unlock_sequence_step = 0;
  tx_retry_count = 0;
  bootloader_rx_window_set(0);
  bootloader_protocol_state = BOOTLOADER_PROTOCOL_UNLOCK;
  return;
}



void bootloader_state1_unlock(void)

{
  bool cVar2;
  short sVar3;
  undefined8 uVar1;
  ulonglong uVar2;
  
  cVar2 = bootloader_rx_window_expired();
  if ((cVar2) && ((bootloader_session_flags & 8) == 0)) {
    if (unlock_sequence_step == uVar5) {
      unlock_sequence_step = unlock_sequence_step + 1;
      bootloader_tx_ack();
      bootloader_rx_window_set(100000);
      bootloader_watchdog_restart(100000);
    }
    else {
      bootloader_session_flags = bootloader_session_flags & 0xef;
      unlock_sequence_step = unlock_sequence_step + 1;
    }
  }
  else {
    cVar2 = bootloader_rx_ready_or_timeout();
    if ((cVar2) && (sVar3 = bootloader_rx_msg_len(), sVar3 == 8)) {
      uVar1 = bootloader_rx_frame_valid();
      if ((int)uVar1 == 1) {
        rx_crc8_previous = 0;
        rx_crc8_accumulator = 0;
        uVar2 = bootloader_rx_set_target_address();
        if ((uVar2 & 0xff) == 1) {
          bootloader_tx_address_response();
          address_response_retry_count = 0;
          bootloader_protocol_state = BOOTLOADER_PROTOCOL_DOWNLOAD;
        }
        else {
          uVar2 = bootloader_rx_enter_flash_mode();
          if ((uVar2 & 0xff) == 1) {
            bootloader_session_flags = bootloader_session_flags & 0xef | 8;
          }
          else {
            uVar2 = bootloader_rx_end_session();
            if ((uVar2 & 0xff) == 1) {
              bootloader_session_flags = bootloader_session_flags & 0xf7;
            }
            else {
              bootloader_tx_abort(0x81);
            }
          }
        }
      }
      else {
        DAT_40001878._0_1_ = rx_crc8_previous;
        bootloader_flexcan_a_tx(0x7a3,uVar8);
        rx_crc8_previous = 0;
        rx_crc8_accumulator = 0;
        bootloader_tx_retry(0x97);
      }
    }
  }
  return;
}



void bootloader_diag_frame_handler(void)

{
  ushort uVar1;
  ushort uVar2;
  ulonglong uVar3;
  short sVar4;
  bool bVar5;
  short _msg_len;
  short _msg_len_unknown;
  
  uVar2 = (ushort)(byte)cleartext_header.payload_size;
  uVar1 = (ushort)(byte)cleartext_header.ecu_type[0];
  uVar3 = bootloader_rx_frame_valid();
  bootloader_eeprom_erase_deferred();
  bootloader_eeprom_write_staged();
  if (((((bootloader_session_flags & 2) == 0) && ((bootloader_session_flags & 1) == 0)) ||
      (((bootloader_session_flags & 1) == 1 &&
       (((bootloader_session_flags & 4) == 0 && (sVar4 = bootloader_rx_msg_len(), sVar4 != 0))))))
     && (((5 < rx_msg_total_bytes &&
          (((int)(short)(uVar2 * 0x100 + uVar1) == rx_msg_total_bytes + -6 && ((uVar3 & 0xff) == 1))
          )) || (bVar5 = bootloader_timeout_expired_2(), bVar5)))) {
    rx_crc8_previous_saved = rx_crc8_previous;
    rx_crc8_previous = 0;
    rx_crc8_accumulator = 0;
    if ((bootloader_error_flags & 2) == 2) {
      bootloader_tx_abort(0x85);
    }
    else if ((bootloader_error_flags & 1) == 1) {
      bootloader_tx_abort(0x88);
    }
    else {
      _msg_len = bootloader_rx_msg_len();
      if (_msg_len < 1025) {
        _msg_len_unknown = bootloader_rx_msg_len();
        if (_msg_len_unknown == 0) {
          if ((remaining_data_size < 1) && (flash_target_base != 0)) {
            bootloader_tx_program_start();
            bootloader_protocol_state = BOOTLOADER_PROTOCOL_WRITE;
          }
          else if ((bootloader_session_flags & 4) == 4) {
            address_response_retry_count = address_response_retry_count + 1;
            if (address_response_retry_count < 100) {
              bootloader_tx_address_response();
            }
            else {
              bootloader_tx_abort(0x8e);
              address_response_retry_count = 0;
            }
          }
          else {
            bootloader_tx_abort(0x83);
          }
        }
        else if ((uVar3 & 0xff) == 0) {
          rx_crc8_previous = 0;
          rx_crc8_accumulator = 0;
          bootloader_tx_retry(0x97);
        }
        else {
          uVar3 = bootloader_rx_handle_retransmit();
          if ((uVar3 & 0xff) == 0) {
            uVar3 = bootloader_dl_request_handler();
            if (((uVar3 & 0xff) < 0x80) || (0x95 < (uVar3 & 0xff))) {
              if (((uVar3 & 0xff) < 0x96) || (0x9f < (uVar3 & 0xff))) {
                if ((uVar3 & 0xff) == 2) {
                  download_block_count = download_block_count + 1;
                  bootloader_session_flags = bootloader_session_flags | 2;
                  if ((short)cleartext_header._0_2_ < remaining_data_size) {
                    bootloader_tx_address_response();
                    address_response_retry_count = 0;
                  }
                }
                else if ((uVar3 & 0xff) == 3) {
                  download_block_count = download_block_count + 1;
                  bootloader_session_flags = bootloader_session_flags | 3;
                  bootloader_tx_erase_start();
                }
              }
              else {
                bootloader_tx_retry((char)uVar3);
              }
            }
            else {
              bootloader_tx_abort((char)uVar3);
            }
          }
        }
      }
      else {
        bootloader_tx_retry(0x96);
      }
    }
  }
  return;
}



void bootloader_comm_protocol_handler(void)

{
  bool bootloader_comm_active;
  int msg_count___;
  undefined8 uVar1;
  ulonglong uVar2;
  
  bootloader_comm_active = bootloader_timeout_expired_2();
  if (bootloader_comm_active) {
    msg_count___._2_2_ = bootloader_rx_msg_len();
    if (msg_count___._2_2_ == 0) {
      bootloader_session_flags = bootloader_session_flags & 0xef;
    }
    else {
      uVar1 = bootloader_rx_frame_valid();
      if ((int)uVar1 == 1) {
        uVar2 = bootloader_rx_handle_retransmit();
        if ((uVar2 & 0xff) == 1) {
          bootloader_retransmit_last();
        }
        else {
          uVar2 = bootloader_rx_set_target_address();
          if ((uVar2 & 0xff) == 1) {
            download_block_count = 0;
            bootloader_tx_address_response();
            rx_crc8_previous = 0;
            rx_crc8_accumulator = 0;
            bootloader_download_state_reset();
            download_block_count = 0;
            unlock_sequence_step = 0;
            tx_retry_count = 0;
            bootloader_session_flags = bootloader_session_flags & 0xfb;
            bootloader_protocol_state = BOOTLOADER_PROTOCOL_DOWNLOAD;
          }
          else {
            uVar2 = bootloader_rx_end_session();
            if ((uVar2 & 0xff) == 1) {
              bootloader_session_flags = bootloader_session_flags & 0xf7;
            }
            else {
              bootloader_tx_abort(0x87);
            }
          }
        }
      }
      else {
        DAT_40001878._0_1_ = rx_crc8_previous;
        bootloader_flexcan_a_tx(0x7a4,1);
        rx_crc8_previous = 0;
        rx_crc8_accumulator = 0;
        bootloader_tx_retry(0x97);
      }
      rx_crc8_previous = 0;
      rx_crc8_accumulator = 0;
    }
  }
  return;
}



void bootloader_state_terminate(void)

{
  return;
}



void bootloader_eeprom_erase_deferred(void)

{
  short sVar1;
  bool bVar2;
  
  if ((((bootloader_session_flags & 1) == 1) && (sVar1 = bootloader_rx_msg_len(), sVar1 == 0)) &&
     (bVar2 = bootloader_timeout_expired_2(), bVar2)) {
    bVar2 = bootloader_eeprom_erase_immediate___();
    if (!bVar2) {
      bootloader_error_flags = bootloader_error_flags | 1;
    }
    bootloader_session_flags = bootloader_session_flags & 0xfe | 4;
  }
  return;
}



void bootloader_eeprom_write_staged(void)

{
  bool bVar1;
  
  if (((bootloader_session_flags & 2) == 2) && ((bootloader_session_flags & 4) == 4)) {
    bVar1 = bootloader_flash_write_staged_chunk();
    if (bVar1) {
      bVar1 = bootloader_staging_buf_drained();
      if (bVar1) {
        bootloader_session_flags = bootloader_session_flags & 0xfd;
      }
    }
    else {
      bootloader_error_flags = bootloader_error_flags | 2;
      bootloader_session_flags = bootloader_session_flags & 0xfd;
    }
  }
  return;
}



bool bootloader_staging_buf_drained(void)

{
  return (short)cleartext_header._0_2_ <= (short)cleartext_header._2_2_;
}



bool bootloader_eeprom_erase_immediate___(void)

{
  int iVar1;
  
  iVar1 = 1;
  if (flash_target_base == 0x40000) {
    iVar1 = flash_c55fmc_program((byte *)0xf,(byte *)0x3,0);
  }
  else if (flash_target_base == 0x20000) {
    iVar1 = flash_c55fmc_program((byte *)0x0,(byte *)0x0,0x10);
  }
  else if (flash_target_base == 0x858) {
    iVar1 = flash_c55fmc_program((byte *)0x0,(byte *)0x0,1);
  }
  else if (flash_target_base == 0x878) {
    iVar1 = flash_c55fmc_program((byte *)0x0,(byte *)0x0,1);
  }
  else if (flash_target_base == 0x838) {
    iVar1 = flash_c55fmc_program((byte *)0x0,(byte *)0x0,1);
  }
  else if (flash_target_base == 0x1c000) {
    iVar1 = flash_c55fmc_program((byte *)0x0,(byte *)0x0,8);
  }
  else if (flash_target_base == 0x1c020) {
    iVar1 = flash_c55fmc_program((byte *)0x0,(byte *)0x0,8);
  }
  else if (flash_target_base == 0x800) {
    iVar1 = flash_c55fmc_program((byte *)0x0,(byte *)0x0,1);
  }
  else if (flash_target_base == 0x808) {
    iVar1 = flash_c55fmc_program((byte *)0x0,(byte *)0x0,1);
  }
  return iVar1 == 0;
}



void bootloader_download_state_reset(void)

{
  cleartext_header._0_2_ = 0;
  cleartext_header._2_2_ = 0;
  cleartext_header._4_1_ = 0;
  header_region_id = 0;
  flash_target_base = 0;
  remaining_data_size = 0;
  flash_write_pointer = 0;
  return;
}



bool bootloader_flash_write_staged_chunk(void)

{
  ulonglong uVar1;
  bool bVar2;
  ulonglong uVar3;
  int iVar4;
  
  if ((((((flash_target_base == 0x40000) || (flash_target_base == 0x20000)) ||
        (flash_target_base == 0x800)) ||
       ((flash_target_base == 0x808 || (flash_target_base == 0x838)))) ||
      ((flash_target_base == 0x1c000 ||
       ((flash_target_base == 0x1c020 || (flash_target_base == 0x858)))))) ||
     (flash_target_base == 0x878)) {
    uVar3 = (longlong)(short)cleartext_header._0_2_ - (longlong)(short)cleartext_header._2_2_;
    iVar4 = (int)uVar3;
    if (iVar4 < 0x11) {
      if (iVar4 < 8) {
        if (iVar4 < 1) {
          return false;
        }
      }
      else {
        uVar3 = 8;
      }
    }
    else {
      uVar3 = 0x10;
    }
    uVar1 = (uVar3 & 7) * 0x20000000 + ((longlong)(uVar3 << 0x20) >> 0x3f);
    iVar4 = (int)uVar3;
    if ((((uint)((uVar1 & 0xffffffff) << 3) | (uint)uVar1 >> 0x1d) == iVar4 >> 0x1f) &&
       ((flash_write_pointer & 7) == 0)) {
      uVar1 = bootloader_flash_c55fmc_program_and_wait
                        (flash_write_pointer,&flash_staging_buffer + (short)cleartext_header._2_2_,
                         iVar4);
      flash_write_pointer = flash_write_pointer + iVar4;
      remaining_data_size = remaining_data_size - iVar4;
      cleartext_header._2_2_ = cleartext_header._2_2_ + (short)uVar3;
      bVar2 = (uVar1 & 0xff) == 0;
    }
    else {
      bVar2 = false;
    }
  }
  else {
    bVar2 = false;
  }
  return bVar2;
}



void bootloader_hc08_prog_finalize(void)

{
  flash_c55fmc_program((byte *)0x0,(byte *)0x1,0);
  memmove(&flash_staging_buffer,(byte *)&HC08CODE_base.programming_magic_word,8);
  flash_staging_buffer = 0;
  DAT_40001c99 = 0;
  DAT_40001c9a = 0;
  DAT_40001c9b = 0;
  bootloader_flash_c55fmc_program_and_wait(0x40088,&flash_staging_buffer,8);
  bootloader_hw_cleanup();
  return;
}



void bootloader_hc08_set_reprogram_flag(void)

{
  flash_c55fmc_program((byte *)0x0,(byte *)0x1,0);
  memmove(&flash_staging_buffer,(byte *)&HC08CODE_base.programming_magic_word,8);
  flash_staging_buffer = 0x88;
  DAT_40001c99 = 0x88;
  DAT_40001c9a = 0x88;
  DAT_40001c9b = 0x88;
  bootloader_flash_c55fmc_program_and_wait(0x40088,&flash_staging_buffer,8);
  bootloader_hw_cleanup();
  return;
}



void bootloader_xtea_decrypt(uint *param_1,uint *param_2)

{
  bool bVar1;
  int rounds;
  ulonglong sum;
  ulonglong v1;
  ulonglong v0;
  
  sum = 0xffffffffc6ef3720;
  rounds = 0x20;
  v0 = (ulonglong)*param_1;
  v1 = (ulonglong)*param_2;
  while( true ) {
    bVar1 = rounds == 0;
    rounds = rounds + -1;
    if (bVar1) break;
    v1 = v1 - (v0 + ((v0 & 0xfffffff) << 4 ^ (v0 << 0x20) >> 0x25) ^
              sum + *(uint *)((int)bootloader_xtea_key + (int)(((sum << 0x20) >> 0x2b & 3) << 2)));
                    // Why is the golden ratio here?
                    // I thought it was only needed to avoid attacks in TEA.
    sum = sum + 0x61c88647;
    v0 = v0 - (v1 + ((v1 & 0xfffffff) << 4 ^ (v1 << 0x20) >> 0x25) ^
              sum + *(uint *)((int)bootloader_xtea_key + (int)((sum & 3) << 2)));
  }
  *param_1 = (uint)v0;
  *param_2 = (uint)v1;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

ushort bootloader_download_decrypt
                 (byte *plaintext_output,byte *ciphertext_input,uint16_t len_aligned)

{
  for (; 7 < len_aligned; len_aligned = len_aligned - 8) {
    __xtea_ciphertext_block_high = *(uint *)ciphertext_input;
    _xtea_ciphertext_block_low = *(uint *)((int)ciphertext_input + 4);
    ciphertext_input = (byte *)((int)ciphertext_input + 8);
    xtea_decrypted_block_low = _xtea_ciphertext_block_low;
    xtea_decrypted_block_high = __xtea_ciphertext_block_high;
    bootloader_xtea_decrypt(&xtea_decrypted_block_high,&xtea_decrypted_block_low);
    xtea_decrypted_block_high = xtea_decrypted_block_high ^ xtea_cbc_iv_high;
    xtea_decrypted_block_low = xtea_decrypted_block_low ^ xtea_cbc_iv_low;
    xtea_cbc_iv_high = __xtea_ciphertext_block_high;
    xtea_cbc_iv_low = _xtea_ciphertext_block_low;
    *(uint *)plaintext_output = xtea_decrypted_block_high;
    *(uint *)((int)plaintext_output + 4) = xtea_decrypted_block_low;
    plaintext_output = (byte *)((int)plaintext_output + 8);
  }
  return len_aligned & 0xff;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void bootloader_xtea_cbc_reset(void)

{
  xtea_cbc_iv_low = 0;
  xtea_cbc_iv_high = 0;
  xtea_decrypted_block_low = 0;
  xtea_decrypted_block_high = 0;
  _xtea_ciphertext_block_low = 0;
  __xtea_ciphertext_block_high = 0;
  return;
}



void bootloader_timebase_reset(void)

{
  timebase_reset_and_clear_dbsr();
  return;
}



void bootloader_watchdog_restart(u32_time_us ticks)

{
  bootloader_watchdog_set(ticks);
  return;
}



void bootloader_comm_loop_hook(void)

{
  bootloader_noop();
  return;
}



bool bootloader_rx_window_expired(void)

{
  bool bVar1;
  
  bVar1 = bootloader_rx_timer_expired();
  return bVar1;
}



void bootloader_rx_window_set(int param_1)

{
  bootloader_rx_timer_set(param_1);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
//  1. Stores the three block-select bitmasks into the SDA-relative work area (0xffff80b8/bc/c0)
//   2. Calls FlashSetLock (via function pointer at r13+0x18) with the Freescale C55FMC unlock
// passwords:
//     - 0xA1A11111 — mid array unlock password
//     - 0xC3C33333 — low array unlock password
//     - 0xB2B22222 — high array unlock password
//   3. Calls FlashGetLock (via r13+0x14) to read current lock state, then clears the relevant bits
//   4. Calls FlashErase (via r13+4) to erase the selected blocks
//   5. Calls FlashCheckStatus (via r13+8) to wait for completion
// 

undefined8 flash_c55fmc_program(byte *dest,byte *src,size_t len)

{
  undefined8 uVar1;
  
  DAT_4000185c = 0;
  DAT_40001850 = dest;
  DAT_40001854 = src;
  DAT_40001858 = len;
  uVar1 = (*DAT_40001798)(&DAT_40001770);
  if ((int)uVar1 == 0) {
    if ((DAT_40001850 == (byte *)0x0) || (DAT_40001854 == (byte *)0x0)) {
      if (DAT_40001858 == 0) {
        if (DAT_40001854 == (byte *)0x1) {
          uVar1 = (*_DAT_400017ac)(&DAT_40001770,4,&DAT_4000182c,&DAT_40001828);
          if ((int)uVar1 != 0) {
            return uVar1;
          }
          if ((DAT_40001854 == (byte *)(DAT_40001828 & (uint)DAT_40001854)) &&
             (uVar1 = (*_DAT_400017b0)(&DAT_40001770,4,DAT_40001828 & ~(uint)DAT_40001854,
                                       0xffffffffa1a11111), (int)uVar1 != 0)) {
            return uVar1;
          }
          uVar1 = (*_DAT_400017ac)(&DAT_40001770,5,&DAT_4000182c,&DAT_40001828);
          if ((int)uVar1 != 0) {
            return uVar1;
          }
          if ((DAT_40001854 == (byte *)(DAT_40001828 & (uint)DAT_40001854)) &&
             (uVar1 = (*_DAT_400017b0)(&DAT_40001770,5,DAT_40001828 & ~(uint)DAT_40001854,
                                       0xffffffffc3c33333), (int)uVar1 != 0)) {
            return uVar1;
          }
          DAT_4000184c = DAT_40001774 + 0x40000;
          DAT_40001848 = 0;
        }
      }
      else {
        uVar1 = (*_DAT_400017b0)(&DAT_40001770,0,1,0xffffffffa1a11111);
        if ((int)uVar1 != 0) {
          return uVar1;
        }
        uVar1 = (*_DAT_400017b0)(&DAT_40001770,1,1,0xffffffffc3c33333);
        if ((int)uVar1 != 0) {
          return uVar1;
        }
        uVar1 = (*_DAT_400017ac)(&DAT_40001770,2,&DAT_4000182c,&DAT_40001828);
        if ((int)uVar1 != 0) {
          return uVar1;
        }
        if ((DAT_40001858 == (DAT_40001828 & DAT_40001858)) &&
           (uVar1 = (*_DAT_400017b0)(&DAT_40001770,2,DAT_40001828 & ~DAT_40001858,0xffffffffa1a11111
                                    ), (int)uVar1 != 0)) {
          return uVar1;
        }
        uVar1 = (*_DAT_400017ac)(&DAT_40001770,3,&DAT_4000182c,&DAT_40001828);
        if ((int)uVar1 != 0) {
          return uVar1;
        }
        if ((DAT_40001858 == (DAT_40001828 & DAT_40001858)) &&
           (uVar1 = (*_DAT_400017b0)(&DAT_40001770,3,DAT_40001828 & ~DAT_40001858,0xffffffffc3c33333
                                    ), (int)uVar1 != 0)) {
          return uVar1;
        }
        if (DAT_40001858 == 0x10) {
          DAT_4000184c = DAT_40001774 + 0x20000;
          DAT_40001848 = 0x10000;
        }
        else if (DAT_40001858 == 8) {
          DAT_4000184c = DAT_40001774 + 0x1c000;
          DAT_40001848 = 0x4000;
        }
        else {
          DAT_4000184c = 0;
          DAT_40001848 = 0;
        }
      }
    }
    else {
      uVar1 = (*_DAT_400017b0)(&DAT_40001770,0,1,0xffffffffa1a11111);
      if ((int)uVar1 != 0) {
        return uVar1;
      }
      uVar1 = (*_DAT_400017b0)(&DAT_40001770,1,1,0xffffffffc3c33333);
      if ((int)uVar1 != 0) {
        return uVar1;
      }
      uVar1 = (*_DAT_400017ac)(&DAT_40001770,6,&DAT_4000182c,&DAT_40001828);
      if ((int)uVar1 != 0) {
        return uVar1;
      }
      if ((DAT_40001850 == (byte *)(DAT_40001828 & (uint)DAT_40001850)) &&
         (uVar1 = (*_DAT_400017b0)(&DAT_40001770,6,DAT_40001828 & ~(uint)DAT_40001850,
                                   0xffffffffb2b22222), (int)uVar1 != 0)) {
        return uVar1;
      }
      uVar1 = (*_DAT_400017ac)(&DAT_40001770,4,&DAT_4000182c,&DAT_40001828);
      if ((int)uVar1 != 0) {
        return uVar1;
      }
      if ((DAT_40001854 == (byte *)(DAT_40001828 & (uint)DAT_40001854)) &&
         (uVar1 = (*_DAT_400017b0)(&DAT_40001770,4,DAT_40001828 & ~(uint)DAT_40001854,
                                   0xffffffffa1a11111), (int)uVar1 != 0)) {
        return uVar1;
      }
      uVar1 = (*_DAT_400017ac)(&DAT_40001770,5,&DAT_4000182c,&DAT_40001828);
      if ((int)uVar1 != 0) {
        return uVar1;
      }
      if ((DAT_40001854 == (byte *)(DAT_40001828 & (uint)DAT_40001854)) &&
         (uVar1 = (*_DAT_400017b0)(&DAT_40001770,5,DAT_40001828 & ~(uint)DAT_40001854,
                                   0xffffffffc3c33333), (int)uVar1 != 0)) {
        return uVar1;
      }
      DAT_4000184c = DAT_40001774 + 0x40000;
      DAT_40001848 = 0x40000;
    }
    if (DAT_40001848 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = (*DAT_4000179c)(&DAT_40001770,DAT_4000185c,DAT_40001858,DAT_40001854,DAT_40001850,
                              0xffffffffffffffff);
      if (((int)uVar1 == 0) &&
         (uVar1 = (*DAT_400017a0)(&DAT_40001770,DAT_4000184c,DAT_40001848,&DAT_40001840,
                                  &DAT_40001838,0xffffffffffffffff), (int)uVar1 == 0)) {
        uVar1 = 0;
      }
    }
  }
  return uVar1;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8
bootloader_flash_c55fmc_program_and_wait(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined8 uVar1;
  
  DAT_40001844 = param_2;
  DAT_40001848 = param_3;
  DAT_4000184c = param_1;
  uVar1 = (*_DAT_400017a4)(&DAT_40001770,param_1,param_3,param_2,0xffffffffffffffff);
  if ((int)uVar1 == 0) {
    uVar1 = (*_DAT_400017a8)(&DAT_40001770,DAT_4000184c,DAT_40001848,DAT_40001844,&DAT_40001840,
                             &DAT_40001838,&DAT_40001830,0xffffffffffffffff);
  }
  return uVar1;
}



//     // Clears hardware interrupt flags and resets peripheral registers
//     // Manipulates registers at 0xc3f88xxx addresses
//     // Clears bits in INTC (Interrupt Controller) and peripheral modules
// 

undefined8 bootloader_hw_cleanup(void)

{
  uint uVar1;
  uint uVar2;
  
  if (DAT_40001850 != 0) {
    uVar1 = DAT_c3f88014;
    uVar2 = DAT_c3f88014;
    DAT_c3f88014 = uVar1 & 0xfffffff & ~DAT_40001850 | uVar2 & 0xf0000000;
    uVar1 = DAT_c3f88008;
    uVar2 = DAT_c3f88008;
    DAT_c3f88008 = uVar1 & 0xfffffff | DAT_40001850 & 0xfffffff | uVar2 & 0xf0000000;
  }
  if (DAT_40001858 != 0) {
    uVar1 = DAT_c3f88010;
    uVar2 = DAT_c3f88010;
    DAT_c3f88010 = uVar1 & 0xffff & ~DAT_40001858 | uVar2 & 0xffff0000;
    uVar1 = DAT_c3f88004;
    uVar2 = DAT_c3f88004;
    DAT_c3f88004 = uVar1 & 0xffff | DAT_40001858 & 0xffff | uVar2 & 0xffff0000;
    uVar1 = DAT_c3f8800c;
    uVar2 = DAT_c3f8800c;
    DAT_c3f8800c = uVar1 & 0xffff | DAT_40001858 & 0xffff | uVar2 & 0xffff0000;
  }
  if (DAT_40001854 != 0) {
    uVar1 = DAT_c3f88010;
    uVar2 = DAT_c3f88010;
    DAT_c3f88010 = (uVar1 >> 0x10 & 0xf & ~DAT_40001854) << 0x10 | uVar2 & 0xfff0ffff;
    uVar1 = DAT_c3f88004;
    uVar2 = DAT_c3f88004;
    DAT_c3f88004 = (uVar1 >> 0x10 & 0xf | DAT_40001854 & 0xf) << 0x10 | uVar2 & 0xfff0ffff;
    uVar1 = DAT_c3f8800c;
    uVar2 = DAT_c3f8800c;
    DAT_c3f8800c = (uVar1 >> 0x10 & 0xf | DAT_40001854 & 0xf) << 0x10 | uVar2 & 0xfff0ffff;
  }
  return 0;
}



void bootloader_set_spr150_4000(void)

{
  return;
}



void hc08_serial_bit_start(void)

{
  undefined8 uVar1;
  
  uVar1 = bootload_timebase_read();
  DAT_40001860 = (int)uVar1;
  return;
}



void hc08_serial_bit_wait(uint32_t param_1)

{
  longlong lVar1;
  
  do {
    lVar1 = bootload_timebase_read();
  } while ((lVar1 - (ulonglong)DAT_40001860 & 0xffffffff) <= (ulonglong)param_1);
  return;
}



void bootloader_hc08_bkgd_pre_delay(void)

{
  bootloader_delay_cycles(300);
  return;
}



void bootloader_hc08_bkgd_set_output(void)

{
  bootloader_siu_pcr_write(0xc6,0x2cc);
  return;
}



void bootloader_hc08_bkgd_set_input(void)

{
  bootloader_siu_pcr_write(0xc6,0x100);
  return;
}



void bootloader_hc08_bkgd_high(void)

{
  siu_gpdo[0xc6] = '\x01';
  return;
}



void bootloader_hc08_bkgd_low(void)

{
  siu_gpdo[0xc6] = '\0';
  return;
}



uint8_t bootloader_hc08_bkgd_read(void)

{
  uint8_t uVar1;
  
  uVar1 = siu_gpdi[0xc6];
  return uVar1;
}



void bootloader_hc08_data_pin_high(void)

{
  siu_gpdo[0xce] = '\x01';
  return;
}



void bootloader_esci_a_pin_init(void)

{
  uint uVar1;
  
  uVar1 = SIU_ISEL2;
  SIU_ISEL2 = uVar1 & 0xffffc0ff | 0x200;
  siu_pcr[0xd6] = 716;
  return;
}



void bootloader_hc08_serial_boot_init(void)

{
  DAT_40001864 = HC08CODE_base.firmware;
  siu_gpdo[0xd1] = 0;
  bootloader_siu_pcr_write(0xd1,0x2cc);
  bootloader_esci_a_pin_init();
  bootloader_hc08_bkgd_set_input();
  siu_gpdo[0xce] = '\0';
  bootloader_siu_pcr_write(0xce,0x2cc);
  bootloader_delay_cycles(10000);
  siu_gpdo[0x16] = '\x01';
  bootloader_siu_pcr_write(0x16,0x2cc);
  return;
}



// serial tx by bitbanging

void bootloader_flash_write_byte(byte val)

{
  uint uVar1;
  
  uVar1 = (uint)(char)val;
  bootloader_hc08_bkgd_set_output();
  bootloader_hc08_bkgd_high();
  hc08_serial_bit_start();
  bootloader_hc08_bkgd_low();
  hc08_serial_bit_wait(2000);
  if ((uVar1 & 1) == 0) {
    bootloader_hc08_bkgd_low();
  }
  else {
    bootloader_hc08_bkgd_high();
  }
  hc08_serial_bit_wait(4000);
  if ((uVar1 & 2) == 0) {
    bootloader_hc08_bkgd_low();
  }
  else {
    bootloader_hc08_bkgd_high();
  }
  hc08_serial_bit_wait(6000);
  if ((uVar1 & 4) == 0) {
    bootloader_hc08_bkgd_low();
  }
  else {
    bootloader_hc08_bkgd_high();
  }
  hc08_serial_bit_wait(8000);
  if ((uVar1 & 8) == 0) {
    bootloader_hc08_bkgd_low();
  }
  else {
    bootloader_hc08_bkgd_high();
  }
  hc08_serial_bit_wait(10000);
  if ((uVar1 & 0x10) == 0) {
    bootloader_hc08_bkgd_low();
  }
  else {
    bootloader_hc08_bkgd_high();
  }
  hc08_serial_bit_wait(12000);
  if ((uVar1 & 0x20) == 0) {
    bootloader_hc08_bkgd_low();
  }
  else {
    bootloader_hc08_bkgd_high();
  }
  hc08_serial_bit_wait(14000);
  if ((uVar1 & 0x40) == 0) {
    bootloader_hc08_bkgd_low();
  }
  else {
    bootloader_hc08_bkgd_high();
  }
  hc08_serial_bit_wait(16000);
  if ((uVar1 & 0x80) == 0) {
    bootloader_hc08_bkgd_low();
  }
  else {
    bootloader_hc08_bkgd_high();
  }
  hc08_serial_bit_wait(18000);
  bootloader_hc08_bkgd_high();
  hc08_serial_bit_wait(20000);
  bootloader_hc08_bkgd_set_input();
  return;
}



// read serial response 

byte bootloader_flash_response_rx(void)

{
  uint8_t uVar2;
  ulonglong uVar1;
  byte bVar3;
  
  uVar2 = bootloader_hc08_bkgd_read();
  if (uVar2 != '\0') {
    bootloader_timer_latch(0);
    do {
      uVar2 = bootloader_hc08_bkgd_read();
      if (uVar2 == '\0') {
        hc08_serial_bit_start();
        hc08_serial_bit_wait(3000);
        uVar2 = bootloader_hc08_bkgd_read();
        bVar3 = uVar2 != '\0';
        hc08_serial_bit_wait(5000);
        uVar2 = bootloader_hc08_bkgd_read();
        if (uVar2 != '\0') {
          bVar3 = bVar3 | 2;
        }
        hc08_serial_bit_wait(7000);
        uVar2 = bootloader_hc08_bkgd_read();
        if (uVar2 != '\0') {
          bVar3 = bVar3 | 4;
        }
        hc08_serial_bit_wait(9000);
        uVar2 = bootloader_hc08_bkgd_read();
        if (uVar2 != '\0') {
          bVar3 = bVar3 | 8;
        }
        hc08_serial_bit_wait(11000);
        uVar2 = bootloader_hc08_bkgd_read();
        if (uVar2 != '\0') {
          bVar3 = bVar3 | 0x10;
        }
        hc08_serial_bit_wait(13000);
        uVar2 = bootloader_hc08_bkgd_read();
        if (uVar2 != '\0') {
          bVar3 = bVar3 | 0x20;
        }
        hc08_serial_bit_wait(15000);
        uVar2 = bootloader_hc08_bkgd_read();
        if (uVar2 != '\0') {
          bVar3 = bVar3 | 0x40;
        }
        hc08_serial_bit_wait(17000);
        uVar2 = bootloader_hc08_bkgd_read();
        if (uVar2 != '\0') {
          bVar3 = bVar3 | 0x80;
        }
        hc08_serial_bit_wait(19000);
        bootloader_hc08_bkgd_read();
        hc08_serial_bit_wait(20000);
        return bVar3;
      }
      uVar1 = bootloader_timer_elapsed(0);
    } while ((uVar1 & 0xffffffff) < 0x4c4b401);
  }
  return 0xff;
}



bool hc08_flash_and_verify(void)

{
  int iVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  byte bVar10;
  
  iVar1 = 0x40009870;
                    //   - 0xAAAAAAAA (-0x55555556): Standard flash write/program mode
                    //   - 0x88888888 (-0x77777778): Flash erase verification mode
                    //   - 0xBBBBBBBB (-0x44444445): zero mode
  if ((HC08CODE_base.programming_magic_word == 0xaaaaaaaa) ||
     (HC08CODE_base.programming_magic_word == 0xbbbbbbbb)) {
    bootloader_flash_write_byte(DAT_40001870);
    bVar2 = bootloader_flash_response_rx();
    bootloader_flash_write_byte(*(byte *)(iVar1 + -0x7fff));
    bVar3 = bootloader_flash_response_rx();
    bootloader_flash_write_byte(mpc5534_reserved[iVar1 + 2]);
    bVar4 = bootloader_flash_response_rx();
    bootloader_flash_write_byte(*(byte *)(iVar1 + -0x7ffd));
    bVar5 = bootloader_flash_response_rx();
    bootloader_flash_write_byte(mpc5534_reserved[iVar1 + 4]);
    bVar6 = bootloader_flash_response_rx();
    bootloader_flash_write_byte(mpc5534_reserved[iVar1 + 5]);
    bVar7 = bootloader_flash_response_rx();
    bootloader_flash_write_byte(mpc5534_reserved[iVar1 + 6]);
    bVar8 = bootloader_flash_response_rx();
    bootloader_flash_write_byte(*(byte *)(iVar1 + -0x7ff9));
    bVar9 = bootloader_flash_response_rx();
    bVar10 = bootloader_flash_response_rx();
    if (((((int)(char)bVar2 == (uint)*(byte *)(iVar1 + -0x8000)) &&
         (((((int)(char)bVar3 == (uint)*(byte *)(iVar1 + -0x7fff) &&
            ((int)(char)bVar4 == (uint)mpc5534_reserved[iVar1 + 2])) &&
           ((int)(char)bVar5 == (uint)*(byte *)(iVar1 + -0x7ffd))) &&
          (((int)(char)bVar6 == (uint)mpc5534_reserved[iVar1 + 4] &&
           ((int)(char)bVar7 == (uint)mpc5534_reserved[iVar1 + 5])))))) &&
        ((int)(char)bVar8 == (uint)mpc5534_reserved[iVar1 + 6])) &&
       (((int)(char)bVar9 == (uint)*(byte *)(iVar1 + -0x7ff9) && ((char)bVar10 == 0x8000)))) {
      return true;
    }
  }
  else if (HC08CODE_base.programming_magic_word == 0x88888888) {
    bootloader_flash_write_byte(0xff);
    bVar2 = bootloader_flash_response_rx();
    bootloader_flash_write_byte(0xff);
    bVar3 = bootloader_flash_response_rx();
    bootloader_flash_write_byte(0xff);
    bVar4 = bootloader_flash_response_rx();
    bootloader_flash_write_byte(0xff);
    bVar5 = bootloader_flash_response_rx();
    bootloader_flash_write_byte(0xff);
    bVar6 = bootloader_flash_response_rx();
    bootloader_flash_write_byte(0xff);
    bVar7 = bootloader_flash_response_rx();
    bootloader_flash_write_byte(0xff);
    bVar8 = bootloader_flash_response_rx();
    bootloader_flash_write_byte(0xff);
    bVar9 = bootloader_flash_response_rx();
    bVar10 = bootloader_flash_response_rx();
    if ((((((char)bVar2 == 0xff) && ((char)bVar3 == 0xff)) && ((char)bVar4 == 0xff)) &&
        ((((char)bVar5 == 0xff && ((char)bVar6 == 0xff)) &&
         (((char)bVar7 == 0xff && (((char)bVar8 == 0xff && ((char)bVar9 == 0xff)))))))) &&
       ((char)bVar10 == 0x8000)) {
      return true;
    }
  }
  return false;
}



undefined8 bootloader_hc08_mon08_read_byte(uint param_1,byte *param_2)

{
  byte bVar2;
  undefined8 uVar1;
  
  bootloader_hc08_bkgd_pre_delay();
  bootloader_flash_write_byte(0x4a);
  bVar2 = bootloader_flash_response_rx();
  if (bVar2 == 0x4a) {
    bootloader_flash_write_byte((byte)((param_1 & 0xffff) >> 8));
    bVar2 = bootloader_flash_response_rx();
    if ((int)(param_1 & 0xffff) >> 8 == (int)(char)bVar2) {
      bootloader_flash_write_byte((byte)param_1);
      bVar2 = bootloader_flash_response_rx();
      if ((param_1 & 0xff) == (int)(char)bVar2) {
        bVar2 = bootloader_flash_response_rx();
        if (bVar2 == 0xff) {
          uVar1 = 0;
        }
        else {
          *param_2 = bVar2;
          uVar1 = 1;
        }
      }
      else {
        uVar1 = 0;
      }
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



undefined8 bootloader_hc08_mon08_write_byte(uint param_1,byte param_2)

{
  byte bVar2;
  undefined8 uVar1;
  
  bootloader_hc08_bkgd_pre_delay();
  bootloader_flash_write_byte(0x49);
  bVar2 = bootloader_flash_response_rx();
  if (bVar2 == 0x49) {
    bootloader_flash_write_byte((byte)((param_1 & 0xffff) >> 8));
    bVar2 = bootloader_flash_response_rx();
    if ((int)(param_1 & 0xffff) >> 8 == (int)(char)bVar2) {
      bootloader_flash_write_byte((byte)param_1);
      bVar2 = bootloader_flash_response_rx();
      if ((param_1 & 0xff) == (int)(char)bVar2) {
        bootloader_flash_write_byte(param_2);
        bVar2 = bootloader_flash_response_rx();
        if ((uint)param_2 == (int)(char)bVar2) {
          uVar1 = 1;
        }
        else {
          uVar1 = 0;
        }
      }
      else {
        uVar1 = 0;
      }
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



undefined8 bootloader_hc08_flash_response_rx_word(ushort *param_1)

{
  byte bVar2;
  undefined8 uVar1;
  byte bVar3;
  
  bootloader_hc08_bkgd_pre_delay();
  bootloader_flash_write_byte(0x1a);
  bVar2 = bootloader_flash_response_rx();
  if (bVar2 == 0x1a) {
    bVar2 = bootloader_flash_response_rx();
    if (bVar2 == 0xff) {
      uVar1 = 0;
    }
    else {
      bVar3 = bootloader_flash_response_rx();
      if (bVar3 == 0xff) {
        uVar1 = 0;
      }
      else {
        *param_1 = (short)(char)bVar2 << 8 | (short)(char)bVar3;
        uVar1 = 1;
      }
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



undefined8 bootloader_hc08_write_next_byte(byte param_1)

{
  byte bVar2;
  undefined8 uVar1;
  
  bootloader_hc08_bkgd_pre_delay();
  bootloader_flash_write_byte(0x19);
  bVar2 = bootloader_flash_response_rx();
  if (bVar2 == 0x19) {
    bootloader_flash_write_byte(param_1);
    bVar2 = bootloader_flash_response_rx();
    if ((uint)param_1 == (int)(char)bVar2) {
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



undefined8 bootloader_hc08_read_pc(ushort *param_1)

{
  byte bVar2;
  byte bVar3;
  undefined8 uVar1;
  byte bVar4;
  
  bootloader_hc08_bkgd_pre_delay();
  bootloader_flash_write_byte(0xc);
  bVar2 = bootloader_flash_response_rx();
  bVar3 = bootloader_flash_response_rx();
  if (bVar3 == 0xff) {
    uVar1 = 0;
  }
  else {
    bVar4 = bootloader_flash_response_rx();
    if (bVar4 == 0xff) {
      uVar1 = 0;
    }
    else if (bVar2 == 0xc) {
      *param_1 = (short)(char)bVar4;
      *param_1 = *param_1 | (short)(char)bVar3 << 8;
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}



bool bootloader_hc08_poll_ack(void)

{
  byte bVar1;
  
  bootloader_hc08_bkgd_pre_delay();
  bootloader_flash_write_byte(0x28);
  bVar1 = bootloader_flash_response_rx();
  return bVar1 == 0x28;
}



undefined8 bootloader_hc08_verify_identity_bytes(void)

{
  undefined8 uVar1;
  undefined8 uVar2;
  ushort uVar3;
  byte local_20 [32];
  
  uVar1 = 0x40009870;
  uVar3 = 0xfff6;
  while( true ) {
    if (0xfffd < uVar3) {
      return 1;
    }
    uVar2 = bootloader_hc08_mon08_read_byte((uint)uVar3,local_20);
    if ((int)uVar2 == 0) break;
    if (HC08CODE_base.programming_magic_word == 0xaaaaaaaa) {
      if (local_20[0] != (&UNK_fffe800a)[(uint)uVar3 + (int)uVar1]) {
        return 0;
      }
    }
    else if ((HC08CODE_base.programming_magic_word == 0x88888888) && (local_20[0] != 0xff)) {
      return 0;
    }
    uVar3 = uVar3 + 1;
  }
  return 0;
}



undefined8 bootloader_hc08_mon08_read_block(ushort param_1,int param_2,byte param_3)

{
  undefined8 uVar1;
  int iVar2;
  ushort local_58 [2];
  byte abStack_54 [84];
  
  if ((param_3 < 0x41) && (1 < param_3)) {
    uVar1 = bootloader_hc08_mon08_read_byte((uint)param_1,abStack_54);
    if ((int)uVar1 == 0) {
      uVar1 = 0;
    }
    else {
      for (iVar2 = 1; iVar2 < (int)(uint)param_3; iVar2 = iVar2 + 2) {
        uVar1 = bootloader_hc08_flash_response_rx_word(local_58);
        if ((int)uVar1 == 0) {
          return 0;
        }
        abStack_54[iVar2] = (byte)(local_58[0] >> 8);
        abStack_54[iVar2 + 1] = (byte)local_58[0];
      }
      uVar1 = bootloader_libc_memcmp((int)abStack_54,param_2,(uint)param_3);
      if ((int)uVar1 == 0) {
        uVar1 = 1;
      }
      else {
        uVar1 = 0;
      }
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



undefined8 bootloader_hc08_flash_program_block(undefined4 param_1,int param_2,byte param_3)

{
  undefined8 uVar1;
  bool bVar2;
  int iVar3;
  ushort local_130 [4];
  undefined1 local_127;
  byte local_126;
  byte local_125;
  byte local_124;
  byte local_123;
  undefined1 local_118;
  byte local_117;
  byte local_116;
  byte local_115;
  
  if (param_3 < 0x41) {
    uVar1 = bootloader_hc08_mon08_write_byte(0x100,0x45);
    if ((int)uVar1 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = bootloader_hc08_write_next_byte(1);
      if ((int)uVar1 == 0) {
        uVar1 = 0;
      }
      else {
        uVar1 = bootloader_hc08_write_next_byte(0x10);
        if ((int)uVar1 == 0) {
          uVar1 = 0;
        }
        else {
          uVar1 = bootloader_hc08_write_next_byte(0xcc);
          if ((int)uVar1 == 0) {
            uVar1 = 0;
          }
          else {
            uVar1 = bootloader_hc08_write_next_byte(0xff);
            if ((int)uVar1 == 0) {
              uVar1 = 0;
            }
            else {
              uVar1 = bootloader_hc08_write_next_byte(0x28);
              if ((int)uVar1 == 0) {
                uVar1 = 0;
              }
              else {
                local_118 = 0x20;
                local_116 = (byte)((uint)param_1 >> 8);
                local_115 = (byte)param_1;
                local_117 = param_3;
                uVar1 = bootloader_hc08_mon08_write_byte(0x110,0x20);
                if ((int)uVar1 == 0) {
                  uVar1 = 0;
                }
                else {
                  uVar1 = bootloader_hc08_write_next_byte(local_117);
                  if ((int)uVar1 == 0) {
                    uVar1 = 0;
                  }
                  else {
                    uVar1 = bootloader_hc08_write_next_byte(local_116);
                    if ((int)uVar1 == 0) {
                      uVar1 = 0;
                    }
                    else {
                      uVar1 = bootloader_hc08_write_next_byte(local_115);
                      if ((int)uVar1 == 0) {
                        uVar1 = 0;
                      }
                      else {
                        for (iVar3 = 0; iVar3 < (int)(uint)param_3; iVar3 = iVar3 + 1) {
                          uVar1 = bootloader_hc08_write_next_byte(*(byte *)(param_2 + iVar3));
                          if ((int)uVar1 == 0) {
                            return 0;
                          }
                        }
                        uVar1 = bootloader_hc08_read_pc(local_130);
                        if ((int)uVar1 == 0) {
                          uVar1 = 0;
                        }
                        else {
                          local_127 = 0x79;
                          local_126 = 0;
                          local_125 = 0;
                          local_124 = 1;
                          local_123 = 0;
                          uVar1 = bootloader_hc08_mon08_write_byte(local_130[0] + 1 & 0xffff,0x79);
                          if ((int)uVar1 == 0) {
                            uVar1 = 0;
                          }
                          else {
                            uVar1 = bootloader_hc08_write_next_byte(local_126);
                            if ((int)uVar1 == 0) {
                              uVar1 = 0;
                            }
                            else {
                              uVar1 = bootloader_hc08_write_next_byte(local_125);
                              if ((int)uVar1 == 0) {
                                uVar1 = 0;
                              }
                              else {
                                uVar1 = bootloader_hc08_write_next_byte(local_124);
                                if ((int)uVar1 == 0) {
                                  uVar1 = 0;
                                }
                                else {
                                  uVar1 = bootloader_hc08_write_next_byte(local_123);
                                  if ((int)uVar1 == 0) {
                                    uVar1 = 0;
                                  }
                                  else {
                                    bVar2 = bootloader_hc08_poll_ack();
                                    if (bVar2) {
                                      bootloader_delay_cycles(20000);
                                      uVar1 = bootloader_hc08_mon08_read_block
                                                        ((ushort)param_1,param_2,param_3);
                                      if ((int)uVar1 == 0) {
                                        uVar1 = 0;
                                      }
                                      else {
                                        uVar1 = 1;
                                      }
                                    }
                                    else {
                                      uVar1 = 0;
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



undefined8 bootloader_hc08_flash_erase(void)

{
  undefined8 uVar1;
  bool bVar2;
  ushort local_120 [4];
  undefined1 local_117;
  byte local_116;
  byte local_115;
  byte local_114;
  byte local_113;
  undefined1 local_108;
  byte local_107;
  byte local_106;
  byte local_105;
  
  uVar1 = bootloader_hc08_mon08_write_byte(0x100,0x45);
  if ((int)uVar1 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = bootloader_hc08_mon08_write_byte(0x101,1);
    if ((int)uVar1 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = bootloader_hc08_mon08_write_byte(0x102,0x10);
      if ((int)uVar1 == 0) {
        uVar1 = 0;
      }
      else {
        uVar1 = bootloader_hc08_mon08_write_byte(0x103,0xcc);
        if ((int)uVar1 == 0) {
          uVar1 = 0;
        }
        else {
          uVar1 = bootloader_hc08_mon08_write_byte(0x104,0xff);
          if ((int)uVar1 == 0) {
            uVar1 = 0;
          }
          else {
            uVar1 = bootloader_hc08_mon08_write_byte(0x105,0x2c);
            if ((int)uVar1 == 0) {
              uVar1 = 0;
            }
            else {
              local_108 = 0x20;
              local_107 = 0;
              local_106 = 0xff;
              local_105 = 0xff;
              uVar1 = bootloader_hc08_mon08_write_byte(0x110,0x20);
              if ((int)uVar1 == 0) {
                uVar1 = 0;
              }
              else {
                uVar1 = bootloader_hc08_mon08_write_byte(0x111,local_107);
                if ((int)uVar1 == 0) {
                  uVar1 = 0;
                }
                else {
                  uVar1 = bootloader_hc08_mon08_write_byte(0x112,local_106);
                  if ((int)uVar1 == 0) {
                    uVar1 = 0;
                  }
                  else {
                    uVar1 = bootloader_hc08_mon08_write_byte(0x113,local_105);
                    if ((int)uVar1 == 0) {
                      uVar1 = 0;
                    }
                    else {
                      uVar1 = bootloader_hc08_read_pc(local_120);
                      if ((int)uVar1 == 0) {
                        uVar1 = 0;
                      }
                      else {
                        local_117 = 0x79;
                        local_116 = 0;
                        local_115 = 0;
                        local_114 = 1;
                        local_113 = 0;
                        uVar1 = bootloader_hc08_mon08_write_byte(local_120[0] + 1 & 0xffff,0x79);
                        if ((int)uVar1 == 0) {
                          uVar1 = 0;
                        }
                        else {
                          uVar1 = bootloader_hc08_mon08_write_byte
                                            (local_120[0] + 2 & 0xffff,local_116);
                          if ((int)uVar1 == 0) {
                            uVar1 = 0;
                          }
                          else {
                            uVar1 = bootloader_hc08_mon08_write_byte
                                              (local_120[0] + 3 & 0xffff,local_115);
                            if ((int)uVar1 == 0) {
                              uVar1 = 0;
                            }
                            else {
                              uVar1 = bootloader_hc08_mon08_write_byte
                                                (local_120[0] + 4 & 0xffff,local_114);
                              if ((int)uVar1 == 0) {
                                uVar1 = 0;
                              }
                              else {
                                uVar1 = bootloader_hc08_mon08_write_byte
                                                  (local_120[0] + 5 & 0xffff,local_113);
                                if ((int)uVar1 == 0) {
                                  uVar1 = 0;
                                }
                                else {
                                  bVar2 = bootloader_hc08_poll_ack();
                                  if (bVar2) {
                                    uVar1 = 1;
                                  }
                                  else {
                                    uVar1 = 0;
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return uVar1;
}



undefined1 bootloader_hc08_erase_and_verify_retry(void)

{
  undefined1 unaff_r30;
  int iVar1;
  
  iVar1 = 0;
  while ((iVar1 < 3 && (unaff_r30 = hc08_flash_and_verify(), !(bool)unaff_r30))) {
    bootloader_delay_cycles(50000);
    iVar1 = iVar1 + 1;
  }
  return unaff_r30;
}



undefined8 bootloader_hc08_write_block_retry(ushort param_1,int param_2,byte param_3)

{
  undefined8 unaff_r30;
  int iVar1;
  
  iVar1 = 0;
  while ((iVar1 < 3 &&
         (unaff_r30 = bootloader_hc08_flash_program_block((uint)param_1,param_2,param_3),
         (int)unaff_r30 == 0))) {
    bootloader_delay_cycles(50000);
    iVar1 = iVar1 + 1;
  }
  return unaff_r30;
}



undefined8 bootloader_hc08_mass_erase_retry(void)

{
  undefined8 unaff_r30;
  int iVar1;
  
  iVar1 = 0;
  while ((iVar1 < 3 && (unaff_r30 = bootloader_hc08_flash_erase(), (int)unaff_r30 == 0))) {
    bootloader_delay_cycles(50000);
    iVar1 = iVar1 + 1;
  }
  return unaff_r30;
}



undefined8 bootloader_hc08_firmware_program(void)

{
  char cVar2;
  undefined8 uVar1;
  int i;
  int iVar3;
  undefined **ppuVar4;
  
  bootloader_set_spr150_4000();
  bootloader_hc08_serial_boot_init();
  bootloader_set_spr150_4000();
  bootloader_tx_hc08_prog_start(5000);
  bootloader_delay_cycles(10176);
  bootloader_hc08_data_pin_high();
  bootloader_delay_cycles(10176);
  cVar2 = bootloader_hc08_erase_and_verify_retry();
  if (cVar2 == '\0') {
    for (i = 0; i < 10000; i = i + 1) {
    }
    bootloader_tx_hc08_error(0x90);
    do {
      bootloader_set_spr150_4000();
    } while( true );
  }
  if (HC08CODE_base.programming_magic_word == 0xbbbbbbbb) {
    uVar1 = bootloader_hc08_mass_erase_retry();
    if ((int)uVar1 != 0) {
      bootloader_tx_hc08_erase_start(0);
      for (iVar3 = 0; iVar3 < 10000; iVar3 = iVar3 + 1) {
      }
      bootloader_tx_hc08_prog_done((undefined *)0x0);
      do {
        bootloader_set_spr150_4000();
      } while( true );
    }
    bootloader_tx_hc08_error(0x91);
    do {
      bootloader_set_spr150_4000();
    } while( true );
  }
  uVar1 = bootloader_hc08_verify_identity_bytes();
  if ((int)uVar1 == 0) {
    uVar1 = bootloader_hc08_mass_erase_retry();
    if ((int)uVar1 != 0) {
      bootloader_tx_hc08_erase_start(30000);
      bootloader_hc08_set_reprogram_flag();
      for (iVar3 = 0; iVar3 < 10000; iVar3 = iVar3 + 1) {
      }
      bootloader_tx_hc08_prog_done((undefined *)&PTR_00000bb8);
      do {
        bootloader_set_spr150_4000();
      } while( true );
    }
    bootloader_tx_hc08_error(0x91);
    do {
      bootloader_set_spr150_4000();
    } while( true );
  }
  uVar1 = bootloader_hc08_mass_erase_retry();
  if ((int)uVar1 == 0) {
    bootloader_tx_hc08_error(0x91);
    do {
      bootloader_set_spr150_4000();
    } while( true );
  }
  bootloader_tx_hc08_erase_start(30000);
  for (ppuVar4 = &PTR_0000dc00; (int)ppuVar4 < 0xfc00; ppuVar4 = ppuVar4 + 0x10) {
    bootloader_set_spr150_4000();
    uVar1 = bootloader_hc08_write_block_retry
                      ((ushort)ppuVar4,(int)(&UNK_ffff2400 + (int)ppuVar4 + DAT_40001864),64);
    if ((int)uVar1 == 0) {
      bootloader_set_spr150_4000();
      bootloader_tx_hc08_error(146);
      do {
        bootloader_set_spr150_4000();
      } while( true );
    }
  }
  bootloader_set_spr150_4000();
  uVar1 = bootloader_hc08_write_block_retry(0xffdc,DAT_40001864 + 0x23dc,0x24);
  if ((int)uVar1 == 0) {
    bootloader_set_spr150_4000();
    bootloader_tx_hc08_error(0x92);
    do {
      bootloader_set_spr150_4000();
    } while( true );
  }
  bootloader_hc08_prog_finalize();
  bootloader_tx_hc08_prog_done((undefined *)0x0);
  return 1;
}



void bootloader_noop3(void)

{
  return;
}



void bootloader_timer_latch(ushort param_1)

{
  undefined8 uVar1;
  
  uVar1 = bootload_timebase_read();
  *(int *)(&DAT_40001868 + (uint)param_1 * 4) = (int)uVar1;
  return;
}



longlong bootloader_timer_elapsed(ushort param_1)

{
  longlong lVar1;
  
  lVar1 = bootload_timebase_read();
  return lVar1 - (ulonglong)*(uint *)(&DAT_40001868 + (uint)param_1 * 4);
}



undefined8 bootload_timebase_read(void)

{
  undefined8 uVar1;
  
  uVar1 = TBLr;
  return uVar1;
}



void bootloader_delay_cycles(uint16_t size_unknown)

{
  ulonglong uVar1;
  
  bootloader_timer_latch(1);
  do {
    uVar1 = bootloader_timer_elapsed(1);
  } while ((uVar1 & 0xffffffff) <= (ulonglong)(uint)((short)size_unknown * 0x50));
  return;
}



void bootloader_siu_pcr_write(uint param_1,uint16_t param_2)

{
  siu_pcr[param_1 & 0xffff] = param_2;
  return;
}



void bootloader_init_default_interrupt_frames
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  undefined4 in_r0;
  undefined4 *puVar1;
  undefined4 unaff_r14;
  undefined4 unaff_r15;
  undefined4 unaff_r16;
  undefined4 unaff_r17;
  undefined4 unaff_r18;
  undefined4 unaff_r19;
  undefined4 unaff_r20;
  undefined4 unaff_r21;
  undefined4 unaff_r22;
  undefined4 unaff_r23;
  undefined4 unaff_r24;
  undefined4 unaff_r25;
  undefined4 unaff_r26;
  undefined4 unaff_r27;
  undefined4 unaff_r28;
  undefined4 unaff_r29;
  undefined4 unaff_r30;
  undefined4 unaff_r31;
  longlong lVar2;
  
  puVar1 = (undefined4 *)&DAT_40000000;
  lVar2 = 0x200;
  do {
    *puVar1 = in_r0;
    puVar1[1] = register0x0000000c;
    puVar1[2] = 0x40009870;
    puVar1[3] = param_1;
    puVar1[4] = param_2;
    puVar1[5] = param_3;
    puVar1[6] = param_4;
    puVar1[7] = param_5;
    puVar1[8] = param_6;
    puVar1[9] = param_7;
    puVar1[10] = param_8;
    puVar1[0xb] = puVar1;
    puVar1[0xc] = 0x200;
    puVar1[0xd] = 0x40009798;
    puVar1[0xe] = unaff_r14;
    puVar1[0xf] = unaff_r15;
    puVar1[0x10] = unaff_r16;
    puVar1[0x11] = unaff_r17;
    puVar1[0x12] = unaff_r18;
    puVar1[0x13] = unaff_r19;
    puVar1[0x14] = unaff_r20;
    puVar1[0x15] = unaff_r21;
    puVar1[0x16] = unaff_r22;
    puVar1[0x17] = unaff_r23;
    puVar1[0x18] = unaff_r24;
    puVar1[0x19] = unaff_r25;
    puVar1[0x1a] = unaff_r26;
    puVar1[0x1b] = unaff_r27;
    puVar1[0x1c] = unaff_r28;
    puVar1[0x1d] = unaff_r29;
    puVar1[0x1e] = unaff_r30;
    puVar1[0x1f] = unaff_r31;
    puVar1 = puVar1 + 0x20;
    lVar2 = lVar2 + -1;
  } while (lVar2 != 0);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 bootloader_flash_isr_install(undefined4 param_1,undefined4 param_2)

{
  if (_DAT_400024d0 == 0) {
    DAT_400024c8 = param_1;
    DAT_400024cc = param_2;
    _DAT_400024d0 = 1;
    return 0;
  }
  return 0xffffffffffffffff;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void bootloader_flash_isr_release(int param_1)

{
  if (param_1 != 0) {
    return;
  }
  DAT_400024c8 = 0;
  DAT_400024cc = 0;
  _DAT_400024d0 = 0;
  return;
}



// This gets called, but the results aren't used

longlong u64_div_int(uint32_t dividend_hi,uint32_t dividend_lo,uint32_t divisor_hi,
                    uint32_t divisor_lo)

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
  ulonglong uVar10;
  ulonglong uVar11;
  longlong lVar12;
  uint uVar14;
  ulonglong uVar13;
  bool bVar15;
  bool bVar16;
  
  uVar7 = (ulonglong)(int)divisor_lo;
  uVar6 = (ulonglong)(int)divisor_hi;
  lVar2 = LZCOUNT(dividend_hi);
  if (dividend_hi == 0) {
    lVar2 = LZCOUNT(dividend_lo) + 0x20;
  }
  lVar12 = LZCOUNT(divisor_hi);
  if (divisor_hi == 0) {
    lVar12 = LZCOUNT(divisor_lo) + 0x20;
  }
  if ((uint)lVar2 <= (uint)lVar12) {
    lVar12 = 0x40 - (lVar12 + 1);
    uVar3 = (uint)lVar2 + (int)lVar12;
    lVar12 = (0x40 - lVar2) - lVar12;
    uVar14 = (uint)lVar12;
    if ((int)uVar14 < 0x20) {
      uVar1 = dividend_lo >> (uVar14 & 0x3f) | dividend_hi << (0x20 - uVar14 & 0x3f);
      uVar8 = (ulonglong)(dividend_hi >> (uVar14 & 0x3f));
    }
    else {
      uVar1 = dividend_hi >> (uVar14 - 0x20 & 0x3f);
      uVar8 = 0;
    }
    uVar10 = (ulonglong)uVar1;
    if ((int)uVar3 < 0x20) {
      uVar14 = dividend_hi << (uVar3 & 0x3f) | dividend_lo >> (0x20 - uVar3 & 0x3f);
      uVar5 = (ulonglong)(dividend_lo << (uVar3 & 0x3f));
    }
    else {
      uVar14 = dividend_lo << (uVar3 - 0x20 & 0x3f);
      uVar5 = 0;
    }
    uVar4 = (ulonglong)uVar14;
    bVar15 = false;
    do {
      bVar16 = CARRY8(uVar5,(ulonglong)bVar15) || CARRY8(uVar5,uVar5 + bVar15);
      uVar5 = uVar5 * 2 + (ulonglong)bVar15;
      uVar9 = (ulonglong)bVar16;
      bVar15 = CARRY8(uVar4,uVar9) || CARRY8(uVar4,uVar4 + uVar9);
      uVar4 = uVar4 * 2 + (ulonglong)bVar16;
      uVar9 = (ulonglong)bVar15;
      uVar11 = uVar10 * 2 + (ulonglong)bVar15;
      uVar9 = uVar8 * 2 + (ulonglong)(CARRY8(uVar10,uVar9) || CARRY8(uVar10,uVar10 + uVar9));
      uVar13 = uVar9 - (uVar6 + (uVar11 < uVar7));
      uVar8 = uVar9;
      uVar10 = uVar11;
      if (-1 < (longlong)uVar13) {
        uVar8 = uVar13;
        uVar10 = uVar11 - uVar7;
      }
      bVar15 = -1 < (longlong)uVar13 ||
               uVar6 <= uVar9 && (ulonglong)(uVar11 < uVar7) <= uVar9 - uVar6;
      lVar12 = lVar12 + -1;
    } while (lVar12 != 0);
    return uVar4 * 2 + (ulonglong)(CARRY8(uVar5,(ulonglong)bVar15) || CARRY8(uVar5,uVar5 + bVar15));
  }
  return 0;
}



void bootloader_flash_isr_register(void)

{
  undefined8 uVar1;
  undefined4 local_8;
  undefined4 local_4;
  
  if (PTR_DAT_400017b8 == &DAT_fffffffe) {
    bootloader_flash_c55fmc_get_context(&local_8,&local_4);
    uVar1 = bootloader_flash_isr_install(local_8,local_4);
    PTR_DAT_400017b8 = (undefined *)uVar1;
  }
  return;
}



void bootloader_flash_isr_deregister(void)

{
  if (PTR_DAT_400017b8 != &DAT_fffffffe) {
    bootloader_flash_isr_release((int)PTR_DAT_400017b8);
    PTR_DAT_400017b8 = &DAT_fffffffe;
  }
  return;
}



undefined8 bootloader_libc_memcmp(int a,int b,uint32_t size)

{
  longlong lVar1;
  byte *pbVar2;
  byte *pbVar3;
  
  pbVar3 = (byte *)(b + -1);
  pbVar2 = (byte *)(a + -1);
  lVar1 = (longlong)(int)size + 1;
  do {
    lVar1 = lVar1 + -1;
    if (lVar1 == 0) {
      return 0;
    }
    pbVar2 = pbVar2 + 1;
    pbVar3 = pbVar3 + 1;
  } while (*pbVar2 == *pbVar3);
  if (*pbVar3 <= *pbVar2) {
    return 1;
  }
  return 0xffffffffffffffff;
}



longlong bootloader_strncmp(char *a,char *b,size_t len)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  longlong lVar4;
  
  pbVar2 = (byte *)(a + -1);
  pbVar3 = (byte *)(b + -1);
  lVar4 = (longlong)(int)len + 1;
  while( true ) {
    lVar4 = lVar4 + -1;
    if (lVar4 == 0) {
      return 0;
    }
    pbVar2 = pbVar2 + 1;
    bVar1 = *pbVar2;
    pbVar3 = pbVar3 + 1;
    if ((ulonglong)bVar1 != (ulonglong)*pbVar3) break;
    if (bVar1 == 0) {
      return 0;
    }
  }
  return (ulonglong)bVar1 - (ulonglong)*pbVar3;
}



// WARNING: Control flow encountered bad instruction data

undefined8
FUN_00007690(int param_1,int *param_2,uint param_3,undefined4 *param_4,int *param_5,
            undefined *param_6)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  int *piVar5;
  uint uVar6;
  undefined8 uVar7;
  
  uVar7 = 0;
  if ((((uint)param_2 | param_3) & 7) == 0) {
    piVar5 = (int *)((int)*(int **)(param_1 + 0xc) + *(uint *)(param_1 + 0x10));
    piVar3 = (int *)((int)*(int **)(param_1 + 4) + *(uint *)(param_1 + 8));
    if (((((param_2 < *(int **)(param_1 + 0xc)) || (piVar5 <= param_2)) ||
         (*(uint *)(param_1 + 0x10) < param_3)) || (piVar5 < (int *)((int)param_2 + param_3))) &&
       (((param_2 < *(int **)(param_1 + 4) || (piVar3 <= param_2)) ||
        ((*(uint *)(param_1 + 8) < param_3 || (piVar3 < (int *)((int)param_2 + param_3))))))) {
      uVar7 = 0x200;
    }
    else {
      uVar4 = 0;
      uVar6 = 0;
      if (param_3 >> 3 != 0) {
        do {
          iVar1 = *param_2;
          iVar2 = param_2[1];
          if (iVar1 != -1 || iVar2 != -1) {
            uVar7 = 0x600;
            *param_4 = param_2;
            *param_5 = iVar1;
            param_5[1] = iVar2;
            break;
          }
          param_2 = param_2 + 2;
          if ((param_6 != &DAT_ffffffff) && (uVar6 == uVar4)) {
            (*(code *)param_6)();
            uVar4 = uVar4 + 0x5a;
          }
          uVar6 = uVar6 + 1;
        } while (uVar6 < param_3 >> 3);
      }
    }
  }
  else {
    uVar7 = 0x100;
  }
  if (*(int *)(param_1 + 0x24) != 0) {
                    // WARNING: Bad instruction - Truncating control flow here
    halt_baddata();
  }
  return uVar7;
}



// WARNING: Control flow encountered bad instruction data

ulonglong FUN_000077e0(undefined4 *param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  ulonglong uVar5;
  
  uVar1 = *(uint *)*param_1;
  if ((uVar1 & 0x40) != 0) {
    uVar5 = 0x20;
    goto LAB_0000794c;
  }
  uVar2 = DAT_c3f90004;
  if (((uVar2 >> 0x10 == 0x5554) && ((uVar2 & 0xffff) < 4)) &&
     (((uVar2 & 0xffff) != 3 ||
      ((*(int *)(param_1[3] + 200) != 0x4c4a4f4e && (*(int *)(param_1[3] + 0xe8) != 0x4c4a4f4e))))))
  {
    uVar5 = 0x10;
    goto LAB_0000794c;
  }
  if (uVar2 == 0x55340000) {
    uVar5 = 0x10;
    goto LAB_0000794c;
  }
  param_1[6] = 0;
  param_1[7] = 0;
  uVar2 = uVar1 >> 0x14 & 7;
  uVar5 = (ulonglong)(uVar1 >> 0xe) & 3 | (~(ulonglong)uVar1 << 0x20) >> 0x2a & 0xc;
  if (uVar2 < 4) {
    iVar3 = 2 << uVar2;
LAB_000078d4:
    param_1[5] = iVar3;
  }
  else {
    if (uVar2 == 4) {
      iVar3 = 10;
      goto LAB_000078d4;
    }
    if (uVar2 == 5) {
      iVar3 = 0xc;
      goto LAB_000078d4;
    }
    if (uVar2 == 6) {
      iVar3 = 6;
      goto LAB_000078d4;
    }
  }
  if ((uVar1 & 0x10000000) == 0) {
    uVar2 = uVar1 >> 6 & 0x3c0000;
    uVar4 = uVar2 + 0x40000;
    param_1[2] = uVar4;
    if (0x40000 < uVar4) {
      param_1[6] = (uVar1 >> 0xf & 2) + 2;
    }
    if (0x80000 < uVar4) {
      param_1[7] = uVar2 - 0x40000 >> 0x11;
    }
  }
  else if ((uVar1 & 0xf000000) == 0) {
    param_1[2] = 0x20000;
    param_1[5] = 4;
  }
  else {
    param_1[2] = 0x50000;
    param_1[6] = 4;
  }
LAB_0000794c:
  if (param_1[9] != 0) {
                    // WARNING: Bad instruction - Truncating control flow here
    halt_baddata();
  }
  return uVar5;
}



// WARNING: Control flow encountered bad instruction data

undefined8 FUN_00007978(int *param_1,int param_2,undefined1 *param_3,uint *param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined8 uVar5;
  
  uVar5 = 0;
  *param_3 = 0;
  if (6 < param_2) {
    uVar5 = 0x800;
    goto LAB_00007a2c;
  }
  iVar2 = 4;
  uVar4 = 0x100000;
  iVar3 = 0x14;
  if (param_2 == 2) {
LAB_000079b0:
    uVar4 = 0;
LAB_00007a00:
    uVar4 = uVar4 | 0xffff;
    iVar3 = 0;
  }
  else if (param_2 == 4) {
LAB_000079c0:
    uVar4 = 0xf0000;
    iVar3 = 0x10;
  }
  else if (param_2 != 0) {
    iVar2 = 0xc;
    if (param_2 == 3) goto LAB_000079b0;
    if (param_2 == 5) goto LAB_000079c0;
    if (param_2 != 6) goto LAB_00007a08;
    iVar2 = 8;
    uVar4 = 0xfff0000;
    goto LAB_00007a00;
  }
LAB_00007a08:
  uVar1 = *(uint *)(iVar2 + *param_1);
  if ((uVar1 & 0x80000000) != 0) {
    *param_3 = 1;
  }
  *param_4 = (uVar1 & uVar4) >> iVar3;
LAB_00007a2c:
  if (param_1[9] == 0) {
    return uVar5;
  }
                    // WARNING: Bad instruction - Truncating control flow here
  halt_baddata();
}



// WARNING: Control flow encountered bad instruction data

undefined8
FUN_00007a58(int param_1,ulonglong param_2,ulonglong param_3,int *param_4,undefined4 *param_5,
            int *param_6,int *param_7,undefined *param_8)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  undefined8 uVar6;
  int *piVar7;
  
  uVar6 = 0;
  if ((((param_2 | param_3) & 7) == 0) && (((uint)param_4 & 3) == 0)) {
    uVar4 = (ulonglong)*(uint *)(param_1 + 0xc) + (ulonglong)*(uint *)(param_1 + 0x10);
    uVar3 = *(uint *)(param_1 + 4) + *(uint *)(param_1 + 8);
    if ((((((param_2 & 0xffffffff) < (ulonglong)*(uint *)(param_1 + 0xc)) ||
          ((uVar4 & 0xffffffff) <= (param_2 & 0xffffffff))) ||
         ((ulonglong)*(uint *)(param_1 + 0x10) < (param_3 & 0xffffffff))) ||
        ((uVar4 & 0xffffffff) < (param_2 + param_3 & 0xffffffff))) &&
       ((((param_2 & 0xffffffff) < (ulonglong)*(uint *)(param_1 + 4) ||
         ((ulonglong)uVar3 <= (param_2 & 0xffffffff))) ||
        (((ulonglong)*(uint *)(param_1 + 8) < (param_3 & 0xffffffff) ||
         ((ulonglong)uVar3 < (param_2 + param_3 & 0xffffffff))))))) {
      uVar6 = 0x200;
    }
    else {
      uVar4 = 0;
      uVar5 = 0;
      if ((param_3 << 0x20) >> 0x23 != 0) {
        do {
          piVar7 = (int *)param_2;
          iVar1 = *piVar7;
          iVar2 = piVar7[1];
          if (*param_4 != iVar1 || param_4[1] != iVar2) {
            *param_5 = piVar7;
            *param_6 = iVar1;
            param_6[1] = iVar2;
            iVar1 = param_4[1];
            uVar6 = 0x700;
            *param_7 = *param_4;
            param_7[1] = iVar1;
            break;
          }
          param_2 = param_2 + 8;
          param_4 = param_4 + 2;
          if ((param_8 != &DAT_ffffffff) && ((uVar5 & 0xffffffff) == (uVar4 & 0xffffffff))) {
            (*(code *)param_8)();
            uVar4 = uVar4 + 0x50;
          }
          uVar5 = uVar5 + 1;
        } while ((uVar5 & 0xffffffff) < (param_3 << 0x20) >> 0x23);
      }
    }
  }
  else {
    uVar6 = 0x100;
  }
  if (*(int *)(param_1 + 0x24) != 0) {
                    // WARNING: Bad instruction - Truncating control flow here
    halt_baddata();
  }
  return uVar6;
}



// WARNING: Control flow encountered bad instruction data

undefined8 FUN_00007bc8(int *param_1,int param_2,int param_3,uint param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint *puVar4;
  undefined8 uVar5;
  
  if (6 < param_2) {
    uVar5 = 0x800;
    goto LAB_00007c9c;
  }
  iVar3 = 4;
  uVar5 = 0;
  uVar2 = 0x100000;
  iVar1 = 0x14;
  if (param_2 == 2) {
LAB_00007bf8:
    uVar2 = 0;
LAB_00007c48:
    uVar2 = uVar2 | 0xffff;
    iVar1 = 0;
  }
  else if (param_2 == 4) {
LAB_00007c08:
    uVar2 = 0xf0000;
    iVar1 = 0x10;
  }
  else if (param_2 != 0) {
    iVar3 = 0xc;
    if (param_2 == 3) goto LAB_00007bf8;
    if (param_2 == 5) goto LAB_00007c08;
    if (param_2 != 6) goto LAB_00007c50;
    iVar3 = 8;
    uVar2 = 0xfff0000;
    goto LAB_00007c48;
  }
LAB_00007c50:
  puVar4 = (uint *)(iVar3 + *param_1);
  if (((*puVar4 & 0x80000000) == 0) && (*puVar4 = param_4, (*puVar4 & 0x80000000) == 0)) {
    uVar5 = 0xb00;
  }
  else {
    *puVar4 = *puVar4 & ~uVar2;
    *puVar4 = *puVar4 | uVar2 & param_3 << iVar1;
  }
LAB_00007c9c:
  if (param_1[9] == 0) {
    return uVar5;
  }
                    // WARNING: Bad instruction - Truncating control flow here
  halt_baddata();
}



// WARNING: Control flow encountered bad instruction data

undefined8
FUN_00008510(int *param_1,int param_2,uint param_3,uint param_4,uint param_5,undefined *param_6)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined8 uVar5;
  
  uVar2 = DAT_c3f90004;
  if (((uVar2 >> 0x10 == 0x5554) && ((uVar2 & 0xffff) < 4)) &&
     (((uVar2 & 0xffff) != 3 ||
      ((*(int *)(param_1[3] + 200) != 0x4c4a4f4e && (*(int *)(param_1[3] + 0xe8) != 0x4c4a4f4e))))))
  {
    uVar5 = 0x10;
  }
  else if (uVar2 == 0x55340000) {
    uVar5 = 0x10;
  }
  else {
    puVar1 = (uint *)*param_1;
    if ((*puVar1 & 0x14) == 0) {
      puVar4 = (undefined4 *)(param_1[3] + 0xe0);
      uVar5 = 0;
      if (param_2 == 0) {
        uVar2 = param_3 & 0xffffffffU >> (0x20U - param_1[5] & 0x3f) |
                (param_4 & 0xffffffffU >> (0x20U - param_1[6] & 0x3f)) << 0x10;
        uVar3 = param_5 & 0xffffffffU >> (0x20U - param_1[7] & 0x3f);
        puVar4 = (undefined4 *)param_1[1];
        if (uVar2 == 0 && uVar3 == 0) goto LAB_000086c8;
        puVar1[4] = uVar2;
        puVar1[5] = uVar3;
      }
      *puVar1 = *puVar1 & 0xffff3fff | 4;
      *puVar4 = 0xffffffff;
      *puVar1 = *puVar1 & 0xffff3fff | 1;
      while ((*puVar1 & 0x400) == 0) {
        if (param_6 != &DAT_ffffffff) {
          (*(code *)param_6)();
        }
      }
      *puVar1 = *puVar1 & 0xffff3ffe;
      if ((*puVar1 & 0x200) == 0) {
        uVar5 = 0x500;
      }
      uVar2 = puVar1[7];
      puVar1[7] = puVar1[7] & 0xfffffffe;
      *puVar1 = *puVar1 & 0xffff3ffb;
      puVar1[7] = puVar1[7] | 1;
      puVar1[7] = uVar2;
    }
    else {
      uVar5 = 0x300;
    }
  }
LAB_000086c8:
  if (param_1[9] != 0) {
                    // WARNING: Bad instruction - Truncating control flow here
    halt_baddata();
  }
  return uVar5;
}


