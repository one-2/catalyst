#include "./EvaluationLogEntry.h"

EvaluationLogEntry::EvaluationLogEntry(
    const int epoch, const int cycle, std::string loss,
    std::list<std::pair<std::string, float>> scores
) : LogEntry(epoch, cycle, build_scores(scores), "evaluation") {}

DataList EvaluationLogEntry::build_scores(std::list<std::pair<std::string, float>> scores) {
    DataList data_list;
    for (const auto& score : scores) {
        data_list.add_datum(Datum(score.first, std::to_string(score.second)));
    }
    return data_list;
}
