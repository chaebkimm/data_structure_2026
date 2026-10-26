# Optional open-addressed deletion autopsy

This is an extension for the older map library. The current required lab
uses linked chains and has no tombstones or per-key deletion operation.
Use [the source-based lab autopsy](../../student/hash_table_autopsy.md) for
Week 9.


`faulty_delete_empty.c` is a standalone, bounded demonstration. Three keys
share one home index. The faulty deletion marks the middle slot `EMPTY`, so
lookup stops before a later colliding key. The repaired copy uses `DELETED`
and remains searchable.

The program performs no allocation, accepts no input, and never links into
the hash-table implementation or its normal tests.
