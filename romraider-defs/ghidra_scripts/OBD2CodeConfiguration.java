//@category OBD
//@menupath Tools.OBD.OBD2 Code Configuration
//@description Process OBD-II code configuration from the binary.

import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionManager;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSpace;
import ghidra.program.model.data.DataType;
import ghidra.program.model.data.DataTypeManager;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.pcode.HighFunction;
import ghidra.program.model.pcode.PcodeOp;
import ghidra.program.model.pcode.PcodeOpAST;
import ghidra.program.model.pcode.Varnode;
import java.util.Iterator;

public class OBD2CodeConfiguration extends GhidraScript {

	private final String OBD_II_FAIL_FUNNAME = "obd_ii_monitor_fail_transition";

	/**
	 * Resolves a varnode to an actual memory address by tracing through P-code operations.
	 * Varnodes can exist in different address spaces (registers, stack, etc.) but may contain
	 * memory addresses as values. This method traces back to find the actual address value.
	 */
	private Address resolveVarnodeToAddress(Varnode vn, int depth) {
		if (depth > 20) {
			println("      [Recursion limit reached]");
			return null;
		}

		String indent = "      " + "  ".repeat(depth);
		println(indent + "Tracing: " + vn + " (space=" + vn.getAddress().getAddressSpace().getName() + ")");

		// If it's a constant, the offset IS the address value
		if (vn.isConstant()) {
			long addressValue = vn.getOffset();
			Address addr = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(addressValue);
			println(indent + "  -> Constant: " + addr);
			return addr;
		}

		// If it's in RAM address space, use the address directly
		if (vn.isAddress()) {
			println(indent + "  -> RAM address: " + vn.getAddress());
			return vn.getAddress();
		}

		// Otherwise, trace back through the defining operation
		PcodeOp def = vn.getDef();
		if (def != null) {
			int opcode = def.getOpcode();
			println(indent + "  -> Def op: " + def.getMnemonic() + " (inputs=" + def.getNumInputs() + ")");

			// For most operations, input[1] contains the address we want
			// (input[0] is typically the address space ID for LOAD/STORE operations)
			if (def.getNumInputs() > 1) {
				println(indent + "  -> Following input[1]");
				return resolveVarnodeToAddress(def.getInput(1), depth + 1);
			}

			// Handle operations with single input
			switch (opcode) {
				case PcodeOp.COPY:
				case PcodeOp.CAST:
				case PcodeOp.INT_ZEXT:
				case PcodeOp.INT_SEXT:
					// These operations pass through values, recurse on input
					return resolveVarnodeToAddress(def.getInput(0), depth + 1);

				case PcodeOp.MULTIEQUAL:
					// PHI node - try first input
					println(indent + "  -> PHI node, following first input");
					return resolveVarnodeToAddress(def.getInput(0), depth + 1);

				default:
					println(indent + "  -> Unhandled single-input op: " + def.getMnemonic());
					// For debugging, show all inputs
					for (int i = 0; i < def.getNumInputs(); i++) {
						Varnode input = def.getInput(i);
						println(indent + "    Input[" + i + "]: " + input);
					}
					break;
			}
		} else {
			println(indent + "  -> No def (parameter or global)");
		}

		// Couldn't resolve - return null
		return null;
	}

	private Address resolveVarnodeToAddress(Varnode vn) {
		return resolveVarnodeToAddress(vn, 0);
	}

	private void extractArgInfo(
		final FunctionManager funcManager,
		final DecompInterface decompiler,
		final Reference ref) {
		final Address callAddr = ref.getFromAddress();

		// Get the function containing this call
		Function callingFunc = funcManager.getFunctionContaining(callAddr);
		if (callingFunc == null) {
			println("WARNING: Could not find function containing call at " + callAddr);
			return;
		}

		// Decompile the calling function
		DecompileResults decompResults = decompiler.decompileFunction(callingFunc, 30, monitor);
		if (!decompResults.decompileCompleted()) {
			println("WARNING: Decompilation failed for function at " + callingFunc.getEntryPoint());
			return;
		}

		HighFunction highFunc = decompResults.getHighFunction();
		if (highFunc == null) {
			println("WARNING: No high function available at " + callAddr);
			return;
		}

		// Find the PcodeOp at this call address
		Iterator<PcodeOpAST> pcodeOps = highFunc.getPcodeOps(callAddr);
		while (pcodeOps.hasNext()) {
			PcodeOpAST pcodeOp = pcodeOps.next();

			// Check if this is a CALL operation
			if (pcodeOp.getOpcode() == PcodeOp.CALL) {
				println("Call at " + callAddr + ":");
				println("  Function: " + callingFunc.getName());

				// Get all input parameters (index 0 is the call target, so start at 1)
				int numArgs = pcodeOp.getNumInputs() - 1;

				final Varnode dtc_num_node = pcodeOp.getInput(5);
				if (! dtc_num_node.isConstant()) {
					println("  ERROR: DTC number is not a constant");
					return;
				}
				final long dtc_num = dtc_num_node.getOffset();

				final Varnode dtc_type_node = pcodeOp.getInput(6);
				if (! dtc_type_node.isConstant()) {
					println("  ERROR: DTC type is not a constant");
					return;
				}
				final long dtc_type = dtc_type_node.getOffset();

				char dtcPrefix;
				switch ((int)dtc_type) {
					case 0: dtcPrefix = 'P'; break;
					case 1: dtcPrefix = 'C'; break;
					case 2: dtcPrefix = 'B'; break;
					case 3: dtcPrefix = 'U'; break;
					default: dtcPrefix = '?'; break;
				}

				String dtcCode = String.format("%c%04X", dtcPrefix, dtc_num);
				String dtcCALName = String.format("CAL_obd_ii_%c%04X", dtcPrefix, dtc_num);
				String dtcLEAName = String.format("LEA_obd_ii_%c%04X", dtcPrefix, dtc_num);

				final Varnode config_node = pcodeOp.getInput(1);
				final Varnode state_node = pcodeOp.getInput(2);

				// Debug: Print varnode information
				println("  Debug config_node:");
				println("    Varnode: " + config_node);
				println("    Address Space: " + config_node.getAddress().getAddressSpace().getName());
				println("    Is Constant: " + config_node.isConstant());
				println("    Is Address: " + config_node.isAddress());
				println("    Offset: 0x" + Long.toHexString(config_node.getOffset()));
				PcodeOp configDef = config_node.getDef();
				if (configDef != null) {
					println("    Def Operation: " + configDef.getMnemonic());
					println("    Def Inputs: " + configDef.getNumInputs());
					for (int i = 0; i < configDef.getNumInputs(); i++) {
						Varnode input = configDef.getInput(i);
						println("      Input[" + i + "]: " + input + " (constant=" + input.isConstant() + ", offset=0x" + Long.toHexString(input.getOffset()) + ")");
					}
				} else {
					println("    Def Operation: null (function parameter or global)");
				}

				println("  Debug state_node:");
				println("    Varnode: " + state_node);
				println("    Address Space: " + state_node.getAddress().getAddressSpace().getName());
				println("    Is Constant: " + state_node.isConstant());
				println("    Is Address: " + state_node.isAddress());
				println("    Offset: 0x" + Long.toHexString(state_node.getOffset()));
				PcodeOp stateDef = state_node.getDef();
				if (stateDef != null) {
					println("    Def Operation: " + stateDef.getMnemonic());
					println("    Def Inputs: " + stateDef.getNumInputs());
					for (int i = 0; i < stateDef.getNumInputs(); i++) {
						Varnode input = stateDef.getInput(i);
						println("      Input[" + i + "]: " + input + " (constant=" + input.isConstant() + ", offset=0x" + Long.toHexString(input.getOffset()) + ")");
					}
				} else {
					println("    Def Operation: null (function parameter or global)");
				}

				// Resolve varnodes to actual memory addresses
				Address configAddr = resolveVarnodeToAddress(config_node);
				Address stateAddr = resolveVarnodeToAddress(state_node);

				if (configAddr != null) {
					println("  Config address: " + configAddr);

					// Add label for config
					try {
						createLabel(configAddr, dtcCALName, true);
						println("    Added label: " + dtcCALName);
					} catch (Exception e) {
						println("    WARNING: Could not add label " + dtcCALName + ": " + e.getMessage());
					}

					// Set data type to u8_obd2level
					try {
						DataTypeManager dtm = currentProgram.getDataTypeManager();
						DataType u8Type = dtm.getDataType("/u8_obd2level");
						if (u8Type != null) {
							createData(configAddr, u8Type);
							println("    Set type: u8_obd2level");
						} else {
							println("    WARNING: Data type 'u8_obd2level' not found");
						}
					} catch (Exception e) {
						println("    WARNING: Could not set type: " + e.getMessage());
					}
				} else {
					println("  WARNING: Could not resolve config_node to memory address");
					println("    Varnode: " + config_node);
				}

				if (stateAddr != null) {
					println("  State address: " + stateAddr);

					// Add label for state
					try {
						createLabel(stateAddr, dtcLEAName, true);
						println("    Added label: " + dtcLEAName);
					} catch (Exception e) {
						println("    WARNING: Could not add label " + dtcLEAName + ": " + e.getMessage());
					}

					// Set data type to struct_dtc_state
					try {
						DataTypeManager dtm = currentProgram.getDataTypeManager();
						DataType structType = dtm.getDataType("/struct_dtc_state");
						if (structType != null) {
							createData(stateAddr, structType);
							println("    Set type: struct_dtc_state");
						} else {
							println("    WARNING: Data type 'struct_dtc_state' not found");
						}
					} catch (Exception e) {
						println("    WARNING: Could not set type: " + e.getMessage());
					}
				} else {
					println("  WARNING: Could not resolve state_node to memory address");
					println("    Varnode: " + state_node);
				}

				println("");
			}
		}
	}

	@Override
	public void run() throws Exception {
		println("OBD-II Code Configuration Analysis");
		println("===================================\n");

		final FunctionManager funcManager = currentProgram.getFunctionManager();
		Function targetFunc = null;
		for (final Function func : funcManager.getFunctions(true)) {
			if (func.getName().equals(OBD_II_FAIL_FUNNAME)) {
				targetFunc = func;
				break;
			}
		}
		if (targetFunc == null) {
			println("ERROR: Function 'obd_ii_monitor_fail_transition' not found!");
			return;
		}

		println("Found function: " + targetFunc.getName() + " at " + targetFunc.getEntryPoint());
		println("\nSearching for all calls to this function...\n");

		// Initialize the decompiler
		final DecompInterface decompiler = new DecompInterface();
		decompiler.openProgram(currentProgram);

		// Get all references to this function
		final ReferenceIterator refIter = currentProgram.getReferenceManager().getReferencesTo(targetFunc.getEntryPoint());

		while (refIter.hasNext()) {
			final Reference ref = refIter.next();
			extractArgInfo(funcManager, decompiler, ref);
			return;
		}

		// Cleanup
		decompiler.dispose();
	}
}
