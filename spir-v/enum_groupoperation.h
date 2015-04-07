#pragma once

// Defines the class of workgroup or subgroup operation. 
// Used by:
//	OpGroupIAdd, OpGroupFAdd, OpGroupFMin, OpGroupUMin,
//	OpGroupSMin, OpGroupFMax, OpGroupUMax, OpGroupSMax
enum class GroupOperation : uint32_t
{
	Reduce = 0,			// Returns the result of a reduction operation for all values
						// of a specific value X specified by workitems within a
						// workgroup.
						// 
						// Required Capability
						//	Kernel

	InclusiveScan = 1,	// The inclusive scan performs a binary operation with an
						// identity I and n(where n is the size of the workgroup)
						// elements[a0, a1, ... an - 1] and returns[a0, (a0 op a1),
						// ... (a0 op a1 op ... op an - 1)]
						// 
						// Required Capability
						//	Kernel

	ExclusiveScan = 2	// The exclusive scan performs a binary operation with an
						// identity I and n(where n is the size of the workgroup)
						// elements[a0, a1, ... an - 1] and returns[I, a0, (a0 op a1), ...
						// (a0 op a1 op ... op an - 2)].
						// 
						// Required Capability
						//	Kernel
};


static char* GroupOperationToString(GroupOperation input)
{
	switch (input)
	{
		case GroupOperation::Reduce:		return "Reduce";
		case GroupOperation::InclusiveScan:	return "InclusiveScan";
		case GroupOperation::ExclusiveScan:	return "ExclusiveScan";
		default:	return "??";
	}
}
