# Collect all source files into one library
file(GLOB_RECURSE SOURCE_FILES *.cpp)
find_package(OpenCL REQUIRED)
add_library(catalyst ${SOURCE_FILES})

# Link to Torch libraries
target_link_libraries(catalyst PRIVATE ${TORCH_LIBRARIES} OpenCL::OpenCL)

# Include directories for the library
target_include_directories(catalyst PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
