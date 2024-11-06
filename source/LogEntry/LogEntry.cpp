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

#include "LogEntry.h"
#include <sstream>

namespace logging {

/**
 * @brief Constructs a new LogEntry object.
 * 
 * @param epoch The epoch time associated with the log entry.
 * @param cycle The cycle number associated with the log entry.
 * @param data The log data associated with the log entry.
 * @param type The type of the log entry.
 */
LogEntry::LogEntry(int epoch, int cycle, Logdata data, std::string type) {
    this->timestamp = std::chrono::system_clock::now();
    this->epoch = epoch;
    this->cycle = cycle;
    this->data = data;
    this->type = type;
}

/**
 * @brief Retrieves the timestamp of the log entry.
 * 
 * @return TimeStamp The timestamp associated with the log entry.
 */
TimeStamp LogEntry::get_timestamp() const {
    return timestamp;
}

/**
 * @brief Retrieves the epoch time of the log entry.
 * 
 * @return int The epoch time associated with the log entry.
 */
int LogEntry::get_epoch() const {
    return epoch;
}

/**
 * @brief Retrieves the cycle value of the LogEntry.
 * 
 * @return int The cycle value.
 */
int LogEntry::get_cycle() const {
    return cycle;
}

/**
 * @brief Retrieves a shared pointer to a constant Logdata object.
 *
 * @return std::shared_ptr<const Logdata> A shared pointer to a constant Logdata object.
 */
std::shared_ptr<const Logdata> LogEntry::get_data() const {
    return std::shared_ptr<const Logdata>(new Logdata(data));
}

/**
 * @brief Retrieves the type of the log entry.
 * 
 * @return std::string The type of the log entry.
 */
std::string LogEntry::get_type() const {
    return type;
}

/**
 * @brief Deserializes a JSON string into a LogEntry object.
 *
 * This function takes a JSON string representation of a LogEntry object,
 * deserializes it using the Cereal library, and returns the resulting LogEntry object.
 *
 * @param json_str The JSON string to deserialize.
 * @return A LogEntry object deserialized from the JSON string.
 */
LogEntry LogEntry::deserialize_logentry(const std::string& json_str) {
    std::istringstream iss(json_str);
    cereal::JSONInputArchive archive(iss);
    LogEntry log_entry;
    archive(log_entry);
    return log_entry;
}

} // namespace logging