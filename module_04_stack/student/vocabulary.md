# Module 4 Vocabulary — Stage B Reference

Open this page after completing and preserving the Cognitive Pause.

| Term | Plain-language definition |
|---|---|
| state | The information a program currently remembers |
| data structure | A planned way to organize information in a program |
| abstract data type (ADT) | A description of a collection through its allowed operations and rules, independent of one storage method |
| Stack ADT | An ADT that permits adding, inspecting, and removing at one end |
| top | The one accessible end of a Stack |
| last in, first out (LIFO) | The most recently added item is the first item that may be removed |
| operation | One task provided by a data structure |
| `push` | Add one item at the top |
| `peek` | Report the top item without removing it |
| `pop` | Remove and report the top item |
| empty Stack | A Stack containing no items and therefore having no top |
| underflow | An attempt to `peek` or `pop` an empty Stack |
| representation | A chosen way to store or show information |
| backend | The lower-level storage used to implement an ADT |
| ArrayList | A resizable numbered sequence |
| character | One symbol; C uses the type `char` to store one character |
| array | A numbered row of matching stored values |
| index | A numbered position; C begins numbering at zero |
| address | A value identifying a location in computer memory |
| pointer | A value that stores an address |
| `NULL` | A pointer value meaning “no storage address” |
| `size` | The number of logical items currently in the Stack |
| `capacity` | The number of allocated character slots |
| `limit` | The greatest Stack size permitted for the task |
| nesting limit | The maximum number of unresolved openings permitted at once |
| logical item | A value that currently belongs to a collection |
| allocation | A block of computer memory obtained while a program runs |
| ownership | Responsibility for eventually releasing requested storage |
| shallow copy | A field-by-field copy that duplicates a pointer but not the separate allocation it identifies |
| invariant | A rule that is true in every valid completed state |
| contract | Rules stating what an operation accepts, changes, reports, and preserves |
| status code | A named result reporting success or one kind of failure |
| caller | The part of a program that asks a function to run |
| output location | Caller-provided storage in which a function writes a result |
| failure atomicity | A failed operation leaves the complete prior valid state unchanged |
| allocation failure | The program could not obtain requested memory |
| resource boundary | A stated limit on how much time or storage a task may use |
| resource exhaustion | Input attempts to consume more of a limited resource than permitted |
| delimiter | A mark that begins or ends a group |
| opening delimiter | One of `(`, `[`, or `{` in this module |
| closing delimiter | One of `)`, `]`, or `}` in this module |
| unresolved opening | An opening delimiter whose closing partner has not appeared |
| delimiter validator | A procedure that checks grouping marks |
| unmatched closing delimiter | A closing delimiter encountered when no opening is available |
| mismatch | A closing delimiter that does not partner with the opening at the top |
| leftover opening delimiter | An opening delimiter still present when input ends |
| depth-limit error | Rejection before an opening would exceed the nesting limit |
| malformed input | Input that breaks stated form rules |
| error index | The numbered input position at which a validator reports a problem |
| `out_error_index` | The caller-provided location where the delimiter validator writes an error index |
| `SIZE_MAX` | The greatest `size_t` value, used here as the success output meaning “there is no error index” |
| trace | A step-by-step record of changing state |
| time complexity | A description of how work grows as input grows |
| `O(1)` | A fixed amount of work |
| `O(n)` | Work that may grow in proportion to an input amount `n` |
| amortized `O(1)` | Constant average work across a sequence, including occasional expensive operations |
| runtime call stack | Bookkeeping commonly used by a C implementation for active function calls |
| call frame | Saved information for one active function call |
| recursion | A function calling itself directly or through other functions |
| stack memory | An informal name for a memory region many implementations use for calls and local variables |
| buffer | A bounded area that stores a sequence of values |
| stack-buffer overflow | An out-of-bounds write past a buffer in the commonly named stack-memory region |
| algorithm | A precise, step-by-step method |
| depth-first search (DFS) | A later tree/graph exploration algorithm that can use LIFO storage for unfinished work |
| `STACK_OK` | The Stack operation succeeded |
| `STACK_INVALID_ARGUMENT` | A required Stack or output location was invalid |
| `STACK_LIMIT` | `push` would exceed the explicit limit, or initialization requested a limit above 1024 |
| `STACK_UNDERFLOW` | `peek` or `pop` was requested while empty |
| `STACK_ALLOCATION` | The ArrayList could not obtain needed storage |
| `STACK_INVALID_STATE` | The stored fields broke the Stack invariant |
| `DELIMITER_OK` | The complete input has valid delimiters |
| `DELIMITER_INVALID_ARGUMENT` | A required validator argument was invalid |
| `DELIMITER_UNMATCHED_CLOSE` | A closing delimiter appeared while the Stack was empty |
| `DELIMITER_MISMATCH` | A closing delimiter did not partner with the opening at the top |
| `DELIMITER_UNCLOSED_OPEN` | Input ended with at least one opening delimiter left |
| `DELIMITER_DEPTH_LIMIT` | An opening delimiter would have exceeded the nesting limit |
| `DELIMITER_ALLOCATION` | The validator's character Stack could not obtain needed storage |
