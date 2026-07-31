# Instructor Lesson Plan — Module 1

## ArrayList and Linked-Node Preview

### Module identity

- **Length:** two 90-minute meetings
- **Audience:** second-semester cybersecurity freshmen with arrays, loops, functions, and conditionals; limited pointer/`struct` fluency
- **Context:** safe collection of synthetic authentication-event codes
- **Spiral role:** establishes representation, invariants, ownership, failure atomicity, and complexity; supplies the ArrayList later reused by Stack
- **Core code scope:** initialize, validate, reserve, get, append, destroy
- **Extension scope:** insert and remove

## Success criteria

At the end of the module, a student can:

1. distinguish `size` from `capacity`;
2. identify logical slots and owned spare storage;
3. reject access when `index >= size`;
4. grow before writing beyond capacity;
5. preserve the old allocation when `realloc` fails;
6. explain which aliases may become stale after successful growth;
7. verify the provided initialization/cleanup code and pass empty, boundary, first-growth, repeated-growth, overflow, and cleanup tests;
8. distinguish worst-case from amortized append cost;
9. compare contiguous storage with linked nodes without claiming either is universally superior.

## Instructor preparation

Prepare:

- the five staged release archives;
- the standard or linear accessible Stage A prompt and Stage C investigation,
  plus the Cognitive Pause in each student's approved response format;
- symbolic address labels such as `A` and `B`;
- the memory-model diagrams and text equivalents;
- starter code, supplied tests, student-test template, and build commands;
- the instructor-only forced allocation-failure target;
- a working instructor solution;
- the isolated faulty-growth demonstration;
- a warning-enabled compiler environment or instructor CI;
- a sanitizer-enabled environment where available;
- an approved debugger/CI alternative where sanitizers are unavailable.

Do not use live authentication data. Keep examples synthetic and small.

Release gates:

1. Stage A before Meeting A; it does not reveal the struct.
2. Stage B only after initial models are preserved.
3. Stage C only after the timed Cognitive Pause and expert growth calibration.
4. Stage D after the Meeting A investigation and exit ticket.
5. Stage E before Meeting B.

---

# Meeting A — Model and Reason

## Purpose

Students derive the representation before seeing implementation details. They construct the invariant, trace growth and failure, analyze operation costs, and preview linked nodes.

## Schedule

| Time | Activity | Instructor move | Student evidence |
|---:|---|---|---|
| 0–7 | Retrieval warm-up | Display `int events[4]`. Ask for valid indexes, third-element expression, and what C knows about logical use. | Individual worksheet |
| 7–13 | Readiness check | Correct only misconceptions that block the lesson: index range, pointer versus value, and fixed allocation. | Annotated correction |
| 13–20 | Cyber scenario | Four authentication events occupy four slots; a fifth arrives. Silent loss and out-of-bounds writing are unacceptable. Pose the Macro-Question. | Initial model |
| 20–28 | Initial construction | Students independently draw or describe the minimum state needed. Do not reveal the struct yet. | Individual representation |
| 28–36 | Pair comparison | Assign “explainer” and “invariant checker,” then switch roles. | Comparison notes |
| 36–43 | Representation reveal | Release Stage B. Reveal only `data`, `size`, and `capacity`; calibrate empty and partially occupied states. Do not reveal growth yet. | Labeled representation |
| 43–48 | Formal Cognitive Pause | Distribute `student/cognitive_pause.md`. Five quiet minutes for two post-append states, alias status, and failure preservation. | Independent core growth model |
| 48–59 | Expert growth calibration | Reveal full, successful-moving-growth, and failed-growth states. Students preserve and annotate their first response. | Corrected model |
| 59–68 | Derive invariant | Release Stage C. Sort valid/invalid state cards. Add ownership and logical-slot boundaries. | Full invariant |
| 68–76 | Operation contracts | Trace get, append without growth, append with growth, and scaffolded insert/remove. | State table |
| 76–82 | Complexity | Derive direct indexing, shifting, one growth cost, and amortized append. | Cost table |
| 82–86 | Linked-node preview | Compare a single allocation with three separately located node cards. | Comparison row |
| 86–90 | Exit ticket | Valid-index rule, failure preservation, stale-pointer risk, and linked-object transfer to tree and graph relationships. | Individual exit response |

## Macro-Question

> How can a fixed block of C memory behave like a collection that grows, and what trade-offs change when elements are stored in separately allocated nodes?

Do not accept “the array just grows” as a complete answer. Ask:

- Which object changes?
- Can the allocation address change?
- Which logical state must remain after failure?
- What new costs and risks appear with separate nodes?

## Cognitive Pause placement

Use `student/cognitive_pause.md` after students have seen the representation
but before a complete growth trace is shown. Schedule five quiet minutes.
Permit paper, editor, table, tactile model, or dictation. Honor approved
extended time or an asynchronous equivalent by withholding the expert
calibration until that student's initial response is complete; preserve the
same reasoning target rather than speed.

The initial response is not graded for correctness. The correction is evidence of learning.

## 75-minute adaptation

Move the linked-node comparison and the last two complexity rows to a short pre-lab activity. Keep the Macro-Question, invariant construction, and Cognitive Pause intact.

---

# Meeting B — Implement and Verify

## Purpose

Students translate the model into checked C, complete and explain the growth
scaffold, implement checked access and append, run boundary tests, and conduct
a memory-fault autopsy.

## Schedule

| Time | Activity | Instructor move | Student evidence |
|---:|---|---|---|
| 0–8 | Closed-resource retrieval | Ask for the invariant, append order, and failed-`realloc` behavior. | Retrieval response |
| 8–22 | Syntax sandbox | Interpret `struct`, `size_t`, `int *`, `->`, `sizeof *ptr`, `realloc`, and `free` using only `IntList`. | Prediction answers |
| 22–34 | Predict defects | Show direct `realloc`, access checked against capacity, and append-before-reserve. Require prediction before execution. | Annotated defects |
| 34–46 | Guided code reading | Walk through the provided `init`, `destroy`, and validity check. Identify what the helper can and cannot prove. | Code annotations |
| 46–51 | Commit-point pause | Students mark the exact reserve commit point and state what changes there. | State diagram |
| 51–76 | Core lab | Students implement get and append around the ordered reserve scaffold; run the smallest failing test after each change. | Passing core tests |
| 76–83 | Segfault Autopsy start | Complete trigger, first invalid assumption, and memory-state sections in class. Assign repair and regression-test sections asynchronously. | Partial incident report |
| 83–87 | Resource policy debrief | Correct dynamic growth still needs limits. Discuss rejection/backpressure separately from representation safety. | Policy statement |
| 87–90 | Exit and submission check | Worst-case versus amortized append; list required evidence. | Exit response |

## Syntax sandbox targets

Students should interpret:

```c
list->data
list->data[index]
sizeof *list->data
&list->data[index]
```

Key distinctions:

- `list` points to an `IntList`.
- `list->data` points to the element allocation.
- `list->data[index]` is an integer.
- `&list->data[index]` is an address inside the allocation.
- `sizeof *list->data` is one element’s size.
- `sizeof list->data` is the pointer size.

Avoid `void *` generic containers in this module.

## Hint ladder

When a student is stuck, reveal one prompt at a time:

1. What invariant must hold before this operation?
2. Which field or allocation may change?
3. What must remain unchanged on failure?
4. Is this index bounded by `size` or `capacity`?
5. Does capacity exist before the write?
6. Who owns the allocation at this line?
7. What is the smallest test that reaches this branch?

Do not take over the keyboard. Ask the student to predict the next line’s effect.

## 75-minute adaptation

Assign the first three core tests as pre-lab. Run the autopsy as the final ten-minute exit task and collect the full incident report asynchronously.

---

# Common misconceptions and responses

| Misconception | Diagnostic prompt | Response |
|---|---|---|
| `size` and `capacity` are interchangeable | “Is index 7 a list element when size is 4 and capacity is 10?” | Capacity is storage; size is logical membership. |
| Capacity is the last valid index | “How many slots does capacity four contain?” | Four slots have indexes `0..3`. |
| Access checks use capacity | “Who inserted a logical value into that spare slot?” | Public access requires `index < size`. |
| Write first, grow later | “Where does `data[size]` point when size equals capacity?” | Reserve before writing. |
| Direct `realloc` assignment is safe | “What address remains if allocation fails?” | Use a temporary and commit on success. |
| `realloc` always moves | “May an allocator extend in place?” | Code must handle either moving or staying. |
| Aliases survive growth | “Which allocation owned that interior address?” | Reacquire by index after successful growth. |
| New storage contains zeroes | “Which statement initialized the spare slots?” | `realloc` does not initialize the new region. |
| `sizeof(data)` gives capacity | “What is the declared type of `data`?” | It gives pointer size. |
| Every append is `O(1)` | “What occurs on a growth append?” | Worst case is `O(n)`; geometric amortized cost is `O(1)`. |
| Linked lists make insertion universally constant | “How is an index located?” | Relinking can be constant once located; traversal may be linear. |
| Dynamic means unlimited | “What happens under an unbounded event stream?” | The application needs limits and backpressure/rejection policy. |
| `free` writes `NULL` | “What bits remain in the variable?” | `free` releases storage; the program resets the field. |

---

# Accessibility and differentiation

## Required provisions

- Provide a structured text table for every diagram.
- Label state explicitly; do not rely on color.
- Permit handwriting, typing, dictation, tactile tokens, or a verbal description.
- Supply commands and code as selectable text.
- Caption demonstrations.
- Use symbolic addresses unless real addresses are necessary.
- Grade pointer reasoning rather than drawing quality, handwriting, typing speed, or spoken fluency.
- Accept instructor-CI or debugger evidence when local sanitizers are unavailable.

## Entry support

- completed first trace row;
- labeled memory-model template;
- public API skeleton;
- ordered reserve phases with the owned-pointer argument left as the checked
  completion step;
- named test failures;
- glossary for allocation, logical size, capacity, ownership, stale pointer, and invariant.

## Extension choices

Offer one:

- implement insert/remove and extension tests;
- instrument copied elements to demonstrate amortized growth;
- compare doubling with growth-by-one;
- add deterministic allocation-failure injection;
- design and analyze a shrink policy without implementing it;
- compare ArrayList and linked-node choices for a supplied workload.

Extensions deepen the same concept and do not replace core safety work.

---

# Evidence collected

1. initial and corrected Cognitive Pause;
2. completed invariant and operation table;
3. core implementation;
4. supplied-test transcript and three student-authored tests with rationale;
5. forced allocation-failure CI result;
6. warning/sanitizer/debugger/CI evidence;
7. Segfault Autopsy;
8. representation choice explanation;
9. bounded-ingestion or backpressure policy.

Use `student/rubric.md`.

## Forward retrieval for Module 2

Begin Module 2 with:

> An ArrayList keeps elements in one movable block. What changes if each element instead stores the address of another separately located object?

Expected retrieval:

- addresses express logical relationships independently of adjacency;
- nodes require explicit links and ownership;
- `NULL` represents absence;
- following links does not give constant-time arbitrary indexed access.
