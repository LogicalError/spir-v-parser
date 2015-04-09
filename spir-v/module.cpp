#define _CRT_SECURE_NO_WARNINGS
#include <stdint.h>
#include "enums.h"
#include "instructions.h"
#include "module.h"

#ifdef HAVE_BYTESWAP_H
#include <byteswap.h>
#else
static inline uint32_t bswap_32(uint32_t x)
{
    return ((x & 0xff000000) >> 24) | ((x & 0x00ff0000) >>  8) | \
           ((x & 0x0000ff00) <<  8) | ((x & 0x000000ff) << 24);
}
#endif


typedef bool ValidationFunction(InstructionHeader const*const instruction);

static ValidationFunction* InstructionValidation[] =
{
    InstructionHelper<Opcode::OpNop>::Validate,
    InstructionHelper<Opcode::OpSource>::Validate,
    InstructionHelper<Opcode::OpSourceExtension>::Validate,
    InstructionHelper<Opcode::OpExtension>::Validate,
    InstructionHelper<Opcode::OpExtInstImport>::Validate,
    InstructionHelper<Opcode::OpMemoryModel>::Validate,
    InstructionHelper<Opcode::OpEntryPoint>::Validate,
    InstructionHelper<Opcode::OpExecutionMode>::Validate,
    InstructionHelper<Opcode::OpTypeVoid>::Validate,
    InstructionHelper<Opcode::OpTypeBool>::Validate,
    InstructionHelper<Opcode::OpTypeInt>::Validate,
    InstructionHelper<Opcode::OpTypeFloat>::Validate,
    InstructionHelper<Opcode::OpTypeVector>::Validate,
    InstructionHelper<Opcode::OpTypeMatrix>::Validate,
    InstructionHelper<Opcode::OpTypeSampler>::Validate,
    InstructionHelper<Opcode::OpTypeFilter>::Validate,
    InstructionHelper<Opcode::OpTypeArray>::Validate,
    InstructionHelper<Opcode::OpTypeRuntimeArray>::Validate,
    InstructionHelper<Opcode::OpTypeStruct>::Validate,
    InstructionHelper<Opcode::OpTypeOpaque>::Validate,
    InstructionHelper<Opcode::OpTypePointer>::Validate,
    InstructionHelper<Opcode::OpTypeFunction>::Validate,
    InstructionHelper<Opcode::OpTypeEvent>::Validate,
    InstructionHelper<Opcode::OpTypeDeviceEvent>::Validate,
    InstructionHelper<Opcode::OpTypeReserveId>::Validate,
    InstructionHelper<Opcode::OpTypeQueue>::Validate,
    InstructionHelper<Opcode::OpTypePipe>::Validate,
    InstructionHelper<Opcode::OpConstantTrue>::Validate,
    InstructionHelper<Opcode::OpConstantFalse>::Validate,
    InstructionHelper<Opcode::OpConstant>::Validate,
    InstructionHelper<Opcode::OpConstantComposite>::Validate,
    InstructionHelper<Opcode::OpConstantSampler>::Validate,
    InstructionHelper<Opcode::OpConstantNullPointer>::Validate,
    InstructionHelper<Opcode::OpConstantNullObject>::Validate,
    InstructionHelper<Opcode::OpSpecConstantTrue>::Validate,
    InstructionHelper<Opcode::OpSpecConstantFalse>::Validate,
    InstructionHelper<Opcode::OpSpecConstant>::Validate,
    InstructionHelper<Opcode::OpSpecConstantComposite>::Validate,
    InstructionHelper<Opcode::OpVariable>::Validate,
    InstructionHelper<Opcode::OpVariableArray>::Validate,
    InstructionHelper<Opcode::OpFunction>::Validate,
    InstructionHelper<Opcode::OpFunctionParameter>::Validate,
    InstructionHelper<Opcode::OpFunctionEnd>::Validate,
    InstructionHelper<Opcode::OpFunctionCall>::Validate,
    InstructionHelper<Opcode::OpExtInst>::Validate,
    InstructionHelper<Opcode::OpUndef>::Validate,
    InstructionHelper<Opcode::OpLoad>::Validate,
    InstructionHelper<Opcode::OpStore>::Validate,
    InstructionHelper<Opcode::OpPhi>::Validate,
    InstructionHelper<Opcode::OpDecorationGroup>::Validate,
    InstructionHelper<Opcode::OpDecorate>::Validate,
    InstructionHelper<Opcode::OpMemberDecorate>::Validate,
    InstructionHelper<Opcode::OpGroupDecorate>::Validate,
    InstructionHelper<Opcode::OpGroupMemberDecorate>::Validate,
    InstructionHelper<Opcode::OpName>::Validate,
    InstructionHelper<Opcode::OpMemberName>::Validate,
    InstructionHelper<Opcode::OpString>::Validate,
    InstructionHelper<Opcode::OpLine>::Validate,
    InstructionHelper<Opcode::OpVectorExtractDynamic>::Validate,
    InstructionHelper<Opcode::OpVectorInsertDynamic>::Validate,
    InstructionHelper<Opcode::OpVectorShuffle>::Validate,
    InstructionHelper<Opcode::OpCompositeConstruct>::Validate,
    InstructionHelper<Opcode::OpCompositeExtract>::Validate,
    InstructionHelper<Opcode::OpCompositeInsert>::Validate,
    InstructionHelper<Opcode::OpCopyObject>::Validate,
    InstructionHelper<Opcode::OpCopyMemory>::Validate,
    InstructionHelper<Opcode::OpCopyMemorySized>::Validate,
    InstructionHelper<Opcode::OpSampler>::Validate,
    InstructionHelper<Opcode::OpTextureSample>::Validate,
    InstructionHelper<Opcode::OpTextureSampleDref>::Validate,
    InstructionHelper<Opcode::OpTextureSampleLod>::Validate,
    InstructionHelper<Opcode::OpTextureSampleProj>::Validate,
    InstructionHelper<Opcode::OpTextureSampleGrad>::Validate,
    InstructionHelper<Opcode::OpTextureSampleOffset>::Validate,
    InstructionHelper<Opcode::OpTextureSampleProjLod>::Validate,
    InstructionHelper<Opcode::OpTextureSampleProjGrad>::Validate,
    InstructionHelper<Opcode::OpTextureSampleLodOffset>::Validate,
    InstructionHelper<Opcode::OpTextureSampleProjOffset>::Validate,
    InstructionHelper<Opcode::OpTextureSampleGradOffset>::Validate,
    InstructionHelper<Opcode::OpTextureSampleProjLodOffset>::Validate,
    InstructionHelper<Opcode::OpTextureSampleProjGradOffset>::Validate,
    InstructionHelper<Opcode::OpTextureFetchTexelLod>::Validate,
    InstructionHelper<Opcode::OpTextureFetchTexelOffset>::Validate,
    InstructionHelper<Opcode::OpTextureFetchSample>::Validate,
    InstructionHelper<Opcode::OpTextureFetchTexel>::Validate,
    InstructionHelper<Opcode::OpTextureGather>::Validate,
    InstructionHelper<Opcode::OpTextureGatherOffset>::Validate,
    InstructionHelper<Opcode::OpTextureGatherOffsets>::Validate,
    InstructionHelper<Opcode::OpTextureQuerySizeLod>::Validate,
    InstructionHelper<Opcode::OpTextureQuerySize>::Validate,
    InstructionHelper<Opcode::OpTextureQueryLod>::Validate,
    InstructionHelper<Opcode::OpTextureQueryLevels>::Validate,
    InstructionHelper<Opcode::OpTextureQuerySamples>::Validate,
    InstructionHelper<Opcode::OpAccessChain>::Validate,
    InstructionHelper<Opcode::OpInBoundsAccessChain>::Validate,
    InstructionHelper<Opcode::OpSNegate>::Validate,
    InstructionHelper<Opcode::OpFNegate>::Validate,
    InstructionHelper<Opcode::OpNot>::Validate,
    InstructionHelper<Opcode::OpAny>::Validate,
    InstructionHelper<Opcode::OpAll>::Validate,
    InstructionHelper<Opcode::OpConvertFToU>::Validate,
    InstructionHelper<Opcode::OpConvertFToS>::Validate,
    InstructionHelper<Opcode::OpConvertSToF>::Validate,
    InstructionHelper<Opcode::OpConvertUToF>::Validate,
    InstructionHelper<Opcode::OpUConvert>::Validate,
    InstructionHelper<Opcode::OpSConvert>::Validate,
    InstructionHelper<Opcode::OpFConvert>::Validate,
    InstructionHelper<Opcode::OpConvertPtrToU>::Validate,
    InstructionHelper<Opcode::OpConvertUToPtr>::Validate,
    InstructionHelper<Opcode::OpPtrCastToGeneric>::Validate,
    InstructionHelper<Opcode::OpGenericCastToPtr>::Validate,
    InstructionHelper<Opcode::OpBitcast>::Validate,
    InstructionHelper<Opcode::OpTranspose>::Validate,
    InstructionHelper<Opcode::OpIsNan>::Validate,
    InstructionHelper<Opcode::OpIsInf>::Validate,
    InstructionHelper<Opcode::OpIsFinite>::Validate,
    InstructionHelper<Opcode::OpIsNormal>::Validate,
    InstructionHelper<Opcode::OpSignBitSet>::Validate,
    InstructionHelper<Opcode::OpLessOrGreater>::Validate,
    InstructionHelper<Opcode::OpOrdered>::Validate,
    InstructionHelper<Opcode::OpUnordered>::Validate,
    InstructionHelper<Opcode::OpArrayLength>::Validate,
    InstructionHelper<Opcode::OpIAdd>::Validate,
    InstructionHelper<Opcode::OpFAdd>::Validate,
    InstructionHelper<Opcode::OpISub>::Validate,
    InstructionHelper<Opcode::OpFSub>::Validate,
    InstructionHelper<Opcode::OpIMul>::Validate,
    InstructionHelper<Opcode::OpFMul>::Validate,
    InstructionHelper<Opcode::OpUDiv>::Validate,
    InstructionHelper<Opcode::OpSDiv>::Validate,
    InstructionHelper<Opcode::OpFDiv>::Validate,
    InstructionHelper<Opcode::OpUMod>::Validate,
    InstructionHelper<Opcode::OpSRem>::Validate,
    InstructionHelper<Opcode::OpSMod>::Validate,
    InstructionHelper<Opcode::OpFRem>::Validate,
    InstructionHelper<Opcode::OpFMod>::Validate,
    InstructionHelper<Opcode::OpVectorTimesScalar>::Validate,
    InstructionHelper<Opcode::OpMatrixTimesScalar>::Validate,
    InstructionHelper<Opcode::OpVectorTimesMatrix>::Validate,
    InstructionHelper<Opcode::OpMatrixTimesVector>::Validate,
    InstructionHelper<Opcode::OpMatrixTimesMatrix>::Validate,
    InstructionHelper<Opcode::OpOuterProduct>::Validate,
    InstructionHelper<Opcode::OpDot>::Validate,
    InstructionHelper<Opcode::OpShiftRightLogical>::Validate,
    InstructionHelper<Opcode::OpShiftRightArithmetic>::Validate,
    InstructionHelper<Opcode::OpShiftLeftLogical>::Validate,
    InstructionHelper<Opcode::OpLogicalOr>::Validate,
    InstructionHelper<Opcode::OpLogicalXor>::Validate,
    InstructionHelper<Opcode::OpLogicalAnd>::Validate,
    InstructionHelper<Opcode::OpBitwiseOr>::Validate,
    InstructionHelper<Opcode::OpBitwiseXor>::Validate,
    InstructionHelper<Opcode::OpBitwiseAnd>::Validate,
    InstructionHelper<Opcode::OpSelect>::Validate,
    InstructionHelper<Opcode::OpIEqual>::Validate,
    InstructionHelper<Opcode::OpFOrdEqual>::Validate,
    InstructionHelper<Opcode::OpFUnordEqual>::Validate,
    InstructionHelper<Opcode::OpINotEqual>::Validate,
    InstructionHelper<Opcode::OpFOrdNotEqual>::Validate,
    InstructionHelper<Opcode::OpFUnordNotEqual>::Validate,
    InstructionHelper<Opcode::OpULessThan>::Validate,
    InstructionHelper<Opcode::OpSLessThan>::Validate,
    InstructionHelper<Opcode::OpFOrdLessThan>::Validate,
    InstructionHelper<Opcode::OpFUnordLessThan>::Validate,
    InstructionHelper<Opcode::OpUGreaterThan>::Validate,
    InstructionHelper<Opcode::OpSGreaterThan>::Validate,
    InstructionHelper<Opcode::OpFOrdGreaterThan>::Validate,
    InstructionHelper<Opcode::OpFUnordGreaterThan>::Validate,
    InstructionHelper<Opcode::OpULessThanEqual>::Validate,
    InstructionHelper<Opcode::OpSLessThanEqual>::Validate,
    InstructionHelper<Opcode::OpFOrdLessThanEqual>::Validate,
    InstructionHelper<Opcode::OpFUnordLessThanEqual>::Validate,
    InstructionHelper<Opcode::OpUGreaterThanEqual>::Validate,
    InstructionHelper<Opcode::OpSGreaterThanEqual>::Validate,
    InstructionHelper<Opcode::OpFOrdGreaterThanEqual>::Validate,
    InstructionHelper<Opcode::OpFUnordGreaterThanEqual>::Validate,
    InstructionHelper<Opcode::OpDPdx>::Validate,
    InstructionHelper<Opcode::OpDPdy>::Validate,
    InstructionHelper<Opcode::OpFwidth>::Validate,
    InstructionHelper<Opcode::OpDPdxFine>::Validate,
    InstructionHelper<Opcode::OpDPdyFine>::Validate,
    InstructionHelper<Opcode::OpFwidthFine>::Validate,
    InstructionHelper<Opcode::OpDPdxCoarse>::Validate,
    InstructionHelper<Opcode::OpDPdyCoarse>::Validate,
    InstructionHelper<Opcode::OpFwidthCoarse>::Validate,
    InstructionHelper<Opcode::OpEmitVertex>::Validate,
    InstructionHelper<Opcode::OpEndPrimitive>::Validate,
    InstructionHelper<Opcode::OpEmitStreamVertex>::Validate,
    InstructionHelper<Opcode::OpEndStreamPrimitive>::Validate,
    InstructionHelper<Opcode::OpControlBarrier>::Validate,
    InstructionHelper<Opcode::OpMemoryBarrier>::Validate,
    InstructionHelper<Opcode::OpImagePointer>::Validate,
    InstructionHelper<Opcode::OpAtomicInit>::Validate,
    InstructionHelper<Opcode::OpAtomicLoad>::Validate,
    InstructionHelper<Opcode::OpAtomicStore>::Validate,
    InstructionHelper<Opcode::OpAtomicExchange>::Validate,
    InstructionHelper<Opcode::OpAtomicCompareExchange>::Validate,
    InstructionHelper<Opcode::OpAtomicCompareExchangeWeak>::Validate,
    InstructionHelper<Opcode::OpAtomicIIncrement>::Validate,
    InstructionHelper<Opcode::OpAtomicIDecrement>::Validate,
    InstructionHelper<Opcode::OpAtomicIAdd>::Validate,
    InstructionHelper<Opcode::OpAtomicISub>::Validate,
    InstructionHelper<Opcode::OpAtomicUMin>::Validate,
    InstructionHelper<Opcode::OpAtomicUMax>::Validate,
    InstructionHelper<Opcode::OpAtomicAnd>::Validate,
    InstructionHelper<Opcode::OpAtomicOr>::Validate,
    InstructionHelper<Opcode::OpAtomicXor>::Validate,
    InstructionHelper<Opcode::OpLoopMerge>::Validate,
    InstructionHelper<Opcode::OpSelectionMerge>::Validate,
    InstructionHelper<Opcode::OpLabel>::Validate,
    InstructionHelper<Opcode::OpBranch>::Validate,
    InstructionHelper<Opcode::OpBranchConditional>::Validate,
    InstructionHelper<Opcode::OpSwitch>::Validate,
    InstructionHelper<Opcode::OpKill>::Validate,
    InstructionHelper<Opcode::OpReturn>::Validate,
    InstructionHelper<Opcode::OpReturnValue>::Validate,
    InstructionHelper<Opcode::OpUnreachable>::Validate,
    InstructionHelper<Opcode::OpLifetimeStart>::Validate,
    InstructionHelper<Opcode::OpLifetimeStop>::Validate,
    InstructionHelper<Opcode::OpCompileFlag>::Validate,
    InstructionHelper<Opcode::OpAsyncGroupCopy>::Validate,
    InstructionHelper<Opcode::OpWaitGroupEvents>::Validate,
    InstructionHelper<Opcode::OpGroupAll>::Validate,
    InstructionHelper<Opcode::OpGroupAny>::Validate,
    InstructionHelper<Opcode::OpGroupBroadcast>::Validate,
    InstructionHelper<Opcode::OpGroupIAdd>::Validate,
    InstructionHelper<Opcode::OpGroupFAdd>::Validate,
    InstructionHelper<Opcode::OpGroupFMin>::Validate,
    InstructionHelper<Opcode::OpGroupUMin>::Validate,
    InstructionHelper<Opcode::OpGroupSMin>::Validate,
    InstructionHelper<Opcode::OpGroupFMax>::Validate,
    InstructionHelper<Opcode::OpGroupUMax>::Validate,
    InstructionHelper<Opcode::OpGroupSMax>::Validate,
    InstructionHelper<Opcode::OpGenericCastToPtrExplicit>::Validate,
    InstructionHelper<Opcode::OpGenericPtrMemSemantics>::Validate,
    InstructionHelper<Opcode::OpReadPipe>::Validate,
    InstructionHelper<Opcode::OpWritePipe>::Validate,
    InstructionHelper<Opcode::OpReservedReadPipe>::Validate,
    InstructionHelper<Opcode::OpReservedWritePipe>::Validate,
    InstructionHelper<Opcode::OpReserveReadPipePackets>::Validate,
    InstructionHelper<Opcode::OpReserveWritePipePackets>::Validate,
    InstructionHelper<Opcode::OpCommitReadPipe>::Validate,
    InstructionHelper<Opcode::OpCommitWritePipe>::Validate,
    InstructionHelper<Opcode::OpIsValidReserveId>::Validate,
    InstructionHelper<Opcode::OpGetNumPipePackets>::Validate,
    InstructionHelper<Opcode::OpGetMaxPipePackets>::Validate,
    InstructionHelper<Opcode::OpGroupReserveReadPipePackets>::Validate,
    InstructionHelper<Opcode::OpGroupReserveWritePipePackets>::Validate,
    InstructionHelper<Opcode::OpGroupCommitReadPipe>::Validate,
    InstructionHelper<Opcode::OpGroupCommitWritePipe>::Validate,
    InstructionHelper<Opcode::OpEnqueueMarker>::Validate,
    InstructionHelper<Opcode::OpEnqueueKernel>::Validate,
    InstructionHelper<Opcode::OpGetKernelNDrangeSubGroupCount>::Validate,
    InstructionHelper<Opcode::OpGetKernelNDrangeMaxSubGroupSize>::Validate,
    InstructionHelper<Opcode::OpGetKernelWorkGroupSize>::Validate,
    InstructionHelper<Opcode::OpGetKernelPreferredWorkGroupSizeMultiple>::Validate,
    InstructionHelper<Opcode::OpRetainEvent>::Validate,
    InstructionHelper<Opcode::OpReleaseEvent>::Validate,
    InstructionHelper<Opcode::OpCreateUserEvent>::Validate,
    InstructionHelper<Opcode::OpIsValidEvent>::Validate,
    InstructionHelper<Opcode::OpSetUserEventStatus>::Validate,
    InstructionHelper<Opcode::OpCaptureEventProfilingInfo>::Validate,
    InstructionHelper<Opcode::OpGetDefaultQueue>::Validate,
    InstructionHelper<Opcode::OpBuildNDRange>::Validate,
    InstructionHelper<Opcode::OpSatConvertSToU>::Validate,
    InstructionHelper<Opcode::OpSatConvertUToS>::Validate,
    InstructionHelper<Opcode::OpAtomicIMin>::Validate,
    InstructionHelper<Opcode::OpAtomicIMax>::Validate
};
static size_t InstructionValidationCount = sizeof(InstructionValidation) / sizeof(ValidationFunction*);




bool Module::Initialize(char* buffer, size_t char_length)
{
    if (InstructionValidationCount != (size_t)Opcode::LastValue + 1)
        return false;

    if (char_length < sizeof(ModuleHeader))
    {
        totalWordCount = 0;
        return false;
    }

    header = (ModuleHeader*)buffer;     
    char_length -= sizeof(ModuleHeader);
    totalWordCount = (char_length / sizeof(uint32_t));
    if ((char_length - (totalWordCount * sizeof(Word))) != 0)
    {
        totalWordCount = 0;
        return false;
    }
    auto words = (Word*)(buffer + sizeof(ModuleHeader));
    if (totalWordCount > 0 &&
        header->magic == SPIRV_MAGIC_REV)
    {
        for (size_t i = 0; i < totalWordCount; ++i)
            words[i] = bswap_32(words[i]);
    }

    // verify header-data
    if (header->magic   != SPIRV_MAGIC ||
        header->version != SPIRV_VERSION)
        return false;

    start   = (InstructionHeader*)words;
    end     = (InstructionHeader*)(words + totalWordCount);

    // lamda to go to next instruction but verify it before returning it,
    //  that way we verify all instructions at the same time as finding
    //  the start positions of all instruction types in the module
    auto NextInstruction = [&](InstructionHeader const* current)
    {
        auto count  = current->wordCount;
        auto opcode = current->opcode;
        auto next   = ((InstructionHeader const*)(((Word const*)current) + count));
        if (count == 0)
            return (InstructionHeader const*)nullptr;

        if (next > end)
            return (InstructionHeader const*)nullptr;

        if (opcode == Opcode::OpNop)
            return (InstructionHeader const*)nullptr;

        if (opcode > Opcode::LastValue)
            return (InstructionHeader const*)nullptr;

        if (!InstructionValidation[(int)opcode](current))
            return (InstructionHeader const*)nullptr;

        return next;
    };

    auto iterator = start;

    // Find the (optional) OpSource instruction
    source = CAST_TO(OpSource, iterator);
    if (source != nullptr) iterator = NextInstruction(iterator);
    if (iterator == nullptr) return false;


    // Find the (optional) OpSourceExtension instructions
    sourceExtensions = CAST_TO(OpSourceExtension, iterator);
    if (sourceExtensions != nullptr)
    {
        while (iterator != nullptr &&
               iterator->opcode == Opcode::OpSourceExtension)
            iterator = NextInstruction(iterator);
    }
    if (iterator == nullptr) return false;


    // Find the (optional) OpCompileFlag instructions
    compileFlags = CAST_TO(OpCompileFlag, iterator);
    if (compileFlags != nullptr)
    {
        while (iterator != nullptr &&
               iterator->opcode == Opcode::OpCompileFlag)
               iterator = NextInstruction(iterator);
    }
    if (iterator == nullptr) return false;


    // Find the (optional) OpExtension instructions
    extensions = CAST_TO(OpExtension, iterator);
    if (extensions != nullptr)
    {
        while (iterator != nullptr &&
               iterator->opcode == Opcode::OpExtension)
               iterator = NextInstruction(iterator);
    }
    if (iterator == nullptr) return false;


    // Find the (optional) OpExtInstImport instructions
    extInstImport = CAST_TO(OpExtInstImport, iterator);
    if (extInstImport != nullptr)
    {
        while (iterator != nullptr &&
               iterator->opcode == Opcode::OpExtInstImport)
               iterator = NextInstruction(iterator);
    }
    if (iterator == nullptr) return false;


    // Find the (required) OpMemoryModel instruction
    // TODO: check for "Graphical Shader, Must select the Logical addressing model."
    memoryModel = CAST_TO(OpMemoryModel, iterator);
    if (memoryModel == nullptr)
        return false;
    iterator = NextInstruction(iterator);
    if (iterator == nullptr) return false;


    // Find the (required) OpEntryPoint instructions
    // Fixme: There is at least one OpEntryPoint instruction, 
    //        UNLESS the Link capability is being used.
    // TODO: check for "Graphical Shader, Can only have one OpEntryPoint."
    // TODO: check for "OpenCL, Can only have Physical32 or Physical64 addressing model."
    entryPoints = CAST_TO(OpEntryPoint, iterator);
    if (entryPoints == nullptr)
        return false;   
    while (iterator != nullptr &&
            iterator->opcode == Opcode::OpEntryPoint)
            iterator = NextInstruction(iterator);
    if (iterator == nullptr) return false;


    // Find the (required) OpExecutionMode instructions
    executionModes = CAST_TO(OpExecutionMode, iterator);
    if (executionModes == nullptr)
        return false;   
    while (iterator != nullptr &&
            iterator->opcode == Opcode::OpExecutionMode)
            iterator = NextInstruction(iterator);
    if (iterator == nullptr) return false;


    // Find the (optional) OpString instructions
    strings = CAST_TO(OpString, iterator);
    if (strings != nullptr)
    {
        while (iterator != nullptr &&
               iterator->opcode == Opcode::OpString)
               iterator = NextInstruction(iterator);
    }
    if (iterator == nullptr) return false;


    // Find the (optional) OpName / OpMemberName instructions
    // Note: documentation is vague about this, you'd expect a 
    //       name to always precede an OpMemberName, but this 
    //       is never explicitly written down
    if (iterator->opcode == Opcode::OpName ||
        iterator->opcode == Opcode::OpMemberName)
    {
        names = iterator;
        if (names != nullptr)
        {
            while (iterator != nullptr &&
                   (
                    iterator->opcode == Opcode::OpName ||                  
                    iterator->opcode == Opcode::OpMemberName
                   ))
                   iterator = NextInstruction(iterator);
        }
        if (iterator == nullptr) return false;
    }


    // Find the (optional) OpLine instructions
    if (iterator->opcode == Opcode::OpLine)
    {
        lines = CAST_TO(OpLine, iterator);
        if (lines != nullptr)
        {
            while (iterator != nullptr &&
                   iterator->opcode == Opcode::OpLine)
                   iterator = NextInstruction(iterator);
        }
        if (iterator == nullptr) return false;
    }


    // Find the (optional) decoration instructions
    if (iterator->opcode == Opcode::OpDecorate ||
        iterator->opcode == Opcode::OpMemberDecorate ||
        iterator->opcode == Opcode::OpGroupDecorate ||
        iterator->opcode == Opcode::OpGroupMemberDecorate ||
        iterator->opcode == Opcode::OpDecorationGroup)
    {
        decorations = iterator;
        if (decorations != nullptr)
        {
            while (iterator != nullptr &&
                   (iterator->opcode == Opcode::OpDecorate ||
                    iterator->opcode == Opcode::OpMemberDecorate ||
                    iterator->opcode == Opcode::OpGroupDecorate ||
                    iterator->opcode == Opcode::OpGroupMemberDecorate ||
                    iterator->opcode == Opcode::OpDecorationGroup
                   ))
                   iterator = NextInstruction(iterator);
        }
        if (iterator == nullptr) return false;
    }




    // Find the declaration instructions
    if (iterator->opcode == Opcode::OpTypeVoid ||
        iterator->opcode == Opcode::OpTypeBool ||
        iterator->opcode == Opcode::OpTypeInt ||
        iterator->opcode == Opcode::OpTypeFloat ||
        iterator->opcode == Opcode::OpTypeVector ||
        iterator->opcode == Opcode::OpTypeMatrix ||
        iterator->opcode == Opcode::OpTypeSampler ||
        iterator->opcode == Opcode::OpTypeFilter ||
        iterator->opcode == Opcode::OpTypeArray ||
        iterator->opcode == Opcode::OpTypeRuntimeArray ||
        iterator->opcode == Opcode::OpTypeStruct ||
        iterator->opcode == Opcode::OpTypeOpaque ||
        iterator->opcode == Opcode::OpTypePointer ||
        iterator->opcode == Opcode::OpTypeFunction ||
        iterator->opcode == Opcode::OpTypeEvent ||
        iterator->opcode == Opcode::OpTypeDeviceEvent ||
        iterator->opcode == Opcode::OpTypeReserveId ||
        iterator->opcode == Opcode::OpTypeQueue ||
        iterator->opcode == Opcode::OpTypePipe ||

        iterator->opcode == Opcode::OpConstantTrue ||
        iterator->opcode == Opcode::OpConstantFalse ||
        iterator->opcode == Opcode::OpConstant ||
        iterator->opcode == Opcode::OpConstantComposite ||
        iterator->opcode == Opcode::OpConstantSampler ||
        iterator->opcode == Opcode::OpConstantNullPointer ||
        iterator->opcode == Opcode::OpConstantNullObject ||
        iterator->opcode == Opcode::OpSpecConstantTrue ||
        iterator->opcode == Opcode::OpSpecConstantFalse ||
        iterator->opcode == Opcode::OpSpecConstant ||
        iterator->opcode == Opcode::OpSpecConstantComposite ||

        iterator->opcode == Opcode::OpVariable ||
        iterator->opcode == Opcode::OpVariableArray)
    {
        declarations = iterator;
        if (declarations != nullptr)
        {
            while (iterator != nullptr &&
                   (iterator->opcode == Opcode::OpTypeVoid ||
                    iterator->opcode == Opcode::OpTypeBool ||
                    iterator->opcode == Opcode::OpTypeInt ||
                    iterator->opcode == Opcode::OpTypeFloat ||
                    iterator->opcode == Opcode::OpTypeVector ||
                    iterator->opcode == Opcode::OpTypeMatrix ||
                    iterator->opcode == Opcode::OpTypeSampler ||
                    iterator->opcode == Opcode::OpTypeFilter ||
                    iterator->opcode == Opcode::OpTypeArray ||
                    iterator->opcode == Opcode::OpTypeRuntimeArray ||
                    iterator->opcode == Opcode::OpTypeStruct ||
                    iterator->opcode == Opcode::OpTypeOpaque ||
                    iterator->opcode == Opcode::OpTypePointer ||
                    iterator->opcode == Opcode::OpTypeFunction ||
                    iterator->opcode == Opcode::OpTypeEvent ||
                    iterator->opcode == Opcode::OpTypeDeviceEvent ||
                    iterator->opcode == Opcode::OpTypeReserveId ||
                    iterator->opcode == Opcode::OpTypeQueue ||
                    iterator->opcode == Opcode::OpTypePipe ||

                    iterator->opcode == Opcode::OpConstantTrue ||
                    iterator->opcode == Opcode::OpConstantFalse ||
                    iterator->opcode == Opcode::OpConstant ||
                    iterator->opcode == Opcode::OpConstantComposite ||
                    iterator->opcode == Opcode::OpConstantSampler ||
                    iterator->opcode == Opcode::OpConstantNullPointer ||
                    iterator->opcode == Opcode::OpConstantNullObject ||
                    iterator->opcode == Opcode::OpSpecConstantTrue ||
                    iterator->opcode == Opcode::OpSpecConstantFalse ||
                    iterator->opcode == Opcode::OpSpecConstant ||
                    iterator->opcode == Opcode::OpSpecConstantComposite ||

                    iterator->opcode == Opcode::OpVariable ||
                    iterator->opcode == Opcode::OpVariableArray
                   ))
                   iterator = NextInstruction(iterator);
        }
        if (iterator == nullptr) return false;
    }


    
    // TODO: find all starting points (source, names, functions etc.)
    // TODO: Check for "No function can be targeted by both an OpEntryPoint instruction and an OpFunctionCall instruction."
    
    // TODO: Implement validation rules

    return true;
}
