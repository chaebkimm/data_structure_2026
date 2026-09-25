# Stack-Top Autopsy — An Inactive Cell Is Not the Top

## Case

An autopsy is a careful study of a supplied defect. This isolated program
uses the same direction of growth as `student/lab.c`. Its fixture is:

```c
char stack[10] = {'?', '?', '?', '?', '?', '?', '?', '?', '*', '+'};
int top = 8;
```

Linear description: indexes 0 through 7 contain `'?'`; index 8 contains
`'*'`; index 9 contains `'+'`; `top` is 8. A chosen marker such as `'?'`
makes an incorrect read repeatable and visible.

The intentionally faulty operation reads:

```c
return stack[top - 1];
```

## 1. Predict before running

Preserve these responses before viewing the autopsy output.

1. Which indexes are currently logical Stack items?
2. Which character should correct peek report?
3. Which index does the faulty expression select, and what character will
   it report?
4. Does either peek change `top`?
5. If a push were allowed, which physical index would receive its character?

Prediction:

____________________________________________________________________

## 2. Record the observation

Run from `module_04_stack/code`:

```sh
make autopsy
```

Or use PowerShell:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Target autopsy
```

Record the initial `top`, the correct top character, the faulty character,
and the two indexes. Copy the important output lines:

```text
top:
capacity:
correct top stack[top]:
faulty top stack[top - 1]:
faulty read selected the next inactive slot:
```

Did the observation match your prediction? Preserve any disagreement before
writing the correction.

____________________________________________________________________

## 3. Find the first broken rule

State the earliest representation rule that the faulty read violates. Do
not begin with a later incorrect calculation.

____________________________________________________________________

Complete the expressions:

```text
nonempty top index = __________
next push index, when room remains = __________
active indexes = __________ through __________
```

## 4. Separate physical safety from logical correctness

1. Why is the faulty read inside the ten-position array for this fixture?
2. Why does being within the array not prove that the selected cell belongs
   to the logical Stack?
3. Would a memory sanitizer necessarily report this fixture's read? Explain.
4. Would the same faulty expression stay in bounds when `top == 0`?

Response:

____________________________________________________________________

## 5. Explain the visible consequence

Suppose this array holds waiting expression operators. Which operator should
be used first? How could using the observed inactive marker instead lead to
a wrong conversion or calculation?

____________________________________________________________________

Why is leaving `top` unchanged insufficient to make peek correct?

____________________________________________________________________

## 6. Repair and prevent recurrence

Write the corrected read for a nonempty Stack:

```c
return ________________________________________________;
```

What guard is still needed before that read when the Stack is empty?

____________________________________________________________________

Describe one regression case that distinguishes the active top from an
inactive marker and verifies unchanged state after peek. This can be one of
your three student tests; it is not a required fourth test.

____________________________________________________________________

## 7. Separate related meanings

Explain which part of this case concerns each idea:

1. The Stack ADT access rule.
2. A fixed character array representing waiting operators.
3. The runtime call stack used for active C calls.

Are the operator characters real call frames? Explain.

____________________________________________________________________
