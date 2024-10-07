// run_tests.cpp
//
// Stephen Elliott, 2024-10-06
//
// This file...
//

#include <gtest/gtest.h>

#include "run_tests.h"  // Include the header file

// Function to run all tests
void run_tests(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);  // Initialize Google Test
    RUN_ALL_TESTS();                          // Run all tests
}