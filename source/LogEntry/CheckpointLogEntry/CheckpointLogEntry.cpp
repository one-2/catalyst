#include "CheckpointLogEntry.h"
#include "../../Model/Model.h"
#include <fstream>
#include "errors/DeserializationError.h"

CheckpointLogEntry::CheckpointLogEntry(int epoch, int cycle, Model model) : LogEntry(epoch, cycle, DataList{Datum{"model", model.serialise()}}, "checkpoint") {}

std::shared_ptr<Model> CheckpointLogEntry::load_model()
{
    try {
        std::string model_serial = retrieve_model_serial();
        return Model::deserialise(model_serial);
    } catch (std::domain_error& e) {
        return nullptr;
    } catch (errors::DeserializationError& e) {
        throw e;
    }
}

std::string CheckpointLogEntry::retrieve_model_serial()
{
    std::string search_key = "checkpoint";
    auto result = std::find_if(data.begin(), data.end(), [&search_key](const Datum datum)
                               { return datum.key == search_key; });

    if (result == data.end())
    {
        throw std::domain_error(
            "ERROR: Log data does not contain key \"checkpoint\". \
            This is probably not a checkpoint log.\
            Best of luck.");
    };
}
