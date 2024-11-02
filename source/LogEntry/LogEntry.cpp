// source/LogEntry/LogEntry.cpp
//
// Author: Stephen Elliott
//
// Date: 2024-10-31
//
// Description: 
//
// Usage: 
//

#include "LogEntry.h"
#include <sstream>

namespace logging {

LogEntry::LogEntry(int epoch, int cycle, Logdata data, std::string type) {
    this->timestamp = std::chrono::system_clock::now().time_since_epoch().count();
    this->epoch = epoch;
    this->cycle = cycle;
    this->data = data;
    this->type = type;
}

int LogEntry::get_timestamp() const {
    return timestamp;
}

int LogEntry::get_epoch() const {
    return epoch;
}

int LogEntry::get_cycle() const {
    return cycle;
}

std::shared_ptr<const Logdata> LogEntry::get_data() const {
    return std::shared_ptr<const Logdata>(new Logdata(data));
}

std::string LogEntry::get_type() const {
    return type;
}

LogEntry deserialize_logentry(const std::string& json_str) {
    std::istringstream iss(json_str);
    cereal::JSONInputArchive archive(iss);
    LogEntry log_entry;
    archive(log_entry);
    return log_entry;
}

} // namespace logging