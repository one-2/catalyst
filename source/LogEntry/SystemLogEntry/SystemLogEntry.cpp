

#include <utility>



SystemLogEntry::SystemLogEntry()
{

}

SystemLogEntry::std::pair<float, float> get_interval_system_usage()
{

}

SystemLogEntry::float get_cpu_usage()
{

}

SystemLogEntry::float get_mem_usage()
{

}

SystemLogEntry::float get_gpu_usage()
{

}




// double LogBook::get_cpu_usage() const {
//     std::ifstream stat_file("/proc/stat");
//     std::string line;
//     std::getline(stat_file, line);  //first line contains CPU stats
//     unsigned long long user, nice, system, idle;
//     std::sscanf(line.c_str(), "cpu  %llu %llu %llu %llu", &user, &nice, &system, &idle);
//     return user + nice + system;  //return sum of work times
// }

// double LogBook::get_mem_usage() const {
//     std::ifstream meminfo("/proc/meminfo");
//     std::string line;
//     unsigned long total, available;
//     while (std::getline(meminfo, line)) {
//         if (line.find("MemTotal:") == 0) {
//             std::sscanf(line.c_str(), "MemTotal: %lu kB", &total);
//         } else if (line.find("MemAvailable:") == 0) {
//             std::sscanf(line.c_str(), "MemAvailable: %lu kB", &available);
//             break;
//         }
//     }
//     return (total - available) / 1024.0;  //return used memory in MB
// }