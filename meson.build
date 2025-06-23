project(
  'tcalc',
  'cpp',
  version: '0.1.0',
  default_options: ['warning_level=3', 'cpp_std=gnu++23'],
)

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
subdir('tests')

pkg_mod = import('pkgconfig')

pkg_mod.generate(
  name: 'tcalc',
  filebase: 'tcalc',
  description: 'Simple computational programming language.',
  libraries: [lib],
  version: '0.1.0',
)