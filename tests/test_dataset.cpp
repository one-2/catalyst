// source/Dataset/test_Dataset.cpp
//
// Author: Stephen Elliott
//
// Date: 2024-10-25
//
// Description: Unit tests for Dataset class.
//

#include <gtest/gtest.h>
#include <torch/torch.h>
#include <fstream>
#include "datahandlers/Dataset/Dataset.h"

using namespace datahandlers;

//
// Constructor from csv
//
TEST(Dataset, ConstructorWithCSVPath) {
    // Write some dummy data to a csv
    torch::Tensor dummy_data = torch::rand({100, 11});
    std::ofstream temp_csv("./constructor_test_temp.csv");
    temp_csv << "col1,col2,col3,col4,col5,col6,col7,col8,col9,col10,target\n"; //Write header
    for (int i = 0; i < 100; ++i) { //Write digits 1-100
        for (int j = 0; j < 10; ++j) {
            temp_csv << std::to_string(dummy_data[i][j].item<float>()) << ","; //Write a row of rand values
        }
        temp_csv << std::to_string(dummy_data[i][10].item<float>()) << "\n"; //Write the target and newline
    }
    temp_csv.close();

    // Test
    Dataset dataset("./constructor_test_temp.csv", 10); //"Direct initialisation" syntax. Reduces init overhead

    EXPECT_EQ(dataset.get_length(), 100);
    EXPECT_EQ(dataset.input.size(1), 10);
    EXPECT_EQ(dataset.target.size(0), 100);

    // Cleanup
    std::remove("./constructor_test_temp.csv");
}

// 
// Constructor from tensors
//
TEST(Dataset, ConstructorWithTensors) {
    torch::Tensor input = torch::rand({100, 10});
    torch::Tensor target = torch::rand({100, 1});
    Dataset dataset(input, target, 0, 100);

    EXPECT_EQ(dataset.get_length(), 100);
    EXPECT_EQ(dataset.input.size(1), 10);
    EXPECT_EQ(dataset.target.size(0), 100);
}

//
// Train/validate/test split the data
//
TEST(Dataset, Split) {
    torch::Tensor input = torch::rand({100, 10});
    torch::Tensor target = torch::rand({100, 1});
    Dataset dataset(input, target, 0, 100);

    auto splits = dataset.split(0.6, 0.2, 0.2);
    std::cout << splits[0]->get_length() << std::endl;
    EXPECT_EQ(splits[0]->get_length(), 60);
    EXPECT_EQ(splits[1]->get_length(), 20);
    EXPECT_EQ(splits[2]->get_length(), 20);

    // Test split method with rounding
    auto rounded_splits = dataset.split(0.333, 0.333, 0.334);
    EXPECT_EQ(rounded_splits[0]->get_length(), 33);
    EXPECT_EQ(rounded_splits[1]->get_length(), 34);
    EXPECT_EQ(rounded_splits[2]->get_length(), 33);
}
