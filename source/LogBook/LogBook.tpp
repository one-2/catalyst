// LogBook.tpp

#ifndef LOGBOOK_TPP
#define LOGBOOK_TPP

#include <future>
#include <utility> // For std::forward
#include "LogBook/LogBook.h"

namespace logging {

// Template member function definition
template<typename LogEntryType, typename... Args>
void LogBook::log_async(Args&&... args) {
    // Launch an asynchronous task
    auto future = std::async(std::launch::async, [this, args...]() mutable {
        // Create an instance of LogEntryType with forwarded arguments
        LogEntryType log_entry(std::forward<Args>(args)...);

        // Add the log entry to the internal map
        add_log_to_map(log_entry);

        // Serialize the log entry
        std::string serialized_log = log_entry.serialize();

        // Generate the log path (implementation assumed)
        std::string path = generate_log_path(log_entry);

        // Write the serialized log to the specified path
        io::write_log(serialized_log, path);
    });

    // Optionally, you can store the future if you need to manage it later
    // For example:
    // futures_.emplace_back(std::move(future));
}

} // namespace logging

#endif // LOGBOOK_TPP
