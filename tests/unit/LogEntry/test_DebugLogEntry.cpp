// #include <gtest/gtest.h>
// #include "LogEntry/DebugLogEntry/DebugLogEntry.h"

// using namespace logging;

// TEST(DebugLogEntryTest, ConstructorTest) {
//     int epoch = 1;
//     int cycle = 2;
//     std::string message = "This is a debug message";

//     DebugLogEntry entry(epoch, cycle, message);

//     EXPECT_EQ(entry.get_epoch(), epoch);
//     EXPECT_EQ(entry.get_cycle(), cycle);
//     EXPECT_EQ(entry.get_type(), "debug");

//     auto data = entry.get_data();
//     EXPECT_EQ(data->first, "message");
//     EXPECT_EQ(std::get<std::string>(data->second), message);
// }

// TEST(DebugLogEntryTest, ConstructorTestWithDifferentMessage) {
//     int epoch = 3;
//     int cycle = 4;
//     std::string message = "Another debug message";

//     DebugLogEntry entry(epoch, cycle, message);

//     EXPECT_EQ(entry.get_epoch(), epoch);
//     EXPECT_EQ(entry.get_cycle(), cycle);
//     EXPECT_EQ(entry.get_type(), "debug");

//     auto data = entry.get_data();
//     EXPECT_EQ(data->first, "message");
//     EXPECT_EQ(std::get<std::string>(data->second), message);
// }