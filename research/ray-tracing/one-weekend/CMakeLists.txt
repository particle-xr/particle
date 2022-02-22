cmake_minimum_required(VERSION 3.21)

project(
  ray-tracing-tutorial
  VERSION 0.0.0
  LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(rt ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_include_directories(rt PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
