


#ifndef CHECKPOINTLOGENTRY_H
#define CHECKPOINTLOGENTRY_H

#include "Model/Model.h"
#include "LogEntry/LogEntry.h"

namespace logging {
class CheckpointLogEntry : LogEntry {
public:
    // CheckpointLogEntry(int epoch, int cycle, Model model);
    // std::shared_ptr<Model> load_model();
};
}

#endif // CHECKPOINTLOGENTRY_H