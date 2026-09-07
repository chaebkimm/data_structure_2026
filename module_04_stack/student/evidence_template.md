# Module 4 Evidence Record

Complete this record after the Stage D notes and Stage E lab. You may replace
any table with a numbered list using the same headings.

Name: ____________________________  
Compiler used: ____________________________

## 1. Stack language

A Stack:

____________________________________________________________________

LIFO and top:

____________________________________________________________________

Push, pop, and peek:

____________________________________________________________________

Underflow and full-Stack rejection:

____________________________________________________________________

## 2. Canonical operation trace

Trace from bottom to top. Record every return and output.

```text
push(100), push(200), push(300), peek, pop, pop, pop
```

| Step | Function return | Output, if any | New size | Logical Stack |
|---:|---:|---:|---:|---|
| Start | none | none | 0 | empty |
| 1 | | | | |
| 2 | | | | |
| 3 | | | | |
| 4 | | | | |
| 5 | | | | |
| 6 | | | | |
| 7 | | | | |

## 3. Representation invariant

State the valid relationship among `size`, `capacity`, and the logical index
range:

____________________________________________________________________

Which expression identifies the top? Which expression identifies the next
unused position?

____________________________________________________________________

Why must the caller pass the actual prepared capacity of its array?

____________________________________________________________________

Why must a `peek` or `pop` output be separate from the Stack array?

____________________________________________________________________

What can remain in an array position after a successful pop, and why is that
value no longer a logical item?

____________________________________________________________________

## 4. Rejection behavior

State the exact return and everything that remains unchanged after:

- `push` on a full Stack;
- `push` with invalid size/capacity metadata;
- `peek` on an empty Stack when its output already contains 999; and
- `pop` on an empty Stack when its output already contains 999.

____________________________________________________________________

## 5. Expression transfer

Trace the number Stack and operator Stack for `1+2*3`:

____________________________________________________________________

State the complete accepted grammar:

____________________________________________________________________

Why must `expression_evaluate` leave its output unchanged after malformed
input, internal capacity failure, or checked integer overflow?

____________________________________________________________________

## 6. Test evidence

| Case | Expected result | Actual result | Pass? |
|---|---|---|---|
| Empty Stack | | | |
| Canonical 100, 200, 300 LIFO trace | | | |
| Peek preserves size and array | | | |
| Pop exposes the previous item | | | |
| Full push preserves size and logical items | | | |
| Invalid metadata is rejected | | | |
| Failed peek preserves output | | | |
| Failed pop preserves output | | | |
| `1+2*3` evaluates to 7 | | | |
| Single digit succeeds | | | |
| Malformed expression is rejected | | | |
| Checked arithmetic overflow is rejected | | | |

### Three student-authored tests

State the new claim checked by each test.

1. Canonical or new LIFO sequence:

   __________________________________________________________________

2. Boundary and preservation case:

   __________________________________________________________________

3. One expression success and one checked rejection:

   __________________________________________________________________

## 7. Costs

| Work | Cost | Reason |
|---|---:|---|
| Push | | |
| Peek | | |
| Pop | | |
| Evaluate input of length `n` | | |
| Two fixed ten-position internal arrays | | |

## 8. Three uses of “stack”

Distinguish:

1. the Stack ADT;
2. the runtime call stack; and
3. the local `int stack[10]` buffer used as one Stack representation.

____________________________________________________________________

## 9. Stack-Top Autopsy

- first incorrect read:
- logical rule broken:
- why the read remains inside physical storage:
- visible wrong value:
- repair:
- regression case:

## 10. Correction note

My initial model:

____________________________________________________________________

The evidence that changed or strengthened it:

____________________________________________________________________
