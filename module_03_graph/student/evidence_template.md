# Module 3 Evidence Record

Complete this record after the Stage D notes and Stage E lab. It asks you
to use the technical words already introduced there. You may replace any
table with a numbered list that uses the same headings.

Name: ____________________________  
Compiler used—the program that translates C into a program the computer can
run: ____________________________

## 1. Vocabulary in your own words

A graph:

____________________________________________________________________

A vertex:

____________________________________________________________________

An edge:

____________________________________________________________________

Directed versus undirected:

____________________________________________________________________

Weighted versus unweighted:

____________________________________________________________________

## 2. Three representations

Show the same small graph as:

1. a diagram or verbal description;
2. an edge set;
3. an adjacency matrix.

____________________________________________________________________

## 3. Matrix meaning

Explain `adjacency[2][4]`:

____________________________________________________________________

Why must an undirected matrix be symmetric?

____________________________________________________________________

## 4. Completed-graph invariant

State every rule required by the course's bounded simple graph:

____________________________________________________________________

Which checks concern only one selected edge?

____________________________________________________________________

Which checks require the full active matrix?

____________________________________________________________________

## 5. Test evidence

| Case | Expected result | Actual result | Pass? |
|---|---|---|---|
| Empty graph | | | |
| Directed add/query/remove | | | |
| Undirected mirrored edge | | | |
| Duplicate edge | | | |
| Self-loop | | | |
| Out-of-range vertex | | | |
| In-degree and out-degree | | | |
| Ordered neighbor report | | | |
| Asymmetric undirected matrix | | | |
| Maximum vertex count | | | |

### Student-authored tests

For each test, state the new claim it checks.

1. Test and rationale:

   ____________________________________________________________________

2. Test and rationale:

   ____________________________________________________________________

3. Test and rationale:

   ____________________________________________________________________

## 6. Representation costs

| Representation | One-edge query | Storage | Useful when |
|---|---|---|---|
| Adjacency matrix | | | |
| Edge list | | | |
| Adjacency list | | | |

Why can a matrix waste space when few edges exist?

____________________________________________________________________

## 7. Matrix Symmetry Autopsy

- first one-sided update:
- invariant broken:
- contradictory observation:
- repair:
- regression test:

## 8. Model boundary

Why does an edge representing a communication permission not prove that a
service was contacted or exploited?

____________________________________________________________________

## 9. Spiral 1 structure choice

**Spiral 1** is the course's first Linear → Tree → Graph sequence.
For each scenario, choose ArrayList, tree, or graph. State one representation
rule, one operation cost, and one safety or correctness risk.

| Scenario | Choice and reason | Central rule | One cost | One risk |
|---|---|---|---|---|
| Ordered event log | | | | |
| One-parent directory hierarchy | | | | |
| Services with shared and returning links | | | | |

## 10. Correction note

My initial model:

____________________________________________________________________

The evidence that changed or strengthened it:

____________________________________________________________________
