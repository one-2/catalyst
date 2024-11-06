#include "./EvaluationLogEntry.h"

namespace logging {

/**
 * @brief Constructs an EvaluationLogEntry object.
 *
 * @param epoch The epoch number associated with this log entry.
 * @param cycle The cycle number associated with this log entry.
 * @param score_name The name of the score being logged.
 * @param score_value The value of the score being logged.
 */
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