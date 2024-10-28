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
        logBook = std::make_unique<LogBook>("/tmp");
    }
};

/// @brief Write/read all logs of some type
/// @param  
/// @param  
TEST_F(LogBookTest, InfoLogsWriteRead) {
    std::list<Info> info_list = {{"key1", "value1", 0.0f}, {"key2", "value2", 2.0f}};
    logBook->log_info(DEBUG, info_list);
    std::list<std::string> logs = logBook->read_log_type(DEBUG);
    ASSERT_EQ(1, logs.size());
}

/// @brief Write/read multiple logs
/// @param  
/// @param  
TEST_F(LogBookTest, InfoLogsWriteReadMultiple) {
    std::list<Info> info_list_1 = {{"key1", "value1", 0.0f}, {"key2", "value2", 2.0f}};
    logBook->log_info(DEBUG, info_list_1);
    std::list<std::string> logs = logBook->read_log_type(DEBUG);
    ASSERT_EQ(1, logs.size());

    std::list<Info> info_list_2 = {{"key1", "value1", 0.0f}, {"key2", "value2", 2.0f}};
    logBook->log_info(DEBUG, info_list_2);
    logs = logBook->read_log_type(DEBUG);
    ASSERT_EQ(2, logs.size());
}

/// @brief Write and read a checkpoint log
/// @param  
/// @param  
TEST_F(LogBookTest, CheckpointWriteRead) {
    Model model;
    logBook->log_checkpoint(model);
    std::list<std::string> logs = logBook->read_log_type(CHECKPOINT);
    ASSERT_EQ(logs.size(), 1);
    ASSERT_TRUE(logs.front().find("Model") != std::string::npos); // Assuming the serialized log contains "Model"
}

/// @brief Write/read non-existent log type
/// @param  
/// @param  
TEST_F(LogBookTest, NonExistentLogType) {
    std::list<std::string> logs = logBook->read_log_type(10000);
    ASSERT_TRUE(logs.empty());
}

/// @brief Write/read empty log type
/// @param  
/// @param  
TEST_F(LogBookTest, EmptyLogType) {
    std::list<std::string> logs = logBook->read_log_type(1);
    ASSERT_TRUE(logs.empty());
}
