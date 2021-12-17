{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
    utils.url = "github:numtide/flake-utils";
    emanote.url = "github:srid/emanote";
  };

  outputs = { self, nixpkgs, utils, ... } @ inputs:
    utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages."${system}";
      in
      {
        devShell = pkgs.mkShell {
          name = "particle";
          nativeBuildInputs = with pkgs; [
            nodejs
          ];
        };

        apps = {
          docs =
            let
              emanote = inputs.emanote.defaultPackage."${system}";
            in
            utils.lib.mkApp {
              drv = pkgs.writeShellApplication {
                name = "eth-nix-docs";
                text = ''
                  PORT=''${1:-8080} ${emanote}/bin/emanote -L ./docs
                '';
              };
            };
        };
      });
}
