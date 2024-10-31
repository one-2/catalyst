#include <string>
#include <list>

#include "../Model/Model.h"
#include "../LogBook/LogBook.h"

#ifndef LOGGER_H
#define LOGGER_H

class Logger {
public:
    void log_system();
    void log_checkpoint(const Model model);
    void log_evaluation(std::string loss, std::list<std::pair<std::string, float>> scores);
    void log_debug(const std::string& message);

private:
    LogBook& logbook;
};

#endif // LOGGER_H
