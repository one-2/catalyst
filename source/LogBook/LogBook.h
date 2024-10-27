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
    LogBook(const std::string& name, const std::string& storage_directory);

    std::string write_log(const std::string& type, std::list<Info> info);
    std::list<std::string> read_log_type(const std::string& type) const;
    std::string serialise_log(const LogEntry log);
    LogEntry deserialise_log(const std::string);
    // friend std::ostream& operator<<(std::ostream& os, const LogBook& logBook);

private:
    std::string storage_directory;
    std::list<std::string> system_logs;
    std::list<std::string> model_checkpoints;
    std::list<std::string> exception_logs;
    std::list<std::string> debug_logs;
};

#endif // LOGBOOK_H