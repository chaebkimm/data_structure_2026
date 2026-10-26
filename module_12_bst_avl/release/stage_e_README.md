# Module 12 — Stage E: Execute the Lab and Record Evidence

Start with [student/lab.md](../student/lab.md). The supplied
[student/lab.c](../student/lab.c) is complete. Write original assertions in
[code/tests/test_lab_student.c](../code/tests/test_lab_student.c), then
record results in the [evidence template](../student/evidence_template.md).
There are no required implementation TODOs.

The lab includes Module 2's exact `lab.c`, which this archive bundles at
`module_02_binary_tree/student/lab.c`. Keep that path intact. From the
archive root run:

```sh
make -C code lab-compile core student-tests comparison
```

See [code/README.md](../code/README.md) for compiler and PowerShell commands.
The drivers supply initialization, independent validation, a plain BST
baseline, and search-comparison measurement. They include the actual AVL
source once and do not link a second copy.

Use the canonical character triples:

```text
LL: C, B, A    RR: A, B, C
LR: C, A, B    RL: A, C, B
```

Every result has B above A and C, with root height 1 and leaf heights 0.
Use all seven characters A–G for ascending, descending, and mixed order
`D,B,F,A,C,E,G`. The sorted plain BSTs have edge-height 6; the mixed BST
and all three AVL results have edge-height 2. The model specifies the
present/missing search targets and exact comparisons.

Callers maintain valid node IDs, fresh child links `-1`, capacity ten, and
a valid starting AVL tree. Equal characters are accepted; rotations may
place an equal value on either side while preserving nondecreasing inorder
order. No allocation, deletion, duplicate rejection, or error-status API
is present. The written rotation autopsy examines lost index links without
requiring an unsafe program.

Submit the lab's traces, original tests and output, comparison, and evidence
as one Week 12 artifact.
