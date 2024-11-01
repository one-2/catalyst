#ifndef SERIALIZATION_ERROR_H
#define SERIALIZATION_ERROR_H

#include <stdexcept>
#include <string>

namespace errors {
    class DeserializationError : public std::runtime_error {
    public:
        explicit DeserializationError(const std::string& message)
            : std::runtime_error(message) {}
    };
}
#endif // SERIALIZATION_ERROR_H
