#include "LogEntry/CheckpointLogEntry/CheckpointLogEntry.h"

using namespace logging;

// std::string type = "checkpoint"; 
//
// NOTE: Out-of-scope non-constant declaration is a bad idea.
//       This causes scope issues and random Segfaults. Whoops.
//

CheckpointLogEntry::CheckpointLogEntry(int epoch, int cycle, std::string serial, std::string model_name)
    : LogEntry(
    epoch,
    cycle,
    Logdata(model_name, serial),
    "checkpoint"
    )
{}


