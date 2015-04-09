#pragma once

// This value is a mask; it can be formed by combining the bits from multiple rows in the table below.
// Used by:
//  OpLoopMerge.
enum class LoopControl : uint32_t
{
    None = 0x0,
    Unroll = 0x1,       // Strong request, to the extent possible, to unroll or unwind
                        // this loop.
    DontUnroll = 0x2,   // Strong request, to the extent possible, to keep this loop as a
                        // loop, without unrolling.
};

static char* LoopControlToString(LoopControl input)
{
    switch (input)
    {
        case LoopControl::None:         return "None";
        case LoopControl::Unroll:       return "Unroll";
        case LoopControl::DontUnroll:   return "DontUnroll";
        default:                        return nullptr;
    }
}
