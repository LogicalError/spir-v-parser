#pragma once

// Class of storage for declared variables (does not include intermediate values).
// Used by:
//	OpTypePointer, OpVariable, OpVariableArray, 
//	OpGenericCastToPtrExplicit
enum class StorageClass : uint32_t
{
	UniformConstant = 0,	// Shared externally, read - only memory, visible across all
							// instantiations or work groups.Graphics uniform memory.
							// 
							// Required Capability
							//	OpenCL Constant memory.

	Input = 1,				// Input from pipeline.Read only. 
							//
							// Required Capability
							//	Shader

	Uniform = 2,			// Shared externally, visible across all instantiations or work
							// groups. 
							//
							// Required Capability
							//	Shader

	Output = 3,				// Output to pipeline. Shader

	WorkgroupLocal = 4,		// Shared across all work items within a work group.
							// OpenGL "shared". 
							//
							// Required Capability
							//	OpenCL local memory.

	WorkgroupGlobal = 5,	// Visible across all work items of all work groups.OpenCL
							// global memory.

	PrivateGlobal = 6,		// Accessible across functions within a module, non - IO(not
							// visible outside the module). 
							//
							// Required Capability
							//	Shader

	Function = 7,			// A variable local to a function. Shader

	Generic = 8,			// A generic pointer, which overloads StoragePrivate,
							// StorageLocal, StorageGlobal. not a real storage class. 
							//
							// Required Capability
							//	Kernel

	Private = 9,			// Private to a work - item and is not visible to another
							// work - item.OpenCL private memory.
							//
							// Required Capability
							//	Kernel

	AtomicCounter = 10		// For holding atomic counters. 
							//
							// Required Capability
							//	Shader
};

static char* StorageClassToString(StorageClass input)
{
	switch (input)
	{
		case StorageClass::UniformConstant:		return "UniformConstant";
		case StorageClass::Input:				return "Input";
		case StorageClass::Uniform:				return "Uniform";
		case StorageClass::Output:				return "Output";
		case StorageClass::WorkgroupLocal:		return "WorkgroupLocal";
		case StorageClass::WorkgroupGlobal:		return "WorkgroupGlobal";
		case StorageClass::PrivateGlobal:		return "PrivateGlobal";
		case StorageClass::Function:			return "Function";
		case StorageClass::Generic:				return "Generic";
		case StorageClass::Private:				return "Private";
		case StorageClass::AtomicCounter:		return "AtomicCounter";
		default:								return nullptr;
	}
}
