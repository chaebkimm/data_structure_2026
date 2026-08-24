# Chapter 1. Keeping Data Together in One Place

## Thinking Logically

### Why should we keep data together?

When you want to do the same task for all your data, having it gathered in one place makes it easy to just go through the items one by one.

### The Simplest Method

If you already know how many pieces of data you want to store, you can just set aside exactly that much memory space for them from the start.

### How do we find data by its number?

Since all the data is lined up right next to each other in the computer's memory, the computer doesn't need to check the items one by one. Instead, it uses a quick math calculation to figure out exactly where that number is and jumps straight to that spot.

### How do we delete data?

Even after deleting a piece of data, we need to keep the remaining data packed closely together. To do this, we move all the data that comes *after* the deleted item forward by one space. After deleting, the final number of items goes down by one.

```text
[10] [50] [20] [30] [ ] (Initial state)
[10] [ ] [20] [30] [ ] (Remove 50)
[10] [20] [30] [ ] [ ] (Shift 20 and 30 to the left)
```

### How do we add data?

You can simply add new data to the very end of your existing data.

If you want to add data right in the middle, you must make sure all the data stays packed together without losing any values. First, shift the data at the target spot—and everything after it—backward by one space. Then, place your new data into the empty spot. After adding it, the final number of items goes up by one.

```text
[10] [20] [30] [ ] [ ] (Initial state)
[10] [20] [ ] [30] [ ] (Shift 30 right)
[10] [20] [99] [30] [ ] (Insert 99 in the middle)
```

### What should we check when adding data?

You need to check if the memory space you set aside is completely full. If it is, you have to handle it with a special extra step.

### How can we add data if the space is full?

You just need to get a new, bigger memory space. Copy the old data over one by one, from start to finish, into the new space. Then, add your new data. Finally, give back (free) the old memory space.

## Calculating Efficiency

### Memory Efficiency

You use exactly the amount of memory you originally set aside for your items. When you need to get a new memory space, it is usually double the size of the old one.

### Efficiency of Adding Data

If you have leftover space and add an item to the very end, it is super fast because no other data needs to move. But if you add an item to the very front, you have to push all existing data back by one space. This means the amount of work increases based on how much data you have.

### Efficiency of Deleting Data

Deleting the very last item is instantly finished because there is nothing behind it to pull forward. But deleting the very first item means you have to shift everything else forward by one space, so the amount of work increases with the total number of items.

### Efficiency of Finding Data by its Number

Because the data items are placed right next to each other, if you just know its number, you can instantly calculate its exact position and find it.

### Efficiency of Finding Data by its Value

You have to check the items one by one, starting from the first one. If it is at the very front, you find it instantly. But if it is at the very end—or not there at all—you have to check absolutely everything. The work grows with the total amount of data.

### Efficiency of Expanding Memory and Copying Data

Because every old item must move to the new memory space, one expansion requires more work as the amount of stored data grows. However, doubling creates many empty slots, so expansion happens less often. Across many additions, the total copying work grows in proportion to the number of items added. Therefore, the average work for each addition remains small.

## Glossary

### Data

The things a computer processes and stores.

### Data Structure

A specific way of organizing and gathering data so we can store, manage, and use it efficiently.

### Contiguous Memory

Memory spaces that are placed right next to each other in a single, unbroken line. Because there are no gaps, the computer can instantly calculate exactly where a specific piece of data is located.

### Array

A data structure where you set aside a fixed amount of memory space ahead of time to store a certain number of items.

### List

A data structure that stores data in a specific, ordered sequence.

### ArrayList

A list that is built using an array under the hood.

### Dynamic Array

An array that automatically gets a bigger memory space and moves the old data into it whenever it gets completely full.

### Index

The number that tells you the exact position of a specific piece of data.

### Element

Each individual piece of data stored inside an array or list.

## Invariant

### What is the invariant (the golden rule) in this data structure?

All data items must be stored consecutively (back-to-back) in memory, with no empty gaps between them. The data is packed tightly at the front of the allocated memory space (from index 0) as an engineering design choice.

### What is the benefit from the invariant?

It enables instant random access. Because the items are stored in a continuous sequence, the computer can use the index numbers to instantly jump to any specific piece of data, rather than having to search through the items one by one.

### How is the invariant maintained during insertion?

To add a new piece of data without breaking the rule, the ArrayList handles it in two ways:

- Adding at the end: You can only place the new item exactly one spot after the current last item. You cannot skip spaces.

- Adding in the middle: You must first shift all subsequent items one space to the right to create an empty "hole," and then you insert the new item into that gap.

### How the invariant is kept during deletion?

When you remove an item from the middle of the list, it leaves a gap. To keep the data contiguous, you must shift all the items that came after the deleted item one space to the left to close the hole.

## Example: managing ip addresses of connected devices

### Where should we save the IP addresses?

An IPv4 address is made up of four numbers ranging from 0 to 255 (for example, 192.168.1.10). Because of this specific size, a single IP address can be converted and fit perfectly inside a standard unsigned int on a typical computer. We will use an array of unsigned int to store these addresses efficiently.

### How many memory slots should we start with?

Before any devices connect, we must set aside a fixed amount of space. Let's start by allocating enough contiguous memory for 10 slots (a capacity of 10).

### What happens when the first IP address is stored?

Because our memory space is completely empty, the first IP address is stored at the very front of our allocated memory, which is index 0. We then update our total count of connected devices to 1.

### What happens when the second IP address is stored?

To maintain our golden rule—that all data must be packed tightly together without any gaps—the new IP address must be placed immediately after the first one. It is saved at index 1, and our total count goes up to 2.

### What happens when the first IP address is deleted?

If the device at index 0 disconnects, deleting its IP address leaves an empty hole at the front of our memory block. To keep the data contiguous, we must pull all the other IP addresses forward (to the left) by exactly one space. The IP at index 1 moves to index 0, the IP at index 2 moves to index 1, and so on. Finally, the total count is reduced by one.

### How do we check whether a specific IP address is connected?

To find a device by its actual IP address (its value, not its index), we cannot jump straight to it. Instead, we must start at index 0 and iterate through the array, checking the items one by one. We stop searching once we either find a match or reach the total number of currently stored IP addresses.

## Coding Plan

### Saving Data in an Array

* **Allocate Memory:** Decide the maximum number of items you want to store and grab that much memory space.
* **Choose Position:** Pick the very first number (spot) in the memory that doesn't have data saved in it yet.
* **Save Data:** Put your data into that chosen spot.
* **Update Count:** Increase the total count of your stored data.

### Reading or Changing Data at a Specific Number

* **Check Number:** Make sure the number you want actually has data saved in it.
* **Read Value:** Read what is saved at that number in the array.
* **Change Value:** Update or change the value saved at that number.

### Deleting Data at a Specific Number

* **Check Number:** Make sure the number actually has data saved in it.
* **Pull Data Forward:** Move everything that comes right after the deleted spot forward by one space, doing it one by one from front to back.
* **Decrease Count:** Decrease the total count of your data.

### Adding Data to a Specific Number

* **Check Number:** Make sure the spot connects to your existing data and fits perfectly inside your total memory size.
* **Push Data Back:** Starting from the very last item down to the spot where you want to add, push each item back by one space.
* **Save Data:** Put your new data into the freshly cleared spot.
* **Increase Count:** Increase the total count of your data.

If we start from the front and move the first item to the right, we will accidentally crush the item sitting in the next spot before it has a chance to move! Starting from the back ensures we move data into empty holes.

### Expanding the Memory Space

* **Create Space:** Get a new memory space that is twice as big as your old one.
* **Transfer Data:** Copy all the data from the old memory into the new memory in the exact same order.
* **Clean Up Old Space:** Give back the old memory space, and start using the new memory space from now on.

## New C Syntax Explained

### `sizeof`

Before you can ask the computer for memory space, you need to know exactly how big your data is. Different types of data take up different amounts of room. `sizeof()` is a built-in tool that calculates exactly how much space (in bytes) one piece of data needs. For example, writing `sizeof(int)` tells the computer the exact size of one integer. To figure out the total space needed for an array, you just multiply the size of one item by the total number of items you want to store.

### `*` (Pointers)

When you get a new space in memory, the computer doesn't hand you the actual space—it hands you the address of where that space starts. A "pointer" is simply a special variable designed to hold a memory address. It literally "points" to where your data lives. In C, you mark a variable as a pointer by putting a star (`*`) next to it. For example, `int *arrayList` creates a pointer that holds the starting address of a bunch of integers.

### `malloc` (Memory Allocation)

When you need to grab a new memory space while your program is already running (like when you are creating a dynamic array), you use malloc. You tell it exactly how much total room you need (for example, `sizeof(int) * 6`). The computer will then find a single, unbroken block of memory that fits your request and hand you back the starting position of that brand new space.

### `NULL`

When you ask the computer for memory using `malloc`, there is a tiny chance it might say "no" (usually because the computer is completely out of memory). When this happens, it doesn't give you a real memory address. Instead, it hands back a special, empty value called `NULL`. `NULL` simply means "pointing to absolutely nothing." You should always check if your pointer equals `NULL` after using `malloc`. If you try to use `NULL` as a valid memory address, the program cannot operate safely and may crash.

### `free`

Whenever you use `malloc` to grab memory, you are only borrowing it. The computer will never take it back automatically. When you are done using that space—such as when your old array gets full and you move your data into a newer, bigger one—you must use `free()` to give the old memory back to the computer. If you forget to free memory that is no longer needed, the program wastes memory for as long as it continues running. This is called a memory leak.

## C Code

### Saving Data in an Array

```c
/* Allocate Memory */
int array[10];
int array_capacity = 10;


/* Choose Position */
int pos = 0;

/* Save Data */
array[pos] = 100;

/* Update Count */
int size = 1;


/* Choose Position */
pos = pos + 1;

/* Save Data */
array[pos] = 200;

/* Update Count */
size = size + 1;


/* Choose Position */
pos = pos + 1;

/* Save Data */
array[pos] = 300;

/* Update Count */
size = size + 1;

```

### Reading or Changing Data at a Specific Number

```c
pos = 1;

/* Check Number */
if (pos >= 0 && pos < size) {
        
        /* Read Data */
        int data = array[pos];

        /* Change Data */
        array[pos] = 500;
}

```

### Deleting Data at a Specific Number

```c
/* Check Number */
if (pos >= 0 && pos < size) {

        /* Pull Data Forward */
        for (int i = pos + 1; i < size; i = i + 1) {
                array[i - 1] = array[i];
        }

        /* Decrease Count */
        size = size - 1;
}

```

### Adding Data to a Specific Number

```c
/* Check Number */
if (pos >= 0 && pos <= size && size < array_capacity) {

        /* Push Data Back */
        for (int i = size - 1; i >= pos; i = i - 1) {
                array[i + 1] = array[i];
        }

        /* Save Data */
        array[pos] = 600;

        /* Increase Count */
        size = size + 1;
}

```

### Making a Dynamic Array

```c
#include <stdlib.h>

int arrayList_capacity = 6;
int *arrayList = malloc(sizeof(int) * arrayList_capacity);

if (arrayList == NULL) {
        exit(1);
}

for (int i = 0; i < arrayList_capacity; i = i + 1) {
        arrayList[i] = i * 100;
}

int arrayList_size = arrayList_capacity; /* Situation where the space is totally full */

```

### Expanding the Memory Space of a Dynamic Array

```c
/* Create Space */
int new_capacity = arrayList_capacity * 2;
int *new_array = malloc(sizeof(int) * new_capacity);

if (new_array != NULL) {

        /* Transfer Data */
        for (int i = 0; i < arrayList_size; i = i + 1) {
                new_array[i] = arrayList[i];
        }

        /* Clean Up Old Space */
        int *old_array = arrayList;
        arrayList = new_array;
        arrayList_capacity = new_capacity;
        free(old_array);
}

```

### Releasing the Entire Dynamic Array

```c
/* Free the allocated memory */
free(arrayList);

/* Reset variables to prevent dangling pointers and logic errors */
arrayList = NULL;
arrayList_size = 0;
arrayList_capacity = 0;
```

## Why Double the Memory Space?

### The Problem with Adding Just a Little Space

Imagine you are moving to a new house because your current one is completely full. Packing up all your furniture and moving it is exhausting and takes a lot of time. In a computer, copying every single piece of data from the old memory space to a new one is exactly like this—it is a slow, heavy task.

If you only increase your memory space by one extra spot, you will run out of room the very next time you want to add an item. This means you have to pack up and move all your data over and over again, every single time you add something new. The computer would become incredibly slow.

### The "Doubling" Solution

Instead of adding just a little bit of space, we ask the computer for a space that is twice as big as the old one.

Moving all your old data to this new, double-sized space still takes some effort. However, because you now have so much extra room, you can add many, many new items instantly without having to move again. The bigger your array gets, the longer you can wait before you have to do another big move.

Doubling is a common design choice because it provides a practical balance between unused memory and repeated copying.
