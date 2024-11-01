#ifndef SYSTEMLOGENTRY_H
#define SYSTEMLOGENTRY_H

#include "LogEntry/LogEntry.h"
#include "LogEntry/DataList/DataList.h"

class SystemLogEntry : public LogEntry {
public:
    SystemLogEntry(const int epoch, const int cycle);

    static const DataList build_usage();
    static const float get_cpu_usage();
    static const float get_mem_usage();
    static const float get_gpu_usage();
};

#endif // SYSTEMLOGENTRY_H