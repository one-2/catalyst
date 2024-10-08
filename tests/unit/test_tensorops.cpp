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
    double test_values[3][2] = {
        {0, 0},
        {0, 0},
        {0, 0}
    };
    torch::Tensor test = torch::from_blob(test_values, {2,3}, {3,3}, {torch::dtype(torch::kFloat64)});

    EXPECT_TRUE
    (
        torch::zeros({3, 2}).equal(test)
    );
}

//
// Identity
//
TEST(TestTensorOps, IdentityTensor)
{
    double test_values[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    torch::Tensor test = torch::from_blob(test_values, {3,3}, {torch::dtype(torch::kFloat64)});

    EXPECT_TRUE
    (
        tensorops::identity(3).equal(test)
    );
}

//
// Tensor sum
//
TEST(TestTensorOps, TensorSum)
{
    double test_values_a[3][3] = {
        {1, 0, 0},
        {0, 1, -1},
        {0, 0, 1}
    };
    torch::Tensor ta = torch::from_blob(test_values_a, {3,3}, {torch::dtype(torch::kFloat64)});

    double test_values_b[3][3] = {
        {0, 1, 0},
        {0, 0.5, 2.1},
        {7, 0, -5.6}
    };
    torch::Tensor tb = torch::from_blob(test_values_b, {3,3}, {torch::dtype(torch::kFloat64)});

    double test_values_c[3][3] = {
        {1, 1, 0},
        {0, 1.5, 1.1},
        {7, 0, -4.6}
    };
    torch::Tensor tc = torch::from_blob(test_values_c, {3,3}, {torch::dtype(torch::kFloat64)});

    EXPECT_TRUE
    (
        tensorops::sum(ta, tb).equal(tc)
    );
}   

//
// Tensor multiple
//
TEST(TestTensorOps, TensorMultiple)
{
    double test_values_a[3][3] = {
        {1, 1, 1},
        {-1, -1, -1},
        {-2, 2, 0}
    };
    torch::Tensor ta = torch::from_blob(test_values_a, {3,3}, {torch::dtype(torch::kFloat64)});

    double test_values_b[3][3] = {
        {-2, -2, -2},
        {2, 2, 2},
        {4, -4, 0}
    };
    torch::Tensor tb = torch::from_blob(test_values_b, {3,3}, {torch::dtype(torch::kFloat64)});

    double test_values_c[3][3] = {
        {4.5, 4.5, 4.5},
        {-4.5, -4.5, -4.5},
        {-9, 9, 0}
    };
    torch::Tensor tc = torch::from_blob(test_values_b, {3,3}, {torch::dtype(torch::kFloat64)});

    EXPECT_TRUE(
        tensorops::multiple(ta, -2).equal(tb)
    );

    EXPECT_TRUE(
        tensorops::multiple(ta, 4.5).equal(tc)
    );
}   

//
// Tensor scalar/dot product
//
TEST(TestTensorOps, TensorScalarProduct) {
    double test_values_a[3][3] = {
        {1, 1, 1},
        {-1, -1, -1},
        {-2, 2, 0}
    };
    torch::Tensor ta = torch::from_blob(test_values_a, {3,3}, {torch::dtype(torch::kFloat64)});

    double test_values_b[3][3] = {
        {-2, -2, -2},
        {2, 2, 2},
        {4, -4, 0}
    };
    torch::Tensor tb = torch::from_blob(test_values_b, {3,3}, {torch::dtype(torch::kFloat64)});

    double test_values_aa[3][3] = {
        {-2, -2, 0},
        {2, 2, 0},
        {0, 0, 0}
    };
    torch::Tensor taa = torch::from_blob(test_values_a, {3,3}, {torch::dtype(torch::kFloat64)});

    double test_values_ab[3][3] = {
        {4, -4, 0},
        {-4, 4, 0},
        {8, 8, 8}
    };
    torch::Tensor tab = torch::from_blob(test_values_a, {3,3}, {torch::dtype(torch::kFloat64)});

    EXPECT_TRUE(
        tensorops::scalar_product(ta, ta).equal(taa) 
    );

    EXPECT_TRUE(
        tensorops::scalar_product(ta, tb).equal(tab)
    );
}

//
// Tensor product
//
TEST(TestTensorOps, TensorProduct) {
    double test_values_a[2][2] = {
        {1, 0},
        {0, 1}
    };
    torch::Tensor ta = torch::from_blob(test_values_a, {2,2}, {torch::dtype(torch::kFloat64)});

    double test_values_b[2][2] = {
        {0, 1},
        {1, 0}
    };
    torch::Tensor tb = torch::from_blob(test_values_b, {2,2}, {torch::dtype(torch::kFloat64)});

    double test_values_c[2][2] = {
        {1, 1},
        {0, 0}
    };
    torch::Tensor tc = torch::from_blob(test_values_c, {2,2}, {torch::dtype(torch::kFloat64)});

    double test_values_d[2][2] = {
        {1, 2},
        {3, 4}
    };
    torch::Tensor td = torch::from_blob(test_values_d, {2,2}, {torch::dtype(torch::kFloat64)});
    
    double test_values_dd[2][2] = {
        {1, 6},
        {6, 16}
    };
    torch::Tensor tdd = torch::from_blob(test_values_dd, {2,2}, {torch::dtype(torch::kFloat64)});
    
    double test_values_identity[2][2] = {
        {1, 0},
        {0, 1}
    };
    torch::Tensor ti = torch::from_blob(test_values_identity, {2,2}, {torch::dtype(torch::kFloat64)});

    double test_values_zeroes[2][2] = {
        {0, 0},
        {0, 0}
    };
    torch::Tensor tz = torch::from_blob(test_values_zeroes, {2,2}, {torch::dtype(torch::kFloat64)});

    // ta x tb
    EXPECT_TRUE (
        tensorops::tensor_product(ta, tb).equal(tz)
    );

    // ta x tc neq tc x ta
    torch::Tensor sca = tensorops::tensor_product(tc, ta);
    torch::Tensor sac = tensorops::tensor_product(ta, tc);

    EXPECT_FALSE (
        sca.equal(sac)
    );

    // td x td
    EXPECT_TRUE (
        tensorops::tensor_product(td, td).equal(tdd)
    );

    // ta x tz
    EXPECT_TRUE (
        tensorops::tensor_product(ta, tz).equal(tz)
    );

    // ta x ti
    EXPECT_TRUE (
        tensorops::tensor_product(ta, ti).equal(ta)
    );
}

//
// Rectified Linear Unit tensor operation
//
TEST(TestTensorOps, ReLu) {
    double test_values_a[5][1] = {
        {-5},
        {3},
        {2.556},
        {-6000.07},
        {405.5}
    };
    torch::Tensor ta = torch::from_blob(test_values_a, {5,1}, {torch::dtype(torch::kFloat64)});

    double test_values_a_relu[5][1] = {
        {0},
        {3},
        {2.556},
        {0},
        {405.5}
    };
    torch::Tensor ta_relu = torch::from_blob(test_values_a_relu, {5,1}, {torch::dtype(torch::kFloat64)});

    EXPECT_TRUE(
        relu(ta).equal(ta_relu)
    );
}

//
// Softmax tensor operation
//
TEST(TestTensorOps, Softmax) {
    double test_values_a[3][1] = {
        {1.3},
        {5.1},
        {2.2}
    };
    torch::Tensor ta = torch::from_blob(test_values_a, {3,1}, {torch::dtype(torch::kFloat64)});

    double test_values_a_softmax[3][1] = {
        {1.3},  // PLACEHOLDER
        {5.1},
        {2.2}
    };
    torch::Tensor ta_softmax = torch::from_blob(test_values_a_softmax, {3,1}, {torch::dtype(torch::kFloat64)});

    EXPECT_TRUE(
        tensorops::softmax(ta).equal(ta_softmax)
    );
}

//
// Pipe << operator overload
//
TEST(TestTensorOps, PipeOperator) {
    double test_values[2][2] = {
        {1, 2},
        {3, 4}
    };
    torch::Tensor test_tensor = torch::from_blob(test_values, {2,2}, {torch::dtype(torch::kFloat64)});

    std::ostringstream oss;
    oss << test_tensor;

    std::string expected_output = " 1  2\n 3  4\n[ CPUFloatType{2,2} ]";
    EXPECT_EQ(
        oss.str(), expected_output
    );
}
