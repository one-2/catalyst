// tests/tensorops/test_TensorOpsSelector.cpp
//
// Author: Stephen Elliott
//
// Date: 2024-11-11
//
// Description: 
//
// Usage: 
//


#include <gtest/gtest.h>

#include "tensorops/TensorOpsSelector.h"
#include "tensorops/TensorStrategy/CPUStrategy/CPUStrategy.h"
#include "tensorops/TensorStrategy/GPUStrategy/GPUStrategy.h"


using namespace tensor;


class TensorOpsSelectorTest : public ::testing::Test {
protected:
    void SetUp() override {
        cpu_selector = std::make_unique<TensorOpsSelector>(false);
        gpu_selector = std::make_unique<TensorOpsSelector>(true);
    }

    std::unique_ptr<TensorOpsSelector> cpu_selector;
    std::unique_ptr<TensorOpsSelector> gpu_selector;
};


TEST_F(TensorOpsSelectorTest, ZeroTensor) {
    auto cpu_tensor = cpu_selector->zero(3, 3);
    auto gpu_tensor = gpu_selector->zero(3, 3);
    EXPECT_EQ(cpu_tensor, gpu_tensor);
}


TEST_F(TensorOpsSelectorTest, ComplexTensor) {
    std::vector<std::vector<float>> complex_data = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
    auto cpu_tensor = cpu_selector->from_vector(complex_data);
    auto gpu_tensor = gpu_selector->from_vector(complex_data);
    EXPECT_EQ(cpu_tensor, gpu_tensor);
}


TEST_F(TensorOpsSelectorTest, SumTensors) {
    std::vector<std::vector<float>> data1 = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
    std::vector<std::vector<float>> data2 = {{9.0, 8.0, 7.0}, {6.0, 5.0, 4.0}, {3.0, 2.0, 1.0}};
    auto tensor1 = cpu_selector->from_vector(data1);
    auto tensor2 = cpu_selector->from_vector(data2);
    auto cpu_sum = cpu_selector->sum(tensor1, tensor2);
    auto gpu_sum = gpu_selector->sum(tensor1, tensor2);
    EXPECT_EQ(cpu_sum, gpu_sum);
}


TEST_F(TensorOpsSelectorTest, MultiplyTensor) {
    std::vector<std::vector<float>> data = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
    auto tensor = cpu_selector->from_vector(data);
    auto scalar = cpu_selector->from_vector({{2.0}}); // Assuming scalar is represented as a tensor
    auto cpu_result = cpu_selector->multiple(tensor, scalar);
    auto gpu_result = gpu_selector->multiple(tensor, scalar);
    EXPECT_EQ(cpu_result, gpu_result);
}


TEST_F(TensorOpsSelectorTest, ScalarProduct) {
    std::vector<std::vector<float>> data1 = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
    std::vector<std::vector<float>> data2 = {{9.0, 8.0, 7.0}, {6.0, 5.0, 4.0}, {3.0, 2.0, 1.0}};
    auto tensor1 = cpu_selector->from_vector(data1);
    auto tensor2 = cpu_selector->from_vector(data2);
    auto cpu_result = cpu_selector->scalar_product(tensor1, tensor2);
    auto gpu_result = gpu_selector->scalar_product(tensor1, tensor2);
    EXPECT_EQ(cpu_result, gpu_result);
}


TEST_F(TensorOpsSelectorTest, TensorProduct) {
    std::vector<std::vector<float>> data1 = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
    std::vector<std::vector<float>> data2 = {{9.0, 8.0, 7.0}, {6.0, 5.0, 4.0}, {3.0, 2.0, 1.0}};
    auto tensor1 = cpu_selector->from_vector(data1);
    auto tensor2 = cpu_selector->from_vector(data2);
    auto cpu_result = cpu_selector->tensor_product(tensor1, tensor2);
    auto gpu_result = gpu_selector->tensor_product(tensor1, tensor2);
    EXPECT_EQ(cpu_result, gpu_result);
}


TEST_F(TensorOpsSelectorTest, ReLU) {
    std::vector<std::vector<float>> data = {{-1.0, -2.0, -3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
    auto tensor = cpu_selector->from_vector(data);
    auto cpu_result = cpu_selector->reLu(tensor);
    auto gpu_result = gpu_selector->reLu(tensor);
    EXPECT_EQ(cpu_result, gpu_result);
}


TEST_F(TensorOpsSelectorTest, Softmax) {
    std::vector<std::vector<float>> data = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
    auto tensor = cpu_selector->from_vector(data);
    auto cpu_result = cpu_selector->softmax(tensor);
    auto gpu_result = gpu_selector->softmax(tensor);
    EXPECT_EQ(cpu_result, gpu_result);
}
