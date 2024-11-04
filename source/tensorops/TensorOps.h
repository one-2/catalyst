// source/tensorops/TensorOps.h
//
// Author: Stephen Elliott
//
// Date: 2024-11-04
//
// Description: Public interface to mathematics operations
//
// Usage: 
//

#ifndef TENSOROPS_H
#define TENSOROPS_H

#include <torch/torch.h>
#include "tensorops/TensorOpsExecutionStrategy.h"
#include "tensorops/maths_typedefs.h"

namespace maths {

class TensorOps
{
public:
    // Constructor

    Tensor zero(int rows, int cols);
    Tensor identity(int dimension);
    Tensor sum(const Tensor& a, const Tensor& b);
    Tensor multiple(const Tensor& a);
    Tensor scalar_product(const Tensor& a, const Tensor& b);
    Tensor tensor_product(const Tensor& a, const Tensor& b);
    Tensor reLu(const Tensor& a);
    Tensor softmax(const Tensor& a);

private:
    TensorOpsExecutionStrategy big_daddy();
};
  
}

#endif // TENSOROPS_H