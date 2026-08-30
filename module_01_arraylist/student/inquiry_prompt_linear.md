# Stage A — Initial Inquiry: Linear Accessible Format

This version has the same questions as the standard initial inquiry. It is
suitable for screen readers, keyboard navigation, speech input, or a
plain-text response.

Preserve each initial answer. Add a labeled correction later. Do not open
later-stage materials yet.

## Student information

Name:

Date:

## A. Distinguish the list from its storage

There are ten neighboring integer slots, numbered 0 through 9. These numbers
are indexes. The list contains 100 at index 0, 200 at index 1, and 300 at
index 2. Slots 3 through 9 are not part of the current list. “Unused” is a
description of a slot’s role, not a special integer value.

### A1. Index 1

Which value is stored at index 1?

Response:

### A2. List indexes

Which indexes belong to the current list?

Response:

### A3. Item count

How many values are in the list?

Response:

### A4. Maximum count

How many values can these ten slots hold at most?

Response:

### A5. Direct access

Could the program read index 2 without checking indexes 0 and 1 first?
Explain.

Response:

## B. Keep the data packed together

Consider these changes in order.

### B1. Remove 200

Which later value must move so the list has no gap?

Response:

### B2. Remaining list

State the remaining list and its new item count.

Response:

### B3. Insert 600

Insert 600 between 100 and 300. Which value must move before 600 can be
stored?

Response:

### B4. List order

Does this operation sort the numbers, or preserve the requested list order?
Explain.

Response:

## C. Decide what happens when the ten slots are full

The number of slots cannot change in this activity. All ten slots now belong
to the list, and a request arrives to add one more value.

### C1. Unsafe write

Why is writing at index 10 unsafe?

Response:

### C2. Report the result

What should the program report to the caller—the code requesting the
addition?

Response:

### C3. Preserve the state

Which values and count should remain unchanged when the request cannot be
completed?

Response:
