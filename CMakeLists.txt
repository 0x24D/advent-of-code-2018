cmake_minimum_required(VERSION 3.13)
project(advent-of-code-2018)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wpedantic)

add_executable(day-1 src/day1.cpp)
add_executable(day-2 src/day2.cpp)
add_executable(day-3 src/day3.cpp)
add_executable(day-4 src/day4.cpp)
add_executable(day-5 src/day5.cpp)
add_executable(day-6 src/day6.cpp)
add_executable(day-7 src/day7.cpp)
add_executable(day-8 src/day8.cpp)
