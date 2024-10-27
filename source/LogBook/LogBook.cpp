// source/LogBook/LogBook.c
//
// Author: Stephen Elliott
//
// Date: 2024-10-27
//
// Description: 
//
// Usage: 
//
#include "LogBook.h"

/// @brief LogBook constructor
/// @param name 
/// @param storage_directory 
LogBook::LogBook(const std::string& name, const std::string& storage_directory) 
    : storage_directory(storage_directory) {
    // TODO
}

/// @brief Writes a log to the parent LogBook.
/// @param type 
/// @param info 
/// @return 
std::string LogBook::write_log(const std::string& type, std::list<Info> info) {
    LogEntry log_entry;
    log_entry.timestamp = std::chrono::system_clock::now();
    log_entry.type = type;
    log_entry.info = info;

    std::string serialised_log = serialise_log(log_entry);

    if (type == "system") {
        system_logs.push_back(serialised_log);
    } else if (type == "model_checkpoint") {
        model_checkpoints.push_back(serialised_log);
    } else if (type == "exception") {
        exception_logs.push_back(serialised_log);
    } else if (type == "debug") {
        debug_logs.push_back(serialised_log);
    }

    return serialised_log;
}

/// @brief Reads all logs of a given type from the logbook
/// @param type 
/// @return 
std::list<std::string> LogBook::read_log_type(const std::string& type) const {
    if (type == "system") {
        return system_logs;
    } else if (type == "model_checkpoint") {
        return model_checkpoints;
    } else if (type == "exception") {
        return exception_logs;
    } else if (type == "debug") {
        return debug_logs;
    }
    return std::list<std::string>();
}

/// @brief Serialises a log using Protobuf
/// @param log 
/// @return 
std::string LogBook::serialise_log(const LogEntry log) {
    // TODO
    return "";
}

// Deserialises a log using Protobuf
LogEntry LogBook::deserialise_log(const std::string) {
    // TODO
    return LogEntry();
}
