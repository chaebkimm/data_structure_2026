# Chapter 10. Picking the Next Data by Urgency and Arrival Order

## Thinking Logically

### Is the first item to arrive always the first one to come out?

A regular waiting line always takes out the item that arrived first. But if we want to process urgent notifications immediately, just looking at who arrived first isn't enough.

Instead, we can attach an "urgency number" to each notification, and agree to always process the one with the smallest number first. In this chapter's code, a smaller number strictly means it gets processed earlier. In the real world, a smaller number doesn't always automatically mean higher urgency, but that is the exact rule we are setting here.

### If urgencies are exactly the same, which one do we pick first?

If we only look at the urgency number, we won't know who should go first among notifications that have the exact same urgency. In this chapter, if the urgencies tie, we break the tie by picking the notification that arrived earlier.

To do this, every time a notification successfully enters our storage, we secretly attach an "arrival ticket" number that starts from 0 and keeps growing by 1. If two urgency numbers match, the notification with the smaller ticket number goes first.

### How do we compare the order of two notifications?

Each notification package holds three important numbers:

* `alert_id`: A simple ID number so we can tell the notifications apart.
* `priority`: The main urgency number.
* `arrival_sequence`: The secret arrival ticket number we attached.

The order between two packages `a` and `b` is decided simply:

```text
If a's urgency is smaller than b's urgency, 'a' goes first.
If the urgencies tie, and a's ticket is smaller than b's ticket, 'a' goes first.

```

The `alert_id` and the physical spot the package sits in the computer's memory do absolutely nothing to change the processing order. A storage system that always hands you the "first" package based on these rules instead of just arrival time is what we are building!

### Should we keep the packages perfectly sorted in memory?

In this chapter, we just drop the packages into a completely unsorted, messy array. When a new package arrives, we just stick it into the very next empty slot at the end. Because of this, whenever we actually need to pull out the most important package, we are forced to search through the entire messy array to find it.

The array doesn't start with 64 empty slots right away. It starts with exactly 4 slots on the very first insertion, and only expands when it gets completely full, following this exact pattern:

```text
0 -> 4 -> 8 -> 16 -> 32 -> 64

```

If the computer fails to give us a bigger array, the new package and its ticket are simply rejected, and the existing packages stay perfectly safe.

### How do we find the most important notification?

We grab the package sitting at the first slot (index 0) and declare it our current "winner". Then, we compare it with every single package from slot 1 all the way to the end. If we find a package that should go earlier based on our rules, we swap it out and make that one our new winner.

If there are `n` total packages, we compare our first winner against the other `n - 1` packages. You can choose to simply look at the winner we found, or you can actually pull that winning package completely out of the storage.

### How do we fill the empty space if we pull out a package from the middle?

If the winning package happens to be sitting right in the middle of our messy array, pulling it out leaves a gap. To fix this instantly, we simply grab the very last living package at the end of the array and drop it directly into that empty gap! Then we decrease our total size count by 1.

This scrambles the physical order in the array, but it doesn't matter at all. The processing order stays perfectly safe because the next time we need a winner, we will just compare all the urgencies and tickets all over again anyway!

### If we put in these exact notifications, what order do they come out?

Let's put seven notifications in. `p` is the urgency, and `s` is the arrival ticket.

```text
71(p3, s0), 88(p1, s1), 42(p2, s2), 17(p1, s3),
26(p4, s4), 9(p2, s5), 63(p1, s6)

```

The processing order will perfectly be:

```text
88, 17, 63, 42, 9, 71, 26

```

For urgency 1, it perfectly follows the tickets: 1, 3, 6. For urgency 2, 42 got its ticket before 9, so it comes out first.

The very first time we look for a winner among 7 items, we have to make 6 comparisons. If we pull out all seven values one by one, the total number of comparisons we make adds up like this:

```text
6 + 5 + 4 + 3 + 2 + 1 + 0 = 21

```

### What if the storage is completely empty or completely full?

If you try to look at or pull a package from a completely empty storage, it politely refuses and returns an `ALERT_PRIORITY_QUEUE_EMPTY` error. If the storage already holds 64 items, it strictly refuses to add more and returns an `ALERT_PRIORITY_QUEUE_FULL` error.

It will also strictly refuse to insert a new package if the secret ticket number hits its absolute maximum limit (`SIZE_MAX`) and can't count any higher. However, if you pull out the very last package so the storage becomes completely empty again, we safely reset the ticket machine back to 0 so we can start fresh!

A failed request leaves your storage and your output variables completely untouched. If our comparison counter hits its maximum limit, it doesn't wrap around and break; it just safely freezes at the maximum.

Our code also has a simple reset tool that only resets the comparison counter back to 0. It absolutely does not touch the packages, the array size, or the ticket machine.

### Will low-urgency notifications ever get processed?

If highly urgent notifications keep arriving forever, a poor low-urgency notification might get pushed to the back forever. Our storage tool doesn't fix this problem by itself. You would need a separate, outside rule to artificially boost the urgency of a notification if it has been waiting too long.

---

## Calculating Efficiency

### Efficiency of putting a notification in?

Because we just stick the new package at the very end of the messy array, it is instantly fast, taking $O(1)$ time. If the array gets full and we have to expand it, moving the $n$ existing items takes $O(n)$ time. However, because we double the size every time we expand, this heavy moving happens very rarely. Averaged out over many insertions, it still acts like a super-fast $O(1)$.

### Efficiency of peeking at the most important notification?

Because the array is completely messy, we are forced to check absolutely every single package to find the winner. If there are $n$ packages, this search always takes $O(n)$ time.

### Efficiency of pulling out the most important notification?

Searching for the winner takes $O(n)$ time. Plugging the empty gap with the very last package is instantly fast, $O(1)$. So, the total time is still $O(n)$.

### Would it be faster if we kept the array perfectly sorted?

If we forced the array to stay sorted so the winner is always waiting at the very end, peeking and pulling would be instantly fast, $O(1)$. However, *inserting* a new package would suddenly become slow, $O(n)$, because we would have to slide lots of packages around just to make room for it in the perfect spot.

The best method really changes depending on whether you insert things more often or pull things out more often. In Chapter 11, we will learn a clever new storage method that handles *both* actions very quickly!

### How much memory does it use?

If there are $n$ packages, the storage space needed grows steadily with the packages, taking $O(n)$ space. Our specific practice code strictly caps the capacity at 64 items.

---

## Glossary

### Priority Queue

A data structure that picks the next data based on a specific comparison rule, not just the arrival order.

### Minimum Priority Queue

A priority queue that returns the record with the smallest value according to the comparison rule first.

### Priority

A value attached to a record to determine its processing order.

### Arrival Sequence

A number assigned by the queue in the exact order that insertions succeed.

### Record

A single item that bundles several related values together.

### Comparator

The rule that decides which of two records should go first.

### Stable Tie-Breaking

The rule that picks the data that arrived earlier when the main comparison values are exactly the same.

### Starvation

A situation where a task is never selected for a long time because tasks with higher priority keep coming in.

---

## Coding Plan

### Initializing the Priority Queue

* **Check initial state:** Make sure all fields are completely clean (`0` or `NULL`).
* **Use lazy allocation:** Do not grab an array right away. Wait and ask the computer for exactly 4 slots only when the very first insertion happens.

### Comparing Record Order

* **Compare priority:** If the two urgency numbers are different, the smaller one wins.
* **Compare arrival sequence:** If the urgencies tie exactly, the smaller ticket number wins.
* **Exclude ID:** Absolutely do not use `alert_id` to decide the winner.

### Inserting a Notification

* **Check limits:** Check if the storage is completely full (64 items) or if the ticket machine is maxed out.
* **Expand space:** If the array is full, double the space.
* **Write record:** Save the ID, urgency, and current ticket number into the next empty slot at the end.
* **Update numbers:** Increase `size` and the ticket machine by 1.

### Finding the Front-Most Position

* **Set first candidate:** Pick the package at index 0 as the very first candidate.
* **Scan array:** Compare this candidate against every single package from index 1 to the end.
* **Count comparisons:** Every time you compare, carefully increase the comparison counter, but freeze it safely if it hits its maximum limit (`SIZE_MAX`).
* **Update candidate:** If you find a package that wins the comparison, remember its exact index.

### Peeking or Extracting the Front-Most Notification

* **Check empty queue:** If the storage is completely empty, safely return an `ALERT_PRIORITY_QUEUE_EMPTY` error.
* **Find minimum:** Scan the array to find the exact index of the winning package.
* **Peek:** If just peeking, copy the winning package to the user's output.
* **Extract:** If pulling out, plug the empty gap using the very last package in the array, and decrease `size`.
* **Clean up empty state:** If you just pulled out the very last package, safely reset the ticket machine to 0.

---

## C Code

### Making the Comparison Rule

```c
#include "alert_priority_queue.h"
#include <stdbool.h>

static bool record_precedes(
        const AlertRecord *left,
        const AlertRecord *right)
{
        if (left->priority != right->priority) {
                return left->priority < right->priority;
        }

        return left->arrival_sequence < right->arrival_sequence;
}


```

### Finding the Front-Most Record

```c
#include <stdint.h>

static size_t find_minimum_index(AlertPriorityQueue *queue)
{
        size_t minimum_index = 0U;

        for (size_t i = 1U; i < queue->size; i = i + 1U) {
                if (queue->comparison_count < SIZE_MAX) {
                        queue->comparison_count =
                                queue->comparison_count + 1U;
                }

                if (record_precedes(
                        &queue->data[i],
                        &queue->data[minimum_index])) {
                        minimum_index = i;
                }
        }

        return minimum_index;
}


```

### Using the Priority Queue

```c
AlertPriorityQueue queue = {0};
AlertRecord next = {0};

if (alert_priority_queue_init(&queue) ==
    ALERT_PRIORITY_QUEUE_OK) {
        alert_priority_queue_insert(&queue, 71, 3U);
        alert_priority_queue_insert(&queue, 88, 1U);
        alert_priority_queue_insert(&queue, 42, 2U);
        alert_priority_queue_insert(&queue, 17, 1U);

        if (alert_priority_queue_peek_min(&queue, &next) ==
            ALERT_PRIORITY_QUEUE_OK) {
                /* next.alert_id is 88 and it is still in the queue. */
        }

        if (alert_priority_queue_extract_min(&queue, &next) ==
            ALERT_PRIORITY_QUEUE_OK) {
                /* next.alert_id is 88 and the next winner is 17. */
        }

        alert_priority_queue_destroy(&queue);
}


```

### Filling the Extracted Spot

```c
static AlertRecord remove_minimum_at(
        AlertPriorityQueue *queue,
        size_t minimum_index)
{
        size_t final_index = queue->size - 1U;
        AlertRecord result = queue->data[minimum_index];

        if (minimum_index != final_index) {
                queue->data[minimum_index] =
                        queue->data[final_index];
        }

        queue->size = final_index;
        if (queue->size == 0U) {
                queue->next_sequence = 0U;
        }

        return result;
}


```

The real `extract-min` function first completely checks if the storage is not empty and that the output address is perfectly correct. Then it finds the winning index, runs this instant swap, and only actually gives the winning record to the user at the very end.