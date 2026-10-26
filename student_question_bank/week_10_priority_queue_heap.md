# Week 10 — Integer Heaps and Shared On-Time: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

## Required scope

The required source is [student/lab.c](../module_10_binary_heap/student/lab.c).
Students trace and test the supplied fixed integer min/max Heap, bottom-up
construction, and ten-device dual-Heap interval search. They submit one
driver/evidence artifact. The alert-record Heap and unsorted-array baseline
are optional references with separate contracts. They do not add required
allocation, stable-arrival, status, checker, or counter implementation tasks.
Use nonnegative closed intervals, with 1–5 ordered disjoint intervals for
each ID 0–9. The supplied code does not validate caller preconditions.

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| Priority Queue | A collection that selects by a comparison rule rather than FIFO arrival. |
| binary Heap | A complete binary tree whose parent-child order keeps an extreme at the root. |
| complete binary tree | Levels fill from left to right without gaps in the active array. |
| active prefix | The positions from 0 through size-1 currently in use. |
| min Heap | Each parent value is no greater than either child value. |
| max Heap | Each parent value is no less than either child value. |
| mode flag | is_min_heap selects <= for nonzero or >= for zero; it is not a checker. |
| root | Position 0, containing an extreme under the current valid Heap order. |
| parent index | (i-1)/2 for a valid non-root position i. |
| left-child index | 2*i+1, if that position exists. |
| right-child index | 2*i+2, if that position exists. |
| sentinel | The value -1 marks an absent position in relation helpers. |
| comparator | A function deciding whether the first value may remain above the second. |
| proper_parent | The helper selecting a winning position, with absent-position handling. |
| swap | Exchange the values at two positions. |
| Heap-order invariant | Every active parent-child pair follows the selected comparison rule. |
| partial order | Parent-child order does not require sorted siblings or a sorted full array. |
| sift-up | Repair one changed position along its ancestors; heapify_up in the lab. |
| sift-down | Repair toward the better existing child; heapify_down in the lab. |
| bottom-up construction | Build order by repairing internal nodes backward with heapify. |
| one-child case | A parent has a left child but no right child. |
| caller precondition | A required valid state that the supplied function does not enforce. |
| fixed capacity | Storage reserves ten positions and never grows. |
| closed interval | An on/off range that includes both endpoints. |
| endpoint | One on-time or off-time of an interval. |
| device ID | An integer 0–9 identifying one row of interval input. |
| epoch | The selected interval number for one ID, starting at 0. |
| interval count | interval_size[id] counts intervals, not endpoint cells. |
| accessor | A helper such as get_on_time that reads the current endpoint for an ID. |
| function pointer | A stored function choice, used for a Heap comparator or swap callback. |
| ID Heap | An array storing IDs whose priorities are obtained from current interval state. |
| inverse position map | An array mapping each ID back to its position in one Heap. |
| priority update | A key change requiring repair even though the stored ID stays the same. |
| direction-aware repair | Use the parent relationship to choose upward or downward repair. |
| latest on-time | The greatest current on endpoint, supplied by max_on_heap. |
| earliest off-time | The smallest current off endpoint, supplied by min_off_heap. |
| overlap | The chosen closed intervals share a time when latest on <= earliest off. |
| exhaustion | Advancing an ID beyond its last interval causes all_on_time to return -1. |
| O(log n) | A repair path grows with complete-tree height for generalized n. |
| O(n + A log n) | Generalized two-Heap construction and A epoch advances. |

### Optional reference vocabulary

| Term | Working meaning |
|---|---|
| stable alert record | Optional library record with priority and insertion-sequence tie-breaking. |
| unsorted baseline | Optional reference library that scans for its next alert. |
| dynamic allocation | Optional library storage obtained and later released through C allocation. |
| comparison counter | Optional library instrumentation absent from student/lab.c. |
| decrease-key interface | A possible extension for changing a selected stored priority. |

## Anticipated student questions

### Meaning and representation

- How does priority selection differ from FIFO arrival order?
- What complete-tree shape does the active array prefix represent?
- Why can a valid min Heap have siblings in either numeric order?
- What does is_min_heap select, and why is it not an invariant checker?
- How do parent, left, and right distinguish a missing position with -1?
- Why does proper_parent return a position rather than a stored value?
- What does the first-argument tie behavior guarantee, and why is FIFO stability not guaranteed?

### Integer operations and tracing

- Where does add place a new value before heapify_up begins?
- Which parent relationships change while adding 1 after 7,3,5?
- What active prefix results from adding 7,3,5,1,9,4?
- Which replacement and child choices produce the first root removal?
- How does heapify_down avoid reading a missing right child?
- Why does singleton removal safely call heapify_down with size zero?
- Why must a caller prevent empty removal and insertion into ten live slots?
- Why must changing the min/max flag on existing values be followed by heapify?
- Why does bottom-up heapify begin at parent(size-1)?

### Interval input and Heap callbacks

- What do the paired cells in toggle_info[id] contain?
- How do interval_size and epoch differ?
- Why must every ID have one through five chronologically ordered valid intervals?
- What do max_on_heap.array and min_off_heap.array store?
- Why do full-Heap comparators receive IDs while basic comp receives positions?
- What function choices are stored in Heap_Full.comp and Heap_Full.swap?
- Why are the fixed full-Heap child helpers different from the size-based helpers?

### Maps and local repair

- What does array[position_map[id]] == id assert?
- Why does each Heap need its own inverse position map?
- Which two map entries must __swap__ update?
- How can stale maps break a later repair even when current Heap order looks valid?
- Why does one epoch change require repairs in both Heaps?
- When does _reheapify choose up, and when does it choose down?
- What assumptions make one-direction repair sufficient after a key change?

### Overlap and correctness

- Why do the latest current on-time and earliest current off-time decide overlap?
- Why does equality count as success for closed intervals?
- Which ID must advance when latest on is greater than earliest off?
- Why can advancing an earliest-off interval not skip a valid common time?
- Which bounds occur in the canonical trace before the answer 8?
- Why does exhaustion return before reading the next endpoint?
- Why must callers avoid current-time accessors after an exhaustion return?
- What does a fresh all_on_time call reset?

### Testing, costs, and transfer

- Which tests check duplicates, max mode, singleton removal, and a left-only child?
- How can a driver check both Heap order and inverse-map consistency?
- Which ten-ID fixtures distinguish immediate overlap, delayed overlap, endpoint equality, and exhaustion?
- Why is bottom-up build O(n) while repeated insertion can take O(n log n)?
- Why is the generalized search O(n + A log n) with O(n) auxiliary storage?
- How do fixed ten-ID storage and at most five intervals bound the literal program?
- How does Heap parent-child order differ from the BST search order taught later?
- What belongs in the single Week 10 driver, trace, test, and correction submission?
- Which allocation, stable-tie, and counter claims belong only to the optional alert library?

## Sources

- [Current Module 10 lab](../module_10_binary_heap/student/lab.c)
- [Teaching package](../module_10_binary_heap/README.md)
- [14-week delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md)
- [Module vocabulary](../module_10_binary_heap/student/vocabulary.md)
