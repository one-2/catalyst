#include "./LogBook.h"
#include <string>
#include <future>
#include <stdexcept>
#include "io/io.h"
#include "LogEntry/SystemLogEntry/SystemLogEntry.h"
#include "LogEntry/CheckpointLogEntry/CheckpointLogEntry.h"
#include "LogEntry/EvaluationLogEntry/EvaluationLogEntry.h"
#include "LogEntry/DebugLogEntry/DebugLogEntry.h"

LogBook::LogBook(std::string& storage_directory_path) 
    : storage_directory(storage_directory_path) {}

LogBook::LogBook(std::string& serialised_directory_root, LogsMap logs_map) 
    : storage_directory(serialised_directory_root), logs_map(logs_map) {}

void LogBook::add_log_to_map(const LogEntry& log) {
    // Put a mutex on the log map
    std::mutex logs_mutex;
    std::lock_guard<std::mutex> lock(logs_mutex);
    if (logs_map.find(log.get_type()) == logs_map.end()) {
        // Creates the list header if it doesn't yet exist
        logs_map[log.get_type()] = std::list<LogEntry>();
    }
    logs_map[log.get_type()].push_back(log);
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

const std::list<LogEntry> LogBook::read_logs(const std::string& type) const {
    std::list<LogEntry> filtered_logs;

    // If the log is held in memory, read it from there
    for (const auto& log_pair : logs_map) {

        // Checks the first entry in the current log key. If the same, returns those logs
        LogEntry first_type = log_pair.second.front();
        if (first_type.get_type() == type) {
            for (const auto& log : log_pair.second) {
                filtered_logs.push_back(log);
            }
            // Return logs found in memory
            if (!(filtered_logs.empty())) {
                return filtered_logs;
            }
        }
    }

    // Else check storage for logs of the given type
    const std::string path = storage_directory + "/" + type;
    std::list<std::string> log_files = io::get_files_in_directory(path);

    // iF logs are not found, throw error
    if (log_files.empty()) {
        throw std::invalid_argument("No logs of type " + type + " found.");
    } else {
        // Return logs found in storage
        for (const auto& log_file : log_files) {
            std::string log_data = io::read_file(path + "/" + log_file);
            LogEntry log = LogEntry::deserialise(log_data);
            filtered_logs.push_back(log);
        }
        return filtered_logs;
    }
}

std::string LogBook::generate_log_path(const LogEntry& log) {
    // Generate the path
    auto epoch = log.get_epoch();
    auto cycle = log.get_cycle();
    int random_number = rand() % 1000;
    return storage_directory + "/" + log.get_type() + "/e" + std::to_string(epoch) + "c" + std::to_string(cycle) + "-" + std::to_string(random_number) + ".log"; // Random number helps prevent overwriting
}

const std::string LogBook::serialise() const {
    // Implement logs_map serialisation
    // Implement storage_directory serialisation
    std::ostringstream oss;
    std::mutex logs_mutex;
    std::lock_guard<std::mutex> lock(logs_mutex);
    for (const auto& log_pair : logs_map) {
        oss << log_pair.first << "\n";
        for (const auto& log : log_pair.second) {
            oss << log.serialise() << "\n";
        }
    }
    oss << storage_directory;
    return oss.str();
}

const LogBook LogBook::deserialise(const std::string& data) {
    // Implement logs_map deserialisation
    // Implement storage_directory deserialisation
    std::istringstream iss(data);
    std::string line;
    LogsMap logs_map;
    std::string storage_directory;

    while (std::getline(iss, line)) {
        if (line.empty()) {
            continue;
        }
        std::string log_type = line;
        std::list<LogEntry> log_entries;
        while (std::getline(iss, line) && !line.empty()) {
            LogEntry log_entry = LogEntry::deserialise(line);
            log_entries.push_back(log_entry);
        }
        logs_map[log_type] = log_entries;
    }

    if (std::getline(iss, line)) {
        storage_directory = line;
    }

    return LogBook(storage_directory, logs_map);
}
