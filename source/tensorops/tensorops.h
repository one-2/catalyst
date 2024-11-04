// source/tensorops/CPUTensorStrategy.h
//
// Stephen Elliott, 2024-10-06
//
// Description: This file contains the declarations for tensor operations
//

#ifndef CPUTENSORSTRATEGY_H
#define CPUTENSORSTRATEGY_H

#include <torch/torch.h>
#include <ostream>
#include "tensorops/maths_typedefs.h"


/////////// TODO TODO RENAME RENAME


// Function declarations
namespace maths
{

class CPUTensorStrategy
{
    CallbackTensor matmul(Tensor& a, Tensor& b);
    CallbackTensor reLu(Tensor& a);
    CallbackTensor softmax(Tensor& a);
    CallbackTensor identity(int n);
    CallbackTensor sum(Tensor& a, Tensor& b);
    CallbackTensor multiple(Tensor& a, Tensor& scalar);
    CallbackTensor scalar_product(Tensor& a, Tensor& b);
    CallbackTensor tensor_product(Tensor& a, Tensor& b);
}

}

#endif // CPUTENSORSTRATEGY_H
