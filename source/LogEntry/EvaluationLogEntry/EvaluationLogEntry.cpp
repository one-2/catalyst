#include "./EvaluationLogEntry.h"

std::string type = "evaluation";

EvaluationLogEntry::EvaluationLogEntry(
    int epoch, int cycle, std::string loss,
    std::list<std::pair<std::string, float>> scores) : LogEntry(
    epoch,
    cycle,
    DataList{build_scores(scores)},
    type)
    {}

DataList EvaluationLogEntry::build_scores(std::list<std::pair<std::string, float>> scores) {
    std::list<Datum> d;
    for (const auto& score : scores) {
        d.push_back(Datum(score.first, std::to_string(score.second)));
    }
    return d;
}
