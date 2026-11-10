# Stage A — Initial Inquiry, Linear Version

Name: ____________________  Date: ____________________

This asks the same questions as `inquiry_prompt.md`. Use numbered sentences
instead of tables or drawings. Begin with one-value lookup; keep the pair
application until section D. Preserve first answers and label later corrections.

## A. Find a value, then remember its position

Input positions 0, 1, and 2 contain values 2, 5, and 6.

1. Read in order to find 5, then search for absent 3. List comparisons and
   the result of each search.
2. Reserve seven places 0–6. At the place equal to a stored value, write
   that value's input position; use -1 for unused places. List all seven entries.
3. Explain lookup for 5 or 3 using that row. What goes wrong with a negative
   stored value or a few values spread across an extremely large range?

Prediction: ________________________________________________________

## B. Group keys into fifteen places

Reserve places 0–14. Take the C remainder after division by 15 and add
15 if it is negative.

1. Give remainder and selected place for 12, 27, -3, -16, and 0. Identify
   keys that share a place.
2. Describe a chain for 12, 27, and -3 through integer next links, putting
   each new record first.
3. Explain why place selection alone cannot identify a key and how a search
   proves that 42 is absent. A separate data field can remember information
   associated with a key without participating in key comparison.

Prediction: ________________________________________________________

## C. Reuse ten records

There are 15 starting references and 10 record slots. An allocation counter
identifies the next unused slot.

1. Predict an eleventh allocation's result. Can all slots be used while some
   starting references still indicate empty places?
2. Explain why clearing only starting references does not restore capacity.
   Must old record contents be erased?
3. Identify the starting references and counter that must reset together.

Prediction: ________________________________________________________

## D. Apply lookup to two positions

The ten numbers in input positions 0–9 are
`-16, -8, -4, -2, -1, 1, 2, 4, 8, 16`.

1. For target 0, read current positions left to right. Compare with earlier
   positions from the most recent down to 0. Give the first pair with the
   earlier position first, then its values. Count comparisons for a complete miss.
2. At position 5, which earlier value is needed? If a record contains an
   earlier value as key and its input position as data, identify the field
   searched and the field supplying the answer position.
3. For target 2 and current value 1, explain self-pairing if storage comes
   before search. With repeated earlier values, identify the first matching
   position for a newest-first chain and descending earlier-position search.

Prediction: ________________________________________________________

One unresolved question: ____________________________________________
