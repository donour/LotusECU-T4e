//@category Lotus ECU
//@description Prepare a raw C132E0278 MPC5534 image for analysis: map RAM/CAL/MMIO,
// import stock calibration/runtime initializers, seed entry/vector functions, and import symbols.

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.nio.file.Files;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.data.Pointer32DataType;
import ghidra.program.model.listing.CodeUnit;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.mem.Memory;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.symbol.RefType;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolTable;

public class PrepareC132E0278 extends GhidraScript {
    private static final long PROGRAM_BASE = 0x00040000L;
    private static final long ENTRY_POINTER = 0x00040004L;
    private static final long VECTOR_BASE = 0x000d5000L;
    private static final int VECTOR_COUNT = 256;
    private static final long DATA_INIT_SOURCE = 0x000d38c8L;
    private static final long RAM_BASE = 0x40000000L;
    private static final int RAM_SIZE = 0x10000;
    private static final int DATA_INIT_SIZE = 0x1648;
    private static final long CAL_FLASH_BASE = 0x00020000L;
    private static final long CAL_RAM_BASE = 0x40008654L;

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 2) {
            throw new IllegalArgumentException(
                "usage: PrepareC132E0278.java <C132E0278_symbols.csv> <stock.cpt>");
        }

        File symbolsFile = new File(args[0]);
        File calibrationFile = new File(args[1]);
        byte[] calibration = Files.readAllBytes(calibrationFile.toPath());

        createMemoryMap(calibration);
        seedSmallDataRegisters();
        seedEntryPoint();
        seedVectorTable();
        importSymbols(symbolsFile);

        println("C132E0278 preparation complete");
    }

    private void seedSmallDataRegisters() throws Exception {
        MemoryBlock program = currentProgram.getMemory().getBlock(toAddr(PROGRAM_BASE));
        if (program == null) {
            throw new IllegalStateException("program block is missing");
        }
        currentProgram.getProgramContext().setValue(
            currentProgram.getRegister("r13"), program.getStart(), program.getEnd(),
            new BigInteger("40009430", 16));
        currentProgram.getProgramContext().setValue(
            currentProgram.getRegister("r2"), program.getStart(), program.getEnd(),
            new BigInteger("4000a8f8", 16));
        println("Seeded EABI small-data anchors r13=0x40009430 and r2=0x4000a8f8");
    }

    private void createMemoryMap(byte[] calibration) throws Exception {
        Memory memory = currentProgram.getMemory();

        MemoryBlock ram = memory.getBlock(toAddr(RAM_BASE));
        boolean ramCreated = ram == null;
        if (ram == null) {
            ram = memory.createInitializedBlock(
                "INTERNAL_RAM", toAddr(RAM_BASE), RAM_SIZE, (byte) 0, monitor, false);
            ram.setRead(true);
            ram.setWrite(true);
            ram.setExecute(false);
        }

        MemoryBlock calFlash = memory.getBlock(toAddr(CAL_FLASH_BASE));
        boolean calFlashCreated = calFlash == null;
        if (calFlash == null) {
            calFlash = memory.createInitializedBlock(
                "CAL_FLASH", toAddr(CAL_FLASH_BASE), calibration.length, (byte) 0, monitor, false);
            calFlash.setRead(true);
            calFlash.setWrite(false);
            calFlash.setExecute(false);
        }
        if (calFlashCreated) {
            memory.setBytes(toAddr(CAL_FLASH_BASE), calibration);
        }
        if (ramCreated) {
            memory.setBytes(toAddr(CAL_RAM_BASE), calibration);
            byte[] initializedData = new byte[DATA_INIT_SIZE];
            memory.getBytes(toAddr(DATA_INIT_SOURCE), initializedData);
            memory.setBytes(toAddr(RAM_BASE), initializedData);
        }

        createUninitializedBlock("CODING_FLASH", 0x0001c000L, 0x44, true, false, false);
        createUninitializedBlock("PERSISTENCE_FLASH", 0x00010000L, 0x8000, true, true, false);
        createUninitializedBlock("MPC5534_C3_PERIPHERALS", 0xc3f80000L, 0x50000, true, true, false);
        createUninitializedBlock("MPC5534_FFF_PERIPHERALS", 0xfff00000L, 0x100000, true, true, false);

        println("Mapped internal RAM, stock CAL flash/shadow, coding/persistence, and MMIO");
    }

    private void createUninitializedBlock(
            String name, long start, long length, boolean read, boolean write, boolean execute)
            throws Exception {
        Memory memory = currentProgram.getMemory();
        if (memory.getBlock(toAddr(start)) != null) {
            return;
        }
        MemoryBlock block = memory.createUninitializedBlock(name, toAddr(start), length, false);
        block.setRead(read);
        block.setWrite(write);
        block.setExecute(execute);
    }

    private void seedEntryPoint() throws Exception {
        Memory memory = currentProgram.getMemory();
        long targetOffset = Integer.toUnsignedLong(memory.getInt(toAddr(ENTRY_POINTER)));
        Address target = toAddr(targetOffset);
        if (targetOffset < PROGRAM_BASE || !memory.contains(target)) {
            throw new IllegalStateException("invalid entry pointer: " + target);
        }
        disassemble(target);
        if (getFunctionAt(target) == null) {
            createFunction(target, "init");
        }
        currentProgram.getSymbolTable().addExternalEntryPoint(target);
        addPointerReference(toAddr(ENTRY_POINTER), target);
        println("Entry point: " + target);
    }

    private void seedVectorTable() throws Exception {
        Memory memory = currentProgram.getMemory();
        Listing listing = currentProgram.getListing();
        int functions = 0;
        for (int index = 0; index < VECTOR_COUNT; index++) {
            Address slot = toAddr(VECTOR_BASE + index * 4L);
            long targetOffset = Integer.toUnsignedLong(memory.getInt(slot));
            Address target = toAddr(targetOffset);
            if (targetOffset < PROGRAM_BASE || !memory.contains(target)) {
                continue;
            }

            CodeUnit existing = listing.getCodeUnitAt(slot);
            if (existing == null) {
                listing.createData(slot, new Pointer32DataType());
            }
            addPointerReference(slot, target);
            disassemble(target);
            if (getFunctionAt(target) == null) {
                createFunction(target, null);
                functions++;
            }
        }
        println("Seeded " + VECTOR_COUNT + " INTC vector slots and " + functions + " new handlers");
    }

    private void addPointerReference(Address from, Address to) {
        currentProgram.getReferenceManager().addMemoryReference(
            from, to, RefType.DATA, SourceType.USER_DEFINED, 0);
    }

    private void importSymbols(File csvFile) throws Exception {
        SymbolTable symbols = currentProgram.getSymbolTable();
        Listing listing = currentProgram.getListing();
        int functions = 0;
        int labels = 0;
        int comments = 0;
        int errors = 0;

        try (BufferedReader reader = new BufferedReader(new FileReader(csvFile))) {
            String header = reader.readLine();
            if (header == null) {
                throw new IllegalArgumentException("empty symbol CSV");
            }
            String[] columns = parseCsvLine(header);
            int nameColumn = findColumn(columns, "Name");
            int locationColumn = findColumn(columns, "Location");
            int kindColumn = findColumn(columns, "Type");
            int commentColumn = findColumn(columns, "EOL Comment");

            String line;
            while ((line = readCsvRecord(reader)) != null) {
                if (line.isBlank()) {
                    continue;
                }
                String[] fields = parseCsvLine(line);
                String name = field(fields, nameColumn);
                String location = field(fields, locationColumn);
                String kind = field(fields, kindColumn);
                String comment = field(fields, commentColumn);
                if (name.isBlank() || location.isBlank()) {
                    continue;
                }

                try {
                    Address address = toAddr(Long.parseUnsignedLong(location, 16));
                    if (kind.equalsIgnoreCase("Function")) {
                        disassemble(address);
                        Function function = getFunctionAt(address);
                        if (function == null) {
                            function = createFunction(address, null);
                        }
                        if (function != null) {
                            function.setName(name, SourceType.USER_DEFINED);
                            if (!comment.isBlank()) {
                                function.setComment(comment);
                                comments++;
                            }
                            functions++;
                        }
                    }
                    else {
                        Symbol primary = symbols.getPrimarySymbol(address);
                        if (primary == null || primary.getSource() == SourceType.DEFAULT) {
                            symbols.createLabel(address, name, SourceType.USER_DEFINED);
                        }
                        else if (!primary.getName().equals(name)) {
                            primary.setName(name, SourceType.USER_DEFINED);
                        }
                        if (!comment.isBlank()) {
                            CodeUnit unit = listing.getCodeUnitContaining(address);
                            if (unit != null) {
                                unit.setComment(CodeUnit.EOL_COMMENT, comment);
                                comments++;
                            }
                        }
                        labels++;
                    }
                }
                catch (Exception exception) {
                    errors++;
                    if (errors <= 20) {
                        printerr(name + " @ " + location + ": " + exception.getMessage());
                    }
                }
            }
        }

        println("Imported functions=" + functions + ", labels=" + labels +
            ", comments=" + comments + ", errors=" + errors);
    }

    private int findColumn(String[] columns, String name) {
        for (int index = 0; index < columns.length; index++) {
            if (columns[index].trim().equalsIgnoreCase(name)) {
                return index;
            }
        }
        return -1;
    }

    private String field(String[] fields, int column) {
        return column >= 0 && column < fields.length ? fields[column].trim() : "";
    }

    private String[] parseCsvLine(String line) {
        List<String> fields = new ArrayList<>();
        StringBuilder value = new StringBuilder();
        boolean quoted = false;
        for (int index = 0; index < line.length(); index++) {
            char character = line.charAt(index);
            if (character == '"') {
                if (quoted && index + 1 < line.length() && line.charAt(index + 1) == '"') {
                    value.append('"');
                    index++;
                }
                else {
                    quoted = !quoted;
                }
            }
            else if (character == ',' && !quoted) {
                fields.add(value.toString());
                value.setLength(0);
            }
            else {
                value.append(character);
            }
        }
        fields.add(value.toString());
        return fields.toArray(new String[0]);
    }

    private String readCsvRecord(BufferedReader reader) throws Exception {
        String first = reader.readLine();
        if (first == null) {
            return null;
        }
        StringBuilder record = new StringBuilder(first);
        while (hasOpenQuote(record)) {
            String continuation = reader.readLine();
            if (continuation == null) {
                break;
            }
            record.append('\n').append(continuation);
        }
        return record.toString();
    }

    private boolean hasOpenQuote(CharSequence text) {
        boolean quoted = false;
        for (int index = 0; index < text.length(); index++) {
            if (text.charAt(index) != '"') {
                continue;
            }
            if (quoted && index + 1 < text.length() && text.charAt(index + 1) == '"') {
                index++;
            }
            else {
                quoted = !quoted;
            }
        }
        return quoted;
    }
}
