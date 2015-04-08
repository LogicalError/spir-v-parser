#pragma once

// Adds additional information to the return type and to each parameter of a function.
enum class FunctionParameterAttribute : uint32_t
{
	Zext = 0,			// Value should be zero extended if needed.
						// 
						// Required Capability
						//	Kernel

	Sext = 1,			// Value should be sign extended if needed.
						// 
						// Required Capability
						//	Kernel

	ByVal = 2,			// This indicates that the pointer parameter should really be
						// passed by value to the function. Only valid for pointer
						// parameters (not for ret value).
						// 
						// Required Capability
						//	Kernel

	Sret = 3,			// Indicates that the pointer parameter specifies the address
						// of a structure that is the return value of the function in the
						// source program. Only applicable to the first parameter
						// which must be a pointer parameters.
						// 
						// Required Capability
						//	Kernel

	NoAlias = 4,		// Indicates that the memory pointed by a pointer parameter
						// is not accessed via pointer values which are not derived
						// from this pointer parameter. Only valid for pointer
						// parameters. Not valid on return values.
						// 
						// Required Capability
						//	Kernel

	NoCapture = 5,		// The callee does not make a copy of the pointer parameter
						// into a location that is accessible after returning from the
						// callee. Only valid for pointer parameters. Not valid on
						// return values.
						// 
						// Required Capability
						//	Kernel

	SVM = 6,			// CL TBD
						// 
						// Required Capability
						//	Kernel

	NoWrite = 7,		// Can only read the memory pointed by a pointer
						// parameter. Only valid for pointer parameters. Not valid
						// on return values.
						// 
						// Required Capability
						//	Kernel

	NoReadWrite = 8,	// Cannot dereference the memory pointed by a pointer
						// parameter. Only valid for pointer parameters. Not valid
						// on return values.
						// 
						// Required Capability
						//	Kernel
};

static char* FunctionParameterAttributeToString(FunctionParameterAttribute input)
{
	switch (input)
	{
		case FunctionParameterAttribute::Zext:			return "Zext";
		case FunctionParameterAttribute::Sext:			return "Sext";
		case FunctionParameterAttribute::ByVal:			return "ByVal";
		case FunctionParameterAttribute::Sret:			return "Sret";
		case FunctionParameterAttribute::NoAlias:		return "NoAlias";
		case FunctionParameterAttribute::NoCapture:		return "NoCapture";
		case FunctionParameterAttribute::SVM:			return "SVM";
		case FunctionParameterAttribute::NoWrite:		return "NoWrite";
		case FunctionParameterAttribute::NoReadWrite:	return "NoReadWrite";
		default:										return nullptr;
	}
}

