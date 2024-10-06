// testtensorops.cpp
//
// Stephen Elliott, 2024-10-06
//
// This file...
//

#include <gtest/gtest.h>

#include "tensorops/tensorops.h"

// Test cases

//
// Tensor sums as expected
//
TEST(TestTensorOps, TensorSum)
{
    EXPECT_EQ(0, 1);
}   

//
// Tensor multiplies as expected
//
TEST(TestTensorOps, MultipleOfTensor)
{
    EXPECT_EQ(0, 1);
}   

//
// Dot product as expected
//
TEST(TestTensorOps, TensorScalarProduct) {
    EXPECT_EQ(0, 1);

}

//
// Dot product fails gracefully
//
TEST(TestTensorOps, InvalidTensorScalarProduct) {
    EXPECT_EQ(0, 1);
    // Empty inputs
    // Invalid dimensions

}

//
// Tensor product as expected
//
TEST(TestTensorOps, TensorTensorProduct) {
    EXPECT_EQ(0, 1);

}

//
// Tensor product fails gracefully
//
TEST(TestTensorOps, InvalidTensorTensorProduct) {
    EXPECT_EQ(0, 1);
    // Empty inputs
    // Invalid dimensions

}
