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
#include "DataList/DataList.h"
#include "LogEntry/Datum/Datum.h" // NOTE: Confusingly, include errors propogate.

typedef std::chrono::time_point<std::chrono::system_clock> TimeStamp;

class LogEntry {
public:
    // Friend class to access private constructor
    friend class DataList;

    // Getters
    const std::string get_type() const;
    const TimeStamp get_timestamp() const;
    const int get_epoch() const;
    const int get_cycle() const;
    const DataList get_all_data() const;

    // Serialisation
    const std::string serialise() const;
    static const std::unique_ptr<LogEntry> deserialise(const std::string data);

protected:
    // Protected constructor
    // For subclass instantiation subroutine.
    LogEntry(int& epoch, int& cycle, DataList data, std::string& type);

    // Protected attributes
    TimeStamp timestamp_;
    int epoch_;
    int cycle_;
    DataList data_;
    std::string type_;

private:
    // Private constructor
    // For deserialisation subroutine.
    LogEntry(TimeStamp timestamp, int epoch, int cycle, DataList data, std::string type);
    //
    // NOTE: Wow! Static methods can call private constructors - surreal.
    //
};

#endif // LOGENTRY_H
