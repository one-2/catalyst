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
#include <filesystem>


//
// Load csv to a tensor
//
TEST(io, LoadTensorFromCsv) {
    std::string csv_content = "col1,col2,col3,col4,col5,col6,col7,col8,col9\n1.0,2.0,3.0\n4.0,5.0,6.0\n7.0,8.0,9.0\n"; //Dummy data
    std::string temp_csv_path = "/tmp/test_data.csv";
    std::ofstream temp_csv_file(temp_csv_path);
    temp_csv_file << csv_content;
    temp_csv_file.close();

    torch::Tensor tensor = io::load_tensor_from_csv(temp_csv_path);
    torch::Tensor expected_tensor = torch::tensor({{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}}, torch::kFloat64);

    ASSERT_TRUE(torch::allclose(tensor, expected_tensor));

    // Clean up
    std::filesystem::remove(temp_csv_path);

}

//
// Build directory path
//
TEST(io, BuildDirectoryPath) {
    std::string temp_directory = "/tmp/test_build_directory";

    // Ensure the directory does not exist before the test
    std::filesystem::remove_all(temp_directory);

    // Call the function to build the directory path
    io::build_directory(temp_directory);

    // Check if the directory is created
    ASSERT_TRUE(std::filesystem::exists(temp_directory));

    // Clean up
    std::filesystem::remove_all(temp_directory);

}


TEST(TestIO, WriteLogTest) {
    std::string test_file_path = "/tmp/test_log.txt";
    std::string log_content = "This is a test log.";
    std::string returned_path = io::write_log(log_content, test_file_path);

    // Check if the file is created
    std::ifstream infile(test_file_path);
    ASSERT_TRUE(infile.good());

    // Check if the content is written correctly
    std::string file_content((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    infile.close();
    EXPECT_EQ(log_content, file_content);

    // Check if the returned path is correct
    EXPECT_EQ(returned_path, test_file_path);

}
