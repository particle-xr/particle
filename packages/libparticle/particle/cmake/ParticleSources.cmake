set(SOURCE_ROOT ${PROJECT_SOURCE_DIR}/particle)
configure_file(${SOURCE_ROOT}/version.cpp.in ${PROJECT_BINARY_DIR}/version.cpp
               @ONLY)

set(SOURCES
    ${PROJECT_BINARY_DIR}/version.cpp
    ${SOURCE_ROOT}/kinematics.cpp
    ${SOURCE_ROOT}/point.cpp
    ${SOURCE_ROOT}/sphere.cpp
    ${SOURCE_ROOT}/state_exporter.cpp
    # ${SOURCE_ROOT}/adapter/debug_info.cpp
    # ${SOURCE_ROOT}/adapter/vulkan/application.cpp
    # ${SOURCE_ROOT}/adapter/vulkan/debugger.cpp
    # ${SOURCE_ROOT}/adapter/vulkan/device.cpp
    # ${SOURCE_ROOT}/adapter/vulkan/instance.cpp
    # ${SOURCE_ROOT}/adapter/vulkan/utils.cpp
)
