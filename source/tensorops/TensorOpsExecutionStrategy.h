// source/tensorops/TensorOpsExecutionStrategy.h
//
// Author: Stephen Elliott
//
// Date: 2024-11-04
//
// Description: Holds strategy class which picks maths execution
//              hardware at runtime. Allows dynamic or mixed execution. 
//
// Usage: Call through TensorOps class.
//

#ifndef TENSOROPSEXECUTIONSTRATEGY_H
#define TENSOROPSEXECUTIONSTRATEGY_H

#include <torch/torch.h>
#include "tensorops/TensorOpsExecutionStrategy.h"
#include "tensorops/maths_typedefs.h"

namespace maths {

class TensorOpsExecutionStrategy
{
public:
    // Constructor
    // NOTE: Should call only when compiling blocks, storing the pointers
    //       on the CG. Must avoid regular reinitialisation.
    //
    virtual Tensor zero(int rows, int cols);
    virtual Tensor identity(int dimension);
    virtual Tensor sum(const Tensor& a, const Tensor& b);
    virtual Tensor multiple(const Tensor& a);
    virtual Tensor scalar_product(const Tensor& a, const Tensor& b);
    virtual Tensor tensor_product(const Tensor& a, const Tensor& b);
    virtual Tensor reLu(const Tensor& a);
    virtual Tensor softmax(const Tensor& a);

};
  
}

#endif TENSOROPSEXECUTIONSTRATEGY_H