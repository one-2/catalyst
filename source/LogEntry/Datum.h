#ifndef DATUM_H
#define DATUM_H

#include <string>
#include <list>

struct Datum {
    std::string key;
    std::string value;
};

std::string LogEntry::serialise_datum(Datum datum) const {
    std::stringstream ss;
    {
        cereal::JSONOutputArchive archive(ss);
        archive(cereal::make_nvp("key", datum.key),
                cereal::make_nvp("value", datum.value));
    }
    return ss.str();
}

typedef std::list<Datum> DataList;

#endif // DATUM_H
