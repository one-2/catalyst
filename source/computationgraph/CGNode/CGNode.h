// source/computationgraph/CGNode/CGNode.h
//
// Author: Stephen Elliott
//
// Date: 2024-11-11
//
// Description: Node element for computation graph
//
// Usage: 
//

#ifndef CGNODE_H
#define CGNODE_H

#include <torch/torch.h>
#include <functional>

using namespace tensorops;

namespace computationgraph
{

class CGNode {
public:
    // Constructors
    CGNode();

    // Computation
    void compute_activations(SharedTensorPtr inputs);
    void compute_gradients(SharedTensorPtr outputs);
    void update_weight(float learning_rate);
    void update_bias(float bias);

    // Getters
    SharedTensorPtr get_current_activations();
    SharedTensorPtr get_current_mean_activation();
    SharedTensorPtr get_current_gradients();
    SharedTensorPtr get_current_weight();
    SharedTensorPtr get_current_bias();

private:
    // Callbacks
    std::function<void(SharedTensorPtr)> input_function_; // TODO update to TensorOp when that's implemented
    std::function<void(SharedTensorPtr)> activation_function_; // TODO update to TensorOp when that's implemented
    std::function<void(SharedTensorPtr)> gradient_function_; // TODO update to TensorOps& when that's implemented

    // Data
    SharedTensorPtr activations_;
    SharedTensorPtr mean_activation_;
    SharedTensorPtr gradients_;
    SharedTensorPtr weight_;
    SharedTensorPtr bias_;
};

} // namespace computationgraph

#endif // CGNODE_H