#include "./LogBook.h"
#include <string>
#include <future>
#include <stdexcept>
#include "../io/io.h"
#include "../LogEntry/SystemLogEntry/SystemLogEntry.h"
#include "../LogEntry/CheckpointLogEntry/CheckpointLogEntry.h"
#include "../LogEntry/EvaluationLogEntry/EvaluationLogEntry.h"
#include "../LogEntry/DebugLogEntry/DebugLogEntry.h"


LogBook::LogBook(std::string& storage_directory_path) 
    : storage_directory(storage_directory_path), logger(create_logger()) {
}

LogBook::LogBook(std::string& serialised_directory_root, LogsMap logs_map) 
    : storage_directory(serialised_directory_root), logs_map(logs_map), logger(create_logger()) {
}

void LogBook::add_log_to_map(const LogEntry& log) {
    // Put a mutex on the log map
    std::lock_guard<std::mutex> lock(logs_mutex) {
        if (logs_map.find(log.get_type()) == logs_map.end()) {
            // Creates the list header if it doesn't yet exist
            logs_map[log.get_type()] = std::list<LogEntry>();
        }
        logs_map[log.get_type()].push_back(log);
    }
    // Return a shared pointer
    
}

std::string LogBook::add_checkpoint_to_map(std::string& path) {
    // Add the checkpoint to the map
    if (logs_map.find("checkpoints") == logs_map.end()) {
        logs_map["checkpoints"] = std::list<std::string>();
    }
    // Return the path
    logs_map["checkpoints"].push_back(path);
    return path;
}

void LogBook::log_system() {
    log_async<SystemLogEntry>();
}

void LogBook::log_checkpoint(const Model model) {
    log_async<CheckpointLogEntry>(model);
}

void LogBook::log_evaluation(std::string loss, std::list<std::pair<std::string, float>> scores) {
    log_async<EvaluationLogEntry>(loss, scores);
}

void LogBook::log_debug(const std::string& message) {
    log_async<DebugLogEntry>(message);
}

template<typename LogEntryType, typename... Args>
void LogBook::log_async(Args&&... args) {
    auto future = std::async(std::launch::async, [this, args...]() {
        LogEntryType log_entry(std::forward<Args>(args)...);
        add_log_to_map(log_entry);
        std::string serialised_log = log_entry.serialise();
        std::string path = generate_log_path(log_entry);
        io.write_log(serialised_log, path);
    });
}

const std::list<LogEntry> LogBook::read_logs(const std::string& type) const {
    std::list<LogEntry> filtered_logs;
    for (const auto& log_pair : logs_map) {

        // Checks the first entry in the current log key. If the same, returns those logs
        LogEntry first_type = log_pair.second.front();
        if (first_type.get_type() == type) {
            for (const auto& log : log_pair.second) {
                filtered_logs.push_back(log);
            }
            return filtered_logs;
        }
    }
    throw std::invalid_argument("No logs of type " + type + " found.");
}

std::string LogBook::generate_log_path(const LogEntry& log) {
    // Generate the path
    return storage_directory + "/" + log.get_type() + "/" + log.get_timestamp().time_since_epoch().count();
}

const std::string LogBook::serialise() const {
    // Implementation for serialising the LogBook
    return "";
}

const LogBook LogBook::deserialise(const std::string& data) {
    // Implementation for deserialising the LogBook
    return LogBook(data);
}