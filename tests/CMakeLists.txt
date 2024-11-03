# tests/CMakeLists.txt

# External libraries
add_subdirectory(${CMAKE_SOURCE_DIR}/tests/third_party/googletest)

# Gather all cpps in this directory (does not collect headers)
file(GLOB_RECURSE SOURCE_FILES *.cpp)

foreach(src ${SOURCE_FILES})
    get_filename_component(test_name ${src} NAME_WE)
    
    # Add test .o to build
    add_executable(${test_name} ${src})
    
    # Link test to dependencies
    target_link_libraries(${test_name} PRIVATE catalyst ${TORCH_LIBRARIES} gtest gtest_main)

    # Include source headers the tests need
    target_include_directories(${test_name} PRIVATE ${CMAKE_SOURCE_DIR}/source)

    # Register tests with CTest
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
