project(
  'tcalc',
  'cpp',
  version: '0.1.0',
  default_options: ['warning_level=3', 'cpp_std=gnu++26'],
)

magic_enum_proj = subproject(
  'magic_enum',
  default_options: ['test=false', 'hash=true'],
)
magic_enum_dep = magic_enum_proj.get_variable('magic_enum_dep')

subdir('include')
subdir('src')

lib = library(
  'tcalc',
  lib_src,
  include_directories: lib_inc,
  dependencies: [magic_enum_dep],
  gnu_symbol_visibility: 'hidden',
  cpp_args: [
    '-DBUILDING_TCALC',
    '-Wno-pedantic',
    '-Werror',
  ],
  install: true,
)

dep_tcalc = declare_dependency(include_directories: lib_inc, link_with: lib)

subdir('tests')

pkg_mod = import('pkgconfig')

pkg_mod.generate(
  name: 'tcalc',
  filebase: 'tcalc',
  description: 'Parser and evaluator for calculator.',
  libraries: [lib],
  version: '0.1.0',
)