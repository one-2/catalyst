// source/tensorops/GPUTensorStrategy.h
//
// Author: Stephen Elliott
//
// Date: 2024-11-05
//
// Description: 
//
// Usage: 
//

#ifndef GPUTENSORSTRATEGY
#define GPUTENSORSTRATEGY

#include "tensorops/maths_typedefs.h"

class GPUTensorStrategy : public TensorOpsExecutionStrategy
{


// TODO: Update block diagram for this interface


public:
    Tensor zero(int rows, int cols);
    Tensor identity(int dimension);
    Tensor sum(const Tensor& a, const Tensor& b);
    Tensor multiple(const Tensor& a);
    Tensor scalar_product(const Tensor& a, const Tensor& b);
    Tensor tensor_product(const Tensor& a, const Tensor& b);
    Tensor reLu(const Tensor& a);
    Tensor softmax(const Tensor& a);

private:
    KernelCallback get_kernel(std::string type); // TODO: Include type from kernel namespace (unment dependency)
    // NOTE: ^ Calls the singleton cache lookup table for this maths type. That method is
    //       encapsulated in KernelCacheSingleton. 
}

#endif // GPUTENSORSTRATEGY