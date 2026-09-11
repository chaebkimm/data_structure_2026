# Module 1, Meeting B — Implement a Checked Array List

Use this plan with Stage E's `lab.md`. The representation remains one fixed
integer array, a current size, and a capacity. Read, update, find, append,
insert, and remove are all core operations.

## Meeting sequence (90 minutes)

| Minutes | Work |
|---|---|
| 0–8 | Retrieve size, capacity, and the rule that active items occupy the prefix before size. |
| 8–18 | Read the supplied function contracts; implement the index check and use it before direct reads/updates. |
| 18–30 | Implement first-match search and distinguish a returned index from an item value. |
| 30–42 | Implement append and reject a full list before writing. |
| 42–58 | Implement insertion, checking first and shifting from back to front. |
| 58–70 | Implement removal by shifting later items left and returning the new count. |
| 70–78 | Run the core tests and add three test cases with their own claims. |
| 78–85 | Preserve a prediction, then run and explain the guarded bounds autopsy. |
| 85–90 | Check the lab's required evidence and correction note. |

## Find C help when you need it

Keep the English or Korean Stage D textbook nearby. **Full C Code
Explanation** is an optional reference: choose the topic that explains the
line you are reading, then return to the lab. Stage D's `notes.md` has a
topic map. You do not need to read every topic or complete its practice
questions before starting.

For the function inputs, returned sizes, and provided test code, use
**Reading the supplied C scaffold** in `lab.md`. Ask for a short trace or
syntax explanation whenever a line is unclear; the schedule can be adjusted
without changing the core learning targets.

The textbook's complete program starts with five active values. Smaller
lists in the inquiry and tests follow the same rules. In the lab, save each
mutation's returned size and treat a search result of `-1` as absence. The
textbook's inline search instead reaches `index == size` for absence.

## Completion

Submit the artifacts listed in `lab.md`: all core operations, passing core
tests, three student tests with rationales, tool evidence, the evidence
record, autopsy response, and corrected Cognitive Pause. Additional
extension tests are optional; insertion and removal are already core work.
