# Module 1 Vocabulary — Stage B Reference

Open this page after preserving the initial inquiry. These definitions use
the chapter’s fixed-capacity model.

| Term | Working definition |
|---|---|
| data | The values a computer processes and stores |
| data structure | A way of organizing data so it can be stored and used |
| contiguous memory | Neighboring memory positions in one continuous block |
| array | A fixed number of neighboring slots for values of one type |
| list | Data stored in a specific sequence |
| ArrayList | A list represented by an array; this module uses a fixed capacity |
| index | A slot number; C starts numbering at zero |
| element | One current item in the list |
| size | The number of current list items |
| capacity | The fixed usable list limit, no larger than the array’s declared length |
| unused slot | A position at or after `size` that is not a current list item |
| invariant | A rule every valid list state follows |
| append | Add an item immediately after the current final item |
| insertion | Place an item at a chosen list position and shift later items |
| deletion | Remove an item and shift later items to close the gap |
| compaction | Moving remaining items together so no gap remains in the list |
| linear search | Check current items from index 0 upward until a match is found |
| first match | The matching current item with the smallest index |
| bounds check | A check that an index lies within the permitted range |
| rejection | Leave the list unchanged because a request is not valid or cannot fit |
| metadata | The size and capacity values that describe the current list state |
| caller | The code that asks a function to run |
| return value | The result a function sends back to its caller |
| `const` | A qualifier stating that the search function does not change its array parameter |
