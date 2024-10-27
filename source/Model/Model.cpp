// Model.cpp
//
// Stephen Elliott, September 2024
//
// This file defines the Model abstract class, an interface to modelling classes. Onwards and upwards.
//

#include <vector>
#include <variant>
#include <iostream>

#include "../ModelHistory"
#include "../DataLoader/DataLoader.h"
#include "../Log/Log.h"

// Model class definition
class Model
{
private:
    ModelHistory training_history;
    ModelHistory evaluation_history;

public:
    Model();
    virtual void train(DataLoader data) = 0;
    virtual void evaluate(DataLoader data) = 0;
    friend std::ostream& operator<<(std::ostream& os, const Model& model);
};

//
// Constructor
//
Model(std::string type, std::string logging_path);

//
// Run a training cycle
//
void train(DataLoader dataloader, int epochs, int batch_size);

//
// Run an evaluation cycle
//
int evaluate(DataLoader dataloader);

//
// Fetch the model logbook
//
const Logbook& get_logbook() const;

//
// Serialise the model (using Protobuf)
//
static void serialise() = 0; //NOTE: Abstract static

//
// Deserialise the model (using Protobuf)
//
static Model deserialise(std::string) = 0;

