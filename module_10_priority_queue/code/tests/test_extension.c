#include "dijkstra.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifndef DIJKSTRA_TESTING
#error "Extension tests require -DDIJKSTRA_TESTING."
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

static bool test_frontier_beyond_sixty_four(void)
{
    DijkstraFrontier frontier = {0};
    DijkstraFrontierEntry previous = {
        0U,
        0U,
        0U
    };
    size_t index;
    bool is_heap = false;

    REQUIRE(
        dijkstra_frontier_init(
            &frontier,
            DIJKSTRA_FRONTIER_MAX_ENTRIES
        ) == DIJKSTRA_FRONTIER_OK
    );
    track_frontier(&frontier);

    for (index = 0U;
         index <
             (size_t)DIJKSTRA_FRONTIER_MAX_ENTRIES;
         ++index) {
        REQUIRE(
            dijkstra_frontier_push(
                &frontier,
                index %
                    (size_t)WEIGHTED_GRAPH_MAX_VERTICES,
                (index * 17U) % 31U
            ) == DIJKSTRA_FRONTIER_OK
        );

        if (index == 0U) {
            REQUIRE(frontier.capacity == 8U);
        } else if (index == 8U) {
            REQUIRE(frontier.capacity == 16U);
        } else if (index == 16U) {
            REQUIRE(frontier.capacity == 32U);
        } else if (index == 32U) {
            REQUIRE(frontier.capacity == 64U);
        } else if (index == 64U) {
            REQUIRE(frontier.capacity == 128U);
        } else if (index == 128U) {
            REQUIRE(
                frontier.capacity ==
                (size_t)DIJKSTRA_FRONTIER_MAX_ENTRIES
            );
        }
    }

    REQUIRE(
        dijkstra_frontier_is_min_heap(
            &frontier,
            &is_heap
        ) == DIJKSTRA_FRONTIER_OK
    );
    REQUIRE(is_heap);
    REQUIRE(
        dijkstra_frontier_push(&frontier, 0U, 0U) ==
        DIJKSTRA_FRONTIER_FULL
    );

    for (index = 0U;
         index <
             (size_t)DIJKSTRA_FRONTIER_MAX_ENTRIES;
         ++index) {
        DijkstraFrontierEntry current;

        REQUIRE(
            dijkstra_frontier_pop(
                &frontier,
                &current
            ) == DIJKSTRA_FRONTIER_OK
        );
        if (index > 0U) {
            REQUIRE(
                previous.distance < current.distance ||
                (previous.distance == current.distance &&
                 previous.insertion_sequence <
                    current.insertion_sequence)
            );
        }
        previous = current;
    }
    REQUIRE(frontier.size == 0U);
    REQUIRE(
        frontier.next_sequence ==
        (size_t)DIJKSTRA_FRONTIER_MAX_ENTRIES
    );
    REQUIRE(
        frontier.capacity ==
        (size_t)DIJKSTRA_FRONTIER_MAX_ENTRIES
    );

    release_active();
    REQUIRE(
        dijkstra_frontier_test_live_allocation_count() ==
        0U
    );
    return true;
}

static bool test_dense_graph_all_stored_arcs(void)
{
    WeightedGraph graph = {0};
    DijkstraResult result;
    size_t from_vertex;

    REQUIRE(
        weighted_graph_init(
            &graph,
            WEIGHTED_GRAPH_MAX_VERTICES,
            WEIGHTED_GRAPH_DIRECTED
        ) == WEIGHTED_GRAPH_OK
    );
    track_graph(&graph);

    for (from_vertex = 0U;
         from_vertex <
             (size_t)WEIGHTED_GRAPH_MAX_VERTICES;
         ++from_vertex) {
        size_t to_vertex;

        for (to_vertex = 0U;
             to_vertex <
                 (size_t)WEIGHTED_GRAPH_MAX_VERTICES;
             ++to_vertex) {
            if (from_vertex != to_vertex) {
                REQUIRE(
                    weighted_graph_add_edge(
                        &graph,
                        from_vertex,
                        to_vertex,
                        (from_vertex + to_vertex) % 7U
                    ) == WEIGHTED_GRAPH_OK
                );
            }
        }
        REQUIRE(
            graph.outgoing[from_vertex].size == 15U
        );
        REQUIRE(
            graph.outgoing[from_vertex].capacity == 16U
        );
    }

    REQUIRE(
        graph.arc_count ==
        (size_t)WEIGHTED_GRAPH_MAX_ARCS
    );
    REQUIRE(
        weighted_graph_validate(&graph) ==
        WEIGHTED_GRAPH_OK
    );
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
    REQUIRE(
        result.arc_count ==
        (size_t)WEIGHTED_GRAPH_MAX_ARCS
    );
    REQUIRE(
        result.relaxation_attempt_count ==
        (size_t)WEIGHTED_GRAPH_MAX_ARCS
    );
    REQUIRE(
        result.push_count <=
        (size_t)DIJKSTRA_FRONTIER_MAX_ENTRIES
    );
    REQUIRE(result.finalized_count == 16U);

    release_active();
    REQUIRE(weighted_graph_test_live_row_count() == 0U);
    REQUIRE(
        dijkstra_frontier_test_live_allocation_count() ==
        0U
    );
    return true;
}

static uint32_t next_random(uint32_t *state)
{
    *state =
        *state * UINT32_C(1664525) +
        UINT32_C(1013904223);
    return *state;
}

static void reference_shortest_paths(
    const WeightedGraph *graph,
    size_t source,
    size_t *out_distance
)
{
    bool selected[WEIGHTED_GRAPH_MAX_VERTICES] =
        {false};
    size_t vertex;

    for (vertex = 0U;
         vertex <
             (size_t)WEIGHTED_GRAPH_MAX_VERTICES;
         ++vertex) {
        out_distance[vertex] = DIJKSTRA_INF;
    }
    out_distance[source] = 0U;

    for (;;) {
        size_t current = DIJKSTRA_NO_VERTEX;
        size_t best = DIJKSTRA_INF;
        const WeightedEdgeArray *row;
        size_t edge_index;

        for (vertex = 0U;
             vertex < graph->vertex_count;
             ++vertex) {
            if (!selected[vertex] &&
                out_distance[vertex] < best) {
                current = vertex;
                best = out_distance[vertex];
            }
        }
        if (current == DIJKSTRA_NO_VERTEX) {
            break;
        }

        selected[current] = true;
        row = &graph->outgoing[current];
        for (edge_index = 0U;
             edge_index < row->size;
             ++edge_index) {
            const WeightedEdge *edge =
                &row->data[edge_index];
            size_t candidate =
                out_distance[current] + edge->weight;

            if (candidate < out_distance[edge->to]) {
                out_distance[edge->to] = candidate;
            }
        }
    }
}

static bool test_random_o_v_squared_differential(void)
{
    enum {
        RANDOM_ROUNDS = 60
    };

    WeightedGraph graph = {0};
    uint32_t state = UINT32_C(0xD1122026);
    int round;

    for (round = 0; round < RANDOM_ROUNDS; ++round) {
        DijkstraResult result;
        size_t reference[
            WEIGHTED_GRAPH_MAX_VERTICES];
        size_t vertex_count =
            2U + (size_t)(
                next_random(&state) % UINT32_C(9)
            );
        size_t source =
            (size_t)(next_random(&state) %
                (uint32_t)vertex_count);
        size_t from_vertex;

        REQUIRE(
            weighted_graph_init(
                &graph,
                vertex_count,
                WEIGHTED_GRAPH_DIRECTED
            ) == WEIGHTED_GRAPH_OK
        );
        track_graph(&graph);

        for (from_vertex = 0U;
             from_vertex < vertex_count;
             ++from_vertex) {
            size_t to_vertex;

            for (to_vertex = 0U;
                 to_vertex < vertex_count;
                 ++to_vertex) {
                uint32_t random_value;

                if (from_vertex == to_vertex) {
                    continue;
                }
                random_value = next_random(&state);
                if (random_value % UINT32_C(100) < 38U) {
                    REQUIRE(
                        weighted_graph_add_edge(
                            &graph,
                            from_vertex,
                            to_vertex,
                            (size_t)(
                                next_random(&state) %
                                UINT32_C(21)
                            )
                        ) == WEIGHTED_GRAPH_OK
                    );
                }
            }
        }

        reference_shortest_paths(
            &graph,
            source,
            reference
        );
        REQUIRE(
            dijkstra_shortest_paths(
                &graph,
                source,
                &result
            ) == DIJKSTRA_OK
        );
        REQUIRE(
            dijkstra_result_validate(&result) ==
            DIJKSTRA_OK
        );

        for (from_vertex = 0U;
             from_vertex < vertex_count;
             ++from_vertex) {
            REQUIRE(
                result.distance[from_vertex] ==
                reference[from_vertex]
            );
        }

        release_active();
        REQUIRE(
            weighted_graph_test_live_row_count() == 0U
        );
        REQUIRE(
            dijkstra_frontier_test_live_allocation_count()
            == 0U
        );
    }
    return true;
}

static bool test_graph_and_frontier_allocation_failures(void)
{
    WeightedGraph graph = {0};
    DijkstraResult output;
    DijkstraResult before;
    WeightedEdge saved_edges[4];
    WeightedEdge *row_identity;
    size_t index;

    REQUIRE(
        weighted_graph_init(
            &graph,
            16U,
            WEIGHTED_GRAPH_DIRECTED
        ) == WEIGHTED_GRAPH_OK
    );
    track_graph(&graph);
    for (index = 1U; index <= 4U; ++index) {
        REQUIRE(
            weighted_graph_add_edge(
                &graph,
                0U,
                index,
                index
            ) == WEIGHTED_GRAPH_OK
        );
    }
    row_identity = graph.outgoing[0].data;
    for (index = 0U; index < 4U; ++index) {
        saved_edges[index] = graph.outgoing[0].data[index];
    }

    weighted_graph_test_fail_allocation_after(0U);
    REQUIRE(
        weighted_graph_add_edge(
            &graph,
            0U,
            5U,
            5U
        ) == WEIGHTED_GRAPH_ALLOCATION
    );
    REQUIRE(graph.outgoing[0].data == row_identity);
    REQUIRE(graph.outgoing[0].size == 4U);
    REQUIRE(graph.outgoing[0].capacity == 4U);
    REQUIRE(graph.arc_count == 4U);
    for (index = 0U; index < 4U; ++index) {
        REQUIRE(
            memcmp(
                &graph.outgoing[0].data[index],
                &saved_edges[index],
                sizeof saved_edges[index]
            ) == 0
        );
    }

    for (index = 5U; index < 16U; ++index) {
        REQUIRE(
            weighted_graph_add_edge(
                &graph,
                0U,
                index,
                1U
            ) == WEIGHTED_GRAPH_OK
        );
    }
    REQUIRE(graph.arc_count == 15U);

    (void)memset(&output, 0xA6, sizeof output);
    before = output;
    dijkstra_frontier_test_fail_allocation_after(0U);
    REQUIRE(
        dijkstra_shortest_paths(
            &graph,
            0U,
            &output
        ) == DIJKSTRA_ALLOCATION
    );
    REQUIRE(
        memcmp(&output, &before, sizeof output) == 0
    );
    REQUIRE(
        dijkstra_frontier_test_live_allocation_count() ==
        0U
    );

    dijkstra_frontier_test_fail_allocation_after(1U);
    REQUIRE(
        dijkstra_shortest_paths(
            &graph,
            0U,
            &output
        ) == DIJKSTRA_ALLOCATION
    );
    REQUIRE(
        memcmp(&output, &before, sizeof output) == 0
    );
    REQUIRE(
        dijkstra_frontier_test_live_allocation_count() ==
        0U
    );

    REQUIRE(
        dijkstra_shortest_paths(
            &graph,
            0U,
            &output
        ) == DIJKSTRA_OK
    );
    REQUIRE(output.frontier_peak == 15U);

    release_active();
    REQUIRE(weighted_graph_test_live_row_count() == 0U);
    return true;
}

static bool test_invalid_state_checkers_and_statuses(void)
{
    DijkstraFrontier frontier = {0};
    bool is_heap = true;

    REQUIRE(
        dijkstra_frontier_init(
            &frontier,
            (size_t)DIJKSTRA_FRONTIER_MAX_ENTRIES + 1U
        ) == DIJKSTRA_FRONTIER_OUT_OF_RANGE
    );
    REQUIRE(
        dijkstra_frontier_init(&frontier, 8U) ==
        DIJKSTRA_FRONTIER_OK
    );
    track_frontier(&frontier);
    REQUIRE(
        dijkstra_frontier_push(&frontier, 0U, 10U) ==
        DIJKSTRA_FRONTIER_OK
    );
    REQUIRE(
        dijkstra_frontier_push(&frontier, 1U, 20U) ==
        DIJKSTRA_FRONTIER_OK
    );
    frontier.data[1].distance = 1U;
    REQUIRE(
        dijkstra_frontier_is_min_heap(
            &frontier,
            &is_heap
        ) == DIJKSTRA_FRONTIER_OK
    );
    REQUIRE(!is_heap);
    frontier.data[1].distance = 20U;

    frontier.size = frontier.capacity + 1U;
    REQUIRE(
        dijkstra_frontier_validate(&frontier) ==
        DIJKSTRA_FRONTIER_INVALID_STATE
    );
    frontier.size = 2U;
    REQUIRE(
        strcmp(
            dijkstra_frontier_status_name(
                DIJKSTRA_FRONTIER_ALLOCATION
            ),
            "unknown DijkstraFrontierStatus"
        ) != 0
    );
    REQUIRE(
        strcmp(
            weighted_graph_status_name(
                WEIGHTED_GRAPH_NEGATIVE_WEIGHT
            ),
            "unknown WeightedGraphStatus"
        ) != 0
    );
    REQUIRE(
        strcmp(
            dijkstra_status_name(DIJKSTRA_COST_RANGE),
            "unknown DijkstraStatus"
        ) != 0
    );

    release_active();
    return true;
}

int main(void)
{
    run_test(
        "Frontier grows beyond sixty-four",
        test_frontier_beyond_sixty_four
    );
    run_test(
        "dense graph stores all 240 arcs",
        test_dense_graph_all_stored_arcs
    );
    run_test(
        "random independent O(V^2) differential",
        test_random_o_v_squared_differential
    );
    run_test(
        "graph and mid-run Frontier allocation failures",
        test_graph_and_frontier_allocation_failures
    );
    run_test(
        "invalid state checkers and status helpers",
        test_invalid_state_checkers_and_statuses
    );

    (void)printf(
        "\n%u extension test(s), %u failure(s)\n",
        tests_run,
        tests_failed
    );
    return tests_failed == 0U ? 0 : 1;
}
