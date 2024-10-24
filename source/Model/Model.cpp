// Model.cpp
//
// Stephen Elliott, September 2024
//
// This file contains the Model abstract class.
// Model is defines an interface to all statistical
// modelling methods.
//
// Onwards and upwards.
//

#include <vector>
// #include "../log/log.h"
#include <string>
#include "./Model.h"

Model::Model() {}

int add_layer(std::string activation,
              std::string out_connection,
              int width)
{
    return 0;
}

int Model::train()
{
    return 0;
}

int Model::validate()
{
    return 0;
}

int Model::test()
{
    return 0;
}

int Model::add_log(std::string type, std::string message)
{
    return 0;
}

// std::ostream& operator<<;
