# MST Cycle Autopsy - Different Endpoints, Same Group

## Purpose

Investigate one bounded logic defect in an isolated program. The program
uses valid array positions and performs no unsafe memory action. Its wrong
test accepts an edge that creates a cycle.

A **logic defect** is a validly executed instruction that makes the wrong
decision. Preserve predictions before running `faulty_endpoint_cycle.c`.

## Frozen graph and sorted order

The graph has three vertices and three logical undirected edges:

```text
ID0 A-B weight 1
ID1 B-C weight 2
ID2 A-C weight 3
```

The records are already sorted. The correct result selects IDs 0 and 1,
has total 3, one component, and no cycle.

The faulty decision is:

```text
if raw endpoint u differs from raw endpoint v:
    select the edge
```

## 1. Predict before running

After ID0, state the DSU groups:

____________________________________________________________________

After ID1, state the DSU groups:

____________________________________________________________________

Are the raw endpoints of ID2 different? _____________________________

Are the representative roots of ID2 different? _____________________

Predict the faulty selected IDs, selected count, and total:

____________________________________________________________________

## 2. Locate the first wrong decision

Complete:

> Raw endpoint inequality answers _________________________________,
> but representative-root inequality answers _____________________.

Why does selecting ID2 create a cycle?

____________________________________________________________________

Why do valid endpoint array positions not make the result correct?

____________________________________________________________________

## 3. Apply the correct decision order

Put these actions in order:

1. obtain the representative root of each endpoint;
2. compare the roots;
3. skip when roots match;
4. store the edge only when roots differ; and
5. union the two groups after successful storage.

Response:

____________________________________________________________________

Why must selection occur before union, but only after the root check?

____________________________________________________________________

## 4. Run the isolated program

To **build** means compile source into a runnable program. Run only the
documented autopsy target. The program is separate from normal tests.

Saved command and output location:

____________________________________________________________________

Observed faulty selected IDs, count, and total:

____________________________________________________________________

Observed correct selected IDs, count, and total:

____________________________________________________________________

Did observation match prediction? __________________________________

## 5. Verify both results

A **validator** is a diagnostic operation that checks stated rules.

Expected status for the faulty result: ______________________________

Exact failed structural rules:

____________________________________________________________________

Expected status for the correct result: _____________________________

Why is selected count `V-1` useful here, but not sufficient by itself on an
arbitrary malformed result?

____________________________________________________________________

## 6. Design a regression test

A **regression test** remains after repair so the defect does not return.

State the input, expected selected IDs, total, component count, and
validator status:

____________________________________________________________________

State at least one assertion that detects the extra cycle even if a faulty
total were edited to look plausible:

____________________________________________________________________

## 7. Separate three claims

**Memory safety** means reads and writes remain within valid storage and
object lifetimes. **Integrity** means stored state obeys its required rules.
**Resilience** means required service continues after a failure.

Why is the faulty run memory-safe but not structurally valid?

____________________________________________________________________

Why would a corrected MST still not prove resilience?

____________________________________________________________________

## 8. Final repair statement

In three sentences, name the wrong comparison, the correct comparison, and
the evidence that proves the repair.

____________________________________________________________________

____________________________________________________________________
