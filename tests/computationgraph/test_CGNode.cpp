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

class ComputationGraphNodeTest : public ::testing::Test {
protected:
    void SetUp() override {
        cgn = std::make_shared<CGNode>();
        
        inputs = std::make_shared<torch::Tensor>(torch::tensor({{-1.1345, 15.29862}, {-25.32458, 10.23498}, {2.22, 2.56}}, torch::kFloat32));
        labels = std::make_shared<torch::Tensor>(torch::tensor({{-15.6198}, {25.04}, {30.222}}, torch::kFloat32));
    };

    std::shared_ptr<CGNode> cgn;

    SharedTensorPtr inputs;
    SharedTensorPtr labels;
};

TEST_F(ComputationGraphNodeTest, ConstructorAndGetters) {
    // May fail sometimes due to random inits and NEAR.
    // Test object creation
    ASSERT_NE(
        cgn, nullptr
    );

    ASSERT_NE(
        sizeof(*cgn), 0
    );

    // Test intialisations are reasonable (w/in 0.5 absolute of 0).
    EXPECT_NE( // note: will sometimes fail due to random init.
        cgn->get_current_weight(), 0.0f
    );

    EXPECT_NE( // note: will sometimes fail due to random init.
        cgn->get_current_bias(), 0.0f
    );

    EXPECT_NEAR( // note: will sometimes fail due to random init.
        cgn->get_current_weight(), 0.0f, 2.0f
    );

    EXPECT_NEAR( // note: will sometimes fail due to random init.
        cgn->get_current_bias(), 0.0f, 2.0f
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
    float mean_activation = cgn->get_current_mean_activation();
    EXPECT_NEAR(
        mean_activation, 0.0f, 1e-5
    ); // Should be initialised to 0.

    // Test get_current_gradients
    SharedTensorPtr gradients = cgn->get_current_gradients();
    EXPECT_NE(gradients, nullptr);
    EXPECT_EQ(gradients->numel(), 0); // Should be initialised with no elements.

    // Test get_current_mean_gradient
    float mean_gradient = cgn->get_current_mean_gradient();
    EXPECT_NEAR(
        mean_gradient, 0.0f, 1e-5
    ); // Should be initialised to 0.

    // Test get_current_weight
    float weight = cgn->get_current_weight();
    EXPECT_NE(weight, 0); // Should be initialised to 1 small random element.

    // Test get_current_bias
    float bias = cgn->get_current_bias();
    EXPECT_NE(bias, 0); // Should be initialised to 1 small random element.
}

TEST_F(ComputationGraphNodeTest, ComputeActivations) {
    // Get node state at initialisation
    float current_weight = cgn->get_current_weight();
    float current_bias = cgn->get_current_bias();

    // Test activations
    // Execute computation
    cgn->compute_activations(inputs);

    // Get computed values
    SharedTensorPtr computed_activations = cgn->get_current_activations();
    float computed_mean_activation = cgn->get_current_mean_activation();   

    // Sanity check: computed activation vector contains the correct number of elements (expect 3*1)
    ASSERT_EQ(
        cgn->get_current_activations()->size(0), 3
    );
    ASSERT_EQ(
        cgn->get_current_activations()->size(1), 1
    );

    // Check activations correct
    // Create an empty activation tensor of dimension inputs->size(0) * 1.
    SharedTensorPtr expected_activations = std::make_shared<torch::Tensor>(torch::zeros({inputs->size(0), 1}));

    for (int i = 0; i < inputs->size(0); i++) { // For each observation
        // Sum the variables
        float input_sum = (*inputs)[i].sum().item<float>();

        // Weight the variables
        float weighted_inputs = input_sum * current_weight + current_bias;
        
        // ReLu the weighted variables
        float activated_weighted_inputs = std::max(weighted_inputs, 0.0f);

        // Save the activated variable to the activation tensor.
        (*expected_activations)[i][0] = activated_weighted_inputs;
    }

    // Sanity check
    // todo: pull to the tensor class as a utility
    auto tensor_to_vector = [](const SharedTensorPtr& tensor) {
        return std::vector<float>(
            tensor->data_ptr<float>(),
            tensor->data_ptr<float>() + tensor->numel()
        );
    };

    // Print the weight, bias, and input values
    // Vectorize and print the weight, bias, and input values
    std::vector<float> input_values_vector = tensor_to_vector(inputs);
    std::vector<float> weight_vector = {current_weight};
    std::vector<float> bias_vector = {current_bias};

    auto print_vector = [](const std::vector<float>& vec, const std::string& name) {
        std::cout << name << ": ";
        for (const auto& val : vec) {
            std::cout << std::fixed << std::setprecision(10) << val << " ";
        }
        std::cout << std::endl;
    };

    print_vector(input_values_vector, "Input Values");
    print_vector(weight_vector, "Weight");
    print_vector(bias_vector, "Bias");



    std::vector<float> computed_values_vector = tensor_to_vector(computed_activations);
    std::vector<float> expected_values_vector = tensor_to_vector(expected_activations);
    
    // todo: pull to the tensor class as a utility
    auto print_vectorised_tensors = [](std::vector<float> computed_values_vector, std::vector<float> expected_values_vectors) {
        std::cout << "Computed Activations: ";
        for (const auto& val : computed_values_vector) {
            std::cout << std::fixed << std::setprecision(10) << val << " ";
        }
        std::cout << std::endl;

        std::cout << "Expected Activations: ";
        for (const auto& val : expected_values_vectors) {
            std::cout << std::fixed << std::setprecision(10) << val << " ";
        }
        std::cout << std::endl;
    };

    print_vectorised_tensors(computed_values_vector, expected_values_vector);

    // Sanity check: activations are non-zero
    // note: ^ No, dummy! Test removed. Be careful. Don't add tests without thinking, like this.

    // Check activations are equal
    auto assert_tensors_near = [](const SharedTensorPtr& tensor1, const SharedTensorPtr& tensor2, float tolerance) {
        ASSERT_EQ(tensor1->sizes(), tensor2->sizes()) << "Tensors have different sizes";
        for (int i = 0; i < tensor1->numel(); ++i) {
            EXPECT_NEAR(tensor1->data_ptr<float>()[i], tensor2->data_ptr<float>()[i], tolerance);
        }
    };

    assert_tensors_near(computed_activations, expected_activations, 1e-5);

    // Check mean of activations correct
    EXPECT_EQ(
        computed_activations->mean().item<float>(), computed_mean_activation
    );
}

TEST_F(ComputationGraphNodeTest, ComputeGradients) {
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

    for (int i = 0; i < labels->size(0); i++) {
        for (int j = 0; j < labels->size(1); j++) {
            float activation_value = (*computed_activations)[i][0].item<float>();
            float gradient = (activation_value > 0) ? 1.0f : 0.0f;
            (*expected_gradients)[i][j] = gradient;
        }
    }

    ASSERT_TRUE(
        torch::equal(*computed_gradients, *expected_gradients)
    );
}

TEST_F(ComputationGraphNodeTest, UpdateWeightsAndBiases) {
    // Execute computation
    cgn->compute_activations(inputs);
    cgn->compute_gradients(labels);

    // Get initial weights and biases
    float initial_weight = cgn->get_current_weight();
    SharedTensorPtr computed_gradients = cgn->get_current_gradients();

    // Execute weight and bias update
    float learning_rate = 0.01;
    float bias_update = 1;

    cgn->update_weight(learning_rate);
    cgn->update_bias(bias_update);

    // Get new weights and biases
    float computed_updated_weight = cgn->get_current_weight();
    float expected_updated_bias = cgn->get_current_bias();

    // Expected values
    float expected_new_weight = initial_weight - learning_rate * computed_gradients->mean().item<float>(); 
    float expected_new_bias = bias_update;

    // Tests
    EXPECT_NEAR( // note: NEAR required for fp comparisons due to precision error
        computed_updated_weight, expected_new_weight, 1e-5
    );

    EXPECT_NEAR(
        expected_updated_bias, expected_new_bias, 1e-5
    );
}
