# Instructor Lesson Plan — Module 4: Character Stack and Postfix Evaluation

## Purpose and limits

Students discover last-in, first-out behavior through an unfinished-function
story, then study its concrete implementation in `student/lab.c`. The current
Stack is a global ten-character array whose top moves toward smaller indexes
on push. The expression work has two phases:

```text
1-2*3+4  ->  123*-4+  ->  -1
 infix       postfix     result
```

The operator Stack stores characters. A separate local integer array stores
numbers and intermediate results during evaluation. The old checked integer
library remains an optional comparison; it is not the required source or API.

By the end, students should be able to:

1. state LIFO independently of its representation;
2. trace `'A'`, `'B'`, and `'C'` through push, peek, and pop;
3. explain `0 <= top <= 10`, active indexes `top..9`, and count `10 - top`;
4. explain full push as a silent no-op and empty peek/pop as `'\0'` returns;
5. distinguish logical removal from clearing stored characters;
6. convert valid infix text to postfix using precedence and left associativity;
7. evaluate postfix using integer values and right-before-left operand pops;
8. distinguish `top`, postfix `size`, and integer `pos`; and
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
The demo should show infix `1-2*3+4`, postfix `123*-4+`, size 7, result -1.
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
| active suffix | The occupied part from `top` through index 9 |
| index versus count | Where the newest item lives versus how many items remain |
| full/empty behavior | No room to add; no item to inspect or remove |
| infix and postfix | An operator between operands versus after its operands |
| precedence and associativity | Which operation goes first and how equal priorities are ordered |
| terminator and length | `'\0'` ends a C string; it is excluded from token count |
| assumption and validation | What a caller must provide versus what code actually checks |

Avoid using “size” without naming the object. In this source global `size`
means postfix output length. Use `10 - top` for character-Stack count and
`pos` for integer-Stack count. `capacity` is declared as 10 but changing it
alone does not alter the hardcoded array or empty check.

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
| 38–45 | Reveal storage | Label all ten indexes; push from 10 to 9 to 8 | Active suffix and count |
| 45–50 | Cognitive Pause | Give exactly the three supplied targets; repeat directions only | Individual response |
| 50–59 | Calibrate | Open vocabulary after preservation; compare trace and boundaries | Labeled corrections |
| 59–70 | Operations | Contrast no-op full push, empty sentinel, and successful reads | Contract table |
| 70–79 | State cases | Explain why empty marker 10 is not an array cell | Index/count explanations |
| 79–86 | Expression transfer | Introduce the two phases and distinct storage roles | Infix/postfix/result distinction |
| 86–90 | Exit and Gate C | Release one investigation format | Top formula and boundary behavior |

### Exactly three Cognitive Pause targets

1. Trace `push('A'), push('B'), push('C'), peek, pop, pop, pop`; record
   character returns, `top`, count, and logical order.
2. Diagnose independent full push, empty peek, and empty pop cases; state what
   changes and what remains unchanged.
3. Explain `1-2*3+4 -> 123*-4+ -> -1` and distinguish the character operator
   Stack from the integer value Stack.

Do not add a fourth target or reveal a worked trace during the pause.

### Meeting A checks and misconceptions

| Misconception | Neutral question | Calibration after attempt |
|---|---|---|
| `top` is the count | What are both values after one push? | `top = 9`, count 1 |
| Top is `stack[top - 1]` | Which index holds the most recent pushed character? | Decrement happened before the write; read `stack[top]` |
| Pop must erase | Which state change removes membership? | Incrementing `top` makes the old cell inactive |
| Empty is `top == 0` | Where does the first push begin? | Empty 10; full 0 |
| `size` describes the character Stack | Which assignment changes `size`? | Appending postfix text |
| Both phases store the same kind of data | Where can the intermediate -5 be kept? | In `int values[10]` |

## Meeting B — Read, run, and explain both phases (90 minutes)

Coding question:

> How do the stored state and the order of updates produce the promised
> result for valid input?

| Minutes | Activity | Instructor move | Evidence |
|---:|---|---|---|
| 0–8 | Retrieval | Trace A, B, C without notes | Correct top and count |
| 8–14 | Gate D calibration | Compare textbook and physical models | Annotated corrections |
| 14–20 | Gate E orientation | Locate `student/lab.c`, driver, and current tests | Package map |
| 20–31 | Stack operations | Trace guard, index change, read/write order | Boundary snapshots |
| 31–43 | Conversion | Append digits; compare incoming and waiting precedence | Per-token table |
| 43–51 | Finish and reuse | Drain operators; reset `size`; write terminator | Repeated/shorter conversion evidence |
| 51–64 | Evaluation | Convert digits; pop right before left; store integer result | `123*-4+` evaluation table |
| 64–71 | Assumptions | Identify unsupported syntax and missing checks by reading | Accurate limits statement |
| 71–79 | Three added tests | Add LIFO, boundary, and valid-expression cases with rationale | Distinct evidence |
| 79–86 | Stack-Top Autopsy | Preserve prediction, run, compare active/inactive indexes | First broken rule |
| 86–90 | Submit | Check evidence, corrections, and complexity | Completion checklist |

## Core input boundary

Use nonempty expressions of at most seven characters: single digits
alternating with `+`, `-`, `*`, `/`, or `%`, without spaces, parentheses, unary
operators, or multi-digit numbers. Divisors must be nonzero; integer
intermediates must be representable. The initial operator Stack must be
empty. The source assumes these conditions and does not safely reject every
violation.

For conversion, `>=` sends equal-precedence operators to output from left to
right. For evaluation, `num2` is the right operand popped first. Use `8-3-2`
to test associativity and `8/2` to expose swapped operands. Explain C integer
division before assigning division or remainder examples.

Keep unsafe malformed-input cases as paper diagnoses in core work. A
checked parser, arithmetic guards, explicit status reporting, and arbitrary
input lengths are extensions. Do not claim checked-output preservation for
this source: it has neither an evaluator output parameter nor an error status.

## Stack-Top Autopsy facilitation — instructor only

Use ten cells: eight `'?'` characters, `'*'` at index 8, `'+'` at index 9,
and `top = 8`. Students predict before running. Correct `stack[top]` returns
`'*'`; faulty `stack[top - 1]` returns inactive `'?'` at index 7. That faulty
read is physically inside the array but logically outside the active suffix.
A sanitizer need not report it. Explain the first broken rule, then choose
a fresh top/inactive pair for a regression case. Keep this answer out of
Stage D diagrams and all earlier releases.

## Assessment and feedback

Use the current 100-point rubric. Prioritize correct LIFO/index reasoning,
full/empty behavior, both expression phases, operand order, and evidence from
three distinct added cases. Require an honest account of assumptions and
missing validation. The current tests include canonical conversion, boundary
behavior, associativity/operand order, reuse, and character-to-integer
conversion; students extend `code/tests/test_lab.c`.

An incorrect first inquiry or pause answer is useful evidence when preserved
and meaningfully corrected. Use neutral prompts before giving hints; after
preservation, calibrate directly. Optional legacy API comparisons may follow
the core, but do not displace the beginner tracing work or become a second
required assignment.
