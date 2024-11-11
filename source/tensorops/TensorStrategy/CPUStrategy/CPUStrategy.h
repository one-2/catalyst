// source/tensorops/CPUStrategy.h
//
// Stephen Elliott, 2024-10-06
//
// Description: This file contains the declarations for tensorPtr operations
//

#ifndef CPUSTRATEGY_H
#define CPUSTRATEGY_H


#include "tensorops/tensor_types.h"
#include "tensorops/TensorStrategy/TensorStrategy.h"

#include <torch/torch.h>

#include <ostream>


namespace tensor
{

class CPUStrategy : public TensorStrategy
{
    TensorPtr zero(int rows, int cols);
    TensorPtr identity(int dimension);
    TensorPtr sum(TensorPtr a, TensorPtr b);
    TensorPtr multiple(TensorPtr a, double scalar);
    TensorPtr scalar_product(TensorPtr a, TensorPtr b);
    TensorPtr tensor_product(TensorPtr a, TensorPtr b);
    TensorPtr reLu(TensorPtr a);
    TensorPtr softmax(TensorPtr a);
};

} // namespace tensor

#endif // CPUSTRATEGY_H
