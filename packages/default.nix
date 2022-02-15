final: prev: {
  catch2 = prev.catch2.overrideAttrs (_: {
    version = "3.x";
    src = prev.fetchFromGitHub {
      owner = "catchorg";
      repo = "Catch2";
      rev = "devel";
      hash = "sha256-MmZiHtcWweI1DgBiyAm41wdgFe3BhYQlAg0snDiZUnk=";
    };
  });
  libparticle = prev.callPackage ./libparticle { };
  tbb = prev.callPackage ./onetbb { };
  usd = prev.callPackage ./usd { };
}
