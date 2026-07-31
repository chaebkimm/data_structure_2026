# Module 2 Evidence Record

Name: ____________________________  
Compiler used—the program that translates C into a program the computer can
run:
____________________________

## 1. Vocabulary in your own words

A node:

____________________________________________________________________

A root:

____________________________________________________________________

A parent and child:

____________________________________________________________________

A leaf:

____________________________________________________________________

A pointer:

____________________________________________________________________

## 2. Three representations of one tree

Show the same tree as:

1. a diagram or verbal description;
2. an index table;
3. C pointer expressions.

____________________________________________________________________

## 3. Completed-tree invariant

State every rule that makes the completed structure a tree rather than an
arbitrary collection of links:

____________________________________________________________________

What can a local child assignment check?

____________________________________________________________________

What requires whole-tree validation?

____________________________________________________________________

## 4. Test evidence

| Case | Expected result | Actual result | Pass? |
|---|---|---|---|
| Leaf with no children | | | |
| Node with two children | | | |
| Out-of-range index | | | |
| Occupied child slot | | | |
| Shared child | | | |
| Cycle | | | |
| Disconnected node | | | |
| Valid BST | | | |
| Global BST violation | | | |
| Duplicate key | | | |

### Student-authored tests

For each test, state the new claim it checks.

1. Test and rationale:

   ____________________________________________________________________

2. Test and rationale:

   ____________________________________________________________________

3. Test and rationale:

   ____________________________________________________________________

## 5. Pointer state

For one nonnull child link:

- parent index:
- child index:
- pointer expression:
- address stored:
- why the nodes need not be adjacent:

## 6. BST range trace

For each visited node in the supplied example, record the allowed lower and
upper key limits.

| Node key | Lower limit | Upper limit | Accepted? | Reason |
|---:|---:|---:|---|---|
| | | | | |
| | | | | |
| | | | | |
| | | | | |

Why are immediate parent-child comparisons insufficient?

____________________________________________________________________

## 7. Tree Structure Autopsy

- first assignment that breaks the pure-tree model:
- rule broken:
- later incorrect result:
- repair:
- regression test:

## 8. Tree-to-graph transfer

A valid tree permits one parent per non-root node. Give a realistic
relationship that may need more than one incoming connection:

____________________________________________________________________

Why does that requirement lead toward a graph rather than a pure tree?

____________________________________________________________________

## 9. Correction note

My initial model:

____________________________________________________________________

The evidence that changed or strengthened it:

____________________________________________________________________
