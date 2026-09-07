# Tree DFS Models

## Running tree

```text
        *
       / \
      +   2
     / \
    3   5
```

## The three orders

```text
preorder copy:       *  +  3  5  2
inorder print:       3  +  5  *  2  -> (3+5)*2
postorder evaluate:  3  5  +  2  *  -> 16
```

## Active calls

```text
root *
└── left +
    └── left 3  <- current
```

The active frames form one root-to-current path. A balanced tree uses
`O(log n)` call space; a one-sided tree uses `O(n)`.
