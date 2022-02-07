cmake_minimum_required(VERSION 3.21)

project(vulkan-tutorial)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(vulkan-tutorial main.cpp)
target_compile_options(vulkan-tutorial PRIVATE -O2)
target_link_options(
  vulkan-tutorial
  PRIVATE
  -lglfw
  -lvulkan
  -ldl
  -lpthread
  -lX11
  -lXxf86vm
  -lXrandr
  -lXi)

install(TARGETS vulkan-tutorial)
