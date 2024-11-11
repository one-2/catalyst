// source/tensorops/GPUStrategy.h
//
// Author: Stephen Elliott
//
// Date: 2024-11-05
//
// Description: 
//


#ifndef GPUSTRATEGY_H
#define GPUSTRATEGY_H


#include "tensorops/TensorStrategy/TensorStrategy.h"
#include "tensorops/tensor_types.h"
#include "GPUOps/GPUOps_types.h"

#include <memory>
#include <string>

namespace tensor
{

class GPUStrategy : public TensorStrategy
{
public:
    GPUStrategy();

    TensorPtr zero(int rows, int cols);
    TensorPtr identity(int dimension);
    TensorPtr sum(TensorPtr a, TensorPtr b);
    TensorPtr multiple(TensorPtr a);
    TensorPtr scalar_product(TensorPtr a, TensorPtr b);
    TensorPtr tensor_product(TensorPtr a, TensorPtr b);
    TensorPtr reLu(TensorPtr a);
    TensorPtr softmax(TensorPtr a);

private:
    KernelPointer get_kernel(std::string type);

};

} // namespace tensor

#endif // GPUSTRATEGY_H