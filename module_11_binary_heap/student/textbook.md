# Chapter 11. Choosing Urgent Work with Priority Queues and Binary Heaps

## Thinking Logically

### Should the first arrival always leave first?

An ordinary Queue processes the first arrival first. Urgent alerts need a
different rule. A recent urgent alert may need attention before an older
routine alert. Attach a number to each alert and select the smallest number
first. This number is the alert's **priority**. Smaller means more urgent in
this course.

We need three operations: add an alert, inspect the next alert, and remove
the next alert. A **Priority Queue** provides these operations under a
stated priority rule. Selecting the smallest value makes it a **minimum
Priority Queue**. The behavior does not require a particular storage method.
A description of public behavior independent of storage is an **abstract
data type (ADT)**. We will provide this one ADT using two representations.

### What happens when priorities tie?

Two equally urgent alerts need a predictable order. Select the earlier
arrival first. Each successful insertion receives an increasing number,
starting at 0. This **arrival sequence** records insertion order even when
records move in memory. Keeping arrival order among equal priorities is
**stable tie-breaking**.

Each alert record contains `alert_id`, `priority`, and `arrival_sequence`.
The ID identifies the alert. It does not rank the alert. The rule comparing
two records is the **comparator**: compare priorities first, then arrival
sequences if priorities tie. Array positions never settle a tie.

Use these seven arrivals throughout the chapter. `p` denotes priority and
`s` denotes arrival sequence.

```text
71(p3,s0), 88(p1,s1), 42(p2,s2), 17(p1,s3),
26(p4,s4), 9(p2,s5), 63(p1,s6)
```

Among priority-1 records, sequences 1, 3, and 6 put IDs 88, 17, and 63 first.
ID 42 precedes ID 9 because their priorities tie and sequence 2 precedes 5.
The full service order is:

```text
88, 17, 63, 42, 9, 71, 26
```

Stable ties do not guarantee that every alert is eventually served. If
higher-priority alerts keep arriving, a lower-priority alert can remain
waiting indefinitely. This is **starvation**. Changing that behavior
requires an additional scheduling policy.

### What can an unsorted array do?

We already know how to append to an array. Store each arrival at `data[size]`
and increase `size`. No comparisons between records are needed. The seven
IDs occupy these positions:

```text
[71, 88, 42, 17, 26, 9, 63]
```

To find the next alert, start with index 0 as the candidate. Compare every
remaining record with the candidate. Replace the candidate index whenever a
record precedes it. Six comparisons select ID 88 from seven records.

Inspection copies the selected record without removing it. Extraction also
fills the selected slot with the final live record and reduces `size`.
After extracting 88, the array is:

```text
[71, 63, 42, 17, 26, 9]
```

ID 17 still precedes 63. The arrival sequence survives the move. Repeated
extractions produce the required service order, with
`6 + 5 + 4 + 3 + 2 + 1 + 0 = 21` comparisons.

This completed scan implementation is the supplied **baseline**: a simple
reference for checking answers and comparing work. You trace it before
implementing the Heap. Both belong to this module.

### How can we avoid scanning for every minimum?

An unsorted array repeats a full scan at every inspection and extraction.
A sorted array can keep the minimum at one end, but inserting a record may
require moving many records. We need enough order to find the minimum while
repairing only a small part of the stored data after a change.

Arrange the array positions as a binary tree. Fill levels from top to
bottom and fill each level from left to right. Every level except possibly
the last is full. This shape is a **complete binary tree**.

For seven positions, index 0 has children 1 and 2. Index 1 has children 3 and
4. Index 2 has children 5 and 6. Reading positions by level gives the array
order. A live position `i` has these related positions:

```text
parent:      (i - 1) / 2, only when i > 0
left child:  2 * i + 1
right child: 2 * i + 2
```

Division discards the remainder. A calculated child exists only when its
index is smaller than `size`. Appending at index `size` preserves the
complete shape without storing pointers between nodes.

### What order must parents and children satisfy?

The minimum must be reachable without a scan. Require that no child precede
its parent under the same priority-then-sequence comparator. Every record
has a path through parents to the root. Following that path never leads to
a later-ranked record, so the root is the minimum.

A complete binary tree with this rule is a **minimum binary Heap**. The rule
is its **Heap-order invariant**: a condition that operations must preserve.
The root occupies `data[0]`, so inspection only copies that record.

This is not a globally sorted array. Siblings need not be ordered. The whole
left subtree need not precede the whole right subtree. A binary search tree
uses a different rule for locating arbitrary keys; a Heap is organized to
select the next record.

### Where can insertion break the order?

Appending preserves the complete shape. Only the new record's relationship
to its parent may violate Heap order. Keep the new record as a candidate.
If it precedes its parent, move the parent down into the open position.
Continue at the parent's old position. Stop at the root or at a parent that
the candidate does not precede. Place the candidate there. This repair is
**sift-up**.

For our example, the first three arrivals form `[88, 71, 42]`. ID 17 arrives
at index 3. It precedes parent 71 at index 1, so 71 moves to index 3. It does
not precede root 88: both have priority 1, but 88 arrived earlier. Place 17
at index 1. The resulting array is `[88, 17, 42, 71]`.

After all seven insertions, the IDs are:

```text
[88, 17, 63, 71, 26, 9, 42]
```

The records move as complete units. Separating a priority from its ID or
arrival sequence would change which alert the record describes.

### How do we repair the root after extraction?

Save the root for the caller. Keep the final live record as the replacement
candidate and reduce the live range by one. Removing the final position
preserves the complete shape. The candidate may need to move down from the
root to restore order.

Choose the earlier-ranked existing child. If that child precedes the
candidate, move the child upward and continue from its old position. Stop
when there is no child or the candidate precedes both children. Place the
candidate in the open position. This repair is **sift-down**.

Extracting 88 from our seven-record Heap uses 42 as the candidate. Of root
children 17 and 63, 17 comes first. Move 17 to the root. Its former children
71 and 26 both follow 42, so place 42 at index 1:

```text
[17, 42, 63, 71, 26, 9]
```

Choosing the later child would leave the remaining child preceding its
new parent and break Heap order. Check whether the right child exists before
reading it. A parent with only a left child needs one child/candidate
comparison and no sibling comparison.

Repeated extraction gives the same service order as the baseline. For this
fixture, Heap insertion makes 8 comparisons and draining makes 12.

### How do we check the whole Heap?

A repair visits one path. To verify all parent relationships, compare each
record from index 1 through `size - 1` with its parent. The checker records
whether any child precedes its parent. It finishes the entire scan even
after finding a violation.

`alert_priority_queue_is_min_heap` returns a status and writes a Boolean
result. For a valid Queue shape, broken Heap order produces status `OK`
and result `false`. A Boolean stores either `true` or `false`. A failed
argument or shape check preserves the output.

An empty Heap needs zero record comparisons. A nonempty Heap with `n`
records needs exactly `n - 1`. Record checker work separately from normal
insertion and extraction work.

### What happens when storage cannot grow?

Both implementations allocate space only when needed. The capacity sequence
is `0, 4, 8, 16, 32, 64`. A Queue owns its allocation: destroy it once, and
do not copy the Queue structure as if the copy owned independent storage.

Insertion validates the state, rejects 64 live records, rejects an exhausted
arrival sequence, and then attempts growth. Save the allocation result in a
temporary pointer. A failed allocation leaves the old pointer and records
available. Every rejected operation preserves Queue fields and allocated
slots. Failed inspection or extraction also preserves the caller's output.
Outputs must use separate caller-owned storage outside the Queue allocation.

`SIZE_MAX` is the largest value of the unsigned size type `size_t`. An
insertion is rejected when `next_sequence` reaches this limit. Draining the
Queue resets `next_sequence` to 0 and retains the allocation. The comparison
counter stops increasing at `SIZE_MAX`; it never wraps to 0. Resetting the
counter changes only that counter.

## Calculating Efficiency

### What work does the scan baseline repeat?

Appending without growth writes one record and updates two counts. Finding
a minimum among `n` records makes `n - 1` comparisons. Extraction adds one
record move after that scan. Therefore baseline insertion without growth is
`O(1)`, while inspection and extraction are `O(n)`.

For our seven arrivals, baseline build comparisons total 0 and drain
comparisons total 21. A full sorted array reverses the tradeoff: insertion
may shift `n` records, while inspection and removal at the minimum end take
constant work.

### How many levels can one repair visit?

A complete tree with three full levels contains `1 + 2 + 4 = 7` records. Four
full levels contain 15. Each extra full level roughly doubles the number of
records. The number of levels therefore grows logarithmically with the
record count, written `O(log n)` for nontrivial sizes.

Sift-up makes at most one comparison per visited parent. Sift-down makes at
most two comparisons per visited level: sibling selection and the selected
child against the candidate. Both follow one path. Heap inspection takes
`O(1)` work; repair after insertion or extraction takes `O(log n)` work.

### Does array growth change insertion cost?

Growth may copy all `n` existing records, so one insertion can take `O(n)`
work in either implementation. Doubling capacity limits the total copying
over a long insertion sequence to an amount proportional to the insertions.
Spreading that total across the sequence is **amortized analysis**. The
baseline's amortized insertion cost is `O(1)`; the Heap's is `O(log n)`.

Our comparison counter measures record comparisons. It does not count copied
bytes, allocation work, or index arithmetic. A small comparison count alone
does not prove a small elapsed time.

### What does checking add?

A complete check examines every parent relationship, so its cost is `O(n)`.
For the seven insertions, checker calls after each insertion add
`0 + 1 + 2 + 3 + 4 + 5 + 6 = 21` comparisons. Checking after each extraction
adds `5 + 4 + 3 + 2 + 1 + 0 + 0 = 15`.

The instrumented Heap totals are 29 for building and 27 for draining. Normal
operation totals remain 8 and 12. Calling the checker after every mutation
makes the measured operation-plus-check cycle linear.

### How much storage is needed?

Both representations retain their allocation after extraction. Storage is
`O(capacity)`, proportional to the largest live record count reached under
geometric growth. It need not be proportional to the current size after a
drain. The Heap derives relationships from indexes instead of allocating
tree links. The course implementation has a 64-record cap; asymptotic
comparisons describe the representation as that limit is increased. Searching
for an arbitrary alert ID can still inspect every record.

## Glossary

The behavior and representation terms describe different parts of the same
Queue. Use these names for the ideas developed above.

| Term | Meaning |
|---|---|
| Abstract data type (추상 자료형) | Public operations and behavior independent of storage. |
| Priority Queue (우선순위 큐) | Selects a record according to a priority rule. |
| Comparator (비교 규칙) | Decides which of two records precedes the other. |
| Stable tie-breaking (안정적 동률 처리) | Preserves arrival order among equal priorities. |
| Baseline (기준 구현) | Simple reference used to compare results and work. |
| Complete binary tree (완전 이진 트리) | Full levels except possibly the last, filled from the left. |
| Minimum binary Heap (최소 이진 힙) | Complete binary tree with no child preceding its parent. |
| Sift-up (위로 이동하며 복구) | Repairs the path from an appended record toward the root. |
| Sift-down (아래로 이동하며 복구) | Repairs downward through the earlier existing child. |
| Amortized cost (분할상환 비용) | Total work spread across a sequence of operations. |

The binary Heap is a data structure. The C dynamic-memory heap is an
allocation area. Sharing a name does not make them the same concept.

## Coding Plan

The supplied baseline establishes the behavior. Complete the Heap's three
TODO sections while keeping that behavior and its failure guarantees.

1. **Read the comparator and baseline.** Follow priority, then arrival
   sequence. Trace the full scan and final-record replacement.
2. **Check Heap order.** Validate the output and Queue shape. Compare every
   non-root record with its parent. Count every comparison and publish the
   Boolean result after the scan.
3. **Insert with sift-up.** Validate and check limits before growth. Build a
   complete candidate. Move parents down along one path. Place the candidate
   before updating `size` and `next_sequence`.
4. **Inspect the root.** Reject an empty Queue and copy `data[0]` on success.
   The supplied implementation needs no record comparisons.
5. **Extract with sift-down.** Save the root and final candidate. Use the new
   size for child boundaries. Select the earlier existing child before
   comparing it with the candidate. Publish the saved output last.
6. **Compare results and work.** Run the supplied baseline and completed Heap
   separately. Use the seven arrivals above. Snapshot the counter before
   each operation and again before its checker call.

## C Code

### How is the ordering rule written?

The supplied implementations use the same helper. It compares complete
records and ignores the alert ID.

```c
static bool alert_record_precedes(
    const AlertRecord *left,
    const AlertRecord *right
)
{
    if (left->priority != right->priority) {
        return left->priority < right->priority;
    }
    return left->arrival_sequence < right->arrival_sequence;
}
```

### How does the reference find its minimum?

The baseline calls this helper only after confirming that the Queue is
valid and nonempty. `count_record_comparison` increments the counter unless
it has reached `SIZE_MAX`.

```c
static size_t find_minimum_index(AlertPriorityQueue *queue)
{
    size_t minimum_index = 0U;
    size_t index;

    for (index = 1U; index < queue->size; ++index) {
        count_record_comparison(queue);
        if (alert_record_precedes(
                &queue->data[index],
                &queue->data[minimum_index]
            )) {
            minimum_index = index;
        }
    }
    return minimum_index;
}
```

The Heap replaces this repeated search with root inspection and path repair.
Implement the three numbered TODOs in `code/starter/alert_priority_queue.c`
using the plan and traces above. The supplied scan implementation is in the
opening package and in Stage E's `code/baseline/` directory.

### How does the checker visit every parent relationship?

After validating `out_is_min_heap` and the Queue shape, the implementation
starts with `bool result = true` and a `size_t child`. It scans every child
even after detecting a violation. The excerpt returns a result only after
finishing the scan.

```c
for (child = 1U; child < queue->size; ++child) {
        size_t parent = (child - 1U) / 2U;

        count_record_comparison(queue);
        if (alert_record_precedes(
                &queue->data[child],
                &queue->data[parent]
            )) {
            result = false;
        }
    }

    *out_is_min_heap = result;
    return ALERT_PRIORITY_QUEUE_OK;
```

### How does insertion repair one upward path?

This excerpt follows successful validation, limit checks, and any required
growth in `alert_priority_queue_insert`. Those checks return before changing
records when an insertion fails. `candidate` is an `AlertRecord` and `index`
is a `size_t`. Every parent comparison includes the stopping comparison.

```c
candidate.alert_id = alert_id;
    candidate.priority = priority;
    candidate.arrival_sequence = queue->next_sequence;
    index = queue->size;

    while (index > 0U) {
        size_t parent = (index - 1U) / 2U;

        count_record_comparison(queue);
        if (!alert_record_precedes(
                &candidate,
                &queue->data[parent]
            )) {
            break;
        }

        queue->data[index] = queue->data[parent];
        index = parent;
    }

    queue->data[index] = candidate;
    queue->size += 1U;
    queue->next_sequence += 1U;
    return ALERT_PRIORITY_QUEUE_OK;
```

### How does inspection avoid comparisons?

After checking the output address, Queue shape, and nonempty state,
`alert_priority_queue_peek_min` copies the root. `result` is an `AlertRecord`.
The output changes only on success.

```c
result = queue->data[0];
*out_record = result;
return ALERT_PRIORITY_QUEUE_OK;
```

### How does extraction choose an existing child?

This excerpt follows successful validation and the nonempty check in
`alert_priority_queue_extract_min`. `result` and `candidate` are
`AlertRecord` variables. `new_size` and `hole` are `size_t` variables, with
`hole` initially 0. Child positions use the reduced size. The right child is
compared only when it exists.

```c
result = queue->data[0];
    new_size = queue->size - 1U;

    if (new_size > 0U) {
        candidate = queue->data[new_size];

        for (;;) {
            size_t left = hole * 2U + 1U;
            size_t selected;
            size_t right;

            if (left >= new_size) {
                break;
            }

            selected = left;
            right = left + 1U;
            if (right < new_size) {
                count_record_comparison(queue);
                if (alert_record_precedes(
                        &queue->data[right],
                        &queue->data[left]
                    )) {
                    selected = right;
                }
            }

            count_record_comparison(queue);
            if (!alert_record_precedes(
                    &queue->data[selected],
                    &candidate
                )) {
                break;
            }

            queue->data[hole] = queue->data[selected];
            hole = selected;
        }

        queue->data[hole] = candidate;
    }

    queue->size = new_size;
    if (new_size == 0U) {
        queue->next_sequence = 0U;
    }
    *out_record = result;
    return ALERT_PRIORITY_QUEUE_OK;
```

### How can the same caller check both backends?

The public service operations are shared. Build the following caller
separately against each backend's header and implementation. It checks every
status and uses the same seven arrivals.

```c
#include "alert_priority_queue.h"

int main(void)
{
    const int ids[] = {71, 88, 42, 17, 26, 9, 63};
    const size_t priorities[] = {3U, 1U, 2U, 1U, 4U, 2U, 1U};
    const int expected[] = {88, 17, 63, 42, 9, 71, 26};
    AlertPriorityQueue queue = {0};
    AlertRecord next = {0};
    int result = 1;
    size_t i;

    if (alert_priority_queue_init(&queue) != ALERT_PRIORITY_QUEUE_OK) {
        return result;
    }
    for (i = 0U; i < 7U; ++i) {
        if (alert_priority_queue_insert(&queue, ids[i], priorities[i]) !=
            ALERT_PRIORITY_QUEUE_OK) {
            goto cleanup;
        }
    }
    if (alert_priority_queue_peek_min(&queue, &next) !=
        ALERT_PRIORITY_QUEUE_OK || next.alert_id != 88) {
        goto cleanup;
    }
    for (i = 0U; i < 7U; ++i) {
        if (alert_priority_queue_extract_min(&queue, &next) !=
            ALERT_PRIORITY_QUEUE_OK || next.alert_id != expected[i]) {
            goto cleanup;
        }
    }
    result = 0;

cleanup:
    alert_priority_queue_destroy(&queue);
    return result;
}
```

`goto cleanup` transfers control to the labeled cleanup block. Every path
after initialization releases the owned allocation. Failed operations leave
the Queue available for that cleanup. The Heap also supplies
`alert_priority_queue_is_min_heap`; call it separately when collecting
checker evidence. Submit one Heap implementation and the comparison record
for this combined module.
