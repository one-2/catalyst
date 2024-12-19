

#ifndef MATMULKERNEL_H
#define MATMULKERNEL_H

#include "gpuops/Kernel/Kernel.h"

namespace gpuops
{

class MatmulKernel : public Kernel
{
public:
    MatmulKernel(int workgroup_size);
    static std::string build_src(int workgroup_size);

private:
    static const std::string base_src_path = "./matmul_base_src.txt";

};
} // namespace gpuops

#endif MATMULKERNEL_H