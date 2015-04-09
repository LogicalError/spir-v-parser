#pragma once

// Enables fast math operations which are otherwise unsafe.
// - Only valid on OpFAdd, OpFSub, OpFMul, OpFDiv, OpFRem, and OpFMod instructions.
// This value is a mask; 
//  it can be formed by combining the bits from multiple rows in the table below.
enum class FPFastMathMode : uint32_t
{
    None = 0x0,
    
    NotNaN = 0x1,       // Assume parameters and result are not NaN.
                        //
                        // Required Capability
                        //  Kernel

    NotInf = 0x2,       // Assume parameters and result are not +/- Inf.
                        //
                        // Required Capability
                        //  Kernel
    
    NSZ = 0x4,          // Treat the sign of a zero parameter or result as
                        // insignificant.
                        //
                        // Required Capability
                        //  Kernel

    AllowRecip = 0x8,   // Allow the usage of reciprocal rather than perform a
                        // division.
                        //
                        // Required Capability
                        //  Kernel

    Fast = 0x10         // Allow algebraic transformations according to real-number
                        // associative and distibutive algebra. This flag implies all
                        // the others.
                        //
                        // Required Capability
                        //  Kernel
};

static char* FPFastMathModeToString(FPFastMathMode input)
{
    switch (input)
    {
        case FPFastMathMode::None:          return "None";
        case FPFastMathMode::NotNaN:        return "NotNaN";
        case FPFastMathMode::NotInf:        return "NotInf";
        case FPFastMathMode::NSZ:           return "NSZ";
        case FPFastMathMode::AllowRecip:    return "AllowRecip";
        case FPFastMathMode::Fast:          return "Fast";
        default:                            return nullptr;
    }
}
