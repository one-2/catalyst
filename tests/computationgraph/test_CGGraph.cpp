// tests/computationgraph/test_CGGraph.cpp
//
// Author: Stephen Elliott
//
// Date: 2025-02-20
//
// Description: 
//
// Usage: 
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
        
    }


};


// Constructors
CGGraph();

// Graph operations
void add_neural_layer(int width);

// Graph execution
void forward(DataLoader& dataloader);
void backward(DataLoader& dataloader);