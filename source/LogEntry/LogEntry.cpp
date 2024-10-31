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

#include "./LogEntry.h"

#include <cereal/archives/json.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/memory.hpp>
#include <sstream>
#include <fstream>

LogEntry::LogEntry(const int& epoch, const int& cycle, const DataList& data, std::string type) {
    this->epoch = epoch;
    this->cycle = cycle;
    this->data = data;
    this->timestamp = std::chrono::system_clock::now();
    this->type = type;
}

const std::string LogEntry::serialise() const {
    // Using cereal
    // Serialise the datalist
    // serialise all attributes
    // return the serialised string
    std::stringstream ss;
    {
        cereal::JSONOutputArchive archive(ss);
        int64_t timestamp_count = timestamp.time_since_epoch().count();
        archive(cereal::make_nvp("timestamp", timestamp_count),
                cereal::make_nvp("epoch", epoch),
                cereal::make_nvp("cycle", cycle),
                cereal::make_nvp("type", type));
        for (const auto& datum : data) {
            std::string serialisedDatum = serialise_datum(datum);
            archive(cereal::make_nvp("datum", serialisedDatum));
        }
    }
    return ss.str();

}

const std::unique_ptr<LogEntry> LogEntry::deserialise(const std::string& data) {
    // Deserialise the file and Call LogEntry(TimeStamp& timestamp, int epoch, int cycle, DataList data)
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
        data_list.push_back(Datum{key, value});
    }
    return std::make_unique<LogEntry>(timestamp, epoch, cycle, data_list, type);
}

LogEntry::LogEntry(TimeStamp& timestamp, int& epoch, int& cycle, DataList& data, std::string type) {
    this->timestamp = timestamp;
    this->epoch = epoch;
    this->cycle = cycle;
    this->data = data;
    this->type = type;
}

const TimeStamp LogEntry::get_timestamp() const {
    return timestamp;
}

const int LogEntry::get_epoch() const {
    return epoch;
}

const int LogEntry::get_cycle() const {
    return cycle;
}

const DataList LogEntry::get_all_data() const {
    return data;
}

std::string LogEntry::serialise_datum(Datum datum) const {
    std::stringstream ss;
    {
        cereal::JSONOutputArchive archive(ss);
        archive(cereal::make_nvp("key", datum.key),
                cereal::make_nvp("value", datum.value));
    }
    return ss.str();
}

const std::string LogEntry::get_type() const {
    return type;
}