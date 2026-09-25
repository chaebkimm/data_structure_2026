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
request       returned character    logical Stack    size    count
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
`size`. Push has return type `void`; peek and pop return characters.

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
valid state:   0 <= size <= capacity     (capacity = 10)
empty:         size == 0,  count 0, no top item
nonempty:      size == 3,  count 3, top item at stack[2]
full:          size == 10, count 10, push makes no change
```

Text equivalent: the full next-insertion position 10 is not an array cell.
Peek and pop check empty before selecting index -1 and return `'\0'` when
empty. A full push stops before writing at index 10. The invariant describes
valid state; the source does not repair arbitrary invalid `size` values.
`capacity` controls the full check and is initialized to 10; the actual array
has ten fixed cells.

## 5. Peek and pop

```text
before: size = 3; stack[0] = 'A', stack[1] = 'B', stack[2] = 'C'

peek: read stack[size - 1], index 2 -> 'C'; size remains 3

pop:  decrease size to 2; read stack[size], index 2 -> 'C'; return 'C'
      stack[2] can still contain 'C', but that cell is now inactive
```

Text equivalent: both operations inspect the current top after checking
nonempty. Only pop changes logical membership. It need not erase or shift
characters. At empty both return `'\0'` and leave the array and `size`
unchanged. A full push also leaves state unchanged but returns no value.

## 6. Two expression phases

```text
infix text         conversion           postfix text        evaluation
1-2*3+4       ----------------->        123*-4+        -----------------> -1
                 char stack[10]                            int values[10]
                 global count size                          local count size

postfix_size = 7
postfix[7] = '\0'     (terminator, not an eighth token)
```

Text equivalent: conversion rearranges character tokens using waiting
operators. Evaluation later processes postfix tokens, converting each digit
to a number and storing intermediate integer results. Global `postfix_size` counts
postfix tokens; it is not the character Stack count. Local `size` counts
active integer values. Global and local `value_size` are separate variables
with the same next-insertion convention.

## 7. Converting `1-2*3+4`

```text
read/work     postfix so far     waiting operators, bottom to top
start         empty              empty
1             1                  empty
-             1                  -
2             12                 -
*             12                 -, *
3             123                -, *
+             123*-              +
4             123*-4             +
drain         123*-4+            empty
```

Text equivalent: digits go straight to the output. When `+` arrives, `*`
has greater precedence and `-` has equal precedence, so both are popped to
output before `+` is pushed. The `>=` comparison enforces left associativity.
After the scan, drain the final operator and write the terminator. Reset
`postfix_size` at the next conversion and write a fresh terminator for shorter text.

## 8. Evaluating `123*-4+`

```text
token    integer values, bottom to top    value_size    calculation
1        1                                1     digit -> integer
2        1, 2                             2     digit -> integer
3        1, 2, 3                          3     digit -> integer
*        1, 6                             2     2 * 3 = 6
-        -5                               1     1 - 6 = -5
4        -5, 4                            2     digit -> integer
+        -1                               1     -5 + 4 = -1
```

Text equivalent: the value array grows upward, with its top at
`values[value_size - 1]`. Each operator pops `num2`, the right operand, before
`num1`, the left operand. Negative results such as -5 are integers in
`values`, not characters in the operator Stack.

## 9. Current input boundary

```text
infix[8]:    at most 7 token characters + '\0'
postfix[8]:  the same tokens reordered  + '\0'
operators:   + -       precedence 1
             * / %     precedence 2
```

Text equivalent: core examples assume a nonempty alternating sequence of
single digits and these operators, with no spaces, parentheses, unary
operators, or multi-digit numbers. Divisors must be nonzero and intermediates
must fit C `int`. These conditions are assumed, not fully checked by the
source. Do not infer safe rejection from a successful valid example.

## 10. Three related meanings

```text
Stack ADT          LIFO behavior through push, peek, pop
explicit storage   char stack[10] and its next-insertion/count size
runtime call stack bookkeeping for actual active function calls
```

Text equivalent: a character label does not create a C call frame. The name
`stack` does not enforce LIFO; the operation bodies do. Later modules may use
a different item type or index direction while retaining the same behavior.
