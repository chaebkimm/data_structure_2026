# Module 13 Diagram and Linear-Text Models

Every visual below is followed by an exact linear description containing the
same indexes, states, keys, values, and routes.

## Model 1 - Sparse direct indexing versus eight slots

```text
possible key positions: 0 ... 10 ... 18 ... 26 ... UINT32_MAX
live records:                K10   K18   K26

compact table indexes: 0 1 2 3 4 5 6 7
```

### Linear equivalent

- possible keys cover every `uint32_t` value from 0 through `UINT32_MAX`
- only keys 10, 18, and 26 are live
- direct indexing would reserve positions through the key universe
- the course table initially owns only indexes 0 through 7

### Selection note

Direct indexing is attractive for a small dense universe. Hashing reduces
storage for sparse keys but introduces collision handling.

## Model 2 - The three slot states

```text
E: EMPTY       no live record; stops an unsuccessful search
O: OCCUPIED    contains one live key/value pair
D: DELETED     no live record; search must continue
```

### Linear equivalent

- `HASH_SLOT_EMPTY` contains no live record and terminates a miss
- `HASH_SLOT_OCCUPIED` contains exactly one live key/value pair
- `HASH_SLOT_DELETED` contains no live record but preserves a probe route
- empty and deleted are not interchangeable

## Model 3 - Canonical collision cluster

```text
capacity 8; home = key % 8

index       0  1  2       3       4       5  6  7
state       E  E  O       O       O       E  E  E
record            10:100  18:180  26:260

put10 route: 2
put18 route: 2,3
put26 route: 2,3,4
```

### Linear equivalent

- index 0 empty
- index 1 empty
- index 2 occupied by key 10, value 100
- index 3 occupied by key 18, value 180
- index 4 occupied by key 26, value 260
- indexes 5, 6, and 7 empty
- all three keys have home 2
- insertion routes are 2; then 2,3; then 2,3,4

## Model 4 - Present and missing searches

```text
get26: 2(O key10) -> 3(O key18) -> 4(O key26 FOUND)
get34: 2(O key10) -> 3(O key18) -> 4(O key26) -> 5(E STOP)
```

### Linear equivalent

- get key 26 inspects indexes 2, 3, and 4
- its result is found true, value 260, probe count 3
- get key 34 inspects indexes 2, 3, 4, and 5
- its result is found false, value 0, probe count 4
- empty index 5 proves key 34 is absent

## Model 5 - Correct deletion preserves reachability

```text
before remove18: E E O10 O18 O26 E E E
after remove18:  E E O10 D   O26 E E E

get26 after: 2(O10) -> 3(D continue) -> 4(O26 FOUND)
```

### Linear equivalent

- before removal, keys 10, 18, and 26 occupy indexes 2, 3, and 4
- successful remove 18 reports value 180 and probe count 2
- after removal, index 3 is deleted, size is 2, and tombstones is 1
- get 26 still follows indexes 2, 3, and 4
- changing index 3 to empty would cause a false miss

## Model 6 - Remember a tombstone but search for the key

```text
state: 2=O10, 3=D, 4=O26, 5=E

put26/999:
  inspect 2, remember 3, find key26 at 4, update index4

put34/340:
  inspect 2, remember 3, pass 4, reach empty 5, insert at 3
```

### Linear equivalent

- both requested keys have home index 2
- put 26 inspects 2, 3, and 4, reports inserted false, and changes only the
  value at index 4 to 999
- put 34 inspects 2, 3, 4, and 5, proves key 34 absent, and reuses index 3
- after put 34, size is 3 and tombstones is 0
- committing at the first deleted slot before completing the key search can
  create a duplicate key

## Model 7 - Wraparound remains bounded

```text
capacity 8; all three homes are 7

index       0       1       2  3  4  5  6  7
state       O       O       E  E  E  E  E  O
record      15:150  23:230                 7:70

routes: 7; then 7,0; then 7,0,1
```

### Linear equivalent

- key 7 occupies index 7 after inspecting 7
- key 15 occupies index 0 after inspecting 7 and 0
- key 23 occupies index 1 after inspecting 7, 0, and 1
- modulo wraparound keeps every inspected index from 0 through 7
- the capacity-bounded loop permits at most eight inspections

## Model 8 - Same-capacity compaction

```text
before put8/80:
index       0  1  2       3  4       5  6  7
state       E  E  O       D  O       D  D  D
record            10:100     26:260
size 2, tombstones 4, effective occupancy 6

requested-key search: index0 E; probe count 1
proposed effective occupancy: 2 + 4 + 1 = 7 > 6

after compact-at-8 and insertion:
index       0     1  2       3       4  5  6  7
state       O     E  O       O       E  E  E  E
record      8:80     10:100  26:260
size 3, tombstones 0
```

### Linear equivalent

- before, keys 10 and 26 occupy indexes 2 and 4
- indexes 3, 5, 6, and 7 are deleted; indexes 0 and 1 are empty
- put key 8 inspects empty home 0 once in the caller-visible table
- proposed effective occupancy 7 exceeds the capacity-8 limit 6
- because live size after insertion is only 3, rebuild at capacity 8
- rehash key 10 to index 2 and key 26 to index 3
- internally place key 8 at index 0
- internal placements do not add to the public probe count 1
- final size is 3 and tombstones is 0

## Model 9 - Rehash from capacity 8 to 16

```text
old occupied order: key10, key18, key26

key10: 10 % 16 = 10 -> index10
key18: 18 % 16 = 2  -> index2
key26: 26 % 16 = 10 -> index11 after collision with key10
```

### Linear equivalent

- scan the old array by increasing old index
- key 10 has new home 10 and occupies 10
- key 18 has new home 2 and occupies 2
- key 26 has new home 10, finds key 10 at 10, and occupies 11
- only occupied records move
- deleted markers disappear
- the old allocation remains owned until every new placement succeeds

## Model 10 - Shallow shape versus full validation

```text
ordinary operation check, fixed fields only:
  slots nonnull; capacity supported; counts within 3/4 bound

explicit full validator, every slot/route:
  state valid; inactive fields zero; counts exact;
  occupied keys unique; each occupied key reachable before EMPTY
```

### Linear equivalent

- ordinary put, get, and remove use a constant-size check of public table
  fields before the requested-key route
- the constant-size check does not scan all slots
- the explicit validator checks every state and exact occupied/deleted count
- every empty and deleted slot must store key 0 and value 0
- no two occupied slots may contain the same key
- each occupied key must be reachable from its home without an earlier empty
- the full teaching validator may require `O(m^2)` work at capacity `m`

## Model 11 - Representation selection

```text
direct array: key is index; fast; space follows key universe
hash table: exact lookup; expected O(1); unordered; worst probe O(m)
AVL tree: ordered lookup/ranges; worst O(log n)
separate chaining: bucket plus linked collision collection
```

### Linear equivalent

- direct indexing suits small dense key universes
- this open-addressed table suits exact unordered lookup under suitable hash
  distribution and load assumptions; one requested-key route can inspect up
  to capacity `m`
- AVL supports sorted traversal and range queries with logarithmic worst-case
  search
- separate chaining resolves collisions outside the main slot array and does
  not need open-addressing tombstones
- no one representation proves record authenticity or overall security
