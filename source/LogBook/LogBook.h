#ifndef LOGBOOK_H
#define LOGBOOK_H

#include <string>
#include <list>
#include "../LogEntry/LogEntry.h"

class LogBook {
private:
    std::string storage_directory;
    std::list<LogEntry> system_logs;
    std::list<LogEntry> debug_logs;

    std::string serialise() const;
    static LogBook deserialise(const std::string&);

public:
    LogBook(const std::string& storage_directory_path);
    LogBook(const std::string& serialised_directory);

    void write_log(const std::string& type, const LogEntry& log);
    std::list<LogEntry> read_logs(const std::string& type) const;
};

#endif // LOGBOOK_H