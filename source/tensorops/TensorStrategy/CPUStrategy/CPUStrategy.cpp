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

namespace tensorops
{
    torch::Tensor matmul(torch::Tensor a, torch::Tensor b)
    {
        return torch::matmul(a, b);
    }

    torch::Tensor reLu(torch::Tensor a)
    {
        return torch::relu(a);
    }

    torch::Tensor softmax(torch::Tensor a)
    {
        return torch::softmax(a, 0);
    }

    torch::Tensor identity(int n)
    {
        return torch::eye(n);
    }

    torch::Tensor sum(torch::Tensor a, torch::Tensor b)
    {
        return a + b;
    }

    torch::Tensor multiple(torch::Tensor a, double scalar)
    {
        return a * scalar;
    }

    torch::Tensor scalar_product(torch::Tensor a, torch::Tensor b)
    {
        return torch::dot(a, b);
    }

    torch::Tensor tensor_product(torch::Tensor a, torch::Tensor b)
    {
        return torch::matmul(a, b);
    }

    std::ostream& operator<<(std::ostream& os, const torch::Tensor& tensor)
    {
        os << tensor.toString();
        return os;
    }
}
