{ stdenv, fetchFromGitHub, cmake, python39, boost, opensubdiv, tbb }:

stdenv.mkDerivation rec {
  pname = "usd";
  version = "21.11";

  src = fetchFromGitHub {
    owner = "PixarAnimationStudios";
    repo = "USD";
    rev = "v${version}";
    hash = "sha256-oSP3XgPP3OI6YwxzDAj39Ppo92P52RL8C08hw4JOaKE=";
  };

  nativeBuildInputs = [ cmake python39 ];
  buildInputs = [
    boost
    opensubdiv
    tbb
    (python39.withPackages (ps: with ps; [ boost pyopengl pyside2 ]))
  ];

  cmakeFlags = [ "-DPXR_BUILD_IMAGING=FALSE" "-DPXR_ENABLE_PYTHON_SUPPORT=ON" "-DPXR_ENABLE_GL_SUPPORT=FALSE" ];
}
