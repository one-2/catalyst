// run_tests.h
//
// Stephen Elliott, 2024-10-06
//
// This file...
//

#include <gtest/gtest.h>

// A simple function to test
int add(int a, int b) {
    return a + b;
}

// Define a test case for the add function
TEST(AdditionTest, HandlesPositiveInput) {
    EXPECT_EQ(add(1, 2), 3);  // Test if 1 + 2 equals 3
}

TEST(AdditionTest, HandlesNegativeInput) {
    EXPECT_EQ(add(-1, -2), -3);  // Test if -1 + -2 equals -3
}
