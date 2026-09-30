# Stage B - Representation Reveal: From Sparse IDs to a Hash Table

Open this file only after preserving the Stage A inquiry.

## 1. Name the public behavior

A **map** is an abstract data type that associates each unique **key** with
one **value**. This module's synthetic indicator index maps a `uint32_t` key,
an unsigned 32-bit whole number, to one C `int` value.

- `put(key, value)` inserts a missing key or updates the one existing key.
- `get(key)` reports whether the key exists and, when it does, its value.
- `remove(key)` reports whether the key existed and removes it when present.

Those behaviors do not require one storage representation. A **hash table**
is the representation used here.

## 2. Calculate a home slot

A **hash function** is a repeatable calculation from key to starting
position. That starting position is the **home slot**. A **bucket** is one
possible hash-selected starting location; in this module each bucket is one
array slot. The course uses a deliberately simple teaching function:

```text
home = key % capacity
```

The `%` operator gives the remainder after whole-number division. At
capacity 8, key 10 has home 2 because `10 % 8 == 2`. Keys 18 and 26 also
have home 2.

Using a small array avoids reserving one position for every possible
`uint32_t` value. Different keys can receive the same home. That event is a
**collision**. A collision is expected table behavior, not evidence of
corruption.

## 3. Resolve a collision by probing

This table uses **open addressing**: every live key/value pair is stored
inside the main slot array. It uses **linear probing**: inspect the home slot,
then each following slot. After the final position, continue at 0.

At capacity 8, inserting 10, 18, and 26 in that order produces:

```text
index       0  1  2   3   4   5  6  7
state       E  E  O   O   O   E  E  E
key               10  18  26
```

The probe routes are `2`; `2,3`; and `2,3,4`. A bounded probe never examines
more than `capacity` slots. This bound prevents an infinite loop when no
never-used slot remains.

## 4. Give every slot one explicit state

Each `HashSlot` has a key, value, and one state:

- `HASH_SLOT_EMPTY`: never occupied since the most recent rehash;
- `HASH_SLOT_OCCUPIED`: contains one live key/value pair; or
- `HASH_SLOT_DELETED`: used earlier, but no longer live.

Empty and deleted slots use canonical key 0 and value 0. Occupied key 0 is
still legal because the separate state field marks whether a record is live.

After removing 18 from the three-key table, index 3 must become `DELETED`,
not `EMPTY`:

```text
index       0  1  2   3   4   5  6  7
state       E  E  O   D   O   E  E  E
key               10      26
```

An `EMPTY` slot proves that the key was not placed farther along this probe
route. A `DELETED` slot cannot prove that. Therefore lookup for 26 examines
2, 3, and 4. Lookup for missing 34 examines 2, 3, 4, and empty slot 5.

## 5. Update before reusing a deleted slot

While inserting, remember the first deleted slot but keep probing. Stop only
when one of these conditions occurs:

1. the key is found -- update its existing value;
2. an empty slot is found -- insert into the remembered deleted slot, or the
   empty slot when no deleted slot was seen; or
3. `capacity` slots have been inspected -- use the remembered deleted slot
   if one exists, otherwise report full.

This order matters. In the state above, `put(26, new_value)` must pass index
3 and update index 4. Inserting immediately at the first deleted slot would
create a second key 26 and violate unique-key map behavior.

## 6. Rebuild before effective occupancy becomes too high

The **load factor** is live size divided by capacity. Deleted markers also
lengthen probes. After the key search, insertion considers the selected
slot. Reusing `DELETED` increases size and decreases tombstones, so effective
occupancy does not change. Inserting into `EMPTY` proposes:

```text
size + tombstones + 1
```

If that proposed count exceeds three quarters of capacity, maintenance
occurs before a distinct key is committed.

- If `size + 1` still fits within three quarters, rebuild at the same
  capacity. This **compaction** removes tombstones.
- Otherwise rebuild at the next capacity: 8 to 16, 16 to 32, or 32 to 64.
- If a distinct insertion would require growth beyond 64, report
  `HASH_TABLE_FULL` without changing the table.

Rebuilding is **rehashing** because each occupied key's home is calculated
using the replacement capacity. Copy only occupied entries. Deleted markers
are not records.

Rehashing is transactional. Allocate and fill a complete replacement first,
checking each bounded internal placement. Only then replace the old array;
ordinary maintenance does not call the full public validator. If allocation fails, return
`HASH_TABLE_ALLOCATION` and preserve the old table exactly.

## 7. Connect the representation to C

The public structures use these ideas:

```c
typedef enum {
    HASH_SLOT_EMPTY = 0,
    HASH_SLOT_OCCUPIED,
    HASH_SLOT_DELETED
} HashSlotState;

typedef struct {
    uint32_t key;
    int value;
    HashSlotState state;
} HashSlot;

typedef struct {
    HashSlot *slots;
    size_t size;
    size_t tombstones;
    size_t capacity;
} HashTable;
```

`hash_table_init` accepts the canonical all-zero state and allocates eight
empty slots. `hash_table_destroy` releases the allocation and restores the
all-zero state. A live table must not be shallow-copied.

Each `put`, `get`, and `remove` result reports a Boolean outcome and the
number of slots examined for the requested key in the caller-visible table.
Internal rehash placement, including placement of a new requested key after
maintenance, is not added to that probe count. On any non-`OK` status, the
complete output result remains unchanged. A successful miss reports
`found == false` or `removed == false`, value 0, and the actual bounded probe
count.

Ordinary operations use constant-time checks for a supported active shape.
`hash_table_validate` is the explicit deeper scan for duplicate keys and
broken probe reachability; it is not part of normal operation cost.

## 8. State cost and security claims precisely

Let `n` be live entries and `m` be capacity. With adequately distributed keys
and controlled occupancy, exact lookup, insertion, and removal have expected
`O(1)` requested-key probe work. Expected means under stated distribution
assumptions; it is not a guarantee for each request. A long cluster can force
`O(m)` probes. Because the table does not shrink and may retain tombstones,
that is not always `O(n)`.

A rebuild scans `m` old slots and reinserts `n` live entries. It is expected
`O(m)`, worst `O(m + n^2)`, and bounded by `O(m^2)`. At a growth event,
`m = Theta(n)`, meaning capacity and live count differ only by constant
factors; this gives expected `O(n)` and worst `O(n^2)`. Geometric
growth spreads expected rebuild cost across an insertion-only sequence.
Deletion/insertion churn can cause repeated same-capacity compactions, so the
growth amortization does not cover every mixed sequence.

An **AVL tree** is an ordered binary search tree that repairs its height, so
exact lookup has logarithmic worst-case work and keys remain available in
sorted order. **Separate chaining** keeps a collision collection, often a
linked list, outside each bucket instead of probing one shared slot array.

Structure choice depends on requirements:

- direct indexing gives worst-case constant lookup when the key universe is
  small and dense, but can waste space for sparse keys;
- an AVL tree provides worst-case `O(log n)` lookup plus sorted traversal and
  range queries;
- separate chaining keeps a collection, often a linked list, at each bucket
  instead of using deleted markers in one array; and
- this open-addressed table offers expected constant-time exact lookup but no
  sorted iteration promise.

Chosen colliding keys can create hash-flood algorithmic-complexity denial of
service when the excess work delays intended service. This course's
transparent remainder function is not cryptographic. The table does not
authenticate indicators, prove authorization, hide keys, or establish
overall security.
