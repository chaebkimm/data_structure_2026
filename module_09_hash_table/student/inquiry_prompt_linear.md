# Stage A — Initial Inquiry, Linear Version

Name: ____________________  Date: ____________________

This version asks the same questions as `inquiry_prompt.md`. Use numbered
sentences instead of tables or drawings. Preserve your first answers and label
later corrections.

## A. Compare every earlier number

The ten numbers, in position order 0 through 9, are
`-16, -8, -4, -2, -1, 1, 2, 4, 8, 16`.

1. The target is 0. Read positions from left to right. Compare each current
   number with earlier numbers in position order starting at 0. Which pair
   appears first? Give positions and numbers separately.
2. Count comparisons at positions 0, 1, 2, and 9. How many comparisons occur
   in a complete search with no answer?
3. At position 5 the number is 1. Which earlier number completes a total of
   0? How might a record of earlier numbers shorten the search?

Response: __________________________________________________________

## B. Group numbers into ten places

Reserve places 0 through 9. Divide a number by 10 and use its C remainder.
Add 10 when the remainder is negative.

1. Give the remainder and selected place separately for 12, 22, -8, -16,
   and 0.
2. Identify the numbers that choose the same place.
3. Describe a chain of those numbers using Module 07's integer next links.
   Put each new record first.
4. Explain why choosing a place is insufficient to identify 22 exactly.
   State how a search proves that 32 is absent.

Response: __________________________________________________________

## C. Keep positions and numbers distinct

A stored record may contain position 4 rather than the number -1.

1. State where the program reads to recover the earlier number.
2. The target is 2 and the current number is 1. Explain how storing the
   current position before searching could use the same position twice.
3. If earlier numbers repeat, decide whether both search methods must return
   identical positions. State the conditions for a valid pair.

Response: __________________________________________________________

## D. Reuse the ten records

A successful search can leave some of the ten linked records in use.

1. Describe what must happen before the next search starts.
2. Explain why clearing only the ten starting references loses reusable
   records.
3. Predict the result of an attempt to take an eleventh record.

Response: __________________________________________________________

One unresolved question: ____________________________________________
