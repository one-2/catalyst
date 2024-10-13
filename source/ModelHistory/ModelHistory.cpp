// test_modelhistory.cpp
//
// Author: Stephen Elliott
//
// Date: 2024-10-13
//
// Description: The ModelHistory class.
//

#include <torch/torch.h>
#include "model_history.h"

ModelHistory::ModelHistory(bool is_training, bool stopwatch, int sampling_rate)
    : is_training(is_training), architecture("default"), history(2) {
    // Initialize history vectors
    history[0].reserve(sampling_rate); // For losses
    if (stopwatch) {
        history[1].reserve(sampling_rate); // For timings
    }
}

void ModelHistory::append_history(float loss, float timing) {
    history[0].push_back(loss);
    if (timing != -1) {
        history[1].push_back(timing);
    }
}

std::vector<float> ModelHistory::get_losses() {
    return history[0];
}

std::vector<float> ModelHistory::get_stopwatch() {
    return history[1];
}

int ModelHistory::get_history_length() {
    return history[0].size();
}

int ModelHistory::get_sampling_rate() {
    return history[0].capacity();
}

bool ModelHistory::get_is_training() {
    return is_training;
}

std::ostream& operator<<(std::ostream& os, ModelHistory& mh) {
    os << "ModelHistory(is_training=" << mh.is_training << ", architecture=" << mh.architecture << ")\n";
    os << "Losses: ";
    for (const auto& loss : mh.history[0]) {
        os << loss << " ";
    }
    os << "\nTimings: ";
    for (const auto& timing : mh.history[1]) {
        os << timing << " ";
    }
    return os;
}