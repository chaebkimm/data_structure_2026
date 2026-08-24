# Chapter 13. Finding Large Numbers in a Small Table

## Starting Question

> "If the possible numbers are very large but we only have a few actual records, how can we find the number we want in a small array?"

**Expected Answer:** Students should say that we must calculate a starting slot using the number, and if the spot is already taken, we must look at the next slots using a set rule until we reach the end of the search.

## Why We Need This

If we use the number we want to find directly as the array position, we might waste almost all the slots. We call this number a "key." When we gather them in a small array, different keys might start at the exact same slot. We call this a "collision." We need rules for calculating the starting slot, moving to the next slot after a collision, and finding things after a deletion all together.

In week 11, we will directly handle checking slots one by one, finding, putting in, changing existing values, and deleting. For "rebuilding" (rehashing), we only complete the decision points and final changes within the provided framework. We do not build the entire rebuild process from scratch.

## Board Walkthrough

The basic slot we look at first is called `home`. The capacity is 8, and `home = key % 8` (the remainder when dividing the key by 8). The structure that calculates the basic slot using a key and stores it in an array is called a "hash table." The rule of looking at the next slots one by one after a collision is called "linear probing."

```text
10: Look at 2 and store it in 2.
18: Look at 2, 3 and store it in 3.
26: Look at 2, 3, 4 and store it in 4.

Position   0  1  2   3   4   5  6  7
Key              10  18  26

```

After deleting 18, we leave slot 3 as a "deleted mark" (tombstone).

| Position | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| State | Empty | Empty | In Use | Deleted Mark | In Use | Empty | Empty | Empty |
| Key |  |  | 10 |  | 26 |  |  |  |

`put(key, value)` is a request to put in a new key or change the value of an existing key. Let's follow two requests starting from this exact same state.

```text
put(26, 999): Look at 2, 3, 4 and change the value in 4.
put(34, 340): Look at 2, 3, 4, 5 and then reuse the remembered slot 3.

```

Ask these questions before showing each result:

* After deleting 18, which slot do we have to check up to when finding 26?
* If `put(26, 999)` stops at the deleted mark in slot 3, what check do we miss?
* If the capacity changes from 8 to 16, how do we calculate the starting slot for key 18?

## Common First Thoughts

* "We should use the key value directly as the array position."
* "We can mark a deleted slot exactly the same as an empty slot that was never used."
* "When inserting a new key, we should write the record down immediately when we meet the first deleted mark."
* "The expected `O(1)` fast time is guaranteed for all keys and in all states."

## Neutral Questions

* In this request, what state allows us to stop looking (probing)?
* How did we separately record the position of the first deleted mark we saw and the position of the exact same key?
* What request results must remain exactly the same before and after rebuilding the table?

## Vocabulary Rules

**Words we can use:** Array position, remainder calculation (modulo), empty slot, keeping the state after a failure, and capacity.

**Names we will introduce in this chapter:** Key and value, map, hash function, hash table, collision, linear probing, deleted mark, rebuilding to reduce deleted marks, rehashing, and expected cost.

**Words we won't use yet:** Names of other collision handling methods, the full implementation of rebuilding from scratch, or attack defense designs for real-world services.

## Final Check

> "Why must we leave slot 3 as a 'deleted mark' after deleting 18, and why must we keep looking even when putting in a new key?"

**Minimum Expected Answer:** Students should mention both the flow of finding 26 (which is stored further down) and the flow of checking to make sure we don't put the exact same key in twice.