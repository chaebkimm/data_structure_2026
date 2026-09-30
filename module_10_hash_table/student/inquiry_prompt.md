# Stage A - Initial Inquiry: Where Should a Sparse Record Go?

Name: ____________________________  
Date: ____________________________

Use only this file during the initial inquiry. Preserve your first answers.
Later, add labeled corrections instead of erasing your first thinking.

An **indicator ID** is an unsigned whole-number label for a synthetic record.
The values in this activity are invented for safe study. An ID identifies a
record; it does not state whether the record is true, harmful, or authorized.

## A. Avoid an enormous mostly empty row - 10 points

A program currently stores three records with IDs 10, 18, and 26. Possible
IDs range from 0 through more than four billion.

### A1. Use the ID directly - 3 points

If the ID itself were the position in one enormous row, which positions
would the three records use? Why could that plan waste storage?

____________________________________________________________________

____________________________________________________________________

### A2. Use eight spots - 4 points

Now only eight spots are available, numbered 0 through 7. Divide each ID by
8 and use its remainder as the record's starting spot.

| ID | Division statement | Remainder | Starting spot |
|---:|---|---:|---:|
| 10 |  |  |  |
| 18 |  |  |  |
| 26 |  |  |  |

### A3. Identify the unresolved question - 3 points

What problem appears when all three records receive the same starting spot?

____________________________________________________________________

## B. Use a repeatable next-spot rule - 12 points

Use this rule without changing it:

1. Begin at the calculated starting spot.
2. If that spot already holds a different ID, inspect the next spot.
3. After spot 7, continue at spot 0.
4. Stop after no more than eight inspected spots.

### B1. Place three same-start records - 4 points

Place IDs 10, 18, and 26 in arrival order.

| Spot | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| Stored ID |  |  |  |  |  |  |  |  |

For each ID, list every inspected spot:

10: ____________________  18: ____________________  26: ____________________

### B2. Wrap at the boundary - 4 points

Start with a fresh empty row. IDs 7, 15, and 23 all start at spot 7. Place
them in arrival order and list each inspected route.

| Spot | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| Stored ID |  |  |  |  |  |  |  |  |

Routes: _____________________________________________________________

### B3. Search for present and missing IDs - 4 points

Return to the 10, 18, 26 row from B1. List the inspected spots when looking
for ID 26. Then list the inspected spots for missing ID 34. State what fact
allows the second search to stop.

____________________________________________________________________

____________________________________________________________________

## C. Remove without breaking later searches - 12 points

Return again to the row containing 10, 18, and 26 in spots 2, 3, and 4.
Remove ID 18 from spot 3.

### C1. Choose a marker - 4 points

Compare these two choices:

- make spot 3 look as though it has never held a record; or
- leave a crossed-out marker showing that a record used to be there.

Which choice still lets a search reach ID 26? Trace the search.

____________________________________________________________________

### C2. Reuse a crossed-out spot - 4 points

Suppose ID 34 arrives. It also starts at spot 2. Why should the program
remember crossed-out spot 3 but keep looking until it reaches an untouched
spot or finds ID 34 already present?

____________________________________________________________________

### C3. Update instead of duplicate - 4 points

Suppose the next request supplies ID 26 with a new associated value. Where
should the value change? Explain why placing a second copy of ID 26 into the
crossed-out spot would be incorrect.

____________________________________________________________________

## D. State cost and scope carefully - 6 points

### D1. Chosen IDs - 3 points

If someone can repeatedly choose IDs with the same starting spot, how could
the repeated next-spot rule require more work than expected?

____________________________________________________________________

### D2. Limit the claim - 3 points

Does quick record placement prove that an indicator is authentic or that a
system is secure? Explain one limit.

____________________________________________________________________

## Initial synthesis

> How can a small row support exact lookup for sparse IDs, and what rule must
> preserve a route when IDs share a starting spot?

Your initial explanation:

____________________________________________________________________

____________________________________________________________________

One question your current model does not settle:

____________________________________________________________________

