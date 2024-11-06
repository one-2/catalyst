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

#include "logging/LogBook/LogBook.h"
#include "Block/Block.h"

#include <list>
#include <string>
#include <memory>
#include <vector>
#include <cereal/archives/json.hpp>

#include "Block/Block.h" // TODO: unmet dependency
#include "datahandlers/DataLoader/DataLoader.h"
#include "LogBook/LogBook.h"


namespace datahandlers {
    class DataLoader;
}


class Model
{
public:
    // Construction
    Model() = default;
    Model(std::string& storage_directory, std::string& device);

    // Inference
    int train(datahandlers::DataLoader& dataloader, int batch_size, int epochs);
    int evaluate(datahandlers::DataLoader& dataloader, int batch_size, int epochs);

    // Logging
    int add_log(std::string type, std::string message);

    // Getters
    int get_epoch() const;
    int get_cycle() const;
    std::string get_name() const;
    // logging::LogBook get_LogBook() const;

    // // Serialisation
    // std::string serialize();
    // static std::shared_ptr<Model> deserialize(std::string& serialized_model);


private:
    // Inference
    void compile();

    // Data
    // logging::LogBook LogBook;
    std::vector<Block> blocks;
    int epoch; // Default -1 (not running)
    int cycle; // Default -1 (not running)
    std::string name = "Model"; // TODO: Initialise as unique identifier (hash or code) in constructor

    // Flags
    bool execute_on_gpu;

};

#endif // MODEL_H
