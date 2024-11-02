#ifndef SYSTEMLOGENTRY_H
#define SYSTEMLOGENTRY_H

#include "LogEntry/LogEntry.h"
#include "datastores/DataList/DataList.h"

namespace logging {
class SystemLogEntry : public LogEntry {
public:
    SystemLogEntry(int epoch, int cycle);

    static datastores::DataList build_usage();
    static const float get_cpu_usage();
    static const float get_mem_usage();
    static const float get_gpu_usage();
    //
    // NOTE: "Passing by value inherently restricts modifications to the copy, 
    //       so in this case const is optional and often omitted for simplicity.""
    //
};
}

#endif // SYSTEMLOGENTRY_H