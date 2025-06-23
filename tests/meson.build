test_token = executable(
  'test_token',
  files('test_token.cpp'),
  dependencies: [tcalc_dep, gtest_dep],
)

test_ast = executable(
  'test_ast',
  files('test_ast.cpp'),
  dependencies: [tcalc_dep, gtest_dep],
)

test_eval = executable(
  'test_eval',
  files('test_eval.cpp'),
  dependencies: [tcalc_dep, gtest_dep],
)

test('test_token', test_token)
test('test_ast', test_ast)
test('test_eval', test_eval)