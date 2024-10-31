
#ifndef LOGBOOK_H
#define LOGBOOK_H

#include <string>
#include <list>
#include "../LogEntry/LogEntry.h"
#include "../Model/Model.h"

typedef std::list<LogEntry> ListOfLogs;
typedef std::unordered_map<std::string, ListOfLogs> LogsMap;


//
// NOTE: Complexity of solution should not be considered for an auxilliary
//       focus of the software. I should concentrate design time in
//       areas which are highly used, fragile, or central to program
//       execution. Not the logger.
//
//       On the other hand, the initial design was crap, and this is way better.
//


class LogBook {
public:
    // Constructors
    LogBook(std::string& storage_directory_path);
    LogBook(std::string& storage_directory_path, LogsMap logs_map);

    // Reading logs
    const std::list<LogEntry> read_logs(const std::string& type) const;

    // Log creation functions
    std::string log_system();
    std::string log_checkpoint(const Model model);
    std::string log_evaluation(std::string loss, std::list<std::pair<std::string, float>> scores);
    std::string log_debug(const std::string& message);

private:
    std::string& storage_directory;

    LogsMap logs_map; // NOTE: this makes things way better

    // Adding to LogBook internal objects
    std::string add_log_to_map(const LogEntry& log); // Normal logs are written and stored on memory
    std::string add_checkpoint_to_map(std::string& path); // Checkpoints are just written

    // Logbook serialisation functions
    const std::string serialise() const;
    static const LogBook deserialise(const std::string&);
};

#endif // LOGBOOK_H