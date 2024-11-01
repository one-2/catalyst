

#include "EvaluationLogEntry.h"
#include "LogEntry/LogEntry.h"

EvaluationLogEntry::EvaluationLogEntry(
    const int epoch, const int cycle, std::string loss,
    std::list<std::pair<std::string, float>> scores) :
    LogEntry(epoch, cycle, build_scores(), "evaluation") 
{}

DataList EvaluationLogEntry::build_scores(std::list<std::pair<std::string, float>> scores) {
    DataList data;
    for (auto score : scores) {
        data.push_back({score.first, std::to_string(score.second)});
    }
    return data;
}
