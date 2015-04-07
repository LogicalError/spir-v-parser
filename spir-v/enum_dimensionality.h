#pragma once

// Dimensionality of a texture. 
// Used by:
//	OpTypeSampler.
enum class Dimensionality : uint32_t
{
    Dim1D = 0,
    Dim2D = 1,
    Dim3D = 2,
    DimCube = 3,	// Required Capability: Shader
    DimRect = 4,	// Required Capability: Shader
    DimBuffer = 5,
};

static char* DimensionalityToString(Dimensionality input)
{
    switch (input)
    {
        case Dimensionality::Dim1D:		return "1D";
        case Dimensionality::Dim2D:		return "2D";
        case Dimensionality::Dim3D:		return "3D";
        case Dimensionality::DimCube:	return "Cube";
        case Dimensionality::DimRect:	return "Rect";
        case Dimensionality::DimBuffer:	return "Buffer";
        default:						return nullptr;
    }
}
