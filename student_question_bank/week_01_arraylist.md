# Week 1 — ArrayList and Linked-Node Preview: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

Required scope: initialize and clean up an ArrayList, complete and explain safe reserve/growth, implement checked access and append, preserve state on failure, analyze costs, and compare contiguous storage with a linked-node preview. Insertion and removal are optional extensions.

Sources: [Module 1 teaching-package overview](../module_01_arraylist/README.md), [Module 1 full vocabulary reference](../module_01_arraylist/student/vocabulary.md), and [Weeks 1–7 anticipated-question source](01_weeks_01_07_questions.md).

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| ArrayList | A resizable sequence whose elements are stored in one contiguous allocation. |
| logical element | A value the list currently considers part of the collection. |
| size | The number of logical elements currently stored. |
| capacity | The number of element slots currently allocated. |
| allocation | A block of storage obtained while the program runs. |
| contiguous storage | Storage in one uninterrupted sequence of memory locations. |
| linked node | A separately stored item that contains a value and a link to another item. |
| pointer | A value that stores a memory address. |
| `NULL` | A pointer value meaning that no object or allocation is referenced. |
| interior pointer | A pointer to a location inside an allocation rather than to its beginning. |
| stale pointer | An address that no longer refers to the intended live object. |
| ownership | Responsibility for keeping storage valid and eventually releasing it. |
| invariant | A rule that must hold in every valid observable state. |
| canonical empty state | The one agreed field combination used to represent an empty structure. |
| bounds check | A check that an index is inside the permitted range before memory is accessed. |
| reserve | Ensure space for at least a requested capacity without changing the logical elements. |
| geometric growth | Increasing capacity by a multiplying factor so growth happens less often. |
| reallocation | Replacing or resizing an allocation, possibly at a different address. |
| failure atomicity | An operation succeeds completely, or the previous valid state remains unchanged. |
| integer overflow | An arithmetic result falls outside the range its C type can represent. |
| amortized analysis | Averaging cost over a sequence that includes occasional expensive operations. |
| `O(1)` | Work bounded by a constant amount as the number of elements grows. |
| `O(n)` | Work that may grow in proportion to an input size `n`. |
| cache locality | The performance benefit of accessing values stored close together in memory. |
| pointer stability | Whether an address continues to identify the same live object after an operation. |
| segmentation fault | A program failure commonly caused by an invalid memory access. |
| sanitizer | A tool that detects certain memory, bounds, or undefined-behavior defects while code runs. |
| denial of service | Loss of availability caused by exhausting time, memory, or another resource. |

## Anticipated student questions

### Meaning and mental model

- What exactly is an ArrayList, and how is it different from an ordinary C array?
- If the elements remain in one block of memory, what part of the list actually “grows”?
- What is the difference between the list’s logical size and its physical capacity?
- Why should we describe the ArrayList behavior separately from the `IntList` representation?

### Representation and invariants

- Which `data`, `size`, and `capacity` combinations form the canonical empty state?
- Why must `size` never be greater than `capacity`?
- When may `data` legally be `NULL`, and what other fields must agree with it?
- What important facts about liveness, allocation extent, initialized elements, and unique ownership can `int_list_is_valid` not prove?

### Operations, C API, and ownership

- When is it legal to call `int_list_init`, and what happens if the object already owns storage?
- Why does `int_list_reserve` promise not to shrink the list or change its size?
- Why must `int_list_get` reject an output pointer that points inside the list’s own allocation?
- After a failed append or reserve, which pointer, size, capacity, and existing values must remain unchanged?

### Tracing

- Starting from `{NULL, 0, 0}`, how do the fields and memory contents change across several appends that trigger growth?
- What should a trace show when an append fits within the existing capacity?
- What should a trace show when `realloc` returns a different address from the original allocation?
- What happens to the original allocation and list state when a forced growth allocation fails?

### Tests and debugging

- Which empty-list, singleton, exact-capacity, and first-growth tests reveal different defects?
- How can a test prove that allocation failure preserves every part of the old list?
- What warning, sanitizer, or debugger evidence would help distinguish an out-of-bounds write from a stale-pointer use?
- In the Segfault Autopsy, why is assigning `realloc` directly to the owned pointer dangerous?

### Complexity

- Why is checked indexing `O(1)` even though the list may contain many elements?
- Why is one growth append `O(n)` while append is still described as amortized `O(1)`?
- What sequence of copied element counts supports the geometric-growth argument?
- How do contiguous storage and separately allocated linked nodes differ for indexing, insertion, cache locality, and pointer stability?

### Cybersecurity and interpretation

- How could an untrusted element count cause integer overflow before an allocation request?
- How could a stale interior pointer become a security or reliability problem after growth?
- Could repeated requests for enormous capacity become a denial-of-service concern even if memory access remains in bounds?
- Why does safe storage of synthetic event codes not prove that the codes themselves are trustworthy?

### Assignment and evidence

- Which functions are required in the Week 1 core, and which functions are not required?
- Why must each student-authored test add evidence beyond the supplied tests instead of renaming one?
- What must the saved test, warning, and sanitizer or debugger evidence demonstrate?
- If my program passes the happy-path tests but leaks memory on an error path, which rubric criteria are still unmet?

### Transfer and prerequisites

- Which C pointer, array, `struct`, and allocation ideas should I review before this lab?
- How will the `size`/`capacity` invariant return when we implement a Stack?
- Why does the linked-node preview matter before we study trees?
- When would stable node addresses matter more than constant-time indexing?

### Extension questions — optional

- Is `int_list_insert` at index `size` equivalent to append, and which boundary indexes must it reject?
- Why does `int_list_remove` shift later elements but leave capacity unchanged?
- How should insertion remain failure-atomic if growth is needed before shifting?
- Are insertion and removal required for the Week 1 submission or only for optional extension credit?
