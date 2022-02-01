cmake_minimum_required(VERSION 3.21)

project(particle)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(vulkan-test main.cpp)
target_compile_options(vulkan-test PRIVATE -O2)
target_link_options(vulkan-test PRIVATE -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi)

install(TARGETS vulkan-test)
