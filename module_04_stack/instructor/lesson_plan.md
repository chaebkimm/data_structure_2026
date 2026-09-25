# Instructor Lesson Plan — Module 4: Integer Stack and Postfix Evaluation

## Purpose and limits

Students discover last-in, first-out behavior through an unfinished-function
story, then study its concrete implementation in `student/lab.c`. The current
Stack is a global ten-integer array whose top moves toward larger indexes
on push. The expression work has two phases:

```text
1-2*3+4  ->  123*-4+  ->  -1
 infix       postfix     result
```

One global integer array stores operator character codes and a sentinel
during conversion, then numbers and intermediate results during evaluation. The old checked integer
library remains an optional comparison; it is not the required source or API.

Use the PPT's direct two-Stack calculation as the bridge: on incoming `+`,
reduce `2*3` to 6 and then the equal-precedence `1-6` to -5 before saving
`+`. After reading 4, the final addition yields -1. Recording the operators
at these calculation times gives `123*-4+`; the C lab generates that order
first and evaluates it afterward.

By the end, students should be able to:

1. state LIFO independently of its representation;
2. trace `'A'`, `'B'`, and `'C'` through push, peek, and pop;
3. explain `0 <= size <= capacity`, active indexes `0..size - 1`, and count `size`;
4. explain full/empty predicates and the unchecked caller preconditions;
5. distinguish logical removal from clearing stored characters;
6. convert valid infix text to postfix using precedence and left associativity;
7. evaluate postfix using integer values and right-before-left operand pops;
8. distinguish shared global `size`, local conversion cursor `pos`, and token length; and
9. describe input assumptions and missing validation accurately.

## Instructor setup

Before Meeting A:

- verify that Stage A contains only its README and two inquiry formats;
- choose the standard or linear format and prepare visible character cards;
- preserve the abstract function-call story before revealing representation;
- keep vocabulary closed until the timed response is preserved; and
- run the current lab demo, lab tests, and isolated autopsy using `code/README.md`.

Before Meeting B, confirm that `make lab-demo` and `make lab-tests` use
`student/lab.c`. The equivalent PowerShell targets are `lab` and `lab-tests`.
Record actual results; legacy test totals do not validate the current source.
The demo should show infix `1-2*3+4`, postfix `123*-4+`, and result -1.
Keep instructor answers and optional legacy solution/extension files out of
the student release.

## Beginner language sequence

Introduce terms just before use; do not require memorized glossary wording.

| Concept | Plain-language entry point |
|---|---|
| state and data structure | Information remembered and a way to organize it |
| Stack, top, LIFO | One accessible end; newest remaining item leaves first |
| push, peek, pop | Add; inspect; remove and report |
| character and integer | A symbol such as `'3'` versus the number 3 |
| active prefix | The occupied part from 0 through `size - 1` |
| index versus count | Where the newest item lives versus how many items remain |
| full/empty preconditions | No room to add; no item to inspect or remove |
| infix and postfix | An operator between operands versus after its operands |
| precedence and associativity | Which operation goes first and how equal priorities are ordered |
| terminator and length | `'\0'` ends a C string; it is excluded from token count |
| assumption and validation | What a caller must provide versus what code actually checks |

Name each state variable precisely: shared global `size` counts active
Stack items in either phase; local conversion cursor `pos` advances for every
`eq_re` write and ends at 8, while token length is 7. The conversion sentinel
is a stored item, later drained as the terminator at `eq_re[7]`; it is not an
empty-read return. Both phases reset `size`. `capacity` affects `is_full()`
only; changing it neither resizes the array nor guards push.

## Five release gates

Preserve attempt before explanation. Standard and linear formats retain the
same learning targets.

| Gate | Release point | Give students | Keep back |
|---|---|---|---|
| A — Inquiry | Start of Meeting A | One inquiry format | Formal vocabulary, representation, code, answers |
| B — Representation | After the initial return-order model is preserved | Representation reveal and three-target Cognitive Pause; vocabulary after the response is preserved | Investigation answers, textbook, code |
| C — Investigation | After pause and calibration | One investigation format | Textbook, completed model, code |
| D — Calibrated explanation | After investigation responses are preserved | Textbook and equivalent Stack models | Autopsy answer, lab, instructor files |
| E — Lab and evidence | Meeting B after retrieval | Lab, source, driver, tests, evidence, rubric, autopsy prompt, build files | Instructor answers and optional legacy solution/extension material |

An accommodation may change timing, response mode, or meeting location while
preserving attempt, preserve, compare, and revise. Accept spoken, typed,
handwritten, or diagrammed reasoning. Do not grade drawing skill or response
speed.

## Meeting A — Discover LIFO and index direction (90 minutes)

Macro-Question:

> If the newest unfinished task must finish first, what access rule should
> the program enforce?

| Minutes | Activity | Instructor move | Evidence |
|---:|---|---|---|
| 0–5 | Welcome | Explain that names and code follow the initial model | Boundary restatement |
| 5–18 | Gate A inquiry | Follow abstract Functions 100, 200, 300 | Initial return-order model |
| 18–27 | Compare | Preserve the first response beside its correction | 200 resumes, then 100 |
| 27–38 | Gate B behavior | Introduce LIFO and push/peek/pop using A, B, C | Character trace |
| 38–45 | Reveal storage | Label all ten indexes; push at 0, 1, 2 as `size` becomes 1, 2, 3 | Active prefix and count |
| 45–50 | Cognitive Pause | Give exactly the three supplied targets; repeat directions only | Individual response |
| 50–59 | Calibrate | Open vocabulary after preservation; compare trace and boundaries | Labeled corrections |
| 59–70 | Operations | Contrast boundary predicates, caller preconditions, and valid reads | Contract table |
| 70–79 | State cases | Explain why the full position 10 is not an array cell | Index/count explanations |
| 79–86 | Expression transfer | Introduce the two phases and distinct storage roles | Infix/postfix/result distinction |
| 86–90 | Exit and Gate C | Release one investigation format | Top formula and boundary behavior |

### Exactly three Cognitive Pause targets

1. Trace `push('A'), push('B'), push('C'), peek, pop, pop, pop`; record
   integer returns shown as character labels, `size`, count, and logical order.
2. Diagnose independent full push, empty peek, and empty pop cases on paper;
   identify the invalid index and why no result or final state is promised.
3. Explain `1-2*3+4 -> 123*-4+ -> -1` and distinguish operator codes and the
   sentinel from numeric values stored in the same array in the later phase.

Do not add a fourth target or reveal a worked trace during the pause.

### Meeting A checks and misconceptions

| Misconception | Neutral question | Calibration after attempt |
|---|---|---|
| `size` is the current top index | What are the count and top index after one push? | `size = 1`, top index 0 |
| Top is `stack[size]` | Which index holds the most recent pushed character? | `size` increased after the write; read `stack[size - 1]` |
| Pop must erase | Which state change removes membership? | Decrementing `size` makes the old cell inactive |
| Empty is `size == 10` | Where does the first push begin? | Empty 0; full 10 |
| `pos` describes the Stack | Which assignment changes `pos`? | Every output write, including the sentinel |
| Both phases store the same kind of data | Where can intermediate -5 be kept? | In reused `int stack[10]`, after resetting `size` |

## Meeting B — Read, run, and explain both phases (90 minutes)

Coding question:

> How do the stored state and the order of updates produce the promised
> result for valid input?

| Minutes | Activity | Instructor move | Evidence |
|---:|---|---|---|
| 0–8 | Retrieval | Trace A, B, C without notes | Correct top and count |
| 8–14 | Gate D calibration | Compare textbook and physical models | Annotated corrections |
| 14–20 | Gate E orientation | Locate `student/lab.c`, driver, and current tests | Package map |
| 20–31 | Stack operations | Trace caller preconditions, index change, read/write order | Predicate and valid-transition snapshots |
| 31–43 | Conversion | Append digits; compare incoming and waiting precedence | Per-token table |
| 43–51 | Finish and reuse | Drain sentinel; explain final `pos == 8`; reset shared `size` on each phase | Repeated seven-character conversion evidence |
| 51–64 | Evaluation | Convert digits; pop right before left; store integer result | `123*-4+` evaluation table |
| 64–71 | Assumptions | Identify unsupported syntax and missing checks by reading | Accurate limits statement |
| 71–79 | Three added tests | Add LIFO, boundary, and valid-expression cases with rationale | Distinct evidence |
| 79–86 | Stack-Top Autopsy | Preserve prediction, run, compare active/inactive indexes | First broken rule |
| 86–90 | Submit | Check evidence, corrections, and complexity | Completion checklist |

## Core input boundary

Use exactly seven characters: four single digits alternating with three
`+ - * / %` operators, followed by a terminator in `eq[7]`. Exclude spaces,
parentheses, unary signs, multi-digit operands, zero divisors, and integer
arithmetic outside `int`. Shorter strings are unsupported by the fixed loops.
Both phases reset shared `size`; conversion also pushes a bottom sentinel.
These conditions are assumed, not validated.

Use `8-3-2+1` to test left associativity and `8/2/2+1` to expose operand order
and equal precedence. Evaluation pops right operand `num2` before left
operand `num1`. Explain integer division before assigning `/` or `%` examples.

Keep malformed-input cases and invalid full/empty operations as paper
diagnoses. A checked parser, arithmetic guards, status reporting, and variable
input lengths are extensions. The current source has no safe rejection
contract or evaluator output parameter.

## Stack-Top Autopsy facilitation — instructor only

Use ten cells: `'+'` at index 0, `'*'` at index 1, and eight `'?'` characters,
and `size = 2`. Students predict before running. Correct `stack[size - 1]` returns
`'*'`; faulty `stack[size]` returns inactive `'?'` at index 2. That faulty
read is physically inside the array but logically outside the active prefix.
A sanitizer need not report it. At full capacity, the faulty read would
select out-of-bounds `stack[10]`. Explain the first broken rule, then choose
a fresh top/inactive pair for a regression case. Keep this answer out of
Stage D diagrams and all earlier releases.

## Assessment and feedback

Use the current 100-point rubric. Prioritize correct LIFO/index reasoning,
full/empty preconditions, both expression phases, operand order, and evidence from
three distinct added cases. Require an honest account of assumptions and
missing validation. The current tests include canonical conversion, boundary
predicates, associativity/operand order, shared-state reset, and character-to-integer
conversion; students extend `code/tests/test_lab.c`.

An incorrect first inquiry or pause answer is useful evidence when preserved
and meaningfully corrected. Use neutral prompts before giving hints; after
preservation, calibrate directly. Optional legacy API comparisons may follow
the core, but do not displace the beginner tracing work or become a second
required assignment.
