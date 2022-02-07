final: prev: {
  libparticle = prev.callPackage ./libparticle { };
  tbb = prev.callPackage ./onetbb { };
  usd = prev.callPackage ./usd { };
}
