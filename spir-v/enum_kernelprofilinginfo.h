#pragma once

// Specify the profiling information to be queried.
// This value is a mask; it can be formed by combining the bits from multiple rows in the table below.
// Used by:
//  OpCaptureEventProfilingInfo.
enum class KernelProfilingInfo : uint32_t
{
    None = 0x0,

    CmdExecTime = 0x1,  // Indicates that the profiling info queried is the execution
                        // time.
                        // 
                        // Required Capability
                        //  Kernel
};


static char* KernelProfilingInfoToString(KernelProfilingInfo input)
{
    switch (input)
    {
        case KernelProfilingInfo::None:         return "None";
        case KernelProfilingInfo::CmdExecTime:  return "CmdExecTime";
        default:                                return nullptr;
    }
}
 