#ifndef TREE_ARENA_H
#define TREE_ARENA_H

#include <stdbool.h>
#include <stddef.h>

#define TREE_ARENA_MAX_NODES 32U
#define TREE_NO_INDEX ((size_t)-1)

/*
 * A node stores one key and up to two child addresses.
 * NULL means that a child is absent.
 */
typedef struct TreeNode {
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

/*
 * An arena is a caller-owned, fixed group of nodes. This module never
 * allocates, resizes, or frees that storage.
 */
typedef struct {
    TreeNode *nodes;
    size_t count;
    TreeNode *root;
} TreeArena;

/*
 * An enum is a C type limited to named choices. TreeStatus reports success
 * or the reason a checked operation failed.
 */
typedef enum {
    TREE_OK = 0,
    TREE_ERR_INVALID_ARGUMENT,
    TREE_ERR_OUT_OF_RANGE,
    TREE_ERR_OCCUPIED,
    TREE_ERR_SELF_LINK,
    TREE_ERR_INVALID_STRUCTURE,
    TREE_ERR_NOT_BST
} TreeStatus;

/* TreeSide names the two child positions accepted by tree_assign_child. */
typedef enum {
    TREE_SIDE_LEFT = 0,
    TREE_SIDE_RIGHT
} TreeSide;

/*
 * Each field is an index into arena->nodes. TREE_NO_INDEX means that the
 * requested relative is absent.
 */
typedef struct {
    size_t parent_index;
    size_t left_child_index;
    size_t right_child_index;
} TreeFamily;

/*
 * In a parameter, const promises that the function will not change an object
 * through that pointer. Names beginning with out_ identify results written
 * into caller-provided variables.
 */

/*
 * Copies key_count keys into caller-owned storage and clears every child
 * link. storage must point to at least key_count TreeNode objects and must
 * remain alive while arena is used. The active limit is 32 nodes.
 *
 * For an empty tree, pass key_count 0 and root_index TREE_NO_INDEX; storage
 * and keys may then be NULL. On failure, arena and storage are unchanged.
 */
TreeStatus tree_arena_init(
    TreeArena *arena,
    TreeNode *storage,
    const int *keys,
    size_t key_count,
    size_t root_index
);

/*
 * Checked node queries. The output is changed only when TREE_OK is returned.
 * These local queries count addresses; they do not prove a whole tree is
 * structurally valid.
 */
TreeStatus tree_node_is_leaf(
    const TreeNode *node,
    bool *out_is_leaf
);

TreeStatus tree_node_child_count(
    const TreeNode *node,
    size_t *out_child_count
);

/*
 * Fills one empty child position. Checks only this requested link: arguments,
 * indexes, an occupied position, and a direct self-link. Therefore TREE_OK
 * does not prove that the whole arena is a tree. Call
 * tree_validate_structure after a set of assignments.
 */
TreeStatus tree_assign_child(
    TreeArena *arena,
    size_t parent_index,
    TreeSide side,
    size_t child_index
);

/*
 * Verifies the whole-arena rules for this course's pure rooted binary tree:
 * every link stays inside the arena, the root has no parent, every other
 * node has exactly one parent, and every node is reachable from the root.
 * "Reachable" means that following child addresses from the root can arrive
 * at that node.
 */
TreeStatus tree_validate_structure(const TreeArena *arena);

/*
 * Reports a node's parent and children. The whole structure must first be a
 * valid tree, because an invalid structure may not have one clear parent.
 * The output is unchanged on failure.
 */
TreeStatus tree_immediate_family(
    const TreeArena *arena,
    size_t node_index,
    TreeFamily *out_family
);

/*
 * Verifies strict binary-search-tree (BST) ordering across entire subtrees.
 * A subtree is one node together with all nodes below it.
 * Every key in a left subtree must be lower; every key in a right subtree
 * must be higher. Equal keys are rejected. A valid tree with incorrect key
 * ordering returns TREE_ERR_NOT_BST.
 */
TreeStatus tree_validate_bst(const TreeArena *arena);

const char *tree_status_name(TreeStatus status);

#endif
