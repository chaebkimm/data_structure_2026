#ifndef TREE_NODE_STACK_H
#define TREE_NODE_STACK_H

#include "tree_dfs.h"

#include <stddef.h>

#define TREE_NODE_STACK_MAX_LIMIT 64U

/*
 * This Stack stores pointers to read-only TreeNode objects. It owns only its
 * growable pointer array; it never owns or releases the tree nodes.
 */
typedef struct {
    const TreeNode **data;
    size_t size;
    size_t capacity;
    size_t limit;
} TreeNodeStack;

typedef enum {
    NODE_STACK_OK = 0,
    NODE_STACK_INVALID_ARGUMENT,
    NODE_STACK_LIMIT,
    NODE_STACK_UNDERFLOW,
    NODE_STACK_ALLOCATION,
    NODE_STACK_INVALID_STATE
} NodeStackStatus;

/*
 * Creates an empty Stack. limit may be zero and may not exceed 64.
 * Call only for an uninitialized or previously destroyed object.
 * Failure leaves the object unchanged.
 */
NodeStackStatus tree_node_stack_init(
    TreeNodeStack *stack,
    size_t limit
);

NodeStackStatus tree_node_stack_validate(
    const TreeNodeStack *stack
);

/*
 * Push uses lazy geometric growth: 0, 4, 8, and so on, clipped to limit.
 * Every failure leaves the Stack unchanged.
 */
NodeStackStatus tree_node_stack_push(
    TreeNodeStack *stack,
    const TreeNode *node
);

/*
 * Pop changes the output only on success. out_node must not point into the
 * Stack's owned pointer array.
 */
NodeStackStatus tree_node_stack_pop(
    TreeNodeStack *stack,
    const TreeNode **out_node
);

/*
 * Releases only the owned pointer array and resets every field. NULL is a
 * no-op. The tree nodes themselves are untouched.
 */
void tree_node_stack_destroy(TreeNodeStack *stack);

const char *node_stack_status_name(NodeStackStatus status);

#ifdef TREE_DFS_TESTING
/* Makes the next pointer-array allocation attempt fail once. */
void tree_node_stack_test_fail_next_allocation(void);
#endif

#endif
