# Stage A — Can Earlier Numbers Help Find a Pair?

Name: ____________________  Date: ____________________

A program receives ten numbers and a target total. It must return the positions
of two different numbers whose sum equals the target. Preserve your first
answers. Add labeled corrections later.

## A. Compare every earlier number

Begin with these numbers in positions 0 through 9:

```text
position   0    1   2   3   4  5  6  7  8   9
number   -16   -8  -4  -2  -1  1  2  4  8  16
```

1. The target is 0. Read positions from left to right. At each position,
   compare its number with each earlier number, starting at position 0.
   Which pair appears first? Return positions, then state their numbers.
2. If no pair exists, how many comparisons does this method make? Count
   the comparisons at positions 0, 1, 2, and 9 before finding the total.
3. At position 5 the number is 1. What earlier number would complete a sum
   of 0? Could a record of earlier numbers avoid comparing all of them?

Predictions and reasoning:

____________________________________________________________________

____________________________________________________________________

## B. Group numbers into ten places

Reserve ten places numbered 0 through 9. Use the remainder after division by
10 to choose a place. When the remainder is negative, add 10.

| Number | C remainder after division by 10 | Selected place |
| ---: | ---: | ---: |
| 12 | | |
| 22 | | |
| -8 | | |
| -16 | | |
| 0 | | |

1. What happens when different numbers choose the same place?
2. Module 07 let one record lead to another using an integer index. Draw a
   small chain for the numbers that share a place. Each new record goes first.
3. When searching for 22, why must the program compare the complete number
   after choosing a place? What would prove that 32 is absent?

Drawing or numbered description:

____________________________________________________________________

____________________________________________________________________

## C. Keep positions and numbers distinct

To return a pair, the program must remember where an earlier number came from.
Suppose a stored record contains position 4 rather than the number -1.

1. Where should the program read to recover the earlier number?
2. The target is 2 and the current number is 1. Why would storing the current
   position before searching allow an invalid answer?
3. If two earlier positions contain the same number, must both methods return
   exactly the same positions? What conditions make an answer valid?

____________________________________________________________________

____________________________________________________________________

## D. Reuse the ten records

Only ten linked records are available. A successful search may stop before
all ten positions are read.

1. What must happen to records left from the previous search before the next
   search starts?
2. Why is clearing only the ten starting references insufficient?
3. Predict what an attempt to take an eleventh record should return.

____________________________________________________________________

One question your current explanation leaves open:

____________________________________________________________________
