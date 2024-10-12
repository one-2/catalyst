// source/ModelHistory/model_history.h
//
// Author: Stephen Elliott
//
// Date: 2024-10-12
//
// Description: Stores information about the model's behaviour during past
// training or evaluation runs.
//
// Usage: 
//

#include <string>
#include <vector>
#include <variant>

class ModelHistory
{
private:
    const bool is_training;
    const std::string architecture;
    std::vector<std::vector<float>> history;

public:
    ModelHistory(bool stopwatch, int sampling_rate);
    bool is_this_training_history();
    std::vector<float> get_losses();
    int get_history_length();
    friend std::ostream& operator<<(std::ostream& os, const ModelHistory& mh);
};
