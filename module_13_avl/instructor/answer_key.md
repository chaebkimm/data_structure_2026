# Module 12 Instructor Answer Key — Trace the Supplied AVL Lab

Use [`student/lab.c`](../student/lab.c) as the authority. Accept equivalent
visual, linear, tactile, typed, dictated, or verbal evidence. Students trace
complete source and write tests; there are no required implementation TODOs.
The investigation, lab, and evidence form one Week 12 submission.

## Initial inquiry and Cognitive Pause

For distinct labels, every label in a left region is smaller than its
parent label and every label in a right region is larger. The rule applies
to a whole region, rather than just its first record. The initial inquiry
uses distinct labels; this is not a duplicate-rejection rule for the C lab.

| Insertion order | Plain root | Plain edge height | Present lookup | Missing lookup |
| --- | --- | ---: | --- | --- |
| `A B C D E F G` | A | 6 | G: 7 comparisons | H: 7 comparisons |
| `G F E D C B A` | G | 6 | A: 7 comparisons | @: 7 comparisons |
| `D B F A C E G` | D | 2 | G: 3 comparisons | H: 3 comparisons |

Count one comparison per visited record. Reaching the end adds none.
In the character set used by the lab builds, `@` sorts before A and H sorts
after G. A chain of seven records contains six links: height and comparison
count measure different things.

Local reconnection can promote the middle label while retaining all
records and the same inorder sequence. Sorted input is valid input that
can force linear plain-BST work. It is not itself an invalid memory access
or proof that a resource has been completely used up.

## Representation reveal

Module 2 supplies `nodes[10]`. Each record has a `char data` and two integer
child IDs. The current lab adds `height[10]`, indexed by the same IDs.

| Item | Meaning |
| --- | --- |
| ID `i` | Position of a record in `nodes`, not its key or height |
| `nodes[i].data` | Character used to choose the search direction |
| Child/root `-1` | No record; never an array index |
| `get_height(-1)` | `-1` |
| Leaf height | `0` |
| Balance factor | Left stored height minus right stored height |

With stable fixture IDs A=0, B=1, ..., G=6, inserting a different order
changes links, not IDs. Every fresh inserted ID must have two `-1` child
links. The caller must save `root = _add(root, id)`.

The lab accepts equal keys: `<=` sends a new equal key left during descent.
A rotation may then place an equal key on the right. The preserved rule is
nondecreasing inorder, equivalently left-region keys `<=` current key and
right-region keys `>=` current key. Three distinct IDs holding B are three
records, not one rejected insertion.

## Four canonical repairs

| Case | Arrival labels | Inserted IDs | Helper at first unbalanced node | Height refresh order |
| --- | --- | --- | --- | --- |
| LL | C B A | `2,1,0` | `rotate_ll(i,l,lr)` | `i`, then `l` |
| RR | A B C | `0,1,2` | `rotate_rr(i,r,rl)` | `i`, then `r` |
| LR | C A B | `2,0,1` | `rotate_lr(i,l,lr,lrl,lrr)` | `i` and `l`, then `lr` |
| RL | A C B | `0,2,1` | `rotate_rl(i,r,rl,rll,rlr)` | `i` and `r`, then `rl` |

All four finish at root ID 1, data B, height 1. Its left child is ID 0
(A), right child ID 2 (C), both height 0. Inorder is `A B C`.
LL/RR are single rotations. LR/RL perform the effect of two rotations by
directly assigning the four affected links; they do not call two helpers.

The helpers change links only. Their caller, `_add`, updates heights.
Updating the promoted root first would read stale child heights. No record
is moved to a different array position.

## Recursive insertion reasoning

1. At `i == -1`, assign height 0 and return the fresh node ID.
2. Compare character data and recursively select one child.
3. Save the returned child root into both `nodes[i].left/right` and `l/r`.
4. Default the local result to `root = i`.
5. Read the two child heights. If the factor is in `[-1,1]`, refresh `i`.
6. At factor 2, compare `ll` and `lr` heights; at factor -2, compare `rr`
   and `rl` heights. Capture inner grandchildren before changing links.
7. Rewire and refresh lower nodes before the promoted root.
8. Return the local root so the preceding stack frame can reconnect it.

An already-valid AVL tree gains at most one level on one path after a leaf
insertion, so the examined factor is in `[-2,2]`. Equality of the two child
heights chooses LL/RR through `>=`. There is no inserted-key shortcut.

## Middle-subtree regression

Use the valid six-label insertion order `F D G B E A`. The final insertion
makes F left-heavy. LL repair promotes D, and E moves from D's right link
to F's left link:

```text
root D: left B, right F
B: left A, right -1
F: left E, right G
A, E, G: two -1 links
```

With stable alphabet IDs this means `root=3`, `nodes[5].left=4`, and all six
inserted IDs remain reachable exactly once. Final heights are D=2, B=1,
F=1, and A/E/G=0. A three-record fixture with an empty middle subtree cannot
detect a lost-middle-link defect.

## Seven-label AVL measurements

All three required insertion orders finish with the same shape:

```text
       D(h=2)
      /      \
   B(h=1)   F(h=1)
   /   \    /   \
  A     C  E     G
```

Every leaf has height 0 and every balance factor is 0. With alphabet IDs,
root is 3, and links are `3:(1,5)`, `1:(0,2)`, `5:(4,6)`.
The listed present and missing searches each take three comparisons in the
AVL tree. Baseline insertion, search counts, and complete validation come
from the test driver, not functions exported by `student/lab.c`.

## Three original test groups

1. **Rotation and metadata:** all four canonical repairs, exact IDs and
   links, heights, sorted inorder, and a nonempty-middle fixture.
2. **Order and measurement:** the three seven-label BST/AVL builds, exact
   roots/heights/comparison counts, and independent link-derived heights.
3. **Duplicates and valid boundaries:** distinct IDs with equal data,
   empty/singleton states, ten fresh IDs, per-insertion reachability and
   balance, and reset between builds.

Reject a claim that duplicate insertion must leave the tree unchanged.
Do not execute an eleventh-ID insertion, a repeated live ID, or an invalid
child link as an expected-error test: the lab has no rejection API.

## Failure investigation and cost

Losing a middle link makes a stored record unreachable from the root. The
array record still exists; this lab performs no heap allocation or release,
so the defect is not an allocation leak. A driver should independently
detect wrong links, repeated IDs, wrong inorder, stale heights, and balance
outside `[-1,1]`. A diagnostic scan is separate from operation work.

One rotation uses a fixed number of assignments: `O(1)`. For a generalized
tree with height h, insertion and directed lookup take `O(h)`. A skewed BST
can reach `O(n)`; AVL bounds this by `O(log n)`. Recursive insertion uses
`O(h)` stack space. Traversal and a visit-once diagnostic take `O(n)`.
Actual storage is capped at ten records; scalable claims describe the
generalized algorithm, not an unbounded service implemented here.

A Heap orders parents against children by priority. It does not provide
the whole-subtree order used by directed BST lookup. AVL preserves that
search order while limiting height. Shape repair reduces the sorted-input
slowdown; it does not validate input, enforce index bounds, authenticate
users, or prove a whole system secure.

## Optional pointer reference

The `code/include`, `starter`, `solution`, `support`, and older reference
tests implement a separate 64-node allocated, unique-integer-key API. Its
status codes, duplicate rejection, allocator hooks, destruction, and
pointer autopsy are optional reference material. They are not required
features or assessment criteria for the supplied array lab.
