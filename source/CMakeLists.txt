# Collect all source files into one library
file(GLOB_RECURSE SOURCE_FILES *.cpp)
add_library(catalyst ${SOURCE_FILES})

# Link to Torch libraries
target_link_libraries(catalyst PRIVATE ${TORCH_LIBRARIES})

# Define OpenCL version
add_definitions(-DCL_TARGET_OPENCL_VERSION=300)

# Link to OpenCL
find_package(OpenCL REQUIRED)
target_link_libraries(catalyst PRIVATE ${OpenCL_LIBRARIES})

# Include directories for the library
target_include_directories(catalyst PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
