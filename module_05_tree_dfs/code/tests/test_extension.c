#include "tree_dfs.h"
#include "tree_node_stack.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define CHECK(condition)                                                   \
    do {                                                                   \
        if (!(condition)) {                                                \
            fprintf(stderr, "  line %d: %s\n", __LINE__, #condition);     \
            return false;                                                  \
        }                                                                  \
    } while (false)

#define CHECK_STACK(condition, stack_pointer)                              \
    do {                                                                   \
        if (!(condition)) {                                                \
            fprintf(stderr, "  line %d: %s\n", __LINE__, #condition);     \
            tree_node_stack_destroy(stack_pointer);                        \
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

static void make_left_chain(TreeNode *nodes, size_t count)
{
    size_t index;

    for (index = 0U; index < count; index += 1U) {
        nodes[index].key = (int)index;
        nodes[index].flagged = (index % 2U) != 0U;
        nodes[index].left =
            index + 1U < count ? &nodes[index + 1U] : NULL;
        nodes[index].right = NULL;
    }
}

static void mark_order(TreeOrder *order)
{
    size_t index;

    order->count = 55U;
    for (index = 0U;
         index < (size_t)TREE_DFS_MAX_NODES;
         index += 1U) {
        order->items[index].key = -55 - (int)index;
        order->items[index].flagged = (index % 2U) != 0U;
    }
}

static bool order_is_marked(const TreeOrder *order)
{
    size_t index;

    if (order->count != 55U) {
        return false;
    }

    for (index = 0U;
         index < (size_t)TREE_DFS_MAX_NODES;
         index += 1U) {
        if (order->items[index].key != -55 - (int)index ||
            order->items[index].flagged != ((index % 2U) != 0U)) {
            return false;
        }
    }

    return true;
}

static bool test_exact_maximum(void)
{
    TreeNode nodes[TREE_DFS_MAX_NODES];
    TreeOrder preorder;
    TreeOrder inorder;
    TreeOrder postorder;
    TreeOrder iterative;
    size_t index;

    make_right_chain(nodes, (size_t)TREE_DFS_MAX_NODES);

    CHECK(
        tree_preorder_recursive(&nodes[0], &preorder) == TREE_DFS_OK
    );
    CHECK(tree_inorder_recursive(&nodes[0], &inorder) == TREE_DFS_OK);
    CHECK(
        tree_postorder_recursive(&nodes[0], &postorder) == TREE_DFS_OK
    );
    CHECK(
        tree_preorder_iterative(&nodes[0], 1U, &iterative) ==
        TREE_DFS_OK
    );

    CHECK(preorder.count == (size_t)TREE_DFS_MAX_NODES);
    CHECK(inorder.count == (size_t)TREE_DFS_MAX_NODES);
    CHECK(postorder.count == (size_t)TREE_DFS_MAX_NODES);
    CHECK(iterative.count == (size_t)TREE_DFS_MAX_NODES);

    for (index = 0U; index < (size_t)TREE_DFS_MAX_NODES; index += 1U) {
        CHECK(preorder.items[index].key == (int)index);
        CHECK(inorder.items[index].key == (int)index);
        CHECK(iterative.items[index].key == (int)index);
        CHECK(
            postorder.items[index].key ==
            (int)((size_t)TREE_DFS_MAX_NODES - 1U - index)
        );
    }
    return true;
}

static bool test_over_maximum_preserves_output(void)
{
    TreeNode nodes[TREE_DFS_MAX_NODES + 1U];
    TreeOrder order;

    make_right_chain(nodes, (size_t)TREE_DFS_MAX_NODES + 1U);

    mark_order(&order);
    CHECK(
        tree_preorder_recursive(&nodes[0], &order) == TREE_DFS_LIMIT
    );
    CHECK(order_is_marked(&order));

    mark_order(&order);
    CHECK(tree_inorder_recursive(&nodes[0], &order) == TREE_DFS_LIMIT);
    CHECK(order_is_marked(&order));

    mark_order(&order);
    CHECK(
        tree_postorder_recursive(&nodes[0], &order) == TREE_DFS_LIMIT
    );
    CHECK(order_is_marked(&order));

    mark_order(&order);
    CHECK(
        tree_preorder_iterative(&nodes[0], 1U, &order) == TREE_DFS_LIMIT
    );
    CHECK(order_is_marked(&order));
    return true;
}

static bool test_left_descent_limit(void)
{
    TreeNode nodes[TREE_DFS_MAX_NODES + 1U];
    TreeOrder order;

    make_left_chain(nodes, (size_t)TREE_DFS_MAX_NODES + 1U);

    mark_order(&order);
    CHECK(tree_preorder_recursive(&nodes[0], &order) == TREE_DFS_LIMIT);
    CHECK(order_is_marked(&order));

    mark_order(&order);
    CHECK(tree_inorder_recursive(&nodes[0], &order) == TREE_DFS_LIMIT);
    CHECK(order_is_marked(&order));

    mark_order(&order);
    CHECK(tree_postorder_recursive(&nodes[0], &order) == TREE_DFS_LIMIT);
    CHECK(order_is_marked(&order));
    return true;
}

static bool test_node_stack_boundaries(void)
{
    TreeNode nodes[TREE_DFS_MAX_NODES];
    TreeNodeStack stack;
    const TreeNode *output = NULL;
    size_t index;

    make_right_chain(nodes, (size_t)TREE_DFS_MAX_NODES);
    CHECK(
        tree_node_stack_init(&stack, (size_t)TREE_DFS_MAX_NODES) ==
        NODE_STACK_OK
    );

    for (index = 0U; index < (size_t)TREE_DFS_MAX_NODES; index += 1U) {
        CHECK(tree_node_stack_push(&stack, &nodes[index]) == NODE_STACK_OK);
    }
    CHECK(
        tree_node_stack_push(&stack, &nodes[0]) == NODE_STACK_LIMIT
    );

    for (index = (size_t)TREE_DFS_MAX_NODES; index > 0U; index -= 1U) {
        CHECK(tree_node_stack_pop(&stack, &output) == NODE_STACK_OK);
        CHECK(output == &nodes[index - 1U]);
    }
    output = &nodes[17];
    CHECK(tree_node_stack_pop(&stack, &output) == NODE_STACK_UNDERFLOW);
    CHECK(output == &nodes[17]);
    tree_node_stack_destroy(&stack);

    CHECK(
        tree_node_stack_init(
            &stack,
            (size_t)TREE_NODE_STACK_MAX_LIMIT + 1U
        ) == NODE_STACK_LIMIT
    );
    return true;
}

static bool test_node_stack_failures(void)
{
    TreeNode nodes[5];
    TreeNodeStack stack;
    TreeNodeStack invalid = {NULL, 1U, 0U, 1U};
    const TreeNode **data_before;
    const TreeNode *items_before[4];
    const TreeNode *output;
    size_t index;
    size_t size_before;
    size_t capacity_before;
    size_t limit_before;

    make_right_chain(nodes, 5U);
    output = &nodes[4];

    CHECK(
        tree_node_stack_init(NULL, 0U) == NODE_STACK_INVALID_ARGUMENT
    );
    CHECK(
        tree_node_stack_validate(NULL) == NODE_STACK_INVALID_ARGUMENT
    );
    CHECK(
        tree_node_stack_pop(NULL, &output) == NODE_STACK_INVALID_ARGUMENT
    );
    CHECK(output == &nodes[4]);
    tree_node_stack_destroy(NULL);

    CHECK(tree_node_stack_init(&stack, 8U) == NODE_STACK_OK);
    for (index = 0U; index < 4U; index += 1U) {
        CHECK_STACK(
            tree_node_stack_push(&stack, &nodes[index]) == NODE_STACK_OK,
            &stack
        );
    }

    data_before = stack.data;
    size_before = stack.size;
    capacity_before = stack.capacity;
    limit_before = stack.limit;
    for (index = 0U; index < 4U; index += 1U) {
        items_before[index] = stack.data[index];
    }

    tree_node_stack_test_fail_next_allocation();
    CHECK_STACK(
        tree_node_stack_push(&stack, &nodes[4]) ==
        NODE_STACK_ALLOCATION,
        &stack
    );
    CHECK_STACK(stack.data == data_before, &stack);
    CHECK_STACK(stack.size == size_before, &stack);
    CHECK_STACK(stack.capacity == capacity_before, &stack);
    CHECK_STACK(stack.limit == limit_before, &stack);
    for (index = 0U; index < 4U; index += 1U) {
        CHECK_STACK(stack.data[index] == items_before[index], &stack);
    }

    CHECK_STACK(
        tree_node_stack_pop(&stack, NULL) ==
        NODE_STACK_INVALID_ARGUMENT,
        &stack
    );
    CHECK_STACK(stack.size == size_before, &stack);
    tree_node_stack_destroy(&stack);

    CHECK(tree_node_stack_init(&stack, 0U) == NODE_STACK_OK);
    CHECK_STACK(
        tree_node_stack_push(&stack, NULL) ==
        NODE_STACK_INVALID_ARGUMENT,
        &stack
    );
    CHECK_STACK(
        tree_node_stack_push(&stack, &nodes[0]) == NODE_STACK_LIMIT,
        &stack
    );
    output = &nodes[4];
    CHECK_STACK(
        tree_node_stack_pop(&stack, &output) == NODE_STACK_UNDERFLOW,
        &stack
    );
    CHECK_STACK(output == &nodes[4], &stack);
    tree_node_stack_destroy(&stack);

    CHECK(
        tree_node_stack_init(
            &stack,
            (size_t)TREE_NODE_STACK_MAX_LIMIT + 1U
        ) == NODE_STACK_LIMIT
    );
    CHECK(stack.data == NULL);
    CHECK(stack.size == 0U);
    CHECK(stack.capacity == 0U);
    CHECK(stack.limit == 0U);

    CHECK(
        tree_node_stack_validate(&invalid) == NODE_STACK_INVALID_STATE
    );
    CHECK(
        tree_node_stack_push(&invalid, &nodes[0]) ==
        NODE_STACK_INVALID_STATE
    );
    CHECK(invalid.data == NULL);
    CHECK(invalid.size == 1U);
    CHECK(invalid.capacity == 0U);
    CHECK(invalid.limit == 1U);
    tree_node_stack_destroy(&invalid);
    return true;
}

static bool test_status_names(void)
{
    CHECK(strcmp(tree_dfs_status_name(TREE_DFS_OK), "ok") == 0);
    CHECK(strcmp(
        tree_dfs_status_name(TREE_DFS_INVALID_ARGUMENT),
        "invalid argument"
    ) == 0);
    CHECK(strcmp(
        tree_dfs_status_name(TREE_DFS_LIMIT),
        "tree or Stack limit reached"
    ) == 0);
    CHECK(strcmp(
        tree_dfs_status_name(TREE_DFS_ALLOCATION),
        "allocation failed"
    ) == 0);
    CHECK(strcmp(
        tree_dfs_status_name(TREE_DFS_DUPLICATE),
        "duplicate key"
    ) == 0);
    CHECK(strcmp(
        tree_dfs_status_name(TREE_DFS_NOT_FOUND),
        "key not found"
    ) == 0);

    CHECK(strcmp(node_stack_status_name(NODE_STACK_OK), "ok") == 0);
    CHECK(strcmp(
        node_stack_status_name(NODE_STACK_INVALID_ARGUMENT),
        "invalid argument"
    ) == 0);
    CHECK(strcmp(
        node_stack_status_name(NODE_STACK_LIMIT),
        "Stack limit reached or requested limit too large"
    ) == 0);
    CHECK(strcmp(
        node_stack_status_name(NODE_STACK_UNDERFLOW),
        "Stack is empty"
    ) == 0);
    CHECK(strcmp(
        node_stack_status_name(NODE_STACK_ALLOCATION),
        "allocation failed"
    ) == 0);
    CHECK(strcmp(
        node_stack_status_name(NODE_STACK_INVALID_STATE),
        "Stack representation is invalid"
    ) == 0);
    CHECK(strcmp(
        node_stack_status_name((NodeStackStatus)99),
        "unknown NodeStackStatus"
    ) == 0);
    CHECK(strcmp(
        tree_dfs_status_name((TreeDfsStatus)99),
        "unknown TreeDfsStatus"
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

    failures += run_test(test_exact_maximum, "exact 64-node maximum");
    failures += run_test(
        test_over_maximum_preserves_output,
        "65-node rejection"
    );
    failures += run_test(
        test_left_descent_limit,
        "left-descent 65-node rejection"
    );
    failures += run_test(test_node_stack_boundaries, "node Stack boundary");
    failures += run_test(
        test_node_stack_failures,
        "node Stack failure preservation"
    );
    failures += run_test(test_status_names, "status names");

    if (failures != 0) {
        printf("%d extension test group(s) failed.\n", failures);
        return 1;
    }

    puts("All extension test groups passed.");
    return 0;
}
