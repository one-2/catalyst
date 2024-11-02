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
#include "datastores/DataList.h"
#include "datastores/Datum.h" // NOTE: Confusingly, include errors propogate.
#include "datastores/IDataList.h"

using namespace datastores;

namespace logging { // NOTE: Namespaces are not inherited.

typedef std::chrono::time_point<std::chrono::system_clock> TimeStamp;

class LogEntry {
public:
    // Friend class to access private constructor
    friend class IDataList;

    // Getters
    const std::string get_type() const;
    const TimeStamp get_timestamp() const;
    const int get_epoch() const;
    const int get_cycle() const;
    const std::shared_ptr<IDataList> get_data() const;

    // // Serialisation
    // template <class Archive>
    // void serialize(Archive& ar) {
    //     ar(CEREAL_NVP(timestamp_), CEREAL_NVP(epoch_)
    //         , CEREAL_NVP(cycle_), CEREAL_NVP(type_)
    //         , CEREAL_NVP(data_));
    // }

    // // Static method for deserialization
    // static std::unique_ptr<LogEntry> deserialize(const std::string& data, bool is_binary = false);


protected:
    // Protected constructor For subclass instantiation subroutine.
    LogEntry(int epoch, int cycle, std::shared_ptr<IDataList> data, std::string type);

    // Protected attributes
    TimeStamp timestamp_;
    int epoch_;
    int cycle_;
    std::shared_ptr<IDataList> data_;
    std::string type_;

private:
    // Private default constructor
    // For deserialisation subroutine.
    // LogEntry() = default;
    LogEntry(TimeStamp timestamp, int epoch, int cycle, std::shared_ptr<IDataList> data, std::string type);
    

    //
    // NOTE: Wow! Static methods can call private constructors - surreal.
    //

    // // Grant Cereal access to private members
    // friend class cereal::access;
};
}

#endif // LOGENTRY_H
