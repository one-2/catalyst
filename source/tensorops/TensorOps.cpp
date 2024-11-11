#include "tensorops/TensorOps.h"

namespace tensor {

// uctorPtr
TensorOps::TensorOps(bool execute_on_gpu) {
    if (execute_on_gpu) {
        // TODO
    } else {
        // TODO
    }
}

// Create a zero tensor
TensorPtr TensorOps::zero(int rows, int cols) {
    // TODO

}

// Create an identity tensor
TensorPtr TensorOps::identity(int dimension) {
    // TODO

}

// Sum of two tensors
TensorPtr TensorOps::sum(TensorPtr a, TensorPtr b) {
    // TODO

}

// Multiply TensorPtr by itself
TensorPtr TensorOps::multiple(TensorPtr a) {
    // TODO

}

// Scalar product of two tensors
TensorPtr TensorOps::scalar_product(TensorPtr a, TensorPtr b) {
    // TODO

}

// Tensor product of two tensors
TensorPtr TensorOps::tensor_product(TensorPtr a, TensorPtr b) {
    // TODO

}

// Apply ReLU activation function
TensorPtr TensorOps::reLu(TensorPtr a) {
    // TODO

}

// Apply softmax function
TensorPtr TensorOps::softmax(TensorPtr a) {
    // TODO

}

} // namespace tensor