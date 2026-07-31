# Module 7 Evidence Template

Name: ____________________________  
Date: ____________________________

**Evidence** is information supporting a claim. Record exact states,
statuses, outputs, commands, and observations so another person can repeat
your checks.

## 1. Queue model

Define in your own words:

- Queue and FIFO:

  __________________________________________________________________

- front, back, enqueue, peek, and dequeue:

  __________________________________________________________________

- physical storage versus logical order:

  __________________________________________________________________

- why FIFO arrival order is not numeric sorting:

  __________________________________________________________________

## 2. Capacity-four trace

After enqueueing `31, 8, 47, 19`, dequeueing twice, then enqueueing `62, 5`:

```text
physical indexes 0, 1, 2, 3:
head:
size:
derived tail:
logical order:
```

Attempted `enqueue(90)`:

```text
status:
fields preserved:
slots preserved:
```

Drain:

```text
reported order:
final head:
final size:
stale physical values, if observed:
```

## 3. Invariant and formulas

Write the full invariant:

____________________________________________________________________

____________________________________________________________________

For positive capacity:

```text
tail =
physical index of logical item k =
```

Why must capacity be checked before `% capacity`?

____________________________________________________________________

How does `size` distinguish full from empty when `head == tail`?

____________________________________________________________________

## 4. Contract and failure evidence

Record one successful operation and one failure.

| Case | Starting state/output | Status | Ending state/output | Contract supported |
|---|---|---|---|---|
| success | | | | |
| failure | | | | |

Explain why a full enqueue must preserve every field and physical slot.

____________________________________________________________________

Explain why empty `peek` and `dequeue` must preserve the output.

____________________________________________________________________

## 5. Student-authored tests

### Test 1 — FIFO, including capacity 1

Claim:

____________________________________________________________________

Operations, expected result, and actual result:

____________________________________________________________________

### Test 2 — wrap-around plus repeated fill/drain

Claim:

____________________________________________________________________

Operations, expected result, and actual result:

____________________________________________________________________

### Test 3 — full/empty failure preservation

Claim:

____________________________________________________________________

Full enqueue failure:

```text
status:
fields before and after:
established slots before and after:
```

After draining, empty peek or dequeue:

```text
status:
fields before and after:
stale slots before and after:
prior output before and after:
```

Why were the fields recorded separately instead of copying the
positive-capacity Queue struct?

____________________________________________________________________

## 6. Tool evidence

A **compiler** translates C into a runnable program. A **sanitizer** checks
for some memory and arithmetic errors while a program runs.

```text
compiler and version:
exact command:
core-test result:
student-test result:
warnings:
sanitizer result, if available:
```

If a tool was unavailable, name the equivalent evidence approved by the
instructor:

____________________________________________________________________

## 7. Ownership, setup, and cleanup

Describe the Queue variable whose four fields start at zero, the one fixed
allocation, the capacity limit, and the state after destruction.

____________________________________________________________________

Why must a live Queue not be shallow-copied and destroyed twice?

____________________________________________________________________

## 8. Policy and representation

Compare reject-newest, discard-oldest, and backpressure. State which policy
the course Queue uses and why silent loss is unsafe.

____________________________________________________________________

Compare shifting array, circular array, and linked Queue costs and storage.

____________________________________________________________________

## 9. Queue Autopsy

```text
prediction:
exact program output:
first incorrect state decision:
broken contract or invariant:
smallest repair idea and precondition:
regression test:
```

## 10. Transfer and correction

How does a Queue differ from a Stack?

____________________________________________________________________

Breadth-first search (BFS) later explores shallower levels before deeper
levels. State only why FIFO storage can support that order.

____________________________________________________________________

My preserved initial claim:

____________________________________________________________________

My labeled correction and supporting evidence:

____________________________________________________________________
