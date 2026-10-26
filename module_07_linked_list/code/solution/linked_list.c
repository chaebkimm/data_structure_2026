#include "linked_list.h"

#include <stdlib.h>

#ifdef LINKED_LIST_TESTING
static bool allocation_failure_armed = false;
static size_t live_node_count = 0U;

void linked_list_test_fail_next_allocation(void)
{
    allocation_failure_armed = true;
}

size_t linked_list_test_live_node_count(void)
{
    return live_node_count;
}
#endif

static LinkedNode *linked_node_allocate(void)
{
    LinkedNode *node;

#ifdef LINKED_LIST_TESTING
    if (allocation_failure_armed) {
        allocation_failure_armed = false;
        return NULL;
    }
#endif

    node = (LinkedNode *)malloc(sizeof *node);

#ifdef LINKED_LIST_TESTING
    if (node != NULL) {
        live_node_count += 1U;
    }
#endif

    return node;
}

static void linked_node_release(LinkedNode *node)
{
    if (node == NULL) {
        return;
    }

#ifdef LINKED_LIST_TESTING
    if (live_node_count > 0U) {
        live_node_count -= 1U;
    }
#endif

    free(node);
}

/*
 * This constant-time check supports O(1) push_front. The public bounded
 * validator remains available when a complete link scan is required.
 */
static bool linked_list_has_valid_shallow_shape(const LinkedList *list)
{
    if (list == NULL ||
        list->limit > (size_t)LINKED_LIST_MAX_NODES ||
        list->size > list->limit) {
        return false;
    }

    return (list->size == 0U) == (list->head == NULL);
}

LinkedListStatus linked_list_init(LinkedList *list, size_t limit)
{
    if (list == NULL) {
        return LINKED_LIST_INVALID_ARGUMENT;
    }
    if (limit > (size_t)LINKED_LIST_MAX_NODES) {
        return LINKED_LIST_OUT_OF_RANGE;
    }

    list->head = NULL;
    list->size = 0U;
    list->limit = limit;
    return LINKED_LIST_OK;
}

bool linked_list_is_valid(const LinkedList *list)
{
    const LinkedNode *current;
    size_t index;

    if (!linked_list_has_valid_shallow_shape(list)) {
        return false;
    }

    current = list->head;
    for (index = 0U; index < list->size; ++index) {
        if (current == NULL) {
            return false;
        }
        current = current->next;
    }

    return current == NULL;
}

LinkedListStatus linked_list_get(
    const LinkedList *list,
    size_t index,
    int *out_value
)
{
    const LinkedNode *current;
    size_t position;

    if (out_value == NULL || list == NULL) {
        return LINKED_LIST_INVALID_ARGUMENT;
    }
    if (!linked_list_is_valid(list)) {
        return LINKED_LIST_INVALID_STATE;
    }
    if (index >= list->size) {
        return LINKED_LIST_OUT_OF_RANGE;
    }

    current = list->head;
    for (position = 0U; position < index; ++position) {
        current = current->next;
    }

    *out_value = current->value;
    return LINKED_LIST_OK;
}

LinkedListStatus linked_list_push_front(LinkedList *list, int value)
{
    LinkedNode *new_node;

    if (list == NULL) {
        return LINKED_LIST_INVALID_ARGUMENT;
    }
    if (!linked_list_has_valid_shallow_shape(list)) {
        return LINKED_LIST_INVALID_STATE;
    }
    if (list->size == list->limit) {
        return LINKED_LIST_FULL;
    }

    new_node = linked_node_allocate();
    if (new_node == NULL) {
        return LINKED_LIST_ALLOCATION;
    }

    new_node->value = value;
    new_node->next = list->head;
    list->head = new_node;
    list->size += 1U;
    return LINKED_LIST_OK;
}

LinkedListStatus linked_list_remove_first(
    LinkedList *list,
    int value,
    bool *out_removed
)
{
    LinkedNode *current;
    LinkedNode *previous = NULL;

    if (out_removed == NULL || list == NULL) {
        return LINKED_LIST_INVALID_ARGUMENT;
    }
    if (!linked_list_is_valid(list)) {
        return LINKED_LIST_INVALID_STATE;
    }

    current = list->head;
    while (current != NULL && current->value != value) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        *out_removed = false;
        return LINKED_LIST_OK;
    }

    {
        LinkedNode *next = current->next;

        if (previous == NULL) {
            list->head = next;
        } else {
            previous->next = next;
        }
        linked_node_release(current);
        list->size -= 1U;
    }

    *out_removed = true;
    return LINKED_LIST_OK;
}

void linked_list_destroy(LinkedList *list)
{
    LinkedNode *current;

    if (list == NULL) {
        return;
    }

    current = list->head;
    while (current != NULL) {
        LinkedNode *next = current->next;

        linked_node_release(current);
        current = next;
    }

    list->head = NULL;
    list->size = 0U;
    list->limit = 0U;
}

const char *linked_list_status_name(LinkedListStatus status)
{
    switch (status) {
        case LINKED_LIST_OK:
            return "LINKED_LIST_OK";
        case LINKED_LIST_INVALID_ARGUMENT:
            return "LINKED_LIST_INVALID_ARGUMENT";
        case LINKED_LIST_OUT_OF_RANGE:
            return "LINKED_LIST_OUT_OF_RANGE";
        case LINKED_LIST_FULL:
            return "LINKED_LIST_FULL";
        case LINKED_LIST_ALLOCATION:
            return "LINKED_LIST_ALLOCATION";
        case LINKED_LIST_INVALID_STATE:
            return "LINKED_LIST_INVALID_STATE";
        default:
            return "LINKED_LIST_UNKNOWN_STATUS";
    }
}
