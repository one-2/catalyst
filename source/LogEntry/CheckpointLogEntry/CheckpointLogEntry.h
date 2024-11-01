


#ifndef CHECKPOINTLOGENTRY_H
#define CHECKPOINTLOGENTRY_H

#include "../../Model/Model.h"
#include "../LogEntry.h"

class CheckpointLogEntry : LogEntry {
public:
    CheckpointLogEntry(int epoch, int cycle, Model model);
    std::shared_ptr<Model> load_model();

private:
    std::string retrieve_model_serial();
};

#endif // CHECKPOINTLOGENTRY_H