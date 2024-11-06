
#include "logging/LogEntry/DebugLogEntry/DebugLogEntry.h"

using namespace logging;

/**
 * @brief Constructs a new DebugLogEntry object.
 * 
 * @param epoch The epoch time of the log entry.
 * @param cycle The cycle count of the log entry.
 * @param message The debug message to be logged.
 */
DebugLogEntry::DebugLogEntry(
    int epoch,
    int cycle,
    std::string& message

) : LogEntry(
    epoch,
    cycle,
    Logdata("message", message),
    "debug"
) {}
