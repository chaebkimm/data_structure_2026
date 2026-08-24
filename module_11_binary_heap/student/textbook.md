# Chapter 11. Taking Out the First Data Without Scanning Everything

## Thinking Logically

### Why do we need a different storage method?

In Chapter 10, our storage dropped new packages into a messy, unsorted array. Dropping a new notification in was super fast, but we were forced to check absolutely every single spot in the array every time we wanted to pull out the most important notification.

This chapter uses the exact same rules for deciding who goes first: a smaller urgency number wins, and if they tie, the earlier arrival ticket wins. What changes here is *how* we organize the packages inside the array so we can find the winner instantly.

### How do we create shortcuts inside an array?

Imagine turning the flat array into a downward-branching family tree. We fill the tree from top to bottom, strictly moving from left to right on every single level. Every level must be completely packed full before anyone moves to the next level down.

Because this perfectly packed shape is so predictable, if a package is sitting at slot `i` in the array, we can use simple math to instantly find the exact positions of its parent or its children:

```text
Left child  = 2 * i + 1
Right child = 2 * i + 2
Parent      = (i - 1) / 2    (only if it is not the top item, slot 0)

```

A child slot only actually has a package in it if the math result is smaller than our total `size`. If we just drop a brand-new package into the very next empty spot (`data[size]`), this perfectly packed shape is naturally maintained!

### How do we gather the most important package at the very top?

We organize the packages using one strict, golden rule: **A parent package must always be more important than its children.**

If a perfectly packed tree strictly follows this rule, it creates a powerful structure. Every single item connects back up to the top spot (position 0) through its parents. Because a child can never, ever beat its parent, the absolute grand champion is naturally trapped right at the top!

### Where does the golden rule break when we put in a new package?

If we drop a new package into the very next empty spot at the end of the array, the perfectly packed shape stays perfect. The relationships between all the old packages also stay perfect. The *only* place the golden rule might break is between the brand-new package and its immediate parent!

If the new package is actually more important than its parent, we simply pull the parent down one step to make room, and we look at the parent's old spot. We keep comparing the new package against the next parent up, climbing higher and higher until we find a parent that is finally more important, or until we reach the very top. This climbing action perfectly fixes the tree!

```text
Set the new package as a candidate at the very last spot.
If the candidate is more important than its parent, pull the parent down.
Keep climbing up until the candidate finds its proper place.
Drop the candidate safely into that final empty spot.

```

### Why is finding the most important package so simple now?

Because our golden rule is never broken, the absolute most important package is *always* sitting exactly at `data[0]`. If you want to look at it, you just copy it. You don't need to scan the array or compare any packages at all!

### How do we fix the tree after pulling out the top package?

When we pull out the grand champion at the top, position 0 suddenly becomes a gaping hole. To fix this, we grab the very last package sitting at the bottom of the array to act as our candidate to plug the hole, and we decrease our total `size` count by 1.

But if we just drop it in at the top, it might break the golden rule with its new children! So, we look at the hole's two children and pick the one that is *more important*. If this selected child is more important than our candidate, we pull the child up to fill the hole, and the candidate drops down a level. We keep doing this until the candidate safely finds a spot where it is more important than the children below it.

```text
Set the last package as the candidate to plug the top hole.
If there are children below, pick the child that is more important.
If that child is more important than the candidate, pull the child up.
Keep dropping the candidate down until it finds its proper place.

```

*(Note: You must always check if a right child actually exists before comparing the two children. If there is only a left child, you just compare the candidate directly against the left child).*

### Why must we always pick the more important child?

If we mistakenly pulled the "less important" child up into the parent spot, the other child sitting below it would actually be *more* important than its new parent! This would instantly break the golden rule. By always pulling the most important child up, we guarantee the new parent-child relationship stays perfect.

### What order will the same seven notifications come out?

Let's insert the exact same seven notifications from Chapter 10:

```text
71(p3, s0), 88(p1, s1), 42(p2, s2), 17(p1, s3),
26(p4, s4), 9(p2, s5), 63(p1, s6)

```

After putting them all in, they shift around to follow the golden rule. The ID numbers sitting in the array look scrambled like this:

```text
[88, 17, 63, 71, 26, 9, 42]

```

But if we pull them all out from the top one by one, the final processing order is exactly the same as in Chapter 10:

```text
88, 17, 63, 42, 9, 71, 26

```

However, if we count the work, the messy array in Chapter 10 made 21 comparisons to pull them all out. Our clever tree structure here only needs to make 12 comparisons!

### Is this tree just a perfectly sorted array?

No! Only the vertical parent-child relationship matters. The order between siblings sitting next to each other doesn't matter at all, and the entire left side of the tree doesn't have to be more important than the entire right side.

Because of this, finding the *most important* package is lightning fast, but if you wanted to find a specific ID number, you would still be forced to check the whole array. This structure is perfectly designed for pulling out the top winner instantly, not for general searching!

### How do we double-check that the golden rule is perfect?

Our safety tool checks every single package (starting from index 1) against its parent. If it finds even one single child that is more important than its parent, it immediately reports that the rule is broken.

If there are `n` packages, this check makes `n - 1` comparisons. This full check takes an amount of work proportional to the items, $O(n)$, so we keep its workload separate from our normal fast operations.

### What if expanding space or an action fails?

Our array grows exactly like before: `0, 4, 8, 16, 32, 64`. If the computer refuses to give more memory, or if the array hits the strict 64 limit, the existing tree stays perfectly safe. Trying to look at or pull from an empty tree also changes nothing.

When the very last package is pulled out, making the tree completely empty again, we safely reset the arrival ticket machine back to 0. If our comparison counter hits its maximum limit, it safely freezes. Our manual reset tool only resets the comparison counter; it never touches the packages or the shape of the tree.

---

## Calculating Efficiency

### Efficiency of peeking at the most important record?

Because it simply grabs the package sitting at index 0, it is instantly fast, $O(1)$.

### Efficiency of putting a record in?

Our climbing action only follows one single path up through the parents. Because the tree is packed perfectly, the number of items has to double just to add one more level of climbing. This makes it incredibly fast, taking $O(\log n)$ work.

If the array is full, moving all the old items takes $O(n)$. But because we double the size every time, this heavy moving is rare. Averaged out, inserting is still a super-fast $O(\log n)$.

### Efficiency of pulling out the most important record?

Our dropping action also only follows one single path down from the top to the bottom. Just like inserting, this takes very little work, $O(\log n)$.

### Efficiency of double-checking the rules or searching?

Checking the golden rule forces you to look at every single parent-child pair, taking $O(n)$ work. Trying to find a specific ID number might also force you to look at every single package, taking $O(n)$ work.

### How much memory does it use?

The array uses memory proportional to the packages, $O(n)$. It doesn't waste any extra memory storing confusing connection addresses because the math does it for us. Our specific practice code caps this at exactly 64 items.

---

## Glossary

### Complete Binary Tree

A binary tree where all levels except the last are completely filled, and the last level is filled continuously from the left.

### Binary Heap

A data structure that maintains both the complete binary tree shape and the parent-child order rule.

### Minimum Heap (Min-Heap)

A binary heap where every parent comes before its children, meaning the absolute minimum value sits at the root.

### Heap-Order Invariant

The strict condition that no child can ever come before its parent.

### Root

The top node that has no parent. In an array-based heap, this is the record at index 0.

### Sift-Up

The action of fixing the heap rule by comparing a newly added record with its parent and moving it upwards toward the root.

### Sift-Down

The action of fixing the heap rule by taking a candidate at the root and moving it downwards by comparing it with its earlier child.

---

## Coding Plan

### Calculating Array Positions

* **Parent calculation:** If the current index `i` is greater than 0, use the math `(i - 1) / 2`.
* **Left child calculation:** Use the math `2 * i + 1`.
* **Right child calculation:** Simply add 1 to the left child's position.
* **Check range:** Only try to read from the array if the math result is strictly smaller than the current `size`.

### Inserting a Record

* **Check conditions:** Verify the 64-item limit, the ticket machine limits, and if the computer can give more memory.
* **Make candidate:** Bundle the new ID, urgency, and ticket into one candidate package.
* **Start at the end:** Pretend the candidate is sitting at the very next empty spot (`size`).
* **Bubble up (Sift-up):** If the candidate beats its parent, pull the parent down one slot.
* **Count comparisons:** Increase your counter every single time you compare the candidate against a parent.
* **Save candidate:** Drop the candidate into the final empty spot it found, then increase `size` and the ticket machine.

### Peeking the Front-Most Record

* **Check empty heap:** If `size == 0`, return an empty state error.
* **Copy root:** Instantly copy `data[0]` straight into the user's output variable.

### Extracting the Front-Most Record

* **Keep result:** Safely copy the grand champion at `data[0]` into a temporary variable.
* **Set candidate:** Grab the very last package in the array to act as the candidate to drop down, and calculate the new size.
* **Pick child:** Look at the hole's children and pick the one that is more important.
* **Bubble down (Sift-down):** If the selected child beats the candidate, pull the child up to fill the hole.
* **Count comparisons:** Count both the comparison to pick the best child, *and* the comparison against the candidate.
* **Confirm state:** Drop the candidate into its final hole, decrease `size`, and give the saved champion to the user.

### Checking the Golden Rule

* **Loop children:** Check every single index from 1 all the way to `size - 1`.
* **Calculate parent:** Find the parent position for each child using the math.
* **Compare order:** Check if the child mistakenly beats the parent.
* **Count comparisons:** Even if you find a broken rule, do not stop; check exactly once for every child to get a perfect count.
* **Save result:** After checking everything, tell the user if it was true or false.

---

## C Code

### Comparing the Order of Records

```c
#include "alert_priority_queue.h"

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

### Calculating Parent and Child Positions

```c
#include <stddef.h>

static size_t parent_index(size_t child)
{
        return (child - 1U) / 2U;
}

static size_t left_child_index(size_t parent)
{
        return parent * 2U + 1U;
}

```

`parent_index` should strictly only be used when `child > 0`.

### Sifting Up a New Record

```c
static void place_by_sifting_up(
        AlertPriorityQueue *queue,
        AlertRecord candidate)
{
        size_t index = queue->size;

        while (index > 0U) {
                size_t parent = parent_index(index);

                if (!record_precedes(
                        &candidate,
                        &queue->data[parent])) {
                        break;
                }

                queue->data[index] = queue->data[parent];
                index = parent;
        }

        queue->data[index] = candidate;
        queue->size = queue->size + 1U;
        queue->next_sequence = queue->next_sequence + 1U;
}

```

The real `insert` function tracks every comparison carefully and only triggers this climbing action after successfully ensuring there is enough memory space.

### Sifting Down the Last Record

```c
static AlertRecord remove_root(AlertPriorityQueue *queue)
{
        AlertRecord result = queue->data[0];
        size_t new_size = queue->size - 1U;

        if (new_size > 0U) {
                AlertRecord candidate = queue->data[new_size];
                size_t hole = 0U;

                while (left_child_index(hole) < new_size) {
                        size_t left = left_child_index(hole);
                        size_t right = left + 1U;
                        size_t selected = left;

                        if (right < new_size &&
                            record_precedes(
                                &queue->data[right],
                                &queue->data[left])) {
                                selected = right;
                        }

                        if (!record_precedes(
                                &queue->data[selected],
                                &candidate)) {
                                break;
                        }

                        queue->data[hole] = queue->data[selected];
                        hole = selected;
                }

                queue->data[hole] = candidate;
        }

        queue->size = new_size;
        if (new_size == 0U) {
                queue->next_sequence = 0U;
        }

        return result;
}

```

This example safely assumes the tree is not empty. The right child is strictly only checked when `right < new_size` guarantees it exists. The real `extract-min` function immediately rejects an empty tree and carefully adds all child and candidate comparisons to the total count.

### Using the Priority Queue

```c
#include "alert_priority_queue.h"

AlertPriorityQueue queue = {0};
AlertRecord next = {0};
bool is_heap = false;

if (alert_priority_queue_init(&queue) ==
    ALERT_PRIORITY_QUEUE_OK) {
        alert_priority_queue_insert(&queue, 71, 3U);
        alert_priority_queue_insert(&queue, 88, 1U);
        alert_priority_queue_insert(&queue, 42, 2U);
        alert_priority_queue_insert(&queue, 17, 1U);

        alert_priority_queue_peek_min(&queue, &next);
        /* next.alert_id is 88. */

        alert_priority_queue_extract_min(&queue, &next);
        /* next.alert_id is 88 and the next champion is 17. */

        alert_priority_queue_is_min_heap(&queue, &is_heap);
        /* After a normal action, is_heap perfectly proves the golden rule is true. */

        alert_priority_queue_destroy(&queue);
}

```

`bool` is a true/false type provided by `<stdbool.h>`, which is conveniently included in the public header. Notice that the public function names here are exactly the same as in Chapter 10, but Chapter 11's internal code smartly, automatically maintains the array using our fast tree rules!