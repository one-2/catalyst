#ifndef MODEL_H // prevent multiple linking/reference errors
#define MODEL_H

#include <vector>
#include <variant>
#include <iostream>

class Model
{
private:


public:
    Model();

    virtual void train(DataLoader data) = 0;
    virtual void evaluate(DataLoader data) = 0;

    friend std::ostream& operator<<(std::ostream& os, const Model& model);
};

#endif // MODEL_H
