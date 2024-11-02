// source/LogEntry/IDataList.h
#ifndef IDATALIST_H
#define IDATALIST_H

#include <cereal/types/polymorphic.hpp>

namespace datastores {

class IDataList {
public:
    virtual ~IDataList() = default;

private:
    // Serialization interface
    template <class Archive>
    void serialize(Archive& ar) {
        // Base class has no data to serialize
        ar();
    }
};

} // namespace datastores

// Cereal macros for polymorphism
CEREAL_REGISTER_TYPE(datastores::IDataList)

#endif // IDATALIST_H