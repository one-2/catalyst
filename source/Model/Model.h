#ifndef MODEL_H // prevent multiple linking/reference errors
#define MODEL_H

#include <list>

class Model
{
public:
<<<<<<< HEAD
    Model(std::string serialized_model);
    
=======
    Model();
>>>>>>> parent of 6f94ea2 (Add source-root pathing and more work on LogEntry subclasses)
    int train();
    int validate();
    int test();
    int add_log(std::string type, std::string message);
    // std::list<int> get_epoch_and_cycle() const;
<<<<<<< HEAD
    std::string serialize();
    static std::shared_ptr<Model> deserialize(std::string& serialized_model);

protected:
    Model();
=======
    // std::string serialise();
    // std::string deserialise();
>>>>>>> parent of 6f94ea2 (Add source-root pathing and more work on LogEntry subclasses)

private:
    // std::vector<Log> logs;
    int epoch; // Default -1 (not running)
    int cycle; // Default -1 (not running)
};

#endif // MODEL_H
