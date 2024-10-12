// Model.cpp
//
// Stephen Elliott, September 2024
//
// This file defines the Model abstract class, an interface to modelling classes. Onwards and upwards.
//

#include <vector>
#include <variant>
#include <iostream>

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

// Model constructor (abstract)
Model::Model()
{
    // Initialise the training and evaluation histories
    training_history = ModelHistory();
    evaluation_history = ModelHistory();
}

// Overload << operator to print model information
std::ostream& operator<<(std::ostream& os, const Model& model)
{
    os << "Model information: TODO" << std::endl;
    return os;
}
