# Instructor Lesson Plan — Module 7: Queue and Circular Buffer

## Purpose and limits

This module begins the third Linear → Tree → Graph spiral. It retrieves:

- fixed indexed storage, bounds checks, and rejection contracts from Module 1;
- owned array storage, the Stack abstract data type (ADT), and last-in, first-out rule from
  Module 4; and
- the habit of separating a scheduling rule from its storage
  representation, reinforced in Modules 5 and 6.

Students now build a **Queue ADT**, a collection whose public promise is
first in, first out. **First in, first out (FIFO)** means the event that has
waited longest is removed first. The production representation is one
dynamically allocated but fixed-capacity circular array. **Fixed capacity**
means initialization chooses the number of slots and successful Queue
operations never grow it.

The canonical Queue stores synthetic integer event codes. A code identifies
an invented event; its numeric value does not state importance. The
non-sorted examples are deliberate. A Queue preserves arrival order rather
than sorting values.

By the end of the module, students should be able to:

1. distinguish FIFO Queue behavior from LIFO Stack behavior;
2. use checked enqueue, dequeue, and peek contracts;
3. distinguish logical Queue order from physical array order;
4. trace `head`, `size`, and derived `tail`;
5. explain when the remainder expression is and is not valid;
6. implement enqueue and dequeue without shifting;
7. preserve Queue state and caller output after every reported failure;
8. explain ownership, initialization, destruction, and the no-alias output
   precondition;
9. compare circular-array and linked-Queue representations; and
10. explain how an explicit full-buffer policy changes which events are
    retained.

All event codes are invented and held in one single-threaded in-memory
Queue. Passing this module does not prove that real logs are complete,
authentic, durable, delivered, or safe from concurrent access.

## Beginner language sequence

Introduce or retrieve each term immediately before students need it.

| Term | First-use explanation |
|---|---|
| abstract data type (ADT) | A public behavior contract that does not require one particular storage layout |
| Queue | An ADT in which the oldest waiting item leaves first |
| first in, first out (FIFO) | The first item added is the first item removed |
| enqueue | Add one item after the currently waiting items |
| dequeue | Remove and report the oldest waiting item |
| peek | Report the oldest waiting item without removing it |
| physical slot | One numbered position in the backing array |
| logical order | The arrival order seen through the Queue contract |
| circular array or circular buffer | An array whose freed beginning slots are reused after the physical end is reached |
| wrap-around | Continuing at physical slot 0 after the last physical slot |
| capacity | The number of physical slots owned by this Queue |
| size | The number of logically waiting events |
| head | The physical index of the oldest event when the Queue is nonempty |
| tail | The derived physical index where the next successful enqueue writes |
| derived | Calculated from other stored facts rather than stored as another field |
| remainder operator | C's `%` operator; here it returns an index to the legal range after reaching capacity |
| invariant | A representation rule that must hold whenever a public operation receives a completed object |
| empty | `size == 0` |
| full | `size == capacity` |
| overflow attempt | An attempt to add to a full fixed-capacity Queue |
| retention policy | A stated rule for which information is kept when storage is full |
| reject newest | Preserve all waiting events and report that the new event was not accepted |
| discard oldest | Explicitly remove the longest-waiting event to make room for the new one |
| backpressure | Ask an upstream producer to slow, pause, or retry instead of silently losing data |
| allocation | Requesting storage while the program runs |
| ownership | Responsibility for releasing an allocated region exactly once |
| alias | A second access path to the same storage |
| failure atomicity | A failed call appears not to have happened: checked state and output remain unchanged |
| constant time, `O(1)` | Work bounded by a fixed number of steps, independent of the number of queued items |
| linear time, `O(n)` | Work that may grow in direct proportion to the number of items |
| linked Queue | A Queue represented by separately stored nodes and links rather than one circular array |
| synthetic | Invented for safe study rather than collected from a live system |

Use **oldest waiting event** before introducing **head**. Use **candidate
write index** when discussing a full Queue because a full enqueue must not
write. Never define `tail` as the newest event; in this package it is the
next successful write position.

## Frozen representation and behavior

The public representation is:

```text
data      owned array of integer event codes, or NULL at capacity 0
capacity  fixed number of slots chosen by successful initialization
head      physical index of the oldest item when size is positive
size      number of logically occupied slots
tail      not stored; derived only when capacity is positive
```

For a valid positive-capacity Queue:

```text
0 <= size <= capacity <= 64
data is not NULL
head < capacity
if size == 0, head == 0
tail = (head + size) % capacity
logical item k is at data[(head + k) % capacity], for 0 <= k < size
```

Capacity zero has the exact all-zero state:

```text
data = NULL, capacity = 0, head = 0, size = 0
```

Do not evaluate either remainder expression at capacity zero. Enqueue on
that valid state returns `EVENT_QUEUE_FULL`; dequeue and peek return
`EVENT_QUEUE_EMPTY`.

After a successful dequeue removes the final item, the implementation
normalizes `head` to 0. **Normalizes** means choosing one standard field
state for all empty Queues.

## Five release gates

A **release gate** is a planned point when the next materials become
available. Students preserve an initial response before seeing a calibrated
model.

| Gate | Release point | Give students | Keep back |
|---|---|---|---|
| A — Arrival-order inquiry | Start of Meeting A | Standard or linear inquiry prompt | Queue/FIFO operation names, circular formula, worked trace, code, answers |
| B — Representation reveal | After each Stage A response is preserved | Representation reveal and exactly-three-target Cognitive Pause, each with an embedded linear equivalent | Vocabulary file during the pause, pause feedback, Stage C, textbook, code |
| C — Investigation | After the timed pause and comparison | Standard or linear investigation worksheet | Textbook, completed models, lab/code |
| D — Calibrated explanation | After preserved Stage C core Sections A–F | Beginner-first textbook and equivalent diagram/text models | Lab package and instructor materials |
| E — Lab and evidence | After Meeting B retrieval of FIFO and the invariant | Lab, evidence form, rubric, safe autopsy, public header, starter, core tests, student-test template, build files | Reference solution, extension tests, answer key, technical notes |

The vocabulary file remains closed for the complete Cognitive Pause.
Instructors may repeat directions and provide approved access support, but
may not define a term, confirm correctness, supply a hint, or introduce a
fourth target.

An accommodation may change time, response method, room, lighting, or
assistive technology. It does not reverse this sequence:

```text
attempt → preserve → compare → correct
```

Stage C core is Sections A–F. Sections G–I are later extension work.

---

# Meeting A — Model FIFO Reuse Without Shifting (90 minutes)

## Macro-Question

> How can a security-event collector process events in arrival order without
> shifting all remaining events after every removal?

| Minutes | Activity | Instructor move | Evidence |
|---:|---|---|---|
| 0–8 | Retrieve ArrayList and Stack | Retrieve indexed slots, `size <= capacity`, owned storage, and “newest leaves first.” Do not yet name Queue, FIFO, circular buffer, head, tail, or modulo. | Spoken or written retrieval |
| 8–22 | Gate A inquiry | Release one accessible format. Require an individual preserved response. Keep letter events `K,B,T` visible so students cannot substitute alphabetical sorting for arrival order. | Initial A–F response |
| 22–31 | Compare without erasing | Ask which promise was used, how slots 0 and 1 can be reused, and what information a full collector might lose or delay. Require labeled additions rather than erased first answers. | Annotated first model |
| 31–42 | Gate B representation | Define Queue, FIFO, enqueue, dequeue, peek, physical/logical order, circular reuse, `head`, `size`, capacity, and derived `tail`. Work the capacity-3 reveal below. | Labeled reveal trace |
| 42–47 | Five-minute Cognitive Pause | Release exactly the three capacity-5 targets below. Repeat directions only. Keep vocabulary closed. | Preserved three-target response |
| 47–57 | Calibration | Open vocabulary only after all three responses are preserved. Compare responses using both the indexed row and the linear logical list. | Corrected pause response |
| 57–71 | Canonical capacity-4 trace | Work the distinct course fixture. Derive each write index, preserve arrival order across wrap-around, reject event 90, and drain to normalized empty state. | Exact trace table |
| 71–80 | Contracts and boundary states | Separate empty from full using `size`; cover capacity 0 and 1; state unchanged-state and unchanged-output rules. | Boundary explanations |
| 80–86 | Retention policy | Compare reject-newest, discard-oldest, and caller-managed backpressure. Freeze reject-newest as the implementation policy. | One justified trade-off |
| 86–90 | Exit and Gate C | Ask students to state FIFO, the positive-capacity tail guard, and why no shift is needed. Release Stage C. | Three-part exit response |

## Stage B representation reveal

The reveal fixture is deliberately different from both the Cognitive Pause
and the course fixture.

```text
capacity = 3
enqueue 71
enqueue 24
dequeue       -> 71
enqueue 83
enqueue 36
```

Use `·` to mean **not logically occupied**. It does not promise that an
inactive memory cell was cleared.

| Completed operation | Physical slots 0,1,2 | `head` | `size` | derived `tail` | Logical order |
|---|---|---:|---:|---:|---|
| initialize | `[·,·,·]` | 0 | 0 | 0 | empty |
| enqueue 71 | `[71,·,·]` | 0 | 1 | 1 | `71` |
| enqueue 24 | `[71,24,·]` | 0 | 2 | 2 | `71,24` |
| dequeue → 71 | `[·,24,·]` | 1 | 1 | 2 | `24` |
| enqueue 83 | `[·,24,83]` | 1 | 2 | 0 | `24,83` |
| enqueue 36 | `[36,24,83]` | 1 | 3 | 1 | `24,83,36` |

Say the verbal rule before showing syntax:

> Start at `head`, count `size` positions, and return to slot 0 after the
> final physical slot.

Then connect it to:

```text
tail = (head + size) % capacity
```

The expression is valid only after the Queue is known valid and
`capacity > 0`. In the final full row, `tail == head`; enqueue must check
full before using that candidate index.

## Stage B Cognitive Pause — exactly three targets

The pause begins from this different capacity-5 state:

```text
physical slots: [18, 77, unused, 42, 9]
capacity = 5
head = 3
size = 4
```

Targets are independent where stated.

1. Give the derived tail, the next physical slot, and the logical event
   order.
2. Starting again from the base state, enqueue 55 and then dequeue once.
   Give the returned event, final physical state, `head`, `size`, derived
   `tail`, and logical order.
3. Starting from the full state immediately after only enqueueing 55,
   attempt to enqueue 66. Give the status, show that the full state is
   unchanged, and explain how `size` distinguishes full from empty when
   derived `tail == head`.

Private responses:

1. `tail = 2`; next write slot 2; logical order `42,9,18,77`.
2. Enqueue writes 55 at slot 2; dequeue returns 42. Final logical overlay is
   `[18,77,55,·,9]`, with stale 42 permitted in inactive slot 3;
   `head = 4`, `size = 4`, `tail = 3`, logical order `9,18,77,55`.
3. `EVENT_QUEUE_FULL`; physical values, pointer, capacity, head 3, size 5,
   tail 3, and logical order `42,9,18,77,55` remain unchanged. `size == 0`
   means empty; `size == capacity` means full.

Do not add a policy-comparison question to the pause. Policy analysis comes
later.

## Canonical course trace

The course fixture uses capacity 4 and a third set of non-sorted event
codes:

```text
enqueue 31, 8, 47, 19
dequeue -> 31
dequeue -> 8
enqueue 62
enqueue 5
attempt enqueue 90
drain
```

| Completed operation | Logical overlay of physical slots 0,1,2,3 | `head` | `size` | `tail` | Logical order |
|---|---|---:|---:|---:|---|
| initialize | `[·,·,·,·]` | 0 | 0 | 0 | empty |
| enqueue 31 | `[31,·,·,·]` | 0 | 1 | 1 | `31` |
| enqueue 8 | `[31,8,·,·]` | 0 | 2 | 2 | `31,8` |
| enqueue 47 | `[31,8,47,·]` | 0 | 3 | 3 | `31,8,47` |
| enqueue 19 | `[31,8,47,19]` | 0 | 4 | 0 | `31,8,47,19` |
| dequeue → 31 | `[·,8,47,19]` | 1 | 3 | 0 | `8,47,19` |
| dequeue → 8 | `[·,·,47,19]` | 2 | 2 | 0 | `47,19` |
| enqueue 62 | `[62,·,47,19]` | 2 | 3 | 1 | `47,19,62` |
| enqueue 5 | `[62,5,47,19]` | 2 | 4 | 2 | `47,19,62,5` |
| enqueue 90 fails | unchanged | 2 | 4 | 2 | `47,19,62,5` |
| dequeue → 47 | `[62,5,·,19]` | 3 | 3 | 2 | `19,62,5` |
| dequeue → 19 | `[62,5,·,·]` | 0 | 2 | 2 | `62,5` |
| dequeue → 62 | `[·,5,·,·]` | 1 | 1 | 2 | `5` |
| dequeue → 5 | `[·,·,·,·]` | 0 | 0 | 0 | empty |

Clarify twice that the overlay hides inactive stale values. The
implementation does not clear slots during dequeue. The failed enqueue of
90 changes neither the logical state nor any physical slot.

## Meeting A checks

Before Meeting A ends, verify that each learner can:

1. say “oldest waiting leaves first” without relying only on the acronym;
2. produce `31,8,47,19` as the first four dequeue results from the original
   arrival sequence, regardless of physical arrangement;
3. identify `head` as a physical index rather than an event value;
4. identify `tail` as derived rather than stored;
5. state the positive-capacity guard before using `% capacity`;
6. use `size == 0` and `size == capacity` rather than `head == tail`;
7. explain why full enqueue 90 must not overwrite event 47;
8. distinguish inactive from cleared storage;
9. name one retention trade-off; and
10. state that event-code magnitude does not set Queue order.

## After Meeting A — Stage C and Gate D

Students preserve Stage C core Sections A–F before receiving the textbook.
Sections G–I may continue later. Gate D materials calibrate vocabulary,
formulas, contracts, costs, and the course trace; they do not contain a code
solution.

Use a short retrieval check before Meeting B:

1. What does FIFO promise?
2. When may the tail formula be evaluated?
3. What distinguishes empty from full if `tail == head`?
4. What must remain unchanged after a failed dequeue?

Expected responses are: oldest arrival leaves first; only for a valid
positive-capacity Queue; `size`; and both Queue state and caller output.

---

# Meeting B — Implement a Checked Circular Queue (90 minutes)

## Coding question

> How do we translate FIFO and circular reuse into C while preventing
> modulo-by-zero, out-of-bounds access, silent overwrite, ownership errors,
> and partial failure?

| Minutes | Activity | Instructor move | Evidence |
|---:|---|---|---|
| 0–8 | Retrieval without IDE | Reconstruct FIFO, invariant, full/empty rules, positive-capacity guard, and course tail values. | Four retrieval responses |
| 8–16 | Gate E and code map | Release the lab. Identify the public header, supplied functions, exactly three TODOs, core tests, student-test template, and build commands. | File map |
| 16–29 | TODO 1: validator | Translate each visible invariant rule into one checked branch. State what C cannot validate about an arbitrary non-NULL pointer. | Warning-clean validator |
| 29–43 | TODO 2: enqueue | Validate, reject full before remainder, derive tail, write the event, then increment size. | Ordinary/full/capacity-0 tests |
| 43–57 | TODO 3: dequeue | Check output first, validate, reject empty, preserve the result locally, derive candidate new fields, normalize final empty head, commit, then publish output. | FIFO/empty/normalization tests |
| 57–64 | Inspect supplied operations | Read init, peek, destroy, status-name mapping, and the test-only one-shot allocation hook. Connect each to the public contract. | Lifecycle explanation |
| 64–72 | Run public core tests | Build with warnings; use the first failing assertion as evidence. Do not hand out the solution. | Core test output |
| 72–79 | Write three student tests | Require the three distinct categories: FIFO including capacity one; wrap plus a repeated cycle; both full and post-drain empty preservation in one third test. | Compiling student tests |
| 79–85 | Safe autopsy | Run the bounded faulty index calculation. Preserve prediction, identify the first wrong decision, repair the circular calculation, and name a regression test. | Four-part autopsy |
| 85–88 | Compare representations and costs | Contrast no-shift circular `O(1)` operations with shifting `O(n)` and a linked Queue. | Cost/representation statement |
| 88–90 | Security boundary and exit | State the selected retention policy and what passing tests cannot prove. | Safe-meaning exit |

## Canonical public model

The exact public status order is:

```text
EVENT_QUEUE_OK
EVENT_QUEUE_INVALID_ARGUMENT
EVENT_QUEUE_LIMIT
EVENT_QUEUE_FULL
EVENT_QUEUE_EMPTY
EVENT_QUEUE_ALLOCATION
EVENT_QUEUE_INVALID_STATE
```

The three student TODOs are exactly:

1. `event_queue_validate`;
2. `event_queue_enqueue`; and
3. `event_queue_dequeue`.

The complete `event_queue_init`, `event_queue_peek`,
`event_queue_destroy`, `event_queue_status_name`, and test-only allocation
hook are supplied and inspectable. Do not turn a supplied function into a
fourth TODO.

### Validator teaching order

1. Reject a missing Queue pointer with
   `EVENT_QUEUE_INVALID_ARGUMENT`.
2. Reject capacity above 64 or size above capacity with
   `EVENT_QUEUE_INVALID_STATE`.
3. At capacity zero, accept only the exact all-zero state.
4. At positive capacity, require non-NULL `data`.
5. At positive capacity and size zero, require `head == 0`.
6. At positive capacity and nonzero size, require `head < capacity`.

The validator checks visible field relationships. It cannot prove that a
non-NULL pointer is live, that the allocation really has `capacity` slots,
that inactive cells were initialized, or that no shallow copy shares the
allocation.

### Enqueue teaching order

1. Validate.
2. If `size == capacity`, return `EVENT_QUEUE_FULL`.
3. Only now derive `(head + size) % capacity`.
4. Store the event code at that slot.
5. Increment `size` last.
6. Return `EVENT_QUEUE_OK`.

This order makes capacity zero safe because it is reported full before `%`
could use a zero right operand.

### Dequeue teaching order

1. Reject a NULL output pointer.
2. Validate.
3. If `size == 0`, return `EVENT_QUEUE_EMPTY`.
4. Copy `data[head]` to a local result.
5. Calculate the candidate new size and head.
6. Use head 0 if the new size is zero; otherwise advance with remainder.
7. Commit `head` and `size`.
8. Publish the local result to the caller.
9. Return `EVENT_QUEUE_OK`.

The output pointer must not point inside the owned Queue allocation. The
public contract documents this no-alias precondition; the implementation
does not attempt an unreliable pointer-origin test.

## Required test interpretation

Public core evidence covers:

- exact zero receiver, positive initialization, live reinitialization
  rejection, destroy, and repeated destroy;
- capacities 0, 1, 64, and rejected 65;
- one-shot positive-capacity allocation failure with complete unchanged
  receiver;
- FIFO, peek, and the exact capacity-4 wrap fixture;
- full enqueue and empty dequeue/peek preservation;
- repeated fill/drain cycles;
- contradictory visible states;
- final-dequeue normalization to `head == 0`;
- every status string and the unknown-status fallback; and
- pointer and capacity stability throughout successful Queue use.

Private extension evidence adds maximum-capacity wrap, deterministic
differential traces, proof that capacity-zero initialization does not
consume the allocation-failure hook, broader corrupted states and head
positions, repeated capacity-one cycles, and explicit error-precedence and
preservation cases.

Student evidence contains three independently meaningful tests:

1. FIFO behavior including a capacity-one boundary;
2. wrap-around followed by another fill/drain cycle; and
3. both full and post-drain empty failure preservation in one test body:
   snapshot a full enqueue failure, drain, then prove an empty peek or
   dequeue preserves metadata, established stale slots, and caller output.

Do not accept three renamings of the public canonical fixture.

## Hint ladder

Outside the no-hint Cognitive Pause, use the least revealing step that
allows progress. Preserve the student's current trace or failing test before
moving down the ladder.

0. Ask the student to read the exact status and failing assertion aloud.
1. Ask which public contract sentence applies.
2. Ask which field or output must remain unchanged.
3. Ask the student to state the operation order in plain language.
4. Point to the relevant branch or expression, but do not supply code.
5. Supply one pseudocode line only after the student records why it is
   needed; require a new regression test before further help.

For remainder difficulty, offer the count-forward model before syntax:
start at `head`, move `size` places, and return to 0 after the last slot.

## Safe autopsy facilitation

The faulty program uses a capacity-3 model with:

```text
physical [10 STALE,20 LIVE,30 LIVE]
head = 1
size = 2
logical order = 20,30
intended enqueue = 40
```

It calculates raw candidate index 3 and checks the bound before any array
access. The guard refuses the operation and leaves logical order `20,30`
unchanged. The program does not print candidate index 3; its visible
evidence is `enqueue 40 accepted: no`, unchanged size 2, and unchanged
logical events. This safety check is a diagnostic guard, not the repair. Do
not suggest extra storage and do not remove the guard.

After prediction is preserved, the instructor key may state the repair:
derive the index circularly after proving positive capacity. The corrected
write is physical slot 0, producing physical `[40,20,30]` and logical
`20,30,40`. A regression test must create a valid non-full state whose raw
`head + size` reaches capacity and then verify both the physical write and
FIFO drain.

## Common misconceptions

| Misconception | Prompt |
|---|---|
| “Smaller event codes leave first.” | “Where does the contract mention numeric priority?” |
| “Queue is just a Stack with different names.” | “Which arrival leaves first in each ADT?” |
| “Tail stores the newest item.” | “At which slot would the next successful enqueue write?” |
| “Store tail too.” | “Can head and size derive it? What contradiction could a third field introduce?” |
| “`head == tail` means empty.” | “What are size and capacity in the full course row?” |
| “Modulo always makes the code safe.” | “What happens if capacity is zero, and was state validated first?” |
| “Dequeue must shift or clear.” | “Can head change the logical beginning without moving bytes?” |
| “A stale cell is still queued.” | “Is its physical slot among the `size` positions starting at head?” |
| “Full enqueue can overwrite the oldest event.” | “Which retention policy did this API promise?” |
| “Return a special integer for empty.” | “Could every integer be a legitimate event code?” |
| “Allocation failure can partially initialize.” | “Which fields may change on a non-OK return?” |
| “Init can replace a live Queue.” | “Who would release the old owned pointer?” |
| “Copying the struct duplicates its storage.” | “How many arrays and how many owners would then exist?” |
| “Output may point into Queue storage.” | “Would publishing the output also mutate owned storage?” |
| “Circular means faster in every operation.” | “Which exact operation avoids an `n`-item shift?” |
| “Passing tests proves secure logging.” | “What live ingestion, persistence, authenticity, and concurrency facts were not modeled?” |

## Accessibility and pacing

- Offer standard indexed rows and linear text with identical target IDs,
  values, order, and scoring.
- Read every physical state as: capacity, head, size, each numbered slot,
  then logical order.
- Use `unused` or `inactive` in text; never require color to distinguish a
  slot.
- Provide the legend that `·` means not logically occupied and may conceal a
  stale value.
- Permit tactile numbered cards, keyboard-only tables, speech, or a
  structured list instead of a drawing.
- Give the count-forward wrap method as an equivalent to mental remainder
  arithmetic.
- Extend time without adding hints or changing the exactly three pause
  targets.
- Assess FIFO state reasoning and contracts, not drawing quality, circular
  imagery, handwriting, or arithmetic speed.
- Keep code lines short enough for magnification and screen readers. Name
  fields and statuses fully when reading code aloud.

## Evidence collected

Collect:

1. preserved and corrected Stage A response;
2. preserved three-target Stage B response;
3. Stage C core Sections A–F;
4. canonical wrap trace;
5. warning-clean starter build after three TODOs;
6. public core-test output;
7. three student-authored tests;
8. full/empty failure-preservation explanation;
9. four-part safe autopsy record;
10. circular-array versus linked-Queue cost comparison;
11. explicit reject-newest policy justification; and
12. safe-meaning statement.

## After Meeting B — transparent completion window

Announce the completion window before Meeting B. Later extension work may
include Stage C G–I, private extension tests after grading, or a conceptual
linked-Queue comparison. Do not silently add a linked implementation,
concurrency, blocking behavior, live logs, file input, network input, or BFS
to the core requirements.

## Instructor readiness checklist

- [ ] Stage A contains no Queue/FIFO/circular formula solution.
- [ ] Standard and linear files have matching target IDs and facts.
- [ ] Stage A uses `K,B,T`, then `R,C,M`, and full arrival `Q`; alphabetical
      position is never treated as priority.
- [ ] The reveal uses capacity 3 and events `71,24,83,36`.
- [ ] The pause uses capacity 5 and events `42,9,18,77,55,66`.
- [ ] The pause has exactly three targets and vocabulary stays closed.
- [ ] The course trace uses capacity 4 and events
      `31,8,47,19,62,5,90`.
- [ ] Event codes are never interpreted as priority.
- [ ] The invariant and capacity-zero guard are stated exactly.
- [ ] Empty positive-capacity state normalizes `head` to 0.
- [ ] `tail` is derived, not stored.
- [ ] `EVENT_QUEUE_FULL` preserves the reject-newest state.
- [ ] `EVENT_QUEUE_EMPTY` preserves caller output.
- [ ] Init uses one allocation and never replaces a live Queue.
- [ ] The no-alias and non-copyable ownership rules are explicit.
- [ ] Student TODOs are validate, enqueue, and dequeue only.
- [ ] Core, extension, and student test categories match the package.
- [ ] The autopsy checks bounds before access and never causes undefined
      behavior.
- [ ] The autopsy guard is not presented as the repair.
- [ ] All professional terms are explained at first use.
- [ ] No example overstates what synthetic single-threaded Queue tests prove.
