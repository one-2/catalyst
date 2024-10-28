// source/Model/Model.cpp
//
// Author: Stephen Elliott
//
// Date: 2024-10-28
//
// Description: Defines Model abstract superclass
//
// Usage: 
//

#include <vector>
#include <variant>
#include <iostream>

#include "./Model.h"

//
// Constructor
//
Model::Model(std::string type, std::string storage_directory_path) {
    this->type = type;
    this->logbook = Logbook(storage_directory_path);
}

//
// Run a training cycle
//
void Model::train(DataLoader dataloader, int epochs, int batch_size) = 0;

//
// Run an evaluation cycle
//
int Model::evaluate(DataLoader dataloader) = 0;

//
// Fetch the model logbook
//
std::shared_ptr<Logbook> Model::get_logbook() {
    return std::make_shared<Logbook>(this->logbook);
}

//
// Serialise the model (using Protobuf)
//
virtual void Model::serialise() = 0;

//
// Deserialise the model (using Protobuf)
//
virtual Model deserialise(std::string) = 0;

//
// Write a checkpoint using the LogBook
//
void Model::write_checkpoint() final {
    // Assuming logbook has a method to write a checkpoint
    this->logbook.write_log("checkpoint", serialise());
}
