
#include "LogEntry/DebugLogEntry/DebugLogEntry.h"

std::string type = "debug";

DebugLogEntry::DebugLogEntry(int epoch, int cycle, std::string message) : LogEntry(
    epoch,
    cycle,
    DataList{{Datum{"message", message}}}, 
    type) {}
