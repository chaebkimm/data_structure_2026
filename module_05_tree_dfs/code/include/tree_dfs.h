#ifndef TREE_DFS_H
#define TREE_DFS_H

#include <stdbool.h>
#include <stddef.h>

/*
 * A tree node stores one key, one teaching flag, and links to at most two
 * children. A child link is NULL when that child is absent.
 */
#define TREE_DFS_MAX_NODES 64U

typedef struct TreeNode {
    int key;
    bool flagged;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct {
    int key;
    bool flagged;
} TreeVisit;

typedef struct {
    TreeVisit items[TREE_DFS_MAX_NODES];
    size_t count;
} TreeOrder;

/* A status is a named result returned by an operation. */
typedef enum {
    TREE_DFS_OK = 0,
    TREE_DFS_INVALID_ARGUMENT,
    TREE_DFS_LIMIT,
    TREE_DFS_ALLOCATION,
    TREE_DFS_DUPLICATE,
    TREE_DFS_NOT_FOUND
} TreeDfsStatus;

/*
 * Allocates one node whose child links initially are NULL. The output changes
 * only on success.
 */
TreeDfsStatus tree_node_create(
    int key,
    bool flagged,
    TreeNode **out_node
);

/*
 * Releases exactly one node created by tree_node_create. It does not follow
 * child links. The caller must ensure the node will not be accessed again.
 * Passing NULL is a no-op.
 */
void tree_node_release(TreeNode *node);

/*
 * Inserts one key into a strict binary search tree (BST). "Strict" means
 * every key is unique: smaller keys go left and larger keys go right.
 * A duplicate or allocation failure leaves the tree unchanged.
 */
TreeDfsStatus tree_bst_insert(
    TreeNode **root,
    int key,
    bool flagged
);

/*
 * Records every visited node as both key and flag. NULL root means an empty
 * traversal. Reaching a 65th non-NULL node returns TREE_DFS_LIMIT, including
 * for orders that would record that node later. On every failure, out_order
 * is unchanged.
 *
 * These functions assume a valid tree: it is acyclic and no node is shared
 * by two parent links.
 */
TreeDfsStatus tree_preorder_recursive(
    const TreeNode *root,
    TreeOrder *out_order
);

TreeDfsStatus tree_inorder_recursive(
    const TreeNode *root,
    TreeOrder *out_order
);

TreeDfsStatus tree_postorder_recursive(
    const TreeNode *root,
    TreeOrder *out_order
);

/*
 * Performs preorder without recursion by using the typed node-pointer Stack.
 * stack_limit may be zero and may not exceed TREE_DFS_MAX_NODES.
 */
TreeDfsStatus tree_preorder_iterative(
    const TreeNode *root,
    size_t stack_limit,
    TreeOrder *out_order
);

/*
 * Searches a valid strict BST. A missing key returns TREE_DFS_NOT_FOUND.
 * out_node changes only when the key is found.
 */
TreeDfsStatus tree_bst_search(
    const TreeNode *root,
    int target,
    const TreeNode **out_node
);

/*
 * Releases a whole valid, uniquely owned tree in postorder and sets *root
 * to NULL. Every reachable node must have been allocated by tree_node_create
 * or tree_bst_insert. Child links must be acyclic and unshared. Do not pass
 * nodes declared as ordinary local variables or array elements. This
 * recursive operation also requires a height that fits the available C
 * runtime call stack.
 *
 * Passing a NULL pointer-to-root is an invalid argument. An already empty
 * tree succeeds.
 */
TreeDfsStatus tree_destroy_postorder(TreeNode **root);

const char *tree_dfs_status_name(TreeDfsStatus status);

#ifdef TREE_DFS_TESTING
/* Public-test seams. Normal builds do not expose these functions. */
void tree_dfs_test_fail_next_node_allocation(void);
size_t tree_dfs_test_live_node_count(void);
#endif

#endif
