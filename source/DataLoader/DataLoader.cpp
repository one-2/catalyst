// source/DataLoader/DataLoader.cpp
//
// Author: Stephen Elliott
//
// Date: 2024-10-25
//
// Description: Wraps the data class in an iterator 
//

#include "DataLoader.h"
#include "../Dataset/Dataset.h"

DataLoader::DataLoader(std::shared_ptr<Dataset> dataset) : dataset_(dataset), current_index_(0) {}

torch::Tensor DataLoader::get_next_value_tensor() {
    if (current_index_ < dataset_.size()) {
        return dataset_.get_tensor_at(current_index_++);
    } else {
        this->_reset_head();
        throw std::out_of_range("No more data in the dataset.");
    }
}

std::shared_ptr<Dataset> DataLoader::get_dataset_ptr() {
    return dataset_;
}

void DataLoader::_reset_head() {
    current_index_ = 0;
}

// friend std::ostream& operator<<(std::ostream& os, const DataLoader& loader);
