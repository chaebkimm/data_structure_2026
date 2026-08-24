# Chapter 7. Taking Out the First-In Data First

## Thinking Logically

### Why do we remember the arrival order?

Imagine event numbers arrived in the order `31`, `8`, `47`, `19`. If you want to process the event that came first, you need to take them out in that exact same order. You do not sort them by how big or small the numbers are.

The simple rule of taking out the data that was put in first is exactly how a waiting line works. The first person to join the line is the first person to be served. A storage system that manages information using this strict rule helps us process things in the exact order they happened.

### What happens if we take out data from the front of an array?

We could put all our items in a straight array. When we take out the item at the very front (index 0), we could pull every single remaining item one step forward to fill the empty space. The order stays perfectly correct, but every time we take out just one item, we have to do a lot of heavy lifting to shift everything else.

To avoid all that moving, we can simply leave the items exactly where they are. Instead of shifting the items forward, we just move our "starting point" marker to the next slot when we take out the oldest item. We store this starting position in a variable called `head`.

### How do we reuse the empty spaces at the front?

If we keep dropping new items in, we will eventually reach the very last slot of our array. But because we already took out some older items earlier, there are empty, unused slots sitting at the very front of the array!

To reuse these empty spaces, we can simply jump the "next empty spot" all the way back to the very first slot. This clever trick treats a straight array as if its ends are connected in a continuous circle. The physical array isn't actually shaped like a circle; only the position calculation loops back to the start when it hits the end.

Our waiting line remembers four important pieces of information:

* `data`: The actual memory array holding the event numbers.
* `capacity`: The total number of slots we have in the array.
* `head`: The exact position marker of the oldest item.
* `size`: The exact count of how many items are currently waiting in line.

We don't need to permanently save the next empty spot; we just calculate it quickly whenever we need it:

```text
tail = (head + size) % capacity

```

Thanks to the remainder math trick (`%`), the calculated spot safely loops around and always points to a valid slot between `0` and `capacity - 1`. If our `capacity` is `0`, we simply skip this math.

### Is the order we see in the array the actual processing order?

Let's say we have an array with 4 slots. We put in `31`, `8`, `47`, `19`, take out the oldest two items, and then put in `62`, `5`. The physical slots in the computer's memory look like this:

```text
Physical array    [62, 5, 47, 19]
head              2
size              4
Processing order  47, 19, 62, 5

```

The physical order the numbers sit in the array and the actual processing order can look completely different! The real order always starts exactly at the `head` marker and reads forward in a looping circular motion based on the `size`.

### If the starting point and the next spot are the same, is it empty?

Because the position loops around in a circle, both a completely empty line and a completely full line can have the `head` (starting point) and the next empty spot pointing to the exact same slot! This is exactly why we must keep a separate `size` count of how many items are actually waiting.

* If `size == 0`, the line is completely empty.
* If `size == capacity`, the line is completely full.

When we finally take out the very last remaining item, we cleanly reset both the `head` and the `size` back to `0`. Even if old numbers are still physically sitting inside the array, the computer logically ignores them because the line is officially empty.

### What if it is completely full or empty?

The waiting line in this chapter does not automatically ask for more slots when it gets full. If we try to squeeze an item into a completely full line, it politely refuses, returns an `EVENT_QUEUE_FULL` error, and keeps the existing items perfectly safe. If we try to look at or take out an item from a completely empty line, it returns an `EVENT_QUEUE_EMPTY` error.

A line built with a capacity of `0` is also considered a perfectly valid, permanently empty line. We obviously can't put items into it, but our clever code safely skips any math that would cause a divide-by-zero crash.

## Calculating Efficiency

### Efficiency of putting data in

We calculate the next looping position just once and drop a value into one single slot. The amount of work is always exactly the same, no matter how long the line is. It is `O(1)`.

### Efficiency of looking at or taking out data

Looking simply reads the slot at the `head` point. Taking out reads that same slot and updates our marker numbers. Because neither action shifts the other data around, both are instantly fast, taking `O(1)`.

### How different is it from an array that shifts values forward?

If we forced everything to slide forward every time we took out the front item, the worst-case scenario for `n` items would require moving `n` items, which takes `O(n)` time. Because our looping calculation doesn't move the actual values around at all, it stays incredibly fast at `O(1)`.

### How much memory does it use?

When we first build the line, we reserve space for the `capacity` number of slots just once. Even if we use fewer items, this space stays exactly the same. Our specific code in this chapter accepts a maximum of 64 slots.

## Glossary

### Queue

A data structure that manages information by taking out the first-in data first.

### First-In, First-Out (FIFO)

The rule where the data that came in first is the very first to go out.

### Enqueue

The specific action of adding new data to the back of the queue.

### Dequeue

The specific action of taking out the oldest data from the front of the queue.

### Peek

The action of looking at the front data without actually removing it from the queue.

### Circular Array

A storage method that treats the position after the end of the array as index 0, allowing us to easily loop around and reuse empty spaces at the front without moving data.

### Logical Order

The true order in which data will actually be taken out of the queue, which may differ from the physical order it sits in the array.

## Coding Plan

### Initializing the Queue

* **Check status:** Make sure all fields of the structure are completely clean (`0` or `NULL`).
* **Check capacity:** Make sure the requested total capacity is 64 or less.
* **Reserve space:** If the capacity is a positive number, grab memory for an `int` array.
* **Save state:** Update the `data` address and `capacity` only after successfully getting the memory space.

### Enqueuing Data

* **Check status:** Make sure the queue's fields are valid.
* **Check empty space:** If `size == capacity`, safely return an `EVENT_QUEUE_FULL` error.
* **Calculate position:** Find the next insert spot using `(head + size) % capacity`.
* **Save value:** Write the event code to that calculated slot and increase `size` by 1.

### Peeking the Front Data

* **Check if empty:** If `size == 0`, safely return an `EVENT_QUEUE_EMPTY` error.
* **Prepare value:** Copy the value sitting at `data[head]` into a safe local variable.
* **Save result:** Write to the user's output variable only after all checks are successfully done.

### Dequeuing the Front Data

* **Keep value:** First, safely copy the value at `data[head]` into a local variable.
* **Decrease count:** Decrease `size` by 1.
* **Move front position:** If values still remain, move `head` forward to the next slot using `(head + 1) % capacity`. If the queue just became completely empty, cleanly reset `head` to `0`.
* **Save result:** Write the saved value to the user's output variable only after all state changes are totally complete.

### Destroying the Queue

* **Return space:** Give the array memory pointed to by `data` back to the computer.
* **Reset status:** Turn all `data`, `capacity`, `head`, and `size` fields completely back to `0` or `NULL`.

## C Code

### Creating and Using the Queue

```c
#include "event_queue.h"

EventQueue queue = {0};
int event_code = 0;

if (event_queue_init(&queue, 4U) == EVENT_QUEUE_OK) {
        event_queue_enqueue(&queue, 31);
        event_queue_enqueue(&queue, 8);
        event_queue_enqueue(&queue, 47);

        if (event_queue_peek(&queue, &event_code) == EVENT_QUEUE_OK) {
                /* event_code is 31. 31 is still in the queue. */
        }

        if (event_queue_dequeue(&queue, &event_code) == EVENT_QUEUE_OK) {
                /* event_code is 31. The next front value is 8. */
        }

        event_queue_destroy(&queue);
}

```

### Calculating the Next Insert Position

```c
if (queue.size < queue.capacity) {
        size_t tail = (queue.head + queue.size) % queue.capacity;

        queue.data[tail] = 62;
        queue.size = queue.size + 1U;
}

```

Since we check `size < capacity` first, we know for sure that `capacity` is not `0`. Therefore, the remainder calculation is completely safe from a divide-by-zero error.

### Dequeuing the Front Data

```c
if (queue.size > 0U) {
        int result = queue.data[queue.head];
        size_t new_size = queue.size - 1U;
        size_t new_head;

        if (new_size == 0U) {
                new_head = 0U;
        } else {
                new_head = (queue.head + 1U) % queue.capacity;
        }

        queue.head = new_head;
        queue.size = new_size;
        event_code = result;
}

```