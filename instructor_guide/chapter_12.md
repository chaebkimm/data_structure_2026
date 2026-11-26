# Chapter 12. Binary Search and BSTs

See the [Module 12 overview](../module_12_binary_search/README.md) and [delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md). Use the [search textbook](../module_12_binary_search/student/textbook.md) for sorted-array examples.

## Starting question and goals

> What rule lets one comparison eliminate several candidates, and can an
> ordered tree still make us inspect every node?

Students explain sorted-input interval elimination, trace first-match binary
search, state BST ordering, trace ordinary search/insertion, connect inorder
to nondecreasing keys, and measure the effect of tree height on lookup.

## Teaching outline

1. Retrieve linear search with `[31,23,17,8,17,42]`: the first 17 is at index 2.
2. Supply `[8,17,17,23,31,42]` already sorted. Trace the half-open candidate
   interval to the first 17 at index 1; include a miss and an empty input.
   The returned position belongs to the current array. Do not teach a sorting
   implementation as a prerequisite.
3. Transfer the smaller/larger decision to indexed binary-tree links. Use the
   plain-BST search and insertion rules to predict each path.
4. Compare `ABCDEFG`, `GFEDCBA`, and `DBFACEG`, using A=0 through G=6.
   Preserve ordering/reachability and explain inorder. Their plain-BST edge
   heights are 6, 6, and 2. Count one logical comparison per visited node.
5. Explain `O(h + 1)` search work and why a chain can require `O(n)` work.
   Finish with the ascending-order chain and carry the repair question into
   Chapter 13. There students insert the same ordered keys into a left-leaning red–black tree.

## Time and assessment outline

| Required contact activity | Minutes |
|---|---:|
| Linear-search recap and first-match binary search on supplied sorted arrays | 45 |
| BST ordering, search, insertion, and inorder reasoning | 60 |
| Height, insertion-order effects, and search costs; finish with a skewed tree | 35 |
| Traces, checks, and one combined evidence artifact | 40 |
| **Total** | **180** |

One submission combines interval and BST search/insertion traces, original
checks, inorder/height/comparison evidence, and a corrected prediction.
Include duplicate first-match search, misses, empty/singleton cases, and
valid indexed-node boundaries. Use the supplied baseline's duplicate rule;
first-match array indices are not a new tree duplicate-rejection contract.
BST deletion and sorting implementations are outside required scope.

## Final check

> Why does binary search on a sorted array have short search paths, while
> a BST holding the same ordered keys can still require a long path?

The answer must distinguish array midpoint access from shape-dependent tree
links. A BST ordering invariant alone does not guarantee balanced height.
Week 13 compares that chain with a left-leaning red–black tree built from the same arrival order.
