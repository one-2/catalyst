#include "CheckpointLogEntry.h"
#include "Model/Model.h"
#include <fstream>
#include "errors/DeserialisationError.h"

using namespace logging;
using namespace datastores;

std::string type = "checkpoint";

CheckpointLogEntry::CheckpointLogEntry(int epoch, int cycle, Model model) 
    : LogEntry(
        epoch, 
        cycle, 
        std::make_unique<DataList<std::string, std::string>>(Datum<std::string, std::string>{Datum<std::string, std::string>("checkpoint", model.serialize())}),
        type) 
{}

std::shared_ptr<Model> CheckpointLogEntry::load_model()
{
    try {
        std::string model_serial = retrieve_model_serial();
        return Model::deserialize(model_serial);
    } catch (std::domain_error& e) {
        return nullptr;
    } catch (errors::DeserializationError& e) {
        throw e;
    }
}
