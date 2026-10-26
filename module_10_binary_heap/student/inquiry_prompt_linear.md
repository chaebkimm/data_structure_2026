# Module 10 Inquiry — Linear Response Format

Use this alternative to [inquiry_prompt.md](inquiry_prompt.md). The learning
targets are the same. Respond in numbered prose, dictated text, or another
accessible format. Preserve initial predictions and add corrections.

1. Requests arrive with values `7,3,5,1,9,4`. Give the removal order when
   smaller is more urgent, then when larger is more urgent.
2. An unsorted array scans all live values before each removal. Describe
   the repeated work. Suggest a nearby-pair rule that keeps the answer at
   position 0 without fully sorting the array.
3. Use these parent/child relationships: 0 has children 1 and 2; 1 has 3
   and 4; 2 has only 5. Place the six values, then explain why your local
   rule makes the root an answer. Explain what sibling order remains free.
4. Append one value at the next position. Describe its possible route
   upward and when repair stops.
5. Remove the root and move the final value into its position. Describe
   which existing child should be chosen and why a missing child cannot
   be treated as an array index.
6. Ten devices each have selected closed intervals. Decide whether their
   intervals overlap using the latest start and earliest end. Explain
   whether equal endpoints count.
7. Use ID 0 with `[1,3],[7,10]`; ID 1 with `[2,5],[8,12]`; IDs 2 through 9
   with `[4,9]`. Predict which device needs its next interval first and
   which needs one next. State the earliest shared time you predict.
8. A device moves to a different position whenever two array entries swap.
   Describe how to remember the current position of each device without
   searching every entry.
9. The supplied integer-Heap functions do not check full/empty conditions.
   State the caller's condition before adding and before removing. Keep
   invalid calls as written predictions.
10. Read [lab.c](lab.c), run valid tests, and attach a correction supported
    by an exact state or returned value.

First response: __________________________________________________

Correction and evidence: __________________________________________
