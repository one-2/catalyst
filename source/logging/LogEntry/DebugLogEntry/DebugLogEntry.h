
#ifndef DEBUGLOGENTRY_H
#define DEBUGLOGENTRY_H

#include "logging/LogEntry/LogEntry.h"

#include <string>


namespace logging {

class DebugLogEntry : public LogEntry {
public:
    DebugLogEntry(
        int epoch,
        int cycle,
        std::string& message
    );
};

}

#endif // DEBUGLOGENTRY_H
