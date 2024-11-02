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
#include <cereal/types/string.hpp>    // Cereal support for std::string
#include <cereal/types/utility.hpp>   // Cereal support for std::pair if needed

namespace datastores {

template<typename K, typename V>
class Datum {
    // Friends
    friend class cereal::access;

public:
    // Constructors
    Datum() = default; // empty
    Datum(const K& key, const V& value) : key_(key), value_(value) {} // lvalues
    Datum(K&& key, V&& value) : key_(std::move(key)), value_(std::move(value)) {} // Move constructor (rvalues)

    // Getters
    const K& get_key() const { return key_; }
    const V& get_value() const { return value_; }

private:
    K key_;
    V value_;

    // Cereal serialization function
    template <class Archive>
    void serialize(Archive& ar) {
        ar(key_, value_);
    }
};

} // namespace datastores

#endif // DATUM_H