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


Tensor GPUStrategy::zero(int rows, int cols) {
    // TODO
    return Tensor();
}


Tensor GPUStrategy::identity(int dimension) {
    // TODO
    return Tensor();
}


Tensor GPUStrategy::sum(const Tensor& a, const Tensor& b) {
    // TODO
    return Tensor();
}


Tensor GPUStrategy::multiple(const Tensor& a) {
    // TODO
    return Tensor();
}


Tensor GPUStrategy::scalar_product(const Tensor& a, const Tensor& b) {
    // TODO
    return Tensor();
}


Tensor GPUStrategy::tensor_product(const Tensor& a, const Tensor& b) {
    // TODO
    return Tensor();
}


Tensor GPUStrategy::reLu(const Tensor& a) {
    // TODO
    return Tensor();
}


Tensor GPUStrategy::softmax(const Tensor& a) {
    // TODO
    return Tensor();
}


KernelPointer GPUStrategy::get_kernel(std::string type) {
    // TODO
    return KernelPointer();
}

