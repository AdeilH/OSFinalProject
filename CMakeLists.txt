cmake_minimum_required(VERSION 3.0.0)
project(FuzzProtoType VERSION 0.1.0)

set(CMAKE_BUILD_TYPE Debug)

add_library(FuzzProtoType FuzzProtoType.cpp)

add_executable(example ${CMAKE_SOURCE_DIR}/Example/main.cpp)
target_link_libraries(example FuzzProtoType)
