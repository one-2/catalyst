// tests/unit/test_m->cpp
//
// Author: Stephen Elliott
//
// Date: 2024-11-04
//
// Description: 
//
// B^)
//
#include <gtest/gtest.h>

#include "Model/Model.h"
#include "logging/LogBook/LogBook.h"
#include "Block/Block.h"

#include <memory>
#include <string>
#include <filesystem>


class MockBlock : public Block {
public:
    std::string type = "mock";
    MockBlock() : Block(type) {}
};

/*
Fixture:
Sets up model as smart pointer
*/class TestModel : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up model in testing temp directory
        temp_dir = "./temp/test";
        std::string device = "cpu";
        std::string name = "test_model";
        m = std::make_shared<Model>(temp_dir, device, name);
    }
    
    std::string temp_dir;
    std::shared_ptr<Model> m;
};
//
// NOTE: error: no matching function for call to ‘Model::Model(std::__cxx11::basic_string<char>&)
//       indicates that your call is wrong.
//

TEST_F(TestModel, Constructor)
{
    // Check if the model is correctly initialized
    EXPECT_EQ(m->get_device(), "cpu");
    EXPECT_EQ(m->get_name(), "test_model");
    EXPECT_EQ(m->get_timestamp().size(), 19);
    EXPECT_EQ(m->get_epoch(), -1);
    EXPECT_EQ(m->get_cycle(), -1);
}


TEST_F(TestModel, AddBlock)
{
    // int block_length_initial = m->get_blocks().size();

    // // Build a block
    // std::shared_ptr<Block> block = std::make_shared<MockBlock>();

    // // Add the block 
    // m->add_block(block);
    // int block_length_ultimate = m->get_blocks().size();
    
    // EXPECT_EQ(
    //     block_length_initial, block_length_ultimate
    // );
}


// TEST_F(TestModel, Compile)
// {
//     // Add a block
//     // Compile the model
//     // Assert no errors thrown
// }


// TEST_F(TestModel, Train)
// {
//     // Add a DEBUG block (friend of the test)
//     // Train it for a few epochs on some random data
//     // Test invalid arg 0, negative
//     // Test no blocks edge case
//     // Assert no errors thrown
//     // Get train losses from logs
//     // Assert nonempty and contain expected values (debug => constant)
// }


// // Set to not run if above fails
// TEST_F(TestModel, EvaluateAndCheckLogs)
// {
//     // Add a block
//     // Train for a bit
//     // Validate for a bit
//     // Assert no errors
//     // Get validation logs
//     // Assert nonempty and contain expected values (debug => constant)
//     // Get test logs
//     // Assert nonempty and contain expected values (debug => constant)
// }


// TEST_F(TestModel, GetExecutionLogs)
// {
//     // Add a block
//     // Train on some dummy data
//     // Validate on some dummy data
//     // Test on some dummy data
//     // Get train, validate and test logs
//     // Assert counts are as expected
//     // Assert all nonempty
// }


// TEST_F(TestModel, TestGetters)
// {
//     // Train for a bit
//     // Get logbook and check training losses
// }


// TEST_F(TestModel, SerialiseDeserialise)
// {
//     // Serialise the model
//     // Assert no errors
//     // Assert model can be deserialise and retrieved, with all relevant data the same
// }
