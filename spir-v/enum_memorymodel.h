#pragma once

// Used by:
//	OpMemoryModel.
enum class MemoryModel : uint32_t
{
	Simple		= 0,	// No shared memory consistency issues. Requires Shader Capability.

	GLSL450		= 1,	// Memory model needed by later versions of GLSL and ESSL. 
						// Works across multiple versions. Requires Shader Capability.

	OpenCL1_2	= 2,	// OpenCL 1.2 memory model. Requires Kernel Capability.
	OpenCL2_0	= 3,	// OpenCL 2.0 memory model. Requires Kernel Capability.
	OpenCL2_1	= 4		// OpenCL 2.1 memory model. Requires Kernel Capability.
};

static char* MemoryModelToString(MemoryModel input)
{
	switch (input)
	{
		case MemoryModel::Simple:		return "Simple";
		case MemoryModel::GLSL450:		return "GLSL450";
		case MemoryModel::OpenCL1_2:	return "OpenCL1_2";
		case MemoryModel::OpenCL2_0:	return "OpenCL2_0";
		case MemoryModel::OpenCL2_1:	return "OpenCL2_1";
		default:	return "??";
	}
}