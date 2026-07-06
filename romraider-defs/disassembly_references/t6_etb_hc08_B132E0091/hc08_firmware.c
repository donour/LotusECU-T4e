#define 0x1A 0x1a
#define 0 0x0
#define 0x12 0x12
#define 0x22 0x22
#define 16 0x10

typedef unsigned char   undefined;

typedef unsigned char    byte;
typedef unsigned int    dword;
typedef unsigned char    uchar;
typedef unsigned int    uint;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned short    ushort;
typedef enum throttle_status_level_t {
    TSL_INIT=0,
    TSL_HANDSHAKE_1=1,
    TSL_HANDSHAKE_2=2,
    TSL_HANDSHAKE_3=3,
    TSL_MONITOR_4=4,
    TSL_MONITOR_5=5,
    TSL_MONITOR_6=6,
    TSL_REARM=7,
    TSL_RUN=8,
    TSL_FAULT=9,
    TSL_SHUTDOWN=10,
    TSL_MAX=11
} throttle_status_level_t;

typedef enum rx_cal_sel_bits {
    RXCAL_CH1_ALT=1,
    RXCAL_CH2_ALT=2,
    RXCAL_FORCE_SHUTDOWN=4,
    RXCAL_DISABLE_CH9=16
} rx_cal_sel_bits;

typedef enum hc08_msg_type_t {
    MSG_CRC=128,
    MSG_STATUS=129
} hc08_msg_type_t;

typedef enum hc08_cmd_t {
    CMD_MODE_1=1,
    CMD_MODE_2=2,
    CMD_MODE_3=3,
    CMD_MONITOR_4=4,
    CMD_MONITOR_5=5,
    CMD_MONITOR_6=6,
    CMD_REARM=7,
    CMD_RUN=8,
    CMD_FORCE_FAULT=9
} hc08_cmd_t;

typedef enum status_flag_bits {
    SF_CH1_CAL_SEL=1,
    SF_CH2_CAL_SEL=2,
    SF_DEBOUNCE_ACTIVE=4,
    SF_COMM_LOSS=8,
    SF_MODE=16,
    SF_TIMEOUT=32
} status_flag_bits;

typedef uint uint32_t;

typedef uchar uint8_t;

typedef ushort uint16_t;



undefined DAT_001d;
undefined DAT_001f;
undefined2 DAT_015e;
undefined DAT_0001;
undefined1 IO_PTD_0003;
undefined IO_ADSCR_003C;
undefined1 IO_ADR_003D;
undefined VECTOR_SWI;
undefined1 IO_TIM_SC_0020;
undefined IO_TIM_MODH_0023;
undefined IO_TIM_MODL_0024;
undefined1 IO_DDRD_0007;
undefined1 IO_TIM_CH_0028;
undefined1 math_acc_b0;
undefined1 math_acc_b1;
undefined1 math_acc_b2;
undefined1 math_acc_b3;
undefined1 adc_ch7;
undefined1 adc_ch2;
undefined1 adc_ch4;
undefined1 adc_ch6;
undefined1 adc_ch1;
undefined1 adc_ch3;
undefined1 adc_ch9;
undefined1 crc_hi;
undefined1 crc_lo;
throttle_status_level_t throttle_status_level;
undefined1 debounce_ch7;
undefined1 debounce_ch2;
undefined1 debounce_crosscheck;
undefined1 debounce_plaus6;
undefined1 debounce_plaus5;
undefined1 debounce_plaus4;
undefined1 debounce_handshake;
undefined1 timeout_cmd5_hi;
undefined1 log_wr_idx;
status_flag_bits status_flags;
undefined1 DAT_dc4a;
undefined1 timeout_cmd5_lo;
undefined1 log_rd_idx;
undefined1 DAT_00f6;
uint16_t timeout_cmd4;
undefined1 timeout_handshake_hi;
undefined1 timeout_handshake_lo;
undefined1 rx_mode2;
hc08_cmd_t rx_cmd_id;
rx_cal_sel_bits rx_cal_sel;
undefined1 rx_param2;
undefined1 armed_cmd6;
undefined1 armed_cmd5;
undefined1 armed_cmd4;
undefined1 armed_handshake;
undefined1 rx_mode;
undefined1 tgt_raw_hi;
undefined1 tgt_raw_lo;
undefined1 pos_calc_hi;
undefined1 pos_calc_lo;
undefined1 throttle_pos_ch1;
undefined1 math_acc_ext;
undefined1 throttle_pos_ch2;
byte[18] CAL_tps_mode_calibration_for_linearization;
undefined1 aux_data_8d;
undefined1 CAL_debounce_crosscheck_limit;
undefined1 CAL_crosscheck_offset;
undefined1 CAL_crosscheck_pos_scale;
undefined1 CAL_ch2_max;
undefined1 CAL_debounce_ch2_limit;
uint16_t CAL_handshake_timeout;
undefined1 CAL_handshake_pos_tol;
undefined1 CAL_debounce_handshake_limit;
undefined1 CAL_debounce_plaus4_limit;
uint16_t CAL_cmd4_timeout;
undefined1 CAL_plaus4_pos_tol;
undefined1 CAL_plaus4_pos_max;
undefined1 CAL_plaus5_pos_tol;
undefined1 CAL_debounce_plaus5_limit;
uint16_t CAL_cmd5_timeout;
undefined1 CAL_ch3_limit;
undefined1 CAL_ch3_polarity;
undefined1 CAL_ch9_limit;
undefined1 CAL_ch9_polarity;
undefined1 CAL_plaus6_pos_tol;
undefined1 CAL_debounce_plaus6_limit;
undefined1 CAL_ch7_shutdown_limit;
undefined1 CAL_debounce_ch7_limit;
char DAT_00f6;
undefined1 ctrl_due;
undefined1 comm_timer;
char DAT_0079;
undefined1 DAT_0079;
byte DAT_0082;
byte DAT_007c;
char DAT_0081;
byte DAT_007b;
byte DAT_007e;
byte DAT_007d;
undefined1 DAT_0029;
byte DAT_0078;
undefined1 DAT_002a;
undefined DAT_0013;
undefined1 IO_SCC2_0014;
undefined DAT_0019;
undefined1 rx_parser_state;
undefined1 rx_tmp;
undefined1 rx_ring_count;
undefined1 rx_ring_rd;
undefined1 rx_ring_wr;
undefined1 tx_buf_ptr;
undefined1 tx_idx;
undefined DAT_0016;
undefined1 DAT_0018;
hc08_msg_type_t rx_msg_type;
undefined1 tick_div;
undefined1 rx_cksum_acc;
undefined1 rx_len;
undefined1 UNK_00b5;
undefined1 UNK_00b6;
undefined1 UNK_00b7;
throttle_status_level_t UNK_00b6;
status_flag_bits UNK_00b7;
undefined1 UNK_00b8;
undefined1 UNK_00b9;
undefined1 UNK_00ba;
undefined1 UNK_00bb;
undefined1 UNK_00bc;
char UNK_00bd;
undefined1 UNK_00be;
byte UNK_00bf;
undefined1 UNK_00c0;
undefined1 UNK_00c1;
undefined1 UNK_00c2;
undefined1 UNK_00c3;
undefined1 rx_payload0;
undefined1 rx_payload1;
undefined1 rx_payload2;
undefined1 DAT_0030;
undefined DAT_0033;
undefined1 DAT_00f5;
undefined DAT_0034;
undefined1 DAT_00f4;
char DAT_00f5;
char DAT_00f4;

void startup_init(void)

{
  byte bVar1;
  
  bVar1 = DAT_001f;
  DAT_001f = bVar1 | 1;
  DAT_001d = 2;
  init_ports_timer_sci();
  sci_init();
  timer2_init();
  reset_monitor_state();
  return;
}



// WARNING: This function may have set the stack pointer

void reset_entry(void)

{
  DAT_015e = 0xdc6d;
  startup_init();
  enter_main_loop();
  return;
}



void adc_to_ports_loop(void)

{
  byte bVar1;
  
  do {
    do {
      bVar1 = IO_ADSCR_003C;
    } while ((bVar1 & 0x80) == 0);
    bVar1 = IO_ADR_003D;
    IO_PTD_0003 = bVar1;
    DAT_0001 = bVar1 >> 4 | bVar1 << 4;
  } while( true );
}



undefined1 default_isr(void)

{
  char cVar1;
  
  do {
    cVar1 = readIRQ();
  } while (cVar1 == '\0');
  (*(code *)&VECTOR_SWI)();
  return 0xdc;
}



byte init_ports_timer_sci(void)

{
  byte bVar1;
  
  bVar1 = IO_PTD_0003;
  IO_PTD_0003 = bVar1 | 8;
  bVar1 = IO_DDRD_0007;
  IO_DDRD_0007 = bVar1 | 8;
  bVar1 = IO_PTD_0003;
  IO_PTD_0003 = bVar1 & 0xef;
  bVar1 = IO_DDRD_0007;
  IO_DDRD_0007 = bVar1 | 0x10;
  IO_TIM_CH_0028 = 0x44;
  IO_TIM_SC_0020 = 0x32;
  IO_TIM_MODH_0023 = 0xff;
  IO_TIM_MODL_0024 = 0xff;
  bVar1 = IO_TIM_SC_0020;
  IO_TIM_SC_0020 = bVar1 | 0x10;
  bVar1 = IO_TIM_SC_0020;
  IO_TIM_SC_0020 = bVar1 & 0xdf;
  return bVar1 & 0xdf;
}



void enter_main_loop(void)

{
  main_loop();
  return;
}



uint8_t lookup_1d_interpolated
                  (uint8_t x_size,uint8_t x_val,uint8_t lut_hi,uint8_t lut_lo,uint8_t xaxis_hi,
                  uint8_t xaxis_lo)

{
  byte bVar1;
  uint8_t uVar2;
  short sVar3;
  byte bVar4;
  uint8_t *cur;
  undefined1 auStack_1d [4];
  undefined1 auStack_19 [4];
  undefined1 auStack_15 [3];
  uint8_t local_12;
  uint32_t index;
  undefined1 auStack_d [2];
  char cStack_b;
  byte bStack_a;
  undefined1 auStack_9 [4];
  undefined1 uStack_5;
  undefined1 uStack_4;
  undefined1 uStack_3;
  uint8_t uStack_2;
  
  uStack_3 = 0;
  uStack_4 = 0;
  uStack_5 = 0;
  uStack_2 = x_size;
  load_acc32_ptr(&uStack_5);
  sub32_acc();
  index._0_1_ = store_acc32(auStack_d);
  if (*(byte *)CONCAT11(xaxis_hi,xaxis_lo) < x_val) {
    cur = (uint8_t *)CONCAT11(cStack_b + xaxis_hi + CARRY1(bStack_a,xaxis_lo),bStack_a + xaxis_lo);
    index._1_1_ = index._0_1_;
    index._2_1_ = index._0_1_;
    index._3_1_ = index._0_1_;
    if (x_val < *cur) {
      while( true ) {
        cur = (uint8_t *)
              CONCAT11(index._2_1_ + xaxis_hi + CARRY1((byte)index,xaxis_lo),(byte)index + xaxis_lo)
        ;
        bVar1 = *cur;
        bVar4 = bVar1 - x_val;
        bVar4 = ((char)bVar4 < '\0') << 2 |
                (((bVar1 & ~x_val & ~bVar4 | ~bVar1 & x_val & bVar4) & 0x80) != 0) << 7;
        if (x_val <= bVar1) break;
        load_acc32_ptr(&index);
        cmp32(auStack_d);
        if ((byte)(bVar4 >> 2 & 1 ^ bVar4 >> 7) != 1) break;
        math_acc_b3 = '\x01';
        math_acc_b2 = 0;
        math_acc_b1 = 0;
        math_acc_b0 = 0;
        add32_to_buf(&index);
      }
      cur = (uint8_t *)
            CONCAT11(index._2_1_ + xaxis_hi + CARRY1((byte)index,xaxis_lo),(byte)index + xaxis_lo);
      if (*cur == x_val) {
        cur = (uint8_t *)
              CONCAT11(index._2_1_ + lut_hi + CARRY1((byte)index,lut_lo),(byte)index + lut_lo);
        return *cur;
      }
      cur = (uint8_t *)
            CONCAT11((index._2_1_ - ((byte)index == 0)) + xaxis_hi +
                     CARRY1((byte)index - 1,xaxis_lo),((byte)index - 1) + xaxis_lo);
      uVar2 = *cur;
      cur = (uint8_t *)
            CONCAT11(index._2_1_ + xaxis_hi + CARRY1((byte)index,xaxis_lo),(byte)index + xaxis_lo);
      if (*cur == uVar2) {
        cur = (uint8_t *)
              CONCAT11(index._2_1_ + lut_hi + CARRY1((byte)index,lut_lo),(byte)index + lut_lo);
        uVar2 = *cur;
      }
      else {
        cur = (uint8_t *)
              CONCAT11((index._2_1_ - ((byte)index == 0)) + lut_hi + CARRY1((byte)index - 1,lut_lo),
                       ((byte)index - 1) + lut_lo);
        local_12 = *cur;
        cur = (uint8_t *)
              CONCAT11(index._2_1_ + lut_hi + CARRY1((byte)index,lut_lo),(byte)index + lut_lo);
        load_acc16_signed(*cur - local_12);
        store_acc32(auStack_9);
        cur = (uint8_t *)
              CONCAT11((index._2_1_ - ((byte)index == 0)) + lut_hi + CARRY1((byte)index - 1,lut_lo),
                       ((byte)index - 1) + lut_lo);
        math_acc_b3 = *cur;
        math_acc_b0 = (char)math_acc_b3 >> 7;
        math_acc_b1 = math_acc_b0;
        math_acc_b2 = math_acc_b0;
        store_acc32(auStack_15);
        cur = (uint8_t *)
              CONCAT11((index._2_1_ - ((byte)index == 0)) + xaxis_hi +
                       CARRY1((byte)index - 1,xaxis_lo),((byte)index - 1) + xaxis_lo);
        math_acc_b3 = *cur;
        math_acc_b2 = 0;
        math_acc_b1 = 0;
        math_acc_b0 = 0;
        store_acc32(auStack_19);
        cur = (uint8_t *)
              CONCAT11(index._2_1_ + xaxis_hi + CARRY1((byte)index,xaxis_lo),(byte)index + xaxis_lo)
        ;
        math_acc_b3 = *cur;
        math_acc_b2 = 0;
        math_acc_b1 = 0;
        math_acc_b0 = 0;
        sub32_acc(auStack_19);
        store_acc32(auStack_19);
        cur = (uint8_t *)
              CONCAT11((index._2_1_ - ((byte)index == 0)) + xaxis_hi +
                       CARRY1((byte)index - 1,xaxis_lo),((byte)index - 1) + xaxis_lo);
        math_acc_b3 = *cur;
        math_acc_b2 = 0;
        math_acc_b1 = 0;
        math_acc_b0 = 0;
        sVar3 = store_acc32(auStack_1d);
        math_acc_b3 = *(uint8_t *)(sVar3 + 0x21);
        math_acc_b2 = 0;
        math_acc_b1 = 0;
        math_acc_b0 = 0;
        sVar3 = sub32_acc();
        mul32_buf(sVar3 + 0x14);
        div32_wrap(auStack_19);
        add32_acc(auStack_15);
        uVar2 = math_acc_b3;
      }
    }
    else {
      cur = (uint8_t *)CONCAT11(cStack_b + lut_hi + CARRY1(bStack_a,lut_lo),bStack_a + lut_lo);
      uVar2 = *cur;
    }
  }
  else {
    uVar2 = *(uint8_t *)CONCAT11(lut_hi,lut_lo);
  }
  return uVar2;
}



undefined1 adc_read_channel(uint8_t channel)

{
  undefined1 voltage;
  byte voltage_tmp;
  
  IO_ADSCR_003C = channel;
  do {
    voltage_tmp = IO_ADSCR_003C;
  } while ((voltage_tmp & 0x80) == 0);
  voltage = IO_ADR_003D;
  return voltage;
}



void adc_sample_all(void)

{
  adc_ch2 = adc_read_channel('\x02');
  adc_ch4 = adc_read_channel('\x04');
  adc_ch6 = adc_read_channel('\x06');
  adc_ch1 = adc_read_channel('\x01');
  adc_ch3 = adc_read_channel('\x03');
  adc_ch7 = adc_read_channel('\a');
  adc_ch9 = adc_read_channel('\t');
  return;
}



undefined2 sub16(byte param_1,char param_2,byte param_3)

{
  undefined1 auStack_2 [2];
  
  return CONCAT11((char)((ushort)auStack_2 >> 8),param_2 + -1 + CARRY1(~param_1,param_3));
}



void cal_table_checksum(void)

{
  byte bVar1;
  undefined1 extraout_X;
  undefined1 extraout_X_00;
  char cVar2;
  undefined1 uStack_3;
  undefined1 uStack_2;
  undefined1 local_1;
  
  crc_hi = 1;
  crc_lo = 0x23;
  local_1 = 0xdc;
  cVar2 = '\0';
  uStack_3 = 0;
  uStack_2 = '\0';
  do {
    bVar1 = local_1;
    cVar2 = cVar2 + '\x01';
    if (cVar2 == '\0') {
      local_1 = local_1 + 1;
    }
    crc_lo = sub16((ushort)bVar1 << 8,crc_hi,crc_lo);
    uStack_2 = uStack_2 + '\x01';
    if (uStack_2 == '\0') {
      uStack_3 = uStack_3 + 1;
    }
    crc_hi = extraout_X;
  } while (uStack_3 < 0x20);
  local_1 = 0xff;
  cVar2 = -0x24;
  uStack_3 = 0;
  uStack_2 = 0;
  do {
    bVar1 = local_1;
    cVar2 = cVar2 + '\x01';
    if (cVar2 == '\0') {
      local_1 = local_1 + 1;
    }
    crc_lo = sub16((ushort)bVar1 << 8,crc_hi,crc_lo);
    crc_hi = extraout_X_00;
    uStack_2 = uStack_2 + 1;
    if (uStack_2 == 0) {
      uStack_3 = uStack_3 + 1;
    }
  } while (uStack_3 < (uStack_2 < 0x24));
  return;
}



throttle_status_level_t release_fault_output(void)

{
  throttle_status_level_t tVar1;
  
  tVar1 = throttle_status_level;
  if (throttle_status_level < TSL_FAULT) {
    tVar1 = IO_PTD_0003;
    tVar1 = tVar1 & 0xef;
    IO_PTD_0003 = tVar1;
  }
  return tVar1;
}



byte enter_fault_state(void)

{
  byte bVar1;
  
  if (throttle_status_level < TSL_FAULT) {
    throttle_status_level = TSL_FAULT;
  }
  bVar1 = IO_PTD_0003;
  IO_PTD_0003 = bVar1 | 0x10;
  return bVar1 | 0x10;
}



throttle_status_level_t release_shutdown_output(void)

{
  throttle_status_level_t tVar1;
  
  tVar1 = throttle_status_level;
  if (throttle_status_level < TSL_SHUTDOWN) {
    tVar1 = IO_PTD_0003;
    tVar1 = tVar1 | TSL_RUN;
    IO_PTD_0003 = tVar1;
  }
  return tVar1;
}



byte enter_shutdown_state(void)

{
  byte bVar1;
  
  if (throttle_status_level < TSL_SHUTDOWN) {
    throttle_status_level = TSL_SHUTDOWN;
  }
  bVar1 = IO_PTD_0003;
  IO_PTD_0003 = bVar1 & 0xf7;
  return bVar1 & 0xf7;
}



void clear_debounce_counters(void)

{
  debounce_handshake = 0;
  debounce_plaus4 = 0;
  debounce_plaus5 = 0;
  debounce_plaus6 = 0;
  debounce_crosscheck = 0;
  debounce_ch2 = 0;
  debounce_ch7 = 0;
  return;
}



void reset_monitor_state(void)

{
  byte bVar1;
  
  cal_table_checksum();
  rx_cmd_id = 0;
  rx_cal_sel = 0;
  rx_param2 = 0;
  throttle_status_level = TSL_INIT;
  status_flags = 0;
  clear_debounce_counters();
  timeout_handshake_hi = 0;
  timeout_handshake_lo = 0;
  timeout_cmd4._0_1_ = 0;
  timeout_cmd4._1_1_ = 0;
  timeout_cmd5_hi = 0;
  timeout_cmd5_lo = 0;
  armed_handshake = 1;
  armed_cmd4 = 1;
  armed_cmd5 = 1;
  armed_cmd6 = 1;
  DAT_00f6 = DAT_dc4a;
  release_shutdown_output();
  release_fault_output();
  adc_sample_all();
  rx_mode2 = 0x1a;
  log_rd_idx = 0;
  log_wr_idx = 0x22;
  bVar1 = 0;
  do {
    *(undefined1 *)(bVar1 + 0xfb) = rx_mode2;
    bVar1 = bVar1 + 1;
  } while (bVar1 < 0x20);
  return;
}



void compute_position_scaled(void)

{
  undefined1 auStack_3 [3];
  
  if (rx_mode == '\x03') {
    pos_calc_hi = tgt_raw_hi;
    pos_calc_lo = tgt_raw_lo;
    load_acc32();
    mul32x8();
    store_acc32(auStack_3);
    math_acc_b3 = 0x10;
    math_acc_b2 = 0x5e;
    math_acc_b1 = 0x5f;
    math_acc_b0 = 0;
    div32_wrap();
    if (1 < math_acc_b2 && (math_acc_b3 < 0x58) <= (byte)(math_acc_b2 - 2)) {
      pos_calc_hi = math_acc_b2;
      pos_calc_lo = math_acc_b3;
      return;
    }
  }
  pos_calc_lo = 0;
  pos_calc_hi = 0;
  return;
}



void ch1_pos_interp(void)

{
                    // x axis: 0xDC12
                    // y axis: 0xDC22
  lookup_1d_interpolated(16,throttle_pos_ch1,0xdc,0x12,0xdc,0x22);
  return;
}



uint8_t normalize_tps_signal(byte val_raw,byte param_2,byte param_3,byte param_4,byte param_5)

{
  undefined1 uVar1;
  byte in_X;
  undefined2 uStack_7;
  undefined1 _tps;
  
  if (in_X < param_4 || (byte)(in_X - param_4) < (val_raw < param_5)) {
    if (param_2 < in_X || (byte)(param_2 - in_X) < (param_3 < val_raw)) {
      math_acc_ext = (in_X - param_2) - (val_raw < param_3);
      uVar1 = mul8_acc(val_raw - param_3);
      uStack_7 = CONCAT11((param_4 - param_2) - (param_5 < param_3),param_5 - param_3);
      _tps = div16(uVar1,uStack_7);
      if (math_acc_ext != '\0') {
        _tps = 0xff;
      }
    }
    else {
      _tps = '\0';
    }
  }
  else {
    _tps = 0xff;
  }
  return _tps;
}



void process_two_channels(void)

{
  if ((rx_cal_sel & RXCAL_CH1_ALT) == 0) {
    throttle_pos_ch1 =
         normalize_tps_signal
                   (adc_ch1,CAL_tps_mode_calibration_for_linearization[0x10],
                    CAL_tps_mode_calibration_for_linearization[0x11],
                    CAL_tps_mode_calibration_for_linearization[0xe],
                    CAL_tps_mode_calibration_for_linearization[0xf]);
    status_flags = status_flags & ~SF_CH1_CAL_SEL;
  }
  else {
    throttle_pos_ch1 =
         normalize_tps_signal
                   (adc_ch6,CAL_tps_mode_calibration_for_linearization[0xc],
                    CAL_tps_mode_calibration_for_linearization[0xd],
                    CAL_tps_mode_calibration_for_linearization[10],
                    CAL_tps_mode_calibration_for_linearization[0xb]);
    status_flags = status_flags | SF_CH1_CAL_SEL;
  }
  if ((rx_cal_sel & RXCAL_CH2_ALT) == 0) {
    throttle_pos_ch2 =
         normalize_tps_signal
                   (adc_ch4,CAL_tps_mode_calibration_for_linearization[6],
                    CAL_tps_mode_calibration_for_linearization[7],
                    CAL_tps_mode_calibration_for_linearization[4],
                    CAL_tps_mode_calibration_for_linearization[5]);
    if (CAL_tps_mode_calibration_for_linearization[8] < throttle_pos_ch2) {
      throttle_pos_ch2 = CAL_tps_mode_calibration_for_linearization[8];
    }
    status_flags = status_flags & ~SF_CH2_CAL_SEL;
  }
  else {
    throttle_pos_ch2 =
         normalize_tps_signal
                   (adc_ch2,CAL_tps_mode_calibration_for_linearization[2],
                    CAL_tps_mode_calibration_for_linearization[3],
                    CAL_tps_mode_calibration_for_linearization[0],
                    CAL_tps_mode_calibration_for_linearization[1]);
    status_flags = status_flags | SF_CH2_CAL_SEL;
  }
  return;
}



void monitor_track_crosscheck(ushort param_1)

{
  byte bVar1;
  byte bVar2;
  byte bStack_2;
  ushort _cosscheck_pos_scale;
  
  _cosscheck_pos_scale = (ushort)CAL_crosscheck_pos_scale;
  bVar2 = (byte)(_cosscheck_pos_scale * 10 >> 8);
  bVar1 = ch1_pos_interp(param_1 & 0xff00);
  bStack_2 = bVar1;
  if ((pos_calc_hi < bVar2 ||
       (byte)(pos_calc_hi - bVar2) < (pos_calc_lo < (byte)(_cosscheck_pos_scale * 10))) &&
     (bStack_2 = CAL_crosscheck_offset + bVar1, CARRY1(CAL_crosscheck_offset,bVar1))) {
    bStack_2 = 0xff;
  }
  aux_data_8d = bStack_2;
  if (throttle_pos_ch1 < CAL_tps_mode_calibration_for_linearization[9]) {
    if (bStack_2 < throttle_pos_ch2) {
      if (debounce_crosscheck < CAL_debounce_crosscheck_limit) {
        debounce_crosscheck = debounce_crosscheck + 1;
        return;
      }
      debounce_crosscheck = CAL_debounce_crosscheck_limit;
      enter_fault_state();
      return;
    }
    if ((debounce_crosscheck != 0) && (debounce_crosscheck < CAL_debounce_crosscheck_limit)) {
      debounce_crosscheck = debounce_crosscheck - 1;
      return;
    }
  }
  if (debounce_crosscheck == 0) {
    release_fault_output();
  }
  return;
}



void monitor_ch2_limit(void)

{
  aux_data_8d = CAL_ch2_max;
  if (CAL_ch2_max < throttle_pos_ch2) {
    if (debounce_ch2 < CAL_debounce_ch2_limit) {
      debounce_ch2 = debounce_ch2 + 1;
      return;
    }
    debounce_ch2 = CAL_debounce_ch2_limit;
    enter_fault_state();
  }
  else {
    if ((debounce_ch2 != 0) && (debounce_ch2 < CAL_debounce_ch2_limit)) {
      debounce_ch2 = debounce_ch2 - 1;
      return;
    }
    if (debounce_ch2 == 0) {
      release_fault_output();
      return;
    }
  }
  return;
}



void monitor_mode_handshake(void)

{
  if (((rx_cmd_id == CMD_MODE_1) || (rx_cmd_id == CMD_MODE_2)) || (rx_cmd_id == CMD_MODE_3)) {
    if ((((rx_cmd_id == CMD_MODE_1) || (rx_cmd_id == CMD_MODE_2)) || (rx_cmd_id == CMD_MODE_3)) &&
       (rx_cmd_id != throttle_status_level)) {
      timeout_handshake_hi = 0;
      timeout_handshake_lo = 0;
      throttle_status_level = TSL_REARM;
    }
    else {
      math_acc_ext = CARRY1(rx_param2,CAL_handshake_pos_tol);
      if ((byte)math_acc_ext < ((byte)(rx_param2 + CAL_handshake_pos_tol) < throttle_pos_ch2)) {
        if (debounce_handshake < CAL_debounce_handshake_limit) {
          debounce_handshake = debounce_handshake + 1;
        }
        else {
          debounce_handshake = CAL_debounce_handshake_limit;
          armed_handshake = 0;
          throttle_status_level = TSL_REARM;
        }
      }
      else if ((debounce_handshake != 0) && (debounce_handshake < CAL_debounce_handshake_limit)) {
        debounce_handshake = debounce_handshake - 1;
      }
      timeout_handshake_lo = timeout_handshake_lo + 1;
      if (timeout_handshake_lo == 0) {
        timeout_handshake_hi = timeout_handshake_hi + 1;
      }
      if (CAL_handshake_timeout._0_1_ <= timeout_handshake_hi &&
          (timeout_handshake_lo < (byte)CAL_handshake_timeout) <=
          (byte)(timeout_handshake_hi - CAL_handshake_timeout._0_1_)) {
        armed_handshake = 0;
        throttle_status_level = TSL_REARM;
        status_flags = status_flags | SF_TIMEOUT;
      }
    }
  }
  else {
    throttle_status_level = TSL_REARM;
  }
  return;
}



void monitor_plausibility_4(void)

{
  math_acc_ext = CARRY1(rx_param2,CAL_plaus4_pos_tol);
  if ((math_acc_ext < ((byte)(rx_param2 + CAL_plaus4_pos_tol) < throttle_pos_ch2)) ||
     (math_acc_ext = false, CAL_plaus4_pos_max < throttle_pos_ch2)) {
    if (debounce_plaus4 < CAL_debounce_plaus4_limit) {
      debounce_plaus4 = debounce_plaus4 + 1;
    }
    else {
      debounce_plaus4 = CAL_debounce_plaus4_limit;
      armed_cmd4 = 0;
      throttle_status_level = TSL_REARM;
    }
  }
  else if ((debounce_plaus4 != 0) && (debounce_plaus4 < CAL_debounce_plaus4_limit)) {
    debounce_plaus4 = debounce_plaus4 - 1;
  }
  timeout_cmd4._1_1_ = (byte)timeout_cmd4 + 1;
  if ((byte)timeout_cmd4 == 0) {
    timeout_cmd4._0_1_ = timeout_cmd4._0_1_ + 1;
  }
  if (timeout_cmd4._0_1_ < CAL_cmd4_timeout._0_1_ ||
      (byte)(timeout_cmd4._0_1_ - CAL_cmd4_timeout._0_1_) <
      ((byte)timeout_cmd4 < (byte)CAL_cmd4_timeout)) {
    if (rx_cmd_id == CMD_MONITOR_4) {
      return;
    }
  }
  else {
    armed_cmd4 = 0;
  }
  throttle_status_level = TSL_REARM;
  return;
}



void monitor_plausibility_5(void)

{
  math_acc_ext = CARRY1(rx_param2,CAL_plaus5_pos_tol);
  if (math_acc_ext < ((byte)(rx_param2 + CAL_plaus5_pos_tol) < throttle_pos_ch2)) {
    if (debounce_plaus5 < CAL_debounce_plaus5_limit) {
      debounce_plaus5 = debounce_plaus5 + 1;
    }
    else {
      debounce_plaus5 = CAL_debounce_plaus5_limit;
      armed_cmd5 = 0;
      throttle_status_level = TSL_REARM;
    }
  }
  else if ((debounce_plaus5 != 0) && (debounce_plaus5 < CAL_debounce_plaus5_limit)) {
    debounce_plaus5 = debounce_plaus5 - 1;
  }
  timeout_cmd5_lo = timeout_cmd5_lo + 1;
  if (timeout_cmd5_lo == 0) {
    timeout_cmd5_hi = timeout_cmd5_hi + 1;
  }
  if (timeout_cmd5_hi < CAL_cmd5_timeout._0_1_ ||
      (byte)(timeout_cmd5_hi - CAL_cmd5_timeout._0_1_) < (timeout_cmd5_lo < (byte)CAL_cmd5_timeout))
  {
    if (rx_cmd_id == CMD_MONITOR_5) {
      return;
    }
  }
  else {
    armed_cmd5 = 0;
  }
  throttle_status_level = TSL_REARM;
  return;
}



bool compare_ch3_limit(void)

{
  bool bVar1;
  
  bVar1 = CAL_ch3_limit <= adc_ch3;
  if (CAL_ch3_polarity == '\0') {
    bVar1 = !bVar1;
  }
  return bVar1;
}



bool compare_ch9_limit(void)

{
  bool bVar1;
  
  bVar1 = CAL_ch9_limit <= adc_ch9;
  if (CAL_ch9_polarity == '\0') {
    bVar1 = !bVar1;
  }
  if ((rx_cal_sel & RXCAL_DISABLE_CH9) != 0) {
    bVar1 = false;
  }
  return bVar1;
}



void monitor_plausibility_6(void)

{
  char cVar1;
  
  math_acc_ext = CARRY1(rx_param2,CAL_plaus6_pos_tol);
  if ((byte)math_acc_ext < ((byte)(rx_param2 + CAL_plaus6_pos_tol) < throttle_pos_ch2)) {
    if (debounce_plaus6 < CAL_debounce_plaus6_limit) {
      debounce_plaus6 = debounce_plaus6 + 1;
    }
    else {
      debounce_plaus6 = CAL_debounce_plaus6_limit;
      armed_cmd6 = 0;
      throttle_status_level = TSL_REARM;
    }
  }
  else {
    cVar1 = compare_ch3_limit();
    if (cVar1 == '\0') {
      cVar1 = compare_ch9_limit();
      if (cVar1 == '\0') {
        if (rx_cmd_id == CMD_MONITOR_6) {
          if ((debounce_plaus6 != 0) && (debounce_plaus6 < CAL_debounce_plaus6_limit)) {
            debounce_plaus6 = debounce_plaus6 - 1;
          }
        }
        else {
          throttle_status_level = TSL_REARM;
        }
      }
      else {
        armed_cmd6 = 0;
        throttle_status_level = TSL_REARM;
      }
    }
    else {
      armed_cmd6 = 0;
      throttle_status_level = TSL_REARM;
    }
  }
  return;
}



void monitor_ch7_shutdown(void)

{
  if (CAL_ch7_shutdown_limit < adc_ch7) {
    if (debounce_ch7 < CAL_debounce_ch7_limit) {
      debounce_ch7 = debounce_ch7 + 1;
      return;
    }
    debounce_ch7 = CAL_debounce_ch7_limit;
    enter_shutdown_state();
  }
  else {
    if ((debounce_ch7 != 0) && (debounce_ch7 < CAL_debounce_ch7_limit)) {
      debounce_ch7 = debounce_ch7 - 1;
      return;
    }
    if (debounce_ch7 == 0) {
      release_shutdown_output();
      return;
    }
  }
  return;
}



void control_monitor_tick(void)

{
  adc_sample_all();
  compute_position_scaled();
  process_two_channels();
  if (rx_mode2 == 0x1a) {
    status_flags = status_flags & ~SF_MODE;
  }
  else {
    status_flags = status_flags | SF_MODE;
  }
  if (TSL_SHUTDOWN < throttle_status_level) {
    monitor_tick_epilogue();
    return;
  }
                    // WARNING: Subroutine does not return
  dispatch_by_status();
}



void monitor_tick_epilogue(void)

{
  if (throttle_status_level < TSL_SHUTDOWN) {
    if ((((debounce_handshake != '\0') || (debounce_plaus4 != '\0')) || (debounce_plaus5 != '\0'))
       || (((debounce_plaus6 != '\0' || (debounce_crosscheck != '\0')) || (debounce_ch2 != '\0'))))
    {
      status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
      return;
    }
  }
  else if (debounce_ch7 != '\0') {
    status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
    return;
  }
  status_flags = status_flags & ~SF_DEBOUNCE_ACTIVE;
  return;
}



void state_00_handler(void)

{
  if (rx_cmd_id == CMD_REARM) {
    throttle_status_level = rx_cmd_id;
  }
  if (DAT_00f6 != '\0') {
    if (throttle_status_level < TSL_SHUTDOWN) {
      if ((((debounce_handshake != '\0') || (debounce_plaus4 != '\0')) || (debounce_plaus5 != '\0'))
         || (((debounce_plaus6 != '\0' || (debounce_crosscheck != '\0')) || (debounce_ch2 != '\0')))
         ) {
        status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
        return;
      }
    }
    else if (debounce_ch7 != '\0') {
      status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
      return;
    }
    status_flags = status_flags & ~SF_DEBOUNCE_ACTIVE;
    return;
  }
  throttle_status_level = TSL_REARM;
  monitor_tick_epilogue();
  return;
}



void state_01_handler(void)

{
  monitor_mode_handshake();
  monitor_tick_epilogue();
  return;
}



void state_02_handler(void)

{
  monitor_mode_handshake();
  monitor_tick_epilogue();
  return;
}



void state_03_handler(void)

{
  monitor_mode_handshake();
  monitor_tick_epilogue();
  return;
}



void state_04_handler(void)

{
  monitor_plausibility_4();
  monitor_tick_epilogue();
  return;
}



void state_05_handler(void)

{
  monitor_plausibility_5();
  monitor_tick_epilogue();
  return;
}



void state_06_handler(void)

{
  monitor_plausibility_6();
  monitor_tick_epilogue();
  return;
}



void state_07_handler(void)

{
  if ((rx_cmd_id == CMD_MODE_1) && (armed_handshake != '\0')) {
    clear_debounce_counters();
    throttle_status_level = TSL_HANDSHAKE_1;
  }
  else if ((rx_cmd_id == CMD_MODE_2) && (armed_handshake != '\0')) {
    clear_debounce_counters();
    throttle_status_level = TSL_HANDSHAKE_2;
  }
  else if ((rx_cmd_id == CMD_MODE_3) && (armed_handshake != '\0')) {
    clear_debounce_counters();
    throttle_status_level = TSL_HANDSHAKE_3;
  }
  else if ((rx_cmd_id == CMD_MONITOR_4) && (armed_cmd4 != '\0')) {
    clear_debounce_counters();
    throttle_status_level = TSL_MONITOR_4;
  }
  else if ((rx_cmd_id == CMD_MONITOR_5) && (armed_cmd5 != '\0')) {
    clear_debounce_counters();
    throttle_status_level = TSL_MONITOR_5;
  }
  else if ((rx_cmd_id == CMD_MONITOR_6) && (armed_cmd6 != '\0')) {
    clear_debounce_counters();
    throttle_status_level = TSL_MONITOR_6;
  }
  monitor_track_crosscheck();
  monitor_tick_epilogue();
  return;
}



void state_08_handler(void)

{
  monitor_ch2_limit();
  monitor_tick_epilogue();
  return;
}



void state_09_handler(void)

{
  enter_fault_state();
  monitor_ch7_shutdown();
  if ((rx_cal_sel & RXCAL_FORCE_SHUTDOWN) != 0) {
    enter_shutdown_state();
  }
  if (throttle_status_level < TSL_SHUTDOWN) {
    if ((((debounce_handshake != '\0') || (debounce_plaus4 != '\0')) || (debounce_plaus5 != '\0'))
       || (((debounce_plaus6 != '\0' || (debounce_crosscheck != '\0')) || (debounce_ch2 != '\0'))))
    {
      status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
      return;
    }
  }
  else if (debounce_ch7 != '\0') {
    status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
    return;
  }
  status_flags = status_flags & ~SF_DEBOUNCE_ACTIVE;
  return;
}



void state_10_handler(void)

{
  enter_fault_state();
  enter_shutdown_state();
  if (throttle_status_level < TSL_SHUTDOWN) {
    if ((((debounce_handshake != '\0') || (debounce_plaus4 != '\0')) || (debounce_plaus5 != '\0'))
       || (((debounce_plaus6 != '\0' || (debounce_crosscheck != '\0')) || (debounce_ch2 != '\0'))))
    {
      status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
      return;
    }
  }
  else if (debounce_ch7 != '\0') {
    status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
    return;
  }
  status_flags = status_flags & ~SF_DEBOUNCE_ACTIVE;
  return;
}



void monitor_tick_epilogue(void)

{
  if (throttle_status_level < TSL_SHUTDOWN) {
    if ((((debounce_handshake != '\0') || (debounce_plaus4 != '\0')) || (debounce_plaus5 != '\0'))
       || (((debounce_plaus6 != '\0' || (debounce_crosscheck != '\0')) || (debounce_ch2 != '\0'))))
    {
      status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
      return;
    }
  }
  else if (debounce_ch7 != '\0') {
    status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
    return;
  }
  status_flags = status_flags & ~SF_DEBOUNCE_ACTIVE;
  return;
}



void main_loop(void)

{
  char cVar1;
  char extraout_X;
  
  do {
    cVar1 = rx_dispatch();
    if (cVar1 != '\0' || extraout_X != '\0') {
      comm_timer = 'd';
      if ((throttle_status_level < TSL_RUN) && (rx_cmd_id == CMD_RUN)) {
        throttle_status_level = TSL_RUN;
      }
      if ((throttle_status_level < TSL_FAULT) && (rx_cmd_id == CMD_FORCE_FAULT)) {
        enter_fault_state();
      }
      if (((rx_cmd_id != CMD_MODE_1) && (rx_cmd_id != CMD_MODE_2)) && (rx_cmd_id != CMD_MODE_3)) {
        timeout_handshake_hi = 0;
        timeout_handshake_lo = 0;
        armed_handshake = 1;
      }
      if (rx_cmd_id != CMD_MONITOR_4) {
        timeout_cmd4._0_1_ = 0;
        timeout_cmd4._1_1_ = 0;
        armed_cmd4 = 1;
      }
      if (rx_cmd_id != CMD_MONITOR_5) {
        timeout_cmd5_hi = 0;
        timeout_cmd5_lo = 0;
        armed_cmd5 = 1;
      }
      if (rx_cmd_id != CMD_MONITOR_6) {
        armed_cmd6 = 1;
      }
    }
    if (comm_timer == 0) {
      status_flags = status_flags | SF_COMM_LOSS;
      enter_fault_state();
    }
    if (ctrl_due == 0) {
      ctrl_due = '\x01';
      control_monitor_tick();
    }
  } while( true );
}



void tim2_div2_task(void)

{
  if (DAT_0079 != '\0') {
    DAT_0079 = 0;
    return;
  }
  rx_mode = DAT_0079;
  return;
}



undefined1 tim1_isr(undefined1 param_1)

{
  byte bVar1;
  char cVar2;
  undefined1 uVar3;
  byte bVar4;
  byte bVar5;
  
  uVar3 = math_acc_ext;
  bVar1 = IO_TIM_CH_0028;
  if ((bVar1 & 0x80) != 0) {
    bVar1 = IO_TIM_CH_0028;
    IO_TIM_CH_0028 = bVar1 & 0x7f;
    DAT_0079 = 1;
    if (rx_mode == '\0') {
      rx_mode = '\x01';
      DAT_0078 = 0xff;
      bVar1 = DAT_002a;
      DAT_007e = bVar1 - DAT_0082;
      cVar2 = DAT_0029;
      DAT_007d = (cVar2 - DAT_0081) - (bVar1 < DAT_0082);
      DAT_0081 = DAT_0029;
      DAT_0082 = DAT_002a;
    }
    else if (rx_mode == '\x01') {
      bVar1 = DAT_002a;
      DAT_007e = bVar1 - DAT_0082;
      cVar2 = DAT_0029;
      DAT_007d = (cVar2 - DAT_0081) - (bVar1 < DAT_0082);
      DAT_0081 = DAT_0029;
      DAT_0082 = DAT_002a;
      rx_mode = '\x02';
    }
    else {
      bVar1 = tgt_raw_hi;
      bVar4 = tgt_raw_lo;
      if (rx_mode == '\x02') {
        bVar5 = DAT_002a;
        DAT_007c = bVar5 - DAT_0082;
        cVar2 = DAT_0029;
        DAT_007b = (cVar2 - DAT_0081) - (bVar5 < DAT_0082);
        DAT_0081 = DAT_0029;
        DAT_0082 = DAT_002a;
        bVar5 = DAT_007d << 1 | DAT_007e >> 7;
        if (bVar5 < DAT_007b ||
            (byte)(bVar5 - DAT_007b) <
            ((byte)(DAT_007e * '\x02') < DAT_007c || (byte)(DAT_007e * '\x02' - DAT_007c) == '\0'))
        {
          DAT_0078 = 0;
          rx_mode = '\x03';
        }
      }
      else {
        if (rx_mode != '\x03') {
          DAT_0079 = 1;
          rx_mode = 0;
          return param_1;
        }
        DAT_0078 = DAT_0078 + 1;
        if (0x43 < DAT_0078) {
          DAT_0078 = 0;
        }
        bVar1 = DAT_002a;
        DAT_007c = bVar1 - DAT_0082;
        cVar2 = DAT_0029;
        math_acc_ext = (cVar2 - DAT_0081) - (bVar1 < DAT_0082);
        DAT_0081 = DAT_0029;
        DAT_0082 = DAT_002a;
        bVar5 = DAT_007d << 1 | DAT_007e >> 7;
        DAT_007b = math_acc_ext;
        bVar1 = math_acc_ext;
        bVar4 = DAT_007c;
        if (bVar5 < math_acc_ext ||
            (byte)(bVar5 - math_acc_ext) <
            ((byte)(DAT_007e * '\x02') < DAT_007c || (byte)(DAT_007e * '\x02' - DAT_007c) == '\0'))
        {
          if ((DAT_0078 == 0) || (DAT_0078 == 0x22)) {
            bVar4 = div16(DAT_007c,3);
            tgt_raw_hi = math_acc_ext;
            bVar1 = tgt_raw_hi;
          }
          else {
            rx_mode = '\0';
            bVar1 = tgt_raw_hi;
            bVar4 = tgt_raw_lo;
          }
        }
      }
      tgt_raw_lo = bVar4;
      tgt_raw_hi = bVar1;
      DAT_007d = DAT_007b;
      DAT_007e = DAT_007c;
    }
  }
  math_acc_ext = uVar3;
  return param_1;
}



void sci_init(void)

{
  byte bVar1;
  
  DAT_0019 = 2;
  DAT_0013 = 0x40;
  IO_SCC2_0014 = 0xc;
  bVar1 = IO_SCC2_0014;
  IO_SCC2_0014 = bVar1 & 0x7f;
  bVar1 = IO_SCC2_0014;
  IO_SCC2_0014 = bVar1 | 0x20;
  rx_ring_wr = 0;
  rx_ring_rd = 0;
  rx_ring_count = 0;
  rx_parser_state = 0;
  rx_tmp = 0;
  return;
}



undefined1 sci_rx_available(void)

{
  if (rx_ring_count != '\0') {
    return 1;
  }
  return 0;
}



undefined1 sci_rx_dequeue(void)

{
  ushort uVar1;
  
  do {
  } while (rx_ring_count == '\0');
  uVar1 = (ushort)rx_ring_rd;
  rx_ring_count = rx_ring_count + -1;
  if (rx_ring_rd < 0x1f) {
    rx_ring_rd = rx_ring_rd + 1;
  }
  else {
    rx_ring_rd = '\0';
  }
  return *(undefined1 *)(uVar1 + 0xd4);
}



byte sci_tx_start(undefined1 param_1)

{
  byte bVar1;
  
  bVar1 = IO_SCC2_0014;
  IO_SCC2_0014 = bVar1 & 0x7f;
  tx_buf_ptr = param_1;
  tx_idx = 0;
  bVar1 = IO_SCC2_0014;
  IO_SCC2_0014 = bVar1 | 0x80;
  return bVar1 | 0x80;
}



undefined1 sci_rx_isr(undefined1 param_1)

{
  byte bVar1;
  undefined1 uVar2;
  byte bVar3;
  
  bVar3 = rx_ring_wr;
  bVar1 = DAT_0016;
  if ((bVar1 & 0x20) != 0) {
    uVar2 = DAT_0018;
    if (rx_ring_count < 0x20) {
      *(undefined1 *)(rx_ring_wr + 0xd4) = uVar2;
      if (bVar3 < 0x1f) {
        rx_ring_wr = rx_ring_wr + 1;
      }
      else {
        rx_ring_wr = 0;
      }
      rx_ring_count = rx_ring_count + 1;
    }
  }
  return param_1;
}



undefined1 sci_tx_isr(undefined1 param_1)

{
  byte bVar1;
  
  bVar1 = IO_SCC2_0014;
  if (((bVar1 & 0x80) != 0) && (bVar1 = DAT_0016, (bVar1 & 0x80) != 0)) {
    bVar1 = tx_idx + 1;
    DAT_0018 = *(undefined1 *)(tx_idx + 0xb4);
    tx_idx = bVar1;
    if (bVar1 == tx_buf_ptr) {
      bVar1 = IO_SCC2_0014;
      IO_SCC2_0014 = bVar1 & 0x7f;
    }
  }
  return param_1;
}



ushort rx_frame_parser(hc08_msg_type_t param_1,ushort param_2)

{
  ushort uVar1;
  undefined1 *puVar2;
  undefined1 uStack_1;
  
  if (rx_parser_state < 0x14) {
    if (tick_div == 0) {
      rx_parser_state = tick_div;
    }
    tick_div = 6;
    if (rx_parser_state == 0) {
      rx_parser_state = '\x01';
      puVar2 = (undefined1 *)0x0;
      rx_cksum_acc = param_1;
      rx_len = param_1;
    }
    else if (rx_parser_state == 1) {
      rx_parser_state = '\x02';
      puVar2 = (undefined1 *)0x0;
      rx_cksum_acc = param_1 + rx_cksum_acc;
      rx_msg_type = param_1;
    }
    else if ((rx_parser_state < 2) ||
            (math_acc_ext = rx_len == 0xff,
            (byte)math_acc_ext < ((byte)(rx_len + 1) < rx_parser_state))) {
      math_acc_ext = 0xfd < rx_len;
      puVar2 = (undefined1 *)(ushort)rx_parser_state;
      if (rx_parser_state != (hc08_msg_type_t)(rx_len + 2) || (bool)math_acc_ext) {
        rx_parser_state = '\0';
      }
      else {
        rx_tmp = puVar2[0x98];
        puVar2[0x99] = param_1;
        rx_parser_state = '\0';
        puVar2 = &uStack_1;
      }
    }
    else {
      uVar1 = (ushort)rx_parser_state;
      rx_parser_state = rx_parser_state + 1;
      *(hc08_msg_type_t *)(uVar1 + 0x99) = param_1;
      puVar2 = (undefined1 *)0x0;
      rx_cksum_acc = param_1 + rx_cksum_acc;
    }
    return (ushort)puVar2 & 0xff00;
  }
  rx_ring_count = 0;
  rx_ring_rd = 0;
  rx_ring_wr = 0;
  rx_parser_state = 0;
  return param_2 & 0xff00;
}



void tx_frame_build(byte param_1,byte param_2)

{
  bool bVar1;
  char cVar2;
  char in_X;
  char *pcVar3;
  undefined1 *puVar4;
  undefined1 auStack_100 [247];
  undefined2 uStack_9;
  char cStack_7;
  byte local_6;
  char local_5;
  char local_4;
  char local_3;
  byte local_2;
  
  *(byte *)CONCAT11(in_X,param_1) = param_2;
  uStack_9 = CONCAT11(in_X + CARRY1(param_2,param_1),param_2 + param_1);
  *(undefined1 *)(uStack_9 + 1) = rx_tmp;
  local_5 = in_X + CARRY1(param_2,param_1);
  local_4 = param_2 + param_1 + 2;
  if (0xfd < (byte)(param_2 + param_1)) {
    local_5 = local_5 + '\x01';
  }
  *(undefined1 *)CONCAT11(local_5,local_4) = 0;
  cStack_7 = '\0';
  local_6 = 0;
  local_3 = in_X;
  local_2 = param_1;
  while (bVar1 = (byte)(param_2 + 1) < local_6, cVar2 = (param_2 == 0xff) - cStack_7,
        (char)(cVar2 - bVar1) < '\0' !=
        (SBORROW1(param_2 == 0xff,cStack_7) != SBORROW1(cVar2,bVar1))) {
    pcVar3 = (char *)CONCAT11(local_3,local_2);
    local_2 = local_2 + 1;
    if (local_2 == 0) {
      local_3 = local_3 + '\x01';
    }
    *(char *)CONCAT11(local_5,local_4) = *pcVar3 + *(char *)CONCAT11(local_5,local_4);
    local_6 = local_6 + 1;
    if (local_6 == 0) {
      cStack_7 = cStack_7 + '\x01';
    }
  }
  *(byte *)CONCAT11(local_5,local_4) = ~*(byte *)CONCAT11(local_5,local_4);
  puVar4 = auStack_100;
  if (0xfc < param_2) {
    puVar4 = (undefined1 *)CONCAT11((char)((ushort)&cStack_7 >> 8),1);
  }
  uStack_9 = 0xea63;
  sci_tx_start(param_2 + 3,puVar4);
  return;
}



// WARNING: Removing unreachable block (RAM,0xea97)
// WARNING: Removing unreachable block (RAM,0xea82)
// WARNING: Removing unreachable block (RAM,0xeaaa)

void send_crc_frame(void)

{
  undefined1 auStack_100 [249];
  undefined2 uStack_7;
  undefined1 uStack_5;
  undefined1 uStack_4;
  undefined1 local_3;
  undefined1 local_2;
  undefined1 uStack_1;
  
  uStack_1 = 0;
  uRAM00b5 = 0x80;
  uRAM00b6 = crc_hi;
  local_2 = 0xb8;
  local_3 = 0;
  uRAM00b7 = crc_lo;
  uStack_4 = 3;
  uStack_5 = 0;
  uStack_7 = 0xeac0;
  tx_frame_build(0xb4,auStack_100);
  return;
}



// WARNING: Removing unreachable block (RAM,0xec0d)
// WARNING: Removing unreachable block (RAM,0xebe7)
// WARNING: Removing unreachable block (RAM,0xebc1)
// WARNING: Removing unreachable block (RAM,0xeb96)
// WARNING: Removing unreachable block (RAM,0xeb40)
// WARNING: Removing unreachable block (RAM,0xeb1a)
// WARNING: Removing unreachable block (RAM,0xeaf4)
// WARNING: Removing unreachable block (RAM,0xeadf)
// WARNING: Removing unreachable block (RAM,0xeb07)
// WARNING: Removing unreachable block (RAM,0xeb2d)
// WARNING: Removing unreachable block (RAM,0xeb53)
// WARNING: Removing unreachable block (RAM,0xeba8)
// WARNING: Removing unreachable block (RAM,0xebd4)
// WARNING: Removing unreachable block (RAM,0xebfa)
// WARNING: Removing unreachable block (RAM,0xec20)

void send_status_frame(void)

{
  undefined1 auStack_100 [247];
  undefined2 uStack_9;
  undefined1 uStack_7;
  undefined1 uStack_6;
  undefined1 local_5;
  undefined1 local_4;
  undefined1 uStack_3;
  char cStack_2;
  undefined1 uStack_1;
  
  uStack_1 = 0;
  uRAM00b5 = 0x81;
  tRAM00b6 = throttle_status_level;
  sRAM00b7 = status_flags;
  uRAM00b8 = throttle_pos_ch1;
  uRAM00b9 = throttle_pos_ch2;
  uRAM00ba = aux_data_8d;
  uRAM00bb = adc_ch7;
  cStack_2 = log_rd_idx - 6;
  uStack_3 = 5 < log_rd_idx;
  if ((*(char *)CONCAT11(uStack_3,cStack_2) != '\x1a') && (log_rd_idx < log_wr_idx)) {
    log_wr_idx = log_rd_idx;
  }
  if (log_rd_idx < 0x20) {
    log_rd_idx = log_rd_idx + 1;
  }
  else {
    log_rd_idx = '\0';
  }
  uRAM00be = *(undefined1 *)CONCAT11(uStack_3,cStack_2);
  bRAM00bf = log_wr_idx;
  uRAM00c0 = adc_ch3;
  uRAM00c1 = adc_ch9;
  uRAM00c2 = crc_hi;
  local_4 = 0xc4;
  local_5 = 0;
  uRAM00c3 = crc_lo;
  uStack_6 = 0xf;
  uStack_7 = 0;
  uStack_9 = 0xec36;
  uRAM00bc = uStack_3;
  cRAM00bd = cStack_2;
  tx_frame_build(0xb4,auStack_100);
  return;
}



undefined1 rx_dispatch(void)

{
  char cVar1;
  char extraout_X;
  char extraout_X_00;
  
  while( true ) {
    do {
      cVar1 = sci_rx_available();
      if (cVar1 == '\0' && extraout_X == '\0') {
        return 0;
      }
      sci_rx_dequeue();
      cVar1 = rx_frame_parser();
    } while (cVar1 == '\0' && extraout_X_00 == '\0');
    if (rx_msg_type == MSG_CRC) break;
    if (rx_msg_type == MSG_STATUS) {
      rx_cmd_id = rx_payload0;
      rx_cal_sel = rx_payload1;
      rx_param2 = rx_payload2;
      send_status_frame();
      return 1;
    }
  }
  send_crc_frame();
  return 1;
}



void timer2_init(void)

{
  byte bVar1;
  
  DAT_0030 = 0x33;
  DAT_0033 = 0xc;
  DAT_0034 = 0x26;
  bVar1 = DAT_0030;
  DAT_0030 = bVar1 | 0x10;
  bVar1 = DAT_0030;
  DAT_0030 = bVar1 | 0x40;
  bVar1 = DAT_0030;
  DAT_0030 = bVar1 & 0xdf;
  comm_timer = 100;
  ctrl_due = 0;
  tick_div = 0;
  DAT_00f5 = 2;
  DAT_00f4 = 0x14;
  return;
}



undefined1 tim2_isr(undefined1 param_1)

{
  byte bVar1;
  undefined1 uVar2;
  
  uVar2 = math_acc_ext;
  bVar1 = DAT_0030;
  DAT_0030 = bVar1 & 0x7f;
  if (comm_timer != '\0') {
    comm_timer = comm_timer + -1;
  }
  if (ctrl_due != '\0') {
    ctrl_due = ctrl_due + -1;
  }
  if (tick_div != '\0') {
    tick_div = tick_div + -1;
  }
  DAT_00f5 = DAT_00f5 + -1;
  if (DAT_00f5 == '\0') {
    DAT_00f5 = '\x02';
    tim2_div2_task();
  }
  DAT_00f4 = DAT_00f4 + -1;
  if ((DAT_00f4 == '\0') && (DAT_00f4 = '\x14', DAT_00f6 != '\0')) {
    DAT_00f6 = DAT_00f6 + -1;
  }
  math_acc_ext = uVar2;
  return param_1;
}



undefined1 mul8_acc(byte param_1)

{
  char in_HI;
  byte in_X;
  
  math_acc_ext = (char)((ushort)param_1 * (ushort)in_X >> 8) + param_1 * in_HI + math_acc_ext * in_X
  ;
  return (char)((ushort)param_1 * (ushort)in_X);
}



void dispatch_by_status(char param_1)

{
  char unaff_retaddr;
  byte unaff_retaddr_00;
  
  if (param_1 < '\0') {
    unaff_retaddr = unaff_retaddr + '\x01';
  }
  if (CARRY1(param_1 * '\x02',unaff_retaddr_00)) {
    unaff_retaddr = unaff_retaddr + '\x01';
  }
                    // WARNING: Could not recover jumptable at 0xed26. Too many branches
                    // WARNING: Treating indirect jump as call
  (**(code **)CONCAT11(unaff_retaddr,param_1 * '\x02' + unaff_retaddr_00))();
  return;
}



undefined1 add32_acc(undefined1 param_1,char *param_2)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  
  bVar1 = param_2[3];
  bVar2 = CARRY1(math_acc_b3,bVar1);
  math_acc_b3 = math_acc_b3 + bVar1;
  bVar1 = math_acc_b2 + param_2[2];
  bVar3 = CARRY1(math_acc_b2,param_2[2]) || CARRY1(bVar1,bVar2);
  math_acc_b2 = bVar1 + bVar2;
  bVar2 = CARRY1(math_acc_b1,param_2[1]);
  bVar1 = math_acc_b1 + param_2[1];
  math_acc_b1 = bVar1 + bVar3;
  math_acc_b0 = math_acc_b0 + *param_2 + (bVar2 || CARRY1(bVar1,bVar3));
  return param_1;
}



undefined1 cmp32(undefined1 param_1)

{
  return param_1;
}



undefined1 div32_wrap(undefined1 param_1)

{
  undefined1 uStack_1;
  
  div32();
  if ((uStack_1 != '\0') && (uStack_1 != '\x03')) {
    neg32_acc();
  }
  return param_1;
}



undefined1 div32_signed(undefined1 param_1)

{
  undefined1 uStack_9;
  undefined1 uStack_8;
  undefined1 uStack_7;
  undefined1 uStack_6;
  undefined1 uStack_1;
  
  div32();
  math_acc_b0 = uStack_9;
  math_acc_b1 = uStack_8;
  math_acc_b2 = uStack_7;
  math_acc_b3 = uStack_6;
  if ((uStack_1 & 2) != 0) {
    neg32_acc();
  }
  return param_1;
}



void div32(char *param_1)

{
  short sVar1;
  undefined1 *puVar2;
  char cStack0007;
  char cStack0008;
  char cStack0009;
  char cStack000a;
  undefined1 uStack000b;
  
  cStack000a = param_1[3];
  cStack0009 = param_1[2];
  cStack0008 = param_1[1];
  cStack0007 = *param_1;
  puVar2 = &stack0x0001;
  uStack000b = 0;
  if (cStack0007 < '\0') {
    sVar1 = neg32_buf(&stack0x0007);
    puVar2 = (undefined1 *)(sVar1 + -6);
    *(char *)(sVar1 + 4) = *(char *)(sVar1 + 4) + '\x01';
  }
  if (math_acc_b0 < '\0') {
    puVar2 = (undefined1 *)neg32_acc();
    puVar2[10] = puVar2[10] + '\x01';
    puVar2[10] = puVar2[10] + '\x01';
  }
  div32_core(puVar2 + 6);
  return;
}



undefined1 div32_quotient(undefined1 param_1)

{
  div32_core();
  return param_1;
}



undefined1 div32_remainder(undefined1 param_1)

{
  undefined1 uStack_4;
  undefined1 uStack_3;
  undefined1 uStack_2;
  undefined1 uStack_1;
  
  div32_core();
  math_acc_b0 = uStack_4;
  math_acc_b1 = uStack_3;
  math_acc_b2 = uStack_2;
  math_acc_b3 = uStack_1;
  return param_1;
}



undefined1 div32_core(byte *param_1)

{
  byte bVar1;
  byte bVar2;
  bool bVar3;
  bool bVar4;
  byte bVar5;
  byte bVar6;
  char cVar7;
  byte bStack0003;
  byte bStack0004;
  byte bStack0005;
  byte bStack0006;
  
  bStack0003 = 0;
  bStack0004 = 0;
  bStack0005 = 0;
  bStack0006 = 0;
  cVar7 = ' ';
  do {
    bVar5 = math_acc_b3 >> 7;
    math_acc_b3 = math_acc_b3 * '\x02';
    bVar6 = math_acc_b2 >> 7;
    math_acc_b2 = math_acc_b2 << 1 | bVar5;
    bVar5 = math_acc_b1 >> 7;
    math_acc_b1 = math_acc_b1 << 1 | bVar6;
    bVar6 = math_acc_b0 >> 7;
    math_acc_b0 = math_acc_b0 << 1 | bVar5;
    bVar5 = bStack0006 >> 7;
    bStack0006 = bStack0006 << 1 | bVar6;
    bVar6 = bStack0005 >> 7;
    bStack0005 = bStack0005 << 1 | bVar5;
    bVar5 = bStack0004 >> 7;
    bStack0004 = bStack0004 << 1 | bVar6;
    bStack0003 = bStack0003 << 1 | bVar5;
    bVar5 = param_1[3];
    bVar6 = bStack0005 - param_1[2];
    bVar3 = bStack0005 < param_1[2] || bVar6 < (bStack0006 < bVar5);
    bVar1 = bStack0004 - param_1[1];
    bVar4 = bStack0004 < param_1[1] || bVar1 < bVar3;
    bVar2 = bStack0003 - *param_1;
    if (*param_1 <= bStack0003 && bVar4 <= bVar2) {
      math_acc_b3 = math_acc_b3 + 1;
      bStack0003 = bVar2 - bVar4;
      bStack0004 = bVar1 - bVar3;
      bStack0005 = bVar6 - (bStack0006 < bVar5);
      bStack0006 = bStack0006 - bVar5;
    }
    cVar7 = cVar7 + -1;
  } while (cVar7 != '\0');
  return 0;
}



undefined1 add32_to_buf(undefined1 param_1,char *param_2)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  
  bVar1 = param_2[3];
  bVar2 = CARRY1(bVar1,math_acc_b3);
  param_2[3] = bVar1 + math_acc_b3;
  bVar1 = param_2[2] + math_acc_b2;
  bVar3 = CARRY1(param_2[2],math_acc_b2) || CARRY1(bVar1,bVar2);
  param_2[2] = bVar1 + bVar2;
  bVar2 = CARRY1(param_2[1],math_acc_b1);
  bVar1 = param_2[1] + math_acc_b1;
  param_2[1] = bVar1 + bVar3;
  *param_2 = *param_2 + math_acc_b0 + (bVar2 || CARRY1(bVar1,bVar3));
  return param_1;
}



void neg32_buf(byte *param_1)

{
  byte bVar1;
  
  *param_1 = ~*param_1;
  param_1[1] = ~param_1[1];
  param_1[2] = ~param_1[2];
  bVar1 = -param_1[3];
  param_1[3] = bVar1;
  if (((bVar1 == 0) && (bVar1 = param_1[2] + 1, param_1[2] = bVar1, bVar1 == 0)) &&
     (bVar1 = param_1[1] + 1, param_1[1] = bVar1, bVar1 == 0)) {
    *param_1 = *param_1 + 1;
  }
  return;
}



undefined1 mul32_buf(undefined1 param_1,char *param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  short sVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  
  bVar1 = param_2[3];
  bVar2 = param_2[2];
  bVar6 = (byte)((ushort)math_acc_b1 * (ushort)bVar1);
  bVar7 = (byte)((ushort)math_acc_b2 * (ushort)bVar2);
  bVar3 = bVar7 + bVar6;
  sVar5 = (ushort)math_acc_b3 * (ushort)(byte)param_2[1];
  bVar8 = (byte)sVar5;
  bVar4 = bVar8 + bVar3;
  math_acc_b0 = (char)((ushort)sVar5 >> 8) +
                (char)((ushort)math_acc_b2 * (ushort)bVar2 >> 8) +
                (char)((ushort)math_acc_b1 * (ushort)bVar1 >> 8) +
                math_acc_b3 * *param_2 +
                math_acc_b2 * param_2[1] + math_acc_b1 * bVar2 + math_acc_b0 * bVar1 +
                CARRY1(bVar7,bVar6) + CARRY1(bVar8,bVar3);
  bVar7 = (byte)((ushort)math_acc_b2 * (ushort)bVar1);
  bVar6 = (byte)((ushort)math_acc_b2 * (ushort)bVar1 >> 8);
  bVar3 = bVar6 + bVar4;
  if (CARRY1(bVar6,bVar4)) {
    math_acc_b0 = math_acc_b0 + '\x01';
  }
  bVar6 = (byte)((ushort)math_acc_b3 * (ushort)bVar2);
  bVar4 = (byte)((ushort)math_acc_b3 * (ushort)bVar2 >> 8);
  bVar2 = bVar4 + bVar3;
  math_acc_b1 = bVar2 + CARRY1(bVar6,bVar7);
  if (CARRY1(bVar4,bVar3) || CARRY1(bVar2,CARRY1(bVar6,bVar7))) {
    math_acc_b0 = math_acc_b0 + '\x01';
  }
  bVar2 = (byte)((ushort)math_acc_b3 * (ushort)bVar1 >> 8);
  math_acc_b3 = (char)((ushort)math_acc_b3 * (ushort)bVar1);
  math_acc_b2 = bVar2 + bVar6 + bVar7;
  if ((CARRY1(bVar2,bVar6 + bVar7)) && (math_acc_b1 = math_acc_b1 + '\x01', math_acc_b1 == '\0')) {
    math_acc_b0 = math_acc_b0 + '\x01';
  }
  return param_1;
}



void neg32_acc(void)

{
  math_acc_b0 = ~math_acc_b0;
  math_acc_b1 = ~math_acc_b1;
  math_acc_b2 = ~math_acc_b2;
  math_acc_b3 = -math_acc_b3;
  if (((math_acc_b3 == '\0') && (math_acc_b2 = math_acc_b2 + 1, math_acc_b2 == 0)) &&
     (math_acc_b1 = math_acc_b1 + 1, math_acc_b1 == 0)) {
    math_acc_b0 = math_acc_b0 + 1;
  }
  return;
}



undefined1 sub32_acc(undefined1 param_1,char *param_2)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  
  bVar1 = param_2[3];
  bVar2 = math_acc_b3 < bVar1;
  math_acc_b3 = math_acc_b3 - bVar1;
  bVar1 = math_acc_b2 - param_2[2];
  bVar3 = math_acc_b2 < (byte)param_2[2] || bVar1 < bVar2;
  math_acc_b2 = bVar1 - bVar2;
  bVar2 = math_acc_b1 < (byte)param_2[1];
  bVar1 = math_acc_b1 - param_2[1];
  math_acc_b1 = bVar1 - bVar3;
  math_acc_b0 = (math_acc_b0 - *param_2) - (bVar2 || bVar1 < bVar3);
  return param_1;
}



undefined1 * load_acc32_ptr(undefined1 *param_1)

{
  math_acc_b0 = *param_1;
  math_acc_b1 = param_1[1];
  math_acc_b2 = param_1[2];
  math_acc_b3 = param_1[3];
  return param_1;
}



undefined1 * store_acc32(undefined1 *param_1)

{
  *param_1 = math_acc_b0;
  param_1[1] = math_acc_b1;
  param_1[2] = math_acc_b2;
  param_1[3] = math_acc_b3;
  return param_1;
}



void mul32x8(byte param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  char cVar4;
  
  bVar2 = (byte)((ushort)param_1 * (ushort)math_acc_b3 >> 8);
  math_acc_b3 = (char)((ushort)param_1 * (ushort)math_acc_b3);
  bVar1 = (byte)((ushort)math_acc_b2 * (ushort)param_1);
  bVar3 = (byte)((ushort)math_acc_b2 * (ushort)param_1 >> 8);
  math_acc_b2 = bVar1 + bVar2;
  if (CARRY1(bVar1,bVar2)) {
    bVar3 = bVar3 + 1;
  }
  bVar1 = (byte)((ushort)math_acc_b1 * (ushort)param_1);
  cVar4 = (char)((ushort)math_acc_b1 * (ushort)param_1 >> 8);
  math_acc_b1 = bVar1 + bVar3;
  if (CARRY1(bVar1,bVar3)) {
    cVar4 = cVar4 + '\x01';
  }
  math_acc_b0 = math_acc_b0 * param_1 + cVar4;
  return;
}



undefined1 div16_remainder(void)

{
  undefined1 extraout_HI;
  undefined1 extraout_X;
  
  div16();
  math_acc_ext = extraout_HI;
  return extraout_X;
}



ushort div16(byte param_1,ushort param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar6;
  ushort uVar5;
  bool bVar7;
  undefined1 in_stack_00000000;
  char cStack_3;
  byte local_1;
  
  bVar4 = (byte)(param_2 >> 8);
  bVar6 = (byte)param_2;
  if (bVar4 != 0) {
    bVar3 = 0;
    cStack_3 = '\b';
    do {
      bVar1 = param_1 >> 7;
      param_1 = param_1 * '\x02';
      bVar2 = math_acc_ext >> 7;
      math_acc_ext = math_acc_ext << 1 | bVar1;
      bVar3 = bVar3 << 1 | bVar2;
      if ((bVar4 <= bVar3) && ((bVar3 != bVar4 || (bVar6 <= math_acc_ext)))) {
        bVar7 = math_acc_ext < bVar6;
        math_acc_ext = math_acc_ext - bVar6;
        bVar3 = (bVar3 - bVar4) - bVar7;
        param_1 = param_1 + 1;
      }
      cStack_3 = cStack_3 + -1;
    } while (cStack_3 != '\0');
    uVar5 = CONCAT11(bVar3,math_acc_ext);
    math_acc_ext = 0;
    return uVar5;
  }
  if (math_acc_ext < bVar6) {
    uVar5 = CONCAT11(math_acc_ext,in_stack_00000000);
    bVar4 = (byte)(uVar5 % (param_2 & 0xff));
    math_acc_ext = 0;
  }
  else {
    uVar5 = (ushort)math_acc_ext;
    math_acc_ext = math_acc_ext / bVar6;
    bVar4 = (byte)((uVar5 % (param_2 & 0xff) << 8 | (ushort)param_1) % (param_2 & 0xff));
  }
  return (ushort)bVar4;
}



void load_acc32_alt(undefined1 param_1)

{
  math_acc_b3 = param_1;
  math_acc_b2 = math_acc_ext;
  math_acc_b1 = 0;
  math_acc_b0 = 0;
  return;
}



void load_acc32(undefined1 param_1)

{
  undefined1 in_X;
  
  math_acc_b3 = param_1;
  math_acc_b2 = in_X;
  math_acc_b1 = 0;
  math_acc_b0 = 0;
  return;
}



// WARNING: Control flow encountered bad instruction data

void load_acc16_alt(undefined1 param_1)

{
  math_acc_b3 = param_1;
  math_acc_b1 = 0;
  math_acc_b2 = math_acc_ext;
  if (math_acc_ext < '\0') {
    math_acc_b1 = 0xff;
  }
  math_acc_b0 = math_acc_b1;
                    // WARNING: Bad instruction - Truncating control flow here
  halt_baddata();
}



// WARNING: Control flow encountered bad instruction data

void load_acc16_signed(undefined1 param_1)

{
  char in_X;
  
  math_acc_b3 = param_1;
  math_acc_b1 = 0;
  math_acc_b2 = in_X;
  if (in_X < '\0') {
    math_acc_b1 = 0xff;
  }
  math_acc_b0 = math_acc_b1;
                    // WARNING: Bad instruction - Truncating control flow here
  halt_baddata();
}


