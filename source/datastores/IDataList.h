// source/LogEntry/IDataList.h
#ifndef IDATALIST_H
#define IDATALIST_H

#include <cereal/types/polymorphic.hpp>

namespace datastores {

class IDataList {
public:
    virtual ~IDataList() = default;

    // Serialization interface
    template <class Archive>
    void serialize(Archive& ar) {
        // Base class has no data to serialize
    }
};

} // namespace datastores

CEREAL_REGISTER_TYPE(datastores::IDataList)

#endif // IDATALIST_H