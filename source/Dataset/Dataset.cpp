// source/Dataset/Dataset.cpp
//
// Author: Stephen Elliott
//
// Date: 2024-10-25
//
// Description: 
//
// Usage: 
//

#include <torch/torch.h>
#include <array>
#include "./Dataset.h"
#include "../io/io.h"

//
// Loads a dataset from a given csv path
//
Dataset::Dataset(std::string path, int target_variable_index) {
    torch::Tensor data = io::load_tensor_from_csv(path);

    //Save input
    torch::Tensor first_part = data.index({torch::indexing::Slice(), torch::indexing::Slice(torch::indexing::None, target_variable_index)});
    torch::Tensor second_part = data.index({torch::indexing::Slice(), torch::indexing::Slice(target_variable_index + 1, torch::indexing::None)});
    this->input = torch::cat({first_part, second_part});

    //Save target
    this->target = data.index({torch::indexing::Slice(), target_variable_index});
};

//
// Load a dataset by splitting a parent dataset
//
Dataset::Dataset(torch::Tensor input, torch::Tensor output, int start_index, int length) {
    torch::Tensor truncated_input = input.index({torch::indexing::Slice(start_index, length), torch::indexing::Slice()});
    torch::Tensor truncated_output = output.index({torch::indexing::Slice(start_index, length), torch::indexing::Slice()});

    this->input = truncated_input;
    this->target = truncated_output;
}

//
// Split the dataset three ways
//
std::array<std::shared_ptr<Dataset>, 3> Dataset::split(float train, float validate, float test) {
    //Compute lengths to split the dataset into
    std::array<int, 3> split_lengths = this->compute_split_lengths(train, validate, test);

    //Split the dataset
    auto train_set = std::make_shared<Dataset>(input, target, 0, split_lengths[0]);
    auto validate_set = std::make_shared<Dataset>(input, target, split_lengths[0], split_lengths[1]);
    auto test_set = std::make_shared<Dataset>(input, target, split_lengths[1], split_lengths[2]);

    return std::array<std::shared_ptr<Dataset>, 3> {train_set, validate_set, test_set};
}

//
// Convert percentage split length arguments into integers
//
std::array<int, 3> Dataset::compute_split_lengths(float train, float validate, float test) {
    //Compute required dataset lengths
    int length = this->get_length();
    int train_length = int(length * train);
    int validate_length = int(length * validate);
    int test_length = int(length * test);
    
    //Correct underflow due to typecasting
    auto underflow_length = [length, train_length, validate_length, test_length]() {
        return length - (train_length + validate_length + test_length);
    };

    while (underflow_length() > 0) {

        //Use the modulus of the underflow to redistribute spare samples
        switch (underflow_length() % 3) {
            case 0:
                train_length++;
                if (train_length == 0 || underflow_length() == 0) {
                    break;
                }
            case 1:
                validate_length++;
                if (validate_length == 0 || underflow_length() == 0) {
                    break;
                }
            case 2:
                test_length++;
                if (test_length == 0 || underflow_length() == 0) {
                    break;
                }
        }
    }

    return std::array<int, 3> {train_length, validate_length, test_length};
}

//
// Get the length of the dataset
// 
int Dataset::get_length() {
    // Implementation for returning the length of the dataset
    return this->input.size(1); //Queries dimension 1
}

//
// Output dataset info to ostream
//
std::ostream& operator<<(std::ostream& os, Dataset& dataset) { //Maybe Dataset& should be const? 
    os << "Dataset details: " << dataset.get_length();
    return os;
}
