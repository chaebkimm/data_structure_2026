# Week 4 — Stack and Nested Delimiters: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

Required scope: specify the Stack ADT independently of storage, implement a checked ArrayList-backed character Stack, validate nested delimiters under a depth limit, preserve state and outputs on failure, analyze costs, and distinguish the Stack ADT from runtime call bookkeeping and stack memory.

Sources: [Module 4 teaching-package overview](../module_04_stack/README.md), [Module 4 full vocabulary reference](../module_04_stack/student/vocabulary.md), and [Weeks 1–7 anticipated-question source](01_weeks_01_07_questions.md).

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| abstract data type (ADT) | A behavior contract defined independently of one storage method. |
| Stack ADT | A collection that adds, observes, and removes items at one accessible end. |
| backend | The lower-level storage used to implement an ADT. |
| top | The accessible end of a Stack. |
| last in, first out (LIFO) | The most recently pushed item is the first item popped. |
| `push` | Add one item at the top. |
| `peek` | Report the top item without removing it. |
| `pop` | Remove and report the top item. |
| empty Stack | A Stack containing no items and therefore having no top. |
| underflow | An attempt to `peek` or `pop` an empty Stack. |
| ArrayList-backed Stack | A Stack whose items are stored in a resizable contiguous array. |
| size | The number of logical items currently in the Stack. |
| capacity | The number of allocated item slots. |
| limit | The greatest Stack size allowed by the task. |
| invariant | A rule that holds in every valid completed Stack state. |
| contract | Rules stating what an operation accepts, changes, reports, and preserves. |
| status code | A named result reporting success or one kind of failure. |
| output parameter | Caller-provided storage in which a function writes a result. |
| failure atomicity | A failed operation leaves the complete prior valid state unchanged. |
| allocation failure | The program could not obtain requested memory. |
| ownership | Responsibility for keeping allocated storage valid and eventually releasing it. |
| geometric growth | Increasing capacity by a multiplying factor to reduce the frequency of reallocations. |
| delimiter | A symbol that begins or ends a grouped part of input. |
| opening delimiter | One of `(`, `[`, or `{` in this week. |
| closing delimiter | One of `)`, `]`, or `}` in this week. |
| unresolved opening | An opening delimiter whose closing partner has not appeared. |
| delimiter validator | An algorithm that checks whether grouping marks are properly nested. |
| unmatched closing delimiter | A closing delimiter encountered when the Stack is empty. |
| mismatch | A closing delimiter that does not match the opening at the top. |
| leftover opening delimiter | An opening delimiter still on the Stack when input ends. |
| nesting limit | The maximum number of unresolved openings permitted at once. |
| depth-limit error | Rejection before an opening would exceed the nesting limit. |
| error index | The numbered input position where the validator reports a problem. |
| resource boundary | A stated limit on how much storage or time a task may use. |
| resource exhaustion | Input attempts to consume more of a limited resource than permitted. |
| trace | A step-by-step record of changing state. |
| `O(1)` | A fixed amount of work as input size grows. |
| `O(n)` | Work that may grow in proportion to an input size `n`. |
| amortized `O(1)` | Constant average work across a sequence with occasional expensive growth. |
| runtime call stack | Bookkeeping commonly used by C for active function calls. |
| call frame | Saved information for one active function call. |
| stack memory | An informal name for a memory region commonly used for calls and local variables. |
| stack-buffer overflow | An out-of-bounds write past a buffer in the commonly named stack-memory region. |
| depth-first search (DFS) | An exploration method that can use LIFO storage for unfinished choices. |

## Anticipated student questions

### Meaning and mental model

- What behavior makes a collection a Stack regardless of how it is stored?
- Why does “last in, first out” match nested opening and closing delimiters?
- What is the difference among the Stack ADT, the C runtime call stack, and a stack-allocated array?
- Why is the top at `data[size - 1]` rather than `data[size]`?

### Representation and invariants

- Which relationships among `data`, `size`, `capacity`, and `limit` must always hold?
- What is the valid representation of a zero-limit Stack?
- Why may capacity be below limit without making the Stack invalid?
- What facts about pointer liveness, allocation extent, and unique ownership can `char_stack_validate` not establish?

### Operations, C API, and ownership

- What must `push`, `pop`, and `peek` do when passed an invalid Stack or invalid output pointer?
- Why must `pop` and `peek` leave `out_value` unchanged on underflow or any other failure?
- Why must `out_value` not point into the Stack’s character allocation?
- How does `char_stack_destroy` reset ownership, and when is calling it legal?

### Tracing

- How do `data`, `size`, `capacity`, and top change across pushes that trigger growth?
- What Stack trace results from the text `a[(b)]`, including ignored characters?
- At which index should the validator report an unmatched close, mismatch, unclosed open, or depth-limit failure?
- What state should remain after a forced allocation failure during `push`?

### Tests and debugging

- Which separate tests exercise underflow, exact limit, growth to a clipped capacity, and allocation failure?
- How can a test prove `peek` observes the top without removing it?
- In the Stack Autopsy, why does reading `data[size]` inspect the slot after the top?
- Which stack-level and delimiter-level regression tests would catch that off-by-one defect?

### Complexity

- Why are `pop` and `peek` worst-case `O(1)`?
- Why is `push` amortized `O(1)` but not worst-case `O(1)` in this representation?
- For text length `n` and maximum nesting depth `d`, why are the validator’s time and extra space expressed separately?
- How would a linked Stack change growth behavior, allocation frequency, and cache locality?

### Cybersecurity and interpretation

- Why is an explicit nesting-depth limit useful when input is untrusted?
- Could a syntactically balanced delimiter string still contain malicious or invalid content?
- How can ignored non-delimiter characters affect what security claim the validator is allowed to make?
- Why must allocation failure and excessive nesting produce distinct, checked statuses?

### Assignment and evidence

- Which `char_stack.c` and `delimiter_validator.c` TODOs are required for Week 4?
- What three student-test categories would demonstrate distinct Stack and validator claims?
- Why must every initialized temporary Stack be destroyed on every return path?
- What should the Stack-to-depth-first-exploration explanation establish without implementing DFS yet?

### Transfer and prerequisites

- Which ArrayList growth and failure-atomicity ideas are reused in the Stack backend?
- What changes when a later typed Stack stores vertex IDs or node pointers instead of characters?
- How can a Stack remember unfinished branches during depth-first exploration?
- Which C concepts should I review if pointer/output contracts in `pop` and `peek` are unclear?

### Extension questions — optional

- How would a fixed-array Stack differ from this growable Stack when the limit is known in advance?
- Could the validator report the matching opening index as well as the closing error index?
- How would quoted strings or escaped delimiters change the parsing state beyond a simple Stack?
- Are parser features beyond `()`, `[]`, `{}`, ignored characters, and the depth policy required this week?
