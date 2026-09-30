# Stage C - Hash-Table Investigation - Linear Form

Name: ____________________________  
Date: ____________________________

This form has the same data, questions, and 100 points as the table form. It
uses numbered records and sentences instead of spatial tables. Preserve A-F
before opening the textbook or code. Unless stated otherwise, capacity is 8
and home is key remainder 8.

## A. Separate map behavior from direct indexing - 10 points

### A1. Identify key and value - 3 points

For `key 18 -> value -4`, identify key and value. State what a later put of
key 18, value 70 must do.

____________________________________________________________________

### A2. Explain sparse direct-index cost - 3 points

Explain why an integer position for every possible `uint32_t` key is wasteful
when only 20 records are live.

____________________________________________________________________

### A3. Calculate homes - 4 points

For each key, write its remainder expression, home, and other listed keys
with the same home: 10, 18, 26, 7, 15, and 23.

1. key 10: _______________________________________________________
2. key 18: _______________________________________________________
3. key 26: _______________________________________________________
4. key 7: ________________________________________________________
5. key 15: _______________________________________________________
6. key 23: _______________________________________________________

## B. Trace collision and wraparound - 15 points

### B1. Build the canonical collision cluster - 6 points

Insert `(10,100)`, `(18,180)`, `(26,260)` in order. For each, state
inspected indexes, final index, inserted Boolean, and probe count. Then list
the state and record, if any, at indexes 0 through 7.

____________________________________________________________________

____________________________________________________________________

### B2. Wrap safely - 5 points

Start fresh and insert `(7,70)`, `(15,150)`, `(23,230)`. State each route,
final index, and every final slot. Explain how accesses stay in range.

____________________________________________________________________

### B3. Stop a missing search - 4 points

Return to B1. For `get(26)` and `get(34)`, state inspected indexes, found,
value, probe count, and stop reason.

____________________________________________________________________

## C. Preserve routes and unique keys - 15 points

### C1. Remove with a tombstone - 5 points

From B1, remove key 18. State removed, value, probe count, index 3 state,
size, and tombstones. Then trace get 26.

____________________________________________________________________

### C2. Update beyond a tombstone - 5 points

From C1, put key 26 value 999. State the complete route and result, final
location/value, size, tombstones, and why no duplicate may be created.

____________________________________________________________________

### C3. Reuse only after proving absence - 5 points

Return to C1 before C2 and put key 34 value 340. Trace through the first
empty position, state the committed index, size, and tombstones.

____________________________________________________________________

## D. Compact or grow transactionally - 15 points

At capacity 8, maintenance is required when
`size + tombstones + 1 > 6` for a new distinct key.

### D1. Select the maintenance action - 5 points

Assume each distinct-key search selects an empty insertion slot. For each
state, show effective occupancy, live-after-insert, and choose none, compact
at 8, grow to 16, or full.

1. capacity 8, size 2, tombstones 3: ______________________________
2. capacity 8, size 2, tombstones 4: ______________________________
3. capacity 8, size 6, tombstones 0: ______________________________
4. capacity 64, size 48, tombstones 0: ____________________________

Explain why updating an existing key may proceed in item 4.

____________________________________________________________________

### D2. Trace same-capacity compaction - 5 points

Starting state: index 0 empty; 1 empty; 2 occupied key10 value100; 3
deleted; 4 occupied key26 value260; 5 deleted; 6 deleted; 7 deleted; size 2;
tombstones 4.

Put key8 value80. Give the pre-maintenance search, why capacity stays 8,
reinsertions in old-index order, final indexes 0 through 7, size, and
tombstones. State the put probe count; internal maintenance placements do
not add to it.

____________________________________________________________________

### D3. Rehash on growth and preserve failure - 5 points

Rehash occupied keys 10, 18, 26 in that order from capacity 8 to 16. State
each new home and final index. Then list every old-table fact preserved if
replacement allocation fails.

____________________________________________________________________

## E. Validate state and preserve errors - 15 points

### E1. Check representation rules - 5 points

For each condition, state valid or invalid and name the rule.

1. capacity8, size3, tombstones1, three reachable occupied and one canonical
   deleted state: __________________________________________________
2. capacity12 and nonnull allocation: _____________________________
3. two occupied copies of key26: _________________________________
4. key26 after an empty slot on its route: ________________________
5. canonical all-zero destroyed state: ____________________________

### E2. Apply status and output rules - 5 points

Null table/result precedes validation. Destroyed/malformed state passed to
put/get/remove is invalid state. Allocation/full applies only to a new key
after search. State status and whether the result may change:

1. get valid table, key26, null result: ____________________________
2. put into destroyed table with valid result: ____________________
3. missing get on valid table: ___________________________________
4. failed growth allocation: _____________________________________

### E3. Explain ownership and cleanup - 5 points

Explain shallow-copy danger, transactional replacement, and the exact state
restored by destroy.

____________________________________________________________________

## F. Analyze cost, selection, and security - 10 points

### F1. State operation costs with assumptions - 4 points

Let `n` be live entries and `m` capacity. Give expected and worst requested-
key probe costs, then expected and worst rehash costs including scan and
reinsertion. Explain why expected constant cost is conditional and why
`O(m)` does not always simplify to `O(n)` without shrinking.

____________________________________________________________________

### F2. Select among four representations - 3 points

Give one fitting workload each for a direct-index array, open-addressed hash
table, AVL tree, and separate chaining. Address sorted/range work.

____________________________________________________________________

### F3. Limit the security claim - 3 points

Explain bounded hash-flooding and two facts neither the course hash nor the
validator proves.

____________________________________________________________________

## G. Design exactly three tests - later work - 9 points

### G1. Collision, wraparound, and bounded probes - 3 points

Design one test using 10/18/26 and 7/15/23 with exact positions, results,
probe counts, and in-range accesses.

____________________________________________________________________

### G2. Tombstone, update, and reuse - 3 points

Design one test covering lookup through deletion, update beyond a deleted
slot, missing-key reuse, and exact counts.

____________________________________________________________________

### G3. Maintenance and preservation - 3 points

Design one test covering compaction, growth, forced maintenance allocation
failure, table/result/ownership preservation, and destruction.

____________________________________________________________________

## H. Complete the bounded autopsy - later work - 6 points

### H1. Find the first wrong state - 2 points

Identify the wrong assignment and first operation exposing it.

____________________________________________________________________

### H2. Repair and verify - 2 points

State correct marker and exact get26 route/result.

____________________________________________________________________

### H3. Add a regression - 2 points

Describe the smallest distinguishing regression.

____________________________________________________________________

## I. Synthesize - later work - 5 points

### I1. Connect invariant to operation - 2 points

Explain empty versus deleted as both safe stopping and preserved reachability.

____________________________________________________________________

### I2. Select and qualify - 2 points

Choose hash or AVL for unordered exact lookup and give one reversing or
qualifying requirement/threat.

____________________________________________________________________

### I3. Exit synthesis - 1 point

Complete: “A hash table can avoid an ordinary full scan when __________,
but it can still require linear work when __________.”

____________________________________________________________________
