#ifndef SYSTEMLOGENTRY_H
#define SYSTEMLOGENTRY_H

#include "LogEntry/LogEntry.h"

namespace logging {
class SystemLogEntry : public LogEntry {
public:
    SystemLogEntry(int epoch, int cycle);

private:
    static Logdata build_usage();
    static float get_cpu_usage();
    static float get_mem_usage();
    static float get_gpu_usage();
    //
    // NOTE: "Passing by value inherently restricts modifications to the copy, 
    //       const is optional and often omitted for simplicity.""
    //
};
}

#endif // SYSTEMLOGENTRY_H