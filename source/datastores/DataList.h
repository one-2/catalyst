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
#include "datastores/Datum.h"
#include "datastores/IDataList.h"

namespace datastores {

template <typename K, typename V>
class DataList : public IDataList {
public:
    // Emplace data
    void add_datum(const K& key, const V& value) {
        data_.emplace_back(key, value);
    }
    
    // Iterators
    std::list<Datum<K, V>>::const_iterator begin() const;
    std::list<Datum<K, V>>::const_iterator end() const;

    // De/serialisation
    template <class Archive>
    void serialize(Archive& ar) {
        ar(cereal::base_class<IDataList>(this),
           cereal::make_nvp("data", data_));
    }

    // Constructors
    DataList() = default; // For constructors
    DataList(std::list<Datum<K, V>> data); // For serialisation, constructors. And analysis classes later.
    
    //
    // NOTE: Friendship is not inherited.
    //

private:
    std::list<Datum<K, V>> data_;

    // // Register with Cereal for polymorphic serialization
    // CEREAL_REGISTER_TYPE(DataList<K, V>)
};
}

#endif // DATALIST_H