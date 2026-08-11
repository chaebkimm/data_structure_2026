# Stage B - Five-Minute Cognitive Pause

Read the starting definitions with the instructor before timing begins.
Then use no notes, slides, classmates, vocabulary file, or coding tools for
five minutes. You may draw, type, dictate, or answer in numbered sentences.
Preserve your first response when correction begins.

At capacity 8, home is `key % 8`. Linear probing examines the home slot and
then following slots, wrapping after 7. `E` means empty, `O` occupied, and
`D` deleted. A search stops at the requested key, at `E`, or after eight
inspections. It does not stop at `D`.

## Target 1 - Trace present and missing lookup

Use this state:

```text
capacity 8, size 3, tombstones 0
index 0 E
index 1 E
index 2 O key10 value100
index 3 O key18 value180
index 4 O key26 value260
index 5 E
index 6 E
index 7 E
```

State:

1. every index inspected by `get(26)` and its complete result;
2. every index inspected by `get(34)` and its complete result; and
3. why the two searches stop at different positions.

Response:

____________________________________________________________________

____________________________________________________________________

## Target 2 - Delete, continue, and update once

Return to Target 1's starting state. Apply `remove(18)`, then `get(26)`, then
`put(26, 999)`.

State:

1. each operation's inspected indexes;
2. the state of index 3 after removal;
3. the final location and value of key 26; and
4. final size and tombstone count.

Response:

____________________________________________________________________

____________________________________________________________________

## Target 3 - Select maintenance and limit the promise

For a new distinct key whose search selects an `EMPTY` insertion slot,
maintenance occurs when `size + tombstones + 1` exceeds three quarters of
capacity.

1. Capacity 8, size 2, tombstones 4: choose same-capacity compaction or
   growth to 16 and explain.
2. Capacity 8, size 6, tombstones 0: choose compaction or growth and explain.
3. State why expected `O(1)` lookup is not a guarantee against chosen
   colliding keys, and why the course hash is not an authenticity check.

Response:

____________________________________________________________________

____________________________________________________________________

## Compare after time is called

Preserve the original response. Label corrections `stop`, `tombstone`,
`unique key`, `maintenance`, `cost`, or `scope`.

The evidence that changed or strengthened my thinking was:

____________________________________________________________________
