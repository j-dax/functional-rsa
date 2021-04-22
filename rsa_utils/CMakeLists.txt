cmake_minimum_required(VERSION 3.20)
project(rsa_utils VERSION 0.1)

# build this library
add_library(
    ${PROJECT_NAME}
    STATIC src/math.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC include
)

