{ stdenv, clang-tools, cmake, doxygen, doctest, nodejs, glfw-wayland, glm, vulkan-headers, vulkan-loader, vulkan-validation-layers }:

stdenv.mkDerivation {
  pname = "particle";
  version = "0.0.0";

  src = ./particle;

  nativeBuildInputs = [ clang-tools cmake doxygen nodejs ];
  buildInputs = [ doctest glfw-wayland glm vulkan-headers vulkan-loader vulkan-validation-layers ];
}
