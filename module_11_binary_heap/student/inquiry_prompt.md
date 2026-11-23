# Module 11 Inquiry — Keep the Minimum Ready

Name ____________________    Date ____________________

Predict first. Then check one prediction against [lab.c](lab.c). You can
also use the [linear response format](inquiry_prompt_linear.md).

## Which value should leave first?

Five requests have priority values 9, 6, 5, 3, and 1. A smaller number
means higher priority. If all five are waiting, give their removal order.
In an unordered array, what work would you repeat to select each minimum?

Prediction _________________________________________________________

## How little order is enough?

Place the five values into the slots below so that each parent is less
than or equal to its children. Find two valid arrangements. What stays
true at index 0 even when two siblings change order?

| Index | Live children | Arrangement 1 | Arrangement 2 |
| ---: | --- | --- | --- |
| 0 | 1, 2 | | |
| 1 | 3, 4 | | |
| 2 | none | | |
| 3 | none | | |
| 4 | none | | |

Reason _____________________________________________________________

## Which path changes?

Start with three unordered values `[9, 6, 5]`. Which child would you
promote to make a min-heap? Next insert 3, then 1. For each insertion,
predict where the new value starts and which parent values move.

After both insertions, predict the first value removed and which value
leaves the last slot to fill the opening. How should the algorithm choose
between two children? What if only the left child exists?

Prediction _________________________________________________________

## When is each call valid?

The array has five slots. Give the size condition for insertion and for
removal. Predict the number of output values when the full heap is drained
into a separate array. What will the heap size be at the end?

Prediction _________________________________________________________

Use the [lab handout](lab.md) to check an answer. Record the operation,
observed state, and what it confirmed or changed.

Evidence ___________________________________________________________
