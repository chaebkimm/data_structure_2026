#ifndef BST_BASELINE_H
#define BST_BASELINE_H

#include "tree_model.h"

#include <stdbool.h>
#include <stddef.h>

/*
 * Checks the complete bounded representation: root/size agreement, no cycle
 * or shared node, strict whole-subtree ordering, and exact size. Cached
 * heights are deliberately ignored for the unbalanced BST baseline.
 */
bool tree_validate_bst(const Tree *tree);

/*
 * Recursively inserts one unique key without rebalancing. New leaves store
 * height 0; existing cached heights are deliberately not refreshed. The
 * caller supplies a valid BST; the operation performs only shallow and
 * bounded search-path checks so its cost remains O(h). Duplicate, full,
 * allocation, and detected invalid-state failures preserve the tree.
 */
TreeStatus bst_insert_baseline(Tree *tree, int key);

/*
 * Recursively searches a valid BST in O(h). A comparison is one visited node
 * whose key is compared with the query. The two output objects must not
 * overlap the tree, each other, or any tree node. Failure preserves both
 * outputs.
 */
TreeStatus bst_search(
    const Tree *tree,
    int key,
    bool *out_found,
    size_t *out_comparisons
);

#endif
