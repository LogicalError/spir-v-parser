#pragma once

// Defines the access permissions of OpTypeSampler and OpTypePipe object.
// Used by:
//  OpTypePipe.
enum class AccessQualifier : uint32_t
{
    ReadOnly = 0,   // A read - only object. Kernel
    WriteOnly = 1,  // A write - only object. Kernel
    ReadWrite = 2   // A readable and writable object. Kernel
};

static char* AccessQualifierToString(AccessQualifier input)
{
    switch (input)
    {
        case AccessQualifier::ReadOnly:     return "ReadOnly";
        case AccessQualifier::WriteOnly:    return "WriteOnly";
        case AccessQualifier::ReadWrite:    return "ReadWrite";
        default:                            return nullptr;
    }
}
