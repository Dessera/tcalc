# Tcalc Syntax Reference

## Expression

Tcalc expressions are pretty similar to ordinary programming languages, here are some examples:

```plaintext
-3
1 + 2
(1 + 2) * 3
sqrt(2)
1 + 2 * 3 / sqrt(pow(3, 2)) - -pi
```

`if` statement is also supported:

```plaintext
if 1 > 0 then 1 else 0
```

Users can also terminate an expression with a semicolon:

```plaintext
1 + 2;
```

### Binary operators

| Operator | Description | Priority |
| --- | --- | --- |
| `*` | Multiplication | 3 |
| `/` | Division | 3 |
| `+` | Addition | 2 |
| `-` | Subtraction | 2 |
| `==` | Equal to | 1 |
| `!=` | Not equal to | 1 |
| `>` | Greater than | 1 |
| `<` | Less than | 1 |
| `>=` | Greater than or equal to | 1 |
| `<=` | Less than or equal to | 1 |
| `&&` | Logical AND | 0 |
| `\|\|` | Logical OR | 0 |

### Unary operators

| Operator | Description |
| --- | --- |
| `-` | Negate |
| `+` | Identity |
| `!` | Logical NOT |

## Identifier

Tcalc use alphanumeric characters, underscores and Decimal digits to form identifiers. Identifiers must start with a letter or an underscore, here are some examples:

```plaintext
a
abc
abc123
_abc
```

If you want to use a non-standard identifier, you can use signle quotes:

```plaintext
'hello world'
```

## Function

Use `def` keyword to define a function:

```plaintext
def add(a, b) a + b
```

Tcalc also supports recursive functions:

```plaintext
def fib(n) if n <= 1 then n else fib(n - 1) + fib(n - 2)
```

You can call a function by its name with arguments:

```plaintext
add(1, 2)
```

### Built-in functions

| Function | Description |
| --- | --- |
| `sqrt(x)` | Square root |
| `pow(x, y)` | Power |
| `sin(x)` | Sine |
| `cos(x)` | Cosine |
| `tan(x)` | Tangent |
| `asin(x)` | Arcsine |
| `acos(x)` | Arccosine |
| `atan(x)` | Arctangent |

## Variable Assignment

Use `let` keyword to assign a value to a variable:

```plaintext
let a = 1
```

You can also assign a value to a variable in an expression:

```plaintext
let a = 1 + 2
```

### Built-in variables

| Variable | Description |
| --- | --- |
| `pi` | Pi |
| `e` | Euler's number |

## Import

Use `import` keyword to import a module:

```plaintext
import hello
```

or:

```plaintext
import 'hello.tc'
```
