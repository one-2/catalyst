// source/LogEntry/LogEntry.h
//
// Author: Stephen Elliott
//
// Date: 2024-10-31
//
// Description: 
//
// Usage: 
//

#ifndef LOGENTRY_H
#define LOGENTRY_H

#include <string>
#include <list>
#include <variant>
#include <chrono>
#include <memory>
#include <map>
#include <cereal/archives/json.hpp>

struct Datum {
    std::string key;
    std::string value;
};

typedef std::list<Datum> DataList;
typedef std::chrono::time_point<std::chrono::system_clock> TimeStamp;

class LogEntry {
public:
    LogEntry(const int& epoch, const int& cycle, const DataList& data);
    LogEntry(TimeStamp& timestamp, int& epoch, int& cycle, DataList& data);

    const std::string serialise() const;
    static const std::unique_ptr<LogEntry> deserialise(const std::string& data);

    const TimeStamp get_timestamp() const;
    const int get_epoch() const;
    const int get_cycle() const;
    const DataList get_all_data() const;

protected:
    TimeStamp timestamp;
    int epoch;
    int cycle;
    DataList data;

    std::string serialise_datum(Datum datum) const;
};

#endif // LOGENTRY_H
