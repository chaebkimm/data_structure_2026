# Module 4 Evidence Record

Complete this record after the Stage D notes and Stage E lab. You may replace
any table with a numbered list using the same headings.

Name: ____________________________  
Compiler used—the program that translates C into a runnable program:
____________________________

## 1. Stack language

A Stack:

____________________________________________________________________

LIFO:

____________________________________________________________________

Top:

____________________________________________________________________

Push, pop, and peek:

____________________________________________________________________

Underflow:

____________________________________________________________________

## 2. Operation trace

Trace this sequence. Show the Stack from bottom to top after every operation.

```text
push('A'), push('B'), peek, pop, push('C'), pop, pop
```

| Step | Returned value, if any | Stack from bottom to top |
|---:|---|---|
| Start | | |
| 1 | | |
| 2 | | |
| 3 | | |
| 4 | | |
| 5 | | |
| 6 | | |
| 7 | | |

## 3. Representation invariant

State every rule required for a valid completed `CharStack`:

____________________________________________________________________

Which field identifies the top item?

____________________________________________________________________

Why must clients use the Stack operations instead of changing `data`,
`size`, or `capacity` directly?

____________________________________________________________________

## 4. Failure behavior

What must remain unchanged after:

- a failed push?
- pop on an empty Stack?
- peek on an empty Stack?
- delimiter validation that cannot allocate memory?

____________________________________________________________________

## 5. Test evidence

| Case | Expected result | Actual result | Pass? |
|---|---|---|---|
| Empty initialized Stack | | | |
| Push, peek, and pop | | | |
| Geometric growth | | | |
| Pop underflow | | | |
| Peek underflow | | | |
| Explicit limit reached | | | |
| Destroy and reset | | | |
| Valid `A(B[C]{D})` | | | |
| Unmatched closing delimiter | | | |
| Mismatched delimiter | | | |
| Leftover opening delimiter | | | |
| Nesting-depth limit | | | |

### Student-authored tests

For each test, state the new claim it checks.

1. Test and rationale:

   ____________________________________________________________________

2. Test and rationale:

   ____________________________________________________________________

3. Test and rationale:

   ____________________________________________________________________

## 6. Costs

| Operation | Cost | Reason |
|---|---|---|
| Peek | | |
| Pop | | |
| Push with spare capacity | | |
| One push that grows | | |
| Long sequence of pushes | | |
| Validate an expression of length `n` | | |

## 7. Three meanings of “stack”

Explain the difference among:

1. the Stack abstract data type;
2. the runtime call stack used by function calls;
3. a stack-allocated character buffer.

____________________________________________________________________

## 8. Stack Autopsy

- first incorrect state or decision:
- contract or invariant broken:
- visible symptom:
- repair:
- regression test:

## 9. Forward connection

Depth-first search explores one unfinished route before returning to an
earlier choice. Explain why a LIFO Stack can remember those unfinished
choices. Do not write the search algorithm yet.

____________________________________________________________________

## 10. Correction note

My initial model:

____________________________________________________________________

The evidence that changed or strengthened it:

____________________________________________________________________
