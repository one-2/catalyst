#include "./LogBook.h"
#include "logging/LogEntry/SystemLogEntry/SystemLogEntry.h"
#include "logging/LogEntry/CheckpointLogEntry/CheckpointLogEntry.h"
#include "logging/LogEntry/EvaluationLogEntry/EvaluationLogEntry.h"
#include "logging/LogEntry/DebugLogEntry/DebugLogEntry.h"
#include "io/io.h"

#include <string>
#include <future>
#include <stdexcept>


namespace logging {

/**
 * @brief Constructs a new LogBook object.
 * 
 * @param storage_directory The directory where log files will be stored.
 */
LogBook::LogBook(std::string& storage_directory) 
    : storage_directory(storage_directory) {}


/**
 * @brief Logs a checkpoint asynchronously.
 * 
 * @param serialized_directory_root The directory where log files will be stored.
 * @param logs_map A map of log entries.
 */
LogBook::LogBook(std::string& serialized_directory_root, LogsMap logs_map) 
    : storage_directory(serialized_directory_root), logs_map(logs_map) {}


/**
 * @brief Logs a system event with the specified epoch and cycle.
 *
 * This function creates a SystemLogEntry with the given epoch and cycle,
 * and then logs it asynchronously.
 *
 * @param epoch The epoch time of the system event.
 * @param cycle The cycle count of the system event.
 */
void LogBook::log_system(int epoch, int cycle)
{
    SystemLogEntry e(epoch, cycle);
    log_async(e);
}


/**
 * @brief Logs a checkpoint asynchronously.
 *
 * This function creates a CheckpointLogEntry with the provided epoch, cycle, serial, and name,
 * and then logs it asynchronously.
 *
 * @param epoch The epoch number of the checkpoint.
 * @param cycle The cycle number of the checkpoint.
 * @param serial The serial number associated with the checkpoint.
 * @param name The name associated with the checkpoint.
 */
void LogBook::log_checkpoint(int epoch, int cycle, std::string& serial, std::string& name)
{
    CheckpointLogEntry e(epoch, cycle, serial, name);
    log_async(e);
}


/**
 * @brief Logs an evaluation entry asynchronously.
 *
 * This function creates an EvaluationLogEntry object with the provided epoch,
 * cycle, score name, and score value, and then logs it asynchronously.
 *
 * @param epoch The current epoch number.
 * @param cycle The current cycle number.
 * @param score_name The name of the score being logged.
 * @param score_value The value of the score being logged.
 */
void LogBook::log_evaluation(int epoch, int cycle, std::string& score_name, float score_value)
{
    EvaluationLogEntry e(epoch, cycle, score_name, score_value);
    log_async(e);
}


/**
 * @brief Logs a debug message asynchronously.
 * 
 * This function creates a DebugLogEntry with the provided epoch, cycle, and message,
 * and then logs it asynchronously.
 * 
 * @param epoch The epoch number associated with the debug message.
 * @param cycle The cycle number associated with the debug message.
 * @param message The debug message to be logged.
 */
void LogBook::log_debug(int epoch, int cycle, std::string& message)
{
    DebugLogEntry e(epoch, cycle, message);
    log_async(e);
}


/**
 * @brief Logs a log entry asynchronously.
 *
 * This function creates a new asynchronous task to log the provided log entry.
 * The task will add the log entry to the internal map and then write it to storage.
 *
 * @param log_entry The log entry to be logged.
 */
void LogBook::log_async(const LogEntry& log_entry)
{
    auto log_task = std::async(std::launch::async, [this, log_entry]() {
        add_log_to_map(log_entry);
        write_log_to_storage(log_entry);
    });
}


/**
 * @brief Adds a log entry to the log map.
 *
 * This function adds a given log entry to the log map. If the log type does not
 * already exist in the map, it creates a new list for that log type and then
 * adds the log entry to the list. The function uses a mutex to ensure thread
 * safety when accessing and modifying the log map.
 *
 * @param log The log entry to be added to the log map.
 */
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


/**
 * @brief Writes a log entry to storage.
 *
 * This function serializes a given log entry to JSON format and writes it to a specified
 * log path in the storage.
 *
 * @param log The log entry to be written to storage.
 * @return A string representing the result of the write operation.
 */
std::string LogBook::write_log_to_storage(const LogEntry& log)
{
    std::string serialized_log = log.to_json();
    std::string log_path = generate_log_path(log);
    return io::write_log(serialized_log, log_path);
}


/**
 * @brief Generates a log file path based on the log entry details.
 *
 * This function constructs a file path for a log entry using its epoch, cycle,
 * and type. The timestamp is appended to prevent overwriting.
 *
 * @param log The log entry for which the path is being generated.
 * @return A string representing the generated log file path.
 */
std::string LogBook::generate_log_path(const LogEntry& log)
{
    // Generate the path
    auto epoch = log.get_epoch();
    auto cycle = log.get_cycle();
    int timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    return storage_directory + "/" + log.get_type() + "/e" + std::to_string(epoch) + "c" + std::to_string(cycle) + "-" + std::to_string(timestamp) + ".log";
}


/**
 * @brief Reads logs of a specified type from the log book.
 *
 * This function searches for logs of the specified type in the in-memory log map.
 * If logs of the specified type are found, they are returned as a list.
 * If no logs of the specified type are found in memory, a range_error exception is thrown.
 *
 * @param type The type of logs to read.
 * @return A list of LogEntry objects of the specified type.
 * @throws std::range_error If no logs of the specified type are found in memory.
 */
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

    // Else check for the logs in storage
    
    throw std::range_error("Log type not found in memory.");
}

} // namespace logging