project(
  'tcalc',
  'cpp',
  version: '0.2.0',
  default_options: ['warning_level=3', 'cpp_std=gnu++23'],
)

cxx = meson.get_compiler('cpp')
cxx_std = get_option('cpp_std')
cxx_std_suffix = cxx_std.split('++')[1]

opt_build_gui = get_option('build_gui')
opt_use_tl_expected = get_option('use_tl_expected')

gtest_dep = dependency(
  'gtest',
  main: true,
  required: false,
  fallback: ['gtest', 'gtest_main_dep'],
)

qt = import('qt6', required: opt_build_gui)
qt_dep = dependency('qt6', modules: ['Core', 'Gui', 'Widgets'], required: opt_build_gui)

tl_expected_dep = dependency(
  'tl-expected',
  modules: ['tl::expected'],
  required: opt_use_tl_expected,
  method: 'cmake',
)

subdir('include')
subdir('src')

lib_args = []
lib_deps = []

if opt_use_tl_expected.enabled()
  lib_args += ['-DTCALC_USE_TL_EXPECTED']
  lib_deps += [tl_expected_dep]
endif

lib_build_args = lib_args + [
  '-DBUILDING_TCALC',
  '-Wno-pedantic',
  '-Werror',
]

lib = library(
  'tcalc',
  lib_src,
  include_directories: lib_inc,
  dependencies: lib_deps,
  gnu_symbol_visibility: 'hidden',
  cpp_args: lib_build_args,
  install: true,
)

tcalc_dep = declare_dependency(
  include_directories: lib_inc,
  link_with: lib,
  compile_args: lib_args,
  dependencies: lib_deps,
)

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
  extra_cflags: lib_args,
  version: '0.2.0',
)