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
def factorial(n) if n then n * factorial(n - 1) else 1
```

> It's undefined behavior to call a function that recurses infinitely for now.

## Function Call

Use `()` to call a function.

```plaintext
add(1, 2)
```

## Control Flow

### If

Use `if` to make a decision.

```plaintext
if a then a else b
```

> There is no boolean expression for now.
