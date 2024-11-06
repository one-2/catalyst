#include <gtest/gtest.h>
#include "LogEntry/DebugLogEntry/DebugLogEntry.h"

using namespace logging;

/**
 * @brief Unit test for the DebugLogEntry constructor.
 *
 * This test verifies that the DebugLogEntry constructor correctly initializes
 * the epoch, cycle, and message fields, and that the type is set to "debug".
 * It also checks that the data returned by get_data() contains the correct
 * key-value pair for the message.
 *
 * Test steps:
 * 1. Initialize epoch, cycle, and message variables.
 * 2. Create a DebugLogEntry object using the initialized variables.
 * 3. Verify that the epoch, cycle, and type fields of the DebugLogEntry object
 *    match the expected values.
 * 4. Retrieve the data from the DebugLogEntry object and verify that it contains
 *    the correct key-value pair for the message.
 */
TEST(DebugLogEntryTest, ConstructorTest) {
    int epoch = 1;
    int cycle = 2;
    std::string message = "This is a debug message";

    DebugLogEntry entry(epoch, cycle, message);

    EXPECT_EQ(entry.get_epoch(), epoch);
    EXPECT_EQ(entry.get_cycle(), cycle);
    EXPECT_EQ(entry.get_type(), "debug");

    auto data = entry.get_data();
    EXPECT_EQ(data->first, "message");
    EXPECT_EQ(std::get<std::string>(data->second), message);
}

/**
 * @brief Unit test for the DebugLogEntry constructor with a different message.
 *
 * This test case verifies that the DebugLogEntry constructor correctly initializes
 * the epoch, cycle, and message fields. It also checks that the type is set to "debug"
 * and that the data contains the correct message.
 *
 * @test
 * - Creates a DebugLogEntry object with epoch 3, cycle 4, and message "Another debug message".
 * - Verifies that the epoch and cycle are correctly set.
 * - Verifies that the type is "debug".
 * - Verifies that the data contains the correct message.
 */
TEST(DebugLogEntryTest, ConstructorTestWithDifferentMessage) {
    int epoch = 3;
    int cycle = 4;
    std::string message = "Another debug message";

    DebugLogEntry entry(epoch, cycle, message);

    EXPECT_EQ(entry.get_epoch(), epoch);
    EXPECT_EQ(entry.get_cycle(), cycle);
    EXPECT_EQ(entry.get_type(), "debug");

    auto data = entry.get_data();
    EXPECT_EQ(data->first, "message");
    EXPECT_EQ(std::get<std::string>(data->second), message);
}