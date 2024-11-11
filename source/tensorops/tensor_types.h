
#ifndef TENSOR_TYPES_H
#define TENSOR_TYPES_H

#include <torch/torch.h>


typedef (std::shared_ptr<torch::tensor>)(TensorPtr);


#endif // TENSOR_TYPES_H