// test_modelhistory.cpp
//
// Author: Stephen Elliott
//
// Date: 2024-10-13
//
// Description: Tests for the ModelHistory class.
//

#include <gtest/gtest.h>
#include "ModelHistory/ModelHistory.h"

// Test cases

//
// Constructor and getters
// Properties initialized correctly
// Constructor tests depend on getters, so these are initialised here too
// 
TEST(ModelHistory, Constructor)
{
    bool is_training_t1 = false;
    bool stopwatch_t1 = false;
    int sampling_rate_t1 = 1000;
    ModelHistory t1 = ModelHistory(is_training_t1, stopwatch_t1, sampling_rate_t1);

    EXPECT_EQ(t1.get_is_training(), is_training_t1);
    EXPECT_EQ(t1.get_history_length(), 0);
    EXPECT_EQ(t1.get_sampling_rate(), sampling_rate_t1);
    EXPECT_EQ(t1.get_losses().size(), 0);

    bool is_training_t2 = true;
    bool stopwatch_t2 = true;
    int sampling_rate_t2 = 2000;
    ModelHistory t2 = ModelHistory(is_training_t2, stopwatch_t2, sampling_rate_t2);

    EXPECT_EQ(t2.get_is_training(), is_training_t2);
    EXPECT_EQ(t2.get_history_length(), 0);
    EXPECT_EQ(t2.get_sampling_rate(), sampling_rate_t2);
    EXPECT_EQ(t2.get_losses().size(), 0);
}

//
// Append history and get_losses
//
TEST(ModelHistory, AppendHistoryAndGetLosses)
{
    ModelHistory mh(false, false, 1000);
    mh.append_history(0.5);
    mh.append_history(0.3);
    mh.append_history(0.2);

    std::vector<float> expected_losses = {0.5, 0.3, 0.2};
    EXPECT_EQ(mh.get_losses(), expected_losses);
    EXPECT_EQ(mh.get_history_length(), 3);
}

//
// Append history with timing and get_stopwatch
//
TEST(ModelHistory, AppendHistoryWithTimingAndGetStopwatch)
{
    ModelHistory mh(false, true, 1000);
    mh.append_history(0.5, 1.0);
    mh.append_history(0.3, 2.0);
    mh.append_history(0.2, 3.0);

    std::vector<float> expected_stopwatch = {1.0, 2.0, 3.0};
    EXPECT_EQ(mh.get_stopwatch(), expected_stopwatch);
    EXPECT_EQ(mh.get_history_length(), 3);
}

//
// Get sampling rate
//
TEST(ModelHistory, GetSamplingRate)
{
    ModelHistory mh(false, false, 1500);
    EXPECT_EQ(mh.get_sampling_rate(), 1500);
}

//
// Get is_training
//
TEST(ModelHistory, GetIsTraining)
{
    ModelHistory mh(true, false, 1000);
    EXPECT_EQ(mh.get_is_training(), true);
}

//
// Operator<< overload
//
TEST(ModelHistory, OperatorOutputStream)
{
    ModelHistory mh(false, false, 1000);
    mh.append_history(0.5);
    mh.append_history(0.3);

    std::ostringstream os;
    os << mh;

    std::string expected_output = "ModelHistory(is_training=0, architecture=default)\nLosses: 0.5 0.3 \nTimings: ";
    EXPECT_EQ(os.str(), expected_output);
}
