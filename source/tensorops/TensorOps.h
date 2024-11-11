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
    TensorPtr sum(TensorPtr a, TensorPtr b);
    TensorPtr multiple(TensorPtr a);
    TensorPtr scalar_product(TensorPtr a, TensorPtr b);
    TensorPtr tensor_product(TensorPtr a, TensorPtr b);
    TensorPtr reLu(TensorPtr a);
    TensorPtr softmax(TensorPtr a);

private:
    TensorStrategy big_daddy;

};
  
}

#endif // TENSOROPS_H