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
    std::shared_ptr<Kernel> build_kernel(std::string type, Args args);
}

} // namespace gpuops

#endif // KERNELFACTORY_H