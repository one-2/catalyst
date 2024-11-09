// source/tensorops/CPUTensorStrategy.h
//
// Stephen Elliott, 2024-10-06
//
// Description: This file contains the declarations for tensor operations
//

#ifndef CPUTENSORSTRATEGY_H
#define CPUTENSORSTRATEGY_H

#include "tensorops/tensor_types.h"
#include "tensorops/TensorStrategy/TensorStrategy.h"

#include <torch/torch.h>
#include <ostream>


namespace tensor
{

class CPUTensorStrategy : public TensorStrategy
{
    Tensor zero(int rows, int cols);
    Tensor identity(int dimension);
    Tensor sum(const Tensor& a, const Tensor& b);
    Tensor multiple(const Tensor& a);
    Tensor scalar_product(const Tensor& a, const Tensor& b);
    Tensor tensor_product(const Tensor& a, const Tensor& b);
    Tensor reLu(const Tensor& a);
    Tensor softmax(const Tensor& a);
};

} // namespace tensor

#endif // CPUTENSORSTRATEGY_H
