# Chapter 10. Choosing by Priority and Arrival Order

## Starting Question

> "To process urgent alerts first, but for alerts with the same urgency, take out the one that came first, what rule do we need?"

**Expected Answer:** If students say we must compare the priority first and then the arrival order if they are the same, write it down. Make it clear that picking the smaller number first is just our rule for this chapter.

## Why We Need This

A normal queue only takes out the first arrived value first. It cannot put urgent alerts at the front. If we only compare priority, the processing order for things with the same priority is not decided.

We need a behavioral rule (a promise) for how to put in, look at, and take out values. When comparing two values, we look at priority first, and only if they are the same do we look at the successful insertion order (arrival order). Even if the storage array is not sorted, we can still follow this rule.

## Board Walkthrough

Use the unsorted array provided by the teacher exactly as it is. `p` is priority and `s` is arrival order.

```text
71/p3/s0, 88/p1/s1, 42/p2/s2, 17/p1/s3, 
26/p4/s4, 9/p2/s5, 63/p1/s6

```

Scan the array from the left and underline the top candidate.

* Prediction 1: Among the seven alerts, which one will be announced first?
* Prediction 2: After taking out 88 and moving 63 to its empty spot, what is the next alert?
* Prediction 3: When taking out all seven values, how many new comparisons will we make in total?

| State Looked At | Top Candidate |
| --- | --- |
| Start | `71/p3/s0` |
| After comparing with 88 | `88/p1/s1` |
| After comparing with 42, 17, 26, 9, 63 | `88/p1/s1` |

The first check makes 6 comparisons. After taking out 88, the physical array is `71, 63, 42, 17, 26, 9`. Even so, the next alert is 17. This is because their priorities are the same, but arrival order 3 is smaller than 6.

After resetting the comparison count to 0, taking out seven times adds 21 new comparisons. If we add the 6 comparisons from the very first check, it makes 27 times in total.

```text
6 + 5 + 4 + 3 + 2 + 1 + 0 = 21

```

Students do not write the code for this storage method. They just read the provided code and check the public rules and the number of comparisons.

## Common First Thoughts

* "Smaller priority numbers are always more urgent." But the direction of the numbers is just a rule decided by the program.
* "If priorities are the same, we can just pick the value on the left side of the array." But we compare the arrival order, not the physical position in the array.
* "Since the array is not sorted, the take-out rule is broken." But when we take something out, we scan the whole array to pick the value that is first according to the rule.
* "Taking out one item only takes one comparison." But if there are `n` records, we must compare the current candidate with the `n - 1` other items.

## Neutral Questions

* When deciding the order to process two alerts, which values do we look at and in what order?
* What decisions are made based on the array positions and arrival orders of 63 and 17?
* If the number of records changes, how does the number of comparisons for one check change?
* Depending on whether there are more putting-in or taking-out tasks, what should we count?

## Vocabulary Rules

**Words we can use:** Array-based list, size and capacity, array expansion, keeping the state after a failure, arrival order of a queue, and average cost divided over a long task.

**Names we will introduce in this chapter:** Priority queue behavioral rule, priority, arrival order, stable tie-breaking, comparison rule, minimum priority queue, `insert`, `peek-min`, `extract-min`, and unsorted array baseline.

**Words we won't use yet:** We save the internal shape and rearranging steps of storage methods different from the provided array for the next chapter. We also won't explain applying this structure to finding paths in later chapters yet.

## Final Check

> "Can you explain the processing order of 88, 17, and 63, and also why there are 21 comparisons when taking out all seven values?"

**Minimum Expected Answer:** Students should mention that priority 1 comes first, tie-breakers follow arrival orders 1, 3, and 6, and that we compare `6+5+4+3+2+1+0` times depending on the number of remaining records.