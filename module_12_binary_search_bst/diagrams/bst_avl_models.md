# Module 12 Models — Character Keys, Integer Links, and AVL Repair

These models describe [`student/lab.c`](../student/lab.c). Every diagram
has a linear equivalent. Use stable IDs A=0, B=1, ..., G=6; a label is the
record's `data`, while a link stores its ID. Missing links are `-1`.

## 1. One balanced three-record tree

```text
          B [id1,h1]
         /          \
 A [id0,h0]       C [id2,h0]
```

Linear equivalent: root ID1 has left ID0 and right ID2. Both leaves have
two -1 links. `height[1]=1`, `height[0]=height[2]=0`. Inorder labels are
A, B, C. No record has moved to a different array position.

## 2. Arrival order changes a plain BST

```text
ascending:  A -> B -> C -> D -> E -> F -> G  (all arrows right)
descending: G -> F -> E -> D -> C -> B -> A  (all arrows left)

mixed D B F A C E G:
             D
           /   \
          B     F
         / \   / \
        A   C E   G
```

Linear equivalent: ascending root A has right B, continuing right through
G; all left links are -1. Descending root G has left F, continuing left
through A; all right links are -1. The mixed root D has children B/F;
B has children A/C; F has children E/G; A/C/E/G are leaves.

Ascending and descending heights are 6. Their deepest endpoint lookups
and selected missing lookups take seven comparisons. Mixed height is 2
and the listed lookups take three comparisons. In all three cases the
inorder labels are A B C D E F G.

## 3. Four local patterns

```text
LL C B A:     C       RR A B C:  A
             /                   \
            B                     B
           /                       \
          A                         C

LR C A B:     C       RL A C B:  A
             /                   \
            A                     C
             \                   /
              B                 B

All after:       B(h1)
                /     \
             A(h0)   C(h0)
```

Linear equivalent: LL has C.left=B and B.left=A; RR has A.right=B and
B.right=C. LR has C.left=A and A.right=B; RL has A.right=C and C.left=B.
All other initial links are -1. Every repaired state has B.left=A and
B.right=C, with both leaves' links -1. Inorder before and after is A B C.

LL uses one right rotation and RR one left rotation. LR/RL produce the
effect of two rotations, using one direct helper call with captured
grandchildren in this source.

## 4. The middle subtree must remain reachable

```text
RR before:          i                    after:        r
                   / \                                / \
                  L   r                              i   rr
                     / \                            / \
                    rl  rr                         L   rl
```

Linear equivalent: before, i has left L and right r, and r has left rl
and right rr. After `rotate_rr(i,r,rl)`, i has left L and right rl; r has
left i and right rr. The returned root is r. Inorder region order remains
L, i, rl, r, rr. The caller then refreshes i before r.

The mirror LL helper assigns `i.left=lr` and `l.right=i`, returns l, and
the caller refreshes i before l. Every symbol denotes a whole subtree
where applicable, so a missing saved region can lose several records.

## 5. Double repair captures two inner regions

```text
LR before:          i                   after:        lr
                   / \                              /  \
                  l   R                            l    i
                 / \                              / \  / \
                ll  lr                           ll lrl lrr R
                   /  \
                  lrl lrr
```

Linear equivalent: before, i has children l/R; l has children ll/lr;
lr has children lrl/lrr. After, lr has children l/i; l has children
ll/lrl; i has children lrr/R. The returned root is lr. Refresh i and l,
then lr. The sequence ll, l, lrl, lr, lrr, i, R is unchanged.

The RL mirror returns rl, with i children L/rll, r children rlr/rr,
and rl children i/r. Refresh i and r, then rl. The source captures
`rll` and `rlr` before changing any links.

## 6. A concrete nonempty-middle check

```text
insert F D G B E A

before repair:        F            after repair:       D(h2)
                     / \                             /     \
                    D   G                         B(h1)    F(h1)
                   / \                            /        / \
                  B   E                          A        E   G
                 /
                A
```

Linear equivalent: before repair F has children D/G, D has children B/E,
and B has left A. After, D has children B/F; B has children A/-1; F has
children E/G. Leaves A/E/G have two -1 links and height 0. D has height 2,
B/F height 1. E is the retained middle record, now at F.left. All six
inserted IDs remain reachable exactly once.

## 7. Stored height is separate from the links

```text
missing link -1: height -1
leaf:           1 + max(-1,-1) = 0
parent:         1 + max(left height,right height)
balance:        left height - right height
AVL allowed:    -1, 0, 1
```

Linear equivalent: a missing child contributes -1, two missing children
make a leaf height 0, and a node's stored height is one more than its
taller child's height. A valid AVL node has factor -1, 0, or 1. When a
leaf is inserted into a valid AVL tree, factors 2 and -2 trigger repair.

Changing `height[i]` alone changes metadata, not connectivity. A driver
must derive actual heights from links to check the cache independently.
Rotations only rewire; `_add` performs the height updates.

## 8. Equal keys with different IDs

```text
three fresh IDs x,y,z all store B

before repair:      B[x]       after:       B[y]
                    /                      /   \
                  B[y]                  B[z]   B[x]
                  /
                B[z]
```

Linear equivalent: `<=` sends y left of x and z left of y. LL repair
promotes y, with z left and x right. All three records are retained.
Inorder keys remain B B B. Equal-only-on-left is not a rotation invariant;
nondecreasing inorder is. A repeated live ID is different from equal
data in fresh IDs and violates the insertion precondition.

## 9. Shared seven-label result and measurements

Every AVL build of ascending, descending, and mixed required orders ends
with Model 2's balanced D(B(A,C),F(E,G)) shape. Heights are D=2, B/F=1,
A/C/E/G=0. With stable IDs, root is 3 and links are `3:(1,5)`,
`1:(0,2)`, `5:(4,6)`.

| Order | Present / missing | Plain comparisons | AVL comparisons |
| --- | --- | --- | --- |
| ascending | G / H | 7 / 7 | 3 / 3 |
| descending | A / @ | 7 / 7 | 3 / 3 |
| mixed | G / H | 3 / 3 | 3 / 3 |

Linear equivalent: the two sorted orders need seven comparisons for their
listed plain-BST lookups; mixed needs three. All listed AVL lookups need
three. Missing @ sorts below A and missing H above G in the lab builds.
Lookups and measurement are supplied by the driver, not the lab source.

## 10. Heap and AVL contrast

Heap order compares each parent with its children by priority. It does not
divide all smaller and larger keys into distinct search regions. The lab's
BST/AVL order gives nondecreasing inorder and directed lookup; AVL also
bounds subtree-height differences. The fixed ten-record implementation
illustrates this algorithm and does not provide an unbounded service API.
