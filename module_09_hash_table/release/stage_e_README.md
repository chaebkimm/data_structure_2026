# Module 09 — Stage E: Lab and Evidence

Read `module_09_hash_table/student/lab.md`. Trace the supplied implementation
and extend `module_09_hash_table/code/tests/test_lab_student.c` with three
original test groups. Submit one driver and its evidence.

Keep these sibling directories together:

- `module_09_hash_table/` contains the lab, instructions, and test drivers.
- `module_07_linked_list/student/lab.c` supplies the exact node pool included
  by the lab. It is a dependency, not a second assignment.

From the extracted root:

```sh
make -C module_09_hash_table/code lab-compile core student-tests
```

The root include path is required. Compile a driver once; do not separately
compile either included source. Call `init_lnodes_pool()` before first use and
recycle active bucket chains with `init_hashtable()` between experiments.
The old open-addressed map and deletion demo are not in this release.
