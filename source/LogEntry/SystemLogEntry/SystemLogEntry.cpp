
#include "./SystemLogEntry.h"
#include <fstream>
#include <sstream>
#include <memory>

std::string type = "system";

namespace logging {
SystemLogEntry::SystemLogEntry(int epoch, int cycle)
    : LogEntry(
        epoch,
        cycle, 
        build_usage(), // NOTE: Bad signatures in header propagate type errors from called functions to caller
        type
    ) {}

Logdata SystemLogEntry::build_usage()
{
    float cpu_usage = get_cpu_usage();
    float mem_usage = get_mem_usage();
    float gpu_usage = get_gpu_usage();

    std::string message = "CPU:\t\t" + std::to_string(cpu_usage) + "%, "
                        + "Memory:\t" + std::to_string(mem_usage) + "MB, "
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
    std::ifstream gpuinfo("/proc/gpuinfo");
    if (!gpuinfo.is_open()) {
        throw std::runtime_error("Failed to open /proc/gpuinfo");
    }

    std::string line;
    unsigned long total = 0, available = 0;
    bool total_found = false, available_found = false;

    while (std::getline(gpuinfo, line)) {
        if (line.find("GPU Total:") == 0) {
            std::sscanf(line.c_str(), "GPU Total: %lu kB", &total);
            total_found = true;
        } else if (line.find("GPU Available:") == 0) {
            std::sscanf(line.c_str(), "GPU Available: %lu kB", &available);
            available_found = true;
        }

        if (total_found && available_found) {
            break;
        }
    }

    if (!total_found || !available_found) {
        throw std::runtime_error("Failed to parse GPU usage information");
    }

    return (total - available) / 1024.0;  // return used memory in MB
}
} // namespace logging