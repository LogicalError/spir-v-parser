#pragma once

// The source language is an annotation, with no semantics that affect 
// the meaning of other parts of the module. 
//
// Used by:
//  OpSource.
enum class SourceLanguage : uint32_t
{
    Unknown = 0,
    ESSL = 1,
    GLSL = 2,
    OpenCL = 3
};

static char* SourceLanguageString(SourceLanguage input)
{
    switch (input)
    {
        case SourceLanguage::Unknown:   return "Unknown";
        case SourceLanguage::ESSL:      return "ESSL";
        case SourceLanguage::GLSL:      return "GLSL";
        case SourceLanguage::OpenCL:    return "OpenCL";
        default:                        return nullptr;
    }
}
