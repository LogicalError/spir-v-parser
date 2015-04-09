#pragma once

// Used by:
//  OpDecorate and OpMemberDecorate.
enum class Decoration : uint32_t
{
    PrecisionLow = 0,           // Apply as described in the ES Precision section. 
                                // 
                                // Required Capability
                                //  Shader

    PrecisionMedium = 1,        // Apply as described in the ES Precision section. 
                                // 
                                // Required Capability
                                //  Shader

    PrecisionHigh = 2,          // Apply as described in the ES Precision section. 
                                // 
                                // Required Capability
                                //  Shader

    Block = 3,                  // Apply to a structure type to establish it is  
                                // A non-SSBO-like shader-interface block. 
                                // TBD can this be removed? Probably doesn't add 
                                // anything over a nonwritable structure in 
                                // the UniformConstant or Uniform storage class.
                                // with a Binding and DescriptorSet decoration. 
                                // 
                                // Required Capability
                                //  Shader

    BufferBlock = 4,            // Apply to a structure type to establish it is 
                                // an SSBO-like shader-interface block. 
                                // TBD can this be removed? Probably doesn't add 
                                // anything over a structure in the UniformConstant 
                                // or Uniform storage class. 
                                // with a Binding and DescriptorSet decoration. 
                                // 
                                // Required Capability
                                //  Shader

    RowMajor = 5,               // Apply to a variable or a member of a structure.
                                // Must decorate an entity whose type is a matrix.
                                // Indicates that components within a row are contiguous in memory. 
                                // 
                                // Required Capability
                                //  Matrix

    ColMajor = 6,               // Apply to a variable or a member of a structure.
                                // Must decorate an entity whose type is a matrix.
                                // Indicates that components within a column are contiguous in memory. 
                                // 
                                // Required Capability
                                //  Matrix

    GLSLShared = 7,             // Apply to a structure type to get GLSL shared memory layout. 
                                // 
                                // Required Capability
                                //  Shader

    GLSLStd140 = 8,             // Apply to a structure type to get GLSL std140 memory layout. 
                                // 
                                // Required Capability
                                //  Shader

    GLSLStd430 = 9,             // Apply to a structure type to get GLSL std430 memory layout. 
                                // 
                                // Required Capability
                                //  Shader 

    GLSLPacked = 10,            // Apply to a structure type to get GLSL packed memory layout. 
                                // 
                                // Required Capability
                                //  Shader

    Smooth = 11,                // Apply to a variable or a member of a structure. 
                                // Indicates that perspective-correct interpolation must be used.
                                // Only valid for the Input and Output Storage Classes. 
                                // 
                                // Required Capability
                                //  Shader

    Noperspective = 12,         // Apply to a variable or a member of a structure. 
                                // Indicates that linear, non-perspective correct, 
                                // interpolation must be used.
                                // Only valid for the Input and Output Storage Classes. 
                                // 
                                // Required Capability
                                //  Shader

    Flat = 13,                  // Apply to a variable or a member of a structure. 
                                // Indicates no interpolation will be done.
                                // The non-interpolated value will come from a vertex, 
                                // as described in the API specification.
                                // Only valid for the Input and Output Storage Classes. 
                                // 
                                // Required Capability
                                //  Shader

    Patch = 14,                 // Apply to a variable or a member of a structure. 
                                // Indicates a tessellation patch.
                                // Only valid for the Input and Output Storage Classes. 
                                //
                                // Required Capability
                                //  Tess

    Centroid = 15,              // Apply to a variable or a member of a structure.
                                // When used with multi-sampling rasterization, allows 
                                // a single interpolation location for an entire pixel.
                                // The interpolation location must lie in both the pixel 
                                // and in the primitive being rasterized.
                                // Only valid for the Input and Output Storage Classes. 
                                // 
                                // Required Capability
                                //  Shader

    Sample = 16,                // Apply to a variable or a member of a structure.
                                // When used with multi-sampling rasterization, 
                                // requires per-sample interpolation. 
                                // The interpolation locations must be the locations of the samples 
                                // lying in both the pixel and in the primitive being rasterized.
                                // Only valid for the Input and Output Storage Classes. 
                                // 
                                // Required Capability
                                //  Shader

    Invariant = 17,             // Apply to a variable, to indicate expressions 
                                // computing its value be done invariant with respect 
                                // to other modules computing the same expressions. 
                                // 
                                // Required Capability
                                //  Shader

    Restrict = 18,              // Apply to a variable, to indicate the compiler may 
                                // compile as if there is no aliasing.
                                // See the Aliasing section for more detail. 

    Aliased = 19,               // Apply to a variable, to indicate the compiler is 
                                // to generate accesses to the variable that work correctly 
                                // in the presence of aliasing.
                                // See the Aliasing section for more detail.

    Volatile = 20,              // Apply to a variable, to indicate the memory 
                                // holding the variable is volatile.
                                // See the Memory Model section for more detail. 

    Constant = 21,              // Indicates that a global variable is constant and 
                                // will never be modified.
                                // Only allowed on global variables. 
                                // 
                                // Required Capability
                                //  Kernel

    Coherent = 22,              // Apply to a variable, to indicate the memory holding 
                                // the variable is coherent.
                                // See the Memory Model section for more detail.

    Nonwritable = 23,           // Apply to a variable, to indicate the memory holding 
                                // the variable is not writable, and that this module 
                                // does not write to it. 

    Nonreadable = 24,           // Apply to a variable, to indicate the memory holding 
                                // the variable is not readable, and that this module 
                                // does not read from it. 

    Uniform = 25,               // Apply to a variable or a member of a structure. 
                                // Asserts that the value backing the decorated <id> is 
                                // dynamically uniform across all instantiations that 
                                // might run in parallel. 
                                // 
                                // Required Capability
                                //  Shader 

    NoStaticUse = 26,           // Apply to a variable to indicate that it is known that 
                                // this module does not read or write it.
                                // Useful for establishing interface. 
                                // TBD consider removing this? 

    CPacked = 27,               // Marks a structure type as "packed", indicating that 
                                // the alignment of the structure is one and that there
                                // is no padding between structure members. 
                                // 
                                // Required Capability
                                //  Kernel 

    FPSaturatedConversion = 28, // Indicates that a conversion to an integer type is saturated.
                                // Only valid for conversion instructions to integer type. 
                                // 
                                // Required Capability
                                //  Kernel 

    Stream = 29,                // Apply to a variable or a member of a structure. 
                                // Indicates the stream number to put an output on. 
                                // Only valid for the Output Storage Class and the 
                                // Geometry Execution Model. 
                                // 
                                // Required Capability
                                //  Geom 
                                // Extra Operands
                                //  Literal-Number Stream number 

    Location = 30,              // Apply to a variable or a structure member.
                                // Forms the main linkage for Storage Class Input 
                                // and Output variables : 
                                //  - between the API and vertex-stage inputs,
                                //  - between consecutive programmable stages, or
                                //  - between fragment-stage outputs and the API.
                                // Only valid for the Input and Output Storage Classes. 
                                // 
                                // Required Capability
                                //  Shader 
                                // Extra Operands
                                //  Literal-Number Location 

    Component = 31,             // Apply to a variable or a member of a structure. 
                                // Indicates which component within a Location will 
                                // be taken by the decorated entity.
                                // Only valid for the Input and Output Storage Classes. 
                                // 
                                // Required Capability
                                //  Shader 
                                // Extra Operands
                                //  Literal-Number Component-within-a-vector 

    Index = 32,                 // Apply to a variable to identify a blend equation 
                                // input index, used as described in the API specification. 
                                // Only valid for the Output Storage Class and 
                                // the Fragment Execution Model. 
                                // 
                                // Required Capability
                                //  Shader 
                                // Extra Operands
                                //  Literal-Number Index 

    Binding = 33,               // Apply to a variable.Part of the main linkage 
                                // between the API and SPIR-V modules for memory buffers, textures, etc.
                                // See the API specification for more information. 
                                // 
                                // Required Capability
                                //  Shader 
                                // Extra Operands
                                //  Literal-Number Binding point 

    DescriptorSet = 34,         // Apply to a variable.Part of the main linkage between 
                                // the API and SPIR-V modules for memory buffers, textures, etc.
                                // See the API specification for more information. 
                                // 
                                // Required Capability
                                //  Shader 
                                // Extra Operands
                                //  Literal-Number Descriptor set 

    Offset = 35,                // Apply to a structure member.
                                // This gives the byte offset of the member 
                                // relative to the beginning of the structure.
                                // Can be used, for example, by both uniform and 
                                // transform-feedback buffers. 
                                // 
                                // Extra Operands
                                //  Literal-Number Byte offset 

    Alignment = 36,             // TBD: This can probably be removed. 
                                // 
                                // Extra Operands
                                //  Literal-Number Declared-alignment

    XfbBuffer = 37,             // Apply to a variable or a member of a structure. 
                                // Indicates which transform-feedback buffer an output is written to.
                                // Only valid for the Output Storage Classes of vertex processing Execution Models. 
                                // 
                                // Required Capability
                                //  Shader 
                                // Extra Operands
                                //  Literal-Number XFB-Buffer-number

    Stride = 38,                // The stride, in bytes, of array elements or transform-feedback buffer vertices. 
                                // 
                                // Required Capability
                                //  Shader 
                                // Extra Operands
                                //  Literal-Number Stride

    Built_In = 39,              // Apply to a variable or a member of a structure. 
                                // Indicates which built-in variable the entity represents. 
                                // 
                                // Required Capability
                                //  Shader 
                                // Extra Operands
                                //  Literal-Number See Built-In 

    FuncParamAttr = 40,         // Indicates a function return value or parameter attribute. 
                                // 
                                // Required Capability
                                //  Kernel 
                                // Extra Operands
                                //  Function-Parameter-Attribute function-parameter-attribute 

    FP_Rounding_Mode = 41,      // Indicates a floating-point rounding mode. 
                                // 
                                // Required Capability
                                //  Kernel 
                                // Extra Operands
                                //  FP-Rounding-Mode floating-point-rounding-mode 

    FP_Fast_Math_Mode = 42,     // Indicates a floating-point fast math flag. 
                                // 
                                // Required Capability
                                //  Kernel 
                                // Extra Operands
                                //  FP-Fast-Math-Mode fast-math-mode 

    Linkage_Type = 43,          // Indicate a linkage type.
                                // Only valid on an OpFunction or a module scope OpVariable. 
                                // 
                                // Required Capability
                                //  Link 
                                // Extra Operands
                                //  Literal-String name
                                //  Linkage-Type linkage-type 

    SpecId = 44                 // Apply to a specialization constant.Forms the API linkage for setting a specialized value.
                                // See specialization. 
                                // 
                                // Required Capability
                                //  Shader 
                                // Extra Operands
                                //  Literal-Number Specialization-Constant-ID
};

static char* DecorationToString(Decoration input)
{
    switch (input)
    {
        case Decoration::PrecisionLow:          return "PrecisionLow";
        case Decoration::PrecisionMedium:       return "PrecisionMedium";
        case Decoration::PrecisionHigh:         return "PrecisionHigh";
        case Decoration::Block:                 return "Block";
        case Decoration::BufferBlock:           return "BufferBlock";
        case Decoration::RowMajor:              return "RowMajor";
        case Decoration::ColMajor:              return "ColMajor";
        case Decoration::GLSLShared:            return "GLSLShared";
        case Decoration::GLSLStd140:            return "GLSLStd140";
        case Decoration::GLSLStd430:            return "GLSLStd430";
        case Decoration::GLSLPacked:            return "GLSLPacked";
        case Decoration::Smooth:                return "Smooth";
        case Decoration::Noperspective:         return "Noperspective";
        case Decoration::Flat:                  return "Flat";
        case Decoration::Patch:                 return "Patch";
        case Decoration::Centroid:              return "Centroid";
        case Decoration::Sample:                return "Sample";
        case Decoration::Invariant:             return "Invariant";
        case Decoration::Restrict:              return "Restrict";
        case Decoration::Aliased:               return "Aliased";
        case Decoration::Volatile:              return "Volatile";
        case Decoration::Constant:              return "Constant";
        case Decoration::Coherent:              return "Coherent";
        case Decoration::Nonwritable:           return "Nonwritable";
        case Decoration::Nonreadable:           return "Nonreadable";
        case Decoration::Uniform:               return "Uniform";
        case Decoration::NoStaticUse:           return "NoStaticUse";
        case Decoration::CPacked:               return "CPacked";
        case Decoration::FPSaturatedConversion: return "FP-Saturated-Conversion";
        case Decoration::Stream:                return "Stream";
        case Decoration::Location:              return "Location";
        case Decoration::Component:             return "Component";
        case Decoration::Index:                 return "Index";
        case Decoration::Binding:               return "Binding";
        case Decoration::DescriptorSet:         return "DescriptorSet";
        case Decoration::Offset:                return "Offset";
        case Decoration::Alignment:             return "Alignment";
        case Decoration::XfbBuffer:             return "XfbBuffer";
        case Decoration::Stride:                return "Stride";
        case Decoration::Built_In:              return "Built-In";
        case Decoration::FuncParamAttr:         return "FuncParamAttr";
        case Decoration::FP_Rounding_Mode:      return "FP-Rounding-Mode";
        case Decoration::FP_Fast_Math_Mode:     return "FP-Fast-Math-Mode";
        case Decoration::Linkage_Type:          return "Linkage Type";
        case Decoration::SpecId:                return "SpecId";
        default:                                return nullptr;
    }
}
