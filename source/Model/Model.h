#ifndef MODEL_H // prevent multiple linking/reference errors
#define MODEL_H

#include <list>
#include <string>
#include <memory>

class Model
{
public:
    Model(std::string serialized_model);
    Model();

    int train();
    int validate();
    int test();
    int add_log(std::string type, std::string message);
    // std::list<int> get_epoch_and_cycle() const;
    std::string serialize();
    static std::shared_ptr<Model> deserialize(std::string& serialized_model);

protected:

private:
    // std::vector<Log> logs;
    int epoch; // Default -1 (not running)
    int cycle; // Default -1 (not running)
};

#endif // MODEL_H
