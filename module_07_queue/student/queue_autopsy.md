# Queue Autopsy — A Free Slot That Is Rejected

An **autopsy** is a careful study of a supplied defect. The standalone
program `code/autopsy/faulty_wrap.c` is intentionally faulty, but it checks
every physical index before use. The same starting state always gives the
same output, and the program does not access outside its three-element
array.

## Case

The training Queue has capacity 3:

| Physical index | 0 | 1 | 2 |
|---:|---:|---:|---:|
| Stored value | `10 STALE` | `20 LIVE` | `30 LIVE` |

`head == 1` and `size == 2`. Logical FIFO order is `20, 30`. Index 0 is
available, so event 40 should fit without moving either live event.

Exact linear equivalent:

1. Physical index 0 contains stale value 10 and is not a Queue item.
2. Physical index 1 contains live event 20, the front.
3. Physical index 2 contains live event 30.
4. Capacity is 3, head is 1, size is 2, and logical order is 20 then 30.

## 1. Predict before running

Without running the program, complete its exact four output lines:

```text
before: __,__
enqueue 40 accepted: __
size after attempt: __
after: __,__
```

Which physical index should a correct addition use?

____________________________________________________________________

What complete logical order should follow a successful addition?

____________________________________________________________________

## 2. Observe the bounded program

From the `code` directory, run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

Copy the four program lines exactly:

```text




```

Did the observation match your prediction? Preserve the prediction and
describe any difference.

____________________________________________________________________

## 3. Locate the first wrong decision

Read `training_enqueue` in `faulty_wrap.c`. A **candidate index** is the
physical position an operation considers using. A **bounds check** tests
whether an index is within the permitted physical positions before use.

Record:

```text
candidate index calculated by the program:
capacity:
bounds-check decision:
returned result:
```

What is the earliest incorrect state decision? Do not begin with the final
printed symptom.

____________________________________________________________________

Which facts prove that the Queue is not full?

____________________________________________________________________

## 4. Separate safety from correctness

The supplied bounds check rejects an index outside the permitted array
positions. It prevents an invalid access.

Why can the program avoid access outside the three permitted positions yet
still violate the Queue contract?

____________________________________________________________________

Why would deleting only the bounds check be unsafe?

____________________________________________________________________

## 5. State a repair without patching yet

A **precondition** is a fact that must be true before a calculation or
operation. Describe the smallest change to the candidate-index decision.
State the capacity precondition that must be checked before applying your
calculation. Do not edit the autopsy program during this step.

____________________________________________________________________

Show the repaired state after accepting 40:

```text
physical index 0:
physical index 1:
physical index 2:
head:
size:
next insertion index:
logical order:
```

## 6. Design regression tests

A **regression test** is kept so a repaired defect does not return.

1. Write one exact test for the 10/20/30 state and attempted event 40.

   _________________________________________________________________

2. Write one different test that reaches the same physical boundary after
   more than one fill/drain cycle.

   _________________________________________________________________

For each test, state the expected status, fields, physical values, and
logical order.

## 7. Autopsy conclusion

```text
prediction:
observation:
first broken rule:
smallest repair idea:
required precondition:
regression test:
```
