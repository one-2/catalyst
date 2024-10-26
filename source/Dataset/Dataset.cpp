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

#include <iostream> //Debugging

//
// Loads a dataset from a given csv path
//
Dataset::Dataset(std::string path, int target_variable_index) {
    torch::Tensor data = io::load_tensor_from_csv(path);

    // std::cout << data << std::endl; //DEBUGGING

    //Save input
    torch::Tensor input_first_part = data.index({
        torch::indexing::Slice(), //All rows
        torch::indexing::Slice(torch::indexing::None, target_variable_index) //Slice of columns up to, not incl, the target
    });
    torch::Tensor input_second_part = data.index({
        torch::indexing::Slice(), //All rows
        torch::indexing::Slice(target_variable_index + 1, torch::indexing::None) //From 1 after target to the end of the cols
    });
    
    std::cout << input_first_part.size(1) << std::endl; //DEBUGGING
    std::cout << input_second_part.size(1) << std::endl; //DEBUGGING

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

    for (int length : split_lengths) {
        std::cout << length << " " << std::endl; // DEBUGGING
    }
    std::cout << "\n" << std::endl;

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
std::array<int, 3> Dataset::compute_split_lengths(float train, float validate, float test) {
    //Compute required dataset lengths
    int length = this->get_length();
    int train_length = int(length * train);
    int validate_length = int(length * validate);
    int test_length = int(length * test);
    
    // Correct underflow due to integer downcasting
    auto underflow_length = [&length, &train_length, &validate_length, &test_length]() {
        //& reference captures by reference (default is by value)
        return length - (train_length + validate_length + test_length);
    };

    while (underflow_length() > 0) {
        std::cout << "underflow_length() = " << underflow_length() << std::endl;

        // Equally redistribute spare samples. Redistribution is sequential (due to mod). Start set is random.
        switch (underflow_length() % 3) {
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
    }

    return std::array<int, 3> {train_length, validate_length, test_length};
}

//
// Get the length of the dataset
// 
int Dataset::get_length() {
    return this->input.size(0); //Queries dimension 0 (rows)
}

//
// Output dataset info to ostream
//
std::ostream& operator<<(std::ostream& os, const Dataset& dataset) {
    os << "Dataset details: " << "length = " << dataset.input.size(0);
}
