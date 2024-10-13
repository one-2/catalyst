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
    ModelHistory(bool is_training, bool stopwatch, int sampling_rate);
    void append_history(float loss, float timing = -1); // default value -1 indicates no timing
    std::vector<float> get_losses();
    std::vector<float> get_stopwatch();
    int get_history_length();
    int get_sampling_rate();
    bool get_is_training();
    friend std::ostream& operator<<(std::ostream& os, ModelHistory& mh);
};
