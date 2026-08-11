# Module 13 Vocabulary

- **Algorithmic-complexity denial of service:** valid attacker-chosen input
  causes an operation to perform far more work than intended.
- **Allocation:** storage reserved while a program runs.
- **Amortized cost:** the total cost of occasional expensive operations is
  spread across a sequence of operations.
- **AVL tree:** an ordered binary search tree that maintains a logarithmic
  height bound and supports sorted/range operations.
- **Bucket:** a possible starting location selected by a hash function. In
  this module, each bucket is one array slot.
- **Capacity:** the number of slots in the allocated array.
- **Collision:** two different keys have the same home slot.
- **Compaction:** rebuild a table at the same capacity so deleted markers
  disappear.
- **Cryptographic hash:** a hash designed for cryptographic properties. The
  transparent course hash is not one.
- **Deleted slot:** a slot that once held an entry and must not terminate a
  search through its collision cluster.
- **Direct indexing:** use a key itself as an array index.
- **Effective occupancy:** live entries plus deleted markers, including the
  proposed new entry when deciding whether maintenance is required.
- **Empty slot:** a slot that has never been occupied since the most recent
  rehash and therefore may terminate an unsuccessful search.
- **Expected cost:** average behavior under stated assumptions about inputs
  or distribution; it is not a guarantee for every operation.
- **Failure preservation:** a failed operation leaves the earlier valid state
  unchanged.
- **Hash function:** a repeatable computation that maps a key to a starting
  slot.
- **Hash-flooding:** supplying many keys that collide so table operations do
  much more work.
- **Hash table:** a key-to-value structure that uses a hash function and a
  collision rule.
- **Home slot:** the first slot selected for a key.
- **Invariant:** a rule that is true for every valid completed state.
- **Key:** the value used to identify and retrieve an entry.
- **Linear probing:** after a collision, inspect following slots one at a
  time and wrap at the array boundary.
- **Live entry:** an occupied key/value pair currently stored in the table.
- **Load factor:** live entry count divided by capacity.
- **Map:** an abstract data type associating each unique key with one value.
- **Occupied slot:** a slot currently holding one live key/value pair.
- **Open addressing:** store every entry inside the main slot array and
  resolve collisions by probing other slots.
- **Probe:** inspect one candidate slot during an operation.
- **Probe cluster:** occupied and deleted slots connected without an empty
  slot between them.
- **Rehash:** place every occupied entry into a fresh slot array using that
  array's capacity.
- **Separate chaining:** resolve collisions by keeping a collection, often a
  linked list, at each bucket.
- **Shallow copy:** copy an owning pointer without copying the owned
  allocation, creating conflicting apparent owners.
- **Slot:** one position in the table's array.
- **Sparse key space:** most possible key values are not currently present.
- **Status:** a named operation outcome.
- **`uint32_t`:** a C unsigned whole-number type with exactly 32 bits.
- **Tombstone:** another name for a deleted-slot marker.
- **Transactional update:** prepare a complete replacement first and commit
  it only after every fallible step succeeds.
- **Theta notation:** `m = Theta(n)` means `m` and `n` remain within constant
  factors of each other as they grow.
- **Value:** information associated with a key.
- **Validator:** a diagnostic operation that reports whether representation
  rules hold.
- **Worst-case cost:** the greatest work permitted by the input and contract.
- **Wraparound:** continue probing at slot 0 after the final array slot.
