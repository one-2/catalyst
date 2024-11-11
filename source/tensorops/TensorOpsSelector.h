// source/tensoropsSelector/TensorOpsSelector.h
//
// Author: Stephen Elliott
//
// Date: 2024-11-04
//
// Description: Public interface to mathematics operations
//


#ifndef TENSOROPSSelector_H
#define TENSOROPSSelector_H

#include <torch/torch.h>
#include "tensorops/TensorStrategy/TensorStrategy.h"
#include "tensorops/tensor_types.h"

namespace tensor {

class TensorOpsSelector
{
public:
    // Constructor
    TensorOpsSelector(bool execute_on_gpu);

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

#endif // TENSOROPSSelector_H