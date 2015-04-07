#pragma once

// Used when Decoration is BuiltIn.
// Apply to either
// - the result <id> of the variable declaration of the built-in variable, or
// - a structure member, if the built-in is a member of a structure.
// These have the semantics described by their originating API and high-level language environments.
// TBD: make these native to this specification.
enum class BuiltIn : uint32_t
{
	Position					= 0,	// Required Capability: Shader
	PointSize					= 1,	// Required Capability: Shader
	ClipVertex					= 2,	// Required Capability: Shader
	ClipDistance				= 3,	// Required Capability: Shader
	CullDistance				= 4,	// Required Capability: Shader
	VertexId					= 5,	// Required Capability: Shader
	InstanceId					= 6,	// Required Capability: Shader
	PrimitiveId					= 7,	// Required Capability: Geom, Tess
	InvocationId				= 8,	// Required Capability: Geom, Tess
	Layer						= 9,	// Required Capability: Geom
	ViewportIndex				= 10,	// Required Capability: Geom
	TessLevelOuter				= 11,	// Required Capability: Tess
	TessLevelInner				= 12,	// Required Capability: Tess
	TessCoord					= 13,	// Required Capability: Tess
	PatchVertices				= 14,	// Required Capability: Tess
	FragCoord					= 15,	// Required Capability: Shader
	PointCoord					= 16,	// Required Capability: Shader
	FrontFacing					= 17,	// Required Capability: Shader
	SampleId					= 18,	// Required Capability: Shader
	SamplePosition				= 19,	// Required Capability: Shader
	SampleMask					= 20,	// Required Capability: Shader
	FragColor					= 21,	// Required Capability: Shader
	FragDepth					= 22,	// Required Capability: Shader
	HelperInvocation			= 23,	// Required Capability: Shader
	NumWorkgroups				= 24,
	WorkgroupSize				= 25,
	WorkgroupId					= 26,
	LocalInvocationId			= 27,
	GlobalInvocationId			= 28,
	LocalInvocationIndex		= 29,	// Required Capability: Shader
	WorkDim						= 30,	// Required Capability: Kernel
	GlobalSize					= 31,	// Required Capability: Kernel
	EnqueuedWorkgroupSize		= 32,	// Required Capability: Kernel
	GlobalOffset				= 33,	// Required Capability: Kernel
	GlobalLinearId				= 34,	// Required Capability: Kernel
	WorkgroupLinearId			= 35,	// Required Capability: Kernel
	SubgroupSize				= 36,	// Required Capability: Kernel
	SubgroupMaxSize				= 37,	// Required Capability: Kernel
	NumSubgroups				= 38,	// Required Capability: Kernel
	NumEnqueuedSubgroups		= 39,	// Required Capability: Kernel
	SubgroupId					= 40,	// Required Capability: Kernel
	SubgroupLocalInvocationId	= 41	// Required Capability: Kernel
};

static char* BuiltInToString(BuiltIn input)
{
	switch (input)
	{
		case BuiltIn::Position:						return "Position"; 
		case BuiltIn::PointSize:					return "PointSize"; 
		case BuiltIn::ClipVertex:					return "ClipVertex"; 
		case BuiltIn::ClipDistance:					return "ClipDistance"; 
		case BuiltIn::CullDistance:					return "CullDistance"; 
		case BuiltIn::VertexId:						return "VertexId"; 
		case BuiltIn::InstanceId:					return "InstanceId"; 
		case BuiltIn::PrimitiveId:					return "PrimitiveId";  
		case BuiltIn::InvocationId:					return "InvocationId";  
		case BuiltIn::Layer:						return "Layer"; 
		case BuiltIn::ViewportIndex:				return "ViewportIndex"; 
		case BuiltIn::TessLevelOuter:				return "TessLevelOuter"; 
		case BuiltIn::TessLevelInner:				return "TessLevelInner"; 
		case BuiltIn::TessCoord:					return "TessCoord"; 
		case BuiltIn::PatchVertices:				return "PatchVertices"; 
		case BuiltIn::FragCoord:					return "FragCoord"; 
		case BuiltIn::PointCoord:					return "PointCoord"; 
		case BuiltIn::FrontFacing:					return "FrontFacing"; 
		case BuiltIn::SampleId:						return "SampleId"; 
		case BuiltIn::SamplePosition:				return "SamplePosition"; 
		case BuiltIn::SampleMask:					return "SampleMask"; 
		case BuiltIn::FragColor:					return "FragColor"; 
		case BuiltIn::FragDepth:					return "FragDepth"; 
		case BuiltIn::HelperInvocation:				return "HelperInvocation"; 
		case BuiltIn::NumWorkgroups:				return "NumWorkgroups";
		case BuiltIn::WorkgroupSize:				return "WorkgroupSize";
		case BuiltIn::WorkgroupId:					return "WorkgroupId";
		case BuiltIn::LocalInvocationId:			return "LocalInvocationId";
		case BuiltIn::GlobalInvocationId:			return "GlobalInvocationId";
		case BuiltIn::LocalInvocationIndex:			return "LocalInvocationIndex"; 
		case BuiltIn::WorkDim:						return "WorkDim"; 
		case BuiltIn::GlobalSize:					return "GlobalSize"; 
		case BuiltIn::EnqueuedWorkgroupSize:		return "EnqueuedWorkgroupSize"; 
		case BuiltIn::GlobalOffset:					return "GlobalOffset"; 
		case BuiltIn::GlobalLinearId:				return "GlobalLinearId"; 
		case BuiltIn::WorkgroupLinearId:			return "WorkgroupLinearId"; 
		case BuiltIn::SubgroupSize:					return "SubgroupSize"; 
		case BuiltIn::SubgroupMaxSize:				return "SubgroupMaxSize"; 
		case BuiltIn::NumSubgroups:					return "NumSubgroups"; 
		case BuiltIn::NumEnqueuedSubgroups:			return "NumEnqueuedSubgroups"; 
		case BuiltIn::SubgroupId:					return "SubgroupId"; 
		case BuiltIn::SubgroupLocalInvocationId:	return "SubgroupLocalInvocationId"; 
		default:	return "??";
	}
}
