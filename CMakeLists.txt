cmake_minimum_required(VERSION 3.10.0)
project(final_test VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CODE_PATH part1)

file(GLOB_RECURSE SRC_FILE ${CODE_PATH}/*.cpp)
include_directories(${CODE_PATH} ${CODE_PATH}/include)
add_executable(${PROJECT_NAME} ${SRC_FILE})