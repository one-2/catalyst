# External libraries
add_subdirectory(${CMAKE_SOURCE_DIR}/tests/third_party/googletest)

# Include the source directory
include_directories(${CMAKE_SOURCE_DIR}/source)

# Register all test files
file(GLOB_RECURSE TEST_SOURCES ${CMAKE_SOURCE_DIR}/tests/*.cpp)

# Add each test executable and link with the source library
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} catalyst gtest gtest_main torch)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()