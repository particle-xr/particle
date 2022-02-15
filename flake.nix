{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
    emanote.url = "github:srid/emanote";
    utils.url = "github:gytis-ivaskevicius/flake-utils-plus";
  };

  outputs = { self, nixpkgs, utils, ... } @ inputs:
    utils.lib.mkFlake {
      inherit self inputs;

      supportedSystems = [ "x86_64-linux" ];

      channels.nixpkgs.overlaysBuilder = channels: [
        self.overlay
        (final: prev: {
          emanote = inputs.emanote.defaultPackage."${prev.system}";
        })
      ];

      overlay = import ./packages;
      overlays = utils.lib.exportOverlays { inherit (self) pkgs inputs; };

      outputsBuilder = channels:
        let pkgs = channels.nixpkgs; in
        {
          apps = {
            docs =
              utils.lib.mkApp {
                drv = pkgs.writeShellApplication {
                  name = "particle-docs";
                  text = ''
                    PORT=''${1:-8080} ${pkgs.emanote}/bin/emanote -L ./docs
                  '';
                };
              };
          };

          defaultPackage = channels.nixpkgs.libparticle;

          packages = utils.lib.exportPackages self.overlays channels;
        };
    };
}
