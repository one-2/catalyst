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

#include <vector>
#include <iostream>
#include <torch/torch.h>
#include "../Dataset/Dataset.h"
#include <memory>

class DataLoader {
public:
    DataLoader(std::shared_ptr<Dataset> dataset);
    torch::Tensor get_next_value_tensor();
    std::shared_ptr<Dataset> get_dataset_ptr();

    // friend std::ostream& operator<<(std::ostream& os, const DataLoader& loader);

private:
    std::shared_ptr<Dataset> _dataset;
    int _current_index;
    void _reset_head();
};

#endif // DATALOADER_H
