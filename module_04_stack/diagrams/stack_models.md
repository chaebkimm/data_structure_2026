# Module 4 Stack Models

These models accompany the current `student/lab.c`. Each diagram has a text
equivalent. Logical states are bottom to top; physical arrays show explicit
indexes. These Stage D models do not include the later autopsy fixture or
its answer.

## 1. One accessible end

```text
logical order:  bottom [ A ][ B ][ C ] top
                                     ^
                               push, peek, pop
```

Text equivalent: A was pushed before B, then C. Peek reports C without
removing it. Pop reports C and exposes B. A later push D makes D the top.
This is last in, first out, regardless of how the cells are arranged.

## 2. Canonical character trace

```text
request       returned code         logical Stack     top    count
start         none                  empty             -1      0
push('A')     none                  A                   0      1
push('B')     none                  A, B                1      2
push('C')     none                  A, B, C             2      3
peek()        C                     A, B, C             2      3
pop()         C                     A, B                1      2
pop()         B                     A                   0      1
pop()         A                     empty             -1      0
```

Text equivalent: pushes increase `top` before writing; pops read before
decreasing it. The count equals `top + 1`. Push has return type `void`;
peek and pop return integers, shown here as character labels.

## 3. Physical cells and the active prefix

```text
index:       0    1    2    3    4    5    6    7    8    9
stack:     [ A ][ B ][ C ][ . ][ . ][ . ][ . ][ . ][ . ][ . ]
            <--- active --> <----------- inactive ---------->
             ^         ^    ^
           bottom    top=2  top+1=3 (next insertion)

active indexes: 0 through 2
count: top + 1 = 3
next push increases top to 3, then writes index 3
```

Text equivalent: dots mean inactive positions, not required stored values.
The most recent character C is at `stack[2]`; bottom A is at index 0. Logical
bottom-to-top order follows increasing physical indexes. The top read is
`stack[top]`.

## 4. Empty, full, and the invariant

```text
valid caller-maintained state: -1 <= top < capacity  (capacity = 10)
empty:    top == -1, no top; is_empty() is true; do not peek or pop
nonempty: top == 2, top at stack[2], count 3
full:     top == 9, count 10; is_full() is true; do not push
```

Text equivalent: `is_full()` checks `top + 1 == capacity`. The predicates
report boundaries but do not guard operations. A full push accesses index
10; empty peek/pop access index -1. These invalid calls have undefined
behavior and no promised return or final state. `capacity` affects
`is_full()` only; it cannot resize the ten-cell array.

## 5. Peek and pop

```text
before: top = 2; stack[0] = 'A', stack[1] = 'B', stack[2] = 'C'
peek:   read stack[top], index 2 -> integer code for 'C'; top stays 2
pop:    read stack[top], index 2 -> integer code for 'C'; then top becomes 1
        stack[2] can still contain 'C', but that cell is now inactive
```

Text equivalent: for a nonempty Stack, both operations report the current
top. Only pop changes membership. Neither operation erases or shifts stored
values. Callers must establish the nonempty precondition.

## 6. Two phases reuse one Stack

The PPT first calculates with conceptual operator and value Stacks. When
`+` arrives in `1-2*3+4`, waiting `*` and then `-` produce 6 and -5; the final
addition with 4 gives -1. Recording this order produces `123*-4+`.

```text
eq: 1-2*3+4 -- convert_to_postfix --> postfix: 123*-4+ -- eval_postfix --> -1
                     |                                      |
               int stack[10]                          same int stack[10]
               operator codes                         numeric values
               reset top = -1                         reset top = -1
               local cursor pos = 0                   result returned by pop

postfix[7] = '\0' is written explicitly after draining; pos ends 8
```

Text equivalent: conversion starts empty and writes postfix characters with
local cursor `pos`. Its operator loop checks nonempty before peeking. A
lower-precedence waiting operator triggers `break`; otherwise it is popped
to output. After the final drain, a separate assignment writes the null
terminator. Evaluation resets the top index and reuses the array for operands
and intermediate results. No bottom sentinel is stored.

## 7. Converting `1-2*3+4`

```text
read/work        visible postfix     Stack, bottom to top     top  pos
reset to empty   empty               empty                     -1    0
1                1                   empty                     -1    1
-                1                   -                          0    1
2                12                  -                          0    2
*                12                  -, *                       1    2
3                123                 -, *                       1    3
+                123*-               +                          0    5
4                123*-4              +                          0    6
drain +          123*-4+             empty                     -1    7
write terminator 123*-4+ terminated  empty                     -1    8
```

Text equivalent: digits go directly to output. At incoming `*`, the waiting
`-` has lower precedence, so the operator loop breaks before `*` is pushed.
Incoming `+` pops `*` and `-`, then the empty check stops the loop before
`+` is pushed. After the final drain, `postfix[pos++] = '\0'` writes at index
7. The Stack holds at most two operators, with maximum `top == 1`.

## 8. Keeping `1+(2+3)` grouped

The inner addition must be recorded before the outer addition. The dedicated
`infix_to_postfix_parentheses()` function reads `eq_paren` and uses `(` as a
boundary between waiting operators.

```text
read/work        visible postfix     Stack, bottom to top     top  pos
reset to empty   empty               empty                     -1    0
1                1                   empty                     -1    1
outer +          1                   +                          0    1
(                1                   +, (                       1    1
2                12                  +, (                       1    2
inner +          12                  +, (, +                    2    2
3                123                 +, (, +                    2    3
)                123+                +                          0    4
drain outer +    123++               empty                     -1    5
write terminator 123++ terminated    empty                     -1    6
```

Text equivalent: an opening `(` is pushed. At `)`, the loop checks nonempty,
pops the inner `+`, and emits it. It then pops `(` and breaks without writing
it. The final drain emits outer `+`; the separate terminator assignment
writes `postfix[5] = '\0'` and advances `pos` from 5 to 6. The maximum
Stack count is three, with `top == 2`. Balanced groups are assumed; an
unmatched close can be silently consumed and an unmatched open can be emitted.

## 9. Evaluating the postfix output

```text
token        integer stack, bottom to top     top    calculation
1            1                                0     digit -> integer
2            1, 2                             1     digit -> integer
3            1, 2, 3                          2     digit -> integer
*            1, 6                             1     2 * 3 = 6
-            -5                               0     1 - 6 = -5
4            -5, 4                            1     digit -> integer
+            -1                               0     -5 + 4 = -1
final pop    empty                           -1     return -1
```

Text equivalent: evaluation resets global `top = -1`, converts digit
characters using `c - '0'`, and reuses `int stack[10]`. Each operator pops
right operand `num2` before left operand `num1`. `pop()` reads before
decrementing `top`. The scan stops before the terminator, and the final pop
empties the Stack. For `123++`, the same evaluator computes `2+3 = 5`, then
`1+5 = 6` and returns 6 with `top == -1`.

## 10. Current input boundary

```text
eq[8]:       up to 7 plain infix characters + '\0'
eq_paren[8]: up to 7 infix characters, including balanced parentheses + '\0'
postfix[8]:  output tokens + '\0', within 8 cells
operators:   + -        precedence 1
             * / %      precedence 2
opening (:              precedence 0
terminator:  '\0'       explicitly written after draining
```

Text equivalent: each input is a nonempty valid expression with single-digit
operands and binary operators. Shorter valid expressions such as `7` and
`1+2` work because all scans stop at `'\0'`. Use the dedicated converter for
balanced parentheses. Exclude spaces, unary signs, multi-digit operands,
zero divisors, and arithmetic outside C `int`. These conditions are
assumptions, not checked rejections.

## 11. Three related meanings

```text
Stack ADT          LIFO behavior through push, peek, pop
explicit storage   int stack[10] and its top index top; count is top + 1
runtime call stack bookkeeping for actual active function calls
```

Text equivalent: a character label does not create a C call frame. The name
`stack` does not enforce LIFO; the operation bodies do. Later modules may use
a different item type or index direction while retaining the same behavior.
