// tests/unit/test_logbook.cpp
//
// Author: Stephen Elliott
//
// Date: 2024-10-27
//
// Description: 
//
// Usage: 
//
#include <gtest/gtest.h>
#include <chrono>
#include <string>
#include <list>

#include "LogBook/LogBook.h"

class LogBookTest : public ::testing::Test {
protected:
    std::unique_ptr<LogBook> logBook;

    /// @brief Fixture. make_unique => no teardown override
    void SetUp() override {
        logBook = std::make_unique<LogBook>("TestLogBook", "/tmp");
    }
};

/// @brief Test write log
/// @param  
/// @param  
/// @brief Test write log
/// @param  
/// @param  
TEST_F(LogBookTest, WriteLog) {
    std::list<Info> infoList = {{"key1", "value1", 1.0f}, {"key2", "value2", 2.0f}};
    std::string logId = logBook->write_log("INFO", infoList);
    ASSERT_FALSE(logId.empty());
}

/// @brief Test read all logs of some type
/// @param  
/// @param  
TEST_F(LogBookTest, ReadLogType) {
    std::list<Info> infoList = {{"key1", "value1", 1.0f}};
    logBook->write_log("INFO", infoList);
    std::list<std::string> logs = logBook->read_log_type("INFO");
    ASSERT_EQ(logs.size(), 1);
}

/// @brief Test log serialisation runs
/// @param  
/// @param  
TEST_F(LogBookTest, SerialiseLog) {
    LogEntry logEntry = {std::chrono::system_clock::now(), "INFO", {{"key1", "value1", 1.0f}}};
    std::string serialisedLog = logBook->serialise_log(logEntry);
    ASSERT_FALSE(serialisedLog.empty());
}

/// @brief Test log serialisation works in both directions
/// @param  
/// @param  
TEST_F(LogBookTest, DeserialiseLog) {
    LogEntry logEntry = {std::chrono::system_clock::now(), "INFO", {{"key1", "value1", 1.0f}}};
    std::string serialisedLog = logBook->serialise_log(logEntry);

    LogEntry deserialisedLog = logBook->deserialise_log(serialisedLog);
    ASSERT_EQ(deserialisedLog.type, logEntry.type);
    ASSERT_EQ(deserialisedLog.info.size(), logEntry.info.size());
    ASSERT_EQ(deserialisedLog.info.front().key, logEntry.info.front().key);
    ASSERT_EQ(deserialisedLog.info.front().string_value, logEntry.info.front().string_value);
    ASSERT_EQ(deserialisedLog.info.front().float_value, logEntry.info.front().float_value);
    ASSERT_EQ(deserialisedLog.timestamp, logEntry.timestamp);
}

/// @brief Test writing and reading back a log
/// @param  
/// @param  
TEST_F(LogBookTest, WriteAndReadLog) {
    std::list<Info> infoList = {{"key1", "value1", 1.0f}};
    logBook->write_log("DEBUG", infoList);
    std::list<std::string> logs = logBook->read_log_type("DEBUG");
    ASSERT_EQ(logs.size(), 1);
    ASSERT_TRUE(logs.front().find("key1") != std::string::npos);
}

/// @brief Test writing/reading non-existent log types
/// @param  
/// @param  
TEST_F(LogBookTest, ReadNonExistentLogType) {
    std::list<std::string> logs = logBook->read_log_type("NON_EXISTENT");
    ASSERT_TRUE(logs.empty());
}
