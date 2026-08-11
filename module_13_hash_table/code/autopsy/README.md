# Hash-Table Delete Autopsy

`faulty_delete_empty.c` is a standalone, bounded demonstration. Three keys
share one home index. The faulty deletion marks the middle slot `EMPTY`, so
lookup stops before a later colliding key. The repaired copy uses `DELETED`
and remains searchable.

The program performs no allocation, accepts no input, and never links into
the hash-table implementation or its normal tests.
