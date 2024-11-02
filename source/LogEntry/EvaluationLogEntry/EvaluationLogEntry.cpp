#include "./EvaluationLogEntry.h"

using namespace logging;

std::string type = "evaluation";

EvaluationLogEntry::EvaluationLogEntry(int epoch, int cycle, std::string score_name, float score_value)
    : LogEntry(
    epoch,
    cycle,
    // std::shared_ptr<Logdata> data
    std::make_shared<Logdata>(
        std::pair<std::string, std::variant<int, long, float, double, std::string>>{
            score_name,
            score_value
        }),
    type
    )
{}


//     LogEntry(int epoch, int cycle, const Logdata& data, std::string type);
