{ stdenv, fetchFromGitHub, cmake }:

stdenv.mkDerivation rec {
  pname = "onetbb";
  version = "2018_U6";

  src = fetchFromGitHub {
    owner = "oneapi-src";
    repo = "oneTBB";
    rev = version;
    hash = "sha256-FMW2Ey9t5MThz14cw02aYmQDjrDVPa2bQ70Ccz6uCNA=";
  };

  installPhase = ''
    mkdir -p $out/lib
    install build/linux*/*.so* $out/lib
    cp -R include $out
  '';
}
