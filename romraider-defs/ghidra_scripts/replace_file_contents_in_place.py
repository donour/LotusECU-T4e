# Ghidra script: replace the bytes of the currently-open program with the contents of an external file.
#
# Typical use:
#   You've reverse-engineered firmware "prog.bin" in Ghidra and built up symbols/comments.
#   Then you (or your patch toolchain) produce a new "prog.bin" with extra code spliced in.
#   Run this script and point it at the new file -- the Ghidra project is updated in place,
#   so all of your prior markup still applies to the unchanged regions.
#
# Caveats:
#   - Only the *first* memory block (the one containing the image base) is rewritten. Programs
#     with multiple memory blocks (e.g. separate RAM/flash regions) will need a different approach.
#   - If the new file is larger than that block, it is truncated. Smaller files leave the tail
#     of the block untouched.
#   - After running, you typically want to re-run Auto Analyze so the disassembler re-interprets
#     the freshly written bytes.
#
# @category Memory

import os
from ghidra.util.task import TaskMonitor
from ghidra.program.model.listing import CodeUnit

def run():
    # Prompt the user for the replacement binary. askFile() throws if the dialog is cancelled,
    # so we catch and bail out cleanly rather than letting a stack trace hit the console.
    try:
        new_file = askFile("Select the new binary file", "Open")
    except Exception:
        print("Selection canceled.")
        return

    file_path = new_file.getAbsolutePath()
    file_size = os.path.getsize(file_path)

    # `currentProgram` is a Ghidra script-environment global -- the program open in the active tool.
    program = currentProgram
    memory = program.getMemory()
    # The image base is the address the loader mapped byte 0 of the binary to. For raw firmware
    # this is whatever you set when importing (e.g. 0x00000000 for a boot ROM, 0x40000 for a
    # PPC prog segment, etc.).
    base_address = program.getImageBase()

    print("[*] Target Program: {}".format(program.getName()))
    print("[*] Project Base Address: {}".format(base_address))
    print("[*] Overwriting with: {} ({} bytes)".format(file_path, file_size))

    with open(file_path, "rb") as f:
        new_bytes = f.read()

    ghidra_byte_array = [b if b < 128 else b - 256 for b in bytearray(new_bytes)]

    tx_id = program.startTransaction("Overwrite Bytes Script")
    try:
        # Grab the memory block that contains the image base. This is the block we will rewrite.
        target_block = memory.getBlock(base_address)
        if target_block is None:
            raise Exception("Could not find memory block at base address.")

        # Truncate the input to fit the block. We do *not* attempt to grow the block, since
        # changing block size has cascading effects on the program's memory map.
        block_size = target_block.getSize()
        if len(ghidra_byte_array) > block_size:
            print("[!] New file ({} bytes) is larger than target block ({} bytes); truncating.".format(
                len(ghidra_byte_array), block_size))
            ghidra_byte_array = ghidra_byte_array[:block_size]

        # Compute the inclusive end of the range we're about to overwrite. clearCodeUnits()
        # takes a [start, end] address pair (both endpoints inclusive), so we subtract one
        # from the length.
        end_address = base_address.add(len(ghidra_byte_array) - 1)

        # STEP 1: Clear existing instructions / defined data in the write zone.
        # If we skip this, putBytes() will fail on any address that is part of an existing
        # CodeUnit. The `True` argument tells Ghidra to also clear references that pointed
        # *into* the cleared range. Symbols, comments, and bookmarks survive -- only the
        # disassembler's interpretation is removed.
        print("[*] Clearing code and data conflicts in write zone...")
        listing = program.getListing()
        listing.clearCodeUnits(base_address, end_address, True)

        # STEP 2: Write the new bytes. putBytes() returns the count actually written, which
        # should equal len(ghidra_byte_array) unless the block ran out of room mid-write.
        bytes_written = target_block.putBytes(base_address, ghidra_byte_array)
        print("[+] Successfully replaced {} bytes in the database block!".format(bytes_written))

        # Commit the transaction so the change shows up in the listing and is undoable as
        # a single step.
        program.endTransaction(tx_id, True)
    except Exception as e:
        program.endTransaction(tx_id, False)
        print("[-] Error replacing bytes: {}".format(str(e)))

run()
