# Graph BFS Autopsy — Repeated Pending Work

An **autopsy** is a careful investigation of a supplied failure. Work in
this file before running `code/autopsy/faulty_frontier.c`. Do not edit that
supplied program.

The standalone program uses only five synthetic vertices and an eight-slot
checked waiting array. A **bounds check** confirms an array position is
inside its permitted range before access. The program requests no dynamic
storage. It has a fixed maximum number of removals and does not change the
course implementation.

## Published contract

A vertex becomes **discovered** immediately after its first successful
enqueue. A **Queue** removes the earliest-added waiting vertex first. Its
pending vertices are listed front to back.

Every discovered vertex must be enqueued at most once. First discovery
fixes distance and predecessor permanently.

## Fixture

```text
0:[1,2]
1:[3,4]
2:[3,4]
3:[0]
4:[]
```

Exact linear edges:

```text
1. 0 -> 1
2. 0 -> 2
3. 1 -> 3
4. 1 -> 4
5. 2 -> 3
6. 2 -> 4
7. 3 -> 0
8. Vertex 4 has no outgoing edge.
```

## 1. Predict before running

Read `faulty_frontier.c`. Do not run it yet.

Predict:

```text
Queue after removing 0 and scheduling its neighbors:
Queue after removing 1 and scheduling its neighbors:
Queue after removing 2 and scheduling its neighbors:
complete removal order:
predecessor[3]:
predecessor[4]:
```

Why did you predict those predecessors?

____________________________________________________________________

## 2. Observe the bounded program

From the `code` directory, run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

Copy the relevant output:

```text




```

Did the observation match your prediction? Preserve the prediction and
describe any difference.

____________________________________________________________________

## 3. Locate the first broken decision

A **decision point** is a place where the program chooses its next action.

Record:

```text
first vertex scheduled more than once:
first Queue state containing that duplicate:
earlier record for that vertex:
decision that permitted the second record:
```

Identify the earliest broken decision, not only the final duplicate removal.

____________________________________________________________________

## 4. State the violated invariant

An **invariant** is a rule that remains true after every completed step.

Which published invariant is broken?

____________________________________________________________________

How does the observed predecessor change show that first discovery was not
permanent?

____________________________________________________________________

What happens at edge `3 -> 0`? Why does that cycle edge not create another
source record in this particular run?

____________________________________________________________________

## 5. Separate safety from correctness

Why can every index remain in bounds while the waiting state and result are
wrong?

____________________________________________________________________

Why would increasing the eight-slot capacity fail to repair the scheduling
rule?

____________________________________________________________________

Why should a report not claim that this exact observation produced a wrong
hop distance?

____________________________________________________________________

## 6. State the smallest repair

Describe the smallest change that makes a neighbor discovered immediately
after its first successful enqueue. Include the source.

____________________________________________________________________

Do not remove bounds checks, Queue checks, or the fixed maximum-removal
check.

After repair, predict:

```text
Queue after processing 2:
complete removal order:
predecessor[3]:
predecessor[4]:
```

## 7. Design a regression test

A **regression test** is retained so a repaired defect does not return.

Write one exact test using this fixture. Check:

- complete visit count and order;
- no duplicate vertex;
- distances of 3 and 4; and
- predecessors of 3 and 4.

____________________________________________________________________

Write one different converging graph that would expose delayed discovery.

____________________________________________________________________

## 8. Autopsy conclusion

```text
prediction:
observation:
first broken decision:
violated invariant:
smallest repair:
regression test:
```
