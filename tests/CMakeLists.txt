# gtest FetchContent setup
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  # For Windows
FetchContent_MakeAvailable(googletest)

# Add the unit tests subdirectory
add_subdirectory(unit)  # Include the unit folder's CMakeLists.txt

# List of test files at this level (without extensions)
set(TEST_SOURCES
    dummy_test
)

# Loop through each test source
foreach(TEST_SOURCE ${TEST_SOURCES})
    # Add executable for each test
    add_executable(${TEST_SOURCE} ${TEST_SOURCE}.cpp)

    # Link each test executable with gtest and the source library
    target_link_libraries(${TEST_SOURCE} PRIVATE source_library gtest gtest_main)

    # Register the test with CTest
    add_test(NAME ${TEST_SOURCE} COMMAND ${TEST_SOURCE})
endforeach()
