cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(catalyst)

# Enable testing
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

# Create the main executable (exclude run_tests.cpp here)
add_executable(main main.cpp)
set_property(TARGET main PROPERTY CXX_STANDARD 17)

# Link requires libraries
find_package(Torch REQUIRED)
target_link_libraries(main "${TORCH_LIBRARIES}")

# Add source library
add_subdirectory(source)

# Add the test directory
add_subdirectory(tests)
