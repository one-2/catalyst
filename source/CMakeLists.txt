# Define the source files in the src directory
file(GLOB_RECURSE SOURCE_FILES "*.cpp" "*.h")

# Create a library target for the source code
add_library(source_library ${SOURCE_FILES})

# Include subdirectories in compiler references
target_include_directories(source_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
