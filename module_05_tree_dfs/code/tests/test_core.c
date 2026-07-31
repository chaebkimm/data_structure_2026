#include "tree_dfs.h"
#include "tree_node_stack.h"

#include <stdbool.h>
#include <stdio.h>

#define CHECK(condition)                                                   \
    do {                                                                   \
        if (!(condition)) {                                                \
            fprintf(                                                       \
                stderr,                                                    \
                "  check failed at line %d: %s\n",                        \
                __LINE__,                                                  \
                #condition                                                 \
            );                                                             \
            return false;                                                  \
        }                                                                  \
    } while (false)

static void make_canonical(TreeNode nodes[5])
{
    nodes[0] = (TreeNode){50, false, &nodes[1], &nodes[2]};
    nodes[1] = (TreeNode){30, true, &nodes[3], &nodes[4]};
    nodes[2] = (TreeNode){70, true, NULL, NULL};
    nodes[3] = (TreeNode){20, false, NULL, NULL};
    nodes[4] = (TreeNode){40, true, NULL, NULL};
}

static bool order_matches(
    const TreeOrder *order,
    const int *keys,
    const bool *flags,
    size_t count
)
{
    size_t index;

    if (order->count != count) {
        return false;
    }

    for (index = 0U; index < count; index += 1U) {
        if (order->items[index].key != keys[index] ||
            order->items[index].flagged != flags[index]) {
            return false;
        }
    }

    return true;
}

static bool orders_equal(const TreeOrder *left, const TreeOrder *right)
{
    size_t index;

    if (left->count != right->count) {
        return false;
    }

    for (index = 0U; index < left->count; index += 1U) {
        if (left->items[index].key != right->items[index].key ||
            left->items[index].flagged != right->items[index].flagged) {
            return false;
        }
    }

    return true;
}

static void mark_order(TreeOrder *order)
{
    size_t index;

    order->count = 37U;
    for (index = 0U;
         index < (size_t)TREE_DFS_MAX_NODES;
         index += 1U) {
        order->items[index].key = -777 - (int)index;
        order->items[index].flagged = (index % 2U) == 0U;
    }
}

static bool order_is_marked(const TreeOrder *order)
{
    size_t index;

    if (order->count != 37U) {
        return false;
    }

    for (index = 0U;
         index < (size_t)TREE_DFS_MAX_NODES;
         index += 1U) {
        if (order->items[index].key != -777 - (int)index ||
            order->items[index].flagged != ((index % 2U) == 0U)) {
            return false;
        }
    }

    return true;
}

static bool test_empty_tree(void)
{
    TreeOrder order;
    TreeNode marker = {-1, false, NULL, NULL};
    const TreeNode *unchanged = &marker;

    mark_order(&order);
    CHECK(tree_preorder_recursive(NULL, &order) == TREE_DFS_OK);
    CHECK(order.count == 0U);

    mark_order(&order);
    CHECK(tree_inorder_recursive(NULL, &order) == TREE_DFS_OK);
    CHECK(order.count == 0U);

    mark_order(&order);
    CHECK(tree_postorder_recursive(NULL, &order) == TREE_DFS_OK);
    CHECK(order.count == 0U);

    mark_order(&order);
    CHECK(tree_preorder_iterative(NULL, 0U, &order) == TREE_DFS_OK);
    CHECK(order.count == 0U);

    CHECK(tree_bst_search(NULL, 50, &unchanged) == TREE_DFS_NOT_FOUND);
    CHECK(unchanged == &marker);
    return true;
}

static bool test_single_node(void)
{
    TreeNode node = {8, true, NULL, NULL};
    TreeOrder order;
    const int keys[] = {8};
    const bool flags[] = {true};

    CHECK(tree_preorder_recursive(&node, &order) == TREE_DFS_OK);
    CHECK(order_matches(&order, keys, flags, 1U));
    CHECK(tree_inorder_recursive(&node, &order) == TREE_DFS_OK);
    CHECK(order_matches(&order, keys, flags, 1U));
    CHECK(tree_postorder_recursive(&node, &order) == TREE_DFS_OK);
    CHECK(order_matches(&order, keys, flags, 1U));
    CHECK(tree_preorder_iterative(&node, 1U, &order) == TREE_DFS_OK);
    CHECK(order_matches(&order, keys, flags, 1U));
    return true;
}

static bool test_canonical_orders_and_flags(void)
{
    TreeNode nodes[5];
    TreeOrder order;
    const int preorder[] = {50, 30, 20, 40, 70};
    const int inorder[] = {20, 30, 40, 50, 70};
    const int postorder[] = {20, 40, 30, 70, 50};
    const bool preorder_flags[] = {false, true, false, true, true};
    const bool inorder_flags[] = {false, true, true, false, true};
    const bool postorder_flags[] = {false, true, true, true, false};
    size_t index;
    int flagged_keys[3] = {0, 0, 0};
    size_t flagged_count = 0U;

    make_canonical(nodes);

    CHECK(tree_preorder_recursive(&nodes[0], &order) == TREE_DFS_OK);
    CHECK(order_matches(&order, preorder, preorder_flags, 5U));

    for (index = 0U; index < order.count; index += 1U) {
        if (order.items[index].flagged) {
            CHECK(flagged_count < 3U);
            flagged_keys[flagged_count] = order.items[index].key;
            flagged_count += 1U;
        }
    }
    CHECK(flagged_count == 3U);
    CHECK(flagged_keys[0] == 30);
    CHECK(flagged_keys[1] == 40);
    CHECK(flagged_keys[2] == 70);

    CHECK(tree_inorder_recursive(&nodes[0], &order) == TREE_DFS_OK);
    CHECK(order_matches(&order, inorder, inorder_flags, 5U));

    CHECK(tree_postorder_recursive(&nodes[0], &order) == TREE_DFS_OK);
    CHECK(order_matches(&order, postorder, postorder_flags, 5U));

    CHECK(tree_preorder_iterative(&nodes[0], 3U, &order) == TREE_DFS_OK);
    CHECK(order_matches(&order, preorder, preorder_flags, 5U));
    return true;
}

static bool test_skewed_tree(void)
{
    TreeNode third = {3, false, NULL, NULL};
    TreeNode second = {2, true, NULL, &third};
    TreeNode first = {1, false, NULL, &second};
    TreeOrder recursive_order;
    TreeOrder iterative_order;
    const int forward[] = {1, 2, 3};
    const int reverse[] = {3, 2, 1};
    const bool forward_flags[] = {false, true, false};
    const bool reverse_flags[] = {false, true, false};

    CHECK(
        tree_preorder_recursive(&first, &recursive_order) == TREE_DFS_OK
    );
    CHECK(order_matches(
        &recursive_order,
        forward,
        forward_flags,
        3U
    ));
    CHECK(
        tree_preorder_iterative(&first, 1U, &iterative_order) ==
        TREE_DFS_OK
    );
    CHECK(order_matches(
        &iterative_order,
        forward,
        forward_flags,
        3U
    ));
    CHECK(orders_equal(&recursive_order, &iterative_order));

    CHECK(tree_inorder_recursive(&first, &recursive_order) == TREE_DFS_OK);
    CHECK(order_matches(
        &recursive_order,
        forward,
        forward_flags,
        3U
    ));
    CHECK(
        tree_postorder_recursive(&first, &recursive_order) == TREE_DFS_OK
    );
    CHECK(order_matches(
        &recursive_order,
        reverse,
        reverse_flags,
        3U
    ));
    return true;
}

static bool test_iterative_limits_and_allocation(void)
{
    TreeNode nodes[5];
    TreeOrder order;
    const int preorder[] = {50, 30, 20, 40, 70};
    const bool flags[] = {false, true, false, true, true};

    make_canonical(nodes);

    CHECK(
        tree_preorder_iterative(&nodes[0], 3U, &order) == TREE_DFS_OK
    );
    CHECK(order_matches(&order, preorder, flags, 5U));

    mark_order(&order);
    CHECK(
        tree_preorder_iterative(&nodes[0], 2U, &order) == TREE_DFS_LIMIT
    );
    CHECK(order_is_marked(&order));

    mark_order(&order);
    tree_node_stack_test_fail_next_allocation();
    CHECK(
        tree_preorder_iterative(&nodes[0], 3U, &order) ==
        TREE_DFS_ALLOCATION
    );
    CHECK(order_is_marked(&order));
    return true;
}

static void release_tree_for_test(TreeNode *node)
{
    if (node == NULL) {
        return;
    }
    release_tree_for_test(node->left);
    release_tree_for_test(node->right);
    tree_node_release(node);
}

#define CHECK_OWNED_TREE(condition, root_pointer)                          \
    do {                                                                   \
        if (!(condition)) {                                                \
            fprintf(                                                       \
                stderr,                                                    \
                "  check failed at line %d: %s\n",                        \
                __LINE__,                                                  \
                #condition                                                 \
            );                                                             \
            release_tree_for_test(root_pointer);                           \
            return false;                                                  \
        }                                                                  \
    } while (false)

static bool test_constructor_and_insert_failures(void)
{
    TreeNode marker = {99, false, NULL, NULL};
    TreeNode *output = &marker;
    TreeNode *created = NULL;
    TreeNode *root = NULL;
    size_t live_before;

    CHECK(tree_node_create(10, true, NULL) == TREE_DFS_INVALID_ARGUMENT);
    CHECK(tree_bst_insert(NULL, 10, true) == TREE_DFS_INVALID_ARGUMENT);
    tree_node_release(NULL);

    tree_dfs_test_fail_next_node_allocation();
    CHECK(tree_node_create(10, true, &output) == TREE_DFS_ALLOCATION);
    CHECK(output == &marker);

    live_before = tree_dfs_test_live_node_count();
    CHECK_OWNED_TREE(
        tree_node_create(12, true, &created) == TREE_DFS_OK,
        created
    );
    CHECK_OWNED_TREE(created != NULL, created);
    CHECK_OWNED_TREE(created->key == 12, created);
    CHECK_OWNED_TREE(created->flagged, created);
    CHECK_OWNED_TREE(created->left == NULL, created);
    CHECK_OWNED_TREE(created->right == NULL, created);
    tree_node_release(created);
    created = NULL;
    CHECK(tree_dfs_test_live_node_count() == live_before);

    tree_dfs_test_fail_next_node_allocation();
    CHECK(tree_bst_insert(&root, 50, false) == TREE_DFS_ALLOCATION);
    CHECK(root == NULL);

    CHECK_OWNED_TREE(
        tree_bst_insert(&root, 50, false) == TREE_DFS_OK,
        root
    );
    CHECK_OWNED_TREE(
        tree_bst_insert(&root, 30, true) == TREE_DFS_OK,
        root
    );
    CHECK_OWNED_TREE(
        tree_bst_insert(&root, 70, true) == TREE_DFS_OK,
        root
    );
    live_before = tree_dfs_test_live_node_count();
    tree_dfs_test_fail_next_node_allocation();
    CHECK_OWNED_TREE(
        tree_bst_insert(&root, 40, true) == TREE_DFS_ALLOCATION,
        root
    );
    CHECK_OWNED_TREE(
        tree_dfs_test_live_node_count() == live_before,
        root
    );
    CHECK_OWNED_TREE(
        root != NULL &&
        root->left != NULL &&
        root->left->right == NULL,
        root
    );
    CHECK_OWNED_TREE(
        tree_bst_insert(&root, 50, true) == TREE_DFS_DUPLICATE,
        root
    );
    CHECK_OWNED_TREE(root != NULL && root->key == 50, root);
    CHECK_OWNED_TREE(root != NULL && !root->flagged, root);
    CHECK_OWNED_TREE(
        root != NULL &&
        root->left != NULL &&
        root->left->key == 30,
        root
    );
    CHECK_OWNED_TREE(
        root != NULL &&
        root->right != NULL &&
        root->right->key == 70,
        root
    );

    release_tree_for_test(root);
    return true;
}

static bool test_bst_search(void)
{
    TreeNode nodes[5];
    const TreeNode *found = NULL;
    const TreeNode *unchanged;

    make_canonical(nodes);
    CHECK(tree_bst_search(&nodes[0], 40, &found) == TREE_DFS_OK);
    CHECK(found == &nodes[4]);
    CHECK(found->flagged);

    CHECK(tree_bst_search(&nodes[0], 50, &found) == TREE_DFS_OK);
    CHECK(found == &nodes[0]);
    CHECK(tree_bst_search(&nodes[0], 20, &found) == TREE_DFS_OK);
    CHECK(found == &nodes[3]);

    unchanged = &nodes[2];
    CHECK(tree_bst_search(&nodes[0], 35, &unchanged) == TREE_DFS_NOT_FOUND);
    CHECK(unchanged == &nodes[2]);
    CHECK(tree_bst_search(&nodes[0], 90, &unchanged) == TREE_DFS_NOT_FOUND);
    CHECK(unchanged == &nodes[2]);
    CHECK(
        tree_bst_search(&nodes[0], 35, NULL) ==
        TREE_DFS_INVALID_ARGUMENT
    );
    return true;
}

static bool test_postorder_destroy(void)
{
    TreeNode *root = NULL;
    size_t baseline = tree_dfs_test_live_node_count();

    CHECK(tree_destroy_postorder(&root) == TREE_DFS_OK);
    CHECK(root == NULL);
    CHECK(tree_destroy_postorder(NULL) == TREE_DFS_INVALID_ARGUMENT);

    CHECK_OWNED_TREE(tree_bst_insert(&root, 8, true) == TREE_DFS_OK, root);
    CHECK_OWNED_TREE(
        tree_dfs_test_live_node_count() == baseline + 1U,
        root
    );
    CHECK(tree_destroy_postorder(&root) == TREE_DFS_OK);
    CHECK(root == NULL);
    CHECK(tree_dfs_test_live_node_count() == baseline);

    CHECK_OWNED_TREE(
        tree_bst_insert(&root, 50, false) == TREE_DFS_OK,
        root
    );
    CHECK_OWNED_TREE(
        tree_bst_insert(&root, 30, true) == TREE_DFS_OK,
        root
    );
    CHECK_OWNED_TREE(
        tree_bst_insert(&root, 70, true) == TREE_DFS_OK,
        root
    );
    CHECK_OWNED_TREE(
        tree_bst_insert(&root, 20, false) == TREE_DFS_OK,
        root
    );
    CHECK_OWNED_TREE(
        tree_bst_insert(&root, 40, true) == TREE_DFS_OK,
        root
    );
    CHECK_OWNED_TREE(
        tree_dfs_test_live_node_count() == baseline + 5U,
        root
    );

    CHECK(tree_destroy_postorder(&root) == TREE_DFS_OK);
    CHECK(root == NULL);
    CHECK(tree_dfs_test_live_node_count() == baseline);

    CHECK_OWNED_TREE(tree_bst_insert(&root, 1, false) == TREE_DFS_OK, root);
    CHECK_OWNED_TREE(tree_bst_insert(&root, 2, true) == TREE_DFS_OK, root);
    CHECK_OWNED_TREE(tree_bst_insert(&root, 3, false) == TREE_DFS_OK, root);
    CHECK_OWNED_TREE(
        tree_dfs_test_live_node_count() == baseline + 3U,
        root
    );
    CHECK(tree_destroy_postorder(&root) == TREE_DFS_OK);
    CHECK(root == NULL);
    CHECK(tree_dfs_test_live_node_count() == baseline);
    return true;
}

static bool test_invalid_outputs(void)
{
    TreeNode node = {1, false, NULL, NULL};
    TreeOrder order;

    CHECK(
        tree_preorder_recursive(&node, NULL) ==
        TREE_DFS_INVALID_ARGUMENT
    );
    CHECK(
        tree_inorder_recursive(&node, NULL) ==
        TREE_DFS_INVALID_ARGUMENT
    );
    CHECK(
        tree_postorder_recursive(&node, NULL) ==
        TREE_DFS_INVALID_ARGUMENT
    );
    CHECK(
        tree_preorder_iterative(&node, 1U, NULL) ==
        TREE_DFS_INVALID_ARGUMENT
    );

    mark_order(&order);
    CHECK(
        tree_preorder_iterative(
            &node,
            (size_t)TREE_DFS_MAX_NODES + 1U,
            &order
        ) == TREE_DFS_LIMIT
    );
    CHECK(order_is_marked(&order));
    return true;
}

typedef bool (*TestFunction)(void);

static int run_test(TestFunction function, const char *name)
{
    bool passed = function();
    printf("%s: %s\n", name, passed ? "PASS" : "FAIL");
    return passed ? 0 : 1;
}

int main(void)
{
    int failures = 0;

    failures += run_test(test_empty_tree, "empty tree");
    failures += run_test(test_single_node, "single node");
    failures += run_test(
        test_canonical_orders_and_flags,
        "canonical orders and flags"
    );
    failures += run_test(test_skewed_tree, "skewed tree");
    failures += run_test(
        test_iterative_limits_and_allocation,
        "iterative limits and allocation"
    );
    failures += run_test(
        test_constructor_and_insert_failures,
        "constructor and insertion failures"
    );
    failures += run_test(test_bst_search, "BST search");
    failures += run_test(test_postorder_destroy, "postorder destroy");
    failures += run_test(test_invalid_outputs, "invalid outputs");

    if (failures != 0) {
        printf("%d core test group(s) failed.\n", failures);
        return 1;
    }

    puts("All core test groups passed.");
    return 0;
}
