#include "logging/LogEntry/CheckpointLogEntry/CheckpointLogEntry.h"

//
// NOTE: Out-of-scope non-constant declaration is a bad idea.
//       > std::string type = "checkpoint"; // BAD
//       This causes scope issues and random Segfaults. Whoops.
//

namespace logging {

/**
 * @brief Constructs a new CheckpointLogEntry object.
 * 
 * @param epoch The epoch number associated with this log entry.
 * @param cycle The cycle number associated with this log entry.
 * @param serial The serial number of the model.
 * @param model_name The name of the model.
 */
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
