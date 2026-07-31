# Initial Inquiry — A Collection That Must Grow

Name: ____________________________  
Date: ____________________________

Preserve your initial answers. Add corrections later rather than erasing the
original reasoning. Do not open later-stage materials yet.

## A. Retrieval warm-up

Given:

```c
int events[4] = {17, 23, 31, 46};
```

1. What are the valid indexes? ______________________________________
2. Write the expression that accesses the third value. _______________
3. What information does C store automatically about how many elements
   the program considers “in use”?

   _________________________________________________________________

4. What would `events[4] = 52;` attempt to do?

   _________________________________________________________________

## B. Macro-Question

> How can a fixed block of C memory behave like a collection that grows, and what trade-offs change when elements are stored in separately allocated nodes?

Initial model:

____________________________________________________________________

____________________________________________________________________

____________________________________________________________________

## C. Derive the minimum state

A fifth event arrives after all four slots are occupied. Without naming C
fields yet, list the minimum facts a reusable collection must remember.

1. _________________________________________________________________
2. _________________________________________________________________
3. _________________________________________________________________

For each fact, explain what could go wrong if it were missing:

____________________________________________________________________

____________________________________________________________________

One question your model does not yet answer:

____________________________________________________________________
