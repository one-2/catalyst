
#ifndef DEBUGLOGENTRY_H
#define DEBUGLOGENTRY_H

#include <string>
<<<<<<< HEAD
#include "LogEntry/LogEntry.h"

namespace logging {
class DebugLogEntry : public LogEntry {
public:
    DebugLogEntry(int epoch, int cycle, std::string message);
};
=======

class DebugLogEntry {
public:
    DebugLogEntry(std::string&, std::string& message);
>>>>>>> parent of 6f94ea2 (Add source-root pathing and more work on LogEntry subclasses)
}

#endif // DEBUGLOGENTRY_H
