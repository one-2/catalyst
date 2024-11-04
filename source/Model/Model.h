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

#include <list>
#include <string>
#include <memory>
#include <vector>
#include "Block/Block.h" // TODO: unmet dependency
#include "datahandlers/DataLoader/DataLoader.h"
#include "LogBook/LogBook.h"

class Model
{
public:
    // Constructor
    Model(std::string storage_directory_path, std::string device);

    // Compose model
    void add_block(std::string type);
    
    // Train/inference
    void train(DataLoader dataloader, int batch_size, int epochs, int cycles_per_epoch);
    void evaluate(DataLoader dataloader, int batch_size, int cycles_per_epoch);
    
    // Getters
    const LogBook get_logbook() const;
    const std::list<LogEntry> get_train_logs();
    const std::list<LogEntry> get_validation_logs();
    const std::list<LogEntry> get_test_logs();
    const std::vector<Block> get_blocks() const;

    const serialise();
    static deserialise(std::string);

private:
    void compile();

    LogBook logbook;
    std::vector<Block> blocks; // TODO: unmet dependency
    bool execute_on_gpu;
};

#endif // MODEL_H
