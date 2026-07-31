# Representation Reveal — Label Before Growth

Open this file only when the instructor releases the representation.

## 1. Label the fields

```c
typedef struct {
    int *data;        // _____________________________________________
    size_t size;      // _____________________________________________
    size_t capacity;  // _____________________________________________
} IntList;
```

Match each field to one fact in your initial model. If your model used a
different fact, preserve it and add a correction.

## 2. Interpret two states

### State E

```text
data = NULL
size = 0
capacity = 0
```

Describe the allocation and logical elements:

____________________________________________________________________

### State A

```text
data = address A
size = 3
capacity = 4
allocation A = [11, 22, 33, unused]
```

Which slots are logical elements? ___________________________________

Which slot is owned but not a logical element? ______________________

Which field sets the valid-index boundary for clients? ______________

## 3. Prepare for the Cognitive Pause

Add this alias to State A:

```c
int *alias = &list.data[1];
```

Record what `alias` refers to now. Do not predict growth until the Cognitive
Pause is released.

____________________________________________________________________
