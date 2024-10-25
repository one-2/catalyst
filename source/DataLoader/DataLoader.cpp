// source/DataLoader/DataLoader.cpp
//
// Author: Stephen Elliott
//
// Date: 2024-10-25
//
// Description: Wraps the data class in an iterator 
//

#include "./DataLoader.h"
#include "../Dataset/Dataset.h"

DataLoader::DataLoader(std::shared_ptr<Dataset> dataset) : dataset_(dataset), current_index_(0) {}

std::array<torch::Tensor, 2> DataLoader::get_next_observation() {
    if (current_index_ < dataset_->get_length()) {
        return {
            dataset_->input[this->current_index_++],
            dataset_->target[this->current_index_++]
        };
    } else {
        reset_head_();
        throw std::out_of_range("No more data in the dataset.");
    }
}

std::shared_ptr<Dataset> DataLoader::get_dataset_ptr() {
    return dataset_;
}

void DataLoader::reset_head_() {
    this->current_index_ = 0;
}

// friend std::ostream& operator<<(std::ostream& os, const DataLoader& loader);
