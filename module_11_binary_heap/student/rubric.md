# Module 10 Assessment Rubric

Total: 100 points. Assess correct reasoning and reproducible evidence.
Typed, linear, dictated, tactile, and verbal explanations are equivalent.
The supplied [lab.c](lab.c) is unchanged; implementation of the optional
alert-record library is not part of this submission.

| Area | Points | Evidence |
| --- | ---: | --- |
| Integer-Heap model | 15 | Live prefix, complete-tree positions, missing-child sentinel, minimum/maximum rules, and distinction from sorted or BST order. |
| Add, remove, and bottom-up build | 20 | Exact shared arrays, correct parent/child choices, lone-left case, singleton drain, and rebuild after changing the mode. |
| Two endpoint Heaps | 15 | ID versus position distinction, function-pointer roles, epochs, and correct maximum-on/minimum-off rankings. |
| Indexed repairs | 15 | Every swap updates both inverse-map entries; `_reheapify` receives a position and chooses a valid direction; both Heaps repaired after an epoch change. |
| Interval reasoning and boundaries | 15 | Shared answer 8, closed-endpoint answer 9, correct earliest-end advancement, exhaustion result, and terminal-state limitation. |
| Three original test groups | 10 | Integer operations, indexed repairs, and interval answers checked by assertions against independent expectations. |
| Cost and correction | 5 | One-path repair versus bottom-up construction and full verification, storage bounds, and a corrected Cognitive Pause/autopsy explanation. |
| Reproducible evidence | 5 | Driver, commands, output, initial predictions, and corrections are complete; supplied compiler warnings are reported. |

The required caller conditions are `size<10` before `add`, `size>0`
before `remove_root`, valid positions for repair, and fully loaded valid
interval data for all ten IDs. Do not claim unchecked functions reject
invalid calls or preserve state on such calls. Analyze invalid calls on
paper. After exhaustion an epoch equals its interval count; do not read
that terminal interval or call the intersection checker on it.

Noncompiling work may still earn reasoning credit from preserved traces
and explanations. Revision remains available under course policy.
