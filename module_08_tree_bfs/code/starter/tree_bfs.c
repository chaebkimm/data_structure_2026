#include "tree_bfs.h"
#include "tree_work_queue.h"

/*
 * TODO 1: Use TreeWorkQueue to record every node in level order. Remove one
 * node, record its key, flag, and depth, then enqueue left before right.
 * Build a local candidate and copy it to out_order only after full success.
 */
TreeBfsStatus tree_level_order(
    const TreeNode *root,
    size_t queue_limit,
    TreeBfsOrder *out_order
)
{
    (void)root;
    (void)queue_limit;

    if (out_order == NULL) {
        return TREE_BFS_INVALID_ARGUMENT;
    }

    return TREE_BFS_NOT_FOUND;
}

/*
 * TODO 2: Search with the same Queue rule. Check a node for target only
 * after removing it. Stop at the first match and commit both output fields
 * together. A missing target and every failure must preserve out_match.
 */
TreeBfsStatus tree_find_shallowest(
    const TreeNode *root,
    int target,
    size_t queue_limit,
    TreeBfsMatch *out_match
)
{
    (void)root;
    (void)target;
    (void)queue_limit;

    if (out_match == NULL) {
        return TREE_BFS_INVALID_ARGUMENT;
    }

    return TREE_BFS_NOT_FOUND;
}

/*
 * TODO 3: Traverse with the Queue while tracking the depth most recently
 * removed. Empty height is -1. Commit out_height only after success, and
 * apply the same Queue and 64-node limits as the other operations.
 */
TreeBfsStatus tree_height_bfs(
    const TreeNode *root,
    size_t queue_limit,
    int *out_height
)
{
    (void)root;
    (void)queue_limit;

    if (out_height == NULL) {
        return TREE_BFS_INVALID_ARGUMENT;
    }

    return TREE_BFS_NOT_FOUND;
}
