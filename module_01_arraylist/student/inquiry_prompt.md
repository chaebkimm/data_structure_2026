# Stage A — Initial Inquiry: Keeping an Ordered List Together

Name: ____________________________
Date: ____________________________

Preserve your initial answers. Add corrections later instead of erasing your
first reasoning. Do not open later-stage materials yet.

## A. Distinguish the list from its storage

The brackets show ten neighboring integer slots. The list currently contains
three values. A blank bracket means “not part of the current list,” not a
special integer value. An **index** is a slot number; numbering starts at 0.

```text
[100] [200] [300] [ ] [ ] [ ] [ ] [ ] [ ] [ ]
```

1. Which value is stored at index 1? ________________________________
2. Which indexes belong to the current list? _______________________
3. How many values are in the list? _________________________________
4. How many values can these ten slots hold at most? _______________
5. Could the program read index 2 without checking indexes 0 and 1
   first? Explain.

   _________________________________________________________________

## B. Keep the data packed together

Consider these changes in order.

1. Remove `200`. Which later value must move so the list has no gap?

   _________________________________________________________________

2. Show the remaining list and state its new item count.

   _________________________________________________________________

3. Insert `600` between `100` and `300`. Which value must move before
   `600` can be stored?

   _________________________________________________________________

4. Does this operation sort the numbers, or preserve the requested list
   order? Explain.

   _________________________________________________________________

## C. Decide what happens when the ten slots are full

The number of slots cannot change in this activity. All ten slots now belong
to the list, and a request arrives to add one more value.

1. Why is writing at index 10 unsafe?

   _________________________________________________________________

2. What should the program report to the caller—the code requesting the
   addition?

   _________________________________________________________________

3. Which values and count should remain unchanged when the request cannot
   be completed?

   _________________________________________________________________
