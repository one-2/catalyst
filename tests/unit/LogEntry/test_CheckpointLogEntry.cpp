#include <gtest/gtest.h>
#include "LogEntry/CheckpointLogEntry/CheckpointLogEntry.h"
#include "Model/Model.h"

using namespace logging;

class MockModel : public Model {
public:
    std::string serialize() const {
        return "mock_serialized_data";
    }
};

TEST(CheckpointLogEntryTest, ConstructorTest) {
    int epoch = 1;
    int cycle = 2;
    std::string model_name = "TestModel";
    MockModel model;
    std::string serial = model.serialize();

    CheckpointLogEntry entry(epoch, cycle, serial, model_name);

    // EXPECT_EQ(entry.get_epoch(), epoch);
    // EXPECT_EQ(entry.get_cycle(), cycle);
    // EXPECT_EQ(entry.get_type(), "checkpoint");

    // auto data = entry.get_data();
    // EXPECT_EQ(data->first, model_name);
    // EXPECT_EQ(std::get<std::string>(data->second), model.serialize());
}

// TEST(CheckpointLogEntryTest, ConstructorTestWithDifferentModel) {
//     int epoch = 3;
//     int cycle = 4;
//     std::string model_name = "AnotherTestModel";
//     MockModel model;
//     std::string serial = model.serialize();

//     CheckpointLogEntry entry(epoch, cycle, serial, model_name);

//     EXPECT_EQ(entry.get_epoch(), epoch);
//     EXPECT_EQ(entry.get_cycle(), cycle);
//     EXPECT_EQ(entry.get_type(), "checkpoint");

//     auto data = entry.get_data();
//     EXPECT_EQ(data->first, model_name);
//     EXPECT_EQ(std::get<std::string>(data->second), model.serialize());
// }