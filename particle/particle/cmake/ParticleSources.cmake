set(SOURCE_ROOT ${PROJECT_SOURCE_DIR}/particle)
configure_file(${SOURCE_ROOT}/version.cxx.in ${PROJECT_BINARY_DIR}/version.cxx
               @ONLY)

set(SOURCES
    ${PROJECT_BINARY_DIR}/version.cxx
    # ${SOURCE_ROOT}/kinematics.cpp
    ${SOURCE_ROOT}/point.cxx
    ${SOURCE_ROOT}/world.cxx
    # ${SOURCE_ROOT}/sphere.cpp
    # ${SOURCE_ROOT}/state_exporter.cpp
    # ${SOURCE_ROOT}/adapter/debug_info.cpp
    # ${SOURCE_ROOT}/adapter/vulkan/application.cpp
    # ${SOURCE_ROOT}/adapter/vulkan/debugger.cpp
    # ${SOURCE_ROOT}/adapter/vulkan/device.cpp
    # ${SOURCE_ROOT}/adapter/vulkan/instance.cpp
    # ${SOURCE_ROOT}/adapter/vulkan/utils.cpp
)
