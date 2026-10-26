# Module 09 staged release manifest

The required release follows `student/lab.c`: ten buckets, index-linked
collision chains, the Module 07 node pool, and brute-force/hash-based two sum.
It contains supplied functions for tracing and testing, with no implementation
TODOs. The older open-addressed library stays an optional repository reference.

Run from the repository root:

```sh
python3 module_09_hash_table/release/prepare_student_release.py
```

PowerShell users may run `release/prepare_student_release.ps1`; it calls the
same Python 3 packager. `--output-dir PATH` selects a separate output folder.
Existing archive names are never overwritten. All sources are read and ZIP
entries verified byte for byte before publication; fixed timestamps make
repeated packaging reproducible. A write failure removes files created in
that attempt. SHA-256 hashes are printed.

## Stage contents and timing

| Archive | Entries | Release after |
| --- | ---: | --- |
| `module_09_stage_a_initial_inquiry.zip` | 3 | Before Meeting A |
| `module_09_stage_b_representation_pause.zip` | 4 | Initial predictions are preserved |
| `module_09_stage_c_investigation.zip` | 3 | Three-target pause and comparison |
| `module_09_stage_d_textbook_models.zip` | 3 | Investigation core is preserved |
| `module_09_stage_e_lab.zip` | 12 | Retrieval and textbook calibration |

Each archive has its stage README at the root. Material retains the
`module_09_hash_table/student/` and `diagrams/` paths. Extract successive
stages into a common parent directory; the stage README may be replaced.
Standard and linear prompts use identical fixtures and tasks. The packager
checks Stage A for early implementation names and executable code fences. Plain text diagrams are allowed.

Stage E contains five student files (`lab.c`, `lab.md`, evidence, rubric,
and source-based autopsy), two test drivers, three student build/guide
files, its README, and the exact
`module_07_linked_list/student/lab.c` dependency. Its two module directories
must stay siblings. The compiler uses the extracted root as an include path.

Instructor notes, completed answers, the old public map header,
starter/solution library, map tests, deletion demo, and generated binaries
are excluded. There is no fixed total source-file inventory: releases use
an explicit allowlist in `prepare_student_release.py`.

## Verify before release

Run `make -C module_09_hash_table/code lab-compile core student-tests`.
Check normalized negative hashes, prepended collision chains, raw payload
lookup, pool exhaustion and unchanged failure state, disjoint active/free
chains, reset and reuse, and two-sum success/miss/repeated runs. Include a
single-occurrence self-pair trap and a duplicate-value pair. Compare valid
pair existence rather than requiring the two algorithms to choose the same
second index. Use sanitizers where supported. Record inherited compiler
warnings separately from failed assertions.

Package to a temporary output directory, compare entries against the
allowlist and source bytes, extract Stage E, and build it independently.
A second run must reject the existing archives without changing their hashes.
