with import <nixpkgs> {};
  mkShell {
    name = "ray-tracing";
    nativeBuildInputs = [
      clang-tools
      cmake
    ];
  }
