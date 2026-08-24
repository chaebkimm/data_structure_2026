# Chapter 4. Taking Out the Last Value First

## Thinking Logically

### How do we remember the most recently opened symbol?

Read the following text from left to right.

```text
A(B[C]{D})
```

When you read `]`, you must pair it with the most recently opened `[`. You should not pair it with the earlier opened `(`. We need a special storage space to remember the unclosed opening symbols in the exact order we found them.

### Which side should we use to put in and take out values?

If you put items in and take them out from only one single end, the very last item you put in will always be the very first one to come out. Think of it like a tall container for plates—you always place a new plate on the very top, and when you need a plate, you take the one sitting right on top.

We have three main actions we can do at this top opening:

* **Add** a new item directly onto the top.
* **Look** at the top item to see what it is, without removing it.
* **Remove** the top item completely.

An empty container has absolutely nothing on top. So, if you try to look at or remove an item from an empty container, it should stop and trigger an error without giving you any value.

### In what order do we check grouping symbols?

Characters that open and close groups, like `(`, `[`, and `{`, act like matching pairs. As we read the text, we follow these simple rules:

1. Put every opening symbol into the container.
2. When you meet a closing symbol, look at the symbol currently sitting on top of the container. Check if they are a perfect match.
3. If they match perfectly, remove that opening symbol from the container.
4. When you finish reading the entire text, the container must be completely empty (meaning every pair was perfectly matched and closed).

Normal letters do not affect this matching process at all, so we completely ignore them.

| Read Character | Action | Inside the Container (Bottom to Top) |
| --- | --- | --- |
| `(` | Add | `(` |
| `[` | Add | `(`, `[` |
| `]` | Check and Remove | `(` |
| `{` | Add | `(`, `{` |
| `}` | Check and Remove | `(` |
| `)` | Check and Remove | Empty |

### Where do wrong inputs show up?

If you read a closing symbol but the container is completely empty, it means you have a closing symbol that has no opening partner. If the closing symbol is a different shape than the one on top of the container, it is a mismatched pair. If you reach the very end of the text but there are still symbols sitting inside, it means some groups were never closed.

We set a strict limit on how deeply these groups can be placed inside one another (how many can be open at the exact same time). If a new opening symbol breaks this limit, we stop checking right at that spot. An empty text, or a text with only normal letters, is considered perfectly fine, even if our limit is set to zero.

### Where do we store the container's values?

We line the characters up in a continuous row in the computer's memory. If the row gets completely filled up, we get a new, larger row and move the characters over. To manage this, our container needs to remember four things: where the row starts, exactly how many characters are currently in it, the total size of the current row, and the absolute maximum size the row is legally allowed to grow to.

```c
typedef struct {
    char *data;
    size_t size;
    size_t capacity;
    size_t limit;
} CharStack;
```

When there is at least one character in the row, the top character is always the very last one currently sitting in the row (`data[size - 1]`). The current size must never exceed the current total capacity, and the capacity must never exceed the strict limit. In our code, the maximum limit is 1024.

When we first need space, we make a row that fits 4 characters. Every time it gets full, we double its size. However, this new doubled size can never go over the maximum limit. If the computer fails to give us a bigger row, we safely keep the old row, its old characters, and its old sizes exactly as they were.

This memory row belongs to one container and one container only. You should only run the setup process on a brand-new container that hasn't been used yet, or one that has been officially cleaned up and destroyed. If you blindly copy a container that is currently in use, or try to run the setup process on it again, you will scramble the memory.

## Calculating Efficiency

### How long does it take to look at or remove the top value?

Looking at or removing the top item only ever deals with one single spot—the very end of the row (`data[size - 1]`). Because the computer jumps straight to it, both actions take an instant amount of time, written as `O(1)`.

### How long does it take to add a value?

If there is empty space left in the row, we just drop the character into the next empty spot, taking an instant `O(1)`. If the row is full and we have to expand it, we must carefully move all `n` existing characters to the new row, which takes time proportional to the amount of items, `O(n)`. However, because we double the size every time, this moving process happens very rarely. When you average it out over many additions, the cost is basically an instant `O(1)` per item.

### How long does it take to check the symbols?

Because we check each character of a text of length `m` exactly once from left to right, it takes an amount of time proportional to the text length, `O(m)`. If there are `d` symbols open at the exact same time, we need `O(d)` memory space. We know `d` will never grow larger than our strict depth limit.

## Glossary

### Stack

A data structure where you put in and take out values from only one end.

### Last-In, First-Out (LIFO)

The order where the last value put in is the first one taken out.

### Top

The end of the stack where the next value is put in or taken out.

### Push

Putting a new value on the top of the stack.

### Peek

Reading the top value without removing it.

### Pop

Reading and removing the top value completely.

### Underflow

The error state when you try to read or remove a value from an empty stack.

### Delimiter

A character that shows the start or end of a group, like `(` and `)`.

### Nesting Depth

The number of opening symbols that have not been closed yet.

### Depth Limit

The maximum number of delimiters that can be open at the same time.

## Coding Plan

### Making an Empty Stack

* **Check:** Make sure the stack's memory address exists and the limit is 1024 or less.
* **Setup:** Set the data row to empty (`NULL`), set the current size and total capacity to 0, and record the requested limit.
* **Fail:** If the request breaks the rules, do not change the structure at all.

### Pushing a Value

* **Check:** Make sure the fields are correct and the current size is strictly smaller than the limit.
* **Expand:** If there is no empty space left, grab space for 4 characters. If it gets full again, double it, but never go past the limit.
* **Write:** Put the new character into the next empty spot (`data[size]`) and increase the size by 1.
* **Fail:** If it hits the limit or the computer runs out of memory, leave the stack exactly as it was.

### Reading and Popping the Top Value

* **Check:** Make sure the stack and the output addresses are correct, and the size is not 0 (not empty).
* **Read:** Copy the character at `data[size - 1]` into the output variable.
* **Remove:** If taking the item completely (popping), decrease the size count by 1. Do not shrink the total capacity of the row.
* **Fail:** If the stack is empty, do not change the output variable or the stack.

### Checking Delimiters

* **Open:** Check the depth limit before putting a new opening symbol into the stack.
* **Close:** Check if the stack is completely empty. If not, check if the symbol matches the one on top.
* **Finish:** It is a perfect success if the stack is completely empty at the end. If symbols are still left inside, record the total length of the string as the location of the error.
* **Clean up:** Give the temporary stack's memory back to the computer, regardless of whether the check succeeded or failed halfway through.

### Destroying the Stack

* **Free:** Give the array memory owned by the stack back to the computer.
* **Reset:** Turn all the numbers back to 0 and set the data address back to empty (`NULL`).

## C Code

### How do we use the stack?

```c
CharStack stack;
char value;

if (char_stack_init(&stack, 6U) != STACK_OK) {
    return 1;
}

if (char_stack_push(&stack, '(') != STACK_OK ||
    char_stack_push(&stack, '[') != STACK_OK) {
    char_stack_destroy(&stack);
    return 1;
}

if (char_stack_peek(&stack, &value) == STACK_OK) {
    printf("top: %c\n", value);   /* [ */
}

if (char_stack_pop(&stack, &value) != STACK_OK) {
    char_stack_destroy(&stack);
    return 1;
}
char_stack_destroy(&stack);
```

### How do we check matches?

```c
static bool delimiters_match(char open, char close)
{
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}
```

When you meet a closing symbol, always check the top value first, and only remove it if they match perfectly. If you remove it *before* checking, you might permanently lose an opening symbol you actually needed, even if you just found a wrong match.

### How do we get the location of the check result?

```c
size_t error_index = 0U;
DelimiterStatus status = delimiter_validate(
    "A(B[C]{D})",
    2U,
    &error_index
);

if (status == DELIMITER_OK) {
    printf("valid\n");            /* error_index == SIZE_MAX */
} else {
    printf("error at %zu\n", error_index);
}
```

If there is a closing symbol with no opening partner or a mismatched pair, the code leaves behind the exact position of that bad closing symbol. If there are unclosed opening symbols left over at the end, it leaves behind the total length of the string. If a symbol tries to go over the maximum depth limit, it leaves behind the exact position of that opening symbol.