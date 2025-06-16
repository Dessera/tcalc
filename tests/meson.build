test_token = executable(
  'test_token',
  files('test_token.cpp'),
  dependencies: [dep_tcalc, catch2_with_main_dep],
)

test_ast = executable(
  'test_ast',
  files('test_ast.cpp'),
  dependencies: [dep_tcalc, catch2_with_main_dep],
)

test('test_token', test_token)
test('test_ast', test_ast)