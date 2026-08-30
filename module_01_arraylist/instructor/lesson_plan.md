# Instructor Lesson Plan — Module 1

## Keeping Data Together in One Place

### Module identity

- **Length:** two 90-minute meetings.
- **Audience:** students who know C variables, arrays, loops, conditions, and
  functions.
- **Representation:** `int array[10]`, an integer size count, and capacity
  ten.
- **Core:** checked indexed read/update, linear first-match search, append,
  insertion, removal, and rejection without mutation.
- **Extensions:** extra edge cases and operation sequences for the same core
  operations.

The revised Chapter 1 fixed-array model defines the scope. Capacity remains
ten. A full append or insertion is rejected before any element moves or is
written.

## Success criteria

After Meeting A, a student can:

1. distinguish size from capacity;
2. explain why active values occupy indexes zero through `size - 1`;
3. read or update an active index directly;
4. find the first matching value by checking active items in order;
5. trace append, right-shift insertion, and left-shift removal;
6. reject a full addition without changing the list; and
7. compare constant work with work that depends on the active item count.

After Meeting B, a student can implement all core operations, retain each
mutator's returned size, and support the result with tests and tool evidence.

## Instructor preparation

Prepare the five staged releases, diagram/text models, starter code, tests,
and a warning-enabled compiler plus an approved runtime-check or debugger
environment. Use the textbook sequence throughout the conceptual lesson:

```text
start:           [100, 200, 300]     size 3, capacity 10
update index 1:  [100, 500, 300]     size 3, capacity 10
remove index 1:  [100, 300]          size 2, capacity 10
insert 600 at 1: [100, 600, 300]     size 3, capacity 10
```

## Five release gates

| Gate | Release time | Student materials | Withhold |
|---|---|---|---|
| A — Initial inquiry | before Meeting A | standard or linear prompt | vocabulary, completed model, code, answers |
| B — Model and pause | after initial answers are preserved | fixed-array reveal, vocabulary reference, and Cognitive Pause | expert calibration and investigation |
| C — Investigation | after the pause and calibration | standard or linear investigation | completed notes and code |
| D — Calibrated notes | after Meeting A investigation and exit ticket | textbook, notes, diagram/text models | lab and instructor materials |
| E — Lab and evidence | Meeting B | lab, rubric, evidence form, autopsy, header, starter, tests, build files | solution and answer key |

Preserve the sequence “attempt, compare, correct.” Accommodations can change
timing without changing the reasoning target or penalizing students.

# Meeting A — Build the Fixed-Array Model (90 minutes)

## Schedule

| Minutes | Activity | Student evidence |
|---:|---|---|
| 0–10 | Reconstruct the ten-position starting state and distinguish active indexes | Initial inquiry |
| 10–22 | Read index one and update its value to `500` | Checked-index trace |
| 22–35 | Remove index one and close the gap | Left-shift trace |
| 35–45 | Insert `600` at index one and justify back-to-front movement | Right-shift trace |
| 45–50 | Reveal size, capacity, and the active-prefix rule | Representation labels |
| 50–55 | Complete the three-target Cognitive Pause | Preserved independent response |
| 55–65 | Calibrate shift direction and full-array rejection | Corrected pause |
| 65–75 | Investigate the invariant and count operation work | Investigation |
| 75–85 | Contrast indexed access with first-match value search; connect bracket syntax | Search trace |
| 85–90 | Complete the exit ticket | Individual explanation |

## Teaching prompts

- Which indexes currently contain active list items?
- Does the capacity change when size changes?
- Is a position below capacity necessarily an active item?
- Which item must move first during insertion?
- What would be overwritten if the shift started from the other end?
- Why does removal move later values toward index zero?
- Which condition proves there is room before a write?
- What must remain unchanged when a full addition is rejected?
- If the target value appears twice, which index should search return?

## Common misconceptions

| Misconception | Response |
|---|---|
| size and capacity are the same number | compare three active items with ten available positions |
| any index below capacity may be read as a list item | point to the first inactive position at index size |
| removing a value automatically closes the gap | trace each later value moving left |
| insertion should move front to back | show the first uncopied value that would be overwritten |
| a full array has room at index capacity | label the last usable index as capacity minus one |
| an old tail value after removal is still a list item | use the new size to mark the active prefix |
| search may return any duplicate | trace from index zero and stop at the first match |

## Efficiency calibration

Attach `O(1)` to a checked indexed read/update and append with room. Attach
`O(n)` worst-case work to value search and shifts near the front, where `n`
is the number of active items. Removing or inserting at the end needs no
shifts. A full append or insertion is rejected with constant work.

The teaching capacity is ten; the notation describes which work changes
with the number of stored items rather than introducing a different model.

# Between meetings

1. Preserve the investigation and exit ticket before releasing Stage D.
2. Ask students to annotate earlier answers using the textbook and notes.
3. Prepare Stage E for Meeting B.
4. Verify reference core and extension tests and the isolated guarded
   autopsy before class.

# Meeting B — Implement and Test (90 minutes)

## Schedule

| Minutes | Activity | Student evidence |
|---:|---|---|
| 0–8 | Retrieve size, capacity, and the active-prefix rule | Short response |
| 8–18 | Read the array-parameter contracts; implement valid-index checks and direct read/update | Header/code annotations |
| 18–30 | Implement first-match linear search | Present, absent, and duplicate tests |
| 30–42 | Implement append with strict capacity check | Append and full-state evidence |
| 42–58 | Implement insertion by shifting right back-to-front | Insert trace and tests |
| 58–70 | Implement removal by shifting left | Remove trace and tests |
| 70–78 | Run core tests and add three nonduplicate student cases | Passing transcript/rationales |
| 78–85 | Investigate the guarded bounds autopsy | Incident report |
| 85–90 | Check evidence and correction note against the rubric | Submission record |

## API teaching boundary

The public functions are `int_list_valid_index`, `int_list_find`,
`int_list_append`, `int_list_insert`, and `int_list_remove`.

- The valid-index helper returns `1` or `0`; use it before direct array reads
  or updates.
- Search returns the first matching index, or `-1` when absent or metadata is
  invalid.
- Append, insert, and remove return the new size on success or the original
  size on rejection. The caller assigns that result back to `size`.
- Every rejected mutation preserves all array elements.
- The caller's actual array must contain at least the stated capacity.

Use these contracts to teach observable behavior. Students do not need a
wrapper object or a status enum.

## Bounds and Invariant Autopsy

The standalone demonstration has ten usable slots and one extra physical
guard slot. A wrong `size <= capacity` condition allows a full append to
overwrite the guard and produce size eleven. The write stays inside the
demonstration array, so a crash is not the learning target.

Ask students to identify the first wrong condition, predict the changed
guard and size, and repair the strict comparison. The guard is only a safe
observation device; adding usable capacity is not the repair.

## Assessment and accessibility

All six operations are core: read, update, find, append, insert, and remove.
Use the 100-point student rubric. Extension tests add boundary and sequence
evidence only and must not hide required insertion/removal work.

| Rubric criterion | Points |
|---|---:|
| Textbook model and invariant | 20 |
| Core operations | 25 |
| Bounds and rejected-state safety | 20 |
| Tests and tool evidence | 15 |
| Operation efficiency | 10 |
| Autopsy and explanation | 10 |
| Total | 100 |

Provide the linear inquiry/investigation versions, text equivalents for
every diagram, selectable commands, and an approved alternative when local
runtime checks are unavailable. Grade reasoning, order preservation, checked
boundaries, and implementation evidence rather than drawing quality or speed.

## Evidence collected

1. initial inquiry;
2. corrected Cognitive Pause;
3. investigation worksheet;
4. all core operations and passing supplied tests;
5. three student-authored tests with rationales;
6. warning and runtime-check/debugger/CI evidence;
7. Bounds and Invariant Autopsy; and
8. correction note.
