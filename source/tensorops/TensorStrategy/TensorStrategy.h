// source/tensorops/TensorStrategy/TensorStrategy.h
//
// Author: Stephen Elliott
//
// Date: 2024-11-11
//
// Description: 
//
// Usage: 
//
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
    // NOTE: Avoid frequent reinitialisation by storing on CG.

    virtual TensorPtr zero(int rows, int cols)                  = 0;
    virtual TensorPtr identity(int dimension)                   = 0;
    virtual TensorPtr sum(TensorPtr a, TensorPtr b)             = 0;
    virtual TensorPtr multiple(TensorPtr a, TensorPtr scalar)   = 0;
    virtual TensorPtr scalar_product(TensorPtr a, TensorPtr b)  = 0;
    virtual TensorPtr Tensor_product(TensorPtr a, TensorPtr b)  = 0;
    virtual TensorPtr reLu(TensorPtr a)                         = 0;
    virtual TensorPtr softmax(TensorPtr a)                      = 0;


};
  
} // namespace tensor

#endif // TENSORSTRATEGY_H