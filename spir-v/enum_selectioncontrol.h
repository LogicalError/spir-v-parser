#pragma once

// This value is a mask; it can be formed by combining the bits from multiple rows in the table below.
// Used by:
//  OpSelectionMerge.
enum class SelectionControl : uint32_t
{
    None = 0x0,

    Flatten = 0x1,      // Strong request, to the extent possible, to remove the flow
                        // control for this selection.

    DontFlatten = 0x2,  // Strong request, to the extent possible, to keep this selection
                        // as flow control.
};

static char* SelectionControlToString(SelectionControl input)
{
    switch (input)
    {
        case SelectionControl::None:            return "None";
        case SelectionControl::Flatten:         return "Flatten";
        case SelectionControl::DontFlatten:     return "DontFlatten";
        default:                                return nullptr;
    }
}
