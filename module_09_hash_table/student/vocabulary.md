# Module 09 Vocabulary

Current pool contract: `new_lnode()` takes no arguments, returns an isolated index with retained data, and initializes the pool only on first use. `save_data` checks the index, writes data/next, then publishes the bucket head. Later `init_lnodes_pool()` calls are no-ops; `init_hashtable()` recycles owned bucket chains.


These terms describe [lab.c](lab.c). Read each definition beside the
corresponding trace in the textbook.

| Term | Meaning in the supplied program |
| --- | --- |
| Two-sum | Find two distinct array positions whose numbers add to a target |
| Target | The requested sum passed to `two_sum_bf` or `two_sum_ht` |
| Complement | The needed number `target - nums[i]` |
| Brute force | Check every earlier position for each current position |
| Hash function | Repeatable calculation selecting a bucket from a number |
| Remainder | The result of C's `%`; a negative input can have a negative remainder |
| Normalization | Add 10 to a negative remainder so `hash_func` returns 0–9 |
| Bucket | One position in `hashtable[10]`, containing a chain-head node position |
| Collision | Different numbers select the same bucket |
| Hash table | Bucket selection plus storage and search of the bucket's candidates |
| Separate chaining | Store colliding candidates in one linked chain per bucket |
| Node pool | The ten `lnodes` records shared with Module 07 |
| Node position | An integer 0–9 selecting a record in `lnodes` |
| Head | The first node position of a chain; -1 means no node |
| Next link | A node's `next` position; -1 ends the chain |
| Payload | A node's `data`; raw data in a storage experiment, a `nums` position in two-sum |
| Prepend | Add a node before the old chain head |
| Free chain | Available nodes linked from `free_head` |
| Pool exhaustion | No available node; `new_lnode` returns -1 |
| Recycling | Return allocated nodes to the free chain for later reuse |
| Active node | A node still reachable through a bucket chain |
| Early return | Leave the function immediately after publishing a successful pair |
| Invariant | A rule preserved in valid state, such as disjoint active and free chains |
| Expected cost | Work estimated under stated assumptions about input distribution |
| Worst-case cost | Greatest work permitted by the allowed inputs |
| Failure preservation | `save_data` leaves the bucket and pool unchanged when no node is available |

`find_data` returns a **node position**, not the stored payload.
`answer` contains **positions in `nums`**, not node positions or numbers.
`-1` marks a missing link or unsuccessful result. The number -1 remains a
legal payload and occurs in `nums[4]`.

The supplied table does not enforce unique keys. Repeated `save_data` calls
can store equal payloads in distinct nodes. Tombstones, linear probing,
dynamic growth, and transactional rehashing belong to the optional older
library, not this lab's representation.
