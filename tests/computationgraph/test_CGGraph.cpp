// tests/computationgraph/test_CGGraph.cpp
//
// Author: Stephen Elliott
//
// Date: 2025-02-20
//
// Description: Test file for CGGraph class in computationgraph namespace.
//

#include <gtest/gtest.h>
#include <torch/torch.h>

#include "computationgraph/CGGraph/CGGraph.h"
#include "tensorops/tensorops.h"
#include "datahandlers/DataLoader/DataLoader.h"

using namespace computationgraph;
using namespace tensorops;
using namespace datahandlers;

class ComputationGraphTest : public ::testing::Test {
protected:
    void SetUp() override {
        cgg = CGGraph();
    };

    CGGraph cgg;
};


// Constructor
TEST_F(ComputationGraphTest, Constructor) {
    std::vector<int> dims = cgg.get_graph_dimensions();
    ASSERT_EQ(
        dims.size(), 0
    );
    ASSERT_EQ(
        cgg.get_last_loss(), nullptr
    ); 
};

// Graph operations
TEST_F(ComputationGraphTest, AddNeuralLayers) {
    // Add a layer
    cgg.add_neural_layer(10);
    std::vector<int> dims = cgg.get_graph_dimensions();
    ASSERT_EQ(
        dims.size(), 1
    );

    EXPECT_EQ(
        dims[0], 10
    );
    
    // Add another layer
    cgg.add_neural_layer(50); // debug: segfault here
    dims = cgg.get_graph_dimensions();

    ASSERT_EQ(
        dims.size(), 2
    );
    
    EXPECT_EQ(
        dims[0], 10
    );

    EXPECT_EQ(
        dims[1], 50
    );
};

// Graph execution
TEST_F(ComputationGraphTest, ForwardPass) {
    cgg.add_neural_layer(1);
    cgg.add_neural_layer(1);

    DataLoader::Observation observation;
    observation.input = torch::rand({1, 5});
    observation.target = torch::rand({1, 5});

    cgg.forward(observation);

    torch::Tensor last_loss = *(cgg.get_last_loss());
    ASSERT_TRUE(last_loss.defined());
    EXPECT_GT(last_loss.item<float>(), 0);
};

TEST_F(ComputationGraphTest, BackwardPass) {
    cgg.add_neural_layer(5);
    cgg.add_neural_layer(5);

    DataLoader::Observation observation;
    observation.input = torch::rand({1, 5});
    observation.target = torch::rand({1, 5});

    cgg.forward(observation);
    cgg.backward();

    // Check that there are gradients on every node
    std::vector<SharedCGNodePtr> topo_sorted_graph = cgg.topo_sort_();
    for (SharedCGNodePtr node : topo_sorted_graph) {
        torch::Tensor gradients = *(node->get_current_gradients());
        ASSERT_TRUE(gradients.defined());
    }
};

// Getters
TEST_F(ComputationGraphTest, GetGraphDimensions) {
    cgg.add_neural_layer(5);
    cgg.add_neural_layer(5);

    std::vector<int> dims = cgg.get_graph_dimensions();
    ASSERT_EQ(
        dims.size(), 2
    );
    EXPECT_EQ(
        dims[0], 5
    );
    EXPECT_EQ(
        dims[1], 5
    );
};

// Topological sort tests
TEST_F(ComputationGraphTest, TopoSortEmptyGraph) {
    std::vector<SharedCGNodePtr> sorted_nodes = cgg.topo_sort_();
    ASSERT_EQ(sorted_nodes.size(), 0);
}

TEST_F(ComputationGraphTest, TopoSortSingleLayer) {
    cgg.add_neural_layer(3);
    std::vector<SharedCGNodePtr> sorted_nodes = cgg.topo_sort_();
    ASSERT_EQ(sorted_nodes.size(), 3);
}

TEST_F(ComputationGraphTest, TopoSortMultipleLayers) {
    cgg.add_neural_layer(2);
    cgg.add_neural_layer(3);
    std::vector<SharedCGNodePtr> sorted_nodes = cgg.topo_sort_();
    ASSERT_EQ(sorted_nodes.size(), 5);
}

TEST_F(ComputationGraphTest, TopoSortOrder) {
    cgg.add_neural_layer(2);
    cgg.add_neural_layer(2);
    std::vector<SharedCGNodePtr> sorted_nodes = cgg.topo_sort_();
    ASSERT_EQ(sorted_nodes.size(), 4);

    // Check that the first two nodes are from the first layer
    std::vector<int> dims = cgg.get_graph_dimensions();
    int first_layer_size = dims[0];
    for (int i = 0; i < first_layer_size; i++) {
        ASSERT_TRUE(std::find(sorted_nodes.begin(), sorted_nodes.begin() + first_layer_size, sorted_nodes[i]) != sorted_nodes.end());
    }

    // Check that the last two nodes are from the second layer
    int second_layer_size = dims[1];
    for (int i = first_layer_size; i < first_layer_size + second_layer_size; i++) {
        ASSERT_TRUE(std::find(sorted_nodes.begin() + first_layer_size, sorted_nodes.end(), sorted_nodes[i]) != sorted_nodes.end());
    }
}
