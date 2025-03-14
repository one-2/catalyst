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
#include "../../tensorops/tensorops.h"

using namespace tensorops;

namespace computationgraph
{

typedef std::shared<CGNode> SharedCGNodePtr;

class CGNode {
public:
    // Constructors
    CGNode();

    // Computation
    void compute_activations(SharedTensorPtr inputs);
    void compute_gradients(SharedTensorPtr outputs);
    void update_weight(float learning_rate);
    void update_bias(float new_bias); // note: new bias to be computed across whole layer by CGGraph

    // Getters
    SharedTensorPtr get_current_activations();
    float get_current_mean_activation();
    SharedTensorPtr get_current_gradients();
    float get_current_mean_gradient();
    float get_current_weight();
    float get_current_bias();

private:
    // Data
    SharedTensorPtr activations_;
    SharedTensorPtr mean_activation_;
    SharedTensorPtr gradients_;
    SharedTensorPtr mean_gradient_;
    SharedTensorPtr weight_;
    SharedTensorPtr bias_;
};

} // namespace computationgraph

#endif // CGNODE_H