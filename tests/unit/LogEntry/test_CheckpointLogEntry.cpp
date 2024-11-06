#include <gtest/gtest.h>

#include "logging/LogEntry/CheckpointLogEntry/CheckpointLogEntry.h"
#include "Model/Model.h"

#include <iostream>

using namespace logging;


class MockModel : public Model {
public:
    std::string msg = "mock_serialized_data";
    std::string serialize() const {
        return msg;
    }

};

/**
 * @brief Unit test for the CheckpointLogEntry constructor.
 *
 * This test verifies the proper construction of a CheckpointLogEntry object.
 * It checks the initialization of epoch, cycle, type, and data fields.
 *
 * Test steps:
 * 1. Initialize epoch, cycle, and model.
 * 2. Serialize the model and define the model name.
 * 3. Construct a CheckpointLogEntry object with the initialized values.
 * 4. Verify that the epoch and cycle are correctly set.
 * 5. Verify that the type is set to "checkpoint".
 * 6. Retrieve the data from the entry and verify the model name and serialized model.
 *
 * Expected results:
 * - The epoch should match the initialized value.
 * - The cycle should match the initialized value.
 * - The type should be "checkpoint".
 * - The data should contain the correct model name and serialized model.
 */
TEST(CheckpointLogEntryTest, ConstructorTest) {
    int epoch = 1;
    int cycle = 2;
    MockModel model;
    std::string serial = model.serialize();
    std::string model_name = "TestModel";

    CheckpointLogEntry entry(epoch, cycle, serial, model_name);

    EXPECT_EQ(entry.get_epoch(), epoch);
    EXPECT_EQ(entry.get_cycle(), cycle);
    EXPECT_EQ(entry.get_type(), "checkpoint");

    auto data = entry.get_data();
    EXPECT_EQ(data->first, model_name);
    EXPECT_EQ(std::get<std::string>(data->second), model.serialize());

}

/**
 * @brief Unit test for the CheckpointLogEntry constructor with a different model.
 *
 * This test verifies that the CheckpointLogEntry constructor correctly initializes
 * the object with the given epoch, cycle, serialized model data, and model name.
 *
 * The test performs the following checks:
 * - Ensures the epoch is correctly set.
 * - Ensures the cycle is correctly set.
 * - Ensures the type is correctly set to "checkpoint".
 * - Ensures the data contains the correct model name and serialized model data.
 */
TEST(CheckpointLogEntryTest, ConstructorTestWithDifferentModel) {
    int epoch = 3;
    int cycle = 4;
    std::string model_name = "AnotherTestModel";
    MockModel model;
    std::string serial = model.serialize();

    CheckpointLogEntry entry(epoch, cycle, serial, model_name);

    EXPECT_EQ(entry.get_epoch(), epoch);
    EXPECT_EQ(entry.get_cycle(), cycle);
    EXPECT_EQ(entry.get_type(), "checkpoint");

    auto data = entry.get_data();
    EXPECT_EQ(data->first, model_name);
    EXPECT_EQ(std::get<std::string>(data->second), model.serialize());

}