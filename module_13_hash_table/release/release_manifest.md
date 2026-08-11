# Module 13 Staged Release Manifest

Run `prepare_student_release.ps1` from this directory to create five ZIP
archives in `../dist`. The script validates the complete source inventory,
refuses to overwrite any existing archive, writes fixed-timestamp temporary
archives, verifies their entries, commits the set transactionally, and
prints SHA-256 hashes.

## Stage A - Sparse Records in Eight Spots

Release before Meeting A:

- standard initial prompt;
- linear accessible initial prompt.

All three Stage A files use ordinary ID, record, row, spot, remainder,
route, removal, and search language. They contain no formal structure name,
implementation vocabulary, code, complexity notation, completed answer,
solution, or instructor material.

## Stage B - Representation and Cognitive Pause

Release after initial models are preserved:

- representation reveal;
- exactly-three-target Cognitive Pause;
- vocabulary reference.

The vocabulary file remains closed until the pause response is preserved.
Approved extended-time or asynchronous versions use the same three targets.

## Stage C - Hash-Table Investigation

Release after the pause and reference-model comparison:

- standard investigation worksheet;
- linear accessible investigation worksheet.

Both forms preserve identical keys, values, capacities, traces, maintenance
decisions, questions, and scoring. They supply questions, not the answer key.

## Stage D - Beginner Textbook and Models

Release after the student completes and preserves the Stage C core:

- an example-first beginner textbook; and
- diagrams with exact collision, wraparound, deletion, lookup, insertion,
  compaction, growth, validation, and cost linear equivalents.

## Stage E - Lab and Evidence

Release after retrieval and Stage D calibration in Meeting B. Its 14 entries
are exactly:

- lab, evidence template, rubric, and Hash-Table Autopsy;
- the public hash-table header;
- the single starter implementation;
- visible core tests and the student-test template;
- student-only PowerShell and GNU Make build files plus the student code
  guide; and
- the isolated autopsy guide and safe `faulty_delete_empty.c` program.

The public contract uses `uint32_t` keys, `int` values, capacities 8 through
64 by powers of two, three explicit slot states, linear probing, a
three-quarter effective-occupancy threshold, transactional maintenance, and
bounded probes. A destroyed table is the all-zero state.

Stage E excludes:

- `instructor/`;
- `code/solution/hash_table.c`;
- `code/tests/test_extension.c`;
- instructor build files, solution targets, and extension targets;
- answer keys and completed TODOs;
- Stages A through D;
- unrelated linked-list, tree, graph, and minimum-spanning-tree code;
- live host or network input, file clients, and network clients; and
- generated binaries, build directories, partial archives, and any unsafe
  memory-fault demonstration.

The Stage E autopsy contains a logical deletion defect, not an invalid
memory access. It compiles as a standalone executable and is never linked
into a core or student-test target.

## Stage A embargo

The preparation script scans all three Stage A files case-insensitively for
formal terms and variants, including:

```text
array, map, key, slot, capacity,
hash, hash function, collision, open addressing, linear probing,
probe, load factor, tombstone, rehash, compaction,
HASH_SLOT_EMPTY, HASH_SLOT_OCCUPIED, HASH_SLOT_DELETED,
algorithm, invariant, validator, complexity, Big-O,
allocation, calloc, malloc, free, pointer, struct,
code, API, TODO, pseudocode, status,
solution, answer key, instructor,
denial of service, DoS, attacker, cryptographic
```

It also rejects `O(...)` forms and fenced code or text blocks. The standard
and linear prompts must preserve identical IDs, values, questions, and
scoring.

## Archive inventory

The five archives contain exactly:

```text
module_13_stage_a_initial_inquiry.zip       3 entries
module_13_stage_b_representation_pause.zip 4 entries
module_13_stage_c_investigation.zip         3 entries
module_13_stage_d_textbook_models.zip       3 entries
module_13_stage_e_lab.zip                  14 entries
```

The source package contains exactly 38 files before `dist`: 26 Markdown, 3
PowerShell, 2 Makefiles, 6 C files, and 1 header. `code/build/` is generated
and excluded from that source inventory.

## Instructor verification

Before release:

- build reference core tests, instructor extensions, student tests, and the
  isolated safe autopsy using the commands in `../code/README.md`;
- use strict C11 warnings and sanitizers where the installed compiler
  supports them;
- verify key 0 and `UINT32_MAX`, collisions, wraparound, misses, updates,
  deletion reachability, tombstone reuse, compaction, growth, and full-table
  behavior;
- verify invalid arguments, invalid state, allocation failure, and growth
  failure preserve the required state and caller outputs;
- verify every probe is capacity-bounded and every public result is
  published only after success;
- verify the full validator accepts canonical states and rejects isolated
  state, count, duplicate-key, unreachable-key, and malformed-slot faults;
- confirm exactly three implementation TODO clusters and three student-test
  TODO categories;
- confirm exactly three Cognitive Pause targets;
- confirm the archive entry counts are 3, 4, 3, 3, and 14;
- compare every ZIP entry byte-for-byte with its listed source file;
- confirm Stage E contains none of its excluded material; and
- confirm a second packaging attempt is rejected without changing archive
  hashes or leaving a partial file.
