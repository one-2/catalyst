#ifndef MODEL_H // prevent multiple linking/reference errors
#define MODEL_H

#include <vector>
#include <variant>
#include <iostream>
#include "../DataLoader/DataLoader.h"

class Model
{
private:
    std::string type;
    Logbook logbook;

public:
    Model(std::string type, std::string logging_path);
    void train(DataLoader dataloader, int epochs, int batch_size);
    int evaluate(DataLoader dataloader);
    const Logbook& get_logbook() const;
    static void serialise() = 0; //NOTE: Abstract static
    static Model deserialise(std::string) = 0;
    void write_checkpoint();
    // friend std::ostream& operator<<(std::ostream& os, const Model& model);
};

#endif // MODEL_H
