// source/Model/Model.h
//
// Author: Stephen Elliott
//
// Date: 2024-10-28
//
// Description: 
//

// class Model
// {
// public:
//     Model(std::string storage_directory_path, std::string device);
//     void add_block(std::string type);
//     void train(DataLoader dataloader, int batch_size);
//     void evaluate(DataLoader dataloader, int batch_size);
//     const LogBook get_logbook();
//     const serialise();
//     static deserialise(std::string);

// private:
//     void compile();

//     LogBook logbook;
//     std::vector<Block> blocks; // TODO: unmet dependency
//     bool execute_on_gpu;
// };
#include "./Model.h"



Model::Model(std::string storage_directory_path, std::string device)
{
    execute_on_gpu = device == "gpu"; // declare the gpu attribute
    logbook = LogBook(storage_directory_path); // create the logbook
}

void Model::add_block(std::string type)
{
    // Todo
}

void Model::train(DataLoader dataloader, int batch_size)
{
    // Todo
}

void Model::evaluate(DataLoader dataloader, int batch_size)
{
    // Todo
}

const Model::LogBook get_logbook()
{
    // Todo
}

const Model::serialise()
{
    // Todo
}

static Model::deserialise(std::string)
{
    // Todo
}
