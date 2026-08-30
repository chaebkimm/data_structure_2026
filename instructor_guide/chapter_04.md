# Chapter 4. Take Out the Last Added Value First

## Starting Question

> "When we read a closing symbol, which opening symbol should we pair it with?"

**Expected Answer:** Students should say that among the opening symbols that are not yet closed, we must check the most recent one first.

## Why We Need This

When opening symbols overlap, a single variable cannot remember all the remaining symbols. We must close the most recently opened group before we close the groups that were opened earlier. We need a rule to take out the last added value first. Here, we introduce the name "stack."

## Board Walkthrough

Read `A(B[C]{D})` from left to right. Write the stack from bottom to top.

| Read Character | Action | Stack State |
| --- | --- | --- |
| Start | None | Empty |
| `A` | None | Empty |
| `(` | `push` | `(` |
| `B` | None | `(` |
| `[` | `push` | `(`, `[` |
| `C` | None | `(`, `[` |
| `]` | `pop` after checking pair | `(` |
| `{` | `push` | `(`, `{` |
| `D` | None | `(`, `{` |
| `}` | `pop` after checking pair | `(` |
| `)` | `pop` after checking pair | Empty |

When `size = 2`, the top is not the very last slot of the entire array, but exactly `data[size - 1]`.

Let's predict:

* When both `(` and `[` are in the stack, what is the next opening symbol to check?
* If we read the `]` in `A(B]`, what happens to the stack and the final result?
* If the input is finished but a `(` is still left in the stack, what do we need to check?

## Common First Thoughts

* "The top is always the very last slot of the allocated array."
* "`peek` also reads and removes the top value."
* "A closing symbol just needs to be paired with the same type from any of the remaining opening symbols."
* "If `limit == 0`, we cannot even check an empty string."

## Neutral Questions

* What value did you use to calculate the top position just now?
* Can you tell me the `size` before and after this action?
* When we read up to the character where the error happened, what is left in the stack?

## Vocabulary Rules

**Words we can use:** Fixed-capacity array-based list, size, capacity, pointers, keeping the state after a rejected operation, and amount of work.

**Names we will introduce in this chapter:** Growable array, checked expansion, doubling, array ownership, delimiter, top, Last-In-First-Out (LIFO), stack, `push`, `peek`, `pop`, underflow, abstract data type, and nesting limit.

**Words we won't use yet:** We will only mention "running function call storage" and "depth-first search" by name. We will not explain how they work or how to build them yet.

## Final Check

> "Can you use the stack state to explain why `]` cannot be paired with `(` in the string `A(B]`?"

**Minimum Expected Answer:** Students should say that the most recently left opening symbol at the top of the stack is `(`, and since it is a different type from the closing symbol `]`, it is not removed and the pairing fails.
