// tests/unit/test_io.cpp
//
// Author: Stephen Elliott
//
// Date: 2024-10-25
//
// Description: Tests for the io class.
//

#include <gtest/gtest.h>
#include <torch/torch.h>
#include "io/io.h"

#include <fstream>


// Test cases
// TODO

//
// Load csv to a tensor
//
TEST(io, LoadTensorFromCsv) {
        std::string csv_content = "1.0,2.0,3.0\n4.0,5.0,6.0\n7.0,8.0,9.0\n"; //Dummy data
        std::string temp_csv_path = "/tmp/test_data.csv";
        std::ofstream temp_csv_file(temp_csv_path);
        temp_csv_file << csv_content;
        temp_csv_file.close();

        torch::Tensor tensor = io::load_tensor_from_csv(temp_csv_path);
        torch::Tensor expected_tensor = torch::tensor({{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}}, torch::kFloat64);

        ASSERT_TRUE(torch::allclose(tensor, expected_tensor));
}

//
// Load model checkpoint
//
// TEST(io, LoadModelCheckpoint) {
    // EXPECT_EQ (
    //     0, 1
    // );
// }

// //
// // Write model checkpoint
// //
// TEST(io, WriteModelCheckpoint) {
    // EXPECT_EQ (
    //     0, 1
    // );
// }
