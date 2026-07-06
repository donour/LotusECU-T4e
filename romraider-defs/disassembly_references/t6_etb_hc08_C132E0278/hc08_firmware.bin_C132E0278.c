#define 16 0x10

typedef unsigned char   undefined;

typedef unsigned char    bool;
typedef unsigned char    byte;
typedef unsigned char    uchar;
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

typedef ushort uint16_t;

typedef uchar uint8_t;



byte DAT_0000;
byte DAT_001d;
undefined IO_ADSCR_003C;
byte DAT_001f;
undefined1 IO_ADR_003D;
byte DAT_0001;
undefined1 debounce_monitor4;
undefined2 DAT_015e;
byte UNK_000f;
undefined1 armed_monitor5;
byte UNK_0010;
byte UNK_001a;
byte UNK_0021;
char UNK_003f;
char UNK_0040;
byte UNK_004c;
undefined1 UNK_005e;
undefined1 UNK_0067;
undefined1 UNK_00b0;
byte UNK_00cc;
byte UNK_00e8;
undefined1 debounce_peak_monitor5;
undefined1 IO_PTD_0003;
undefined IO_TIM_MODH_0023;
undefined1 DAT_001d;
undefined VECTOR_SWI;
undefined1 IO_TIM_CH_0028;
undefined1 IO_DDRD_0007;
undefined1 IO_TIM_SC_0020;
undefined IO_TIM_MODL_0024;
uint8_t DAT_0063;
char DAT_0062;
char DAT_0061;
char DAT_0060;
uint8_t[7] adc_latch;
char DAT_008b;
byte DAT_008c;
throttle_status_level_t throttle_status_level;
undefined1 debounce_ch2_run;
undefined1 debounce_crosscheck;
undefined1 debounce_monitor6;
undefined1 debounce_monitor5;
undefined1 debounce_ch7_shutdown;
undefined1 debounce_peak_monitor6;
undefined1 debounce_peak_monitor4;
undefined1 debounce_peak_ch2run;
undefined1 debounce_peak_crosscheck;
undefined1 DAT_00ff;
undefined1 DAT_0103;
undefined1 DAT_007a;
undefined1 DAT_0079;
undefined DAT_0104;
hc08_cmd_t rx_cmd_id;
status_flag_bits status_flags;
rx_cal_sel_bits rx_cal_sel;
undefined1 CAL_handshake_init_count;
undefined1 armed_monitor6;
undefined1 armed_monitor4;
undefined armed_mode;
undefined1 monitor5_timeout_hi;
undefined1 monitor5_timeout_lo;
undefined1 monitor4_timeout_hi;
undefined1 monitor4_timeout_lo;
undefined mode_timeout_hi;
undefined mode_timeout_lo;
undefined1 commanded_position_offset;
char DAT_0082;
undefined1 DAT_0087;
undefined1 DAT_0088;
byte DAT_0063;
byte DAT_0062;
uint16_t computed_position;
undefined1 DAT_0061;
undefined1 DAT_0060;
undefined1 throttle_pos_ch1;
undefined1 math_acc_ext;
undefined1 throttle_pos_ch2;
byte[18] CAL_tps_mode_calibration_for_linearization;
char DAT_008d;
undefined1 CAL_crosscheck_ch2_offset;
undefined1 CAL_crosscheck_scale;
undefined1 CAL_debounce_crosscheck_limit;
undefined1 crosscheck_ch2_reference;
undefined1 CAL_crosscheck_ch2_bias;
undefined1 CAL_crosscheck_pos_threshold;
undefined1 CAL_debounce_ch2run_limit;
undefined1 CAL_ch2_run_limit;
undefined1 CAL_monitor4_timeout_hi;
undefined1 CAL_monitor4_timeout_lo;
undefined1 CAL_monitor4_offset;
undefined1 CAL_monitor4_max;
undefined1 CAL_debounce_monitor4_limit;
undefined1 CAL_monitor5_timeout_hi;
undefined1 CAL_monitor5_timeout_lo;
undefined1 CAL_monitor5_offset;
undefined1 CAL_debounce_monitor5_limit;
undefined1 CAL_ch3_limit;
undefined1 CAL_ch3_polarity;
undefined1 CAL_ch9_limit;
undefined1 CAL_ch9_polarity;
undefined1 CAL_monitor6_offset;
undefined1 CAL_debounce_monitor6_limit;
undefined1 CAL_ch7_shutdown_limit;
undefined1 CAL_debounce_ch7_limit;
char DAT_0103;
char DAT_00ff;
undefined1 tick_due_flag;
undefined1 comm_timeout;
char DAT_0081;
undefined1 DAT_0081;
byte DAT_002a;
byte DAT_008a;
byte DAT_0084;
char DAT_0029;
char DAT_0089;
byte DAT_0083;
byte DAT_0086;
byte DAT_0085;
byte DAT_0080;
byte DAT_0088;
byte DAT_0087;
undefined1 DAT_0019;
undefined1 DAT_0013;
undefined1 DAT_00bc;
undefined1 DAT_00bb;
undefined1 DAT_00ba;
undefined1 DAT_00b6;
undefined1 DAT_00b7;
undefined1 IO_SCC2_0014;
char DAT_00ba;
byte DAT_00bb;
undefined1 DAT_00b8;
undefined1 DAT_00b9;
byte DAT_0016;
undefined1 DAT_0018;
byte DAT_00ba;
byte DAT_00bc;
byte DAT_00b6;
byte DAT_00a1;
byte DAT_00a2;
byte DAT_00a3;
undefined1 tx_busy_timer;
undefined1 DAT_008b;
undefined1 DAT_008c;
undefined1 UNK_00be;
undefined1 UNK_00bf;
undefined1 UNK_00c0;
byte DAT_007a;
byte DAT_0079;
throttle_status_level_t UNK_00bf;
status_flag_bits UNK_00c0;
undefined1 UNK_00c1;
undefined1 UNK_00c2;
undefined1 UNK_00c3;
uint8_t UNK_00c4;
char UNK_00c5;
char UNK_00c6;
undefined1 UNK_00c7;
byte UNK_00c8;
uint8_t UNK_00c9;
uint8_t UNK_00ca;
undefined1 UNK_00cb;
undefined1 UNK_00cc;
undefined1 UNK_00cd;
undefined1 UNK_00ce;
undefined1 UNK_00cf;
undefined1 UNK_00d0;
undefined1 UNK_00d1;
char DAT_00a3;
hc08_cmd_t DAT_00a4;
byte DAT_008d;
rx_cal_sel_bits DAT_00a5;
undefined1 DAT_00a6;
undefined1 DAT_0030;
undefined1 DAT_0033;
undefined1 DAT_0034;
undefined1 DAT_00fe;
undefined1 DAT_00fd;
byte DAT_0030;
char DAT_00fe;
char DAT_00fd;
byte DAT_0061;
undefined1 DAT_0062;
undefined1 DAT_0063;

// WARNING: Control flow encountered bad instruction data
// WARNING: Instruction at (RAM,0xdc6c) overlaps instruction at (RAM,0xdc6b)
// 
// WARNING: This function may have set the stack pointer

char * FUN_dc6b(char *param_1,undefined1 param_2)

{
  byte bVar1;
  byte extraout_A;
  undefined1 uVar2;
  char cVar4;
  char *pcVar3;
  byte in_CCR;
  
  if ((DAT_0000 & 1) == 0) {
    return param_1;
  }
  debounce_monitor4 = debounce_monitor4 & 0x7f;
  if ((DAT_001d & 2) == 0) {
                    // WARNING: Could not recover jumptable at 0xdc7d. Too many branches
                    // WARNING: Treating indirect jump as call
    pcVar3 = (char *)(*(code *)(param_1 + -0x5c33))();
    return pcVar3;
  }
  bVar1 = bRAM00cc & param_1[0xff];
  cVar4 = (char)param_1;
  *param_1 = cVar4;
  *param_1 = cVar4;
  uVar2 = (undefined1)((ushort)param_1 >> 8);
  if (cVar4 == '\0') {
    if ((bRAM000f & 8) != 0) {
                    // WARNING: Bad instruction - Truncating control flow here
      halt_baddata();
    }
    debounce_peak_monitor5 = debounce_peak_monitor5 >> 1;
    if ((bRAM00e8 & 2) != 0) {
      armed_monitor5 = armed_monitor5 >> 1;
      *param_1 = *param_1 << 1;
      *param_1 = *param_1 << 1;
      *param_1 = *param_1 << 1;
      *param_1 = *param_1 << 1;
      *param_1 = *param_1 << 1;
      *param_1 = *param_1 << 1;
      return (char *)CONCAT11(uVar2,param_2);
    }
  }
  else {
    if (((in_CCR & 0x78) >> 3 & 1) == 1) {
      DAT_0000 = ~DAT_0000;
      pcVar3 = (char *)CONCAT11(uVar2,cVar4 << 1);
      if ((bRAM001a & 1) != 0) {
        bRAM004c = ~bRAM004c;
        pcVar3[0x80] = (byte)pcVar3[0x80] >> 1 | 0x80;
        DAT_001f = DAT_001f & 0xef;
        if ((byte)(bVar1 + pcVar3[-0x190e] + ((byte)(cVar4 << 1) < bRAM00cc) + *pcVar3) != '\0') {
          cRAM003f = cRAM003f >> 1;
          debounce_monitor4 = uRAM005e;
                    // WARNING: Bad instruction - Truncating control flow here
          halt_baddata();
        }
        if ((DAT_0001 & 1) == 0) {
adc_to_ports_loop:
          do {
          } while( true );
        }
        if ((IO_TIM_MODH_0023 & 0x20) == 0) {
          if (((DAT_0000 & 1) == 0) && ((DAT_0000 & 1) == 0)) {
            if ((bRAM0010 & 1) != 0) goto adc_to_ports_loop;
          }
          else {
            DAT_001f = DAT_001f | 1;
          }
          DAT_001d = 2;
          init_ports_timer_sci();
          sci_init();
          init_tick_state();
          pcVar3 = (char *)reset_monitor_state();
          return pcVar3;
        }
      }
      bRAM0021 = bRAM0021 & 0xf7;
      cRAM0040 = -cRAM0040;
      debounce_peak_monitor5 = uRAM0067;
                    // WARNING: Bad instruction - Truncating control flow here
      halt_baddata();
    }
    DAT_015e = 0xdc8f;
    param_1 = (char *)startup_init();
    bVar1 = extraout_A;
  }
  pcVar3 = (char *)enter_main_loop(bVar1,(ushort)param_1);
  return pcVar3;
}



void startup_init(void)

{
  DAT_001f = DAT_001f | 1;
  DAT_001d = 2;
  init_ports_timer_sci();
  sci_init();
  init_tick_state();
  reset_monitor_state();
  return;
}



// WARNING: This function may have set the stack pointer

void reset_entry(void)

{
  char extraout_A;
  ushort uVar1;
  
  DAT_015e = 0xdc8f;
  uVar1 = startup_init();
  enter_main_loop(extraout_A,uVar1);
  return;
}



void adc_to_ports_loop(void)

{
                    // WARNING: Do nothing block with infinite loop
  do {
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



void init_ports_timer_sci(void)

{
  IO_PTD_0003 = IO_PTD_0003 & 0xef | 8;
  IO_DDRD_0007 = IO_DDRD_0007 | 0x18;
  IO_TIM_CH_0028 = 0x44;
  IO_TIM_MODH_0023 = 0xff;
  IO_TIM_MODL_0024 = 0xff;
  IO_TIM_SC_0020 = 0x12;
  return;
}



void enter_main_loop(char param_1,ushort param_2)

{
  main_loop(param_1,param_2);
  return;
}



// table_interp(count, x, data_ptr, axis_ptr): binary-search x in axis[], linear-
// interpolate the matching data[] entry. Used for both cross-check transfer tables.

uint8_t table_interp(undefined1 param_1,byte param_2,uint8_t param_3,byte param_4,uint8_t param_5,
                    byte param_6)

{
  byte bVar1;
  char cVar2;
  undefined1 uVar3;
  uint8_t uVar4;
  short sVar5;
  byte bVar6;
  undefined2 uStack_1f;
  char acStack_15 [3];
  undefined1 local_12;
  byte bStack_11;
  byte bStack_10;
  byte bStack_f;
  byte bStack_e;
  char cStack_b;
  byte bStack_a;
  undefined1 uStack_5;
  undefined1 uStack_4;
  undefined1 uStack_3;
  undefined1 uStack_2;
  
  uStack_3 = 0;
  uStack_4 = 0;
  uStack_5 = 0;
  uStack_2 = param_1;
  FUN_f173();
  FUN_f159();
  bStack_11 = FUN_f17e();
  if (*(byte *)CONCAT11(param_5,param_6) < param_2) {
    uStack_1f = (byte *)CONCAT11(cStack_b + param_5 + CARRY1(bStack_a,param_6),bStack_a + param_6);
    bStack_10 = bStack_11;
    bStack_f = bStack_11;
    bStack_e = bStack_11;
    if (param_2 < *uStack_1f) {
      while( true ) {
        uStack_1f = (byte *)CONCAT11(bStack_f + param_5 + CARRY1(bStack_e,param_6),
                                     bStack_e + param_6);
        bVar1 = *uStack_1f;
        bVar6 = bVar1 - param_2;
        bVar6 = ((char)bVar6 < '\0') << 2 |
                (((bVar1 & ~param_2 & ~bVar6 | ~bVar1 & param_2 & bVar6) & 0x80) != 0) << 7;
        if (param_2 <= bVar1) break;
        uVar3 = FUN_f173();
        FUN_ef90(uVar3);
        if ((byte)(bVar6 >> 2 & 1 ^ bVar6 >> 7) != 1) break;
        DAT_0063 = '\x01';
        DAT_0062 = 0;
        DAT_0061 = 0;
        DAT_0060 = 0;
        FUN_f088();
      }
      uStack_1f = (byte *)CONCAT11(bStack_f + param_5 + CARRY1(bStack_e,param_6),bStack_e + param_6)
      ;
      if (*uStack_1f == param_2) {
        uStack_1f = (byte *)CONCAT11(bStack_f + param_3 + CARRY1(bStack_e,param_4),
                                     bStack_e + param_4);
        return *uStack_1f;
      }
      uStack_1f = (byte *)CONCAT11((bStack_f - (bStack_e == 0)) + param_5 +
                                   CARRY1(bStack_e - 1,param_6),(bStack_e - 1) + param_6);
      cVar2 = *uStack_1f;
      uStack_1f = (byte *)CONCAT11(bStack_f + param_5 + CARRY1(bStack_e,param_6),bStack_e + param_6)
      ;
      if (*uStack_1f == cVar2) {
        uStack_1f = (byte *)CONCAT11(bStack_f + param_3 + CARRY1(bStack_e,param_4),
                                     bStack_e + param_4);
        uVar4 = *uStack_1f;
      }
      else {
        uStack_1f = (byte *)CONCAT11((bStack_f - (bStack_e == 0)) + param_3 +
                                     CARRY1(bStack_e - 1,param_4),(bStack_e - 1) + param_4);
        local_12 = *uStack_1f;
        FUN_f230();
        FUN_f17e();
        uStack_1f = (byte *)CONCAT11((bStack_f - (bStack_e == 0)) + param_3 +
                                     CARRY1(bStack_e - 1,param_4),(bStack_e - 1) + param_4);
        DAT_0063 = *uStack_1f;
        DAT_0060 = (char)DAT_0063 >> 7;
        DAT_0061 = DAT_0060;
        DAT_0062 = DAT_0060;
        FUN_f17e();
        uStack_1f = (byte *)CONCAT11((bStack_f - (bStack_e == 0)) + param_5 +
                                     CARRY1(bStack_e - 1,param_6),(bStack_e - 1) + param_6);
        DAT_0063 = *uStack_1f;
        DAT_0062 = 0;
        DAT_0061 = 0;
        DAT_0060 = 0;
        FUN_f17e();
        uStack_1f = (byte *)CONCAT11(bStack_f + param_5 + CARRY1(bStack_e,param_6),
                                     bStack_e + param_6);
        DAT_0063 = *uStack_1f;
        DAT_0062 = 0;
        DAT_0061 = 0;
        DAT_0060 = 0;
        FUN_f159();
        FUN_f17e();
        uStack_1f = (byte *)CONCAT11((bStack_f - (bStack_e == 0)) + param_5 +
                                     CARRY1(bStack_e - 1,param_6),(bStack_e - 1) + param_6);
        DAT_0063 = *uStack_1f;
        DAT_0062 = 0;
        DAT_0061 = 0;
        DAT_0060 = 0;
        sVar5 = FUN_f17e();
        DAT_0063 = *(uint8_t *)(sVar5 + 0x21);
        DAT_0062 = 0;
        DAT_0061 = 0;
        DAT_0060 = 0;
        FUN_f159();
        uVar3 = FUN_f0b4();
        uVar3 = div32_wrap(uVar3);
        add32_acc(uVar3,acStack_15);
        uVar4 = DAT_0063;
      }
    }
    else {
      uStack_1f = (byte *)CONCAT11(cStack_b + param_3 + CARRY1(bStack_a,param_4),bStack_a + param_4)
      ;
      uVar4 = *uStack_1f;
    }
  }
  else {
    uVar4 = *(uint8_t *)CONCAT11(param_3,param_4);
  }
  return uVar4;
}



undefined1 adc_read_channel(byte param_1)

{
  IO_ADSCR_003C = param_1;
  do {
  } while ((param_1 & 0x80) == 0);
  return IO_ADR_003D;
}



void adc_sample_all(void)

{
  adc_latch[1] = adc_read_channel(2);
  adc_latch[2] = adc_read_channel(4);
  adc_latch[3] = adc_read_channel(6);
  adc_latch[4] = adc_read_channel(1);
  adc_latch[5] = adc_read_channel(3);
  adc_latch[0] = adc_read_channel(7);
  adc_latch[6] = adc_read_channel(9);
  return;
}



undefined2 checksum_add16(byte param_1,char param_2,byte param_3)

{
  undefined1 auStack_2 [2];
  
  return CONCAT11((char)((ushort)auStack_2 >> 8),param_2 + -1 + CARRY1(~param_1,param_3));
}



void cal_table_checksum(void)

{
  byte bVar1;
  byte *pbVar2;
  undefined2 uVar3;
  char cVar4;
  undefined1 uStack_3;
  undefined1 uStack_2;
  undefined1 local_1;
  
  DAT_008b = '\x01';
  DAT_008c = 0x23;
  local_1 = -0x24;
  cVar4 = '\0';
  uStack_3 = 0;
  uStack_2 = '\0';
  do {
    pbVar2 = (byte *)CONCAT11(local_1,cVar4);
    cVar4 = cVar4 + '\x01';
    if (cVar4 == '\0') {
      local_1 = local_1 + '\x01';
    }
    bVar1 = *pbVar2;
    uVar3 = checksum_add16(bVar1,DAT_008b,DAT_008c);
    DAT_008b = (char)uVar3;
    uStack_2 = uStack_2 + '\x01';
    if (uStack_2 == '\0') {
      uStack_3 = uStack_3 + 1;
    }
    DAT_008c = bVar1;
  } while (uStack_3 < 0x20);
  local_1 = -1;
  cVar4 = -0x24;
  uStack_3 = 0;
  uStack_2 = 0;
  do {
    pbVar2 = (byte *)CONCAT11(local_1,cVar4);
    cVar4 = cVar4 + '\x01';
    if (cVar4 == '\0') {
      local_1 = local_1 + '\x01';
    }
    bVar1 = *pbVar2;
    uVar3 = checksum_add16(bVar1,DAT_008b,DAT_008c);
    DAT_008c = bVar1;
    DAT_008b = (char)uVar3;
    uStack_2 = uStack_2 + 1;
    if (uStack_2 == 0) {
      uStack_3 = uStack_3 + 1;
    }
  } while (uStack_3 < (uStack_2 < 0x24));
  return;
}



void release_fault_output(void)

{
  if (throttle_status_level < TSL_FAULT) {
    IO_PTD_0003 = IO_PTD_0003 & 0xef;
  }
  return;
}



void enter_fault_state(void)

{
  if (throttle_status_level < TSL_FAULT) {
    throttle_status_level = TSL_FAULT;
  }
  IO_PTD_0003 = IO_PTD_0003 | 0x10;
  return;
}



void release_shutdown_output(void)

{
  if (throttle_status_level < TSL_SHUTDOWN) {
    IO_PTD_0003 = IO_PTD_0003 | 8;
  }
  return;
}



void enter_shutdown_state(void)

{
  if (throttle_status_level < TSL_SHUTDOWN) {
    throttle_status_level = TSL_SHUTDOWN;
  }
  IO_PTD_0003 = IO_PTD_0003 & 0xf7;
  return;
}



void clear_debounce_counters(void)

{
  debounce_monitor4 = 0;
  debounce_monitor5 = 0;
  debounce_monitor6 = 0;
  debounce_crosscheck = 0;
  debounce_ch2_run = 0;
  debounce_ch7_shutdown = 0;
  return;
}



void update_debounce_peaks(void)

{
  if (debounce_peak_ch2run < debounce_ch2_run) {
    debounce_peak_ch2run = debounce_ch2_run;
  }
  if (debounce_peak_monitor4 < debounce_monitor4) {
    debounce_peak_monitor4 = debounce_monitor4;
  }
  if (debounce_peak_monitor5 < debounce_monitor5) {
    debounce_peak_monitor5 = debounce_monitor5;
  }
  if (debounce_peak_monitor6 < debounce_monitor6) {
    debounce_peak_monitor6 = debounce_monitor6;
  }
  if (debounce_peak_crosscheck < debounce_crosscheck) {
    debounce_peak_crosscheck = debounce_crosscheck;
  }
  return;
}



void reset_monitor_state(void)

{
  byte bVar1;
  
  cal_table_checksum();
  rx_cmd_id = 0;
  rx_cal_sel = 0;
  commanded_position_offset = 0;
  throttle_status_level = TSL_INIT;
  status_flags = 0;
  clear_debounce_counters();
  mode_timeout_hi = 0;
  mode_timeout_lo = 0;
  monitor4_timeout_hi = 0;
  monitor4_timeout_lo = 0;
  monitor5_timeout_hi = 0;
  monitor5_timeout_lo = 0;
  armed_mode = 1;
  armed_monitor4 = 1;
  armed_monitor5 = 1;
  armed_monitor6 = 1;
  handshake_countdown = CAL_handshake_init_count;
  release_shutdown_output();
  release_fault_output();
  adc_sample_all();
  DAT_0103 = 0x1a;
  DAT_007a = 0;
  DAT_0079 = 0x22;
  bVar1 = 0;
  do {
    (&DAT_0104)[bVar1] = DAT_0103;
    bVar1 = bVar1 + 1;
  } while (bVar1 < 0x20);
  debounce_peak_ch2run = 0;
  debounce_peak_monitor4 = 0;
  debounce_peak_monitor5 = 0;
  debounce_peak_monitor6 = 0;
  debounce_peak_crosscheck = 0;
  return;
}



void compute_position_scaled(void)

{
  undefined1 uVar1;
  
  if (DAT_0082 == '\x03') {
    computed_position._0_1_ = DAT_0087;
    computed_position._1_1_ = DAT_0088;
    FUN_f21f();
    FUN_f189();
    uVar1 = FUN_f17e();
    DAT_0063 = 0x10;
    DAT_0062 = 0x5e;
    DAT_0061 = 0x5f;
    DAT_0060 = 0;
    div32_wrap(uVar1);
    if (1 < DAT_0062 && (DAT_0063 < 0x58) <= (byte)(DAT_0062 - 2)) {
      computed_position._0_1_ = DAT_0062;
      computed_position._1_1_ = DAT_0063;
      return;
    }
  }
  computed_position._1_1_ = 0;
  computed_position._0_1_ = 0;
  return;
}



// crosscheck_lookup_ch1: expected_ch2 = table_interp(throttle_pos_ch1) using
// axis CAL_crosscheck_ch1_axis (0xDC22) and data CAL_crosscheck_ch2_data (0xDC12).

void crosscheck_lookup_ch1(void)

{
  table_interp(0x10,throttle_pos_ch1,0xdc,0x12,0xdc,0x22);
  return;
}



// normalize_tps_signal: rescale a raw ADC input to 0..255 between two 16-bit
// breakpoints (lo,hi). Saturates 0x00 below lo and 0xFF above hi; linear between.
// Breakpoints come from the linearization table at 0xDC00.

undefined1 normalize_tps_signal(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5)

{
  byte in_X;
  undefined1 uStack_2;
  
  if (in_X < param_4 || (byte)(in_X - param_4) < (param_1 < param_5)) {
    if (param_2 < in_X || (byte)(param_2 - in_X) < (param_3 < param_1)) {
      math_acc_ext = (in_X - param_2) - (param_1 < param_3);
      mul8_acc(param_1 - param_3);
      uStack_2 = mul8_acc();
      if (math_acc_ext != '\0') {
        uStack_2 = 0xff;
      }
    }
    else {
      uStack_2 = 0;
    }
  }
  else {
    uStack_2 = 0xff;
  }
  return uStack_2;
}



// linearize_tps_channels: produce throttle_pos_ch1/ch2 (0..255) from the raw TPS
// ADC tracks. PRIMARY vs ALT breakpoint pair per channel is selected by rx_cal_sel.
// ch2 is clamped to CAL_ch2_position_max (table[8]=0xDC08).

void linearize_tps_channels(void)

{
  if ((rx_cal_sel & RXCAL_CH1_ALT) == 0) {
    throttle_pos_ch1 =
         normalize_tps_signal
                   (adc_latch[4],CAL_tps_mode_calibration_for_linearization[0x10],
                    CAL_tps_mode_calibration_for_linearization[0x11],
                    CAL_tps_mode_calibration_for_linearization[0xe],
                    CAL_tps_mode_calibration_for_linearization[0xf]);
    status_flags = status_flags & ~SF_CH1_CAL_SEL;
  }
  else {
    throttle_pos_ch1 =
         normalize_tps_signal
                   (adc_latch[3],CAL_tps_mode_calibration_for_linearization[0xc],
                    CAL_tps_mode_calibration_for_linearization[0xd],
                    CAL_tps_mode_calibration_for_linearization[10],
                    CAL_tps_mode_calibration_for_linearization[0xb]);
    status_flags = status_flags | SF_CH1_CAL_SEL;
  }
  if ((rx_cal_sel & RXCAL_CH2_ALT) == 0) {
    throttle_pos_ch2 =
         normalize_tps_signal
                   (adc_latch[2],CAL_tps_mode_calibration_for_linearization[6],
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
                   (adc_latch[1],CAL_tps_mode_calibration_for_linearization[2],
                    CAL_tps_mode_calibration_for_linearization[3],
                    CAL_tps_mode_calibration_for_linearization[0],
                    CAL_tps_mode_calibration_for_linearization[1]);
    status_flags = status_flags | SF_CH2_CAL_SEL;
  }
  return;
}



// monitor_crosscheck: dual-track plausibility (states 1-3, 7). Computes a reference
// ch2 from ch1 via the transfer table + bias/offset, slews it into
// crosscheck_ch2_reference, then -- only while throttle_pos_ch1 < CAL ch1 gate
// (table[9]=0xDC09=178) -- faults if throttle_pos_ch2 exceeds the reference for
// CAL_debounce_crosscheck_limit (0xDC61) consecutive samples.

void monitor_crosscheck(void)

{
  bool bVar1;
  byte bVar2;
  undefined1 uVar3;
  char acStack_9 [4];
  char local_5;
  byte local_4;
  byte bStack_3;
  undefined2 local_2;
  
  local_2 = (ushort)CAL_crosscheck_pos_threshold * 10;
  local_4 = crosscheck_lookup_ch1();
  local_5 = '\0';
  if (computed_position._0_1_ < local_2._0_1_ ||
      (byte)(computed_position._0_1_ - local_2._0_1_) < ((byte)computed_position < (byte)local_2)) {
    bVar2 = CAL_crosscheck_ch2_bias + local_4;
    local_5 = CARRY1(CAL_crosscheck_ch2_bias,local_4);
    local_4 = bVar2 + CAL_crosscheck_ch2_offset;
    if (CARRY1(bVar2,CAL_crosscheck_ch2_offset)) {
      local_5 = local_5 + '\x01';
    }
  }
  else {
                    // DAT_008d is always 1
    if (DAT_008d != '\0') {
      if (computed_position._0_1_ < 0x1f ||
          (byte)(computed_position._0_1_ - 0x1f) < ((byte)computed_position < 0xe0)) {
        bStack_3 = (byte)((byte)((byte)((byte)((byte)computed_position >> 1 |
                                              computed_position._0_1_ << 7) >> 1 |
                                       (computed_position._0_1_ >> 1) << 7) >> 1 |
                                (computed_position._0_1_ >> 2) << 7) >> 1 |
                         (computed_position._0_1_ >> 3) << 7) >> 1 |
                   (computed_position._0_1_ >> 4) << 7;
      }
      else {
        bStack_3 = 0xff;
      }
                    // CAL_crosscheck2_pos_axis (0xDC32) and CAL_crosscheck2_data (0xDC42) are the
                    // two halves of one lookup table inside the throttle safety monitor:
                    // 
                    // - CAL_crosscheck2_pos_axis = the table's input breakpoints (the X-axis).
                    // - CAL_crosscheck2_data = the table's output values (the Y-axis), one per
                    // breakpoint. The monitor interpolates between them.
                    // 
                    // What the table is for
                    // 
                    // The HC08 chip measures throttle position two independent ways:
                    // 1. an analog voltage track (throttle_pos_ch2), and
                    // 2. a PWM/pulse-width-encoded position signal (computed_position).
                    // 
                    // This table answers one question: "Given the PWM-measured position, how far
                    // open is the analog track allowed to read?"
                    // 
                    // - You look up the PWM position in the axis (DC32).
                    // - You read out the corresponding expected/allowed analog ch2 from the data
                    // (DC42).
                    // - A fixed tolerance is added (CAL_crosscheck_ch2_offset 0xDC52), giving the
                    // ceiling stored in crosscheck_ch2_reference.
                    // - If the analog ch2 ever reads higher than that ceiling (for the debounced
                    // count), the monitor declares a fault and pulls the throttle to a safe state.
                    // 
                    // In plain terms: it's the agreement curve between the two redundant throttle
                    // sensors in the low‑to‑mid throttle range. It's a safety cross‑check,
                    // not a control knob — it commands nothing, it only sets fault thresholds.
                    // (On the GT430 it's always active in the low region, because the enable bit is
                    // calibrated on, as we traced.) Above the high‑throttle split point the
                    // monitor switches to the other curve, DC22/DC12.
                    // 
                    // When you should change them
                    // 
                    // Change them only if the physical or numeric relationship between the PWM
                    // position signal and the analog ch2 track changes, or to retune the safety
                    // tolerance:
                    // 
                    // 1. Different throttle-body / TPS hardware — a new sensor, linkage, or
                    // PWM-position source shifts how the two signals relate. The curve must be
                    // re-mapped to the new parts.
                    // 2. You change the HC08's analog linearization (the 0xDC00 table, which sets
                    // ch2's 0–255 scaling) → the data column (DC42) must be re-gridded so the
                    // allowed values still correspond to real positions.
                    // 3. The PWM-position scaling changes (the capture/divisor in
                    // compute_position_scaled, or the encoding of the source signal) → the axis
                    // (DC32) breakpoints must be re-gridded.
                    // 4. You change the ECU's TPS scaling / throttle authority such that the
                    // steady‑state positions the two sensors report no longer match what this
                    // curve assumes → re-grid to stay consistent (same coupling principle as the
                    // main DC22/DC12 table).
                    // 5. You need to tighten or loosen the cross-check tolerance. Note the cleaner
                    // knobs for overall tolerance are the scalars CAL_crosscheck_ch2_offset
                    // (0xDC52) and CAL_crosscheck_ch2_bias (0xDC69), plus the debounce limit
                    // CAL_debounce_crosscheck_limit (0xDC61). Use DC42 when the tolerance needs to
                    // vary with position (shape the band), not as a global offset.
                    // 
                    // Important caveats (this is a safety function)
                    // 
                    // - There are two ways to get it wrong, both bad:
                    //   - Too low / too tight → the throttle trips into limp/shutdown during
                    // normal driving (nuisance faults).
                    //   - Too high / too loose → the monitor won't catch a genuine throttle
                    // over‑travel (the failure it exists to prevent).
                    // - The DC42 curve must envelope every legitimate operating point with margin:
                    // at each PWM position, the allowed ch2 (plus offset) has to sit above the
                    // highest ch2 that ever occurs there normally — otherwise good driving looks
                    // like a fault.
                    // - Don't touch these to change throttle feel or response; that's the ECU's
                    // CAL_tps*/CAL_tpssmooth_* tables. These only move fault thresholds.
                    // - Any change should be validated across the full range (cold/warm, idle to
                    // WOT) before trusting it, and ideally kept consistent with its sibling table
                    // DC22/DC12.
                    // 
                    // One honesty note: I haven't reverse-engineered the exact fixed-point scaling
                    // applied to the DC42 lookup result before the offset is added (there's a
                    // multiply/normalize step in monitor_crosscheck), so if you intend to compute
                    // new values numerically rather than by re-mapping proportionally to a hardware
                    // change, I'd want to nail that scaling down first. I can do that if you plan
                    // to edit the values directly.
      table_interp(16,bStack_3,0xdc,0x42,0xdc,0x32);
      math_acc_ext = local_5;
      mul8_acc(local_4);
      local_4 = mul8_acc();
      local_5 = math_acc_ext;
    }
    bVar2 = CAL_crosscheck_ch2_offset + local_4;
    bVar1 = CARRY1(CAL_crosscheck_ch2_offset,local_4);
    local_4 = bVar2;
    if (bVar1) {
      local_5 = local_5 + '\x01';
    }
  }
  if (local_5 != '\0') {
    local_4 = 0xff;
    local_5 = '\0';
  }
  if (local_5 == '\0' && (crosscheck_ch2_reference < local_4) <= (byte)-local_5) {
    math_acc_ext = local_5;
    mul8_acc(local_4);
    FUN_f218();
    FUN_f17e();
    FUN_f230();
    uVar3 = FUN_f0b4();
    uVar3 = div32_wrap(uVar3);
    add32_acc(uVar3,acStack_9);
    FUN_f17e();
    uVar3 = FUN_f173();
    div32_wrap(uVar3);
    crosscheck_ch2_reference = DAT_0063;
  }
  else {
    crosscheck_ch2_reference = local_4;
    FUN_f21f();
    FUN_f17e();
  }
  if (throttle_pos_ch1 < CAL_tps_mode_calibration_for_linearization[9]) {
    if (crosscheck_ch2_reference < throttle_pos_ch2) {
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



// monitor_ch2_run_limit: RUN state. Faults if throttle_pos_ch2 exceeds the absolute
// CAL_ch2_run_limit (0xDC53), debounced to CAL_debounce_ch2run_limit (0xDC62).

void monitor_ch2_run_limit(void)

{
  crosscheck_ch2_reference = CAL_ch2_run_limit;
  if (CAL_ch2_run_limit < throttle_pos_ch2) {
    if (debounce_ch2_run < CAL_debounce_ch2run_limit) {
      debounce_ch2_run = debounce_ch2_run + 1;
      return;
    }
    debounce_ch2_run = CAL_debounce_ch2run_limit;
    enter_fault_state();
  }
  else {
    if ((debounce_ch2_run != 0) && (debounce_ch2_run < CAL_debounce_ch2run_limit)) {
      debounce_ch2_run = debounce_ch2_run - 1;
      return;
    }
    if (debounce_ch2_run == 0) {
      release_fault_output();
      return;
    }
  }
  return;
}



// monitor_selftest_4: cmd-4 self-test. Injects commanded_position_offset + 
// CAL_monitor4_offset (0xDC57), checks response within CAL_monitor4_timeout, 
// debounce CAL_debounce_monitor4_limit; failure -> TSL_REARM.

void monitor_selftest_4(void)

{
  bool bVar1;
  undefined1 uVar2;
  byte bVar3;
  char acStack_5 [4];
  bool local_1;
  
  bVar3 = CAL_monitor4_offset + commanded_position_offset;
  bVar1 = CARRY1(CAL_monitor4_offset,commanded_position_offset);
  if (bVar1) {
    bVar3 = 0xff;
  }
  local_1 = !bVar1 && bVar1;
  if (!bVar1 && bVar1 || (byte)-local_1 < (CAL_monitor4_max < bVar3)) {
    local_1 = false;
    bVar3 = CAL_monitor4_max;
  }
  if (local_1 == false && (crosscheck_ch2_reference < bVar3) <= (byte)-local_1) {
    math_acc_ext = local_1;
    mul8_acc(bVar3);
    FUN_f218();
    FUN_f17e();
    FUN_f230();
    uVar2 = FUN_f0b4();
    uVar2 = div32_wrap(uVar2);
    add32_acc(uVar2,acStack_5);
    FUN_f17e();
    uVar2 = FUN_f173();
    div32_wrap(uVar2);
    crosscheck_ch2_reference = DAT_0063;
  }
  else {
    crosscheck_ch2_reference = bVar3;
    FUN_f21f();
    FUN_f17e();
  }
  math_acc_ext = CARRY1(commanded_position_offset,CAL_monitor4_offset);
  if (((byte)math_acc_ext <
       ((byte)(commanded_position_offset + CAL_monitor4_offset) < throttle_pos_ch2)) ||
     (math_acc_ext = false, CAL_monitor4_max < throttle_pos_ch2)) {
    if (debounce_monitor4 < CAL_debounce_monitor4_limit) {
      debounce_monitor4 = debounce_monitor4 + 1;
    }
    else {
      debounce_monitor4 = CAL_debounce_monitor4_limit;
      armed_monitor4 = 0;
      throttle_status_level = TSL_REARM;
    }
  }
  else if ((debounce_monitor4 != 0) && (debounce_monitor4 < CAL_debounce_monitor4_limit)) {
    debounce_monitor4 = debounce_monitor4 - 1;
  }
  monitor4_timeout_lo = monitor4_timeout_lo + 1;
  if (monitor4_timeout_lo == 0) {
    monitor4_timeout_hi = monitor4_timeout_hi + 1;
  }
  if (monitor4_timeout_hi < CAL_monitor4_timeout_hi ||
      (byte)(monitor4_timeout_hi - CAL_monitor4_timeout_hi) <
      (monitor4_timeout_lo < CAL_monitor4_timeout_lo)) {
    if (rx_cmd_id == CMD_MONITOR_4) {
      return;
    }
  }
  else {
    armed_monitor4 = 0;
  }
  throttle_status_level = TSL_REARM;
  return;
}



// monitor_selftest_5: cmd-5 self-test (CAL_monitor5_offset 0xDC5B, timeout 0xDC59).

void monitor_selftest_5(void)

{
  bool bVar1;
  undefined1 uVar2;
  byte bVar3;
  char acStack_5 [4];
  bool local_1;
  
  bVar3 = CAL_monitor5_offset + commanded_position_offset;
  bVar1 = CARRY1(CAL_monitor5_offset,commanded_position_offset);
  if (bVar1) {
    bVar3 = 0xff;
  }
  local_1 = !bVar1 && bVar1;
  if (!bVar1 && bVar1 || (byte)-local_1 < (crosscheck_ch2_reference < bVar3)) {
    crosscheck_ch2_reference = bVar3;
    FUN_f21f();
    FUN_f17e();
  }
  else {
    math_acc_ext = local_1;
    mul8_acc(bVar3);
    FUN_f218();
    FUN_f17e();
    FUN_f230();
    uVar2 = FUN_f0b4();
    uVar2 = div32_wrap(uVar2);
    add32_acc(uVar2,acStack_5);
    FUN_f17e();
    uVar2 = FUN_f173();
    div32_wrap(uVar2);
    crosscheck_ch2_reference = DAT_0063;
  }
  math_acc_ext = CARRY1(commanded_position_offset,CAL_monitor5_offset);
  if ((byte)math_acc_ext <
      ((byte)(commanded_position_offset + CAL_monitor5_offset) < throttle_pos_ch2)) {
    if (debounce_monitor5 < CAL_debounce_monitor5_limit) {
      debounce_monitor5 = debounce_monitor5 + 1;
    }
    else {
      debounce_monitor5 = CAL_debounce_monitor5_limit;
      armed_monitor5 = 0;
      throttle_status_level = TSL_REARM;
    }
  }
  else if ((debounce_monitor5 != 0) && (debounce_monitor5 < CAL_debounce_monitor5_limit)) {
    debounce_monitor5 = debounce_monitor5 - 1;
  }
  monitor5_timeout_lo = monitor5_timeout_lo + 1;
  if (monitor5_timeout_lo == 0) {
    monitor5_timeout_hi = monitor5_timeout_hi + 1;
  }
  if (monitor5_timeout_hi < CAL_monitor5_timeout_hi ||
      (byte)(monitor5_timeout_hi - CAL_monitor5_timeout_hi) <
      (monitor5_timeout_lo < CAL_monitor5_timeout_lo)) {
    if (rx_cmd_id == CMD_MONITOR_5) {
      return;
    }
  }
  else {
    armed_monitor5 = 0;
  }
  throttle_status_level = TSL_REARM;
  return;
}



// compare_ch3_limit: adc_latch[5] vs CAL_ch3_limit (0xDC64), sense CAL_ch3_polarity.

bool compare_ch3_limit(void)

{
  bool bVar1;
  
  bVar1 = CAL_ch3_limit <= adc_latch[5];
  if (CAL_ch3_polarity == '\0') {
    bVar1 = !bVar1;
  }
  return bVar1;
}



// compare_ch9_limit: adc_latch[6] vs CAL_ch9_limit (0xDC65), sense CAL_ch9_polarity;
// disabled by rx_cal_sel RXCAL_DISABLE_CH9.

bool compare_ch9_limit(void)

{
  bool bVar1;
  
  bVar1 = CAL_ch9_limit <= adc_latch[6];
  if (CAL_ch9_polarity == '\0') {
    bVar1 = !bVar1;
  }
  if ((rx_cal_sel & RXCAL_DISABLE_CH9) != 0) {
    bVar1 = false;
  }
  return bVar1;
}



// monitor_selftest_6: cmd-6 self-test (CAL_monitor6_offset 0xDC5C) plus the ch3/ch9
// hardware-limit checks (compare_ch3_limit / compare_ch9_limit).

void monitor_selftest_6(void)

{
  undefined1 uVar1;
  bool bVar2;
  byte bVar3;
  char acStack_5 [2];
  undefined1 uStack_3;
  byte bStack_2;
  bool local_1;
  
  bVar3 = CAL_monitor6_offset + commanded_position_offset;
  bVar2 = CARRY1(CAL_monitor6_offset,commanded_position_offset);
  if (bVar2) {
    bVar3 = 0xff;
  }
  local_1 = !bVar2 && bVar2;
  if (!bVar2 && bVar2 || (byte)-local_1 < (crosscheck_ch2_reference < bVar3)) {
    crosscheck_ch2_reference = bVar3;
    FUN_f21f();
    FUN_f17e();
  }
  else {
    math_acc_ext = local_1;
    mul8_acc(bVar3);
    FUN_f218();
    FUN_f17e();
    FUN_f230();
    uVar1 = FUN_f0b4();
    uVar1 = div32_wrap(uVar1);
    add32_acc(uVar1,acStack_5);
    FUN_f17e();
    uVar1 = FUN_f173();
    div32_wrap(uVar1);
    crosscheck_ch2_reference = DAT_0063;
  }
  bStack_2 = CAL_monitor6_offset;
  uStack_3 = 0;
  math_acc_ext = CARRY1(commanded_position_offset,CAL_monitor6_offset);
  if ((byte)math_acc_ext <
      ((byte)(commanded_position_offset + CAL_monitor6_offset) < throttle_pos_ch2)) {
    if (debounce_monitor6 < CAL_debounce_monitor6_limit) {
      debounce_monitor6 = debounce_monitor6 + 1;
    }
    else {
      debounce_monitor6 = CAL_debounce_monitor6_limit;
      armed_monitor6 = 0;
      throttle_status_level = TSL_REARM;
    }
  }
  else {
    bVar2 = compare_ch3_limit();
    if (bVar2) {
      armed_monitor6 = 0;
      throttle_status_level = TSL_REARM;
    }
    else {
      bVar2 = compare_ch9_limit();
      if (bVar2) {
        armed_monitor6 = 0;
        throttle_status_level = TSL_REARM;
      }
      else if (rx_cmd_id == CMD_MONITOR_6) {
        if ((debounce_monitor6 != 0) && (debounce_monitor6 < CAL_debounce_monitor6_limit)) {
          debounce_monitor6 = debounce_monitor6 - 1;
        }
      }
      else {
        throttle_status_level = TSL_REARM;
      }
    }
  }
  return;
}



// monitor_ch7_shutdown: adc_latch[0] (ch7) vs CAL_ch7_shutdown_limit (0xDC5D);
// over-limit for CAL_debounce_ch7_limit (0xDC63) -> enter_shutdown_state.

void monitor_ch7_shutdown(void)

{
  if (CAL_ch7_shutdown_limit < adc_latch[0]) {
    if (debounce_ch7_shutdown < CAL_debounce_ch7_limit) {
      debounce_ch7_shutdown = debounce_ch7_shutdown + 1;
      return;
    }
    debounce_ch7_shutdown = CAL_debounce_ch7_limit;
    enter_shutdown_state();
  }
  else {
    if ((debounce_ch7_shutdown != 0) && (debounce_ch7_shutdown < CAL_debounce_ch7_limit)) {
      debounce_ch7_shutdown = debounce_ch7_shutdown - 1;
      return;
    }
    if (debounce_ch7_shutdown == 0) {
      release_shutdown_output();
      return;
    }
  }
  return;
}



void control_monitor_tick(void)

{
  undefined1 extraout_A;
  short sVar1;
  
  adc_sample_all();
  compute_position_scaled();
  linearize_tps_channels();
  if (DAT_0103 == '\x1a') {
    status_flags = status_flags & ~SF_MODE;
  }
  else {
    status_flags = status_flags | SF_MODE;
  }
  if (throttle_status_level < TSL_MAX) {
    sVar1 = dispatch_by_status(throttle_status_level);
    *(undefined1 *)(sVar1 + 0x8b) = extraout_A;
    *(undefined1 *)(sVar1 + 0xa1) = extraout_A;
    *(undefined1 *)(sVar1 + 0xa6) = extraout_A;
    *(undefined1 *)(sVar1 + 0xab) = extraout_A;
    *(undefined1 *)(sVar1 + 0xb0) = extraout_A;
    *(undefined1 *)(sVar1 + 0xb5) = extraout_A;
    *(undefined1 *)(sVar1 + 0xba) = extraout_A;
    *(undefined1 *)(sVar1 + 0xbf) = extraout_A;
    *(undefined1 *)(sVar1 + 0xfe) = extraout_A;
  }
  if (throttle_status_level < TSL_SHUTDOWN) {
    if ((((debounce_monitor4 != '\0') || (debounce_monitor5 != '\0')) || (debounce_monitor6 != '\0')
        ) || ((debounce_crosscheck != '\0' || (debounce_ch2_run != '\0')))) {
      status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
      goto LAB_e853;
    }
  }
  else if (debounce_ch7_shutdown != '\0') {
    status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
    goto LAB_e853;
  }
  status_flags = status_flags & ~SF_DEBOUNCE_ACTIVE;
LAB_e853:
  update_debounce_peaks();
  return;
}



void handler_state_init(void)

{
  if (rx_cmd_id == CMD_REARM) {
    throttle_status_level = rx_cmd_id;
  }
  if (handshake_countdown == '\0') {
    throttle_status_level = TSL_REARM;
  }
  if (throttle_status_level < TSL_SHUTDOWN) {
    if ((((debounce_monitor4 != '\0') || (debounce_monitor5 != '\0')) || (debounce_monitor6 != '\0')
        ) || ((debounce_crosscheck != '\0' || (debounce_ch2_run != '\0')))) {
      status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
      goto LAB_e853;
    }
  }
  else if (debounce_ch7_shutdown != '\0') {
    status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
    goto LAB_e853;
  }
  status_flags = status_flags & ~SF_DEBOUNCE_ACTIVE;
LAB_e853:
  update_debounce_peaks();
  return;
}



void handler_state_mode1(void)

{
  monitor_crosscheck();
  if (throttle_status_level < TSL_SHUTDOWN) {
    if ((((debounce_monitor4 != '\0') || (debounce_monitor5 != '\0')) || (debounce_monitor6 != '\0')
        ) || ((debounce_crosscheck != '\0' || (debounce_ch2_run != '\0')))) {
      status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
      goto LAB_e853;
    }
  }
  else if (debounce_ch7_shutdown != '\0') {
    status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
    goto LAB_e853;
  }
  status_flags = status_flags & ~SF_DEBOUNCE_ACTIVE;
LAB_e853:
  update_debounce_peaks();
  return;
}



void handler_state_mode2(void)

{
  monitor_crosscheck();
  if (throttle_status_level < TSL_SHUTDOWN) {
    if ((((debounce_monitor4 != '\0') || (debounce_monitor5 != '\0')) || (debounce_monitor6 != '\0')
        ) || ((debounce_crosscheck != '\0' || (debounce_ch2_run != '\0')))) {
      status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
      goto LAB_e853;
    }
  }
  else if (debounce_ch7_shutdown != '\0') {
    status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
    goto LAB_e853;
  }
  status_flags = status_flags & ~SF_DEBOUNCE_ACTIVE;
LAB_e853:
  update_debounce_peaks();
  return;
}



void handler_state_mode3(void)

{
  monitor_crosscheck();
  if (throttle_status_level < TSL_SHUTDOWN) {
    if ((((debounce_monitor4 != '\0') || (debounce_monitor5 != '\0')) || (debounce_monitor6 != '\0')
        ) || ((debounce_crosscheck != '\0' || (debounce_ch2_run != '\0')))) {
      status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
      goto LAB_e853;
    }
  }
  else if (debounce_ch7_shutdown != '\0') {
    status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
    goto LAB_e853;
  }
  status_flags = status_flags & ~SF_DEBOUNCE_ACTIVE;
LAB_e853:
  update_debounce_peaks();
  return;
}



void handler_state_monitor4(void)

{
  monitor_selftest_4();
  if (throttle_status_level < TSL_SHUTDOWN) {
    if ((((debounce_monitor4 != '\0') || (debounce_monitor5 != '\0')) || (debounce_monitor6 != '\0')
        ) || ((debounce_crosscheck != '\0' || (debounce_ch2_run != '\0')))) {
      status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
      goto LAB_e853;
    }
  }
  else if (debounce_ch7_shutdown != '\0') {
    status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
    goto LAB_e853;
  }
  status_flags = status_flags & ~SF_DEBOUNCE_ACTIVE;
LAB_e853:
  update_debounce_peaks();
  return;
}



void handler_state_monitor5(void)

{
  monitor_selftest_5();
  if (throttle_status_level < TSL_SHUTDOWN) {
    if ((((debounce_monitor4 != '\0') || (debounce_monitor5 != '\0')) || (debounce_monitor6 != '\0')
        ) || ((debounce_crosscheck != '\0' || (debounce_ch2_run != '\0')))) {
      status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
      goto LAB_e853;
    }
  }
  else if (debounce_ch7_shutdown != '\0') {
    status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
    goto LAB_e853;
  }
  status_flags = status_flags & ~SF_DEBOUNCE_ACTIVE;
LAB_e853:
  update_debounce_peaks();
  return;
}



void handler_state_monitor6(void)

{
  monitor_selftest_6();
  if (throttle_status_level < TSL_SHUTDOWN) {
    if ((((debounce_monitor4 != '\0') || (debounce_monitor5 != '\0')) || (debounce_monitor6 != '\0')
        ) || ((debounce_crosscheck != '\0' || (debounce_ch2_run != '\0')))) {
      status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
      goto LAB_e853;
    }
  }
  else if (debounce_ch7_shutdown != '\0') {
    status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
    goto LAB_e853;
  }
  status_flags = status_flags & ~SF_DEBOUNCE_ACTIVE;
LAB_e853:
  update_debounce_peaks();
  return;
}



void handler_state_rearm(void)

{
  if ((rx_cmd_id == CMD_MONITOR_4) && (armed_monitor4 != '\0')) {
    clear_debounce_counters();
    throttle_status_level = TSL_MONITOR_4;
  }
  else if ((rx_cmd_id == CMD_MONITOR_5) && (armed_monitor5 != '\0')) {
    clear_debounce_counters();
    throttle_status_level = TSL_MONITOR_5;
  }
  else if ((rx_cmd_id == CMD_MONITOR_6) && (armed_monitor6 != '\0')) {
    clear_debounce_counters();
    throttle_status_level = TSL_MONITOR_6;
  }
  monitor_crosscheck();
  if (throttle_status_level < TSL_SHUTDOWN) {
    if ((((debounce_monitor4 != '\0') || (debounce_monitor5 != '\0')) || (debounce_monitor6 != '\0')
        ) || ((debounce_crosscheck != '\0' || (debounce_ch2_run != '\0')))) {
      status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
      goto LAB_e853;
    }
  }
  else if (debounce_ch7_shutdown != '\0') {
    status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
    goto LAB_e853;
  }
  status_flags = status_flags & ~SF_DEBOUNCE_ACTIVE;
LAB_e853:
  update_debounce_peaks();
  return;
}



void handler_state_run(void)

{
  monitor_ch2_run_limit();
  if (throttle_status_level < TSL_SHUTDOWN) {
    if ((((debounce_monitor4 != '\0') || (debounce_monitor5 != '\0')) || (debounce_monitor6 != '\0')
        ) || ((debounce_crosscheck != '\0' || (debounce_ch2_run != '\0')))) {
      status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
      goto LAB_e853;
    }
  }
  else if (debounce_ch7_shutdown != '\0') {
    status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
    goto LAB_e853;
  }
  status_flags = status_flags & ~SF_DEBOUNCE_ACTIVE;
LAB_e853:
  update_debounce_peaks();
  return;
}



void handler_state_fault(void)

{
  enter_fault_state();
  monitor_ch7_shutdown();
  if ((rx_cal_sel & RXCAL_FORCE_SHUTDOWN) != 0) {
    enter_shutdown_state();
  }
  if (throttle_status_level < TSL_SHUTDOWN) {
    if ((((debounce_monitor4 != '\0') || (debounce_monitor5 != '\0')) || (debounce_monitor6 != '\0')
        ) || ((debounce_crosscheck != '\0' || (debounce_ch2_run != '\0')))) {
      status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
      goto LAB_e853;
    }
  }
  else if (debounce_ch7_shutdown != '\0') {
    status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
    goto LAB_e853;
  }
  status_flags = status_flags & ~SF_DEBOUNCE_ACTIVE;
LAB_e853:
  update_debounce_peaks();
  return;
}



void handler_state_shutdown(void)

{
  enter_fault_state();
  enter_shutdown_state();
  if (throttle_status_level < TSL_SHUTDOWN) {
    if ((((debounce_monitor4 != '\0') || (debounce_monitor5 != '\0')) || (debounce_monitor6 != '\0')
        ) || ((debounce_crosscheck != '\0' || (debounce_ch2_run != '\0')))) {
      status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
      goto LAB_e853;
    }
  }
  else if (debounce_ch7_shutdown != '\0') {
    status_flags = status_flags | SF_DEBOUNCE_ACTIVE;
    goto LAB_e853;
  }
  status_flags = status_flags & ~SF_DEBOUNCE_ACTIVE;
LAB_e853:
  update_debounce_peaks();
  return;
}



void main_loop(char param_1,ushort param_2)

{
  char extraout_A;
  
  do {
    param_2 = rx_dispatch(param_2);
    if (param_1 != '\0' || (char)param_2 != '\0') {
      comm_timeout = 'd';
      if ((throttle_status_level < TSL_RUN) && (rx_cmd_id == CMD_RUN)) {
        throttle_status_level = TSL_RUN;
      }
      if ((throttle_status_level < TSL_FAULT) && (rx_cmd_id == CMD_FORCE_FAULT)) {
        param_2 = enter_fault_state();
      }
      if (((rx_cmd_id != CMD_MODE_1) && (rx_cmd_id != CMD_MODE_2)) && (rx_cmd_id != CMD_MODE_3)) {
        mode_timeout_hi = 0;
        mode_timeout_lo = 0;
        armed_mode = 1;
      }
      if (rx_cmd_id != CMD_MONITOR_4) {
        monitor4_timeout_hi = 0;
        monitor4_timeout_lo = 0;
        armed_monitor4 = 1;
      }
      if (rx_cmd_id != CMD_MONITOR_5) {
        monitor5_timeout_hi = 0;
        monitor5_timeout_lo = 0;
        armed_monitor5 = 1;
      }
      if (rx_cmd_id != CMD_MONITOR_6) {
        armed_monitor6 = 1;
      }
    }
    if (comm_timeout == '\0') {
      status_flags = status_flags | SF_COMM_LOSS;
      param_2 = enter_fault_state();
    }
    param_1 = tick_due_flag;
    if (tick_due_flag == '\0') {
      tick_due_flag = '\x01';
      param_2 = control_monitor_tick();
      param_1 = extraout_A;
    }
  } while( true );
}



void capture_state_reset(void)

{
  if (DAT_0081 != '\0') {
    DAT_0081 = 0;
    return;
  }
  DAT_0082 = DAT_0081;
  return;
}



undefined1 tim_capture_isr(undefined1 param_1)

{
  undefined1 uVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  
  uVar1 = math_acc_ext;
  if ((IO_TIM_CH_0028 & 0x80) != 0) {
    IO_TIM_CH_0028 = IO_TIM_CH_0028 & 0x7f;
    DAT_0081 = 1;
    if (DAT_0082 == '\0') {
      DAT_0082 = '\x01';
      DAT_0080 = 0xff;
      DAT_0086 = DAT_002a - DAT_008a;
      DAT_0085 = (DAT_0029 - DAT_0089) - (DAT_002a < DAT_008a);
      DAT_0089 = DAT_0029;
      DAT_008a = DAT_002a;
    }
    else if (DAT_0082 == '\x01') {
      DAT_0086 = DAT_002a - DAT_008a;
      DAT_0085 = (DAT_0029 - DAT_0089) - (DAT_002a < DAT_008a);
      DAT_0089 = DAT_0029;
      DAT_008a = DAT_002a;
      DAT_0082 = '\x02';
    }
    else {
      bVar2 = DAT_0087;
      bVar3 = DAT_0088;
      if (DAT_0082 == '\x02') {
        DAT_0084 = DAT_002a - DAT_008a;
        DAT_0083 = (DAT_0029 - DAT_0089) - (DAT_002a < DAT_008a);
        DAT_0089 = DAT_0029;
        DAT_008a = DAT_002a;
        bVar4 = DAT_0085 << 1 | DAT_0086 >> 7;
        if (bVar4 < DAT_0083 ||
            (byte)(bVar4 - DAT_0083) <
            ((byte)(DAT_0086 * '\x02') < DAT_0084 || (byte)(DAT_0086 * '\x02' - DAT_0084) == '\0'))
        {
          DAT_0080 = 0;
          DAT_0082 = '\x03';
        }
      }
      else {
        if (DAT_0082 != '\x03') {
          DAT_0081 = 1;
          DAT_0082 = 0;
          return param_1;
        }
        DAT_0080 = DAT_0080 + 1;
        if (0x43 < DAT_0080) {
          DAT_0080 = 0;
        }
        DAT_0084 = DAT_002a - DAT_008a;
        math_acc_ext = (DAT_0029 - DAT_0089) - (DAT_002a < DAT_008a);
        DAT_0089 = DAT_0029;
        DAT_008a = DAT_002a;
        bVar4 = DAT_0085 << 1 | DAT_0086 >> 7;
        DAT_0083 = math_acc_ext;
        bVar2 = math_acc_ext;
        bVar3 = DAT_0084;
        if (bVar4 < math_acc_ext ||
            (byte)(bVar4 - math_acc_ext) <
            ((byte)(DAT_0086 * '\x02') < DAT_0084 || (byte)(DAT_0086 * '\x02' - DAT_0084) == '\0'))
        {
          if ((DAT_0080 == 0) || (DAT_0080 == 0x22)) {
            bVar3 = mul8_acc();
            DAT_0087 = math_acc_ext;
            bVar2 = DAT_0087;
          }
          else {
            DAT_0082 = '\0';
            bVar2 = DAT_0087;
            bVar3 = DAT_0088;
          }
        }
      }
      DAT_0088 = bVar3;
      DAT_0087 = bVar2;
      DAT_0085 = DAT_0083;
      DAT_0086 = DAT_0084;
    }
  }
  math_acc_ext = uVar1;
  return param_1;
}



void sci_init(void)

{
  DAT_0019 = 2;
  DAT_0013 = 0x40;
  IO_SCC2_0014 = 0x2c;
  DAT_00bc = 0;
  DAT_00bb = 0;
  DAT_00ba = 0;
  DAT_00b6 = 0;
  DAT_00b7 = 0;
  return;
}



undefined1 sci_rx_available(void)

{
  if (DAT_00ba != '\0') {
    return 1;
  }
  return 0;
}



undefined1 sci_rx_read_byte(void)

{
  ushort uVar1;
  
  do {
  } while (DAT_00ba == '\0');
  uVar1 = (ushort)DAT_00bb;
  DAT_00ba = DAT_00ba + -1;
  if (DAT_00bb < 0x1f) {
    DAT_00bb = DAT_00bb + 1;
  }
  else {
    DAT_00bb = '\0';
  }
  return *(undefined1 *)(uVar1 + 0xdd);
}



void sci_tx_start(undefined1 param_1)

{
  DAT_00b8 = param_1;
  DAT_00b9 = 0;
  IO_SCC2_0014 = IO_SCC2_0014 & 0x7f | 0x80;
  return;
}



undefined1 sci_rx_isr(undefined1 param_1)

{
  byte bVar1;
  
  bVar1 = DAT_00bc;
  if (((DAT_0016 & 0x20) != 0) && (DAT_00ba < 0x20)) {
    *(undefined1 *)(DAT_00bc + 0xdd) = DAT_0018;
    if (bVar1 < 0x1f) {
      DAT_00bc = DAT_00bc + 1;
    }
    else {
      DAT_00bc = 0;
    }
    DAT_00ba = DAT_00ba + 1;
  }
  return param_1;
}



ushort rx_frame_parser(byte param_1,ushort param_2)

{
  ushort uVar1;
  undefined1 *puVar2;
  undefined1 uStack_1;
  
  if (DAT_00b6 < 0x14) {
    if (tx_busy_timer == 0) {
      DAT_00b6 = tx_busy_timer;
    }
    tx_busy_timer = 6;
    if (DAT_00b6 == 0) {
      DAT_00b6 = '\x01';
      puVar2 = (undefined1 *)0x0;
      DAT_00a1 = param_1;
      DAT_00a2 = param_1;
    }
    else if (DAT_00b6 == 1) {
      DAT_00b6 = '\x02';
      puVar2 = (undefined1 *)0x0;
      DAT_00a1 = param_1 + DAT_00a1;
      DAT_00a3 = param_1;
    }
    else if ((DAT_00b6 < 2) ||
            (math_acc_ext = DAT_00a2 == 0xff, (byte)math_acc_ext < ((byte)(DAT_00a2 + 1) < DAT_00b6)
            )) {
      math_acc_ext = 0xfd < DAT_00a2;
      puVar2 = (undefined1 *)(ushort)DAT_00b6;
      if (DAT_00b6 != (byte)(DAT_00a2 + 2) || (bool)math_acc_ext) {
        DAT_00b6 = '\0';
      }
      else {
        DAT_00b7 = puVar2[0xa1];
        puVar2[0xa2] = param_1;
        DAT_00b6 = '\0';
        puVar2 = &uStack_1;
      }
    }
    else {
      uVar1 = (ushort)DAT_00b6;
      DAT_00b6 = DAT_00b6 + 1;
      *(byte *)(uVar1 + 0xa2) = param_1;
      puVar2 = (undefined1 *)0x0;
      DAT_00a1 = param_1 + DAT_00a1;
    }
    return (ushort)puVar2 & 0xff00;
  }
  DAT_00ba = 0;
  DAT_00bb = 0;
  DAT_00bc = 0;
  DAT_00b6 = 0;
  return param_2 & 0xff00;
}



void tx_build_frame(byte param_1,byte param_2)

{
  bool bVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  char in_X;
  char *pcVar5;
  undefined2 uStack_9;
  char cStack_7;
  byte local_6;
  char local_3;
  byte local_2;
  
  *(byte *)CONCAT11(in_X,param_1) = param_2;
  uStack_9 = CONCAT11(in_X + CARRY1(param_2,param_1),param_2 + param_1);
  *(undefined1 *)(uStack_9 + 1) = DAT_00b7;
  cVar4 = in_X + CARRY1(param_2,param_1);
  cVar3 = param_2 + param_1 + 2;
  if (0xfd < (byte)(param_2 + param_1)) {
    cVar4 = cVar4 + '\x01';
  }
  *(undefined1 *)CONCAT11(cVar4,cVar3) = 0;
  cStack_7 = '\0';
  local_6 = 0;
  local_3 = in_X;
  local_2 = param_1;
  while (bVar1 = (byte)(param_2 + 1) < local_6, cVar2 = (param_2 == 0xff) - cStack_7,
        (char)(cVar2 - bVar1) < '\0' !=
        (SBORROW1(param_2 == 0xff,cStack_7) != SBORROW1(cVar2,bVar1))) {
    pcVar5 = (char *)CONCAT11(local_3,local_2);
    local_2 = local_2 + 1;
    if (local_2 == 0) {
      local_3 = local_3 + '\x01';
    }
    *(char *)CONCAT11(cVar4,cVar3) = *pcVar5 + *(char *)CONCAT11(cVar4,cVar3);
    local_6 = local_6 + 1;
    if (local_6 == 0) {
      cStack_7 = cStack_7 + '\x01';
    }
  }
  *(byte *)CONCAT11(cVar4,cVar3) = ~*(byte *)CONCAT11(cVar4,cVar3);
  sci_tx_start(param_2 + 3);
  return;
}



// WARNING: Removing unreachable block (RAM,0xec7a)
// WARNING: Removing unreachable block (RAM,0xec65)
// WARNING: Removing unreachable block (RAM,0xec8d)

void tx_crc_message(void)

{
  uRAM00be = 0x80;
  uRAM00bf = DAT_008b;
  uRAM00c0 = DAT_008c;
  tx_build_frame(0xbd,3);
  return;
}



// WARNING: Removing unreachable block (RAM,0xee4f)
// WARNING: Removing unreachable block (RAM,0xee29)
// WARNING: Removing unreachable block (RAM,0xee03)
// WARNING: Removing unreachable block (RAM,0xeddd)
// WARNING: Removing unreachable block (RAM,0xedb7)
// WARNING: Removing unreachable block (RAM,0xed8b)
// WARNING: Removing unreachable block (RAM,0xed36)
// WARNING: Removing unreachable block (RAM,0xed10)
// WARNING: Removing unreachable block (RAM,0xecea)
// WARNING: Removing unreachable block (RAM,0xecc2)
// WARNING: Removing unreachable block (RAM,0xecd7)
// WARNING: Removing unreachable block (RAM,0xecfd)
// WARNING: Removing unreachable block (RAM,0xed23)
// WARNING: Removing unreachable block (RAM,0xed79)
// WARNING: Removing unreachable block (RAM,0xeda4)
// WARNING: Removing unreachable block (RAM,0xedca)
// WARNING: Removing unreachable block (RAM,0xedf0)
// WARNING: Removing unreachable block (RAM,0xee16)
// WARNING: Removing unreachable block (RAM,0xee3c)
// WARNING: Removing unreachable block (RAM,0xee62)

void tx_status_message(void)

{
  uRAM00be = 0x81;
  tRAM00bf = throttle_status_level;
  sRAM00c0 = status_flags;
  uRAM00c1 = throttle_pos_ch1;
  uRAM00c2 = throttle_pos_ch2;
  uRAM00c3 = crosscheck_ch2_reference;
  uRAM00c4 = adc_latch[0];
  cRAM00c6 = DAT_007a + 3;
  cRAM00c5 = (0xfc < DAT_007a) + '\x01';
  if ((*(char *)CONCAT11(cRAM00c5,cRAM00c6) != '\x1a') && (DAT_007a < DAT_0079)) {
    DAT_0079 = DAT_007a;
  }
  if (DAT_007a < 0x20) {
    DAT_007a = DAT_007a + 1;
  }
  else {
    DAT_007a = '\0';
  }
  uRAM00c7 = *(undefined1 *)CONCAT11(cRAM00c5,cRAM00c6);
  bRAM00c8 = DAT_0079;
  uRAM00c9 = adc_latch[5];
  uRAM00ca = adc_latch[6];
  uRAM00cb = DAT_008b;
  uRAM00cc = DAT_008c;
  uRAM00cd = debounce_peak_ch2run;
  uRAM00ce = debounce_peak_monitor4;
  uRAM00cf = debounce_peak_monitor5;
  uRAM00d0 = debounce_peak_monitor6;
  uRAM00d1 = debounce_peak_crosscheck;
  tx_build_frame(0xbd,0x14);
  return;
}



short rx_dispatch(ushort param_1)

{
  char cVar1;
  byte bVar2;
  byte extraout_HI;
  byte extraout_HI_00;
  
  while( true ) {
    do {
      cVar1 = sci_rx_available();
      if (cVar1 == '\0' && (char)param_1 == '\0') {
        return param_1 & 0xff00;
      }
      bVar2 = sci_rx_read_byte();
      param_1 = rx_frame_parser(bVar2,param_1 & 0xff00);
    } while (bVar2 == 0 && (char)param_1 == '\0');
    if (DAT_00a3 == -0x80) break;
    if (DAT_00a3 == -0x7f) {
                    // is always set to 1 by incoming GT430 data
      DAT_008d = DAT_00a4 >> 7;
      rx_cmd_id = DAT_00a4 & 0x7f;
      rx_cal_sel = DAT_00a5;
      commanded_position_offset = DAT_00a6;
      tx_status_message();
      return (ushort)extraout_HI_00 << 8;
    }
  }
  tx_crc_message();
  return (ushort)extraout_HI << 8;
}



void init_tick_state(void)

{
  DAT_0033 = 0xc;
  DAT_0034 = 0x26;
  DAT_0030 = 0x53;
  comm_timeout = 100;
  tick_due_flag = 0;
  tx_busy_timer = 0;
  DAT_00fe = 2;
  DAT_00fd = 0x14;
  return;
}



undefined1 decrement_soft_timers(undefined1 param_1)

{
  undefined1 uVar1;
  
  uVar1 = math_acc_ext;
  DAT_0030 = DAT_0030 & 0x7f;
  if (comm_timeout != '\0') {
    comm_timeout = comm_timeout + -1;
  }
  if (tick_due_flag != '\0') {
    tick_due_flag = tick_due_flag + -1;
  }
  if (tx_busy_timer != '\0') {
    tx_busy_timer = tx_busy_timer + -1;
  }
  DAT_00fe = DAT_00fe + -1;
  if (DAT_00fe == '\0') {
    DAT_00fe = '\x02';
    capture_state_reset();
  }
  DAT_00fd = DAT_00fd + -1;
  if ((DAT_00fd == '\0') && (DAT_00fd = '\x14', handshake_countdown != '\0')) {
    handshake_countdown = handshake_countdown + -1;
  }
  math_acc_ext = uVar1;
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



// dispatch_by_status: indirect jump through the inline 11-entry jump table at
// throttle_status_jumptable (0xE772), indexed by throttle_status_level.

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
                    // WARNING: Could not recover jumptable at 0xef75. Too many branches
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
  bVar2 = CARRY1(DAT_0063,bVar1);
  DAT_0063 = DAT_0063 + bVar1;
  bVar1 = DAT_0062 + param_2[2];
  bVar3 = CARRY1(DAT_0062,param_2[2]) || CARRY1(bVar1,bVar2);
  DAT_0062 = bVar1 + bVar2;
  bVar2 = CARRY1(DAT_0061,param_2[1]);
  bVar1 = DAT_0061 + param_2[1];
  DAT_0061 = bVar1 + bVar3;
  DAT_0060 = DAT_0060 + *param_2 + (bVar2 || CARRY1(bVar1,bVar3));
  return param_1;
}



undefined1 FUN_ef90(undefined1 param_1)

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



undefined1 FUN_efc9(undefined1 param_1)

{
  undefined1 uStack_9;
  undefined1 uStack_8;
  undefined1 uStack_7;
  undefined1 uStack_6;
  undefined1 uStack_1;
  
  div32();
  DAT_0060 = uStack_9;
  DAT_0061 = uStack_8;
  DAT_0062 = uStack_7;
  DAT_0063 = uStack_6;
  if ((uStack_1 & 2) != 0) {
    neg32_acc();
  }
  return param_1;
}



// WARNING: Control flow encountered bad instruction data

void div32(void)

{
                    // WARNING: Bad instruction - Truncating control flow here
  halt_baddata();
}


