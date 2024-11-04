// Kernel/Kernel.h
//
// Author: Stephen Elliott
//
// Date: 2024-11-05
//
// Description: Abstract superclass to OpenCL dynamic GPU kernels. 
//

#ifndef KERNEL_H
#define KERNEL_H

namespace gpuops {

class Kernel
{
public:
    virtual void execute() = 0; // NOTE: =0 => virtual must be overridden. Otherwise, it's optional.
    void compile();

protected:
    Kernel() = default; // For subclasses
    // NOTE: Should I also define destructors for these?

};
} // namespace gpuops

#endif // KERNEL_H