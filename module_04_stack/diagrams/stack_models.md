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
request       returned code         logical Stack    size    count
start         none                  empty              0      0
push('A')     none                  A                  1      1
push('B')     none                  A, B               2      2
push('C')     none                  A, B, C            3      3
peek()        C                     A, B, C            3      3
pop()         C                     A, B               2      2
pop()         B                     A                  1      1
pop()         A                     empty              0      0
```

Text equivalent: pushes increase `size`; pops decrease it. The count equals
`size`. Push has return type `void`; peek and pop return integers, shown here as character labels.

## 3. Physical cells and the active prefix

```text
index:       0    1    2    3    4    5    6    7    8    9
stack:     [ A ][ B ][ C ][ . ][ . ][ . ][ . ][ . ][ . ][ . ]
            <--- active --> <----------- inactive ---------->
             ^         ^    ^
           bottom     top  size = 3 (next insertion)

active indexes: 0 through 2
count: size = 3
next push writes index 3, then increases size to 4
```

Text equivalent: dots mean inactive positions, not required stored values.
The most recent character C is at `stack[2]`; bottom A is at index 0. Logical
bottom-to-top order follows increasing physical indexes. The top read is
`stack[size - 1]`.

## 4. Empty, full, and the invariant

```text
valid caller-maintained state: 0 <= size <= capacity  (capacity = 10)
empty:    size == 0, no top; is_empty() is true; do not peek or pop
nonempty: size == 3, top at stack[2]
full:     size == 10; is_full() is true; do not push
```

Text equivalent: the predicates report boundaries but do not guard the
operations. A full push accesses index 10; empty peek/pop access index -1.
These invalid calls have undefined behavior and no promised return or final
state. `capacity` affects `is_full()` only; it cannot resize the ten-cell array.

## 5. Peek and pop

```text
before: size = 3; stack[0] = 'A', stack[1] = 'B', stack[2] = 'C'
peek:   read stack[size - 1], index 2 -> integer code for 'C'; size stays 3
pop:    --size makes size 2; read stack[2] -> integer code for 'C'
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
eq: 1-2*3+4  -- conversion -->  eq_re: 123*-4+  -- evaluation -->  -1
                    |                                 |
             int stack[10]                     same int stack[10]
             operator codes + sentinel         numeric values
             reset global size                 reset global size
             local cursor pos starts 0         no sentinel

eq_re[7] = '\0'; conversion pos ends 8; visible token length is 7
```

Text equivalent: conversion writes postfix characters using a local cursor
`pos`. Its Stack holds operator codes above a real bottom sentinel. Evaluation
resets the same global count and reuses the same integer array for operands
and intermediate results. No separate value array or global output count exists.

## 7. Converting `1-2*3+4`

```text
read/work       visible postfix     Stack, bottom to top    size  pos
push sentinel   empty               '\0'                       1    0
1               1                   '\0'                       1    1
-               1                   '\0', -                    2    1
2               12                  '\0', -                    2    2
*               12                  '\0', -, *                 3    2
3               123                 '\0', -, *                 3    3
+               123*-               '\0', +                    2    5
4               123*-4              '\0', +                    2    6
drain +         123*-4+             '\0'                       1    7
drain sentinel  123*-4+ terminated  empty                      0    8
```

Text equivalent: digits go directly to output. Incoming `+` pops `*` and `-`
because their precedence is greater or equal, then stops at the precedence-0
sentinel. The final drain writes `+`, then writes the sentinel to `eq_re[7]`.
That last write increments `pos` to 8. Each conversion resets `size` and `pos`.

## 8. Evaluating `123*-4+`

```text
token        integer stack, bottom to top    size    calculation
1            1                               1      digit -> integer
2            1, 2                            2      digit -> integer
3            1, 2, 3                         3      digit -> integer
*            1, 6                            2      2 * 3 = 6
-            -5                              1      1 - 6 = -5
4            -5, 4                           2      digit -> integer
+            -1                              1      -5 + 4 = -1
final pop    empty                           0      return -1
```

Text equivalent: evaluation resets global `size`, converts digit characters
using `c - '0'`, and reuses `int stack[10]`. Each operator pops right operand
`num2` before left operand `num1`. `pop()` decrements `size` before reading.
The seven-token loop excludes the terminator; the final pop empties the Stack.

## 9. Current input boundary

```text
eq[8]:       exactly 7 token characters + '\0'
eq_re[8]:    those 7 tokens reordered  + '\0'
operators:   + -       precedence 1
             * / %     precedence 2
sentinel:    '\0'      precedence 0
```

Text equivalent: four single digits alternate with three binary operators.
Both loops run exactly seven times; shorter expressions are unsupported.
Exclude spaces, parentheses, unary signs, multi-digit operands, zero divisors,
and arithmetic outside C `int`. These conditions are assumptions, not checked
rejections.

## 10. Three related meanings

```text
Stack ADT          LIFO behavior through push, peek, pop
explicit storage   int stack[10] and its next-insertion/count size
runtime call stack bookkeeping for actual active function calls
```

Text equivalent: a character label does not create a C call frame. The name
`stack` does not enforce LIFO; the operation bodies do. Later modules may use
a different item type or index direction while retaining the same behavior.
