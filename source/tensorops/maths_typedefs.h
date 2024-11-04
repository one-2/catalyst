
#ifndef MATHS_TYPEDEFS_H
#define MATHS_TYPEDEFS_H

#include <torch/torch.h>

typedef torch::Tensor Tensor;
typedef (*CallbackTensor)(Tensor);

#endif // MATHS_TYPEDEFS_H