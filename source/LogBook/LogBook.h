
#ifndef LOGBOOK_H
#define LOGBOOK_H

#include <string>
#include <list>
#include "../LogEntry/LogEntry.h"
#include "../Model/Model.h"
#include <future>
#include "io/io.h"

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

namespace logging {
class LogBook {
public:
    // Logging template
    template<typename LogEntryType, typename... Args>
    void log_async(Args&&... args);

    // Constructors
    LogBook(std::string& storage_directory_path);
    LogBook(std::string& storage_directory_path, LogsMap logs_map);

    // Reading logs
    const std::list<LogEntry> read_logs(const std::string& type) const;

    // Log creation functions
    void log_system();
    void log_checkpoint(const Model model);
    void log_evaluation(std::string loss, std::list<std::pair<std::string, float>> scores);
    void log_debug(const std::string& message);

    std::string generate_log_path(const LogEntry& log);

private:
    std::string storage_directory;

    LogsMap logs_map; // NOTE: this makes things way better

    // Adding to LogBook internal objects
    void add_log_to_map(const LogEntry& log); // Normal logs are written and stored on memory
    std::string add_checkpoint_to_map(std::string& path); // Checkpoints are just written

    // Logbook serialisation functions
    const std::string serialise() const;
    static const LogBook deserialise(const std::string&);
};

template<typename LogEntryType, typename... Args>
void LogBook::log_async(Args&&... args) {
    auto future = std::async(std::launch::async, [this, args...]() {
        LogEntryType log_entry(std::forward<Args>(args)...);
        add_log_to_map(log_entry);
        std::string serialised_log = log_entry.serialise();
        std::string path = generate_log_path(log_entry);
        io::write_log(serialised_log, path);
    });
}
}

#endif // LOGBOOK_H