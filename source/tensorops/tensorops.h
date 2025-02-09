// testtensorops.h
//
// Stephen Elliott, 2024-10-06
//
// This file contains the declarations for tensor operations
//

#ifndef TESTTENSOROPS_H
#define TESTTENSOROPS_H

#include <torch/torch.h>
#include <ostream>

// Function declarations
namespace tensorops
{
    typedef std::shared_ptr<torch::Tensor> SharedTensorPtr;

    torch::Tensor matmul(torch::Tensor a, torch::Tensor b);
    torch::Tensor reLu(torch::Tensor a);
    torch::Tensor softmax(torch::Tensor a);
    torch::Tensor identity(int n);
    torch::Tensor sum(torch::Tensor a, torch::Tensor b);
    torch::Tensor multiple(torch::Tensor a, double scalar);
    torch::Tensor scalar_product(torch::Tensor a, torch::Tensor b);
    torch::Tensor tensor_product(torch::Tensor a, torch::Tensor b);

    // Overloaded operator<< for the tensor library
    std::ostream& operator<<(std::ostream& os, const torch::Tensor& tensor);
}

#endif // TESTTENSOROPS_H
