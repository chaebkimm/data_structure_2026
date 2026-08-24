# Instructor Lesson Plan — Module 1

## Keeping Data Together in One Place

### Module identity

- **Length:** two 90-minute meetings
- **Audience:** students who know C variables, functions, arrays, loops, and
  conditional statements
- **Textbook context:** connected-device IP-address values
- **Conceptual core:** contiguous storage, indexed access, value search,
  insertion, deletion, expansion, and average work across repeated additions
- **Lab extension:** the repository's checked `IntList` implementation

The frozen student textbook is the source of truth for the conceptual scope.
Do not require lab-specific contracts during the first meeting.

## Success criteria

After Meeting A, a student can:

1. explain direct indexed access and sequential value search;
2. preserve the no-gap, index-0 invariant;
3. trace insertion and deletion shifts;
4. describe expansion as obtain, copy, add, release, and continue;
5. explain why doubling reduces how often copying occurs;
6. identify the jobs of `sizeof`, pointers, `malloc`, `NULL`, and `free`.

After Meeting B, a student can map those ideas to the supplied `IntList`
interface and satisfy its implementation contracts.

## Instructor preparation

Prepare the five staged releases, memory-model diagrams, starter code, tests,
and an approved warning/sanitizer/debugger environment. Keep the textbook
unchanged. Use the same values—10, 50, 20, 30, and 99—through the conceptual
lesson.

# Meeting A — Build the Textbook Model

## Schedule

| Time | Activity | Student evidence |
|---:|---|---|
| 0–10 | Read the five-slot starting state and answer index questions | Initial inquiry A |
| 10–25 | Delete 50 and close the gap | Initial inquiry B |
| 25–40 | Insert 99 and justify back-to-front movement | Shift trace |
| 40–48 | Reveal the memory-space model and state the golden rule | Representation reveal |
| 48–55 | Cognitive Pause: move a full array to eight slots | Independent growth trace |
| 55–65 | Calibrate obtain, copy, add, release, and continue | Corrected trace |
| 65–75 | Compare indexed access, value search, insertion, and deletion work | Investigation D–E |
| 75–83 | Compare one-slot growth with doubling | Investigation F |
| 83–88 | Connect `sizeof`, pointers, `malloc`, `NULL`, and `free` | Investigation G |
| 88–90 | Exit ticket | Investigation H |

## Teaching prompts

- Which item moves first?
- What would be overwritten if movement started from the other end?
- Which positions contain stored data after this action?
- What condition tells us the current space is full?
- Which facts must remain in the same order after copying?
- Why does a larger jump create more ordinary additions between expansions?

Avoid requiring the names `IntList`, `size`, `capacity`, failure
atomicity, ownership, integer overflow, or stale pointer during this meeting.
Those are implementation extensions, not basic textbook prerequisites.

## Common conceptual misconceptions

| Misconception | Response |
|---|---|
| Removing a value automatically closes the gap | Trace the later values moving left |
| Insertion should move front to back | Show the first value that would be overwritten |
| An index search and value search do the same work | Contrast address calculation with checking values |
| A full array can accept one more write | Ask which allocated slot receives it |
| One-slot growth is memory-efficient, so it is always best | Count complete copies across repeated additions |
| Doubling makes every addition identical | Separate ordinary writes from expansion steps |
| `free` resets the pointer | Show the explicit assignment to `NULL` |

# Meeting B — Map the Model to the Lab

## Purpose

Students translate the textbook's three tracked facts into `IntList`, then
complete and test the checked implementation. Introduce implementation
contracts only when they become necessary for the code.

## Schedule

| Time | Activity | Student evidence |
|---:|---|---|
| 0–10 | Retrieve the golden rule and expansion order | Short response |
| 10–22 | Map starting address and tracking numbers to `data`, `size`, and `capacity` | Labeled struct |
| 22–35 | Read initialization, destruction, and checked access contracts | Code annotations |
| 35–50 | Relate `realloc` to obtain–copy–release and explain the temporary result | Reserve trace |
| 50–72 | Implement checked access and append; run core tests | Passing transcript |
| 72–82 | Complete the unsafe-growth autopsy | Incident report |
| 82–87 | Attach `O(1)`, `O(n)`, and amortized terminology to counted work | Cost table |
| 87–90 | Check submission evidence | Evidence record |

## Lab boundary

The lab legitimately adds details absent from the textbook:

- the `IntList` public API and status values;
- exact field invariants and reset state;
- allocation-failure preservation;
- arithmetic-limit checks;
- testing, warnings, and sanitizer/debugger evidence.

Present these as engineering requirements for this implementation. Do not
retroactively describe them as missing basic concepts in the textbook.

## Accessibility

Provide the linear inquiry and investigation variants, structured text for
every diagram, selectable build commands, and approved alternatives to local
sanitizers. Grade the reasoning and working implementation rather than drawing
quality, handwriting, typing speed, or spoken fluency.

## Evidence collected

1. initial inquiry;
2. corrected Cognitive Pause;
3. investigation worksheet;
4. core implementation and tests;
5. warning and sanitizer/debugger/CI evidence;
6. Segfault Autopsy;
7. correction note.

Use `student/rubric.md`.
