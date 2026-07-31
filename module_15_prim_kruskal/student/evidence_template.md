# Module 15 Evidence Record

Name: ____________________________
Date: ____________________________

Use exact saved output or a precise written trace. Do not replace evidence
with "it worked."

## 1. Preserved inquiry and pause

Stage A file location: ______________________________________________

Three-target pause location: _______________________________________

Correction labels used: ____________________________________________

Evidence that changed my first model: _______________________________

## 2. Objective contrast

```text
Dijkstra selected edges and sum:
Dijkstra A-to-C path and cost:
MST selected edges and total:
MST A-to-C path and cost:
```

Why both results can be correct:

____________________________________________________________________

## 3. Canonical Prim evidence

```text
pop order:
selected IDs:
total:
pushes / pops:
stale / already-in-tree pops:
frontier peak:
incident scans:
eligible crossing tests:
key improvements:
validator status:
```

Evidence for the equal D-to-E decision:

____________________________________________________________________

## 4. Prim restart evidence

For the six-vertex boundary graph:

```text
restart roots:
selected IDs:
components:
selected count:
total:
V-c check:
self-loop decision:
parallel-edge decision:
```

Saved output location: ______________________________________________

## 5. Canonical Kruskal evidence

Sorted edge order: __________________________________________________

```text
selected IDs:
examined:
cycle skips:
self-loop skips:
components:
total:
validator status:
```

DSU groups after each accepted edge:

____________________________________________________________________

## 6. Equal-result evidence

All-weight-1 square:

```text
Prim selected IDs and total:
Kruskal selected IDs and total:
```

Why total must agree while edge IDs may differ:

____________________________________________________________________

## 7. Structural and minimum validation

One malformed structural result and returned status:

____________________________________________________________________

One structurally valid but nonminimum result and returned status:

____________________________________________________________________

Canonical exchange-check evidence:

____________________________________________________________________

Why validation is an explicit diagnostic rather than hidden algorithm work:

____________________________________________________________________

## 8. Numeric evidence

Large triangle MST and mathematical total:

____________________________________________________________________

Order-independent cancellation case:

____________________________________________________________________

Truly out-of-range final total and preserved output marker:

____________________________________________________________________

Comparator extreme evidence:

____________________________________________________________________

## 9. Three implementation clusters

### Cluster 1 - Prim restart, pop, filter, and select

Smallest relevant test: ____________________________________________

Key evidence: ______________________________________________________

### Cluster 2 - Prim scan, improve, and push-before-commit

Smallest relevant test: ____________________________________________

Key evidence: ______________________________________________________

### Cluster 3 - Kruskal sort, root check, select, and union

Smallest relevant test: ____________________________________________

Key evidence: ______________________________________________________

## 10. Exactly three original tests

### Test 1 - Prim lazy trace and restart

Claim and key assertions:

____________________________________________________________________

### Test 2 - Kruskal filtering and ties

Claim and key assertions:

____________________________________________________________________

### Test 3 - Boundaries, preservation, and cross-validation

Claim and key assertions:

____________________________________________________________________

## 11. Build and autopsy evidence

Warning-enabled command: ___________________________________________

Core-test result: __________________________________________________

Student-test result: _______________________________________________

Autopsy prediction and observed first wrong decision:

____________________________________________________________________

Autopsy repair and regression:

____________________________________________________________________

## 12. Representation and complexity memo

Supplied representation and density: ________________________________

Recommended algorithm: _____________________________________________

Conversion work: ___________________________________________________

Actual time and extra-storage bounds:

____________________________________________________________________

## 13. Cost and resilience

Canonical failure analyzed: ________________________________________

Backup edge and failures it protects: _______________________________

Failures it does not protect: ______________________________________

Four facts the result cannot prove about real input or service:

____________________________________________________________________

## 14. Final synthesis

In four sentences, distinguish shortest paths, MST/MSF, structural and
minimum validation, and resilience.

____________________________________________________________________

____________________________________________________________________
