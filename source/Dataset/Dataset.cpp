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
#include <tuple>
#include "./Dataset.h"
#include "../io/io.h"

//
// Loads a dataset from a given csv path
//
Dataset::Dataset(std::string path, int outcome_variable_index) {
    torch::Tensor data = load_tensor_from_csv(path);

    //Save input
    torch::Tensor first_part = data.index({torch::indexing::Slice(), torch::indexing::Slice(None, outcome_variable_index)});
    torch::Tensor second_part = data.index({torch::indexing::Slice(), torch::indexing::Slice(outcome_variable_index + 1, None)});
    this->input = torch::cat({first_part, second_part});

    //Save outcome
    this->outcome = data.index({torch::indexing::Slice(), outcome_variable_index});
};

//
// Load a dataset by splitting a parent dataset
//
Dataset::Dataset(torch::Tensor input, torch::Tensor output, int start_index, int length) {
    torch::Tensor truncated_input = input.index({torch::indexing::Slice(start_index, length), torch::indexing::Slice()});
    torch::Tensor truncated_output = output.index({torch::indexing::Slice(start_index, length), torch::indexing::Slice()});

    this->input = truncated_input;
    this->output = truncated_output;
}


//
// Build a dataloader from this dataset
//
DataLoader Dataset::get_dataloader() {
    return DataLoader(this->input, this->outcome);
}

//
// Split the dataset three ways
//
std::list<Dataset> Dataset::split(float train, float validate, float test) {
    //Compute lengths to split the dataset into
    std::list<int, int, int> split_lengths = this->compute_split_lengths(train, validate, test);

    //Split the dataset
    Dataset train_set = Dataset(*this, 0, split_lengths[0]);
    Dataset validate_set = Dataset(*this, split_lengths[0], split_lengths[1]);
    Dataset test_set = Dataset(*this, split_lengths[1], split_lengths[2]);

    return std::list<Dataset> {train_set, validate_set, test_set};
}

//
// Convert percentage split length arguments into integers
//
Dataset::tuple<int, int, int> Dataset::compute_split_lengths() {
    //Compute required dataset lengths
    int length = this->get_length();
    int train_length = int(length * train);
    int validate_length = int(length * validate);
    int test_length = int(length * test);
    
    //Correct underflow due to typecasting
    int overflow_length(int train_length, int validate_length, int test_length, int length) {
        return length - (train_length + validate_length + test_length)
    } 

    while (overflow_length(train_length, validate_length, test_length, length) > 0) {
        int overflow_mod = overflow_length(train_length, validate_length, test_length, length) % 3;

        switch {
            case overflow_mod == 0:
                train_length--;
                if (train_length == 0 || overflow_length(train_length, validate_length, test_length, length) == 0) {
                    break;
                }
            case overflow_mod == 1:
                validate_length--;
                if (validate_length == 0 || overflow_length(train_length, validate_length, test_length, length) == 0) {
                    break;
                }
            case overflow_mod == 2:
                test_length--;
                if (test_length == 0 || overflow_length(train_length, validate_length, test_length, length) == 0) {
                    break;
                }
        }
    }

    return std::make_tuple(train_length, validate_length, test_length);
}

//
// Get the length of the dataset
// 
int Dataset::get_length() {
    // Implementation for returning the length of the dataset
    return this->input.size();
}

//
// Output dataset info to ostream
//
std::ostream& operator<<(std::ostream& os, const Dataset& dataset) {
    os << "Dataset details: " << dataset.path;
    return os;
}
