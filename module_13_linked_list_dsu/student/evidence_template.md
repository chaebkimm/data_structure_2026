# Module 13 Evidence Record

Name: ____________________________
Date: ____________________________
Revision label: __________________

Preserve initial work. Add corrections with labels rather than replacing
the evidence that shows how your reasoning changed.

## 1. Preserved inquiry and Cognitive Pause

- Stage A file preserved: yes / no
- Stage B three-target response preserved: yes / no
- correction labels used: ___________________________________________

The most important correction was:

____________________________________________________________________

## 2. Canonical linked-list construction

Record the state after each operation.

| Operation | Head | Size | Limit | Reachable values |
|---|---|---:|---:|---|
| initialize with limit 4 | | | | |
| push 31 as P | | | | |
| push 23 as Q | | | | |
| push 17 as R | | | | |

Attach or reproduce a memory diagram that labels each symbolic node,
stored value, `next`, owner, and `NULL`.

## 3. Remove and destroy

For removal of the first 23:

- comparison order: _________________________________________________
- predecessor: _____________________________________________________
- victim: __________________________________________________________
- saved successor: __________________________________________________
- relink: ___________________________________________________________
- final chain and size: _____________________________________________

For destruction:

| Iteration | Current node | Saved successor | Released node |
|---:|---|---|---|
| 1 | | | |
| 2 | | | |

Exact final state:

```text
head = ______
size = ______
limit = ______
```

## 4. List invariant and ownership

Explain how the successful final states satisfy:

1. head/empty agreement: ____________________________________________
2. exact reachable count: __________________________________________
3. size/limit bound: _______________________________________________
4. no cycle: _______________________________________________________
5. one owner/no shallow copy: ______________________________________

Evidence that every successful allocation was released exactly once:

____________________________________________________________________

## 5. Preservation and no-removal outcomes

| Case | Before-state evidence | Status | After-state evidence |
|---|---|---|---|
| allocation failure | | | |
| full limit | | | |
| absent value, successful no-removal | | | |

State why equal values do not violate the invariant and which duplicate is
removed:

____________________________________________________________________

## 6. Linked-list autopsy

The earliest invalid operation was:

____________________________________________________________________

The defect is a use-after-free because:

____________________________________________________________________

Correct successor-save, relink, release, and count order:

____________________________________________________________________

A **sanitizer** is a runtime checker for errors such as invalid memory
access. A **debugger** is a tool for pausing a program and inspecting its
state.

- tool used or instructor alternative: ______________________________
- first reported line or trace step: _________________________________
- regression-test result: ___________________________________________

## 7. Make eight singleton DSU sets

After make-set creates A through H:

```text
parent:         ______________________________________
component_size: ______________________________________
element_count:  ______
components:     ______
inactive sentinel positions: _________________________
```

## 8. Exact seven-union trace

Use operation order:

```text
A-B, C-D, A-C, E-F, G-H, E-G, A-E
```

| Step | Roots | Winner | Complete parent array | Complete size array | Components |
|---:|---|---|---|---|---:|
| 1 | | | | | |
| 2 | | | | | |
| 3 | | | | | |
| 4 | | | | | |
| 5 | | | | | |
| 6 | | | | | |
| 7 | | | | | |

Explain one equal-size smaller-root decision:

____________________________________________________________________

## 9. Find H and union D-H

Before `find(H)`:

```text
parent:         [A,A,A,C,A,E,E,G]
component_size: [8,0,0,0,0,0,0,0]
```

H first-pass path: _________________________________________________

Entries changed during compression: _________________________________

Parent after `find(H)`: _____________________________________________

D path during `union(D,H)`: _________________________________________

Roots returned: ____________________________________________________

`merged`: ___________________________________________________________

Final parent array: _________________________________________________

Why the D-H relationship is cycle-producing:

____________________________________________________________________

## 10. Three implementation TODO clusters

### TODO 1 - linked push, remove, destroy

- changed functions: ________________________________________________
- key ownership ordering: ___________________________________________
- supplied tests passed: ____________________________________________

### TODO 2 - make-set and iterative find

- validation before indexing: _______________________________________
- first-pass bound: _________________________________________________
- failure/output preservation: ______________________________________

### TODO 3 - union by component size

- smaller/equal-size policy: ________________________________________
- size and component-count updates: _________________________________
- same-set behavior: _______________________________________________

## 11. Exactly three original tests

### Test 1 - list lifecycle and preservation

Name and distinct assertion:

____________________________________________________________________

### Test 2 - creation, compression, tie, and invalid ID

Name and distinct assertion:

____________________________________________________________________

### Test 3 - relationship cycles and scope

Name and distinct assertion:

____________________________________________________________________

Test output location or attachment:

____________________________________________________________________

## 12. Build and memory evidence

- compiler/version: _________________________________________________
- warning-enabled command/result: ___________________________________
- sanitizer command/result or approved alternative: _________________
- live-allocation baseline restored: yes / no
- normal build excludes faulty autopsy object: yes / no

## 13. Supplied edge pre-lab

An **incident record** describes one relationship as stored at one
endpoint. Two **reciprocal records** describe the two stored directions of
one undirected relationship. **Parallel edges** are distinct relationships
sharing endpoints.

- ten fixture incident records validated: yes / no
- emitted logical records: __________________________________________
- both A-B edge IDs retained: _______________________________________
- sorted order: ____________________________________________________
- first cycle-producing sorted edge: ________________________________
- self-loop boundary result: ________________________________________
- `INT64_MIN`/`INT64_MAX` comparator result: _________________________

Why relational comparison is safer than subtraction:

____________________________________________________________________

## 14. Complexity

Explain each implemented cost:

- push-front mutation core `O(1)`: _________________________________
- remove-by-value `O(n)`: __________________________________________
- destroy/full list validation `O(n)`: ______________________________
- all make-set operations `O(n)`: __________________________________
- amortized DSU `O(alpha(n))`: _____________________________________

What cost is excluded from the amortized claim?

____________________________________________________________________

## 15. Scope and Spiral 5 bridge

Shared DSU membership proves:

____________________________________________________________________

It does not prove authorization, trust, a route, a shortest path,
resilience, or deletion support because:

____________________________________________________________________

Complete:

| Local change | Global rule preserved | Later connection |
|---|---|---|
| list relink | | |
| DSU compression | | |
| DSU root attachment | | |
| one edge-list record per edge ID | | |

## 16. Final synthesis

> How can careful local link changes preserve a correct whole structure,
> and how will DSU support a later graph algorithm?

Final response:

____________________________________________________________________

One limitation that now matters to my design:

____________________________________________________________________
