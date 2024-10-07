cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(catalyst)

# Enable testing
enable_testing()

find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

# Create the main executable (exclude run_tests.cpp here)
add_executable(main main.cpp)
target_link_libraries(main "${TORCH_LIBRARIES}")

set_property(TARGET main PROPERTY CXX_STANDARD 17)

# Add source library
add_subdirectory(source)

# Add the test directory
add_subdirectory(tests)
