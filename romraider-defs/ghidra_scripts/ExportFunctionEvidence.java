//@category Lotus ECU
//@description Export decompilation, instructions, p-code, and references for named/addressed targets.

import java.io.File;
import java.io.PrintWriter;

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.pcode.PcodeOp;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import ghidra.program.model.symbol.Symbol;

public class ExportFunctionEvidence extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 2) {
            throw new IllegalArgumentException(
                "usage: ExportFunctionEvidence.java <output.txt> <symbol-or-hex-address> [...]");
        }

        File output = new File(args[0]);
        DecompInterface decompiler = new DecompInterface();
        decompiler.toggleCCode(true);
        decompiler.toggleSyntaxTree(true);
        if (!decompiler.openProgram(currentProgram)) {
            throw new IllegalStateException("decompiler could not open program");
        }

        try (PrintWriter writer = new PrintWriter(output)) {
            writer.println("Program: " + currentProgram.getName());
            writer.println("Language: " + currentProgram.getLanguageID());
            writer.println("Compiler: " + currentProgram.getCompilerSpec().getCompilerSpecID());

            for (int index = 1; index < args.length; index++) {
                Address address = resolve(args[index]);
                writer.println();
                writer.println("================================================================================");
                writer.println("TARGET " + args[index] + " @ " + address);
                writer.println("================================================================================");
                exportReferences(writer, address);

                Function function = getFunctionAt(address);
                if (function == null) {
                    function = getFunctionContaining(address);
                }
                if (function != null) {
                    exportFunction(writer, decompiler, function);
                }
            }
        }
        decompiler.dispose();
        println("Wrote " + output.getAbsolutePath());
    }

    private Address resolve(String target) {
        String normalized = target.toLowerCase().startsWith("0x") ? target.substring(2) : target;
        if (normalized.matches("[0-9a-fA-F]{4,16}")) {
            return toAddr(Long.parseUnsignedLong(normalized, 16));
        }
        for (Symbol symbol : currentProgram.getSymbolTable().getSymbols(target)) {
            return symbol.getAddress();
        }
        Function function = getFunction(target);
        if (function != null) {
            return function.getEntryPoint();
        }
        throw new IllegalArgumentException("target not found: " + target);
    }

    private void exportReferences(PrintWriter writer, Address address) {
        writer.println("\nREFERENCES TO TARGET");
        ReferenceIterator references = currentProgram.getReferenceManager().getReferencesTo(address);
        int count = 0;
        while (references.hasNext()) {
            Reference reference = references.next();
            Address from = reference.getFromAddress();
            Function owner = getFunctionContaining(from);
            Instruction instruction = getInstructionContaining(from);
            writer.printf("  %s %-12s owner=%s instruction=%s%n",
                from, reference.getReferenceType(), owner == null ? "-" : owner.getName(),
                instruction == null ? "-" : instruction.toString());
            count++;
        }
        writer.println("Reference count: " + count);
    }

    private void exportFunction(PrintWriter writer, DecompInterface decompiler, Function function) {
        writer.println("\nFUNCTION " + function.getName() + " @ " + function.getEntryPoint());
        writer.println("Body: " + function.getBody());

        writer.println("\nDECOMPILATION");
        DecompileResults results = decompiler.decompileFunction(function, 120, monitor);
        if (results.decompileCompleted() && results.getDecompiledFunction() != null) {
            writer.println(results.getDecompiledFunction().getC());
        }
        else {
            writer.println("Decompiler failure: " + results.getErrorMessage());
        }

        writer.println("\nINSTRUCTIONS AND PCODE");
        InstructionIterator instructions =
            currentProgram.getListing().getInstructions(function.getBody(), true);
        while (instructions.hasNext()) {
            Instruction instruction = instructions.next();
            writer.printf("%s  %-12s %s%n", instruction.getAddress(),
                instruction.getMnemonicString(), instruction.toString());
            for (PcodeOp op : instruction.getPcode()) {
                writer.println("    " + op);
            }
        }
    }
}
