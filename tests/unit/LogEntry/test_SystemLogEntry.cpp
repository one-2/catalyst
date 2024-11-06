// source/LogEntry/SystemLogEntry/test_SystemLogEntry.cpp
//
// Author: Stephen Elliott
//
// Date: 2024-10-31
//
// Description: Tests for SystemLogEntry class
//

#include <gtest/gtest.h>
#include "LogEntry/SystemLogEntry/SystemLogEntry.h"
#include <fstream>


namespace logging {

/**
 * @brief Unit test for the SystemLogEntry class constructor.
 *
 * This test verifies that the SystemLogEntry constructor correctly initializes
 * the epoch and cycle values, sets the type to "system", and ensures that the
 * data contains the strings "CPU", "RAM", and "GPU". Additionally, it checks
 * that the data contains exactly three float values.
 *
 * @test
 * - Creates a SystemLogEntry object with epoch and cycle values.
 * - Verifies that the epoch and cycle values are correctly set.
 * - Verifies that the type is set to "system".
 * - Extracts the data from the entry and checks that it contains the strings
 *   "CPU", "RAM", and "GPU".
 * - Parses the data to count the number of float values and verifies that there
 *   are exactly three float values.
 */
TEST(SystemLogEntryTest, ConstructorTest) {
    int epoch = 1;
    int cycle = 2;

    SystemLogEntry entry(epoch, cycle); 

    EXPECT_EQ(entry.get_epoch(), epoch);
    EXPECT_EQ(entry.get_cycle(), cycle);
    EXPECT_EQ(entry.get_type(), "system");
    
    // get the data from the variant as a string
    std::string data = std::get<std::string>(entry.get_data()->second);

    // check that it is a string with "CPU", "RAM", and "GPU" in it
    using namespace std;
    cout << data << endl;
    EXPECT_NE(data.find("CPU"), std::string::npos);
    EXPECT_NE(data.find("RAM"), std::string::npos);
    EXPECT_NE(data.find("GPU"), std::string::npos);

    // check that it contains 3 float blocks
    std::istringstream iss(data);
    std::string token;
    int floatCount = 0;
    while (iss >> token) {
        try {
            std::stof(token);
            floatCount++;
        } catch (const std::invalid_argument&) {
            // Not a float, continue
        }
    }
    EXPECT_EQ(floatCount, 3);
}

} // namespace logging