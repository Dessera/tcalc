executable(
  'tcalc_repl',
  files('tcalc_repl.cpp'),
  dependencies: [tcalc_dep],
  install: true,
)

if opt_build_gui.enabled()
  gui_deps = [tcalc_dep, qt_dep]
  gui_src = files(
    'tcalc_gui/application.cpp',
    'tcalc_gui/calculator.cpp',
    'tcalc_gui/key.cpp',
    'tcalc_gui/keyboard.cpp',
    'tcalc_gui/main.cpp',
  )
  gui_src += qt.compile_moc(
    headers: gui_moc_src,
    dependencies: gui_deps,
  )

  executable(
    'tcalc_gui',
    gui_src,
    dependencies: gui_deps,
    install: true,
  )
endif