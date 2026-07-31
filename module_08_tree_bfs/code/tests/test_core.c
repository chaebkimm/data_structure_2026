#include "tree_bfs.h"
#include "tree_work_queue.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#ifndef TREE_BFS_TESTING
#error "Core tests require -DTREE_BFS_TESTING."
#endif

#define CHECK(condition)                                                   \
    do {                                                                   \
        if (!(condition)) {                                                \
            fprintf(stderr, "  check failed at line %d: %s\n",            \
                __LINE__, #condition);                                     \
            return false;                                                  \
        }                                                                  \
    } while (false)

static void make_canonical(TreeNode nodes[9])
{
    nodes[0] = (TreeNode){42, false, &nodes[1], &nodes[2]};
    nodes[1] = (TreeNode){17, true, &nodes[3], &nodes[4]};
    nodes[2] = (TreeNode){68, false, &nodes[5], &nodes[6]};
    nodes[3] = (TreeNode){23, false, NULL, NULL};
    nodes[4] = (TreeNode){91, true, &nodes[7], NULL};
    nodes[5] = (TreeNode){17, true, NULL, NULL};
    nodes[6] = (TreeNode){5, false, NULL, &nodes[8]};
    nodes[7] = (TreeNode){44, true, NULL, NULL};
    nodes[8] = (TreeNode){44, false, NULL, NULL};
}

static bool order_matches(
    const TreeBfsOrder *order,
    const int *keys,
    const bool *flags,
    const size_t *depths,
    size_t count
)
{
    size_t index;

    if (order->count != count) {
        return false;
    }

    for (index = 0U; index < count; index += 1U) {
        if (order->items[index].key != keys[index] ||
            order->items[index].flagged != flags[index] ||
            order->items[index].depth != depths[index]) {
            return false;
        }
    }

    return true;
}

static void mark_order(TreeBfsOrder *order)
{
    size_t index;

    order->count = 37U;
    for (index = 0U; index < (size_t)TREE_BFS_MAX_NODES; index += 1U) {
        order->items[index].key = -700 - (int)index;
        order->items[index].flagged = (index % 2U) != 0U;
        order->items[index].depth = 700U + index;
    }
}

static bool order_is_marked(const TreeBfsOrder *order)
{
    size_t index;

    if (order->count != 37U) {
        return false;
    }
    for (index = 0U; index < (size_t)TREE_BFS_MAX_NODES; index += 1U) {
        if (order->items[index].key != -700 - (int)index ||
            order->items[index].flagged != ((index % 2U) != 0U) ||
            order->items[index].depth != 700U + index) {
            return false;
        }
    }
    return true;
}

static bool test_empty_and_singleton(void)
{
    TreeBfsOrder order;
    TreeNode marker = {-1, false, NULL, NULL};
    TreeNode only = {8, true, NULL, NULL};
    TreeBfsMatch match = {&marker, 91U};
    int height = 91;
    const int keys[] = {8};
    const bool flags[] = {true};
    const size_t depths[] = {0U};

    mark_order(&order);
    CHECK(tree_level_order(NULL, 0U, &order) == TREE_BFS_OK);
    CHECK(order.count == 0U);

    CHECK(
        tree_find_shallowest(NULL, 8, 0U, &match) ==
        TREE_BFS_NOT_FOUND
    );
    CHECK(match.node == &marker);
    CHECK(match.depth == 91U);

    CHECK(tree_height_bfs(NULL, 0U, &height) == TREE_BFS_OK);
    CHECK(height == -1);

    CHECK(tree_level_order(&only, 1U, &order) == TREE_BFS_OK);
    CHECK(order_matches(&order, keys, flags, depths, 1U));
    CHECK(
        tree_find_shallowest(&only, 8, 1U, &match) ==
        TREE_BFS_OK
    );
    CHECK(match.node == &only);
    CHECK(match.depth == 0U);
    CHECK(tree_height_bfs(&only, 1U, &height) == TREE_BFS_OK);
    CHECK(height == 0);

    mark_order(&order);
    CHECK(
        tree_level_order(&only, 0U, &order) == TREE_BFS_LIMIT
    );
    CHECK(order_is_marked(&order));
    match.node = &marker;
    match.depth = 91U;
    CHECK(
        tree_find_shallowest(&only, 8, 0U, &match) ==
        TREE_BFS_LIMIT
    );
    CHECK(match.node == &marker);
    CHECK(match.depth == 91U);
    height = 91;
    CHECK(tree_height_bfs(&only, 0U, &height) == TREE_BFS_LIMIT);
    CHECK(height == 91);
    return true;
}

static bool test_canonical_order_search_and_height(void)
{
    TreeNode nodes[9];
    TreeBfsOrder order;
    TreeBfsMatch match;
    TreeNode marker = {-1, false, NULL, NULL};
    int height;
    const int keys[] = {42, 17, 68, 23, 91, 17, 5, 44, 44};
    const bool flags[] = {
        false, true, false, false, true, true, false, true, false
    };
    const size_t depths[] = {0U, 1U, 1U, 2U, 2U, 2U, 2U, 3U, 3U};

    make_canonical(nodes);
    CHECK(tree_level_order(&nodes[0], 4U, &order) == TREE_BFS_OK);
    CHECK(order_matches(&order, keys, flags, depths, 9U));

    CHECK(
        tree_find_shallowest(&nodes[0], 17, 4U, &match) ==
        TREE_BFS_OK
    );
    CHECK(match.node == &nodes[1]);
    CHECK(match.depth == 1U);
    CHECK(match.node->flagged);

    CHECK(
        tree_find_shallowest(&nodes[0], 44, 4U, &match) ==
        TREE_BFS_OK
    );
    CHECK(match.node == &nodes[7]);
    CHECK(match.depth == 3U);
    CHECK(match.node->flagged);

    match.node = &marker;
    match.depth = 77U;
    CHECK(
        tree_find_shallowest(&nodes[0], 99, 4U, &match) ==
        TREE_BFS_NOT_FOUND
    );
    CHECK(match.node == &marker);
    CHECK(match.depth == 77U);

    height = -88;
    CHECK(tree_height_bfs(&nodes[0], 4U, &height) == TREE_BFS_OK);
    CHECK(height == 3);
    return true;
}

static bool test_canonical_limit_preservation(void)
{
    TreeNode nodes[9];
    TreeBfsOrder order;
    TreeBfsMatch match;
    TreeNode marker = {-1, false, NULL, NULL};
    int height = 812;

    make_canonical(nodes);
    mark_order(&order);
    CHECK(
        tree_level_order(&nodes[0], 3U, &order) == TREE_BFS_LIMIT
    );
    CHECK(order_is_marked(&order));

    match.node = &marker;
    match.depth = 812U;
    CHECK(
        tree_find_shallowest(&nodes[0], 44, 3U, &match) ==
        TREE_BFS_LIMIT
    );
    CHECK(match.node == &marker);
    CHECK(match.depth == 812U);

    CHECK(
        tree_height_bfs(&nodes[0], 3U, &height) == TREE_BFS_LIMIT
    );
    CHECK(height == 812);

    /* The earlier target is removed before capacity four is needed. */
    CHECK(
        tree_find_shallowest(&nodes[0], 17, 2U, &match) ==
        TREE_BFS_OK
    );
    CHECK(match.node == &nodes[1]);
    CHECK(match.depth == 1U);
    return true;
}

static bool test_skewed_and_wide_shapes(void)
{
    TreeNode chain[5];
    TreeNode wide[7];
    TreeBfsOrder order;
    int height;
    size_t index;

    for (index = 0U; index < 5U; index += 1U) {
        chain[index].key = (int)(10U + index);
        chain[index].flagged = (index % 2U) == 0U;
        chain[index].left = NULL;
        chain[index].right =
            index + 1U < 5U ? &chain[index + 1U] : NULL;
    }

    CHECK(tree_level_order(&chain[0], 1U, &order) == TREE_BFS_OK);
    CHECK(order.count == 5U);
    for (index = 0U; index < 5U; index += 1U) {
        CHECK(order.items[index].key == (int)(10U + index));
        CHECK(order.items[index].depth == index);
    }
    CHECK(tree_height_bfs(&chain[0], 1U, &height) == TREE_BFS_OK);
    CHECK(height == 4);

    wide[0] = (TreeNode){1, false, &wide[1], &wide[2]};
    wide[1] = (TreeNode){2, false, &wide[3], &wide[4]};
    wide[2] = (TreeNode){3, false, &wide[5], &wide[6]};
    wide[3] = (TreeNode){4, false, NULL, NULL};
    wide[4] = (TreeNode){5, false, NULL, NULL};
    wide[5] = (TreeNode){6, false, NULL, NULL};
    wide[6] = (TreeNode){7, false, NULL, NULL};
    CHECK(tree_level_order(&wide[0], 4U, &order) == TREE_BFS_OK);
    CHECK(order.count == 7U);
    CHECK(tree_height_bfs(&wide[0], 4U, &height) == TREE_BFS_OK);
    CHECK(height == 2);
    return true;
}

static bool test_invalid_arguments_and_limits(void)
{
    TreeNode node = {1, false, NULL, NULL};
    TreeNode marker = {-1, false, NULL, NULL};
    TreeBfsOrder order;
    TreeBfsMatch match = {&marker, 33U};
    int height = 33;
    size_t too_large = (size_t)TREE_BFS_MAX_NODES + 1U;

    CHECK(
        tree_level_order(&node, 1U, NULL) ==
        TREE_BFS_INVALID_ARGUMENT
    );
    CHECK(
        tree_find_shallowest(&node, 1, 1U, NULL) ==
        TREE_BFS_INVALID_ARGUMENT
    );
    CHECK(
        tree_height_bfs(&node, 1U, NULL) ==
        TREE_BFS_INVALID_ARGUMENT
    );

    mark_order(&order);
    CHECK(tree_level_order(NULL, too_large, &order) == TREE_BFS_LIMIT);
    CHECK(order_is_marked(&order));
    CHECK(
        tree_find_shallowest(NULL, 1, too_large, &match) ==
        TREE_BFS_LIMIT
    );
    CHECK(match.node == &marker);
    CHECK(match.depth == 33U);
    CHECK(tree_height_bfs(NULL, too_large, &height) == TREE_BFS_LIMIT);
    CHECK(height == 33);
    return true;
}

static bool test_work_queue_directly(void)
{
    TreeNode nodes[4];
    TreeWorkQueue queue = {0};
    TreeWorkItem item;
    TreeWorkItem output;
    TreeWorkItem before_slots[3];
    size_t index;

    for (index = 0U; index < 4U; index += 1U) {
        nodes[index] = (TreeNode){(int)index, false, NULL, NULL};
    }

    CHECK(tree_work_queue_init(&queue, 3U) == WORK_QUEUE_OK);
    CHECK(tree_work_queue_validate(&queue) == WORK_QUEUE_OK);
    for (index = 0U; index < 3U; index += 1U) {
        item.node = &nodes[index];
        item.depth = index;
        CHECK(tree_work_queue_enqueue(&queue, item) == WORK_QUEUE_OK);
    }
    CHECK(queue.head == 0U);
    CHECK(queue.size == 3U);
    for (index = 0U; index < 3U; index += 1U) {
        before_slots[index] = queue.data[index];
    }
    item.node = &nodes[3];
    item.depth = 3U;
    CHECK(tree_work_queue_enqueue(&queue, item) == WORK_QUEUE_LIMIT);
    CHECK(queue.head == 0U);
    CHECK(queue.size == 3U);
    for (index = 0U; index < 3U; index += 1U) {
        CHECK(queue.data[index].node == before_slots[index].node);
        CHECK(queue.data[index].depth == before_slots[index].depth);
    }

    CHECK(tree_work_queue_dequeue(&queue, &output) == WORK_QUEUE_OK);
    CHECK(output.node == &nodes[0]);
    CHECK(output.depth == 0U);
    item.node = &nodes[3];
    item.depth = 3U;
    CHECK(tree_work_queue_enqueue(&queue, item) == WORK_QUEUE_OK);
    CHECK(queue.data[0].node == &nodes[3]);
    CHECK(queue.head == 1U);
    CHECK(queue.size == 3U);

    for (index = 1U; index < 4U; index += 1U) {
        CHECK(tree_work_queue_dequeue(&queue, &output) == WORK_QUEUE_OK);
        CHECK(output.node == &nodes[index]);
        CHECK(output.depth == index);
    }
    CHECK(queue.head == 0U);
    CHECK(queue.size == 0U);
    output.node = &nodes[3];
    output.depth = 99U;
    CHECK(
        tree_work_queue_dequeue(&queue, &output) ==
        WORK_QUEUE_UNDERFLOW
    );
    CHECK(output.node == &nodes[3]);
    CHECK(output.depth == 99U);
    return true;
}

static bool test_tree_support_and_ownership(void)
{
    TreeNode *root = NULL;
    TreeNode *created = NULL;
    TreeNode marker = {-1, false, NULL, NULL};
    size_t baseline = tree_bfs_test_live_node_count();

    CHECK(tree_node_create(1, false, NULL) == TREE_BFS_INVALID_ARGUMENT);
    tree_bfs_test_fail_next_node_allocation();
    created = &marker;
    CHECK(tree_node_create(8, true, &created) == TREE_BFS_ALLOCATION);
    CHECK(created == &marker);
    CHECK(tree_bfs_test_live_node_count() == baseline);

    CHECK(tree_bst_insert(&root, 30, false) == TREE_BFS_OK);
    CHECK(tree_bst_insert(&root, 20, true) == TREE_BFS_OK);
    CHECK(tree_bst_insert(&root, 40, false) == TREE_BFS_OK);
    CHECK(tree_bst_insert(&root, 30, true) == TREE_BFS_DUPLICATE);
    CHECK(root != NULL);
    CHECK(root->key == 30);
    CHECK(!root->flagged);
    CHECK(root->left != NULL && root->left->key == 20);
    CHECK(root->right != NULL && root->right->key == 40);
    CHECK(tree_bfs_test_live_node_count() == baseline + 3U);

    tree_bfs_test_fail_next_node_allocation();
    CHECK(tree_bst_insert(&root, 35, true) == TREE_BFS_ALLOCATION);
    CHECK(root->right->left == NULL);
    CHECK(tree_bfs_test_live_node_count() == baseline + 3U);

    CHECK(tree_destroy_postorder(&root) == TREE_BFS_OK);
    CHECK(root == NULL);
    CHECK(tree_bfs_test_live_node_count() == baseline);
    CHECK(tree_destroy_postorder(&root) == TREE_BFS_OK);
    CHECK(tree_destroy_postorder(NULL) == TREE_BFS_INVALID_ARGUMENT);
    tree_node_release(NULL);
    return true;
}

static bool test_status_names(void)
{
    CHECK(strcmp(tree_bfs_status_name(TREE_BFS_OK), "ok") == 0);
    CHECK(strcmp(
        tree_bfs_status_name(TREE_BFS_INVALID_ARGUMENT),
        "invalid argument"
    ) == 0);
    CHECK(strcmp(
        tree_bfs_status_name(TREE_BFS_LIMIT),
        "tree or Queue limit reached"
    ) == 0);
    CHECK(strcmp(
        tree_bfs_status_name(TREE_BFS_ALLOCATION),
        "allocation failed"
    ) == 0);
    CHECK(strcmp(
        tree_bfs_status_name(TREE_BFS_DUPLICATE),
        "duplicate key"
    ) == 0);
    CHECK(strcmp(
        tree_bfs_status_name(TREE_BFS_NOT_FOUND),
        "key not found"
    ) == 0);
    CHECK(strcmp(
        tree_bfs_status_name((TreeBfsStatus)99),
        "unknown TreeBfsStatus"
    ) == 0);

    CHECK(strcmp(
        tree_work_queue_status_name(WORK_QUEUE_OK),
        "ok"
    ) == 0);
    CHECK(strcmp(
        tree_work_queue_status_name(WORK_QUEUE_INVALID_ARGUMENT),
        "invalid argument"
    ) == 0);
    CHECK(strcmp(
        tree_work_queue_status_name(WORK_QUEUE_LIMIT),
        "Queue limit reached"
    ) == 0);
    CHECK(strcmp(
        tree_work_queue_status_name(WORK_QUEUE_UNDERFLOW),
        "Queue is empty"
    ) == 0);
    CHECK(strcmp(
        tree_work_queue_status_name(WORK_QUEUE_INVALID_STATE),
        "Queue representation is invalid"
    ) == 0);
    CHECK(strcmp(
        tree_work_queue_status_name((TreeWorkQueueStatus)99),
        "unknown TreeWorkQueueStatus"
    ) == 0);
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

    failures += run_test(test_empty_and_singleton, "empty and singleton");
    failures += run_test(
        test_canonical_order_search_and_height,
        "canonical order, search, and height"
    );
    failures += run_test(
        test_canonical_limit_preservation,
        "canonical limit preservation"
    );
    failures += run_test(
        test_skewed_and_wide_shapes,
        "skewed and wide shapes"
    );
    failures += run_test(
        test_invalid_arguments_and_limits,
        "invalid arguments and limits"
    );
    failures += run_test(test_work_queue_directly, "typed work Queue");
    failures += run_test(
        test_tree_support_and_ownership,
        "tree support and ownership"
    );
    failures += run_test(test_status_names, "status names");

    if (failures != 0) {
        printf("%d core test group(s) failed.\n", failures);
        return 1;
    }

    puts("All core test groups passed.");
    return 0;
}
