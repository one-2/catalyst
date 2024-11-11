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

    // Setters
    void set_activation_function(std::function<TensorPtr(TensorPtr)> func);
    void set_gradient_function(std::function<TensorPtr(TensorPtr)> func);
    void update_weight(float learning_rate);

    // Computations
    TensorPtr compute_activation(TensorPtr input);
    TensorPtr compute_gradient(TensorPtr input);


private:
    // Callbacks
    std::function<void()> input_function_; // TODO parameterise properly
    std::function<TensorPtr(TensorPtr)> activation_function_;
    std::function<TensorPtr(TensorPtr)> gradient_function_; // TODO which autodiff package to use?

    // Data
    TensorPtr input_;
    TensorPtr activation_;
    TensorPtr gradient_;
    TensorPtr weight_;

    // Hyperparameters
    int batch_size_;

};

} // namespace computationgraph

#endif // CGNODE_H