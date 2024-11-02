

#ifndef CHECKPOINTLOGENTRY_H
#define CHECKPOINTLOGENTRY_H

#include "Model/Model.h"
#include "LogEntry/LogEntry.h"

namespace logging {
class CheckpointLogEntry : public LogEntry {
public:
    CheckpointLogEntry(int epoch, int cycle, Model& model, std::string &model_name);
};
}


#endif // CHECKPOINTLOGENTRY_H