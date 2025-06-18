# Tcalc Syntax Reference

## Variable Assignment

Use keyword `let` to declare and assign a value to it.

```plaintext
let x = 5
```

Note that you can reassign a variable later, which will overwrite its previous value.

> Actually, there is no `declaration` in tcalc, keyword `let` is just a helper for ast parser.

## Function Declaration

Use keyword `def` to declare a function.

```plaintext
def add(a, b) a + b
```

You can recursively call a function in its body:

```plaintext
def factorial(n) if n < 2 then 1 else n * factorial(n - 1)
```

## Function Call

Use `()` to call a function.

```plaintext
add(1, 2)
```

## Import

Use keyword `import` to import a module.

```plaintext
import math
```

or use complex identifiers:

```plaintext
import 'math.tc'
```

## Control Flow

### If

Use `if` to make a decision.

```plaintext
if a < 5 then a else 5
```

## Operator

### Arithmetic

- `+` add
- `-` subtract
- `*` multiply
- `/` divide

### Comparison

- `==` equal
- `!=` not equal
- `<` less than
- `>` greater than
- `<=` less than or equal to
- `>=` greater than or equal to

### Unary

- `+` positive
- `-` negative
