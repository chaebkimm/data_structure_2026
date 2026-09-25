# Chapter 4. Taking Out the Last Value First

We will store items so that only the newest remaining item can be read or
removed, then use that rule to decide when to calculate an expression.

## Thinking Logically

### Why do we need a special order?

A Stack lets us read or remove only the newest remaining item. Adding or
removing that item leaves the other stored items in place. This rule is
called **last in, first out (LIFO)**.

We can implement it with a list: append at the end, read the last item,
and remove the last item. Earlier items never need to shift. In the lab,
an array stores that list and a count marks its current end.

### What does the array look like?

The lab uses this global state:

```c
int stack[10];
int capacity = 10;
int size = 0;
```

The valid array indexes are 0 through 9. `size` is the number of stored
items. Because indexes start at zero, this count is also the position where
the next item will be added. The initial
`size == 0` marks an empty Stack. Push writes at `stack[size]`, then
increases `size`, so the first item goes into `stack[0]`. Later items go
into indexes 1, 2, and so on. The Stack grows toward larger indexes.

With `size == 3`, the active items occupy indexes 0 through 2. The top item
is `stack[size - 1]`, or `stack[2]`, and the number of items is 3. Positions
at or above `size` are inactive. When the Stack is full, `size == capacity`
marks the boundary past the array; `stack[10]` is not a cell we may write.

`capacity` is used by the full check. It must match the ten cells reserved
by `stack[10]`. Changing `capacity` alone does not resize the array.

### How do push, peek, and pop change the state?

Use character labels `'A'`, `'B'`, and `'C'` for three saved tasks. In the
logical lists below, the rightmost item is the top. Arrival order and
increasing array-index order are the same here.

| Request | Returned value | Items, bottom to top | `size` | Active indexes |
|---|---|---|---:|---|
| start | — | empty | 0 | none |
| `push('A')` | none (`void`) | A | 1 | 0 |
| `push('B')` | none (`void`) | A, B | 2 | 0–1 |
| `push('C')` | none (`void`) | A, B, C | 3 | 0–2 |
| `peek()` | `'C'` | A, B, C | 3 | 0–2 |
| `pop()` | `'C'` | A, B | 2 | 0–1 |
| `pop()` | `'B'` | A | 1 | 0 |
| `pop()` | `'A'` | empty | 0 | none |

To pop, first decrease `size`, then read and return `stack[size]`.
The expression `stack[--size]` performs those steps in that order. Pop does not erase the array cell.
Decreasing `size` makes the old top inactive. The next push may overwrite it.

### What happens at the boundaries?

The Stack is full when `size == capacity` and empty when `size == 0`.
`is_full()` and `is_empty()` report these states as 1 or 0. They do not
change the array or the count.

`push`, `peek`, and `pop` do not call these checks. A caller must only push
when `size < capacity` and only peek or pop when `size > 0`. Pushing at
size 10 attempts to write `stack[10]`. Peeking at size 0 attempts to read
`stack[-1]`. Popping at size 0 first changes `size` to -1 and then attempts
to read `stack[-1]`. These out-of-bounds operations have undefined behavior;
they are not rejected operations with an unchanged state or a special return value.

An empty read or removal is called **underflow**. The expression conversion
below avoids it for supported input by first storing a special bottom
marker, `\0` written in C as `'\0'`. This **sentinel** is an actual Stack
item. It is not a value automatically returned by an empty Stack.

### How does this relate to function calls?

When one function pauses to call another, the runtime commonly saves a
**call frame** so it can resume the older call later. Nested calls finish
in LIFO order. The inquiry's numeric function IDs and this chapter's
character labels model that order. Neither is a real call frame, and this
global integer array is not the runtime call stack.

### How can two stacks calculate the original expression?

Read `1-2*3+4` from left to right using two Stacks: one for waiting
operators and one for numbers. Multiplication has higher precedence than
subtraction or addition. When `*` arrives, the waiting `-` must stay in
its Stack until the multiplication is ready.

When a new operator arrives, calculate with waiting operators of equal or
greater precedence first. For each calculation, pop its operator, then
pop the right number before the left number, and push the result. At the
end, finish all waiting operations. Each list below runs bottom to top;
the rightmost item is the newest one.

| Input/action | Waiting operators | Numbers | Reason or calculation |
|---|---|---|---|
| read `1` | empty | 1 | Save the first number. |
| read `-` | `-` | 1 | Save the waiting subtraction. |
| read `2` | `-` | 1, 2 | Save the next number. |
| read `*` | `-`, `*` | 1, 2 | `*` has higher precedence, so `-` waits. |
| read `3` | `-`, `*` | 1, 2, 3 | Both operands of `*` are ready. |
| before saving `+`: pop `*`, 3, 2 | `-` | 1, 6 | Push `2 * 3 = 6`; `*` outranks `+`. |
| still before saving `+`: pop `-`, 6, 1 | empty | -5 | Push `1 - 6 = -5`; `-` and `+` have equal precedence. |
| save the incoming `+` | `+` | -5 | No waiting operator remains. |
| read `4` | `+` | -5, 4 | Save the last number. |
| end: pop `+`, 4, -5 | empty | -1 | Push `-5 + 4 = -1`, the final answer. |

This is a way to calculate the original expression directly. It makes the
waiting and calculation order visible. The lab's C program uses that same
order in two separate phases: first rewrite the expression, then calculate
the rewritten expression.

### Why put operators after their operands?

The numbers above were read in the order `1`, `2`, `3`, `4`. The
calculations happened after `3` (first `*`, then `-`) and after `4` (`+`).
Keep the numbers in place and write each operator when its calculation
can happen:

```text
1 2 3 * - 4 +
```

Now the rewritten expression records when each operation should run.
The spaces make the tokens easy to see; the lab stores `123*-4+`.

An **operand** is a value such as `2`. An **operator** is an action such as
`*`. **Infix** places the operator between its operands: `2*3`.
**Postfix** places it after them: `23*`. Each digit is a separate operand
in this lab; `23*` means multiply 2 and 3, not the number 23.

The program has two distinct phases. Conversion stores waiting operator
character codes in the global integer Stack and writes a string to `eq_re`.
Evaluation resets the same Stack and stores integer operands and results.
The phases run one after the other. Conversion does not calculate the arithmetic.

### How do we evaluate the new order?

For the rewritten expression `123*-4+`, seven characters are expression
tokens. The final `'\0'` marks the end of the string and is not evaluated.
`eval_postfix()` begins with `size = 0;` and uses the global `int stack[10]`
for numeric values. Active indexes are 0 through `size - 1`; the top is
`stack[size - 1]`. No local value array or separate value count is needed.

The same storage has different contents in the two phases:

| Phase | Contents of global `stack` | Meaning of global `size` |
|---|---|---|
| conversion | bottom sentinel and waiting operator character codes | number of active items, including the sentinel |
| evaluation | integer operands and intermediate results | number of active numeric values |

For a digit, `c - '0'` gives the integer value. For an operator, pop two
integers, calculate, and push the result. The first popped value is the
**right** operand, `num2`. The second is the **left** operand, `num1`.
Subtraction, division, and remainder depend on that order.

| Postfix token | Action | Values, bottom to top | `size` |
|---|---|---|---:|
| `1` | push 1 | 1 | 1 |
| `2` | push 2 | 1, 2 | 2 |
| `3` | push 3 | 1, 2, 3 | 3 |
| `*` | `2 * 3` | 1, 6 | 2 |
| `-` | `1 - 6` | -5 | 1 |
| `4` | push 4 | -5, 4 | 2 |
| `+` | `-5 + 4` | -1 | 1 |

The final `return pop();` returns -1 and leaves `size == 0`. Intermediate
values remain integers, so they can be negative or larger than a digit.
No numeric sentinel is pushed during evaluation; zero is a valid number.

`calc` implements `+`, `-`, `*`, `/`, and `%`. Division is C integer
division: `7/2` gives 3. Remainder gives what is left after integer division:
`7%2` gives 1. These operations do not produce floating-point results.

### How do we convert infix to postfix?

The rewritten order can be built without calculating the numbers. Use the
integer Stack to hold waiting operator character codes, then write each
operator when its calculation would be due in the direct two-stack method.

#### Which operator leaves first?

Waiting operators need a priority so we can decide which one to output.
`prec` returns these precedence levels:

| Characters | Precedence |
|---|---:|
| `+`, `-` | 1 |
| `*`, `/`, `%` | 2 |
| other characters, including `'\0'` | 0 |

A digit goes directly to the postfix output. Before pushing an incoming
operator, conversion pops every waiting operator of equal or greater
precedence into that output. The equality case makes operators at the same
level **left associative**: `8-3-2+1` means `((8-3)-2)+1`.

Conversion first resets `size` and pushes `'\0'`. Its precedence is 0,
lower than every supported operator. When no operator remains, `peek()`
reads this stored sentinel and the comparison stops. The Stack still
contains one item at that point. There is no empty peek.

#### How does the example convert?

Start by resetting `size` to 0 and pushing the bottom sentinel. Lists run
bottom to top. The sentinel counts as an item throughout conversion.

| Input/action | Postfix characters so far | Stack, bottom to top | `size` | `pos` |
|---|---|---|---:|---:|
| push sentinel | empty | `'\0'` | 1 | 0 |
| read `1` | `1` | `'\0'` | 1 | 1 |
| read `-` | `1` | `'\0'`, `-` | 2 | 1 |
| read `2` | `12` | `'\0'`, `-` | 2 | 2 |
| read `*` | `12` | `'\0'`, `-`, `*` | 3 | 2 |
| read `3` | `123` | `'\0'`, `-`, `*` | 3 | 3 |
| read `+`: pop `*`, pop `-`, push `+` | `123*-` | `'\0'`, `+` | 2 | 5 |
| read `4` | `123*-4` | `'\0'`, `+` | 2 | 6 |
| end: pop `+` | `123*-4+` | `'\0'` | 1 | 7 |
| end: pop sentinel | `123*-4+` followed by `'\0'` | empty | 0 | 8 |

The input and output arrays each contain eight positions:

```c
char eq[8] = "1-2*3+4";
char eq_re[8] = "";
```

The local `pos` starts at 0 and gives the next output position.
Conversion scans exactly indexes 0 through 6, using `i < 7`. The last drain
pops every remaining item, including the sentinel. That final pop writes
`'\0'` to `eq_re[7]` and increments `pos` to 8. This marker is the string's
**null terminator**. Seven digits/operators are tokens; the terminator is
an eighth stored character, not an expression token.

Each call starts with a fresh `pos`, resets global `size`, and pushes a new
sentinel. A repeated conversion overwrites all eight output cells for a
valid seven-token input. Shorter expressions are not supported by this loop.

### Which inputs may this lab use?

The supplied program assumes exactly seven input characters in this order:

```text
digit operator digit operator digit operator digit
```

Each operand is one digit. Each operator is one of `+`, `-`, `*`, `/`, `%`.
The input occupies `eq[0]` through `eq[6]`, with `'\0'` at `eq[7]`.
Inputs contain no spaces, parentheses, unary operators, or multi-digit
operands. Division and remainder require a nonzero right operand, and
arithmetic results must be representable as `int`. Evaluate only after
converting such an input. Each phase resets the global Stack itself.

These are caller assumptions, not checks implemented by `lab.c`:

- The loop processes seven positions even if a shorter input contains an
  earlier `'\0'`. An unsupported character has precedence 0, so conversion
  can pop the sentinel and then peek below `stack[0]`.
- Missing operands can make evaluation pop below `stack[0]`. Extra operands
  are not rejected either. The evaluator does not verify its final count.
- Full pushes, empty reads, division or remainder by zero, and integer
  overflow are not guarded. The functions have no error-status interface.

Do not interpret the fallback 0 from `calc` as safe validation: operand
reads have already happened. Character/grammar checks, operand-count
checks, buffer bounds, and arithmetic error reporting are extension
exercises. They are not present in the supplied code.

### What must each operation preserve?

For the global integer Stack in a valid completed state, `capacity` is
10 and the following rules hold:

```text
0 <= size <= capacity
active indexes: 0 through size - 1 (none when size == 0)
number of active items: size
read stack[size - 1] only when size > 0
write a new item at stack[size] only when size < capacity
```

The caller must satisfy the boundaries before an unchecked operation.
Push uses `stack[size++]`: it indexes with the old count and increases the
count. Pop uses `stack[--size]`: it decreases the count before indexing.
Peek reads `stack[size - 1]` without changing `size`. No operation shifts
old items or erases inactive cells.

Conversion writes at indexes 0 through 7, with `pos` reaching 8 after the
terminator is stored. The sentinel stays at the bottom until the final
drain. During evaluation, `size` counts available operands/results; an
operator needs two values and the complete expression leaves exactly one
before the final pop. The current evaluator relies on those facts rather
than checking them.

## Calculating Efficiency

### How much work does one Stack operation do?

Push writes one cell and changes one count. Peek reads one cell. Pop
changes one count and reads one cell. The predicates each compare one
count. None shifts existing elements, so each operation takes `O(1)` time.

### Why are the two expression phases linear?

Conversion of `1-2*3+4` scans seven tokens, pushes three operators and one
sentinel, and pops those four items. Although one incoming operator can
trigger several pops, no waiting operator is popped twice. In a version
extended to `n` input characters, the scan and total Stack work take `O(n)`
time. The current loops always process exactly seven tokens.

Evaluation reads the seven postfix tokens once. Four digits add four
integers. Each of the three operators removes two integers and adds one
result. The last pop returns that result. With fixed work per token,
generalized evaluation also takes `O(n)` time.

### How much storage is reserved?

The program declares one global array of ten integers and two arrays of
eight characters. Conversion and evaluation reuse the same integer array.
Only a few local counters and temporary values are added; there is no local
numeric array. Their fixed lengths make this `O(1)` storage. The current
input length is exactly seven characters. In a generalized version whose
buffers grow with input, postfix output alone needs `O(n)` space; Stack
space can also grow with the supported expression grammar.

## Glossary

The names below refer to ideas already used in the worked example. The
Stage B vocabulary reference supplies the wider course vocabulary.

| Term | Meaning in this chapter |
|---|---|
| Stack; LIFO | An access rule that removes the newest remaining item first |
| top | The accessible end; its array index is `size - 1` when nonempty |
| push, peek, pop | Add, inspect, or remove the top item |
| active prefix | Array indexes 0 through `size - 1`; empty when `size == 0` |
| underflow | A request to read/remove an item when the Stack is empty |
| sentinel | A stored bottom marker; here `'\0'` stops precedence pops and later terminates the output |
| invariant | A rule preserved by valid operations, such as `0 <= size <= capacity` |
| infix; postfix | Operators between operands; operators after operands |
| operand; operator | A value; an operation applied to values |
| precedence | The ordering priority of operators |
| left associativity | Processing equal-precedence operators left to right |
| null terminator | The `'\0'` at the end of a C string, outside its token count |
| call frame | Runtime information needed to resume a function call |
| precondition | An assumption the caller must satisfy before a function runs |
| integer overflow | A result outside the representable range of `int` |

## Coding Plan

The implementation follows the same example in two phases. Reuse the
global integer Stack after resetting its count between phases.

1. **Prepare integer storage.** Start global `size` at 0. Push with
   `stack[size++]`, peek at `stack[size - 1]`, and pop with `stack[--size]`.
   Define full as `size == capacity` and empty as `size == 0`. These
   predicates report state; the operations do not call them automatically.
2. **Set precedence and strings.** Use level 1 for `+`/`-`, level 2 for
   `*`/`/`/`%`. Reserve seven tokens and one terminator in `eq` and `eq_re`.
3. **Convert to postfix.** Start local `pos` at 0, reset `size`, and push
   `'\0'`. Scan exactly seven characters. Copy digits and emit waiting
   operators according to precedence. Drain the Stack, including the
   sentinel that terminates the output.
4. **Define integer calculations.** Calculate `num1 op num2` for each
   supported operator. The caller must satisfy the arithmetic assumptions.
5. **Evaluate postfix.** Reset `size` to zero. Read exactly seven tokens,
   convert digits to numbers, and use the same `push` and `pop`. Pop right
   before left for each operator. Push each result and return the final pop.
6. **Run and collect evidence.** Use the driver, then test LIFO, the
   boundary predicates, precedence, operand order, and repeated conversion
   of valid seven-character inputs. Do not call the unchecked operations
   outside their preconditions.

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

`char eq[8] = "1-2*3+4";` reserves eight character positions for seven
expression characters and the terminator. `char eq_re[8] = "";`
initializes all eight positions to zero. The condition `i < 7` processes
exactly seven input positions. Conversion pops the stored sentinel into
`eq_re[7]` to terminate the output.

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

The final drain must continue while the Stack has an item, including its sentinel.
`!is_empty()` uses logical NOT: `!` produces 1 when its operand is zero and
0 otherwise. `is_empty()` returns 1 for an empty Stack, so the negated
condition is false at that boundary. Comparisons such as `size == 0`
also produce integer 1 for true and 0 for false.

### Updating an index or count

Push and pop move the boundary by one position. Postfix increment uses the
old value, then increases the stored count. Prefix decrement decreases the
stored count before using its value.

An append needs the old free position. In `stack[size++] = data;`, size 3
selects `stack[3]` and the completed statement leaves `size` equal to 4.
In `eq_re[pos++] = c;`, position 3 selects `eq_re[3]` and leaves `pos`
equal to 4. This local output position is separate from global Stack size.

Removal needs the last occupied position. In `return stack[--size];`,
size 3 becomes 2 before indexing. The function reads `stack[2]` and
returns the old top. The evaluator calls `pop()` in separate statements
for the two operands, so the right operand is removed before the left.

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
`student/lab.c`. `extern char eq[8];` declares the existing array's name
and type so the driver can use it. This declaration does not create a
second array. The same rule applies to `eq_re`. Both source
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

In `(void)printf("postfix: %s\n", eq_re);`, `(void)` is a cast that explicitly
discards `printf`'s return value. The call still runs and prints the postfix
string.
It differs from `(void)` in a function's parameter list. The argument
`eval_postfix()` in the final display call is evaluated to obtain the
integer that `%d` will print. `return 0;` then ends `main` and reports
successful completion.

## C Code

The blocks below reproduce the current lab functions in source order. They
are one program split for reading, not independent programs. `lab.c` has
no `main`; the last block is its separate demonstration driver.

Before reading, distinguish `'3'` (a character), `3` (an integer), and
`"3"` (a character string with a terminator). `c - '0'` converts a checked
digit to its integer value. `stack[size++]` uses the old insertion index;
`stack[--size]` decreases the count first to select the old top.

### Integer Stack operations

The caller must satisfy the array boundaries. The full and empty predicates
only report state; push, peek, and pop do not call them.

```c
int stack[10];
int capacity = 10;
int size = 0;

void push(int data) {stack[size++] = data;}

int peek() {return stack[size - 1];}
int pop() {return stack[--size];}

int is_full() {return size == capacity;}
int is_empty() {return size == 0;}
```

### Precedence and expression storage

Waiting operators need a priority, and the two expression strings each need
room for seven tokens plus a terminator.

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

char eq[8] = "1-2*3+4";
char eq_re[8] = "";
```

### Infix-to-postfix conversion

Conversion starts with a fresh output position and a stored bottom sentinel.
The sentinel stops precedence pops for supported operators and becomes the
output terminator during the final drain.

```c
void infix_to_postfix() {
    int pos = 0;
    size = 0;
    push('\0');
    for (int i = 0; i < 7; i++) {
        char c = eq[i];

        if (c >= '0' && c <= '9') {
            eq_re[pos++] = c;
        }
        else {
            char op = peek();
            while (prec(op) >= prec(c)) {
                eq_re[pos++] = pop();
                op = peek();
            }
            push(c);
        }
    }
    while (!is_empty()) {
        eq_re[pos++] = pop();
    }
}
```

### Integer operations

Each operation uses the left operand first and the right operand second.
The caller must satisfy the arithmetic preconditions.

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

The evaluator resets the same global Stack and reuses it for integers.
Every operator removes the right operand before the left operand.

```c
int eval_postfix() {
    size = 0;

    for (int i = 0; i < 7; i++) {
        char c = eq_re[i];
        if (c >= '0' && c <= '9') {
            push(c - '0');
        }
        else {
            int num2 = pop();
            int num1 = pop();
            push(calc(num1, num2, c));
        }
    }

    return pop();
}
```

### A separate entry point

The companion `code/lab_demo.c` supplies `main`. Compile it together with
`student/lab.c`; do not paste another copy of the lab definitions into it.

```c
/* Entry point for the instructional functions in ../student/lab.c. */
#include <stdio.h>

extern char eq[8];
extern char eq_re[8];

void infix_to_postfix(void);
int eval_postfix(void);

int main(void)
{
    infix_to_postfix();
    (void)printf("infix: %s\n", eq);
    (void)printf("postfix: %s\n", eq_re);
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
result: -1
```

For new C declarations, write `(void)` when a function takes no parameters.
The supplied lab still spells those definitions with `()`; Clang in C11 mode
with the supplied warning flags emits six missing-prototype warnings and four
integer-to-character conversion warnings in conversion. Record the actual diagnostics.

Before running, explain why conversion finishes with `size == 0`, why its
local `pos` reaches 8 for seven tokens, and why subtraction receives 1 as
its left operand and 6 as its right operand. Then trace another valid
seven-character input such as `8-3-2+1`, whose postfix form is `83-2-1+`
and whose result is 4. Repeat conversion and evaluation to check the resets.

The older `int_stack_*` and `expression_evaluate` sources under `code/`
use a different checked interface. They remain an optional comparison;
they are not the implementation described by this chapter or the core lab.

## Full C Code Explanation

This reference follows the six blocks in the C Code section. It explains
every declaration and function, then connects the statements to the worked
expression `1-2*3+4`. Keep track of what each function returns and what it
changes in shared storage. Those are separate ways to produce a result.

### 1. Reading declarations, function calls, and shared state

First identify storage that survives between calls. A declaration such as
`int size = 0;` introduces a variable, gives its type, and sets its initial
value. An assignment such as `size = 0;` changes an existing variable.
Semicolons end statements; braces group a function, condition, or loop.

The definitions outside functions create global storage. `stack`,
`capacity`, `size`, `eq`, and `eq_re` last for the program's execution.
Their initializers run when that storage is prepared, not whenever a
helper is called. Both expression phases use the same `stack` and `size`.

The return type tells us what a call supplies. `push` and
`infix_to_postfix` return `void`; their results are changes to shared
storage. `peek`, `pop`, and all other lab functions return `int`.
`return stack[--size];` changes the count, reads a cell, and returns its
integer value. A stored character code is also an integer value.

Parameters and ordinary local variables belong to one call. In
`push(int data)`, `data` receives a copy of the argument. Conversion's
local `pos` tracks its output position. Its `i` and `c` are separate
from the evaluator's variables with those names.

Defining a function does not execute its body. The driver starts in `main`,
calls conversion, prints the strings, and calls evaluation for the last
printed value. The lab functions themselves do not print anything.

### 2. Integer storage: why an empty Stack starts at zero

The first declarations reserve space and describe which cells are active.
`int stack[10];` reserves ten integer cells at indexes 0 through 9. A
global array with no explicit initializer starts with zero in every cell.
Those contents do not determine whether the Stack is empty; `size` does.

`int capacity = 10;` records the capacity used by `is_full`. It is a
separate integer, not a command to resize the array. Keep it equal to the
number of cells reserved by `stack[10]`.

`int size = 0;` records no stored items. The first insertion uses index 0.
With three items, the active cells are 0, 1, and 2, and the top index is
`size - 1`. When size is 10, the caller must not push: the next insertion
index would be `stack[10]`. The helper itself does not prevent this write.
Character constants such as `'A'` and `'+'` can be stored as integer codes;
computed values such as -5 use the same cells during evaluation.

### 3. `is_full` and `push`: report the boundary and add an item

A caller can test whether another item fits. `is_full` returns the result
of `size == capacity`: 1 for equal and 0 otherwise. It changes no storage.
It does not reject a later push or validate an already invalid count.

`push(int data)` contains only `stack[size++] = data;`. The postfix
increment supplies the old count as the index. The completed statement
leaves `size` one greater and a copy of `data` in that cell. The return
type is `void`, so no success flag is returned.

| Call | `size` before | Cell written | `size` after |
|---|---:|---|---:|
| `push('A')` | 0 | `stack[0] = 'A'` | 1 |
| `push('B')` | 1 | `stack[1] = 'B'` | 2 |
| `push('C')` | 2 | `stack[2] = 'C'` | 3 |

Reaching the closing brace returns control to the caller. The parameter
belongs to the finished call, but the copied integer remains in the global
array. Earlier items do not move. A push requires `0 <= size < capacity`;
the function does not call `is_full` before writing.

### 4. `is_empty`, `peek`, and `pop`: locate the last occupied cell

Reading or removing an item requires a nonempty Stack. `is_empty` returns
the result of `size == 0` without changing anything. Neither `peek` nor
`pop` calls this predicate automatically.

`peek` directly returns `stack[size - 1]`. After three pushes, it reads
`stack[2]` and returns `'C'` as an integer code, leaving `size` equal to 3.

`pop` directly returns `stack[--size]`. Prefix decrement changes the count
before it is used as the array index:

| Step | Effect when `size == 3` and `stack[2] == 'C'` |
|---|---|
| `--size` | Change `size` to 2. |
| `stack[2]` | Read the old top from index 2. |
| `return` | Supply that integer value to the caller. |

The old top cell still contains `'C'`, but it lies outside the active
prefix. A later push can overwrite it. With `size == 0`, peek would read
index -1 and pop would first decrement size to -1, then read that index.
No empty sentinel is returned automatically. Conversion must push its
own sentinel before using peek.

### 5. `prec`: translate an operator into a precedence level

Conversion needs numeric priorities to decide which waiting operator to
release. `prec(char op)` accepts one character and returns its priority
without changing the Stack.

The first condition checks `op == '+' || op == '-'` and returns 1 when
true. The `else if` checks `'*'`, `'/'`, and `'%'` and returns 2 when one
matches. The final `return 0;` handles all other characters.

In the example, `prec('-')` is 1 and `prec('*')` is 2. The stored bottom
sentinel has `prec('\0') == 0`. After all waiting operators are popped,
peek reads that remaining item. Its lower priority ends the comparison.

Returning 0 for an unsupported character does not reject it. Such an input
could make `0 >= 0` true at the sentinel, pop that sentinel, and then peek
at index -1. Use only the specified seven-character input grammar.

### 6. Expression storage: characters, length, and the terminator

The expression needs room for both its visible characters and its end
marker. `char eq[8] = "1-2*3+4";` creates these eight cells:

| Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|---|---|---|---|---|---|---|---|---|
| `eq` | `'1'` | `'-'` | `'2'` | `'*'` | `'3'` | `'+'` | `'4'` | `'\0'` |

`char eq_re[8] = "";` creates an initially empty string. All eight cells
start at zero. There is no separate global output-length variable.
Conversion keeps its next output index in local `pos`.

Conversion copies digits and changes the order of operators. It does not
calculate `2 * 3`. At the end, `eq_re[0]` through `eq_re[6]` contain
`123*-4+`. The sentinel popped into `eq_re[7]` terminates the string.
The local `pos` reaches 8 because it counts that final stored character too.

### 7. `infix_to_postfix`: scan digits and release waiting operators

Conversion must build a fresh output from the current input. `int pos = 0;`
creates its local output position. `size = 0;` discards any active global
Stack items. `push('\0');` stores the bottom sentinel and makes `size` 1.
The function does not need the caller to empty the Stack first.

The `for` loop starts `i` at 0, tests `i < 7`, and increments `i` after
each body. It reads exactly `eq[0]` through `eq[6]`. It does not search for
the input terminator. `char c = eq[i];` copies the current character.

If `c >= '0' && c <= '9'`, `eq_re[pos++] = c;` writes the digit at the
old output position and increases `pos`. The first digit goes to
`eq_re[0]` and leaves `pos == 1`. The Stack does not change for a digit.

Otherwise, input assumptions make `c` a supported operator. `char op =
peek();` copies the waiting top or the stored sentinel. If
`prec(op) >= prec(c)`, `eq_re[pos++] = pop();` appends that operator.
`op = peek();` refreshes the local copy before the next comparison. A
change to global Stack storage does not update a local copy automatically.

When the comparison becomes false, `push(c);` saves the incoming operator.
The `>=` comparison includes equal priorities, so an earlier `-` leaves
before the new `+` is pushed. This preserves left-to-right order for
operators of equal precedence.

Just before input index 5, output is `123`, `pos` is 3, and the Stack
holds the sentinel at index 0, `'-'` at index 1, and `'*'` at index 2.
The count is 3, including the sentinel.

| Step | Comparison or action | Output so far | `pos` | global `size` |
|---|---|---|---:|---:|
| read top | `op = '*'` | `123` | 3 | 3 |
| first iteration | `2 >= 1`; pop `'*'`, peek `'-'` | `123*` | 4 | 2 |
| second iteration | `1 >= 1`; pop `'-'`, peek `'\0'` | `123*-` | 5 | 1 |
| leave loop | `0 >= 1` is false | `123*-` | 5 | 1 |
| save input operator | `push('+')` | `123*-` | 5 | 2 |

The table shows only characters written so far. Intermediate output is not
guaranteed to be a terminated string, especially during repeated conversion.

After the last digit `'4'`, `pos` is 6. The final `while (!is_empty())`
pops `'+'` into `eq_re[6]`, leaving `size == 1` and `pos == 7`. It runs
again because the sentinel remains. That pop writes `'\0'` to `eq_re[7]`,
leaving `size == 0` and `pos == 8`. Now `is_empty()` returns 1 and `!1`
is 0, ending the drain.

There is no separate terminator assignment after the loop. Writing at
`eq_re[pos]` now would use index 8, outside the array. The function returns
no value; the completed string remains in global `eq_re`. Its local `pos`
ends with the call. Every valid repeated conversion writes all eight cells.
Shorter input is unsupported because the input loop still reads seven positions.

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

### 9. `eval_postfix`: reuse the global Stack for integers

Evaluation needs integers for operands and results. The global array already
has type `int`, so `size = 0;` makes the same storage ready for this phase.
No sentinel is pushed. Only the active prefix matters; every numeric cell
is written before a valid evaluation reads it.

The loop starts `i` at 0, checks `i < 7`, and advances after every body.
`char c = eq_re[i];` reads one output token. The loop processes exactly
indexes 0 through 6 and does not evaluate the terminator at index 7.

For a digit, `push(c - '0');` converts the character into an integer and
stores it in the next Stack cell. `'3' - '0'` gives integer 3.

An operator assumes at least two active values. `int num2 = pop();`
removes the top as the right operand. `int num1 = pop();` removes the next
value as the left operand. These separate statements fix their order.
`push(calc(num1, num2, c));` computes a result and stores it in the same
Stack. Two operands have become one result.

The three operators in `123*-4+` cause these changes:

| Operator | Active values before | `num2` (right) | `num1` (left) | Calculation | `size` sequence | Active values after |
|---|---|---:|---:|---|---|---|
| `'*'` | 1, 2, 3 | 3 | 2 | `2 * 3 = 6` | 3 → 2 → 1 → 2 | 1, 6 |
| `'-'` | 1, 6 | 6 | 1 | `1 - 6 = -5` | 2 → 1 → 0 → 1 | -5 |
| `'+'` | -5, 4 | 4 | -5 | `-5 + 4 = -1` | 2 → 1 → 0 → 1 | -1 |

Between subtraction and addition, digit `'4'` becomes integer 4 and is
pushed. Negative intermediate results such as -5 remain integers.

A valid expression leaves `size == 1` after the loop. `return pop();`
reduces size to 0, reads `stack[0]`, and returns -1. The global array remains,
but all its cells are now inactive. `eq` and `eq_re` are unchanged.
Another call resets size again and can evaluate the same stored output.

The code does not check for missing operands or verify that exactly one
result remains. The seven-token grammar and arithmetic assumptions must
hold before this function is called.

### 10. The driver: share definitions and display the results

The lab supplies helper functions; another source file supplies the program
entry point that calls them. The initial `/* ... */` is a comment and has
no execution effect. `#include <stdio.h>` declares the output function
`printf`.

`extern char eq[8];` and `extern char eq_re[8];` declare names whose
storage is defined in `lab.c`. They do not create or initialize new arrays.
When both files are built together, the linker connects these references
to their definitions.

`void infix_to_postfix(void);` and `int eval_postfix(void);` declare the
functions before use. A semicolon ends each declaration; there is no body.
The leading type describes the returned value. `(void)` explicitly says
there are no parameters. The lab's older `()` definitions are also called
without arguments here, but in C11 they do not provide the same prototype
information.

`int main(void)` defines the entry point. Its first call performs conversion.
The next two calls print the input and output strings. `%s` prints until
the null terminator, excluding it. The final call obtains the integer from
`eval_postfix()` and prints it with `%d`. Each `\n` starts a new output line.

The `(void)` before each `printf` explicitly discards that function's return
value. It does not stop the call or discard the printed argument.
`return 0;` ends `main` with a success status, separate from the expression
result -1. The three lines display `1-2*3+4`, `123*-4+`, and -1.

In the repository, `make lab-demo` compiles `lab.c` with `lab_demo.c`.
For a single-file reading exercise, join only the six C blocks in the
C Code section in their displayed order. Compile that file alone. Do not
add the earlier small storage examples, which would duplicate definitions,
or also link `lab.c` when its definitions are already in the joined file.

### 11. Check the state changes

Before running the demo, answer these questions from the stored values.
Each answer follows from a particular statement.

1. **Why does `peek()` return `'C'` after three pushes?**
   The count is 3 and `stack[2]` contains `'C'`. Peek reads
   `stack[size - 1]` without changing the count.
2. **Why may a popped value remain in the array?**
   Pop first decreases `size`, then reads the old top at that index.
   The cell is outside the active prefix, so it need not be erased.
3. **Why does the incoming `'+'` release both `'*'` and `'-'`?**
   Their priorities 2 and 1 both satisfy `>= prec('+')`. The remaining
   stored sentinel has priority 0 and stops the comparison.
4. **Why does conversion end with `pos == 8` and `size == 0`?**
   Seven token characters and one terminator were written. The last drain
   removed all operators and the sentinel. During evaluation, the same
   `size` counts integers and the final result pop leaves it 0 again.
5. **Why is the subtraction `1 - 6` rather than `6 - 1`?**
   The first pop places 6 in right operand `num2`. The second places 1 in
   left operand `num1`. `calc` computes `num1 - num2`.
6. **Why can another seven-character input replace the previous output?**
   Conversion starts a fresh local `pos`, resets `size`, and pushes a new
   sentinel. All eight output cells are written. A shorter input does not
   satisfy the loop's fixed-length precondition.
