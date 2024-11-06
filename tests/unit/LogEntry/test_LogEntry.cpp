// source/LogEntry/test_LogEntry.cpp
//
// Author: Stephen Elliott
//
// Date: 2sample_timestamp24-1sample_timestamp-31
//
// Description: Tests for LogEntry class
//

#include <gtest/gtest.h>
#include <cereal/archives/json.hpp>

#include "logging/LogEntry/LogEntry.h"

#include <sstream>

namespace logging {

/**
 * @brief Unit test for the LogEntry class constructor and getter methods.
 *
 * This test verifies the following:
 * - The constructor correctly initializes the epoch, cycle, data, and type fields.
 * - The getter methods (get_epoch, get_cycle, get_type, get_data) return the expected values.
 * - The timestamp is set to a non-zero value and is greater than a sample timestamp taken before the LogEntry object is created.
 */
TEST(LogEntryTest, ConstructorAndGetters) {
    TimeStamp sample_timestamp = std::chrono::system_clock::now();
    Logdata data = {"key", 1};
    LogEntry log_entry(1, 2, data, "INFO");

    EXPECT_EQ(log_entry.get_epoch(), 1);
    EXPECT_EQ(log_entry.get_cycle(), 2);
    EXPECT_EQ(log_entry.get_type(), "INFO");

    auto log_data = log_entry.get_data();
    EXPECT_EQ(*log_data, data);

    // Check timestamp is set (non-zero)
    EXPECT_GT(log_entry.get_timestamp(), sample_timestamp);
}

/**
 * @brief Unit test for the LogEntry class, specifically testing the GetTimestamp method.
 *
 * This test case verifies that the timestamp of a LogEntry object is correctly set and is greater than a sample timestamp
 * taken just before the LogEntry object is created.
 *
 * @test
 * - Create a sample timestamp using the current system time.
 * - Create a Logdata object with sample data.
 * - Create a LogEntry object with the sample data and a log level of "INFO".
 * - Verify that the timestamp of the LogEntry object is greater than the sample timestamp.
 */
TEST(LogEntryTest, GetTimestamp) {
    TimeStamp sample_timestamp = std::chrono::system_clock::now();
    Logdata data = {"key", 1};
    LogEntry log_entry(1, 2, data, "INFO");

    // Check timestamp is set (non-zero)
    EXPECT_GT(log_entry.get_timestamp(), sample_timestamp);
}

/**
 * @brief Unit test for the LogEntry class's get_epoch method.
 *
 * This test case verifies that the get_epoch method of the LogEntry class
 * correctly returns the epoch value that was set during the construction
 * of the LogEntry object.
 *
 * Test steps:
 * 1. Create a Logdata object with a key and a value.
 * 2. Construct a LogEntry object with specific epoch, timestamp, Logdata, and log level.
 * 3. Use EXPECT_EQ to check if the get_epoch method returns the expected epoch value.
 */
TEST(LogEntryTest, GetEpoch) {
    Logdata data = {"key", 1};
    LogEntry log_entry(1, 2, data, "INFO");

    EXPECT_EQ(log_entry.get_epoch(), 1);
}

/**
 * @brief Unit test for the LogEntry class's get_cycle method.
 *
 * This test verifies that the get_cycle method of the LogEntry class
 * correctly returns the cycle value that was set during the construction
 * of the LogEntry object.
 *
 * Test case:
 * - Create a LogEntry object with a specific cycle value.
 * - Verify that the get_cycle method returns the expected cycle value.
 */
TEST(LogEntryTest, GetCycle) {
    Logdata data = {"key", 1};
    LogEntry log_entry(1, 2, data, "INFO");

    EXPECT_EQ(log_entry.get_cycle(), 2);
}

/**
 * @brief Unit test for the LogEntry class's get_data method.
 *
 * This test case verifies that the get_data method of the LogEntry class
 * correctly returns the data associated with the log entry.
 *
 * Test steps:
 * 1. Create a Logdata object with a key-value pair.
 * 2. Initialize a LogEntry object with specific parameters including the Logdata object.
 * 3. Call the get_data method on the LogEntry object.
 * 4. Verify that the returned data matches the original Logdata object using EXPECT_EQ.
 */
TEST(LogEntryTest, GetData) {
    Logdata data = {"key", 1};
    LogEntry log_entry(1, 2, data, "INFO");

    auto log_data = log_entry.get_data();
    EXPECT_EQ(*log_data, data);
}

/**
 * @brief Unit test for the LogEntry class to verify the get_type() method.
 *
 * This test case creates a LogEntry object with a specified type and checks
 * if the get_type() method returns the correct type.
 *
 * Test case steps:
 * 1. Create a Logdata object with a key and value.
 * 2. Instantiate a LogEntry object with the Logdata object and a type "INFO".
 * 3. Verify that the get_type() method of the LogEntry object returns "INFO".
 */
TEST(LogEntryTest, GetType) {
    Logdata data = {"key", 1};
    LogEntry log_entry(1, 2, data, "INFO");

    EXPECT_EQ(log_entry.get_type(), "INFO");
}

/**
 * @brief Unit test for the serialization and deserialization of LogEntry.
 *
 * This test verifies that a LogEntry object can be correctly serialized to a JSON string
 * and then deserialized back to a LogEntry object. It checks that the epoch, cycle, type,
 * and data fields of the deserialized LogEntry match those of the original LogEntry.
 *
 * Test steps:
 * 1. Create a LogEntry object with specific values.
 * 2. Serialize the LogEntry object to a JSON string using cereal::JSONOutputArchive.
 * 3. Deserialize the JSON string back to a LogEntry object using LogEntry::deserialize_logentry.
 * 4. Verify that the epoch, cycle, and type fields of the deserialized LogEntry match the original.
 * 5. Verify that the data field of the deserialized LogEntry matches the original.
 */
TEST(LogEntryTest, SerializationAndDeserialization) {
    Logdata data = {"key", 1};
    LogEntry log_entry(1, 2, data, "INFO");

    std::ostringstream oss;
    {
        cereal::JSONOutputArchive archive(oss);
        archive(log_entry);
    }

    std::string json_str = oss.str();
    LogEntry deserialized_log_entry = LogEntry::deserialize_logentry(json_str);

    EXPECT_EQ(deserialized_log_entry.get_epoch(), log_entry.get_epoch());
    EXPECT_EQ(deserialized_log_entry.get_cycle(), log_entry.get_cycle());
    EXPECT_EQ(deserialized_log_entry.get_type(), log_entry.get_type());

    auto deserialized_data = deserialized_log_entry.get_data();
    EXPECT_EQ(*deserialized_data, data);
}

} // namespace logging