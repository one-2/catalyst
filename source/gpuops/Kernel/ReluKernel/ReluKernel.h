#ifndef RELUKERNEL_H
#define RELUKERNEL_H

#include "gpuops/Kernel/Kernel.h"

namespace gpuops
{

class ReLuKernel : public Kernel
{
public:
    ReLuKernel(int workgroup_size, int workgroup_count);
    static std::string build_src(int workgroup_size, int workgroup_count);

private:
    static const std::string base_src_path = "./relu_base_src.txt";

};
} // namespace gpuops

#endif RELUKERNEL_H