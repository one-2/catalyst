#include "./TensorOpsSelector.h"

namespace tensor {

// uctorPtr
TensorOpsSelector::TensorOps(bool execute_on_gpu) {
    if (execute_on_gpu) {
        // TODO
    } else {
        // TODO
    }
}

// Create a zero tensor
TensorPtr TensorOpsSelector::zero(int rows, int cols) {
    // TODO

}

// Create an identity tensor
TensorPtr TensorOpsSelector::identity(int dimension) {
    // TODO

}

// Sum of two tensors
TensorPtr TensorOpsSelector::sum(TensorPtr a, TensorPtr b) {
    // TODO

}

// Multiply TensorPtr by itself
TensorPtr TensorOpsSelector::multiple(TensorPtr a) {
    // TODO

}

// Scalar product of two tensors
TensorPtr TensorOpsSelector::scalar_product(TensorPtr a, TensorPtr b) {
    // TODO

}

// Tensor product of two tensors
TensorPtr TensorOpsSelector::tensor_product(TensorPtr a, TensorPtr b) {
    // TODO

}

// Apply ReLU activation function
TensorPtr TensorOpsSelector::reLu(TensorPtr a) {
    // TODO

}

// Apply softmax function
TensorPtr TensorOpsSelector::softmax(TensorPtr a) {
    // TODO

}

} // namespace tensor