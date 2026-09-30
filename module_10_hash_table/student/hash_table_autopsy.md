# Hash-Table Autopsy - Delete, Then Lose the Route

## Purpose

An **autopsy** is a careful investigation after a failure. This activity
examines one bounded logical defect in isolation. It is never linked into the
ordinary table tests.

The fixture contains capacity 8 and exactly three occupied entries:

```text
index2 key10 value100
index3 key18 value180
index4 key26 value260
all other indexes EMPTY
```

All three keys have home 2. The intended operation removes key 18.

## 1. Predict before running

The faulty branch clears the removed slot this way:

```c
slot->key = 0U;
slot->value = 0;
slot->state = HASH_SLOT_EMPTY;
table->size -= 1U;
```

In plain language, what fact does each assignment change?

____________________________________________________________________

Which line first violates the probe-route rule?

____________________________________________________________________

Predict the inspected indexes and result of `get(26)` after this branch.

____________________________________________________________________

## 2. Inspect the bounded evidence

From the `code/` directory, run only the documented autopsy target:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

or:

```text
make autopsy
```

Record the relevant output:

____________________________________________________________________

The program remains inside indexes 0 through 7. What incorrect logical
answer appears?

____________________________________________________________________

## 3. Find the first divergence

Complete the two traces.

```text
correct after remove18: index2 O10, index3 ___, index4 O26
faulty after remove18:  index2 O10, index3 ___, index4 O26
```

Correct `get(26)` route/result:

____________________________________________________________________

Faulty `get(26)` route/result:

____________________________________________________________________

The earliest wrong state is:

____________________________________________________________________

## 4. Repair the invariant

Write the corrected state/count changes:

```c
slot->key = ________;
slot->value = ________;
slot->state = ____________________;
table->size ____________________;
table->tombstones ____________________;
```

Why are the inactive key and value cleared even though lookup uses state?

____________________________________________________________________

## 5. Add a regression

Describe or write the smallest regression that distinguishes empty from
deleted. It must:

1. create a collision chain;
2. remove a nonfinal entry;
3. look up a later entry;
4. assert exact slot state and counts; and
5. validate and destroy the table.

____________________________________________________________________

____________________________________________________________________

## 6. Classify the failure precisely

Check each claim and justify it.

- [ ] The faulty example demonstrates an out-of-bounds array access.
- [ ] The faulty example demonstrates a use-after-free.
- [ ] The faulty example demonstrates a logical invariant failure.
- [ ] The faulty example proves an indicator is malicious.

Justification:

____________________________________________________________________

The lesson is that a locally plausible empty marker can destroy global
lookup reachability. It is not evidence of memory corruption, indicator
authenticity, unauthorized access, or overall system compromise.
