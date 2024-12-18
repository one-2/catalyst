// source/io/io.cpp
//
// Author: Stephen Elliott
//
// Date: 2024-10-25
//
// Description: Data input-output.
//

#include <torch/torch.h>


#include "./io.h"

#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>


namespace io {

torch::Tensor load_tensor_from_csv(std::string path) {
    //Set up the bit stream, buffer, and container
    std::ifstream file(path);
    std::string line;
    std::vector<std::vector<float>> data;

    std::getline(file, line); //Skip the header row

    while (std::getline(file, line)) {
        //For every line
        std::stringstream ss(line); //Open a stream on the line
        std::string item;
        std::vector<float> row;

        while (std::getline(ss, item, ',')) { //For every comma-delimited segment
            row.push_back(std::stof(item)); //Add the line onto the row vector
        }
        data.push_back(row); //Append the row vector to the outer vector
    }
    
    torch::Tensor tensor_data = torch::empty({static_cast<long>(data.size()), static_cast<long>(data[0].size())}, torch::kFloat64);

    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data[i].size(); ++j) {
            tensor_data[i][j] = data[i][j]; //Fill the tensor with the data read into the vector before
        }
    }

    return tensor_data;

}

std::string write_log(const std::string& serialized_log, const std::string& path) {
    std::ofstream log_file(path, std::ios::app); // Open file in append mode
    if (!log_file.is_open()) {
        throw std::runtime_error("Could not open log file: " + path);
    }
    log_file << serialized_log; // Write the log entry
    log_file.close();
    return path;

}

void build_directory(const std::string& directory) {
    std::filesystem::path dir_path(directory);
    if (!std::filesystem::exists(dir_path)) {
        std::filesystem::create_directories(dir_path);
    }

}

} // namespace io
