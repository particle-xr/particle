{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
    emanote.url = "github:srid/emanote";
    utils.url = "github:gytis-ivaskevicius/flake-utils-plus";
    pre-commit.url = "github:cachix/pre-commit-hooks.nix";
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

          checks = {
            pre-commit = inputs.pre-commit.lib."${pkgs.system}".run {
              src = ./.;
              hooks =
                let
                  pre-commit-hooks = "${pkgs.python3Packages.pre-commit-hooks}/bin";
                in
                {
                  check-executables-have-shebangs = {
                    entry = "${pre-commit-hooks}/check-executables-have-shebangs";
                    types = [ "text" "executable" ];
                  };
                  check-json = {
                    enable = true;
                    entry = "${pre-commit-hooks}/check-json";
                    types = [ "json" ];
                  };
                  check-merge-conflict = {
                    enable = true;
                    entry = "${pre-commit-hooks}/check-merge-conflict";
                    types = [ "text" ];
                  };
                  check-toml = {
                    enable = true;
                    entry = "${pre-commit-hooks}/check-toml";
                    types = [ "toml" ];
                  };
                  check-yaml = {
                    enable = true;
                    entry = "${pre-commit-hooks}/check-yaml";
                    types = [ "yaml" ];
                  };
                  clang-format = {
                    enable = true;
                    types_or = [ "c" "c++" ];
                  };
                  end-of-file-fixer = {
                    enable = true;
                    entry = "${pre-commit-hooks}/end-of-file-fixer";
                    types = [ "text" ];
                  };
                  nixpkgs-fmt.enable = true;
                  trailing-whitespace = {
                    enable = true;
                    entry = "${pre-commit-hooks}/trailing-whitespace-fixer";
                    types = [ "text" ];
                  };
                };
            };
          };

          defaultPackage = channels.nixpkgs.libparticle;

          devShell = pkgs.stdenv.mkDerivation {
            name = "particle";
            inherit (pkgs.libparticle) buildInputs nativeBuildInputs;
            inherit (self.checks."${pkgs.system}".pre-commit) shellHook;
          };

          packages = utils.lib.exportPackages self.overlays channels;
        };
    };
}
