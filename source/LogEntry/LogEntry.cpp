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
using namespace datastores;

LogEntry::LogEntry(int epoch, int cycle, std::shared_ptr<IDataList> data, std::string type) {
    this->epoch_ = epoch;
    this->cycle_ = cycle;
    this->data_ = data;
    this->timestamp_ = std::chrono::system_clock::now();
    this->type_ = type;
}

LogEntry::LogEntry(TimeStamp timestamp, int epoch, int cycle, std::shared_ptr<IDataList> data, std::string type) {
    this->timestamp_ = timestamp;
    this->epoch_ = epoch;
    this->cycle_ = cycle;
    this->data_ = data;
    this->type_ = type;
}

const TimeStamp LogEntry::get_timestamp() const {
    return timestamp_;
}

const int LogEntry::get_epoch() const {
    return epoch_;
}

const int LogEntry::get_cycle() const {
    return cycle_;
}
const std::shared_ptr<IDataList> LogEntry::get_data() const {
    return data_;
}

const std::string LogEntry::get_type() const {
    return type_;
}

std::unique_ptr<LogEntry> LogEntry::deserialize(const std::string& data, bool is_binary) {
    std::istringstream is(data);
    auto logEntry = std::make_unique<LogEntry>();
    if (is_binary) {
        cereal::BinaryInputArchive archive(is);
        archive(cereal::make_nvp("logEntry", *logEntry));
        archive(*logEntry);
        return logEntry;
    } else {
        cereal::JSONInputArchive archive(is);
        archive(*logEntry);
        return logEntry;
    }
}
