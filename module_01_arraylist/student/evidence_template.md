# Module 1 Evidence Record

Name: ____________________________
Compiler or approved test environment: _____________________________

## 1. Textbook-to-code mapping

Explain the roles of `int array[10]`, `size`, and `capacity`.

____________________________________________________________________

Why can a slot exist in the array without being a current list item?

____________________________________________________________________

## 2. Representation invariant

State the permitted size range and where current items must be stored:

____________________________________________________________________

Explain how the rules are preserved:

- after a successful insertion: ____________________________________
- after a successful deletion: _____________________________________
- after a rejected full-list addition: _____________________________

## 3. One operation sequence

Start with `[100, 200, 300]` in ten slots. Show the list and count after
updating index 1 to 500, removing index 1, and inserting 600 at index 1.

____________________________________________________________________

For one call, show how the caller stores the returned count:

____________________________________________________________________

## 4. Operation costs

| Operation | Items read, written, or moved | Reason |
|---|---:|---|
| Read or update a valid index | | |
| Search for a missing value | | |
| Append with room | | |
| Insert at the front | | |
| Delete at the front | | |
| Reject an addition when full | | |

## 5. Test evidence

| Case | Expected result | Actual result | Pass? |
|---|---|---|---|
| Read check on an empty list | | | |
| Read or update at index `size` | | | |
| First append | | | |
| Full append preserves array and size | | | |
| Full insertion preserves array and size | | | |
| Negative or otherwise invalid index | | | |
| Insertion preserves suffix order | | | |
| Deletion compacts current items | | | |
| Search returns the first duplicate | | | |
| Search ignores an unused matching value | | | |
| Invalid size/capacity preserves state | | | |

### Three student-authored tests

For each test, state the claim it checks and why it adds evidence beyond the
supplied tests.

1. Test and rationale:

   __________________________________________________________________

2. Test and rationale:

   __________________________________________________________________

3. Test and rationale:

   __________________________________________________________________

## 6. Tool evidence

Warning-enabled build command and result:

```text
paste output here
```

Student-test command and result:

```text
paste output here
```

Sanitizer, debugger, or approved instructor-test evidence:

```text
paste output here
```

## 7. Bounds and Invariant Autopsy

- starting size and usable capacity:
- first incorrect condition:
- guard value before and after the write:
- size after the faulty call:
- why the extra guard slot is not a fix:
- repair:
- regression test:

## 8. Explain the boundary

How would a caller tell that an addition was rejected, and how should the
caller report it without pretending the new item was stored?

____________________________________________________________________

Why may zero or `-1` be valid list data rather than an “empty” marker?

____________________________________________________________________

## 9. Correction note

My initial misconception:

____________________________________________________________________

The evidence that changed my reasoning:

____________________________________________________________________
