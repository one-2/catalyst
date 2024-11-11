// tensorops.cpp
//
// Stephen Elliott, October 8 2024
//
// This file contains the tensorops namespace.
// tensorops is an interface to operations on pytorchcpp
// data structures.
//
// The tallest tree sees the farthest.
//

#include <torch/torch.h>
#include "./CPUStrategy.h"

namespace tensor
{

TensorPtr CPUStrategy::zero(int rows, int cols)
{
    return std::make_shared<torch::Tensor>(torch::zeros({rows, cols}));
}


TensorPtr CPUStrategy::matmul(TensorPtr a, TensorPtr b)
{
    return std::make_shared<torch::Tensor>(torch::matmul(*a, *b));
}


TensorPtr CPUStrategy::reLu(TensorPtr a)
{
    return std::make_shared<torch::Tensor>(torch::relu(*a));
}


TensorPtr CPUStrategy::softmax(TensorPtr a)
{
    return std::make_shared<torch::Tensor>(torch::softmax(*a, 0));
}


TensorPtr CPUStrategy::identity(int n)
{
    return std::make_shared<torch::Tensor>(torch::eye(n));
}


TensorPtr CPUStrategy::sum(TensorPtr a, TensorPtr b)
{
    return std::make_shared<torch::Tensor>(*a + *b);
}


TensorPtr CPUStrategy::multiple(TensorPtr a, double scalar)
{
    return std::make_shared<torch::Tensor>(*a * scalar);
}


TensorPtr CPUStrategy::scalar_product(TensorPtr a, TensorPtr b)
{
    return std::make_shared<torch::Tensor>(torch::dot(*a, *b));
}


TensorPtr CPUStrategy::tensor_product(TensorPtr a, TensorPtr b)
{
    return torch::matmul(a, b);
}


} // namespace tensor

