#include "graph_bfs.h"
#include "vertex_queue.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#ifndef GRAPH_BFS_TESTING
#error "Extension tests require -DGRAPH_BFS_TESTING."
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
    {0U, 1U}, {0U, 2U}, {1U, 3U}, {1U, 4U}, {2U, 4U},
    {2U, 5U}, {3U, 6U}, {4U, 6U}, {5U, 4U}, {6U, 1U}
};

typedef struct {
    size_t vertex_count;
    GraphKind kind;
    const size_t *data[GRAPH_MAX_VERTICES];
    size_t size[GRAPH_MAX_VERTICES];
    size_t capacity[GRAPH_MAX_VERTICES];
    size_t values[GRAPH_MAX_VERTICES][GRAPH_MAX_VERTICES];
} ListSnapshot;

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
    size_t cursor;

    if (graph_adj_list_init(
            graph,
            8U,
            GRAPH_DIRECTED
        ) != GRAPH_ADJ_LIST_OK) {
        return false;
    }
    for (cursor = 10U; cursor > 0U; --cursor) {
        size_t index = cursor - 1U;

        if (graph_adj_list_add_edge(
                graph,
                canonical_edges[index][0],
                canonical_edges[index][1]
            ) != GRAPH_ADJ_LIST_OK) {
            graph_adj_list_destroy(graph);
            return false;
        }
    }
    return true;
}

static void snapshot_list(
    const GraphAdjList *graph,
    ListSnapshot *snapshot
)
{
    size_t vertex;

    snapshot->vertex_count = graph->vertex_count;
    snapshot->kind = graph->kind;
    for (vertex = 0U;
         vertex < (size_t)GRAPH_MAX_VERTICES;
         ++vertex) {
        size_t index;

        snapshot->data[vertex] = graph->neighbors[vertex].data;
        snapshot->size[vertex] = graph->neighbors[vertex].size;
        snapshot->capacity[vertex] =
            graph->neighbors[vertex].capacity;
        for (index = 0U;
             index < graph->neighbors[vertex].size;
             ++index) {
            snapshot->values[vertex][index] =
                graph->neighbors[vertex].data[index];
        }
    }
}

static bool list_matches_snapshot(
    const GraphAdjList *graph,
    const ListSnapshot *snapshot
)
{
    size_t vertex;

    if (graph->vertex_count != snapshot->vertex_count ||
        graph->kind != snapshot->kind) {
        return false;
    }

    for (vertex = 0U;
         vertex < (size_t)GRAPH_MAX_VERTICES;
         ++vertex) {
        size_t index;

        if (graph->neighbors[vertex].data != snapshot->data[vertex] ||
            graph->neighbors[vertex].size != snapshot->size[vertex] ||
            graph->neighbors[vertex].capacity !=
                snapshot->capacity[vertex]) {
            return false;
        }
        for (index = 0U;
             index < graph->neighbors[vertex].size;
             ++index) {
            if (graph->neighbors[vertex].data[index] !=
                snapshot->values[vertex][index]) {
                return false;
            }
        }
    }
    return true;
}

static bool matrices_equal(const Graph *left, const Graph *right)
{
    size_t row;
    size_t column;

    if (left->vertex_count != right->vertex_count ||
        left->kind != right->kind) {
        return false;
    }
    for (row = 0U;
         row < (size_t)GRAPH_MAX_VERTICES;
         ++row) {
        for (column = 0U;
             column < (size_t)GRAPH_MAX_VERTICES;
             ++column) {
            if (left->adjacency[row][column] !=
                right->adjacency[row][column]) {
                return false;
            }
        }
    }
    return true;
}

static void mark_result(GraphBfsResult *result)
{
    size_t index;

    result->vertex_count = 41U;
    result->source = 42U;
    result->visit_count = 43U;
    for (index = 0U;
         index < (size_t)GRAPH_MAX_VERTICES;
         ++index) {
        result->visit_order[index] = 100U + index;
        result->discovered[index] = (index % 2U) == 0U;
        result->distance[index] = 200U + index;
        result->predecessor[index] = 300U + index;
    }
}

static bool result_is_marked(const GraphBfsResult *result)
{
    size_t index;

    if (result->vertex_count != 41U ||
        result->source != 42U ||
        result->visit_count != 43U) {
        return false;
    }
    for (index = 0U;
         index < (size_t)GRAPH_MAX_VERTICES;
         ++index) {
        if (result->visit_order[index] != 100U + index ||
            result->discovered[index] != ((index % 2U) == 0U) ||
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

    path->count = 55U;
    for (index = 0U;
         index < (size_t)GRAPH_MAX_VERTICES;
         ++index) {
        path->vertices[index] = 600U + index;
    }
}

static bool path_is_marked(const GraphBfsPath *path)
{
    size_t index;

    if (path->count != 55U) {
        return false;
    }
    for (index = 0U;
         index < (size_t)GRAPH_MAX_VERTICES;
         ++index) {
        if (path->vertices[index] != 600U + index) {
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

static bool test_exact_maximum_chain_and_star(void)
{
    Graph graph;
    GraphBfsResult result;
    GraphBfsPath path;
    size_t limit;
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
            graph_add_edge(&graph, vertex, vertex + 1U) ==
            GRAPH_OK
        );
    }
    CHECK(
        graph_bfs_matrix(&graph, 0U, 1U, &result) ==
        GRAPH_BFS_OK
    );
    CHECK(result.visit_count == (size_t)GRAPH_MAX_VERTICES);
    for (vertex = 0U;
         vertex < (size_t)GRAPH_MAX_VERTICES;
         ++vertex) {
        CHECK(result.visit_order[vertex] == vertex);
        CHECK(result.distance[vertex] == vertex);
        CHECK(
            result.predecessor[vertex] ==
            (vertex == 0U
                ? GRAPH_BFS_NO_VERTEX
                : vertex - 1U)
        );
    }
    CHECK(
        graph_bfs_reconstruct_path(
            &result,
            (size_t)GRAPH_MAX_VERTICES - 1U,
            &path
        ) == GRAPH_BFS_OK
    );
    CHECK(path.count == (size_t)GRAPH_MAX_VERTICES);
    for (vertex = 0U;
         vertex < (size_t)GRAPH_MAX_VERTICES;
         ++vertex) {
        CHECK(path.vertices[vertex] == vertex);
    }

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
        graph_bfs_matrix(
            &graph,
            0U,
            (size_t)GRAPH_MAX_VERTICES - 1U,
            &result
        ) == GRAPH_BFS_OK
    );
    CHECK(result.visit_count == (size_t)GRAPH_MAX_VERTICES);

    mark_result(&result);
    CHECK(
        graph_bfs_matrix(
            &graph,
            0U,
            (size_t)GRAPH_MAX_VERTICES - 2U,
            &result
        ) == GRAPH_BFS_LIMIT
    );
    CHECK(result_is_marked(&result));

    for (limit = 0U;
         limit <= (size_t)GRAPH_MAX_VERTICES;
         ++limit) {
        mark_result(&result);
        if (limit < (size_t)GRAPH_MAX_VERTICES - 1U) {
            CHECK(
                graph_bfs_matrix(
                    &graph,
                    0U,
                    limit,
                    &result
                ) == GRAPH_BFS_LIMIT
            );
            CHECK(result_is_marked(&result));
        } else {
            CHECK(
                graph_bfs_matrix(
                    &graph,
                    0U,
                    limit,
                    &result
                ) == GRAPH_BFS_OK
            );
            CHECK(
                result.visit_count ==
                (size_t)GRAPH_MAX_VERTICES
            );
        }
    }
    return true;
}

static bool test_second_allocation_failure_is_atomic(void)
{
    GraphAdjList graph = {0};
    ListSnapshot snapshot;
    size_t baseline = graph_adj_list_test_live_array_count();
    size_t live_before_failure;
    size_t vertex;
    bool has_edge = false;

    CHECK(
        graph_adj_list_init(&graph, 10U, GRAPH_UNDIRECTED) ==
        GRAPH_ADJ_LIST_OK
    );
    for (vertex = 2U; vertex <= 5U; ++vertex) {
        CHECK_LIST(
            graph_adj_list_add_edge(&graph, 0U, vertex) ==
            GRAPH_ADJ_LIST_OK,
            &graph
        );
    }
    for (vertex = 6U; vertex <= 9U; ++vertex) {
        CHECK_LIST(
            graph_adj_list_add_edge(&graph, 1U, vertex) ==
            GRAPH_ADJ_LIST_OK,
            &graph
        );
    }
    CHECK_LIST(graph.neighbors[0].size == 4U, &graph);
    CHECK_LIST(graph.neighbors[0].capacity == 4U, &graph);
    CHECK_LIST(graph.neighbors[1].size == 4U, &graph);
    CHECK_LIST(graph.neighbors[1].capacity == 4U, &graph);

    snapshot_list(&graph, &snapshot);
    live_before_failure = graph_adj_list_test_live_array_count();
    graph_adj_list_test_fail_allocation_after(1U);
    CHECK_LIST(
        graph_adj_list_add_edge(&graph, 0U, 1U) ==
        GRAPH_ADJ_LIST_ALLOCATION,
        &graph
    );
    CHECK_LIST(list_matches_snapshot(&graph, &snapshot), &graph);
    CHECK_LIST(
        graph_adj_list_test_live_array_count() ==
        live_before_failure,
        &graph
    );

    CHECK_LIST(
        graph_adj_list_add_edge(&graph, 0U, 1U) ==
        GRAPH_ADJ_LIST_OK,
        &graph
    );
    CHECK_LIST(graph.neighbors[0].size == 5U, &graph);
    CHECK_LIST(graph.neighbors[0].capacity == 8U, &graph);
    CHECK_LIST(graph.neighbors[1].size == 5U, &graph);
    CHECK_LIST(graph.neighbors[1].capacity == 8U, &graph);
    CHECK_LIST(
        graph_adj_list_has_edge(
            &graph,
            1U,
            0U,
            &has_edge
        ) == GRAPH_ADJ_LIST_OK,
        &graph
    );
    CHECK_LIST(has_edge, &graph);
    CHECK_LIST(
        graph_adj_list_validate(&graph) == GRAPH_ADJ_LIST_OK,
        &graph
    );

    graph_adj_list_destroy(&graph);
    CHECK(graph_adj_list_test_live_array_count() == baseline);
    return true;
}

static bool test_adjacency_list_growth_to_sixteen(void)
{
    GraphAdjList graph = {0};
    GraphBfsResult result;
    size_t baseline = graph_adj_list_test_live_array_count();
    size_t destination;

    CHECK(
        graph_adj_list_init(
            &graph,
            (size_t)GRAPH_MAX_VERTICES,
            GRAPH_DIRECTED
        ) == GRAPH_ADJ_LIST_OK
    );

    for (destination = 9U; destination > 0U; --destination) {
        CHECK_LIST(
            graph_adj_list_add_edge(
                &graph,
                0U,
                destination
            ) == GRAPH_ADJ_LIST_OK,
            &graph
        );
    }

    CHECK_LIST(graph.neighbors[0].size == 9U, &graph);
    CHECK_LIST(
        graph.neighbors[0].capacity ==
        (size_t)GRAPH_MAX_VERTICES,
        &graph
    );
    for (destination = 1U; destination <= 9U; ++destination) {
        CHECK_LIST(
            graph.neighbors[0].data[destination - 1U] ==
            destination,
            &graph
        );
    }
    CHECK_LIST(
        graph_adj_list_validate(&graph) == GRAPH_ADJ_LIST_OK,
        &graph
    );

    CHECK_LIST(
        graph_bfs_list(&graph, 0U, 9U, &result) ==
        GRAPH_BFS_OK,
        &graph
    );
    CHECK_LIST(result.visit_count == 10U, &graph);
    for (destination = 0U; destination <= 9U; ++destination) {
        CHECK_LIST(
            result.visit_order[destination] == destination,
            &graph
        );
        CHECK_LIST(
            result.distance[destination] ==
            (destination == 0U ? 0U : 1U),
            &graph
        );
    }

    graph_adj_list_destroy(&graph);
    CHECK(graph_adj_list_test_live_array_count() == baseline);
    return true;
}

static bool test_adjacency_list_malformed_states(void)
{
    GraphAdjList graph = {0};
    size_t saved_size;
    size_t saved_value;
    GraphKind saved_kind;

    CHECK(make_canonical_list(&graph));

    saved_size = graph.neighbors[0].size;
    graph.neighbors[0].size = graph.neighbors[0].capacity + 1U;
    CHECK_LIST(
        graph_adj_list_validate(&graph) ==
        GRAPH_ADJ_LIST_INVALID_GRAPH,
        &graph
    );
    graph.neighbors[0].size = saved_size;

    saved_value = graph.neighbors[0].data[1];
    graph.neighbors[0].data[1] = graph.neighbors[0].data[0];
    CHECK_LIST(
        graph_adj_list_validate(&graph) ==
        GRAPH_ADJ_LIST_INVALID_GRAPH,
        &graph
    );
    graph.neighbors[0].data[1] = saved_value;

    saved_value = graph.neighbors[0].data[0];
    graph.neighbors[0].data[0] = graph.vertex_count;
    CHECK_LIST(
        graph_adj_list_validate(&graph) ==
        GRAPH_ADJ_LIST_INVALID_GRAPH,
        &graph
    );
    graph.neighbors[0].data[0] = saved_value;

    graph.neighbors[15].size = 1U;
    CHECK_LIST(
        graph_adj_list_validate(&graph) ==
        GRAPH_ADJ_LIST_INVALID_GRAPH,
        &graph
    );
    graph.neighbors[15].size = 0U;

    saved_kind = graph.kind;
    graph.kind = (GraphKind)88;
    CHECK_LIST(
        graph_adj_list_validate(&graph) ==
        GRAPH_ADJ_LIST_INVALID_GRAPH,
        &graph
    );
    graph.kind = saved_kind;
    CHECK_LIST(
        graph_adj_list_validate(&graph) == GRAPH_ADJ_LIST_OK,
        &graph
    );
    graph_adj_list_destroy(&graph);

    CHECK(
        graph_adj_list_init(&graph, 3U, GRAPH_UNDIRECTED) ==
        GRAPH_ADJ_LIST_OK
    );
    CHECK_LIST(
        graph_adj_list_add_edge(&graph, 0U, 1U) ==
        GRAPH_ADJ_LIST_OK,
        &graph
    );
    graph.neighbors[1].size = 0U;
    CHECK_LIST(
        graph_adj_list_validate(&graph) ==
        GRAPH_ADJ_LIST_INVALID_GRAPH,
        &graph
    );
    graph.neighbors[1].size = 1U;
    CHECK_LIST(
        graph_adj_list_validate(&graph) == GRAPH_ADJ_LIST_OK,
        &graph
    );
    graph_adj_list_destroy(&graph);
    CHECK(graph_adj_list_test_live_array_count() == 0U);
    return true;
}

static bool expect_invalid_result(const GraphBfsResult *result)
{
    return graph_bfs_result_validate(result) ==
        GRAPH_BFS_INVALID_RESULT;
}

static bool test_malformed_result_variants(void)
{
    Graph graph;
    GraphBfsResult valid;
    GraphBfsResult malformed;
    GraphBfsPath path;

    CHECK(make_canonical_matrix(&graph));
    CHECK(
        graph_bfs_matrix(&graph, 0U, 3U, &valid) ==
        GRAPH_BFS_OK
    );

    malformed = valid;
    malformed.visit_order[2] = malformed.visit_order[1];
    CHECK(expect_invalid_result(&malformed));

    malformed = valid;
    malformed.visit_order[7] = 0U;
    CHECK(expect_invalid_result(&malformed));

    malformed = valid;
    malformed.distance[0] = 1U;
    CHECK(expect_invalid_result(&malformed));

    malformed = valid;
    malformed.distance[7] = 0U;
    CHECK(expect_invalid_result(&malformed));

    malformed = valid;
    malformed.predecessor[6] = 15U;
    CHECK(expect_invalid_result(&malformed));

    malformed = valid;
    malformed.distance[6] = 2U;
    CHECK(expect_invalid_result(&malformed));

    malformed = valid;
    malformed.discovered[8] = true;
    CHECK(expect_invalid_result(&malformed));

    malformed = valid;
    malformed.visit_count = 0U;
    CHECK(expect_invalid_result(&malformed));

    CHECK(
        graph_bfs_result_validate(NULL) ==
        GRAPH_BFS_INVALID_ARGUMENT
    );

    malformed = valid;
    malformed.predecessor[6] = 15U;
    mark_path(&path);
    CHECK(
        graph_bfs_reconstruct_path(&malformed, 6U, &path) ==
        GRAPH_BFS_INVALID_RESULT
    );
    CHECK(path_is_marked(&path));
    return true;
}

static bool test_inputs_are_not_mutated(void)
{
    Graph matrix;
    Graph matrix_before;
    GraphAdjList list = {0};
    ListSnapshot list_before;
    GraphBfsResult matrix_result;
    GraphBfsResult list_result;
    GraphBfsResult result_before;
    GraphBfsPath path;

    CHECK(make_canonical_matrix(&matrix));
    matrix_before = matrix;
    CHECK(make_canonical_list(&list));
    snapshot_list(&list, &list_before);

    CHECK_LIST(
        graph_bfs_matrix(&matrix, 0U, 3U, &matrix_result) ==
        GRAPH_BFS_OK,
        &list
    );
    CHECK_LIST(matrices_equal(&matrix, &matrix_before), &list);
    CHECK_LIST(
        graph_bfs_list(&list, 0U, 3U, &list_result) ==
        GRAPH_BFS_OK,
        &list
    );
    CHECK_LIST(list_matches_snapshot(&list, &list_before), &list);
    CHECK_LIST(results_equal(&matrix_result, &list_result), &list);

    mark_result(&matrix_result);
    CHECK_LIST(
        graph_bfs_matrix(&matrix, 0U, 2U, &matrix_result) ==
        GRAPH_BFS_LIMIT,
        &list
    );
    CHECK_LIST(result_is_marked(&matrix_result), &list);
    CHECK_LIST(matrices_equal(&matrix, &matrix_before), &list);

    mark_result(&list_result);
    CHECK_LIST(
        graph_bfs_list(&list, 0U, 2U, &list_result) ==
        GRAPH_BFS_LIMIT,
        &list
    );
    CHECK_LIST(result_is_marked(&list_result), &list);
    CHECK_LIST(list_matches_snapshot(&list, &list_before), &list);

    CHECK_LIST(
        graph_bfs_matrix(&matrix, 0U, 3U, &matrix_result) ==
        GRAPH_BFS_OK,
        &list
    );
    result_before = matrix_result;
    CHECK_LIST(
        graph_bfs_reconstruct_path(
            &matrix_result,
            6U,
            &path
        ) == GRAPH_BFS_OK,
        &list
    );
    CHECK_LIST(results_equal(&matrix_result, &result_before), &list);

    graph_adj_list_destroy(&list);
    CHECK(graph_adj_list_test_live_array_count() == 0U);
    return true;
}

static bool test_queue_invalid_states_and_status_names(void)
{
    VertexQueue excessive = {{0U}, 17U, 0U, 0U};
    VertexQueue empty_head = {{0U}, 3U, 1U, 0U};
    VertexQueue excessive_size = {{0U}, 2U, 0U, 3U};
    VertexQueue wrapped = {{0U}, 4U, 3U, 2U};
    VertexQueue queue = {{0U}, 7U, 6U, 5U};
    size_t output = 71U;

    CHECK(
        vertex_queue_init(&queue, 17U) ==
        VERTEX_QUEUE_LIMIT
    );
    CHECK(queue.limit == 7U && queue.head == 6U && queue.size == 5U);
    CHECK(
        vertex_queue_validate(&excessive) ==
        VERTEX_QUEUE_INVALID_STATE
    );
    CHECK(
        vertex_queue_validate(&empty_head) ==
        VERTEX_QUEUE_INVALID_STATE
    );
    CHECK(
        vertex_queue_validate(&excessive_size) ==
        VERTEX_QUEUE_INVALID_STATE
    );

    wrapped.data[3] = 2U;
    wrapped.data[0] = (size_t)GRAPH_MAX_VERTICES;
    CHECK(
        vertex_queue_validate(&wrapped) ==
        VERTEX_QUEUE_INVALID_STATE
    );
    CHECK(vertex_queue_dequeue(&wrapped, &output) == VERTEX_QUEUE_OK);
    CHECK(output == 2U);
    output = 71U;
    CHECK(
        vertex_queue_dequeue(&wrapped, &output) ==
        VERTEX_QUEUE_INVALID_STATE
    );
    CHECK(output == 71U);

    CHECK(strcmp(
        graph_adj_list_status_name(GRAPH_ADJ_LIST_OK),
        "ok"
    ) == 0);
    CHECK(strcmp(
        graph_adj_list_status_name(GRAPH_ADJ_LIST_INVALID_ARGUMENT),
        "invalid argument"
    ) == 0);
    CHECK(strcmp(
        graph_adj_list_status_name(GRAPH_ADJ_LIST_OUT_OF_RANGE),
        "vertex count or index out of range"
    ) == 0);
    CHECK(strcmp(
        graph_adj_list_status_name(GRAPH_ADJ_LIST_SELF_LOOP),
        "self-loops are not allowed"
    ) == 0);
    CHECK(strcmp(
        graph_adj_list_status_name(GRAPH_ADJ_LIST_EDGE_EXISTS),
        "edge already exists"
    ) == 0);
    CHECK(strcmp(
        graph_adj_list_status_name(GRAPH_ADJ_LIST_EDGE_ABSENT),
        "edge does not exist"
    ) == 0);
    CHECK(strcmp(
        graph_adj_list_status_name(GRAPH_ADJ_LIST_INVALID_GRAPH),
        "graph does not satisfy adjacency-list representation rules"
    ) == 0);
    CHECK(strcmp(
        graph_adj_list_status_name(GRAPH_ADJ_LIST_ALLOCATION),
        "allocation failed"
    ) == 0);
    CHECK(strcmp(
        graph_adj_list_status_name((GraphAdjListStatus)99),
        "unknown GraphAdjListStatus"
    ) == 0);

    CHECK(strcmp(
        vertex_queue_status_name(VERTEX_QUEUE_OK),
        "ok"
    ) == 0);
    CHECK(strcmp(
        vertex_queue_status_name(VERTEX_QUEUE_INVALID_ARGUMENT),
        "invalid argument"
    ) == 0);
    CHECK(strcmp(
        vertex_queue_status_name(VERTEX_QUEUE_LIMIT),
        "vertex Queue limit reached"
    ) == 0);
    CHECK(strcmp(
        vertex_queue_status_name(VERTEX_QUEUE_UNDERFLOW),
        "vertex Queue is empty"
    ) == 0);
    CHECK(strcmp(
        vertex_queue_status_name(VERTEX_QUEUE_INVALID_STATE),
        "vertex Queue representation is invalid"
    ) == 0);
    CHECK(strcmp(
        vertex_queue_status_name((VertexQueueStatus)99),
        "unknown VertexQueueStatus"
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
        test_exact_maximum_chain_and_star,
        "exact 16-vertex chain and star"
    );
    failures += run_test(
        test_second_allocation_failure_is_atomic,
        "second staged allocation failure"
    );
    failures += run_test(
        test_adjacency_list_growth_to_sixteen,
        "adjacency-list growth from capacity 8 to 16"
    );
    failures += run_test(
        test_adjacency_list_malformed_states,
        "adjacency-list malformed states"
    );
    failures += run_test(
        test_malformed_result_variants,
        "malformed BFS result variants"
    );
    failures += run_test(
        test_inputs_are_not_mutated,
        "matrix, list, and result nonmutation"
    );
    failures += run_test(
        test_queue_invalid_states_and_status_names,
        "Queue invalid states and support status names"
    );

    if (failures != 0) {
        printf("%d extension test group(s) failed.\n", failures);
        return 1;
    }

    puts("All extension test groups passed.");
    return 0;
}
