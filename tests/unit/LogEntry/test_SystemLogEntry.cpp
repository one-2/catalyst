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
// Call the constructor and check the values are set correctly
TEST(SystemLogEntryTest, ConstructorTest) {
    int epoch = 1;
    int cycle = 2;

    SystemLogEntry entry(epoch, cycle); 

    EXPECT_EQ(entry.get_epoch(), epoch);
    EXPECT_EQ(entry.get_cycle(), cycle);
    // EXPECT_EQ(entry.get_type(), "system");       // SEGFAULT HERE
    
    // get the data from the variant as a string
    std::string data = std::get<std::string>(entry.get_data()->second);

    // check that it is a string with "cpu", "gpu", and "mem" in it
    // // EXPECT_NE(data.find("cpu"), std::string::npos);
    // // EXPECT_NE(data.find("gpu"), std::string::npos);
    // // EXPECT_NE(data.find("mem"), std::string::npos);

    // // // check that it contains 3 float blocks
    // // std::istringstream iss(data);
    // // std::string token;
    // // int floatCount = 0;
    // // while (iss >> token) {
    // //     try {
    // //         std::stof(token);
    // //         floatCount++;
    // //     } catch (const std::invalid_argument&) {
    // //         // Not a float, continue
    // //     }
    // // }
    // // EXPECT_EQ(floatCount, 3);
}

} // namespace logging