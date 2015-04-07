#pragma once

// Associate a rounding mode to a floating-point conversion instruction.
// By default
// - Conversions from floating-point to integer types use the round-toward-zero rounding mode.
// - Conversions to floating-point types use the round-to-nearest-even rounding mode.
enum class FPRoundingMode : uint32_t
{
    RTE = 0,	// Round to nearest even.
                //
                // Required Capability
                //	Kernel

    RTZ = 1,	// Round towards zero.
                //
                // Required Capability
                //	Kernel

    RTP = 2,	// Round towards positive infinity.
                //
                // Required Capability
                //	Kernel

    RTN = 3,	// Round towards negative infinity.
                //
                // Required Capability
                //	Kernel
};

static char* FPRoundingModeToString(FPRoundingMode input)
{
    switch (input)
    {
        case FPRoundingMode::RTE:	return "RTE";
        case FPRoundingMode::RTZ:	return "RTZ";
        case FPRoundingMode::RTP:	return "RTP";
        case FPRoundingMode::RTN:	return "RTN";
        default:					return nullptr;
    }
}

