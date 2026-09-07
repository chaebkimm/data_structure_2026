# Module 4 Stack Models

Each model includes a text equivalent. State rows are written from bottom to
top unless a physical array is shown with explicit indexes.

## 1. The one accessible end

```text
                 top
                  |
                  v
bottom   [ 100 ][ 200 ][ 300 ]
                              ^
                       push, peek, pop
```

Text equivalent: the Stack contains 100, 200, and 300 in that order from
bottom to top. Only the right end is accessible. A successful `peek` reports
300 without changing the Stack. A successful `pop` reports 300 and makes 200
the new top. A successful `push(400)` would place 400 after 300.

## 2. Canonical function-return trace

```text
request       returned/output       logical Stack       size
start         none                  empty                 0
push(100)     1                     100                   1
push(200)     2                     100, 200              2
push(300)     3                     100, 200, 300         3
peek          return 1, output 300  100, 200, 300         3
pop           return 2, output 300  100, 200              2
pop           return 1, output 200  100                   1
pop           return 0, output 100  empty                 0
```

Text equivalent: starts add function IDs in the order 100, 200, 300. Finishes
remove them in reverse order: 300, 200, 100. This is last in, first out.
`peek` reports the same ID a following pop would report, but does not remove
it.

## 3. Physical slots and logical membership

```text
index:       0       1       2       3       4
array:    [ 100 ][ 200 ][  30 ][  40 ][  50 ]
             |_______|       |________________|
             logical            inactive

size = 2
capacity = 5
top index = size - 1 = 1
next unused index = size = 2
```

Text equivalent: the physical array has five prepared positions, but only
indexes 0 and 1 belong to the logical Stack because size is two. The top is
the value 200 at index one. Indexes two through four are allocated but
inactive; their stored bits do not make them Stack items. The next successful
push writes at index two.

## 4. The metadata invariant

```text
valid:      0 <= size <= capacity

size = 0, capacity = 10     valid empty Stack; no top
size = 3, capacity = 10     valid; top is stack[2]
size = 10, capacity = 10    valid full Stack; push is rejected
size = -1, capacity = 10    invalid metadata
size = 11, capacity = 10    invalid metadata
size = 0, capacity = -1     invalid metadata
```

Text equivalent: a valid size cannot be negative and cannot exceed capacity;
capacity cannot be negative. Empty and full are both valid states. Empty
`peek` and `pop` are rejected because no logical top exists. Full `push` is
rejected before an array position is written.

## 5. Successful and rejected push

```text
before: size 2, capacity 3, [ 100 ][ 200 ][ inactive ]
push 300
after:  size 3, capacity 3, [ 100 ][ 200 ][ 300 ]
return: 3

before: size 3, capacity 3, [ 100 ][ 200 ][ 300 ]
push 400
after:  size 3, capacity 3, [ 100 ][ 200 ][ 300 ]
return: 3
```

Text equivalent: when space remains, push writes at the old size and returns
the increased size. When size equals capacity, push returns the original size
and preserves every array position. The prepared capacity never changes.

## 6. Peek and pop share a read, not an effect

```text
before: size 3, [ 100 ][ 200 ][ 300 ]

peek: read stack[size - 1] -> 300
      output = 300, return = 1, size remains 3

pop:  read stack[size - 1] -> 300
      output = 300, return = 2, array still contains 300 at index 2
```

Text equivalent: both operations read index `size - 1` after proving size is
positive. Peek reports success as one and leaves the logical Stack unchanged.
Pop reports the former top and returns the smaller logical size. The old bits
may remain in the now-inactive array cell.

## 7. Rejection preserves a caller output

```text
before empty peek:
    size = 0
    output = 999

request rejected:
    return = 0
    size = 0
    output = 999
```

Text equivalent: the function checks the array pointer, output pointer,
metadata, and nonempty condition before writing the output. Because the empty
request fails, 999 remains observable. Empty pop follows the same output rule
and returns the original size, zero.

## 8. Two-Stack trace for `1+2*3`

```text
event             number Stack     operator Stack     calculation
start             empty            empty              none
read 1            1                empty              none
read +            1                +                  none
read 2            1, 2             +                  none
read *            1, 2             +, *               none
read 3            1, 2, 3          +, *               none
end: apply *      1, 6             +                  2 * 3 = 6
end: apply +      7                empty              1 + 6 = 7
```

Text equivalent: `*` has greater precedence than `+`, so the waiting
multiplication is applied first at end of input. Each operator pops the right
operand before the left operand. The evaluator accepts only when exactly one
number remains and the operator Stack is empty; it then writes 7 to the
caller output.

## 9. Capacity limits occupancy, not expression length

```text
input scan ----> tokens arrive over time
                  |          |
                  v          v
             [number Stack] [operator Stack]
                10 slots        10 slots
                  ^          ^
                  |__________|
                slots are reused
```

Text equivalent: each internal Stack has ten simultaneous positions. Before
each push, the evaluator checks the current size against ten. Applying an
operator removes operands and reuses positions, so the input string is not
rejected merely because its total length exceeds ten characters.

## 10. Three related meanings

```text
Stack ADT
    behavior: LIFO through push, peek, and pop

caller-owned int array
    one representation: physical storage plus size and capacity

runtime call stack
    implementation bookkeeping for active C function calls
```

Text equivalent: storing integer 100 in the course Stack does not create a C
call frame. Naming an array `stack` does not enforce LIFO; the operation
contracts do. The runtime may use its own call stack while these C functions
run, but the module does not inspect or control it.
