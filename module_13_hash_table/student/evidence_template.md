# Module 13 Evidence Record

Name: ____________________________  
Date: ____________________________  
Compiler/platform: _________________________________________________

Preserve original predictions. Add corrections with labels; do not erase the
earlier model.

## 1. Build and test evidence

Warning-enabled build command:

____________________________________________________________________

Build result and warnings, if any:

____________________________________________________________________

Core-test command/result:

____________________________________________________________________

Student-test command/result:

____________________________________________________________________

Sanitizer or instructor-CI evidence:

____________________________________________________________________

## 2. Canonical collision evidence

Capacity 8; insert `(10,100)`, `(18,180)`, `(26,260)`.

| Key | Home | Inspected indexes | Final index | Inserted | Probes |
|---:|---:|---|---:|:---:|---:|
| 10 |  |  |  |  |  |
| 18 |  |  |  |  |  |
| 26 |  |  |  |  |  |

Final indexes 0 through 7:

____________________________________________________________________

`get(26)` result:

____________________________________________________________________

`get(34)` result:

____________________________________________________________________

Validator result: _________________________________________________

## 3. Wraparound evidence

Capacity 8; insert `(7,70)`, `(15,150)`, `(23,230)`.

| Key | Inspected indexes | Final index | Probes |
|---:|---|---:|---:|
| 7 |  |  |  |
| 15 |  |  |  |
| 23 |  |  |  |

Evidence that no index exceeded 7:

____________________________________________________________________

## 4. Tombstone and unique-key evidence

From the canonical collision table:

| Operation | Route | Boolean | Value | Probes | Size | Tombstones |
|---|---|:---:|---:|---:|---:|---:|
| `remove(18)` |  |  |  |  |  |  |
| `get(26)` |  |  |  |  |  |  |
| `put(26,999)` |  |  | n/a |  |  |  |
| `put(34,340)` after reset to deleted state |  |  | n/a |  |  |  |

Index 3 after remove: state ______ key ______ value ______

Location/value of the one live key 26 after update:

____________________________________________________________________

Why the search must continue after remembering a deleted slot:

____________________________________________________________________

## 5. Maintenance evidence

### Growth

Six direct keys at capacity 8, then one new distinct key:

```text
before capacity ______ size ______ tombstones ______
requested-key probes ______
after capacity ______ size ______ tombstones ______
```

All seven values retrieved correctly: [ ] yes [ ] no

### Same-capacity compaction

Capacity 8, size 2, tombstones 4, requested key with an empty home:

```text
effective proposal ____________________
selected capacity _____________________
public probe count ____________________
final size ____________________________
final tombstones ______________________
```

Explain why internal rehash placements are excluded from the result metric:

____________________________________________________________________

### Failure preservation

Record pointer identity, capacity, size, tombstones, all occupied records,
and caller result before a forced replacement-allocation failure.

Before snapshot:

____________________________________________________________________

Status: _____________________ Result unchanged: [ ] yes [ ] no

After comparison:

____________________________________________________________________

Live-allocation baseline restored after destroy: [ ] yes [ ] no

## 6. Maximum boundary and output evidence

At capacity 64 with size 48 and zero tombstones:

```text
new distinct put status __________________________
table preserved _________________________________
caller result preserved _________________________
existing-key update status/result ______________
```

After removing one entry and inserting one new distinct key:

____________________________________________________________________

Missing get complete successful result:

____________________________________________________________________

One non-`OK` call and proof its entire result struct stayed unchanged:

____________________________________________________________________

## 7. Exactly three original test categories

### Test 1 - Collision, wraparound, exact probes

Claim:

____________________________________________________________________

Distinct assertions and result:

____________________________________________________________________

### Test 2 - Tombstone reachability, update, reuse

Claim:

____________________________________________________________________

Distinct assertions and result:

____________________________________________________________________

### Test 3 - Maintenance and allocation-failure preservation

Claim:

____________________________________________________________________

Distinct assertions and result:

____________________________________________________________________

## 8. Autopsy evidence

Prediction before run:

____________________________________________________________________

Faulty `get(26)` route/result:

____________________________________________________________________

Corrected route/result:

____________________________________________________________________

Smallest regression:

____________________________________________________________________

Failure classification and limit:

____________________________________________________________________

## 9. Cost and structure selection

Fill every cell with a qualified claim.

| Representation | Exact lookup | Space/ownership | Ordered/range work | Important worst case |
|---|---|---|---|---|
| Direct-index array |  |  |  |  |
| Open-addressed table |  |  |  |  |
| AVL tree |  |  |  |  |
| Separate chaining |  |  |  |  |

Define live `n` and capacity `m`, then record expected/worst requested-key
probe, expected/worst rebuild, space, and expected-amortized statements:

____________________________________________________________________

## 10. Security and scope statement

Complete in two or three precise sentences:

> Chosen colliding keys can ________________________________________.
> This bounded evidence does not prove _____________________________.
> The course remainder function is not ____________________________.

## 11. Final synthesis

What invariant made the largest change to your initial model?

____________________________________________________________________

When would you select this table instead of an AVL tree, and what assumption
must accompany the choice?

____________________________________________________________________
