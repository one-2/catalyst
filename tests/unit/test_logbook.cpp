
#include "gtest/gtest.h"
#include "LogBook/LogBook.h"
#include "LogEntry/LogEntry.h"
#include "Model/Model.h"
#include <string>
#include "LogEntry/SystemLogEntry/SystemLogEntry.h"
#include "LogEntry/CheckpointLogEntry/CheckpointLogEntry.h"
#include "LogEntry/EvaluationLogEntry/EvaluationLogEntry.h"
#include "LogEntry/DebugLogEntry/DebugLogEntry.h"


// MockIO class definition
class MockIO {
public:
    std::string write_log(const std::string& serialized_log, const std::string& path) {
        // Mock implementation of write_log
        return path;
    }
};

// Model and logbook fixture
class LogBookTest : public ::testing::Test {
protected:
    void SetUp() override {
        storage_directory = "test_logs";
        logBook = new logging::LogBook(storage_directory);
        model = new Model();
    }

    void TearDown() override {
        delete logBook;
        delete model;
    }

    std::string storage_directory;
    logging::LogBook* logBook;
    Model* model;

};


TEST_F(LogBookTest, ReadSystemLogs) {
    logBook->log_system(1, 1);
    auto logs = logBook->read_logs("system");
    ASSERT_EQ(logs.size(), 1);
    ASSERT_EQ(logs.front().get_epoch(), 1);
    ASSERT_EQ(logs.front().get_cycle(), 1);
}

TEST_F(LogBookTest, ReadCheckpointLogs) {
    std::string serial = "serial";
    std::string name = "name";
    logBook->log_checkpoint(1, 1, serial, name);
    auto logs = logBook->read_logs("checkpoint");
    ASSERT_EQ(logs.size(), 1);
    ASSERT_EQ(logs.front().get_epoch(), 1);
    ASSERT_EQ(logs.front().get_cycle(), 1);
}

TEST_F(LogBookTest, ReadEvaluationLogs) {
    std::string score_name = "accuracy";
    logBook->log_evaluation(1, 1, score_name, 0.6);
    auto logs = logBook->read_logs("evaluation");
    ASSERT_EQ(logs.size(), 1);
    ASSERT_EQ(logs.front().get_epoch(), 1);
    ASSERT_EQ(logs.front().get_cycle(), 1);
}

TEST_F(LogBookTest, ReadDebugLogs) {
    std::string message = "Debug message";
    logBook->log_debug(1, 1, message);
    auto logs = logBook->read_logs("debug");
    ASSERT_EQ(logs.size(), 1);
    ASSERT_EQ(logs.front().get_epoch(), 1);
    ASSERT_EQ(logs.front().get_cycle(), 1);
}

TEST_F(LogBookTest, ReadNonExistentLogs) {
    ASSERT_THROW(logBook->read_logs("nonexistent"), std::range_error);
}

TEST_F(LogBookTest, TestWriteLogSystem) {
    logBook->log_system(model->get_epoch(), model->get_cycle());
    auto logs = logBook->read_logs("system");
    ASSERT_EQ(logs.size(), 1);
    ASSERT_EQ(logs.front().get_epoch(), 1);
    ASSERT_EQ(logs.front().get_cycle(), 1);

}

TEST_F(LogBookTest, TestWriteLogCheckpoint) {
    std::string serial = "serial";
    std::string name = "name";
    logBook->log_checkpoint(model->get_epoch(), model->get_cycle(), serial, name); // Encapsulates testing by avoiding calls to model
    auto logs = logBook->read_logs("checkpoint");
    ASSERT_EQ(logs.size(), 1);
    ASSERT_EQ(logs.front().get_epoch(), 1);
    ASSERT_EQ(logs.front().get_cycle(), 1);

}

TEST_F(LogBookTest, TestWriteLogEvaluation) {
    std::string score_name = "accuracy";
    logBook->log_evaluation(
        model->get_epoch(),
        model->get_cycle(),
        score_name,
        0.6
    );
    auto logs = logBook->read_logs("evaluation");
    ASSERT_EQ(logs.size(), 1);
    ASSERT_EQ(logs.front().get_epoch(), 1);
    ASSERT_EQ(logs.front().get_cycle(), 1);

    std::shared_ptr<const logging::Logdata> data = logs.front().get_data();
    
    ASSERT_EQ(data->first, score_name);

    auto variant = std::get<double>(data->second);
    ASSERT_EQ(variant, 0.6);

}

TEST_F(LogBookTest, TestWriteLogDebug) {
    std::string message = "Debug message";
    logBook->log_debug(model->get_epoch(), model->get_cycle(), message);
    auto logs = logBook->read_logs("debug");
    ASSERT_EQ(logs.size(), 1);
    ASSERT_EQ(logs.front().get_epoch(), 1);
    ASSERT_EQ(logs.front().get_cycle(), 1);

    std::shared_ptr<const logging::Logdata> data = logs.front().get_data();
    
    std::string expected_key = "message";
    ASSERT_EQ(data->first, expected_key);

    auto variant = std::get<std::string>(data->second);
    ASSERT_EQ(variant, message);

}


TEST_F(LogBookTest, WriteAllLogsToStorage) {
    // SystemLogEntry
    logging::SystemLogEntry system_log_entry(1, 1);
    MockIO mock_io;
    std::string system_expected_path = storage_directory + "/SystemLogEntry/e1c1-0.log";
    std::string system_expected_serialized_log = system_log_entry.to_json();
    std::string system_log_path = mock_io.write_log(system_expected_serialized_log, system_expected_path);
    EXPECT_EQ(system_log_path, system_expected_path);

    // CheckpointLogEntry
    std::string serial = "serial_data";
    std::string name = "checkpoint_name";
    logging::CheckpointLogEntry checkpoint_log_entry(1, 1, serial, name);
    std::string checkpoint_expected_path = storage_directory + "/CheckpointLogEntry/e1c1-0.log";
    std::string checkpoint_expected_serialized_log = checkpoint_log_entry.to_json();
    std::string checkpoint_log_path = mock_io.write_log(checkpoint_expected_serialized_log, checkpoint_expected_path);
    EXPECT_EQ(checkpoint_log_path, checkpoint_expected_path);

    // EvaluationLogEntry
    std::string score_name = "accuracy";
    float score_value = 0.95;
    logging::EvaluationLogEntry evaluation_log_entry(1, 1, score_name, score_value);
    std::string evaluation_expected_path = storage_directory + "/EvaluationLogEntry/e1c1-0.log";
    std::string evaluation_expected_serialized_log = evaluation_log_entry.to_json();
    std::string evaluation_log_path = mock_io.write_log(evaluation_expected_serialized_log, evaluation_expected_path);
    EXPECT_EQ(evaluation_log_path, evaluation_expected_path);

    // DebugLogEntry
    std::string message = "debug_message";
    logging::DebugLogEntry debug_log_entry(1, 1, message);
    std::string debug_expected_path = storage_directory + "/DebugLogEntry/e1c1-0.log";
    std::string debug_expected_serialized_log = debug_log_entry.to_json();
    std::string debug_log_path = mock_io.write_log(debug_expected_serialized_log, debug_expected_path);
    EXPECT_EQ(debug_log_path, debug_expected_path);

}
