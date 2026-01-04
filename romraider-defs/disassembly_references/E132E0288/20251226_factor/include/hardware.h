/*
 * hardware.h
 *
 * Hardware Peripheral Register Definitions
 *
 * This file contains memory-mapped I/O register declarations for the
 * MPC5534 microcontroller peripherals used in the Lotus T6e ECU.
 *
 * Peripheral Base Addresses:
 *   - INTC:  0xFFF48000 (Interrupt Controller)
 *   - SIU:   0xC3F90000 (System Integration Unit)
 *   - EQADC: 0xFFF80000 (Enhanced Queued ADC)
 *   - eTPU:  0xC3FC0000 (Enhanced Time Processing Unit)
 *   - EMIOS: 0xC3FA0000 (Enhanced Modular I/O System)
 *   - DSPI:  SPI peripheral
 *   - ESCI:  Serial Communication Interface
 *   - FlexCAN: CAN controller
 *   - FMPLL: Frequency Modulated PLL
 *   - EBI:   External Bus Interface
 */

#ifndef HARDWARE_H
#define HARDWARE_H

#include "types.h"

/* ========================================================================
 * Memory-Mapped Hardware Registers
 * ======================================================================== */

uint32_t FMPLL_SYNCSR;
uint32_t siu_srcr;
uint32_t FMPLL_SYNCR;
undefined intc_setup_safe_write;
uint32_t intc_mcr;
uint32_t intc_iackr;
uint32_t intc_cpr;
uint16_t siu_pcr[229];
uint32_t SIU_ECCR;
uint16_t siu_pcr[214];
uint16_t[343] siu_pcr;
uint32_t EBI_MCR;
uint32_t EBI_BR0;
uint32_t EBI_OR0;
uint16_t[6] eqadc_cfcr;
uint16_t[6] eqadc_idcr;
uint32_t[6] eqadc_fisr;
uint32_t[6] EQADC_CFPR;
uint32_t[6] EQADC_RFPR0;
uint32_t EQADC_CFSR;
uint32_t EQADC_RFPR0[2];
uint32_t eqadc_fisr[2];
uint32_t EQADC_RFPR0[3];
uint32_t eqadc_fisr[3];
uint32_t EQADC_RFPR0[1];
uint32_t eqadc_fisr[1];
uint32_t EQADC_RFPR0[4];
uint32_t eqadc_fisr[4];
uint16_t eqadc_cfcr[4];
uint16_t eqadc_cfcr[5];
uint16_t eqadc_cfcr[1];
uint16_t eqadc_cfcr[2];
uint16_t eqadc_cfcr[3];
uint16_t eqadc_idcr[4];
uint16_t eqadc_idcr[5];
uint16_t eqadc_idcr[1];
uint16_t eqadc_idcr[2];
uint32_t eqadc_fisr[5];
uint16_t eqadc_idcr[3];
uint32_t etpu_base_unknown2;
uint32_t *etpu_mcr_addr;
uint32_t eTPU_base_unknown;
uint16_t siu_pcr[92];
uint16_t siu_pcr[124];
uint16_t siu_pcr[125];
uint16_t siu_pcr[189];
uint16_t siu_pcr[126];
uint16_t siu_pcr[127];
uint16_t siu_pcr[120];
uint16_t siu_pcr[184];
uint16_t siu_pcr[121];
uint16_t siu_pcr[122];
uint16_t siu_pcr[186];
uint16_t siu_pcr[91];
uint16_t siu_pcr[123];
uint16_t siu_pcr[116];
uint16_t siu_pcr[180];
uint16_t siu_pcr[212];
uint16_t siu_pcr[117];
uint16_t siu_pcr[86];
uint16_t siu_pcr[118];
uint16_t siu_pcr[119];
uint16_t siu_pcr[183];
uint16_t siu_pcr[144];
uint16_t siu_pcr[113];
uint16_t siu_pcr[145];
uint16_t siu_pcr[114];
uint16_t siu_pcr[115];
uint16_t siu_pcr[179];
uint16_t siu_pcr[211];
uint16_t siu_pcr[143];
uint16_t siu_pcr[207];
uint16_t siu_pcr[136];
uint16_t siu_pcr[137];
uint16_t siu_pcr[202];
uint16_t siu_pcr[203];
uint16_t siu_pcr[100];
uint16_t siu_pcr[132];
uint16_t siu_pcr[133];
uint16_t siu_pcr[134];
uint16_t siu_pcr[135];
uint16_t siu_pcr[199];
uint16_t siu_pcr[96];
uint16_t siu_pcr[128];
uint16_t siu_pcr[193];
uint16_t siu_pcr[98];
uint16_t siu_pcr[99];
uint16_t siu_pcr[131];
uint16_t siu_pcr[195];
uint32_t siu_rsr;
byte emios_uc[0].uc[136];
byte emios_uc[0].uc[140];
byte emios_uc[0].uc[128];
byte emios_uc[0].uc[132];
byte emios_uc[0].uc[144];
undefined4 etpu_elapsed_min_ticks;
undefined4 etpu_elapsed_max_captured_ticks;
uint32_t eTPU_crank_angle_speed_scaling;
uint16_t siu_pcr[108];
uint16_t siu_pcr[93];
uint16_t siu_pcr[109];
uint16_t siu_pcr[94];
uint16_t siu_pcr[110];
uint16_t siu_pcr[190];
uint16_t siu_pcr[95];
struct_dspi_mmio DSPI_B;
uint16_t siu_pcr[104];
struct_dspi_mmio DSPI_C;
uint16_t siu_pcr[105];
uint16_t siu_pcr[107];
uint16_t siu_pcr[101];
uint16_t siu_pcr[102];
uint16_t siu_pcr[103];
uint32_t DSPI_C.popr;
uint32_t DSPI_C.ctar[0];
uint32_t DSPI_C.sr;
uint32_t DSPI_C.pushr;
uint32_t DSPI_C.ctar[1];
uint32_t EMIOS_MCR;
struct_emios_unified_channel_register[24] emios_uc;
uint8_t[212] INTC_PSR;
byte emios_uc[0].uc[208];
byte emios_uc[0].uc[160];
byte emios_uc[0].uc[176];
byte emios_uc[0].uc[164];
uint16_t siu_pcr[188];
byte emios_uc[1].uc[32];
byte emios_uc[1].uc[48];
byte emios_uc[1].uc[36];
uint8_t[214] siu_gpdi;
uint32_t ETPU_MCR;
byte[3071] ETPU_shared_ram;
byte[12287] ETPU_scm;
undefined ETPU_sdm_pse_mirror;
undefined4 eTPU_period;
undefined4 eTPU_freq;
undefined2 eTPU_period2;
undefined1 eTPU_status_flag;
uint32_t siu_start;
uint16_t siu_pcr[182];
uint16_t siu_pcr[201];
uint16_t siu_pcr[140];
uint16_t siu_pcr[206];
uint16_t siu_pcr[22];
uint16_t siu_pcr[198];
uint16_t siu_pcr[209];
uint16_t siu_pcr[141];
uint16_t siu_pcr[196];
uint16_t siu_pcr[197];
uint16_t siu_pcr[142];
uint16_t siu_pcr[129];
byte emios_uc[2].uc[40];
byte emios_uc[2].uc[44];
byte emios_uc[2].uc[32];
byte emios_uc[2].uc[36];
byte emios_uc[2].uc[72];
byte emios_uc[2].uc[76];
byte emios_uc[2].uc[64];
byte emios_uc[2].uc[68];
byte emios_uc[0].uc[200];
byte emios_uc[0].uc[204];
byte emios_uc[0].uc[192];
byte emios_uc[0].uc[196];
uint16_t siu_pcr[204];
uint16_t siu_pcr[185];
uint16_t siu_pcr[187];
flexcan_msg_buffer[64] fca_buffer;
flexcan_msg_buffer[64] fcb_buffer;
uint16_t siu_pcr[84];
uint16_t siu_pcr[83];
uint flexcan_msg_buffer_303;
uint16_t siu_pcr[88];
uint16_t siu_pcr[87];
struct_esci_control_registers esci_a;
uint32_t esci_a.sr;
uint32_t esci_a.lpr;
uint32_t esci_a.lcr;
uint16_t siu_pcr[89];
uint16_t siu_pcr[90];
uint16_t esci_a.cr2;
uint16_t esci_a.dr+1;
byte[32] esci_a_buffer;
undefined1 esci_a_buffer_len;
undefined1 esci_seq_number;
uint16_t siu_pcr[130];
byte emios_uc[0].uc[72];
byte emios_uc[0].uc[76];
byte emios_uc[0].uc[64];
byte emios_uc[0].uc[68];
uint16_t siu_pcr[181];
uint32_t siu_midr;
undefined4 intc_eoir;
  install_intc_vector___();
  init_siu_ebi_segment();

#endif /* HARDWARE_H */
