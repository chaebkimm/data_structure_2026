# Chapter 13. Left-leaning red–black trees

## Thinking logically

### Can we keep the same search and shorten the path?

Insert 10, 20, 30, 40, 50, 60, 70 into an empty ordinary BST. Each key after 10 becomes a right child. Finding 70 takes seven visits. We can keep one key per node and the smaller-left, larger-right search rule. What we need to change is the shape we leave behind after insertion.

### What does a red left link mean in a 2–3–4 tree?

Imagine storing 10 and 20 in the same group. Draw 20 above its left child 10 and color the link between them red. Read across that red link to get one group, `[10 | 20]`. A black link leads to a different group. A search for 10 still visits two binary nodes, first 20 and then 10.

These three snapshots come from inserting 10, 20, 30. R and B mark the color of the link into each key. The root is marked B.

```text
After inserting 10    After repairing 20    After attaching 30, before the flip

      10B                    20B                       20B
                            /                         /   \
                          10R                       10R   30R

     [10]                [10 | 20]               [10 | 20 | 30]
     2-node                3-node                    4-node
```

The names count the child ranges of an internal **2–3–4 tree** node. One key separates two ranges. Two keys separate three. Three keys separate four. For `[10 | 20 | 30]`, those ranges are below 10, between 10 and 20, between 20 and 30, and above 30. At a leaf these positions are empty.

A 2–3–4 tree can retain the 4-node. The bottom-up insertion used here splits it as soon as both child links are red. After the flip and root recoloring, `[20]` is the root with separate children `[10]` and `[30]`. The completed tree therefore contains only 2-nodes and 3-nodes when read in groups.

This binary representation with the bottom-up repair rule gives the **left-leaning red–black tree (LLRB)** used in this chapter. After each insertion, the root is black, every red link goes left, and a path never contains two red links in a row. Every path from the root to a missing child contains the same number of black keyed nodes. This count is the **black height** in this chapter. We include a black root and count a missing child as zero. Missing links are treated as black when testing colors.

### What if the second key lands on the right?

Insert 10, then 20. A new child enters on a red link so the insertion initially adds no black level. The new link points right. Lift 20, put 10 on its left, and give 20 the old root's color. This is a **left rotation**. The numbers are still in sorted order. The red left link after the rotation represents the 3-node `[10 | 20]`.

```text
Before repair           After rotating left at 10

   10B                          20B
      \                        /
      20R                    10R
```

The path from 20 directly to its missing right child contains one black key. So does the longer path through 10. The binary paths can have different lengths while their black counts agree.

### What if two keys arrive on the left?

Start a fresh tree with 30, 20, 10. After inserting 20 the red link already leans left. Inserting 10 creates two consecutive red links. A **right rotation** lifts 20. It inherits 30's color, and the old root becomes its red right child. Now 20 has two red children. A **color flip** turns those children black and passes red up to 20. At the end of insertion we color the root black.

```text
After attaching 10       Rotate right at 30       Flip at 20, then blacken root

       30B                      20B                         20B
       /                       /   \                       /   \
     20R                     10R   30R                   10B   30B
     /
   10R
```

Join both red links in the middle picture to read the 4-node `[10 | 20 | 30]`. A color flip splits this group. The two outer keys begin separate groups, and the middle key joins the group above through its incoming red link. Here the middle key is already at the root, so recoloring it black starts a new black level. Every child index stays in place during the flip.

### Where does the middle subtree go during a rotation?

Return to the ascending sequence. After inserting 40, the root is 20B and its right child is 40B with left child 30R. Insert 50 to the right of 40. Flip at 40, then rotate left at 20. Watch 30 during the rotation.

```text
After flipping at 40          After rotating left at 20

       20B                             40B
      /   \                          /    \
    10B   40R                      20R    50B
          / \                     /   \
        30B 50B                 10B   30B
```

The subtree rooted at 30 started on the left of 40. It becomes the right child of 20 because 20 < 30 < 40. Trace the lookup for 30 after the rotation. The path is 40, 20, 30. Looking for 35 visits the same keys and ends at 30's missing right child.

### How far can a color change travel?

Continue with 60 and 70. Inserting 60 produces a red right link from 50. Rotate left at 50. Now 60 has a red left child, 50. Inserting 70 gives 60 a second red child. Flip at 60. Its parent, 40, already has a red left child, 20. Flip again at 40 and color the root black. All seven keys are now black. This insertion raises the black height from two to three while the longest binary path still has two edges.

## Calculating efficiency

### Why does search stay short?

Search for 70 in the finished tree. It visits 40, 60, 70. The ordinary BST built from the same ordered input visits seven nodes. Both searches use only key comparisons and child links.

After insertion finishes, join each red link on paper. The resulting groups have one or two keys, and each internal group has at least two children. With b black levels, this needs at least 2^b − 1 keys. Thus b is at most log₂(n + 1) for n keys. Each group contributes at most two binary nodes on a path. A search visits at most 2b keyed nodes. An insertion follows one search path and does a fixed amount of repair per returning call. Worst-case search and insertion both take O(log(n + 1)) time. The recursive insertion uses O(log(n + 1)) stack space.

## Glossary

| Term | What to look for |
|---|---|
| Red link | Groups a child’s key with its parent’s key inside one 2–3–4 node |
| Black height | Count of black keyed nodes from the root to a missing child, using the convention above |
| Left rotation | Lift the right child. Its former left subtree becomes the old root's right subtree. |
| Right rotation | Lift the left child. Its former right subtree becomes the old root's left subtree. |
| Color flip | In this insertion algorithm, change two red children to black and their black parent to red. |

## Coding plan

1. Descend by ordinary BST comparisons. At a missing link, attach a red node.
2. On the return from each child, rotate left if only the right link is red.
3. On the resulting subtree, rotate right if the left link and the next left link are red.
4. On the resulting subtree, flip colors if both child links are red. Return the current subtree root to the caller. At the top, store the returned root and color it black.

## C code

In the [indexed node representation](../code/llrb.h), `left` and `right` hold node IDs. `NO_NODE` marks a missing link. The child's `red` field stores its incoming color. The first repair in [insert_at](../code/llrb.c) reads:

```c
if (is_red(tree, node->right) && !is_red(tree, node->left)) {
    id = rotate_left(tree, id);
    node = &tree->nodes[id];
}
```

The rotation returns the new subtree root. After inserting 50, failing to save that return would leave 20 where 40 belongs. The next two tests use the updated node. They run independently and in order, so a right rotation can be followed immediately by a flip.

The supplied set accepts up to 64 distinct integer keys. A duplicate or a full tree returns `false` and preserves the set. The [guided lab](lab.md) uses both insertion orders to check the colors, links, and search paths.
