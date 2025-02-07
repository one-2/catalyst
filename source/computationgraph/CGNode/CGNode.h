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

namespace computationgraph
{

class CGNode {
public:
    // Constructors
    CGNode(int batch_size);

    // Computation
    SharedTensorPtr compute_activation(SharedTensorPtr inputs);
    SharedTensorPtr compute_gradient(SharedTensorPtr inputs);
    void update_weight(float learning_rate);


private:
    // Callbacks
    TensorOps& input_function_;
    TensorOps& activation_function_;
    TensorOps& gradient_function_;

    // Data
    SharedTensorPtr activations_;
    float mean_activation_;
    SharedTensorPtr gradients_;
    SharedTensorPtr weight_;
};

} // namespace computationgraph

#endif // CGNODE_H