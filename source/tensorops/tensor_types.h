
#ifndef TENSOR_TYPES_H
#define TENSOR_TYPES_H

#include <torch/torch.h>


typedef (std::shared_ptr<torch::tensor>)(TensorPtr);
// NOTE: Tensors are kept non-constant as we will update weights in-place.


#endif // TENSOR_TYPES_H