#include "LogEntry/CheckpointLogEntry/CheckpointLogEntry.h"

using namespace logging;

std::string type = "checkpoint";

CheckpointLogEntry::CheckpointLogEntry(int epoch, int cycle, Model& model, std::string &model_name)
    : LogEntry(
        epoch,
        cycle,
        std::make_shared<Logdata>(model_name, model.serialize()),
        type)
    {}


