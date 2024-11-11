// source/tensorops/TensorOps.h
//
// Author: Stephen Elliott
//
// Date: 2024-11-04
//
// Description: Public interface to mathematics operations
//


#ifndef TENSOROPS_H
#define TENSOROPS_H

#include <torch/torch.h>
#include "tensorops/TensorStrategy/TensorStrategy.h"
#include "tensorops/tensor_types.h"

namespace tensor {

class TensorOps
{
public:
    // Constructor
    TensorOps(bool execute_on_gpu);

    TensorPtr zero(int rows, int cols);
    TensorPtr identity(int dimension);
    TensorPtr sum(const TensorPtr& a, const TensorPtr& b);
    TensorPtr multiple(const TensorPtr& a);
    TensorPtr scalar_product(const TensorPtr& a, const TensorPtr& b);
    TensorPtr tensor_product(const TensorPtr& a, const TensorPtr& b);
    TensorPtr reLu(const TensorPtr& a);
    TensorPtr softmax(const TensorPtr& a);

private:
    TensorStrategy big_daddy;

};
  
}

#endif // TENSOROPS_H