// source/tensorops/TensorOpsSelector.cpp
//
// Author: Stephen Elliott
//
// Date: 2024-11-11
//
// Description: 
//
// Usage: 
//
#include "./TensorOpsSelector.h"
#include "tensorops/TensorStrategy/GPUStrategy/GPUStrategy.h"
#include "tensorops/TensorStrategy/CPUStrategy/CPUStrategy.h"


namespace tensor {

// uctorPtr
TensorOpsSelector::TensorOps(bool execute_on_gpu) {
    if (execute_on_gpu) {
        big_daddy = GPUStrategy();
    } else {
        big_daddy = CPUStrategy();
    };

}

// Create a zero tensor
TensorPtr TensorOpsSelector::zero(int rows, int cols) {
    return big_daddy.zero(rows, cols);

}

// Create an identity tensor
TensorPtr TensorOpsSelector::identity(int dimension) {
    return big_daddy.identity(dimension);

}

// Sum of two tensors
TensorPtr TensorOpsSelector::sum(TensorPtr a, TensorPtr b) {
    return big_daddy.sum(a, b);

}

// Multiply TensorPtr by itself
TensorPtr TensorOpsSelector::multiple(TensorPtr a, TensorPtr scalar) {
    return big_daddy.multiple(a, scalar);

}

// Scalar product of two tensors
TensorPtr TensorOpsSelector::scalar_product(TensorPtr a, TensorPtr b) {
    return big_daddy.scalar_product(a, b);

}

// Tensor product of two tensors
TensorPtr TensorOpsSelector::tensor_product(TensorPtr a, TensorPtr b) {
    return big_daddy.tensor_product(a, b);

}

// Apply ReLU activation function
TensorPtr TensorOpsSelector::reLu(TensorPtr a) {
    return big_daddy.reLu(a);

}

// Apply softmax function
TensorPtr TensorOpsSelector::softmax(TensorPtr a) {
    return big_daddy.softmax(a);

}

} // namespace tensor