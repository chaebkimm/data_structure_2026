# Week 4 — Character Stack and Postfix Evaluation: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

Required scope: trace the current `student/lab.c` character Stack, its
forward next-insertion position and full/empty behavior, then convert `1-2*3+4` to
`123*-4+` and evaluate it as -1 using a separate integer value Stack. Describe
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
| top | The accessible end; its nonempty index is `pos - 1` in this source. |
| `push` | Write one character at `pos`, then increment `pos`. |
| `peek` | Return the top character without removal. |
| `pop` | Decrement `pos`, then read and return the character there. |
| empty Stack | No active characters; `pos == 0`. |
| underflow | An inspection/removal request made while empty. |
| full Stack | Ten active characters; `pos == 10`. |
| fixed capacity | A number of available positions that does not grow. |
| item count | `pos` for the character Stack. |
| capacity | Ten positions here; the variable controls the full check but does not resize the array. |
| active prefix | Character-Stack indexes 0 through `pos - 1`. |
| inactive slot | A physical array cell outside the active prefix. |
| invariant | A rule true in every valid completed state, here `0 <= pos <= capacity`. |
| representation | The physical storage and variables implementing the access rule. |
| contract | Input assumptions, effects, returns, and preserved state. |
| global state | Shared variables declared outside the functions. |
| state preservation | Leaving `pos` and all stored characters unchanged on a boundary request. |
| sentinel | A special returned value, here `'\0'` on an empty read. |
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
| number Stack | Local `int values[10]` containing operands and results. |
| operator Stack | Global character Stack holding waiting operators during conversion. |
| single-digit operand | One character from `'0'` through `'9'` converted to a number. |
| token | One operand or operator character. |
| grammar | The allowed order and kinds of tokens. |
| input assumption | A condition the current code expects without necessarily checking. |
| null terminator | The `'\0'` character marking the end of a C string. |
| postfix length | Global `size`, excluding the terminating null character. |
| `pos` | The next insertion index and count; global for `stack`, separately local for `values`. |
| intermediate result | A numeric result used by a later operation, such as -5. |
| time complexity | How the amount of work changes with input length. |
| `O(1)` | A fixed amount of work or reserved storage in this program. |
| `O(n)` | Work proportional to token count `n`. |

## Anticipated student questions

### Meaning and mental model

- Why must the newest saved item leave before older items?
- How do push, peek, and pop differ?
- Why can LIFO behavior stay the same when array indexes grow in a different direction?
- How is the explicit character Stack different from runtime call bookkeeping?

### Representation and invariants

- Which indexes are active when `pos == 3`, and how many characters are stored?
- Why does push write `stack[pos]` before incrementing, while peek reads `stack[pos - 1]`?
- Why may an inactive cell still contain a character after pop?
- Why are `pos == 0` and `pos == 10` the empty and full states respectively?

### Operations and C API

- What does a full push do, and why does it return no value?
- What do empty peek and pop return, and which state stays unchanged?
- Why does a successful pop decrement `pos` before reading, without erasing its old cell?
- How does `capacity` control the full check without resizing the actual ten-position array?

### Tracing

- What indexes and states result from pushing `'A'`, `'B'`, and `'C'`?
- What do peek and two pops return after those three pushes?
- Why does `pos` equal the count, while the nonempty top index is `pos - 1`?
- How can an array snapshot prove that a full push changed nothing?

### Expression conversion and evaluation

- How does `1-2*3+4` become `123*-4+` before any numeric evaluation occurs?
- Why does incoming `+` cause both waiting `*` and `-` to be emitted?
- Why must evaluation pop right operand `num2` before left operand `num1`?
- How do global `pos`, global `size`, and local `pos` describe different state?

### Tests and debugging

- Which tests distinguish empty, one-item, and full Stack states?
- How can `8-3-2` distinguish left associativity from right associativity?
- Why can a faulty top read stay inside the physical array and still be wrong?
- Why do repeated conversion and a shorter replacement expression test both reset and termination?

### Complexity

- Why do push, peek, and pop each take `O(1)` time?
- Why does pop require no shifting?
- Why is conversion `O(n)` despite its inner operator-pop loop?
- Why is evaluation `O(n)`, and how do the current fixed buffers bound storage?

### Safety and interpretation

- Why do eight-character input and output arrays allow at most seven token characters?
- Which syntax restrictions are assumptions rather than validated rejections in this source?
- Why must divisors be nonzero and intermediate integer results be representable?
- Why can an empty-read sentinel be ambiguous if a caller stores `'\0'` as data?

### Assignment and evidence

- How do the lab driver and current tests use `student/lab.c`?
- What LIFO, boundary, and valid-expression cases provide three distinct additions to `test_lab.c`?
- Which warning and sanitizer outputs should accompany the trace evidence?
- What must an autopsy explanation distinguish about physical bounds and the active prefix?

### Transfer and prerequisites

- How does this active prefix reuse Chapter 1's count and next-insertion convention?
- How can a later Stack use integer or pointer items while preserving LIFO?
- How does delaying operators illustrate remembering unfinished work?
- Why does `c - '0'` turn a digit character into a numeric operand?

### Extension questions — optional

- How could explicit error reporting safely reject unsupported characters and missing operands?
- What additional parsing rules and buffers would multi-digit operands require?
- How would parentheses change the operator-Stack algorithm?
- How does the optional legacy caller-owned integer API share the active-prefix layout but differ in ownership and error reporting?
