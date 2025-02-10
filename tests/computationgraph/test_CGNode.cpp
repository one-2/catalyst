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
#include <torch/torch.h>

#include "computationgraph/CGNode/CGNode.h"
#include "tensorops/tensorops.h"

using namespace computationgraph;
using namespace tensorops;

class ComputationGraphTest : public ::testing::Test {
protected:
    void SetUp() override {
        cgn = std::make_shared<CGNode>();
    };

    std::shared_ptr<CGNode> cgn;
};

TEST_F(ComputationGraphTest, ConstructorAndGetters) {
    // May fail sometimes due to random inits and NEAR.
    // Test object creation
    ASSERT_NE(
        cgn, nullptr
    );

    ASSERT_NE(
        sizeof(*cgn), 0
    );

    // Test intialisations are reasonable (w/in 0.5 absolute of 0).
    EXPECT_NEAR( // Expect this to fail sometimes due to NE and random init of weight/bias.
        cgn->get_current_weight()->item<double>(), 0, 0.5
    );

    EXPECT_NEAR( // Expect this to fail sometimes due to NE and random init of weight/bias.
        cgn->get_current_bias()->item<double>(), 0, 0.5
    );

    // Test parameters are randomly initialised
    auto cgn2 = CGNode();

    EXPECT_NE(
        cgn->get_current_weight(), cgn2.get_current_weight()
    );

    EXPECT_NE(
        cgn->get_current_bias(), cgn2.get_current_bias()
    );

    // Test get_current_activations
    SharedTensorPtr activations = cgn->get_current_activations();
    EXPECT_NE(activations, nullptr);
    EXPECT_EQ(activations->numel(), 0); // Should be initialised with no elements.

    // Test get_current_mean_activation
    SharedTensorPtr mean_activation = cgn->get_current_mean_activation();
    EXPECT_NE(mean_activation, nullptr);
    EXPECT_EQ(mean_activation->numel(), 0); // Should be initialised with no elements.

    // Test get_current_gradients
    SharedTensorPtr gradients = cgn->get_current_gradients();
    EXPECT_NE(gradients, nullptr);
    EXPECT_EQ(gradients->numel(), 0); // Should be initialised with no elements.

    // Test get_current_mean_gradient
    SharedTensorPtr mean_gradient_ = cgn->get_current_mean_gradient();
    EXPECT_NE(mean_gradient_, nullptr);
    EXPECT_EQ(mean_gradient_->numel(), 0); // Should be initialised with no elements.

    // Test get_current_weight
    SharedTensorPtr weight = cgn->get_current_weight();
    EXPECT_NE(weight, nullptr);
    EXPECT_EQ(weight->numel(), 1); // Should be initialised with 1 element.

    // Test get_current_bias
    SharedTensorPtr bias = cgn->get_current_bias();
    EXPECT_NE(bias, nullptr);
    EXPECT_EQ(bias->numel(), 1); // Should be initialised with 1 element.
}

TEST_F(ComputationGraphTest, ComputeActivations) {
    // Data
    SharedTensorPtr inputs = std::make_shared<torch::Tensor>(
        torch::tensor({{1, 1}, {2, 1}, {2, 2}}, torch::kFloat32)
    );

    // Get node state at initialisation
    SharedTensorPtr current_weight = cgn->get_current_weight();
    SharedTensorPtr current_bias = cgn->get_current_bias();

    // Test activations
    // Execute computation
    cgn->compute_activations(inputs); // DEBUG bug here

    // Get computed values
    SharedTensorPtr computed_activations = cgn->get_current_activations();
    SharedTensorPtr computed_mean_activation = cgn->get_current_mean_activation();   
    
    // Check activations correct
    SharedTensorPtr expected_activations = std::make_shared<torch::Tensor>(torch::zeros({inputs->size(0), current_weight->size(0)}));
    for (int i = 0; i < inputs->size(0); i++) { // For each observation
            float activation = 0.0f;
            
            for (int k = 0; k < inputs->size(1); k++) { // For each input variable
                // Sum the inputs
            }

            // Weight the inputs

            // Activate the weighted values with ReLu

            // Save the activated value to a Tensor of dimension inputs->size(0) * 1.



            // TODO current bug was here, rewrite



    }

    ASSERT_TRUE(
        torch::equal(*computed_activations, *expected_activations)
    );

    // Check mean of activations correct
    ASSERT_TRUE(
        torch::equal(computed_activations->mean(), *computed_mean_activation)
    );
}

TEST_F(ComputationGraphTest, ComputeGradients) {
    // Data
    SharedTensorPtr inputs = std::make_shared<torch::Tensor>(torch::tensor({{1, 1}, {2, 1}, {2, 2}}));
    SharedTensorPtr labels = std::make_shared<torch::Tensor>(torch::tensor({{15}, {25}, {30}}));

    // Execute computation
    cgn->compute_activations(inputs);
    cgn->compute_gradients(labels);

    // Get computed values
    SharedTensorPtr computed_activations = cgn->get_current_activations();
    SharedTensorPtr computed_gradients = cgn->get_current_gradients();

    // Check gradients correct
    SharedTensorPtr expected_gradients = std::make_shared<torch::Tensor>(
        torch::zeros_like(*labels)
    );

    for (int i = 0; i < inputs->size(0); i++) {
        for (int j = 0; j < inputs->size(1); j++) {
            // Get values
            float input_value = (*inputs)[i][j].item<float>();
            float weight_value = (*cgn->get_current_weight())[j].item<float>();
            float activation_value = (*computed_activations)[i][j].item<float>();

            // Apply ReLu derivative
            float gradient = (activation_value > 0) ? input_value * weight_value : 0.0f;
            (*expected_gradients)[i][j] = gradient;
        }
    }

    ASSERT_TRUE(
        torch::equal(*computed_gradients, *expected_gradients)
    );
}

TEST_F(ComputationGraphTest, UpdateWeightsAndBiases) {
    // Data
    SharedTensorPtr inputs = std::make_shared<torch::Tensor>(torch::tensor({{1, 1}, {2, 1}, {2, 2}}));
    SharedTensorPtr labels = std::make_shared<torch::Tensor>(torch::tensor({{15}, {25}, {30}}));

    // Execute computation
    cgn->compute_activations(inputs);
    cgn->compute_gradients(labels);

    // Get initial weights and biases
    SharedTensorPtr current_weight = cgn->get_current_weight();
    SharedTensorPtr current_bias = cgn->get_current_bias();
    SharedTensorPtr computed_gradients = cgn->get_current_gradients();

    // Execute weight and bias update
    cgn->update_weight(0.01);
    cgn->update_bias(1);

    // Get new weights and biases
    SharedTensorPtr new_weight = cgn->get_current_weight();
    SharedTensorPtr new_bias = cgn->get_current_bias();
    
    // Check updated values correct
    ASSERT_NE(
        current_weight, new_weight
    );

    ASSERT_NE(
        current_bias, new_bias
    );

    // Check updates correct
    // Data
    SharedTensorPtr expected_new_weight = std::make_shared<torch::Tensor>(
        torch::zeros_like(*current_weight)
    );
    SharedTensorPtr expected_new_bias = std::make_shared<torch::Tensor>(
        torch::zeros_like(*current_bias)
    );
    
    // Expected values
    (*expected_new_weight) = (*current_weight) - 0.01 * (*computed_gradients); // TODO replace with variable learning rate value
    (*expected_new_bias) = (*current_bias) - 1 * (*computed_gradients);

    // Tests
    ASSERT_TRUE(
        torch::equal(*new_weight, *expected_new_weight)
    );

    ASSERT_TRUE(
        torch::equal(*new_bias, *expected_new_bias)
    );
}
