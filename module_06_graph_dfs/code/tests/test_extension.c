#include "graph_dfs.h"
#include "vertex_stack.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define CHECK(condition)                                                   \
    do {                                                                   \
        if (!(condition)) {                                                \
            fprintf(stderr, "  check failed at line %d: %s\n",            \
                __LINE__, #condition);                                     \
            return false;                                                  \
        }                                                                  \
    } while (false)

#define CHECK_STACK(condition, stack_pointer)                              \
    do {                                                                   \
        if (!(condition)) {                                                \
            fprintf(stderr, "  check failed at line %d: %s\n",            \
                __LINE__, #condition);                                     \
            vertex_stack_destroy(stack_pointer);                           \
            return false;                                                  \
        }                                                                  \
    } while (false)

typedef bool (*TestFunction)(void);

static bool order_is_sequence(
    const GraphDfsOrder *order,
    size_t count
)
{
    size_t index;

    if (order->count != count) {
        return false;
    }
    for (index = 0U; index < count; ++index) {
        if (order->vertices[index] != index) {
            return false;
        }
    }
    return true;
}

static void mark_order(GraphDfsOrder *order)
{
    size_t index;

    order->count = 82U;
    for (index = 0U;
         index < (size_t)GRAPH_MAX_VERTICES;
         ++index) {
        order->vertices[index] = 300U + index;
    }
}

static bool order_is_marked(const GraphDfsOrder *order)
{
    size_t index;

    if (order->count != 82U) {
        return false;
    }
    for (index = 0U;
         index < (size_t)GRAPH_MAX_VERTICES;
         ++index) {
        if (order->vertices[index] != 300U + index) {
            return false;
        }
    }
    return true;
}

static bool test_exact_maximum_star(void)
{
    Graph graph;
    GraphDfsOrder order;
    size_t vertex;

    CHECK(
        graph_init(
            &graph,
            (size_t)GRAPH_MAX_VERTICES,
            GRAPH_DIRECTED
        ) == GRAPH_OK
    );
    for (vertex = 1U;
         vertex < (size_t)GRAPH_MAX_VERTICES;
         ++vertex) {
        CHECK(graph_add_edge(&graph, 0U, vertex) == GRAPH_OK);
    }

    CHECK(
        graph_dfs_recursive(&graph, 0U, &order) == GRAPH_DFS_OK
    );
    CHECK(order_is_sequence(&order, (size_t)GRAPH_MAX_VERTICES));

    CHECK(
        graph_dfs_iterative(
            &graph,
            0U,
            (size_t)GRAPH_MAX_VERTICES - 1U,
            &order
        ) == GRAPH_DFS_OK
    );
    CHECK(order_is_sequence(&order, (size_t)GRAPH_MAX_VERTICES));

    mark_order(&order);
    CHECK(
        graph_dfs_iterative(
            &graph,
            0U,
            (size_t)GRAPH_MAX_VERTICES - 2U,
            &order
        ) == GRAPH_DFS_LIMIT
    );
    CHECK(order_is_marked(&order));
    return true;
}

static bool test_exact_maximum_chain_and_components(void)
{
    Graph graph;
    GraphDfsOrder order;
    size_t components = 99U;
    size_t vertex;

    CHECK(
        graph_init(
            &graph,
            (size_t)GRAPH_MAX_VERTICES,
            GRAPH_DIRECTED
        ) == GRAPH_OK
    );
    for (vertex = 0U;
         vertex + 1U < (size_t)GRAPH_MAX_VERTICES;
         ++vertex) {
        CHECK(
            graph_add_edge(&graph, vertex, vertex + 1U) == GRAPH_OK
        );
    }

    CHECK(
        graph_dfs_iterative(&graph, 0U, 1U, &order) == GRAPH_DFS_OK
    );
    CHECK(order_is_sequence(&order, (size_t)GRAPH_MAX_VERTICES));
    CHECK(
        graph_dfs_recursive(&graph, 0U, &order) == GRAPH_DFS_OK
    );
    CHECK(order_is_sequence(&order, (size_t)GRAPH_MAX_VERTICES));

    CHECK(
        graph_init(
            &graph,
            (size_t)GRAPH_MAX_VERTICES,
            GRAPH_UNDIRECTED
        ) == GRAPH_OK
    );
    CHECK(
        graph_count_connected_components(&graph, &components) ==
        GRAPH_DFS_OK
    );
    CHECK(components == (size_t)GRAPH_MAX_VERTICES);
    return true;
}

static bool test_inactive_cells_are_not_active_vertices(void)
{
    Graph graph;
    GraphDfsOrder order;
    const size_t expected[] = {0U, 1U};

    CHECK(graph_init(&graph, 3U, GRAPH_DIRECTED) == GRAPH_OK);
    CHECK(graph_add_edge(&graph, 0U, 1U) == GRAPH_OK);
    graph.adjacency[GRAPH_MAX_VERTICES - 1U]
                   [GRAPH_MAX_VERTICES - 1U] = true;
    graph.adjacency[1U][GRAPH_MAX_VERTICES - 1U] = true;

    CHECK(graph_validate(&graph) == GRAPH_OK);
    CHECK(
        graph_dfs_recursive(&graph, 0U, &order) == GRAPH_DFS_OK
    );
    CHECK(order.count == 2U);
    CHECK(order.vertices[0] == expected[0]);
    CHECK(order.vertices[1] == expected[1]);
    CHECK(
        graph_dfs_iterative(&graph, 0U, 1U, &order) == GRAPH_DFS_OK
    );
    CHECK(order.count == 2U);
    CHECK(order.vertices[0] == expected[0]);
    CHECK(order.vertices[1] == expected[1]);
    return true;
}

static bool test_vertex_stack_boundaries(void)
{
    VertexStack stack;
    size_t output = 777U;
    size_t index;

    CHECK(
        vertex_stack_init(
            &stack,
            (size_t)VERTEX_STACK_MAX_LIMIT
        ) == VERTEX_STACK_OK
    );
    CHECK(vertex_stack_validate(&stack) == VERTEX_STACK_OK);

    for (index = 0U;
         index < (size_t)GRAPH_MAX_VERTICES;
         ++index) {
        CHECK_STACK(
            vertex_stack_push(&stack, index) == VERTEX_STACK_OK,
            &stack
        );
    }
    CHECK_STACK(
        stack.capacity == (size_t)GRAPH_MAX_VERTICES,
        &stack
    );
    CHECK_STACK(
        vertex_stack_push(&stack, 0U) == VERTEX_STACK_LIMIT,
        &stack
    );

    for (index = (size_t)GRAPH_MAX_VERTICES; index > 0U; --index) {
        CHECK_STACK(
            vertex_stack_pop(&stack, &output) == VERTEX_STACK_OK,
            &stack
        );
        CHECK_STACK(output == index - 1U, &stack);
    }

    output = 777U;
    CHECK_STACK(
        vertex_stack_pop(&stack, &output) == VERTEX_STACK_UNDERFLOW,
        &stack
    );
    CHECK_STACK(output == 777U, &stack);
    vertex_stack_destroy(&stack);
    CHECK(stack.data == NULL);
    CHECK(stack.size == 0U);
    CHECK(stack.capacity == 0U);
    CHECK(stack.limit == 0U);
    return true;
}

static bool test_vertex_stack_failure_atomicity(void)
{
    VertexStack stack;
    VertexStack invalid = {NULL, 1U, 0U, 1U};
    size_t *data_before;
    size_t values_before[4];
    size_t output = 888U;
    size_t size_before;
    size_t capacity_before;
    size_t limit_before;
    size_t index;

    CHECK(
        vertex_stack_init(NULL, 0U) ==
        VERTEX_STACK_INVALID_ARGUMENT
    );
    CHECK(
        vertex_stack_validate(NULL) ==
        VERTEX_STACK_INVALID_ARGUMENT
    );
    CHECK(
        vertex_stack_pop(NULL, &output) ==
        VERTEX_STACK_INVALID_ARGUMENT
    );
    CHECK(output == 888U);
    vertex_stack_destroy(NULL);

    CHECK(vertex_stack_init(&stack, 6U) == VERTEX_STACK_OK);
    for (index = 0U; index < 4U; ++index) {
        CHECK_STACK(
            vertex_stack_push(&stack, index) == VERTEX_STACK_OK,
            &stack
        );
    }

    data_before = stack.data;
    size_before = stack.size;
    capacity_before = stack.capacity;
    limit_before = stack.limit;
    for (index = 0U; index < 4U; ++index) {
        values_before[index] = stack.data[index];
    }

    vertex_stack_test_fail_next_allocation();
    CHECK_STACK(
        vertex_stack_push(&stack, 4U) == VERTEX_STACK_ALLOCATION,
        &stack
    );
    CHECK_STACK(stack.data == data_before, &stack);
    CHECK_STACK(stack.size == size_before, &stack);
    CHECK_STACK(stack.capacity == capacity_before, &stack);
    CHECK_STACK(stack.limit == limit_before, &stack);
    for (index = 0U; index < 4U; ++index) {
        CHECK_STACK(stack.data[index] == values_before[index], &stack);
    }

    CHECK_STACK(
        vertex_stack_push(&stack, 4U) == VERTEX_STACK_OK,
        &stack
    );
    CHECK_STACK(stack.capacity == 6U, &stack);
    CHECK_STACK(
        vertex_stack_push(&stack, 5U) == VERTEX_STACK_OK,
        &stack
    );
    CHECK_STACK(
        vertex_stack_push(&stack, 6U) == VERTEX_STACK_LIMIT,
        &stack
    );
    CHECK_STACK(
        vertex_stack_push(
            &stack,
            (size_t)GRAPH_MAX_VERTICES
        ) == VERTEX_STACK_INVALID_ARGUMENT,
        &stack
    );
    CHECK_STACK(
        vertex_stack_pop(&stack, NULL) ==
        VERTEX_STACK_INVALID_ARGUMENT,
        &stack
    );
    CHECK_STACK(stack.size == 6U, &stack);
    vertex_stack_destroy(&stack);

    CHECK(vertex_stack_init(&stack, 0U) == VERTEX_STACK_OK);
    CHECK_STACK(
        vertex_stack_push(&stack, 0U) == VERTEX_STACK_LIMIT,
        &stack
    );
    output = 888U;
    CHECK_STACK(
        vertex_stack_pop(&stack, &output) ==
        VERTEX_STACK_UNDERFLOW,
        &stack
    );
    CHECK_STACK(output == 888U, &stack);
    vertex_stack_destroy(&stack);

    CHECK(
        vertex_stack_init(
            &stack,
            (size_t)VERTEX_STACK_MAX_LIMIT + 1U
        ) == VERTEX_STACK_LIMIT
    );
    CHECK(stack.data == NULL);
    CHECK(stack.size == 0U);
    CHECK(stack.capacity == 0U);
    CHECK(stack.limit == 0U);

    CHECK(
        vertex_stack_validate(&invalid) ==
        VERTEX_STACK_INVALID_STATE
    );
    CHECK(
        vertex_stack_push(&invalid, 0U) ==
        VERTEX_STACK_INVALID_STATE
    );
    CHECK(invalid.data == NULL);
    CHECK(invalid.size == 1U);
    CHECK(invalid.capacity == 0U);
    CHECK(invalid.limit == 1U);
    vertex_stack_destroy(&invalid);
    return true;
}

static bool test_status_names(void)
{
    CHECK(strcmp(
        graph_dfs_status_name(GRAPH_DFS_OK),
        "ok"
    ) == 0);
    CHECK(strcmp(
        graph_dfs_status_name(GRAPH_DFS_INVALID_ARGUMENT),
        "invalid argument"
    ) == 0);
    CHECK(strcmp(
        graph_dfs_status_name(GRAPH_DFS_OUT_OF_RANGE),
        "start vertex out of range"
    ) == 0);
    CHECK(strcmp(
        graph_dfs_status_name(GRAPH_DFS_INVALID_GRAPH),
        "graph does not satisfy required representation rules"
    ) == 0);
    CHECK(strcmp(
        graph_dfs_status_name(GRAPH_DFS_REQUIRES_UNDIRECTED),
        "operation requires an undirected graph"
    ) == 0);
    CHECK(strcmp(
        graph_dfs_status_name(GRAPH_DFS_LIMIT),
        "vertex Stack limit reached or requested limit too large"
    ) == 0);
    CHECK(strcmp(
        graph_dfs_status_name(GRAPH_DFS_ALLOCATION),
        "allocation failed"
    ) == 0);
    CHECK(strcmp(
        graph_dfs_status_name((GraphDfsStatus)99),
        "unknown GraphDfsStatus"
    ) == 0);

    CHECK(strcmp(
        vertex_stack_status_name(VERTEX_STACK_OK),
        "ok"
    ) == 0);
    CHECK(strcmp(
        vertex_stack_status_name(VERTEX_STACK_INVALID_ARGUMENT),
        "invalid argument"
    ) == 0);
    CHECK(strcmp(
        vertex_stack_status_name(VERTEX_STACK_LIMIT),
        "Stack limit reached or requested limit too large"
    ) == 0);
    CHECK(strcmp(
        vertex_stack_status_name(VERTEX_STACK_UNDERFLOW),
        "Stack is empty"
    ) == 0);
    CHECK(strcmp(
        vertex_stack_status_name(VERTEX_STACK_ALLOCATION),
        "allocation failed"
    ) == 0);
    CHECK(strcmp(
        vertex_stack_status_name(VERTEX_STACK_INVALID_STATE),
        "Stack representation is invalid"
    ) == 0);
    CHECK(strcmp(
        vertex_stack_status_name((VertexStackStatus)99),
        "unknown VertexStackStatus"
    ) == 0);
    return true;
}

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
        test_exact_maximum_star,
        "exact 16-vertex star and Stack frontier"
    );
    failures += run_test(
        test_exact_maximum_chain_and_components,
        "exact 16-vertex chain and isolated components"
    );
    failures += run_test(
        test_inactive_cells_are_not_active_vertices,
        "inactive matrix cells remain inactive"
    );
    failures += run_test(
        test_vertex_stack_boundaries,
        "vertex Stack boundaries and LIFO"
    );
    failures += run_test(
        test_vertex_stack_failure_atomicity,
        "vertex Stack failure atomicity"
    );
    failures += run_test(test_status_names, "status names");

    if (failures != 0) {
        printf("%d extension test group(s) failed.\n", failures);
        return 1;
    }

    puts("All extension test groups passed.");
    return 0;
}
