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

class SystemLogEntryTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a mock /proc/gpuinfo file for testing
        std::ofstream gpuinfo("/tmp/gpuinfo");
        gpuinfo << "GPU Total: 8192 kB\n";
        gpuinfo << "GPU Available: 4096 kB\n";
        gpuinfo.close();
    }

    void TearDown() override {
        // Remove the mock /proc/gpuinfo file after testing
        std::remove("/tmp/gpuinfo");
    }
};

TEST_F(SystemLogEntryTest, GetGpuUsage) {
    // Redirect the file path to the mock file
    std::ifstream gpuinfo("/tmp/gpuinfo");
    ASSERT_TRUE(gpuinfo.is_open());

    SystemLogEntry log_entry(1, 2);
    float gpu_usage = logging::get_gpu_usage();

    EXPECT_FLOAT_EQ(gpu_usage, 4096.0f / 1024.0f);  // 4096 kB used, should be 4 MB
}

TEST_F(SystemLogEntryTest, GetGpuUsageFileNotFound) {
    // Remove the mock file to simulate file not found
    std::remove("/tmp/gpuinfo");

    SystemLogEntry log_entry(1, 2);
    EXPECT_THROW(logging::get_gpu_usage(), std::runtime_error);
}

TEST_F(SystemLogEntryTest, GetGpuUsageParseError) {
    // Create a malformed /proc/gpuinfo file for testing
    std::ofstream gpuinfo("/tmp/gpuinfo");
    gpuinfo << "Malformed data\n";
    gpuinfo.close();

    SystemLogEntry log_entry(1, 2);
    EXPECT_THROW(logging::get_gpu_usage(), std::runtime_error);
}

} // namespace logging