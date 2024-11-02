#include "./EvaluationLogEntry.h"

using namespace logging;
using namespace datastores;

std::string type = "evaluation";

EvaluationLogEntry::EvaluationLogEntry(
    int epoch, int cycle, std::string loss, std::list<std::pair<std::string, float>> scores)
    : LogEntry(
        epoch,
        cycle,
        build_scores(scores),
        type)
    {}

std::unique_ptr<DataList<std::string, float>> EvaluationLogEntry::build_scores(std::list<std::pair<std::string, float>> scores) {
    std::list<Datum<std::string, float>> d;
    for (const auto& score : scores) {
        d.emplace_back(Datum(score.first, score.second));
    }
    return std::make_unique<DataList<std::string, float>>(d);
}
