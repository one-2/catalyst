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
#include "DataLoader/DataLoader.h"


class Dataset
{
private:
    struct data_point
    {
        int index;
        std::vector<std::variant<int, float>> predictors;
        std::variant<int, float> target;
    }

    std::vector<data_point> data;

public:
    DataLoader get_dataloader();
    std::tuple<Dataset, Dataset, Dataset> split(float train, float test, float validate);
    int length();
    friend std::ostream& operator<<(std::ostream& os, const Dataset& dataset);
};

#endif // DATASET_H
