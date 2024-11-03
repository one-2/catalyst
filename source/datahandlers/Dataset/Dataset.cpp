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
#include "datahandlers/Dataset/Dataset.h"
#include "io/io.h"

using namespace datahandlers;

//
// Loads a dataset from a given csv path
//
Dataset::Dataset(std::string path, int target_variable_index) {
    torch::Tensor data = io::load_tensor_from_csv(path);

    //Construct input vectors
    torch::Tensor input_first_part = data.slice(1, 0, target_variable_index); //Faster + more concise than the data.index approach. .narrow is an alternative
    torch::Tensor input_second_part = data.slice(1, target_variable_index + 1, torch::indexing::None);

    // Declare input
    if (input_first_part.size(1) == 0) { //Checks col dimension
        this->input = input_second_part;
    } else if (input_second_part.size(1) == 0) {
        this->input = input_first_part;
    } else {
        this->input = torch::cat({input_first_part, input_second_part});
    }

    // Declare target
    this->target = data.index({torch::indexing::Slice(), target_variable_index});
};

//
// Load a dataset by splitting a parent dataset
//
Dataset::Dataset(const torch::Tensor& input, const torch::Tensor& output, int start_index, int length) {
    this->input = input.slice(0, start_index, length); //Length passed as end index
    this->target = output.slice(0, start_index, length);
}

//
// Split the dataset three ways
//
std::array<std::shared_ptr<Dataset>, 3> Dataset::split(float train, float validate, float test) {
    //Compute lengths to split the dataset into
    std::array<int, 3> split_lengths = this->compute_split_lengths_(train, validate, test);

    //Split the dataset
    int train_stop = split_lengths[0];
    int validate_stop = train_stop + split_lengths[1];
    int test_stop = validate_stop + split_lengths[2];

    auto train_set = std::make_shared<Dataset>(input, target, 0, train_stop);
    auto validate_set = std::make_shared<Dataset>(input, target, train_stop, validate_stop);
    auto test_set = std::make_shared<Dataset>(input, target, validate_stop, test_stop);

    return std::array<std::shared_ptr<Dataset>, 3> {train_set, validate_set, test_set};
}

//
// Convert percentage split length arguments into integers
//
std::array<int, 3> Dataset::compute_split_lengths_(float train, float validate, float test) {
    //Compute required dataset lengths
    int length = this->get_length();
    int train_length = int(length * train);
    int validate_length = int(length * validate);
    int test_length = int(length * test);
    
    // Correct underflow due to integer downcasting.
    // Equally redistribute spare samples. Redistribution is sequential (due to mod). Start set is random.
    //
    int underflow_length = length - (train_length + validate_length + test_length);

    while (underflow_length > 0) {
        switch (underflow_length % 3) {
            case 0:
                train_length++;
                break;
            case 1:
                validate_length++;
                break;
            case 2:
                test_length++;
                break;
        }

        underflow_length--;
    }

    return std::array<int, 3> {train_length, validate_length, test_length};
}

//
// Get the length of the dataset
// 
int Dataset::get_length() {
    return this->input.size(0); //Queries dimension 0 (rows)
}
