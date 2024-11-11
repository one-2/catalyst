// source/tensorops/test_TensorOps.h
//
// Author: Stephen Elliott
//
// Date: 2024-11-04
//
// Description: Unit tests for TensorOps class
//

#ifndef TEST_TENSOROPS_H
#define TEST_TENSOROPS_H


#include "tensorops/TensorOps.h"

#include <gtest/gtest.h>
#include <torch/torch.h>

#include <memory>


namespace tensor {

using TensorPtr = std::shared_ptr<torch::Tensor>;

class TensorOpsTestUsingCPUStrategy : public ::testing::Test {
protected:
    TensorOps* tensorOps;

    void SetUp() override {
        tensorOps = new TensorOps(false); // Using CPU execution for tests
    }

    void TearDown() override {
        delete tensorOps;
    }
};

TEST_F(TensorOpsTestUsingCPUStrategy, ZeroTensor) {
    TensorPtr expected = std::make_shared<torch::Tensor>(torch::zeros({3, 2}, torch::dtype(torch::kFloat64)));
    TensorPtr result = tensorOps->zero(3, 2);
    EXPECT_TRUE(result->equal(*expected));
}

TEST_F(TensorOpsTestUsingCPUStrategy, IdentityTensor) {
    TensorPtr expected = std::make_shared<torch::Tensor>(torch::eye(3, torch::dtype(torch::kFloat64)));
    TensorPtr result = tensorOps->identity(3);
    EXPECT_TRUE(result->equal(*expected));
}

TEST_F(TensorOpsTestUsingCPUStrategy, SumTensors) {
    TensorPtr a = std::make_shared<torch::Tensor>(torch::tensor({{1.0, 2.0}, {3.0, 4.0}}, torch::dtype(torch::kFloat64)));
    TensorPtr b = std::make_shared<torch::Tensor>(torch::tensor({{5.0, 6.0}, {7.0, 8.0}}, torch::dtype(torch::kFloat64)));
    TensorPtr expected = std::make_shared<torch::Tensor>(torch::tensor({{6.0, 8.0}, {10.0, 12.0}}, torch::dtype(torch::kFloat64)));
    TensorPtr result = tensorOps->sum(a, b);
    EXPECT_TRUE(result->equal(*expected));
}

TEST_F(TensorOpsTestUsingCPUStrategy, MultipleTensor) {
    TensorPtr a = std::make_shared<torch::Tensor>(torch::tensor({{1.0, 2.0}, {3.0, 4.0}}, torch::dtype(torch::kFloat64)));
    TensorPtr expected = std::make_shared<torch::Tensor>(torch::tensor({{2.0, 4.0}, {6.0, 8.0}}, torch::dtype(torch::kFloat64)));
    TensorPtr result = tensorOps->multiple(a, 2.0);
    EXPECT_TRUE(result->equal(*expected));
}

TEST_F(TensorOpsTestUsingCPUStrategy, ScalarProduct) {
    TensorPtr a = std::make_shared<torch::Tensor>(torch::tensor({1.0, 2.0, 3.0}, torch::dtype(torch::kFloat64)));
    TensorPtr b = std::make_shared<torch::Tensor>(torch::tensor({4.0, 5.0, 6.0}, torch::dtype(torch::kFloat64)));
    TensorPtr expected = std::make_shared<torch::Tensor>(torch::tensor(32.0, torch::dtype(torch::kFloat64)));
    TensorPtr result = tensorOps->scalar_product(a, b);
    EXPECT_TRUE(result->equal(*expected));
}

TEST_F(TensorOpsTestUsingCPUStrategy, TensorProduct) {
    TensorPtr a = std::make_shared<torch::Tensor>(torch::tensor({{1.0, 2.0}, {3.0, 4.0}}, torch::dtype(torch::kFloat64)));
    TensorPtr b = std::make_shared<torch::Tensor>(torch::tensor({{5.0, 6.0}, {7.0, 8.0}}, torch::dtype(torch::kFloat64)));
    TensorPtr expected = std::make_shared<torch::Tensor>(torch::tensor({{19.0, 22.0}, {43.0, 50.0}}, torch::dtype(torch::kFloat64)));
    TensorPtr result = tensorOps->tensor_product(a, b);
    EXPECT_TRUE(result->equal(*expected));
}

TEST_F(TensorOpsTestUsingCPUStrategy, ReLu) {
    TensorPtr a = std::make_shared<torch::Tensor>(torch::tensor({{-1.0, 2.0}, {-3.0, 4.0}}, torch::dtype(torch::kFloat64)));
    TensorPtr expected = std::make_shared<torch::Tensor>(torch::tensor({{0.0, 2.0}, {0.0, 4.0}}, torch::dtype(torch::kFloat64)));
    TensorPtr result = tensorOps->reLu(a);
    EXPECT_TRUE(result->equal(*expected));
}

TEST_F(TensorOpsTestUsingCPUStrategy, Softmax) {
    TensorPtr a = std::make_shared<torch::Tensor>(torch::tensor({1.0, 2.0, 3.0}, torch::dtype(torch::kFloat64)));
    TensorPtr expected = std::make_shared<torch::Tensor>(torch::softmax(*a, 0, torch::dtype(torch::kFloat64)));
    TensorPtr result = tensorOps->softmax(a);
    EXPECT_TRUE(result->allclose(*expected, 1e-4));
}

} // namespace tensor

#endif // TEST_TENSOROPS_H