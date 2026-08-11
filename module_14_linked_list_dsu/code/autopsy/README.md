# Isolated Linked-Deletion Autopsy

The clinic starts with the canonical three-node chain:

```text
R(17) -> Q(23) -> P(31)
```

It removes the middle node `Q`, so `previous` points to `R` and `victim`
points to `Q`. `faulty_linked_delete.c` contains one intentional
use-after-free:

```c
free(victim);
previous->next = victim->next;
```

After `free(victim)`, the program no longer owns the node, so reading its
`next` field is invalid. The safe order is:

1. save `victim->next` while the node is live;
2. set `previous->next` to that saved address;
3. free the victim exactly once.

This source is never linked into the list, DSU, edge-list, or normal test
targets. The ordinary `autopsy` target defines `AUTOPSY_INSPECT_ONLY`; it
describes the defect and cleans up safely without executing undefined
behavior.

The `autopsy-unsafe` target compiles the actual defect with AddressSanitizer
and UndefinedBehaviorSanitizer when supported, but deliberately does not run
it. Run that binary only in an instructor-controlled disposable environment.
Sanitizers should identify the single `victim->next` read after `free`.
