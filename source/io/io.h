// source/IO/IO.h
//
// Author: Stephen Elliott
//
// Date: 2024-10-25
//
// Description: Header for data io.
//
#ifndef IO_H
#define IO_H

#include <string>
#include <torch/torch.h>
#include "../Model/Model.h"

namespace io {
    torch::Tensor load_tensor_from_csv(std::string path);
    // Model load_checkpoint(std::string path);
    // std::string write_checkpoint(std::string path, std::string label);
}

#endif // IO_H
