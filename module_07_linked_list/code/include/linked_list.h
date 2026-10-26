#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>

#define LINKED_LIST_MAX_NODES 16U

/*
 * A node stores one value and the address of the next node. NULL means that
 * there is no next node.
 */
typedef struct LinkedNode {
    int value;
    struct LinkedNode *next;
} LinkedNode;

/*
 * The list owns every node reachable from head. Live nodes must not be
 * freed by callers or shared with another LinkedList.
 */
typedef struct {
    LinkedNode *head;
    size_t size;
    size_t limit;
} LinkedList;

typedef enum {
    LINKED_LIST_OK = 0,
    LINKED_LIST_INVALID_ARGUMENT,
    LINKED_LIST_OUT_OF_RANGE,
    LINKED_LIST_FULL,
    LINKED_LIST_ALLOCATION,
    LINKED_LIST_INVALID_STATE
} LinkedListStatus;

/*
 * Initializes an uninitialized automatic object or a previously destroyed
 * list. limit may be zero through LINKED_LIST_MAX_NODES. Do not reinitialize
 * a live list: init cannot portably discover and release hidden ownership.
 * Every reported failure preserves the receiver.
 */
LinkedListStatus linked_list_init(LinkedList *list, size_t limit);

/*
 * Checks the complete bounded representation. A valid list has exactly size
 * distinct reachable nodes followed by NULL, and head is NULL exactly when
 * size is zero.
 *
 * This diagnostic accepts NULL and returns false. Like every C pointer
 * checker, it cannot make an arbitrary or dangling pointer safe to read.
 */
bool linked_list_is_valid(const LinkedList *list);

/*
 * Reports the value at a zero-based position. out_value must be separate
 * caller-owned storage outside the list object and its nodes. Failure
 * preserves out_value.
 */
LinkedListStatus linked_list_get(
    const LinkedList *list,
    size_t index,
    int *out_value
);

/*
 * Allocates one node and makes it the new head. Full and allocation failures
 * preserve the complete list.
 */
LinkedListStatus linked_list_push_front(LinkedList *list, int value);

/*
 * Removes only the first matching value. An absent value is not an error:
 * the function returns OK, writes false, and leaves the topology unchanged.
 * out_removed must be caller-owned storage outside the list and its nodes.
 * Every error preserves both the list and out_removed.
 */
LinkedListStatus linked_list_remove_first(
    LinkedList *list,
    int value,
    bool *out_removed
);

/*
 * Releases every owned node and restores the exact all-zero state. Passing
 * NULL and repeating destroy are safe. Every non-NULL input must be a valid
 * initialized or already destroyed list.
 */
void linked_list_destroy(LinkedList *list);

const char *linked_list_status_name(LinkedListStatus status);

#ifdef LINKED_LIST_TESTING
/* Makes the next attempted node allocation fail once. */
void linked_list_test_fail_next_allocation(void);

/* Reports successful node allocations that have not yet been released. */
size_t linked_list_test_live_node_count(void);
#endif

#endif
