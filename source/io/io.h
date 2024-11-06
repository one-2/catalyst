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
    // Load
    torch::Tensor load_tensor_from_csv(std::string path);

    // Pathing
    void build_directory(const std::string& directory);

    // Write
    std::string write_log(const std::string& serialized_log, const std::string& path);

}

#endif // IO_H
