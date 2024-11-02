
#include "LogEntry/DebugLogEntry/DebugLogEntry.h"

using namespace logging;

std::string type = "debug";

DebugLogEntry::DebugLogEntry(int epoch, int cycle, std::string message)
    : LogEntry(
        epoch,
        cycle,
        std::make_shared<Logdata>("message", message),
        type)
    {}
