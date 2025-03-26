cmake_minimum_required(VERSION 3.15)
project(tests)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR})



# Add GoogleTest
# -> uncomment this section for when you are not on your laptop and dont have gtest

# *
# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
# )
# *

#else
find_package(GTest REQUIRED)




# For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()



# test for fibonacci functions
add_executable(test_functions test.cpp
                ${CMAKE_SOURCE_DIR}/fibonacci_functions.cpp)

# ling libraries
# target_link_libraries(test_functions gtest_main)  ##for when not on laptop
target_link_libraries(test_functions GTest::GTest GTest::Main)


# Register tests
add_test(NAME FibFuncTests COMMAND test_functions)