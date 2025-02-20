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

using namespace computationgraph;
using namespace tensorops;

class ComputationGraphTest : public ::testing::Test {
protected:
    void SetUp() override {
        cgg = CGGraph();
    }

    CGGraph cgg;
};


// Constructors
TEST_F(ComputationGraphTest, Constructor) {
    ASSERT_NE(
        cgg, nullptr
    )
}
// CGGraph();

// Graph operations
TEST_F(ComputationGraphTest, AddNeuralLayers) {
    cgg.add_neural_layer(10);
    std::vector<int> dims = cgg.get_graph_dimensions();
    ASSERT_EQ(
        dims.size(), 1
    )
    EXPECT_EQ(
        dims[0], 10
    )
    
    cgg.add_neural_layer(50);
    dims = cgg.get_graph_dimensions;
    ASSERT_EQ(
        dims.size(), 2
    )
    EXPECT_EQ(
        dims[0], 10
    )
    EXPECT_EQ(
        dims[1], 50
    )
}
// void add_neural_layer(int width);

// Graph execution
TEST_F(ComputationGraphTest, ForwardPass) {
    cgg.add_neural_layer(5);
    cgg.add_neural_layer(5);

    cgg.forward(
        // Dataloader&
    )
    EXPECT_EQ(
        // Not sure what to put here
    )
}
// void forward(DataLoader& dataloader);


TEST_F(ComputationGraphTest, BackwardPass) {
    cgg.add_neural_layer(5);
    cgg.add_neural_layer(5);

    cgg.forward(
        // Dataloader&
    )

    cgg.backward(
        // Dataloader&
    )

    EXPECT_EQ(
        // Not sure what to put here
    )
}
// void backward(DataLoader& dataloader);
