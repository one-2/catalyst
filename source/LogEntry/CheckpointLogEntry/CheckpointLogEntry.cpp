#include "CheckpointLogEntry.h"
<<<<<<< HEAD
#include "Model/Model.h"
#include <fstream>
#include "errors/DeserialisationError.h"

using namespace logging;
using namespace datastores;

std::string type = "checkpoint";

// CheckpointLogEntry::CheckpointLogEntry(int epoch, int cycle, Model model) 
//     : LogEntry(
//         epoch, 
//         cycle, 
//         std::make_unique<DataList<std::string, std::string>>(Datum<std::string, std::string>{Datum<std::string, std::string>("checkpoint", model.serialize())}),
//         type) 
// {}

// std::shared_ptr<Model> CheckpointLogEntry::load_model()
// {
    // try {
    //     std::string model_serial = retrieve_model_serial();
    //     return Model::deserialize(model_serial);
    // } catch (std::domain_error& e) {
    //     return nullptr;
    // } catch (errors::DeserializationError& e) {
    //     throw e;
    // }
// }
=======
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
>>>>>>> parent of 6f94ea2 (Add source-root pathing and more work on LogEntry subclasses)
