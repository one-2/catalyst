

#ifndef EVALUATIONLOGENTRY_H
#define EVALUATIONLOGENTRY_H

#include <string>
#include <list>
#include <utility>

class EvaluationLogEntry {
public:
    EvaluationLogEntry(std::string loss, std::list<std::pair<std::string, float>> scores);

private:
    std::string loss_;
    std::list<std::pair<std::string, float>> scores_;
};

#endif // EVALUATIONLOGENTRY_H
