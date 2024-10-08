# tests/CMakeLists.txt

# External libraries
# gtest FetchContent setup
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  # For Windows
FetchContent_MakeAvailable(googletest)

# Gather all test files
file(GLOB_RECURSE SOURCE_FILES *.cpp)

foreach(src ${SOURCE_FILES})
    get_filename_component(test_name ${src} NAME_WE)
    
    add_executable(${test_name} ${src})
    
    # Link to source, Torch, gtest
    target_link_libraries(${test_name} PRIVATE catalyst ${TORCH_LIBRARIES} gtest gtest_main)

    # Make sure to include the source directory where headers reside
    target_include_directories(${test_name} PRIVATE ${CMAKE_SOURCE_DIR}/source)

    # Register the test with CTest
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
