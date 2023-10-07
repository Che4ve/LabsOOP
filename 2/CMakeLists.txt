cmake_minimum_required(VERSION 3.27.5)
project(lab)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify source directories
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# Include directories for regular sources and tests
include_directories(${INCLUDE_DIR})

# Create a list of source files for the library and main executable
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)
add_library(${CMAKE_PROJECT_NAME}_lib ${SOURCES})

# Main executable
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${CMAKE_PROJECT_NAME}_lib)

# Find Google Test
find_package(GTest REQUIRED)

# Include Google Test headers
include_directories(${GTEST_INCLUDE_DIRS})

# Create and link test executables
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false ${TEST_DIR}/*.cpp)
foreach(test_src ${TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})
    target_link_libraries(${test_name} ${CMAKE_PROJECT_NAME}_lib ${GTEST_BOTH_LIBRARIES})
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

# Add tests
enable_testing()
