# Module 14 Diagram and Linear-Text Models

Every visual below is followed by an exact linear description containing
the same labels, links, and values.

## Model 1 - Balanced three-key BST

```text
    20(h=1)
    /     \
10(h=0) 30(h=0)
```

### Linear equivalent

- root: key 20, stored height 1
- root left child: key 10, stored height 0
- root right child: key 30, stored height 0
- key 10 has no children
- key 30 has no children

## Model 2 - Ascending plain BST

```text
1 -right-> 2 -right-> 3 -right-> 4 -right-> 5
  -right-> 6 -right-> 7 -right-> 8 -right-> 9
  -right-> 10 -right-> 11 -right-> 12 -right-> 13
  -right-> 14 -right-> 15
Every left link is NULL. Key 15 has two NULL links.
```

### Linear equivalent

- root key: 1
- for every key `k` from 1 through 14, the right child is `k+1`
- every left child is `NULL`
- key 15 has no children

### Measurement note

The edge height is 14. A deepest or suitable missing search makes 15
comparisons.

## Model 3 - Descending plain BST

```text
15 -left-> 14 -left-> 13 -left-> 12 -left-> 11
   -left-> 10 -left-> 9 -left-> 8 -left-> 7
   -left-> 6 -left-> 5 -left-> 4 -left-> 3
   -left-> 2 -left-> 1
Every right link is NULL. Key 1 has two NULL links.
```

### Linear equivalent

- root key: 15
- for every key `k` from 15 down through 2, the left child is `k-1`
- every right child is `NULL`
- key 1 has no children

### Measurement note

The edge height is 14. A deepest or suitable missing search makes 15
comparisons.

## Model 4 - Fixed mixed order

```text
             8
        /         \
       4           12
     /   \       /    \
    2     6     10     14
   / \   / \    / \    / \
  1   3 5   7  9  11  13 15
```

### Linear equivalent

- root 8 has children 4 and 12
- 4 has children 2 and 6
- 12 has children 10 and 14
- 2 has children 1 and 3
- 6 has children 5 and 7
- 10 has children 9 and 11
- 14 has children 13 and 15
- keys 1, 3, 5, 7, 9, 11, 13, and 15 have no children

### Measurement note

The edge height is 3. A deepest or suitable missing search makes four
comparisons.

## Model 5 - LL and right rotation

```text
before:       30        after:      20
              /                    /  \
             20                   10  30
             /
            10
```

### Linear equivalent

- before root: 30; its left child is 20; 20's left child is 10
- after root: 20; its left child is 10; its right child is 30

### Repair note

Use one right rotation at 30. Afterward, 20 has height 1; 10 and 30 have
height 0. Inorder before and after is 10, 20, 30.

## Model 6 - RR and left rotation

```text
before: 10              after:      20
          \                        /  \
           20                     10  30
             \
              30
```

### Linear equivalent

- before root: 10; its right child is 20; 20's right child is 30
- after root: 20; its left child is 10; its right child is 30

### Repair note

Use one left rotation at 10. Afterward, 20 has height 1; 10 and 30 have
height 0. Inorder before and after is 10, 20, 30.

## Model 7 - LR and RL

```text
LR before: 30       RL before: 10       both after: 20
           /                    \                  /  \
          10                     30               10  30
            \                   /
             20                20
```

### Linear equivalent

- LR insertion order: 30, 10, 20
- RL insertion order: 10, 30, 20
- both after states: root 20, left child 10, right child 30

### Repair note

LR uses a left rotation at 10, then a right rotation at 30. RL uses a right
rotation at 30, then a left rotation at 10. Both have heights 1 at 20 and 0
at 10/30. Inorder before and after is 10, 20, 30.

## Model 8 - Middle subtree during a left rotation

```text
before:
        X
       / \
      L   Y
         / \
        M   R

after:
        Y
       / \
      X   R
     / \
    L   M
```

### Linear equivalent

- before: X is the local root
- before: X's left subtree is L and right child is Y
- before: Y's left subtree is M and right subtree is R
- after: Y is the local root
- after: Y's left child is X and right subtree is R
- after: X's left subtree is L and right subtree is M
- inorder grouping before and after: L, X, M, Y, R

### Ownership note

Save M before overwriting a link. Then every allocation represented by L,
X, M, Y, and R remains reachable.

## Model 9 - Balance-factor examples

```text
factor = left height - right height
allowed AVL factors: -1, 0, 1
repair required: factor <= -2 or factor >= 2
```

### Linear equivalent

- balance factor equals left-subtree height minus right-subtree height
- AVL permits factor -1
- AVL permits factor 0
- AVL permits factor 1
- a factor at most -2 requires repair
- a factor at least 2 requires repair

## Model 10 - Heap and AVL contrast

```text
Heap:
- each parent precedes its children by priority
- left and right subtrees are not fully ordered

AVL:
- every left-subtree key is smaller than its node key
- every right-subtree key is larger than its node key
- every balance factor is -1, 0, or 1
```

### Linear equivalent

- a binary Heap requires each parent to precede its children by priority
- a binary Heap does not fully order left and right subtrees
- an AVL tree requires every left-subtree key smaller than its node key
- an AVL tree requires every right-subtree key larger than its node key
- an AVL tree also requires each balance factor to be -1, 0, or 1
