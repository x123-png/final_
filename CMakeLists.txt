cmake_minimum_required(VERSION 3.10.0)
project(final_test VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CODE_PATH part1)

file(GLOB_RECURSE SRC_FILE ${CODE_PATH}/*.cpp)
include_directories(${CODE_PATH} ${CODE_PATH}/include ${CMAKE_SOURCE_DIR}/include)

add_executable(server ${CODE_PATH}/main.cpp part1/src/part1.cpp)
add_executable(client ${CODE_PATH}/client_use.cpp)

target_include_directories(server PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(client PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(server PRIVATE ws2_32)
target_link_libraries(client PRIVATE ws2_32)

# cmake_minimum_required(VERSION 3.10.0)
# project(final_test VERSION 0.1.0 LANGUAGES C CXX)

# set(CMAKE_CXX_STANDARD 20)
# set(CODE_PATH part1)

# file(GLOB_RECURSE SRC_FILE ${CODE_PATH}/*.cpp)
# include_directories(${CODE_PATH} ${CODE_PATH}/include)
# add_executable(${PROJECT_NAME} ${SRC_FILE})
# include_directories(${CMAKE_SOURCE_DIR}/include)  # 添加全局 include 目录
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)