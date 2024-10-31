#ifndef MODEL_H // prevent multiple linking/reference errors
#define MODEL_H

#include <list>

class Model
{
public:
    Model();
    int train();
    int validate();
    int test();
    int add_log(std::string type, std::string message);
    // std::list<int> get_epoch_and_cycle() const;
    // std::string serialise();
    // std::string deserialise();

private:
    // std::vector<Log> logs;
    int epoch; // Default -1 (not running)
    int cycle; // Default -1 (not running)
};

#endif // MODEL_H
