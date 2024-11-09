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

    Tensor zero(int rows, int cols);
    Tensor identity(int dimension);
    Tensor sum(const Tensor& a, const Tensor& b);
    Tensor multiple(const Tensor& a);
    Tensor scalar_product(const Tensor& a, const Tensor& b);
    Tensor tensor_product(const Tensor& a, const Tensor& b);
    Tensor reLu(const Tensor& a);
    Tensor softmax(const Tensor& a);

private:
    KernelPointer get_kernel(std::string type);

};

} // namespace tensor

#endif // GPUSTRATEGY_H