# Segfault Autopsy — Unsafe Growth

## Case

Analyze this fragment before running the supplied demonstration:

```c
list->data = realloc(
    list->data,
    list->capacity * 2 * sizeof *list->data
);
list->capacity *= 2;
list->data[list->size++] = value;
return true;
```

## Incident report

### 1. Trigger

Describe at least one starting state or allocator outcome that makes this code unsafe.

____________________________________________________________________

### 2. First invalid assumption

Do not report only the final crash. Identify the earliest assumption that stops being valid.

____________________________________________________________________

### 3. Memory state

Show the state immediately before and after the first invalid operation. Include:

- old allocation address;
- result returned by `realloc`;
- `data`;
- `size`;
- `capacity`;
- ownership of the old allocation.

____________________________________________________________________

### 4. Consequences

Check every consequence that can occur and explain:

- [ ] lost allocation/leak;
- [ ] `NULL` dereference or invalid write;
- [ ] capacity no longer describes owned storage;
- [ ] multiplication overflow;
- [ ] zero-capacity growth remains zero;
- [ ] size increases without a stored logical element.

Explanation:

____________________________________________________________________

### 5. Patch

Write pseudocode for a failure-atomic repair. Identify the commit point.

____________________________________________________________________

### 6. Regression tests

Write at least two tests that would distinguish the faulty and repaired versions.

1. _________________________________________________________________
2. _________________________________________________________________

### 7. Categorize the error

Label each discovered error as one or more of:

`bounds` · `arithmetic` · `allocation` · `ownership` · `ordering` · `invariant`

____________________________________________________________________

