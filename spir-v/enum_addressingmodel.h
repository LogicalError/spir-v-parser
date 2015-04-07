#pragma once

// Used by:
//	OpMemoryModel.
enum class AddressingModel : uint32_t
{
    Logical = 0,
    Physical32 = 1,		// Indicates a 32-bit module, where the address width is equal to 32 bits. Requires Addr Capability.
    Physical64 = 2		// Indicates a 64-bit module, where the address width is equal to 64 bits. Requires Addr Capability.
};

static char* AddressingModelToString(AddressingModel input)
{
    switch (input)
    {
        case AddressingModel::Logical:		return "Logical";
        case AddressingModel::Physical32:	return "Physical32";
        case AddressingModel::Physical64:	return "Physical64";
        default:							return nullptr;
    }
}
