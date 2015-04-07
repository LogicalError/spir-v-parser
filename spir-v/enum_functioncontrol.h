#pragma once

// This value is a mask; it can be formed by combining the bits from multiple rows in the table below.
// Used by:
//	OpFunction.
enum class FunctionControl : uint32_t
{
	InLine = 1,		// Strong request, to the extent possible, to inline the function.

	DontInline = 2,	// Strong request, to the extent possible, to not inline the function.

	Pure = 4,		// Compiler can assume this function has no side effect, but 
					// might read global memory or read through dereferenced
					// function parameters.Always computes the same result for
					// the same argument values.

	Const = 8		// Compiler can assume this function has no side effects, and
					// will not access global memory or dereference function
					// parameters. Always computes the same result for the same
					// argument values.
};

static char* FunctionControlMaskToString(FunctionControl input)
{
	switch (input)
	{
		case FunctionControl::InLine:		return "InLine";
		case FunctionControl::DontInline:	return "DontInline";
		case FunctionControl::Pure:			return "Pure";
		case FunctionControl::Const:		return "Const";
		default:	return "??";
	}
}
