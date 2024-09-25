#ifndef Log.h
#define Log.h

class Log
{
public:
    Log(std::string directory);
    int log_info(std::string message);
    int log_exception(std::exception exception);
    int log_debugging(std::string message);
    std::string get_logs(std::string path);
    std::ostream& operator<<;

private:
    std::string directory;
}

#endif // LOG_H
