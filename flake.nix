{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
    emanote.url = "github:srid/emanote";
    utils.url = "github:numtide/flake-utils";
    pre-commit.url = "github:cachix/pre-commit-hooks.nix";
  };

  outputs = {
    self,
    nixpkgs,
    utils,
    ...
  } @ inputs:
    utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {
        inherit system;
        overlays = [
          (final: prev: {
            catch2 = prev.catch2.overrideAttrs (_: {
              version = "3.x";
              src = prev.fetchFromGitHub {
                owner = "catchorg";
                repo = "Catch2";
                rev = "devel";
                hash = "sha256-MmZiHtcWweI1DgBiyAm41wdgFe3BhYQlAg0snDiZUnk=";
              };
            });
            emanote = inputs.emanote.packages."${system}".default;
            reactphysics3d = prev.callPackage ./thirdparty/reactphysics3d {};
          })
          (final: prev: {
            libparticle = prev.callPackage ./particle {};
          })
        ];
      };
    in {
      apps = {
        docs = utils.lib.mkApp {
          drv = pkgs.writeShellApplication {
            name = "particle-docs";
            text = ''
              PORT=''${1:-8080} ${pkgs.emanote}/bin/emanote -L ./docs
            '';
          };
        };
      };

      checks = {
        pre-commit = inputs.pre-commit.lib."${system}".run {
          src = ./.;
          hooks = let
            pre-commit-hooks = "${pkgs.python3Packages.pre-commit-hooks}/bin";
          in {
            alejandra.enable = true;
            check-executables-have-shebangs = {
              entry = "${pre-commit-hooks}/check-executables-have-shebangs";
              types = ["text" "executable"];
            };
            check-json = {
              enable = true;
              entry = "${pre-commit-hooks}/check-json";
              types = ["json"];
            };
            check-merge-conflict = {
              enable = true;
              entry = "${pre-commit-hooks}/check-merge-conflict";
              types = ["text"];
            };
            check-toml = {
              enable = true;
              entry = "${pre-commit-hooks}/check-toml";
              types = ["toml"];
            };
            check-yaml = {
              enable = true;
              entry = "${pre-commit-hooks}/check-yaml";
              types = ["yaml"];
            };
            clang-format = {
              enable = true;
              types_or = ["c" "c++"];
            };
            end-of-file-fixer = {
              enable = true;
              entry = "${pre-commit-hooks}/end-of-file-fixer";
              types = ["text"];
            };
            trailing-whitespace = {
              enable = true;
              entry = "${pre-commit-hooks}/trailing-whitespace-fixer";
              types = ["text"];
            };
          };
        };
      };

      devShells.default = pkgs.gcc11Stdenv.mkDerivation {
        name = "particle";
        inherit (pkgs.libparticle) buildInputs nativeBuildInputs;
        inherit (self.checks."${system}".pre-commit) shellHook;
      };

      packages = {
        inherit (pkgs) libparticle;
        default = pkgs.libparticle;
      };
    });
}
