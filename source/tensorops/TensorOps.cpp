#include "tensorops/TensorOps.h"

namespace tensor {

// Constructor
TensorOps::TensorOps(bool execute_on_gpu) {
    if (execute_on_gpu) {
        // TODO
    } else {
        // TODO
    }
}

// Create a zero tensor
Tensor TensorOps::zero(int rows, int cols) {
    // TODO

}

// Create an identity tensor
Tensor TensorOps::identity(int dimension) {
    // TODO

}

// Sum of two tensors
Tensor TensorOps::sum(const Tensor& a, const Tensor& b) {
    // TODO

}

// Multiply tensor by itself
Tensor TensorOps::multiple(const Tensor& a) {
    // TODO

}

// Scalar product of two tensors
Tensor TensorOps::scalar_product(const Tensor& a, const Tensor& b) {
    // TODO

}

// Tensor product of two tensors
Tensor TensorOps::tensor_product(const Tensor& a, const Tensor& b) {
    // TODO

}

// Apply ReLU activation function
Tensor TensorOps::reLu(const Tensor& a) {
    // TODO

}

// Apply softmax function
Tensor TensorOps::softmax(const Tensor& a) {
    // TODO

}

// Private method
TensorStrategy TensorOps::big_daddy() {
    // TODO

}

} // namespace tensor