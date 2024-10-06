#ifndef Model.h // prevent multiple linking/reference errors
#define Model.h

class Model
{
public:
    int Model();
    int train();
    int validate();
    int test();
    int add_log(std::string type, std::string message);
    std::ostream& operator<<;

private:
    std::vector<Log> logs;
}

#endif // MODEL_H
