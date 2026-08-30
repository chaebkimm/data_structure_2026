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

### How do we add data?

You can simply add new data to the very end of your existing data.

If you want to add data right in the middle, you must make sure all the data stays packed together without losing any values. First, shift the data at the target spot—and everything after it—backward by one space. Then, place your new data into the empty spot. After adding it, the final number of items goes up by one.

### What should we check when adding data?

Check that the insertion position is valid and that the array has room for one more item. The capacity is the number of available slots. The size is the number of items currently stored.

### What happens if the space is full?

Reject the addition and leave the stored values and size unchanged. This chapter uses a fixed array of ten integers. Deleting an item makes room for another item; the array itself does not become larger.

## Calculating Efficiency

### Memory Efficiency

The array reserves its full capacity even when only some slots are in use. An array of ten integers still has ten slots when the list contains only three items. The remaining slots are outside the current list.

### Efficiency of Adding Data

If you have leftover space and add an item to the very end, it is super fast because no other data needs to move. But if you add an item to the very front, you have to push all existing data back by one space. This means the amount of work increases based on how much data you have.

### Efficiency of Deleting Data

Deleting the very last item is instantly finished because there is nothing behind it to pull forward. But deleting the very first item means you have to shift everything else forward by one space, so the amount of work increases with the total number of items.

### Efficiency of Finding Data by its Number

Because the data items are placed right next to each other, if you just know its number, you can instantly calculate its exact position and find it.

### Efficiency of Finding Data by its Value

You have to check the items one by one, starting from the first one. If it is at the very front, you find it instantly. But if it is at the very end—or not there at all—you have to check absolutely everything. The work grows with the total amount of data.

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

### What happens if the invariant is broken?

Imagine you delete an item from the middle of your list but decide to skip the heavy work of shifting the remaining data. This breaks the golden rule, leaving an empty "hole" or gap in the middle of your memory space.

If you allow this to happen, the entire structure of the ArrayList breaks down in three major ways:

- Random Access Fails: The biggest advantage of an array is being able to instantly jump to an item using its number. But with a gap, the numbers no longer match the data's true order. In the example above, if you ask for the 3rd item (index 2), the computer will hand you an empty space instead of the number 40.

- Messy Code and Lost Speed: Every time you try to read, print, or search for data, you can no longer just breeze through the memory. Your code would have to constantly ask, "Wait, is this spot empty?" before doing anything. This extra checking destroys the elegant simplicity and speed of the list.

- Confusion with Size: If you have 4 items scattered across 5 memory slots, what is the "size" of your list? Does your size variable track the number of items (4), or the next available index at the very end (5)? Adding a new item to the end becomes confusing because you lose track of where the actual data ends.

By strictly enforcing the invariant—even when shifting data takes extra work—we guarantee that our data is always predictable, perfectly ordered, and instantly accessible.

## Coding Plan

### Saving Data in an Array

- Declare an Array: Choose a fixed capacity and set aside that many slots.
- Choose Position: Pick the very first number (spot) in the memory that doesn't have data saved in it yet.
- Save Data: Put your data into that chosen spot.
- Update Count: Increase the total count of your stored data.

### Reading or Changing Data at a Specific Number

- Check Number: Make sure the number you want actually has data saved in it.
- Read Value: Read what is saved at that number in the array.
- Change Value: Update or change the value saved at that number.

### Deleting Data at a Specific Number

- Check Number: Make sure the number actually has data saved in it.
- Pull Data Forward: Move everything that comes right after the deleted spot forward by one space, doing it one by one from front to back.
- Decrease Count: Decrease the total count of your data.

### Adding Data to a Specific Number

- Check Number: Make sure the spot connects to your existing data and fits perfectly inside your total memory size.
- Push Data Back: Starting from the very last item down to the spot where you want to add, push each item back by one space.
- Save Data: Put your new data into the freshly cleared spot.
- Increase Count: Increase the total count of your data.

If we start from the front and move the first item to the right, we will accidentally crush the item sitting in the next spot before it has a chance to move! Starting from the back ensures we move data into empty holes.

## New C Syntax Explained

### `[capacity]` (Creating an Array)

To create an array in C, you use square brackets `[]` immediately after the name of your variable. Inside these brackets, you write the exact number of items you want to store. For example, writing `int array[10];` tells the computer to set aside a single, continuous block of memory big enough to hold exactly 10 integers. Because this space is fixed, you must know the maximum capacity you need right from the start.

### `[index]` (Accessing Data)

Once the array is created, you use the square brackets again to look at or change the data inside it. You simply put the specific number (the index) of the item you want inside the brackets. In C, counting always starts at 0, not 1. Therefore, `array[0]` lets you access the very first item, `array[1]` accesses the second item, and so on.

## C Code

### Saving Data in an Array

```c
/* Declare Fixed Storage */
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
