# Linked-List Autopsy - Release, Then Read

## Purpose

An **autopsy** is a careful investigation after a failure. This activity
examines one bounded use-after-free defect in isolation. It is never linked
into the normal list or DSU build.

The fixture contains exactly three allocated nodes:

```text
R(17) -> Q(23) -> P(31) -> NULL
```

The intended operation removes Q.

## 1. Predict before running

The faulty order is:

```c
free(victim);
successor = victim->next;
previous->next = successor;
```

In plain language, what does each line attempt to do?

____________________________________________________________________

Which line first violates an object's lifetime?

____________________________________________________________________

## 2. Mark ownership before the defect

Complete:

| Symbol | Object | Live? | Owned by the list? |
|---|---|---|---|
| `previous` | | | |
| `victim` | | | |
| `victim->next` before release | | | |

Why is Q reachable and owned before `free(victim)`?

____________________________________________________________________

## 3. Locate the first invalid action

`free(victim)` ends Q's lifetime. The saved pointer value `victim` may
still contain Q's old address, but that address no longer names a live Q
object.

Explain why evaluating `victim->next` is a use-after-free even if the old
bytes appear unchanged:

____________________________________________________________________

State why a crash is not required for the program to be wrong:

____________________________________________________________________

## 4. Repair the order

Number these actions in a safe order:

___ save `victim->next` in `successor`

___ change `previous->next` to `successor`

___ release `victim`

___ decrease the list's stored node count

Write the exact final chain:

____________________________________________________________________

## 5. Run the isolated program

Use the autopsy build described in the code README. Record:

- compiler and version: _____________________________________________
- warning-enabled result: __________________________________________
- sanitizer or debugger result: ____________________________________
- first reported invalid source line: _______________________________

An AddressSanitizer report, debugger evidence, or instructor-provided trace
is acceptable. Tool availability is not graded.

## 6. Design a regression test

Describe one test that would fail if deletion left R pointing to released
Q or lost P:

____________________________________________________________________

State the expected values, size, and live-allocation count:

____________________________________________________________________

## 7. Separate four claims

Complete each statement.

1. **Memory safety:** _______________________________________________
2. **Ownership:** __________________________________________________
3. **List integrity:** ______________________________________________
4. **Application meaning:** _________________________________________

Removing one synthetic record correctly does not establish whether the
record was true, authorized, or safe.

## 8. Final repair statement

Write one sentence explaining why successor-save, relink, and release must
occur in that order:

____________________________________________________________________
