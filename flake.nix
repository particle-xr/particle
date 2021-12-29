{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
    emanote.url = "github:srid/emanote";
  };

  outputs = { self, nixpkgs, utils, ... } @ inputs:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs {
        inherit system;
        overlays = [
          self.overlay
        ];
      };
    in
    {
      devShell."${system}" = pkgs.mkShell {
        name = "particle";
        nativeBuildInputs = with pkgs; [
          nodejs
        ];
      };

      apps."${system}" = {
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

      overlay = final: prev: {
        onetbb = prev.callPackage ./packages/onetbb { };
        usd = prev.callPackage ./packages/usd { };
      };

      packages."${system}" = {
        inherit (pkgs) onetbb usd;
      };
    };
}
