
#include "LogEntry/DebugLogEntry/DebugLogEntry.h"

using namespace logging;

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
