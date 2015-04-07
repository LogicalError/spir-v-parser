#pragma once

// Memory classification and ordering semantics.
// This value is a mask; it can be formed by combining the bits from multiple rows in the table below.
//
// Used by:
//	OpMemoryBarrier, OpAtomicLoad, OpAtomicStore, OpAtomicExchange, 
//	OpAtomicCompareExchange, OpAtomicCompareExchangeWeak, 
//	OpAtomicIIncrement, OpAtomicIDecrement, OpAtomicIAdd, 
//	OpAtomicISub, OpAtomicUMin, OpAtomicUMax, OpAtomicAnd, 
//	OpAtomicOr, OpAtomicXor, OpAtomicIMin, OpAtomicIMax
enum class MemorySemantics : uint32_t
{
	None = 0x0,
	
	Relaxed = 0x1,					// TBD

	SequentiallyConsistent = 0x2,	// All observers will see this memory access in the same order
									// WRT to other sequentially-consistent memory accesses from
									// this invocation.

	Acquire = 0x4,					// All memory operations provided in program order after this
									// memory operation will execute after this memory operation.

	Release = 0x8,					// All memory operations provided in program order before
									// this memory operation will execute before this memory
									// operation.

	UniformMemory = 0x10,			// Filter the memory operations being constrained to just those
									// accessing Uniform Storage Class memory.

	SubgroupMemory = 0x20,			// The memory semantics only have to be correct WRT to this
									// invocation’s subgroup memory.

	WorkgroupLocalMemory = 0x40,	// The memory semantics only have to be correct WRT to this
									// invocation’s local workgroup memory.

	WorkgroupGlobalMemory = 0x80,	// The memory semantics only have to be correct WRT to this
									// invocation’s global workgroup memory.

	AtomicCounterMemory = 0x100,	// Filter the memory operations being constrained to just those
									// accessing AtomicCounter Storage Class memory.

	ImageMemory = 0x200,			// Filter the memory operations being constrained to just those
									// accessing images (see OpTypeSampler Content).
};

static char* MemorySemanticsToString(MemorySemantics input)
{
	switch (input)
	{
		case MemorySemantics::None:						return "None";
		case MemorySemantics::Relaxed:					return "Relaxed";
		case MemorySemantics::SequentiallyConsistent:	return "SequentiallyConsistent";
		case MemorySemantics::Acquire:					return "Acquire";
		case MemorySemantics::Release:					return "Release";
		case MemorySemantics::UniformMemory:			return "UniformMemory";
		case MemorySemantics::SubgroupMemory:			return "SubgroupMemory";
		case MemorySemantics::WorkgroupLocalMemory:		return "WorkgroupLocalMemory";
		case MemorySemantics::WorkgroupGlobalMemory:	return "WorkgroupGlobalMemory";
		case MemorySemantics::AtomicCounterMemory:		return "AtomicCounterMemory";
		case MemorySemantics::ImageMemory:				return "ImageMemory";
		default:	return "??";
	}
}
