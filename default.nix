{
  stdenv,
  lib,

  # Build tools
  meson,
  ninja,
  pkg-config,

  # deps
  qtbase,
  wrapQtAppsHook,
}:
stdenv.mkDerivation {
  name = "tcalc";
  src = lib.cleanSource ./.;

  buildInputs = [ qtbase ];

  nativeBuildInputs = [
    meson
    ninja
    pkg-config
    wrapQtAppsHook
  ];
}
