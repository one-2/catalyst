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

// Test cases
// TODO
// class io {
// public:
//     io(std::string out_path);
//     torch::tensor load_from_csv(std::string path);
//     Model load_checkpoint(std::string path);
//     &std::string write_checkpoint(std::string label);
    
//     friend std::ostream& operator<<(std::ostream& os, io& mh);
// }

//
// Constructor
//
TEST(io, Constructor) {
    EXPECT_EQ (
        0, 1
    );
}

//
// Load csv data
//
TEST(io, LoadCsv) {
    EXPECT_EQ (
        0, 1
    );
}

//
// Load model checkpoint
//
TEST(io, LoadModelCheckpoint) {
    EXPECT_EQ (
        0, 1
    );
}

//
// Write model checkpoint
//
TEST(io, WriteModelCheckpoint) {
    EXPECT_EQ (
        0, 1
    );
}
