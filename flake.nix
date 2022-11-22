{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
    emanote.url = "github:srid/emanote";
    flake-parts.url = "github:hercules-ci/flake-parts";
    pre-commit-hooks.url = "github:cachix/pre-commit-hooks.nix";
  };

  outputs = {
    self,
    nixpkgs,
    flake-parts,
    ...
  } @ inputs:
    flake-parts.lib.mkFlake {inherit self;} {
      # systems = nixpkgs.lib.systems.flakeExposed;
      systems = ["x86_64-linux"];

      imports = [
        ./nix/particle.nix
        inputs.emanote.flakeModule
        inputs.pre-commit-hooks.flakeModule
      ];

      perSystem = {
        self',
        config,
        pkgs,
        system,
        ...
      }: {
        pre-commit = {
          settings = {
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
          inherit (self'.packages.libparticle) buildInputs nativeBuildInputs;
          shellHook = ''
            ${config.pre-commit.installationScript}
          '';
        };

        emanote = {
          sites."docs" = {
            layers = [./docs];
            layersString = ["./docs"];
            baseUrl = "/particle/";
          };
        };
      };
    };
}
