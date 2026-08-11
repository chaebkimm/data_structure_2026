# Student Textbook - Sparse Lookup with a Hash Table

## 1. Begin with map behavior

A key-to-value **map** answers a narrow question: given one key, is there a
record for it, and if so, what value belongs to it? This module uses
synthetic `uint32_t` indicator keys and `int` values.

The key is an identifier, not an array position promised by the public
interface. `put(18,-4)` associates key 18 with value -4. A later
`put(18,70)` updates that association. A valid map never contains two live
entries with key 18.

A map does not by itself promise sorted traversal, range queries, oldest-
first service, or smallest-value selection. Those are different contracts.

## 2. Compress a sparse key universe

Direct indexing uses the key itself as an array index. It is excellent when
keys are dense and have a small known maximum. A Boolean visited array for
graph vertex IDs 0 through 63 is a good example.

The largest `uint32_t` key is much greater than four billion. Reserving one
slot for each possible key is wasteful when only a few indicators are live.
A hash table owns a smaller array and calculates a starting location, called
the **home slot**.

The course calculation is:

```text
home = key % capacity
```

At capacity 8, `10 % 8`, `18 % 8`, and `26 % 8` all equal 2. Mapping a large
key universe to a small array means different keys can have the same home.
That **collision** is normal and requires a repeatable resolution rule.

## 3. Probe one array with wraparound

In **open addressing**, all live entries stay in the table's main array.
This module uses **linear probing**. Start at home. If the key is not there,
inspect the next slot. After the final index, wrap to 0.

Insert 10, 18, and 26 into a new capacity-8 table:

```text
10 examines 2 and occupies 2
18 examines 2,3 and occupies 3
26 examines 2,3,4 and occupies 4
```

For a requested key `k`, a convenient bounded index expression is:

```text
(home + step) % capacity
```

where `step` ranges from 0 through `capacity - 1`. The bound matters. A
malformed or unusually occupied table must not trap the program in an
infinite loop.

Keys 7, 15, and 23 show wraparound. All have home 7 at capacity 8, so they
occupy 7, 0, and 1. No access uses index 8.

## 4. Stop only when the state supplies evidence

Each slot has one state:

- `EMPTY`: never occupied since the most recent rehash;
- `OCCUPIED`: contains one live key/value pair; or
- `DELETED`: held a record earlier but no longer does.

To get a key, inspect up to capacity slots:

1. An occupied matching key means found.
2. An empty slot means missing.
3. An occupied different key or a deleted slot means continue.
4. Reaching the capacity bound means missing.

In the 10, 18, 26 cluster, get 26 examines 2, 3, 4. Missing get 34 examines
2, 3, 4, 5, including the empty slot that proves absence.

The result struct records the outcome, value, and number of inspected slots.
A successful miss has `found == false`, value 0, and its real probe count.
A non-`OK` status is different: the caller's entire result struct remains
unchanged.

## 5. Delete without cutting a route

Suppose removing key 18 changed index 3 to empty. A later get 26 would inspect
index 2, see empty index 3, and stop before reaching 26 at index 4. Every
access would be in bounds, but the answer would be wrong.

Correct removal changes occupied to deleted. It also clears the inactive
key/value fields to their canonical zeros, decreases size once, and increases
tombstones once. Get 26 then walks through the deleted marker.

A tombstone is a search instruction, not a live record. It preserves what
the slot history implies: some key may have passed this position during
insertion.

## 6. Search completely before reusing a tombstone

Insertion must support both new keys and updates. During a probe, remember
the first deleted slot, but do not commit there immediately.

With key 10 at 2, deleted at 3, key 26 at 4, and empty at 5:

- `put(26,999)` examines 2, 3, 4 and updates index 4. It reports
  `inserted == false`. Size and tombstones do not change.
- `put(34,340)` examines 2, 3, 4, 5. Empty 5 proves 34 absent, so the
  remembered index 3 may be reused. It reports `inserted == true`; size
  increases and tombstones decreases.

If the table has no empty slot, the probe still stops after capacity
inspections. It may use a remembered tombstone. If no insertion position
exists in a supposedly valid active table, the implementation reports an
invalid state rather than indexing an invalid position.

## 7. Control effective occupancy

Long clusters increase work. The table maintains nonempty-state count at no
more than three quarters of capacity:

```text
size + tombstones <= 3 * capacity / 4
```

After searching for a new key, consider the selected insertion slot.
Reusing deleted changes one deleted slot to occupied, so the sum does not
grow. Inserting into empty would increase the sum by one. If that proposal
exceeds the bound, maintenance occurs first.

When tombstones exist, rebuilding at the same capacity is enough because
only live entries return. This **compaction** clears all deleted markers. If
there are no tombstones, grow 8 to 16, 16 to 32, or 32 to 64. At capacity 64,
a distinct key that would cross the bound reports full. Searching happens
first, so an existing-key update is still allowed at the boundary.

## 8. Rehash transactionally

Changing capacity changes homes. Moving the old array bytes without
recalculating would break lookup. A rehash must:

1. allocate a zeroed replacement array;
2. scan old indexes in order;
3. internally insert each occupied entry using the new capacity;
4. insert the requested new record when maintenance belongs to a put;
5. commit pointer, size, tombstones, and capacity only after every bounded
   placement succeeds; and
6. release the old allocation after commit.

Deleted slots are not copied. Internal placements are maintenance work and
do not add to the requested key's caller-visible probe count.

If allocation fails, the old allocation remains the only committed table.
The public result is unchanged. Do not free or overwrite the old array before
the replacement is complete.

## 9. Separate shallow checks from full diagnosis

Ordinary put, get, and remove first perform constant-time shape checks: a
nonnull slot pointer, supported capacity, and counts within the maintained
bound. They do not run an expensive complete scan before every operation.

`hash_table_validate` is an explicit diagnostic. It checks:

- canonical all-zero destroyed state or a supported active shape;
- exact occupied and deleted counts;
- zero key/value fields in inactive slots;
- valid slot-state values;
- unique occupied keys; and
- reachability of every occupied slot from its home without crossing empty.

The straightforward course validator may compare entries and probe routes
with quadratic worst-case work. That does not change the expected cost of an
ordinary operation because the validator is called separately in tests and
debugging.

## 10. Make conditional cost and security claims

Let `n` mean live entries and `m` mean capacity. With adequately distributed
keys and the occupancy bound, get, put, and remove use expected `O(1)`
requested-key probes. A cluster can make one route inspect `O(m)` slots.
Because the table does not shrink and may retain deleted markers, `m` is not
always proportional to current live `n`.

Rehash scans `m` old slots and reinserts `n` live entries. It is expected
`O(m)`, worst `O(m + n^2)`, and therefore bounded by `O(m^2)`. At a growth
event `m = Theta(n)`, meaning capacity and live count differ only by constant
factors, so that becomes expected `O(n)` and worst `O(n^2)`.
Doubling spreads expected growth work across an insertion-only sequence,
producing expected amortized `O(1)` there under the same distribution
assumptions. Repeated deletion/insertion churn can trigger same-capacity
compaction repeatedly, so it has no unconditional constant amortized claim.

Compare alternatives:

- direct array: worst-case constant indexing, but space follows the key
  universe;
- open-addressed table: expected constant exact lookup and compact storage,
  but no sorted-order promise and linear worst case;
- AVL tree: worst-case logarithmic exact lookup plus sorted and range work;
- separate chaining: collision collections outside the main array, often
  linked nodes, with different allocation and locality costs.

If an attacker can choose many colliding keys, the resulting work can become
hash-flood algorithmic-complexity denial of service. The classroom trace is a
bounded demonstration, not proof that a resource has been exhausted. The
remainder calculation is intentionally transparent and non-cryptographic.
Neither it nor the validator authenticates indicators, proves authorization,
ensures availability, or establishes overall security.
