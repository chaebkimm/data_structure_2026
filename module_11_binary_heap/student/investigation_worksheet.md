# Module 10 Investigation Worksheet

Name: ____________________ Date: ____________________

Use the current [lab](lab.md) and [source](lab.c). Predict first, run second,
then add a correction. The [linear version](investigation_worksheet_linear.md)
has the same targets without response tables.

## A. Which positions are live?

The array reserves ten integers. Start with `size=6` and values
`[7,3,5,1,9,4]`. Draw the complete tree using positions before adding values.

| Position | Parent | Left child | Right child |
| ---: | --- | --- | --- |
| 0 | | | |
| 1 | | | |
| 2 | | | |
| 3 | | | |
| 4 | | | |
| 5 | | | |

Explain `-1` and why capacity is different from `size`. Which position has
only a left child? What remains in inactive slots after `init_heap()`?

Prediction: ______________________________________________________
Correction: ______________________________________________________

## B. Which value belongs at the root?

Start independently with `init_heap()`. Add `7,3,5,1,9,4`.
For each addition, record the appended position, tested parents, swaps,
and final array. Keep values distinct from positions in every explanation.

| Value added | Appended position | Parent route | Final live array |
| ---: | ---: | --- | --- |
| 7 | | | |
| 3 | | | |
| 5 | | | |
| 1 | | | |
| 9 | | | |
| 4 | | | |

Explain the exact result of `proper_parent(-1,-1)`,
`proper_parent(2,-1)`, and `proper_parent(-1,2)` in a valid state.
Explain which position wins a tie and why this is not an arrival-order
promise.

__________________________________________________________________

## C. Which child repairs the root?

Use the final minimum Heap from B. Predict `remove_root()`.

| Moment | Returned/saved value | `size` | Live array |
| --- | --- | ---: | --- |
| before removal | | | |
| after replacement, before repair | | | |
| after first swap | | | |
| after stopping | | | |

List all child choices, including stop comparisons. Explain why choosing
the worse child can leave a violation. Check every parent/child pair in
the final array; do not require sorted sibling order.

In a separate run add one value, then remove it once. Trace the child
helpers and `proper_parent(0,-1)` when size becomes 0. State why another
removal would be invalid.

__________________________________________________________________

## D. Why build from the bottom?

Load `[7,3,5,1,9,4]` directly, set size 6 and minimum mode, then call
`heapify()`. Fill the states after repairs from positions 2, 1, and 0.
Explain why the children below each visited position are already Heaps.
Then change to maximum mode and rebuild. Do not assume changing the flag
moves any values.

| Call or repair | Final array |
| --- | --- |
| `heapify_down(2)` | |
| `heapify_down(1)` | |
| `heapify_down(0)` | |
| maximum-mode `heapify()` | |

Compare work for many separate insertions, one bottom-up build, one
root inspection, and one full diagnostic scan. The source has no supplied
comparison counter or full-order checker; keep any driver instrumentation
separate from the unchanged lab.

__________________________________________________________________

## E. Which endpoints decide overlap?

All ten IDs have valid closed intervals. Use ID 0 `[1,3],[7,10]`, ID 1
`[2,5],[8,12]`, and IDs 2–9 `[4,9]`. Load every row and interval count.
State why each row has at most five pairs and why prior off-time must be
strictly before the next on-time in this exercise.

| State | `epoch[0]` | `epoch[1]` | Latest start `L` | Earliest end `R` | Next action |
| --- | ---: | ---: | ---: | ---: | --- |
| after initialization | | | | | |
| after first advance | | | | | |
| after second advance | | | | | |

Explain why `L<=R` means that every device is on at `L`. When `L>R`, why
can the ID ending at `R` safely discard that interval? Why does this
advancement process preserve the earliest possible answer?

__________________________________________________________________

## F. Which number is an ID?

Read `_proper_parent`, `__swap__`, and `_reheapify`. Distinguish array
positions, stored IDs, and endpoint times. Fill both complete arrays and
both position maps after `_init_heaps()` and after each epoch advance.
Attach additional sheets if needed.

```text
max IDs: __________________________________________________________
max positions by ID: ______________________________________________
min IDs: __________________________________________________________
min positions by ID: ______________________________________________
```

Check `array[pos[id]]==id` for every ID in both Heaps. Show the two map
entries changed by one swap. Explain why `_reheapify(&max_on_heap,id)`
is generally incorrect and give the correct map-based argument.

The fixed-ten helpers give position 4 only left child 9. `_heapify` visits
5 through 0; explain why the first visit is harmless.

__________________________________________________________________

## G. What happens at the boundaries?

Predict and test only valid calls.

1. Integer duplicates in each mode: explain local tie behavior.
2. Empty and singleton bottom-up build: explain why no invalid position
   is visited.
3. Ten live integer values: stop adding; do not execute an eleventh add.
4. Interval equality: change ID 1's second interval to `[9,12]`.
5. Interval exhaustion: ID 0 only `[1,3]`, all other IDs `[4,9]`.
6. Immediate success: all ten IDs `[4,9]`.
7. Another call to `all_on_time()` with valid input: explain how epochs
   and maps restart.

Expected and observed results: ____________________________________

After exhaustion, identify the ID whose epoch equals its count. Explain
why no time accessor, repair, or `check_all_on()` should use that terminal
state. It is not an unchanged-state failure contract.

__________________________________________________________________

## H. What evidence supports the explanation?

Complete three original test groups in the [lab](lab.md). Compare interval
answers with a simple independent scan of all selected endpoints. Record
order and inverse-map checks after successful repairs.

State generalized costs using `n` IDs and `r` interval advances. Distinguish
one-path repair, bottom-up building, root inspection, total interval work,
and full diagnostics. Then state the actual ten-ID/five-interval limits.

Original claim: __________________________________________________
Observed evidence: ________________________________________________
Corrected claim: __________________________________________________
