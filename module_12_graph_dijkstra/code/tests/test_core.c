#include "dijkstra.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifndef DIJKSTRA_TESTING
#error "Core tests require -DDIJKSTRA_TESTING."
#endif

typedef bool (*TestFunction)(void);

static WeightedGraph *active_graph = NULL;
static DijkstraFrontier *active_frontier = NULL;
static unsigned int tests_run = 0U;
static unsigned int tests_failed = 0U;

static void track_graph(WeightedGraph *graph)
{
    active_graph = graph;
}

static void track_frontier(DijkstraFrontier *frontier)
{
    active_frontier = frontier;
}

static void release_active(void)
{
    if (active_frontier != NULL) {
        dijkstra_frontier_destroy(active_frontier);
        active_frontier = NULL;
    }
    if (active_graph != NULL) {
        weighted_graph_destroy(active_graph);
        active_graph = NULL;
    }
}

#define REQUIRE(condition)                                                   \
    do {                                                                     \
        if (!(condition)) {                                                  \
            (void)fprintf(                                                   \
                stderr,                                                      \
                "  requirement failed at %s:%d: %s\n",                     \
                __FILE__,                                                    \
                __LINE__,                                                    \
                #condition                                                   \
            );                                                               \
            release_active();                                                \
            return false;                                                    \
        }                                                                    \
    } while (false)

static void run_test(const char *name, TestFunction test)
{
    bool passed;

    tests_run += 1U;
    passed = test();
    if (passed) {
        (void)printf("PASS %s\n", name);
    } else {
        tests_failed += 1U;
        (void)printf("FAIL %s\n", name);
    }
}

static bool add_edge(
    WeightedGraph *graph,
    size_t from,
    size_t to,
    size_t weight
)
{
    return weighted_graph_add_edge(
        graph,
        from,
        to,
        weight
    ) == WEIGHTED_GRAPH_OK;
}

static bool build_canonical_graph(WeightedGraph *graph)
{
    return add_edge(graph, 0U, 1U, 9U) &&
        add_edge(graph, 0U, 2U, 2U) &&
        add_edge(graph, 0U, 4U, 14U) &&
        add_edge(graph, 1U, 3U, 0U) &&
        add_edge(graph, 1U, 4U, 8U) &&
        add_edge(graph, 2U, 1U, 2U) &&
        add_edge(graph, 2U, 3U, 2U) &&
        add_edge(graph, 3U, 4U, 2U);
}

static bool result_bytes_equal(
    const DijkstraResult *left,
    const DijkstraResult *right
)
{
    return memcmp(left, right, sizeof *left) == 0;
}

static bool path_bytes_equal(
    const DijkstraPath *left,
    const DijkstraPath *right
)
{
    return memcmp(left, right, sizeof *left) == 0;
}

static bool test_weight_parser_and_sorted_graph(void)
{
    WeightedGraph graph = {0};
    size_t output = 700U;
    char maximum_text[64];
    char overflow_text[80];

    REQUIRE(
        weighted_graph_parse_weight("  +42\t", &output) ==
        WEIGHTED_GRAPH_OK
    );
    REQUIRE(output == 42U);
    REQUIRE(
        weighted_graph_parse_weight("0", &output) ==
        WEIGHTED_GRAPH_OK
    );
    REQUIRE(output == 0U);

    output = 700U;
    REQUIRE(
        weighted_graph_parse_weight("-1", &output) ==
        WEIGHTED_GRAPH_NEGATIVE_WEIGHT
    );
    REQUIRE(output == 700U);
    REQUIRE(
        weighted_graph_parse_weight(
            " -999999999999999999999999",
            &output
        ) == WEIGHTED_GRAPH_NEGATIVE_WEIGHT
    );
    REQUIRE(output == 700U);
    REQUIRE(
        weighted_graph_parse_weight("", &output) ==
        WEIGHTED_GRAPH_INVALID_WEIGHT_TEXT
    );
    REQUIRE(
        weighted_graph_parse_weight("+", &output) ==
        WEIGHTED_GRAPH_INVALID_WEIGHT_TEXT
    );
    REQUIRE(
        weighted_graph_parse_weight("12x", &output) ==
        WEIGHTED_GRAPH_INVALID_WEIGHT_TEXT
    );
    REQUIRE(
        weighted_graph_parse_weight("1 2", &output) ==
        WEIGHTED_GRAPH_INVALID_WEIGHT_TEXT
    );
    REQUIRE(output == 700U);
    REQUIRE(
        weighted_graph_parse_weight(NULL, &output) ==
        WEIGHTED_GRAPH_INVALID_ARGUMENT
    );
    REQUIRE(
        weighted_graph_parse_weight("1", NULL) ==
        WEIGHTED_GRAPH_INVALID_ARGUMENT
    );

    (void)snprintf(
        maximum_text,
        sizeof maximum_text,
        "%zu",
        SIZE_MAX
    );
    (void)snprintf(
        overflow_text,
        sizeof overflow_text,
        "%zu0",
        SIZE_MAX
    );
    REQUIRE(
        weighted_graph_parse_weight(
            maximum_text,
            &output
        ) == WEIGHTED_GRAPH_WEIGHT_OUT_OF_RANGE
    );
    REQUIRE(
        weighted_graph_parse_weight(
            overflow_text,
            &output
        ) == WEIGHTED_GRAPH_WEIGHT_OUT_OF_RANGE
    );
    REQUIRE(output == 700U);

    REQUIRE(
        weighted_graph_init(
            &graph,
            4U,
            WEIGHTED_GRAPH_DIRECTED
        ) == WEIGHTED_GRAPH_OK
    );
    track_graph(&graph);
    REQUIRE(
        weighted_graph_add_edge_text(
            &graph,
            0U,
            3U,
            "7"
        ) == WEIGHTED_GRAPH_OK
    );
    REQUIRE(add_edge(&graph, 0U, 1U, 0U));
    REQUIRE(add_edge(&graph, 0U, 2U, 5U));
    REQUIRE(graph.arc_count == 3U);
    REQUIRE(graph.outgoing[0].size == 3U);
    REQUIRE(graph.outgoing[0].data[0].to == 1U);
    REQUIRE(graph.outgoing[0].data[1].to == 2U);
    REQUIRE(graph.outgoing[0].data[2].to == 3U);
    REQUIRE(
        weighted_graph_validate(&graph) ==
        WEIGHTED_GRAPH_OK
    );

    output = 800U;
    REQUIRE(
        weighted_graph_get_weight(
            &graph,
            0U,
            1U,
            &output
        ) == WEIGHTED_GRAPH_OK
    );
    REQUIRE(output == 0U);
    output = 800U;
    REQUIRE(
        weighted_graph_get_weight(
            &graph,
            3U,
            0U,
            &output
        ) == WEIGHTED_GRAPH_EDGE_ABSENT
    );
    REQUIRE(output == 800U);
    REQUIRE(
        weighted_graph_add_edge(
            &graph,
            0U,
            1U,
            99U
        ) == WEIGHTED_GRAPH_EDGE_EXISTS
    );
    REQUIRE(
        weighted_graph_add_edge(
            &graph,
            1U,
            1U,
            2U
        ) == WEIGHTED_GRAPH_SELF_LOOP
    );
    REQUIRE(
        weighted_graph_add_edge(
            &graph,
            1U,
            4U,
            2U
        ) == WEIGHTED_GRAPH_OUT_OF_RANGE
    );
    REQUIRE(
        weighted_graph_add_edge(
            &graph,
            1U,
            2U,
            SIZE_MAX
        ) == WEIGHTED_GRAPH_WEIGHT_OUT_OF_RANGE
    );

    release_active();
    REQUIRE(weighted_graph_test_live_row_count() == 0U);
    return true;
}

static bool test_undirected_atomic_allocation(void)
{
    WeightedGraph graph = {0};
    size_t weight = 900U;

    REQUIRE(
        weighted_graph_init(
            &graph,
            4U,
            WEIGHTED_GRAPH_UNDIRECTED
        ) == WEIGHTED_GRAPH_OK
    );
    track_graph(&graph);

    weighted_graph_test_fail_allocation_after(1U);
    REQUIRE(
        weighted_graph_add_edge(
            &graph,
            0U,
            3U,
            6U
        ) == WEIGHTED_GRAPH_ALLOCATION
    );
    REQUIRE(graph.arc_count == 0U);
    REQUIRE(graph.outgoing[0].size == 0U);
    REQUIRE(graph.outgoing[3].size == 0U);
    REQUIRE(
        weighted_graph_test_live_row_count() == 0U
    );
    REQUIRE(
        weighted_graph_validate(&graph) ==
        WEIGHTED_GRAPH_OK
    );

    REQUIRE(add_edge(&graph, 0U, 3U, 6U));
    REQUIRE(graph.arc_count == 2U);
    REQUIRE(
        weighted_graph_get_weight(
            &graph,
            0U,
            3U,
            &weight
        ) == WEIGHTED_GRAPH_OK
    );
    REQUIRE(weight == 6U);
    REQUIRE(
        weighted_graph_get_weight(
            &graph,
            3U,
            0U,
            &weight
        ) == WEIGHTED_GRAPH_OK
    );
    REQUIRE(weight == 6U);

    graph.outgoing[3].data[0].weight = 7U;
    REQUIRE(
        weighted_graph_validate(&graph) ==
        WEIGHTED_GRAPH_INVALID_GRAPH
    );
    graph.outgoing[3].data[0].weight = 6U;

    release_active();
    REQUIRE(weighted_graph_test_live_row_count() == 0U);
    return true;
}

static bool test_frontier_stability_growth_and_failures(void)
{
    DijkstraFrontier frontier = {0};
    DijkstraFrontierEntry output = {
        15U,
        700U,
        800U
    };
    DijkstraFrontierEntry preserved = output;
    DijkstraFrontierEntry snapshot[8];
    DijkstraFrontierEntry *data_identity;
    size_t index;
    size_t comparison_snapshot;
    bool is_heap = false;

    REQUIRE(
        dijkstra_frontier_init(&frontier, 10U) ==
        DIJKSTRA_FRONTIER_OK
    );
    track_frontier(&frontier);

    REQUIRE(
        dijkstra_frontier_push(&frontier, 3U, 7U) ==
        DIJKSTRA_FRONTIER_OK
    );
    REQUIRE(
        dijkstra_frontier_push(&frontier, 5U, 7U) ==
        DIJKSTRA_FRONTIER_OK
    );
    REQUIRE(
        dijkstra_frontier_push(&frontier, 1U, 2U) ==
        DIJKSTRA_FRONTIER_OK
    );
    REQUIRE(
        dijkstra_frontier_pop(&frontier, &output) ==
        DIJKSTRA_FRONTIER_OK
    );
    REQUIRE(output.vertex == 1U);
    REQUIRE(output.distance == 2U);
    REQUIRE(
        dijkstra_frontier_pop(&frontier, &output) ==
        DIJKSTRA_FRONTIER_OK
    );
    REQUIRE(output.vertex == 3U);
    REQUIRE(output.insertion_sequence == 0U);
    REQUIRE(
        dijkstra_frontier_pop(&frontier, &output) ==
        DIJKSTRA_FRONTIER_OK
    );
    REQUIRE(output.vertex == 5U);
    REQUIRE(output.insertion_sequence == 1U);
    REQUIRE(frontier.size == 0U);
    REQUIRE(frontier.next_sequence == 3U);
    REQUIRE(frontier.capacity == 8U);

    for (index = 0U; index < 8U; ++index) {
        REQUIRE(
            dijkstra_frontier_push(
                &frontier,
                index % 16U,
                100U - index
            ) == DIJKSTRA_FRONTIER_OK
        );
    }
    REQUIRE(frontier.capacity == 8U);
    REQUIRE(
        dijkstra_frontier_is_min_heap(
            &frontier,
            &is_heap
        ) == DIJKSTRA_FRONTIER_OK
    );
    REQUIRE(is_heap);

    for (index = 0U; index < 8U; ++index) {
        snapshot[index] = frontier.data[index];
    }
    data_identity = frontier.data;
    comparison_snapshot = frontier.comparison_count;
    dijkstra_frontier_test_fail_allocation_after(0U);
    REQUIRE(
        dijkstra_frontier_push(&frontier, 9U, 1U) ==
        DIJKSTRA_FRONTIER_ALLOCATION
    );
    REQUIRE(frontier.data == data_identity);
    REQUIRE(frontier.size == 8U);
    REQUIRE(frontier.capacity == 8U);
    REQUIRE(frontier.next_sequence == 11U);
    REQUIRE(
        frontier.comparison_count == comparison_snapshot
    );
    for (index = 0U; index < 8U; ++index) {
        REQUIRE(
            memcmp(
                &frontier.data[index],
                &snapshot[index],
                sizeof snapshot[index]
            ) == 0
        );
    }

    REQUIRE(
        dijkstra_frontier_push(&frontier, 9U, 1U) ==
        DIJKSTRA_FRONTIER_OK
    );
    REQUIRE(frontier.capacity == 10U);
    REQUIRE(
        dijkstra_frontier_push(&frontier, 10U, 0U) ==
        DIJKSTRA_FRONTIER_OK
    );
    REQUIRE(frontier.size == 10U);
    REQUIRE(
        dijkstra_frontier_push(&frontier, 11U, 0U) ==
        DIJKSTRA_FRONTIER_FULL
    );
    REQUIRE(
        dijkstra_frontier_is_min_heap(
            &frontier,
            &is_heap
        ) == DIJKSTRA_FRONTIER_OK
    );
    REQUIRE(is_heap);

    release_active();
    REQUIRE(
        dijkstra_frontier_test_live_allocation_count() ==
        0U
    );

    REQUIRE(
        dijkstra_frontier_init(&frontier, 0U) ==
        DIJKSTRA_FRONTIER_OK
    );
    track_frontier(&frontier);
    REQUIRE(
        dijkstra_frontier_push(&frontier, 0U, 0U) ==
        DIJKSTRA_FRONTIER_FULL
    );
    output = preserved;
    REQUIRE(
        dijkstra_frontier_pop(&frontier, &output) ==
        DIJKSTRA_FRONTIER_EMPTY
    );
    REQUIRE(
        memcmp(
            &output,
            &preserved,
            sizeof output
        ) == 0
    );
    release_active();
    return true;
}

static bool test_canonical_dijkstra_trace(void)
{
    static const size_t expected_distance[6] = {
        0U, 4U, 2U, 4U, 6U, DIJKSTRA_INF
    };
    static const size_t expected_predecessor[6] = {
        DIJKSTRA_NO_VERTEX,
        2U,
        0U,
        2U,
        3U,
        DIJKSTRA_NO_VERTEX
    };
    static const size_t expected_order[5] = {
        0U, 2U, 1U, 3U, 4U
    };
    static const size_t expected_pop_vertex[8] = {
        0U, 2U, 1U, 3U, 4U, 1U, 4U, 4U
    };
    static const size_t expected_pop_distance[8] = {
        0U, 2U, 4U, 4U, 6U, 9U, 12U, 14U
    };
    static const size_t expected_pop_sequence[8] = {
        0U, 2U, 4U, 5U, 7U, 1U, 6U, 3U
    };
    static const bool expected_stale[8] = {
        false, false, false, false,
        false, true, true, true
    };
    WeightedGraph graph = {0};
    DijkstraResult result;
    size_t index;

    REQUIRE(
        weighted_graph_init(
            &graph,
            6U,
            WEIGHTED_GRAPH_DIRECTED
        ) == WEIGHTED_GRAPH_OK
    );
    track_graph(&graph);
    REQUIRE(build_canonical_graph(&graph));
    REQUIRE(graph.arc_count == 8U);

    REQUIRE(
        dijkstra_shortest_paths(
            &graph,
            0U,
            &result
        ) == DIJKSTRA_OK
    );
    REQUIRE(
        dijkstra_result_validate(&result) == DIJKSTRA_OK
    );
    REQUIRE(result.vertex_count == 6U);
    REQUIRE(result.arc_count == 8U);
    REQUIRE(result.source == 0U);
    REQUIRE(result.finalized_count == 5U);
    REQUIRE(result.relaxation_attempt_count == 8U);
    REQUIRE(result.successful_relaxation_count == 7U);
    REQUIRE(result.push_count == 8U);
    REQUIRE(result.pop_count == 8U);
    REQUIRE(result.stale_pop_count == 3U);
    REQUIRE(result.frontier_peak == 4U);
    REQUIRE(result.heap_comparison_count == 17U);

    for (index = 0U; index < 6U; ++index) {
        REQUIRE(
            result.distance[index] ==
            expected_distance[index]
        );
        REQUIRE(
            result.predecessor[index] ==
            expected_predecessor[index]
        );
        REQUIRE(
            result.finalized[index] == (index < 5U)
        );
    }
    for (index = 0U; index < 5U; ++index) {
        REQUIRE(
            result.finalized_order[index] ==
            expected_order[index]
        );
    }
    for (index = 0U; index < 8U; ++index) {
        REQUIRE(
            result.pop_trace[index].vertex ==
            expected_pop_vertex[index]
        );
        REQUIRE(
            result.pop_trace[index].snapshot_distance ==
            expected_pop_distance[index]
        );
        REQUIRE(
            result.pop_trace[index].insertion_sequence ==
            expected_pop_sequence[index]
        );
        REQUIRE(
            result.pop_trace[index].stale ==
            expected_stale[index]
        );
    }

    release_active();
    REQUIRE(weighted_graph_test_live_row_count() == 0U);
    REQUIRE(
        dijkstra_frontier_test_live_allocation_count() ==
        0U
    );
    return true;
}

static bool test_paths_and_failure_preservation(void)
{
    WeightedGraph graph = {0};
    DijkstraResult result;
    DijkstraResult malformed;
    DijkstraResult output;
    DijkstraResult before_output;
    DijkstraPath path;
    DijkstraPath before_path;

    REQUIRE(
        weighted_graph_init(
            &graph,
            6U,
            WEIGHTED_GRAPH_DIRECTED
        ) == WEIGHTED_GRAPH_OK
    );
    track_graph(&graph);
    REQUIRE(build_canonical_graph(&graph));
    REQUIRE(
        dijkstra_shortest_paths(
            &graph,
            0U,
            &result
        ) == DIJKSTRA_OK
    );

    (void)memset(&path, 0xA5, sizeof path);
    REQUIRE(
        dijkstra_reconstruct_path(
            &result,
            4U,
            &path
        ) == DIJKSTRA_OK
    );
    REQUIRE(path.count == 4U);
    REQUIRE(path.vertices[0] == 0U);
    REQUIRE(path.vertices[1] == 2U);
    REQUIRE(path.vertices[2] == 3U);
    REQUIRE(path.vertices[3] == 4U);
    REQUIRE(path.total_cost == 6U);

    REQUIRE(
        dijkstra_reconstruct_path(
            &result,
            0U,
            &path
        ) == DIJKSTRA_OK
    );
    REQUIRE(path.count == 1U);
    REQUIRE(path.vertices[0] == 0U);
    REQUIRE(path.total_cost == 0U);

    (void)memset(&path, 0x3C, sizeof path);
    before_path = path;
    REQUIRE(
        dijkstra_reconstruct_path(
            &result,
            5U,
            &path
        ) == DIJKSTRA_UNREACHABLE
    );
    REQUIRE(path_bytes_equal(&path, &before_path));
    REQUIRE(
        dijkstra_reconstruct_path(
            &result,
            6U,
            &path
        ) == DIJKSTRA_OUT_OF_RANGE
    );
    REQUIRE(path_bytes_equal(&path, &before_path));
    REQUIRE(
        dijkstra_reconstruct_path(
            &result,
            0U,
            NULL
        ) == DIJKSTRA_INVALID_ARGUMENT
    );

    output = result;
    output.source = 3U;
    before_output = output;
    REQUIRE(
        dijkstra_shortest_paths(
            &graph,
            6U,
            &output
        ) == DIJKSTRA_OUT_OF_RANGE
    );
    REQUIRE(result_bytes_equal(
        &output,
        &before_output
    ));

    graph.arc_count += 1U;
    REQUIRE(
        dijkstra_shortest_paths(
            &graph,
            0U,
            &output
        ) == DIJKSTRA_INVALID_GRAPH
    );
    REQUIRE(result_bytes_equal(
        &output,
        &before_output
    ));
    graph.arc_count -= 1U;

    malformed = result;
    malformed.pop_trace[7].snapshot_distance = 11U;
    REQUIRE(
        dijkstra_result_validate(&malformed) ==
        DIJKSTRA_INVALID_RESULT
    );

    result.predecessor[3] = 3U;
    REQUIRE(
        dijkstra_result_validate(&result) ==
        DIJKSTRA_INVALID_RESULT
    );
    REQUIRE(
        dijkstra_reconstruct_path(
            &result,
            4U,
            &path
        ) == DIJKSTRA_INVALID_RESULT
    );
    REQUIRE(path_bytes_equal(&path, &before_path));

    release_active();
    return true;
}

static bool test_cost_range_is_explicit(void)
{
    WeightedGraph graph = {0};
    DijkstraResult output;
    DijkstraResult before;

    (void)memset(&output, 0x5A, sizeof output);
    before = output;

    REQUIRE(
        weighted_graph_init(
            &graph,
            3U,
            WEIGHTED_GRAPH_DIRECTED
        ) == WEIGHTED_GRAPH_OK
    );
    track_graph(&graph);
    REQUIRE(add_edge(&graph, 0U, 1U, SIZE_MAX - 3U));
    REQUIRE(add_edge(&graph, 1U, 2U, 5U));
    REQUIRE(
        dijkstra_shortest_paths(
            &graph,
            0U,
            &output
        ) == DIJKSTRA_COST_RANGE
    );
    REQUIRE(result_bytes_equal(&output, &before));
    release_active();

    REQUIRE(
        weighted_graph_init(
            &graph,
            3U,
            WEIGHTED_GRAPH_DIRECTED
        ) == WEIGHTED_GRAPH_OK
    );
    track_graph(&graph);
    REQUIRE(add_edge(&graph, 0U, 1U, SIZE_MAX - 3U));
    REQUIRE(add_edge(&graph, 1U, 2U, 3U));
    REQUIRE(
        dijkstra_shortest_paths(
            &graph,
            0U,
            &output
        ) == DIJKSTRA_COST_RANGE
    );
    REQUIRE(result_bytes_equal(&output, &before));

    release_active();
    REQUIRE(
        dijkstra_frontier_test_live_allocation_count() ==
        0U
    );
    return true;
}

int main(void)
{
    run_test(
        "weight parser and sorted weighted graph",
        test_weight_parser_and_sorted_graph
    );
    run_test(
        "undirected atomic allocation",
        test_undirected_atomic_allocation
    );
    run_test(
        "stable growing Frontier and failures",
        test_frontier_stability_growth_and_failures
    );
    run_test(
        "canonical Dijkstra trace and counters",
        test_canonical_dijkstra_trace
    );
    run_test(
        "path reconstruction and preservation",
        test_paths_and_failure_preservation
    );
    run_test(
        "explicit overflow and reserved-INF range",
        test_cost_range_is_explicit
    );

    (void)printf(
        "\n%u core test(s), %u failure(s)\n",
        tests_run,
        tests_failed
    );
    return tests_failed == 0U ? 0 : 1;
}
