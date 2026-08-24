# Initial Inquiry — Keeping Ordered Data Together

Name: ____________________________
Date: ____________________________

Preserve your initial answers. Add corrections later instead of erasing your
first reasoning. Do not open later-stage materials yet.

## A. Start with one memory space

The brackets show five neighboring memory slots. Four IP-address values are
currently stored.

```text
[10] [50] [20] [30] [ ]
```

1. Which value is stored at index 2? ________________________________
2. Which indexes currently contain stored data? _____________________
3. How could you find the value at index 3 without checking indexes 0,
   1, and 2 first?

   _________________________________________________________________

## B. Keep the data packed together

1. Cross out `50`. What gap remains? _______________________________
2. What must move so that the remaining values stay together?

   _________________________________________________________________

3. Starting again from `[10] [20] [30] [ ] [ ]`, insert `99` between
   `20` and `30`. Which value must move first, and why?

   _________________________________________________________________

## C. When the memory space becomes full

Suppose every allocated slot contains data.

1. Why is writing one more value into the next position unsafe?

   _________________________________________________________________

2. Describe how the program can continue without losing the existing order.

   _________________________________________________________________

3. What should happen to the old memory space after every value has been
   copied successfully?

   _________________________________________________________________
