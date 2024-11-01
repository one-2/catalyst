#include "LogEntry/EvaluationLogEntry/EvaluationLogEntry.h"

EvaluationLogEntry::EvaluationLogEntry(
    const int epoch, const int cycle, std::string loss,
    std::list<std::pair<std::string, float>> scores
) : LogEntry(epoch, cycle, build_scores(scores), "evaluation") {}

DataList EvaluationLogEntry::build_scores(std::list<std::pair<std::string, float>> scores) {
    DataList dataList;
    for (const auto& score : scores) {
        dataList.push_back(Datum(score.first, std::to_string(score.second)));
    }
    return dataList;
}
