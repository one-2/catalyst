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
    std::string write_log(const std::string& serialised_log, const std::string& directory);
    void build_directory_path(const std::string& directory);
}

#endif // IO_H
