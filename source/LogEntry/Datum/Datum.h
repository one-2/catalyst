// source/LogEntry/Datum.h
//
// Author: Stephen Elliott
//
// Date: 2024-11-01
//
// Description: Data storage format for DataList. In LogEntry.
//

#ifndef DATUM_H
#define DATUM_H

#include <string>
#include <list>

class Datum {
public:
    friend DataList;
    Datum::Datum(std::string key, std::variant<int, double, std::string> value);

    const std::string serialise_datum(Datum datum);
    static std::unique_ptr<const Datum> deserialise_datum(const std::string& data);

private:
    std::string key_;
    std::variant<int, double, std::string> value_;
};

#endif // DATUM_H
