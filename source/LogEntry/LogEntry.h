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
// NOTE: Confusingly, include errors propogate.

namespace logging { // NOTE: Namespaces are not inherited.

typedef std::chrono::time_point<std::chrono::system_clock> TimeStamp;
typedef std::pair<std::string, std::variant<int, long, float, double, std::string>> Logdata;

class LogEntry {
public:
    LogEntry(int epoch, int cycle, std::shared_ptr<Logdata> data, std::string type);
    LogEntry(TimeStamp timestamp, int epoch, int cycle, std::shared_ptr<Logdata> data, std::string type);

    const std::string serialise() const;
    static const std::unique_ptr<LogEntry> deserialise(const std::string& data);

    const TimeStamp get_timestamp() const;
    const int get_epoch() const;
    const int get_cycle() const;
    const std::list<std::string, Logdata> get_data() const;

    // // Serialisation
    // template <class Archive>
    // void serialize(Archive& ar) {
    //     ar(CEREAL_NVP(timestamp_), CEREAL_NVP(epoch_)
    //         , CEREAL_NVP(cycle_), CEREAL_NVP(type_)
    //         , CEREAL_NVP(data_));
    // }

    // // Static method for deserialization
    // static std::unique_ptr<LogEntry> deserialize(const std::string& data, bool is_binary = false);

    const std::string get_type() const;

protected:
    TimeStamp timestamp;
    int epoch;
    int cycle;
    Logdata data;
    std::string type = "LogEntry";

private:
    // Private default constructor
    // For deserialisation subroutine.
    // LogEntry() = default;
    LogEntry(TimeStamp timestamp, int epoch, int cycle, std::shared_ptr<Logdata> data, std::string type);
    

    //
    // NOTE: Wow! Static methods can call private constructors - surreal.
    //

    // // Grant Cereal access to private members
    // friend class cereal::access;
};
}

#endif // LOGENTRY_H
