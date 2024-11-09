
#include "./Block.h"

#include <string>


Block::Block(std::string& type)
{ // TODO tests
    this->type = type;
}

std::string Block::get_type()
{ // TODO tests
    return type;
}
