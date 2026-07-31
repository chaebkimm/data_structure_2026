# Module 7 Vocabulary

Use this page after Stage A. Each definition is written for a first course.

| Term | Working definition |
|---|---|
| data structure | A planned way to organize information |
| abstract data type (ADT) | A collection described by its operations and rules, independent of storage method |
| Queue | An ADT that removes the earliest-added item first |
| first in, first out (FIFO) | Earliest added is earliest removed; this preserves arrival order rather than sorting values |
| front | The oldest Queue item |
| back | The newest Queue item |
| `enqueue` | Add an item at the back |
| `peek` | Report the front without removing it |
| `dequeue` | Remove and report the front |
| empty | Having no current items |
| full | Having `size == capacity` |
| underflow | An attempted report or removal while empty |
| overflow | An attempted addition that cannot fit under the selected policy |
| Stack | An ADT that removes the newest-added item first |
| last in, first out (LIFO) | Newest added is earliest removed |
| array | A numbered row of same-type values |
| buffer | Bounded temporary storage |
| circular buffer | An array representation that reuses beginning positions after reaching the physical end |
| physical index | One actual numbered array position |
| logical order | The order in which current items belong to the ADT |
| capacity | The fixed number of physical positions in this Queue |
| `head` | The physical index of the front item when the Queue is not empty |
| `size` | The number of current logical items |
| tail | The next physical insertion index, not the newest item's index |
| derived | Calculated from stored facts rather than stored separately |
| remainder (`%`) | What remains after whole-number division |
| wrap-around | Continuing at index 0 after the physical end |
| `LIVE` | A physical value that currently belongs to the Queue |
| `STALE` | A physical value left after its logical item was removed |
| `UNUSED` | A position that has not stored an item in the current trace |
| invariant | A rule true in every valid completed state |
| struct | A C type that groups named fields |
| pointer | A value that stores a memory address |
| `NULL` | A pointer value meaning “points to no object” |
| `size_t` | C's nonnegative whole-number type for counts and indexes |
| allocation | A storage block obtained while a program runs |
| ownership | Responsibility for releasing obtained storage |
| shallow copy | A field-only copy that duplicates a pointer, not the owned allocation |
| function | A named block of instructions that performs one task |
| API | The set of functions other program parts may call |
| caller | The program part requesting a function |
| output location | Caller-provided storage where a function writes a result |
| contract | A rule stating what a function accepts, changes, reports, and preserves |
| status code | A named result reporting success or one kind of failure |
| validation | Checking whether visible state follows stated rules |
| failure preservation | A failed operation leaves the prior valid state and protected output unchanged |
| retention policy | A rule stating which information is kept when storage is full |
| reject newest | Refuse the attempted addition and preserve current items |
| discard oldest | Remove the longest-waiting item to make room |
| backpressure | Ask a source to slow or stop producing work |
| shifting array Queue | A Queue that moves remaining array items after a removal |
| node | A separately stored object holding an item and one or more links |
| linked Queue | A Queue made from linked nodes, usually with front and back pointers |
| time complexity | A description of how work grows with input or collection size |
| `O(1)` | A fixed amount of work |
| `O(n)` | Work that may grow with `n` items |
| synthetic | Invented for safe practice |
| regression test | A test kept so a repaired defect does not return |
| breadth-first search (BFS) | A later algorithm that explores shallower levels before deeper levels |

## EventQueue statuses

The interface lists these named results in this exact order:

1. `EVENT_QUEUE_OK` — success.
2. `EVENT_QUEUE_INVALID_ARGUMENT` — a required Queue or output is invalid.
3. `EVENT_QUEUE_LIMIT` — requested capacity is above 64.
4. `EVENT_QUEUE_FULL` — no item fits under the reject-newest policy.
5. `EVENT_QUEUE_EMPTY` — no item exists to report or remove.
6. `EVENT_QUEUE_ALLOCATION` — requested storage could not be obtained.
7. `EVENT_QUEUE_INVALID_STATE` — visible fields break the invariant.
