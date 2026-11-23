# Module 11 Class Workbook — Binary Heaps

Name ____________________    Date ____________________

Use the [concept slides](ppt_material.md), [lab slides](ppt_lab_material.md),
and [source](lab.c). Keep your first prediction, then compare it with the
operation in the [handout](lab.md). Either version of the
[investigation worksheet](investigation_worksheet.md) can hold your trace.

## 1. Which child should rise?

Draw the tree stored as `[9, 6, 5]` at size 3. Before `heapify()`, explain
why each child already forms a heap. Circle the child that must move and
show the final position of 9. How could you check the result using only
parent–child comparisons?

Prediction ____________________    Checked trace ____________________

## 2. Which values actually move during insertion?

Starting from that heap, trace `enqueue(3)` and then `enqueue(1)`.
For each, draw an arrow for each parent copied down. Mark the slot
returned by `sift_up` and the statement in `enqueue` that fills it.

Prediction ____________________    Checked trace ____________________

## 3. How does one removal preserve the shape?

Start from the full heap you just drew. Circle the saved root and underline
the former last value. After the size decreases, list the surviving child
indices at the root. Which child moves, and what stops the replacement
from going any farther? Give the returned value and remaining live array.

Prediction ____________________    Checked trace ____________________

## 4. Where does the sorted order appear?

Continue removing until the last value leaves. List the returned values
in order. On the last removal, which condition stops a child read? Explain
why the example gives `heap_sort` a separate array and why the sort loop
saves the starting size.

Prediction ____________________    Checked trace ____________________

## 5. What would you test?

Choose one of the three original cases in the [handout](lab.md). Describe
the input, the first assertion you would write, and a mistake that the
assertion would catch. State the size conditions for insertion and removal.

Test idea __________________________________________________________
