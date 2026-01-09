/*
 * constants.h
 *
 * Constants and Bit Flag Definitions for Lotus T6e ECU Firmware (E132E0288)
 *
 * This file contains named constants extracted from the disassembly to improve
 * code readability. Magic numbers and bit patterns have been replaced with
 * descriptive names.
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

/* ========================================================================
 * Section 1: Bit Flag Masks
 * ======================================================================== */

/* Knock Detection Flags */
#define KNOCK_FLAG_ACTIVE              0x80    /* Knock actively detected */
#define KNOCK_FLAG_CONDITIONS          0x08    /* Knock monitoring conditions met */
#define KNOCK_FLAG_INHIBIT             0x02    /* Knock detection inhibited */

/* Ignition Flags */
#define IGN_FLAG_COLDSTART             0x02    /* Cold start mode active */

/* Engine State Failure Flags */
#define ENGINE_FAILURE_KNOCK_MONITOR   0x400000  /* Knock monitor failure */

/* Diagnostic Flags (main_diagnostic_flags) */
#define DIAG_FLAG_CHECKSUM_ERROR       0x0001  /* Checksum/verification error */
#define DIAG_FLAG_PROCESSOR_ERROR      0x0002  /* ECU processor error */
#define DIAG_FLAG_VIN_INVALID          0x0004  /* VIN data invalid/missing */
#define DIAG_FLAG_COD_INVALID          0x0008  /* COD (coding) data invalid */
#define DIAG_FLAG_IPS_FAULT            0x0020  /* IPS transmission fault */

/* Closed Loop Fuel Flags */
#define CL_STATE_ACTIVE                0x0001  /* Closed loop active */

/* Injection Flags */
#define INJ_FLAG_OVERRUN               0x0001  /* Overrun fuel cut active */

/* Ignition On Flags */
#define IGN_ON_FLAG_RUNNING            0x0001  /* Engine running */

/* Lifter Follower Bleed (LFB) Flags */
#define LFB_FLAG_ACTIVE                0x80    /* LFB active */

/* IPS Shift State Flags (DAT_40002738) */
#define IPS_SHIFT_FLAG_SPEED_MATCH     0x01    /* Speed matching requested */
#define IPS_SHIFT_FLAG_PRESHIFT        0x02    /* Pre-shift mode */

/* Traction Control Flags */
#define TC_FLAG_ENABLED                0x01    /* Traction control enabled */

/* Torque Reduction Flags (DAT_40002857) */
#define TORQUE_REDUCTION_ACTIVE        0x01    /* Torque reduction request active */

/* Fuel Pressure State Flags */
#define FUEL_PRESS_FLAG_ERROR          0x01    /* Fuel pressure error */

/* OBD-II Mode Flags */
#define OBD_MODE_09_SUPPORTED          0x01    /* Mode 09 supported */

/* Rev Limit State Flags */
#define REVLIMIT_FLAG_HARD             0x01    /* Hard rev limiter active */
#define REVLIMIT_FLAG_SOFT             0x02    /* Soft rev limiter active */

/* Paddle Shift Flags */
#define PADDLE_SHIFT_UP                0x01    /* Upshift requested */
#define PADDLE_SHIFT_DOWN              0x02    /* Downshift requested */

/* Cruise Control Flags */
#define CRUISE_FLAG_ACTIVE             0x01    /* Cruise control active */
#define CRUISE_FLAG_SET                0x02    /* Cruise control set */


/* ========================================================================
 * Section 2: OBD-II Constants
 * ======================================================================== */

/* DTC Entry Size */
#define DTC_ENTRY_SIZE                 2       /* Size of each DTC entry in array */

/* OBD-II Monitor Enable Masks */
#define OBD_MONITOR_ENABLE_MASK        0x07    /* Bits 0-2: enable, fail thresh, pass thresh */

/* OBD-II Level T6 State Bits */
#define OBD_STATE_PENDING              0x01
#define OBD_STATE_CONFIRMED            0x02
#define OBD_STATE_MIL_ON               0x04


/* ========================================================================
 * Section 3: Engine Speed/Load Thresholds
 * ======================================================================== */

/* Common RPM Thresholds (approximate values, adjust based on calibration) */
#define ENGINE_SPEED_IDLE_TARGET       800     /* Typical idle target RPM */
#define ENGINE_SPEED_HIGH_RPM          6000    /* High RPM threshold */
#define ENGINE_SPEED_REDLINE           7200    /* Typical redline RPM */

/* Misfire Detection Thresholds */
#define MISFIRE_CAT_DAMAGE_THRESHOLD   200     /* Threshold for catalyst damage */


/* ========================================================================
 * Section 4: Array Sizes and Limits
 * ======================================================================== */

/* Cylinder Count */
#define NUM_CYLINDERS                  6       /* V6 engine */

/* CAN Message Buffers */
#define CAN_DATA_SIZE                  8       /* CAN message data size */

/* ADC Channels */
#define ADC_BUFFER_SIZE                256     /* ADC DMA buffer size */

/* MAF/MAP Averaging */
#define MAF_BUFFER_SIZE                32      /* MAF voltage buffer size */
#define MAP_BUFFER_SIZE                32      /* MAP voltage buffer size */

/* Engine Speed History */
#define ENGINE_SPEED_HISTORY_SIZE      4       /* 500ms history */

/* TPS History */
#define TPS_HISTORY_SIZE               16      /* TPS target history */

/* OBD DTCs */
#define OBD_MAX_STORED_DTCS            8       /* Max stored DTCs */

/* FlexCAN Timeslots */
#define FLEXCAN_TIMESLOT_COUNT         10      /* Number of CAN timeslots */


/* ========================================================================
 * Section 5: Hardware Register Addresses
 * ======================================================================== */

/* MPC5534 Peripheral Base Addresses */
#define INTC_BASE                      0xFFF48000  /* Interrupt Controller */
#define EQADC_BASE                     0xFFF80000  /* Enhanced Queued ADC */
#define ETPU_BASE                      0xC3FC0000  /* eTPU */
#define SIU_BASE                       0xC3F90000  /* System Integration Unit */


/* ========================================================================
 * Section 6: Conversion Factors
 * ======================================================================== */

/* Scaling Factors */
#define SCALE_FACTOR_1024              1024    /* 10-bit scaling */
#define SCALE_FACTOR_2560              2560    /* Common PID scaling */

/* Unit Conversions */
#define MS_PER_SECOND                  1000    /* Milliseconds per second */
#define US_PER_MS                      1000    /* Microseconds per millisecond */


/* ========================================================================
 * Section 7: Timeouts and Delays
 * ======================================================================== */

/* Timer Intervals */
#define TIMER_1000HZ_INTERVAL          1       /* 1ms */
#define TIMER_200HZ_INTERVAL           5       /* 5ms */
#define TIMER_100HZ_INTERVAL           10      /* 10ms */
#define TIMER_50HZ_INTERVAL            20      /* 20ms */
#define TIMER_20HZ_INTERVAL            50      /* 50ms */
#define TIMER_10HZ_INTERVAL            100     /* 100ms */
#define TIMER_5HZ_INTERVAL             200     /* 200ms */
#define TIMER_2HZ_INTERVAL             500     /* 500ms */
#define TIMER_1HZ_INTERVAL             1000    /* 1000ms */

/* Common Timeouts */
#define IPS_SHIFT_TIMEOUT_MS           3000    /* IPS shift state timeout */
#define ENGINE_START_TIMEOUT_MS        5000    /* Engine start timeout */
#define O2_HEATER_WARMUP_MS            120000  /* O2 sensor heater warmup (2 min) */


/* ========================================================================
 * Section 8: Numeric Constants
 * ======================================================================== */

/* Maximum Values */
#define UINT8_MAX_VALUE                255
#define UINT16_MAX_VALUE               65535
#define INT16_MAX_VALUE                32767
#define INT16_MIN_VALUE                -32768

/* Percentage/Factor Limits */
#define PERCENT_100                    100
#define PERCENT_0                      0

/* Common Array Indices */
#define CYLINDER_INDEX_0               0
#define CYLINDER_INDEX_1               1
#define CYLINDER_INDEX_2               2
#define CYLINDER_INDEX_3               3
#define CYLINDER_INDEX_4               4
#define CYLINDER_INDEX_5               5


/* ========================================================================
 * Section 9: Character Constants
 * ======================================================================== */

/* ASCII Character Codes */
#define CHAR_0                         '0'     /* 0x30 */
#define CHAR_9                         '9'     /* 0x39 */
#define CHAR_A                         'A'     /* 0x41 */
#define CHAR_F                         'F'     /* 0x46 */
#define CHAR_E                         'E'     /* 0x45 */


/* ========================================================================
 * Section 10: State Machine States
 * ======================================================================== */

/* IPS Rev Match State Values */
#define IPS_REV_MATCH_INACTIVE         0
#define IPS_REV_MATCH_PRESHIFT         1
#define IPS_REV_MATCH_SPEED_MATCH      2
#define IPS_REV_MATCH_REENGAGE         3
#define IPS_REV_MATCH_RECOVERY         4

/* Engine Running State Values */
#define ENGINE_STATE_STOPPED           0
#define ENGINE_STATE_CRANKING          1
#define ENGINE_STATE_RUNNING           2


#endif /* CONSTANTS_H */
