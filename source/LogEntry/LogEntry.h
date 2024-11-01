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
    const std::string get_type() const;
    const TimeStamp get_timestamp() const;
    const int get_epoch() const;
    const int get_cycle() const;
    const DataList get_all_data() const;

    // Serialisation functions
    const std::string serialise() const;
    static const std::unique_ptr<LogEntry> deserialise(const std::string data);

protected:
    // Protected constructors
    // Prevents the class from being instantiated, except by deserialise() and subclasses.
    LogEntry(const int epoch, const int cycle, const DataList data, std::string type);
    LogEntry(TimeStamp timestamp, int epoch, int cycle, DataList data, std::string type);

    TimeStamp timestamp_;
    int epoch_;
    int cycle_;
    DataList data_;
    std::string type_;

    std::string serialise_datum(Datum datum) const;
};

#endif // LOGENTRY_H
