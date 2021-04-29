cmake_minimum_required(VERSION 3.16)
project(functional-rsa VERSION 1.0)

# https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(
    rsa_utils
)
add_subdirectory(
    test
)
add_subdirectory(
    rsa
)