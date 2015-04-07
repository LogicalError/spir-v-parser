#pragma once


// TODO: get rid of macros? at least outside of this header file?
// TODO: get rid of templates? 
// TODO: probably should just use new khronos header files, no C++ class enums ..	-> still want the enum to string conversions for debugging
// Q: should we support both C and C++? (naming differences between C++ and C version of khronos header files are problematic though)
// TODO: support GLSL450Lib.h /OpenCLLib.h

template<Opcode T> struct Instruction {};

#define OP_STRUCT(OP_NAME) OP_NAME##Struct
#define OP_INSTRUCTION_BASE(OP_NAME, MinWordCount, MaxWordCount, ParentStruct) \
    struct OP_STRUCT(OP_NAME);\
    template<> struct Instruction<Opcode::OP_NAME>\
    {\
        static bool Validate(InstructionHeader const*const instruction) \
        {\
            return instruction->opcode == Opcode::OP_NAME &&\
                   (instruction->wordCount >= MinWordCount) &&\
                   (instruction->wordCount <= MaxWordCount);\
        }\
        \
        static OP_STRUCT(OP_NAME) const*const CastTo(InstructionHeader const*const instruction) \
        {\
            if (instruction->opcode != Opcode::OP_NAME) return nullptr; \
            return (OP_STRUCT(OP_NAME) const*const)instruction; \
        }\
    };\
    struct OP_STRUCT(OP_NAME) : ParentStruct

#define OP_INSTRUCTION(OP_NAME, MinWordCount, MaxWordCount) OP_INSTRUCTION_BASE(OP_NAME, MinWordCount, MaxWordCount, InstructionHeader)
#define CAST_TO(OP_NAME, instruction) Instruction<Opcode::OP_NAME>::CastTo(instruction)
#define VALIDATE(OP_NAME, instruction) Instruction<Opcode::OP_NAME>::Validate(instruction)
#define NEXT(instruction) ((InstructionHeader*)(((Word*)instruction) + instruction->wordCount))


// --------------------------
// Instruction property types
// --------------------------

typedef uint32_t	Word;
typedef Word		Id;
typedef Word		LiteralNumber;
typedef char		LiteralString[sizeof(Word)];

#include "enums.h"


#pragma pack(push)
#pragma pack(1)

// Header of all instructions, contains the opcode identifier and the size of the instruction
struct InstructionHeader
{
    Opcode		opcode    : 16;
    uint16_t	wordCount : 16;

    // TODO: overflow danger .. how to handle this?
    // TODO: figure out if this is the best way to do this ..
    // TODO: test
    inline InstructionHeader const*const Next() const 
    { 
        return ((InstructionHeader const*)(((Word const*)this) + wordCount)); 
    }

    // TODO: test this
    // TODO: figure out if this is the best way to do this ..
    // NOTE: assumes string is the last element of an instruction (so far always the case)
    inline size_t GetStringLength(LiteralString string)
    {
        size_t offset = (size_t)(((Word const*)string) - ((Word const*)this));
        if (offset > wordCount || offset < 1) return (size_t)0;
        return (size_t)(wordCount - offset) * sizeof(Word);
    }

    // TODO: test this
    // TODO: figure out if this is the best way to do this ..
    // NOTE: assumes string is the last element of an instruction (so far always the case)
    inline char const* GetString(LiteralString string)
    {
        size_t offset = (size_t)(((Word const*)string) - ((Word const*)this));
        if (offset > wordCount || offset < 1) return nullptr;
        return (char const*)string;
    }

    // TODO: figure out how to best validate an instruction using it's opcode 
    //		 and the definitions below
};




// ---------------------------------
// 3.27.1 Miscellaneous Instructions
// ---------------------------------



OP_INSTRUCTION(OpNop, 1, 1)
// Use is invalid.
{
};

OP_INSTRUCTION(OpUndef, 3, 3)
// Make an intermediate object with no initialization.
{
    Id					resultType;			// The type of object to make.
    Id					resultID;
};



// -------------------------------------
// 3.27.2 Debug (Removable) Instructions
// -------------------------------------



OP_INSTRUCTION(OpSource, 2, 2)
// Document what source language this module was translated from. 
// This has no semantic impact and can safely be removed from a module.
{
    SourceLanguage		sourceLanguage;
    LiteralNumber		version;			// The version of the source language. 
};

OP_INSTRUCTION(OpSourceExtension, 1, 65535)
// Document an extension to the source language.
// This has no semantic impact and can safely be removed from a module.
{
    LiteralString		extension;			// A string describing a source-language extension.
                                            // Its form is dependent on the how the source language describes extensions.
};

OP_INSTRUCTION(OpName, 2, 65535)
// Name a Result <id>. 
// This has no semantic impact and can safely be removed from a module
{
    Id					target;				// The Result <id> to name. It can be the Result <id> of any other instruction; 
                                            // a variable, function, type, intermediate result, etc.
    LiteralString		name;				// The string to name <id> with.
};

OP_INSTRUCTION(OpMemberName, 3, 65535)
// Name a member of a structure type. 
// This has no semantic impact and can safely be removed from a module.
{
    Id					type;				// The <id> from an OpTypeStruct instruction.
    LiteralNumber		member;				// The number of the member to name in the structure. 
                                            // The first member is member 0, the next is member 1, ...
    LiteralString		name;				// The string to name the member with.
};

OP_INSTRUCTION(OpString, 2, 65535)
// Name a string for use with other debug instructions (see OpLine). 
// This has no semantic impact and can safely be removed from a module
{
    Id					resultID;
    LiteralString		string;				// The literal string being assigned a Result <id>. 
                                            // It has no result type and no storage
};

OP_INSTRUCTION(OpLine, 5, 5)
// Add source-level location information. 
// This has no semantic impact and can safely be removed from a module.
{
    Id					target;				// The Result <id> to locate. It can be the Result <id> 
                                            // of any other instruction; a variable, function, type,
                                            // intermediate result, etc.
    Id					file;				// The <id> from an OpString instruction and is the 
                                            // source-level file name.
    LiteralNumber		line;				// The source-level line number.
    LiteralNumber		column;				// The source-level column number.
};



// ------------------------------
// 3.27.3 Annotation Instructions
// ------------------------------



OP_INSTRUCTION(OpDecorationGroup, 2, 2)
// A collector of decorations from OpDecorate instructions. 
// All such instructions must precede this instruction. 
// Subsequent OpGroupDecorate and OpGroupMemberDecorate 
// instructions can consume the Result <id> to apply multiple
// decorations to multiple target <id>s. Those are the only 
// instructions allowed to consume the Result <id>.
{
    Id					resultID;
};

OP_INSTRUCTION(OpDecorate, 3, 65535)
// Add a decoration to another <id>.
{
    Id					target;				// The <id> to decorate. It can potentially be any <id> 
                                            // that is a forward reference. A set of decorations can be
                                            // grouped together by having multiple OpDecorate instructions 
                                            // target the same OpDecorationGroup instruction.
    Decoration			decoration;
    LiteralNumber		values[1];
};

OP_INSTRUCTION(OpMemberDecorate, 4, 65535)
// Add a decoration to a member of a structure type.
{
    Id					structureType;		// The <id> of a type from OpTypeStruct.
    LiteralNumber		member;				// The number of the member to decorate in the structure. 
                                            // The first member is member 0, the next is member 1, ...
    Decoration			decoration;
    LiteralNumber		values[1];
};

OP_INSTRUCTION(OpGroupDecorate, 2, 65535)
// Add a group of decorations to another <id>.
{
    Id					decorationGroup;	// The <id> of an OpDecorationGroup instruction.
    Id					targets[1];			// The target <id>s to decorate with the groups of decorations
};

OP_INSTRUCTION(OpGroupMemberDecorate, 2, 65535)
// Add a decoration to a member of a structure type.
{
    Id					decorationGroup;	// The <id> of an OpDecorationGroup instruction.
    Id					targets[1];			// The target <id>s to decorate with the groups of decorations.
};



// -----------------------------
// 3.27.4 Extension Instructions
// -----------------------------



OP_INSTRUCTION(OpExtension, 1, 65535)
// Declare use of an extension to SPIR-V. This allows
// validation of additional instructions, tokens, semantics, etc.
{
    LiteralString		name;				// the extension’s name string
};

OP_INSTRUCTION(OpExtInstImport, 2, 65535)
// Import an extended set of instructions. It can be later referenced by the Result <id>.
// See Extended Instruction Sets for more information.
{
    Id					resultID;
    LiteralString		name;				// The extended instruction-set’s name string.
};

OP_INSTRUCTION(OpExtInst, 5, 65535)
// Execute an instruction in an imported set of extended instructions.
{
    Id					resultType;
    Id					resultID;
    Id					set;				// The result of an OpExtInstImport instruction.
    LiteralNumber		instruction;		// The enumerant of the instruction to execute within the extended instruction Set.
    Id					operands[1];		// The operands to the extended instruction.
};



// --------------------------------
// 3.27.5 Mode-Setting Instructions
// --------------------------------



OP_INSTRUCTION(OpMemoryModel, 3, 3)
// Set addressing model and memory model for the entire module
{
    AddressingModel		addressingModel;	// Selects the module’s addressing model, see Addressing Model.
    MemoryModel			memoryModel;		// Selects the module’s memory model, see Memory Model.
};

OP_INSTRUCTION(OpEntryPoint, 3, 3)
// Declare an entry point and its execution model.
{
    ExecutionModel		executionModel;		// The execution model for the entry point and its static call tree. 
                                            // See Execution Model.
    Id					result;				// The Result <id> of an OpFunction instruction.
};

OP_INSTRUCTION(OpExecutionMode, 3, 65535)
// Declare an execution mode for an entry point.
{
    Id					entryPoint;			// Must be the Entry Point <id> operand of an OpEntryPoint instruction.
    ExecutionMode		mode;				// The execution mode. See Execution Mode.
    LiteralNumber		literals[1];
};

OP_INSTRUCTION(OpCompileFlag, 1, 65535)
// Add a compilation Flag.
// Capability: Kernel
{
    LiteralString		flag;
};



// ------------------------------------
// 3.27.6 Type-Declaration Instructions
// ------------------------------------



struct TypeBaseInstruction : InstructionHeader
{
    Id					result;				// the <id> of the new type.
};

OP_INSTRUCTION_BASE(OpTypeVoid, 2, 2, TypeBaseInstruction)
// Declare the void type.
{};

OP_INSTRUCTION_BASE(OpTypeBool, 2, 2, TypeBaseInstruction)
// Declare the Boolean type. Values of this type can only be either true or false. 
// There is no physical size or bit pattern defined for these values.
// If they are stored(in conjuction with OpVariable), 
// they can only be used with logical addressing operations, not physical, 
// and only with non-externally visible shader storage classes : 
// WorkgroupLocal, WorkgroupGlobal, PrivateGlobal, and Function.
{};

OP_INSTRUCTION_BASE(OpTypeInt, 4, 4, TypeBaseInstruction)
// Declare a new integer type.
{
    LiteralNumber		width;				// Specifies how many bits wide the type is. 
                                            // The bit pattern of a signed integer value is two’s complement.
    LiteralNumber		signedness;			// Specifies whether there are signed semantics to preserve or validate.
                                            //		0 indicates unsigned, or no signedness semantics
                                            //		1 indicates signed semantics.
                                            // In all cases, the type of operation of an instruction comes from 
                                            // the instruction’s opcode, not the signedness of the operands
};

OP_INSTRUCTION_BASE(OpTypeFloat, 3, 3, TypeBaseInstruction)
// Declare a new floating-point type.
{
    LiteralNumber		width;				// Specifies how many bits wide the type is. 
                                            // The bit pattern of a floating-point value is as described by the IEEE 754 standard.
};

OP_INSTRUCTION_BASE(OpTypeVector, 4, 4, TypeBaseInstruction)
// Declare a new vector type.
{
    Id					componentType;		// The type of each component in the resulting type.
    LiteralNumber		componentCount;		// The number of compononents in the resulting type. 
                                            // It must be at least 2.
};

OP_INSTRUCTION_BASE(OpTypeMatrix, 4, 4, TypeBaseInstruction)
// Declare a new matrix type.
// Capability: Matrix
{
    Id					columnType;			// The type of each column in the matrix. It must be vector type.
    LiteralNumber		columnCount;		// The number of columns in the new matrix type. 
                                            // It must be at least 2.
};


OP_INSTRUCTION_BASE(OpTypeSampler, 8, 9, TypeBaseInstruction)
// Declare a new sampler type. Consumed, for example, 
// by OpTextureSample. This type is opaque: values of 
// this type have no defined physical size or bit pattern.
{
    Id					sampledType;		// A scalar type, of the type of the components resulting 
                                            // from sampling or loading through this sampler.

    Dimensionality		dimensionality;		// Is the texture dimensionality.

    LiteralNumber		content;			// Must be one of the following indicated values:
                                            //		0 indicates a texture, no filter(no sampling state)
                                            //		1 indicates an image
                                            //		2 indicates both a texture and filter(sampling state), 
                                            //		  see OpTypeFilte

    LiteralNumber		arrayed;			// Must be one of the following indicated values:
                                            //		0 indicates non- arrayed content
                                            //		1 indicates arrayed content

    LiteralNumber		compare;			// Must be one of the following indicated values:
                                            //		0 indicates depth comparisons are not done
                                            //		1 indicates depth comparison are done

    LiteralNumber		multisampled;		// Must be one of the following indicated values:
                                            //		0 indicates single- sampled content
                                            //		1 indicates multisampled content

    Id					qualifier;			// (optional) An image access qualifier. See Access Qualifier.

};

OP_INSTRUCTION_BASE(OpTypeFilter, 2, 2, TypeBaseInstruction)
// Declare the filter type. Consumed by OpSampler. This
// type is opaque: values of this type have no defined
// physical size or bit pattern
{};

OP_INSTRUCTION_BASE(OpTypeArray, 4, 4, TypeBaseInstruction)
// Declare a new array type: a dynamically-indexable 
// ordered aggregate of elements all having the same type.
{
    Id					elementType;		// The type of each element in the array.
    Id					length;				// The number of elements in the array. It must be at least 1. 
                                            // Length must come from a constant instruction of an
                                            // Integer-type scalar whose value is at least 1.
};

OP_INSTRUCTION_BASE(OpTypeRuntimeArray, 3, 3, TypeBaseInstruction)
// Declare a new run-time array type. 
// Its length is not known at compile time.
// Objects of this type can only be created with OpVariable using the Uniform
// Storage Class.
// Capability: Shader
{
    Id					elementType;		// The type of each element in the array. See OpArrayLength for
                                            // getting the Length of an array of this type.
};

OP_INSTRUCTION_BASE(OpTypeStruct, 2, 65535, TypeBaseInstruction)
// Declare a new structure type: an aggregate of heteregeneous members
{
    Id					memberType[1];		// The type of member N of the structure. 
                                            // The first member is member 0, the next is member 1, ...
};

OP_INSTRUCTION_BASE(OpTypeOpaque, 2, 65535, TypeBaseInstruction)
// Declare a named structure type with no body specified.
// Capability: Kernel
{
    LiteralString		opaqueType;			// The name of the opaque type.
};

OP_INSTRUCTION_BASE(OpTypePointer, 4, 4, TypeBaseInstruction)
// Declare a new pointer type.
{
    StorageClass		storageClass;		// The Storage Class of the memory holding the object pointed to.
    Id					type;				// The type of the object pointed to.
};

OP_INSTRUCTION_BASE(OpTypeFunction, 3, 65535, TypeBaseInstruction)
// Declare a new function type. OpFunction and OpFunctionDecl, 
// will use this to declare the return type and parameter types
// of a function.
{
    Id					returnType;			// The type of the return value of functions of this type. 
                                            // If the function has no return value, Return Type should
                                            // be from OpTypeVoid.
    Id					parameterType[1];	// The type <id> of the type of parameter N.
};

OP_INSTRUCTION_BASE(OpTypeEvent, 2, 2, TypeBaseInstruction)
// Declare an OpenCL event object.
// Capability: Kernel
{};

OP_INSTRUCTION_BASE(OpTypeDeviceEvent, 2, 2, TypeBaseInstruction)
// Declare an OpenCL device-side event object.
// Capability: Kernel
{};

OP_INSTRUCTION_BASE(OpTypeReserveId, 2, 2, TypeBaseInstruction)
// Declare an OpenCL reservation id object.
// Capability: Kernel
{};

OP_INSTRUCTION_BASE(OpTypeQueue, 2, 2, TypeBaseInstruction)
// Declare an OpenCL queue object.
// Capability: Kernel
{};

OP_INSTRUCTION_BASE(OpTypePipe, 4, 4, TypeBaseInstruction)
// Declare an OpenCL pipe object type.
// Capability: Kernel
{
    Id					type;				// The data type of the pipe.
    AccessQualifier		qualifier;			// The pipe access qualifier.
};



// -------------------------------------
// 3.27.7 Constant-Creation Instructions
// -------------------------------------



OP_INSTRUCTION(OpConstantTrue, 3, 3)
// Declare a true Boolean-type scalar constant.
{
    Id					resultType;			// Must be the scalar Boolean type
    Id					result;
};

OP_INSTRUCTION(OpConstantFalse, 3, 3)
// Declare a false Boolean-type scalar constant.
{
    Id					resultType;			// Must be the scalar Boolean type
    Id					result;
};

OP_INSTRUCTION(OpConstant, 3, 65535)
// Declare a new Integer-type or Floating-point-type scalar constant.
{
    Id					resultType;			// Must be a scalar Integer type or Floating-point type.
    Id					result;
    LiteralNumber		value[1];			// The bit pattern for the constant. 
                                            // Types 32 bits wide or smaller take one word. 
                                            // Larger types take multiple words,
                                            // with low-order words appearing first.
};

OP_INSTRUCTION(OpConstantComposite, 3, 65535)
// Declare a new composite constant.
{
    Id					resultType;			// Must be a composite type, whose top-level members /
                                            // elements / components / columns have the same type 
                                            // as the types of the operands.
    Id					result;
    Id					constituents[1];	// Constituents will become members of a structure, 
                                            // or elements of an array, or components of a vector, 
                                            // or columns of a matrix. There must be exactly one 
                                            // Constituent for each top-level member / element /
                                            // component / column of the result. The Constituents 
                                            // Must appear in the order needed by the definition of 
                                            // the type of the result. The Constituents must be 
                                            // the <id> of other constant declarations.
};

OP_INSTRUCTION(OpConstantSampler, 6, 6)
// Declare a new sampler constant.
// Capability: Kernel
{
    Id					resultType;
    Id					result;
    LiteralNumber		mode;				// The addressing Mode. See Sampler Addressing Mode.
    LiteralNumber		param;				// One of:
                                            //		0 Nonparametric
                                            //		1 Parametric
    LiteralNumber		filter;				// The filter mode. See Sampler Filter Mode.
};

OP_INSTRUCTION(OpConstantNullPointer, 3, 3)
// Declare a new null pointer constant.
// Capability: Addr
{
    Id					resultType;
    Id					result;
};

OP_INSTRUCTION(OpConstantNullObject, 3, 3)
// Declare a new null object constant.
// The objerct can be a queue, event or
// reservation id.
// Capability: Kernel
{
    Id					resultType;
    Id					result;
};

OP_INSTRUCTION(OpSpecConstantTrue, 3, 3)
// Declare a Boolean-type scalar specialization 
// constant with a default value of true.
// This instruction can be specialized to become 
// either an OpConstantTrue or OpConstantFalse 
// instruction.
// See Specialization.
// Capability: Shader
{
    Id					resultType;			// Must be the scalar Boolean type.
    Id					result;
};

OP_INSTRUCTION(OpSpecConstantFalse, 3, 3)
// Declare a Boolean-type scalar specialization 
// constant with a default value of false.
// This instruction can be specialized to become 
// either an OpConstantTrue or OpConstantFalse 
// instruction.
// See Specialization.
// Capability: Shader
{
    Id					resultType;			// Must be the scalar Boolean type.
    Id					result;
};

OP_INSTRUCTION(OpSpecConstant, 3, 65535)
// Declare a new Integer-type or Floating-point-type 
// scalar specialization constant.
// This instruction can be specialized to become
// an OpConstant instruction.
// See Specialization.
// Capability: Shader
{
    Id					resultType;
    Id					result;
    LiteralNumber		value[1];			// The bit pattern for the default value 
                                            // of the constant. Types 32 bits wide or smaller
                                            // take one word. Larger types take multiple words, 
                                            // with low-order words appearing first.
};

OP_INSTRUCTION(OpSpecConstantComposite, 3, 65535)
// Declare a new composite specialization constant.
// This instruction will be specialized to an 
// OpConstantComposite instruction.
// See Specialization.
// Capability: Shader
{
    Id					resultType;			// Must be a composite type, whose top-level members / 
                                            // elements / components / columns have the same type 
                                            // as the types of the operands.
    Id					result;
    Id					constituents[1];	// Constituents will become members of a structure, 
                                            // or elements of an array, or components
                                            // of a vector, or columns of a matrix. 
                                            // There must be exactly one Constituent for each
                                            // top-level member / element / component / column 
                                            // of the result.
                                            // The Constituents must appear in the order needed 
                                            // by the definition of the type of the result.
                                            // The Constituents must be the <id> of other 
                                            // specialization constant or constant declarations.
};



// --------------------------
// 3.27.8 Memory Instructions
// --------------------------



OP_INSTRUCTION(OpVariable, 4, 5)
// Allocate an object in memory, resulting in a 
// pointer to it, which can be used with OpLoad and OpStore
{
    Id					resultType;			// A type from OpTypePointer, where the type pointed 
                                            // to is the type of object in memory.
    Id					result;
    StorageClass		storageClass;		// The kind of memory holding the object.
    Id					initializer;		// (optional) If Initializer is present, it will be 
                                            // the initial value of the variable’s memory content. 
                                            // Initializer must be an <id> from a constant 
                                            // instruction. Initializer must have the same type 
                                            // as the type pointed to by Result Type.
};

OP_INSTRUCTION(OpVariableArray, 5, 5)
// Allocate <count> objects sequentially in memory, 
// resulting in a pointer to the first such object
// Note: This is not the same thing as allocating a single object that is an array.
// Capability: Addr
{
    Id					resultType;			// A type from OpTypePointer whose type pointed to is 
                                            // The type of one of the <count> objects allocated in memory.
    Id					result;
    StorageClass		storageClass;		// The kind of memory holding the object.
    Id					count;				// Is the number of objects to allocate.
};

OP_INSTRUCTION(OpLoad, 4, 65535)
// Load through a pointer.
{
    Id					resultType;
    Id					result;
    Id					pointer;			// The pointer to load through. It must have a type of 
                                            // OpTypePointer whose operand is the same as Result Type.
    MemoryAccess		memoryAccess[1];	// Must be a Memory Access literal. See Memory Access for more detail.
};

OP_INSTRUCTION(OpStore, 3, 65535)
// Store through a pointer.
{
    Id					pointer;			// The pointer to store through. It must have a type of 
                                            // OpTypePointer whose operand is the same as the type of Object.
    Id					object;				// the object to store.
    MemoryAccess		memoryAccess[1];	// Must be a Memory Access literal. See Memory Access for more detail.
};

OP_INSTRUCTION(OpCopyMemory, 3, 65535)
// Copy from the memory pointed to by Source to 
// the memory pointed to by Target. Both operands 
// Must be non-void pointers of the same type.
// Matching storage class is not required.
// The amount of memory copied is the size of 
// the type pointed to.
{
    Id					target;
    Id					source;
    MemoryAccess		memoryAccess[1];	// Must be a Memory Access literal. See Memory Access for more detail.
};

OP_INSTRUCTION(OpCopyMemorySized, 4, 65535)
// Copy from the memory pointed to by Source to 
// the memory pointed to by Target.
{
    Id					target;
    Id					source;
    Id					size;
    MemoryAccess		memoryAccess[1];	// Must be a Memory Access literal. See Memory Access for more detail.
};

OP_INSTRUCTION(OpAccessChain, 4, 65535)
// Create a pointer into a composite object 
// that can be used with OpLoad and OpStore.
// The storage class of the pointer created 
// will be the same as the storage class of 
// the base operand.
{
    Id					resultType;
    Id					result;
    Id					base;				// Must be a pointer type, pointing to the base of the object.
    Id					indexes[1];			// Indexes walk the type hierarchy to the desired depth, 
                                            // potentially down to scalar granularity. 
                                            // The type of the pointer created will be to the type reached 
                                            // by walking the type hierarchy down to the last provided index.
};

OP_INSTRUCTION(OpInBoundsAccessChain, 4, 65535)
// Has the same semantics as OpAccessChain, 
// with the addition that the resulting pointer
// is known to point within the base object.
{
    Id					resultType;
    Id					result;
    Id					base;				
    Id					indices[1];			
};

OP_INSTRUCTION(OpArrayLength, 5, 5)
// Result is the array length of a run-time array.
// Capability: Shader
{
    Id					resultType;
    Id					result;
    Id					structure;			// Must be an object of type OpTypeStruct that contains a 
                                            // member that is a run-time array.
    LiteralNumber		arrayMember;		// A member number of Structure that must have a type from
                                            // OpTypeRuntimeArray.
};

OP_INSTRUCTION(OpImagePointer, 6, 6)
// Form a pointer to a texel of an image. 
// Use of such a pointer is limited to atomic operations.
// TBD. This requires an Image storage class to be added.
{
    Id					resultType;
    Id					result;
    Id					image;				// A pointer to a variable of type of OpTypeSampler.
    Id					coordinate;			// Specify which texel and sample within the 
                                            // image to form an address of.
    Id					sample;				// specify which texel and sample within the 
                                            // Image to form an address of.
};

OP_INSTRUCTION(OpGenericPtrMemSemantics, 4, 4)
// Returns a valid Memory Semantics value for ptr. 
// ptr must point to Generic.
// Capability: Kernel
{
    Id					resultType;			// Must be a 32-bits wide OpTypeInt value.
    Id					result;
    Id					ptr;
};



// ----------------------------
// 3.27.9 Function Instructions
// ----------------------------



OP_INSTRUCTION(OpFunction, 5, 5)
// Add a function. This instruction must be immediately 
// followed by one OpFunctionParameter instruction per 
// each formal parameter of this function. 
// This function’s body or declaration will terminate 
// with the next OpFunctionEnd instruction.
{
    Id					resultType;			// Must be the same as the Return Type declared in Function Type.
    Id					result;
    FunctionControl		functionControl;
    Id					functionType;		// The result of an OpTypeFunction, which declares the types of 
                                            // the return value and parameters of the function.
};

OP_INSTRUCTION(OpFunctionParameter, 3, 3)
// Declare the <id> for a formal parameter belonging 
// to the current function.
// This instruction must immediately follow an 
// OpFunction or OpFunctionParameter instruction. 
// The order of contiguous OpFunctionParameter 
// instructions is the same order arguments will 
// be listed in an OpFunctionCall instruction to this
// function. It is also the same order in which 
// Parameter Type operands are listed in the 
// OpTypeFunction of the Function Type operand 
// for this function’s OpFunction instruction.
{
    Id					resultType;			// for all the OpFunctionParameter instructions 
                                            // for a function must be the same as, in order,
                                            // the Parameter Type operands listed in the 
                                            // OpTypeFunction of the Function Type operand 
                                            // for this function’s OpFunction instruction.
    Id					result;
};

OP_INSTRUCTION(OpFunctionEnd, 4, 4)
// Last instruction of a function.
{
};

OP_INSTRUCTION(OpFunctionCall, 4, 65535)
// Call a function
// Note: A forward call is possible because 
// there is no missing type information: 
// Result Type must match the Return Type of
// the function, and the calling argument 
// types must match the formal parameter types.
{
    Id					resultType;			// The type of the return value of the function.
    Id					result;
    Id					function;			// The <id> of an OpFunction instruction. 
                                            // This could be a forward reference.
    Id					arguments[1];		// The <id>s of the object to copy to parameter N of Function
};



// ----------------------------
// 3.27.10 Texture Instructions
// ----------------------------



OP_INSTRUCTION(OpSampler, 5, 5)
// Create a sampler containing both a filter and texture.
{
    Id					resultType;			// Must be an OpTypeSampler whose Sampled Type, 
                                            // Dimensionality, Arrayed, Comparison, and 
                                            // Multisampled operands all equal those of 
                                            // this instruction’s Sampler operand. 
                                            // Further, the Result Type must have its 
                                            // Content operand set to 2, indicating 
                                            // both a texture and filter are present.
    Id					result;
    Id					sampler;			// Must be an object whose type is from an OpTypeSampler. 
                                            // Its type must have its Content operand set to 0,
                                            // indicating a texture with no filter.
    Id					filter;				// Must be an object whose type is OpTypeFilter.
};

OP_INSTRUCTION(OpTextureSample, 5, 65535)
// Sample a texture with an implicit level of detail.
//
// This instruction is only allowed under the 
// Fragment Execution Model. In addition, it 
// consumes an implicit derivative that can 
// be affected by code motion.
//
// Capability: Shader
{
    Id					resultType;			// Result Type’s component type must be the same as 
                                            // Sampled Type of Sampler’s type. Result Type must 
                                            // be scalar if the Sampler’s type sets depth-comparison, 
                                            // and must be a vector of four components if the 
                                            // Sampler’s type does not set depth-comparison.
    Id					result;
    Id					sampler;			// Must be an object whose type is from an OpTypeSampler. 
                                            // Its type must have its Content operand set to 2, 
                                            // indicating both a texture and a filter.
    Id					coordinate;			// A floating-point scalar or vector containing 
                                            // (u[, v] ... [, array layer] [, Dref]) as needed
                                            // by the definiton of Sampler.
                                            // It may be a vector larger than needed, but all 
                                            // unused components will appear after all used components.
    Id					bias;				// (optional) A bias to the implicit level of detail.
};

OP_INSTRUCTION(OpTextureSampleDref, 6, 6)
// Sample a cube-map-array texture with depth
// comparison using an implicit level of detail.
//
// This instruction is only allowed under the 
// Fragment Execution Model. In addition, it 
// consumes an implicit derivative that can 
// be affected by code motion.
//
// Capability: Shader
{
    Id					resultType;			// Must be scalar of the same type as Sampled Type 
                                            // of Sampler’s type.
    Id					result;
    Id					sampler;			// Must be an object of a type made by OpTypeSampler. 
                                            // Its type must have its Content operand set to 2, 
                                            // indicating both a texture and a filter. 
                                            // It must be for a Cube-arrayed depth-comparison type.
    Id					coordinate;			// A vector of size 4 containing (u, v, w, array layer).
    Id					dref;				// The depth-comparison reference value.
};

OP_INSTRUCTION(OpTextureSampleLod, 6, 6)
// Sample a texture using an explicit 
// level of detail.
//
// Capability: Shader
{
    Id					resultType;			// Result Type’s component type must be the same as 
                                            // Sampled Type of Sampler’s type. Result Type must 
                                            // be scalar if the Sampler’s type sets depth-comparison, 
                                            // and must be a vector of four components if the 
                                            // Sampler’s type does not set depth-comparison.
    Id					result;
    Id					sampler;			// Must be an object of a type made by OpTypeSampler. 
                                            // Its type must have its Content operand set to 2, 
                                            // indicating both a texture and a filter.
    Id					coordinate;			// a floating-point scalar or vector containing 
                                            // (u[, v] ... [, array layer] [, Dref]) as needed
                                            // by the definiton of Sampler.
                                            // It may be a vector larger than needed, but all 
                                            // unused components will appear after all used components.
    Id					levelOfDetail;		// explicitly controls the level of detail used when sampling.
};

OP_INSTRUCTION(OpTextureSampleProj, 5, 6)
// Sample a texture with a projective 
// coordinate using an implicit level of detail.
//
// This instruction is only allowed under the 
// Fragment Execution Model. In addition, it 
// consumes an implicit derivative that can 
// be affected by code motion.
//
// Capability: Shader
{
    Id					resultType;			// Result Type’s component type must be the same as 
                                            // Sampled Type of Sampler’s type. Result Type must 
                                            // be scalar if the Sampler’s type sets depth-comparison, 
                                            // and must be a vector of four components if the 
                                            // Sampler’s type does not set depth-comparison.
    Id					result;
    Id					sampler;			// Must be an object of a type made by OpTypeSampler. 
                                            // Its type must have its Content operand set to 2, 
                                            // indicating both a texture and a filter.
    Id					coordinate;			// A floating-point vector of four components containing 
                                            // (u [, v] [, Dref], q) or (u [, v] [,w], q), as 
                                            // needed by the definiton of Sampler, with the q 
                                            // component consumed for the projective division.
                                            // That is, the actual sample coordinate will be
                                            // (u/q[, v/q][, Dref/q]) or (u/q[, v/q][, w/q]), as
                                            // needed by the definiton of Sampler.
    Id					bias;				// (optional) A bias to the implicit level of detail.
};

OP_INSTRUCTION(OpTextureSampleGrad, 7, 7)
// Sample a texture with an explicit gradient.
//
// Capability: Shader
{
    Id					resultType;			// Result Type’s component type must be the same as 
                                            // Sampled Type of Sampler’s type. Result Type must be
                                            // scalar if the Sampler’s type sets depth-comparison, 
                                            // and must be a vector of four components if the
                                            // Sampler’s type does not set depth-comparison.
    Id					result;
    Id					sampler;			// Must be an object of a type made by OpTypeSampler. 
                                            // Its type must have its Content operand set to 2, 
                                            // indicating both a texture and a filter.
    Id					coordinate;			// A floating-point scalar or vector containing 
                                            // (u[, v] ... [, array layer]) as needed by the
                                            // definiton of Sampler.
    Id					dx, dy;				// dx and dy are explicit derivatives in the x 
                                            // and y direction to use in computing level of
                                            // detail. Each is a scalar or vector containing
                                            // (du/dx[, dv/dx][, dw/dx]) and 
                                            // (du/dy[, dv/dy][, dw/dy]).
                                            // The number of components of each must equal 
                                            // the number of components in Coordinate, 
                                            // minus the array layer component, if present.
};

OP_INSTRUCTION(OpTextureSampleOffset, 6, 7)
// Sample a texture with an offset from a 
// coordinate using an implicit level of detail.
//
// This instruction is only allowed under the 
// Fragment Execution Model. In addition, it 
// consumes an implicit derivative that can 
// be affected by code motion.
//
// Capability: Shader
{
    Id					resultType;			// Result Type’s component type must be the same as 
                                            // Sampled Type of Sampler’s type. Result Type must be
                                            // scalar if the Sampler’s type sets depth-comparison, 
                                            // and must be a vector of four components if the
                                            // Sampler’s type does not set depth-comparison.
    Id					result;
    Id					sampler;			// Must be an object of a type made by OpTypeSampler. 
                                            // Its type must have its Content operand set to 2, 
                                            // indicating both a texture and a filter.
    Id					coordinate;			// A floating-point scalar or vector containing 
                                            // (u[, v] ... [, array layer]) as needed by the
                                            // definiton of Sampler.
    Id					offset;				// Added to (u, v, w) before texel lookup. 
                                            // It must be an <id> of an integer-based constant
                                            // instruction of scalar or vector type.
                                            // It is a compile-time error if these fall outside 
                                            // a target-dependent allowed range.
                                            // The number of components in Offset must equal 
                                            // the number of components in Coordinate, 
                                            // minus the array layer component, if present.
    Id					bias;				// An optional operand. If present, it is used as 
                                            // a bias to the implicit level of detail.
};

OP_INSTRUCTION(OpTextureSampleProjLod, 6, 6)
// Sample a texture with a projective 
// coordinate using an explicit level of detail.
//
// Capability: Shader
{
    Id					resultType;			// Result Type’s component type must be the same as 
                                            // Sampled Type of Sampler’s type. Result Type must be
                                            // scalar if the Sampler’s type sets depth-comparison, 
                                            // and must be a vector of four components if the
                                            // Sampler’s type does not set depth-comparison.
    Id					result;
    Id					sampler;			// Must be an object of a type made by OpTypeSampler. 
                                            // Its type must have its Content operand set to 2, 
                                            // indicating both a texture and a filter.
    Id					coordinate;			// A floating-point vector of four components 
                                            // containing (u [,v] [,Dref], q) 
                                            // or (u [,v] [,w], q), as needed by the definiton 
                                            // of Sampler, with the q component consumed for 
                                            // the projective division. 
                                            // That is, the actual sample coordinate will be
                                            // (u/q[, v/q][, Dref/q]) or (u/q[, v/q][, w/q]), 
                                            // as needed by the definiton of Sampler.
    Id					levelOfDetail;		// explicitly controls the level of detail 
                                            // used when sampling.
};

OP_INSTRUCTION(OpTextureSampleProjGrad, 7, 7)
// Sample a texture with a projective 
// coordinate using an explicit gradient.
//
// Capability: Shader
{
    Id					resultType;			// Result Type’s component type must be the same as 
                                            // Sampled Type of Sampler’s type. Result Type must be
                                            // scalar if the Sampler’s type sets depth-comparison, 
                                            // and must be a vector of four components if the
                                            // Sampler’s type does not set depth-comparison.
    Id					result;
    Id					sampler;			// Must be an object of a type made by OpTypeSampler. 
                                            // Its type must have its Content operand set to 2, 
                                            // indicating both a texture and a filter.
    Id					coordinate;			// A floating-point vector of four components 
                                            // containing (u [,v] [,Dref], q) 
                                            // or (u [,v] [,w], q), as needed by the definiton 
                                            // of Sampler, with the q component consumed for 
                                            // the projective division. 
                                            // That is, the actual sample coordinate will be
                                            // (u/q[, v/q][, Dref/q]) or (u/q[, v/q][, w/q]), 
                                            // as needed by the definiton of Sampler.
    Id					dx, dy;				// dx and dy are explicit derivatives in the x 
                                            // and y direction to use in computing level of
                                            // detail. Each is a scalar or vector containing
                                            // (du/dx[, dv/dx][, dw/dx]) and 
                                            // (du/dy[, dv/dy][, dw/dy]).
                                            // The number of components of each must equal 
                                            // the number of components in Coordinate, 
                                            // minus the array layer component, if present.
};

OP_INSTRUCTION(OpTextureSampleLodOffset, 7, 7)
// Sample a texture with explicit level of 
// detail using an offset from a coordinate.
//
// Capability: Shader
{
    Id					resultType;			// Result Type’s component type must be the same as 
                                            // Sampled Type of Sampler’s type. Result Type must be
                                            // scalar if the Sampler’s type sets depth-comparison, 
                                            // and must be a vector of four components if the
                                            // Sampler’s type does not set depth-comparison.
    Id					result;
    Id					sampler;			// Must be an object of a type made by OpTypeSampler. 
                                            // Its type must have its Content operand set to 2, 
                                            // indicating both a texture and a filter.
    Id					coordinate;			// A floating-point scalar or vector containing 
                                            // (u[, v] ... [, array layer]) as needed by the
                                            // definiton of Sampler.
    Id					levelOfDetail;		// explicitly controls the level of detail 
                                            // used when sampling.
    Id					offset;				// Added to (u, v, w) before texel lookup. 
                                            // It must be an <id> of an integer-based constant
                                            // instruction of scalar or vector type.
                                            // It is a compile-time error if these fall outside 
                                            // a target-dependent allowed range.
                                            // The number of components in Offset must equal 
                                            // the number of components in Coordinate, 
                                            // minus the array layer component, if present.
};

OP_INSTRUCTION(OpTextureSampleProjOffset, 6, 7)
// Sample a texture with an offset from a projective 
// coordinate using an implicit level of detail.
//
// This instruction is only allowed under the 
// Fragment Execution Model. In addition, it 
// consumes an implicit derivative that can 
// be affected by code motion.
//
// Capability: Shader
{
    Id					resultType;			// Result Type’s component type must be the same as 
                                            // Sampled Type of Sampler’s type. Result Type must be
                                            // scalar if the Sampler’s type sets depth-comparison, 
                                            // and must be a vector of four components if the
                                            // Sampler’s type does not set depth-comparison.
    Id					result;
    Id					sampler;			// Must be an object of a type made by OpTypeSampler. 
                                            // Its type must have its Content operand set to 2, 
                                            // indicating both a texture and a filter.
    Id					coordinate;			// A floating-point vector of four components 
                                            // containing (u [,v] [,Dref], q) 
                                            // or (u [,v] [,w], q), as needed by the definiton 
                                            // of Sampler, with the q component consumed for 
                                            // the projective division. 
                                            // That is, the actual sample coordinate will be
                                            // (u/q[, v/q][, Dref/q]) or (u/q[, v/q][, w/q]), 
                                            // as needed by the definiton of Sampler.
    Id					offset;				// Added to (u, v, w) before texel lookup. 
                                            // It must be an <id> of an integer-based constant
                                            // instruction of scalar or vector type.
                                            // It is a compile-time error if these fall outside 
                                            // a target-dependent allowed range.
                                            // The number of components in Offset must equal 
                                            // the number of components in Coordinate, 
                                            // minus the array layer component, if present.
    Id					bias;				// (optional) A bias to the implicit level of detail.
};

OP_INSTRUCTION(OpTextureSampleGradOffset, 8, 8)
// Sample a texture with an offset 
// coordinate and an explicit gradient.
//
// Capability: Shader
{
    Id					resultType;			// Result Type’s component type must be the same as 
                                            // Sampled Type of Sampler’s type. Result Type must be
                                            // scalar if the Sampler’s type sets depth-comparison, 
                                            // and must be a vector of four components if the
                                            // Sampler’s type does not set depth-comparison.
    Id					result;
    Id					sampler;			// Must be an object of a type made by OpTypeSampler. 
                                            // Its type must have its Content operand set to 2, 
                                            // indicating both a texture and a filter.
    Id					coordinate;			// A floating-point scalar or vector containing 
                                            // (u[, v] ... [, array layer]) as needed by the
                                            // definiton of Sampler.
    Id					dx, dy;				// dx and dy are explicit derivatives in the x 
                                            // and y direction to use in computing level of
                                            // detail. Each is a scalar or vector containing
                                            // (du/dx[, dv/dx][, dw/dx]) and 
                                            // (du/dy[, dv/dy][, dw/dy]).
                                            // The number of components of each must equal 
                                            // the number of components in Coordinate, 
                                            // minus the array layer component, if present.
    Id					offset;				// Added to (u, v, w) before texel lookup. 
                                            // It must be an <id> of an integer-based constant
                                            // instruction of scalar or vector type.
                                            // It is a compile-time error if these fall outside 
                                            // a target-dependent allowed range.
                                            // The number of components in Offset must equal 
                                            // the number of components in Coordinate, 
                                            // minus the array layer component, if present.
};

OP_INSTRUCTION(OpTextureSampleProjLodOffset, 7, 7)
// Sample a texture with an offset from a projective 
// coordinate and an explicit level of detail.
//
// Capability: Shader
{
    Id					resultType;			// Result Type’s component type must be the same as 
                                            // Sampled Type of Sampler’s type. Result Type must be
                                            // scalar if the Sampler’s type sets depth-comparison, 
                                            // and must be a vector of four components if the
                                            // Sampler’s type does not set depth-comparison.
    Id					result;
    Id					sampler;			// Must be an object of a type made by OpTypeSampler. 
                                            // Its type must have its Content operand set to 2, 
                                            // indicating both a texture and a filter.
    Id					coordinate;			// A floating-point vector of four components 
                                            // containing (u [,v] [,Dref], q) 
                                            // or (u [,v] [,w], q), as needed by the definiton 
                                            // of Sampler, with the q component consumed for 
                                            // the projective division. 
                                            // That is, the actual sample coordinate will be
                                            // (u/q[, v/q][, Dref/q]) or (u/q[, v/q][, w/q]), 
                                            // as needed by the definiton of Sampler.
    Id					levelOfDetail;		// explicitly controls the level of detail 
                                            // used when sampling.
    Id					offset;				// Added to (u, v, w) before texel lookup. 
                                            // It must be an <id> of an integer-based constant
                                            // instruction of scalar or vector type.
                                            // It is a compile-time error if these fall outside 
                                            // a target-dependent allowed range.
                                            // The number of components in Offset must equal 
                                            // the number of components in Coordinate, 
                                            // minus the array layer component, if present.
};

OP_INSTRUCTION(OpTextureSampleProjGradOffset, 8, 8)
// Sample a texture with an offset from a projective 
// coordinate and an explicit gradient.
//
// Capability: Shader
{
    Id					resultType;			// Result Type’s component type must be the same as 
                                            // Sampled Type of Sampler’s type. Result Type must be
                                            // scalar if the Sampler’s type sets depth-comparison, 
                                            // and must be a vector of four components if the
                                            // Sampler’s type does not set depth-comparison.
    Id					result;
    Id					sampler;			// Must be an object of a type made by OpTypeSampler. 
                                            // Its type must have its Content operand set to 2, 
                                            // indicating both a texture and a filter.
    Id					coordinate;			// A floating-point vector of four components 
                                            // containing (u [,v] [,Dref], q) 
                                            // or (u [,v] [,w], q), as needed by the definiton 
                                            // of Sampler, with the q component consumed for 
                                            // the projective division. 
                                            // That is, the actual sample coordinate will be
                                            // (u/q[, v/q][, Dref/q]) or (u/q[, v/q][, w/q]), 
                                            // as needed by the definiton of Sampler.
    Id					dx, dy;				// dx and dy are explicit derivatives in the x 
                                            // and y direction to use in computing level of
                                            // detail. Each is a scalar or vector containing
                                            // (du/dx[, dv/dx][, dw/dx]) and 
                                            // (du/dy[, dv/dy][, dw/dy]).
                                            // The number of components of each must equal 
                                            // the number of components in Coordinate, 
                                            // minus the array layer component, if present.
    Id					offset;				// Added to (u, v, w) before texel lookup. 
                                            // It must be an <id> of an integer-based constant
                                            // instruction of scalar or vector type.
                                            // It is a compile-time error if these fall outside 
                                            // a target-dependent allowed range.
                                            // The number of components in Offset must equal 
                                            // the number of components in Coordinate, 
                                            // minus the array layer component, if present.
};

OP_INSTRUCTION(OpTextureFetchTexelLod, 6, 6)
// Fetch a single texel from a texture.
//
// Capability: Shader
{
    Id					resultType;			// Must be a vector of four components of the same 
                                            // type as Sampled Type of Sampler’s type.
    Id					result;
    Id					sampler;			// Must be an object of a type made by OpTypeSampler. 
                                            // Its type must have its Content operand set to 2, 
                                            // indicating both a texture and a filter.
                                            // It must have a Dimensionality of 1D, 2D, or 3D. 
                                            // It cannot have depth-comparison type
                                            // (the type’s Compare operand must be 0).
    Id					coordinate;			// An integer scalar or vector containing 
                                            // (u[, v] ... [, array layer]) as needed by the
                                            // definiton of Sampler.
    Id					levelOfDetail;		// Explicitly controls the level of detail 
                                            // used when sampling.
};

OP_INSTRUCTION(OpTextureFetchTexelOffset, 6, 6)
// Fetch a single offset texel from a texture.
//
// Capability: Shader
{
    Id					resultType;			// Must be a vector of four components of the same 
                                            // type as Sampled Type of Sampler’s type.
    Id					result;
    Id					sampler;			// Must be an object of a type made by OpTypeSampler. 
                                            // Its type must have its Content operand set to 2, 
                                            // indicating both a texture and a filter.
                                            // It must have a Dimensionality of 1D, 2D, or 3D. 
                                            // It cannot have depth-comparison type
                                            // (the type’s Compare operand must be 0).
    Id					coordinate;			// An integer scalar or vector containing 
                                            // (u[, v] ... [, array layer]) as needed by the
                                            // definiton of Sampler.
    Id					offset;				// Added to (u, v, w) before texel lookup. 
                                            // It must be an <id> of an integer-based constant
                                            // instruction of scalar or vector type.
                                            // It is a compile-time error if these fall outside 
                                            // a target-dependent allowed range.
                                            // The number of components in Offset must equal 
                                            // the number of components in Coordinate, 
                                            // minus the array layer component, if present.
};

OP_INSTRUCTION(OpTextureFetchSample, 6, 6)
// Fetch a single sample from a multi-sample texture.
//
// Capability: Shader
{
    Id					resultType;			// Must be a vector of four components of the same 
                                            // type as Sampled Type of Sampler’s type.
    Id					result;
    Id					sampler;			// Must be an object of a type made by OpTypeSampler. 
                                            // Its type must have its Content operand set to 2, 
                                            // indicating both a texture and a filter.
                                            // It must be a multi-sample texture.
    Id					coordinate;			// An integer scalar or vector containing 
                                            // (u[, v] ... [, array layer]) as needed by the
                                            // definiton of Sampler.
    Id					sample;				// The sample number of the sample to return.
};

OP_INSTRUCTION(OpTextureFetchTexel, 5, 5)
// Fetch an element out of a buffer texture.
//
// Capability: Shader
{
    Id					resultType;			// Must be a vector of four components of the same 
                                            // type as Sampled Type of Sampler’s type.
    Id					result;
    Id					sampler;			// Must be an object of a type made by OpTypeSampler. 
                                            // Its type must have its Content operand set to 2, 
                                            // indicating both a texture and a filter.
                                            // It must have a Dimensionality of Rect or Buffer.
    Id					element;			// A scalar integer index into the buffer.
};

OP_INSTRUCTION(OpTextureGather, 6, 6)
// Gathers the requested component from 
// four sampled texels.
//
// Capability: Shader
{
    Id					resultType;			// Must be a vector of four components of the same 
                                            // type as Sampled Type of Sampler’s type.
                                            // The result has one component per gathered texel.
    Id					result;
    Id					sampler;			// Must be an object of a type made by OpTypeSampler. 
                                            // Its type must have its Content operand set to 2, 
                                            // indicating both a texture and a filter.
                                            // It must have a Dimensionality of 2D, Cube, or Rect.
    Id					coordinate;			// A floating-point scalar or vector containing 
                                            // (u[, v] ... [, array layer] [, Dref]) as needed
                                            // by the definiton of Sampler.
    Id					component;			// component number that will be gathered from all 
                                            // four texels. It must be 0, 1, 2 or 3.
};

OP_INSTRUCTION(OpTextureGatherOffset, 7, 7)
// Gathers the requested component from 
// four offset sampled texels.
//
// Capability: Shader
{
    Id					resultType;			// Must be a vector of four components of the same 
                                            // type as Sampled Type of Sampler’s type.
                                            // The result has one component per gathered texel.

    Id					result;

    Id					sampler;			// Must be an object of a type made by OpTypeSampler. 
                                            // Its type must have its Content operand set to 2, 
                                            // indicating both a texture and a filter.
                                            // It must have a Dimensionality of 2D or Rect.

    Id					coordinate;			// A floating-point scalar or vector containing 
                                            // (u[, v] ... [, array layer] [, Dref]) as needed
                                            // by the definiton of Sampler.

    Id					component;			// component number that will be gathered from all 
                                            // four texels. It must be 0, 1, 2 or 3.

    Id					offset;				// Added to (u, v) before texel lookup. It is a 
                                            // compile-time error if these fall outside a
                                            // target-dependent allowed range.
};

OP_INSTRUCTION(OpTextureGatherOffsets, 7, 7)
// Gathers the requested component from
// four offset sampled texels.
//
// Capability: Shader
{
    Id					resultType;			// Must be a vector of four components of the same 
                                            // type as Sampled Type of Sampler’s type.
                                            // The result has one component per gathered texel.

    Id					result;

    Id					sampler;			// Must be an object of a type made by OpTypeSampler. 
                                            // Its type must have its Content operand set to 2, 
                                            // indicating both a texture and a filter.
                                            // It must have a Dimensionality of 2D or Rect.

    Id					coordinate;			// A floating-point scalar or vector containing 
                                            // (u[, v] ... [, array layer] [, Dref]) as needed
                                            // by the definiton of Sampler.

    Id					component;			// component number that will be gathered from all 
                                            // four texels. It must be 0, 1, 2 or 3.

    Id					offsets;			// Must be an <id> of a constant instruction making 
                                            // an array of size four of vectors of two integer
                                            // components. Each gathered texel is identified 
                                            // by adding one of these array elements to the
                                            // (u, v) sampled location. It is a compile-time 
                                            // error if this falls outside a target-dependent 
                                            // allowed range.
};

OP_INSTRUCTION(OpTextureQuerySizeLod, 5, 5)
// Query the dimensions of the texture for 
// Sampler for mipmap level for Level of Detail.
//
// Capability: Shader
{
    Id					resultType;			// Must be an integer type scalar or vector. 
                                            // The number of components must be
                                            //	1 for 1D Dimensionality,
                                            //	2 for 2D, and Cube Dimensionalities,
                                            //	3 for 3D Dimensionality,
                                            // plus 1 more if the sampler type is arrayed.
                                            // This vector is filled in with 
                                            // (width[, height][, depth][, elements]) 
                                            // where elements is the number of layers 
                                            // in a texture array, or the number of cubes in
                                            // a cube-map array.

    Id					result;

    Id					sampler;			// Must be an object of a type made by OpTypeSampler. 
                                            // Its type must have its Content operand set to 2, 
                                            // indicating both a texture and a filter.
                                            // Sampler must have a type with Dimensionality 
                                            // of 1D, 2D, 3D, or Cube.
                                            // Sampler cannot have a multisampled type.
                                            // See OpTextureQuerySize for querying texture 
                                            // types lacking level of detail.

    Id					levelOfDetail;		// explicitly controls the level of detail 
                                            // used when sampling.
};

OP_INSTRUCTION(OpTextureQuerySize, 4, 4)
// Query the dimensions of the texture for 
// Sampler, with no level of detail.
//
// Capability: Shader
{
    Id					resultType;			// Must be an integer type scalar or vector. 
                                            // The number of components must be
                                            //	1 for Buffer Dimensionality,
                                            //	2 for 2D and Rect Dimensionalities,
                                            // plus 1 more if the sampler type is arrayed.
                                            // This vector is filled in with
                                            // (width[, height][,elements]) where elements 
                                            // is the number of layers in a texture array.
    Id					result;
    Id					sampler;			// Must be an object of a type made by OpTypeSampler. 
                                            // Its type must have its Content operand set to 2, 
                                            // indicating both a texture and a filter.
                                            // Sampler must have a type with Dimensionality of 
                                            // Rect or Buffer, or be multisampled 2D. 
                                            // Sampler cannot have a texture with levels of 
                                            // detail; there is no implicit level-of-detail 
                                            // consumed by this instruction.
                                            // See OpTextureQuerySizeLod for querying textures 
                                            // having level of detail.
};

OP_INSTRUCTION(OpTextureQueryLod, 5, 5)
// Query the mipmap level and the level 
// of detail for a hypothetical sampling 
// of Sampler at Coordinate using an 
// implicit level of detail.
//
// If called on an incomplete texture, 
// the results are undefined. 
//
// This instruction is only allowed under the 
// Fragment Execution Model. In addition, it 
// consumes an implicit derivative that can 
// be affected by code motion.
// Capability: Shader
{
    Id					resultType;			// Must be a two-component floating-point type vector.
                                            // The first component of the result will contain 
                                            // the mipmap array layer. The second component 
                                            // of the result will contain the implicit level 
                                            // of detail relative to the base level.
                                            // TBD: Does this need the GLSL pseudo code 
                                            // for computing array layer and LoD?
    Id					result;
    Id					sampler;			// Must be an object of a type made by OpTypeSampler. 
                                            // Its type must have its Content operand set to 2, 
                                            // indicating both a texture and a filter.
                                            // Sampler must have a type with Dimensionality 
                                            // of 1D, 2D, 3D, or Cube.
    Id					coordinate;			// A floating-point scalar or vector containing 
                                            // (u[, v] ... [, array layer]) as needed by the
                                            // definiton of Sampler.
};

OP_INSTRUCTION(OpTextureQueryLevels, 4, 4)
// Query the number of mipmap levels 
// accessible through Sampler.
//
// TBD: The value zero will be returned 
// if no texture or an incomplete texture 
// is associated with Sampler.
//
// Capability: Shader
{
    Id					resultType;			// Must be a scalar integer type. 
                                            // The result is the number of mipmap levels, 
                                            // as defined by the API specification.
    Id					result;
    Id					sampler;			// Must be an object of a type made by OpTypeSampler. 
                                            // Its type must have its Content operand set to 2, 
                                            // indicating both a texture and a filter.
                                            // Sampler must have a type with Dimensionality 
                                            // of 1D, 2D, 3D, or Cube.
};

OP_INSTRUCTION(OpTextureQuerySamples, 4, 4)
// Query the number of samples available 
// per texel fetch in a multisample texture.
//
// Capability: Shader
{
    Id					resultType;			// Must be a scalar integer type. 
                                            // The result is the number of samples.
    Id					result;
    Id					sampler;			// Must be an object of a type made by OpTypeSampler. 
                                            // Its type must have its Content operand set to 2, 
                                            // indicating both a texture and a filter.
                                            // Sampler must have a type with Dimensionality 
                                            // of 2D and be a multisample texture.
};



// -------------------------------
// 3.27.11 Conversion Instructions
// -------------------------------



OP_INSTRUCTION(OpConvertFToU, 4, 4)
// Convert(value preserving) Float Value from 
// floating point to unsigned integer, 
// with round toward 0.0.
//
// Results are computed per component.
// The operand’s type and Result Type 
// Must have the same number of components.
//
// Result Type cannot be a signed integer type.
{
    Id					resultType;			
    Id					result;
    Id					floatValue;
};

OP_INSTRUCTION(OpConvertFToS, 4, 4)
// Convert(value preserving) Float Value from 
// floating point to signed integer, 
// with round toward 0.0.
//
// Results are computed per component.
// The operand’s type and Result Type 
// Must have the same number of components.
{
    Id					resultType;
    Id					result;
    Id					floatValue;
};

OP_INSTRUCTION(OpConvertSToF, 4, 4)
// Convert(value preserving) Signed Value 
// from signed integer to floating point.
//
// Results are computed per component.
// The operand’s type and Result Type 
// Must have the same number of components.
{
    Id					resultType;
    Id					result;
    Id					signedValue;
};

OP_INSTRUCTION(OpConvertUToF, 4, 4)
// Convert(value preserving) Unsigned value 
// from unsigned integer to floating point.
//
// Results are computed per component.
// The operand’s type and Result Type 
// Must have the same number of components.
{
    Id					resultType;
    Id					result;
    Id					unsignedValue;
};

OP_INSTRUCTION(OpUConvert, 4, 4)
// Convert(value preserving) the width of 
// Unsigned value. This is either 
// a truncate or a zero extend.
//
// Results are computed per component.
// The operand’s type and Result Type 
// Must have the same number of components.
// The widths of the components of the 
// operand and the Result Type must be 
// different. Result Type cannot be a 
// signed integer type.
{
    Id					resultType;
    Id					result;
    Id					unsignedValue;
};

OP_INSTRUCTION(OpSConvert, 4, 4)
// Convert(value preserving) the width of 
// Signed Value. This is either a 
// truncate or a sign extend.
//
// Results are computed per component.
// The operand’s type and Result Type 
// Must have the same number of components.
// The widths of the components of the 
// operand and the Result Type must be different.
{
    Id					resultType;
    Id					result;
    Id					signedValue;
};

OP_INSTRUCTION(OpFConvert, 4, 4)
// Convert(value preserving) the width 
// of Float Value.
//
// Results are computed per component.
// The operand’s type and Result Type 
// Must have the same number of components.
// The widths of the components of the 
// operand and the Result Type must be different.
{
    Id					resultType;
    Id					result;
    Id					floatValue;
};

OP_INSTRUCTION(OpConvertPtrToU, 4, 4)
// Convert Pointer to an unsigned 
// integer type. A Result Type width 
// larger than the width of Pointer 
// will zero extend. A Result Type 
// smaller than the width of Pointer 
// will truncate. For same-width 
// source and target, this is the 
// same as OpBitCast.
//
// Capability: Addr
{
    Id					resultType;			// Cannot be a signed integer type.
    Id					result;
    Id					pointer;
};

OP_INSTRUCTION(OpConvertUToPtr, 4, 4)
// Converts Integer value to a pointer.
// A Result Type width smaller than the 
// width of Integer value pointer will 
// truncate. A Result Type width larger 
// than the width of Integer value 
// pointer will zero extend. For 
// same-width source and target, 
// this is the same as OpBitCast.
//
// Capability: Addr
{
    Id					resultType;			
    Id					result;
    Id					integerValue;
};

OP_INSTRUCTION(OpPtrCastToGeneric, 4, 4)
// Converts Source pointer to a pointer 
// value pointing to storage class Generic.
// Source pointer must point to storage 
// class WorkgroupLocal, WorkgroupGlobal
// or Private. Result Type must be a 
// pointer type pointing to storage 
// class Generic.
//
// Result Type and Source pointer 
// Must point to the same type.
//
// Capability: Kernel
{
    Id					resultType;			
    Id					result;
    Id					sourcePointer;
};

OP_INSTRUCTION(OpGenericCastToPtr, 4, 4)
// Converts Source pointer to a 
// non-Generic storage-class pointer 
// value. Source pointer must point 
// to Generic.
//
// Result Type and Source pointer 
// Must point to the same type.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a pointer type pointing to 
                                            // WorkgroupLocal, WorkgroupGlobal or
                                            // Private.
    Id					result;
    Id					sourcePointer;
};

OP_INSTRUCTION(OpBitcast, 4, 4)
// Bit-pattern preserving type conversion 
// for Numerical-type or pointer-type 
// vectors and scalars.
//
// Results are computed per component.
// The operand’s type and Result Type 
// Must have the same number of components.
{
    Id					resultType;			// Must be different than the type of Operand. 
                                            // Both Result Type and the type of Operand 
                                            // Must be Numerical-types or pointer types.
                                            // The components of Operand and Result 
                                            // Type must be same bit width.
    Id					result;
    Id					operand;			// The bit pattern whose type will change.
};

OP_INSTRUCTION(OpGenericCastToPtrExplicit, 4, 4)
// Attempts to explicitly convert Source 
// pointer to storage storage-class 
// pointer value. Source pointer must 
// point to Generic. If the cast cast 
// fails, the instruction returns an 
// OpConstantNullPointer in storage 
// Storage Class.
//
// Result Type and Source pointer 
// Must point to the same type.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a pointer type pointing to storage 
                                            //Storage Class. Storage can be one of the 
                                            // following literal values: 
                                            // WorkgroupLocal, WorkgroupGlobal or Private.
    Id					result;
    Id					sourcePointer;		
    StorageClass		storage;
};

OP_INSTRUCTION(OpSatConvertSToU, 4, 4)
// Convert the Signed Value from signed 
// integer to unsigned integer. 
// Converted values outside the 
// representable range of Result Type 
// are clamped to the nearest 
// representable value of Result Type.
//
// Results are computed per component.
// The operand’s type and Result Type 
// Must have the same number of 
// components.
//
// Capability: Kernel
{
    Id					resultType;			
    Id					result;
    Id					signedValue;
};

OP_INSTRUCTION(OpSatConvertUToS, 4, 4)
// Convert Unsigned Value from unsigned 
// integer to signed integer. Converted 
// values outside the representable 
// range of Result Type are clamped to 
// the nearest representable value 
// of Result Type.
//
// Results are computed per component.
// The operand’s type and Result Type 
// Must have the same number of 
// components.
//
// Capability: Kernel
{
    Id					resultType;
    Id					result;
    Id					unsignedValue;
};



// -------------------------------
// 3.27.12 Composite Instructions
// -------------------------------



OP_INSTRUCTION(OpVectorExtractDynamic, 5, 5)
// Read a single, dynamically selected, 
// component of a vector.
//
// The value read is undefined if Index’s 
// value is less than zero or greater than
// or equal to the number of components in 
// Vector.
//
// The Result Type must be the same type as
// the type of Vector.
{
    Id					resultType;
    Id					result;
    Id					vector;				// Must be a vector type and is the vector from which to read the component.
    Id					index;				// Must be a scalar-integer 0-based index of which component to read.
};

OP_INSTRUCTION(OpVectorInsertDynamic, 6, 6)
// Write a single, variably selected, component into a vector.
//
// What memory is written is undefined if Index’s value is less than zero or greater than or equal to the number of
// components in Vector.
//
// The Result Type must be the same type as the type of Vector.
{
    Id					resultType;
    Id					result;
    Id					vector;				// Must be a vector type and is the vector that the non-written components will be taken from.
    Id					component;			
    Id					index;				// Must be a scalar-integer 0-based index of which component to read.
};

OP_INSTRUCTION(OpVectorShuffle, 5, 65535)
// Select arbitrary components from two vectors to make a new vector.
//
// Note: A vector “swizzle” can be done by using the vector for both Vector operands, or using an OpUndef for one of the
// Vector operands.
{
    Id					resultType;			// Must be a vector of the same component type as the Vector operands’ component type. The number of
                                            // components in Result Type must be the same as the number of Component operands.
    Id					result;
    Id					vector1, vector2;	// Vector 1 and Vector 2 are logically concatenated, forming a single vector with Vector 1’s components appearing before
                                            // Vector 2’s. The components of this logical vector are logically numbered with a single consecutive set of numbers from 0
                                            // to one less than the total number of components. These two vectors must be of the same component type, but do not have
                                            // to have the same number of components.

    LiteralNumber		components[1];		// Components are these logical numbers (see above), selecting which of the logically numbered components form the result.
                                            // They can select the components in any order and can repeat components. The first component of the result is selected by
                                            // the first Component operand, the second component of the result is selected by the second Component operand, etc.


};

OP_INSTRUCTION(OpCompositeConstruct, 3, 65535)
//Construct a new composite object from a set of constituent objects that will fully form it.
{
    Id					resultType;			// Must be a composite type, whose top-level members/elements/components/columns have the same type as the
                                            // types of the operands, with one exception. The exception is that for constructing a vector, the operands may also be
                                            // vectors with the same component type as the Result Type component type. When constructing a vector, the total number of
                                            // components in all the operands must equal the number of components in Result Type.
    Id					result;
    Id					constituents[1];	// Constituents will become members of a structure, or elements of an array, or components of a vector, or columns of a
                                            // matrix. There must be exactly one Constituent for each top-level member / element / component / column of the result, with
                                            // one exception. The exception is that for constructing a vector, a contiguous subset of the scalars consumed can be
                                            // represented by a vector operand instead. The Constituents must appear in the order needed by the definition of the type of
                                            // the result. When constructing a vector, there must be at least two Constituent operands.
};

OP_INSTRUCTION(OpCompositeExtract, 4, 65535)
// Extract a part of a composite object.
{
    Id					resultType;			// Must be the type of object selected by the last provided index. The instruction result is the extracted object.
    Id					result;
    Id					composite;			// Composite in the composite to extract from.
    LiteralNumber		indexes[1];			// Indexes walk the type hierarchy, down to component granularity. All indexes must be in bounds.
};

OP_INSTRUCTION(OpCompositeInsert, 5, 65535)
// Insert into a composite object.
{
    Id					resultType;			// Must be the same type as Composite, and the instruction result is a modified version of Composite.
    Id					result;
    Id					object;				// The object to insert.
    Id					composite;			// Composite in the composite to insert into.
    LiteralNumber		indexes[1];			// Indexes walk the type hierarchy to the desired depth, potentially down to component granularity. All indexes must be in bounds.
};

OP_INSTRUCTION(OpCopyObject, 4, 4)
// Make a copy of Operand. There are no dereferences involved.
{
    Id					resultType;			// Must match Operand type. There are no other restrictions on the types.
    Id					result;
    Id					operand;
};

OP_INSTRUCTION(OpTranspose, 4, 4)
// Transpose a matrix.
//
// Capability: Matrix
{
    Id					resultType;			// Must be an <id> from an OpTypeMatrix instruction, where the number of
                                            // columns and the column size is the reverse of those of the type of Matrix.
    Id					result;
    Id					matrix;				// Must be an intermediate <id> whose type comes from an OpTypeMatrix instruction.
};



// -------------------------------
// 3.27.13 Arithmetic Instructions
// -------------------------------



OP_INSTRUCTION(OpSNegate, 4, 4)
// Signed-integer subtract of Operand from zero. The operand’s type and Result Type must both be
// scalars or vectors of integer types with the same number of components and the same component
// widths. Works with any mixture of signedness.
{
    Id					resultType;
    Id					result;
    Id					operand;
};

OP_INSTRUCTION(OpFNegate, 4, 4)
// Floating-point subtract of Operand from zero. The operand’s type and Result
// Type must both be scalars or vectors of floating-point types with the same number
// of components and the same component widths.
{
    Id					resultType;
    Id					result;
    Id					operand;
};

OP_INSTRUCTION(OpNot, 4, 4)
// Complement the bits of Operand. The operand type and Result Type
// Must be scalars or vectors of integer types with the same number of
// components and same component widths.
{
    Id					resultType;
    Id					result;
    Id					operand;
};

OP_INSTRUCTION(OpIAdd, 5, 5)
// Integer addition of Operand 1 and Operand 2. The operands’ types and Result Type must all be
// scalars or vectors of integer types with the same number of components and the same component
// widths. Works with any mixture of signedness.
{
    Id					resultType;
    Id					result;
    Id					operand1, operand2;
};

OP_INSTRUCTION(OpFAdd, 5, 5)
// Floating-point addition of Operand 1 and Operand 2. The operands’ types and Result
// Type must all be scalars or vectors of floating-point types with the same number of
// components and the same component widths.
{
    Id					resultType;
    Id					result;
    Id					operand1, operand2;
};

OP_INSTRUCTION(OpISub, 5, 5)
// Integer subtraction of Operand 2 from Operand 1. The operands’ types and Result Type must all be
// scalars or vectors of integer types with the same number of components and the same component
// widths. Works with any mixture of signedness.
{
    Id					resultType;
    Id					result;
    Id					operand1, operand2;
};

OP_INSTRUCTION(OpFSub, 5, 5)
// Floating-point subtraction of Operand 2 from Operand 1. The operands’ types and
// Result Type must all be scalars or vectors of floating-point types with the same number
// of components and the same component widths.
{
    Id					resultType;
    Id					result;
    Id					operand1, operand2;
};

OP_INSTRUCTION(OpIMul, 5, 5)
// Integer multiplication of Operand 1 and Operand 2. The operands’ types and Result Type must all be
// scalars or vectors of integer types with the same number of components and the same component
// widths. Works with any mixture of signedness.
{
    Id					resultType;
    Id					result;
    Id					operand1, operand2;
};

OP_INSTRUCTION(OpFMul, 5, 5)
// Floating-point multiplication of Operand 1 and Operand 2. The operands’ types and
// Result Type must all be scalars or vectors of floating-point types with the same number
// of components and the same component widths.
{
    Id					resultType;
    Id					result;
    Id					operand1, operand2;
};

OP_INSTRUCTION(OpUDiv, 5, 5)
// Unsigned-integer division of Operand 1 divided by Operand 2. The operands’ types and Result Type must all be scalars or
// vectors of integer types with the same number of components and the same component widths. The operands’ types and
// Result Type cannot be signed types. The resulting value is undefined if Operand 2 is 0.
{
    Id					resultType;
    Id					result;
    Id					operand1, operand2;
};

OP_INSTRUCTION(OpSDiv, 5, 5)
// Signed-integer division of Operand 1 divided by Operand 2. The operands’ types and Result Type must all be scalars or
// vectors of integer types with the same number of components and the same component widths. Works with any mixture of
// signedness. The resulting value is undefined if Operand 2 is 0.
{
    Id					resultType;
    Id					result;
    Id					operand1, operand2;
};

OP_INSTRUCTION(OpFDiv, 5, 5)
// Floating-point division of Operand 1 divided by Operand 2. The operands’ types and Result Type must all be
// scalars or vectors of floating-point types with the same number of components and the same component widths.
// The resulting value is undefined if Operand 2 is 0.
{
    Id					resultType;
    Id					result;
    Id					operand1, operand2;
};

OP_INSTRUCTION(OpUMod, 5, 5)
// Unsigned modulo operation of Operand 1 modulo Operand 2. The operands’ types and Result Type must all be scalars or
// vectors of integer types with the same number of components and the same component widths. The operands’ types and
// Result Type cannot be signed types. The resulting value is undefined if Operand 2 is 0.
{
    Id					resultType;
    Id					result;
    Id					operand1, operand2;
};

OP_INSTRUCTION(OpSRem, 5, 5)
// Signed remainder operation of Operand 1 divided by Operand 2. The sign of a non-0 result comes from Operand 1. The
// operands’ types and Result Type must all be scalars or vectors of integer types with the same number of components and
// the same component widths. Works with any mixture of signedness. The resulting value is undefined if Operand 2 is 0.
{
    Id					resultType;
    Id					result;
    Id					operand1, operand2;
};

OP_INSTRUCTION(OpSMod, 5, 5)
// Signed modulo operation of Operand 1 modulo Operand 2. The sign of a non-0 result comes from Operand 2. The
// operands’ types and Result Type must all be scalars or vectors of integer types with the same number of components and
// the same component widths. Works with any mixture of signedness. The resulting value is undefined if Operand 2 is 0.
{
    Id					resultType;
    Id					result;
    Id					operand1, operand2;
};

OP_INSTRUCTION(OpFRem, 5, 5)
// Floating-point remainder operation of Operand 1 divided by Operand 2. The sign of a non-0 result comes from Operand
// 1. The operands’ types and Result Type must all be scalars or vectors of floating-point types with the same number of
// components and the same component widths. The resulting value is undefined if Operand 2 is 0.
{
    Id					resultType;
    Id					result;
    Id					operand1, operand2;
};

OP_INSTRUCTION(OpFMod, 5, 5)
// Floating-point modulo operation of Operand 1 modulo Operand 2. The sign of a non-0 result comes from Operand 2. The
// operands’ types and Result Type must all be scalars or vectors of floating-point types with the same number of components
// and the same component widths. The resulting value is undefined if Operand 2 is 0.
{
    Id					resultType;
    Id					result;
    Id					operand1, operand2;
};

OP_INSTRUCTION(OpVectorTimesScalar, 5, 5)
// Scale a floating-point vector.
{
    Id					resultType;			// Must be the same as the type of Vector.
    Id					result;				
    Id					vector;				// Must have a floating-point vector type.
    Id					scalar;				// Must be a floating-point scalar.
};

OP_INSTRUCTION(OpMatrixTimesScalar, 5, 5)
// Scale a floating-point matrix.
//
// Capability: Matrix
{
    Id					resultType;			// Must be the same as the type of Matrix.
    Id					result;
    Id					matrix;				// Must have a floating-point matrix type.
    Id					scalar;				// Must have a floating-point scalar type.
};

OP_INSTRUCTION(OpVectorTimesMatrix, 5, 5)
// Linear-algebraic Vector X Matrix.
//
// Capability: Matrix
{
    Id					resultType;			// Must be a vector whose size is the number of columns in the matrix.
    Id					result;
    Id					vector;				// Must have a floating-point vector type.
    Id					matrix;				// Must have a floating-point matrix type.
};

OP_INSTRUCTION(OpMatrixTimesVector, 5, 5)
// Linear-algebraic Vector X Matrix.
//
// Capability: Matrix
{
    Id					resultType;			// Must be a vector whose size is the number of rows in the matrix.
    Id					result;
    Id					matrix;				// Must have a floating-point matrix type.
    Id					vector;				// Must have a floating-point vector type.
};

OP_INSTRUCTION(OpMatrixTimesMatrix, 5, 5)
// Linear-algebraic multiply of LeftMatrix X RightMatrix.
//
// Capability: Matrix
{
    Id					resultType;			// Must be a matrix whose number of columns is the number of columns in
                                            // RightMatrix and whose number of rows is the number of rows of LeftMatrix
    Id					result;
    Id					leftMatrix,
                        rightMatrix;		// LeftMatrix and RightMatrix must both have a floating-point matrix type.
                                            // The number of columns of LeftMatrix must equal the number of rows of RightMatrix.
};

OP_INSTRUCTION(OpOuterProduct, 5, 5)
// Linear-algebraic outer product of Vector 1 and Vector 2.
//
// The operands’ types must be floating-point vectors with the same component type and the same
// number of components.
{
    Id					resultType;			// Must be a matrix type. Its number of columns must equal the number of components
                                            // in Vector 2. The vector type of its columns must be the same as the type of Vector 1.
    Id					result;
    Id					vector1, vector2;
};

OP_INSTRUCTION(OpDot, 5, 5)
// Dot product of Vector 1 and Vector 2.
//
// The operands’ types must be floating-point vectors with the same component type and the same
// number of components.
{
    Id					resultType;			// Must be a scalar of the same type as the operands’ component type.
    Id					result;
    Id					vector1, vector2;
};

OP_INSTRUCTION(OpShiftRightLogical, 5, 5)
// Shift the bits in Operand 1 right by the number of bits specified in Operand 2. The most-significant bits will be zero filled.
// Operand 2 is consumed as an unsigned integer. The result is undefined if Operand 2 is greater than the bit width of the
// components of Operand 1.
//
// The number of components and bit width of Result Type must match those of Operand 1 type. All types must be integer
// types. Works with any mixture of signedness.
{
    Id					resultType;
    Id					result;
    Id					operand1, operand2;
};

OP_INSTRUCTION(OpShiftRightArithmetic, 5, 5)
// Shift the bits in Operand 1 right by the number of bits specified in Operand 2. The most-significant bits will be filled with
// the sign bit from Operand 1. Operand 2 is treated as unsigned. The result is undefined if Operand 2 is greater than the bit
// width of the components of Operand 1.
//
// The number of components and bit width of Result Type must match those Operand 1 type. All types must be integer
// types. Works with any mixture of signedness.
{
    Id					resultType;
    Id					result;
    Id					operand1, operand2;
};

OP_INSTRUCTION(OpShiftLeftLogical, 5, 5)
// Shift the bits in Operand 1 left by the number of bits specified in Operand 2. The least-significant bits will be zero filled.
//
// Operand 2 is treated as unsigned. The result is undefined if Operand 2 is greater than the bit width of the components of
// Operand 1.
// The number of components and bit width of Result Type must match those Operand 1 type. All types must be integer
// types. Works with any mixture of signedness.
{
    Id					resultType;
    Id					result;
    Id					operand1, operand2;
};

OP_INSTRUCTION(OpBitwiseOr, 5, 5)
// Result is 1 if either Operand 1 or Operand 2 is 1. Result is 0 if both Operand 1 and Operand 2 are 0.
//
// Results are computed per component, and within each component, per bit. The operands’ types and Result Type must all be
// scalars or vectors of integer types with the same number of components and the same component widths. Works with any
// mixture of signedness.
{
    Id					resultType;
    Id					result;
    Id					operand1, operand2;
};

OP_INSTRUCTION(OpBitwiseXor, 5, 5)
// Result is 1 if exactly one of Operand 1 or Operand 2 is 1. Result is 0 if Operand 1 and Operand 2 have the same value.
//
// Results are computed per component, and within each component, per bit. The operands’ types and Result Type must all be
// scalars or vectors of integer types with the same number of components and the same component widths. Works with any
// mixture of signedness.
{
    Id					resultType;
    Id					result;
    Id					operand1, operand2;
};

OP_INSTRUCTION(OpBitwiseAnd, 5, 5)
// Result is 1 if both Operand 1 and Operand 2 are 1. Result is 0 if either Operand 1 or Operand 2 are 0.
//
// Results are computed per component, and within each component, per bit. The operands’ types and Result Type must all be
// scalars or vectors of integer types with the same number of components and the same component widths. Works with any
// mixture of signedness.
{
    Id					resultType;
    Id					result;
    Id					operand1, operand2;
};



// -------------------------------------------
// 3.27.14 Relational and Logical Instructions
// -------------------------------------------



OP_INSTRUCTION(OpAny, 4, 4)
// Result is true if any component of Vector is true, otherwise result is false.
{
    Id					resultType;			// Must be a Boolean type scalar.
    Id					result;
    Id					vector;				// Must be a vector of Boolean type.
};

OP_INSTRUCTION(OpAll, 4, 4)
// Result is true if all components of Vector are true, otherwise result is false.
{
    Id					resultType;			// Must be a Boolean type scalar.
    Id					result;
    Id					vector;				// Must be a vector of Boolean type.
};

OP_INSTRUCTION(OpIsNan, 4, 4)
// Result is true if x is an IEEE NaN, otherwise result is false.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operand. Results are computed per component. The operand’s type and Result Type must have the same number of components.
    Id					result;
    Id					x;
};

OP_INSTRUCTION(OpIsInf, 4, 4)
// Result is true if x is an IEEE Inf, otherwise result is false
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operand. Results are computed per component. The operand’s type and Result Type must have the same number of components.
    Id					result;
    Id					x;
};

OP_INSTRUCTION(OpIsFinite, 4, 4)
// Result is true if x is an IEEE finite number, otherwise result is false.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operand. Results are computed per component. The operand’s type and Result Type must have the same number of components.
    Id					result;
    Id					x;
};

OP_INSTRUCTION(OpIsNormal, 4, 4)
// Result is true if x is an IEEE normal number, otherwise result is false.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operand. Results are computed per component. The operand’s type and Result Type must have the same number of components.
    Id					result;
    Id					x;
};

OP_INSTRUCTION(OpSignBitSet, 4, 4)
// Result is true if x has its sign bit set, otherwise result is false.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operand. Results are computed per component. The operand’s type and Result Type must have the same number of components.
    Id					result;
    Id					x;
};

OP_INSTRUCTION(OpLessOrGreater, 5, 5)
// Result is true if x < y or x > y, where IEEE comparisons are used, otherwise result is false.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands. Results are computed per component. The operands’ types and Result Type must all have the same number of components.
    Id					result;
    Id					x;
    Id					y;
};

OP_INSTRUCTION(OpOrdered, 5, 5)
// Result is true if both x == x and y == y are true, where IEEE comparison is used, otherwise result is false.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands. Results are computed per component. The operands’ types and Result Type must all have the same number of components.
    Id					result;
    Id					x;
    Id					y;
};

OP_INSTRUCTION(OpUnordered, 5, 5)
// Result is true if either x or y is an IEEE NaN, otherwise result is false.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands. Results are computed per component. The operands’ types and Result Type must all have the same number of components.
    Id					result;
    Id					x;
    Id					y;
};

OP_INSTRUCTION(OpLogicalOr, 5, 5)
// Result is true if either Operand 1 or Operand 2 is true. Result is false if both Operand 1 and Operand 2 are false.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands. Results are computed per component. The operands’ types and Result Type must all have the same number of components.
    Id					result;
    Id					operand1,
                        operand2;			// Operand 1 and Operand 2 must both be scalars or vectors of Boolean type.
};

OP_INSTRUCTION(OpLogicalXor, 5, 5)
// Result is true if exactly one of Operand 1 or Operand 2 is true. Result is false if Operand 1 and Operand 2 have the same value.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands. Results are computed per component. The operands’ types and Result Type must all have the same number of components.
    Id					result;
    Id					operand1,
                        operand2;			// Operand 1 and Operand 2 must both be scalars or vectors of Boolean type.
};

OP_INSTRUCTION(OpLogicalAnd, 5, 5)
// Result is true if both Operand 1 and Operand 2 are true. Result is false if either Operand 1 or Operand 2 are false.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands. Results are computed per component. The operands’ types and Result Type must all have the same number of components.
    Id					result;
    Id					operand1,
                        operand2;			// Operand 1 and Operand 2 must both be scalars or vectors of Boolean type.
};

OP_INSTRUCTION(OpSelect, 6, 6)
// Select between two objects. Results are computed per component.
// 
// Result Type, the type of Object 1, and the type of Object 2 must all be the same.
{
    Id					resultType;
    Id					result;
    Id					condition;			// Must be a Boolean type scalar or vector.
                                            // Must have the same number of components as the operands.
    Id					object1;			// Object 1 is selected as the result if Condition is true.
    Id					object2;			// Object 2 is selected as the result if Condition is false.
};

OP_INSTRUCTION(OpIEqual, 5, 5)
// Integer comparison for equality.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands.
    Id					result;
    Id					operand1;
    Id					operand2;
};

OP_INSTRUCTION(OpFOrdEqual, 5, 5)
// Floating-point comparison for being ordered and equal.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands.
    Id					result;
    Id					operand1;
    Id					operand2;
};

OP_INSTRUCTION(OpFUnordEqual, 5, 5)
// Floating-point comparison for being unordered or equal.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands.
    Id					result;
    Id					operand1;
    Id					operand2;
};

OP_INSTRUCTION(OpINotEqual, 5, 5)
// Integer comparison for inequality.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands.
    Id					result;
    Id					operand1;
    Id					operand2;
};

OP_INSTRUCTION(OpFOrdNotEqual, 5, 5)
// Floating-point comparison for being ordered and not equal.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands.
    Id					result;
    Id					operand1;
    Id					operand2;
};

OP_INSTRUCTION(OpFUnordNotEqual, 5, 5)
// Floating-point comparison for being unordered or not equal.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands.
    Id					result;
    Id					operand1;
    Id					operand2;
};

OP_INSTRUCTION(OpULessThan, 5, 5)
// Unsigned-integer comparison if Operand 1 is less than Operand 2.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands.
    Id					result;
    Id					operand1;
    Id					operand2;
};

OP_INSTRUCTION(OpSLessThan, 5, 5)
// Signed-integer comparison if Operand 1 is less than Operand 2.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands.
    Id					result;
    Id					operand1;
    Id					operand2;
};

OP_INSTRUCTION(OpFOrdLessThan, 5, 5)
// Floating-point comparison if operands are ordered and Operand 1 is less than Operand 2.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands.
    Id					result;
    Id					operand1;
    Id					operand2;
};

OP_INSTRUCTION(OpFUnordLessThan, 5, 5)
// Floating-point comparison if operands are unordered or Operand 1 is less than Operand 2.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands.
    Id					result;
    Id					operand1;
    Id					operand2;
};

OP_INSTRUCTION(OpUGreaterThan, 5, 5)
// Unsigned-integer comparison if Operand 1 is greater than Operand 2.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands.
    Id					result;
    Id					operand1;
    Id					operand2;
};

OP_INSTRUCTION(OpSGreaterThan, 5, 5)
// Signed-integer comparison if Operand 1 is greater than Operand 2.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands.
    Id					result;
    Id					operand1;
    Id					operand2;
};

OP_INSTRUCTION(OpFOrdGreaterThan, 5, 5)
// Floating-point comparison if operands are ordered and Operand 1 is greater than Operand 2.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands.
    Id					result;
    Id					operand1;
    Id					operand2;
};

OP_INSTRUCTION(OpFUnordGreaterThan, 5, 5)
// Floating-point comparison if operands are unordered or Operand 1 is greater than Operand 2.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands.
    Id					result;
    Id					operand1;
    Id					operand2;
};

OP_INSTRUCTION(OpULessThanEqual, 5, 5)
// Unsigned-integer comparison if Operand 1 is less than or equal to Operand 2.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands.
    Id					result;
    Id					operand1;
    Id					operand2;
};

OP_INSTRUCTION(OpSLessThanEqual, 5, 5)
// Signed-integer comparison if Operand 1 is less than or equal to Operand 2.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands.
    Id					result;
    Id					operand1;
    Id					operand2;
};

OP_INSTRUCTION(OpFOrdLessThanEqual, 5, 5)
// Floating-point comparison if operands are ordered and Operand 1 is less than or equal to Operand 2.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands.
    Id					result;
    Id					operand1;
    Id					operand2;
};

OP_INSTRUCTION(OpFUnordLessThanEqual, 5, 5)
// Floating-point comparison if operands are unordered or Operand 1 is less than or equal to Operand 2.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands.
    Id					result;
    Id					operand1;
    Id					operand2;
};

OP_INSTRUCTION(OpUGreaterThanEqual, 5, 5)
// Unsigned-integer comparison if Operand 1 is greater than or equal to Operand 2.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands.
    Id					result;
    Id					operand1;
    Id					operand2;
};

OP_INSTRUCTION(OpSGreaterThanEqual, 5, 5)
// Signed-integer comparison if Operand 1 is greater than or equal to Operand 2.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands.
    Id					result;
    Id					operand1;
    Id					operand2;
};

OP_INSTRUCTION(OpFOrdGreaterThanEqual, 5, 5)
// Floating-point comparison if operands are ordered and Operand 1 is greater than or equal to Operand 2.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands.
    Id					result;
    Id					operand1;
    Id					operand2;
};

OP_INSTRUCTION(OpFUnordGreaterThanEqual, 5, 5)
// Floating-point comparison if operands are unordered or Operand 1 is greater than or equal to Operand 2.
{
    Id					resultType;			// Must be a scalar or vector of Boolean type, with the same number of components as the operands.
    Id					result;
    Id					operand1;
    Id					operand2;
};



// -------------------------------
// 3.27.15 Derivative Instructions
// -------------------------------



OP_INSTRUCTION(OpDPdx, 4, 4)
// Same result as either OpDPdxFine or OpDPdxCoarse on P. Selection of which one is
// based on external factors.
//
// Capability: Shader
{
    Id					resultType;			// Must be the same as the type of P. This type must be a floating-point scalar or floating-point vector.
    Id					result;
    Id					P;					// the value to take the derivative of.
};

OP_INSTRUCTION(OpDPdy, 4, 4)
// Same result as either OpDPdyFine or OpDPdyCoarse on P. Selection of which one is
// based on external factors.
//
// Capability: Shader
{
    Id					resultType;			// Must be the same as the type of P. This type must be a floating-point scalar or floating-point vector.
    Id					result;
    Id					P;					// the value to take the derivative of.
};

OP_INSTRUCTION(OpFwidth, 4, 4)
// Result is the same as computing the sum of the absolute values of OpDPdx and
// OpDPdy on P.
//
// Capability: Shader
{
    Id					resultType;			// Must be the same as the type of P. This type must be a floating-point scalar or floating-point vector.
    Id					result;
    Id					P;					// the value to take the derivative of.
};

OP_INSTRUCTION(OpDPdxFine, 4, 4)
// Result is the partial derivative of P with respect to the window x coordinate. Will use local
// differencing based on the value of P for the current fragment and its immediate
// neighbor(s).
//
// Capability: Shader
{
    Id					resultType;			// Must be the same as the type of P. This type must be a floating-point scalar or floating-point vector.
    Id					result;
    Id					P;					// the value to take the derivative of.
};

OP_INSTRUCTION(OpDPdyFine, 4, 4)
// Result is the partial derivative of P with respect to the window y coordinate. Will use local
// differencing based on the value of P for the current fragment and its immediate
// neighbor(s).
//
// Capability: Shader
{
    Id					resultType;			// Must be the same as the type of P. This type must be a floating-point scalar or floating-point vector.
    Id					result;
    Id					P;					// the value to take the derivative of.
};

OP_INSTRUCTION(OpFwidthFine, 4, 4)
// Result is the same as computing the sum of the absolute values of OpDPdxFine and
// OpDPdyFine on P.
//
// Capability: Shader
{
    Id					resultType;			// Must be the same as the type of P. This type must be a floating-point scalar or floating-point vector.
    Id					result;
    Id					P;					// the value to take the derivative of.
};

OP_INSTRUCTION(OpDPdxCoarse, 4, 4)
// Result is the partial derivative of P with respect to the window x coordinate. Will use
// local differencing based on the value of P for the current fragment’s neighbors, and will
// possibly, but not necessarily, include the value of P for the current fragment. That is, over
// a given area, the implementation can compute x derivatives in fewer unique locations
// than would be allowed for OpDPdxFine.
//
// Capability: Shader
{
    Id					resultType;			// Must be the same as the type of P. This type must be a floating-point scalar or floating-point vector.
    Id					result;
    Id					P;					// the value to take the derivative of.
};

OP_INSTRUCTION(OpDPdyCoarse, 4, 4)
// Result is the partial derivative of P with respect to the window y coordinate. Will use
// local differencing based on the value of P for the current fragment’s neighbors, and will
// possibly, but not necessarily, include the value of P for the current fragment. That is, over
// a given area, the implementation can compute y derivatives in fewer unique locations
// than would be allowed for OpDPdyFine.
//
// Capability: Shader
{
    Id					resultType;			// Must be the same as the type of P. This type must be a floating-point scalar or floating-point vector.
    Id					result;
    Id					P;					// the value to take the derivative of.
};

OP_INSTRUCTION(OpFwidthCoarse, 4, 4)
// Result is the same as computing the sum of the absolute values of OpDPdxCoarse and
// OpDPdyCoarse on P.
//
// Capability: Shader
{
    Id					resultType;			// Must be the same as the type of P. This type must be a floating-point scalar or floating-point vector.
    Id					result;
    Id					P;					// the value to take the derivative of.
};



// ---------------------------------
// 3.27.16 Flow-Control Instructions
// ---------------------------------


struct PhiPair
{
    Id					variable;
    Id					parent;
};

OP_INSTRUCTION(OpPhi, 3, 65535)
// The SSA phi function. Operands are pairs(<id> of variable, <id> of
// parent block).All variables must have a type matching Result Type.
{
    Id					resultType;			//
    Id					result;
    PhiPair				pairs[1];
};

OP_INSTRUCTION(OpLoopMerge, 3, 3)
// Declare and control a structured control-flow loop construct.
// 
// See Structured Control Flow for more detail.
{
    Id					label;				// The label of the merge block for this structured loop construct.
    LoopControl			loopControl;
};

OP_INSTRUCTION(OpSelectionMerge, 3, 3)
// Declare and control a structured control-flow selection construct, used with OpBranchConditional or OpSwitch.
//
// See Structured Control Flow for more detail.
{
    Id					label;				// The label of the merge block for this structured selection construct.
    SelectionControl	selectionControl;
};

OP_INSTRUCTION(OpLabel, 3, 3)
// The block label instruction : Any reference to a block is through the Result
// <id> of its label.
//
// Must be the first instruction of any block, and appears only as the first
// instruction of a block.
{
    Id					result;
};

OP_INSTRUCTION(OpBranch, 3, 3)
// Unconditional branch to Target Label.
//
// This instruction must be the last instruction in a block.
{
    Id					targetLabel;		// Must be the Result <id> of an OpLabel instruction in the current function.
};

OP_INSTRUCTION(OpBranchConditional, 4, 65535)
// If Condition is true, branch to True Label, otherwise branch to False Label.
{
    Id					condition;			// Must be a Boolean type scalar.
    Id					trueLabel;			// Must be an OpLabel in the current function.
    Id					falseLabel;			// Must be an OpLabel in the current function.
    LiteralNumber		branchWeights[1];	// Branch weights are unsigned 32-bit integer literals. There must be either no Branch Weights or exactly two branch weights.
                                            // If present, the first is the weight for branching to True Label, and the second is the weight for branching to False Label.
                                            // The implied probability that a branch is taken is its weight divided by the sum of the two Branch weights.
                                            // This instruction must be the last instruction in a block.
};

struct SwitchCase
{
    LiteralNumber		selector;
    Id					label;
};

OP_INSTRUCTION(OpSwitch, 3, 65535)
// Multi-way branch to one of the operand label <id>.
//
// This instruction must be the last instruction in a block.
{
    Id					selector;			// Must be a scalar integer type. It will be compared for equality to the Target literals. 
    Id					defaultLabel;		// Must be the <id> of a label. If Selector does not equal any of the Target literals, control flow will branch to the Default label <id>.
    SwitchCase			target[1];			// Target must be alternating scalar-integer literals and the <id> of a label. If Selector equals one of the literals, control flow
                                            // will branch to the following label <id>.It is invalid for any two Target literals to be equal to each other. If Target is not
                                            // present, control flow will branch to the Default label <id>.
};

OP_INSTRUCTION(OpKill, 1, 1)
// Fragment shader discard.
// This instruction must be the last instruction in a block.
// Capability: Shader
{
};

OP_INSTRUCTION(OpReturn, 1, 1)
// Return with no value from a function with void return type.
// This instruction must be the last instruction in a block.
{
};

OP_INSTRUCTION(OpReturnValue, 2, 2)
// Return a value from a function.
//
// This instruction must be the last instruction in a block.
{
    Id					value;				// the value returned, by copy, and must match the Return Type operand of the OpTypeFunction type of the OpFunction body this return instruction is in.
};

OP_INSTRUCTION(OpUnreachable, 1, 1)
// Declares that this block is not reachable in the CFG.
// This instruction must be the last instruction in a
// block.
//
// Capability: Kernel
{
};

OP_INSTRUCTION(OpLifetimeStart, 3, 3)
// Declare that the content of the object pointed to was not defined before this instruction.
// If Operand 1 has a non-void type, Operand 2 must be 0, otherwise Operand 2 is the
// amount of memory whose lifetime is starting.
{
    Id					operand1;
    LiteralNumber		operand2;
};

OP_INSTRUCTION(OpLifetimeStop, 3, 3)
// Declare that the content of the object pointed to is dead after this instruction. If
// Operand 1 has a non-void type, Operand 2 must be 0, otherwise Operand 2 is the
// amount of memory whose life-time is ending.
{
    Id					operand1;
    LiteralNumber		operand2;
};



// ---------------------------
// 3.27.17 Atomic Instructions
// ---------------------------



OP_INSTRUCTION(OpAtomicInit, 3, 3)
// Initialize atomic memory to Value. This is not done atomically with
// respect to anything.
//
// The type of Value and the type pointed to by Pointer must be the
// same type.
{
    Id					pointer;
    Id					value;
};

OP_INSTRUCTION(OpAtomicLoad, 6, 6)
// Atomically load through Pointer using the given Semantics. All subparts of the value that is loaded will be
// read atomically with respect to all other atomic accesses to it within Scope.
//
// Result Type must be the same type as the type pointed to by Pointer.
{
    Id					resultType;			
    Id					result;
    Id					pointer;
    ExecutionScope		scope;
    MemorySemantics		semantics;
};

OP_INSTRUCTION(OpAtomicStore, 5, 5)
// Atomically store through Pointer using the given Semantics. All subparts of Value will be written
// atomically with respect to all other atomic accesses to it within Scope.
//
// The type pointed to by Pointer must be the same type as the type of Value.
{
    Id					pointer;
    ExecutionScope		scope;
    MemorySemantics		semantics;
    Id					value;
};

OP_INSTRUCTION(OpAtomicExchange, 7, 7)
// Perform the following steps atomically with respect to any other atomic accesses within Scope to the same location :
//	1 load through Pointer to get an Original Value,
//	2 get a New Value from copying Value, and
//	3 store the New Value back through Pointer.
//
// The instruction’s result is the Original Value.
//
// Result Type, the type of Value, and the type pointed to by Pointer must all be same type.
{
    Id					resultType;
    Id					result;
    Id					pointer;
    ExecutionScope		scope;
    MemorySemantics		semantics;
    Id					value;
};

OP_INSTRUCTION(OpAtomicCompareExchange, 8, 8)
// Perform the following steps atomically with respect to any other atomic accesses within Scope to the same location :
//	1 load through Pointer to get an Original Value,
//	2 get a New Value by selecting Value if Original Value equals Comparator or selecting Original Value otherwise, and
//	3 store the New Value back through Pointer.
// 
// The instruction’s result is the Original Value.
//
// Result Type, the type of Value, and the type pointed to by Pointer must all be same type.
{
    Id					resultType;
    Id					result;
    Id					pointer;
    ExecutionScope		scope;
    MemorySemantics		semantics;
    Id					value;
    Id					comparator;
};

OP_INSTRUCTION(OpAtomicCompareExchangeWeak, 8, 8)
// Attempts to do the following :
// Perform the following steps atomically with respect to any other atomic accesses within Scope to the same location :
//	1 load through Pointer to get an Original Value,
//	2 get a New Value by selecting Value if Original Value equals Comparator or selecting Original Value otherwise, and
//	3 store the New Value back through Pointer.
// 
// The instruction’s result is the Original Value.
//
// Result Type, the type of Value, and the type pointed to by Pointer must all be same type. This type must also match the type
// of Comparator.
//
// TBD. What is the result if the operation fails ? 
{
    Id					resultType;
    Id					result;
    Id					pointer;
    ExecutionScope		scope;
    MemorySemantics		semantics;
    Id					value;
    Id					comparator;
};

OP_INSTRUCTION(OpAtomicIIncrement, 6, 6)
// Perform the following steps atomically with respect to any other atomic accesses within Scope to the same location :
//	1 load through Pointer to get an Original Value,
//	2 get a New Value through integer addition of 1 to Original Value, and
//	3 store the New Value back through Pointer.
//
// The instruction’s result is the Original Value.
//
// Result Type must be the same type as the type pointed to by Pointer.
{
    Id					resultType;
    Id					result;
    Id					pointer;
    ExecutionScope		scope;
    MemorySemantics		semantics;
};

OP_INSTRUCTION(OpAtomicIDecrement, 6, 6)
// Perform the following steps atomically with respect to any other atomic accesses within Scope to the same location:
//	1 load through Pointer to get an Original Value,
//	2 get a New Value through integer subtraction of 1 from Original Value, and
//	3 store the New Value back through Pointer.
//
// The instruction’s result is the Original Value.
// 
// Result Type must be the same type as the type pointed to by Pointer.
{
    Id					resultType;
    Id					result;
    Id					pointer;
    ExecutionScope		scope;
    MemorySemantics		semantics;
};

OP_INSTRUCTION(OpAtomicIAdd, 7, 7)
// Perform the following steps atomically with respect to any other atomic accesses within Scope to the same location :
//	1 load through Pointer to get an Original Value,
//	2 get a New Value by integer addition of Original Value and Value, and
//	3 store the New Value back through Pointer.
//
// The instruction’s result is the Original Value.
//
// Result Type, the type of Value, and the type pointed to by Pointer must all be same type.
{
    Id					resultType;
    Id					result;
    Id					pointer;
    ExecutionScope		scope;
    MemorySemantics		semantics;
    Id					value;
};

OP_INSTRUCTION(OpAtomicISub, 7, 7)
// Perform the following steps atomically with respect to any other atomic accesses within Scope to the same location :
//	1 load through Pointer to get an Original Value,
//	2 get a New Value by integer subtraction of Value from Original Value, and
//	3 store the New Value back through Pointer.
//
// The instruction’s result is the Original Value.
//
// Result Type, the type of Value, and the type pointed to by Pointer must all be same type.
{
    Id					resultType;
    Id					result;
    Id					pointer;
    ExecutionScope		scope;
    MemorySemantics		semantics;
    Id					value;
};

OP_INSTRUCTION(OpAtomicUMin, 7, 7)
// Perform the following steps atomically with respect to any other atomic accesses within Scope to the same location :
//	1 load through Pointer to get an Original Value,
//	2 get a New Value by finding the smallest unsigned integer of Original Value and Value, and
//	3 store the New Value back through Pointer.
//
// The instruction’s result is the Original Value.
//
// Result Type, the type of Value, and the type pointed to by Pointer must all be same type.
{
    Id					resultType;
    Id					result;
    Id					pointer;
    ExecutionScope		scope;
    MemorySemantics		semantics;
    Id					value;
};

OP_INSTRUCTION(OpAtomicUMax, 7, 7)
// Perform the following steps atomically with respect to any other atomic accesses within Scope to the same location :
//	1 load through Pointer to get an Original Value,
//	2 get a New Value by finding the largest unsigned integer of Original Value and Value, and
//	3 store the New Value back through Pointer.
//
// The instruction’s result is the Original Value.
//
// Result Type, the type of Value, and the type pointed to by Pointer must all be same type.
{
    Id					resultType;
    Id					result;
    Id					pointer;
    ExecutionScope		scope;
    MemorySemantics		semantics;
    Id					value;
};

OP_INSTRUCTION(OpAtomicAnd, 7, 7)
// Perform the following steps atomically with respect to any other atomic accesses within Scope to the same location :
//	1 load through Pointer to get an Original Value,
//	2 get a New Value by the bitwise AND of Original Value and Value, and
//	3 store the New Value back through Pointer.
//
// The instruction’s result is the Original Value.
//
// Result Type, the type of Value, and the type pointed to by Pointer must all be same type.
{
    Id					resultType;
    Id					result;
    Id					pointer;
    ExecutionScope		scope;
    MemorySemantics		semantics;
    Id					value;
};

OP_INSTRUCTION(OpAtomicOr, 7, 7)
// Perform the following steps atomically with respect to any other atomic accesses within Scope to the same location :
//	1 load through Pointer to get an Original Value,
//	2 get a New Value by the bitwise OR of Original Value and Value, and
//	3 store the New Value back through Pointer.
//
// The instruction’s result is the Original Value.
//
// Result Type, the type of Value, and the type pointed to by Pointer must all be same type.
{
    Id					resultType;
    Id					result;
    Id					pointer;
    ExecutionScope		scope;
    MemorySemantics		semantics;
    Id					value;
};

OP_INSTRUCTION(OpAtomicXor, 7, 7)
// Perform the following steps atomically with respect to any other atomic accesses within Scope to the same location :
//	1 load through Pointer to get an Original Value,
//	2 get a New Value by the bitwise exclusive OR of Original Value and Value, and
//	3 store the New Value back through Pointer.
//
// The instruction’s result is the Original Value.
//
// Result Type, the type of Value, and the type pointed to by Pointer must all be same type.
{
    Id					resultType;
    Id					result;
    Id					pointer;
    ExecutionScope		scope;
    MemorySemantics		semantics;
    Id					value;
};

OP_INSTRUCTION(OpAtomicIMin, 7, 7)
// Perform the following steps atomically with respect to any other atomic accesses within Scope to the same location :
//	1 load through Pointer to get an Original Value,
//	2 get a New Value by finding the smallest signed integer of Original Value and Value, and
//	3 store the New Value back through Pointer.
//
// The instruction’s result is the Original Value.
//
// Result Type, the type of Value, and the type pointed to by Pointer must all be same type.
{
    Id					resultType;
    Id					result;
    Id					pointer;
    ExecutionScope		scope;
    MemorySemantics		semantics;
    Id					value;
};

OP_INSTRUCTION(OpAtomicIMax, 7, 7)
// Perform the following steps atomically with respect to any other atomic accesses within Scope to the same location :
//	1 load through Pointer to get an Original Value,
//	2 get a New Value by finding the largest signed integer of Original Value and Value, and
//	3 store the New Value back through Pointer.
//
// The instruction’s result is the Original Value.
//
// Result Type, the type of Value, and the type pointed to by Pointer must all be same type.
{
    Id					resultType;
    Id					result;
    Id					pointer;
    ExecutionScope		scope;
    MemorySemantics		semantics;
    Id					value;
};



// ------------------------------
// 3.27.18 Primitive Instructions
// ------------------------------




OP_INSTRUCTION(OpEmitVertex, 1, 1)
// Emits the current values of all output
// variables to the current output primitive.
// After execution, the values of all output
// variables are undefined.
// This instruction can only be used when
// only one stream is present.
//
// Capability: Geom
{
};

OP_INSTRUCTION(OpEndPrimitive, 1, 1)
// Finish the current primitive
// and start a new one. No
// vertex is emitted.
// This instruction can only
// be used when only one
// stream is present.
//
// Capability: Geom
{
};

OP_INSTRUCTION(OpEmitStreamVertex, 2, 2)
// Emits the current values of all output variables to
// the current output primitive. After execution, the
// values of all output variables are undefined.
//
// Stream must be an <id> of a constant instruction
// with a scalar integer type. It is the stream the
// primitive is on.
//
// This instruction can only be used when multiple
// streams are present.
//
// Capability: Geom
{
    Id					stream;
};

OP_INSTRUCTION(OpEndStreamPrimitive, 2, 2)
// Finish the current primitive and start a new one.
// No vertex is emitted.
//
// Stream must be an <id> of a constant instruction
// with a scalar integer type. It is the stream the
// primitive is on.
//
// This instruction can only be used when multiple
// streams are present.
//
// Capability: Geom
{
    Id					stream;
};



// ------------------------------
// 3.27.19 Barrier Instructions
// ------------------------------




OP_INSTRUCTION(OpControlBarrier, 2, 2)
// Wait for other invocations of this module to reach this same point of execution.
//
// All invocations of this module within Scope must reach this point of execution before any will proceed beyond it.
//
// This instruction is only guaranteed to work correctly if placed strictly within dynamically uniform control flow within
// Scope. This ensures that if any invocation executes it, all invocations will execute it. If placed elsewhere, an invocation
// may stall indefinitely.
//
// It is only valid to use this instruction with TessellationControl, GLCompute, or Kernel execution models.
{
    ExecutionScope		scope;
};

OP_INSTRUCTION(OpMemoryBarrier, 3, 3)
// Control the order that memory accesses are observed.
//
// Ensures that memory accesses issued before this instruction will be observed before memory accesses issued after this
// instruction. This control is ensured only for memory accesses issued by this invocation and observed by another invocation
// executing within Scope.
//
// Semantics declares what kind of memory is being controlled and what kind of control to apply.
{
    ExecutionScope		scope;
    MemorySemantics		semantics;
};



// --------------------------
// 3.27.20 Group Instructions
// --------------------------



OP_INSTRUCTION(OpAsyncGroupCopy, 9, 9)
// Perform an asynchronous group copy of Num Elements elements from Source to Destination. The
// asynchronous copy is performed by all work-items in a group.
//
// Returns an event object that can be used by OpWaitGroupEvents to wait for the copy to finish.
//
// Event must be OpTypeEvent.
//
// Event can be used to associate the copy with a previous copy allowing an event to be shared by multiple
// copies. Otherwise Event should be a OpConstantNullObject.
//
// If Event argument is not OpConstantNullObject, the event object supplied in event argument will be returned.
//
// Scope must be theWorkgroup or Subgroup Execution Scope.
//
// Destination and Source should both be pointers to the same integer or floating point scalar or vector data type.
//
// Destination and Source pointer storage class can be eitherWorkgroupLocal or WorkgroupGlobal.
//
// When Destination pointer storage class isWorkgroupLocal, the Source pointer storage class must be
// WorkgroupGlobal. In this case Stride defines the stride in elements when reading from Source pointer.
//
// When Destination pointer storage class isWorkgroupGlobal, the Source pointer storage class must be
// WorkgroupLocal. In this case Stride defines the stride in elements when writing each element to
// Destination pointer.
//
// Stride and NumElemens must be a 32 bit OpTypeInt when the Addressing Model is Physical32 and 64 bit
// OpTypeInt when the Addressing Model is Physical64.
//
// Capability: Kernel
{
    Id					resultType;
    Id					result;
    ExecutionScope		scope;
    Id					destination;
    Id					source;
    Id					numElements;
    Id					stride;
    Id					event;
};

OP_INSTRUCTION(OpWaitGroupEvents, 6, 6)
// Wait for events generated by OpAsyncGroupCopy operations to complete. The event objects pointed
// by Events List will be released after the wait is performed.
//
// Capability: Kernel
{
    Id					resultType;
    Id					result;
    ExecutionScope		scope;				// Must be theWorkgroup or Subgroup Execution Scope.
    Id					numEvents;			// Must be a 32 bits wide OpTypeInt.
    Id					eventsList;			// Must be a pointer to OpTypeEvent.
};

OP_INSTRUCTION(OpGroupAll, 5, 5)
// Evaluates a predicate for all work-items in the group,and returns true if predicate evaluates to
// true for all work-items in the group, otherwise returns false.
//
// Capability: Kernel
{
    Id					resultType;			// Must be of OpTypeBool.
    Id					result;
    ExecutionScope		scope;				// Must be theWorkgroup or Subgroup Execution Scope.
    Id					predicate;			// Must be of OpTypeBool.
};

OP_INSTRUCTION(OpGroupAny, 5, 5)
// Evaluates a predicate for all work-items in the group,and returns true if predicate evaluates to
// true for any work-item in the group, otherwise returns false.
//
// Capability: Kernel
{
    Id					resultType;			// Must be of OpTypeBool.
    Id					result;
    ExecutionScope		scope;				// Must be theWorkgroup or Subgroup Execution Scope.
    Id					predicate;			// Must be of OpTypeBool.
};

OP_INSTRUCTION(OpGroupBroadcast, 6, 6)
// Broadcast a value for workitem identified by the local id to all work-items in the group.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a 32 or 64 bits wise OpTypeInt or a 16, 32 or 64 OpTypeFloat
                                            // floating-point scalar datatype.
    Id					result;
    ExecutionScope		scope;				// Must be theWorkgroup or Subgroup Execution Scope.
    Id					value;				// Must be a 32 or 64 bits wise OpTypeInt or a 16, 32 or 64 OpTypeFloat
                                            // floating-point scalar datatype.
    Id					localId;			// Must be an integer datatype. It can be a scalar, or a vector with 2 components or a vector
                                            // with 3 components. LocalId must be the same for all work-items in the group.
};

OP_INSTRUCTION(OpGroupIAdd, 6, 6)
// An integer add group operation specified for all values of X specified by work-items in the group.
//
// The identity I is 0.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a 32 or 64 bits wide OpTypeInt data type.
    Id					result;
    ExecutionScope		scope;				// Must be theWorkgroup or Subgroup Execution Scope.
    GroupOperation		operation;
    Id					x;					// Must be a 32 or 64 bits wide OpTypeInt data type.
};

OP_INSTRUCTION(OpGroupFAdd, 6, 6)
// A floating-point add group operation specified for all values of X specified by work-items in the
// group.
//
// The identity I is 0.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a 16, 32 or 64 bits wide OpTypeFloat data type.
    Id					result;
    ExecutionScope		scope;				// Must be theWorkgroup or Subgroup Execution Scope.
    GroupOperation		operation;
    Id					x;					// Must be a 16, 32 or 64 bits wide OpTypeFloat data type.
};

OP_INSTRUCTION(OpGroupFMin, 6, 6)
// A floating-point minimum group operation specified for all values of X specified by work-items in
// the group.
//
// The identity I is + INF.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a 16, 32 or 64 bits wide OpTypeFloat data type.
    Id					result;
    ExecutionScope		scope;				// Must be theWorkgroup or Subgroup Execution Scope.
    GroupOperation		operation;
    Id					x;					// Must be a 16, 32 or 64 bits wide OpTypeFloat data type.
};

OP_INSTRUCTION(OpGroupUMin, 6, 6)
// An unsigned integer minimum group operation specified for all values of X specified by work-items
// in the group.
//
// The identity I is UINT_MAX when X is 32 bits wide and ULONG_MAX when X is 64 bits wide.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a 32 or 64 bits wide OpTypeInt data type.
    Id					result;
    ExecutionScope		scope;				// Must be theWorkgroup or Subgroup Execution Scope.
    GroupOperation		operation;
    Id					x;					// Must be a 32 or 64 bits wide OpTypeInt data type.
};

OP_INSTRUCTION(OpGroupSMin, 6, 6)
// A signed integer minimum group operation specified for all values of X specified by work-items in
// the group.
//
// The identity I is INT_MAX when X is 32 bits wide and LONG_MAX when X is 64 bits wide.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a 32 or 64 bits wide OpTypeInt data type.
    Id					result;
    ExecutionScope		scope;				// Must be theWorkgroup or Subgroup Execution Scope.
    GroupOperation		operation;
    Id					x;					// Must be a 32 or 64 bits wide OpTypeInt data type.
};

OP_INSTRUCTION(OpGroupFMax, 6, 6)
// A floating-point maximum group operation specified for all values of X specified by work-items in
// the group.
//
// The identity I is-INF.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a 16, 32 or 64 bits wide OpTypeFloat data type.
    Id					result;
    ExecutionScope		scope;				// Must be theWorkgroup or Subgroup Execution Scope.
    GroupOperation		operation;
    Id					x;					// Must be a 16, 32 or 64 bits wide OpTypeFloat data type.
};

OP_INSTRUCTION(OpGroupUMax, 6, 6)
// An unsigned integer maximum group operation specified for all values of X specified by work-items
// in the group.
//
// The identity I is 0.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a 32 or 64 bits wide OpTypeInt data type.
    Id					result;
    ExecutionScope		scope;				// Must be theWorkgroup or Subgroup Execution Scope.
    GroupOperation		operation;
    Id					x;					// Must be a 32 or 64 bits wide OpTypeInt data type.
};

OP_INSTRUCTION(OpGroupSMax, 6, 6)
// A signed integer maximum group operation specified for all values of X specified by work-items in
// the group.
//
// The identity I is INT_MIN when X is 32 bits wide and LONG_MIN when X is 64 bits wide.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a 32 or 64 bits wide OpTypeInt data type.
    Id					result;
    ExecutionScope		scope;				// Must be theWorkgroup or Subgroup Execution Scope.
    GroupOperation		operation;
    Id					x;					// Must be a 32 or 64 bits wide OpTypeInt data type.
};



// ----------------------------------------
// 3.27.21 Device-Side Enqueue Instructions
// ----------------------------------------



OP_INSTRUCTION(OpEnqueueMarker, 7, 7)
// Enqueue a marker command to to the queue object specified by q. The marker command waits for a list
// of events to complete, or if the list is empty it waits for all previously enqueued commands in q to
// complete before the marker completes.
//
// These are the possible return values:
//	A successfull enqueue is indicated by the integer value 0
//	A failed enqueue is indicated by the negative integer value -101
//
// When running the clCompileProgram or clBuildProgram with -g flag, the following errors may be returned instead of the negative integer value -101:
//	- When q is an invalid queue object, the negative integer value -102 is returned.
//	- When Wait Events is null and Num Events > 0, or if Wait Events is not null and Num Events is 0, or if event objects in Wait Events are not valid events, the negative integer value -57 is returned.
//	- When the queue object q is full, the negative integer value -161 is returned.
//	- When Ret Event is not a null object and an event could not be allocated, the negative integer value -100 is returned.
//	- When there is a failure to queue Invoke in the queue q because of insufficient resources needed to execute the kernel, the negative integer value -5 is returned.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a 32 bit OpTypeInt.
    Id					result;
    Id					q;					// 
    Id					numEvents;			// specifies the number of event objects in the wait list pointed Wait Events and must be 32 bit OpTypeInt treated as unsigned integer.
    Id					waitEvents;			// specifies the list of wait event objects and must be a OpTypePointer to OpTypeDeviceEvent.
    Id					retEvents;			// OpTypePointer to OpTypeDeviceEvent which gets implictly retained by this instruction. must be a OpTypePointer to OpTypeDeviceEvent. If Ret Event is set to null this instruction becomes a no-op.
};

OP_INSTRUCTION(OpEnqueueKernel, 13, 65535)
// Enqueue the the function specified by Invoke and the NDRange specified by ND Range for execution to the queue object specified by q.
//
// These are the possible return values:
//	A successfull enqueue is indicated by the integer value 0
//	A failed enqueue is indicated by the negative integer value -101
//
// When running the clCompileProgram or clBuildProgram with -g flag, the following errors may be returned instead of the negative value -101:
//	- When q is an invalid queue object, the negative integer value -102 is returned.
//	- When ND Range is an invalid descriptor or if the program was compiled with -cl-uniform-work-group-size and the local work size is specified in ndrange but the global work size specified in ND Range is not a multiple of the local work size, the negative integer value -160 is returned.
//	- When Wait Events is null and Num Events > 0, or if Wait Events is not null and Num Events is 0, or if event objects in Wait Events are not valid events, the negative integer value -57 is returned.
//	- When the queue object q is full, the negative integer value -161 is returned.
//	- When one of the operands Local Size is 0, the negative integer value -51 is returned.
//	- When Ret Event is not a null object and an event could not be allocated, the negative integer value -100 is returned.
//	- When there is a failure to queue Invoke in the queue q because of insufficient resources needed to execute the kernel, the negative integer value -5 is returned.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a 32 bit OpTypeInt.
    Id					result;
    Id					q;					// 
    KernelEnqueueFlags	flags;				// 
    Id					NDrange;			// Must be a OpTypeStruct created by OpBuildNDRange.
    Id					numEvents;			// specifies the number of event objects in the wait list pointed Wait Events and must be 32 bit OpTypeInt treated as unsigned integer.
    Id					waitEvents;			// specifies the list of wait event objects and must be a OpTypePointer to OpTypeDeviceEvent.
    Id					retEvents;			// OpTypePointer to OpTypeDeviceEvent which gets implictly retained by this instruction. must be a OpTypePointer to OpTypeDeviceEvent.
    Id					invoke;				// Must be a OpTypeFunction with the following signature:
                                            //	- Result Type must be OpTypeVoid.
                                            //	- The first parameter must be OpTypePointer to 8 bits OpTypeInt.
                                            //	- Optional list of parameters that must be OpTypePointer with WorkgroupLocal storage class.
    Id					param;				// the first parameter of the function specified by Invoke and must be OpTypePointer to 8 bit OpTypeInt.
    Id					paramSize;			// the size in bytes of the memory pointed by Param and must be a 32 bit OpTypeInt treated as unsigned int.
    Id					paramAlign;			// the alignment of Param.
    Id					localSize[1];		// (optional) list of 32 bit OpTypeInt values which are treated as unsigned integers. Every Local Size specifies the size in bytes of the OpTypePointer with WorkgroupLocal of Invoke. The number of Local Size operands must match the signature of Invoke OpTypeFunction
};

OP_INSTRUCTION(OpGetKernelNDrangeSubGroupCount, 5, 5)
// Returns the number of subgroups in each workgroup of the dispatch (except for the last in cases where the global size does not divide cleanly into work-groups) given the combination of the passed NDRange descriptor specified by ND Range and the function specified by Invoke.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a 32 bit OpTypeInt.
    Id					result;
    Id					NDrange;			// Must be a OpTypeStruct created by OpBuildNDRange.
    Id					invoke;				// Must be a OpTypeFunction with the following signature:
                                            //	- Result Type must be OpTypeVoid.
                                            //	- The first parameter must be OpTypePointer to 8 bits OpTypeInt.
                                            //	- Optional list of parameters that must be OpTypePointer with WorkgroupLocal storage class.
};

OP_INSTRUCTION(OpGetKernelNDrangeMaxSubGroupSize, 5, 5)
// Returns the maximum sub-group size for the function specified by Invoke and the NDRange specified by ND Range.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a 32 bit OpTypeInt.
    Id					result;
    Id					NDrange;			// Must be a OpTypeStruct created by OpBuildNDRange.
    Id					invoke;				// Must be a OpTypeFunction with the following signature:
                                            //	- Result Type must be OpTypeVoid.
                                            //	- The first parameter must be OpTypePointer to 8 bits OpTypeInt.
                                            //	- Optional list of parameters that must be OpTypePointer with WorkgroupLocal storage class.
};

OP_INSTRUCTION(OpGetKernelWorkGroupSize, 4, 4)
// Returns the maximum work-group size that can be used to execute the function specified by Invoke on the device.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a 32 bit OpTypeInt.
    Id					result;
    Id					invoke;				// Must be a OpTypeFunction with the following signature:
                                            //	- Result Type must be OpTypeVoid.
                                            //	- The first parameter must be OpTypePointer to 8 bits OpTypeInt.
                                            //	- Optional list of parameters that must be OpTypePointer with WorkgroupLocal storage class.
};

OP_INSTRUCTION(OpGetKernelPreferredWorkGroupSizeMultiple, 4, 4)
// Returns the preferred multiple of work-group size for the function specified by Invoke.
// This is a performance hint. Specifying a work-group size that is not a multiple of the
// value returned by this query as the value of the local work size will not fail to enqueue
// Invoke for execution unless the work-group size specified is larger than the device
// maximum.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a 32 bit OpTypeInt.
    Id					result;
    Id					invoke;				// Must be a OpTypeFunction with the following signature:
                                            //	- Result Type must be OpTypeVoid.
                                            //	- The first parameter must be OpTypePointer to 8 bits OpTypeInt.
                                            //	- Optional list of parameters that must be OpTypePointer with WorkgroupLocal storage class.
};

OP_INSTRUCTION(OpRetainEvent, 2, 2)
// Increments the reference count of the
// event object specified by event.
//
// Capability: Kernel
{
    Id					event;				// Must be an event that was
                                            // produced by OpEnqueueKernel,
                                            // OpEnqueueMarker or
                                            // OpCreateUserEvent.
};

OP_INSTRUCTION(OpReleaseEvent, 2, 2)
// Decrements the reference count of the event
// object specified by event. The event object is
// deleted once the event reference count is zero,
// the specific command identified by this event has
// completed (or terminated) and there are no
// commands in any device command queue that
// require a wait for this event to complete.
//
// Capability: Kernel
{
    Id					event;				// Must be an event that was produced by
                                            // OpEnqueueKernel, OpEnqueueMarker or
                                            // OpCreateUserEvent.
};

OP_INSTRUCTION(OpCreateUserEvent, 3, 3)
// Create a user event. The execution status
// of the created event is set to a value of 2
// (CL_SUBMITTED).
//
// Capability: Kernel
{
    Id					resultType;			// Must be OpTypeDeviceEvent.
    Id					result;
};

OP_INSTRUCTION(OpIsValidEvent, 4, 4)
// Returns true if the event specified by event is a valid event,
// otherwise returns false.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a OpTypeBool.
    Id					result;
    Id					event;				// Must be a OpTypeDeviceEvent
};

OP_INSTRUCTION(OpSetUserEventStatus, 3, 3)
// Sets the execution status of a user event specified by event. status can be
// either 0 (CL_COMPLETE) to indicate that this kernel and all its child
// kernels finished execution successfully, or a negative integer value indicating
// an error.
//
// Capability: Kernel
{
    Id					event;				// Must be a OpTypeDeviceEvent that was produced by
                                            // OpCreateUserEvent.
    Id					status;				// Must be a 32-bit OpTypeInt treated as a signed integer.
};

OP_INSTRUCTION(OpCaptureEventProfilingInfo, 4, 4)
// Captures the profiling information specified by info for the command associated with the
// event specified by event in the memory pointed by value. The profiling information will
// be available in value once the command identified by event has completed.
//
// When info is CmdExecTime value must be a OpTypePointer with WorkgroupGlobal
// storage class, to two 64-bit OpTypeInt values. The first 64-bit value describes the elapsed
// time CL_PROFILING_COMMAND_END-CL_PROFLING_COMMAND_START for
// the command identified by event in nanoseconds. The second 64-bit value describes the
// elapsed time CL_PROFILING_COMMAND_COMPLETE-CL_PROFILING_COMAMND_START 
// for the command identified by event in nanoseconds.
//
// Note: The behavior of of this instruction is undefined when called multiple times for the
// same event.
//
// Capability: Kernel
{
    Id					event;				// Must be a OpTypeDeviceEvent that was produced by OpEnqueueKernel or
                                            // OpEnqueueMarker.
    KernelProfilingInfo	info;				// 
    Id					status;				// 
};

OP_INSTRUCTION(OpGetDefaultQueue, 3, 3)
// Returns the default device queue. If a default device queue
// has not been created, null queue object is returned using the
// OpConstantNullObject instruction.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a OpTypeQueue.
    Id					result;
};

OP_INSTRUCTION(OpBuildNDRange, 6, 6)
// Given the global work size specified by GlobalWorkSize, local work size specified by LocalWorkSize
// and global work offset specified by GlobalWorkOffset, builds a 1D, 2D or 3D ND-range descriptor
// structure.
//
// GlobalWorkSize, LocalWorkSize and GlobalWorkOffset must be a scalar or an array with 2 or 3
// components. Where the type of each element in the array is 32 bit OpTypeInt when the Addressing
// Model is Physical32 or 64 bit OpTypeInt when the Addressing Model is Physical64.
//
// Result Type is the descriptor and must be a OpTypeStruct with the following ordered list of members,
// starting from the first to last:
//	- 32 bit OpTypeInt that specifies the number of dimensions used to specify the global work-items and
//	  work-items in the work-group.
//	- OpTypeArray with 3 elements, where each element is 32 bit OpTypeInt when the Addressing
//	  Model is Physical32 and 64 bit OpTypeInt when the Addressing Model is Physical64. This
//	  member is an array of per-dimension unsigned values that describe the offset used to calculate the
//	  global Id of a work-item.
//	- OpTypeArray with 3 elements, where each element is 32 bit OpTypeInt when the Addressing
//	  Model is Physical32 and 64 bit OpTypeInt when the Addressing Model is Physical64. This
//	  member is an array of per-dimension unsigned values that describe the number of global work-items
//	  in the dimensions that will execute the kernel function.
//	- OpTypeArray with 3 elements, where each element is 32 bit OpTypeInt when the Addressing
//	  Model is Physical32 and 64 bit OpTypeInt when the Addressing Model is Physical64. This
//	  member is an array of an array of per-dimension unsigned values that describe the number of
//	  work-items that make up a work-group.
//
// Capability: Kernel
{
    Id					resultType;		
    Id					result;
    Id					globalWorkSize;	
    Id					localWorkSize;	
    Id					globalWorkOffset;
};



// ----------------------------------------
// 3.27.22 Pipe Instructions
// ----------------------------------------



OP_INSTRUCTION(OpReadPipe, 5, 5)
// Read a packet from the pipe object specified by p into ptr. Returns 0 if the operation is
// successfull and a negative value if the pipe is empty.
//
// Capability: Kernel
{
    Id					resultType;
    Id					result;
    Id					p;					// Must be a OpTypePipe with ReadOnly Access Qualifier.
    Id					ptr;				// Must be a OpTypePointer with the same data type as p and a Generic storage class.
};

OP_INSTRUCTION(OpWritePipe, 5, 5)
// Write a packet from ptr to the pipe object specified by p. Returns 0 if the operation is successfull
// and a negative value if the pipe is full.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a 32-bits OpTypeInt.
    Id					result;
    Id					p;					// Must be a OpTypePipe with WriteOnly Access Qualifier.
    Id					ptr;				// Must be a OpTypePointer with the same data type as p and a Generic storage class.
};

OP_INSTRUCTION(OpReservedReadPipe, 7, 7)
// Read a packet from the reserved area specified by reserve_id and index of the pipe object specified by p
// into ptr. The reserved pipe entries are referred to by indices that go from 0 ... num_packets-1.
// Returns 0 if the operation is successfull and a negative value otherwise.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a 32-bits OpTypeInt.
    Id					result;
    Id					p;					// Must be a OpTypePipe with ReadOnly Access Qualifier.
    Id					reserve_id;			// Must be a OpTypeReserveId.
    Id					index;				// Must be a 32-bits OpTypeInt which is treated as unsigned value.
    Id					ptr;				// Must be a OpTypePointer with the same data type as p and a Generic storage class.
};

OP_INSTRUCTION(OpReservedWritePipe, 7, 7)
// Write a packet from ptr into the reserved area specified by reserve_id and index of the pipe object
// specified by p. The reserved pipe entries are referred to by indices that go from 0 ... num_packets -1. 
// Returns 0 if the operation is successfull and a negative value otherwise.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a 32-bits OpTypeInt.
    Id					result;
    Id					p;					// Must be a OpTypePipe with WriteOnly Access Qualifier.
    Id					reserve_id;			// Must be a OpTypeReserveId.
    Id					index;				// Must be a 32-bits OpTypeInt which is treated as unsigned value.
    Id					ptr;				// Must be a OpTypePointer with the same data type as p and a Generic storage class.
};

OP_INSTRUCTION(OpReserveReadPipePackets, 5, 5)
// Reserve num_packets entries for reading from the pipe object
// specified by p. Returns a valid reservation Id if the reservation is
// successful.
//
// Capability: Kernel
{
    Id					resultType;			
    Id					result;
    Id					p;					
    Id					num_packets;		
};

OP_INSTRUCTION(OpReserveWritePipePackets, 5, 5)
// Reserve num_packets entries for writing to the pipe object specified
// by p. Returns a valid reservation Id if the reservation is successful.
//
// Capability: Kernel
{
    Id					resultType;			
    Id					result;
    Id					p;					
    Id					num_packets;		
};

OP_INSTRUCTION(OpCommitReadPipe, 3, 3)
// Indicates that all reads to num_packets associated with the reservation
// specified by reserve_id and the pipe object specified by p are completed.
//
// Capability: Kernel
{
    Id					p;					// Must be a OpTypePipe with ReadOnly Access Qualifier.
    Id					reserve_id;			// Must be a OpTypeReserveId.
};

OP_INSTRUCTION(OpCommitWritePipe, 3, 3)
// Indicates that all writes to num_packets associated with the reservation
// specified by reserve_id and the pipe object specified by p are completed.
//
// Capability: Kernel
{
    Id					p;					// Must be a OpTypePipe with WriteOnly Access Qualifier.
    Id					reserve_id;			// Must be a OpTypeReserveId.
};

OP_INSTRUCTION(OpIsValidReserveId, 4, 4)
// Return true if reserve_id is a valid reservation Id and false
// otherwise.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a OpTypeBool.
    Id					result;
    Id					reserve_id;			// Must be a OpTypeReserveId.
};

OP_INSTRUCTION(OpGetNumPipePackets, 4, 4)
// Returns the number of available entries in the pipe object specified by p. The number of
// available entries in a pipe is a dynamic value. The value returned should be considered
// immediately stale.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a 32-bits OpTypeInt which should be treated as unsigned value.
    Id					result;
    Id					p;					// Must be a OpTypePipe with ReadOnly or WriteOnly Access Qualifier.
};

OP_INSTRUCTION(OpGetMaxPipePackets, 4, 4)
// Returns the maximum number of packets specified when the pipe object specified by p
// was created.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a 32-bits OpTypeInt which should be treated as unsigned value.
    Id					result;
    Id					p;					// Must be a OpTypePipe with ReadOnly or WriteOnly Access Qualifier.
};

OP_INSTRUCTION(OpGroupReserveReadPipePackets, 6, 6)
// Reserve num_packets entries for reading from the pipe object specified by p at group level. Returns a
// valid reservation Id if the reservation is successful.
//
// The reserved pipe entries are referred to by indices that go from 0 ... num_packets-1.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a OpTypeReserveId.
    Id					result;
    ExecutionScope		scope;				// Must be theWorkgroup or Subgroup Execution Scope.
    Id					p;					// Must be a OpTypePipe with ReadOnly Access Qualifier.
    Id					num_packets;		// Must be a 32-bits OpTypeInt which is treated as unsigned value.
};

OP_INSTRUCTION(OpGroupReserveWritePipePackets, 6, 6)
// Reserve num_packets entries for writing to the pipe object specified by p at group level. Returns a
// valid reservation Id if the reservation is successful.
//
// The reserved pipe entries are referred to by indices that go from 0 ... num_packets-1.
//
// Capability: Kernel
{
    Id					resultType;			// Must be a OpTypeReserveId.
    Id					result;
    ExecutionScope		scope;				// Must be theWorkgroup or Subgroup Execution Scope.
    Id					p;					// Must be a OpTypePipe with WriteOnly Access Qualifier.
    Id					num_packets;		// Must be a 32-bits OpTypeInt which is treated as unsigned value.
};

OP_INSTRUCTION(OpGroupCommitReadPipe, 4, 4)
// A group level indication that all reads to num_packets associated with the reservation
// specified by reserve_id to the pipe object specified by p are completed.
//
// Capability: Kernel
{
    ExecutionScope		scope;				// Must be theWorkgroup or Subgroup Execution Scope.
    Id					p;					// Must be a OpTypePipe with ReadOnly Access Qualifier.
    Id					reserve_id;			// Must be a OpTypeReserveId.
};

OP_INSTRUCTION(OpGroupCommitWritePipe, 4, 4)
// A group level indication that all writes to num_packets associated with the reservation
// specified by reserve_id to the pipe object specified by p are completed.
//
// Capability: Kernel
{
    ExecutionScope		scope;				// Must be theWorkgroup or Subgroup Execution Scope.
    Id					p;					// Must be a OpTypePipe with WriteOnly Access Qualifier.
    Id					reserve_id;			// Must be a OpTypeReserveId.
};

#pragma pack(pop)