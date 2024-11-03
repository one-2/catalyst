#include "LogEntry/CheckpointLogEntry/CheckpointLogEntry.h"

//
// NOTE: Out-of-scope non-constant declaration is a bad idea.
//       > std::string type = "checkpoint"; // BAD
//       This causes scope issues and random Segfaults. Whoops.
//

namespace logging {

CheckpointLogEntry::CheckpointLogEntry(
    int epoch,
    int cycle,
    std::string& serial,
    std::string& model_name

) : LogEntry(
    epoch,
    cycle,
    Logdata(model_name, serial),
    "checkpoint"
) {}

}
