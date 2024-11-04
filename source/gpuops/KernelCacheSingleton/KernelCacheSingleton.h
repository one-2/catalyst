// KernelCacheSingleton/KernelCacheSingleton.h
//
// Author: Stephen Elliott
//
// Date: 2024-11-05
//
// Description: Singleton class to store a cache of compiled kernels.
//

namespace gpuops
{

class KernelCacheSingleton
{
public:
    KernelCallback get_kernel(std::string type, Args args); // < Replace args struct with generalisation
    // TODO: Implement by the standard way to handle arguments by unpacking?

private:
    // Method:
    KernelCallback search_cache(std::string type, Args args); // TODO: Throw error if not found
    KernelCallback build_kernel(std::string type, Args args);

    // TODO attribute: Some Map of compiled kernel (shared?) pointers? What
    //                 happens when we parallelise?

}

} // namespace gpuops