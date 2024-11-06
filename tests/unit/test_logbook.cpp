
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

// TEST_F(LogBookTest, TestLogSystem) {
//     logBook->log_system(model->get_epoch(), model->get_cycle());
//     auto logs = logBook->read_logs("system");
//     ASSERT_EQ(logs.size(), 1);
//     ASSERT_EQ(logs.front().get_epoch(), 1);
//     ASSERT_EQ(logs.front().get_cycle(), 1);
// }

// TEST_F(LogBookTest, TestLogCheckpoint) {
//     logBook->log_checkpoint(model->get_epoch(), model->get_cycle(), *model);
//     auto logs = logBook->read_logs("checkpoint");
//     ASSERT_EQ(logs.size(), 1);
//     ASSERT_EQ(logs.front().get_epoch(), 1);
//     ASSERT_EQ(logs.front().get_cycle(), 1);
// }

TEST_F(LogBookTest, TestLogEvaluation) {
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
    // ASSERT_EQ(data->second, 0.6);

}

// TEST_F(LogBookTest, TestLogDebug) {
//     std::string message = "Debug message";
//     logBook->log_debug(model->get_epoch(), model->get_cycle(), message);
//     auto logs = logBook->read_logs("debug");
//     ASSERT_EQ(logs.size(), 1);
//     ASSERT_EQ(logs.front().get_epoch(), 1);
//     ASSERT_EQ(logs.front().get_cycle(), 1);
//     ASSERT_EQ(logs.front().get_message(), message);
// }

