// source/io/io.cpp
//
// Author: Stephen Elliott
//
// Date: 2024-10-25
//
// Description: Data input-output.
//

#include <torch/torch.h>
#include <string>
#include "../Model/Model.h"
#include "io.h"

namespace io {
    torch::Tensor load_from_csv(std::string path) {
        return torch::Tensor();
    }


    Model load_checkpoint(std::string path) {
        return Model();
    }

    std::string write_checkpoint(std::string path, std::string label) {
        return "";
    }

}
