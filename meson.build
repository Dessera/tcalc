project(
  'tcalc',
  'cpp',
  version: '0.1.0',
  default_options: ['warning_level=3', 'cpp_std=gnu++23'],
)

magic_enum_proj = subproject(
  'magic_enum',
  default_options: ['test=false', 'hash=true'],
)
magic_enum_dep = magic_enum_proj.get_variable('magic_enum_dep')

catch2_proj = subproject('catch2')
catch2_with_main_dep = catch2_proj.get_variable('catch2_with_main_dep')

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