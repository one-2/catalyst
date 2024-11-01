# Collect all source files into one library
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(catalyst ${SOURCE_FILES})

# Link to Torch libraries
target_link_libraries(catalyst PRIVATE ${TORCH_LIBRARIES})

# Collect all subdirectories
file(GLOB_RECURSE ALL_SUBDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)

# Filter out files, keep only directories
set(DIR_LIST "")
foreach(SUBDIR ${ALL_SUBDIRS})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR})
        list(APPEND DIR_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR})
    endif()
endforeach()

# Include directories for the library
target_include_directories(catalyst PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${DIR_LIST})