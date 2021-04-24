cmake_minimum_required(VERSION 3.16)
project(rsa_utils_test VERSION 0.1)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/23ef29555ef4789f555f1ba8c51b4c52975f0907.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    ${PROJECT_NAME}
    math_tests.cc
)

target_link_libraries(
    ${PROJECT_NAME}
    rsa_utils
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})