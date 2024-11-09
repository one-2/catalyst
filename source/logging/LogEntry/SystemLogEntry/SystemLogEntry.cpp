#include <CL/cl.h>

#include "./SystemLogEntry.h"

#include <fstream>
#include <sstream>
#include <memory>

namespace logging {

/**
 * @brief Constructs a new SystemLogEntry object.
 * 
 * @param epoch The epoch time at which the log entry is created.
 * @param cycle The cycle count associated with the log entry.
 * 
 * @note Calls base class constructor.
 */
SystemLogEntry::SystemLogEntry(
    int epoch,
    int cycle
) : LogEntry(
    epoch,
    cycle, 
    build_usage(), // NOTE: Bad signatures in header propagate type errors from called functions to caller
    "system"
) {}


/**
 * @brief Constructs a Logdata object containing system usage information.
 *
 * This function retrieves the current CPU, memory, and GPU usage, formats
 * them into a human-readable string, and returns a Logdata object with
 * the usage information.
 *
 * @return Logdata object containing the system usage information.
 */
Logdata SystemLogEntry::build_usage()
{
    float cpu_usage = get_cpu_usage();
    float mem_usage = get_mem_usage();
    float gpu_usage = get_gpu_usage();

    std::string message = "CPU:\t\t" + std::to_string(cpu_usage) + "%, "
                        + "RAM:\t" + std::to_string(mem_usage) + "MB, "
                        + "GPU:\t\t" + std::to_string(gpu_usage) + "MB";

    return Logdata("usage", message);
}


/**
 * @brief Retrieves the current CPU usage percentage.
 *
 * This function reads the CPU statistics from the /proc/stat file and calculates
 * the CPU usage percentage based on the user, nice, system, and idle times.
 *
 * @return float The CPU usage percentage.
 *
 * @throws std::runtime_error If the /proc/stat file cannot be opened or if the CPU usage information cannot be parsed.
 */
float get_cpu_usage()
{
    std::ifstream stat_file("/proc/stat");
    if (!stat_file.is_open()) {
        throw std::runtime_error("Failed to open /proc/stat");
    }

    std::string line;
    std::getline(stat_file, line);  // first line contains CPU stats

    unsigned long long user = 0, nice = 0, system = 0, idle = 0;
    std::sscanf(line.c_str(), "cpu  %llu %llu %llu %llu", &user, &nice, &system, &idle);

    if (user == 0 && nice == 0 && system == 0 && idle == 0) {
        throw std::runtime_error("Failed to parse CPU usage information");
    }

    return static_cast<float>(user + nice + system) / (user + nice + system + idle) * 100.0f;  // return CPU usage percentage
}


/**
 * @brief Retrieves the current memory usage of the system.
 *
 * This function reads the memory information from the /proc/meminfo file
 * and calculates the used memory in megabytes (MB).
 *
 * @return float The used memory in MB.
 *
 * @throws std::runtime_error If the /proc/meminfo file cannot be opened or
 *         if the memory usage information cannot be parsed.
 */
float get_mem_usage()
{
    std::ifstream meminfo("/proc/meminfo");
    if (!meminfo.is_open()) {
        throw std::runtime_error("Failed to open /proc/meminfo");
    }

    std::string line;
    unsigned long total = 0, available = 0;
    bool total_found = false, available_found = false;

    while (std::getline(meminfo, line)) {
        if (line.find("MemTotal:") == 0) {
            std::sscanf(line.c_str(), "MemTotal: %lu kB", &total);
            total_found = true;
        } else if (line.find("MemAvailable:") == 0) {
            std::sscanf(line.c_str(), "MemAvailable: %lu kB", &available);
            available_found = true;
        }

        if (total_found && available_found) {
            break;
        }
    }

    if (!total_found || !available_found) {
        throw std::runtime_error("Failed to parse memory usage information");
    }

    return (total - available) / 1024.0;  // return used memory in MB
}


/**
 * @brief Retrieves the GPU usage by querying the OpenCL platform and device information.
 * 
 * This function uses the OpenCL API to get the number of platforms and devices available,
 * and then retrieves the global memory size of the first GPU device found. The memory size
 * is returned in megabytes (MB).
 * 
 * @return float The total global memory size of the first GPU device in MB.
 * 
 * @throws std::runtime_error If any OpenCL API call fails, an exception is thrown with an appropriate error message.
 */
float get_gpu_usage()
{
    cl_uint num_platforms;
    cl_int err = clGetPlatformIDs(0, nullptr, &num_platforms);
    if (err != CL_SUCCESS) {
        throw std::runtime_error("Failed to get OpenCL platforms");
    }

    std::vector<cl_platform_id> platforms(num_platforms);
    err = clGetPlatformIDs(num_platforms, platforms.data(), nullptr);
    if (err != CL_SUCCESS) {
        throw std::runtime_error("Failed to get OpenCL platform IDs");
    }

    cl_uint num_devices;
    err = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_GPU, 0, nullptr, &num_devices);
    if (err != CL_SUCCESS) {
        throw std::runtime_error("Failed to get OpenCL devices");
    }

    std::vector<cl_device_id> devices(num_devices);
    err = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_GPU, num_devices, devices.data(), nullptr);
    if (err != CL_SUCCESS) {
        throw std::runtime_error("Failed to get OpenCL device IDs");
    }

    cl_ulong mem_size;
    err = clGetDeviceInfo(devices[0], CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(mem_size), &mem_size, nullptr);
    if (err != CL_SUCCESS) {
        throw std::runtime_error("Failed to get OpenCL device memory size");
    }

    err = clGetDeviceInfo(devices[0], CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(mem_size), &mem_size, nullptr);
    if (err != CL_SUCCESS) {
        throw std::runtime_error("Failed to get OpenCL device memory size");
    }

    // Assuming the GPU memory usage is not directly available, we return the total memory size
    return static_cast<float>(mem_size) / 1024.0 / 1024.0;  // return total memory in MB
}

}