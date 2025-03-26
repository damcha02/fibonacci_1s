cmake_minimum_required(VERSION 3.15)
project (fibonacci)

set (CMAKE_CXX_STANDARD 17)

add_subdirectory(Tests)

add_executable(main main.cpp fibonacci_functions.cpp helper_functions.cpp)
