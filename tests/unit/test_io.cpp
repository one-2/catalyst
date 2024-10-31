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

// Test cases

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
// Write log to a file and non-existent directory
//
TEST(io, WriteLog) {
    std::string log_content = "This is a test log entry.";
    std::string temp_directory = "/tmp/test_logs";

    // Set up
    std::filesystem::remove_all(temp_directory); //Clean the directory
    
    // Write the log and check it exists
    std::string path_written_existing = io::write_log(log_content, temp_directory); // includes directory builder
    ASSERT_TRUE(std::filesystem::exists(path_written_existing)); //File exists

    // Check it contains the expected content
    std::ifstream log_file_existing(path_written_existing);
    std::string file_content_existing((std::istreambuf_iterator<char>(log_file_existing)), std::istreambuf_iterator<char>());
    log_file_existing.close();
    ASSERT_EQ(file_content_existing, log_content + "\n");

    // Clean up
    std::filesystem::remove_all(temp_directory);

    // Test for non-existent directory
    std::string non_existent_directory = "/tmp/non_existent_directory";
    std::filesystem::remove_all(non_existent_directory); // clean the directory

    std::string path_written_non_existent = io::write_log(log_content, non_existent_directory); // includes directory builder
    ASSERT_TRUE(std::filesystem::exists(path_written_non_existent)); //File exists

    std::ifstream log_file_non_existent(path_written_non_existent); //Contains expected content
    std::string file_content_non_existent((std::istreambuf_iterator<char>(log_file_non_existent)), std::istreambuf_iterator<char>());
    log_file_non_existent.close();
    ASSERT_EQ(file_content_non_existent, log_content + "\n");

    // Clean up
    std::filesystem::remove_all(non_existent_directory);
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
