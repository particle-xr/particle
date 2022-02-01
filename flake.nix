{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
    emanote.url = "github:srid/emanote";
  };

  outputs = { self, nixpkgs, utils, ... } @ inputs:
    utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages."${system}";
      in
      rec {
        apps = {
          docs =
            let
              emanote = inputs.emanote.defaultPackage."${system}";
            in
            utils.lib.mkApp {
              drv = pkgs.writeShellApplication {
                name = "particle-docs";
                text = ''
                  PORT=''${1:-8080} ${emanote}/bin/emanote -L ./docs
                '';
              };
            };
        };

        devShell = pkgs.mkShell {
          name = "particle";
          nativeBuildInputs = with pkgs; [ nodejs ];
        };

        overlay = final: prev: {
          onetbb = prev.callPackage ./packages/onetbb { };
          usd = prev.callPackage ./packages/usd { };
        };
      });
}
