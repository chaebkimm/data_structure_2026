# Instructor Lesson Plan — Module 4: Fixed-Capacity Stack

## Purpose and limits

This module introduces a **Stack**, a collection whose operations use one end,
the **top**. Students discover last-in, first-out behavior through function IDs
100, 200, and 300, represent that behavior with a caller-owned integer array,
and transfer it to the checked expression `1+2*3`.

The implementation deliberately stays small:

```c
int stack[10];
int size = 0;
int capacity = 10;
```

The operations request no storage, change no storage extent, and release no
storage. The module includes no structure-owned buffer, generic `void *`
container, linked backend, unrelated parser, or traversal application. Later
modules may reuse the LIFO behavior while choosing a different element type
or storage policy.

By the end, students should be able to:

1. state LIFO independently of the storage representation;
2. trace `push`, `peek`, and `pop` from bottom to top;
3. explain `0 <= size <= capacity` and `stack[size - 1]`;
4. implement the three checked integer-Stack operations;
5. prove that a rejection preserves the array, logical size, and required
   caller output;
6. distinguish logical removal from clearing physical bits;
7. evaluate the stated single-digit `+`/`*` grammar with precedence and left
   associativity;
8. reject malformed input, live Stack-capacity failure, and `int` overflow
   without changing the evaluator output; and
9. distinguish the Stack ADT, its local array representation, and the runtime
   call stack.

## Instructor setup

Before Meeting A:

- verify that Stage A contains only the two inquiry formats and its README;
- choose the standard or linear format for each learner;
- prepare cards labeled 100, 200, and 300 if a physical model is useful;
- keep Stage B vocabulary closed until the timed response is preserved; and
- build the solution and isolated autopsy using `code/README.md`.

Before Meeting B:

- confirm that the reference core reports 8 passing tests;
- confirm that the extension suite reports 5 passing tests;
- run the autopsy and record the deterministic 20-versus-777 result;
- confirm that student build files compile only starter sources; and
- keep `code/solution/`, `code/tests/test_extension.c`, and this instructor
  directory out of Stage E.

## Beginner language sequence

Introduce terms immediately before use. The student vocabulary has 40 terms;
do not require memorized definitions.

| Concept group | Plain-language entry point |
|---|---|
| state and data structure | Information the program remembers and a planned way to organize it |
| Stack ADT and top | A collection whose allowed access occurs at one end |
| LIFO | The newest remaining item is the first one removed |
| push, peek, pop | Add; report without removal; remove and report |
| empty, underflow, full | No logical item; empty inspection/removal; size equals capacity |
| array, index, logical item, inactive slot | Physical positions versus the positions currently counted by size |
| size and capacity | Current logical count versus prepared position count |
| caller-owned storage | The caller creates the array; operations borrow it |
| invariant and contract | A valid-state rule and each function's behavioral promise |
| rejection and preservation | Refusal before mutation; required information stays unchanged |
| expression terms | Digits, operands, operators, precedence, and left associativity |
| integer overflow | A mathematical result outside the C `int` range |
| regression test | A retained test that detects return of a repaired defect |

Use “full-Stack rejection” for this module's capacity result. If “stack
overflow” arises, separate it from runtime call-space exhaustion and from an
out-of-bounds buffer write.

## Five release gates

A **release gate** is a planned point at which the next materials become
available. Preserve attempt before explanation.

| Gate | Release point | Give students | Keep back |
|---|---|---|---|
| A — Inquiry | Start of Meeting A | One inquiry format | Formal Stack/LIFO vocabulary, representation, code, answers |
| B — Representation | After the initial return-order model is preserved | Representation reveal and three-target Cognitive Pause; vocabulary only after the response is preserved | Investigation answers, textbook, code |
| C — Investigation | After the pause and brief calibration | One investigation format | Textbook, completed model, code |
| D — Calibrated explanation | After Sections A–F are preserved | Textbook and equivalent Stack models | Autopsy answer, lab, solution, instructor files |
| E — Lab and evidence | Meeting B after retrieval | Lab, evidence form, rubric, autopsy prompt, public headers, starter, public tests, student-test template, build files | Solution, extension tests, instructor files and answers |

An accommodation may change timing, response mode, or meeting location. It
should preserve the sequence of attempt, preserve, compare, and revise. The
standard and linear files have the same targets.

---

# Meeting A — Discover LIFO and Fixed Stack State (90 minutes)

## Macro-Question

> If the most recently started unfinished task must finish first, what access
> rule should the program enforce?

| Minutes | Activity | Instructor move | Evidence |
|---:|---|---|---|
| 0–5 | Welcome and boundary | State that learners will name the access rule only after preserving an initial model. | Boundary restatement |
| 5–18 | Gate A inquiry | Release one inquiry format. Ask students to follow Functions 100, 200, and 300. | Initial return-order model |
| 18–27 | Compare models | Ask which unfinished function resumes after 300. Preserve corrections beside original work. | Justified answer: 200, then 100 |
| 27–38 | Gate B representation | Define Stack, top, LIFO, push, peek, pop, underflow, and full. | Labeled behavior model |
| 38–45 | Reveal fixed storage | Show `int stack[10]`, separate size/capacity, active indexes, and the top formula. | Physical/logical distinction |
| 45–50 | Five-minute Cognitive Pause | Give exactly the three supplied targets. Repeat directions only. | Individual preserved response |
| 50–59 | Correct and compare | Calibrate trace, boundary preservation, and expression transfer. Open vocabulary after preservation. | Labeled corrections |
| 59–70 | Operation contracts | Trace successful and rejected calls. Ask what each return means. | Complete contract table |
| 70–79 | Invariant cases | Classify empty, nonempty, full, negative metadata, and size beyond capacity. | Valid/invalid explanations |
| 79–86 | `1+2*3` transfer | Use number and operator cards. Leave `+` waiting while `*` takes precedence. | Two-Stack trace and result 7 |
| 86–90 | Exit and Gate C | Release one investigation format. Ask for the top formula and one preservation promise. | Two-sentence exit response |

## Stage B Cognitive Pause — exactly three targets

Do not add hints or another target during the five minutes.

1. Trace `push(100), push(200), push(300), peek, pop, pop, pop`; record every
   return, output, size, and bottom-to-top state.
2. Diagnose independent full-push, empty-peek, and empty-pop cases; preserve
   the existing values and the output sentinel 999.
3. Explain precedence and the result for `1+2*3`; reject `1++2` while
   preserving a preexisting evaluator output.

## Meeting A checks

Before leaving, verify that each student can state:

- LIFO means the newest remaining item is removed first;
- push, peek, and pop all use the top end;
- logical items occupy indexes `0` through `size - 1`;
- `stack[size - 1]` is legal as a top expression only when `size > 0`;
- `stack[size]` is the next unused position when space remains;
- valid metadata satisfies `0 <= size <= capacity`;
- full push and empty peek/pop are rejected before mutation;
- a rejected output-producing operation leaves the output unchanged; and
- `*` takes precedence over `+` in `1+2*3`.

## Likely Meeting A misconceptions

| Misconception | Diagnostic question | Repair move |
|---|---|---|
| 100 resumes before 200 | Which call began most recently and is still unfinished? | Remove the 300 card, then expose 200 |
| Top means index `size` | Which indexes are counted when size is two? | Label indexes 0 and 1 active; index 2 inactive |
| Pop must erase a cell | Which variable decides membership? | Keep old bits visible while reducing size |
| Capacity equals size | Can an empty ten-position array be valid? | Separate prepared positions from logical count |
| Full is invalid metadata | Does `size == capacity` satisfy the invariant? | Mark full as valid state but rejected push |
| Ten slots means ten input characters | Can an applied operator free positions? | Trace reuse over time; capacity bounds occupancy |

---

# Meeting B — Implement Checked Operations and Evaluator (90 minutes)

## Coding question

> How can each operation either complete its contract or preserve everything
> that the contract promises?

| Minutes | Activity | Instructor move | Evidence |
|---:|---|---|---|
| 0–8 | Retrieval | Without notes, trace 100, 200, 300 through peek and three pops. | Accurate trace |
| 8–14 | Gate D calibration | Correct top, invariant, and rejection language using the textbook and models. | Annotated correction |
| 14–20 | Gate E orientation | Release the lab. Define header, implementation, public test, starter, and reference solution. | Package map |
| 20–32 | Implement `push` | Check pointers and metadata, check full, write at old size, return new size. | Passing push cases |
| 32–44 | Implement `peek` and `pop` | Reject before index arithmetic; delay output writes until success. | Passing empty and preservation cases |
| 44–50 | Logical removal | Show that pop receives a const array and need not erase the old top. | Inactive-slot explanation |
| 50–61 | Evaluator grammar | Alternate expected digit/operator states. Reject all unstated syntax. | Grammar table |
| 61–73 | Precedence reduction | Before pushing an operator, reduce waiting equal-or-greater precedence. Pop right before left. | `1+2*3` and left-associative traces |
| 73–79 | Checked arithmetic and commit | Check `int` bounds before calculation; write caller result only after full success. | Unchanged-output overflow test |
| 79–84 | Three student tests | Require one LIFO, one rejection/preservation, and one evaluator test with rationale. | Three nonduplicate tests |
| 84–88 | Stack-Top Autopsy | Predict 20 versus 777 before running. Name the first broken logical rule. | Prediction and observation |
| 88–90 | Submission check | Review evidence and boundaries. | Completion checklist |

## Public API calibration

```c
int int_stack_push(int stack[], int size, int capacity, int value);

int int_stack_peek(
    const int stack[],
    int size,
    int capacity,
    int *out_value
);

int int_stack_pop(
    const int stack[],
    int size,
    int capacity,
    int *out_value
);

int expression_evaluate(const char expression[], int *out_result);
```

Calibrate the unusual but intentional return contracts:

- successful push returns `size + 1`; rejected push returns original `size`;
- successful peek returns 1; rejected peek returns 0;
- successful pop returns `size - 1`; rejected pop returns original `size`;
- successful evaluation returns 1; rejected evaluation returns 0.

Because a rejected pop from an empty Stack also returns zero, callers must
decide acceptance from the preconditions or use the operation only after a
successful nonempty check. This small API emphasizes size threading rather
than a rich status enumeration.

## Evaluator grammar and boundary

The accepted grammar is:

```text
expression := digit (('+' | '*') digit)*
digit      := '0' | '1' | ... | '9'
```

Reject empty input, missing pointers, missing or repeated tokens, spaces,
parentheses, unary operators, multi-digit operands, other symbols, internal
full-Stack conditions, and arithmetic outside `INT_MIN` through `INT_MAX`.
Every rejection leaves `*out_result` unchanged.

Each internal Stack has ten slots. Ten is not a total-token or total-string
limit. Check each live push; earlier reductions can free slots for later
tokens.

## Test design requirements

Students replace exactly three placeholder bodies:

1. a canonical or extended LIFO trace involving 100, 200, and 300;
2. a full, empty, invalid-metadata, or missing-output rejection that checks
   preservation; and
3. a valid precedence case or rejected grammar/arithmetic case, including
   unchanged output on rejection.

Do not accept three examples that restate the same claim. Require each test's
comment to name the contract promise it supports.

## Stack-Top Autopsy facilitation

The fixture is deliberately memory-safe:

```text
stack = [10, 20, 777, 888]
size = 2
capacity = 4
```

Students predict before running. The correct top is 20 at index one. The
faulty read uses `stack[size]`, reaches inactive index two, and reports 777.
Do not lead with “no sanitizer finding.” Lead with the first broken contract:
the top of a nonempty Stack is `stack[size - 1]`. Physical bounds are
necessary but not sufficient for logical correctness.

## Assessment and feedback

Use the 100-point student rubric. Prioritize:

1. logical top and invariant correctness;
2. rejection before mutation and delayed output writes;
3. exact grammar, precedence, left associativity, and checked arithmetic;
4. evidence from nonduplicate tests; and
5. explanation of the autopsy and costs.

Do not penalize an incorrect first inquiry or pause response if it is
preserved and meaningfully corrected. Drawing quality, response speed, and
memorized wording are not grading targets.

## Optional extension boundaries

Appropriate discussion questions include how a richer status-returning API
could remove ambiguity, how a different fixed capacity changes accepted live
states, or how another element type could preserve the same LIFO contract.
Do not require storage-management extensions, additional expression syntax,
or traversal applications as part of the core submission.
