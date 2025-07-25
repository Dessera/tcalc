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

              package = pkgs.qt6Packages.callPackage ./default.nix {
                inherit stdenv;
                useTlExpected = true;
              };
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
            gcc-12 = mkDevEnv pkgs.gcc12Stdenv;
            gcc-11 = mkDevEnv pkgs.gcc11Stdenv;
            gcc-10 = mkDevEnv pkgs.gcc10Stdenv;
            gcc-9 = mkDevEnv pkgs.gcc9Stdenv;
            clang-20 = mkDevEnv pkgs.llvmPackages_20.libcxxStdenv;
            clang-19 = mkDevEnv pkgs.llvmPackages_19.libcxxStdenv;
            clang-18 = mkDevEnv pkgs.llvmPackages_18.libcxxStdenv;
            clang-17 = mkDevEnv pkgs.llvmPackages_17.libcxxStdenv;
            clang-16 = mkDevEnv pkgs.llvmPackages_16.libcxxStdenv;
            clang-15 = mkDevEnv pkgs.llvmPackages_15.libcxxStdenv;
            clang-14 = mkDevEnv pkgs.llvmPackages_14.libcxxStdenv;
            clang-13 = mkDevEnv pkgs.llvmPackages_13.libcxxStdenv;
            clang-12 = mkDevEnv pkgs.llvmPackages_12.libcxxStdenv;
          };
        };
    };
}
