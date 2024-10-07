# Define test sources (in this case, only the test files inside the unit folder)
file(GLOB UNIT_TEST_FILES "*.cpp")

# Find Torch package (make sure this is at the top to use Torch correctly)
find_package(Torch REQUIRED)

# Add test executables for each test source file
foreach(test_file ${UNIT_TEST_FILES})
  get_filename_component(test_name ${test_file} NAME_WE)
  add_executable(${test_name} ${test_file})
  
  # Link against the source library, gtest, and Torch
  target_link_libraries(${test_name} PRIVATE source_library gtest gtest_main "${TORCH_LIBRARIES}")

  # Ensure Torch's include directories are available
  target_include_directories(${test_name} PRIVATE ${TORCH_INCLUDE_DIRS})
  
  # Register the test with CTest
  add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
