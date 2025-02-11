// source/computationgraph/CGNode/CGNode.cpp
//
// Author: Stephen Elliott
//
// Date: 2025-02-09
//
// Description: Implementation of CGNode class in computationgraph namespace.
//

#include "./CGNode.h"

namespace computationgraph {

// Constructor
CGNode::CGNode() {
    // Initialise weight and bias with random values
    weight_ = std::make_shared<torch::Tensor>(torch::randn({2, 1}));
    bias_ = std::make_shared<torch::Tensor>(torch::randn({1}));

    // Initialise activations, mean_activation, and gradients as empty tensors.
    activations_ = std::make_shared<torch::Tensor>(torch::empty({0}));
    mean_activation_ = std::make_shared<torch::Tensor>(torch::empty({0}));
    gradients_ = std::make_shared<torch::Tensor>(torch::empty({0}));
    mean_gradient_ = std::make_shared<torch::Tensor>(torch::empty({0}));

    // Initialise current_weight and current_bias with 1 element apiece, set to a small random number.
    weight_ = std::make_shared<torch::Tensor>(torch::randn({1}) * 0.01);
    bias_   = std::make_shared<torch::Tensor>(torch::randn({1}) * 0.01);
}

// Computation
void CGNode::compute_activations(SharedTensorPtr inputs) {
    // Input function: sum.
    // Activation function: ReLu.

    // Broadcast weight to match the input dimensions
    auto expanded_weight = weight_->expand({inputs->size(1), weight_->size(0)});

    // Weight the inputs
    auto weighted_inputs = torch::matmul(*inputs, expanded_weight);

    // Sum the weighted inputs and add bias
    auto biased_sum = weighted_inputs + *bias_;

    // Custom ReLu activation function
    auto relu = [](const torch::Tensor& tensor) {
        return torch::max(tensor, torch::zeros_like(tensor));
    };

    // Activate the biased sum using custom ReLu
    auto activated_weighted_inputs = relu(biased_sum);

    // Save the activated values to the activation tensor
    activations_ = std::make_shared<torch::Tensor>(activated_weighted_inputs);

    // Compute and save the mean activation
    mean_activation_ = std::make_shared<torch::Tensor>(activations_->mean());
}

void CGNode::compute_gradients(SharedTensorPtr outputs) {
    // ReLu gradient function
    gradients_ = std::make_shared<torch::Tensor>(torch::zeros_like(*outputs)); // TODO make return instead
    for (int i = 0; i < outputs->size(0); i++) {
        for (int j = 0; j < outputs->size(1); j++) {
            float activation_value = (*activations_)[i][j].item<float>();
            float gradient = (activation_value > 0) ? 1.0f : 0.0f;
            (*gradients_)[i][j] = gradient;
        }
    }

    // Compute and save the mean gradient
    mean_gradient_ = std::make_shared<torch::Tensor>(gradients_->mean());
}

void CGNode::update_weight(float learning_rate) {
    *weight_ -= learning_rate * (*gradients_);
}

void CGNode::update_bias(float new_bias) {
    (*bias_)[0] = new_bias;
}

// Getters
SharedTensorPtr CGNode::get_current_activations() {
    return activations_;
}

SharedTensorPtr CGNode::get_current_mean_activation() {
    return mean_activation_;
}

SharedTensorPtr CGNode::get_current_gradients() {
    return gradients_;
}
SharedTensorPtr CGNode::get_current_mean_gradient() {
    return mean_gradient_;
}

float CGNode::get_current_weight() {
    return weight_->item().toFloat();
}

float CGNode::get_current_bias() {
    return bias_->item().toFloat();
}

} // namespace computationgraph