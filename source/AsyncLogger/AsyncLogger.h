#include <string>
#include <list>

#include "../LogEntry/LogEntry.h"
#include "../Model/Model.h"
#include "../LogBook/LogBook.h"

#ifndef ASYNCLOGGER_H
#define ASYNCLOGGER_H

#include <future>

class AsyncLogger {
public:
    std::future<LogEntry> log_system();
    std::future<LogEntry> log_checkpoint(const Model model);
    std::future<LogEntry> log_evaluation(std::string loss, std::list<std::pair<std::string, float>> scores);
    std::future<LogEntry> log_debug(const std::string& message);

private:
    LogBook& logbook;
};

#endif // ASYNCLOGGER_H
