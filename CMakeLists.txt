# Cmake setup
cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project setup
project(catalyst)

# Build type is testing
enable_testing() # TODO: remove in prod

#### CUDA
# cpp libtorch is bundled as cpu-only and with cuda. I'm planning to use opencl initially
# and learn cuda later (open standard = better?). Using bundled from the start to avoid issues later.
# CUDA could be removed by installing the non-cuda libtorch and removing the find_package(CUDA REQUIRED) line.
# 
# Dependency is CUDA 12.4 version of libtorch
# Installed Nov 3 2024 from https://download.pytorch.org/libtorch/cu124/libtorch-cxx11-abi-shared-with-deps-2.5.1%2Bcu124.zip
#
# Configure CUDA
set(CMAKE_CUDA_STANDARD 11)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)
set(CUDA_ARCHITECTURES "60;61;70;75;80")

# Find CUDA before findings libtorch
find_package(CUDA REQUIRED)

# Find libtorch
set(CMAKE_PREFIX_PATH "../libtorch") # Set libtorch path
find_package(Torch REQUIRED) # Find libtorch


# Global flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

# Global debug flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra") # TODO: remove in prod

# Create main executable
add_executable(main main.cpp)
set_property(TARGET main PROPERTY CXX_STANDARD 20) # Set main executable to cpp20 standard

# Link Torch
target_link_libraries(main PRIVATE ${TORCH_LIBRARIES} catalyst)

# Add subdirectories to build tree
add_subdirectory(source)
add_subdirectory(tests)
