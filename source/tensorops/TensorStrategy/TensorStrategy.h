// source/tensorops/TensorStrategy.h
//
// Author: Stephen Elliott
//
// Date: 2024-11-04
//
// Description: Defines strategy interface. Tensor  strategy is picked
//              at runtime from the implementing classes (GPU and CPU).
//


#ifndef TENSORSTRATEGY_H
#define TENSORSTRATEGY_H

#include <torch/torch.h>
#include "tensorops/TensorStrategy/TensorStrategy.h"
#include "tensorops/tensor_types.h"

namespace tensor {

class TensorStrategy
{
public:
    // Constructor
    // NOTE: Avoid frequent reinitialisation.

    virtual Tensor zero(int rows, int cols)                             = 0;
    virtual Tensor identity(int dimension)                              = 0;
    virtual Tensor sum(const Tensor& a, const Tensor& b)                = 0;
    virtual Tensor multiple(const Tensor& a)                            = 0;
    virtual Tensor scalar_product(const Tensor& a, const Tensor& b)     = 0;
    virtual Tensor tensor_product(const Tensor& a, const Tensor& b)     = 0;
    virtual Tensor reLu(const Tensor& a)                                = 0;
    virtual Tensor softmax(const Tensor& a)                             = 0;

};
  
} // namespace tensor

#endif // TENSORSTRATEGY_H