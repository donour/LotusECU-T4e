# Rename the u8 2D-map lookup (0x00A49724, "lookup3d_interpolated_u8???") to
# lookup3d_interp_u8 and set its signature to match the u16 sibling.
#   uint lookup3d_interp_u8(int x_size, int y_size, uint x_val, uint y_val,
#                           byte *lut, byte *x_axis, byte *y_axis)
# Requires write access (omit -readOnly; GUI project closed).
# @category Labeling
from ghidra.program.model.symbol import SourceType
from ghidra.program.model.listing import ParameterImpl, Function
from ghidra.program.model.data import (IntegerDataType, UnsignedIntegerDataType,
    ByteDataType, PointerDataType)

space = currentProgram.getAddressFactory().getDefaultAddressSpace()
fm = currentProgram.getFunctionManager()

f = fm.getFunctionAt(space.getAddress(0xa49724))
if f is None:
    print("!! no function at 0x00a49724")
else:
    f.setName("lookup3d_interp_u8", SourceType.USER_DEFINED)
    f.setReturnType(UnsignedIntegerDataType(), SourceType.USER_DEFINED)
    bytep = PointerDataType(ByteDataType())
    i = IntegerDataType()
    u = UnsignedIntegerDataType()
    params = [
        ParameterImpl("x_size", i, currentProgram),
        ParameterImpl("y_size", i, currentProgram),
        ParameterImpl("x_val",  u, currentProgram),
        ParameterImpl("y_val",  u, currentProgram),
        ParameterImpl("lut",    bytep, currentProgram),
        ParameterImpl("x_axis", bytep, currentProgram),
        ParameterImpl("y_axis", bytep, currentProgram),
    ]
    f.replaceParameters(params,
        Function.FunctionUpdateType.DYNAMIC_STORAGE_FORMAL_PARAMS,
        True, SourceType.USER_DEFINED)
    print("renamed + signature set: %s @ %s" % (f.getName(), f.getEntryPoint()))
    print("  " + f.getPrototypeString(False, False))
