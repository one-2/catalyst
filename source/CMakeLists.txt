# Collect all source files into one library
file(GLOB_RECURSE SOURCE_FILES *.cpp)
# Exclude cereal examples so this bad boy builds
list(FILTER SOURCE_FILES EXCLUDE REGEX "source/third_party/cereal/sandbox/.*")
add_library(catalyst ${SOURCE_FILES})

# Find Boost libraries
find_package(Boost 1.74 REQUIRED COMPONENTS serialization)

# Link Boost libraries
target_link_libraries(catalyst PRIVATE Boost::serialization)

# Link to Torch libraries
target_link_libraries(catalyst PRIVATE ${TORCH_LIBRARIES})

# Define OpenCL version
add_definitions(-DCL_TARGET_OPENCL_VERSION=300)

# Link to OpenCL
find_package(OpenCL REQUIRED)
target_link_libraries(catalyst PRIVATE ${OpenCL_LIBRARIES})


# Include directories for the library
target_include_directories(catalyst PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
