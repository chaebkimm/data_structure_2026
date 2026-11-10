# Module 09 Vocabulary

These terms describe [lab.c](lab.c). Read them beside the textbook traces.

| Term | Meaning in the supplied program |
| --- | --- |
| Two-sum | Find two distinct array positions whose values add to a target |
| Target | The sum passed to `two_sum_bf` or `two_sum_ht` |
| Complement | The needed value `target - nums[i]` |
| Brute force | Check each current `i` against `j = i-1` down through 0 |
| Direct addressing | Use a key directly as a table index when its range permits |
| Hash function | Repeatable calculation selecting a bucket from a key |
| Remainder | C's `%` result; a negative key can yield a negative remainder |
| Normalization | Add 15 to a negative remainder, yielding a bucket in 0–14 |
| Bucket | One of 15 positions in `hashtable`, containing a chain-head index |
| Collision | Different keys select the same bucket |
| Separate chaining | Keep colliding entries in one linked chain per bucket |
| Key | `hnode.key`, used by hashing and equality checks in `find` |
| Payload | `hnode.data`, associated information; an earlier `nums` index in two-sum |
| Node array | The ten `hnodes` records owned by this source |
| Node index | An integer 0–9 selecting a record in `hnodes` |
| Allocation counter | `hnodes_unused`, the next unused slot; 10 means exhausted |
| Head | First node index in a bucket chain; -1 means empty |
| Next link | A node index in `next`; -1 ends the chain |
| Prepend | Insert before the old chain head |
| Duplicate key | A repeated key stored in a new node; `find` returns the newest match |
| Initialization/reset | Set the allocation counter to 0 and all 15 heads to -1 |
| Capacity exhaustion | `new_hnode` and `insert` return -1 without changing table state |
| Invariant | A preserved rule, such as every stored two-sum position being earlier than `i` |
| Expected cost | Work estimated under assumptions about key distribution and load |
| Worst-case cost | Greatest work among inputs allowed by the assumptions |
| Open addressing | Alternative collision rule using table slots and probing |
| Robin Hood hashing | Probing strategy that can favor an entry farther from its starting slot |

`insert(k,d)` returns **0 on success**, not the allocated node index.
`find(k)` returns a **node index**, not the payload. Read
`hnodes[find_result].data` only after checking the result is not -1.
`answer = {j,i}` contains **input positions**, with `j < i`, not node indices
or values. The value -1 remains a legal key and payload even though it is
also the missing-node/result sentinel in the appropriate fields.

`initialize()` does not erase old node fields or change `answer`. There is
no shared Module 07 pool, free list, deletion, or resizing in this lab.
Open addressing, tombstones, and dynamic growth belong to the optional older
library rather than the assessed implementation.
