
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


/**
 * @brief Test case for reading system logs from the LogBook.
 *
 * This test case verifies that the LogBook correctly logs a system event
 * and that the logs can be read back accurately. It performs the following steps:
 * 1. Logs a system event with epoch 1 and cycle 1.
 * 2. Reads the logs of type "system".
 * 3. Asserts that the size of the logs is 1.
 * 4. Asserts that the epoch of the first log entry is 1.
 * 5. Asserts that the cycle of the first log entry is 1.
 */
TEST_F(LogBookTest, ReadSystemLogs) {
    logBook->log_system(1, 1);
    auto logs = logBook->read_logs("system");
    ASSERT_EQ(logs.size(), 1);
    ASSERT_EQ(logs.front().get_epoch(), 1);
    ASSERT_EQ(logs.front().get_cycle(), 1);
}

/**
 * @brief Unit test for reading checkpoint logs from the LogBook.
 *
 * This test case verifies that a checkpoint log entry can be successfully
 * logged and read from the LogBook. It performs the following steps:
 * 1. Logs a checkpoint with specific epoch, cycle, serial, and name.
 * 2. Reads the logs filtered by "checkpoint".
 * 3. Asserts that the size of the logs is 1.
 * 4. Asserts that the epoch of the first log entry is 1.
 * 5. Asserts that the cycle of the first log entry is 1.
 */
TEST_F(LogBookTest, ReadCheckpointLogs) {
    std::string serial = "serial";
    std::string name = "name";
    logBook->log_checkpoint(1, 1, serial, name);
    auto logs = logBook->read_logs("checkpoint");
    ASSERT_EQ(logs.size(), 1);
    ASSERT_EQ(logs.front().get_epoch(), 1);
    ASSERT_EQ(logs.front().get_cycle(), 1);
}

/**
 * @brief Test case for reading evaluation logs from the LogBook.
 *
 * This test case logs an evaluation with specific parameters and then reads
 * the logs to verify that the log entry was correctly recorded.
 *
 * @details
 * - Logs an evaluation with epoch 1, cycle 1, score name "accuracy", and score value 0.6.
 * - Reads the logs of type "evaluation".
 * - Asserts that the size of the logs is 1.
 * - Asserts that the epoch of the first log entry is 1.
 * - Asserts that the cycle of the first log entry is 1.
 */
TEST_F(LogBookTest, ReadEvaluationLogs) {
    std::string score_name = "accuracy";
    logBook->log_evaluation(1, 1, score_name, 0.6);
    auto logs = logBook->read_logs("evaluation");
    ASSERT_EQ(logs.size(), 1);
    ASSERT_EQ(logs.front().get_epoch(), 1);
    ASSERT_EQ(logs.front().get_cycle(), 1);
}

/**
 * @brief Unit test for reading debug logs from the LogBook.
 *
 * This test case verifies that a debug log entry can be successfully written
 * and read from the LogBook. It performs the following steps:
 * 1. Logs a debug message with specific epoch and cycle values.
 * 2. Reads the logs filtered by the "debug" log level.
 * 3. Asserts that the size of the retrieved logs is 1.
 * 4. Asserts that the epoch and cycle values of the retrieved log match the expected values.
 */
TEST_F(LogBookTest, ReadDebugLogs) {
    std::string message = "Debug message";
    logBook->log_debug(1, 1, message);
    auto logs = logBook->read_logs("debug");
    ASSERT_EQ(logs.size(), 1);
    ASSERT_EQ(logs.front().get_epoch(), 1);
    ASSERT_EQ(logs.front().get_cycle(), 1);
}

/**
 * @brief Test case to verify the behavior of reading non-existent logs.
 *
 * This test case checks if the LogBook class throws a std::range_error
 * exception when attempting to read logs that do not exist.
 *
 * @note This test uses the Google Test framework.
 */
TEST_F(LogBookTest, ReadNonExistentLogs) {
    ASSERT_THROW(logBook->read_logs("nonexistent"), std::range_error);
}

/**
 * @brief Unit test for the LogBook class to verify the log_system function.
 *
 * This test case checks if the log_system function correctly logs the system
 * state by verifying the size of the logs and the values of epoch and cycle.
 *
 * @details
 * - Calls log_system with the current epoch and cycle from the model.
 * - Reads the logs with the type "system".
 * - Asserts that the size of the logs is 1.
 * - Asserts that the epoch of the first log is 1.
 * - Asserts that the cycle of the first log is 1.
 */
TEST_F(LogBookTest, TestWriteLogSystem) {
    logBook->log_system(model->get_epoch(), model->get_cycle());
    auto logs = logBook->read_logs("system");
    ASSERT_EQ(logs.size(), 1);
    ASSERT_EQ(logs.front().get_epoch(), 1);
    ASSERT_EQ(logs.front().get_cycle(), 1);

}

/**
 * @brief Unit test for the LogBook class to verify the functionality of writing a log checkpoint.
 *
 * This test case checks if a checkpoint log entry is correctly written to the log book.
 * It performs the following steps:
 * 1. Creates a serial and name string.
 * 2. Calls the log_checkpoint method of the logBook object with the current epoch and cycle from the model, along with the serial and name.
 * 3. Reads the logs with the type "checkpoint".
 * 4. Asserts that the size of the logs is 1.
 * 5. Asserts that the epoch of the first log entry is 1.
 * 6. Asserts that the cycle of the first log entry is 1.
 */
TEST_F(LogBookTest, TestWriteLogCheckpoint) {
    std::string serial = "serial";
    std::string name = "name";
    logBook->log_checkpoint(model->get_epoch(), model->get_cycle(), serial, name); // Encapsulates testing by avoiding calls to model
    auto logs = logBook->read_logs("checkpoint");
    ASSERT_EQ(logs.size(), 1);
    ASSERT_EQ(logs.front().get_epoch(), 1);
    ASSERT_EQ(logs.front().get_cycle(), 1);

}

/**
 * @brief Unit test for the LogBook class to verify the log_evaluation method.
 *
 * This test checks if the log_evaluation method correctly logs an evaluation
 * with the given parameters and if the log can be read back correctly.
 *
 * @details
 * - Sets up a score name "accuracy" and logs an evaluation with epoch 1, cycle 1, and score 0.6.
 * - Reads back the logs and verifies that there is exactly one log entry.
 * - Checks that the epoch and cycle of the log entry are correct.
 * - Verifies that the logged data contains the correct score name and value.
 */
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

/**
 * @brief Unit test for the LogBook class to verify the functionality of writing a debug log.
 *
 * This test case checks if a debug message is correctly logged and can be retrieved.
 * 
 * - It logs a debug message with the current epoch and cycle.
 * - It reads the logs filtered by the "debug" level.
 * - It asserts that there is exactly one log entry.
 * - It asserts that the epoch and cycle of the log entry are correct.
 * - It asserts that the log entry contains the expected message.
 */
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


/**
 * @brief Unit test for writing all types of log entries to storage.
 * 
 * This test verifies that the `write_log` function of the `MockIO` class correctly writes
 * different types of log entries (`SystemLogEntry`, `CheckpointLogEntry`, `EvaluationLogEntry`, 
 * and `DebugLogEntry`) to their respective expected file paths and ensures that the paths 
 * returned by the `write_log` function match the expected paths.
 * 
 * The test performs the following steps:
 * 1. Creates a `SystemLogEntry` and writes it to the expected path, then checks if the returned path matches the expected path.
 * 2. Creates a `CheckpointLogEntry` with a serial and name, writes it to the expected path, then checks if the returned path matches the expected path.
 * 3. Creates an `EvaluationLogEntry` with a score name and value, writes it to the expected path, then checks if the returned path matches the expected path.
 * 4. Creates a `DebugLogEntry` with a message, writes it to the expected path, then checks if the returned path matches the expected path.
 */
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
