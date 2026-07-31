#ifndef TREE_MODEL_H
#define TREE_MODEL_H

#include <stddef.h>

#define BST_AVL_MAX_NODES 64U

/*
 * A node stores one unique search key, its cached edge height, and links to
 * at most two children. An edge height counts edges: NULL is -1 and a leaf
 * is 0.
 */
typedef struct TreeNode {
    int key;
    int height;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

/*
 * The tree owns every node reachable from root. Nodes may not be shared with
 * another Tree. size counts those reachable nodes.
 */
typedef struct {
    TreeNode *root;
    size_t size;
} Tree;

typedef enum {
    TREE_OK = 0,
    TREE_INVALID_ARGUMENT,
    TREE_FULL,
    TREE_DUPLICATE,
    TREE_ALLOCATION_FAILED,
    TREE_INVALID_STATE
} TreeStatus;

/*
 * Initializes an uninitialized automatic object or a destroyed Tree. Do not
 * reinitialize a live tree; destroy its owned nodes first.
 */
TreeStatus tree_init(Tree *tree);

/*
 * Supplied allocation helpers used by both insertion algorithms. A new node
 * has the requested key, height 0, and two NULL links. Failure preserves
 * out_node. Releasing NULL is safe.
 */
TreeStatus tree_node_create(int key, TreeNode **out_node);
void tree_node_release(TreeNode *node);

/*
 * Recursively measures actual edge height from links rather than reading
 * cached height fields. The input must be an acyclic, uniquely owned shape
 * with at most BST_AVL_MAX_NODES nodes.
 */
int tree_actual_height(const TreeNode *node);

/*
 * Iteratively releases every owned node and restores {NULL, 0}. Passing NULL
 * and repeating destruction are safe. Every other input must have an
 * acyclic, uniquely owned shape of at most BST_AVL_MAX_NODES nodes.
 */
void tree_destroy_iterative(Tree *tree);

const char *tree_status_name(TreeStatus status);

#ifdef TREE_TESTING
/* Makes the next attempted node allocation fail exactly once. */
void tree_test_fail_next_allocation(void);

/* Reports successful node allocations not yet released. */
size_t tree_test_live_node_count(void);
#endif

#endif
