
#ifndef LOGBOOK_H
#define LOGBOOK_H

#include <string>
#include <list>
#include <future>

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/unordered_map.hpp>

#include "../LogEntry/LogEntry.h"
#include "io/io.h"


//
// NOTE: Complexity of solution should not be considered for an auxilliary
//       focus of the software. I should concentrate design time in
//       areas which are highly used, fragile, or central to program
//       execution. Not the logger.
//
//       On the other hand, the initial design was crap, and this is way better.
//

class Model; // Forward declaration for checkpoint log builder

namespace logging {

typedef std::list<logging::LogEntry> ListOfLogs;
typedef std::unordered_map<std::string, ListOfLogs> LogsMap;

class LogBook {
public:
    // Constructors
    LogBook(std::string& storage_directory);
    LogBook(std::string& storage_directory, LogsMap logs_map);

    // Reading logs
    const ListOfLogs read_logs(const std::string& type) const;

    // Log creation functions
    void log_system(int epoch, int cycle);
    void log_checkpoint(int epoch, int cycle, std::string& serial, std::string&  name);
    void log_evaluation(int epoch, int cycle, std::string& score_name, float score_value);
    void log_debug(int epoch, int cycle, std::string& message);

    std::string generate_log_path(const LogEntry& log);

    // // Serialization
    // template <class Archive>
    // void serialize(Archive& ar);


    // // Deserialization
    // static LogBook deserialize(const std::string& json_str);

private:
    LogBook() = default; // For deserialisation

    void log_async(const LogEntry& log_entry);

    LogsMap logs_map; // NOTE: this makes things way better
    std::string storage_directory;

    // Adding to LogBook internal objects
    void add_log_to_map(const LogEntry& log); // Normal logs are written and stored on memory
    std::string add_checkpoint_to_map(std::string& path); // Checkpoints are just written
};

}

#endif // LOGBOOK_H