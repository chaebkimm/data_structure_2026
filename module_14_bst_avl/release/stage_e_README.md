# Module 14 - Stage E: Lab and Evidence

Start with `student/lab.md`, then edit only:

- the three numbered `TODO` clusters across
  `code/starter/avl_rotations.c` and `code/starter/avl_tree.c`; and
- the three `TODO` test categories in `code/tests/test_student.c`.

`TODO` marks an unfinished section that the student must complete.

Students complete:

1. link-preserving left and right rotations with bottom-up height repair;
2. LL, RR, LR, and RL rebalance selection; and
3. bounded AVL insertion with strict duplicate rejection and failure
   preservation.

The supplied BST baseline, tree support, public headers, and core tests must
not be changed. The maximum live size is 64. A null link has edge-height
`-1`, a leaf has edge-height `0`, and balance factor is left height minus
right height. Valid AVL factors are `-1`, `0`, and `1`.

Use the canonical rotation triples:

```text
LL: 30, 20, 10    RR: 10, 20, 30
LR: 30, 10, 20    RL: 10, 30, 20
```

All four finish with root 20, children 10 and 30, root height 1, and leaf
heights 0.

The exact 15-key experiment compares ascending, descending, and the supplied
mixed order. Plain ascending and descending BSTs have edge-height 14 and
take 15 comparisons for the listed deepest and missing searches. The mixed
BST and all three AVL results have edge-height 3 and take 4 comparisons for
the listed searches.

The autopsy - a careful investigation after a failure - contains an actual
faulty left-rotation branch that can lose an owned subtree. It is compiled
separately and never linked into normal tests. The ordinary target defines
`AUTOPSY_INSPECT_ONLY` and runs a safe inspection. The unsafe target requires
sanitizers, compiles the actual defect, prints its path, and deliberately
does not run it.

Full AVL deletion is not part of this lab. Submit the files and evidence
listed in the lab, then complete `student/evidence_template.md`.
