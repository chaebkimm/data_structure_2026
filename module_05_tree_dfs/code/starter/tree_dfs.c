#include "tree_dfs.h"
#include "tree_node_stack.h"

static TreeDfsStatus append_visit(
    TreeOrder *order,
    const TreeNode *node
)
{
    if (order->count == (size_t)TREE_DFS_MAX_NODES) {
        return TREE_DFS_LIMIT;
    }

    order->items[order->count].key = node->key;
    order->items[order->count].flagged = node->flagged;
    order->count += 1U;
    return TREE_DFS_OK;
}

/*
 * Count a reached non-NULL node before following either child. This keeps
 * recursive descent bounded even when a traversal records the node later.
 */
static TreeDfsStatus count_reached_node(size_t *seen)
{
    if (*seen == (size_t)TREE_DFS_MAX_NODES) {
        return TREE_DFS_LIMIT;
    }

    *seen += 1U;
    return TREE_DFS_OK;
}

/*
 * TODO 1: finish root-left-right recursive preorder after the supplied
 * NULL and reached-node checks. Append this node, recurse left, then recurse
 * right. Pass along the same seen pointer and return any failure at once.
 */
static TreeDfsStatus preorder_visit(
    const TreeNode *root,
    TreeOrder *order,
    size_t *seen
)
{
    TreeDfsStatus status;

    if (root == NULL) {
        return TREE_DFS_OK;
    }

    status = count_reached_node(seen);
    if (status != TREE_DFS_OK) {
        return status;
    }

    (void)order;

    /* Placeholder only: NOT_FOUND is not a traversal result contract. */
    return TREE_DFS_NOT_FOUND;
}

TreeDfsStatus tree_preorder_recursive(
    const TreeNode *root,
    TreeOrder *out_order
)
{
    TreeOrder candidate = {0};
    size_t seen = 0U;
    TreeDfsStatus status;

    if (out_order == NULL) {
        return TREE_DFS_INVALID_ARGUMENT;
    }

    status = preorder_visit(root, &candidate, &seen);
    if (status == TREE_DFS_OK) {
        *out_order = candidate;
    }
    return status;
}

static TreeDfsStatus inorder_visit(
    const TreeNode *node,
    TreeOrder *order,
    size_t *seen
)
{
    TreeDfsStatus status;

    if (node == NULL) {
        return TREE_DFS_OK;
    }

    status = count_reached_node(seen);
    if (status != TREE_DFS_OK) {
        return status;
    }

    status = inorder_visit(node->left, order, seen);
    if (status != TREE_DFS_OK) {
        return status;
    }

    status = append_visit(order, node);
    if (status != TREE_DFS_OK) {
        return status;
    }

    return inorder_visit(node->right, order, seen);
}

TreeDfsStatus tree_inorder_recursive(
    const TreeNode *root,
    TreeOrder *out_order
)
{
    TreeOrder candidate = {0};
    size_t seen = 0U;
    TreeDfsStatus status;

    if (out_order == NULL) {
        return TREE_DFS_INVALID_ARGUMENT;
    }

    status = inorder_visit(root, &candidate, &seen);
    if (status == TREE_DFS_OK) {
        *out_order = candidate;
    }
    return status;
}

static TreeDfsStatus postorder_visit(
    const TreeNode *node,
    TreeOrder *order,
    size_t *seen
)
{
    TreeDfsStatus status;

    if (node == NULL) {
        return TREE_DFS_OK;
    }

    status = count_reached_node(seen);
    if (status != TREE_DFS_OK) {
        return status;
    }

    status = postorder_visit(node->left, order, seen);
    if (status != TREE_DFS_OK) {
        return status;
    }

    status = postorder_visit(node->right, order, seen);
    if (status != TREE_DFS_OK) {
        return status;
    }

    return append_visit(order, node);
}

TreeDfsStatus tree_postorder_recursive(
    const TreeNode *root,
    TreeOrder *out_order
)
{
    TreeOrder candidate = {0};
    size_t seen = 0U;
    TreeDfsStatus status;

    if (out_order == NULL) {
        return TREE_DFS_INVALID_ARGUMENT;
    }

    status = postorder_visit(root, &candidate, &seen);
    if (status == TREE_DFS_OK) {
        *out_order = candidate;
    }
    return status;
}

/*
 * TODO 2: implement iterative preorder with TreeNodeStack.
 * Do not inspect Stack fields. Pop until NODE_STACK_UNDERFLOW. Push the right
 * child before the left child so the left child is removed first.
 */
TreeDfsStatus tree_preorder_iterative(
    const TreeNode *root,
    size_t stack_limit,
    TreeOrder *out_order
)
{
    (void)root;
    (void)stack_limit;

    if (out_order == NULL) {
        return TREE_DFS_INVALID_ARGUMENT;
    }

    /* Placeholder only: NOT_FOUND is not a traversal result contract. */
    return TREE_DFS_NOT_FOUND;
}

/*
 * TODO 3: follow the scaffold: compare target with current->key, then move
 * left, move right, or report success. Preserve out_node when not found.
 */
TreeDfsStatus tree_bst_search(
    const TreeNode *root,
    int target,
    const TreeNode **out_node
)
{
    const TreeNode *current;

    if (out_node == NULL) {
        return TREE_DFS_INVALID_ARGUMENT;
    }

    current = root;
    while (current != NULL) {
        if (target < current->key) {
            /* TODO: move to the smaller-key child. */
            return TREE_DFS_NOT_FOUND;
        } else if (target > current->key) {
            /* TODO: move to the larger-key child. */
            return TREE_DFS_NOT_FOUND;
        } else {
            /* TODO: commit the found node to the output. */
            return TREE_DFS_NOT_FOUND;
        }
    }

    return TREE_DFS_NOT_FOUND;
}

/*
 * TODO 4: recursively destroy left, then right, then this node. Finally set
 * the caller's root to NULL. Use tree_node_release for each node.
 */
TreeDfsStatus tree_destroy_postorder(TreeNode **root)
{
    if (root == NULL) {
        return TREE_DFS_INVALID_ARGUMENT;
    }

    /* Placeholder only: NOT_FOUND is not a destroy result contract. */
    return TREE_DFS_NOT_FOUND;
}
