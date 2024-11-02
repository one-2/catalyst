// source/LogEntry/DataList/DataList.h
//
// Author: Stephen Elliott
//
// Date: 2024-11-01
//
// Description: Container for Datum objects.
#ifndef DATALIST_H
#define DATALIST_H

#include "Datum.h"
#include <list>
#include <cereal/types/list.hpp>

template <typename K, typename V>
class DataList : public IDataList {
public:
    using iterator = typename std::list<datastores::Datum<K, V>>::const_iterator;

    iterator begin() const { return data_.begin(); }
    iterator end() const { return data_.end(); }

    // Constructors
    DataList() = default;
    DataList(std::list<datastores::Datum<K, V>> data) : data_(std::move(data)) {}

private:
    std::list<datastores::Datum<K, V>> data_;

    // Serialization
    template <class Archive>
    void serialize(Archive& ar) {
        ar(data_);
    }
};

#endif // DATALIST_H