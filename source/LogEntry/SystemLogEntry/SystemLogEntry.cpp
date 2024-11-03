
#include "./SystemLogEntry.h"
#include <fstream>
#include <sstream>
#include <memory>
#include <CL/cl.h>

namespace logging {

SystemLogEntry::SystemLogEntry(
    int epoch,
    int cycle
) : LogEntry(
    epoch,
    cycle, 
    build_usage(), // NOTE: Bad signatures in header propagate type errors from called functions to caller
    "system"
) {}

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