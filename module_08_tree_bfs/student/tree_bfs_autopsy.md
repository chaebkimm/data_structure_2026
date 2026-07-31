# Tree BFS Autopsy — Which Equal Match Leaves First?

An **autopsy** is a careful study of a supplied defect. Work in this file
before editing or running the isolated program
`code/autopsy/faulty_shallowest.c`.

**Breadth-first search (BFS)** visits smaller node depths before larger
depths. **Depth** is the child-link count from the root. A **Queue** removes
work in first-in, first-out order.

The program uses a fixed Queue and a small synthetic tree. A **bounds
check** confirms that an array index is inside its permitted positions
before access. The program keeps these checks, does not change the course
implementation, and does not access outside its arrays.

## Case

```text
A(42)
├─ left: B(17)
│  └─ left: D(44)
└─ right: C(68)
   └─ right: E(44)
```

Exact linear equivalent:

1. `A`, value 42, is the root.
2. `A` has left child `B`, value 17, and right child `C`, value 68.
3. `B` has left child `D`, value 44, and no right child.
4. `C` has no left child and has right child `E`, value 44.
5. `D` and `E` have no children.

Both matching nodes have depth 2. The published course contract removes
work in first-in, first-out order and adds a left child before a right child.
Therefore, the intended complete node-label order is:

```text
A, B, C, D, E
```

An intended search for 44 returns `D` at depth 2.

## 1. Predict before running

Read `faulty_shallowest.c`. Without running it, predict the exact three
visible output lines.

```text
complete observation:
search observation:
match:
```

Predicted complete node-label order:

____________________________________________________________________

Predicted node and depth returned for target 44:

____________________________________________________________________

## 2. Observe the bounded program

From the `code` directory, run the autopsy target named in `code/README.md`.
Copy the three visible lines. Invisible trailing spaces do not need to be
reproduced.

```text



```

Did the observation match your prediction? Preserve the prediction and
describe any difference.

____________________________________________________________________

## 3. Locate the first broken decision

A **decision point** is a place where the program chooses between possible
next actions.

Record:

```text
frontier immediately after A:
next node removed:
required next node:
first decision that made them differ:
```

Identify the earliest decision that breaks the published course order. Do
not begin with the final returned node.

____________________________________________________________________

## 4. Separate safety from correctness

Why can every index remain within its permitted array positions while the
program still returns the wrong equal-depth match?

____________________________________________________________________

Why would deleting a bounds or Queue-state check fail to repair the ordering
contract safely?

____________________________________________________________________

## 5. State the smallest repair

Describe the smallest source-level change that restores the published
left-first order. Do not rewrite the entire traversal.

____________________________________________________________________

After that repair, state:

```text
complete node-label order:
search observation:
returned node:
returned depth:
```

## 6. Design a regression test

A **regression test** is retained so a repaired defect does not return.

Write one exact test using nodes `A` through `E`. Check both the complete
order and the identity of the returned 44 node.

____________________________________________________________________

Write one different test in which equal target values occur at the same
depth on opposite sides of a root.

____________________________________________________________________

## 7. Autopsy conclusion

```text
prediction:
observation:
first broken decision:
smallest repair:
regression test:
```
