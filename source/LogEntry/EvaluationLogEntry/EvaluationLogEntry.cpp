#include "./EvaluationLogEntry.h"

namespace logging {

EvaluationLogEntry::EvaluationLogEntry(
    int epoch,
    int cycle,
    std::string score_name,
    float score_value

) : LogEntry(
    epoch,
    cycle,
    Logdata(score_name, score_value),
    "evaluation"

) {}

}