# Chapter 4. Taking Out the Last Value First

We will use one rule for remembering work that must finish in reverse order.

## Thinking Logically

### Why do we need a special order?

In `1-2*3+4`, multiplication must happen before subtraction and addition. An operator may need to wait while a later operator is processed. If `-` is waiting and `*` arrives, the newer `*` must finish first.

### What does the array look like?

The lab uses this global state:

```c
char stack[10];
int capacity = 10;
int top = 10;
```

The valid array indexes are 0 through 9. The initial `top == 10` marks an
empty Stack; it is not an index we may read. Push decreases `top` before
writing, so the first item goes into `stack[9]`. Later items go into indexes
8, 7, and so on. The Stack grows toward smaller indexes.

With `top == 7`, the active items occupy indexes 7 through 9. The top item
is `stack[7]`, and the number of items is `10 - top`, or 3. Positions below
`top` are inactive. A high physical index does not necessarily mean the
newest item.

`capacity` records the intended capacity, but the current implementation
uses literal `10` for initialization and the empty check. Changing
`capacity` alone does not resize the array or change those operations.

### How do push, peek, and pop change the state?

Use character labels `'A'`, `'B'`, and `'C'` for three saved tasks. In the
logical lists below, the rightmost item is the top. Those lists show arrival
order, not increasing array-index order.

| Request | Returned value | Items, bottom to top | `top` | Active indexes |
|---|---|---|---:|---|
| start | — | empty | 10 | none |
| `push('A')` | none (`void`) | A | 9 | 9 |
| `push('B')` | none (`void`) | A, B | 8 | 8–9 |
| `push('C')` | none (`void`) | A, B, C | 7 | 7–9 |
| `peek()` | `'C'` | A, B, C | 7 | 7–9 |
| `pop()` | `'C'` | A, B | 8 | 8–9 |
| `pop()` | `'B'` | A | 9 | 9 |
| `pop()` | `'A'` | empty | 10 | none |

Pop does not erase the array cell. Increasing `top` makes the old top
inactive. The next push may overwrite it.

### What happens at the boundaries?

The Stack is full when `top == 0`. A full `push` returns without changing
the array or `top`; it does not return a success flag. The Stack is empty
when `top == 10`. Empty `peek` and `pop` return `'\0'` and leave `top`
unchanged. This is a sentinel value, not a separate error status. If a
caller deliberately stores `'\0'`, the returned character alone cannot
distinguish that item from an empty Stack.

These checks protect normal full and empty Stack operations. They do not
validate the expression or repair an externally corrupted `top`.

### How does this relate to function calls?

When one function pauses to call another, the runtime commonly saves a
**call frame** so it can resume the older call later. Nested calls finish
in LIFO order. The inquiry's numeric function IDs and this chapter's
character labels model that order. Neither is a real call frame, and this
global character array is not the runtime call stack.

### Why put operators after their operands?

An **operand** is a value such as `2`. An **operator** is an action such as
`*`. **Infix** places the operator between its operands: `2*3`.
**Postfix** places it after them: `23*`. Each digit is a separate operand
in this lab; `23*` means multiply 2 and 3, not the number 23.

The program has two distinct phases. Conversion uses the global character
Stack to hold waiting operators and writes a character string to `postfix`.
Evaluation later uses a separate local integer array for calculated values.
Conversion does not calculate the arithmetic.

#### Which operator leaves first?

`prec` returns these precedence levels:

| Characters | Precedence |
|---|---:|
| `+`, `-` | 1 |
| `*`, `/`, `%` | 2 |
| other characters, including `'\0'` | 0 |

A digit goes directly to the postfix output. Before pushing an incoming
operator, conversion pops every waiting operator of equal or greater
precedence into that output. The equality case makes operators at the same
level **left associative**: `8-3-2` means `(8-3)-2`.

On an empty Stack, `peek()` returns `'\0'`, whose precedence is 0. This
stops the comparison for the supported operators, which have precedence 1
or 2. The lab does not push a null sentinel onto the Stack.

#### How does the example convert?

Start with `top == 10`. Operator lists run bottom to top.

| Input/action | Postfix characters so far | Waiting operators | `top` |
|---|---|---|---:|
| read `1` | `1` | empty | 10 |
| read `-` | `1` | `-` | 9 |
| read `2` | `12` | `-` | 9 |
| read `*` | `12` | `-`, `*` | 8 |
| read `3` | `123` | `-`, `*` | 8 |
| read `+`: pop `*`, pop `-`, push `+` | `123*-` | `+` | 9 |
| read `4` | `123*-4` | `+` | 9 |
| end: pop remaining `+` | `123*-4+` | empty | 10 |

The input and output arrays each contain eight positions:

```c
char infix[8] = "1-2*3+4";
char postfix[8] = "";
int size = 0;
```

`size` counts postfix characters, not the number of items in the operator
Stack. Conversion resets `size` to 0, scans until the input's `'\0'`, and
finishes by writing `postfix[size] = '\0'`. For the example, `size == 7`;
the terminator occupies index 7 and is not counted as an expression token.

Resetting `size` prevents a second conversion from appending to an old
result. Writing the terminator prevents leftover characters from appearing
when a later expression is shorter. Normal conversion drains the operator
Stack, leaving it empty for the next conversion.

### How do we evaluate the new order?

`eval_postfix()` has its own local Stack:

```c
int values[10];
int pos = 0;
```

Here `pos` counts the active integers. Active indexes are 0 through
`pos - 1`; the top is `values[pos - 1]`. This Stack grows toward larger
indexes. It uses the same LIFO rule as the character Stack with a different
index convention.

| Variable | Meaning | How an item is added |
|---|---|---|
| `top` | index of the character Stack's top; 10 means empty | decrement, then write `stack[top]` |
| `size` | number of postfix characters, excluding `'\0'` | append `postfix[size++]` |
| `pos` | count of active integer values | write `values[pos++]` |

For a digit, `c - '0'` gives the integer value. For an operator, pop two
integers, calculate, and push the result. The first popped value is the
**right** operand, `num2`. The second is the **left** operand, `num1`.
Subtraction, division, and remainder depend on that order.

| Postfix token | Action | Values, bottom to top | `pos` |
|---|---|---|---:|
| `1` | push 1 | 1 | 1 |
| `2` | push 2 | 1, 2 | 2 |
| `3` | push 3 | 1, 2, 3 | 3 |
| `*` | `2 * 3` | 1, 6 | 2 |
| `-` | `1 - 6` | -5 | 1 |
| `4` | push 4 | -5, 4 | 2 |
| `+` | `-5 + 4` | -1 | 1 |

The final `return values[--pos]` returns `-1`. Intermediate values are
integers, so they can be negative or larger than a digit. They are not
stored back into the character Stack.

`calc` implements `+`, `-`, `*`, `/`, and `%`. Division is C integer
division: `7/2` gives 3. Remainder gives what is left after integer division:
`7%2` gives 1. These operations do not produce floating-point results.

### Which inputs may this lab use?

The supplied program assumes a nonempty input matching:

```text
digit (('+' | '-' | '*' | '/' | '%') digit)*
```

Each operand is one digit, and the whole expression must fit in seven
characters plus its null terminator. Inputs contain no spaces, parentheses,
unary operators, or multi-digit operands. Division and remainder require a
nonzero right operand, and arithmetic results must be representable as
`int`. Start conversion with an empty operator Stack, and evaluate only
after a successful conversion of such an input.

These are caller assumptions, not checks implemented by `lab.c`:

- An unsupported character has precedence 0. The conversion loop can keep
  popping an empty Stack and write past `postfix`.
- Missing operands or empty input can make evaluation read below
  `values[0]`. Extra operands are not rejected either.
- Division or remainder by zero is not checked. Arithmetic overflow is not
  checked. The functions have no error-status interface.

Do not interpret a returned 0 from `calc`'s default branch as safe validation:
operand reads have already happened. Adding character/grammar checks,
operand-count checks, buffer bounds, and arithmetic error reporting is an
extension exercise. A discussion of those extensions does not mean they
are already present in the supplied code.

### What must each operation preserve?

For the global character Stack in a valid completed state:

```text
0 <= top <= 10
active indexes: top through 9
number of active items: 10 - top
read stack[top] only when top < 10
```

Push preserves this rule by checking full state, decreasing `top`, then
writing. Pop checks empty state, reads `stack[top]`, then increases `top`.
Peek reads the same top without changing it. Neither operation shifts old
items or erases inactive cells.

The postfix output has a separate bound: `0 <= size <= 7`, leaving room for
`postfix[size] = '\0'`. During valid evaluation, `pos` is the number of
available operands/results; an operator needs two values and the complete
expression leaves exactly one. The current evaluator relies on those facts
rather than checking them.

## Calculating Efficiency

### How much work does one Stack operation do?

Push checks one boundary, changes one index, and writes one cell. Peek checks
one boundary and reads one cell. Pop adds one index update to the read. None
shifts existing elements, so each operation takes `O(1)` time.

### Why are the two expression phases linear?

Conversion of `1-2*3+4` scans seven tokens, pushes three operators, and pops
those three operators. Although one incoming operator can trigger several
pops, no waiting operator is popped twice. For `n` input characters, the
scan and total Stack work therefore take `O(n)` time.

Evaluation reads the seven postfix tokens once. A digit adds one integer.
Each of the three operators removes two integers and adds one result. With
fixed work per token, evaluation also takes `O(n)` time.

### How much storage is reserved?

The program declares ten character positions for operators, eight for infix,
eight for postfix, and ten local integer positions during evaluation. Their
fixed lengths make this `O(1)` storage with respect to input length. The
current input length is capped at seven characters. In a generalized version
whose buffers grow with input, postfix output alone needs `O(n)` space;
Stack space can also grow with the supported expression grammar.

## Glossary

The names below refer to ideas already used in the worked example. The
Stage B vocabulary reference supplies the wider course vocabulary.

| Term | Meaning in this chapter |
|---|---|
| Stack; LIFO | An access rule that removes the newest remaining item first |
| top | The accessible end; global `top` is its character-array index |
| push, peek, pop | Add, inspect, or remove the top item |
| active suffix | Character indexes `top` through 9 |
| underflow | A request to read/remove an item when the Stack is empty |
| sentinel | A special value; here `'\0'` returned by an empty peek/pop |
| invariant | A rule preserved by valid operations, such as `0 <= top <= 10` |
| infix; postfix | Operators between operands; operators after operands |
| operand; operator | A value; an operation applied to values |
| precedence | The ordering priority of operators |
| left associativity | Processing equal-precedence operators left to right |
| null terminator | The `'\0'` at the end of a C string, outside its token count |
| call frame | Runtime information needed to resume a function call |
| precondition | An assumption the caller must satisfy before a function runs |
| integer overflow | A result outside the representable range of `int` |

## Coding Plan

The implementation follows the same example in two phases. Keep the
character operator Stack separate from the integer values used later.

1. **Prepare character storage.** Start `top` at 10. Define full as 0 and
   empty as 10. On push, check full, decrement, then write. On peek/pop,
   check empty before reading; only pop increments `top` afterward.
2. **Set precedence and strings.** Use level 1 for `+`/`-`, level 2 for
   `*`/`/`/`%`. Reserve space for seven tokens and one terminator in each
   expression array. `size` counts output tokens only.
3. **Convert to postfix.** Start with the operator Stack empty. Reset
   `size`, scan digits into output, and use precedence to decide when to
   emit waiting operators. Drain the Stack and terminate the output.
4. **Define integer calculations.** Calculate `num1 op num2` for each
   supported operator. The caller must satisfy the arithmetic assumptions.
5. **Evaluate postfix.** Start `pos` at zero in a local integer array.
   Convert digits to numbers. Pop right before left for each operator and
   push the result. A valid complete expression leaves one result.
6. **Run and collect evidence.** Use the separate driver, then test LIFO,
   boundaries, precedence, operand order, and repeated/shorter conversion.
   Discuss missing validation separately from observed supported behavior.

## New C Syntax Explained

The program must store expression characters, move array boundaries, and
choose an arithmetic operation. The syntax below connects those actions to
the code. Some forms repeat earlier chapters in a new setting.

### Characters, numbers, and terminated strings

The expression stores written digits before evaluation turns them into
numbers. `'3'` is a character constant, `3` is an integer value, and `"3"`
is a string containing the character `'3'` followed by `'\0'`. Single quotes
mark one character; double quotes mark a string. The null character `'\0'`
has value zero. It differs from the digit character `'0'`.

`char infix[8] = "1-2*3+4";` reserves eight character positions for seven
expression characters and the terminator. `char postfix[8] = "";`
initializes all eight positions to zero. `infix[i] != '\0'` asks whether
the scan has reached the end. After conversion, `postfix[size] = '\0';`
writes the terminator after the last output character.

A checked digit becomes a number through `c - '0'`. C guarantees consecutive
values for the digit characters, so `'3' - '0'` produces integer 3. The
single quotes around `'+'` in a comparison identify an operator character;
the unquoted `+` in `num1 + num2` performs addition.

### Combining and reversing conditions

A precedence level can accept more than one operator. In
`op == '+' || op == '-'`, `||` means logical OR: at least one comparison
must be true. C checks the right comparison only when the left is false.
The familiar `&&` in `c >= '0' && c <= '9'` requires both comparisons to
hold and checks the right only when the left is true.

The final drain must continue while the character Stack has an item.
`!is_empty()` uses logical NOT: `!` produces 1 when its operand is zero and
0 otherwise. `is_empty()` returns 1 for an empty Stack, so the negated
condition is false at that boundary. Comparisons such as `top == 10`
also produce integer 1 for true and 0 for false.

### Updating an index or count

Push and pop move the boundary by one position. `top -= 1;` subtracts one
from `top`, and `top += 1;` adds one. Here they have the same effect as
`top = top - 1;` and `top = top + 1;`.

An append needs the old free position. In `postfix[size++] = c;`, postfix
increment supplies the old `size` as the index. Starting at 3 writes
`postfix[3]` and leaves `size` equal to 4. `values[pos++]` uses the same
rule for integer storage.

Removing an integer needs the last occupied position. Prefix decrement in
`values[--pos]` decreases `pos` before supplying the index. Starting at 3
reads `values[2]` and leaves `pos` equal to 2. The two operand reads are
separate statements, so the right operand is removed before the left.

### Choosing a calculation with `switch` and `case`

The evaluator must select one calculation from the operator character.
`switch (op)` evaluates `op` and starts at the matching `case` label.
`case '+':` is a label ending with a colon; it identifies the addition
branch. Character constants can be compared with the integer parameter
`op`.

Every supplied case ends with `return`, which finishes the whole `calc`
call and sends the calculated integer back to its caller. A `break` is
therefore unnecessary here. Without `return` or `break`, execution could
continue into the next case. If no case matches, execution reaches the
`return 0;` after the switch. That fallback does not validate an expression.

### Integer division and remainder

The value array stores integers, so `/` performs integer division:
`7 / 2` produces 3. Division discards the fractional part toward zero;
`-7 / 2` produces -3. `%` computes the remainder: `7 % 2` produces 1,
and `-7 % 2` produces -1. This `%` is an arithmetic operator. It has a
different role from `%d` inside a printing format string.

The right operand must be nonzero for `/` and `%`. The arithmetic result
must also be representable as `int`. The lab assumes valid arithmetic;
these operators do not provide an error result when that assumption fails.

### Referring to definitions in another source file

The demonstration driver needs the arrays and functions defined in
`student/lab.c`. `extern char infix[8];` declares the existing array's name
and type so the driver can use it. This declaration does not create a
second array. The same rule applies to `postfix` and `size`. Both source
files must be compiled and linked into the program.

`void infix_to_postfix(void);` declares a function without defining its
body. The leading `void` means no value is returned; `(void)` means no
parameters. The final semicolon ends the declaration. This form is a
**function prototype**, which lets the compiler check calls. In C11, the
lab's definitions written with `()` do not provide the same parameter
checking for callers.

### Printing strings and discarding a return value

The driver displays the stored characters and the computed answer.
`#include <stdio.h>` supplies the declaration of `printf`. Its `%s`
conversion prints characters until a null terminator; `%d` prints an
integer. `\n` moves the output to a new line.

In `(void)printf("size: %d\n", size);`, `(void)` is a cast that explicitly
discards `printf`'s return value. The call still runs and prints the size.
It differs from `(void)` in a function's parameter list. The argument
`eval_postfix()` in the final display call is evaluated to obtain the
integer that `%d` will print. `return 0;` then ends `main` and reports
successful completion.

## C Code

The blocks below reproduce the current lab functions in source order. They
are one program split for reading, not independent programs. `lab.c` has
no `main`; the last block is its separate demonstration driver.

Before reading, distinguish `'3'` (a character), `3` (an integer), and
`"3"` (a character string with a terminator). C guarantees consecutive digit
character values, so `c - '0'` converts a checked digit to its integer value.
In `postfix[size++] = c`, indexing uses the old count before incrementing.
In `values[--pos]`, decrement happens first, selecting the current top.

### Character Stack operations

The checks prevent ordinary full and empty operations from indexing outside
the array. They do not validate arbitrary changes to the global `top`.

```c
char stack[10];
int capacity = 10;
int top = 10;

int is_full() {
    return top == 0;
}

void push(char data) {
    if (is_full()) {
        return;
    }
    top -= 1;
    stack[top] = data;
}

int is_empty() {
    return top == 10;
}

char peek() {
    if (is_empty()) {
        return '\0';
    }
    return stack[top];
}

char pop() {
    if (is_empty()) {
        return '\0';
    }
    char data = stack[top];
    top += 1;
    return data;
}
```

### Precedence and expression storage

The same seven input tokens will be rearranged into seven output tokens.
Each array has an eighth position for its terminator.

```c
int prec(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/' || op == '%') {
        return 2;
    }
    return 0;
}

char infix[8] = "1-2*3+4";

char postfix[8] = "";
int size = 0;
```

### Infix-to-postfix conversion

Conversion writes operators into the output without evaluating them. The
`>=` comparison includes equal precedence to preserve left associativity.
For supported operators, an empty peek has lower precedence and ends the loop.

```c
void infix_to_postfix() {
    size = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];

        if (c >= '0' && c <= '9') {
            postfix[size++] = c;
        }
        else {
            char op = peek();
            while (prec(op) >= prec(c)) {
                postfix[size++] = pop();
                op = peek();
            }
            push(c);
        }
    }
    while (!is_empty()) {
        postfix[size++] = pop();
    }
    postfix[size] = '\0';
}
```

### Integer operations

The order of arguments matters for subtraction, division, and remainder.
The source assumes a nonzero divisor and representable arithmetic results.

```c
int calc(int num1, int num2, int op) {
    switch (op) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return num1 / num2;
        case '%': return num1 % num2;
    }
    return 0;
}
```

### Postfix evaluation

Digits and intermediate results live in the integer array. Each operator
removes its right operand first, then its left operand.

```c
int eval_postfix() {
    int values[10];
    int pos = 0;

    for (int i = 0; i < size; i++) {
        char c = postfix[i];
        if (c >= '0' && c <= '9') {
            values[pos++] = c - '0';
        }
        else {
            int num2 = values[--pos];
            int num1 = values[--pos];
            values[pos++] = calc(num1, num2, c);
        }
    }

    return values[--pos];
}
```

### A separate entry point

The companion `code/lab_demo.c` supplies `main`. Compile it together with
`student/lab.c`; do not paste another copy of the lab definitions into it.

```c
/* Entry point for the instructional functions in ../student/lab.c. */
#include <stdio.h>

extern char infix[8];
extern char postfix[8];
extern int size;

void infix_to_postfix(void);
int eval_postfix(void);

int main(void)
{
    infix_to_postfix();
    (void)printf("infix: %s\n", infix);
    (void)printf("postfix: %s\n", postfix);
    (void)printf("size: %d\n", size);
    (void)printf("result: %d\n", eval_postfix());
    return 0;
}
```

From `module_04_stack/code`, run:

```sh
make lab-demo
make lab-tests
```

The demo prints:

```text
infix: 1-2*3+4
postfix: 123*-4+
size: 7
result: -1
```

For new C declarations, write `(void)` when a function takes no parameters.
The supplied lab still spells those definitions with `()`; C11 compilers
may warn about the missing prototypes. Record the actual diagnostics.

Before running, explain why the character Stack becomes empty again, why
`size` is 7 rather than 8, and why subtraction receives 1 as its left
operand and 6 as its right operand. Then predict another valid expression
that fits the arrays and compare your trace with the program.

The older `int_stack_*` and `expression_evaluate` sources under `code/`
use a different checked interface. They remain an optional comparison;
they are not the implementation described by this chapter or the core lab.

## Full C Code Explanation

This reference follows the six blocks in the C Code section. It explains
every declaration and function, then connects the statements to the worked
expression `1-2*3+4`. Keep track of what each function returns and what it
changes in shared storage. Those are separate ways to produce a result.

### 1. Reading declarations, function calls, and shared state

First identify the storage that survives between calls. A declaration such
as `int top = 10;` introduces a variable, gives its type, and sets its
initial value. An assignment such as `size = 0;` changes an existing
variable. Semicolons end these declarations and statements. Curly braces
group the statements belonging to a function, condition, or loop.

The definitions outside functions create global storage. `stack`,
`capacity`, `top`, `infix`, `postfix`, and `size` last for the program's
execution. Their initializers run as part of preparing that storage, not
whenever a helper is called. Every Stack operation uses the same `stack`
and `top`.

The return type tells us what a call supplies to its caller. `push` and
`infix_to_postfix` return `void`, so their work is recorded by changing
global variables. `peek` and `pop` return a `char`. The other lab functions
return an `int`. `return;` ends a `void` function without a value;
`return data;` ends a function and supplies the value of `data`.

Parameters and ordinary local variables belong to one call. In
`push(char data)`, `data` receives a copy of the supplied character. In
`pop`, the local variable also named `data` is a separate object. The
`i` and `c` variables in the converter are separate from those in the
evaluator. Reusing a name does not share its value between functions.

Defining a function does not execute its body. The driver starts in `main`,
calls the converter, prints the stored strings and length, and calls the
evaluator to obtain the value for the final printed line. The lab functions
themselves do not print anything.

### 2. Character storage: why an empty Stack starts at ten

The first declarations reserve space and describe which cells are active.
`char stack[10];` reserves ten character cells at indexes 0 through 9. As a
global array with no explicit initializer, its cells initially contain
zero characters. Their contents do not determine whether the Stack is
empty; `top` does.

`int capacity = 10;` records the intended capacity. It is a separate
integer, not a command to resize the array. The supplied Stack functions
use literal `10` for their empty boundary and do not read `capacity`.
Changing only that variable would leave the actual array and checks as
they were.

`int top = 10;` starts just beyond the last valid index. No cell is active
yet. The program may store the number 10 in `top`, but it must not read
`stack[10]`. A successful push first moves `top` to 9, making the first
write valid. With three items, `top` is 7 and the active cells are 7, 8,
and 9. The item count is `10 - top`.

### 3. `is_full` and `push`: check, move, then write

Before adding a character, the program must establish that a free cell
exists. `is_full` returns the result of `top == 0`. Equality produces
integer 1 when true and 0 when false. It compares `top` without changing
it or reading the array.

`push(char data)` first calls `is_full`. An `if` condition treats zero as
false and a nonzero value as true. If the Stack is full, `return;` ends
the call immediately. Neither `top` nor the array changes. Because `push`
returns `void`, it does not supply a success flag.

Otherwise, `top -= 1;` decreases the index by one. Only then does
`stack[top] = data;` copy the character into the newly active cell. The
order prevents an empty Stack from writing at index 10.

| Call | `top` before | Cell written | `top` after |
|---|---:|---|---:|
| `push('A')` | 10 | `stack[9] = 'A'` | 9 |
| `push('B')` | 9 | `stack[8] = 'B'` | 8 |
| `push('C')` | 8 | `stack[7] = 'C'` | 7 |

Reaching the closing brace returns control to the caller. The parameter
`data` belongs to the completed call, but its copied character remains in
the global array. Existing characters do not move.

### 4. `is_empty`, `peek`, and `pop`: read before removing

Reading the next character first requires ruling out the empty state.
`is_empty` returns the result of `top == 10`. Like `is_full`, it produces
1 or 0 without changing storage.

`peek` calls `is_empty` before indexing the array. If empty, it returns
`'\0'` immediately. Otherwise, `return stack[top];` returns the top
character. Neither path changes `top`. After the three pushes above,
`peek()` returns `'C'` and leaves `top` at 7.

`pop` uses the same empty check and returns the same sentinel for an empty
Stack. On a nonempty Stack, its three remaining statements have distinct
jobs:

| Statement | Effect when `top == 7` and `stack[7] == 'C'` |
|---|---|
| `char data = stack[top];` | Save `'C'` in a local variable. |
| `top += 1;` | Change `top` to 8, making index 7 inactive. |
| `return data;` | Return the saved `'C'`, even though `top` has changed. |

Reading after increasing `top` would select the next item instead. The
local copy keeps the removed character available until the return. The
old cell still contains `'C'`; logical removal changes the active range
without erasing storage. A later push can overwrite that cell.

Empty `peek` and `pop` leave both the array and `top` unchanged. The
sentinel `'\0'` cannot distinguish empty state from a deliberately stored
null character. The converter stores supported operator characters, so
none of its actual items has that value. These checks assume that `top`
already satisfies `0 <= top <= 10`.

### 5. `prec`: translate an operator into a precedence level

The converter needs a number it can compare before deciding which waiting
operator to remove. `prec(char op)` receives one character and returns
that number without changing the Stack.

The first condition, `op == '+' || op == '-'`, accepts either of the two
level-1 operators. If true, `return 1;` finishes the call immediately.
Otherwise, the `else if` tests for `'*'`, `'/'`, or `'%'` and returns 2
for a match. The final `return 0;` handles every other character.

For the worked expression, `prec('-')` is 1 and `prec('*')` is 2. For an
empty Stack, `peek()` supplies `'\0'` and `prec('\0')` is 0. Every
supported incoming operator therefore has higher precedence than the
empty sentinel. That fact lets the converter's comparison stop at an
empty Stack.

Returning zero for an unsupported character does not reject an invalid
expression. If that character reaches the operator branch, even an empty
peek can satisfy `0 >= 0`, so the loop can continue writing beyond the
output array. The input assumptions stated earlier are required.

### 6. Expression storage: characters, length, and the terminator

The expression needs storage for both its visible characters and its end
marker. `char infix[8] = "1-2*3+4";` creates these eight cells:

| Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|---|---|---|---|---|---|---|---|---|
| `infix` | `'1'` | `'-'` | `'2'` | `'*'` | `'3'` | `'+'` | `'4'` | `'\0'` |

`char postfix[8] = "";` creates an initially empty string. Its first
character is the null terminator, and its remaining cells also start at
zero. `int size = 0;` records that there are no postfix tokens yet. The
eight-cell capacity and the token count have different meanings.

The converter copies digit characters and rearranges operator characters.
It does not calculate `2 * 3` or store the integer answer here. After
conversion, the seven postfix characters are `123*-4+`, followed by the
terminator at index 7. `size` is 7, excluding that terminator.

### 7. `infix_to_postfix`: scan digits and release waiting operators

The converter must build a fresh output from the current input. Its first
statement, `size = 0;`, resets the output count. It does not clear the
whole output array or reset `top`. The caller must start with an empty
operator Stack; normal completion of the previous conversion leaves it
empty.

The `for` loop starts a local `i` at zero. Before each iteration,
`infix[i] != '\0'` asks whether the current character is still part of
the expression. After the body, `i++` advances to the next character.
For the example, the body runs for indexes 0 through 6 and stops at 7.
`char c = infix[i];` copies the current character into a local variable.

The condition `c >= '0' && c <= '9'` recognizes a digit. If true,
`postfix[size++] = c;` writes it at the old output count, then leaves
`size` increased by one. On the first iteration, `'1'` goes into
`postfix[0]` and `size` becomes 1. No operator is pushed for a digit.

For a non-digit, the `else` branch treats `c` as an operator. This relies
on the input containing only the five supported operators. `char op =
peek();` copies the current waiting operator, or the empty sentinel, into
a local variable. Merely peeking does not remove anything.

The `while` condition compares `prec(op)` with `prec(c)`. When the waiting
operator has equal or greater precedence, `postfix[size++] = pop();`
removes it from the Stack and appends the returned character to output.
The next statement, `op = peek();`, refreshes the local copy so that the
next condition examines the newly exposed top. A local variable does not
update itself when the global Stack changes.

When the condition becomes false, `push(c);` saves the incoming operator.
The converter repeats the outer loop for the next input character.
The `>=` includes equal precedence, so a waiting `-` leaves before a new
`+` is saved. For equal-precedence operators, this preserves left-to-right
evaluation.

The arrival of `'+'` at input index 5 shows the inner loop in detail.
The output so far is `123`, `size` is 3, and the waiting operators are
`'-'` at index 9 and `'*'` at index 8, with `top == 8`.

| Step | Comparison or action | Output so far | `size` | `top` |
|---|---|---|---:|---:|
| Read the top | `op = '*'` | `123` | 3 | 8 |
| First loop pass | `2 >= 1`; pop `'*'`, then peek `'-'` | `123*` | 4 | 9 |
| Second loop pass | `1 >= 1`; pop `'-'`, then peek `'\0'` | `123*-` | 5 | 10 |
| Leave the loop | `0 >= 1` is false | `123*-` | 5 | 10 |
| Save the input operator | `push('+')` | `123*-` | 5 | 9 |

These intermediate output strings show characters written so far. They
are not guaranteed to be terminated strings until the converter finishes.
In particular, a repeated conversion may still have old characters beyond
the current count.

After the outer loop copies the last digit `'4'`, the output count is 6.
The final `while (!is_empty())` drains the remaining operators. Here it
pops `'+'` into `postfix[6]`, leaving `size == 7` and `top == 10`. The
loop stops because `is_empty()` now returns 1 and `!1` is 0.

Finally, `postfix[size] = '\0';` writes the terminator without incrementing
`size`. The result is the string `123*-4+`. A later conversion of a shorter
input writes its own earlier terminator, so old trailing characters are
not displayed. The function returns no value; its results are the global
`postfix` array, updated `size`, and empty operator Stack. It assumes the
input and output fit their arrays rather than checking each write.

### 8. `calc`: return one integer operation

Once two integer operands are ready, evaluation needs to apply the stored
operator. `calc(int num1, int num2, int op)` receives copies of the left
operand, right operand, and operator code. When the evaluator passes its
`char c`, the character value is converted to the parameter's `int` type.
The comparisons still use the codes for `'+'`, `'-'`, `'*'`, `'/'`, and
`'%'`.

`switch (op)` selects the matching `case` label. Each label immediately
returns its calculation, so execution leaves the whole function. No
`break` is needed after those returns.

| Selected label | Returned expression | Example |
|---|---|---|
| `case '+'` | `num1 + num2` | `calc(-5, 4, '+')` returns -1. |
| `case '-'` | `num1 - num2` | `calc(1, 6, '-')` returns -5. |
| `case '*'` | `num1 * num2` | `calc(2, 3, '*')` returns 6. |
| `case '/'` | `num1 / num2` | `calc(7, 2, '/')` returns 3. |
| `case '%'` | `num1 % num2` | `calc(7, 2, '%')` returns 1. |

If no label matches, execution reaches `return 0;` after the switch.
There is no `default:` label in the supplied code. That fallback is not
an error report: zero is also a valid arithmetic answer. The function
assumes nonzero divisors and representable integer results, including the
quotient for division and remainder.

### 9. `eval_postfix`: use a local Stack of integers

Evaluation must store calculated numbers rather than operator characters.
`int values[10];` reserves ten local integer cells. Unlike the global
character array, this ordinary local array has no automatic zero
initialization. Valid evaluation writes each active cell before reading
it.

`int pos = 0;` starts the count of available values at zero. Active cells
are `values[0]` through `values[pos - 1]`. The next push writes at `pos`;
the next pop decreases `pos` and reads there. This convention differs
from the downward-growing character Stack. The evaluator never calls
the global `push` or `pop` functions.

The `for` loop starts `i` at zero, checks `i < size`, and advances `i`
after every body. `char c = postfix[i];` reads one output token. The loop
uses the stored count rather than searching for a terminator. With
`size == 7`, it processes indexes 0 through 6 and does not process index 7.

The digit condition is the same as the converter's. This time,
`values[pos++] = c - '0';` converts the digit character into an integer
and pushes that number. For `'3'`, subtraction gives integer 3. The write
uses the old `pos`; the completed statement leaves `pos` one larger.

Otherwise, evaluation expects an operator and at least two active values.
`int num2 = values[--pos];` decreases `pos` first and reads the former top
as the right operand. `int num1 = values[--pos];` decreases it again and
reads the left operand. Each declaration is a separate statement, so the
right-then-left order is explicit.

`values[pos++] = calc(num1, num2, c);` calls `calc`, stores its returned
integer in the next free cell, and leaves the count increased by one.
The two consumed operands are replaced by one result. Popping does not
clear their old cells; only the current active prefix matters.

The three operators in `123*-4+` produce these changes. The count sequence
records the starting count, both pops, and the result push.

| Operator | Active values before | `num2` (right) | `num1` (left) | Calculation | `pos` sequence | Active values after |
|---|---|---:|---:|---|---|---|
| `'*'` | 1, 2, 3 | 3 | 2 | `2 * 3 = 6` | 3 → 2 → 1 → 2 | 1, 6 |
| `'-'` | 1, 6 | 6 | 1 | `1 - 6 = -5` | 2 → 1 → 0 → 1 | -5 |
| `'+'` | -5, 4 | 4 | -5 | `-5 + 4 = -1` | 2 → 1 → 0 → 1 | -1 |

The digit `'4'` is pushed between the subtraction and addition rows.
Negative intermediate results such as -5 fit the integer array without
being converted back to characters.

After the loop, a valid expression leaves `pos == 1`. The statement
`return values[--pos];` changes it to zero, reads `values[0]`, and returns
-1. The returned integer survives the call even though the local array
does not. Evaluation leaves `postfix`, `size`, and the global character
Stack unchanged. A second call starts with a fresh local `pos` and can
evaluate the same stored expression again.

The code does not check for too few operands or verify that exactly one
result remains. Empty or malformed postfix input can read outside the
array. The successful trace depends on the documented expression rules
and arithmetic assumptions.

### 10. The driver: share definitions and display the results

The lab supplies helpers, so a separate source file provides the entry
point that calls them. The opening `/* ... */` text is a comment and has
no runtime effect. `#include <stdio.h>` provides the declaration of
`printf`, the library function used for output.

`extern char infix[8];`, `extern char postfix[8];`, and `extern int size;`
declare names whose storage is defined in `lab.c`. They do not create
separate arrays or reset existing values. Building both source files
together lets the linker connect these references to the definitions.

`void infix_to_postfix(void);` and `int eval_postfix(void);` declare the
functions before the driver calls them. These declarations end with
semicolons and contain no function bodies. The leading type describes the
return value; `(void)` in the parameter list explicitly means no
parameters. The lab's older `()` definitions are called without arguments
here, but do not provide the same prototype information in C11.

`int main(void)` defines the program's entry point. It first calls
`infix_to_postfix();`, so the output exists before any line prints it.
The next three calls display the input string, converted string, and
token count. `%s` prints characters through the point just before a null
terminator; `%d` prints an integer. The `\n` at the end of each format
string moves subsequent output onto a new line.

The final print call passes `eval_postfix()` as its integer argument.
Evaluation completes and supplies -1 before `printf` displays the result
line. `(void)` before each `printf` call explicitly discards the printing
function's own return value; it does not prevent printing or discard the
argument being displayed.

`return 0;` finishes `main` with a successful program status. That zero
is separate from the expression's answer, -1. The four output lines
therefore report `1-2*3+4`, `123*-4+`, 7, and -1 as shown in the C Code
section.

For the repository build, compile the existing `lab.c` and `lab_demo.c`
together with `make lab-demo`. For a single-file reading experiment,
concatenate only the six C blocks from the C Code section, in their
displayed order, and compile that file by itself. The earlier small
storage examples repeat declarations and should not be added again.
Do not also link `lab.c` when the combined file already contains those
definitions.

### 11. Check the state changes

Use the stored values to answer these questions before running the demo.
Each answer follows a specific statement in the code.

1. **After the three character pushes, why does `peek()` return `'C'`?**
   The pushes leave `top == 7` and put `'C'` in `stack[7]`. Peek reads
   that cell without changing the index.
2. **Why can a removed character remain in the array?** Pop saves its
   value, then increases `top`. The active suffix no longer includes the
   old cell; erasing it is unnecessary.
3. **Why does arriving `'+'` release both `'*'` and `'-'`?** Their
   precedence levels, 2 and 1, both satisfy `>= prec('+')`. The refreshed
   empty peek has precedence 0, which ends the loop.
4. **Why are `size` and `pos` different after conversion and evaluation?**
   Global `size` remains the seven-token postfix length. Local `pos`
   counts available integers, reaches one result, and becomes zero as
   the final return reads it. That local variable then ceases to exist.
5. **Why is subtraction `1 - 6`, not `6 - 1`?** Six is popped first into
   `num2`, the right operand. One is popped second into `num1`, the left
   operand. `calc` evaluates `num1 - num2`.
6. **What stops a shorter second output from showing old characters?**
   Conversion resets `size` before writing and places `'\0'` at the new
   end. Cells after that terminator can still hold old values.
