// Model.cpp
//
// Stephen Elliott, September 2024
//
// This file contains the Model abstract class.
// Model is defines an interface to all statistical
// modelling methods.
//
// Onwards and upwards.
//

#include "./Model.h"

Model::Model(std::string& storage_directory, std::string& device) {
    this->execute_on_gpu = device == "gpu";
    this->LogBook = logging::LogBook(storage_directory);
}

Model::Model() : epoch(-1), cycle(-1), execute_on_gpu(false) {
    // TODO
}

int Model::train(datahandlers::DataLoader& dataloader, int batch_size, int epochs) {
    // TODO
    return 0;
}

int Model::evaluate(datahandlers::DataLoader& dataloader, int batch_size, int epochs) {
    // TODO
    return 0;
}

int Model::add_log(std::string type, std::string message) {
    // TODO
    return 0;
}

int Model::get_epoch() const {
    return epoch;
}

int Model::get_cycle() const {
    return cycle;
}

std::string Model::get_name() const {
    return name;
}

logging::Logbook Model::get_logbook() const {
    return logbook;
}

void Model::compile() {
    // Compile method implementation
}