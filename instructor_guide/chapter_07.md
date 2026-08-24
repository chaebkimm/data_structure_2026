# Chapter 7. How to Take Out the First Value First

## Starting Question

> "To take values out in the order they arrived without moving them, what do we need to remember?"

**Expected Answer:** If students say we need to remember the position of the value that waited the longest and the current number of values, write it down. Let them find out the position after reaching the end of the array during the board walkthrough.

## Why We Need This

A stack takes out the last added value first. If we take out the value at position 0 of an array and move the rest forward every time, we keep the arrival order, but the more values we have, the more moving we have to do.

If we reuse the empty spaces at the front for the next additions, we don't have to move the values. We need to store the position of the oldest value and the current number of values together.

## Board Walkthrough

Draw an array with a capacity of 4. Show the old values left in the array and the current queue values in different colors. Cover the next lines and ask first:

* Prediction 1: If we put in four values and take out two, what will `head` and `size` be?
* Prediction 2: In that state, what is the physical position (array slot) where we should put 62?
* Prediction 3: After putting in 5, what will the physical array and the take-out order be?

| Finished Request | Physical Array | `head` | `size` | `tail` | Logical Order or Result |
| --- | --- | --- | --- | --- | --- |
| Initialization | `Empty, Empty, Empty, Empty` | 0 | 0 | 0 | Empty |
| Put 31, 8, 47, 19 | `31, 8, 47, 19` | 0 | 4 | 0 | `31, 8, 47, 19` |
| Take out twice | `31 old, 8 old, 47, 19` | 2 | 2 | 0 | `31`, then returns `8` |
| Put 62 | `62, 8 old, 47, 19` | 2 | 3 | 1 | `47, 19, 62` |
| Put 5 | `62, 5, 47, 19` | 2 | 4 | 2 | `47, 19, 62, 5` |
| Try to put 90 | Same as before | 2 | 4 | 2 | `EVENT_QUEUE_FULL` |

Calculate `tail = (head + size) % capacity` for every state. If the capacity is 0, we don't use the formula. In a full state, we reject the new value and keep all states exactly as they were.

## Common First Thoughts

* "Reading from the left of the array gives the take-out order." But the physical position and the logical order can be different.
* "The old numbers in the taken-out slots are still in the queue." But `head` and `size` decide what the current active values are.
* "If `head` and `tail` are the same, it's an empty queue." But the same exact position also appears when the queue is completely full.
* "If it's full, we just throw away the oldest value." But our rule for this chapter is to reject the new value and keep the existing ones.

## Neutral Questions

* What information can we use to read the physical array and the take-out order, respectively?
* How can we tell the difference between the two states where `head` and `tail` point to the same position?
* After failing to put 90 in, which values and fields should we check to see if the state was saved?

## Vocabulary Rules

**Words we can use:** Array, size, capacity, stack, ownership, and keeping the state after a failure.

**Names we will introduce in this chapter:** First-In-First-Out (FIFO), queue, `enqueue`, `dequeue`, `peek`, circular array, `head`, `size`, calculated `tail`, physical position, and logical order.

**Words we won't use yet:** We won't name the search method that looks at the closest nodes or vertices first. We will also save the explanation of applying a queue to that specific search for the next chapter.

## Final Check

> "Can you explain why the take-out order is `47, 19, 62, 5` in the physical array `[62, 5, 47, 19]`, and what state must remain after we fail to put 90 in?"

**Minimum Expected Answer:** Students should mention that `head == 2` and `size == 4`, explain how to calculate the wrap-around position using the remainder (modulo), and state that the array and fields must stay exactly the same before and after the failure.