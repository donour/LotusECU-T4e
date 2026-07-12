//@category Lotus ECU
//@description Seed vectors and entry points in the HC08 supervisor image embedded in C132E0278.

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.data.WordDataType;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.mem.Memory;
import ghidra.program.model.symbol.RefType;
import ghidra.program.model.symbol.SourceType;

public class PrepareC132E0278HC08 extends GhidraScript {
    @Override
    public void run() throws Exception {
        Memory memory = currentProgram.getMemory();
        Listing listing = currentProgram.getListing();
        int targets = 0;

        for (long slotOffset = 0xffe0; slotOffset <= 0xfffe; slotOffset += 2) {
            Address slot = toAddr(slotOffset);
            int targetOffset = Short.toUnsignedInt(memory.getShort(slot));
            Address target = toAddr(targetOffset);
            if (targetOffset < 0xdc00 || targetOffset == 0xffff || !memory.contains(target)) {
                continue;
            }

            if (listing.getCodeUnitAt(slot) == null) {
                listing.createData(slot, new WordDataType());
            }
            currentProgram.getReferenceManager().addMemoryReference(
                slot, target, RefType.DATA, SourceType.USER_DEFINED, 0);
            disassemble(target);
            Function function = getFunctionAt(target);
            if (function == null) {
                String name = slotOffset == 0xfffe ? "hc08_reset" :
                    String.format("hc08_vector_%04x_handler", slotOffset);
                function = createFunction(target, name);
            }
            if (slotOffset == 0xfffe) {
                function.setName("hc08_reset", SourceType.USER_DEFINED);
                currentProgram.getSymbolTable().addExternalEntryPoint(target);
            }
            targets++;
        }
        println("Seeded " + targets + " HC08 vector targets");
    }
}
