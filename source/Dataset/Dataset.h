// source/Dataset/Dataset.h
//
// Author: Stephen Elliott
//
// Date: 2024-10-13
//
// Description: Header file for the Dataset class.
//
// Usage: 
//

#ifndef DATASET_H
#define DATASET_H

#include <vector>
#include <variant>
#include <iostream>
#include <torch/torch.h>

class Dataset
{
public:
    Dataset(std::string path, int target_variable_index);
    Dataset(torch::Tensor input, torch::Tensor output, int start_index, int length);
    std::array<std::shared_ptr<Dataset>, 3> split(float train, float validate, float test);
    int get_length();
    friend std::ostream& operator<<(std::ostream& os, const Dataset& dataset);
    torch::Tensor input;
    torch::Tensor target;

private:
    std::array<int, 3> compute_split_lengths(float train, float validate, float test);
};

#endif // DATASET_H
