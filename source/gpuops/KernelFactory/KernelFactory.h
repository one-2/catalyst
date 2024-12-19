// KernelFactory/KernelFactory.h
//
// Author: Stephen Elliott
//
// Date: 2024-11-05
//
// Description: Factory pattern creates and compiles GPU kernels on demand.
//

#ifndef KERNELFACTORY_H
#define KERNELFACTORY_H

#include <string>

namespace gpuops
{

class KernelFactory
{
public:
    KernelPtr build_kernel(std::string type, int workgroup_size, int workgroup_count);

private:
    KernelPtr build_matmul(int workgroup_size, int workgroup_count);
    KernelPtr build_relu(int workgroup_size, int workgroup_count);

}

} // namespace gpuops

#endif // KERNELFACTORY_H