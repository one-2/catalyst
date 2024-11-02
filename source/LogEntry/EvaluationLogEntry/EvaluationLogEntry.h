

#ifndef EVALUATIONLOGENTRY_H
#define EVALUATIONLOGENTRY_H

#include <string>
#include <list>
#include <utility>
#include "datastores/DataList.h"
#include "LogEntry/LogEntry.h"

namespace logging {
class EvaluationLogEntry : public LogEntry {
public:
    EvaluationLogEntry(
        int epoch, int cycle, std::string loss,
        std::list<std::pair<std::string, float>> scores
    );

private:
    static std::unique_ptr<DataList<std::string, float>> build_scores(std::list<std::pair<std::string, float>> scores);
};
}

#endif // EVALUATIONLOGENTRY_H
