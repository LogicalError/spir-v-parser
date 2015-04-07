#pragma once

// Specify when the child kernel begins execution.
// Note: Implementations are not required to honor this flag.
//		 Implementations may not schedule kernel launch earlier than the
//		 point specified by this flag, however.
// Used by:
//	OpEnqueueKernel.
enum class KernelEnqueueFlags : uint32_t
{
	NoWait = 0,			// Indicates that the enqueued kernels do not need to wait
						// for the parent kernel to finish execution before they begin
						// execution.
						// 
						// Required Capability
						//	Kernel

	WaitKernel = 1,		// Indicates that all work-items of the parent kernel must
						// finish executing and all immediate side effects committed
						// before the enqueued child kernel may begin execution.
						// Note: Immediate meaning not side effects resulting from
						// child kernels. The side effects would include stores to
						// global memory and pipe reads and writes.
						// 
						// Required Capability
						//	Kernel

	WaitWorkGroup = 2	// Indicates that the enqueued kernels wait only for the
						// workgroup that enqueued the kernels to finish before they
						// begin execution.
						// Note: This acts as a memory synchronization point
						// between work-items in a work-group and child kernels
						// enqueued by work-items in the work-group.
						// 
						// Required Capability
						//	Kernel
};


static char* KernelEnqueueFlagsToString(KernelEnqueueFlags input)
{
	switch (input)
	{
		case KernelEnqueueFlags::NoWait:		return "NoWait";
		case KernelEnqueueFlags::WaitKernel:	return "WaitKernel";
		case KernelEnqueueFlags::WaitWorkGroup:	return "WaitWorkGroup";
		default:	return "??";
	}
}
