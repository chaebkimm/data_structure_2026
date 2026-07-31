# Module 11 Evidence Record

Name: ____________________________
Date: ____________________________
Compiler or instructor CI: __________________________________________

CI means a separate computer automatically builds and tests submitted code.

## 1. Preserved reasoning

- Stage A response location: _________________________________________
- Three-target pause location: _____________________________________
- Correction labels: _______________________________________________
- Evidence that changed my model: __________________________________

## 2. Shape and order contract

```text
left child formula:
right child formula:
parent formula:
child-exists test:
```

State Heap order using priority and sequence:

____________________________________________________________________

Why this is not global sorting:

____________________________________________________________________

## 3. Locked pause evidence

```text
Target 1 checker output and count:
Target 2 final IDs and normal count:
Target 3 output, final IDs, and normal count:
```

## 4. Canonical trace

```text
final built Heap IDs:
normal build comparisons:
peek output and comparisons:
drain output IDs:
normal drain comparisons:
```

First three post-extraction arrays:

```text
after 88:
after 17:
after 63:
```

## 5. Checker instrumentation

```text
checks after seven insertions:
build combined instrumented count:
checks after seven extractions:
drain combined instrumented count:
```

Why checker work is excluded from the claimed normal operation bound:

____________________________________________________________________

## 6. Implementation evidence

### TODO 1 - checker

Smallest relevant test: ____________________________________________

How failure preserves output and count: ____________________________

### TODO 2 - insert and sift-up

Smallest relevant test: ____________________________________________

How growth failure preserves state: ________________________________

### TODO 3 - extract and sift-down

Smallest relevant test: ____________________________________________

How the lone-left case is bounded: _________________________________

## 7. Exactly three original tests

### Test 1 - sift-up, stable ties, and separate deltas

Claim and key assertions: __________________________________________

### Test 2 - better child and missing right

Claim and key assertions: __________________________________________

### Test 3 - growth, checker, and full preservation

Claim and complete preservation snapshot: __________________________

## 8. Build and run evidence

Warning-enabled command: ___________________________________________

Core-test result: __________________________________________________

Student-test result: _______________________________________________

Sanitizer, debugger, or instructor-CI result: _______________________

## 9. Structure contrasts

Heap versus BST:

____________________________________________________________________

Heap versus sorted sequence:

____________________________________________________________________

Heap versus Module 10 unsorted backend:

____________________________________________________________________

Binary Heap versus C dynamic-memory heap:

____________________________________________________________________

## 10. Safe autopsy

```text
correct first child:
correct final IDs:
faulty final IDs:
first divergence:
```

Exact repair and regression:

____________________________________________________________________

## 11. Integrity and scope

One defect the checker detects: ____________________________________

Two facts it cannot prove: _________________________________________

Honest response if later Dijkstra needs more than 64 records:

____________________________________________________________________

What passing this lab does not prove about a real security operations center
(SOC):

____________________________________________________________________

## 12. Final synthesis

In three sentences, answer the module question using complete shape,
Heap order, and operation cost.

____________________________________________________________________

____________________________________________________________________
