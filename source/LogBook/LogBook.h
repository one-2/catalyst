// source/LogBook/LogBook.h
//
// Author: Stephen Elliott
//
// Date: 2024-10-27
//
// Description: 
//
// Usage: 
//

#ifndef LOGBOOK_H
#define LOGBOOK_H

#include <string>
#include <list>
#include <ostream>
#include <chrono>

#include "../Model/Model.h"

enum Types {
    SYSTEM = 0,
    CHECKPOINT = 1,
    DEBUG = 2
};

struct Info {
    std::string key;
    std::string string_value;
    float float_value;
};

struct LogEntry {
    std::chrono::time_point<std::chrono::system_clock> timestamp;
    std::string type;
    std::list<Info> info;
};

class LogBook {
public:
    LogBook(const std::string& storage_directory);

    std::string log_info(const int& type, const std::list<Info>& info);
    std::list<LogEntry> read_log_type(const int& type) const;
    std::string log_checkpoint(const Model& model);
    // friend std::ostream& operator<<(std::ostream& os, const LogBook& logBook);

private:
    std::string serialise_log(const LogEntry& log) const;
    LogEntry deserialise_log(const std::string& path) const;

    std::string storage_directory;
    std::list<std::string> system_logs;
    std::list<std::string> model_checkpoints;
    std::list<std::string> debug_logs;

    std::string system_logs_directory;
    std::string checkpoint_directory; 
    std::string debug_directory; 
};

#endif // LOGBOOK_H