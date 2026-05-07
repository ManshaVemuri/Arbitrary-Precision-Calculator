# APC — Arbitrary Precision Calculator

A command-line calculator in C that performs arithmetic on arbitrarily large integers — numbers that exceed the limits of standard `int` or `long long` types. Built using a **doubly linked list (DLL)** to store each digit individually, enabling operations on numbers of any size.

---

## Features

- **Addition** of two large numbers
- **Subtraction** with automatic sign handling (handles cases where the second operand is larger)
- **Multiplication** using the standard long-multiplication algorithm
- **Integer Division** with divide-by-zero protection
- Input validation for operators and numeric arguments
- Proper memory management — all allocated nodes are freed after use

---

## Project Structure

```
apc3/
├── apc.h         # Header file: struct definitions, macros, function declarations
├── main.c        # Entry point: argument parsing, validation, dispatch
├── helpers.c     # DLL utility functions (insert, compare, copy, print, free, etc.)
├── operators.c   # Arithmetic operations (Addition, Subtraction, Multiplication, Division)
└── a.out         # Pre-compiled binary (Linux x86-64)
```

---

## How It Works

Each number is stored as a doubly linked list where every node holds a single decimal digit. For example, `12345` is stored as:

```
[1] <-> [2] <-> [3] <-> [4] <-> [5]
```

This representation allows operations to be performed digit-by-digit from either end of the number, just like manual arithmetic — carrying, borrowing, and shifting as needed.

---

## Build

Compile from source using `gcc`:

```bash
gcc main.c helpers.c operators.c -o apc
```

---

## Usage

```bash
./apc <number1> <operator> <number2>
```

### Supported Operators

| Operator | Operation      |
|----------|----------------|
| `+`      | Addition       |
| `-`      | Subtraction    |
| `*`      | Multiplication |
| `/`      | Division       |

> **Note:** When using `*` for multiplication in a Unix shell, wrap it in single quotes to prevent shell globbing:
> ```bash
> ./apc 123 '*' 456
> ```

### Examples

```bash
$ ./apc 99999999999999999999 + 1
Result = 100000000000000000000

$ ./apc 1000000000000 - 999999999999
Result = 1

$ ./apc 123456789 '*' 987654321
Result = 121932631112635269

$ ./apc 100000000000 / 7
Result = 14285714285

$ ./apc 5 - 10
Result = -5
```

---

## Input Validation

The program validates all inputs before processing:

- Exactly 3 arguments must be provided (`<num1> <operator> <num2>`)
- Both numbers must contain only digit characters (`0–9`)
- The operator must be one of: `+`, `-`, `*`, `/`
- Division by zero is detected and reported as an error

---

## Implementation Notes

- **Subtraction** automatically swaps operands if the first is smaller and prepends a `-` sign node to the result.
- **Multiplication** uses the classic shift-and-add approach — each digit of the second number multiplies the entire first number, with the partial result shifted (zero-padded) before being accumulated.
- **Division** implements long division: digits are brought down one at a time into a running remainder, and repeated subtraction counts how many times the divisor fits.
- **Leading zeros** are stripped from results using `remove_leading_zeros()`.

---

## Author

**Mansha Vemuri**
