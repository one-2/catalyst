// source/Model/Model.h
//
// Author: Stephen Elliott
//
// Date: 2024-10-28
//
// Description: 
//
// Usage: 
//
#ifndef MODEL_H // prevent multiple linking/reference errors
#define MODEL_H

#include <vector>
#include <variant>
#include <iostream>
#include "../DataLoader/DataLoader.h"
#include "../Logbook/Logbook.h"

class Model
{
private:
    std::string type;
    Logbook logbook;

public:
    Model(std::string type, std::string storage_directory_path);
    void train(DataLoader dataloader, int epochs, int batch_size) = 0;
    void evaluate(DataLoader dataloader) = 0;
    std::shared_ptr<Logbook> get_logbook();
    virtual void serialise() = 0; //NOTE: Pure virtual <=> Abstract function
    virtual Model deserialise(std::string) = 0;
    void write_checkpoint() final; //NOTE: Impure virtual, final => no override
    // friend std::ostream& operator<<(std::ostream& os, const Model& model);
};

#endif // MODEL_H
