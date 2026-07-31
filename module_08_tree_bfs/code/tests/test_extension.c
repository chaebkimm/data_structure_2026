#include "tree_bfs.h"
#include "tree_work_queue.h"

#include <stdbool.h>
#include <stdio.h>

#ifndef TREE_BFS_TESTING
#error "Extension tests require -DTREE_BFS_TESTING."
#endif

#define CHECK(condition)                                                   \
    do {                                                                   \
        if (!(condition)) {                                                \
            fprintf(stderr, "  check failed at line %d: %s\n",            \
                __LINE__, #condition);                                     \
            return false;                                                  \
        }                                                                  \
    } while (false)

static void make_right_chain(TreeNode *nodes, size_t count)
{
    size_t index;

    for (index = 0U; index < count; index += 1U) {
        nodes[index].key = (int)index;
        nodes[index].flagged = (index % 2U) != 0U;
        nodes[index].left = NULL;
        nodes[index].right =
            index + 1U < count ? &nodes[index + 1U] : NULL;
    }
}

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

static bool nodes_match_snapshot(
    const TreeNode *nodes,
    const TreeNode *snapshot,
    size_t count
)
{
    size_t index;

    for (index = 0U; index < count; index += 1U) {
        if (nodes[index].key != snapshot[index].key ||
            nodes[index].flagged != snapshot[index].flagged ||
            nodes[index].left != snapshot[index].left ||
            nodes[index].right != snapshot[index].right) {
            return false;
        }
    }
    return true;
}

static void mark_order(TreeBfsOrder *order)
{
    size_t index;

    order->count = 55U;
    for (index = 0U; index < (size_t)TREE_BFS_MAX_NODES; index += 1U) {
        order->items[index].key = -55 - (int)index;
        order->items[index].flagged = (index % 2U) != 0U;
        order->items[index].depth = 500U + index;
    }
}

static bool order_is_marked(const TreeBfsOrder *order)
{
    size_t index;

    if (order->count != 55U) {
        return false;
    }
    for (index = 0U; index < (size_t)TREE_BFS_MAX_NODES; index += 1U) {
        if (order->items[index].key != -55 - (int)index ||
            order->items[index].flagged != ((index % 2U) != 0U) ||
            order->items[index].depth != 500U + index) {
            return false;
        }
    }
    return true;
}

static bool test_exact_64_node_boundary(void)
{
    TreeNode nodes[TREE_BFS_MAX_NODES];
    TreeBfsOrder order;
    TreeBfsMatch match;
    int height = -7;
    size_t index;

    make_right_chain(nodes, (size_t)TREE_BFS_MAX_NODES);
    CHECK(tree_level_order(&nodes[0], 1U, &order) == TREE_BFS_OK);
    CHECK(order.count == (size_t)TREE_BFS_MAX_NODES);
    for (index = 0U; index < (size_t)TREE_BFS_MAX_NODES; index += 1U) {
        CHECK(order.items[index].key == (int)index);
        CHECK(order.items[index].depth == index);
    }
    CHECK(
        tree_find_shallowest(
            &nodes[0],
            (int)TREE_BFS_MAX_NODES - 1,
            1U,
            &match
        ) == TREE_BFS_OK
    );
    CHECK(match.node == &nodes[TREE_BFS_MAX_NODES - 1U]);
    CHECK(match.depth == (size_t)TREE_BFS_MAX_NODES - 1U);
    CHECK(tree_height_bfs(&nodes[0], 1U, &height) == TREE_BFS_OK);
    CHECK(height == (int)TREE_BFS_MAX_NODES - 1);
    return true;
}

static bool test_65th_node_preserves_outputs(void)
{
    TreeNode nodes[TREE_BFS_MAX_NODES + 1U];
    TreeNode marker = {-1, false, NULL, NULL};
    TreeBfsOrder order;
    TreeBfsMatch match = {&marker, 404U};
    int height = 404;

    make_right_chain(nodes, (size_t)TREE_BFS_MAX_NODES + 1U);
    mark_order(&order);
    CHECK(tree_level_order(&nodes[0], 1U, &order) == TREE_BFS_LIMIT);
    CHECK(order_is_marked(&order));
    CHECK(
        tree_find_shallowest(
            &nodes[0],
            (int)TREE_BFS_MAX_NODES,
            1U,
            &match
        ) == TREE_BFS_LIMIT
    );
    CHECK(match.node == &marker);
    CHECK(match.depth == 404U);
    CHECK(tree_height_bfs(&nodes[0], 1U, &height) == TREE_BFS_LIMIT);
    CHECK(height == 404);

    /* A search may finish before reaching the oversized remainder. */
    CHECK(
        tree_find_shallowest(&nodes[0], 0, 1U, &match) ==
        TREE_BFS_OK
    );
    CHECK(match.node == &nodes[0]);
    CHECK(match.depth == 0U);
    return true;
}

static bool test_complete_tree_queue_boundary(void)
{
    TreeNode nodes[63];
    TreeBfsOrder order;
    int height = 81;
    size_t index;

    for (index = 0U; index < 63U; index += 1U) {
        size_t left = index * 2U + 1U;
        size_t right = left + 1U;

        nodes[index].key = (int)index;
        nodes[index].flagged = false;
        nodes[index].left = left < 63U ? &nodes[left] : NULL;
        nodes[index].right = right < 63U ? &nodes[right] : NULL;
    }

    CHECK(tree_level_order(&nodes[0], 32U, &order) == TREE_BFS_OK);
    CHECK(order.count == 63U);
    CHECK(order.items[62].depth == 5U);
    CHECK(tree_height_bfs(&nodes[0], 32U, &height) == TREE_BFS_OK);
    CHECK(height == 5);

    mark_order(&order);
    CHECK(tree_level_order(&nodes[0], 31U, &order) == TREE_BFS_LIMIT);
    CHECK(order_is_marked(&order));
    height = 81;
    CHECK(tree_height_bfs(&nodes[0], 31U, &height) == TREE_BFS_LIMIT);
    CHECK(height == 81);
    return true;
}

static bool test_algorithms_do_not_mutate_tree(void)
{
    TreeNode nodes[9];
    TreeNode snapshot[9];
    TreeBfsOrder order;
    TreeBfsMatch match;
    int height;
    size_t index;

    make_canonical(nodes);
    for (index = 0U; index < 9U; index += 1U) {
        snapshot[index] = nodes[index];
    }

    CHECK(tree_level_order(&nodes[0], 4U, &order) == TREE_BFS_OK);
    CHECK(nodes_match_snapshot(nodes, snapshot, 9U));
    CHECK(
        tree_find_shallowest(&nodes[0], 44, 4U, &match) ==
        TREE_BFS_OK
    );
    CHECK(match.node == &nodes[7]);
    CHECK(nodes_match_snapshot(nodes, snapshot, 9U));
    CHECK(tree_height_bfs(&nodes[0], 4U, &height) == TREE_BFS_OK);
    CHECK(height == 3);
    CHECK(nodes_match_snapshot(nodes, snapshot, 9U));

    CHECK(
        tree_find_shallowest(&nodes[0], 99, 4U, &match) ==
        TREE_BFS_NOT_FOUND
    );
    CHECK(nodes_match_snapshot(nodes, snapshot, 9U));
    CHECK(tree_level_order(&nodes[0], 3U, &order) == TREE_BFS_LIMIT);
    CHECK(nodes_match_snapshot(nodes, snapshot, 9U));
    return true;
}

static bool test_queue_all_head_positions(void)
{
    TreeNode nodes[5];
    size_t target_head;
    size_t index;

    for (index = 0U; index < 5U; index += 1U) {
        nodes[index] = (TreeNode){(int)index, false, NULL, NULL};
    }

    for (target_head = 0U; target_head < 5U; target_head += 1U) {
        TreeWorkQueue queue = {0};
        TreeWorkItem output;

        CHECK(tree_work_queue_init(&queue, 5U) == WORK_QUEUE_OK);
        for (index = 0U; index < 5U; index += 1U) {
            TreeWorkItem item = {&nodes[index], index};

            CHECK(tree_work_queue_enqueue(&queue, item) == WORK_QUEUE_OK);
        }
        for (index = 0U; index < target_head; index += 1U) {
            CHECK(
                tree_work_queue_dequeue(&queue, &output) ==
                WORK_QUEUE_OK
            );
        }
        for (index = 0U; index < target_head; index += 1U) {
            TreeWorkItem item = {&nodes[index], 5U + index};

            CHECK(tree_work_queue_enqueue(&queue, item) == WORK_QUEUE_OK);
        }
        CHECK(queue.size == 5U);
        if (target_head == 0U) {
            CHECK(queue.head == 0U);
        } else {
            CHECK(queue.head == target_head);
        }
        CHECK(tree_work_queue_validate(&queue) == WORK_QUEUE_OK);
    }
    return true;
}

static bool test_queue_invalid_states_and_failures(void)
{
    TreeNode node = {1, false, NULL, NULL};
    TreeWorkQueue invalid_cases[5] = {0};
    TreeWorkQueue queue = {0};
    TreeWorkItem item = {&node, 0U};
    TreeWorkItem output = {&node, 99U};
    size_t index;

    invalid_cases[0].head = 1U;
    invalid_cases[1].size = 1U;
    invalid_cases[2].limit = 2U;
    invalid_cases[2].head = 1U;
    invalid_cases[3].limit = 2U;
    invalid_cases[3].head = 2U;
    invalid_cases[3].size = 1U;
    invalid_cases[4].limit = (size_t)TREE_BFS_MAX_NODES + 1U;

    CHECK(
        tree_work_queue_init(
            &queue,
            (size_t)TREE_BFS_MAX_NODES + 1U
        ) == WORK_QUEUE_LIMIT
    );
    CHECK(queue.limit == 0U && queue.head == 0U && queue.size == 0U);
    CHECK(tree_work_queue_init(&queue, 0U) == WORK_QUEUE_OK);
    CHECK(tree_work_queue_enqueue(&queue, item) == WORK_QUEUE_LIMIT);
    CHECK(
        tree_work_queue_dequeue(&queue, &output) ==
        WORK_QUEUE_UNDERFLOW
    );
    CHECK(output.node == &node && output.depth == 99U);
    item.node = NULL;
    CHECK(
        tree_work_queue_enqueue(&queue, item) ==
        WORK_QUEUE_INVALID_ARGUMENT
    );
    CHECK(tree_work_queue_dequeue(&queue, NULL) == WORK_QUEUE_INVALID_ARGUMENT);
    CHECK(tree_work_queue_validate(NULL) == WORK_QUEUE_INVALID_ARGUMENT);
    CHECK(tree_work_queue_init(NULL, 0U) == WORK_QUEUE_INVALID_ARGUMENT);

    for (index = 0U; index < 5U; index += 1U) {
        size_t limit_before = invalid_cases[index].limit;
        size_t head_before = invalid_cases[index].head;
        size_t size_before = invalid_cases[index].size;

        CHECK(
            tree_work_queue_validate(&invalid_cases[index]) ==
            WORK_QUEUE_INVALID_STATE
        );
        item.node = &node;
        CHECK(
            tree_work_queue_enqueue(&invalid_cases[index], item) ==
            WORK_QUEUE_INVALID_STATE
        );
        CHECK(invalid_cases[index].limit == limit_before);
        CHECK(invalid_cases[index].head == head_before);
        CHECK(invalid_cases[index].size == size_before);
        CHECK(
            tree_work_queue_dequeue(&invalid_cases[index], &output) ==
            WORK_QUEUE_INVALID_STATE
        );
        CHECK(output.node == &node && output.depth == 99U);
    }
    return true;
}

static bool test_node_support_failure_atomicity(void)
{
    TreeNode *root = NULL;
    TreeNode marker = {-1, false, NULL, NULL};
    TreeNode *output = &marker;
    size_t baseline = tree_bfs_test_live_node_count();

    tree_bfs_test_fail_next_node_allocation();
    CHECK(tree_node_create(10, true, &output) == TREE_BFS_ALLOCATION);
    CHECK(output == &marker);
    CHECK(tree_bfs_test_live_node_count() == baseline);

    CHECK(tree_bst_insert(&root, 10, false) == TREE_BFS_OK);
    CHECK(tree_bst_insert(&root, 5, true) == TREE_BFS_OK);
    tree_bfs_test_fail_next_node_allocation();
    CHECK(tree_bst_insert(&root, 7, true) == TREE_BFS_ALLOCATION);
    CHECK(root != NULL && root->left != NULL);
    CHECK(root->left->right == NULL);
    CHECK(tree_bfs_test_live_node_count() == baseline + 2U);
    CHECK(tree_destroy_postorder(&root) == TREE_BFS_OK);
    CHECK(tree_bfs_test_live_node_count() == baseline);
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

    failures += run_test(
        test_exact_64_node_boundary,
        "exact 64-node boundary"
    );
    failures += run_test(
        test_65th_node_preserves_outputs,
        "65th-node preservation"
    );
    failures += run_test(
        test_complete_tree_queue_boundary,
        "complete-tree Queue boundary"
    );
    failures += run_test(
        test_algorithms_do_not_mutate_tree,
        "input-tree nonmutation"
    );
    failures += run_test(
        test_queue_all_head_positions,
        "Queue head positions"
    );
    failures += run_test(
        test_queue_invalid_states_and_failures,
        "Queue invalid states"
    );
    failures += run_test(
        test_node_support_failure_atomicity,
        "node support failure atomicity"
    );

    if (failures != 0) {
        printf("%d extension test group(s) failed.\n", failures);
        return 1;
    }

    puts("All extension test groups passed.");
    return 0;
}
