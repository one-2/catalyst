// source/DataLoader/DataLoader.h
//
// Author: Stephen Elliott
//
// Date: 2024-10-13
//
// Description: Header file for the DataLoader class.
//
// Usage: 
//

#ifndef DATALOADER_H
#define DATALOADER_H

#include <array>
#include <iostream>
#include <torch/torch.h>
#include "../Dataset/Dataset.h"
#include <memory>

class DataLoader {
public:
    DataLoader(std::shared_ptr<Dataset> dataset);
    std::array<torch::Tensor, 2> get_next_observation();
    std::shared_ptr<Dataset> get_dataset_ptr();

    // friend std::ostream& operator<<(std::ostream& os, const DataLoader& loader);

private:
    std::shared_ptr<Dataset> dataset_;
    int current_index_;
    void reset_head_();
};

#endif // DATALOADER_H
