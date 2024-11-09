// source/Model/Model.h
//
// Author: Stephen Elliott
//
// Date: 2024-10-28
//
// Description: 
//

#include "./Model.h"

#include <chrono>


Model::Model(std::string& storage_directory, std::string& device, std::string& name)
    : logbook(logging::LogBook(storage_directory)) // Initialize LogBook member variable
{
    this->execute_on_gpu = device == "gpu";
    this->name = name;
    this->timestamp = std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
    this->epoch = -1;
    this->cycle = -1;
}

//  ^^^
// NOTE: Copped a bug here because I didn't explicitly initialise the LogBook.
//       "In C++, member variables are initialized in the order they are declared
//       in the class, and this initialization happens before the constructor body
//       is executed. If you don't explicitly initialize a member variable in the
//       constructor's initializer list, the compiler will try to use the default
//       constructor for that member."
//


void Model::add_block(std::shared_ptr<Block> block)
{
    blocks.push_back(block);
}


int Model::train(datahandlers::DataLoader& dataloader, int batch_size, int epochs)
{
    // TODO
    return 0;
}


int Model::evaluate(datahandlers::DataLoader& dataloader, int batch_size, int epochs)
{
    // TODO
    return 0;
}


std::vector<std::shared_ptr<Block>> Model::get_blocks()
{
    return blocks;
}


int Model::get_epoch() const
{
    return epoch;
}


int Model::get_cycle() const
{
    return cycle;
}


std::string Model::get_name() const
{
    return name;
}

std::string Model::get_timestamp() const
{
    return timestamp;
}

logging::LogBook Model::get_logbook() const
{
    return logbook;
}

std::string Model::get_device() const
{
    return execute_on_gpu ? "gpu" : "cpu";
}

void Model::compile()
{
    // TODO
    // Compile method implementation
}
