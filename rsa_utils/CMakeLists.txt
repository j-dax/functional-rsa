cmake_minimum_required(VERSION 3.16)
project(rsa_utils VERSION 0.1)

# build this library
add_library(
    ${PROJECT_NAME}
    STATIC src/math_utils.cpp
    src/primes.cpp
    src/print.cpp
    src/large_number.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC include
)
