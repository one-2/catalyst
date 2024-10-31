- storage_directory: std::string
- system_logs: std::list<Log>
- debug_logs: std::list<LogEntry>
- Info:
+ LogBook(storage_directory_path: std::string&)
+ LogBook(serialised_directory: std::string&)
+ write_log(type: std::string, log: LogEntry)
+ const read_logs(type: std::string&): std::list<LogEntry>
+ serialise(): std::string
+ static deserialise(std::string&): ...