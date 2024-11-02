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
#include "LogEntry/LogEntry.h"

using namespace logging;
using namespace datastores;

LogEntry::LogEntry(int epoch, int cycle, DataList data, std::string type) {
    this->epoch_ = epoch;
    this->cycle_ = cycle;
    this->data_ = data;
    this->timestamp_ = std::chrono::system_clock::now();
    this->type_ = type;
}

const std::string LogEntry::serialise() const {
    // Using cereal
    // Serialise the datalist
    // serialise all attributes
    // return the serialised string
    std::stringstream ss;
    {
        cereal::JSONOutputArchive archive(ss);
        int64_t timestamp_count = timestamp_.time_since_epoch().count();
        archive(cereal::make_nvp("timestamp", timestamp_count),
                cereal::make_nvp("epoch", epoch_),
                cereal::make_nvp("cycle", cycle_),
                cereal::make_nvp("type", type_));
        for (const Datum datum : data_) {
            std::string serialisedDatum = datum.serialise_datum();
            archive(cereal::make_nvp("datum", serialisedDatum));
        }
    }
    return ss.str();

}

const LogEntry LogEntry::deserialise(std::string& data) {
    // Deserialise the file and Call LogEntry(TimeStamp timestamp, int epoch, int cycle, DataList data)
    std::stringstream ss(data);
    cereal::JSONInputArchive archive(ss);

    int64_t timestamp_count;
    int epoch, cycle;
    std::string type;

    archive(cereal::make_nvp("timestamp", timestamp_count),
            cereal::make_nvp("epoch", epoch),
            cereal::make_nvp("cycle", cycle),
            cereal::make_nvp("type", type));
    TimeStamp timestamp = std::chrono::system_clock::time_point(std::chrono::milliseconds(timestamp_count));
    DataList data_list;
    while (!ss.eof()) {
        std::string key, value;
        archive(cereal::make_nvp("datum", key), cereal::make_nvp("datum", value));
        data_list.add_datum(key, value);
    }
    return LogEntry(timestamp, epoch, cycle, data_list, type);
}

LogEntry::LogEntry(TimeStamp timestamp, int epoch, int cycle, DataList data, std::string type) {
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
    return const_cast<const decltype(epoch_)&>(epoch_);
}

const int LogEntry::get_cycle() const {
    return const_cast<const decltype(cycle_)&>(cycle_);
}

const DataList LogEntry::get_all_data() const {
    return const_cast<const decltype(data_)&>(data_);
}

const std::string LogEntry::get_type() const {
    return const_cast<const decltype(type_)&>(type_);
}
