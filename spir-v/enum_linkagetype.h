#pragma once

// Associate a linkage type to functions or global variables. 
// See linkage.
enum class LinkageType : uint32_t
{
    Export = 0,     // Accessible by other modules as well.
                    //
                    // Required Capability
                    //  Link
    Import = 1      // A declaration of a global variable or a function that exists
                    // in another module.   
                    //
                    // Required Capability
                    //  Link
};

static char* LinkageTypeToString(LinkageType input)
{
    switch (input)
    {
        case LinkageType::Export:   return "Export";
        case LinkageType::Import:   return "Import";
        default:                    return nullptr;
    }
}
 