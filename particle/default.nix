{
  gcc11Stdenv,
  clang-tools,
  cmake,
  doctest,
  doxygen,
  fmt_8,
  glfw-wayland,
  glm,
  nodejs,
  # reactphysics3d,
  spdlog,
  vulkan-headers,
  vulkan-loader,
  vulkan-validation-layers,
}:
gcc11Stdenv.mkDerivation {
  pname = "particle";
  version = "0.0.0";

  src = ./particle;

  nativeBuildInputs = [
    clang-tools
    cmake
    doxygen
    nodejs
  ];
  buildInputs = [
    doctest
    fmt_8
    glfw-wayland
    glm
    # reactphysics3d
    spdlog
    vulkan-headers
    vulkan-loader
    vulkan-validation-layers
  ];
}
