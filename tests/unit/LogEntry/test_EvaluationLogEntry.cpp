#include <gtest/gtest.h>
#include "LogEntry/EvaluationLogEntry/EvaluationLogEntry.h"

using namespace logging;

TEST(EvaluationLogEntryTest, ConstructorTest) {
    int epoch = 1;
    int cycle = 2;
    std::string score_name = "accuracy";
    float score_value = 0.95;

    EvaluationLogEntry entry(epoch, cycle, score_name, score_value);

    EXPECT_EQ(entry.get_epoch(), epoch);
    EXPECT_EQ(entry.get_cycle(), cycle);
    EXPECT_EQ(entry.get_type(), "evaluation");

    auto data = entry.get_data();
    EXPECT_EQ(data->first, score_name);
    EXPECT_EQ(std::get<float>(data->second), score_value);
}

TEST(EvaluationLogEntryTest, ConstructorTestWithDifferentScore) {
    int epoch = 3;
    int cycle = 4;
    std::string score_name = "loss";
    float score_value = 0.05;

    EvaluationLogEntry entry(epoch, cycle, score_name, score_value);

    EXPECT_EQ(entry.get_epoch(), epoch);
    EXPECT_EQ(entry.get_cycle(), cycle);
    EXPECT_EQ(entry.get_type(), "evaluation");

    auto data = entry.get_data();
    EXPECT_EQ(data->first, score_name);
    EXPECT_EQ(std::get<float>(data->second), score_value);
}