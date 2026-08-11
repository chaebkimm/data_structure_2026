# Module 13 - Stage E: Lab and Evidence

Start with `student/lab.md`, then edit only:

- the three numbered `TODO` clusters in `code/starter/hash_table.c`; and
- the three `TODO` test categories in `code/tests/test_student.c`.

`TODO` marks an unfinished section that the student must complete. Do not
change the public header or supplied core tests merely to make a test pass.

Students complete:

1. bounded lookup and probing with wraparound, empty-stop, deleted-slot
   continuation, and output-last behavior;
2. insertion, update, and deletion with first-tombstone memory, unique keys,
   exact count changes, and failure preservation; and
3. transactional same-capacity compaction or geometric growth that reinserts
   only occupied entries before commit.

The table maps `uint32_t` keys to `int` values. Key 0 and `UINT32_MAX` are
legal because state is separate from key data. Active capacities are 8, 16,
32, or 64. The home slot is `key % capacity`; every requested-key probe is
bounded by the current capacity.

The autopsy is a careful investigation after a failure. Its isolated,
memory-safe program changes a removed occupied slot directly to `EMPTY`, so
a later colliding key becomes unreachable. It compiles and runs as a
separate executable and is never linked into normal tests.

Expected constant-time operations require an adequately distributed hash
and controlled load. A collision cluster can still require linear work.
The teaching hash is not cryptographic and does not authenticate records.

Submit the files and evidence listed in the lab, then complete
`student/evidence_template.md` and `student/hash_table_autopsy.md`.
