cmake_minimum_required(VERSION 3.16)
project(rsa VERSION 1.0)

add_executable(
    ${PROJECT_NAME}
    src/rsa.cpp
    src/main.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    rsa_utils
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC include
)

