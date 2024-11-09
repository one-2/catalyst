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



namespace datahandlers {
    class DataLoader;
}


class Model
{
public:
    // Construction
    Model() = default;
    Model(std::string& storage_directory, std::string& device, std::string& name);

    // Compose model
    void add_block(std::shared_ptr<Block> block);

    // Inference
    int train(datahandlers::DataLoader& dataloader, int batch_size, int epochs);
    int evaluate(datahandlers::DataLoader& dataloader, int batch_size, int epochs);

    // Getters
    int get_epoch() const;
    int get_cycle() const;
    std::string get_name() const;
    std::string get_timestamp() const;
    std::string get_device() const;
    logging::LogBook get_logbook() const;
    std::vector<std::shared_ptr<Block>> get_blocks();

    // Serialisation                                TODO: LAST
    // std::string serialize();
    // static std::shared_ptr<Model> deserialize(std::string& serialized_model);


private:
    // Compile method for CG
    void compile();

    // Data
    logging::LogBook logbook;
    std::vector<std::shared_ptr<Block>> blocks;
    int epoch;
    int cycle;
    std::string name;
    std::string timestamp;

    // Flags
    bool execute_on_gpu;

};

#endif // MODEL_H
