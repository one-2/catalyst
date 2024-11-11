
#ifndef TENSOR_TYPES_H
#define TENSOR_TYPES_H

#include <torch/torch.h>


namespace tensor
{
    
typedef std::shared_ptr<torch::Tensor> TensorPtr;
// NOTE: Tensors are kept non-constant as we will update weights in-place.

} // namespace tensor

#endif // TENSOR_TYPES_H