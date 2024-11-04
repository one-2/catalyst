// tests/unit/test_Model.cpp
//
// Author: Stephen Elliott
//
// Date: 2024-11-04
//
// Description: 
//
// B^)
//
#include <gtest/gtest>

#include <memory>

/*
Fixture:
Sets up model as smart pointer
*/
class TestModel : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up model in testing temp directory
        std::string temp_dir = "./temp/test";        
        std::shared_ptr<Model> m = std::make_shared<Model>(temp_dir);
    }
};


TEST_F(TestModel, Constructor)
{
    LogBook logbook = model.get_logbook();
    std::string log_path = logbook.generate_log_path();

    EXPECT_TRUE
    (
        log_path.find(temp_dir) != std::string::npos
    );
    
    EXPECT_TRUE
    (
        log_path.exists()
    );
    
    // Else
    // struct stat buffer;
    // bool buffer_exists_and_at_0 = (stat (log_path.c_str(), &buffer) == 0);
}

TEST_F(TestModel, AddBlock)
{
    int block_length_initial = model.get_blocks().size();
    std::string type = "DEBUG"; // TODO add to block diagram  
    model.add_block(type);
    int block_length_ultimate = model.get_blocks().size();
    
    EXPECT_EQ
    (
        block_length_initial, block_length_ultimate
    )
}

// TEST_F(TestModel, Compile) // TODO remove from block diagram; this method 
// should not be exposed.

TEST_F(TestModel, Train)
{
    // Add a DEBUG block (friend of the test)
    // Train it for a few epochs on some random data
    // Test invalid arg 0, negative
    // Test no blocks edge case
    // Assert no errors thrown
    // Get train losses from logs
    // Assert nonempty and contain expected values (debug => constant)
}

// Set to not run if above fails
TEST_F(TestModel, EvaluateAndCheckLogs)
{
    // Add a block
    // Train for a bit
    // Validate for a bit
    // Assert no errors
    // Get validation logs
    // Assert nonempty and contain expected values (debug => constant)
    // Get test logs
    // Assert nonempty and contain expected values (debug => constant)
}

TEST_F(TestModel, GetExecutionLogs)
{
    // Add a block
    // Train on some dummy data
    // Validate on some dummy data
    // Test on some dummy data
    // Get train, validate and test logs
    // Assert counts are as expected
    // Assert all nonempty
}

TEST_F(TestModel, GetLogbook)
{
    // Train for a bit
    // Get logbook and check training losses
}

TEST_F(TestModel, SerialiseAndDeserialise)
{
    // Serialise the model
    // Assert no errors
    // Assert model can be deserialise and retrieved, with all relevant data the same
}
