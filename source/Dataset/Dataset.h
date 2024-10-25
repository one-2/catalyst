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
#include <tuple>
#include "../DataLoader/DataLoader.h"


class Dataset
{
public:
    Dataset(std::string path);
    Dataset::Dataset(torch::Tensor input, torch::Tensor output, int start_index, int length);
    DataLoader get_dataloader();
    std::list<Dataset> split(float train, float test, float validate);
    int get_length();
    friend std::ostream& operator<<(std::ostream& os, const Dataset& dataset);

private:
    torch::tensor input;
    torch::tensor outcome;

    std::list<int> Dataset::compute_split_lengths();
};

#endif // DATASET_H
