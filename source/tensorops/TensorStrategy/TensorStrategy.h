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
    // NOTE: Avoid frequent reinitialisation by storing on CG.

    virtual TensorPtr zero(int rows, int cols)                                  = 0;
    virtual TensorPtr identity(int dimension)                                   = 0;
    virtual TensorPtr sum(const TensorPtr a, const TensorPtr b)                 = 0;
    virtual TensorPtr multiple(const TensorPtr a)                               = 0;
    virtual TensorPtr scalar_product(const TensorPtr a, const TensorPtr b)      = 0;
    virtual TensorPtr Tensor_product(const TensorPtr a, const TensorPtr b)      = 0;
    virtual TensorPtr reLu(const TensorPtr a)                                   = 0;
    virtual TensorPtr softmax(const TensorPtr a)                                = 0;


};
  
} // namespace tensor

#endif // TENSORSTRATEGY_H