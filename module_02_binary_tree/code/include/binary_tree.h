#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stddef.h>

struct TreeNode {
    /* An integer value or a character constant such as '+' or '*'. */
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

/*
 * Each non-NULL link must identify an initialized node object that remains
 * alive for the entire operation. Reachable nodes must form a finite,
 * acyclic tree with no shared child. These functions do not validate that
 * structure. When linking nodes directly, the caller must choose an empty
 * side and attach a fresh node or a disjoint subtree whose root is not
 * already linked elsewhere, without making a cycle.
 */

/*
 * Searches without changing any node. Preorder means current node first,
 * then the entire left subtree, then the right subtree. Returns the first
 * matching address, or NULL for an empty link or an absent target. Zero is
 * an ordinary data value, not an empty-node marker.
 */
struct TreeNode *tree_find(struct TreeNode *node, int target);

/*
 * Recursively sets every reachable node's data to 0 and both links to NULL.
 * NULL is a no-op. Node objects remain alive and may be inspected or
 * reinitialized afterward. An outside parent's link is not detached:
 * the caller must set that link to NULL when removing a child subtree.
 */
void tree_clear(struct TreeNode *node);

#endif
