lib_inc = include_directories('.')

install_subdir('tcalc', install_dir: 'include')

if opt_build_gui.enabled()
  gui_moc_src = files(
    'tcalc_gui/application.hpp',
    'tcalc_gui/calculator.hpp',
    'tcalc_gui/key.hpp',
    'tcalc_gui/keyboard.hpp',
  )
endif