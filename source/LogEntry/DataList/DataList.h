// source/LogEntry/DataList/DataList.h
//
// Author: Stephen Elliott
//
// Date: 2024-11-01
//
// Description: Container for Datum objects. In LogEntry.

#ifndef DATALIST_H
#define DATALIST_H

#include <list>
#include <string>
#include <sstream>
#include <cereal/archives/json.hpp>
#include <cereal/types/list.hpp>
#include "LogEntry/Datum/Datum.h"

class DataList {
public:
    // Pusher
    void add_datum(std::string key, std::string value);
    
    // Iterators
    std::list<Datum>::const_iterator begin();
    std::list<Datum>::const_iterator end();

    // Serialisation
    const std::string serialise(const DataList& data_list);
    static DataList deserialise(const std::string& data);

    // Constructors
    DataList() = default; // For constructors
    DataList(std::list<Datum> data); // For deserialisation subroutine and logentry constructors. And analysis later
    //
    // NOTE: Friendship didn't work for this because friendship is not inherited.
    //

private:
    std::list<Datum> data_;
};

#endif // DATALIST_H