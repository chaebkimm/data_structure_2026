#include "tree_dfs.h"

/*
 * TODO 1: copy original in preorder. Create the current node, then copy and
 * attach the left and right subtrees. Restore destination->used and preserve
 * out_copy if any recursive step fails.
 */
TreeDfsStatus tree_copy_preorder(
    const Node *original,
    NodePool *destination,
    Node **out_copy
)
{
    (void)original;
    if (destination == NULL || out_copy == NULL) {
        return TREE_DFS_INVALID_ARGUMENT;
    }
    return TREE_DFS_INVALID_EXPRESSION;
}

/*
 * TODO 2: format a valid addition-and-multiplication expression in inorder. Add
 * parentheses when a child operator would otherwise change the tree's
 * grouping. Return OUTPUT_TOO_SMALL rather than writing past the buffer.
 */
TreeDfsStatus tree_print_inorder(
    const Node *root,
    char *output,
    size_t output_capacity
)
{
    (void)root;
    if (output == NULL || output_capacity == 0U) {
        return TREE_DFS_INVALID_ARGUMENT;
    }
    output[0] = '\0';
    return TREE_DFS_INVALID_EXPRESSION;
}

/*
 * TODO 3: evaluate digits as leaves. Recursively obtain the left and right
 * values before applying + or *. Preserve out_value on every failure.
 */
TreeDfsStatus tree_evaluate_postorder(const Node *root, int *out_value)
{
    (void)root;
    if (out_value == NULL) return TREE_DFS_INVALID_ARGUMENT;
    return TREE_DFS_INVALID_EXPRESSION;
}
