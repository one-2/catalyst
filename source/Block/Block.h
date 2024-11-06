// source/Block/Block.h
//
// Author: Stephen Elliott
//
// Date: 2024-11-04
//
// Description: 
//
// Usage: 
//
#ifndef BLOCK_H
#define BLOCK_H


#include <string>


class Block
{
protected: // NOTE: Had a bug here. Methods/attributes default to PRIVATE scope. Not public.
    Block(std::string& type);

    std::string type;
};


#endif // BLOCK_H