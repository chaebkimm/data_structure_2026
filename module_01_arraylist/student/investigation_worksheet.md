# Investigation Worksheet — Operations and Efficiency

Name: ____________________________
Date: ____________________________

Open this file after completing the Cognitive Pause.

## D. Keep the invariant

The allocated space contains:

```text
[10] [50] [20] [30] [ ] [ ]
```

1. State the golden rule for where stored items belong.

   _________________________________________________________________

2. Delete the item at index 1. Draw the final packed state.

   _________________________________________________________________

3. Why must deletion move later items to the left?

   _________________________________________________________________

4. Insert `99` at index 2. In what direction must existing items move?

   _________________________________________________________________

5. Why must insertion move items from the back toward the target position?

   _________________________________________________________________

## E. Compare operations

Complete each explanation without using timing symbols.

| Operation | Amount of work as stored data grows | Why? |
|---|---|---|
| Find by index | | |
| Find by value | | |
| Add at the end when space remains | | |
| Insert at the front | | |
| Delete at the end | | |
| Delete at the front | | |
| Expand the memory space | | |

## F. Explain doubling

1. Why would adding only one new slot cause repeated copying?

   _________________________________________________________________

2. Why does doubling make expansion happen less often?

   _________________________________________________________________

3. Across many additions, what happens to the average work for one addition?

   _________________________________________________________________

## G. Connect the idea to C

Match each C feature to its job.

| C feature | Job |
|---|---|
| `sizeof` | |
| pointer | |
| `malloc` | |
| `NULL` | |
| `free` | |

Put these expansion actions in order:

___ copy every stored item in the same order
___ obtain a larger memory space
___ release the old memory space
___ start using the new memory space
___ add the new item

## H. Exit ticket

1. Why can an index locate an item directly?

   _________________________________________________________________

2. Why does searching by value require checking items one by one?

   _________________________________________________________________

3. What condition means that expansion is required?

   _________________________________________________________________

4. What must happen before the old memory space is freed?

   _________________________________________________________________
