#ifndef TREE_BFS_H
#define TREE_BFS_H

#include <stdbool.h>
#include <stddef.h>

#define TREE_BFS_MAX_NODES 64U

/*
 * This is the same binary-node shape used in Module 5. Module 8 accepts a
 * general binary tree, so equal keys are allowed in instructor-built trees.
 * The strict-BST insertion helper below still rejects equal keys.
 */
typedef struct TreeNode {
    int key;
    bool flagged;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct {
    int key;
    bool flagged;
    size_t depth;
} TreeBfsVisit;

typedef struct {
    TreeBfsVisit items[TREE_BFS_MAX_NODES];
    size_t count;
} TreeBfsOrder;

/*
 * node is a borrowed pointer into the caller-owned tree. The caller must keep
 * that tree alive while using the pointer.
 */
typedef struct {
    const TreeNode *node;
    size_t depth;
} TreeBfsMatch;

typedef enum {
    TREE_BFS_OK = 0,
    TREE_BFS_INVALID_ARGUMENT,
    TREE_BFS_LIMIT,
    TREE_BFS_ALLOCATION,
    TREE_BFS_DUPLICATE,
    TREE_BFS_NOT_FOUND
} TreeBfsStatus;

/*
 * Allocates one node. The output changes only on success.
 */
TreeBfsStatus tree_node_create(
    int key,
    bool flagged,
    TreeNode **out_node
);

/*
 * Releases exactly one node created by tree_node_create or tree_bst_insert.
 * It does not follow child links. Passing NULL is a no-op.
 */
void tree_node_release(TreeNode *node);

/*
 * Inserts into a strict binary search tree. A duplicate or allocation
 * failure leaves the tree unchanged.
 */
TreeBfsStatus tree_bst_insert(
    TreeNode **root,
    int key,
    bool flagged
);

/*
 * Releases a valid, uniquely owned tree in postorder and sets *root to NULL.
 * Every reachable node must have come from the allocation helpers above.
 */
TreeBfsStatus tree_destroy_postorder(TreeNode **root);

/*
 * Records nodes in nondecreasing depth. A processed node's non-NULL left
 * child is enqueued before its non-NULL right child.
 *
 * queue_limit may be zero and may not exceed 64. A NULL root succeeds with
 * an empty order even when queue_limit is zero. A nonempty tree with limit
 * zero returns TREE_BFS_LIMIT. Reaching a 65th node also returns that status.
 * On every failure, out_order is unchanged.
 *
 * The input must be a valid tree: finite, acyclic, and without a node shared
 * by two parent links. This operation never changes or owns tree nodes.
 */
TreeBfsStatus tree_level_order(
    const TreeNode *root,
    size_t queue_limit,
    TreeBfsOrder *out_order
);

/*
 * Returns the first matching key removed from the Queue. Therefore the match
 * is shallowest; equal-depth ties follow the left-before-right rule above.
 * A NULL root or missing key returns TREE_BFS_NOT_FOUND. The output changes
 * only on success. Search may succeed before inspecting the rest of a tree.
 */
TreeBfsStatus tree_find_shallowest(
    const TreeNode *root,
    int target,
    size_t queue_limit,
    TreeBfsMatch *out_match
);

/*
 * Computes edge height with BFS: height(NULL) is -1 and a leaf has height 0.
 * Queue limits and the valid-tree precondition match tree_level_order.
 * The output changes only on success.
 */
TreeBfsStatus tree_height_bfs(
    const TreeNode *root,
    size_t queue_limit,
    int *out_height
);

const char *tree_bfs_status_name(TreeBfsStatus status);

#ifdef TREE_BFS_TESTING
void tree_bfs_test_fail_next_node_allocation(void);
size_t tree_bfs_test_live_node_count(void);
#endif

#endif
