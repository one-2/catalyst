// Model.cpp
//
// Stephen Elliott, September 2024
//
// This file defines the Model abstract class, an interface to modelling classes.
//
// Onwards and upwards.
//

#include <vector>
#include <variant>
#include <iostream>

#include "../Log/Log.h"

class Model
{
private:
    // How to store training results? Weights? Losses? Intermediate checkpoints?

public:
    Model();
    virtual void train(std::vector<std::variant<int, float>>::iterator data) = 0;
    virtual void evaluate(std::vector<std::variant<int, float>>::iterator data) = 0;

    friend std::ostream& operator<<(std::ostream& os, const Model& model);
};

Model::Model()
{
    //
}

std::ostream& operator<<(std::ostream& os, const Model& model)
{
    os << "Model information: TODO" << std::endl;
    return os;
}
