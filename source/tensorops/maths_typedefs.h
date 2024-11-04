
#ifndef MATHS_TYPEDEFS_H
#define MATHS_TYPEDEFS_H

#include <torch/torch.h>

typedef torch::Tensor Tensor;
// typedef (*CallbackTensor)(Tensor); // Pointer to a function returning Tensor?

typedef (*KernelCallback)(Kernel) // TODO: Move to Kernel namespace

#endif // MATHS_TYPEDEFS_H