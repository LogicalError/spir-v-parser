#pragma once

// Declare the modes this module’s stage will execute in. 
// Used by:
//	OpExecutionMode.
enum class ExecutionMode : uint32_t
{
    Invocations = 0,				// Number of times to invoke the geometry stage for
                                    // each input primitive received. The default is to run
                                    // once for each input primitive. If greater than the
                                    // target-dependent maximum, it will fail to compile.
                                    // Only valid with the Geometry Execution Model.
                                    //
                                    // Extra Operands
                                    //	Literal-Number Number-of-invocations
                                    // Required Capability
                                    //	Geom 

    SpacingEqual = 1,				// Requests the tessellation primitive generator to divide
                                    // edges into a collection of equal-sized segments. Only
                                    // valid with one of the tessellation Execution Models.
                                    //
                                    // Required Capability
                                    //	Tess

    SpacingFractionalEven = 2,		// Requests the tessellation primitive generator to divide
                                    // edges into an even number of equal-length segments
                                    // plus two additional shorter fractional segments. Only
                                    // valid with one of the tessellation Execution Models.
                                    //
                                    // Required Capability
                                    //	Tess

    SpacingFractionalOdd = 3,		// Requests the tessellation primitive generator to divide
                                    // edges into an odd number of equal-length segments
                                    // plus two additional shorter fractional segments. Only
                                    // valid with one of the tessellation Execution Models.
                                    //
                                    // Required Capability
                                    //	Tess

    VertexOrderCw = 4,				// Requests the tessellation primitive generator to
                                    // generate triangles in clockwise order. Only valid with
                                    // one of the tessellation Execution Models.
                                    //
                                    // Required Capability
                                    //	Tess

    VertexOrderCcw = 5,				// Requests the tessellation primitive generator to
                                    // generate triangles in counter-clockwise order. Only
                                    // valid with one of the tessellation Execution Models.
                                    //
                                    // Required Capability
                                    //	Tess

    PixelCenterInteger = 6,			// Pixels appear centered on whole-number pixel
                                    // offsets. E.g., the coordinate (0.5, 0.5) appears to
                                    // move to (0.0, 0.0). Only valid with the Fragment
                                    // Execution Model.
                                    //
                                    // Required Capability
                                    //	Shader

    OriginUpperLeft = 7,			// Pixel coordinates appear to originate in the upper left,
                                    // and increase toward the right and downward. Only
                                    // valid with the Fragment Execution Model.
                                    //
                                    // Required Capability
                                    //	Shader

    EarlyFragmentTests = 8,			// Fragment tests are to be performed before fragment
                                    // shader execution. Only valid with the Fragment
                                    // Execution Model.
                                    //
                                    // Required Capability
                                    //	Shader

    PointMode = 9,					// Requests the tessellation primitive generator to
                                    // generate a point for each distinct vertex in the
                                    // subdivided primitive, rather than to generate lines or
                                    // triangles. Only valid with one of the tessellation
                                    // Execution Models.
                                    //
                                    // Required Capability
                                    //	Tess

    Xfb = 10,						// This stage will run in transform feedback-capturing
                                    // mode and this module is responsible for describing
                                    // the transform-feedback setup. See the XfbBuffer,
                                    // Offset, and Stride Decorations.
                                    //
                                    // Required Capability
                                    //	Shader

    DepthReplacing = 11,			// This mode must be declared if this module
                                    // potentially changes the fragment’s depth. Only valid
                                    // with the Fragment Execution Model.
                                    //
                                    // Required Capability
                                    //	Shader

    DepthAny = 12,					// TBD: this should probably be removed. Depth
                                    // testing will always be performed after the shader has
                                    // executed. Only valid with the Fragment Execution
                                    // Model.
                                    //
                                    // Required Capability
                                    //	Shader

    DepthGreater = 13,				// External optimizations may assume depth
                                    // modifications will leave the fragment’s depth as
                                    // greater than or equal to the fragment’s interpolated
                                    // depth value (given by the z component of the
                                    // FragCoord BuiltIn decorated variable). Only valid
                                    // with the Fragment Execution Model.
                                    //
                                    // Required Capability
                                    //	Shader

    DepthLess = 14,					// External optimizations may assume depth
                                    // modifications leave the fragment’s depth less than the
                                    // fragment’s interpolated depth value, (given by the z
                                    // component of the FragCoord BuiltIn decorated
                                    // variable). Only valid with the Fragment Execution
                                    // Model.
                                    //
                                    // Required Capability
                                    //	Shader

    DepthUnchanged = 15,			// External optimizations may assume this stage did not
                                    // modify the fragment’s depth. However,
                                    // DepthReplacing mode must accurately represent
                                    // depth modification. Only valid with the Fragment
                                    // Execution Model.
                                    //
                                    // Required Capability
                                    //	Shader

    LocalSize = 16,					// Indicates the work-group size in the x, y, and z
                                    // dimensions. Only valid with the GLCompute or
                                    // Kernel Execution Models.
                                    //
                                    // Extra Operands
                                    //	Literal-Number x-size
                                    //	Literal-Number y-size
                                    //	Literal-Number z-size

    LocalSizeHint = 17,				// A hint to the compiler, which indicates the most
                                    // likely to be used work-group size in the x, y, and z
                                    // dimensions. Only valid with the Kernel Execution
                                    // Model.
                                    //
                                    // Extra Operands
                                    //	Literal-Number x-size
                                    //	Literal-Number y-size
                                    //	Literal-Number z-size
                                    // Required Capability
                                    //	Kernel

    InputPoints = 18,				// Stage input primitive is points. Only valid with the
                                    // Geometry Execution Model.
                                    //
                                    // Required Capability
                                    //	Geom

    InputLines = 19,				// Stage input primitive is lines. Only valid with the
                                    // Geometry Execution Model.
                                    //
                                    // Required Capability
                                    //	Geom

    InputLinesAdjacency = 20,		// Stage input primitive is lines adjacency. Only valid
                                    // with the Geometry Execution Model.
                                    //
                                    // Required Capability
                                    //	Geom

    InputTriangles = 21,			// For a geometry stage, input primitive is triangles. For
                                    // a tessellation stage, requests the tessellation primitive
                                    // generator to generate triangles. Only valid with the
                                    // Geometry or one of the tessellation Execution
                                    // Models.
                                    //
                                    // Required Capability
                                    //	Geom, Tess

    InputTrianglesAdjacency = 22,	// Geometry stage input primitive is triangles
                                    // adjacency. Only valid with the Geometry Execution
                                    // Model.
                                    //
                                    // Required Capability
                                    //	Geom

    InputQuads = 23,				// Requests the tessellation primitive generator to
                                    // generate quads. Only valid with one of the
                                    // tessellation Execution Models.
                                    //
                                    // Required Capability
                                    //	Tess

    InputIsolines = 24,				// Requests the tessellation primitive generator to
                                    // generate isolines. Only valid with one of the
                                    // tessellation Execution Models.
                                    //
                                    // Required Capability
                                    //	Tess

    OutputVertices = 25,			// For a geometry stage, the maximum number of
                                    // vertices the shader will ever emit in a single
                                    // invocation. For a tessellation-control stage, the
                                    // number of vertices in the output patch produced by
                                    // the tessellation control shader, which also specifies
                                    // the number of times the tessellation control shader is
                                    // invoked. Only valid with the Geometry or one of the
                                    // tessellation Execution Models.
                                    //
                                    // Extra Operand
                                    //	Literal-Number Vertex-count
                                    // Required Capability
                                    //	Geom, Tess

    OutputPoints = 26,				// Stage output primitive is points. Only valid with the
                                    // Geometry Execution Model.
                                    //
                                    // Required	Capability
                                    //	Geom

    OutputLineStrip = 27,			// Stage output primitive is line strip. Only valid with
                                    // the Geometry Execution Model.
                                    //
                                    // Required Capability
                                    //	Geom

    OutputTriangleStrip = 28,		// Stage output primitive is triangle strip. Only valid
                                    // with the Geometry Execution Model.
                                    //
                                    // Required Capability
                                    //	Geom

    VecTypeHint = 29,				// A hint to the compiler, which indicates that most
                                    // operations used in the entry point are explicitly
                                    // vectorized using a particular vector type. Only valid
                                    // with the Kernel Execution Model.
                                    //
                                    // Extra Operand
                                    //	<id> Vector type
                                    // Required Capability
                                    //	Kernel 

    ContractionOff = 30				// Indicates that floating-point-expressions contraction
                                    // is disallowed. Only valid with the Kernel Execution
                                    // Model.
                                    //
                                    // Required Capability
                                    //	Kernel
};

static char* ExecutionModeToString(ExecutionMode input)
{
    switch (input)
    {
        case ExecutionMode::Invocations:				return "Invocations";
        case ExecutionMode::SpacingEqual:				return "SpacingEqual";
        case ExecutionMode::SpacingFractionalEven:		return "SpacingFractionalEven";
        case ExecutionMode::SpacingFractionalOdd:		return "SpacingFractionalOdd";
        case ExecutionMode::VertexOrderCw:				return "VertexOrderCw";
        case ExecutionMode::VertexOrderCcw:				return "VertexOrderCcw";
        case ExecutionMode::PixelCenterInteger:			return "PixelCenterInteger";
        case ExecutionMode::OriginUpperLeft:			return "OriginUpperLeft";
        case ExecutionMode::EarlyFragmentTests:			return "EarlyFragmentTests";
        case ExecutionMode::PointMode:					return "PointMode";
        case ExecutionMode::Xfb:						return "Xfb";
        case ExecutionMode::DepthReplacing:				return "DepthReplacing";
        case ExecutionMode::DepthAny:					return "DepthAny";
        case ExecutionMode::DepthGreater:				return "DepthGreater";
        case ExecutionMode::DepthLess:					return "DepthLess";
        case ExecutionMode::DepthUnchanged:				return "DepthUnchanged";
        case ExecutionMode::LocalSize:					return "LocalSize";
        case ExecutionMode::LocalSizeHint:				return "LocalSizeHint";
        case ExecutionMode::InputPoints:				return "InputPoints";
        case ExecutionMode::InputLines:					return "InputLines";
        case ExecutionMode::InputLinesAdjacency:		return "InputLinesAdjacency";
        case ExecutionMode::InputTriangles:				return "InputTriangles";
        case ExecutionMode::InputTrianglesAdjacency:	return "InputTrianglesAdjacency";
        case ExecutionMode::InputQuads:					return "InputQuads";
        case ExecutionMode::InputIsolines:				return "InputIsolines";
        case ExecutionMode::OutputVertices:				return "OutputVertices";
        case ExecutionMode::OutputPoints:				return "OutputPoints";
        case ExecutionMode::OutputLineStrip:			return "OutputLineStrip";
        case ExecutionMode::OutputTriangleStrip:		return "OutputTriangleStrip";
        case ExecutionMode::VecTypeHint:				return "VecTypeHint";
        case ExecutionMode::ContractionOff:				return "ContractionOff";
        default:										return nullptr;
    }
}
