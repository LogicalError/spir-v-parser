#pragma once

// Scope of execution.
// Used by:
//  OpControlBarrier, OpMemoryBarrier, OpAtomicLoad, OpAtomicStore, OpAtomicExchange, 
//  OpAtomicCompareExchange, OpAtomicCompareExchangeWeak, OpAtomicIIncrement, 
//  OpAtomicIDecrement, OpAtomicIAdd, OpAtomicISub, OpAtomicUMin,OpAtomicUMax, 
//  OpAtomicAnd, OpAtomicOr, OpAtomicXor, OpAsyncGroupCopy, OpWaitGroupEvents, 
//  OpGroupAll, OpGroupAny, OpGroupBroadcast, OpGroupIAdd, OpGroupFAdd, OpGroupFMin, 
//  OpGroupUMin, OpGroupSMin, OpGroupFMax, OpGroupUMax, OpGroupSMax, 
//  OpGroupReserveReadPipePackets, OpGroupReserveWritePipePackets, 
//  OpGroupCommitReadPipe, OpGroupCommitWritePipe, OpAtomicIMin, OpAtomicIMax
enum class ExecutionScope : uint32_t
{
    CrossDevice = 0,    // Everything executing on all the execution devices in the
                        // system.

    Device = 1,         // Everything executing on the device executing this
                        // invocation.

    Workgroup = 2,      // All invocations for the invoking workgroup.

    Subgroup = 3,       // All invocations in the currently executing subgroup.
};


static char* ExecutionScopeToString(ExecutionScope input)
{
    switch (input)
    {
        case ExecutionScope::CrossDevice:   return "CrossDevice";
        case ExecutionScope::Device:        return "Device";
        case ExecutionScope::Workgroup:     return "Workgroup";
        case ExecutionScope::Subgroup:      return "Subgroup";
        default:                            return nullptr;
    }
}
