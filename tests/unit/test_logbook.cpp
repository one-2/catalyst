
#include "gtest/gtest.h"
#include "LogBook/LogBook.h"
#include "LogEntry/LogEntry.h"
#include "Model/Model.h"


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

