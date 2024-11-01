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

// Nested in DataList
class DataList {
public:
    friend class LogEntry;

    void add_datum(std::string key, std::string value);
    
    // Iterators
    std::list<Datum>::const_iterator begin();
    std::list<Datum>::const_iterator end();

    const std::string serialise(const DataList& data_list);
    static DataList deserialise(const std::string& data);

protected:
    DataList(); // For initial construction in LogEntry subclasses

private:
    DataList(std::list<Datum> data); // For deserialisation subroutine
    std::list<Datum> data_;
};

#endif // DATALIST_H