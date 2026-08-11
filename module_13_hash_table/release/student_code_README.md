# Module 13 Student Code

This directory is a self-contained bounded C lab. You do not need files or
compiled programs from another module.

Complete only the marked clusters in:

- `starter/hash_table.c`; and
- `tests/test_student.c`.

Do not change the public header or supplied core tests merely to make a test
pass. The starter contains exactly three numbered implementation clusters,
and the student-test file contains exactly three required test categories.

## Public model

The table maps one `uint32_t` key to one `int` value. A slot stores a key,
value, and one separate state:

```text
HASH_SLOT_EMPTY
HASH_SLOT_OCCUPIED
HASH_SLOT_DELETED
```

Key 0 and `UINT32_MAX` are legal. The state field, not a sentinel key,
decides whether a slot is active. Positive capacities are exactly 8, 16, 32,
or 64. The all-zero table is the canonical destroyed state.

Important public operations are:

- `hash_table_init`
- `hash_table_validate`
- `hash_table_put`
- `hash_table_get`
- `hash_table_remove`
- `hash_table_destroy`
- `hash_table_status_name`

Test builds also expose the one-shot allocation-failure hook and live
allocation count declared under `HASH_TABLE_TESTING`.

## Probing and deletion

The home slot is:

```text
key % capacity
```

Linear probing examines the home slot, then each next slot, wrapping to zero.
Every search stops after at most `capacity` inspections. A miss may stop at
the first `EMPTY` slot, but it must continue past `DELETED`.

When inserting, remember the first deleted slot but continue until the key,
an empty slot, or the capacity bound is reached. This prevents a duplicate
key from being inserted before an existing copy later in the probe chain.

Removing a present key writes `DELETED`, clears its stored key and value,
decreases `size` once, and increases `tombstones` once. A missing removal is
a successful no-change result.

## Maintenance and failure preservation

Before adding a distinct key, effective occupancy is:

```text
size + tombstones + 1
```

Maintenance is required when that value exceeds three quarters of capacity.
Compact at the same capacity when the live entries plus the new entry still
fit. Otherwise grow to the next supported capacity. Reinsert only occupied
entries into fresh zeroed storage.

Maintenance is transactional: fully populate the replacement with bounded
internal insertions, then commit it. Allocation failure, invalid input,
invalid state, or growth beyond 64 preserves the old table and caller
outputs as required by the header.

## Build and run

From this `code` directory, run public core tests:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
```

Run your three test categories:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -StudentTests
```

Compile and run the standalone safe autopsy:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

Add `-Sanitize` when the selected compiler supports sanitizers.

GNU Make users can run:

```text
make starter-core
make starter-student-tests
make autopsy
```

The autopsy changes a removed slot directly to `EMPTY`. It demonstrates a
logical reachability failure with bounded, valid memory accesses. It is
compiled alone and never linked into normal tests.

## Cost and scope

With an adequately distributed hash and controlled load, lookup, insertion,
and removal have expected constant-time probe work. With capacity `m`, a
collision cluster can force an ordinary operation to inspect `O(m)` slots.
With `n` live entries, rebuilding scans all `m` old slots and reinserts `n`
entries. It therefore takes expected `O(m + n) = O(m)` time under those same
assumptions, but worst-case `O(m + n^2)`, which is at most `O(m^2)` because
`n <= m`; it also needs `O(m)` fresh temporary storage. Only a growth rebuild
with no tombstones and the maintained load relationship simplifies to
expected `O(n)` and worst-case `O(n^2)`. The explicit full validator is an
`O(m^2)` diagnostic and is not hidden inside ordinary-operation cost claims.

The course hash is transparent for tracing. It is not cryptographic, does
not authenticate records, and does not prevent attacker-chosen collisions.

The starter is intentionally incomplete. A failed first core-test run is
expected. Fix the earliest failed requirement without weakening a test or
changing a supplied interface.
