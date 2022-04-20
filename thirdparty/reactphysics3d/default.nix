{
  stdenv,
  cmake,
  fetchFromGitHub,
}:
stdenv.mkDerivation rec {
  pname = "reactphysics3d";
  version = "0.9.0";

  src = fetchFromGitHub {
    owner = "DanielChappuis";
    repo = pname;
    rev = "v${version}";
    hash = "sha256-AUdsUXsygsGfS8H+AHEV1fSrrX7zGmfsaTONYUG3zqk=";
  };

  nativeBuildInputs = [cmake];
}
