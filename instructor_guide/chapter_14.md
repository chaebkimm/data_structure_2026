# Chapter 14. Connecting Scattered Nodes and Managing Connected Groups

## Starting Question

> "To safely delete one node from a list connected by addresses, and to quickly know if two vertices are already connected, what do we need to remember?"

**Expected Answer:** Students should say that we must save the next address before cutting the node, and for each vertex, we must remember the path to the representative (leader) of its group.

## Why We Need This

A list connected by addresses changes links instead of moving values. A line that points only to one next node is called a "singly linked list." If we do the steps in the wrong order, we might lose the address of the next node or try to read a deleted node again.

We also need to reduce the work of searching the whole graph again every time a new undirected relationship comes in. Groups that have no overlapping items are called "disjoint sets." The structure that manages these groups by saving the path to the representative is written for short as "DSU" (Disjoint Set Union).

In week 12, we only code fixing the ownership (pointers) to delete one middle node, and the DSU. We trace other list actions using provided code. For the provided edge list maker and safe comparison function, we just check the running results.

## Board Walkthrough

First, let's delete Q.

```text
R(17) -> Q(23) -> P(31) -> NULL

previous  = R
victim    = Q
successor = P

R(17) -> P(31) -> NULL

```

While Q is still alive, we save the `successor` (the next node) first. After changing the link to P, we delete Q.

Next, we process these mergers step by step. `parent` is the parent ID to follow. `component_size` saves the group's size only at the representative root. `components` is the current number of connected parts.

```text
A-B, C-D, A-C, E-F, G-H, E-G, A-E

parent          [A,A,A,C,A,E,E,G]
component_size  [8,0,0,0,0,0,0,0]
components      1

```

Finding H follows `H->G->E->A`, and then makes only that path shorter.

```text
parent          [A,A,A,C,A,E,A,A]
component_size  [8,0,0,0,0,0,0,0]

```

A cycle (loop) is a path that comes back to the starting point without repeating any other vertices. If D and H have the same representative root, adding a D-H edge makes a cycle using the existing path and the new edge.

Ask these questions before doing the next action:

* Before deleting Q, which address must we save separately?
* After finding H, which positions in the `parent` array change?
* After checking the representative roots of D and H, what state do we leave exactly as it is?

## Common First Thoughts

* "We can delete Q first and then read `Q->next` afterwards."
* "If we just copy the `head`, the two lists will have completely different nodes."
* "If we find H, all parents in the DSU change to A at the same time."
* "Knowing they are in the same group also tells us the actual path between them."

## Neutral Questions

* What is the address that can only be reached through the node we are about to delete right now?
* Which IDs did this search actually pass through?
* What are the states of the two representative roots and the group sizes right before merging?

## Vocabulary Rules

**Words we can use:** Node address, ownership, `NULL`, undirected graph, connected component, cycle, and array ID.

**Names we will introduce in this chapter:** Singly linked list, traversal, insert at front, use-after-free, disjoint set, DSU, representative root, path compression, and union by size.

**Words we won't use yet:** Full list feature implementation, structures that support deleting relationships, or the minimum connection method and selection reasons from Chapter 16.

## Final Check

> "How do we decide the order of deleting Q, and the range of parents to change after finding H?"

**Minimum Expected Answer:** Students should mention the exact moment to save the next address, and that we only compress the path of parents we actually passed through.