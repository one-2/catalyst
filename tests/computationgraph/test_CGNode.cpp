// tests/computationgraph/test_CGNode.cpp
//
// Author: Stephen Elliott
//
// Date: 2025-02-08
//
// Description: Test file for CGNode class in computationgraph namespace.
//
// Usage: 
//

#include <gtest/gtest.h>
#include "computationgraph/CGNode/CGNode.h"
#include <torch/torch.h>

using namespace computationgraph;

class TestGraph : public ::testing::Test {
protected:
    void SetUp() override {
        auto cg = CGNode();
        }

    std::shared_ptr<CGNode> cg;
}

TEST_F(ComputationGraph, Constructor) {
    EXPECT_NEQ(
        cg, NULL
    );

    EXPECT_NEQ(
        sizeof(*cg), 0
    );

    EXPECT_NEAR( // Expect this to fail sometimes
        cg.get_current_weight, 0, 0.5
    );

    EXPECT_NEAR( // Expect this to fail sometimes also
        cg.get_current_bias, 0, 0.5
    );

    auto cg2 = CGNode(); // Test that the initialisation is neq
    EXPECT_NEQ(
        cg.get_current_weight, cg2.get_current_weight
    );

    EXPECT_NEQ(
        cg.get_current_bias, cg2.get_current_bias
    )
}

TEST_F(ComputationGraph, ComputeAndUpdateActivationsGradients) {
    // Data
    SharedTensorPtr input = make_shared<torch::Tensor>({{1, 1}, {2, 1}, {2, 2}}); // {10s, 5s}
    SharedTensorPtr label = make_shared<torch::Tensor>({{15}, {25}, {30}});

    // Compute
    // Node state at initialisation
    SharedTensorPtr current_weight = cg.get_current_weight();
    SharedTensorPtr current_bias = cg.get_current_bias();

    // Computation
    SharedTensorPtr activations = cg.compute_activations(inputs);
    SharedTensorPtr gradients = cg.compute_gradients(labels);
    
    // Expected values
    SharedTensorPtr expected_activations; // TODO apply node operation
    SharedTensorPtr expected_gradients; // apply node operation
    
    EXPECT_EQ(
        *activations, *expected_activations
    );

    EXPECT_EQ(
        *gradients, *expected_gradients
    );
    
    // Update
    // Expected update
    SharedTensorPtr expected_weight = *current_weight - *

    // Execute
    cg.update_weight(0.01);
    cg.update_bias(1);


}