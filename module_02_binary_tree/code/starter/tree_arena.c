#include "tree_arena.h"

static bool tree_find_index(
    const TreeArena *arena,
    const TreeNode *node,
    size_t *out_index
)
{
    size_t index;

    if (arena == NULL || node == NULL || out_index == NULL) {
        return false;
    }

    for (index = 0U; index < arena->count; ++index) {
        if (node == &arena->nodes[index]) {
            *out_index = index;
            return true;
        }
    }

    return false;
}

static TreeStatus tree_check_arena_container(const TreeArena *arena)
{
    size_t root_index;

    if (arena == NULL) {
        return TREE_ERR_INVALID_ARGUMENT;
    }

    if (arena->count > (size_t)TREE_ARENA_MAX_NODES) {
        return TREE_ERR_INVALID_STRUCTURE;
    }

    if (arena->count == 0U) {
        return arena->nodes == NULL && arena->root == NULL
            ? TREE_OK
            : TREE_ERR_INVALID_STRUCTURE;
    }

    if (arena->nodes == NULL || arena->root == NULL) {
        return TREE_ERR_INVALID_STRUCTURE;
    }

    if (!tree_find_index(arena, arena->root, &root_index)) {
        return TREE_ERR_INVALID_STRUCTURE;
    }

    return TREE_OK;
}

TreeStatus tree_arena_init(
    TreeArena *arena,
    TreeNode *storage,
    const int *keys,
    size_t key_count,
    size_t root_index
)
{
    size_t index;

    if (arena == NULL) {
        return TREE_ERR_INVALID_ARGUMENT;
    }

    if (key_count > (size_t)TREE_ARENA_MAX_NODES) {
        return TREE_ERR_OUT_OF_RANGE;
    }

    if (key_count == 0U) {
        if (root_index != TREE_NO_INDEX) {
            return TREE_ERR_OUT_OF_RANGE;
        }

        arena->nodes = NULL;
        arena->count = 0U;
        arena->root = NULL;
        return TREE_OK;
    }

    if (storage == NULL || keys == NULL) {
        return TREE_ERR_INVALID_ARGUMENT;
    }

    if (root_index >= key_count) {
        return TREE_ERR_OUT_OF_RANGE;
    }

    for (index = 0U; index < key_count; ++index) {
        storage[index].key = keys[index];
        storage[index].left = NULL;
        storage[index].right = NULL;
    }

    arena->nodes = storage;
    arena->count = key_count;
    arena->root = &storage[root_index];
    return TREE_OK;
}

TreeStatus tree_node_is_leaf(
    const TreeNode *node,
    bool *out_is_leaf
)
{
    if (node == NULL || out_is_leaf == NULL) {
        return TREE_ERR_INVALID_ARGUMENT;
    }

    /*
     * TODO(core): A leaf has no left child and no right child.
     * Store the answer in out_is_leaf, then return TREE_OK.
     */
    return TREE_ERR_INVALID_STRUCTURE;
}

TreeStatus tree_node_child_count(
    const TreeNode *node,
    size_t *out_child_count
)
{
    size_t result = 0U;

    if (node == NULL || out_child_count == NULL) {
        return TREE_ERR_INVALID_ARGUMENT;
    }

    /*
     * TODO(core): Add one for each non-NULL child address.
     * Assign result to out_child_count only after the count is complete.
     */
    (void)result;
    return TREE_ERR_INVALID_STRUCTURE;
}

TreeStatus tree_assign_child(
    TreeArena *arena,
    size_t parent_index,
    TreeSide side,
    size_t child_index
)
{
    TreeStatus status;

    status = tree_check_arena_container(arena);
    if (status != TREE_OK) {
        return status;
    }

    if (side != TREE_SIDE_LEFT && side != TREE_SIDE_RIGHT) {
        return TREE_ERR_INVALID_ARGUMENT;
    }

    if (parent_index >= arena->count || child_index >= arena->count) {
        return TREE_ERR_OUT_OF_RANGE;
    }

    if (parent_index == child_index) {
        return TREE_ERR_SELF_LINK;
    }

    if (side == TREE_SIDE_LEFT) {
        if (arena->nodes[parent_index].left != NULL) {
            return TREE_ERR_OCCUPIED;
        }

        /*
         * TODO(core): Store &arena->nodes[child_index] in this parent's
         * left field.
         */
    } else {
        if (arena->nodes[parent_index].right != NULL) {
            return TREE_ERR_OCCUPIED;
        }

        /*
         * TODO(core): Store &arena->nodes[child_index] in this parent's
         * right field.
         */
    }

    /*
     * TODO(core): After the selected field is assigned, return TREE_OK.
     *
     * Do not add a whole-tree search here. This function intentionally
     * performs local checks only; tree_validate_structure performs the
     * separate global check.
     */
    (void)child_index;
    return TREE_ERR_INVALID_STRUCTURE;
}

/*
 * Instructor-supplied whole-tree validator.
 * A traversal systematically visits nodes. Traversal is studied formally in
 * later modules; no edits are required here.
 */
TreeStatus tree_validate_structure(const TreeArena *arena)
{
    TreeStatus status;
    size_t incoming[TREE_ARENA_MAX_NODES] = { 0U };
    bool seen[TREE_ARENA_MAX_NODES] = { false };
    size_t pending[TREE_ARENA_MAX_NODES];
    size_t root_index;
    size_t index;
    size_t pending_count = 0U;
    size_t seen_count = 0U;

    status = tree_check_arena_container(arena);
    if (status != TREE_OK) {
        return status;
    }

    if (arena->count == 0U) {
        return TREE_OK;
    }

    if (!tree_find_index(arena, arena->root, &root_index)) {
        return TREE_ERR_INVALID_STRUCTURE;
    }

    for (index = 0U; index < arena->count; ++index) {
        const TreeNode *children[2];
        size_t child_number;

        children[0] = arena->nodes[index].left;
        children[1] = arena->nodes[index].right;

        for (child_number = 0U; child_number < 2U; ++child_number) {
            size_t child_index;

            if (children[child_number] == NULL) {
                continue;
            }

            if (!tree_find_index(
                    arena,
                    children[child_number],
                    &child_index
                )) {
                return TREE_ERR_INVALID_STRUCTURE;
            }

            incoming[child_index] += 1U;
            if (incoming[child_index] > 1U) {
                return TREE_ERR_INVALID_STRUCTURE;
            }
        }
    }

    if (incoming[root_index] != 0U) {
        return TREE_ERR_INVALID_STRUCTURE;
    }

    for (index = 0U; index < arena->count; ++index) {
        if (index != root_index && incoming[index] != 1U) {
            return TREE_ERR_INVALID_STRUCTURE;
        }
    }

    pending[pending_count] = root_index;
    pending_count += 1U;

    while (pending_count > 0U) {
        const TreeNode *children[2];
        size_t current_index;
        size_t child_number;

        pending_count -= 1U;
        current_index = pending[pending_count];
        if (seen[current_index]) {
            return TREE_ERR_INVALID_STRUCTURE;
        }

        seen[current_index] = true;
        seen_count += 1U;
        children[0] = arena->nodes[current_index].left;
        children[1] = arena->nodes[current_index].right;

        for (child_number = 0U; child_number < 2U; ++child_number) {
            size_t child_index;

            if (children[child_number] == NULL) {
                continue;
            }

            if (!tree_find_index(
                    arena,
                    children[child_number],
                    &child_index
                )) {
                return TREE_ERR_INVALID_STRUCTURE;
            }

            if (pending_count >= (size_t)TREE_ARENA_MAX_NODES) {
                return TREE_ERR_INVALID_STRUCTURE;
            }

            pending[pending_count] = child_index;
            pending_count += 1U;
        }
    }

    return seen_count == arena->count
        ? TREE_OK
        : TREE_ERR_INVALID_STRUCTURE;
}

TreeStatus tree_immediate_family(
    const TreeArena *arena,
    size_t node_index,
    TreeFamily *out_family
)
{
    TreeStatus status;
    TreeFamily result;
    size_t index;

    if (out_family == NULL) {
        return TREE_ERR_INVALID_ARGUMENT;
    }

    status = tree_validate_structure(arena);
    if (status != TREE_OK) {
        return status;
    }

    if (node_index >= arena->count) {
        return TREE_ERR_OUT_OF_RANGE;
    }

    result.parent_index = TREE_NO_INDEX;
    result.left_child_index = TREE_NO_INDEX;
    result.right_child_index = TREE_NO_INDEX;

    /*
     * TODO(guided):
     * 1. If the selected node has a left child, use tree_find_index to
     *    record that child's index in result.left_child_index.
     * 2. Do the same for the right child.
     * 3. In the loop below, detect the node whose left or right address
     *    equals &arena->nodes[node_index]. Record that node's index as
     *    result.parent_index and stop the loop.
     */
    for (index = 0U; index < arena->count; ++index) {
        /* TODO(guided): compare this node's two child addresses. */
        (void)index;
    }

    *out_family = result;
    return TREE_OK;
}

/*
 * Instructor-supplied strict BST validator.
 * It carries lower and upper limits into every subtree and rejects equality.
 */
typedef struct {
    size_t node_index;
    bool has_lower_bound;
    int lower_bound;
    bool has_upper_bound;
    int upper_bound;
} TreeBstCheck;

TreeStatus tree_validate_bst(const TreeArena *arena)
{
    TreeStatus status;
    TreeBstCheck pending[TREE_ARENA_MAX_NODES];
    size_t root_index;
    size_t pending_count = 0U;

    status = tree_validate_structure(arena);
    if (status != TREE_OK) {
        return status;
    }

    if (arena->count == 0U) {
        return TREE_OK;
    }

    if (!tree_find_index(arena, arena->root, &root_index)) {
        return TREE_ERR_INVALID_STRUCTURE;
    }

    pending[pending_count].node_index = root_index;
    pending[pending_count].has_lower_bound = false;
    pending[pending_count].lower_bound = 0;
    pending[pending_count].has_upper_bound = false;
    pending[pending_count].upper_bound = 0;
    pending_count += 1U;

    while (pending_count > 0U) {
        TreeBstCheck check;
        const TreeNode *node;

        pending_count -= 1U;
        check = pending[pending_count];
        node = &arena->nodes[check.node_index];

        if ((check.has_lower_bound && node->key <= check.lower_bound) ||
            (check.has_upper_bound && node->key >= check.upper_bound)) {
            return TREE_ERR_NOT_BST;
        }

        if (node->right != NULL) {
            size_t right_index;

            if (!tree_find_index(arena, node->right, &right_index) ||
                pending_count >= (size_t)TREE_ARENA_MAX_NODES) {
                return TREE_ERR_INVALID_STRUCTURE;
            }

            pending[pending_count].node_index = right_index;
            pending[pending_count].has_lower_bound = true;
            pending[pending_count].lower_bound = node->key;
            pending[pending_count].has_upper_bound =
                check.has_upper_bound;
            pending[pending_count].upper_bound = check.upper_bound;
            pending_count += 1U;
        }

        if (node->left != NULL) {
            size_t left_index;

            if (!tree_find_index(arena, node->left, &left_index) ||
                pending_count >= (size_t)TREE_ARENA_MAX_NODES) {
                return TREE_ERR_INVALID_STRUCTURE;
            }

            pending[pending_count].node_index = left_index;
            pending[pending_count].has_lower_bound =
                check.has_lower_bound;
            pending[pending_count].lower_bound = check.lower_bound;
            pending[pending_count].has_upper_bound = true;
            pending[pending_count].upper_bound = node->key;
            pending_count += 1U;
        }
    }

    return TREE_OK;
}

const char *tree_status_name(TreeStatus status)
{
    switch (status) {
        case TREE_OK:
            return "ok";
        case TREE_ERR_INVALID_ARGUMENT:
            return "invalid argument";
        case TREE_ERR_OUT_OF_RANGE:
            return "index or count out of range";
        case TREE_ERR_OCCUPIED:
            return "child position already occupied";
        case TREE_ERR_SELF_LINK:
            return "node cannot be its own direct child";
        case TREE_ERR_INVALID_STRUCTURE:
            return "arena does not satisfy the required tree rules";
        case TREE_ERR_NOT_BST:
            return "tree keys do not satisfy strict BST ordering";
        default:
            return "unknown TreeStatus";
    }
}
