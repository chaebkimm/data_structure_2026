# Module 5 Technical Notes

The public grammar is intentionally small:

```text
expression := digit | expression '+' expression | expression '*' expression
digit      := '0' through '9'
```

Digits must be leaves. Operators must have two children. The fixed
`NodePool` owns all nodes it supplies and can supply 100 nodes.

`tree_copy_preorder` is transactional with respect to the pool position and
output pointer. It rewinds `used` after any recursive failure. Old bytes in
rewound positions are irrelevant because the pool no longer considers those
positions active.

`tree_print_inorder` uses precedence 2 for `*`, 1 for `+`, and adds stricter
parentheses on a right operator of equal precedence. This preserves the exact
tree grouping even though `+` and `*` are associative mathematically.

`tree_evaluate_postorder` uses local candidates and commits only on success.
It rejects malformed shapes and checks positive integer addition and
multiplication for `INT_MAX` overflow.

The functions assume an acyclic, unshared tree. Cycle detection belongs to
the later graph DFS module.
