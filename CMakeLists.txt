cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project("pool_struct")

include_directories("include")

add_executable(test "src/test.cpp")
add_executable(bench "src/bench.cpp")

