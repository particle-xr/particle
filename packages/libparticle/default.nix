{ stdenv, cmake, doxygen }:

stdenv.mkDerivation {
  pname = "particle";
  version = "0.0.0";

  src = ./particle;

  nativeBuildInputs = [ cmake doxygen ];
}
