
#include "LogEntry/DebugLogEntry/DebugLogEntry.h"

using namespace logging;
using namespace datastores;

std::string type = "debug";

DebugLogEntry::DebugLogEntry(int epoch, int cycle, std::string message) : LogEntry(
    epoch,
    cycle,
    DataList{{Datum{"message", message}}}, 
    type) {}
