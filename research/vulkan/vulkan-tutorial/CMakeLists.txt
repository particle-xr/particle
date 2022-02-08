cmake_minimum_required(VERSION 3.21)

project(vulkan-tutorial)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(Vulkan REQUIRED)
find_package(tinyobjloader REQUIRED)
find_path(STB_INCLUDE_DIR stb_image.h PATH_SUFFIXES stb REQUIRED)

add_executable(glslang::validator IMPORTED)
find_program(GLSLANG_VALIDATOR "glslangValidator" REQUIRED)
set_target_properties(glslang::validator PROPERTIES IMPORTED_LOCATION
                                                    ${GLSLANG_VALIDATOR})

add_executable(vulkan-tutorial main.cpp)
target_compile_options(vulkan-tutorial PRIVATE -O2)
target_include_directories(vulkan-tutorial PRIVATE ${STB_INCLUDE_DIR})
target_link_libraries(
  vulkan-tutorial PRIVATE glfw glm::glm tinyobjloader::tinyobjloader
                          Vulkan::Vulkan)
target_link_options(
  vulkan-tutorial
  PRIVATE
  -ldl
  -lpthread
  -lX11
  -lXxf86vm
  -lXrandr
  -lXi)

set(SHADERS_DIR ${PROJECT_BINARY_DIR}/shaders)
set(SHADER_SOURCES ${PROJECT_SOURCE_DIR}/26_shader_depth.frag
                   ${PROJECT_SOURCE_DIR}/26_shader_depth.vert)
add_custom_command(OUTPUT ${SHADERS_DIR} COMMAND ${CMAKE_COMMAND} -E
                                                 make_directory ${SHADERS_DIR})
add_custom_command(
  OUTPUT ${SHADERS_DIR}/frag.spv ${SHADERS_DIR}/vert.spv
  COMMAND glslang::validator ARGS --target-env vulkan1.0 ${SHADER_SOURCES}
          --quiet
  WORKING_DIRECTORY ${SHADERS_DIR}
  DEPENDS ${SHADERS_DIR} ${SHADER_SOURCES}
  COMMENT "Compiling Shaders"
  VERBATIM)
add_custom_target(vulkan-tutorial-shaders DEPENDS ${SHADERS_DIR}/frag.spv
                                                  ${SHADERS_DIR}/vert.spv)

add_dependencies(vulkan-tutorial vulkan-tutorial-shaders)

file(COPY ${PROJECT_SOURCE_DIR}/viking_room.obj
     DESTINATION ${PROJECT_BINARY_DIR}/models)
file(COPY ${PROJECT_SOURCE_DIR}/viking_room.png
     DESTINATION ${PROJECT_BINARY_DIR}/textures)

install(TARGETS vulkan-tutorial)
