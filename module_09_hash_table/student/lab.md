# Stage E — C Lab: Chaining and Two Sum

The required lesson follows the self-contained [lab.c](lab.c). Its
operations are supplied. Trace them and write an assertion driver that
exercises the actual source. Keep the supplied `lab.c` unchanged.
There are no required implementation TODOs. The older open-addressed library
under `code/include`, `code/starter`, and `code/solution` is optional.

Use the current lab's ten nodes, fifteen buckets, signed input,
descending brute-force inner loop, and failure checks for executable
assertions.

The supplied scaffold is `code/tests/test_lab_student.c`. Add three original
test groups there, or create the separate driver below. From the repository
root, run:

```sh
make -C module_09_hash_table/code lab-compile core student-tests
```

The supplied student driver initially contains only a smoke test. Passing
it does not complete the three required test groups.

## Build a driver that includes the supplied source

Create `module_09_hash_table/student/lab_driver.c` containing:

```c
#include <assert.h>
#include "lab.c"

int main(void) {
    two_sum_ht(0); /* initializes its own table */
    assert(answer[0] == 4 && answer[1] == 5);
    assert(hnodes_unused == 5);
    initialize();
    assert(hnodes_unused == 0);
    assert(answer[0] == 4 && answer[1] == 5); /* reset retains the answer */
    return 0;
}
```

From the repository root, compile and run the driver alone:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic module_09_hash_table/student/lab_driver.c -o /tmp/module09_lab_driver
/tmp/module09_lab_driver
```

The source has no external module dependency. Do not also compile `lab.c`
as a second translation unit: including it already defines its globals and
functions. Record the command, warnings, assertions, and result. Use a
course-provided compiler if the local compiler is unavailable.

## 1. Trace signed hashing, keys, and collision chains

Read `NODES_CAPACITY = 10` and
`TABLE_CAPACITY = NODES_CAPACITY * 3 / 2`, which evaluates to 15.
`hash_func` takes `% TABLE_CAPACITY` and adds the capacity if the remainder
is negative. Check negative, zero, positive, and negative-multiple keys.
All returned buckets must be in 0–14.

Call `initialize()` before a standalone table experiment. It sets all
bucket heads to -1 and `hnodes_unused` to 0. Static zero initialization is
not a valid empty-bucket setup.

Insert `(12,120)`, `(27,270)`, and `(-3,-30)` in that order. Each call
returns 0 and all keys select bucket 12. Predict each new node's index,
`key`, `data`, and `next`, the bucket head, and `hnodes_unused`.
The final chain is `2 → 1 → 0 → -1`.

Trace `find(27)` through nodes 2 and 1; its return is node index 1 and the
associated data is 270. Trace missing key 42 through all three nodes.
Assert that payload 120 is not found as a key.
Insert `(27,999)` and prove that a new node is allocated rather than an
existing node updated: `find(27)` returns node 3, and node 1 still holds
`key=27,data=270`. Every collision search compares full keys.

## 2. Check exhaustion and whole-table reset

After a reset, insert keys `0,15,30,45,60,75,90,105,120,135` with distinct
payloads. All ten nodes occupy bucket 0, so fourteen buckets remain empty.
Snapshot the counter, all heads, and each node field before an eleventh
insertion. Assert that `insert(150,10)` returns -1 and preserves the entire
snapshot. Also test failed insertion into a previously empty bucket.

Call `initialize()`. All fifteen heads must be -1 and `hnodes_unused` must
be 0; node fields, `nums`, and `answer` are unchanged. Old node indices no
longer represent active records. No chain traversal or free list is used.
A new `insert` succeeds in node 0 and overwrites its key, data, and next.
A second reset on an empty table is safe. Resetting only the counter would
leave stale heads pointing into reused slots; always use `initialize()`.

`new_hnode(key,data,next)` returns the allocated index or -1. Unlike that
helper, `insert(key,data)` returns 0 or -1. Do not interpret a successful
`insert` return value as its node index.

## 3. Compare the two pair searches

`two_sum_bf` visits `i` in ascending order and earlier `j` from `i-1` down
to 0. Both implementations write `{j,i}` with `j<i`, or `{-1,-1}` on a miss.
Brute force does not change the table.

`two_sum_ht` calls `initialize()` at entry. At each `i`, it calls
`find(target - nums[i])`. A successful node holds the complement in `key`
and the earlier input position in `data`. Only after a miss does it call
`insert(nums[i],i)`. Lookup before insertion prevents self-pairing.
A successful return leaves the earlier nodes available for inspection.

With the unchanged input array, check these exact answers:

| Target | `two_sum_bf` | `two_sum_ht` |
| ---: | --- | --- |
| 0 | `{4,5}` | `{4,5}` |
| 2 | `{3,7}` | `{3,7}` |
| 3 | `{5,6}` | `{5,6}` |
| 100 | `{-1,-1}` | `{-1,-1}` |

Target 0 leaves five nodes; target 100 leaves ten. Run 100 followed by 0
without manually resetting between calls. The second call resets all heads
and starts allocation again at node 0.

Temporarily use `{1,1,5,0,0,0,0,0,0,0}` and target 6. Both algorithms
return `{1,2}`: descending brute force and newest-first matching-key lookup
choose the latest matching earlier position. Also assert valid bounds,
distinct positions, and the target sum. Check a fixture with only one 5
and target 10 to rule out self-pairing; then add another 5 and check success.
Restore the original array after custom tests.

If `insert` fails, the hash-based search loop breaks and writes `{-1,-1}`.
That answer alone does not distinguish exhaustion from an ordinary miss.
For the supplied fixed-size scan, initialization and capacity for all ten
inputs ensure no insertion failure is reached during normal use.

## Write three original assertion groups

State each claim before its assertions. Test:

1. Signed hashing, key/payload distinction, head insertion, collisions,
   present/missing lookup, and duplicate-key behavior.
2. All ten allocations, unchanged failed insertion, full reset, retained
   old fields and answer, repeated reset, and successful slot reuse.
3. Both pair searches, exact supplied results, valid distinct indices,
   misses, duplicate values, and repeated calls after hits and full misses.

Assertions must inspect results and state; printing a chain is insufficient.
Complete the [source-based autopsy](hash_table_autopsy.md) in a separate
driver or by hand. Do not introduce defects into the supplied lab.

## Explain the work and submit one record

A complete brute-force miss makes 45 comparisons; target 0 makes 11.
The target-0 hash search makes one key comparison. Head insertion is
constant work when capacity remains. Reset scans fifteen bucket heads and
does not walk old chains, so its generalized cost is `Θ(b)`.

Expected short chains require adequately distributed keys and controlled
load `n/b`. Under those conditions, generalized lookup is `O(1+n/b)` and
hash two sum can be expected `O(n)` when `b=Θ(n)` and node capacity suffices.
Collision-heavy searches can take `O(n^2)` total work. This fixed source
has ten numbers, ten nodes, and fifteen buckets; it never grows its arrays.
All evaluated sums and complement subtractions in your tests must fit in
`int`; the source does not check overflow.

Submit the driver with three groups, warning-enabled output,
[evidence record](evidence_template.md), completed investigation worksheet,
corrected [Cognitive Pause](cognitive_pause.md), and autopsy explanation.
Use [rubric.md](rubric.md) to check the submission. Dynamic allocation,
tombstones, rehashing, and the older library's tests are optional enrichment.
