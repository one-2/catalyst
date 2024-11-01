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
    void push_back(std::string key, std::string value);
    void pop_back();

    const std::string serialise(const DataList& data_list);
    static DataList deserialise(const std::string& data);

private:
    DataList(std::list<Datum> data); // For deserialisation subroutine
    std::list<Datum> data_;
};

#endif // DATALIST_H