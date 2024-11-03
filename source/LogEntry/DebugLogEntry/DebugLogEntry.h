
#ifndef DEBUGLOGENTRY_H
#define DEBUGLOGENTRY_H

#include <string>
#include "LogEntry/LogEntry.h"

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
