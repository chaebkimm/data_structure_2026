# Week 4 — Integer Stack and Postfix Evaluation: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

Required scope: trace the current `student/lab.c` integer Stack, its
forward growth with item count `size` and full/empty preconditions. First use the PPT’s direct
calculation of `1-2*3+4` to explain why a number Stack remembers values while
an operator Stack remembers waiting operations. Then convert `1-2*3+4` to
`123*-4+` and evaluate it as -1 in the lab’s two separate phases. Describe
the supported-input assumptions and missing validation accurately. The older
checked integer API is optional legacy material.

Sources: [Module 4 teaching-package overview](../module_04_stack/README.md),
[Module 4 vocabulary](../module_04_stack/student/vocabulary.md), and
[Weeks 1–7 question view](01_weeks_01_07_questions.md).

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| Stack | A collection whose accessible end is the top. |
| last in, first out (LIFO) | The newest remaining item is the first item removed. |
| top | The accessible end; its nonempty index is `size - 1` in this source. |
| `push` | Write integer data at `size`, then increment `size`; caller ensures room. |
| `peek` | Return the top integer without removal; caller ensures nonempty. |
| `pop` | Decrement `size`, then return integer `stack[size]`; caller ensures nonempty. |
| empty Stack | No active items; `size == 0`. |
| underflow | An inspection/removal request made while empty. |
| full Stack | Ten active items; `size == 10`. |
| fixed capacity | A number of available positions that does not grow. |
| item count | `size` for the integer Stack. |
| capacity | Ten positions here; the variable controls the full check but does not resize the array. |
| active prefix | Shared Stack indexes 0 through `size - 1`. |
| inactive slot | A physical array cell outside the active prefix. |
| invariant | A rule true in every valid completed state, here `0 <= size <= capacity`. |
| representation | The physical storage and variables implementing the access rule. |
| contract | Input assumptions, effects, returns, and preserved state. |
| global state | Shared variables declared outside the functions. |
| state preservation | Leaving state unchanged, as with a predicate or a valid peek. |
| sentinel | A real bottom `'\0'` item in conversion, later drained as the output terminator. |
| function label | An abstract name used to model unfinished work. |
| runtime call stack | Runtime bookkeeping for actual active function calls. |
| operand | A number used by an operator. |
| operator | A symbol such as `+`, `-`, `*`, `/`, or `%`. |
| precedence | The priority used to order operations. |
| equal precedence | Two operators with the same priority level. |
| left associativity | Applying equal-precedence operators from left to right. |
| infix | Expression notation with an operator between operands. |
| postfix | Expression notation with an operator after its operands. |
| conversion | Rearranging infix tokens into postfix order. |
| expression evaluator | Code that computes a number from expression tokens. |
| number Stack | Shared `int stack[10]` reused for numeric operands and results during evaluation. |
| operator Stack | The same global integer Stack holding operator codes and the bottom sentinel during conversion. |
| single-digit operand | One character from `'0'` through `'9'` converted to a number. |
| token | One operand or operator character. |
| grammar | The allowed order and kinds of tokens. |
| input assumption | A condition the current code expects without necessarily checking. |
| null terminator | The `'\0'` character marking the end of a C string. |
| postfix length | Seven token characters, excluding the terminator at `eq_re[7]`. |
| `size` | Shared global item count and next insertion index, reset at each expression phase. |
| `pos` | Local conversion cursor, ending at 8 after seven tokens and the sentinel are written. |
| intermediate result | A numeric result used by a later operation, such as -5. |
| time complexity | How the amount of work changes with input length. |
| `O(1)` | A fixed amount of work or reserved storage in this program. |
| `O(n)` | Work proportional to token count `n`. |

## Anticipated student questions

### Meaning and mental model

- Why must the newest saved item leave before older items?
- How do push, peek, and pop differ?
- Why can LIFO behavior stay the same when array indexes grow in a different direction?
- How is the explicit integer Stack different from runtime call bookkeeping?

### Representation and invariants

- Which indexes are active when `size == 3`, and how many items are stored?
- Why does push write `stack[size]` before incrementing, while peek reads `stack[size - 1]`?
- Why may an inactive cell still contain a character after pop?
- Why are `size == 0` and `size == 10` the empty and full states respectively?

### Operations and C API

- Why must callers avoid full push even though `is_full()` exists?
- Which out-of-bounds index would empty peek/pop select, and why is no return value promised?
- Why does `pop()` decrement `size` before reading `stack[size]`, without erasing the old cell?
- How does `capacity` control the full check without resizing the actual ten-position array?

### Tracing

- What indexes and states result from pushing `'A'`, `'B'`, and `'C'`?
- What do peek and two pops return after those three pushes?
- Why does `size` equal the count, while the nonempty top index is `size - 1`?
- How can a snapshot show that a boundary predicate preserves state without calling an invalid operation?

### Expression conversion and evaluation

- How does `1-2*3+4` become `123*-4+` before any numeric evaluation occurs?
- Why does incoming `+` cause both waiting `*` and `-` to be emitted?
- Why must evaluation pop right operand `num2` before left operand `num1`?
- How do shared global `size`, local output cursor `pos`, and token length describe different state?
- Why does conversion count the sentinel in `size` and finish with `pos == 8`?

### Tests and debugging

- Which tests distinguish empty, one-item, and full Stack states?
- How can `8-3-2+1` distinguish left associativity from right associativity?
- Why can a faulty top read stay inside the physical array and still be wrong?
- Why do repeated seven-character conversions and prior active items test shared-state reset and termination?

### Complexity

- Why do push, peek, and pop each take `O(1)` time?
- Why does pop require no shifting?
- Why is conversion `O(n)` despite its inner operator-pop loop?
- Why is evaluation `O(n)`, and how do the current fixed buffers bound storage?

### Safety and interpretation

- Why do the fixed seven-iteration loops require exactly seven token characters, even for a shorter valid mathematical expression?
- Which syntax restrictions are assumptions rather than validated rejections in this source?
- Why must divisors be nonzero and intermediate integer results be representable?
- How does the stored `'\0'` sentinel prevent an empty peek during valid conversion?

### Assignment and evidence

- How do the lab driver and current tests use `student/lab.c`?
- What LIFO, boundary, and valid-expression cases provide three distinct additions to `test_lab.c`?
- Which warning and sanitizer outputs should accompany the trace evidence?
- What must an autopsy explanation distinguish about physical bounds and the active prefix?

### Transfer and prerequisites

- How does this active prefix reuse Chapter 1's count and next-insertion convention?
- How can a later Stack use pointer items while preserving the same LIFO rule?
- How does delaying operators illustrate remembering unfinished work?
- Why does `c - '0'` turn a digit character into a numeric operand?

### Extension questions — optional

- How could explicit error reporting safely reject unsupported characters and missing operands?
- What additional parsing rules and buffers would multi-digit operands require?
- How would parentheses change the operator-Stack algorithm?
- How does the optional legacy caller-owned integer API share the active-prefix layout but differ in ownership and error reporting?
