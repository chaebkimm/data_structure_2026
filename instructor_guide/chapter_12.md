# Chapter 12. Repairing an Ordered Tree with Integer Links

Use the [Module 12 source](../module_12_bst_avl/student/lab.c) and
[180-minute lesson plan](../module_12_bst_avl/instructor/lesson_plan.md).
Students trace supplied complete code and write tests. One Week 12
submission collects the investigation and evidence. AVL deletion and the
older pointer-library starter are optional.

## Starting question

> If the same labels form a long line because of arrival order, how can we
> shorten its routes while preserving their smaller-to-larger order?

Expected reasoning: reconnect a small local region, keep every record
reachable, and promote a middle label. Introduce the formal names after
students preserve their initial model.

## Source contract to establish

Module 2 supplies `nodes[10]`, with character `data` and integer `left`
and `right` IDs. Module 12 adds a separate `height[10]`. A missing link
or empty root is -1; missing height is -1 and leaf height is 0. IDs, data,
and heights are three different quantities.

`_add(root,id)` inserts an existing fresh ID with two -1 child links.
Save its return value with `root = _add(root,id)`. The routine assumes a
valid AVL input and valid IDs, does no allocation, and supplies no error
statuses, duplicate rejection, search function, or capacity guard.

Equality descends left through `<=`, but a rotation may place equal keys
on either side. The lasting ordering rule is nondecreasing inorder, with
left-region keys `<=` the current key and right-region keys `>=` it.
Do not import the optional library's unique-key rule into the required lab.

## Board walkthrough

Use stable IDs A=0, B=1, ..., G=6. Inserting C, A, B produces LR:

```text
       C                      B(h1)
      /                      /     \
     A          ->        A(h0)    C(h0)
      \
       B
```

The caller captures both inner child IDs before calling
`rotate_lr(i,l,lr,lrl,lrr)`. The helper directly rewires the four links;
it does not call two single-rotation helpers or refresh heights. `_add`
then refreshes the two lower nodes i and l before the promoted node lr.

| Input | Case | Height refresh order |
| --- | --- | --- |
| C B A | LL | i, l |
| A B C | RR | i, r |
| C A B | LR | i, l, lr |
| A C B | RL | i, r, rl |

Every result is root ID1 B, left ID0 A, right ID2 C, with heights 1/0/0.
Explain why the recursive return may replace a child root and why the
chained assignment updates both the actual link and the local l/r cache.

## Compare the same seven labels

| Arrival order | Plain height | Plain present/missing counts | AVL root/height/counts |
| --- | ---: | --- | --- |
| A B C D E F G | 6 | G/H: 7/7 | D / 2 / 3,3 |
| G F E D C B A | 6 | A/@: 7/7 | D / 2 / 3,3 |
| D B F A C E G | 2 | G/H: 3/3 | D / 2 / 3,3 |

The driver supplies plain insertion, lookup, independent height
measurement, and validation. They are not exported by the lab. The final
AVL links are D(B(A,C),F(E,G)). Missing @ sorts before A and H after G in
the lab builds. Count one comparison per visited record, not per missing
link.

## Questions that expose understanding

- What changes in the arrays during a rotation, and what stays in its slot?
- Why is `get_height(-1)` safe while `height[-1]` is not?
- Which saved middle ID would become unreachable if a link were overwritten?
- Why must demoted nodes have their heights refreshed before the new root?
- What happens to three fresh IDs that all hold B?
- Why can a test with an empty middle subtree miss a broken rotation?

Use `F D G B E A` for a concrete LL repair with retained middle E. The
result is D(B(A,-1),F(E,G)); D has height 2, B/F height 1, leaves height 0.

## Assessment and limits

Require three original test groups: rotation/metadata, order/measurement,
and duplicate/valid-boundary behavior. Check exact links, reachability,
nondecreasing inorder, independently derived heights, and balance after
insertion. The capacity is ten distinct IDs; invalid IDs and repeated live
IDs are outside the source contract, not expected rejection tests.

For a generalized tree, insertion and lookup take O(h), each rotation
O(1), and AVL height gives O(log n) operation cost. The ten-slot lab is
fixed in size. A visit-once diagnostic scan takes O(n) and belongs outside
the insertion measurement.

Sorted valid arrival order can force linear plain-BST work. AVL repairs
this shape-based slowdown; it does not provide input validation or prove
system-wide security. A lost array link loses reachability, not allocated
heap storage. The retained 64-node pointer API and actual leak autopsy
are separate optional references.
