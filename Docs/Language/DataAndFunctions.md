# C4 Language Documentation
## Part I — Core Concepts
 
---
 
# 1. Data Types
 
> **Audience:** This chapter is written for someone who already programs in at least one language
> but is new to C4. No prior knowledge of C is required.
> **Goal:** By the end of this chapter you will be able to write a valid C4 program that
> declares variables, performs arithmetic, and prints output to the screen.
 
---
 
## What a C4 program looks like
 
Every C4 program starts executing from a function called `main`. Here is the smallest valid C4
program:
 
```c4
fn main() -> i32:
    return 0
:
```
 
There are four things to notice here:
 
- `fn` begins a function declaration.
- `main` is the name of the function. The runtime always calls `main` first.
- `-> i32` declares that `main` returns a 32-bit integer. By convention, returning `0` signals
  that the program finished successfully.
- The block opens with a `:` after the function signature and closes with a standalone `:` on
  its own line. Every block in C4 works this way — there are no curly braces.
 
A program that prints a message looks like this:
 
```c4
fn main() -> i32:
    printf("Hello, world\n")    // print a message to the terminal
    return 0
:
```
 
`\n` is an escape sequence that moves the cursor to a new line after printing. Without it, the
next line of output would appear immediately after your message on the same line.
 
---
 
## 1.1 Concept Overview
 
A type tells the compiler what kind of value a variable holds and how much memory to reserve
for it. Every variable in C4 must have a declared type before it can be used. Types serve two
purposes:
 
- **Correctness** — the compiler can catch operations that make no sense for a given kind of
  value (for example, taking the remainder of a floating-point number).
- **Efficiency** — knowing the size and representation of a value at compile time allows the
  compiler to generate optimal machine code.
 
---
 
## 1.2 Classification
 
C4 provides three primitive types in the current documentation:
 
| Type | Meaning | Example values |
| ------ | --------- | --------------- |
| `i32` | 32-bit signed integer | `0`, `-7`, `2048` |
| `f32` | 32-bit floating-point number | `3.14`, `-0.5`, `1.0` |
| `char` | A single character | `'A'`, `'z'`, `'9'` |
 
Use `i32` when you are counting, indexing, or doing whole-number arithmetic. Use `f32` when
you need decimal precision — for measurements, averages, or any calculation where truncating
the fractional part would give a wrong answer. Use `char` when you are working with a single
symbol.
 
> **[PENDING]** The full primitive type table has not yet been published. This table will
> be expanded to include all types (signed/unsigned integers of other widths, etc.) once
> the spec is delivered. Do not treat this table as exhaustive.
 
> **[PENDING]** Composite types have not yet been specified in the documentation. This
> section will be expanded once confirmed.
 
---
 
## 1.3 Syntax and Declaration
 
### Declaring variables
 
Before you can use a variable you must declare it. A declaration states the type followed by
the name:
 
```c4
// fragment — declarations only
i32 answer
f32 pi
char letter
```
 
Declaration reserves space for the variable but does not give it a value. To store a value, use
an assignment statement:
 
```c4
// fragment
i32 answer
answer = 42
```
 
You can also combine declaration and assignment into a single line:
 
```c4
// fragment
i32 answer = 42
f32 pi = 3.14159
char letter = 'A'
```
 
The combined form is preferred whenever the initial value is known at the point of declaration —
it makes the code easier to read and avoids the risk of using an uninitialised variable.
 
> **[PENDING]** What happens if you read a variable before assigning it is not yet
> specified in the documentation. Depending on the compiler this may be a compile-time error
> (preferable) or undefined behavior. This section will be updated once confirmed.
 
### Characters
 
A `char` variable stores a single character. Write character literals with single quotes:
 
```c4
fn main() -> i32:
    char c = 'A'
    printf("%c\n", c)   // prints: A
    return 0
:
```
 
Characters are printed with the `%c` format specifier (not `%d`).
 
C4 supports the standard escape sequences inside character and string literals:
 
| Sequence | Meaning |
| ---------- | --------- |
| `\n` | Newline — moves to the next line |
| `\t` | Tab — inserts a horizontal tab |
| `\\` | A literal backslash character |
| `\'` | A literal single-quote character |
| `\"` | A literal double-quote character |
 
---
 
## 1.4 Memory Representation
 
> **[PENDING]** The memory representation of each data type — including size in bytes,
> memory layout, and alignment and padding rules — has not yet been specified in the
> documentation. This section will be updated once confirmed.
 
---
 
## 1.5 Type Behavior
 
### Arithmetic expressions
 
C4 supports the standard arithmetic operators:
 
| Operator | Operation | Example |
| ---------- | ----------- | --------- |
| `+` | Addition | `3 + 4` → `7` |
| `-` | Subtraction | `10 - 3` → `7` |
| `*` | Multiplication | `3 * 4` → `12` |
| `/` | Division | `10 / 4` → `2` (integers), `2.5` (floats) |
| `%` | Remainder (modulo) | `10 % 3` → `1` |
 
### Operator precedence
 
When an expression contains more than one operator, C4 evaluates them in this order:
 
1. Parentheses `()` — evaluated first, innermost first
2. `*`, `/`, `%` — evaluated left to right
3. `+`, `-` — evaluated left to right
 
This means `1 + 2 * 4` evaluates to `9`, not `12`, because the multiplication happens before
the addition. When in doubt, use parentheses to make the intended order explicit:
 
```c4
fn main() -> i32:
    i32 result = (1 + 2) * 4    // parentheses force addition first → 12
    printf("%d\n", result)
    return 0
:
```
 
### Integer division vs floating-point division
 
This is one of the most common sources of bugs when coming from a higher-level language. The
type of the operands determines how division works:
 
```c4
fn main() -> i32:
    i32 a = 1 / 3       // both operands are integers → result is 0 (truncated)
    f32 b = 1.0 / 3.0   // both operands are floats → result is ~0.333
    printf("%d\n", a)   // prints: 0
    printf("%f\n", b)   // prints: 0.333333
    return 0
:
```
 
Integer division always truncates toward zero — it drops the decimal part entirely. `7 / 2`
gives `3`, not `3.5`.
 
> **Warning:** Mixing integer and floating-point operands in a single expression may produce
> unexpected results. The exact promotion rules are **[PENDING]**. Until confirmed, write
> both operands in the type you intend: `1.0 / 3.0` for float division, `1 / 3` for integer
> division.
 
> **[PENDING]** Type conversion rules (implicit and explicit) and casting rules have not
> yet been specified in the documentation. This section will be updated once confirmed.
 
---
 
## 1.6 Code Examples
 
### Example 1 — Declaring and printing each primitive type
 
```c4
fn main() -> i32:
    i32 score = 95
    f32 average = 91.5
    char grade = 'A'
    printf("Score: %d\n", score)        // %d prints an i32
    printf("Average: %f\n", average)    // %f prints an f32
    printf("Grade: %c\n", grade)        // %c prints a char
    return 0
:
```
 
### Example 2 — Arithmetic and operator precedence
 
```c4
fn main() -> i32:
    i32 result = (1 + 2) * 4    // parentheses force addition first → 12
    printf("%d\n", result)
    return 0
:
```
 
### Example 3 — Integer division vs floating-point division
 
```c4
fn main() -> i32:
    i32 a = 1 / 3       // both operands are integers → result is 0 (truncated)
    f32 b = 1.0 / 3.0   // both operands are floats → result is ~0.333
    printf("%d\n", a)   // prints: 0
    printf("%f\n", b)   // prints: 0.333333
    return 0
:
```
 
### Example 4 — Printing multiple values in one call
 
```c4
fn main() -> i32:
    i32 width = 10
    i32 height = 5
    printf("Width: %d, Height: %d\n", width, height)
    return 0
:
```
 
### Example 5 — Character and its numeric value
 
```c4
fn main() -> i32:
    char c = 'B'
    printf("Character: %c\n", c)       // prints: B
    printf("Numeric value: %d\n", c)   // prints: 66
    return 0
:
```
 
> **[PENDING]** Whether `printf` is part of a C standard library bundled with C4 or a
> built-in language construct has not yet been confirmed. This affects whether a module import
> or `#include` equivalent is needed. This section will be updated once confirmed.
 
---
 
## 1.7 Common Errors
 
### Mistake 1 — Integer division when you wanted a decimal result
 
```c4
// fragment — WRONG
i32 result = 7 / 2
printf("%d\n", result)   // prints 3, not 3.5
```
 
If you need the decimal part, use `f32` and floating-point literals:
 
```c4
// fragment — correct
f32 result = 7.0 / 2.0
printf("%f\n", result)   // prints 3.500000
```
 
### Mistake 2 — Mismatched format specifier
 
Using the wrong specifier for a type produces garbled or incorrect output:
 
```c4
// fragment — WRONG
f32 pi = 3.14159
printf("%d\n", pi)   // %d expects i32, not f32 — output is unpredictable
```
 
Always match the specifier to the type of the variable:
 
```c4
// fragment — correct
f32 pi = 3.14159
printf("%f\n", pi)   // prints 3.141590
```
 
### Mistake 3 — Forgetting `\n` at the end of a printf
 
```c4
// fragment — easy to miss
printf("Result: %d", answer)    // cursor stays on the same line
printf("Done")                  // prints immediately after — reads: "Result: 42Done"
```
 
Always end format strings with `\n` unless you intentionally want the next output on the same
line:
 
```c4
// fragment — correct
printf("Result: %d\n", answer)
printf("Done\n")
```
 
### Mistake 4 — Using a variable before declaring it
 
```c4
// fragment — WRONG
total = 100    // error: 'total' has not been declared
i32 total
```
 
Always declare a variable before you use it. The declaration must appear earlier in the block
than any statement that reads or writes the variable:
 
```c4
// fragment — correct
i32 total
total = 100
```
 
---
 
## 1.8 Best Practices
 
> **[PENDING]** Best practices for choosing appropriate types and writing safe and portable
> code have not yet been specified in the documentation. This section will be updated once
> confirmed.
 
---
 
# 2. Functions
 
## 2.1 Concept Overview
 
In C4, functions are the **fundamental building blocks of modularity**. A function is a self-contained block of code designed to perform a specific task, allowing for:
 
- **Code reuse** — write logic once, call it anywhere
- **Improved readability** — complex programs become easier to follow
- **Easier debugging** — smaller, isolated units are simpler to test and fix
 
By breaking complex logic into smaller, testable units, functions enable structured programming and efficient memory management.
 
---
 
## 2.2 Syntax and Structure
 
C4 uses a clean, **colon-delimited syntax** for function definitions, emphasizing clarity and type safety.
 
- **Function Definition:** A function starts with the `fn` keyword (or `pub fn` for global visibility), followed by the name, parameters, return type arrow `->`, and a terminating colon `:`.
- **Return Types:** All functions must explicitly declare a return type (e.g., `i32`, `void`).
 
### Structure
 
```c4
// Syntax Pattern
pub fn name(type param1, type param2) -> return_type:
    // logic
    return value
:
```
 
| Component | Description |
|---|---|
| `pub fn` | Declares a publicly visible function |
| `fn` | Declares a private (file-scoped) function |
| `type param` | Named parameter with its type |
| `-> return_type` | The type of value the function returns |
| `:` ... `:` | Block delimiters — equivalent to `{` and `}` in C or Java |
 
---
 
## 2.3 Function Behavior
 
### Parameter Passing
 
C4 currently implements **Pass-by-Value**. When a function is called, a _copy_ of the argument's value is passed into the function's local scope.
 
> ⚠️ Changes made to parameters inside the function **do not** affect the original variables in the calling scope.
 
### Return Value Handling
 
The `return` keyword immediately halts function execution and passes the resulting value back to the caller. At the assembly level, this value is stored in the `%rax` (or `%eax`) register.
 
---
 
## 2.4 Execution Model
 
C4 follows a standard **stack-based execution model**. When a function is invoked, the following steps occur in order:
 
1. **Call** — The return address is pushed onto the stack.
2. **Prologue** — The function saves the previous base pointer (`rbp`) and sets up its own stack frame by moving the stack pointer (`rsp`).
3. **Local Storage** — Space is allocated on the stack for local variables (e.g., `i32 a = 20`).
4. **Epilogue** — Before returning, the function tears down its stack frame and pops the return address to jump back to the caller.
 
> 💡 Think of the stack like a pile of trays — each function call adds a tray on top, and each return removes it cleanly.
 
---
 
## 2.5 Code Examples
 
### Example 1 — Basic Function (No Parameters)
 
A function that takes no input and returns a constant value.
 
```c4
fn get_answer() -> i32:
    return 42
:
 
pub fn main() -> i32:
    i32 result = get_answer()
    return result
:
```
 
---
 
### Example 2 — Addition
 
```c4
fn add_numbers(i32 a, i32 b) -> i32:
    i32 sum = a + b
    return sum
:
 
pub fn main() -> i32:
    i32 result = add_numbers(3, 7)
    return result
:
```
 
---
 
### Example 3 — Subtraction
 
```c4
fn subtract(i32 a, i32 b) -> i32:
    i32 result = a - b
    return result
:
 
pub fn main() -> i32:
    i32 result = subtract(10, 4)
    return result
:
```
 
---
 
### Example 4 — Multiplication
 
```c4
fn multiply(i32 a, i32 b) -> i32:
    i32 result = a * b
    return result
:
 
pub fn main() -> i32:
    i32 result = multiply(6, 7)
    return result
:
```
 
---
 
### Example 5 — Square a Number
 
A function that takes a single value and returns it multiplied by itself.
 
```c4
fn square(i32 a) -> i32:
    i32 result = a * a
    return result
:
 
pub fn main() -> i32:
    i32 result = square(9)
    return result
:
```
 
---
 
### Example 6 — Cube a Number
 
```c4
fn cube(i32 a) -> i32:
    i32 result = a * a * a
    return result
:
 
pub fn main() -> i32:
    i32 result = cube(3)
    return result
:
```
 
---
 
### Example 7 — Double a Value
 
```c4
fn double(i32 a) -> i32:
    return a * 2
:
 
pub fn main() -> i32:
    i32 result = double(15)
    return result
:
```
 
---
 
### Example 8 — Triple a Value
 
```c4
fn triple(i32 a) -> i32:
    return a * 3
:
 
pub fn main() -> i32:
    i32 result = triple(5)
    return result
:
```
 
---
 
### Example 9 — Increment and Decrement
 
```c4
fn increment(i32 a) -> i32:
    return a + 1
:
 
fn decrement(i32 a) -> i32:
    return a - 1
:
 
pub fn main() -> i32:
    i32 value = 10
    i32 up = increment(value)
    i32 down = decrement(value)
    return up
:
```
 
---
 
### Example 10 — Average of Two Numbers
 
> 💡 Using `f32` throughout ensures decimal results are preserved. `average(7.0, 2.0)` correctly returns `4.5`, not `4`.
 
```c4
fn average(f32 a, f32 b) -> f32:
    f32 sum = a + b
    f32 result = sum / 2.0
    return result
:
 
pub fn main() -> f32:
    f32 result = average(10.0, 20.0)
    return result
:
```
 
---
 
### Example 11 — Sum of Three Numbers
 
```c4
fn sum_three(i32 a, i32 b, i32 c) -> i32:
    i32 result = a + b + c
    return result
:
 
pub fn main() -> i32:
    i32 result = sum_three(5, 10, 15)
    return result
:
```
 
---
 
### Example 12 — Chaining Functions
 
The output of one function is passed directly as the input to another.
 
```c4
fn double(i32 a) -> i32:
    return a * 2
:
 
fn square(i32 a) -> i32:
    i32 result = a * a
    return result
:
 
pub fn main() -> i32:
    i32 step1 = double(4)
    i32 step2 = square(step1)
    return step2
:
```
 
`double(4)` → `8`, then `square(8)` → `64`.
 
---
 
## 2.6 Common Errors
 
| Error | Cause | Fix |
|---|---|---|
| `Undefined reference to 'main'` | Entry point not marked `pub`, making it invisible to the linker | Change `fn main` to `pub fn main` |
| Missing return | Function declares `-> i32` but reaches the closing `:` without a `return` statement | Always include a `return` statement matching the declared type |
 
> ⚠️ A missing `return` does not cause a compile-time error in all cases — but the value left in `%rax` will be **undefined**, leading to unpredictable runtime behaviour.
 
---
 
## 2.7 Best Practices
 
### Visibility
 
Only use `pub` for functions that need to be accessed from other files or by the OS (such as `main`). Keep internal helper functions private with `fn` alone.
 
```c4
fn helper_logic() -> i32:   // private — not accessible outside this file
    return 1
:
 
pub fn main() -> void:      // public — entry point visible to the linker
    helper_logic()
:
```
 
### Naming
 
Use `snake_case` for all function names to maintain consistency with the C4 standard library.
 
```c4
// ✅ Good
pub fn calculate_total() -> i32:
 
// ❌ Avoid
pub fn CalculateTotal() -> i32:
```
 
### Single Responsibility
 
Each function should do **exactly one thing**. If a function is performing more than two distinct logical tasks, consider splitting it into smaller functions.
 
```c4
// ❌ Doing too much in one function
pub fn process_and_print(i32 x) -> void:
    i32 result = x * 2
    // ... additional unrelated logic
    // ... printing logic
:
 
// ✅ Separated responsibilities
fn double_value(i32 x) -> i32:
    return x * 2
:
 
pub fn print_result(i32 x) -> void:
    // printing logic only
:
```
 
---
