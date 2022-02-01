{ stdenv, cmake, glfw-wayland, glm, vulkan-headers, vulkan-loader, vulkan-validation-layers, xorg }:

stdenv.mkDerivation {
  pname = "libparticle";
  version = "0.0.x";
  src = ./.;

  nativeBuildInputs = [ cmake ];
  buildInputs = with xorg; [
    glfw-wayland
    glm
    vulkan-headers
    vulkan-loader
    vulkan-validation-layers
    libX11
    libXrandr
    libXi
    libXxf86vm
  ];
}
