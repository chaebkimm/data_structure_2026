#include "tree_bfs.h"
#include "tree_work_queue.h"

static TreeBfsStatus map_queue_failure(TreeWorkQueueStatus status)
{
    if (status == WORK_QUEUE_LIMIT) {
        return TREE_BFS_LIMIT;
    }

    return TREE_BFS_INVALID_ARGUMENT;
}

static TreeBfsStatus enqueue_child(
    TreeWorkQueue *queue,
    const TreeNode *child,
    size_t depth
)
{
    TreeWorkItem item;
    TreeWorkQueueStatus status;

    if (child == NULL) {
        return TREE_BFS_OK;
    }

    item.node = child;
    item.depth = depth;
    status = tree_work_queue_enqueue(queue, item);
    return status == WORK_QUEUE_OK
        ? TREE_BFS_OK
        : map_queue_failure(status);
}

static TreeBfsStatus enqueue_children(
    TreeWorkQueue *queue,
    const TreeWorkItem *parent
)
{
    TreeBfsStatus status;
    size_t child_depth = parent->depth + 1U;

    status = enqueue_child(queue, parent->node->left, child_depth);
    if (status != TREE_BFS_OK) {
        return status;
    }

    return enqueue_child(queue, parent->node->right, child_depth);
}

TreeBfsStatus tree_level_order(
    const TreeNode *root,
    size_t queue_limit,
    TreeBfsOrder *out_order
)
{
    TreeWorkQueue queue = {0};
    TreeBfsOrder candidate = {0};
    TreeWorkQueueStatus queue_status;
    TreeBfsStatus status;

    if (out_order == NULL) {
        return TREE_BFS_INVALID_ARGUMENT;
    }

    queue_status = tree_work_queue_init(&queue, queue_limit);
    if (queue_status != WORK_QUEUE_OK) {
        return map_queue_failure(queue_status);
    }

    if (root != NULL) {
        TreeWorkItem root_item = {root, 0U};

        queue_status = tree_work_queue_enqueue(&queue, root_item);
        if (queue_status != WORK_QUEUE_OK) {
            return map_queue_failure(queue_status);
        }
    }

    for (;;) {
        TreeWorkItem item;

        queue_status = tree_work_queue_dequeue(&queue, &item);
        if (queue_status == WORK_QUEUE_UNDERFLOW) {
            break;
        }
        if (queue_status != WORK_QUEUE_OK) {
            return map_queue_failure(queue_status);
        }

        if (candidate.count == (size_t)TREE_BFS_MAX_NODES) {
            return TREE_BFS_LIMIT;
        }

        candidate.items[candidate.count].key = item.node->key;
        candidate.items[candidate.count].flagged = item.node->flagged;
        candidate.items[candidate.count].depth = item.depth;
        candidate.count += 1U;

        status = enqueue_children(&queue, &item);
        if (status != TREE_BFS_OK) {
            return status;
        }
    }

    *out_order = candidate;
    return TREE_BFS_OK;
}

TreeBfsStatus tree_find_shallowest(
    const TreeNode *root,
    int target,
    size_t queue_limit,
    TreeBfsMatch *out_match
)
{
    TreeWorkQueue queue = {0};
    TreeWorkQueueStatus queue_status;
    size_t reached = 0U;
    TreeBfsStatus status;

    if (out_match == NULL) {
        return TREE_BFS_INVALID_ARGUMENT;
    }

    queue_status = tree_work_queue_init(&queue, queue_limit);
    if (queue_status != WORK_QUEUE_OK) {
        return map_queue_failure(queue_status);
    }

    if (root != NULL) {
        TreeWorkItem root_item = {root, 0U};

        queue_status = tree_work_queue_enqueue(&queue, root_item);
        if (queue_status != WORK_QUEUE_OK) {
            return map_queue_failure(queue_status);
        }
    }

    for (;;) {
        TreeWorkItem item;

        queue_status = tree_work_queue_dequeue(&queue, &item);
        if (queue_status == WORK_QUEUE_UNDERFLOW) {
            return TREE_BFS_NOT_FOUND;
        }
        if (queue_status != WORK_QUEUE_OK) {
            return map_queue_failure(queue_status);
        }

        if (reached == (size_t)TREE_BFS_MAX_NODES) {
            return TREE_BFS_LIMIT;
        }
        reached += 1U;

        if (item.node->key == target) {
            TreeBfsMatch candidate = {item.node, item.depth};

            *out_match = candidate;
            return TREE_BFS_OK;
        }

        status = enqueue_children(&queue, &item);
        if (status != TREE_BFS_OK) {
            return status;
        }
    }
}

TreeBfsStatus tree_height_bfs(
    const TreeNode *root,
    size_t queue_limit,
    int *out_height
)
{
    TreeWorkQueue queue = {0};
    TreeWorkQueueStatus queue_status;
    size_t reached = 0U;
    int candidate = -1;
    TreeBfsStatus status;

    if (out_height == NULL) {
        return TREE_BFS_INVALID_ARGUMENT;
    }

    queue_status = tree_work_queue_init(&queue, queue_limit);
    if (queue_status != WORK_QUEUE_OK) {
        return map_queue_failure(queue_status);
    }

    if (root != NULL) {
        TreeWorkItem root_item = {root, 0U};

        queue_status = tree_work_queue_enqueue(&queue, root_item);
        if (queue_status != WORK_QUEUE_OK) {
            return map_queue_failure(queue_status);
        }
    }

    for (;;) {
        TreeWorkItem item;

        queue_status = tree_work_queue_dequeue(&queue, &item);
        if (queue_status == WORK_QUEUE_UNDERFLOW) {
            break;
        }
        if (queue_status != WORK_QUEUE_OK) {
            return map_queue_failure(queue_status);
        }

        if (reached == (size_t)TREE_BFS_MAX_NODES) {
            return TREE_BFS_LIMIT;
        }
        reached += 1U;
        candidate = (int)item.depth;

        status = enqueue_children(&queue, &item);
        if (status != TREE_BFS_OK) {
            return status;
        }
    }

    *out_height = candidate;
    return TREE_BFS_OK;
}
