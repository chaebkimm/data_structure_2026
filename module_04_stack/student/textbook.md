# Chapter 4. Taking Out the Last Value First

## Thinking Logically

### Why do we need a special order?

The expression `1 + 2 * 3` cannot be evaluated strictly from left to right. Multiplication must be completed before addition. This rule is called **operator precedence**. The evaluator must delay `1 +` until `2 * 3` is complete. It needs storage that returns the most recently delayed item first.

### How do we find what to calculate next?

If the evaluator delays `+` and then `*`, it must finish `*` before returning to `+`. The needed operator is at the top, so the evaluator does not search through older items. Reading the top without removing it reveals the next waiting step.

### The Top-Only Method

When items enter and leave through one end, the last item added is the first item removed. A stack of plates follows this rule because both actions happen at the top.

### How do we remove data?

When the most recent saved item is no longer needed, you logically remove it by decreasing the count. Its old bits may remain in the array, but they are no longer part of the Stack. The item below it becomes the new top.

### How do we add data?

To delay a number or operator, place it at the top. No existing item moves. Increase the item count by one.

### How does the computer use this for paused functions?

In the previous chapter on trees, you learned about recursion. When a function pauses to call a new function, the runtime commonly uses the same Last-In, First-Out behavior. It saves a **call frame** containing what the active call needs in order to resume. The integer function ID used later in this chapter models that order; it is not a real call frame or the runtime's hidden storage.

### What should we check when adding or removing?

When adding data, check that the Stack has not reached its fixed capacity. When looking at or removing data, check that the Stack contains an item.

In this module, the caller creates the fixed array and keeps its `size` and `capacity`. The Stack operations borrow that array without creating, resizing, or releasing it. This arrangement is called **caller-owned storage**.

### What happens if the space is full?

If a recursive function forgets its stopping rule, it can exhaust the runtime space used for calls. That event is separate from this chapter's checked fixed-array Stack. A push requested when `size == capacity` is rejected before any array cell changes. A peek or pop requested when `size == 0` reports underflow and leaves the checked output unchanged.

### How do two Stacks preserve precedence?

The checked **expression evaluator** uses one Stack for numbers and one for operators. Before pushing a new operator, it applies every waiting operator with equal or greater precedence. Equal-precedence operators therefore run from left to right.

The right end of each list below is the top:

- Start: numbers `[]`; operators `[]`.
- Read `1`: numbers `[1]`; operators `[]`.
- Read `+`: numbers `[1]`; operators `[+]`.
- Read `2`: numbers `[1, 2]`; operators `[+]`.
- Read `*`: numbers `[1, 2]`; operators `[+, *]`. The waiting `+` has lower precedence.
- Read `3`: numbers `[1, 2, 3]`; operators `[+, *]`.
- Reach the end: Apply `*` first, producing numbers `[1, 6]`. Then apply `+`, producing `[7]`.

The evaluator accepts only a nonempty sequence that starts with one digit, alternates between an operator and one digit, and ends with a digit. The only operators are `+` and `*`. It rejects spaces, parentheses, unsupported characters, missing operands, an internal push when its Stack is full, or a mathematical result outside the C `int` range. A result outside that range is called **integer overflow**. Every rejection leaves the caller's previous result unchanged. The two internal Stacks have ten positions each. This limit applies to the number of items currently in each Stack, not directly to expression length.

## Calculating Efficiency

### Memory Efficiency

The Stack reserves its full fixed capacity even when only some positions are active. Positions at or above `size` are inactive, even if they still contain old bits. The array uses `O(capacity)` storage.

### Efficiency of Adding Data

If space remains, pushing writes one array cell and increases size once. No existing item moves. A checked fixed-capacity push therefore takes `O(1)` time.

### Efficiency of Deleting Data

After its checks, pop reads one array cell and decreases size once. It does not shift the older data, so it takes `O(1)` time.

### Efficiency of Reading the Top Data

Peek reads one position, `stack[size - 1]`, after checking the metadata and empty state. It takes `O(1)` time.

### Efficiency of Evaluating an Expression

For an expression containing `n` characters, the evaluator scans each character once and applies each operator once. It takes `O(n)` time. Its two fixed ten-position arrays use `O(1)` extra storage.

## Glossary

### Stack

A data structure where you put in and take out items from only one end.

### Last-In, First-Out (LIFO)

The order where the last item put in is the first one taken out.

### Top

The single active end of the stack where all reading, adding, and removing happens.

### Push

The action of adding a new item directly onto the top of the stack.

### Pop

The action of reporting and logically removing the top item from the Stack.

### Peek

The action of looking at the top item's value without removing it.

### Call Frame

A runtime record containing what one active function call needs in order to resume. The integer ID in this chapter models call order; it is not a real call frame.

### Capacity

The number of usable array positions supplied by the caller.

### Caller-Owned Storage

A fixed array created and controlled by the caller. The Stack operations borrow it without resizing or releasing it.

### Full-Stack Rejection

A rejected push when `size == capacity`. The Stack remains unchanged. Runtime call-space exhaustion is a different event.

### Underflow

The rejected request to peek or pop an empty Stack. The Stack and checked output remain unchanged.

### Operator Precedence

The rule that determines which operator must be applied first.

### Expression Evaluator

A procedure that calculates an expression accepted by its stated rules.

### Integer Overflow

A mathematical result outside the range of C type `int`. The checked evaluator rejects it before committing an output.

## Invariant

### What is the invariant (the golden rule) in this data structure?

You must interact with the active Stack through its top. Push adds at index `size`. Peek and pop use index `size - 1`. Valid metadata also satisfies `0 <= size <= capacity`.

### What is the benefit from the invariant?

It preserves Last-In, First-Out (LIFO) order. The newest active item is always the next item inspected or removed. With the fixed-array representation, push, peek, and pop each use a constant number of checks, reads, writes, or size updates.

### How is the invariant maintained during insertion?

When you push a new item, place it at index `size`, then increase size. If the Stack is full or its metadata is invalid, reject the request before writing.

### How is the invariant maintained during deletion?

When you remove data, you are only allowed to pop the single item currently sitting at the very top. You never pull an item out from the middle. By taking only the top item, the piece of data immediately below it is safely exposed and naturally becomes the new top.

### What happens if the invariant is broken?

If code removes an older item while newer items remain, the next pop no longer reports the newest saved item. An expression evaluator can then apply operators in the wrong order and compute the wrong value.

If the metadata rule breaks, `stack[size - 1]` may name an inactive slot or a position outside the caller's array. The operations prevent these outcomes by checking metadata, full state, and empty state before accessing an element.

## Coding Plan

### Making an Empty Stack

- Set Capacity: Note the fixed maximum number of IDs the prepared array can hold.
- Initialize Count: Set the total count of stored items (the current size) to 0, meaning the container is completely empty.

### Pushing a Value (Function Call)

- Check Space: Make sure the current size is strictly less than the total capacity.
- Save Data: Put the new function ID into the underlying array exactly at the spot matching the current size.
- Increase Count: Increase the total size count by 1 so the new item officially becomes the new top.
- Fail: If the Stack is full or metadata is invalid, return the original size and leave every array cell unchanged.

### Reading the Top Value (Peek)

- Check Empty: Make sure the size is greater than 0 so there is actually a paused function to look at.
- Read Data: Look at the function ID stored at exactly one spot below the current size (size - 1). Do not change the size count.
- Fail: If the Stack is empty or metadata is invalid, reject the read and leave the checked output unchanged.

### Removing the Top Value (Pop / Return)

- Check Empty: Make sure the size is greater than 0.
- Read Data: Copy the function ID at `size - 1` to the checked output.
- Decrease Count: Decrease the total size count by 1. You do not need to physically erase the old data in the array; decreasing the count safely hides it and automatically makes the item below it the new top.
- Fail: If the Stack is empty or metadata is invalid, return the original size and leave the checked output unchanged.

### Evaluating the Expression

- Read Left to Right: Expect one digit, then one operator, repeating until the end.
- Save Work: Push digits onto the number Stack and operators onto the operator Stack.
- Respect Precedence: Before pushing an operator, apply every waiting operator with equal or greater precedence.
- Finish: Apply the remaining operators from the top down.
- Commit or Reject: Write the result only after the input rules, Stack operations, and checked arithmetic all succeed. Otherwise, leave the caller's output unchanged.

## New C Syntax Explained

### Strings and the Null Terminator (`\0`)

In C, text such as `"1+2*3"` is a string literal. It creates an array of characters whose last character is `'\0'`, the null terminator. In the evaluator's loop, `expression[index] != '\0'` means to keep reading until that terminator is reached.

### Single Quotes vs. Double Quotes (`'0'` vs `"1+2*3"`)

In C, single quotes and double quotes mean very different things.

- Double quotes (`""`) are used for strings (an array of characters ending with a hidden `'\0'`).

- Single-quoted forms such as `'0'` and `'+'` represent one individual character. When the evaluator writes `char current = expression[index];`, it is pulling out one character, so it checks that value with forms such as `current == '+'`.

### Character Math (`current - '0'`)

C represents each character with an integer value. The C language guarantees that the digit characters from `'0'` through `'9'` have consecutive values.

After checking that `current` is a digit, subtracting `'0'` converts it to the matching integer. For example, `current - '0'` produces `3` when `current` is `'3'`. This works without assuming a particular character encoding.

## C Code

The next blocks show the array actions inside the checked Stack operations. In the lab, `int_stack_push`, `int_stack_peek`, and `int_stack_pop` package these actions as functions.

### Making an Empty Stack

```c
/* Set Capacity */
int stack[10];
int capacity = 10;

/* Initialize Count */
int size = 0;
```

### Pushing a Value (Function Call)

```c
/* The ID of the new function being called */
int new_function = 100;

/* Check Valid Metadata and Space */
if (size >= 0 && size < capacity) {

        /* Save Data */
        stack[size] = new_function;

        /* Increase Count */
        size = size + 1;
}
```

### Reading the Top Value (Peek)

```c
int top_function = -1; /* Existing output stays unchanged on failure */

/* Check Valid Metadata and Empty State */
if (size > 0 && size <= capacity) {

        /* Read Data */
        top_function = stack[size - 1];
}
```

### Removing the Top Value (Pop / Return)

```c
int returned_function = -1; /* Existing output stays unchanged on failure */

/* Check Valid Metadata and Empty State */
if (size > 0 && size <= capacity) {

        /* Read Data */
        returned_function = stack[size - 1];

        /* Decrease Count */
        size = size - 1;
}
```

### Calling the Expression Evaluator

The header `expression_evaluator.h` declares the evaluator function. A caller can use it without seeing the evaluator's internal two-Stack implementation.

```c
int result = -1;
int success = expression_evaluate("1+2*3", &result);

/* success is 1, and result is 7. */
```
