with import <nixpkgs> { };

mkShell {
  name = "vulkan-tutorial";
  nativeBuildInputs = with xorg; [
    cmake
    glfw-wayland
    glm
    glslang
    stb
    tinyobjloader
    vulkan-headers
    vulkan-loader
    vulkan-validation-layers
    libX11
    libXrandr
    libXi
    libXxf86vm
    lldb_12
  ];
}
