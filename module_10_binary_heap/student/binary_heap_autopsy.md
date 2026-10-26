# Module 10 Autopsy — Repair the Wrong Relationship

Use an independent driver or paper trace based on [lab.c](lab.c). Preserve
the supplied source. The older faulty alert-library program under
`code/autopsy` is an optional reference with a different API.

## What if downward repair chooses the wrong child?

Start in minimum mode with `[1,3,4,7,9,5]`, size 6. Remove the root.
The final value 5 replaces 1; the live size becomes 5. Correct repair
chooses child value 3 rather than 4 and ends at `[3,5,4,7,9]`.

On paper, replace the better-child choice with a choice of the larger child.
Write the first comparison where the paths differ. Show the resulting
parent/child violation. Explain why looking only at the new root's selected
path cannot certify every relationship.

First divergence: __________________________________________________
Broken relationship: _______________________________________________
Regression assertion: ______________________________________________

## What if a swap forgets the inverse map?

The indexed Heaps store device IDs. For the shared interval fixture,
initial `_max_heap_pos[0]` is 8. Advancing ID 0 changes its on-time from
1 to 7. Correct upward repair moves ID 0 to root position 0 and updates
its inverse-map entry to 0.

Suppose the array swap occurs but the map still says 8. State what
`max_on_heap.array[_max_heap_pos[0]]` now contains and why a later repair
would target the wrong ID. The correct post-advance array is
`[0,3,2,7,4,5,6,1,8,9]`, so position 8 contains ID 8.

First divergence: __________________________________________________
Two map assignments that must accompany a swap: _____________________
Regression assertion for every ID: __________________________________

## What if changing an epoch repairs only one Heap?

Use ID 0 `[1,3],[7,10]`, ID 1 `[2,5],[8,12]`, and IDs 2–9 `[4,9]`.
After advancing ID 0, both its on-time and off-time change. Explain which
ranking becomes stale if only `min_off_heap` is repaired. Trace the stale
latest start 4 and earliest end 5. The stale check would return 4 even
though ID 0 is now on only from 7 through 10. Compare that result with
the correct bounds `(7,5)`.

Prediction: ________________________________________________________
Correction: ________________________________________________________

## What if equality is rejected?

Change ID 1's second interval to `[9,12]`. The final latest start and
earliest end are both 9. Explain why replacing `<=` with `<` in the
intersection test loses the valid answer 9.

Regression assertion: ______________________________________________

## What if exhaustion is followed by another time read?

Use only `[1,3]` for ID 0 and `[4,9]` for every other ID. The next advance
sets `epoch[0]==interval_size[0]` and `all_on_time()` returns `-1` before
repairing. Explain why a later `check_all_on()` would read an unselected
interval. Describe valid reinitialization before a new run.

Explanation: ______________________________________________________

One corrected claim supported by the source: ________________________
