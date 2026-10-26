# Stage E — C Lab: Chaining and Two Sum

The required lesson follows [lab.c](lab.c). Its operations are supplied.
Trace them and write an assertion driver that exercises the actual source.
There are no required implementation TODOs. The older open-addressed library
under `code/include`, `code/starter`, and `code/solution` is optional.

The supplied driver scaffold is `code/tests/test_lab_student.c`. Add your
three original test groups there, or create the separate driver shown below.
From the repository root, run the current-source checks with:

```sh
make -C module_09_hash_table/code lab-compile
make -C module_09_hash_table/code core
make -C module_09_hash_table/code student-tests
```

The supplied student driver initially contains only a smoke test. Passing
that smoke test does not complete the three required test groups.

## Build a driver that includes the supplied source

The hash-table source includes `module_07_linked_list/student/lab.c`. Keep the
repository folder layout and pass the repository root as an include path.
Create `module_09_hash_table/student/lab_driver.c` containing:

```c
#include <assert.h>
#include "lab.c"

int main(void) {
    init_lnodes_pool();
    two_sum_ht(0);
    assert(answer[0] == 5 && answer[1] == 4);
    init_hashtable();
    return 0;
}
```

From the repository root, compile and run the driver alone:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic -I. module_09_hash_table/student/lab_driver.c -o /tmp/module09_lab_driver
/tmp/module09_lab_driver
```

Do not separately compile either included `lab.c`. Both files define globals
and functions. Record your compiler command, warnings, assertions, and result.
Use a course-provided compiler if the local compiler is unavailable.

## Prepare and protect the shared pool

The table has ten bucket heads in `hashtable[10]`. Each head is `-1` or a
node index. The included Module 07 source provides `lnodes[10]`,
`free_head`, `init_lnodes_pool()`, and `new_lnode(data_value, next_value)`.

Call `init_lnodes_pool()` before the first allocation while all buckets are empty.
The initial free chain is `0→1→2→3→4→5→6→7→8→9→-1`.
`init_hashtable()` returns active bucket chains to the free chain and sets
each bucket head to `-1`. It does not initialize the pool for first use.
Never reset the pool while buckets or another linked structure still own
nodes. For this lab, reserve the shared pool for the hash table.

Every chain must contain valid indices, end at `-1`, and remain acyclic.
A node belongs to exactly one bucket chain or the free chain. The source does
not diagnose broken chains, double recycling, or invalid bucket arguments.
Use buckets 0 through 9 and values whose sums and complements fit in `int`.

## 1. Trace signed hashing and collision chains

The source calculates `value % 10` and adds 10 if that remainder is negative.
Check negative, zero, and positive values. All returned buckets are 0–9.

Save 12, 22, and -8 using `save_data(hash_func(value), value)`.
Predict returned node indices, `data`, `next`, bucket head, and `free_head`
after every save. New records go at the head. Search for present 22 and
missing 32 with `find_data` and list every visited node.

Save another 22. Assert that another record was allocated and that searching
returns the newest matching payload. `save_data` does not update or reject
an existing payload. `find_data(hash, data)` checks only the selected chain
and compares `lnodes[node].data == data`.

## 2. Recycle chains and check exhaustion

Call `init_hashtable()` after the chain experiment. Trace
`free_lnode_chunk`: find the chunk tail, link it to the existing free head,
then make the chunk head the new free head. Buckets clear in index order.
Clearing does not promise zeroed node data.

In an independent experiment, save `0,10,20,30,40,50,60,70,80,90`.
Snapshot bucket heads, node fields, and `free_head` before saving 100.
Assert that the eleventh save returns `-1` and that the snapshot remains
unchanged. Clear and prove that another allocation succeeds. Check that an
empty-table clear leaves the free chain unchanged.

Use `init_hashtable()` to clear table-owned nodes. Calling
`free_lnode_chunk` manually while a bucket still points to the same chunk
would leave an active reference to recycled nodes.

## 3. Compare the two pair searches

`two_sum_bf` visits `i` in ascending order and checks earlier `j` values from
0 through `i-1`. It returns positions in `answer[0]` and `answer[1]`.
A complete miss writes `{-1,-1}`.

`two_sum_ht` clears old bucket chains at entry. At each `i`, it searches for
`target - nums[i]` among earlier positions. Node data stores an earlier
position `j`, so the comparison is `nums[j] == j_num`. Only after a miss
does it save `i` in `hash_func(nums[i])`. This order prevents using one
position twice. A successful return leaves earlier records in the table.
The next call recycles them automatically.

With the unchanged source array, check these exact position answers:

| Target | `two_sum_bf` | `two_sum_ht` |
| ---: | --- | --- |
| 0 | `{5,4}` | `{5,4}` |
| 2 | `{7,3}` | `{7,3}` |
| 3 | `{6,5}` | `{6,5}` |
| 100 | `{-1,-1}` | `{-1,-1}` |

Run 100 followed by 0 without manually resetting the pool between calls.
Then temporarily use `{1,1,5,0,0,0,0,0,0,0}` and target 6.
Predict why brute force returns `{2,0}` while the table returns `{2,1}`.
For general duplicate fixtures compare answer existence, valid distinct
positions, and target sum. Do not require identical pair positions when
multiple answers are valid. Restore the original array after custom tests.

A failed `save_data` causes `two_sum_ht` to stop and report `{-1,-1}`.
That result does not distinguish allocation failure from an ordinary miss.
With an initialized pool reserved for this ten-number search, capacity is
sufficient; the normal search needs at most ten records.

## Write three original assertion groups

State each claim before its assertions. Test:

1. Signed hashing, head insertion, collisions, present/missing lookup, and
   duplicate payloads.
2. Recycling, empty clear, all ten allocations, unchanged state after an
   eleventh failed save, and successful reuse.
3. Both two-sum methods, valid indices and sums, no self-pair, missing
   answers, duplicate values, and repeated calls after early success and
   after a full miss.

Assertions must inspect results and state. Merely printing a chain or
finishing a process is insufficient. Keep the supplied `lab.c` unchanged.
Complete the [source-based autopsy](hash_table_autopsy.md) in your driver or
by hand before and after tracing the relevant conditions.

## Explain the work and submit one record

Count before using cost symbols. A complete brute-force miss makes
`0+1+...+9 = 45` pair comparisons. A chain search inspects at most its chain
length. Head insertion takes constant work when a free node exists.
Clearing scans ten bucket heads and walks each returned chain once.
Expected short chains require distributed values and a controlled number of
records per bucket. Long collision chains can make complete hash-based
two-sum work quadratic in a generalized input size. This fixed source has
ten numbers, ten buckets, and ten nodes; it never grows the table or pool.

Submit your driver with three test groups, warning-enabled output,
[evidence record](evidence_template.md), completed investigation worksheet,
corrected [Cognitive Pause](cognitive_pause.md), and autopsy explanation.
Use [rubric.md](rubric.md) to check the submission. Dynamic allocation,
tombstones, rehashing, and the older library's tests are optional enrichment.
