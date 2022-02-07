cmake_minimum_required(VERSION 3.21)

project(
  particle
  VERSION 0.0.0
  LANGUAGES CXX)
set(PARTICLE_VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(SOURCE_ROOT ${PROJECT_SOURCE_DIR}/particle)
set(SOURCES ${SOURCE_ROOT}/state_exporter.cpp)

include(CMakePackageConfigHelpers)
include(GenerateDocs)
include(GNUInstallDirs)

add_library(particle ${SOURCES})
set_target_properties(particle PROPERTIES VERSION ${PROJECT_VERSION}
                                          SOVERSION ${PROJECT_VERSION_MAJOR})
target_include_directories(
  particle
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/detail>)

add_library(Particle::particle ALIAS particle)

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_INCLUDEDIR}/particle)
configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/cmake/ParticleConfig.cmake.in
  ${PROJECT_BINARY_DIR}/ParticleConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  PATH_VARS INCLUDE_INSTALL_DIR)
write_basic_package_version_file(
  ${PROJECT_BINARY_DIR}/ParticleConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

install(TARGETS particle EXPORT ParticleTargets)
install(
  EXPORT ParticleTargets
  NAMESPACE Particle::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
install(
  DIRECTORY ${SOURCE_ROOT}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING
  PATTERN *.hpp)
install(FILES ${PROJECT_BINARY_DIR}/ParticleConfig.cmake
              ${PROJECT_BINARY_DIR}/ParticleConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
