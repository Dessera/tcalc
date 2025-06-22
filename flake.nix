{
  description = "Simple computational programming language.";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixpkgs-unstable";
    flake-parts.url = "github:hercules-ci/flake-parts";
  };

  outputs =
    { flake-parts, ... }@inputs:
    flake-parts.lib.mkFlake { inherit inputs; } {
      systems = [ "x86_64-linux" ];

      perSystem =
        { pkgs, ... }:
        let
          mkDevEnv =
            stdenv:
            let
              clang-tools = pkgs.callPackage ./.nix-support/clang-tools.nix {
                inherit stdenv;
              };

              package = pkgs.callPackage ./default.nix { inherit stdenv; };
            in
            pkgs.mkShell.override
              {
                inherit stdenv;
              }
              {
                inputsFrom = [ package ];
                hardeningDisable = [ "fortify" ];

                packages =
                  (with pkgs; [
                    nixd
                    nixfmt-rfc-style
                    mesonlsp
                    doxygen
                  ])
                  ++ [ clang-tools ];
              };
        in
        {
          packages.default = pkgs.callPackage ./default.nix { stdenv = pkgs.gcc14Stdenv; };
          devShells = rec {
            default = gcc-14;
            gcc-14 = mkDevEnv pkgs.gcc14Stdenv;
            gcc-13 = mkDevEnv pkgs.gcc13Stdenv;
            clang-19 = mkDevEnv pkgs.llvmPackages_19.libcxxStdenv;
            clang-18 = mkDevEnv pkgs.llvmPackages_18.libcxxStdenv;
            clang-17 = mkDevEnv pkgs.llvmPackages_17.libcxxStdenv;
          };
        };
    };
}
