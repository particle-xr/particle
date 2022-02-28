{ lib, stdenv, fetchFromGitHub, cmake, libglvnd, python39, boost170, opencolorio_1, openimageio2, opensubdiv, osl, ptex, tbb, enableImaging ? false, enableUsdview ? true }:

with lib;
stdenv.mkDerivation rec {
  pname = "usd";
  version = "21.11";

  src = fetchFromGitHub {
    owner = "PixarAnimationStudios";
    repo = "USD";
    rev = "v${version}";
    hash = "sha256-oSP3XgPP3OI6YwxzDAj39Ppo92P52RL8C08hw4JOaKE=";
  };

  nativeBuildInputs = [ cmake ];
  buildInputs = [
    # Core
    (boost170.override { enablePython = true; python = python39; })
    libglvnd
    # python39
    tbb
  ] ++ optionals enableImaging [
    opencolorio_1
    openimageio2
    opensubdiv
    osl
    ptex
  ] ++ optionals enableUsdview [
    (python39.withPackages (ps: with ps; [ jinja2 pyopengl pyside2 pyside2-tools ]))
  ];

  cmakeFlags = optionals (!enableImaging) [ "-DPXR_BUILD_IMAGING=OFF" ];
}
