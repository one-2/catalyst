// tests/unit/test_dataset.cpp
//
// Author: Stephen Elliott
//
// Date: 2024-10-13
//
// Description: Tests for Dataset class.
//

#include <vector>
#include <variant>
#include <gtest/gtest.h>
#include "Dataset/Dataset.h"

// Test cases

//
// Split the dataset
//
TEST(Dataset, SplitDataset)
{
    //
    // Even split - percentages partition the dataset at integer indexes
    //
    Dataset dataset1;    // Add mock data to the dataset using IO class and local test file

    auto [train, test, validate] = dataset1.split(0.7, 0.2, 0.1);

    EXPECT_EQ
    (
        train.length(), 7
    );
    EXPECT_EQ
    (
        test.length(), 2
    );
    EXPECT_EQ
    (
        validate.length(), 1
    );

    //
    // Odd split - percentages partition the dataset at fractional indexes
    //
    Dataset dataset2;    // Add mock data to the dataset using IO class and local test file

    auto [train, test, validate] = dataset2.split(0.4, 0.3, 0.3); // Split over-allocates the training set

    EXPECT_EQ
    (
        train.length(), 2
    );
    EXPECT_EQ
    (
        test.length(), 1
    );
    EXPECT_EQ
    (
        validate.length(), 1
    );
}

//
// Retrieve a dataloader
//
TEST(Dataset, GetDataLoader)
{
    Dataset dataset;
    // Add mock data to the dataset
    // TODO

    DataLoader dataloader = dataset.get_dataloader();

    // verify dataloader output stream
    // TODO
}

//
// Operator<< overload
//
TEST(Dataset, OutputStreamOperator)
{
    Dataset dataset;
    // Add mock data to the dataset
    // TODO

    std::ostringstream os;
    os << dataset;

    std::string expected_output = "..."; // TODO
    EXPECT_EQ(os.str(), expected_output);
}