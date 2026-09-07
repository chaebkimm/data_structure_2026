# Stack-Top Autopsy — The Next Inactive Slot Is Not the Top

## Case

An autopsy is a careful study of a supplied defect. The isolated program uses
a caller-owned four-position integer array:

```text
stack:   [ 10 ][ 20 ][ 777 ][ 888 ]
index:      0      1      2       3
size: 2
capacity: 4
```

Indexes 0 and 1 are logical Stack items. Indexes 2 and 3 are allocated but
inactive. The sentinel values 777 and 888 make an incorrect read visible and
repeatable. A sentinel is a chosen marker used for observation.

The faulty operation reads:

```c
return stack[size];
```

Because `size < capacity`, this exact read stays inside the array. The autopsy
is memory-safe, but its Stack logic is intentionally wrong.

## 1. Predict before running

What value should a correct `peek` report?

____________________________________________________________________

What value will the faulty `peek` report?

____________________________________________________________________

Will either peek change `size`? _____________________________________

Which position is the next unused position? _________________________

## 2. Record the observation

Copy the important output lines:

```text
size:
capacity:
correct top stack[size - 1]:
faulty top stack[size]:
faulty read selected the next inactive slot:
```

Did the observation match your prediction?

____________________________________________________________________

## 3. Find the first broken rule

Do not begin with a later wrong decision. State the earliest Stack rule the
program violates.

____________________________________________________________________

Complete the indexes:

```text
top index = size - ___
next unused index = size
```

## 4. Separate physical safety from logical correctness

Why does `stack[size]` stay within the physical array in this fixture?

____________________________________________________________________

Why does “within capacity” not mean “currently in the logical Stack”?

____________________________________________________________________

Would this defect necessarily be caught by a memory sanitizer in this
fixture? Explain.

____________________________________________________________________

## 5. Explain the caller-visible consequence

Suppose 10 and 20 are IDs for paused functions. Which ID should resume next?

____________________________________________________________________

What false conclusion could a caller make after receiving 777?

____________________________________________________________________

Why is leaving `size == 2` not enough to make the result correct?

____________________________________________________________________

## 6. Repair and prevent recurrence

Write the corrected one-line read:

```c
return ________________________________________________;
```

Describe one regression case that would fail if `stack[size]` returned. This
may become one of your three required student tests; it is not a fourth test.

____________________________________________________________________

## 7. Separate related meanings

Which objects appear in this autopsy?

- [ ] the Stack ADT access rule;
- [ ] a caller-owned fixed integer array; and
- [ ] the runtime call stack used for active C function calls.

More than one box may apply. Explain each choice in one sentence.

____________________________________________________________________
