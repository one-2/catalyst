
#include "./SystemLogEntry.h"
#include <fstream>
#include <sstream>

using namespace logging;
using namespace datastores;

std::string type = "system";

SystemLogEntry::SystemLogEntry(int epoch, int cycle) : LogEntry(epoch, cycle, build_usage(), type) {}

DataList SystemLogEntry::build_usage()
{
    Datum cpu_usage("cpu_usage", get_cpu_usage());
    Datum mem_usage("mem_usage", get_mem_usage());
    Datum gpu_usage("gpu_usage", get_gpu_usage());
    std::list<Datum> usage = {cpu_usage, mem_usage, gpu_usage};
    return DataList(usage);
}

const float SystemLogEntry::get_cpu_usage()
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

const float SystemLogEntry::get_mem_usage()
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

const float SystemLogEntry::get_gpu_usage()
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
