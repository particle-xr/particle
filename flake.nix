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
        nativeBuildInputs = with pkgs; with xorg; [
          cmake
          nodejs
          glfw-wayland
          glm
          vulkan-headers
          # TODO: vulkan-extension-layer
          vulkan-validation-layers
          libX11
          libXrandr
          libXi
          libXxf86vm
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

        test = utils.lib.mkApp {
          drv = pkgs.libparticle;
          exePath = "/bin/vulkan-test";
        };
      };

      overlay = final: prev: {
        libparticle = prev.callPackage ./libparticle { };
        onetbb = prev.callPackage ./packages/onetbb { };
        usd = prev.callPackage ./packages/usd { };
      };

      packages."${system}" = {
        inherit (pkgs) libparticle onetbb usd;
      };
    };
}
