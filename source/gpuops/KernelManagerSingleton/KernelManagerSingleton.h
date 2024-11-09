// KernelManagerSingleton/KernelManagerSingleton.h
//
// Author: Stephen Elliott
//
// Date: 2024-11-05
//
// Description: Singleton class to store a cache of compiled kernels and an access interface.
//              Async-extensible.
//

namespace gpuops
{

class KernelManagerSingleton
{
public:
    KernelCallback get_kernel(std::string type, Args args); // < Replace args struct with generalisation
    // TODO: Implement by the standard way to handle arguments by unpacking?

private:
    // Method:
    KernelCallback search_Manager(std::string type, Args args); // TODO: Throw error if not found
    KernelCallback build_kernel(std::string type, Args args);

    // TODO attribute: Some Map of compiled kernel (shared?) pointers? What
    //                 happens when we parallelise?

}

} // namespace gpuops