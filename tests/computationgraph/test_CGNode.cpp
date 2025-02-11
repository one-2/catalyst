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
        cgn->get_current_bias(), 0.0f, 0.5f
    );

    EXPECT_NEAR( // Expect this to fail sometimes due to NE and random init of weight/bias.
        cgn->get_current_bias(), 0.0f, 0.5f
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
    float weight = cgn->get_current_weight();
    EXPECT_NE(weight, 0); // Should be initialised to 1 small random element.

    // Test get_current_bias
    float bias = cgn->get_current_bias();
    EXPECT_NE(bias, 0); // Should be initialised to 1 small random element.
}

TEST_F(ComputationGraphTest, ComputeActivations) {
    // Data
    SharedTensorPtr inputs = std::make_shared<torch::Tensor>(
        torch::tensor({{1, 1}, {2, 1}, {2, 2}}, torch::kFloat32)
    );

    // Get node state at initialisation
    float current_weight = cgn->get_current_weight();
    float current_bias = cgn->get_current_bias();

    // Test activations
    // Execute computation
    cgn->compute_activations(inputs);

    // Get computed values
    SharedTensorPtr computed_activations = cgn->get_current_activations();
    SharedTensorPtr computed_mean_activation = cgn->get_current_mean_activation();   

    // Sanity check
    ASSERT_EQ(
        cgn->get_current_activations()->numel(), 3
    );
    
    // Check activations correct
    // Create an empty activation tensor of dimension inputs->size(0) * 1.
    SharedTensorPtr expected_activations = std::make_shared<torch::Tensor>(torch::zeros({inputs->size(0), 1}));

    for (int i = 0; i < inputs->size(0); i++) { // For each observation
        float input_sum = 0.0f; // note: without f in 0.0f, this is saved as a double

        for (int k = 0; k < inputs->size(1); k++) { // For each input variable
            // Sum the inputs
            input_sum += (*inputs)[i][k].item<float>();
        }

        // Weight the inputs
        float weighted_inputs = input_sum * current_weight + current_bias;
    
        // Activate the weighted values with ReLu
        float activated_weighted_inputs = std::max(weighted_inputs, 0.0f);

        // Save the activated value to the activation tensor.
        (*expected_activations)[i][0] = activated_weighted_inputs;
    }

    // debug: fetch every value from the computed_activations and expected_activations objects
    torch::Tensor t1 = (*computed_activations); // This is size 0
    torch::Tensor t2 = (*expected_activations); // This is size 3*1, as expected
    std::vector t1_size = t1.sizes().vec();
    std::vector t2_size = t2.sizes().vec();


    ASSERT_TRUE(
        torch::equal(*computed_activations, *expected_activations) // debug: FAILING
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
            float weight_value = cgn->get_current_weight();
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
    float current_weight = cgn->get_current_weight();
    float current_bias = cgn->get_current_bias();
    SharedTensorPtr computed_gradients = cgn->get_current_gradients();

    // Execute weight and bias update
    float learning_rate = 0.01;
    float bias_update = 1;

    cgn->update_weight(learning_rate);
    cgn->update_bias(bias_update);

    // Get new weights and biases
    float computed_new_weight = cgn->get_current_weight();
    float computed_new_bias = cgn->get_current_bias();
    
    // Check updated values correct
    ASSERT_NE(
        current_weight, computed_new_weight
    );

    ASSERT_NE(
        current_bias, computed_new_bias
    );

    // Check updates correct
    // Data
    SharedTensorPtr expected_new_weight = std::make_shared<torch::Tensor>(
        torch::zeros({})
    );
    SharedTensorPtr expected_new_bias = std::make_shared<torch::Tensor>(
        torch::zeros({})
    );
    
    // Expected values
    (*expected_new_weight) = current_weight - 0.01 * (*computed_gradients); // TODO replace with variable learning rate value
    (*expected_new_bias) = current_bias - 1 * (*computed_gradients);

    // Tests
    ASSERT_TRUE(
        torch::equal(torch::tensor(computed_new_weight), (*expected_new_weight)[0])
    );

    ASSERT_TRUE(
        torch::equal(torch::tensor(computed_new_bias), (*expected_new_bias)[0])
    );
}
