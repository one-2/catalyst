#ifndef MODEL_H // prevent multiple linking/reference errors
#define MODEL_H

class Model
{
public:
    Model();
    int train();
    int validate();
    int test();
    int add_log(std::string type, std::string message);
    // std::ostream& operator<<;

private:
    // std::vector<Log> logs;
};

#endif // MODEL_H
