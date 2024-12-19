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

#include <string>

namespace gpuops
{

class Kernel
{
public:
    virtual void compile() = 0;
    static std::string get_machine_code();

protected:
    Kernel(int workgroup_size, int workgroup_count);

private:
    int workgroup_size;
    int workgroup_count;
    std::string src;
    std::string machine_code;

};
} // namespace gpuops

#endif // KERNEL_H