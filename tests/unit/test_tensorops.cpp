// testtensorops.cpp
//
// Stephen Elliott, 2024-10-06
//
// This file...
//

#include <gtest/gtest.h>
#include <torch/torch.h>
#include "tensorops/tensorops.h"

// Test cases

//
// Zeroes
// Produces the zeroes vector
//
TEST(TestTensorOps, ZeroTensor)
{
    torch::Tensor output = zeroes(3,2);
    
    double array[] test_values = {
        {0, 0, 0}, {0, 0, 0}
    };
    torch::Tensor test = torch::Tensor(test_values, {torch::kfloat64});

    EXPECT_EQ
    (
        output, test
    )
}

//
// Identity
//
TEST(TestTensorOps, IdentityTensor)
{

    double array[] test_values = {
        {1, 0, 0}, {0, 1, 0}, {0, 0, 1}
    };
    torch::Tensor test = torch::Tensor(test_values, {torch::kfloat64});

    EXPECT_EQ
    (
        identity(3), test
    )
}

//
// Tensor sum
//
TEST(TestTensorOps, TensorSum)
{
    double array[] test_values_a = {
        {1, 0, 0}, {0, 1, -1}, {0, 0, 1}
    };
    torch::Tensor ta = torch::Tensor(test_values_a, {torch::kfloat64});

    double array[] test_values_b = {
        {0, 1, 0}, {0, 0.5, 2.1}, {7, 0, -5.6}
    };
    torch::Tensor tb = torch::Tensor(test_values_b, {torch::kfloat64});

    double array[] test_values_c = {
        {1, 1, 0}, {0, 1.5, 1.1}, {7, 0, -4.6}
    };
    torch::Tensor tc = torch::Tensor(test_values_c, {torch::kfloat64});

    EXPECT_EQ
    (
        sum(ta, tb), tc
    )
}   

//
// Tensor multiple
//
TEST(TestTensorOps, TensorMultiple)
{
    double array[] test_values_a = {
        {1, 1, 1}, {-1, -1, -1}, {-2, 2, 0}
    };
    torch::Tensor ta = torch::Tensor(test_values_a, {torch::kfloat64});

    double array[] test_values_b = {
        {-2, -2, -2}, {2, 2, 2}, {4, -4, 0}
    };
    torch::Tensor tb = torch::Tensor(test_values_b, {torch::kfloat64});

    double array[] test_values_c = {
        {4.5, 4.5, 4.5}, {-4.5, -4.5, -4.5}, {-9, 9, 0}
    };
    torch::Tensor tc = torch::Tensor(test_values_b, {torch::kfloat64});


    EXPECT_EQ(
        multiple(ta, -2), tb
    );

    EXPECT_EQ(
        multiple(ta, 4.5), tc
    );
}   

//
// Tensor scalar/dot product
//
TEST(TestTensorOps, TensorScalarProduct) {
    double array[] test_values_a = {
        {1, 1, 1}, {-1, -1, -1}, {-2, 2, 0}
    };
    torch::Tensor ta = torch::Tensor(test_values_a, {torch::kfloat64});

    double array[] test_values_b = {
        {-2, -2, -2}, {2, 2, 2}, {4, -4, 0}
    };
    torch::Tensor tb = torch::Tensor(test_values_b, {torch::kfloat64});

    double array[] test_values_aa = {
        {, , }, {, , }, {, , }
    };
    torch::Tensor taa = torch::Tensor(test_values_a, {torch::kfloat64});

    double array[] test_values_ab = {
        {, , }, {, , }, {, , }
    };
    torch::Tensor tab = torch::Tensor(test_values_a, {torch::kfloat64});

    EXPECT_EQ(
        scalar_product(ta, ta), taa 
    );

    EXPECT_EQ(
        scalar_product(ta, tb), tab 
    );
}

//
// Tensor product
//
TEST(TestTensorOps, TensorProduct) {
    double array[] test_values_a = {
        {1, 0}, {0, 1}
    };
    torch::Tensor ta = torch::Tensor(test_values_a, {torch::kfloat64});

    double array[] test_values_b = {
        {0, 1}, {1, 0}
    };
    torch::Tensor tb = torch::Tensor(test_values_b, {torch::kfloat64});

    double array[] test_values_c = {
        {1, 1}, {0, 0}
    };
    torch::Tensor tc = torch::Tensor(test_values_c, {torch::kfloat64});

    double array[] test_values_d = {
        {1, 2}, {3, 4}
    };
    torch::Tensor tc = torch::Tensor(test_values_d, {torch::kfloat64});
    
    double array[] test_values_dd = {
        {1, 6}, {6, 16}
    };
    torch::Tensor tc = torch::Tensor(test_values_dd, {torch::kfloat64});
    
    double array[] test_values_identity = {
        {1, 0}, {0, 1}
    };
    torch::Tensor ti = torch::Tensor(test_values_identity, {torch::kfloat64});


    double array[] test_values_zeroes = {
        {0, 0}, {0, 0}
    };
    torch::Tensor tz = torch::Tensor(test_values_zeroes, {torch::kfloat64});


    // ta x tb
    EXPECT_EQ(
        tensor_product(ta, tb), t_zeroes
    );

    // ta x tc neq tc x ta
    EXPECT_NE(
        tensor_product(ta, tc), tensor_product(tc, ta)
    );

    // td x td
    EXPECT_EQ(
        tensor_product(td, td), tdd
    );

    // ta x tz
    EXPECT_EQ(
        tensor_product(ta, tz), tz
    );

    // ta x ti
    EXPECT_EQ(
        tensor_product(ta, ti), ta
    );
}

//
// Rectified Linear Unit tensor operation
//
TEST(TestTensorOps, ReLu) {
    double array[] test_values_a = {
        {-5, 3, 2.556, -6000.07, 405.5}
    };
    torch::Tensor ta = torch::Tensor(test_values, {torch::kfloat64});

    double array[] test_values_a_relu = {
        {0, 3, 2.556, 0, 405.5}
    };
    torch::Tensor ta_relu = torch::Tensor(test_values, {torch::kfloat64});

    EXPECT_EQ(
        relu(ta), ta_relu
    );
}

//
// Softmax tensor operation
//
TEST(TestTensorOps, Softmax) {
    double array[] test_values_a = {
        {1.3, 5.1, 2.2}
    };
    torch::Tensor ta = torch::Tensor(test_values, {torch::kfloat64});

    double array[] test_values_a_softmax = {
        {1.3, 5.1, 2.2}
    };
    torch::Tensor ta_softmax = torch::Tensor(test_values, {torch::kfloat64});

    EXPECT_EQ(
        softmax(ta), ta_softmax
    );
}

//
// Pipe << operator overload
//
TEST(TEstTensorOps, PipeOperator) {
    EXPECT_EQ(
        0, 1
    )
}
