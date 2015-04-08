#pragma once

// Used by:
//	OpMemoryModel.
enum class ExecutionModel : uint32_t
{
	Vertex					= 0,	// Vertex shading stage.
	TessellationControl		= 1,	// Tessellation control (or hull) shading stage.
	TessellationEvaluation	= 2,	// Tessellation evaluation (or domain) shading stage.
	Geometry				= 3,	// Geometry shading stage.
	Fragment				= 4,	// Fragment shading stage.
	GLCompute				= 5,	// Graphical compute shading stage.
	Kernel					= 6		// Compute kernel.
};

static char* ExecutionModelToString(ExecutionModel input)
{
	switch (input)
	{
		case ExecutionModel::Vertex:					return "Vertex";
		case ExecutionModel::TessellationControl:		return "TessellationControl";
		case ExecutionModel::TessellationEvaluation:	return "TessellationEvaluation";
		case ExecutionModel::Geometry:					return "Geometry";
		case ExecutionModel::Fragment:					return "Fragment";
		case ExecutionModel::GLCompute:					return "GLCompute";
		case ExecutionModel::Kernel:					return "Kernel";
		default:										return nullptr;
	}
}

