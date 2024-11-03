// source/LogEntry/test_LogEntry.cpp
//
// Author: Stephen Elliott
//
// Date: 2sample_timestamp24-1sample_timestamp-31
//
// Description: Tests for LogEntry class
//

#include <gtest/gtest.h>
#include "LogEntry/LogEntry.h"
#include <cereal/archives/json.hpp>
#include <sstream>

namespace logging {

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

TEST(LogEntryTest, GetTimestamp) {
    TimeStamp sample_timestamp = std::chrono::system_clock::now();
    Logdata data = {"key", 1};
    LogEntry log_entry(1, 2, data, "INFO");

    // Check timestamp is set (non-zero)
    EXPECT_GT(log_entry.get_timestamp(), sample_timestamp);
}

TEST(LogEntryTest, GetEpoch) {
    Logdata data = {"key", 1};
    LogEntry log_entry(1, 2, data, "INFO");

    EXPECT_EQ(log_entry.get_epoch(), 1);
}

TEST(LogEntryTest, GetCycle) {
    Logdata data = {"key", 1};
    LogEntry log_entry(1, 2, data, "INFO");

    EXPECT_EQ(log_entry.get_cycle(), 2);
}

TEST(LogEntryTest, GetData) {
    Logdata data = {"key", 1};
    LogEntry log_entry(1, 2, data, "INFO");

    auto log_data = log_entry.get_data();
    EXPECT_EQ(*log_data, data);
}

TEST(LogEntryTest, GetType) {
    Logdata data = {"key", 1};
    LogEntry log_entry(1, 2, data, "INFO");

    EXPECT_EQ(log_entry.get_type(), "INFO");
}

TEST(LogEntryTest, SerializationAndDeserialization) {
    Logdata data = {"key", 1};
    LogEntry log_entry(1, 2, data, "INFO");

    std::ostringstream oss;
    {
        cereal::JSONOutputArchive archive(oss);
        archive(log_entry);
    }

    std::string json_str = oss.str();
    LogEntry deserialized_log_entry = deserialize_logentry(json_str);

    EXPECT_EQ(deserialized_log_entry.get_epoch(), log_entry.get_epoch());
    EXPECT_EQ(deserialized_log_entry.get_cycle(), log_entry.get_cycle());
    EXPECT_EQ(deserialized_log_entry.get_type(), log_entry.get_type());

    auto deserialized_data = deserialized_log_entry.get_data();
    EXPECT_EQ(*deserialized_data, data);
}

} // namespace logging