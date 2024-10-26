// tests/unit/test_dataloader.cpp
//
// Author: Stephen Elliott
//
// Date: 2024-10-25
//
// Description: Unit tests for DataLoader class.
//

#include <gtest/gtest.h>
#include "Dataset/Dataset.h"
#include "DataLoader/DataLoader.h"


// NOTE: v Thank you to this test! Caught a double-indexing bug
//          Read through modified code at regular intervals. 
TEST(DataLoader, GetNextObservation) {
    // Create a simple dataset
    torch::Tensor inputs = torch::tensor({1, 2, 3, 4});
    auto targets = torch::tensor({10, 20, 30, 40}); //auto for readability
    auto dataset = std::make_shared<Dataset>(inputs, targets, 0, 4);

    // Create DataLoader instance
    DataLoader dataLoader(dataset);

    // Test getting observations
    auto obs1 = dataLoader.get_next_observation();
    std::cout << obs1.input << std::endl;
    std::cout << obs1.target << std::endl;

    EXPECT_EQ(1.0, obs1.input.item<double>()); // Output:    Correct
    EXPECT_EQ(10, obs1.target.item<double>());

    auto obs2 = dataLoader.get_next_observation();
    EXPECT_EQ(2.0,  obs2.input.item<double>());
    EXPECT_EQ(20.0, obs2.target.item<double>());

    auto obs3 = dataLoader.get_next_observation();
    EXPECT_EQ(3.0,  obs3.input.item<double>());     // DEBUG NOTE: I need to look at the input stream to the vector - NO, go in order of proximate causes * areas recently modified.
    EXPECT_EQ(30.0, obs3.target.item<double>());

    auto obs4 = dataLoader.get_next_observation();
    EXPECT_EQ(obs4.input.item<double>(), 4);
    EXPECT_EQ(obs4.target.item<double>(), 40);

    // Test out of range
    EXPECT_THROW(dataLoader.get_next_observation(), std::out_of_range);
}

// NOTE: Thought I would have to modify the code for this, but my use of the class's implementation made the objects
//       transfer neatly. That is an advantage of using established implementations for high-overhead components.
//
TEST(DataLoader, GetNextObservationMultiDimensional) {
    // Create a multi-dimensional dataset
    torch::Tensor inputs = torch::tensor({{1, 2}, {3, 4}, {5, 6}, {7, 8}});
    auto targets = torch::tensor({{10, 20}, {30, 40}, {50, 60}, {70, 80}});
    auto dataset = std::make_shared<Dataset>(inputs, targets, 0, 4);

    // Create DataLoader instance
    DataLoader dataLoader(dataset);

    // Test getting observations
    auto obs1 = dataLoader.get_next_observation();
    std::cout << obs1.input << std::endl;
    std::cout << obs1.target << std::endl;

    EXPECT_EQ(1.0, obs1.input[0].item<double>());
    EXPECT_EQ(2.0, obs1.input[1].item<double>());
    EXPECT_EQ(10.0, obs1.target[0].item<double>());
    EXPECT_EQ(20.0, obs1.target[1].item<double>());

    auto obs2 = dataLoader.get_next_observation();
    EXPECT_EQ(3.0, obs2.input[0].item<double>());
    EXPECT_EQ(4.0, obs2.input[1].item<double>());
    EXPECT_EQ(30.0, obs2.target[0].item<double>());
    EXPECT_EQ(40.0, obs2.target[1].item<double>());

    auto obs3 = dataLoader.get_next_observation();
    EXPECT_EQ(5.0, obs3.input[0].item<double>());
    EXPECT_EQ(6.0, obs3.input[1].item<double>());
    EXPECT_EQ(50.0, obs3.target[0].item<double>());
    EXPECT_EQ(60.0, obs3.target[1].item<double>());

    auto obs4 = dataLoader.get_next_observation();
    EXPECT_EQ(7.0, obs4.input[0].item<double>());
    EXPECT_EQ(8.0, obs4.input[1].item<double>());
    EXPECT_EQ(70.0, obs4.target[0].item<double>());
    EXPECT_EQ(80.0, obs4.target[1].item<double>());

    // Test out of range
    EXPECT_THROW(dataLoader.get_next_observation(), std::out_of_range);
}
