#pragma once

// Memory access semantics.
// This value is a mask; it can be formed by combining the bits from multiple rows in the table below.
enum class MemoryAccess : uint32_t
{
    None = 0x0,
    
    Volatile = 0x1, // This access cannot be optimized away; it has to be executed.

    Aligned = 0x2,  // This access has a known alignment, provided as a literal in
                    // the next operand
};

static char* MemoryAccessToString(MemoryAccess input)
{
    switch (input)
    {
        case MemoryAccess::None:        return "None";
        case MemoryAccess::Volatile:    return "Volatile";
        case MemoryAccess::Aligned:     return "Aligned";
        default:                        return nullptr;
    }
}
 