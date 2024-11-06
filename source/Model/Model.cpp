// source/Model/Model.h
//
// Author: Stephen Elliott
//
// Date: 2024-10-28
//
// Description: 
//

#include "./Model.h"

Model::Model(std::string& storage_directory, std::string& device)
    // : LogBook(storage_directory)
{
    this->execute_on_gpu = device == "gpu";
}
//
// NOTE: Copped a bug here because I didn't explicitly initialise the LogBook.
//       "In C++, member variables are initialized in the order they are declared
//       in the class, and this initialization happens before the constructor body
//       is executed. If you don't explicitly initialize a member variable in the
//       constructor's initializer list, the compiler will try to use the default
//       constructor for that member.""
//


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

// logging::LogBook Model::get_logbook() const
// {
//     // TODO
//     return 0;
// }


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

// logging::LogBook Model::get_LogBook() const
// {
//     return LogBook;
// }


void Model::compile()
{
    // Compile method implementation
}
