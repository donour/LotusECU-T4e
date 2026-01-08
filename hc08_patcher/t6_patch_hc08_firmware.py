import os, sys

TPS_MAX_TABLE_LEN = 16
TPS_MAX_TABLE_CAL_LOC = 0x0E3E
TPS_MAX_TABLE_AXIS_CAL_LOC = 0x0E2E

TPS_MAX_TABLE_PROG_LOC = 0x91432
TPS_MAX_TABLE_AXIS_PROG_LOC = 0x91422

CRC_MAGIC_INSTRUCTION_LOC=0x337c0

def patch_firmware(prog_filename, cal_filename):
    # open the cal file and extract the TPS max table and TPS max table x axis
    with open(cal_filename, 'rb') as cal_file:
        cal_data = cal_file.read()
        # extract tps max table and x axis from cal_data
        tps_max_table = cal_data[TPS_MAX_TABLE_CAL_LOC:TPS_MAX_TABLE_CAL_LOC + TPS_MAX_TABLE_LEN]
        tps_max_x_axis = cal_data[TPS_MAX_TABLE_AXIS_CAL_LOC:TPS_MAX_TABLE_AXIS_CAL_LOC + TPS_MAX_TABLE_LEN]
        # print extracted data as a a list of hex values
        print("Extracted TPS Max Table: ", [hex(b) for b in tps_max_table])
        print("Extracted TPS Max X Axis:", [hex(b) for b in tps_max_x_axis])            

    # open program file and load the table from the firmware region and print the marginal difference
    with open(prog_filename, 'rb') as prog_file:
        prog_data = bytearray(prog_file.read())
        # extract existing tps max table and x axis from prog_data
        existing_tps_max_table = prog_data[TPS_MAX_TABLE_PROG_LOC:TPS_MAX_TABLE_PROG_LOC + TPS_MAX_TABLE_LEN]
        existing_tps_max_x_axis = prog_data[TPS_MAX_TABLE_AXIS_PROG_LOC:TPS_MAX_TABLE_AXIS_PROG_LOC + TPS_MAX_TABLE_LEN]
        # print existing data as a a list of hex values
        print("Existing TPS Max Table:  ", [hex(b) for b in existing_tps_max_table])
        print("Existing TPS Max X Axis: ", [hex(b) for b in existing_tps_max_x_axis])            
        
        # calculate and print marginal difference
        table_diff = [(new - old) for new, old in zip(tps_max_table, existing_tps_max_table)]
        x_axis_diff = [(new - old) for new, old in zip(tps_max_x_axis, existing_tps_max_x_axis)]
        print("TPS Max Table Difference: ", table_diff)
        print("TPS Max X Axis Difference:", x_axis_diff)

        # write the tps max table data to the firmware region in the prog file
        prog_data[TPS_MAX_TABLE_PROG_LOC:TPS_MAX_TABLE_PROG_LOC + TPS_MAX_TABLE_LEN] = tps_max_table
        prog_data[TPS_MAX_TABLE_AXIS_PROG_LOC:TPS_MAX_TABLE_AXIS_PROG_LOC + TPS_MAX_TABLE_LEN] = tps_max_x_axis
        with open(prog_filename + '.patched', 'wb') as patched_file:
            patched_file.write(prog_data)

    # extract the new checksum from the firmware in the program file by running hc08_sum.py script from this directory
    from hc08_sum import SUM_HC08_T6
    cksum = SUM_HC08_T6()
    off = int.from_bytes(prog_data[0x8C:0x90], 'big') - 0x40000
    cksum.update(prog_data[off       :off+0x2000])
    cksum.update(prog_data[off+0x23DC:off+0x2400])
    new_checksum = cksum.get()
    print("New Checksum T6 : 0x{:04X}".format(new_checksum))

    # set the checksum file in the crc checker in the program file
    # This is pretty hacky. CRC_MAGIC_INSTRUCTION_LOC contains a ppc32 that 
    # subtract and immediate val (crc_check_magic) from $r3 to get the actual 
    # value. We need to replace the immediate value in the instruction.
    # Instruction format: 38 63 xx xx  (where xx xx is the immediate value)
    instr_offset = CRC_MAGIC_INSTRUCTION_LOC
    instr = prog_data[instr_offset:instr_offset+4]
    if instr[0] != 0x38 or instr[1] != 0x63:
        print("Unexpected instruction at CRC magic location!")
        return
    new_instr = bytearray(instr)
    new_instr[2] = (new_checksum >> 8) & 0xFF
    new_instr[3] = new_checksum & 0xFF
    prog_data[instr_offset:instr_offset+4] = new_instr
    with open(prog_filename + '.patched', 'wb') as patched_file:
        print("Patching checksum...")
        patched_file.write(prog_data) 


if __name__ == "__main__":
    prog_filename, cal_filename = sys.argv[1:3]
    patch_firmware(prog_filename, cal_filename)
