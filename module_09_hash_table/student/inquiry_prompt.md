# Stage A — Initial Inquiry: Find Stored Values

Name: ____________________  Date: ____________________

Begin by finding one value in an array. Build an alternative way to remember
its input position before considering an application with two positions.
Preserve first answers and add labeled corrections later.

## A. Find a value, then remember its position

```text
input position   0  1  2
value            2  5  6
```

1. Read the array in order to find 5, then look for absent 3. Which values
   are compared, and what result should each search report?
2. Reserve seven places numbered 0–6. At the place equal to a stored value,
   write its input position; write -1 at all unused places. Fill the row.

| Place | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| Input position | | | | | | | |

3. How does the row answer a lookup for 5 or 3? What problem arises if a
   stored value is negative, or if a few stored values are extremely large?

Prediction: ________________________________________________________

## B. Group keys into fifteen places

Reserve places 0–14. Use the C remainder after division by 15, adding 15 if
it is negative.

| Key | C remainder `% 15` | Selected place |
| --- | --- | --- |
| 12 | | |
| 27 | | |
| -3 | | |
| -16 | | |
| 0 | | |

1. Calculate each remainder and selected place. Which keys share a place?
2. Draw or describe a chain for 12, 27, and -3, putting each new record first.
3. Why must a search compare the complete key after selecting a place?
   How could it prove that 42 is absent? A separate data field can remember
   information associated with the key without taking part in the comparison.

Prediction: ________________________________________________________

## C. Reuse ten records

There are 15 starting references but only 10 record slots. An allocation
counter identifies the next unused slot.

1. What should an eleventh allocation return? Could unused starting places
   remain even when all record slots have been taken?
2. Why would clearing only the starting references leave the counter unable
   to reuse records? Must old record contents be erased to make them reusable?
3. Which references and counter must reset together before another experiment?

Prediction: ________________________________________________________

## D. Apply lookup to two positions

Only after the storage questions, consider these ten numbers:

```text
input position   0    1   2   3   4  5  6  7  8   9
value          -16   -8  -4  -2  -1  1  2  4  8  16
```

1. For target 0, read current positions left to right. At each position,
   try earlier positions from the most recent down to 0. Which pair is first?
   Give the earlier position first and its values separately. Count the
   comparisons for a complete miss.
2. At position 5, which earlier value is needed? If records keep earlier
   values as keys and input positions as data, which field should be searched
   and which field supplies the answer position?
3. For target 2 and current value 1, why could storing before searching use
   the same position twice? If earlier values repeat, which matching position
   is visited first by a newest-first chain and by descending earlier positions?

Prediction: ________________________________________________________

One unresolved question: ____________________________________________
