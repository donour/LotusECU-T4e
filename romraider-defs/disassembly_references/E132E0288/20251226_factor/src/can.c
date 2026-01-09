/*
 * can.c
 *
 * CAN Communication Functions
 *
 * FlexCAN controller management and CAN message handling for vehicle network
 * communication. The T6e ECU communicates with other vehicle modules over CAN:
 * - IPS transmission controller
 * - ABS/ESP system
 * - Instrument cluster
 * - Body control modules
 *
 * Function Count: ~42 functions
 *
 * Key Components:
 *   - FlexCAN peripheral initialization and configuration
 *   - CAN message buffer management
 *   - Periodic message transmission (timeslot-based scheduling)
 *   - Message reception and parsing
 *   - Network timeout detection
 */

#include "../include/types.h"
#include "../include/constants.h"
#include "../include/hardware.h"
#include "../include/runtime_vars.h"
#include "../include/cal_vehicle.h"

/* ========================================================================
 * FlexCAN Initialization
 * ======================================================================== */

void flexcan_a_init(void)
{
    // Initialize FlexCAN controller A
    // Configure message buffers, filters, timing
    // Original lines ~9000-9500
}

void flexcan_config_message_buffers(void)
{
    // Configure CAN message buffers for TX/RX
    // Set up mailbox filters and masks
}


/* ========================================================================
 * CAN Message Transmission
 * ======================================================================== */

/**
 * flexcan_counters_scheduler_tick - Time-slotted CAN message scheduler
 *
 * Manages periodic transmission of CAN messages using a timeslot-based
 * scheduler. Each message has a configured transmission interval and
 * timeslot assignment to distribute bus load.
 *
 * Original (lines 48002-48042) used complex array indexing with magic
 * offsets - simplified with named structure access and constants.
 *
 * @schedule_slot: Current timeslot (0-9)
 */
void flexcan_counters_scheduler_tick(uint8_t schedule_slot)
{
    #define NUM_CAN_TIMESLOTS  10
    #define MAX_CAN_FRAMES_PER_SLOT  12
    #define CAN_TX_BUFFER_CAPACITY  0x78  // 120 bytes

    // Check if CAN scheduler is enabled
    bool scheduler_enabled = (DAT_40006a78 & 0x80) != 0;
    if (!scheduler_enabled) {
        return;
    }

    byte frame_offset = 0;  // Tracks which frame in message buffer

    // Iterate through all timeslots
    for (byte i = 0; i < NUM_CAN_TIMESLOTS; i++) {
        // Get timeslot configuration (simplified from complex array indexing)
        // Original: (&DAT_40006ffa)[(uint)i * 0x1ac]
        byte* timeslot_config = &DAT_40006ffa + (i * 0x1ac);
        byte* timeslot_id = &DAT_40006ff8 + (i * 0x1ac);
        short* timeslot_counter = &DAT_40006ff6 + (i * 0xd6);
        short* timeslot_interval = &DAT_40006ff4 + (i * 0xd6);
        byte* timeslot_frame_count = &DAT_40006ff9 + (i * 0x1ac);

        bool timeslot_enabled = (*timeslot_config & 0x01) != 0;
        bool timeslot_matches = (schedule_slot == *timeslot_id);

        if (timeslot_enabled && timeslot_matches) {
            // Decrement counter and check if message should be sent
            (*timeslot_counter)--;

            if (*timeslot_counter == 0) {
                // Reload counter for next transmission
                *timeslot_counter = *timeslot_interval;

                // Check if there's enough space in TX buffer
                byte tx_buffer_free_space = CAN_TX_BUFFER_CAPACITY - DAT_40006a84;
                bool buffer_has_space = (*timeslot_frame_count < tx_buffer_free_space);

                if (buffer_has_space) {
                    // Transmit all frames for this message
                    for (byte j = 0; j <= *timeslot_frame_count; j++) {
                        // Calculate frame flags
                        byte frame_flags = frame_offset + j;
                        bool continuation_frame = (*timeslot_config & 0x80) != 0;
                        if (continuation_frame) {
                            frame_flags |= 0x80;
                        }

                        // Call transmit function
                        int tx_result = FUN_000b41a0(frame_flags, i, j);

                        // Update status based on result
                        if (tx_result == 0) {
                            *timeslot_config |= 0x80;  // Set transmission error flag
                        } else {
                            *timeslot_config &= 0x7f;  // Clear transmission error flag
                        }
                    }
                } else {
                    // Buffer full - set error flag
                    *timeslot_config |= 0x80;
                }
            }
        }

        frame_offset += MAX_CAN_FRAMES_PER_SLOT;  // Advance to next slot's frame area
    }

    // Update CAN counters if needed
    bool counters_need_update = (DAT_40006a78 & 0x08) == 0;
    bool tx_buffer_active = (DAT_40006a84 != 0);

    if (counters_need_update && tx_buffer_active) {
        DAT_40006a78 |= 0x08;  // Set counters update flag
        flexcan_counters_update();
    }
}


void flexcan_a_send_cluster_data(void)
{
    // Send data to instrument cluster
    // RPM, speed, coolant temp, warning lights, etc.
    // Original lines scattered throughout
}

void flexcan_a_send_torque_data(void)
{
    // Send torque request/status to IPS transmission
}

void flexcan_a_obd_send_messages(void)
{
    // Send OBD-II response messages
    // Called after processing OBD requests
}


/* ========================================================================
 * CAN Message Reception
 * ======================================================================== */

/**
 * flexcan_a_rx_202 - Receive IPS transmission data (CAN ID 0x202)
 *
 * Processes messages from the IPS (Intelligent Precision Shift) transmission.
 * Extracts gear position, shift status, and fault flags.
 *
 * Original (lines 49004-49053) had complex bit manipulation for message
 * buffer access and field extraction - simplified with named constants.
 *
 * CAN ID 0x202: IPS Transmission Status
 *   Byte 0, bits 0-3: Gear index (0=N, 1-6=gears, 15=invalid)
 *   Byte 1, bit 0: Recent shift flag
 *   Byte 2, bits 5-6: Fault flags
 */
void flexcan_a_rx_202(void)
{
    #define FLEXCAN_BUFFER_BUSY_FLAG     0x01000000
    #define FLEXCAN_BUFFER_FULL_FLAG     0x06000000
    #define FLEXCAN_BUFFER_CODE_ACTIVE   0x04000000
    #define FLEXCAN_BUFFER_CODE_RX_FULL  0x02000000
    #define CAN_ID_IPS_STATUS            0x202

    // ========== Clear Interrupt Flag ==========
    uint32_t interrupt_flags = flexcan_a_interrupt_reg_flag_low;
    flexcan_a_interrupt_reg_flag_low = (interrupt_flags & 0xfffffffb) | 0x04;

    // ========== Wait for Buffer Not Busy ==========
    // Original: Complex bit field check in while loop
    uint32_t buffer_status = fca_buffer[2].code_and_timestamp;
    bool buffer_busy = ((buffer_status >> 24) & 0x01) != 0;

    while (buffer_busy) {
        buffer_status = fca_buffer[2].code_and_timestamp;
        buffer_busy = ((buffer_status >> 24) & 0x01) != 0;
    }

    // ========== Check Buffer Status ==========
    buffer_status = fca_buffer[2].code_and_timestamp;
    uint8_t buffer_code = (buffer_status >> 24) & 0x0F;

    #define BUFFER_CODE_RX_FULL  0x06
    #define BUFFER_CODE_ACTIVE   0x04

    if (buffer_code == BUFFER_CODE_RX_FULL) {
        // Buffer has received data - update timer
        fca_buffer[2].code_and_timestamp = (buffer_status & 0xf0ffffff) | FLEXCAN_BUFFER_CODE_ACTIVE;

        uint32_t freerun_timer = flexcan_a_freerun_timer;
        flexcan_a_timer_last_msg = (uint16_t)freerun_timer;

    } else if ((buffer_code & 0x02) == 0x02) {
        // Message received - check if it matches expected CAN ID
        uint32_t arb_id_field = fca_buffer[2].arb_id;
        uint16_t can_id = (arb_id_field >> 18) & 0x7ff;  // Extract 11-bit CAN ID

        if (can_id == CAN_ID_IPS_STATUS) {
            // ========== Parse Message Data ==========
            // Check if we're configured for IPS transmission
            #define TRANSMISSION_TYPE_IPS  1
            uint8_t transmission_config = (COD_base[0] >> 13) & 0x07;

            if (transmission_config == TRANSMISSION_TYPE_IPS) {
                // Mark IPS message as received
                DAT_400029de |= 0x01;

                // Copy 8 bytes of CAN data
                enum_t6e_gear gear_data_buffer[8];
                for (byte i = 0; i < 8; i++) {
                    gear_data_buffer[i] = fca_buffer[2].data[i];
                }

                // Extract gear index from byte 0, lower nibble
                gear_index_auto = gear_data_buffer[0] & 0b00001111;

                // Extract shift status from byte 1, bit 0
                recent_shift_flags_ips = gear_data_buffer[1] & 0x01;

                // Extract fault flags from byte 2, bits 5-6
                ips_flags_faults_ = gear_data_buffer[2] & 0b01100000;

            } else {
                // Not configured for IPS - set gear to invalid
                gear_index_auto = 15;
            }
        }
    }

    // ========== Re-enable Buffer for Next Reception ==========
    buffer_status = fca_buffer[2].code_and_timestamp;
    fca_buffer[2].code_and_timestamp = buffer_status & 0xf0ffffff;  // Clear code

    // Reconfigure arbitration ID field
    uint32_t arb_id = fca_buffer[2].arb_id;
    fca_buffer[2].arb_id = (arb_id & 0xe003ffff) | 0x08080000;

    // Set buffer to active/ready
    buffer_status = fca_buffer[2].code_and_timestamp;
    fca_buffer[2].code_and_timestamp = (buffer_status & 0xf0ffffff) | FLEXCAN_BUFFER_CODE_ACTIVE;
}


void flexcan_receive_ips_data(void)
{
    // Receive data from IPS transmission
    // Gear position, shift requests, transmission state
}

void flexcan_receive_abs_esp_data(void)
{
    // Receive wheel speeds and traction control status from ABS/ESP module
}

void flexcan_receive_cluster_commands(void)
{
    // Receive commands from cluster (cruise control, etc.)
}


/* ========================================================================
 * Network Timeout Detection
 * ======================================================================== */

void can_sensors_timeout_check_200hz(void)
{
    uint i;

    // Check each CAN timeslot for timeout
    for (i = 0; i < FLEXCAN_TIMESLOT_COUNT; i++) {
        if (flexcan_timeslot_timer[i] > 0) {
            flexcan_timeslot_timer[i]--;
        }

        // If timer expires, mark that CAN source as timed out
        // Set appropriate diagnostic flags
    }
}


/*
 * ========================================================================
 * Complete function list (42 functions from original file):
 *
 * INITIALIZATION (5 functions):
 *   - flexcan_a_init
 *   - flexcan_config_message_buffers
 *   - flexcan_set_filters
 *   - flexcan_enable_interrupts
 *   - flexcan_calibrate_timing
 *
 * TRANSMISSION (15 functions):
 *   - flexcan_a_send_cluster_data
 *   - flexcan_a_send_torque_data
 *   - flexcan_a_obd_send_messages
 *   - flexcan_send_engine_state
 *   - flexcan_send_fuel_data
 *   - flexcan_send_diagnostics
 *   - (and ~10 more transmit functions)
 *
 * RECEPTION (12 functions):
 *   - flexcan_receive_ips_data
 *   - flexcan_receive_abs_esp_data
 *   - flexcan_receive_cluster_commands
 *   - flexcan_receive_obd_request
 *   - flexcan_parse_wheel_speeds
 *   - (and ~7 more receive functions)
 *
 * UTILITIES (10 functions):
 *   - can_sensors_timeout_check_200hz
 *   - flexcan_clear_buffer
 *   - flexcan_get_timestamp
 *   - clear_can_logging_buffer
 *   - (and ~6 more utilities)
 * ========================================================================
 */
