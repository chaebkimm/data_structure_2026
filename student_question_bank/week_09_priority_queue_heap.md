# Week 9 — Priority Queue Contract to Binary Heap: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

## Required scope for the 14-week course

Module 10 contributes the stable-minimum Priority Queue contract, comparator,
tie rule, unsorted-array trace, and cost baseline. The instructor supplies its
verified unsorted-array implementation; students inspect it rather than complete
or submit a separate Module 10 project. Module 11 is the main lab: students
implement the Heap backend, test sifting and stable ties, check the Heap
invariant, and compare its work with the supplied reference. These parts form
**one combined Week 9 artifact**, with one rubric and one due date.

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| abstract data type (ADT) | Public behavior and operations described independently of one storage method. |
| Priority Queue | An ADT that reports or removes the waiting record ranked first. |
| priority | A number used to rank service; this course serves smaller numbers first. |
| minimum-priority rule | The record with the smaller numeric priority is selected first. |
| record | One value grouping related named fields. |
| field | One named part of a record. |
| insert | Add one record to the Priority Queue. |
| `peek_min` | Report the selected minimum record without removing it. |
| `extract_min` | Remove and report the selected minimum record. |
| tie | Two records having equal priority. |
| stable tie behavior | Equal-priority records leave in their successful arrival order. |
| arrival sequence | An increasing number assigned at successful insertion to break priority ties. |
| comparator | The exact rule deciding which of two records comes first. |
| deterministic | Producing the same public result from the same completed state and ordering rule. |
| backend | A storage and implementation method used to provide an ADT. |
| supplied reference implementation | Instructor-provided working code used as a baseline and expected-result model. |
| unsorted array | Contiguous storage not maintained in service order. |
| physical position | One actual array index. |
| logical service order | The order promised by the ADT, independent of physical positions. |
| scan | Inspect live positions one by one. |
| candidate minimum | The best record found so far during a baseline scan. |
| comparison count | The number of times the record comparator is applied. |
| workload | A selected mixture and order of operations used for comparison. |
| binary tree | A hierarchy with at most two child positions per node. |
| complete binary tree | A tree whose levels are full except possibly the last, which fills left to right without gaps. |
| binary Heap | A complete binary tree stored compactly and arranged by a priority rule. |
| minimum Heap (min-Heap) | A Heap whose first-ranked record is at the root. |
| root | The top Heap node, stored at array index 0. |
| parent | The Heap node directly above a child. |
| child | A Heap node directly below a parent. |
| array index relationship | A parent or child location calculated from its 0-based array index. |
| implicit relationship | A tree relationship calculated from positions rather than stored with pointers. |
| Heap-order invariant | No child record comes before its parent under the comparator. |
| partial order | Only required parent-child relationships are ordered; the full array need not be sorted. |
| globally sorted array | An array whose every record is in total comparator order. |
| append | Place a new record at the end of the live Heap array. |
| swap | Exchange two complete records. |
| sift-up | Repair Heap order from a newly appended record toward the root. |
| better child | The existing child that comes first under the comparator. |
| sift-down | Repair Heap order from the root toward a leaf. |
| leaf | A Heap node with no children. |
| one-child case | The complete-tree case in which a node has a left child but no right child. |
| invariant checker | A diagnostic operation that checks every required Heap relationship. |
| mutation | An operation that changes stored state. |
| instrumentation | Extra measurement or checking added for study and debugging. |
| normal-operation count | Comparator work measured separately from diagnostic checker work. |
| differential test | A test that applies the same requests to two implementations and compares public results. |
| reference model | A simpler implementation used to supply expected results in a differential test. |
| geometric growth | Increasing array capacity by a multiplying factor when more storage is needed. |
| ownership | Responsibility for releasing allocated storage exactly once. |
| failure preservation | A failed operation leaves protected prior state and caller output unchanged. |
| integrity | Stored state still obeys all required rules. |
| corruption | An unintended state change that breaks a required rule. |
| `O(1)` | Work bounded independently of the number of live records. |
| `O(log n)` | Work proportional to the height of a complete binary tree. |
| `O(n)` | Work that may inspect all `n` live records. |
| starvation | A waiting item is postponed indefinitely because other items continue to rank ahead of it. |
| C dynamic-memory heap | The allocation region used by C; it is different from the binary Heap data structure. |
| combined artifact | The single Week 9 submission containing Heap code, tests, traces, and backend comparison. |

### Optional vocabulary for extension questions

| Term | Working meaning |
|---|---|
| student-written unsorted backend | An optional reimplementation of the Module 10 baseline, which is supplied in the required path. |
| bottom-up heap construction | Building a Heap by sifting internal nodes downward instead of repeatedly inserting every record. |
| decrease-key | Lowering a priority already stored in a Priority Queue and repairing its backend. |
| maximum Heap (max-Heap) | A Heap whose comparator places the greatest-ranked record at the root. |
| mutable priority | A priority allowed to change while its record waits. |

## Anticipated student questions

### Meaning and mental model

- How is a Priority Queue different from the FIFO Queue used for BFS?
- What does "minimum" mean under the course's alert-priority convention?
- What makes the Priority Queue stable when two priorities are equal?
- Why can two storage backends implement the same Priority Queue ADT?
- What does a binary Heap promise that a globally sorted array does not?

### Representation and invariants

- Which public record fields and service rules must remain identical across the supplied unsorted backend and the Heap backend?
- What makes the array representation a complete binary tree?
- How are a nonroot node's parent and its possible child indexes calculated?
- What exact parent-child relationship defines the stable minimum-Heap invariant?
- Why can a valid minimum Heap contain an array that is not globally sorted?
- Which Queue fields describe owned storage, logical size, capacity, arrival sequence, and diagnostic comparison work?

### Operations, C API, and ownership

- Why is the Module 10 unsorted-array implementation supplied rather than student-written in Week 9?
- What happens to a complete Heap and caller output if growth allocation fails during insertion?
- Why can Heap `peek_min` return the root without performing record comparisons?
- What steps must extraction perform before and during sift-down?
- Why must output storage for a returned record not point inside the Queue's allocation?
- What does `alert_priority_queue_destroy` own, release, and reset?

### Tracing

- How does the supplied unsorted baseline insert, inspect the minimum, and remove the minimum?
- Given an insertion sequence, where is each new Heap record appended and which comparisons cause it to sift upward?
- Given a root extraction, which record moves to index 0 and how is the smaller child chosen during sift-down?
- How should sift-down behave when a node has a left child but no right child?
- How do equal priorities and arrival sequences determine swaps during a Heap trace?
- Which fields may change during extraction even though the public service behavior remains unchanged?

### Testing and debugging

- Which focused tests isolate sift-up, sift-down, stable ties, and the one-child case?
- How can `alert_priority_queue_is_min_heap` expose a local order violation after a mutation?
- Why must checker comparisons be measured separately from normal-operation comparisons?
- How can randomized differential testing compare the Heap against the supplied unsorted reference without assuming identical internal arrays?
- What bug would occur if sift-down compared only priorities and ignored arrival sequence?

### Complexity

- What are the insertion, minimum-inspection, and minimum-removal costs of the supplied unsorted-array baseline?
- Why are Heap insertion and extraction `O(log n)` while Heap minimum inspection is `O(1)`?
- Why is a Heap's height logarithmic in its number of records?
- Which workload would make the unsorted baseline competitive, and which workload would favor the Heap?

### Security and interpretation

- How can an incorrect priority calibration cause unfairness or starvation even when the data structure is correct?
- Why is stable tie handling a policy guarantee rather than a security authorization decision?
- How could unchecked index arithmetic or a missing-child read corrupt Heap behavior or memory?

### Assignment and evidence

- What belongs in the single combined Week 9 submission?
- Why is there no separate student implementation or submission for Module 10 in the 14-week path?
- Which traces and tests demonstrate the complete-tree indexes, stable comparator, sift behavior, and Heap invariant?
- What comparison evidence fairly distinguishes the supplied baseline's costs from the Heap backend's costs?

### Transfer

- Why can Dijkstra use the Priority Queue contract without depending on whether its backend is an unsorted array or Heap?
- How does Heap order differ from the strict ordering rule of a BST or AVL tree?
- How do comparison counts provide evidence about backend choice without proving wall-clock performance on every machine?
- What failure-preservation ideas transfer from dynamic arrays to both Priority Queue backends?

### Extension questions

- How would you implement the unsorted-array Priority Queue while preserving the same public contract?
- How could bottom-up heap construction differ from repeated insertion?
- What interface changes would a decrease-key Heap require?
- How would a maximum-oriented Heap change the comparator and invariant while retaining the same array geometry?

## Sources

- [14-week delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md)
- [Master spiral curriculum](../Data_Structures_Course_2026_Spiral_Curriculum.md)
- [Original Weeks 8–14 question bank](02_weeks_08_14_questions.md)
- [Module 10 baseline role](../module_10_priority_queue/README.md)
- [Module 10 vocabulary reference](../module_10_priority_queue/student/vocabulary.md)
- [Module 11 main-lab role](../module_11_binary_heap/README.md)
- [Module 11 vocabulary reference](../module_11_binary_heap/student/vocabulary.md)
