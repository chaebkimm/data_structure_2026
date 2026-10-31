# Module 10 Evidence Record

Name: ____________________ Date: ____________________
Source: [student/lab.c](lab.c). Keep predictions and corrections.

## Build and source

Compiler/version: __________________________________________________
Commands: ________________________________________________________
Supplied test result: _____________________________________________
Student-test result: ______________________________________________
Warnings or remaining limits: _____________________________________

The source was left unchanged: _____________________________________

## Integer-Heap trace

Start with `init_heap()` and add `7,3,5,1,9,4`.

| Step | First prediction | Observed live array | `size` |
| --- | --- | --- | ---: |
| add 7 | | | |
| add 3 | | | |
| add 5 | | | |
| add 1 | | | |
| add 9 | | | |
| add 4 | | | |
| remove root | | | |

Return value and better-child decisions: ___________________________
Lone-left-child example: __________________________________________
Singleton removal and no-child stop: ______________________________
Caller conditions before add/remove: ______________________________

## Bottom-up build and comparator change

Load `[7,3,5,1,9,4]`, `size=6`, minimum mode.

| Repaired position | Live array |
| ---: | --- |
| 2 | |
| 1 | |
| 0 | |

After `is_min_heap=0; heapify();`: _________________________________
Why the flag alone is insufficient: _______________________________
Equal-value behavior and its limitation: __________________________

## Interval data and roots

Use ID 0 `[1,3],[7,10]`; ID 1 `[2,5],[8,12]`; IDs 2–9 `[4,9]`.
State all input preconditions: ____________________________________

| State | Latest on-time | Earliest off-time | Advanced ID or answer |
| --- | ---: | ---: | --- |
| epochs all 0 | | | |
| after first advance | | | |
| after second advance | | | |

For initialization and each advance, attach both complete ID arrays and
both position maps. Verify both `array[pos[id]]==id` relations for all IDs.

`max_on_heap` state: ______________________________________________
`_max_heap_pos` state: ____________________________________________
`min_off_heap` state: _____________________________________________
`_min_heap_pos` state: ____________________________________________

ID versus position in `_proper_parent`: ____________________________
Position passed to `_reheapify`: ___________________________________
Why both Heaps need repair: _______________________________________

## Original tests and boundaries

| Test group | Independent expected result | Observed result |
| --- | --- | --- |
| Integer-Heap operations | | |
| Indexed key repairs and inverse maps | | |
| Interval overlap, equality, and exhaustion | | |

Closed-endpoint variant and answer: _______________________________
Exhaustion fixture and answer: ____________________________________
Why terminal time access is invalid: ______________________________
Reset before another run: _________________________________________

## Work and correction

One-path repair work as live count grows: __________________________
Bottom-up build work: _____________________________________________
Full order/map verification work: _________________________________
Generalized interval-advance work: _________________________________
Actual fixed storage and generalized storage: _____________________

Original explanation: _____________________________________________
Evidence that changed it: _________________________________________
Corrected explanation: ____________________________________________
