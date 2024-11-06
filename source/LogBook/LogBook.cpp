#include "./LogBook.h"
#include <string>
#include <future>
#include <stdexcept>
#include "io/io.h"
#include "LogEntry/SystemLogEntry/SystemLogEntry.h"
#include "LogEntry/CheckpointLogEntry/CheckpointLogEntry.h"
#include "LogEntry/EvaluationLogEntry/EvaluationLogEntry.h"
#include "LogEntry/DebugLogEntry/DebugLogEntry.h"

namespace logging {

LogBook::LogBook(std::string& storage_directory) 
    : storage_directory(storage_directory) {}

LogBook::LogBook(std::string& serialized_directory_root, LogsMap logs_map) 
    : storage_directory(serialized_directory_root), logs_map(logs_map) {}

void LogBook::log_system(int epoch, int cycle)
{
    SystemLogEntry e(epoch, cycle);
    log_async(e);
}

void LogBook::log_checkpoint(int epoch, int cycle, std::string& serial, std::string& name)
{
    CheckpointLogEntry e(epoch, cycle, serial, name);
    log_async(e);
}

void LogBook::log_evaluation(int epoch, int cycle, std::string& score_name, float score_value)
{
    EvaluationLogEntry e(epoch, cycle, score_name, score_value);
    log_async(e);
}

void LogBook::log_debug(int epoch, int cycle, std::string& message)
{
    DebugLogEntry e(epoch, cycle, message);
    log_async(e);
}

void LogBook::log_async(const LogEntry& log_entry)
{
    auto log_task = std::async(std::launch::async, [this, log_entry]() {
        add_log_to_map(log_entry);
        write_log_to_storage(log_entry);
    });

    // TODO: implement local write as well
}

void LogBook::add_log_to_map(const LogEntry& log)
{
    // Put a mutex on the log map
    std::mutex logs_mutex;
    std::lock_guard<std::mutex> lock(logs_mutex);
    if (logs_map.find(log.get_type()) == logs_map.end()) {
        // Creates the list header if it doesn't yet exist
        logs_map[log.get_type()] = std::list<LogEntry>();
    }
    logs_map[log.get_type()].push_back(log);
}

std::string LogBook::write_log_to_storage(const LogEntry& log)
{
    std::string serialized_log = log.to_json();
    std::string log_path = generate_log_path(log);
    return io::write_log(serialized_log, log_path);
}

std::string LogBook::generate_log_path(const LogEntry& log)
{
    // Generate the path
    auto epoch = log.get_epoch();
    auto cycle = log.get_cycle();
    int random_number = rand() % 1000;
    return storage_directory + "/" + log.get_type() + "/e" + std::to_string(epoch) + "c" + std::to_string(cycle) + "-" + std::to_string(random_number) + ".log"; // Random number helps prevent overwriting
}

const std::list<LogEntry> LogBook::read_logs(const std::string& type) const
{
    std::list<LogEntry> filtered_logs;

    // If the log is held in memory, read it from there
    for (const auto& log_pair : logs_map) {

        // Check the first entry in the current log key.
        LogEntry first_type = log_pair.second.front();
        if (first_type.get_type() == type) {
            // Type found. Get all these logs and return.
            for (const auto& log : log_pair.second) {
                filtered_logs.push_back(log);
            }
            // Return logs found in memory
            if (!(filtered_logs.empty())) {
                return filtered_logs;
            }
        }
    }

    // Else check for the logs in memory
    
    throw std::range_error("Log type not found in memory.");
}

//     // Else check storage for logs of the given type
//     const std::string path = storage_directory + "/" + type;
//     std::list<std::string> log_files = io::get_files_in_directory(path);

//     // iF logs are not found, throw error
//     if (log_files.empty()) {
//         throw std::invalid_argument("No logs of type " + type + " found.");
//     } else {
//         // Return logs found in storage
//         for (const auto& log_file : log_files) {
//             std::string log_data = io::read_file(path + "/" + log_file);
//             LogEntry log = *LogEntry::deserialize(log_data);
//             filtered_logs.push_back(log);
//         }
//         return filtered_logs;
//     }
// }

} // namespace logging