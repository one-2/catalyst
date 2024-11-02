
#include "LogEntry/DebugLogEntry/DebugLogEntry.h"

using namespace logging;
using namespace datastores;

std::string type = "debug";

DebugLogEntry::DebugLogEntry(int epoch, int cycle, std::string message) : LogEntry(
    epoch,
    cycle,
    std::make_unique<DataList<std::string, std::string>>(Datum<std::string, std::string>{{Datum<std::string, std::string>{"message", message}}}), 
    type) {}
