// source/LogEntry/Datum.cpp
//
// Author: Stephen Elliott
//
// Date: 2024-11-01
//

#include <string>
#include <sstream>
#include <cereal/archives/json.hpp>
#include <cereal/types/string.hpp>
#include "Datum.h"
#include <variant>

Datum::Datum(std::string key, std::variant<int, double, std::string> value) {};

// Serialisation
const std::string Datum::serialise_datum(Datum datum)
{
    std::stringstream ss;
    {
        cereal::JSONOutputArchive archive(ss);
        archive(cereal::make_nvp("key", datum.key_),
                cereal::make_nvp("value", datum.value_));
    }
    return ss.str();
}

// Deserialisation
std::unique_ptr<const Datum> Datum::deserialise_datum(const std::string& data)
{
    auto datum = std::make_unique<Datum>();
    std::stringstream ss(data);
    {
        cereal::JSONInputArchive archive(ss);
        archive(cereal::make_nvp("key", datum->key_),
                cereal::make_nvp("value", datum->value_));
    }
    return std::move(datum);
}
