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
#include <variant>

namespace datastores {
class Datum {
public:
    friend class DataList; // To allow instantiation in DataList

    // Constructor for DataList and deserialisation
    Datum(std::string key, std::variant<int, double, std::string> value);
    //
    // Note: Poorly encapsulated so I can use it in analysis classes later
    //       Also too hard to encapsulate properly.
    //

    const std::string serialise_datum() const; // NOTE: Const propogates down here from LogEntry.
    static std::unique_ptr<const Datum> deserialise_datum(const std::string& data);
    // To allow instantiation by deserialisation

    // Getters
    const std::string get_key() const;

private:

    std::string key_;
    std::variant<int, double, std::string> value_;
};
}

#endif // DATUM_H
