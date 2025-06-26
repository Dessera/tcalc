project(
  'tcalc',
  'cpp',
  version: '0.1.0',
  default_options: ['warning_level=3', 'cpp_std=gnu++23'],
)

opt_build_gui = get_option('build_gui')

gtest_dep = dependency(
  'gtest',
  main: true,
  required: false,
  fallback: ['gtest', 'gtest_main_dep'],
)

qt = import('qt6', required: opt_build_gui)
qt_dep = dependency('qt6', modules: ['Core', 'Gui', 'Widgets'], required: opt_build_gui)

subdir('include')
subdir('src')

lib = library(
  'tcalc',
  lib_src,
  include_directories: lib_inc,
  dependencies: [],
  gnu_symbol_visibility: 'hidden',
  cpp_args: [
    '-DBUILDING_TCALC',
    '-Wno-pedantic',
    '-Werror',
  ],
  install: true,
)

tcalc_dep = declare_dependency(include_directories: lib_inc, link_with: lib)

subdir('bin')

if not gtest_dep.found()
  message('gtest not found, skipping tests')
else
  subdir('tests')
endif

pkg_mod = import('pkgconfig')

pkg_mod.generate(
  name: 'tcalc',
  filebase: 'tcalc',
  description: 'Simple computational programming language.',
  libraries: [lib],
  version: '0.1.0',
)