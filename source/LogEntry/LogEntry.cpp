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

#include <cereal/archives/json.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/memory.hpp>
#include <sstream>
#include <fstream>
#include <cereal/archives/binary.hpp>
#include "LogEntry/LogEntry.h"

using namespace logging;

LogEntry::LogEntry(int epoch, int cycle, std::shared_ptr<Logdata> data, std::string type) {
    this->timestamp = std::chrono::system_clock::now();
    this->epoch = epoch;
    this->cycle = cycle;
    this->data = data;
    this->type = type;
}

LogEntry::LogEntry(TimeStamp timestamp, int epoch, int cycle, Logdata data, std::string type) {
    this->timestamp = timestamp;
    this->epoch = epoch;
    this->cycle = cycle;
    this->data = std::shared_ptr<Logdata>(new Logdata(data));
    this->type = type;
}

TimeStamp LogEntry::get_timestamp() const {
    return timestamp;
}

int LogEntry::get_epoch() const {
    return epoch;
}

int LogEntry::get_cycle() const {
    return cycle;
}

std::shared_ptr<const Logdata> LogEntry::get_data() const {
    Logdata copy = *data;
    return std::shared_ptr<const Logdata>(new Logdata(*data));
}

std::string LogEntry::get_type() const {
    return type;
}

// std::unique_ptr<LogEntry> LogEntry::deserialize(const std::string& data, bool is_binary) {
//     std::istringstream is(data);
//     auto logEntry = std::make_unique<LogEntry>();
//     if (is_binary) {
//         cereal::BinaryInputArchive archive(is);
//         archive(cereal::make_nvp("logEntry", *logEntry));
//         archive(*logEntry);
//         return logEntry;
//     } else {
//         cereal::JSONInputArchive archive(is);
//         archive(*logEntry);
//         return logEntry;
//     }
// }
