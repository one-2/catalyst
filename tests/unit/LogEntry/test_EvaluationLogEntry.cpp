#include <gtest/gtest.h>

#include "logging/LogEntry/EvaluationLogEntry/EvaluationLogEntry.h"

using namespace logging;

/**
 * @brief Unit test for the EvaluationLogEntry constructor.
 *
 * This test verifies that the EvaluationLogEntry constructor correctly initializes
 * the object with the given parameters and that the getter methods return the expected values.
 *
 * Test steps:
 * 1. Initialize the parameters for the EvaluationLogEntry constructor.
 * 2. Create an EvaluationLogEntry object with the given parameters.
 * 3. Verify that the get_epoch() method returns the correct epoch value.
 * 4. Verify that the get_cycle() method returns the correct cycle value.
 * 5. Verify that the get_type() method returns the string "evaluation".
 * 6. Retrieve the data from the entry using the get_data() method.
 * 7. Verify that the first element of the data pair is the correct score name.
 * 8. Verify that the second element of the data pair is the correct score value.
 */
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

/**
 * @brief Unit test for the EvaluationLogEntry constructor with different score values.
 *
 * This test verifies that the EvaluationLogEntry constructor correctly initializes
 * the object with the provided epoch, cycle, score name, and score value. It checks
 * that the epoch, cycle, and type are correctly set and that the data contains the
 * correct score name and score value.
 *
 * @param None
 * @return None
 */
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