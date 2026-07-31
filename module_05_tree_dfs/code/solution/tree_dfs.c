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

static TreeDfsStatus preorder_visit(
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

    status = append_visit(order, node);
    if (status != TREE_DFS_OK) {
        return status;
    }

    status = preorder_visit(node->left, order, seen);
    if (status != TREE_DFS_OK) {
        return status;
    }

    return preorder_visit(node->right, order, seen);
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

static TreeDfsStatus map_stack_failure(NodeStackStatus status)
{
    if (status == NODE_STACK_LIMIT) {
        return TREE_DFS_LIMIT;
    }
    if (status == NODE_STACK_ALLOCATION) {
        return TREE_DFS_ALLOCATION;
    }
    return TREE_DFS_INVALID_ARGUMENT;
}

TreeDfsStatus tree_preorder_iterative(
    const TreeNode *root,
    size_t stack_limit,
    TreeOrder *out_order
)
{
    TreeNodeStack stack;
    TreeOrder candidate = {0};
    NodeStackStatus stack_status;
    TreeDfsStatus status = TREE_DFS_OK;

    if (out_order == NULL) {
        return TREE_DFS_INVALID_ARGUMENT;
    }

    stack_status = tree_node_stack_init(&stack, stack_limit);
    if (stack_status != NODE_STACK_OK) {
        return map_stack_failure(stack_status);
    }

    if (root != NULL) {
        stack_status = tree_node_stack_push(&stack, root);
        if (stack_status != NODE_STACK_OK) {
            status = map_stack_failure(stack_status);
        }
    }

    while (status == TREE_DFS_OK) {
        const TreeNode *node = NULL;

        stack_status = tree_node_stack_pop(&stack, &node);
        if (stack_status == NODE_STACK_UNDERFLOW) {
            break;
        }
        if (stack_status != NODE_STACK_OK) {
            status = map_stack_failure(stack_status);
            break;
        }

        status = append_visit(&candidate, node);
        if (status != TREE_DFS_OK) {
            break;
        }

        if (node->right != NULL) {
            stack_status = tree_node_stack_push(&stack, node->right);
            if (stack_status != NODE_STACK_OK) {
                status = map_stack_failure(stack_status);
                break;
            }
        }

        if (node->left != NULL) {
            stack_status = tree_node_stack_push(&stack, node->left);
            if (stack_status != NODE_STACK_OK) {
                status = map_stack_failure(stack_status);
                break;
            }
        }
    }

    tree_node_stack_destroy(&stack);
    if (status == TREE_DFS_OK) {
        *out_order = candidate;
    }
    return status;
}

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
            current = current->left;
        } else if (target > current->key) {
            current = current->right;
        } else {
            *out_node = current;
            return TREE_DFS_OK;
        }
    }

    return TREE_DFS_NOT_FOUND;
}

static void destroy_nodes_postorder(TreeNode *node)
{
    if (node == NULL) {
        return;
    }

    destroy_nodes_postorder(node->left);
    destroy_nodes_postorder(node->right);
    tree_node_release(node);
}

TreeDfsStatus tree_destroy_postorder(TreeNode **root)
{
    if (root == NULL) {
        return TREE_DFS_INVALID_ARGUMENT;
    }

    destroy_nodes_postorder(*root);
    *root = NULL;
    return TREE_DFS_OK;
}
