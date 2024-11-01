#include "LogEntry/DataList/DataList.h"

DataList::DataList(std::list<Datum> data) : data_(data) {} // For deserialisation

// Add data
void DataList::add_datum(std::string key, std::string value) {
    data_.push_back(Datum(key, value));
}

// (const) Iterators
std::list<Datum>::const_iterator DataList::begin() {
    return data_.begin();
}

std::list<Datum>::const_iterator DataList::end() {
    return data_.end();
}

// Serialisation
const std::string DataList::serialise(const DataList& data_list) {
    std::stringstream ss;
    {
        cereal::JSONOutputArchive archive(ss);
        archive(cereal::make_nvp("data_list", data_list));
    }
    return ss.str();
}

// Deserialisation
DataList DataList::deserialise(const std::string& data) {
    DataList data_list = DataList();
    std::istringstream ss(data); // Doesn't need extra scope {} because its local is small
    cereal::JSONInputArchive archive(ss);
    archive(cereal::make_nvp("data_list", data_list));
    return data_list;
}

DataList::DataList(std::list<Datum> data) // For deserialisation subroutine
{
    data_ = data;
}