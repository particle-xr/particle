{ stdenv, fetchFromGitHub, pkgs, ... }:

stdenv.mkDerivation rec {
  pname = "usd";
  version = "21.11";

  src = fetchFromGitHub {
    owner = "PixarAnimationStudios";
    repo = "USD";
    rev = "v${version}";
    hash = "sha256-oSP3XgPP3OI6YwxzDAj39Ppo92P52RL8C08hw4JOaKE=";
  };

  nativeBuildInputs = with pkgs; [ cmake python39 ];
  buildInputs = with pkgs; [
    boost
    opensubdiv
    tbb
    (python3.withPackages (ps: with ps; [ boost pyopengl pyside2 ]))
  ];

  enableParallelBuilding = true;
  cmakeFlags = [ "-DPXR_BUILD_IMAGING=FALSE" "-DPXR_ENABLE_PYTHON_SUPPORT=ON" "-DPXR_ENABLE_GL_SUPPORT=FALSE" ];
}
