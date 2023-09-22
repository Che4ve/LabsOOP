cmake_minimum_required(VERSION 3.27.5)
project(timeconverter)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

# Задаем переменные с переменными
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

# Подключаем дирректории для билда
include_directories(${INCLUDE_DIR})

# Создаем листы исходников
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false ${TEST_DIR}/*.cpp)

add_library(${CMAKE_PROJECT_NAME}_lib ${SOURCES})

add_executable(${PROJECT_NAME} src/timecalc.cpp main.cpp)
add_executable(tests ${TEST_SOURCES})

# Связываем библиотеки с исполняемыми файлами
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME}_lib)

target_include_directories(tests PRIVATE ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

target_link_libraries(tests PRIVATE ${CMAKE_PROJECT_NAME}_lib gtest gtest_main)

# Добавляем тесты
add_test(NAME BASIC COMMAND tests)
