#pragma once

// Define the filter mode of read image extended instructions.
enum class SamplerFilterMode : uint32_t
{
	Nearest = 16,		// Use filter nearset mode when performing a read image
						// operation. 
						//
						// Required Capability
						//	Kernel

	Linear = 32			// Use filter linear mode when performing a read image
						// operation. 
						//
						// Required Capability
						//	Kernel
};

static char* SamplerFilterModeToString(SamplerFilterMode input)
{
	switch (input)
	{
		case SamplerFilterMode::Nearest:	return "Nearest";
		case SamplerFilterMode::Linear:		return "Linear";
		default:	return "??";
	}
}

