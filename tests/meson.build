test_tokens = executable(
  'test_tokens',
  files('test_tokens.cpp'),
  dependencies: [dep_tcalc],
)

test_ast = executable(
  'test_ast',
  files('test_ast.cpp'),
  dependencies: [dep_tcalc],
)

test('test_tokens', test_tokens)
test('test_ast', test_ast)