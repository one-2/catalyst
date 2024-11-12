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

namespace gpuops
{

class KernelFactory
{
public:
    KernelCallback build_kernel(std::string type, int in_size);
    // NOTE: should change KernelCallback to KernelPtr?

private:
    KernelCallback build_matmul(int in_size, int workgroup_size); // NOTE: Do we need in_size here?
    KernelCallback build_relu(int in_size, int workgroup_size);

}

} // namespace gpuops

#endif // KERNELFACTORY_H