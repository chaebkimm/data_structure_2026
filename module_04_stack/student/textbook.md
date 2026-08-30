# Chapter 4. Taking Out the Last Value First

## Thinking Logically

### Why do we need a special order?

In the chapter on trees, you learned about recursion. When a function pauses to call a new function, the computer needs to remember exactly where to resume later. Because the most recently called function must always finish first, we must store these "return addresses" so that the last one saved is the very first one we take back out.

### The Top-Only Method

If you put items in and take them out from only one single end, the very last item you put in will always be the very first one to come out. Think of it like a tall container for plates—you always place a new plate on the very top, and when you need a plate, you always take the one sitting right on top.

### How do we find where to return?

Since the program only ever cares about the most recently paused function, the computer doesn't need to search through all the saved data one by one. It simply looks directly at the item sitting on the very top of the container to see what it is, without actually removing it.

### How do we remove data?

When a function finishes running, its saved information is no longer needed. You remove the top item completely from the container. The item directly underneath it instantly becomes the new top, telling the computer exactly where to return next. After deleting, the final number of items goes down by one.

### How do we add data?

Every time a new function is called, you simply add its return information (a new "frame") directly onto the very top of your existing pile. No other existing data needs to be shifted, moved, or changed. After adding it, the final number of items goes up by one.

### What should we check when adding or removing?

When adding data, check that the container hasn't reached its strict maximum depth limit. When looking at or removing data, check that the container actually has something in it. An empty container means the program has finished running completely.

### What happens if the space is full?

If a recursive function forgets its stopping rule, it will keep calling itself and adding new items until the container is completely full. If it tries to add one more item when the space is full, it triggers a fatal error—an Overflow—and stops the program immediately. Similarly, trying to remove an item when the container is already empty triggers an Underflow error.

## Calculating Efficiency

### Memory Efficiency

The stack reserves its full capacity even when only some slots are in use. The remaining slots simply sit empty, waiting outside the current stack limits.

### Efficiency of Adding Data

If you have leftover space, adding a new function call directly to the very top is super fast because no other existing data needs to move or shift out of the way. Because a stack strictly forbids adding items into the middle or the bottom, the amount of work is always instantly finished. 

### Efficiency of Deleting Data

Removing a function call when it finishes is instantly finished. Unlike an array list where deleting from the front forces you to pull everything else forward, a stack only ever removes the most recently added item from the very top. There is absolutely no need to shift or reorganize the older data underneath it.

### Efficiency of Reading the Top Data

In a stack, you are strictly restricted to finding one specific piece of data: the item sitting on the very top. Because the computer keeps a running count of exactly how many items are currently stored, it can instantly calculate the top item's exact position in memory and jump straight to it. 

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

The action of completely removing the top item from the stack.

### Peek

The action of looking at the top item's value without removing it.

### Call Frame

The package of data saved on the stack that remembers a paused function's exact return address and local variables.

### Capacity

The fixed maximum number of items the stack's underlying memory can hold.

### Stack Overflow

A fatal error that happens when a program tries to push a new item onto the stack, but the fixed memory capacity is already completely full.

### Underflow

The error state when you try to read or remove a value from an empty stack.

## Invariant

### What is the invariant (the golden rule) in this data structure?

You must only ever interact with the very top of the stack. All adding (pushing), removing (popping), and reading (peeking) must happen exclusively at this single active end. The older data trapped underneath the top is completely off-limits and cannot be touched until the items above it are removed.

### What is the benefit from the invariant?

It guarantees perfect Last-In, First-Out (LIFO) order. By restricting all access to just the top, the stack flawlessly tracks nested sequences—like paused recursive functions—ensuring the computer always returns to the most recently paused task first. It also guarantees that every single action is incredibly fast, because no time is ever wasted searching through the data or shifting items around.

### How is the invariant maintained during insertion?

When you push a new item, you simply place it in the very first empty spot directly above the current data. This new item instantly becomes the new top. You are strictly forbidden from sneaking the new item into the middle or bottom of the existing pile.

### How the invariant is kept during deletion?

When you remove data, you are only allowed to pop the single item currently sitting at the very top. You never pull an item out from the middle. By taking only the top item, the piece of data immediately below it is safely exposed and naturally becomes the new top.

### What happens if the invariant is broken?

Imagine you could reach into the middle of the stack to change or remove an older paused function without popping the newer ones on top of it first.

If you allow this to happen, the purpose of the stack breaks down in two major ways:

- The Order is Destroyed: The stack's entire job is to remember the exact reverse order of events. If you pull an older function out from the middle, you break the chain of return addresses. When the newer functions on top finally finish running, the computer will look down for its next step, find a missing link, and crash.

- Loss of Instant Speed: If we allowed adding or removing items from the middle, we would suddenly have to push and pull the remaining data to close the empty gaps, just like an Array List. This extra work destroys the elegant, instant speed of the stack.

By strictly enforcing the top-only rule—even when it feels restricting—we guarantee that our data's timeline is always perfectly ordered, safe, and instantly accessible.

## Coding Plan

### Making an Empty Stack

- Set Capacity: Note the fixed maximum number of function calls the stack's memory can hold.
- Initialize Count: Set the total count of stored items (the current size) to 0, meaning the container is completely empty.

### Pushing a Value (Function Call)

- Check Space: Make sure the current size is strictly less than the total capacity.
- Save Data: Put the new function ID into the underlying array exactly at the spot matching the current size.
- Increase Count: Increase the total size count by 1 so the new item officially becomes the new top.
- Fail: If the stack is already full, reject the addition and stop the program to prevent a Stack Overflow.

### Reading the Top Value (Peek)

- Check Empty: Make sure the size is greater than 0 so there is actually a paused function to look at.
- Read Data: Look at the function ID stored at exactly one spot below the current size (size - 1). Do not change the size count.
- Fail: If the stack is empty, reject the read because there is nothing to check.

### Removing the Top Value (Pop / Return)

- Check Empty: Make sure the size is greater than 0.
- Decrease Count: Decrease the total size count by 1. You do not need to physically erase the old data in the array; decreasing the count safely hides it and automatically makes the item below it the new top.
- Fail: If the stack is already empty, reject the removal to prevent an Underflow error.

## C Code

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

/* Check Space */
if (size < capacity) {
        
        /* Save Data */
        stack[size] = new_function;

        /* Increase Count */
        size = size + 1;
}
```

### Reading the Top Value (Peek)

```c
/* Check Empty */
if (size > 0) {
        
        /* Read Data */
        int top_function = stack[size - 1];
}
```

### Removing the Top Value (Pop / Return)

```c
/* Check Empty */
if (size > 0) {
        
        /* Decrease Count */
        size = size - 1;
}
```

## Coding Exercise: Evaluating an Expression

### Handling Operator Precedence

If you calculate `1 + 2 * 3` strictly left to right, you get `9`. However, multiplication has a higher priority than addition. The computer must put the `1 +` on hold, safely remembering it until `2 * 3` is calculated.

To process equations properly, the computer uses two stacks: one for numbers and one for operators. It assigns a priority level to each symbol (e.g., `*` is high, `+` is low) and follows one golden rule: Before pushing a new operator, calculate any waiting operators that have equal or higher priority.

### The C Code

To make this easy to read, we use a loop to process a simple string of characters (`"1+2*3"`). We also use a small helper function to check the priority of the math symbols.

```c
/* Helper function to check priority level */
int get_priority(char operator) {
        if (operator == '*') return 2;
        if (operator == '+') return 1;
        return 0;
}
```

Here is the main logic using the two stacks side-by-side:

```c
/* Create the two stacks */
int num_stack[10];
int num_size = 0;

char op_stack[10];
int op_size = 0;

/* The equation to solve (no spaces for simplicity) */
char equation[] = "1+2*3";

/* Read the equation left to right */
for (int i = 0; equation[i] != '\0'; i = i + 1) {
        char current = equation[i];

        /* If it is a number (between '0' and '9') */
        if (current >= '0' && current <= '9') {
                /* Convert character to integer and push to Number Stack */
                num_stack[num_size] = current - '0';
                num_size = num_size + 1;
        } 
        /* If it is an operator (*, +) */
        else {
                /* While the top operator is STRONGER or EQUAL to the current one */
                while (op_size > 0 && get_priority(op_stack[op_size - 1]) >= get_priority(current)) {
                        
                        /* Pop the operator */
                        op_size = op_size - 1;
                        char op = op_stack[op_size];

                        /* Pop the right and left numbers */
                        num_size = num_size - 1;
                        int right = num_stack[num_size];

                        num_size = num_size - 1;
                        int left = num_stack[num_size];

                        /* Calculate and push result back */
                        if (op == '*') num_stack[num_size] = left * right;
                        if (op == '+') num_stack[num_size] = left + right;
                        num_size = num_size + 1;
                }                
                /* Now it is safe to push the current operator */
                op_stack[op_size] = current;
                op_size = op_size + 1;
        }
}

/* End of Equation: Apply any remaining operators left in the stack */
while (op_size > 0) {
        op_size = op_size - 1;
        char op = op_stack[op_size];

        num_size = num_size - 1;
        int right = num_stack[num_size];

        num_size = num_size - 1;
        int left = num_stack[num_size];

        if (op == '*') num_stack[num_size] = left * right;
        if (op == '+') num_stack[num_size] = left + right;
        num_size = num_size + 1;
}

/* The final answer is sitting at the bottom of the number stack */
int final_answer = num_stack[0]; /* 7 */
```
