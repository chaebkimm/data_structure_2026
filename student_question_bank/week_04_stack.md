# Week 4 — Fixed-Capacity Stack and Expression Precedence: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

Required scope: specify last-in-first-out behavior, implement checked push,
peek, and pop over a caller-owned fixed integer array, preserve state and
outputs after rejection, trace function IDs, and evaluate alternating
single-digit expressions containing only `+` and `*` with two fixed Stacks.

Sources: [Module 4 teaching-package overview](../module_04_stack/README.md),
[Module 4 vocabulary](../module_04_stack/student/vocabulary.md), and
[Weeks 1–7 question view](01_weeks_01_07_questions.md).

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| Stack | A collection whose accessible end is the top. |
| last in, first out (LIFO) | The most recently pushed item is the first item popped. |
| top | The one end used for Stack access. |
| `push` | Add one item at the top. |
| `peek` | Report the top without removing it. |
| `pop` | Remove and report the top. |
| empty Stack | A Stack with size zero and no top item. |
| underflow | A rejected peek or pop requested while empty. |
| full Stack | A Stack whose size equals its capacity. |
| fixed capacity | A maximum number of available array slots that does not grow. |
| size | The number of active Stack items. |
| capacity | The fixed usable array bound supplied by the caller. |
| active prefix | Array indexes zero through `size - 1`. |
| inactive slot | An allocated array position at or above `size`. |
| metadata | The size and capacity values describing the Stack. |
| invariant | A rule true in every valid completed state. |
| representation | The fixed array plus its separate metadata. |
| contract | Rules for accepted input, changes, reports, and preserved state. |
| caller | Code that requests a Stack operation. |
| output parameter | Caller-provided storage in which a function writes a result. |
| rejection | A request that cannot be completed under the contract. |
| state preservation | Keeping the complete prior state after rejection. |
| valid metadata | Integer values satisfying `0 <= size <= capacity`. |
| call frame | Saved information for one active function call. |
| runtime call stack | Runtime bookkeeping for unfinished function calls. |
| function ID | A simplified integer label used in the chapter trace. |
| operand | A number used by an operator. |
| operator | A symbol such as `+` or `*` that combines operands. |
| precedence | A rule deciding which waiting operator is applied first. |
| equal precedence | Two operators with the same priority level. |
| expression | A sequence of operands and operators. |
| expression evaluator | Code that computes a value from a supported expression. |
| number Stack | The evaluator's Stack of numbers and intermediate results. |
| operator Stack | The evaluator's Stack of waiting operators. |
| single-digit operand | One character from `0` through `9` used as a number. |
| token | One operand or operator read from the expression. |
| grammar | The allowed order and kinds of tokens. |
| malformed input | Input that does not follow the supported grammar. |
| arithmetic overflow | A result outside the range of C type `int`. |
| current character | The expression character being processed now. |
| null terminator | The `\0` character that ends a C string. |
| time complexity | A description of how work changes with input size. |
| `O(1)` | A fixed amount of work. |
| `O(n)` | Work that may grow in proportion to input length `n`. |

## Anticipated student questions

### Meaning and mental model

- Why must the newest saved item leave before older items?
- How do push, peek, and pop differ?
- Why is only one end called the top?
- How is the course Stack related to, but different from, runtime call bookkeeping?

### Representation and invariants

- Which array indexes belong to a Stack with size 3 and capacity 10?
- Why is the top at `stack[size - 1]` rather than `stack[size]`?
- Why may an inactive slot still contain an old integer?
- What goes wrong when size is negative or greater than capacity?

### Operations and C API

- What does push return when the Stack is full or metadata is invalid?
- Why must peek leave size and every array slot unchanged?
- Why can pop remove an item by decreasing size without erasing its cell?
- Which failures must leave the caller's output value unchanged?

### Tracing

- What states result from pushing 100, 200, and 300 in that order?
- What do peek and two pops report after those three pushes?
- What remains active after the first pop, and what remains physically stored?
- How can a snapshot prove that a rejected push changed nothing?

### Expression evaluation

- Why does `1+2*3` evaluate to 7 rather than 9?
- What is stored in the number and operator Stacks after each character?
- When must a waiting operator be applied before a new operator is pushed?
- Why are spaces, parentheses, multi-digit numbers, and other operators rejected?

### Tests and debugging

- Which tests distinguish empty, one-item, and full Stack states?
- How can a test prove that zero is ordinary Stack data?
- Why does the faulty-top autopsy read an inactive slot without leaving the array?
- Which malformed-expression tests exercise token order and unsupported characters?

### Complexity

- Why do checked push, peek, and pop each take `O(1)` time?
- Why does pop require no shifting?
- Why does evaluating an expression of length `n` take `O(n)` time?
- Why does this evaluator use bounded additional space even for a longer valid input?

### Safety and interpretation

- Why must the caller's array contain at least capacity elements?
- Why can a function validate metadata but not discover the array's physical length?
- How does checked integer arithmetic prevent undefined signed overflow?
- Why does a valid result establish only the supported arithmetic grammar and value?

### Assignment and evidence

- Which `int_stack.c` and `expression_evaluator.c` TODOs are required?
- What three student-test categories provide nonduplicate evidence?
- Which warning and sanitizer commands should be recorded?
- What must the corrected autopsy explanation distinguish about size and capacity?

### Transfer and prerequisites

- Which Chapter 1 active-prefix and rejection rules are reused?
- How will later Stacks change the item type while preserving LIFO behavior?
- How can LIFO storage remember unfinished choices in later traversal work?
- Which pointer concepts should I review for checked output parameters?

### Extension questions — optional

- How could a checked evaluator support subtraction while preserving operand order?
- What additional rules would multi-digit operands require?
- How would parentheses change the operator-Stack algorithm?
- How would a growable backend change the representation without changing LIFO behavior?
