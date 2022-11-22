{
  self,
  lib,
  flake-parts,
  ...
}: {
  config = {
    perSystem = {
      self',
      config,
      lib,
      pkgs,
      ...
    }: {
      packages = {
        libparticle = pkgs.callPackage ../particle {};
      };
    };
  };
}
