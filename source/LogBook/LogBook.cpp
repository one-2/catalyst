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

#include <list>
#include <string>
#include "../io/io.h"

/// @brief LogBook constructor
/// @param name 
/// @param storage_directory 
LogBook::LogBook(const std::string& storage_directory)
    : storage_directory(storage_directory), system_logs(), //Empty init => uses the default constructor
    model_checkpoints(), debug_logs() {
        auto generate_path = [storage_directory](std::string subdir_name) {
            return storage_directory + "/" + subdir_name;
        };
        this->system_logs_directory = generate_path("system_logs");
        this->checkpoint_directory = generate_path("checkpoints");
        this->debug_directory = generate_path("debug_logs");
}

/// @brief Writes a log to the parent LogBook.
/// @param type 
/// @param info 
/// @return 
std::string LogBook::log_info(const int& type, const std::list<Info>& info) {
    LogEntry log_entry;
    log_entry.timestamp = std::chrono::system_clock::now();
    log_entry.type = type;
    log_entry.info = info;

    std::string serialised_log = serialise_log(log_entry);
    std::string path;

    switch (type) {
        case SYSTEM:
            path = io::write_log(serialised_log, system_logs_directory);
            system_logs.push_back(path);
            break;
        case CHECKPOINT:
            path = io::write_log(serialised_log, checkpoint_directory);
            model_checkpoints.push_back(path);
            break;
        case DEBUG:
            path = io::write_log(serialised_log, debug_directory);
            debug_logs.push_back(path);
            break;
    }

    return path;
}

/// @brief Reads all logs of a given type from the logbook
/// @param type 
/// @return 
std::list<LogEntry> LogBook::read_log_type(const int& type) const {
    std::list<std::string> log_paths;

    // Get log paths
    switch (type) {
        case SYSTEM:
            log_paths = system_logs;
            break;
        case CHECKPOINT:
            log_paths = model_checkpoints;
            break;
        case DEBUG:
            log_paths = debug_logs;
            break;
        default:
            throw "Invalid log category selected.";
    }

    // Deserialise logs
    std::list<LogEntry> logs;
    for (auto path : log_paths) {
        logs.push_back(deserialise_log(path));
    }
    
    return logs;
}

/// @brief Logs a Model into a checkpoint file
/// @param model 
/// @return 
std::string LogBook::log_checkpoint(const Model& model) {
    // Model.serialise
    // Create log
    // Log.serialise
    return "";
}



/// @brief Serialises a log into json or binary using Protobuf
/// @param log 
/// @return 
std::string LogBook::serialise_log(const LogEntry& log) const {
    // TODO
    return "";
}

// Deserialises a log using Protobuf
LogEntry LogBook::deserialise_log(const std::string& path) const {
    // TODO
    return LogEntry();
}
