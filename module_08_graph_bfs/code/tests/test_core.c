#include "graph_bfs.h"
#include "vertex_queue.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#ifndef GRAPH_BFS_TESTING
#error "Core tests require -DGRAPH_BFS_TESTING."
#endif

#define CHECK(condition)                                                   \
    do {                                                                   \
        if (!(condition)) {                                                \
            fprintf(stderr, "  check failed at line %d: %s\n",            \
                __LINE__, #condition);                                     \
            return false;                                                  \
        }                                                                  \
    } while (false)

#define CHECK_LIST(condition, list_pointer)                                \
    do {                                                                   \
        if (!(condition)) {                                                \
            fprintf(stderr, "  check failed at line %d: %s\n",            \
                __LINE__, #condition);                                     \
            graph_adj_list_destroy(list_pointer);                          \
            return false;                                                  \
        }                                                                  \
    } while (false)

typedef bool (*TestFunction)(void);

static const size_t canonical_edges[10][2] = {
    {0U, 1U},
    {0U, 2U},
    {1U, 3U},
    {1U, 4U},
    {2U, 4U},
    {2U, 5U},
    {3U, 6U},
    {4U, 6U},
    {5U, 4U},
    {6U, 1U}
};

static bool make_canonical_matrix(Graph *graph)
{
    size_t index;

    if (graph_init(graph, 8U, GRAPH_DIRECTED) != GRAPH_OK) {
        return false;
    }
    for (index = 0U; index < 10U; ++index) {
        if (graph_add_edge(
                graph,
                canonical_edges[index][0],
                canonical_edges[index][1]
            ) != GRAPH_OK) {
            return false;
        }
    }
    return true;
}

static bool make_canonical_list(GraphAdjList *graph)
{
    const size_t insertion_order[10] = {
        9U, 5U, 3U, 7U, 0U, 8U, 2U, 6U, 1U, 4U
    };
    size_t index;

    if (graph_adj_list_init(
            graph,
            8U,
            GRAPH_DIRECTED
        ) != GRAPH_ADJ_LIST_OK) {
        return false;
    }

    for (index = 0U; index < 10U; ++index) {
        size_t edge_index = insertion_order[index];

        if (graph_adj_list_add_edge(
                graph,
                canonical_edges[edge_index][0],
                canonical_edges[edge_index][1]
            ) != GRAPH_ADJ_LIST_OK) {
            graph_adj_list_destroy(graph);
            return false;
        }
    }
    return true;
}

static void mark_result(GraphBfsResult *result)
{
    size_t index;

    result->vertex_count = 91U;
    result->source = 92U;
    result->visit_count = 93U;
    for (index = 0U;
         index < (size_t)GRAPH_MAX_VERTICES;
         ++index) {
        result->visit_order[index] = 100U + index;
        result->discovered[index] = (index % 2U) != 0U;
        result->distance[index] = 200U + index;
        result->predecessor[index] = 300U + index;
    }
}

static bool result_is_marked(const GraphBfsResult *result)
{
    size_t index;

    if (result->vertex_count != 91U ||
        result->source != 92U ||
        result->visit_count != 93U) {
        return false;
    }
    for (index = 0U;
         index < (size_t)GRAPH_MAX_VERTICES;
         ++index) {
        if (result->visit_order[index] != 100U + index ||
            result->discovered[index] != ((index % 2U) != 0U) ||
            result->distance[index] != 200U + index ||
            result->predecessor[index] != 300U + index) {
            return false;
        }
    }
    return true;
}

static void mark_path(GraphBfsPath *path)
{
    size_t index;

    path->count = 77U;
    for (index = 0U;
         index < (size_t)GRAPH_MAX_VERTICES;
         ++index) {
        path->vertices[index] = 500U + index;
    }
}

static bool path_is_marked(const GraphBfsPath *path)
{
    size_t index;

    if (path->count != 77U) {
        return false;
    }
    for (index = 0U;
         index < (size_t)GRAPH_MAX_VERTICES;
         ++index) {
        if (path->vertices[index] != 500U + index) {
            return false;
        }
    }
    return true;
}

static bool results_equal(
    const GraphBfsResult *left,
    const GraphBfsResult *right
)
{
    size_t index;

    if (left->vertex_count != right->vertex_count ||
        left->source != right->source ||
        left->visit_count != right->visit_count) {
        return false;
    }
    for (index = 0U;
         index < (size_t)GRAPH_MAX_VERTICES;
         ++index) {
        if (left->visit_order[index] != right->visit_order[index] ||
            left->discovered[index] != right->discovered[index] ||
            left->distance[index] != right->distance[index] ||
            left->predecessor[index] != right->predecessor[index]) {
            return false;
        }
    }
    return true;
}

static bool canonical_result_matches(const GraphBfsResult *result)
{
    const size_t expected_order[7] = {
        0U, 1U, 2U, 3U, 4U, 5U, 6U
    };
    const size_t expected_distance[8] = {
        0U, 1U, 1U, 2U, 2U, 2U, 3U,
        GRAPH_BFS_NO_DISTANCE
    };
    const size_t expected_predecessor[8] = {
        GRAPH_BFS_NO_VERTEX, 0U, 0U, 1U, 1U, 2U, 3U,
        GRAPH_BFS_NO_VERTEX
    };
    size_t index;

    if (result->vertex_count != 8U ||
        result->source != 0U ||
        result->visit_count != 7U) {
        return false;
    }

    for (index = 0U; index < 7U; ++index) {
        if (result->visit_order[index] != expected_order[index]) {
            return false;
        }
    }
    for (index = 7U;
         index < (size_t)GRAPH_MAX_VERTICES;
         ++index) {
        if (result->visit_order[index] != GRAPH_BFS_NO_VERTEX) {
            return false;
        }
    }

    for (index = 0U; index < 8U; ++index) {
        bool expected_discovered = index != 7U;

        if (result->discovered[index] != expected_discovered ||
            result->distance[index] != expected_distance[index] ||
            result->predecessor[index] !=
                expected_predecessor[index]) {
            return false;
        }
    }
    for (index = 8U;
         index < (size_t)GRAPH_MAX_VERTICES;
         ++index) {
        if (result->discovered[index] ||
            result->distance[index] != GRAPH_BFS_NO_DISTANCE ||
            result->predecessor[index] != GRAPH_BFS_NO_VERTEX) {
            return false;
        }
    }
    return true;
}

static bool path_matches(
    const GraphBfsPath *path,
    const size_t *vertices,
    size_t count
)
{
    size_t index;

    if (path->count != count) {
        return false;
    }
    for (index = 0U; index < count; ++index) {
        if (path->vertices[index] != vertices[index]) {
            return false;
        }
    }
    for (index = count;
         index < (size_t)GRAPH_MAX_VERTICES;
         ++index) {
        if (path->vertices[index] != GRAPH_BFS_NO_VERTEX) {
            return false;
        }
    }
    return true;
}

static bool test_canonical_matrix_and_paths(void)
{
    Graph graph;
    GraphBfsResult result;
    GraphBfsPath path;
    const size_t path_to_six[4] = {0U, 1U, 3U, 6U};
    const size_t path_to_four[3] = {0U, 1U, 4U};
    const size_t path_to_source[1] = {0U};

    CHECK(make_canonical_matrix(&graph));
    CHECK(
        graph_bfs_matrix(&graph, 0U, 3U, &result) ==
        GRAPH_BFS_OK
    );
    CHECK(canonical_result_matches(&result));
    CHECK(graph_bfs_result_validate(&result) == GRAPH_BFS_OK);

    CHECK(
        graph_bfs_reconstruct_path(&result, 6U, &path) ==
        GRAPH_BFS_OK
    );
    CHECK(path_matches(&path, path_to_six, 4U));
    CHECK(
        graph_bfs_reconstruct_path(&result, 4U, &path) ==
        GRAPH_BFS_OK
    );
    CHECK(path_matches(&path, path_to_four, 3U));
    CHECK(
        graph_bfs_reconstruct_path(&result, 0U, &path) ==
        GRAPH_BFS_OK
    );
    CHECK(path_matches(&path, path_to_source, 1U));
    return true;
}

static bool test_list_equivalence_and_sorted_rows(void)
{
    Graph matrix;
    GraphAdjList list = {0};
    GraphBfsResult matrix_result;
    GraphBfsResult list_result;
    GraphNeighbors neighbors;

    CHECK(make_canonical_matrix(&matrix));
    CHECK(make_canonical_list(&list));
    CHECK_LIST(
        graph_adj_list_validate(&list) == GRAPH_ADJ_LIST_OK,
        &list
    );
    CHECK_LIST(
        graph_adj_list_out_neighbors(&list, 2U, &neighbors) ==
        GRAPH_ADJ_LIST_OK,
        &list
    );
    CHECK_LIST(neighbors.count == 2U, &list);
    CHECK_LIST(neighbors.vertices[0] == 4U, &list);
    CHECK_LIST(neighbors.vertices[1] == 5U, &list);

    CHECK_LIST(
        graph_bfs_matrix(&matrix, 0U, 3U, &matrix_result) ==
        GRAPH_BFS_OK,
        &list
    );
    CHECK_LIST(
        graph_bfs_list(&list, 0U, 3U, &list_result) ==
        GRAPH_BFS_OK,
        &list
    );
    CHECK_LIST(canonical_result_matches(&list_result), &list);
    CHECK_LIST(results_equal(&matrix_result, &list_result), &list);

    graph_adj_list_destroy(&list);
    return true;
}

static bool test_limits_and_unreachable_preservation(void)
{
    Graph graph;
    GraphBfsResult result;
    GraphBfsPath path;

    CHECK(make_canonical_matrix(&graph));

    mark_result(&result);
    CHECK(
        graph_bfs_matrix(&graph, 0U, 2U, &result) ==
        GRAPH_BFS_LIMIT
    );
    CHECK(result_is_marked(&result));

    CHECK(
        graph_bfs_matrix(&graph, 0U, 3U, &result) ==
        GRAPH_BFS_OK
    );
    mark_path(&path);
    CHECK(
        graph_bfs_reconstruct_path(&result, 7U, &path) ==
        GRAPH_BFS_UNREACHABLE
    );
    CHECK(path_is_marked(&path));

    mark_result(&result);
    CHECK(
        graph_bfs_matrix(&graph, 0U, 0U, &result) ==
        GRAPH_BFS_LIMIT
    );
    CHECK(result_is_marked(&result));
    CHECK(
        graph_bfs_matrix(
            &graph,
            0U,
            (size_t)GRAPH_MAX_VERTICES + 1U,
            &result
        ) == GRAPH_BFS_LIMIT
    );
    CHECK(result_is_marked(&result));
    return true;
}

static bool test_empty_singleton_undirected_and_arguments(void)
{
    Graph graph;
    GraphBfsResult result;
    GraphBfsPath path;
    const size_t expected_order[4] = {0U, 1U, 2U, 3U};

    CHECK(graph_init(&graph, 0U, GRAPH_DIRECTED) == GRAPH_OK);
    mark_result(&result);
    CHECK(
        graph_bfs_matrix(
            &graph,
            0U,
            (size_t)GRAPH_MAX_VERTICES + 1U,
            &result
        ) == GRAPH_BFS_OUT_OF_RANGE
    );
    CHECK(result_is_marked(&result));

    CHECK(graph_init(&graph, 1U, GRAPH_DIRECTED) == GRAPH_OK);
    CHECK(
        graph_bfs_matrix(&graph, 0U, 1U, &result) ==
        GRAPH_BFS_OK
    );
    CHECK(result.vertex_count == 1U);
    CHECK(result.visit_count == 1U);
    CHECK(result.visit_order[0] == 0U);
    CHECK(result.discovered[0]);
    CHECK(result.distance[0] == 0U);
    CHECK(result.predecessor[0] == GRAPH_BFS_NO_VERTEX);

    CHECK(graph_init(&graph, 4U, GRAPH_UNDIRECTED) == GRAPH_OK);
    CHECK(graph_add_edge(&graph, 0U, 2U) == GRAPH_OK);
    CHECK(graph_add_edge(&graph, 0U, 1U) == GRAPH_OK);
    CHECK(graph_add_edge(&graph, 2U, 3U) == GRAPH_OK);
    CHECK(
        graph_bfs_matrix(&graph, 0U, 2U, &result) ==
        GRAPH_BFS_OK
    );
    CHECK(result.visit_count == 4U);
    CHECK(
        memcmp(
            result.visit_order,
            expected_order,
            sizeof expected_order
        ) == 0
    );
    CHECK(result.distance[3] == 2U);
    CHECK(result.predecessor[3] == 2U);

    mark_result(&result);
    CHECK(
        graph_bfs_matrix(NULL, 0U, 1U, &result) ==
        GRAPH_BFS_INVALID_ARGUMENT
    );
    CHECK(result_is_marked(&result));
    CHECK(
        graph_bfs_matrix(&graph, 0U, 1U, NULL) ==
        GRAPH_BFS_INVALID_ARGUMENT
    );
    CHECK(
        graph_bfs_list(NULL, 0U, 1U, &result) ==
        GRAPH_BFS_INVALID_ARGUMENT
    );
    CHECK(
        graph_bfs_reconstruct_path(NULL, 0U, &path) ==
        GRAPH_BFS_INVALID_ARGUMENT
    );
    CHECK(
        graph_bfs_reconstruct_path(&result, 0U, NULL) ==
        GRAPH_BFS_INVALID_ARGUMENT
    );
    return true;
}

static bool test_vertex_queue_directly(void)
{
    VertexQueue queue = {{0U}, 0U, 0U, 0U};
    VertexQueue invalid = {{0U}, 2U, 0U, 1U};
    size_t output = 99U;

    CHECK(vertex_queue_init(&queue, 3U) == VERTEX_QUEUE_OK);
    CHECK(vertex_queue_enqueue(&queue, 1U) == VERTEX_QUEUE_OK);
    CHECK(vertex_queue_enqueue(&queue, 2U) == VERTEX_QUEUE_OK);
    CHECK(vertex_queue_enqueue(&queue, 3U) == VERTEX_QUEUE_OK);
    CHECK(vertex_queue_enqueue(&queue, 4U) == VERTEX_QUEUE_LIMIT);
    CHECK(queue.size == 3U && queue.head == 0U);

    CHECK(vertex_queue_dequeue(&queue, &output) == VERTEX_QUEUE_OK);
    CHECK(output == 1U);
    CHECK(vertex_queue_enqueue(&queue, 4U) == VERTEX_QUEUE_OK);
    CHECK(queue.head == 1U && queue.size == 3U);
    CHECK(vertex_queue_validate(&queue) == VERTEX_QUEUE_OK);

    CHECK(vertex_queue_dequeue(&queue, &output) == VERTEX_QUEUE_OK);
    CHECK(output == 2U);
    CHECK(vertex_queue_dequeue(&queue, &output) == VERTEX_QUEUE_OK);
    CHECK(output == 3U);
    CHECK(vertex_queue_dequeue(&queue, &output) == VERTEX_QUEUE_OK);
    CHECK(output == 4U);
    CHECK(queue.head == 0U && queue.size == 0U);

    output = 99U;
    CHECK(
        vertex_queue_dequeue(&queue, &output) ==
        VERTEX_QUEUE_UNDERFLOW
    );
    CHECK(output == 99U);
    CHECK(
        vertex_queue_enqueue(
            &queue,
            (size_t)GRAPH_MAX_VERTICES
        ) == VERTEX_QUEUE_INVALID_ARGUMENT
    );

    invalid.data[0] = (size_t)GRAPH_MAX_VERTICES;
    CHECK(
        vertex_queue_validate(&invalid) ==
        VERTEX_QUEUE_INVALID_STATE
    );
    output = 99U;
    CHECK(
        vertex_queue_dequeue(&invalid, &output) ==
        VERTEX_QUEUE_INVALID_STATE
    );
    CHECK(output == 99U);
    return true;
}

static bool test_adjacency_list_operations_and_allocation(void)
{
    GraphAdjList list = {0};
    GraphNeighbors neighbors;
    bool has_edge = false;
    size_t baseline = graph_adj_list_test_live_array_count();

    CHECK(
        graph_adj_list_init(&list, 6U, GRAPH_DIRECTED) ==
        GRAPH_ADJ_LIST_OK
    );
    CHECK_LIST(
        graph_adj_list_add_edge(&list, 0U, 3U) ==
        GRAPH_ADJ_LIST_OK,
        &list
    );
    CHECK_LIST(
        graph_adj_list_add_edge(&list, 0U, 1U) ==
        GRAPH_ADJ_LIST_OK,
        &list
    );
    CHECK_LIST(
        graph_adj_list_out_neighbors(&list, 0U, &neighbors) ==
        GRAPH_ADJ_LIST_OK,
        &list
    );
    CHECK_LIST(neighbors.count == 2U, &list);
    CHECK_LIST(neighbors.vertices[0] == 1U, &list);
    CHECK_LIST(neighbors.vertices[1] == 3U, &list);
    CHECK_LIST(
        graph_adj_list_has_edge(&list, 0U, 3U, &has_edge) ==
        GRAPH_ADJ_LIST_OK,
        &list
    );
    CHECK_LIST(has_edge, &list);
    CHECK_LIST(
        graph_adj_list_add_edge(&list, 0U, 3U) ==
        GRAPH_ADJ_LIST_EDGE_EXISTS,
        &list
    );
    CHECK_LIST(
        graph_adj_list_add_edge(&list, 0U, 0U) ==
        GRAPH_ADJ_LIST_SELF_LOOP,
        &list
    );
    CHECK_LIST(
        graph_adj_list_remove_edge(&list, 0U, 3U) ==
        GRAPH_ADJ_LIST_OK,
        &list
    );
    CHECK_LIST(
        graph_adj_list_remove_edge(&list, 0U, 3U) ==
        GRAPH_ADJ_LIST_EDGE_ABSENT,
        &list
    );
    graph_adj_list_destroy(&list);
    CHECK(graph_adj_list_test_live_array_count() == baseline);

    CHECK(
        graph_adj_list_init(&list, 4U, GRAPH_UNDIRECTED) ==
        GRAPH_ADJ_LIST_OK
    );
    CHECK_LIST(
        graph_adj_list_add_edge(&list, 0U, 2U) ==
        GRAPH_ADJ_LIST_OK,
        &list
    );
    CHECK_LIST(
        graph_adj_list_has_edge(&list, 2U, 0U, &has_edge) ==
        GRAPH_ADJ_LIST_OK,
        &list
    );
    CHECK_LIST(has_edge, &list);
    CHECK_LIST(
        graph_adj_list_validate(&list) == GRAPH_ADJ_LIST_OK,
        &list
    );
    graph_adj_list_destroy(&list);
    CHECK(graph_adj_list_test_live_array_count() == baseline);

    CHECK(
        graph_adj_list_init(&list, 3U, GRAPH_DIRECTED) ==
        GRAPH_ADJ_LIST_OK
    );
    graph_adj_list_test_fail_allocation_after(0U);
    CHECK_LIST(
        graph_adj_list_add_edge(&list, 0U, 1U) ==
        GRAPH_ADJ_LIST_ALLOCATION,
        &list
    );
    CHECK_LIST(list.neighbors[0].data == NULL, &list);
    CHECK_LIST(list.neighbors[0].size == 0U, &list);
    CHECK_LIST(list.neighbors[0].capacity == 0U, &list);
    CHECK_LIST(
        graph_adj_list_test_live_array_count() == baseline,
        &list
    );
    graph_adj_list_destroy(&list);
    CHECK(graph_adj_list_test_live_array_count() == baseline);
    return true;
}

static bool test_invalid_graphs_and_results_preserve_outputs(void)
{
    Graph matrix;
    GraphAdjList list = {0};
    GraphBfsResult result;
    GraphBfsResult valid;
    GraphBfsResult malformed;
    GraphBfsPath path;
    size_t temporary;

    CHECK(graph_init(&matrix, 3U, GRAPH_DIRECTED) == GRAPH_OK);
    matrix.adjacency[1][1] = true;
    mark_result(&result);
    CHECK(
        graph_bfs_matrix(&matrix, 0U, 3U, &result) ==
        GRAPH_BFS_INVALID_GRAPH
    );
    CHECK(result_is_marked(&result));

    CHECK(graph_init(&matrix, 3U, GRAPH_UNDIRECTED) == GRAPH_OK);
    matrix.adjacency[0][2] = true;
    CHECK(
        graph_bfs_matrix(&matrix, 9U, 3U, &result) ==
        GRAPH_BFS_INVALID_GRAPH
    );
    CHECK(result_is_marked(&result));

    CHECK(make_canonical_list(&list));
    temporary = list.neighbors[0].data[0];
    list.neighbors[0].data[0] = list.neighbors[0].data[1];
    list.neighbors[0].data[1] = temporary;
    CHECK_LIST(
        graph_bfs_list(&list, 0U, 3U, &result) ==
        GRAPH_BFS_INVALID_GRAPH,
        &list
    );
    CHECK_LIST(result_is_marked(&result), &list);
    temporary = list.neighbors[0].data[0];
    list.neighbors[0].data[0] = list.neighbors[0].data[1];
    list.neighbors[0].data[1] = temporary;
    graph_adj_list_destroy(&list);

    CHECK(make_canonical_matrix(&matrix));
    CHECK(
        graph_bfs_matrix(&matrix, 0U, 3U, &valid) ==
        GRAPH_BFS_OK
    );
    malformed = valid;
    malformed.predecessor[6] = 15U;
    CHECK(
        graph_bfs_result_validate(&malformed) ==
        GRAPH_BFS_INVALID_RESULT
    );
    mark_path(&path);
    CHECK(
        graph_bfs_reconstruct_path(&malformed, 6U, &path) ==
        GRAPH_BFS_INVALID_RESULT
    );
    CHECK(path_is_marked(&path));

    CHECK(
        graph_bfs_reconstruct_path(&valid, 8U, &path) ==
        GRAPH_BFS_OUT_OF_RANGE
    );
    CHECK(path_is_marked(&path));
    return true;
}

static bool test_status_names(void)
{
    CHECK(strcmp(
        graph_bfs_status_name(GRAPH_BFS_OK),
        "ok"
    ) == 0);
    CHECK(strcmp(
        graph_bfs_status_name(GRAPH_BFS_INVALID_ARGUMENT),
        "invalid argument"
    ) == 0);
    CHECK(strcmp(
        graph_bfs_status_name(GRAPH_BFS_OUT_OF_RANGE),
        "source or destination vertex out of range"
    ) == 0);
    CHECK(strcmp(
        graph_bfs_status_name(GRAPH_BFS_INVALID_GRAPH),
        "graph does not satisfy required representation rules"
    ) == 0);
    CHECK(strcmp(
        graph_bfs_status_name(GRAPH_BFS_LIMIT),
        "vertex Queue limit reached or requested limit too large"
    ) == 0);
    CHECK(strcmp(
        graph_bfs_status_name(GRAPH_BFS_UNREACHABLE),
        "destination is unreachable from the source"
    ) == 0);
    CHECK(strcmp(
        graph_bfs_status_name(GRAPH_BFS_INVALID_RESULT),
        "BFS result is invalid"
    ) == 0);
    CHECK(strcmp(
        graph_bfs_status_name((GraphBfsStatus)99),
        "unknown GraphBfsStatus"
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
        test_canonical_matrix_and_paths,
        "canonical matrix state and paths"
    );
    failures += run_test(
        test_list_equivalence_and_sorted_rows,
        "matrix/list equivalence and sorted rows"
    );
    failures += run_test(
        test_limits_and_unreachable_preservation,
        "Queue limits and unreachable preservation"
    );
    failures += run_test(
        test_empty_singleton_undirected_and_arguments,
        "empty, singleton, undirected, and arguments"
    );
    failures += run_test(
        test_vertex_queue_directly,
        "direct circular vertex Queue"
    );
    failures += run_test(
        test_adjacency_list_operations_and_allocation,
        "adjacency-list operations and allocation"
    );
    failures += run_test(
        test_invalid_graphs_and_results_preserve_outputs,
        "invalid graph/result preservation"
    );
    failures += run_test(test_status_names, "BFS status names");

    if (failures != 0) {
        printf("%d core test group(s) failed.\n", failures);
        return 1;
    }

    puts("All core test groups passed.");
    return 0;
}
