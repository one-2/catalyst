#include "CheckpointLogEntry.h"
#include "Model.h"
#include <fstream>

CheckpointLogEntry::CheckpointLogEntry(Model model) : model(model) {}

void CheckpointLogEntry::save() {
    // std::ofstream outFile("checkpoint.dat", std::ios::binary);
    // if (outFile.is_open()) {
    //     model.serialize(outFile);
    //     outFile.close();
    // } else {
    //     // Handle error
    // }
}

void CheckpointLogEntry::load() {
    // std::ifstream inFile("checkpoint.dat", std::ios::binary);
    // if (inFile.is_open()) {
    //     Model m = model.deserialize(inFile);
    //     inFile.close();
    // } else {
    //     // Handle error
    // }
}