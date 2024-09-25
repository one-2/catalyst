#ifndef matrixops.h
#define matrixops.h

namespace matrixops
{
    Torch::tensor matmul(torch::Tensor a, torch::Tensor b);

    Torch::tensor reLu(Torch::Tensor a);

    Torch::tensor softMax(Torch::Tensor a);
    
    Torch::tensor identity(Torch::Tensor a);

    std::ostream& operator<<;
}

#endif //MATRIXOPS_H
