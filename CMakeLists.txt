cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(catalyst)

# Enable testing
enable_testing()

# Find Torch globally
find_package(Torch REQUIRED)

# Set C++ standard globally
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set Torch-related flags globally
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

# Create the main executable and link Torch
add_executable(main main.cpp)
target_link_libraries(main PRIVATE ${TORCH_LIBRARIES} catalyst)

# Add source and tests directories
add_subdirectory(source)
add_subdirectory(tests)

# Ensure Torch is found in all subdirectories
set_property(TARGET main PROPERTY CXX_STANDARD 17)
