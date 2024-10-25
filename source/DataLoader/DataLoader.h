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
#include "../Dataset/Dataset.h"

class DataLoader {
private:
    DataSet& dataset;
public:
    DataLoader(DataSet& dataset);
    friend std::ostream& operator<<(std::ostream& os, const DataLoader& loader);
};

#endif // DATALOADER_H
