{ stdenv, fetchFromGitHub, pkgs, ... }:

stdenv.mkDerivation rec {
  pname = "onetbb";
  version = "2021.5.0";

  src = fetchFromGitHub {
    owner = "oneapi-src";
    repo = "oneTBB";
    rev = "v${version}";
    hash = "sha256-TJ/oSSMvgtKuz7PVyIoFEbBW6EZz7t2wr/kP093HF/w=";
  };

  nativeBuildInputs = with pkgs; [ cmake ];

  enableParallelBuilding = true;
}
