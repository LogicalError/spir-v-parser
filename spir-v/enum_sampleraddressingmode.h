#pragma once

// Define the addressing mode of read image extended instructions.
enum class SamplerAddressingMode : uint32_t
{
    None = 0,           // The image coordinates used to sample elements of the
                        // image refer to a location inside the image, otherwise the
                        // results are undefined. 
                        //
                        // Required Capability
                        //  Kernel

    ClampEdge = 2,      // Out-of-range image coordinates are clamped to the extent. 
                        //
                        // Required Capability
                        //  Kernel

    Clamp = 4,          // Out-of-range image coordinates will return a border color. 
                        //
                        // Required Capability
                        //  Kernel

    Repeat = 6,         // Out-of-range image coordinates are wrapped to the valid
                        // range. Can only be used with normalized coordinates. 
                        //
                        // Required Capability
                        //  Kernel

    RepeatMirrored = 8  // Flip the image coordinate at every integer junction.Can
                        // only be used with normalized coordinates. 
                        //
                        // Required Capability
                        //  Kernel
};


static char* SamplerAddressingModeToString(SamplerAddressingMode input)
{
    switch (input)
    {
        case SamplerAddressingMode::None:           return "None";
        case SamplerAddressingMode::ClampEdge:      return "ClampEdge";
        case SamplerAddressingMode::Clamp:          return "Clamp";
        case SamplerAddressingMode::Repeat:         return "Repeat";
        case SamplerAddressingMode::RepeatMirrored: return "RepeatMirrored";
        default:                                    return nullptr;
    }
}
 