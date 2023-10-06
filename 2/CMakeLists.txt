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

# Tests
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false ${TEST_DIR}/*.cpp)
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests ${CMAKE_PROJECT_NAME}_lib)

# Find Google Test
find_package(GTest REQUIRED)

# Include Google Test headers
include_directories(${GTEST_INCLUDE_DIRS})

# Link your tests with Google Test
target_link_libraries(tests ${GTEST_BOTH_LIBRARIES})

# Add tests
enable_testing()
add_test(NAME ThirteenConstructorTest COMMAND tests)
add_test(NAME ThirteenSetTest COMMAND tests)
add_test(NAME ThirteenAlgebraTest COMMAND tests)