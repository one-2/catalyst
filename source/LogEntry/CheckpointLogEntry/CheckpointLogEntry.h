

#ifndef CHECKPOINTLOGENTRY_H
#define CHECKPOINTLOGENTRY_H

#include "Model/Model.h"
#include "LogEntry/LogEntry.h"

class CheckpointLogEntry : public LogEntry {
public:
    CheckpointLogEntry(Model model);
//     void save();
//     void load();
// private:
//     Model model;
};


#endif // CHECKPOINTLOGENTRY_H