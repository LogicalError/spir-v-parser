#pragma once

enum class Opcode : uint16_t
{
    OpNop = 0,
    OpSource = 1,
    OpSourceExtension = 2,
    OpExtension = 3,
    OpExtInstImport = 4,
    OpMemoryModel = 5,
    OpEntryPoint = 6,
    OpExecutionMode = 7,
    OpTypeVoid = 8,
    OpTypeBool = 9,
    OpTypeInt = 10,
    OpTypeFloat = 11,
    OpTypeVector = 12,
    OpTypeMatrix = 13,
    OpTypeSampler = 14,
    OpTypeFilter = 15,
    OpTypeArray = 16,
    OpTypeRuntimeArray = 17,
    OpTypeStruct = 18,
    OpTypeOpaque = 19,
    OpTypePointer = 20,
    OpTypeFunction = 21,
    OpTypeEvent = 22,
    OpTypeDeviceEvent = 23,
    OpTypeReserveId = 24,
    OpTypeQueue = 25,
    OpTypePipe = 26,
    OpConstantTrue = 27,
    OpConstantFalse = 28,
    OpConstant = 29,
    OpConstantComposite = 30,
    OpConstantSampler = 31,
    OpConstantNullPointer = 32,
    OpConstantNullObject = 33,
    OpSpecConstantTrue = 34,
    OpSpecConstantFalse = 35,
    OpSpecConstant = 36,
    OpSpecConstantComposite = 37,
    OpVariable = 38,
    OpVariableArray = 39,
    OpFunction = 40,
    OpFunctionParameter = 41,
    OpFunctionEnd = 42,
    OpFunctionCall = 43,
    OpExtInst = 44,
    OpUndef = 45,
    OpLoad = 46,
    OpStore = 47,
    OpPhi = 48,
    OpDecorationGroup = 49,
    OpDecorate = 50,
    OpMemberDecorate = 51,
    OpGroupDecorate = 52,
    OpGroupMemberDecorate = 53,
    OpName = 54,
    OpMemberName = 55,
    OpString = 56,
    OpLine = 57,
    OpVectorExtractDynamic = 58,
    OpVectorInsertDynamic = 59,
    OpVectorShuffle = 60,
    OpCompositeConstruct = 61,
    OpCompositeExtract = 62,
    OpCompositeInsert = 63,
    OpCopyObject = 64,
    OpCopyMemory = 65,
    OpCopyMemorySized = 66,
    OpSampler = 67,
    OpTextureSample = 68,
    OpTextureSampleDref = 69,
    OpTextureSampleLod = 70,
    OpTextureSampleProj = 71,
    OpTextureSampleGrad = 72,
    OpTextureSampleOffset = 73,
    OpTextureSampleProjLod = 74,
    OpTextureSampleProjGrad = 75,
    OpTextureSampleLodOffset = 76,
    OpTextureSampleProjOffset = 77,
    OpTextureSampleGradOffset = 78,
    OpTextureSampleProjLodOffset = 79,
    OpTextureSampleProjGradOffset = 80,
    OpTextureFetchTexelLod = 81,
    OpTextureFetchTexelOffset = 82,
    OpTextureFetchSample = 83,
    OpTextureFetchTexel = 84,
    OpTextureGather = 85,
    OpTextureGatherOffset = 86,
    OpTextureGatherOffsets = 87,
    OpTextureQuerySizeLod = 88,
    OpTextureQuerySize = 89,
    OpTextureQueryLod = 90,
    OpTextureQueryLevels = 91,
    OpTextureQuerySamples = 92,
    OpAccessChain = 93,
    OpInBoundsAccessChain = 94,
    OpSNegate = 95,
    OpFNegate = 96,
    OpNot = 97,
    OpAny = 98,
    OpAll = 99,
    OpConvertFToU = 100,
    OpConvertFToS = 101,
    OpConvertSToF = 102,
    OpConvertUToF = 103,
    OpUConvert = 104,
    OpSConvert = 105,
    OpFConvert = 106,
    OpConvertPtrToU = 107,
    OpConvertUToPtr = 108,
    OpPtrCastToGeneric = 109,
    OpGenericCastToPtr = 110,
    OpBitcast = 111,
    OpTranspose = 112,
    OpIsNan = 113,
    OpIsInf = 114,
    OpIsFinite = 115,
    OpIsNormal = 116,
    OpSignBitSet = 117,
    OpLessOrGreater = 118,
    OpOrdered = 119,
    OpUnordered = 120,
    OpArrayLength = 121,
    OpIAdd = 122,
    OpFAdd = 123,
    OpISub = 124,
    OpFSub = 125,
    OpIMul = 126,
    OpFMul = 127,
    OpUDiv = 128,
    OpSDiv = 129,
    OpFDiv = 130,
    OpUMod = 131,
    OpSRem = 132,
    OpSMod = 133,
    OpFRem = 134,
    OpFMod = 135,
    OpVectorTimesScalar = 136,
    OpMatrixTimesScalar = 137,
    OpVectorTimesMatrix = 138,
    OpMatrixTimesVector = 139,
    OpMatrixTimesMatrix = 140,
    OpOuterProduct = 141,
    OpDot = 142,
    OpShiftRightLogical = 143,
    OpShiftRightArithmetic = 144,
    OpShiftLeftLogical = 145,
    OpLogicalOr = 146,
    OpLogicalXor = 147,
    OpLogicalAnd = 148,
    OpBitwiseOr = 149,
    OpBitwiseXor = 150,
    OpBitwiseAnd = 151,
    OpSelect = 152,
    OpIEqual = 153,
    OpFOrdEqual = 154,
    OpFUnordEqual = 155,
    OpINotEqual = 156,
    OpFOrdNotEqual = 157,
    OpFUnordNotEqual = 158,
    OpULessThan = 159,
    OpSLessThan = 160,
    OpFOrdLessThan = 161,
    OpFUnordLessThan = 162,
    OpUGreaterThan = 163,
    OpSGreaterThan = 164,
    OpFOrdGreaterThan = 165,
    OpFUnordGreaterThan = 166,
    OpULessThanEqual = 167,
    OpSLessThanEqual = 168,
    OpFOrdLessThanEqual = 169,
    OpFUnordLessThanEqual = 170,
    OpUGreaterThanEqual = 171,
    OpSGreaterThanEqual = 172,
    OpFOrdGreaterThanEqual = 173,
    OpFUnordGreaterThanEqual = 174,
    OpDPdx = 175,
    OpDPdy = 176,
    OpFwidth = 177,
    OpDPdxFine = 178,
    OpDPdyFine = 179,
    OpFwidthFine = 180,
    OpDPdxCoarse = 181,
    OpDPdyCoarse = 182,
    OpFwidthCoarse = 183,
    OpEmitVertex = 184,
    OpEndPrimitive = 185,
    OpEmitStreamVertex = 186,
    OpEndStreamPrimitive = 187,
    OpControlBarrier = 188,
    OpMemoryBarrier = 189,
    OpImagePointer = 190,
    OpAtomicInit = 191,
    OpAtomicLoad = 192,
    OpAtomicStore = 193,
    OpAtomicExchange = 194,
    OpAtomicCompareExchange = 195,
    OpAtomicCompareExchangeWeak = 196,
    OpAtomicIIncrement = 197,
    OpAtomicIDecrement = 198,
    OpAtomicIAdd = 199,
    OpAtomicISub = 200,
    OpAtomicUMin = 201,
    OpAtomicUMax = 202,
    OpAtomicAnd = 203,
    OpAtomicOr = 204,
    OpAtomicXor = 205,
    OpLoopMerge = 206,
    OpSelectionMerge = 207,
    OpLabel = 208,
    OpBranch = 209,
    OpBranchConditional = 210,
    OpSwitch = 211,
    OpKill = 212,
    OpReturn = 213,
    OpReturnValue = 214,
    OpUnreachable = 215,
    OpLifetimeStart = 216,
    OpLifetimeStop = 217,
    OpCompileFlag = 218,
    OpAsyncGroupCopy = 219,
    OpWaitGroupEvents = 220,
    OpGroupAll = 221,
    OpGroupAny = 222,
    OpGroupBroadcast = 223,
    OpGroupIAdd = 224,
    OpGroupFAdd = 225,
    OpGroupFMin = 226,
    OpGroupUMin = 227,
    OpGroupSMin = 228,
    OpGroupFMax = 229,
    OpGroupUMax = 230,
    OpGroupSMax = 231,
    OpGenericCastToPtrExplicit = 232,
    OpGenericPtrMemSemantics = 233,
    OpReadPipe = 234,
    OpWritePipe = 235,
    OpReservedReadPipe = 236,
    OpReservedWritePipe = 237,
    OpReserveReadPipePackets = 238,
    OpReserveWritePipePackets = 239,
    OpCommitReadPipe = 240,
    OpCommitWritePipe = 241,
    OpIsValidReserveId = 242,
    OpGetNumPipePackets = 243,
    OpGetMaxPipePackets = 244,
    OpGroupReserveReadPipePackets = 245,
    OpGroupReserveWritePipePackets = 246,
    OpGroupCommitReadPipe = 247,
    OpGroupCommitWritePipe = 248,
    OpEnqueueMarker = 249,
    OpEnqueueKernel = 250,
    OpGetKernelNDrangeSubGroupCount = 251,
    OpGetKernelNDrangeMaxSubGroupSize = 252,
    OpGetKernelWorkGroupSize = 253,
    OpGetKernelPreferredWorkGroupSizeMultiple = 254,
    OpRetainEvent = 255,
    OpReleaseEvent = 256,
    OpCreateUserEvent = 257,
    OpIsValidEvent = 258,
    OpSetUserEventStatus = 259,
    OpCaptureEventProfilingInfo = 260,
    OpGetDefaultQueue = 261,
    OpBuildNDRange = 262,
    OpSatConvertSToU = 263,
    OpSatConvertUToS = 264,
    OpAtomicIMin = 265,
    OpAtomicIMax = 266,

    LastValue = 266

};

static char* OpcodeToString(Opcode input)
{
    switch (input)
    {
        case Opcode::OpNop: return "Nop";
        case Opcode::OpSource: return "Source";
        case Opcode::OpSourceExtension: return "SourceExtension";
        case Opcode::OpExtension: return "Extension";
        case Opcode::OpExtInstImport: return "ExtInstImport";
        case Opcode::OpMemoryModel: return "MemoryModel";
        case Opcode::OpEntryPoint: return "EntryPoint";
        case Opcode::OpExecutionMode: return "ExecutionMode";
        case Opcode::OpTypeVoid: return "TypeVoid";
        case Opcode::OpTypeBool: return "TypeBool";
        case Opcode::OpTypeInt: return "TypeInt";
        case Opcode::OpTypeFloat: return "TypeFloat";
        case Opcode::OpTypeVector: return "TypeVector";
        case Opcode::OpTypeMatrix: return "TypeMatrix";
        case Opcode::OpTypeSampler: return "TypeSampler";
        case Opcode::OpTypeFilter: return "TypeFilter";
        case Opcode::OpTypeArray: return "TypeArray";
        case Opcode::OpTypeRuntimeArray: return "TypeRuntimeArray";
        case Opcode::OpTypeStruct: return "TypeStruct";
        case Opcode::OpTypeOpaque: return "TypeOpaque";
        case Opcode::OpTypePointer: return "TypePointer";
        case Opcode::OpTypeFunction: return "TypeFunction";
        case Opcode::OpTypeEvent: return "TypeEvent";
        case Opcode::OpTypeDeviceEvent: return "TypeDeviceEvent";
        case Opcode::OpTypeReserveId: return "TypeReserveId";
        case Opcode::OpTypeQueue: return "TypeQueue";
        case Opcode::OpTypePipe: return "TypePipe";
        case Opcode::OpConstantTrue: return "ConstantTrue";
        case Opcode::OpConstantFalse: return "ConstantFalse";
        case Opcode::OpConstant: return "Constant";
        case Opcode::OpConstantComposite: return "ConstantComposite";
        case Opcode::OpConstantSampler: return "ConstantSampler";
        case Opcode::OpConstantNullPointer: return "ConstantNullPointer";
        case Opcode::OpConstantNullObject: return "ConstantNullObject";
        case Opcode::OpSpecConstantTrue: return "SpecConstantTrue";
        case Opcode::OpSpecConstantFalse: return "SpecConstantFalse";
        case Opcode::OpSpecConstant: return "SpecConstant";
        case Opcode::OpSpecConstantComposite: return "SpecConstantComposite";
        case Opcode::OpVariable: return "Variable";
        case Opcode::OpVariableArray: return "VariableArray";
        case Opcode::OpFunction: return "Function";
        case Opcode::OpFunctionParameter: return "FunctionParameter";
        case Opcode::OpFunctionEnd: return "FunctionEnd";
        case Opcode::OpFunctionCall: return "FunctionCall";
        case Opcode::OpExtInst: return "ExtInst";
        case Opcode::OpUndef: return "Undef";
        case Opcode::OpLoad: return "Load";
        case Opcode::OpStore: return "Store";
        case Opcode::OpPhi: return "Phi";
        case Opcode::OpDecorationGroup: return "DecorationGroup";
        case Opcode::OpDecorate: return "Decorate";
        case Opcode::OpMemberDecorate: return "MemberDecorate";
        case Opcode::OpGroupDecorate: return "GroupDecorate";
        case Opcode::OpGroupMemberDecorate: return "GroupMemberDecorate";
        case Opcode::OpName: return "Name";
        case Opcode::OpMemberName: return "MemberName";
        case Opcode::OpString: return "String";
        case Opcode::OpLine: return "Line";
        case Opcode::OpVectorExtractDynamic: return "VectorExtractDynamic";
        case Opcode::OpVectorInsertDynamic: return "VectorInsertDynamic";
        case Opcode::OpVectorShuffle: return "VectorShuffle";
        case Opcode::OpCompositeConstruct: return "CompositeConstruct";
        case Opcode::OpCompositeExtract: return "CompositeExtract";
        case Opcode::OpCompositeInsert: return "CompositeInsert";
        case Opcode::OpCopyObject: return "CopyObject";
        case Opcode::OpCopyMemory: return "CopyMemory";
        case Opcode::OpCopyMemorySized: return "CopyMemorySized";
        case Opcode::OpSampler: return "Sampler";
        case Opcode::OpTextureSample: return "TextureSample";
        case Opcode::OpTextureSampleDref: return "TextureSampleDref";
        case Opcode::OpTextureSampleLod: return "TextureSampleLod";
        case Opcode::OpTextureSampleProj: return "TextureSampleProj";
        case Opcode::OpTextureSampleGrad: return "TextureSampleGrad";
        case Opcode::OpTextureSampleOffset: return "TextureSampleOffset";
        case Opcode::OpTextureSampleProjLod: return "TextureSampleProjLod";
        case Opcode::OpTextureSampleProjGrad: return "TextureSampleProjGrad";
        case Opcode::OpTextureSampleLodOffset: return "TextureSampleLodOffset";
        case Opcode::OpTextureSampleProjOffset: return "TextureSampleProjOffset";
        case Opcode::OpTextureSampleGradOffset: return "TextureSampleGradOffset";
        case Opcode::OpTextureSampleProjLodOffset: return "TextureSampleProjLodOffset";
        case Opcode::OpTextureSampleProjGradOffset: return "TextureSampleProjGradOffset";
        case Opcode::OpTextureFetchTexelLod: return "OpTextureFetchTexelLod";
        case Opcode::OpTextureFetchTexelOffset: return "TextureFetchTexelOffset";
        case Opcode::OpTextureFetchSample: return "TextureFetchSample";
        case Opcode::OpTextureFetchTexel: return "OpTextureFetchTexel";
        case Opcode::OpTextureGather: return "TextureGather";
        case Opcode::OpTextureGatherOffset: return "TextureGatherOffset";
        case Opcode::OpTextureGatherOffsets: return "TextureGatherOffsets";
        case Opcode::OpTextureQuerySizeLod: return "TextureQuerySizeLod";
        case Opcode::OpTextureQuerySize: return "TextureQuerySize";
        case Opcode::OpTextureQueryLod: return "TextureQueryLod";
        case Opcode::OpTextureQueryLevels: return "TextureQueryLevels";
        case Opcode::OpTextureQuerySamples: return "TextureQuerySamples";
        case Opcode::OpAccessChain: return "AccessChain";
        case Opcode::OpInBoundsAccessChain: return "InBoundsAccessChain";
        case Opcode::OpSNegate: return "SNegate";
        case Opcode::OpFNegate: return "FNegate";
        case Opcode::OpNot: return "Not";
        case Opcode::OpAny: return "Any";
        case Opcode::OpAll: return "All";
        case Opcode::OpConvertFToU: return "ConvertFToU";
        case Opcode::OpConvertFToS: return "ConvertFToS";
        case Opcode::OpConvertSToF: return "ConvertSToF";
        case Opcode::OpConvertUToF: return "ConvertUToF";
        case Opcode::OpUConvert: return "UConvert";
        case Opcode::OpSConvert: return "SConvert";
        case Opcode::OpFConvert: return "FConvert";
        case Opcode::OpConvertPtrToU: return "ConvertPtrToU";
        case Opcode::OpConvertUToPtr: return "ConvertUToPtr";
        case Opcode::OpPtrCastToGeneric: return "PtrCastToGeneric";
        case Opcode::OpGenericCastToPtr: return "GenericCastToPtr";
        case Opcode::OpBitcast: return "Bitcast";
        case Opcode::OpTranspose: return "Transpose";
        case Opcode::OpIsNan: return "IsNan";
        case Opcode::OpIsInf: return "IsInf";
        case Opcode::OpIsFinite: return "IsFinite";
        case Opcode::OpIsNormal: return "IsNormal";
        case Opcode::OpSignBitSet: return "SignBitSet";
        case Opcode::OpLessOrGreater: return "LessOrGreater";
        case Opcode::OpOrdered: return "Ordered";
        case Opcode::OpUnordered: return "Unordered";
        case Opcode::OpArrayLength: return "ArrayLength";
        case Opcode::OpIAdd: return "IAdd";
        case Opcode::OpFAdd: return "FAdd";
        case Opcode::OpISub: return "ISub";
        case Opcode::OpFSub: return "FSub";
        case Opcode::OpIMul: return "IMul";
        case Opcode::OpFMul: return "FMul";
        case Opcode::OpUDiv: return "UDiv";
        case Opcode::OpSDiv: return "SDiv";
        case Opcode::OpFDiv: return "FDiv";
        case Opcode::OpUMod: return "UMod";
        case Opcode::OpSRem: return "SRem";
        case Opcode::OpSMod: return "SMod";
        case Opcode::OpFRem: return "FRem";
        case Opcode::OpFMod: return "FMod";
        case Opcode::OpVectorTimesScalar: return "VectorTimesScalar";
        case Opcode::OpMatrixTimesScalar: return "MatrixTimesScalar";
        case Opcode::OpVectorTimesMatrix: return "VectorTimesMatrix";
        case Opcode::OpMatrixTimesVector: return "MatrixTimesVector";
        case Opcode::OpMatrixTimesMatrix: return "MatrixTimesMatrix";
        case Opcode::OpOuterProduct: return "OuterProduct";
        case Opcode::OpDot: return "Dot";
        case Opcode::OpShiftRightLogical: return "ShiftRightLogical";
        case Opcode::OpShiftRightArithmetic: return "ShiftRightArithmetic";
        case Opcode::OpShiftLeftLogical: return "ShiftLeftLogical";
        case Opcode::OpLogicalOr: return "LogicalOr";
        case Opcode::OpLogicalXor: return "LogicalXor";
        case Opcode::OpLogicalAnd: return "LogicalAnd";
        case Opcode::OpBitwiseOr: return "BitwiseOr";
        case Opcode::OpBitwiseXor: return "BitwiseXor";
        case Opcode::OpBitwiseAnd: return "BitwiseAnd";
        case Opcode::OpSelect: return "Select";
        case Opcode::OpIEqual: return "IEqual";
        case Opcode::OpFOrdEqual: return "FOrdEqual";
        case Opcode::OpFUnordEqual: return "FUnordEqual";
        case Opcode::OpINotEqual: return "INotEqual";
        case Opcode::OpFOrdNotEqual: return "FOrdNotEqual";
        case Opcode::OpFUnordNotEqual: return "FUnordNotEqual";
        case Opcode::OpULessThan: return "ULessThan";
        case Opcode::OpSLessThan: return "SLessThan";
        case Opcode::OpFOrdLessThan: return "FOrdLessThan";
        case Opcode::OpFUnordLessThan: return "FUnordLessThan";
        case Opcode::OpUGreaterThan: return "UGreaterThan";
        case Opcode::OpSGreaterThan: return "SGreaterThan";
        case Opcode::OpFOrdGreaterThan: return "FOrdGreaterThan";
        case Opcode::OpFUnordGreaterThan: return "FUnordGreaterThan";
        case Opcode::OpULessThanEqual: return "ULessThanEqual";
        case Opcode::OpSLessThanEqual: return "SLessThanEqual";
        case Opcode::OpFOrdLessThanEqual: return "FOrdLessThanEqual";
        case Opcode::OpFUnordLessThanEqual: return "FUnordLessThanEqual";
        case Opcode::OpUGreaterThanEqual: return "UGreaterThanEqual";
        case Opcode::OpSGreaterThanEqual: return "SGreaterThanEqual";
        case Opcode::OpFOrdGreaterThanEqual: return "FOrdGreaterThanEqual";
        case Opcode::OpFUnordGreaterThanEqual: return "FUnordGreaterThanEqual";
        case Opcode::OpDPdx: return "DPdx";
        case Opcode::OpDPdy: return "DPdy";
        case Opcode::OpFwidth: return "Fwidth";
        case Opcode::OpDPdxFine: return "DPdxFine";
        case Opcode::OpDPdyFine: return "DPdyFine";
        case Opcode::OpFwidthFine: return "FwidthFine";
        case Opcode::OpDPdxCoarse: return "DPdxCoarse";
        case Opcode::OpDPdyCoarse: return "DPdyCoarse";
        case Opcode::OpFwidthCoarse: return "FwidthCoarse";
        case Opcode::OpEmitVertex: return "EmitVertex";
        case Opcode::OpEndPrimitive: return "EndPrimitive";
        case Opcode::OpEmitStreamVertex: return "EmitStreamVertex";
        case Opcode::OpEndStreamPrimitive: return "EndStreamPrimitive";
        case Opcode::OpControlBarrier: return "ControlBarrier";
        case Opcode::OpMemoryBarrier: return "MemoryBarrier";
        case Opcode::OpImagePointer: return "ImagePointer";
        case Opcode::OpAtomicInit: return "AtomicInit";
        case Opcode::OpAtomicLoad: return "AtomicLoad";
        case Opcode::OpAtomicStore: return "AtomicStore";
        case Opcode::OpAtomicExchange: return "AtomicExchange";
        case Opcode::OpAtomicCompareExchange: return "AtomicCompareExchange";
        case Opcode::OpAtomicCompareExchangeWeak: return "AtomicCompareExchangeWeak";
        case Opcode::OpAtomicIIncrement: return "AtomicIIncrement";
        case Opcode::OpAtomicIDecrement: return "AtomicIDecrement";
        case Opcode::OpAtomicIAdd: return "AtomicIAdd";
        case Opcode::OpAtomicISub: return "AtomicISub";
        case Opcode::OpAtomicUMin: return "AtomicUMin";
        case Opcode::OpAtomicUMax: return "AtomicUMax";
        case Opcode::OpAtomicAnd: return "AtomicAnd";
        case Opcode::OpAtomicOr: return "AtomicOr";
        case Opcode::OpAtomicXor: return "AtomicXor";
        case Opcode::OpLoopMerge: return "LoopMerge";
        case Opcode::OpSelectionMerge: return "SelectionMerge";
        case Opcode::OpLabel: return "Label";
        case Opcode::OpBranch: return "Branch";
        case Opcode::OpBranchConditional: return "BranchConditional";
        case Opcode::OpSwitch: return "Switch";
        case Opcode::OpKill: return "Kill";
        case Opcode::OpReturn: return "Return";
        case Opcode::OpReturnValue: return "ReturnValue";
        case Opcode::OpUnreachable: return "Unreachable";
        case Opcode::OpLifetimeStart: return "LifetimeStart";
        case Opcode::OpLifetimeStop: return "LifetimeStop";
        case Opcode::OpCompileFlag: return "CompileFlag";
        case Opcode::OpAsyncGroupCopy: return "AsyncGroupCopy";
        case Opcode::OpWaitGroupEvents: return "WaitGroupEvents";
        case Opcode::OpGroupAll: return "GroupAll";
        case Opcode::OpGroupAny: return "GroupAny";
        case Opcode::OpGroupBroadcast: return "GroupBroadcast";
        case Opcode::OpGroupIAdd: return "GroupIAdd";
        case Opcode::OpGroupFAdd: return "GroupFAdd";
        case Opcode::OpGroupFMin: return "GroupFMin";
        case Opcode::OpGroupUMin: return "GroupUMin";
        case Opcode::OpGroupSMin: return "GroupSMin";
        case Opcode::OpGroupFMax: return "GroupFMax";
        case Opcode::OpGroupUMax: return "GroupUMax";
        case Opcode::OpGroupSMax: return "GroupSMax";
        case Opcode::OpGenericCastToPtrExplicit: return "GenericCastToPtrExplicit";
        case Opcode::OpGenericPtrMemSemantics: return "GenericPtrMemSemantics";
        case Opcode::OpReadPipe: return "ReadPipe";
        case Opcode::OpWritePipe: return "WritePipe";
        case Opcode::OpReservedReadPipe: return "ReservedReadPipe";
        case Opcode::OpReservedWritePipe: return "ReservedWritePipe";
        case Opcode::OpReserveReadPipePackets: return "ReserveReadPipePackets";
        case Opcode::OpReserveWritePipePackets: return "ReserveWritePipePackets";
        case Opcode::OpCommitReadPipe: return "CommitReadPipe";
        case Opcode::OpCommitWritePipe: return "CommitWritePipe";
        case Opcode::OpIsValidReserveId: return "IsValidReserveId";
        case Opcode::OpGetNumPipePackets: return "GetNumPipePackets";
        case Opcode::OpGetMaxPipePackets: return "GetMaxPipePackets";
        case Opcode::OpGroupReserveReadPipePackets: return "GroupReserveReadPipePackets";
        case Opcode::OpGroupReserveWritePipePackets: return "GroupReserveWritePipePackets";
        case Opcode::OpGroupCommitReadPipe: return "GroupCommitReadPipe";
        case Opcode::OpGroupCommitWritePipe: return "GroupCommitWritePipe";
        case Opcode::OpEnqueueMarker: return "EnqueueMarker";
        case Opcode::OpEnqueueKernel: return "EnqueueKernel";
        case Opcode::OpGetKernelNDrangeSubGroupCount: return "GetKernelNDrangeSubGroupCount";
        case Opcode::OpGetKernelNDrangeMaxSubGroupSize: return "GetKernelNDrangeMaxSubGroupSize";
        case Opcode::OpGetKernelWorkGroupSize: return "GetKernelWorkGroupSize";
        case Opcode::OpGetKernelPreferredWorkGroupSizeMultiple: return "GetKernelPreferredWorkGroupSizeMultiple";
        case Opcode::OpRetainEvent: return "RetainEvent";
        case Opcode::OpReleaseEvent: return "ReleaseEvent";
        case Opcode::OpCreateUserEvent: return "CreateUserEvent";
        case Opcode::OpIsValidEvent: return "IsValidEvent";
        case Opcode::OpSetUserEventStatus: return "SetUserEventStatus";
        case Opcode::OpCaptureEventProfilingInfo: return "CaptureEventProfilingInfo";
        case Opcode::OpGetDefaultQueue: return "GetDefaultQueue";
        case Opcode::OpBuildNDRange: return "BuildNDRange";
        case Opcode::OpSatConvertSToU: return "SatConvertSToU";
        case Opcode::OpSatConvertUToS: return "SatConvertUToS";
        case Opcode::OpAtomicIMin: return "AtomicIMin";
        case Opcode::OpAtomicIMax: return "AtomicIMax";

        default: return nullptr;
    }
}
