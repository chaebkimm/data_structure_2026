# Module 8 Evidence Template

Name: ____________________________  
Date: ____________________________

**Evidence** is information supporting a claim. Record exact states,
statuses, outputs, commands, and observations so another person can repeat
your checks.

Complete this form after the Stage D textbook and Stage E lab. Technical
terms below use the definitions supplied in those two files.

## 1. BFS model

Define in your own words:

- breadth-first search and level order:

  __________________________________________________________________

- depth and shallowest:

  __________________________________________________________________

- frontier and work record:

  __________________________________________________________________

- why FIFO Queue behavior produces nondecreasing depth:

  __________________________________________________________________

## 2. Canonical trace

For the canonical `C0` through `C8` tree, record:

```text
complete key order:
complete flag order:
complete depth order:
largest Queue count:
one frontier state at that count:
```

Why can a Queue contain adjacent depths at the same time?

____________________________________________________________________

## 3. Search evidence

| Target | Expected node/depth or status | Actual result | Pass? |
|---:|---|---|---|
| 17 | | | |
| 44 | | | |
| 99 | | | |

Why does target 44 test equal-depth left-before-right behavior?

____________________________________________________________________

Show that missing target 99 preserves the previous `TreeBfsMatch`.

____________________________________________________________________

## 4. Shape measurements

```text
width at depth 0:
width at depth 1:
width at depth 2:
width at depth 3:
maximum width w:
edge height h:
root balance factor:
```

State the height of `NULL`, a leaf, and an `n`-node one-child chain.

____________________________________________________________________

## 5. Contract and failure evidence

| Case | Starting output | Status | Ending output | Claim supported |
|---|---|---|---|---|
| empty level order | | | | |
| nonempty, Queue limit 0 | | | | |
| canonical level order, Queue limit 4 | | | | |
| canonical level order, Queue limit 3 | | | | |
| canonical search for 17, Queue limit 2 | | | | |
| canonical height, Queue limit 4 | | | | |
| canonical height, Queue limit 3 | | | | |
| empty height | | | | |
| missing search | | | | |

Why do the BFS functions commit a local candidate only after success?

____________________________________________________________________

## 6. Student-authored tests

### Test 1 — level order and depths

Claim, operations, expected result, and actual result:

____________________________________________________________________

### Test 2 — shallowest duplicate and missing preservation

Claim, operations, expected result, and actual result:

____________________________________________________________________

### Test 3 — height and Queue boundary

Claim, operations, expected result, and actual result:

____________________________________________________________________

## 7. Tool evidence

```text
compiler and version:
exact core-test command:
core-test result:
exact student-test command:
student-test result:
warnings:
sanitizer result, if available:
```

If a tool was unavailable, name the approved equivalent evidence:

____________________________________________________________________

## 8. Storage and ownership

Where is the typed Queue's work array stored? Why does it require no
allocation or destruction?

____________________________________________________________________

Who owns the tree nodes? When does a `TreeBfsMatch.node` pointer stop being
safe to use?

____________________________________________________________________

Record cleanup evidence:

```text
constructed nodes:
destroy result:
root after destroy:
live-node count, when the testing hook is available:
```

## 9. BFS and DFS costs

| Method | Full-traversal time | Auxiliary space | Shape that stresses it |
|---|---:|---:|---|
| BFS | | | |
| DFS | | | |

Why is returned `TreeBfsOrder` storage separate from auxiliary space?

____________________________________________________________________

## 10. Balance preview

For the strict BST `30 ← 20 ← 10`, record:

```text
heights before:
balance factors before:
relationships after supplied right rotation:
inorder after:
height after:
balance factors after:
```

## 11. Tree BFS Autopsy

```text
predicted faulty order:
observed faulty order:
predicted returned node:
observed returned node:
first broken decision:
smallest repair:
regression test:
```

## 12. Transfer and correction

Why does a valid tree need no visited record, while a graph usually does?

____________________________________________________________________

My preserved Stage A claim:

____________________________________________________________________

My labeled correction and supporting evidence:

____________________________________________________________________
