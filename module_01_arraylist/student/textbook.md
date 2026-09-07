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
