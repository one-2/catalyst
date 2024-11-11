// source/tensorops/TensorStrategy/GPUStrategy/GPUStrategy.cpp
//
// Author: Stephen Elliott
//
// Date: 2024-11-11
//
// Description: 
//
// Usage: 
//
// source/tensorops/TensorStrategy/GPUStrategy/GPUStrategy.cpp
//
// Author: Stephen Elliott
//
// Date: 2024-11-10
//
// Description: 
//


#include "./GPUStrategy.h"


GPUStrategy::GPUStrategy()
{
    // TODO
}


TensorPtr GPUStrategy::zero(int rows, int cols) {
    // TODO
    return TensorPtr();
}


TensorPtr GPUStrategy::identity(int dimension) {
    // TODO
    return TensorPtr();
}


TensorPtr GPUStrategy::sum(TensorPtr a, TensorPtr b) {
    // TODO
    return TensorPtr();
}


TensorPtr GPUStrategy::multiple(TensorPtr a, TensorPtr scalar) {
    // TODO
    return TensorPtr();
}


TensorPtr GPUStrategy::scalar_product(TensorPtr a, TensorPtr b) {
    // TODO
    return TensorPtr();
}


TensorPtr GPUStrategy::tensor_product(TensorPtr a, TensorPtr b) {
    // TODO
    return TensorPtr();
}


TensorPtr GPUStrategy::reLu(TensorPtr a) {
    // TODO
    return TensorPtr();
}


TensorPtr GPUStrategy::softmax(TensorPtr a) {
    // TODO
    return TensorPtr();
}


KernelPointer GPUStrategy::get_kernel(std::string type) {
    // TODO
    return KernelPointer();
}

