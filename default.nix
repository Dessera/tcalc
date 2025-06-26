{
  stdenv,
  lib,

  # Build tools
  meson,
  cmake,
  ninja,
  pkg-config,

  # Deps
  qtbase,
  tl-expected,
  wrapQtAppsHook,

  # Config
  useTlExpected ? false,
}:
stdenv.mkDerivation {
  name = "tcalc";
  src = lib.cleanSource ./.;

  buildInputs =
    [ qtbase ]
    ++ (
      if useTlExpected then
        [
          tl-expected
          cmake
        ]
      else
        [ ]
    );

  nativeBuildInputs = [
    meson
    ninja
    pkg-config
    wrapQtAppsHook
  ];
}
