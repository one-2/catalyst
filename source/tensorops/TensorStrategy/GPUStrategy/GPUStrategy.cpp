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


GPUStrategy::GPUStrategy() {
    // TODO
    // Initialise the KernelManager

}


TensorPtr GPUStrategy::zero(int rows, int cols) {
    // TODO
    // Call KernelManager.run_kernel(type, in_size)
    return nullptr;
}


TensorPtr GPUStrategy::identity(int dimension) {
    // TODO
    // Call KernelManager.run_kernel(type, in_size)
    return nullptr;
}


TensorPtr GPUStrategy::sum(TensorPtr a, TensorPtr b) {
    // TODO
    // Call KernelManager.run_kernel(type, in_size)
    return nullptr;
}


TensorPtr GPUStrategy::multiple(TensorPtr a, TensorPtr scalar) {
    // TODO
    // Call KernelManager.run_kernel(type, in_size)
    return nullptr;
}


TensorPtr GPUStrategy::scalar_product(TensorPtr a, TensorPtr b) {
    // TODO
    // Call KernelManager.run_kernel(type, in_size)
    return nullptr;
}


TensorPtr GPUStrategy::tensor_product(TensorPtr a, TensorPtr b) {
    // TODO
    // Call KernelManager.run_kernel(type, in_size)
    return nullptr;
}


TensorPtr GPUStrategy::reLu(TensorPtr a) {
    // TODO
    // Call KernelManager.run_kernel(type, in_size)
    return nullptr;
}


TensorPtr GPUStrategy::softmax(TensorPtr a) {
    // TODO
    // Call KernelManager.run_kernel(type, in_size)
    return nullptr;
}


KernelPointer GPUStrategy::get_kernel(std::string type) {
    // TODO
    return KernelPointer();
}

