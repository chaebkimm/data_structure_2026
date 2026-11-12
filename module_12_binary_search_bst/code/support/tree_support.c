#include "avl_tree.h"
#include "bst_baseline.h"
#include "tree_model.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {
    const TreeNode *seen[BST_AVL_MAX_NODES];
    size_t seen_count;
} ValidationState;

static bool fail_next_allocation = false;
static size_t live_node_count = 0U;

static int maximum_int(int left, int right)
{
    return left > right ? left : right;
}

static bool pointer_was_seen(
    const ValidationState *state,
    const TreeNode *node
)
{
    size_t index;

    for (index = 0U; index < state->seen_count; ++index) {
        if (state->seen[index] == node) {
            return true;
        }
    }
    return false;
}

static bool validate_bst_node(
    const TreeNode *node,
    bool has_lower,
    int lower,
    bool has_upper,
    int upper,
    ValidationState *state
)
{
    if (node == NULL) {
        return true;
    }
    if (state->seen_count >= (size_t)BST_AVL_MAX_NODES ||
        pointer_was_seen(state, node)) {
        return false;
    }
    if ((has_lower && node->key <= lower) ||
        (has_upper && node->key >= upper)) {
        return false;
    }

    state->seen[state->seen_count] = node;
    state->seen_count += 1U;

    return validate_bst_node(
        node->left,
        has_lower,
        lower,
        true,
        node->key,
        state
    ) && validate_bst_node(
        node->right,
        true,
        node->key,
        has_upper,
        upper,
        state
    );
}

static bool validate_avl_node(
    const TreeNode *node,
    bool has_lower,
    int lower,
    bool has_upper,
    int upper,
    ValidationState *state,
    int *out_height
)
{
    int left_height;
    int right_height;
    int actual_height;
    int balance;

    if (node == NULL) {
        *out_height = -1;
        return true;
    }
    if (state->seen_count >= (size_t)BST_AVL_MAX_NODES ||
        pointer_was_seen(state, node)) {
        return false;
    }
    if ((has_lower && node->key <= lower) ||
        (has_upper && node->key >= upper)) {
        return false;
    }

    state->seen[state->seen_count] = node;
    state->seen_count += 1U;

    if (!validate_avl_node(
            node->left,
            has_lower,
            lower,
            true,
            node->key,
            state,
            &left_height
        ) ||
        !validate_avl_node(
            node->right,
            true,
            node->key,
            has_upper,
            upper,
            state,
            &right_height
        )) {
        return false;
    }

    actual_height = 1 + maximum_int(left_height, right_height);
    balance = left_height - right_height;
    if (node->height != actual_height ||
        balance < -1 ||
        balance > 1) {
        return false;
    }

    *out_height = actual_height;
    return true;
}

static bool tree_state_is_shallow_valid(const Tree *tree)
{
    return tree != NULL &&
        tree->size <= (size_t)BST_AVL_MAX_NODES &&
        ((tree->root == NULL) == (tree->size == 0U));
}

static bool locate_key_recursive(
    const TreeNode *node,
    int key,
    size_t *remaining_steps,
    bool *out_exists
)
{
    if (node == NULL) {
        *out_exists = false;
        return true;
    }
    if (*remaining_steps == 0U) {
        return false;
    }

    *remaining_steps -= 1U;
    if (key == node->key) {
        *out_exists = true;
        return true;
    }
    if (key < node->key) {
        return locate_key_recursive(
            node->left,
            key,
            remaining_steps,
            out_exists
        );
    }
    return locate_key_recursive(
        node->right,
        key,
        remaining_steps,
        out_exists
    );
}

static TreeStatus insert_baseline_recursive(
    TreeNode **link,
    int key
)
{
    TreeNode *created = NULL;
    TreeStatus status;

    if (*link == NULL) {
        status = tree_node_create(key, &created);
        if (status != TREE_OK) {
            return status;
        }
        *link = created;
        return TREE_OK;
    }
    if (key < (*link)->key) {
        return insert_baseline_recursive(&(*link)->left, key);
    }
    return insert_baseline_recursive(&(*link)->right, key);
}

static bool search_recursive(
    const TreeNode *node,
    int key,
    size_t *remaining_steps,
    size_t *comparisons,
    bool *out_found
)
{
    if (node == NULL) {
        *out_found = false;
        return true;
    }
    if (*remaining_steps == 0U) {
        return false;
    }

    *remaining_steps -= 1U;
    *comparisons += 1U;
    if (key == node->key) {
        *out_found = true;
        return true;
    }
    if (key < node->key) {
        return search_recursive(
            node->left,
            key,
            remaining_steps,
            comparisons,
            out_found
        );
    }
    return search_recursive(
        node->right,
        key,
        remaining_steps,
        comparisons,
        out_found
    );
}

TreeStatus tree_init(Tree *tree)
{
    if (tree == NULL) {
        return TREE_INVALID_ARGUMENT;
    }

    tree->root = NULL;
    tree->size = 0U;
    return TREE_OK;
}

TreeStatus tree_node_create(int key, TreeNode **out_node)
{
    TreeNode *created;

    if (out_node == NULL) {
        return TREE_INVALID_ARGUMENT;
    }
    if (fail_next_allocation) {
        fail_next_allocation = false;
        return TREE_ALLOCATION_FAILED;
    }

    created = (TreeNode *)malloc(sizeof *created);
    if (created == NULL) {
        return TREE_ALLOCATION_FAILED;
    }

    created->key = key;
    created->height = 0;
    created->left = NULL;
    created->right = NULL;
    live_node_count += 1U;
    *out_node = created;
    return TREE_OK;
}

void tree_node_release(TreeNode *node)
{
    if (node != NULL) {
        free(node);
        live_node_count -= 1U;
    }
}

int tree_actual_height(const TreeNode *node)
{
    int left_height;
    int right_height;

    if (node == NULL) {
        return -1;
    }

    left_height = tree_actual_height(node->left);
    right_height = tree_actual_height(node->right);
    return 1 + maximum_int(left_height, right_height);
}

void tree_destroy_iterative(Tree *tree)
{
    TreeNode *stack[BST_AVL_MAX_NODES];
    size_t stack_size = 0U;

    if (tree == NULL) {
        return;
    }
    if (tree->root != NULL) {
        stack[stack_size] = tree->root;
        stack_size += 1U;
    }

    while (stack_size > 0U) {
        TreeNode *node;

        stack_size -= 1U;
        node = stack[stack_size];
        if (node->left != NULL) {
            stack[stack_size] = node->left;
            stack_size += 1U;
        }
        if (node->right != NULL) {
            stack[stack_size] = node->right;
            stack_size += 1U;
        }
        tree_node_release(node);
    }

    tree->root = NULL;
    tree->size = 0U;
}

bool tree_validate_bst(const Tree *tree)
{
    ValidationState state = {{NULL}, 0U};

    if (tree == NULL ||
        tree->size > (size_t)BST_AVL_MAX_NODES ||
        ((tree->root == NULL) != (tree->size == 0U))) {
        return false;
    }

    if (!validate_bst_node(
            tree->root,
            false,
            0,
            false,
            0,
            &state
        )) {
        return false;
    }
    return state.seen_count == tree->size;
}

bool tree_validate_avl(const Tree *tree)
{
    ValidationState state = {{NULL}, 0U};
    int height = -1;

    if (tree == NULL ||
        tree->size > (size_t)BST_AVL_MAX_NODES ||
        ((tree->root == NULL) != (tree->size == 0U))) {
        return false;
    }

    if (!validate_avl_node(
            tree->root,
            false,
            0,
            false,
            0,
            &state,
            &height
        )) {
        return false;
    }
    return state.seen_count == tree->size;
}

TreeStatus bst_insert_baseline(Tree *tree, int key)
{
    size_t remaining_steps;
    bool exists = false;
    TreeStatus status;

    if (tree == NULL) {
        return TREE_INVALID_ARGUMENT;
    }
    if (!tree_state_is_shallow_valid(tree)) {
        return TREE_INVALID_STATE;
    }
    remaining_steps = tree->size;
    if (!locate_key_recursive(
            tree->root,
            key,
            &remaining_steps,
            &exists
        )) {
        return TREE_INVALID_STATE;
    }
    if (exists) {
        return TREE_DUPLICATE;
    }
    if (tree->size >= (size_t)BST_AVL_MAX_NODES) {
        return TREE_FULL;
    }

    status = insert_baseline_recursive(&tree->root, key);
    if (status == TREE_OK) {
        tree->size += 1U;
    }
    return status;
}

TreeStatus bst_search(
    const Tree *tree,
    int key,
    bool *out_found,
    size_t *out_comparisons
)
{
    size_t remaining_steps;
    size_t comparisons = 0U;
    bool found = false;

    if (tree == NULL ||
        out_found == NULL ||
        out_comparisons == NULL) {
        return TREE_INVALID_ARGUMENT;
    }
    if (!tree_state_is_shallow_valid(tree)) {
        return TREE_INVALID_STATE;
    }

    remaining_steps = tree->size;
    if (!search_recursive(
            tree->root,
            key,
            &remaining_steps,
            &comparisons,
            &found
        )) {
        return TREE_INVALID_STATE;
    }
    *out_found = found;
    *out_comparisons = comparisons;
    return TREE_OK;
}

const char *tree_status_name(TreeStatus status)
{
    switch (status) {
        case TREE_OK:
            return "TREE_OK";
        case TREE_INVALID_ARGUMENT:
            return "TREE_INVALID_ARGUMENT";
        case TREE_FULL:
            return "TREE_FULL";
        case TREE_DUPLICATE:
            return "TREE_DUPLICATE";
        case TREE_ALLOCATION_FAILED:
            return "TREE_ALLOCATION_FAILED";
        case TREE_INVALID_STATE:
            return "TREE_INVALID_STATE";
        default:
            return "TREE_UNKNOWN_STATUS";
    }
}

#ifdef TREE_TESTING
void tree_test_fail_next_allocation(void)
{
    fail_next_allocation = true;
}

size_t tree_test_live_node_count(void)
{
    return live_node_count;
}
#endif
