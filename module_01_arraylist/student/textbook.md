# Chapter 1. Keeping data together in one place

## Thinking logically

### Why should we keep data together?

When you want to do the same task for all your data, having it gathered in one place makes it easy to just go through the items one by one.

### The simplest method

If you already know how many pieces of data you want to store, you can just set aside exactly that much memory space for them from the start.

### How do we add data?

Simply add new data to the end of the existing data. To add data in the middle, shift all the data starting from the target spot one space to the right. Then, place your new data into the empty spot.

### Which metadata is useful?

If you track the total count of stored items, you can easily distinguish between the occupied memory and the available unused capacity.

### What should we check when adding data?

First, check that the array has room for one more item by comparing the current item count against the total capacity. Then, check that the insertion position is valid.

### What happens if the space is full?

If the space is full, we cannot add another item.

### How do we find data by its position?

Calculate the exact memory address from its position, then jump straight to that spot.

### How do we find data by its value?

Start at the beginning and check the items one by one until you find a match.

### How do we delete data?

To close the gap, shift all data after the deleted item one space to the left.

## Calculating efficiency

### Memory efficiency

Regardless of the number of stored items, the array reserves its full capacity.

### Efficiency of adding data

The workload increases based on the number of items shifted. On average, this work is proportional to the total number of stored items.

### Efficiency of finding data by its position

The workload is constant because the memory address is calculated from the position.

### Efficiency of finding data by its value

The workload grows with every item checked. On average, the effort is directly proportional to the total number of stored items.

### Efficiency of deleting data

The workload increases based on the number of items shifted. On average, this work is proportional to the total number of stored items.

## Glossary

### Contiguous memory

Memory spaces that are placed right next to each other in a single, unbroken line. Also called contiguous storage or consecutive memory locations.

### Array

A data structure where you set aside a fixed amount of memory space ahead of time to store a certain number of items.

The array used here is also called a fixed-size array or fixed-length array. Its number of slots does not change.

### List

A data structure that stores items in an ordered sequence. Also called a sequence in this context. Ordered means the items have positions; it does not mean their values are sorted.

### Array list

A list that is built using an array under the hood. Also written as array-based list or ArrayList.

This chapter uses a fixed-capacity array list. A version that grows its underlying storage is often called a dynamic array or resizable array.

### Index

The numerical position of a single item in an array or list. Also called a subscript or position. In this chapter, indices start at 0.

### Element

A single item stored inside an array or list. Also called an item or entry.

### Size

The actual number of elements currently being stored inside the data structure. Also called the element count, item count, or list length.

Here, size counts stored elements, not bytes. The length of the underlying array counts all its slots, so it equals capacity instead.

### Capacity

The total number of items the underlying array has space for before it runs out of room. Also called the allocated slot count. For this fixed-capacity list, it is the maximum size.

## Invariant

### What is the invariant (the golden rule) in this data structure?

Pack all items contiguously in memory. No empty gaps.

### What is the benefit from the invariant?

The item is found in one step by calculating the memory address from its index.

### How is the invariant maintained during insertion?

By adding items only at the end or in the middle. When adding in the middle, shift all subsequent items one space to the right to create an empty spot for the new item.

### How the invariant is kept during deletion?

To close the gap left by the removed item, shift all subsequent items one space to the left.

### What happens if the invariant is broken?

If a gap appears in contiguous memory, the indices no longer reflect the data's true order. Consequently, memory addresses cannot be calculated from the index alone, and the system loses track of which locations contain valid data versus empty space.

## Coding plan

### Saving data in an array

- Declare an array: Choose a fixed capacity and set aside that many slots.
- Choose position: Pick the very first number (spot) in memory that doesn't have data saved in it yet.
- Save data: Put your data into that chosen spot.
- Update count: Increase the total count of your stored data by 1.

### Reading or changing data at a specific number

- Check number: Make sure the number you want actually has data saved in it.
- Read value: Read what is saved at that number in the array.
- Change value: Update the value saved at that number.

### Finding data by its value

- Choose target: Set `target` to the value you want to find.
- Compare values: Start at `index = 0` and compare each stored item with `target` while `index < size`.
- Stop at a match: Use `break` when the values match. The first matching position remains in `index`.
- Recognize no match: If the loop finishes without a match, `index` equals `size`.

### Deleting data at a specific number

- Check number: Make sure the number actually has data saved in it.
- Shift data: Move everything that comes right after the deleted spot one space to the left.
- Decrease count: Decrease the total count of your data by 1.

If we shift items starting from the rightmost end, we will overwrite existing data before it can be moved. Starting from the left (immediately after the deleted spot) ensures we safely shift data into the vacated space.

### Adding data to a specific number

- Check number and capacity: Make sure the spot connects to your existing data and fits inside your total memory size.
- Shift data: Starting from the last item down to the spot where you want to add, shift each item one space to the right.
- Save data: put your new data into the newly cleared spot.
- Increase count: increase the total count of your data by 1.

If we shift elements starting from the left (the insertion point), we will overwrite existing data before it can be moved. Starting from the right (the last item) ensures we safely shift data into the vacated space.

## New C syntax explained

### `[capacity]` (creating an array)

To create an array in C, you use square brackets `[]` immediately after the name of your variable. Inside these brackets, you write the exact number of items you want to store. For example, writing `int array[10];` tells the computer to set aside a single, continuous block of memory big enough to hold exactly 10 integers. Because this space is fixed, you must know the maximum capacity you need right from the start.

### `[index]` (accessing data)

Once the array is created, you use the square brackets again to look at or change the data inside it. You simply put the specific number (the index) of the item you want inside the brackets. In C, counting always starts at 0, not 1. Therefore, `array[0]` lets you access the very first item, `array[1]` accesses the second item, and so on.

## C Code

### Saving data in an array

```c
/* Declare fixed storage */
int array[10] = {100, 200, 300, 400, 500, 0, 0, 0, 0, 0};
int array_capacity = 10;

/* Setup item count */
int size = 5;

/* Position to access item */
int pos;
```

### Reading or changing data at a specific number

```c
pos = 1;

/* Check number */
if (pos >= 0 && pos < size) {
        
        /* Read data */
        int data = array[pos];

        /* Change data */
        array[pos] = 500;
}
```

### Finding data by its value


```c
/* Target value to find */
int target = 300;

/* Where the result will be saved */
int index;

for (index = 0; index < size; index = index + 1) {
        if (array[index] == target) {
                break;
        }
}
```

### Deleting data at a specific number

```c
/* Check number */
if (pos >= 0 && pos < size) {

        /* Shift data left */
        for (int i = pos + 1; i < size; i = i + 1) {
                array[i - 1] = array[i];
        }

        /* Decrease count */
        size = size - 1;
}
```

### Adding data to a specific number

```c
/* Check number */
if (pos >= 0 && pos <= size && size < array_capacity) {

        /* Shift data right */
        for (int i = size - 1; i >= pos; i = i - 1) {
                array[i + 1] = array[i];
        }

        /* Save data */
        array[pos] = 600;

        /* Increase count */
        size = size + 1;
}
```

## Full C Code Explanation

This section starts with no assumed knowledge of C. It explains all five
examples in **C Code**, including the small symbols, the order of execution,
and the values stored after each operation. You can read one explanation
alongside its original example and return for the next operation later.

### 1. What are we reading, and where does execution begin?

**Code** is text written in a programming language. C is the language used
here. A **program** is a complete set of instructions that a computer can
run. To **execute** an instruction means to carry it out. A C **compiler**
translates C source code into a form the computer can run.

The five examples above are parts of a program. For this explanation, we
place them together inside one function and run them in their printed
order: set up storage, read and change an item, search, delete, and insert.
A **function** is a named piece of code. Section 10 supplies the complete
program and explains its starting function, `main`.

The later examples use variables created in the first example. They do not
automatically start again with the original array. For example, the search
sees the array after the read/change example has changed it. If you run
separate experiments, set up the starting values for each experiment.

A **value** is a piece of information, such as the number `5`. A **variable**
is a named place to store a value. An **expression** produces a value:
`size + 1`, for example, calculates one more than the current value of
`size`. A **statement** tells the program to do something. An assignment
statement such as `size = size + 1;` stores a calculated value.

In these examples, execution normally proceeds from one statement to the
next. An `if` can skip a group of statements. A `for` can repeat a group.
We will follow both changes of direction explicitly.

The shaded code boxes, the surrounding backticks, and the `c` label used
to format this document are not part of a C program. Copy the text inside
the box when copying C code.

### 2. Reading names, numbers, comments, and punctuation

Start with a line from the chapter:

```c
int size = 5;
```

| Part | Meaning here |
|---|---|
| `int` | A C keyword specifying an integer type: a kind of value that can represent whole numbers, including negative numbers, zero, and positive numbers within its supported range. |
| `size` | The name we chose for this variable. It will record the number of active list items. |
| `=` | Introduces the initial value when used in this declaration. |
| `5` | The whole-number value to store initially. A number written directly in code is called a numeric literal. |
| `;` | Ends this declaration. It is part of the C code. |

This line **declares** the variable, introducing its name and type, and
**initializes** it, giving it its first value. Read it as: “Create an integer
variable named size and start it at five.” The type does not mean that the
variable can hold every imaginable integer; our small example values fit.

Names such as `size`, `array`, `array_capacity`, `pos`, `data`, `target`,
`index`, and `i` were chosen by the programmer. C does not automatically
understand their intended jobs. In particular, naming a variable `size`
does not make it count array items for us. Our statements must maintain it.

`array_capacity` is one name. The underscore `_` joins parts of that name;
it does not subtract or perform another calculation. `pos` is our short
name for “position,” and `i` is a short name for a loop's changing index.
Names distinguish uppercase and lowercase letters: `size` and `Size`
would be different names. Keywords such as `int`, `if`, `for`, and `break`
have meanings defined by C and cannot be used as our variable names.

Now compare two other lines:

```c
int pos;
pos = 1;
```

`int pos;` declares an integer variable without giving it an initial value.
For this local variable inside a function, we must not read its value
before assigning one. It does **not** automatically start at zero.
`pos = 1;` then stores `1` in that existing variable. We omit `int` because
this second line is an assignment, not another declaration.

The same rule applies to `int index;` in the search example: the loop will
assign `0` before testing or otherwise reading `index`.

This chapter also uses comments:

```c
/* Setup item count */
```

`/*` starts a comment, and `*/` ends it. The words between them explain the
code to a person; they are not executed. This comment does not set up the
item count by itself. The following `int size = 5;` does that work. The
slash and star here belong to the comment markers, not to arithmetic.

Spaces and line breaks separate and arrange the code. The space between
`int` and `size` keeps them separate words; `intsize` would be one name.
Blank lines help us see groups. Indentation means the spaces at the start
of a line. It helps a reader see which statements belong together, but
braces determine the groups in these examples. Moving a statement left
or right on the page does not move it out of its braces. A line break also
does not replace a required semicolon.

### 3. Explaining every part of the storage setup

Here is the original setup again:

```c
/* Declare fixed storage */
int array[10] = {100, 200, 300, 400, 500, 0, 0, 0, 0, 0};
int array_capacity = 10;

/* Setup item count */
int size = 5;

/* Position to access item */
int pos;
```

The lines beginning with `/*` are comments. They label the jobs of the
following declarations. The array declaration is longer, but each part
has a specific job:

| Part | Meaning in this declaration |
|---|---|
| `int` | Each array element stores an integer. |
| `array` | Our name for the array. |
| `[10]` | Reserve ten element positions. Here the number in square brackets is the array's length, not a position being accessed. |
| `=` | Introduce the array's initial values. |
| `{` and `}` | Surround the list of initial values. These braces are an initializer, not a group of statements to execute. |
| `100, 200, ...` | Give the values in position order. Each comma separates one value from the next. The actual code writes all ten values; the dots here only abbreviate the table explanation. |
| `;` | End the whole declaration. |

An **array element** is one of the array's storage positions. Its **index**
is the number selecting that position. Ten positions have indexes `0`
through `9`, because index `0` selects the first position. Index `10` would
ask for an eleventh position, which this array does not have.

After the setup, the stored values and our interpretation are:

| Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
|---|---|---|---|---|---|---|---|---|---|---|
| Stored value | 100 | 200 | 300 | 400 | 500 | 0 | 0 | 0 | 0 | 0 |
| Belongs to the current list? | Yes | Yes | Yes | Yes | Yes | No | No | No | No | No |

`int array_capacity = 10;` creates a separate integer variable containing
`10`. We use it as the maximum allowed item count. It does not create the
array or connect itself automatically to `[10]`. Changing this variable
would not resize the array. In this chapter we keep both the array's ten
positions and the capacity value fixed.

`int size = 5;` creates another integer variable containing `5`. We choose
five because the first five positions are our initial list items. Size is
an item count, not the last index: the last active index is `size - 1`,
which is `4` here. The active items occupy consecutive positions starting
at zero. That initial part of the array is called the **active prefix**.

All ten elements have initial values, including the five zeros at the end.
Those zeros do not mean “empty” to C. We exclude those positions from the
list because their indexes are at least `size`. Zero can also be an active
list item. Later, an inactive position may contain an old nonzero value;
size will still tell us where the active list ends.

Finally, `int pos;` introduces the position variable. It is separate from
both the array and the size. The next example assigns a value before
using it. The setup itself produces no screen output: storing information
and displaying information are different actions.

### 4. Reading calculations, conditions, and groups of statements

These are all the calculation and comparison operators in the original
five examples. An **operator** is a symbol that specifies an operation on
values.

| Written form | How to read it | Result when `size` is 5 and `pos` is 1 |
|---|---|---|
| `size + 1` | Add one to size. | The expression produces `6`; size itself has not changed yet. |
| `size - 1` | Subtract one from size. | The expression produces `4`; size itself has not changed yet. |
| `pos >= 0` | Is pos greater than or equal to zero? | True. |
| `pos < size` | Is pos strictly less than size? | True. |
| `pos <= size` | Is pos less than or equal to size? | True; equality would be allowed too. |
| `array[index] == target` | Does the selected value equal target? | Depends on the selected value and target. |
| `pos >= 0 && pos < size` | Are both comparisons true? | True. |

In a condition, C treats zero as false and a nonzero value as true. The
comparisons used here produce `1` for true or `0` for false. `&&`, called
logical AND, also produces `1` or `0`. It joins conditions that must all
be true.

`&&` checks its left side first. If that side is false, the right side is
not evaluated. This is called **short-circuit evaluation**. For example,
when `pos` is `-1`, `pos >= 0` is false, so the combined condition is already
false. Here the minus sign in `-1` marks a negative number; in `size - 1`
it instead instructs us to subtract one value from another.

The comparison signs belong together: `>=` is one operator, as are `<=`
and `==`. Read the comparisons in `pos >= 0 && pos < size` as two complete
questions joined by `&&`. C's grouping rules give the comparisons priority
over the logical AND. We could make that grouping visible with extra
parentheses: `(pos >= 0) && (pos < size)`.

**Assignment and comparison have different jobs.** `pos = 1;` stores a
value. `pos == 1` asks whether a value is already equal to one. Do not
replace `==` with `=` in a comparison: assignment can be accepted inside a
C condition and would change the variable instead of performing the
intended equality test.

Consider this assignment from the chapter:

```c
size = size + 1;
```

Read the current size on the right, add one, and store that result in the
variable on the left. If size was `5`, it becomes `6`. This is not a
mathematical claim that five equals six. The right side uses the old
value; the left side receives the new value. A later change to size does
not automatically repeat earlier calculations.

Here is the structure of an `if` from the chapter:

```c
if (pos >= 0 && pos < size) {
        int data = array[pos];
        array[pos] = 500;
}
```

`if` introduces a decision. Its parentheses `(` and `)` surround the
condition to check. If the condition is true, execution enters the braces
and runs their statements in order. If it is false, execution skips the
whole group and continues after the closing brace. There is no repeated
check between the statements inside this group.

Here `{` and `}` form a **block**, a group of declarations and statements.
These braces have a different job from the braces around the array's
initial values. The two statements inside end with semicolons. This `if`
block does not need an extra semicolon after its closing brace. Do not put
a semicolon between the closing `)` of this `if` condition and its opening
`{`: that would make the controlled statement empty and leave the block
outside the intended decision.

A variable declared inside a block can be used from its declaration to
the end of that block, including nested blocks unless another declaration
uses the same name there. This part of the program where a name can be
used is its **scope**. Here `data` belongs to the `if` block. The outer
variables `array`, `size`, and `pos` can be used inside it. Changing their
values there affects the subsequent examples; leaving the block does not
undo those changes.

### 5. Reading and changing an item, line by line

The original example starts with `pos = 1;`. This assigns index `1` to
`pos`, selecting the second array element. It does not mean “find the
number 1.” The position is `1`; the value initially stored there is `200`.

The guard `if (pos >= 0 && pos < size)` checks two requirements: the index
must not be negative, and it must be less than the number of active items.
With `pos` equal to `1` and size equal to `5`, both requirements hold.
The statements inside the block therefore execute.

```c
int data = array[pos];
```

`int data` declares a new integer variable. `=` introduces its initial
value. `array[pos]` reads the element selected by the current value of
`pos`, so it reads `array[1]`. Unlike `[10]` in the array declaration,
these brackets select an existing element. The semicolon ends the
declaration. The new variable `data` now contains a **copy** of `200`.

```c
array[pos] = 500;
```

On the left of this assignment, `array[pos]` selects the destination to
change. The number `500` on the right is stored there. The array's second
element changes from `200` to `500`; the other elements are unchanged.

The earlier copy in `data` is still `200`. It is not a permanently linked
view of the array element. Although the array value has been copied into
`data`, nothing in the original example prints it. Its name is no longer
available once execution leaves this `if` block. The complete program below displays it
while still inside that block.

| Moment | `pos` | `size` | Active list | `data` inside the block |
|---|---|---|---|---|
| After assigning pos | 1 | 5 | 100, 200, 300, 400, 500 | Not declared yet. |
| After reading | 1 | 5 | 100, 200, 300, 400, 500 | 200 |
| After changing | 1 | 5 | 100, 500, 300, 400, 500 | 200 |

If pos were `-1`, `5`, or `10` with size `5`, this guard would reject it.
Position `5` exists in the underlying array but does not currently hold
an active item. Position `10` does not even exist in this ten-element
array. C does not automatically check array bounds for us. Access outside
the actual array has undefined behavior: C gives no dependable outcome.
It need not produce a helpful error or crash. These guards protect access
under our maintained rule that size is between zero and capacity and
capacity matches the actual ten available elements.

### 6. Finding a value and understanding every step of a loop

The search starts with these declarations:

```c
/* Target value to find */
int target = 300;

/* Where the result will be saved */
int index;
```

The comments label the two jobs. `int target = 300;` declares an integer
named `target` and initializes it to the value we want to find. `int index;`
declares the integer that will hold a position. It has no initial value
yet. These declarations introduce different variables from `pos`: changing
`index` will not change `pos`.

The search then uses a **loop**, a statement that repeats work:

```c
for (index = 0; index < size; index = index + 1) {
        if (array[index] == target) {
                break;
        }
}
```

`for` is the C keyword introducing this loop. The parentheses contain
three parts, separated by two semicolons. These semicolons separate the
loop's setup, condition, and update; they do not finish the entire `for`.

| Part | Meaning | When it happens |
|---|---|---|
| `index = 0` | Store zero in the existing index variable. | Once, before the first check. |
| `index < size` | Ask whether index still selects an active position. | Before each attempted execution of the body. |
| `index = index + 1` | Add one to index and store the result back in index. | After each completed body, unless `break` exits the loop. |

The braces after the parentheses enclose the **body**, the code that the
loop repeats. There is no semicolon between the closing `)` and the body
in this example. Within the body, a second pair of braces belongs to the
`if`. The inner closing brace ends the `if` block; the outer closing brace
ends the loop body.

For a loop that continues normally, execution follows this order:

1. Initialize index to `0`, once.
2. Check `index < size`. If false, continue after the loop.
3. If true, execute the body using that index.
4. Execute the update, increasing index by one.
5. Return to step 2, without repeating the initialization.

The body checks `array[index] == target`. Square brackets select the
current array element; `==` compares its value with target. The `if`
parentheses surround that condition. If the values differ, its block is
skipped, and the loop reaches its update.

If the values match, the body executes `break;`. `break` is a keyword that
exits the nearest enclosing loop here. The semicolon ends that statement.
Although it is written inside an `if`, it exits the surrounding `for`,
not merely the `if` block. Execution continues after the loop's closing
brace. The update is skipped, so index retains the matching position.

The array now contains the change from Section 5:

| Index being checked | Selected value | Is it equal to target 300? | What happens next? |
|---|---|---|---|
| 0 | 100 | No. | Update index to 1. |
| 1 | 500 | No. | Update index to 2. |
| 2 | 300 | Yes. | Execute `break`; index remains 2. |

The result is index `2`, which selects the third item. The search reads
the array but changes neither its elements nor size. `pos` is still `1`.
Because `index` was declared before the loop, its name is available after
the loop for us to inspect the result.

If target were `999`, the loop would inspect indexes `0` through `4`,
then update index to `5`. The condition `5 < 5` would be false, so the body
would not run with index `5`. Index equal to size means “not found” in
this example. It is a result to test, not a position to read. Do not read
`array[index]` after a search unless index is less than size. If the list
were full, reading at index equal to size would also be outside the array.

An empty list has size `0`: initialization still sets index to `0`, but
the first test `0 < 0` is false and no array element is read. If several
active elements equal the target, `break` stops at the first one. In our
current list, searching for `500` would find index `1`, not index `4`.

### 7. Deleting an item and tracing each copy to the left

The deletion example uses the existing `pos`, which is still `1`. It
does not use the search result `index`, which is `2`. At this point size
is `5`, and the active list is `100, 500, 300, 400, 500`.

```c
/* Check number */
if (pos >= 0 && pos < size) {

        /* Shift data left */
        for (int i = pos + 1; i < size; i = i + 1) {
                array[i - 1] = array[i];
        }

        /* Decrease count */
        size = size - 1;
}
```

The comments describe the check, copies, and count change; they perform
none of those actions themselves. The outer `if` repeats the two checks
for an existing item: pos must be at least zero and strictly less than
size. With pos `1`, the body executes. If the condition were false, both
the loop and the size change would be skipped.

The `for` again has setup, condition, and update between parentheses:

| Part | Exact meaning here |
|---|---|
| `int i = pos + 1` | Declare a new integer `i`. Calculate pos plus one and use it as the initial value: `2`. This starts immediately after the item being deleted. |
| `i < size` | Continue only while i selects an active source item. |
| `i = i + 1` | After a completed body, increase i by one so the next source is farther right. |

This time `int i` appears inside the loop's setup. Its scope covers the
rest of the loop, including its condition, update, and body. This `i` is
not available after the loop. A later loop may declare its own `int i`.

Read the body's assignment from its source to its destination:

```c
array[i - 1] = array[i];
```

The right side reads the value at index `i`. On the left, `i - 1`
calculates the previous index and selects that destination. The assignment
copies the value into that destination. Neither bracket expression changes
`i`. The loop's update changes it afterward. A copy does not erase its
source, so the array can temporarily contain repeated values.

| Step | Copy performed | Values at indexes 0 through 4 | Size |
|---|---|---|---|
| Before the loop | None. | 100, 500, 300, 400, 500 | 5 |
| Body with i = 2 | Copy `array[2]` into `array[1]`. | 100, 300, 300, 400, 500 | 5 |
| Body with i = 3 | Copy `array[3]` into `array[2]`. | 100, 300, 400, 400, 500 | 5 |
| Body with i = 4 | Copy `array[4]` into `array[3]`. | 100, 300, 400, 500, 500 | 5 |
| After update to i = 5 | `5 < 5` is false; leave the loop. | 100, 300, 400, 500, 500 | 5 |
| `size = size - 1;` | Calculate 5 minus 1 and store 4 in size. | 100, 300, 400, 500, 500 | 4 |

The loop's closing brace comes **before** `size = size - 1;`. Consequently,
the size change happens once after all the copies, not once for each
copy. Size must keep its original value while the loop uses it to find
the last source element.

The resulting active list is `100, 300, 400, 500`, at indexes `0` through
`3`. The old `500` at index `4` is still physically present, but it is now
outside the active list. Deletion does not need to replace it with zero,
and the array's capacity is still ten.

Why start with the source immediately after pos? Each copy overwrites a
position whose old value is either the removed item or has already been
copied left. If we copied index `4` into `3` first in this example, we would
overwrite `400` before copying it to index `2`. The direction protects
values we still need.

Deleting the last item needs no copies: the setup makes i equal to size,
so the first loop condition is false. The size decrease still happens
once. Deleting from an empty list is rejected by the outer guard, so size
does not become negative.

### 8. Inserting an item and tracing each copy to the right

Continue from the deletion result: size is `4`, pos is `1`, and the active
list is `100, 300, 400, 500`. The insertion example is:

```c
/* Check number */
if (pos >= 0 && pos <= size && size < array_capacity) {

        /* Shift data right */
        for (int i = size - 1; i >= pos; i = i - 1) {
                array[i + 1] = array[i];
        }

        /* Save data */
        array[pos] = 600;

        /* Increase count */
        size = size + 1;
}
```

The outer `if` has three comparisons joined by `&&`. All must be true:

| Comparison | Requirement | Evaluation in this example |
|---|---|---|
| `pos >= 0` | Do not insert at a negative position. | `1 >= 0` is true. |
| `pos <= size` | Allow a position within the list or immediately after it, with no gap. | `1 <= 4` is true. |
| `size < array_capacity` | Require room for one more item. | `4 < 10` is true. |

The middle comparison uses `<=`, not the `<` used for reading and
deleting. Insertion at pos equal to size creates a new last item. This is
called **appending**. Reading or deleting at that same position would try
to use an item that does not yet belong to the list.

The capacity comparison is strict. When size equals `10`, the array is
full and insertion is rejected. Writing `array[10]` would be outside the
array. When any guard comparison is false, the loop, new-value assignment,
and size increase are all skipped, so the existing array and size remain
unchanged. The combined condition is checked when entering the `if`, not
again between each statement inside it.

Here is the loop header broken down:

| Part | Exact meaning here |
|---|---|
| `int i = size - 1` | Declare this loop's integer i and initialize it to the last active index: `3`. |
| `i >= pos` | Continue while the source is at or after the insertion position. Equality includes the item currently at pos. |
| `i = i - 1` | After each body, decrease i by one to visit the next source to the left. |

The source is again on the right of the assignment:

```c
array[i + 1] = array[i];
```

Read the value at index `i` and copy it into the next position, at index
`i + 1`. The addition chooses a destination; it does not change i. The
first destination is the old size, index `4`, which fits because the
guard confirmed spare capacity. No item is added to size during the loop.

| Step | Copy or assignment | Values at indexes 0 through 4 | Size |
|---|---|---|---|
| Before the loop | Index 4 contains an inactive old value. | 100, 300, 400, 500, 500 | 4 |
| Body with i = 3 | Copy `array[3]` into `array[4]`. | 100, 300, 400, 500, 500 | 4 |
| Body with i = 2 | Copy `array[2]` into `array[3]`. | 100, 300, 400, 400, 500 | 4 |
| Body with i = 1 | Copy `array[1]` into `array[2]`. | 100, 300, 300, 400, 500 | 4 |
| After update to i = 0 | `0 >= 1` is false; leave the loop. | 100, 300, 300, 400, 500 | 4 |
| `array[pos] = 600;` | Store 600 at index 1. | 100, 600, 300, 400, 500 | 4 |
| `size = size + 1;` | Calculate 4 plus 1 and store 5 in size. | 100, 600, 300, 400, 500 | 5 |

The two statements after the loop each run once. `array[pos] = 600;`
selects the new item's destination and assigns its value. `size = size + 1;`
then includes the additional position in the active list. The outer
closing brace ends the whole guarded insertion.

The first copy in the table happens to store `500` over an old `500`.
The code still performs the copy; it does not depend on the inactive
destination's previous value. The temporary repeated values are expected
while we make space. The final active order is `100, 600, 300, 400, 500`.

Why move from right to left? Copying index `1` into `2` first would destroy
the `400` that we still need to move out of index `2`. Beginning with the
last item preserves every source before its position is overwritten.

For append, pos equals size. The initial i is size minus one, so the
first condition `i >= pos` is false. The program skips copying, writes at
`array[pos]`, and increases size. In an empty list, size and pos are both
zero; i starts at `-1`, and `-1 >= 0` is false, so no element at a negative
index is accessed. The ordinary `int` used here can represent negative
numbers. When inserting at the front of a nonempty list, i likewise
becomes `-1` after copying the item at index `0`, and the next condition
stops the loop before another array access.

### 9. Following the five examples as one continuous story

Every row below continues from the previous row. Capacity stays ten.
The square brackets in this table simply display the active list; they
are not additional C statements.

| After this operation | Active list | Size | Other information |
|---|---|---|---|
| Set up storage | `[100, 200, 300, 400, 500]` | 5 | pos has been declared but not assigned. |
| Set pos, read, and change | `[100, 500, 300, 400, 500]` | 5 | pos is 1; data received a copy of 200 inside its block. |
| Search for 300 | `[100, 500, 300, 400, 500]` | 5 | index is 2; pos is still 1. |
| Delete at pos 1 | `[100, 300, 400, 500]` | 4 | Index 4 still stores an inactive old 500. |
| Insert 600 at pos 1 | `[100, 600, 300, 400, 500]` | 5 | The added item is between 100 and 300. |

Search saved the number `2` in index. Later operations can move the item
that was found: after deletion, `300` is at position `1`; after insertion,
it is back at position `2`. The saved number does not automatically
follow an item when the array changes. Search again if you need its
current location after changes.

### 10. Putting the examples in a complete program

The five original examples have no instructions for displaying results.
The program below places them inside `main` and adds display statements
so we can see the read value, the search result, and the final list. Its
array operations are the ones explained above. This is a separate,
complete example that can be copied as one file.

Before reading it, we need the additional syntax used to start a program
and display values:

| Code | Explanation |
|---|---|
| `#include <stdio.h>` | An instruction to the C preprocessing step, before compilation, to include the standard input/output header. It provides the declaration of `printf`. The `#` begins the directive; `include` names what to do; `<stdio.h>` identifies a standard header. There is no semicolon on this line. |
| `stdio.h` | The header's name. “stdio” refers to standard input/output; `.h` is the header filename ending. These are not variable names in our program. |
| `<` and `>` in the include line | Delimit the header name. In this context they do not compare numbers. |
| `int main(void)` | Begin the definition of the function where this program's execution starts. `int` says it returns an integer result. `main` is the entry function's name. The parentheses describe inputs; `void` here means there are no parameters. |
| `{` and `}` following `main` | Enclose the function's body. Its statements run in order, subject to the decisions and loops inside it. |
| `printf` | The name of a standard library function that displays formatted text. A library supplies functions a program can use. |
| `printf("Read value: %d\n", data);` | Call that function: ask it to perform its job with the inputs between parentheses. The semicolon ends the call statement. |
| `"Read value: %d\n"` | A string literal: text enclosed in double quotation marks. The quotation marks delimit the string in code; they are not printed. |
| `%d` inside that string | A format specification asking `printf` to display the corresponding integer argument in decimal form. `%d` is interpreted as part of the format string, not as an ordinary variable name or arithmetic expression. |
| `\n` inside that string | A backslash and n forming an escape sequence for a newline. The output moves to the next line; it does not print a backslash followed by an n. |
| `, data` | A comma separates the format string from the next argument, the current value of data to display. |
| `return 0;` | The C keyword `return` ends main here and returns integer zero to the environment that ran the program, reporting successful completion. It does not display the number zero. |

A function's **parameters** are the named inputs specified when the
function is declared or defined. **Arguments** are the values supplied
when calling a function. This `main(void)` defines no parameters.
`printf("Read value: %d\n", data)` supplies a format string and the value of
data as arguments to printf. Parentheses identify the call's arguments
here; after `if` they instead surround a condition, and after `for` they
surround the three loop parts. Use the surrounding words to recognize
their job.

In `printf("array[%d] = %d\n", i, array[i]);`, the first `%d` displays i,
and the second displays the value of `array[i]`. The two integer arguments
match the two specifications in that order. The characters `array[`, `]`,
and ` = ` inside the quotation marks are ordinary printed text. They do
not select an array element or assign a value. The `array[i]` outside the
quotation marks is the C expression that actually reads an element.

```c
#include <stdio.h>

int main(void)
{
        /* Declare fixed storage */
        int array[10] = {100, 200, 300, 400, 500, 0, 0, 0, 0, 0};
        int array_capacity = 10;

        /* Setup item count */
        int size = 5;

        /* Position to access item */
        int pos;

        pos = 1;

        /* Check number */
        if (pos >= 0 && pos < size) {
                /* Read data */
                int data = array[pos];
                printf("Read value: %d\n", data);

                /* Change data */
                array[pos] = 500;
        }

        /* Target value to find */
        int target = 300;

        /* Where the result will be saved */
        int index;

        for (index = 0; index < size; index = index + 1) {
                if (array[index] == target) {
                        break;
                }
        }
        printf("Search result index: %d\n", index);

        /* Check number */
        if (pos >= 0 && pos < size) {
                /* Shift data left */
                for (int i = pos + 1; i < size; i = i + 1) {
                        array[i - 1] = array[i];
                }

                /* Decrease count */
                size = size - 1;
        }

        /* Check number */
        if (pos >= 0 && pos <= size && size < array_capacity) {
                /* Shift data right */
                for (int i = size - 1; i >= pos; i = i - 1) {
                        array[i + 1] = array[i];
                }

                /* Save data */
                array[pos] = 600;

                /* Increase count */
                size = size + 1;
        }

        printf("Final size: %d\n", size);
        for (int i = 0; i < size; i = i + 1) {
                printf("array[%d] = %d\n", i, array[i]);
        }

        return 0;
}
```

The added final loop declares its own i starting at `0`, checks `i < size`
before each body, and increases i after each body. Each body displays one
active element. It stops when i reaches size. The earlier loops' local
variables named i are already out of scope, so this declaration is
independent of them. `return 0;` runs after the display loop, and the last
brace closes main.

The expected output is:

```text
Read value: 200
Search result index: 2
Final size: 5
array[0] = 100
array[1] = 600
array[2] = 300
array[3] = 400
array[4] = 500
```

For this target, index `2` is a successful search result. If you change the
target to a missing value, the displayed index will equal size at the
time of the search; it will mean “not found,” as explained in Section 6.
The display statement prints the saved index and does not read an array
element at that index.

To try the program, save only the complete C code as `chapter1.c`, a plain
text source file. The `.c` filename ending identifies C source. You can
compile and run it using the compiler provided for your course. With GCC
or Clang available as `cc` on macOS or Linux, these terminal commands work:

```sh
cc -std=c11 -Wall -Wextra chapter1.c -o chapter1
./chapter1
```

These two lines are **terminal commands**, not C statements to paste into
the source file. Run them from the folder where you saved `chapter1.c`.
`cc` invokes the compiler. `-std=c11` selects the C11 language version,
which supports the declarations inside these loop headers. `-Wall` and
`-Wextra` request useful compiler warnings. `chapter1.c` names the input
file; `-o chapter1` names the output program. Compile successfully first,
then use `./chapter1` to run the program named chapter1 in the current
folder. The `./` is a terminal path notation. Its dot and slash are not
part of the C syntax explained above.

### 11. Small checks, with explanations of the answers

Try each question before reading its answer. Each question states its
own starting situation; it does not silently change the earlier trace.

1. **In `int size = 5;`, which part is the variable's name? Does the name
   make C count items automatically?**

   **Answer:** The name is `size`. C stores the value we supply, `5`.
   Our later statements must change that value when the item count changes.

2. **Immediately after `int pos;` inside main, can we safely assume pos
   contains zero?**

   **Answer:** No. This declaration supplies no initial value. Assign a
   value, as `pos = 1;` does, before reading pos or using it as an index.

3. **If size is `5`, what happens when `size + 1` is calculated? What
   additional action does `size = size + 1;` perform?**

   **Answer:** The calculation produces `6`. The assignment also stores
   that result back in size, changing size from `5` to `6`.

4. **After copying `array[1]`, whose value is `200`, into data, we assign
   `500` to `array[1]`. What does data contain while still in its block?**

   **Answer:** `200`. Reading an integer into another integer variable
   copies the value. The later array change does not change that copy.

5. **With size `5`, is pos `5` a valid position to read? Can it be a valid
   insertion position when capacity is `10`?**

   **Answer:** Reading is rejected because `5 < 5` is false. Insertion is
   allowed because `5 <= 5` and `5 < 10` are true. It appends a new item.

6. **The search finds a match with index `2` and executes `break;`. Does
   the loop's update change index to `3` afterward? Does pos change?**

   **Answer:** No to both. Break leaves the loop before its update. Pos
   is a separate variable and is not assigned anywhere in the search.

7. **When deleting the last item of a nonempty list, the shift loop runs
   zero times. Does size still decrease?**

   **Answer:** Yes. The size assignment is after the loop but inside the
   valid-position guard, so it runs once for this valid deletion.

8. **During insertion, does `array[i + 1] = array[i];` increase i?**

   **Answer:** No. `i + 1` calculates the destination index. The assignment
   changes an array element. The separate update `i = i - 1` changes i.

9. **Size and capacity are both `10`. We try to insert at pos `0`. Which
   check prevents a write, and what remains afterward?**

   **Answer:** `size < array_capacity` is false. The entire insertion body
   is skipped. Every array value and size keep their previous values.

10. **An inactive slot contains `500`, and an active slot contains `0`.
    Which one belongs to the list?**

    **Answer:** The active slot containing zero belongs to the list.
    Membership depends on whether its index is less than size, not on
    whether its stored value looks like an “empty” marker.
