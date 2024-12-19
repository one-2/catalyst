// KernelManagerSingleton/KernelManagerSingleton.h
//
// Author: Stephen Elliott
//
// Date: 2024-11-05
//
// Description: Singleton class to store a cache of compiled kernels and an access interface.
//              Async-extensible.
//

#ifndef KERNELMANAGERSINGLETON_H
#define KERNELMANAGERSINGLETON_H


#include <unordered_map>
#include <string>
#include <list>

namespace gpuops
{

class KernelManagerSingleton
{
public:
    TensorPtr run_kernel( // Gets the kernel and executes that baddie on some data
        std::string type,
        int in_size,
        TensorPtr in_data
    );
    
private:
    // Get kernel: finds a kernel in the cache or initialises it if it's not in the cache
    KernelPtr get_kernel(std::string type, int in_size); // Search cache and build if not found
    
    // helpers for get_kernel
    KernelPtr search_cache(std::string type, int in_size); // Searches map
    KernelPtr build_kernel(std::string type, int in_size); // Calls builder class and register_kernel
    KernelPtr register_kernel(std::string type, int in_size); // Registers a kernel to the map

    // Load gpu: enqueues kernel and data to GPU
    KernelPtr load_gpu(KernelPtr kernel_ptr, TensorPtr in_data);

    // Kernel map
    std::unordered_map<std::string, std::list<KernelPtr>> kernel_map; // Hashmap of type to a list of kernel ptrs


    // NOTE: need a variable pointing to the GPU for enqueue?
    // NOTE: need a variable containing work group size? Or can probs just hard-code for now
};

} // namespace gpuops


#endif // KERNELMANAGERSINGLETON_H