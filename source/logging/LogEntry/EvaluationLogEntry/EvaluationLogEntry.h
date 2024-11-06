

#ifndef EVALUATIONLOGENTRY_H
#define EVALUATIONLOGENTRY_H

#include "logging/LogEntry/LogEntry.h"

#include <string>
#include <list>
#include <utility>


namespace logging {

class EvaluationLogEntry : public LogEntry {
public:
    EvaluationLogEntry(
        int epoch, 
        int cycle, 
        std::string score_name, 
        float score_value
    );
};

}

#endif // EVALUATIONLOGENTRY_H
