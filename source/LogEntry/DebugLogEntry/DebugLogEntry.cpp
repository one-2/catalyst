
#include "LogEntry/DebugLogEntry/DebugLogEntry.h"

DebugLogEntry::DebugLogEntry(int epoch, int cycle, std::string message) : LogEntry(epoch, cycle, DataList{Datum{"message", message}}, "debug") {}
