#pragma once

#pragma pack(push)
#pragma pack(1)


static const int SPIRV_MAGIC        = 0x07230203;
static const int SPIRV_MAGIC_REV    = 0x03022307;
static const int SPIRV_VERSION      = 99;

struct ModuleHeader
{
    uint32_t            magic;
    uint32_t            version;
    uint32_t            generator;
    uint32_t            bound;
    uint32_t            reserved;
};

struct Module
{
public:
    Module()
        : totalWordCount                (0)
        , header                (nullptr)
        , source                (nullptr)
        , sourceExtensions      (nullptr)
        , compileFlags          (nullptr)
        , extensions            (nullptr)
        , extInstImport         (nullptr)
        , memoryModel           (nullptr)
        , entryPoints           (nullptr)
        , executionModes        (nullptr)
        , strings               (nullptr)
        , names                 (nullptr)
        , lines                 (nullptr)
        , decorations               (nullptr)
        , declarations          (nullptr)
        , functionDeclarations  (nullptr)
        , functionDefinitions   (nullptr)
    {
    }

public:
    size_t                              totalWordCount;

    ModuleHeader*                       header;
    InstructionHeader const*            start;
    InstructionHeader const*            end;

    // TODO: should we have start-end pointers for different sections?

    // The module layout
    OP_STRUCT(OpSource) const*          source;                 // optional / single
    OP_STRUCT(OpSourceExtension) const* sourceExtensions;       // optional / multiple
    OP_STRUCT(OpCompileFlag) const*     compileFlags;           // optional / multiple
    OP_STRUCT(OpExtension) const*       extensions;             // optional / multiple
    OP_STRUCT(OpExtInstImport) const*   extInstImport;          // optional / multiple
    OP_STRUCT(OpMemoryModel) const*     memoryModel;            // required / single
    OP_STRUCT(OpEntryPoint) const*      entryPoints;            // required / multiple
    OP_STRUCT(OpExecutionMode) const*   executionModes;         // required / multiple

    // all debug and annotation instructions
    OP_STRUCT(OpString) const*          strings;                // all string declarations,     optional / multiple
    InstructionHeader const*            names;                  // all name declarations,       optional / multiple
    OP_STRUCT(OpLine) const*            lines;                  // all line declarations,       optional / multiple
    InstructionHeader const*            decorations;            // all decoration declarations, optional / multiple

    // all type declaration / all constant instructions
    InstructionHeader const*            declarations;
    OP_STRUCT(OpFunction) const*        functionDeclarations;   // optional / multiple    
    OP_STRUCT(OpFunction) const*        functionDefinitions;    // required / multiple      


public:
    bool Initialize(char* buffer, size_t char_length);


private:

    // TODO: test this
    InstructionHeader const*const Next(InstructionHeader const* previous) const
    { 
        auto result = ((InstructionHeader const*)(((Word const*)previous) + previous->wordCount));
        if (result >= end)
            return nullptr;
        return result;
    }

    // TODO: test this
    // NOTE: assumes string is the last element of an instruction (so far always the case)
    char const* GetString(InstructionHeader const* instruction, LiteralString string, size_t* out_length) const
    {
        *out_length = 0;
        auto offset = (size_t)(((Word const*)string) - ((Word const*)instruction));
        if (offset > instruction->wordCount || offset < 1) 
            return nullptr;

        auto length = (size_t)(instruction->wordCount - offset) * sizeof(Word);
        if ((void*)(string + length) >= (void*)end)
            return nullptr;

        *out_length = length;
        return (char const*)string;
    }


};


#pragma pack(pop)