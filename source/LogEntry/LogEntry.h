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
#include <memory>
#include <chrono>
#include <variant>
#include <cereal/archives/json.hpp>
#include <cereal/archives/binary.hpp> // Include this header for BinaryOutputArchive
#include <cereal/types/memory.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/variant.hpp> // Include this header for variant support
#include <cereal/types/chrono.hpp>

namespace logging {

typedef std::chrono::system_clock::time_point TimeStamp;
typedef std::pair<std::string, std::variant<int, long, float, double, std::string>> Logdata;

class LogEntry {
public:
    LogEntry(int epoch, int cycle, Logdata data, std::string type);
    LogEntry() = default; // Default constructor for deserialization

    TimeStamp get_timestamp() const;
    int get_epoch() const;
    int get_cycle() const;
    std::shared_ptr<const Logdata> get_data() const;
    std::string get_type() const;

    // Serialization
    template <class Archive>
    void serialize(Archive& ar)
    {
        ar(CEREAL_NVP(timestamp), CEREAL_NVP(epoch), CEREAL_NVP(cycle), CEREAL_NVP(data), CEREAL_NVP(type));
    }

    std::string to_json() const {
        std::ostringstream os;
        {
            cereal::JSONOutputArchive archive(os);
            archive(cereal::make_nvp("log_entry", *this));
        }
        return os.str();
    }

protected:
    TimeStamp timestamp;
    int epoch;
    int cycle;
    Logdata data;
    std::string type = "LogEntry";

private:
    // Grant Cereal access to private members
    friend class cereal::access;
};

// Serialization function for Logdata
template <class Archive>
void serialize(Archive& ar, Logdata& logdata) {
    ar(CEREAL_NVP(logdata.first), CEREAL_NVP(logdata.second));
}

LogEntry deserialize_logentry(const std::string& json_str);

} // namespace logging

#endif // LOGENTRY_H