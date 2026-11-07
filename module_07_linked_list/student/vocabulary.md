# Chapter 7 Vocabulary — Organizing data with links

Keep your initial predictions before opening this reference. The first group follows the [textbook glossary](textbook.md#glossary); the later groups support the [workbook](class_material.md) and [lab](lab.md).

## Glossary / 용어 정리

### Node / 노드

One integer value together with the next node's index, stored in `struct Linked_Node`.

### Singly linked list / 단일 연결 리스트

A sequence in which each node records one successor; our lists have no cycles and end at `-1`.

### First node / 첫 노드

The node from which the list is accessed; the caller saves its index separately in a variable such as `first`.

### Predecessor / 선행 노드

The node immediately before another node in the list.

### Successor / 후속 노드

The node immediately after another node in the list.

### Traversal / 순회

Following successive `next` links until `-1`, checking the index before accessing a node.

### Cycle / 순환

A path of links that returns to a previously visited node.

### Node pool / 노드 풀

The fixed array `lnodes[CAPACITY]` of ten reusable nodes shared by its callers.

### Free list / 가용 리스트

The chain of available nodes reached from `free_head`; `free_head = -1` means no slot is available.

### Allocation / 할당

Taking a node out of the free list and assigning it to a caller; the caller checks its index before writing data.

### Detached node / 분리된 노드

An allocated node outside every chain, held by its caller with `next = -1`.

### Recycling / 반환

Returning an allocated, detached node to the free list exactly once.

### Ownership / 소유 책임

Responsibility for keeping a node in exactly one state: free, in one active list, or detached for a caller.

### Stale index / 이전 소유자의 인덱스

An index retained after returning a node, which no longer identifies the old caller's record.

### Stack / 스택

A structure that removes the most recently added value first: LIFO, or last in, first out. Here the caller adds and removes at `first`.

### Queue / 큐

A structure that removes the earliest added value first: FIFO, or first in, first out. Here it appends at `qtail` and removes at `qhead`.

### Enqueue / 큐에 넣기

Add an allocated, isolated node at the queue's tail.

### Dequeue / 큐에서 꺼내기

Remove the queue's head and return its isolated index; the caller reads the data and recycles the node.

## Representation and rules / 표현과 규칙

| Term | Meaning in this chapter |
| --- | --- |
| Node index / 노드 인덱스 | A physical slot from 0 through 9, distinct from its stored data. |
| Sentinel / 끝 표시 | Index `-1` means no node; it must not be used as an array subscript. A data value of `-1` is valid. |
| Invariant / 불변식 | A rule preserved after each complete operation. |
| Precondition / 사전 조건 | A condition the caller establishes before calling an operation. |
| Shared pool / 공유 풀 | Several disjoint lists take nodes from the same free list, each keeping its own first index. |
| Pool exhaustion / 풀 소진 | No slot is free, so allocation returns `-1` without changing state. |
| Missing return / 반환 누락 | An allocated, detached slot remains unavailable; losing its index prevents the caller from returning it. |
| Double recycling / 중복 반환 | Returning an already-free node, which can create a cycle in the free list. |
| Constant time / 상수 시간 | A fixed amount of work independent of the list's length. |
| Linear time / 선형 시간 | Work proportional to the number of nodes visited. |

## New C syntax / 새로운 C 문법

| Syntax | Meaning |
| --- | --- |
| `enum { CAPACITY = 10 };` | Gives the integer constant 10 a name used by the array declaration and loops. |
| Local `static` | Keeps a local variable's value between calls; `initialized` is set to 0 only once. |
| `(void)` parameters | Declares that a function takes no arguments. |
| `void` return type | Declares that a function returns no value; `return;` finishes it immediately. |
| `qhead = qtail = node;` | Assigns the same index to both queue endpoints. |
| `return qhead == -1;` | Returns 1 when empty and 0 otherwise. |

## Source names / 소스의 함수 이름

| Name | Operation and caller responsibility |
| --- | --- |
| `init_lnodes_pool()` | Connect the free list once; later calls preserve live state and do not reset the pool. |
| `new_lnode()` | Take a free node, set `next = -1`, retain its data, and return its index or `-1`. |
| `simple_link_lnode_to_prev(prev, node)` | Insert an allocated, isolated node after a valid, distinct non-queue predecessor. |
| `simple_delink_next_lnode_from_prev(prev)` | Bypass and isolate the successor, returning its index or `-1`; it does not recycle. |
| `free_lnode(node)` | Prepend an allocated, detached node to the free list; `-1` is a no-op. |
| `enqueue_lnode(node)` | Append an allocated, isolated index; `-1` is a no-op and the function returns no value. |
| `dequeue_lnode()` | Return the isolated oldest index or `-1` when empty; it does not recycle. |
| `is_empty_queue()` | Compare `qhead` with `-1`; correct queue state also makes `qtail = -1` when empty. |

These operations use the array pool. `free_lnode` does not call C's `free`, and no separate stack interface is supplied. The [lab source](lab.c) defines the executable names; presentation aliases are read-only teaching references.
