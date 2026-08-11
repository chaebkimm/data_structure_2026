#include "minimum_spanning_forest.h"

#include "dsu.h"
#include "prim_frontier.h"
#include "undirected_edge_list.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef bool (*TestFunction)(void);

#define REQUIRE(condition)                                                   \
    do {                                                                     \
        if (!(condition)) {                                                  \
            (void)fprintf(                                                   \
                stderr,                                                      \
                "Requirement failed at %s:%d: %s\n",                        \
                __FILE__,                                                    \
                __LINE__,                                                    \
                #condition                                                   \
            );                                                               \
            return false;                                                    \
        }                                                                    \
    } while (false)

static bool add_edge(
    UndirectedIncidentGraph *graph,
    size_t u,
    size_t v,
    int64_t weight
)
{
    return mst_graph_add_edge(graph, u, v, weight) == MST_OK;
}

static bool test_frontier_stability_drain_and_full_diagnostic(void)
{
    PrimFrontier frontier = {0};
    PrimFrontierEntry entry;
    bool is_heap = false;
    size_t baseline = prim_frontier_test_live_allocation_count();
    size_t retained_capacity;
    size_t retained_sequence;

    REQUIRE(prim_frontier_init(&frontier, 6U) ==
        PRIM_FRONTIER_OK);
    REQUIRE(prim_frontier_push(
        &frontier,
        0U,
        INT64_C(0),
        PRIM_FRONTIER_NO_VERTEX,
        PRIM_FRONTIER_NO_EDGE
    ) == PRIM_FRONTIER_OK);
    REQUIRE(prim_frontier_push(
        &frontier,
        1U,
        INT64_C(4),
        0U,
        0U
    ) == PRIM_FRONTIER_OK);
    REQUIRE(prim_frontier_push(
        &frontier,
        2U,
        INT64_C(4),
        0U,
        1U
    ) == PRIM_FRONTIER_OK);
    REQUIRE(prim_frontier_push(
        &frontier,
        3U,
        -INT64_C(1),
        1U,
        2U
    ) == PRIM_FRONTIER_OK);
    REQUIRE(prim_frontier_test_live_allocation_count() ==
        baseline + 1U);
    REQUIRE(prim_frontier_is_min_heap(&frontier, &is_heap) ==
        PRIM_FRONTIER_OK);
    REQUIRE(is_heap);

    REQUIRE(prim_frontier_pop(&frontier, &entry) ==
        PRIM_FRONTIER_OK);
    REQUIRE(entry.vertex == 3U && entry.key == -INT64_C(1));
    REQUIRE(prim_frontier_pop(&frontier, &entry) ==
        PRIM_FRONTIER_OK);
    REQUIRE(entry.vertex == 0U && entry.insertion_sequence == 0U);
    REQUIRE(prim_frontier_pop(&frontier, &entry) ==
        PRIM_FRONTIER_OK);
    REQUIRE(entry.vertex == 1U && entry.insertion_sequence == 1U);
    REQUIRE(prim_frontier_pop(&frontier, &entry) ==
        PRIM_FRONTIER_OK);
    REQUIRE(entry.vertex == 2U && entry.insertion_sequence == 2U);
    retained_capacity = frontier.capacity;
    retained_sequence = frontier.next_sequence;
    REQUIRE(frontier.size == 0U && retained_capacity > 0U);
    REQUIRE(retained_sequence == 4U);
    REQUIRE(prim_frontier_validate(&frontier) ==
        PRIM_FRONTIER_OK);

    REQUIRE(prim_frontier_push(
        &frontier,
        4U,
        INT64_C(4),
        0U,
        3U
    ) == PRIM_FRONTIER_OK);
    REQUIRE(frontier.capacity == retained_capacity);
    REQUIRE(frontier.data[0].insertion_sequence == 4U);
    REQUIRE(prim_frontier_pop(&frontier, &entry) ==
        PRIM_FRONTIER_OK);
    REQUIRE(entry.insertion_sequence == 4U);
    REQUIRE(prim_frontier_pop(&frontier, &entry) ==
        PRIM_FRONTIER_EMPTY);

    prim_frontier_destroy(&frontier);
    REQUIRE(prim_frontier_test_live_allocation_count() == baseline);
    return true;
}

static bool test_frontier_rejects_impossible_shapes_and_duplicates(void)
{
    PrimFrontier impossible = {0};
    PrimFrontier frontier = {0};
    PrimFrontierEntry before;
    bool output = true;

    impossible.limit = 4U;
    impossible.next_sequence = 1U;
    REQUIRE(prim_frontier_validate(&impossible) ==
        PRIM_FRONTIER_INVALID_STATE);

    REQUIRE(prim_frontier_init(&frontier, 4U) ==
        PRIM_FRONTIER_OK);
    REQUIRE(prim_frontier_push(
        &frontier,
        0U,
        INT64_C(1),
        PRIM_FRONTIER_NO_VERTEX,
        PRIM_FRONTIER_NO_EDGE
    ) == PRIM_FRONTIER_OK);
    REQUIRE(prim_frontier_push(
        &frontier,
        1U,
        INT64_C(1),
        0U,
        0U
    ) == PRIM_FRONTIER_OK);
    frontier.data[1].insertion_sequence =
        frontier.data[0].insertion_sequence;
    REQUIRE(prim_frontier_is_min_heap(&frontier, &output) ==
        PRIM_FRONTIER_INVALID_STATE);
    REQUIRE(output);
    frontier.data[1].insertion_sequence = 1U;

    before = frontier.data[0];
    frontier.next_sequence = 0U;
    REQUIRE(prim_frontier_validate(&frontier) ==
        PRIM_FRONTIER_INVALID_STATE);
    REQUIRE(frontier.data[0].vertex == before.vertex);
    frontier.next_sequence = 2U;
    prim_frontier_destroy(&frontier);
    return true;
}

static bool test_frontier_allocation_failure_and_limit_preserve(void)
{
    PrimFrontier frontier = {0};
    PrimFrontier before;
    PrimFrontierEntry saved[8];
    PrimFrontierEntry output = {
        9U, INT64_C(9), 9U, 9U, 9U
    };
    UndirectedIncidentGraph graph;
    PrimResult prim;
    PrimResult prim_before;
    size_t baseline = prim_frontier_test_live_allocation_count();
    size_t index;

    REQUIRE(prim_frontier_init(&frontier, 9U) ==
        PRIM_FRONTIER_OK);
    before = frontier;
    prim_frontier_test_fail_next_growth();
    REQUIRE(prim_frontier_push(
        &frontier,
        0U,
        INT64_C(0),
        PRIM_FRONTIER_NO_VERTEX,
        PRIM_FRONTIER_NO_EDGE
    ) == PRIM_FRONTIER_ALLOCATION);
    REQUIRE(memcmp(&frontier, &before, sizeof frontier) == 0);
    REQUIRE(prim_frontier_test_live_allocation_count() == baseline);

    for (index = 0U; index < 8U; ++index) {
        REQUIRE(prim_frontier_push(
            &frontier,
            index,
            (int64_t)index,
            PRIM_FRONTIER_NO_VERTEX,
            PRIM_FRONTIER_NO_EDGE
        ) == PRIM_FRONTIER_OK);
    }
    REQUIRE(frontier.capacity == 8U);
    (void)memcpy(saved, frontier.data, sizeof saved);
    before = frontier;
    prim_frontier_test_fail_next_growth();
    REQUIRE(prim_frontier_push(
        &frontier,
        8U,
        INT64_C(8),
        PRIM_FRONTIER_NO_VERTEX,
        PRIM_FRONTIER_NO_EDGE
    ) == PRIM_FRONTIER_ALLOCATION);
    REQUIRE(memcmp(&frontier, &before, sizeof frontier) == 0);
    REQUIRE(memcmp(frontier.data, saved, sizeof saved) == 0);
    while (frontier.size > 0U) {
        REQUIRE(prim_frontier_pop(&frontier, &output) ==
            PRIM_FRONTIER_OK);
    }
    output = (PrimFrontierEntry){
        9U, INT64_C(9), 9U, 9U, 9U
    };
    REQUIRE(prim_frontier_pop(&frontier, &output) ==
        PRIM_FRONTIER_EMPTY);
    REQUIRE(output.vertex == 9U &&
        output.key == INT64_C(9) &&
        output.parent == 9U &&
        output.edge_id == 9U &&
        output.insertion_sequence == 9U);
    prim_frontier_destroy(&frontier);
    REQUIRE(prim_frontier_test_live_allocation_count() == baseline);

    REQUIRE(prim_frontier_init(&frontier, 2U) ==
        PRIM_FRONTIER_OK);
    REQUIRE(prim_frontier_push(
        &frontier,
        0U,
        INT64_C(0),
        PRIM_FRONTIER_NO_VERTEX,
        PRIM_FRONTIER_NO_EDGE
    ) == PRIM_FRONTIER_OK);
    REQUIRE(prim_frontier_push(
        &frontier,
        1U,
        INT64_C(1),
        0U,
        0U
    ) == PRIM_FRONTIER_OK);
    before = frontier;
    REQUIRE(prim_frontier_push(
        &frontier,
        2U,
        INT64_C(2),
        1U,
        1U
    ) == PRIM_FRONTIER_FULL);
    REQUIRE(memcmp(&frontier, &before, sizeof frontier) == 0);
    REQUIRE(prim_frontier_pop(&frontier, NULL) ==
        PRIM_FRONTIER_INVALID_ARGUMENT);
    prim_frontier_destroy(&frontier);
    REQUIRE(prim_frontier_test_live_allocation_count() == baseline);

    REQUIRE(mst_graph_init(&graph, 1U) == MST_OK);
    (void)memset(&prim, 0xA5, sizeof prim);
    prim_before = prim;
    prim_frontier_test_fail_next_growth();
    REQUIRE(prim_minimum_spanning_forest(&graph, &prim) ==
        MST_ALLOCATION);
    REQUIRE(memcmp(&prim, &prim_before, sizeof prim) == 0);
    REQUIRE(prim_frontier_test_live_allocation_count() == baseline);
    return true;
}

static bool test_comparator_extremes_and_graph_limits(void)
{
    UndirectedEdge low = {0U, 1U, INT64_MIN, 1U};
    UndirectedEdge high = {0U, 1U, INT64_MAX, 0U};
    UndirectedEdge first = {0U, 2U, INT64_C(4), 2U};
    UndirectedEdge second = {1U, 2U, INT64_C(4), 1U};
    UndirectedIncidentGraph graph;
    UndirectedIncidentGraph before;
    size_t index;

    REQUIRE(undirected_edge_compare(&low, &high) < 0);
    REQUIRE(undirected_edge_compare(&high, &low) > 0);
    REQUIRE(undirected_edge_compare(&first, &second) < 0);
    REQUIRE(undirected_edge_compare(&second, &first) > 0);
    REQUIRE(undirected_edge_compare(&first, &first) == 0);

    REQUIRE(mst_graph_init(&graph, 1U) == MST_OK);
    for (index = 0U;
         index < (size_t)UNDIRECTED_EDGE_LIST_MAX_LOGICAL_EDGES;
         ++index) {
        REQUIRE(add_edge(&graph, 0U, 0U, (int64_t)index));
    }
    REQUIRE(graph.incident_count ==
        (size_t)UNDIRECTED_EDGE_LIST_MAX_INCIDENT_RECORDS);
    before = graph;
    REQUIRE(mst_graph_add_edge(&graph, 0U, 0U, INT64_C(1)) ==
        MST_LIMIT);
    REQUIRE(memcmp(&graph, &before, sizeof graph) == 0);
    return true;
}

static bool test_all_negative_minimum_check_and_count_rejection(void)
{
    UndirectedIncidentGraph graph;
    UndirectedEdgeList list;
    MstForest forest = {0};
    PrimResult prim;

    REQUIRE(mst_graph_init(&graph, 3U) == MST_OK);
    REQUIRE(add_edge(&graph, 0U, 1U, -INT64_C(5)));
    REQUIRE(add_edge(&graph, 1U, 2U, -INT64_C(4)));
    REQUIRE(add_edge(&graph, 0U, 2U, -INT64_C(1)));
    REQUIRE(prim_minimum_spanning_forest(&graph, &prim) == MST_OK);
    REQUIRE(prim.forest.total_weight == -INT64_C(9));
    REQUIRE(mst_forest_validate(&graph, &prim.forest) == MST_OK);

    REQUIRE(undirected_edge_list_build(&graph, &list) ==
        UNDIRECTED_EDGE_LIST_OK);
    forest.vertex_count = 3U;
    forest.input_edge_count = 3U;
    forest.selected_edges[0] = list.edges[0];
    forest.selected_edges[1] = list.edges[2];
    forest.selected_count = 2U;
    forest.component_count = 1U;
    forest.total_weight = -INT64_C(6);
    REQUIRE(mst_forest_validate(&graph, &forest) ==
        MST_NOT_MINIMUM);

    forest = prim.forest;
    forest.component_count = 2U;
    REQUIRE(mst_forest_validate(&graph, &forest) ==
        MST_INVALID_RESULT);
    return true;
}

static bool test_validator_rejects_result_corruption(void)
{
    UndirectedIncidentGraph graph;
    UndirectedEdgeList list;
    KruskalResult result;
    MstForest bad;

    REQUIRE(mst_graph_init(&graph, 3U) == MST_OK);
    REQUIRE(add_edge(&graph, 0U, 1U, INT64_C(1)));
    REQUIRE(add_edge(&graph, 1U, 2U, INT64_C(2)));
    REQUIRE(add_edge(&graph, 0U, 2U, INT64_C(3)));
    REQUIRE(add_edge(&graph, 1U, 1U, -INT64_C(5)));
    REQUIRE(undirected_edge_list_build(&graph, &list) ==
        UNDIRECTED_EDGE_LIST_OK);
    REQUIRE(kruskal_minimum_spanning_forest(&graph, &result) ==
        MST_OK);
    REQUIRE(mst_forest_validate(&graph, &result.forest) == MST_OK);

    bad = result.forest;
    bad.selected_edges[bad.selected_count].u = 1U;
    REQUIRE(mst_forest_validate(&graph, &bad) ==
        MST_INVALID_RESULT);

    bad = result.forest;
    bad.selected_edges[1] = bad.selected_edges[0];
    bad.total_weight = INT64_C(2);
    REQUIRE(mst_forest_validate(&graph, &bad) ==
        MST_INVALID_RESULT);

    bad = result.forest;
    bad.selected_edges[1] = list.edges[3];
    bad.total_weight = -INT64_C(4);
    REQUIRE(mst_forest_validate(&graph, &bad) ==
        MST_INVALID_RESULT);

    bad = result.forest;
    bad.component_count = 2U;
    REQUIRE(mst_forest_validate(&graph, &bad) ==
        MST_INVALID_RESULT);
    return true;
}

static bool test_malformed_graph_and_status_names(void)
{
    UndirectedIncidentGraph graph;
    PrimResult prim;
    PrimResult before;

    REQUIRE(mst_graph_init(&graph, 2U) == MST_OK);
    REQUIRE(add_edge(&graph, 0U, 1U, INT64_C(3)));
    graph.incidents[1].weight = INT64_C(4);
    (void)memset(&prim, 0xA5, sizeof prim);
    before = prim;
    REQUIRE(prim_minimum_spanning_forest(&graph, &prim) ==
        MST_INVALID_GRAPH);
    REQUIRE(memcmp(&prim, &before, sizeof prim) == 0);

    REQUIRE(strcmp(mst_status_name(MST_NOT_MINIMUM),
        "MST_NOT_MINIMUM") == 0);
    REQUIRE(strcmp(
        prim_frontier_status_name(PRIM_FRONTIER_ALLOCATION),
        "PRIM_FRONTIER_ALLOCATION"
    ) == 0);
    REQUIRE(strcmp(dsu_status_name(DSU_FULL), "DSU_FULL") == 0);
    REQUIRE(strcmp(
        undirected_edge_list_status_name(
            UNDIRECTED_EDGE_LIST_INVALID_GRAPH
        ),
        "UNDIRECTED_EDGE_LIST_INVALID_GRAPH"
    ) == 0);
    REQUIRE(strcmp(
        mst_status_name((MstStatus)99),
        "MST_UNKNOWN_STATUS"
    ) == 0);
    return true;
}

static int run_test(TestFunction test, const char *name)
{
    bool passed = test();

    (void)printf("%s: %s\n", name, passed ? "PASS" : "FAIL");
    return passed ? 0 : 1;
}

int main(void)
{
    int failures = 0;

    failures += run_test(
        test_frontier_stability_drain_and_full_diagnostic,
        "stable signed Frontier and retained drain state"
    );
    failures += run_test(
        test_frontier_rejects_impossible_shapes_and_duplicates,
        "Frontier rejects impossible states and duplicate sequences"
    );
    failures += run_test(
        test_frontier_allocation_failure_and_limit_preserve,
        "Frontier allocation/full failure preservation"
    );
    failures += run_test(
        test_comparator_extremes_and_graph_limits,
        "relational comparator extremes and graph limits"
    );
    failures += run_test(
        test_all_negative_minimum_check_and_count_rejection,
        "all-negative path maximum and component/count rejection"
    );
    failures += run_test(
        test_validator_rejects_result_corruption,
        "validator rejects inactive, duplicate, loop, and count corruption"
    );
    failures += run_test(
        test_malformed_graph_and_status_names,
        "malformed graph preservation and status names"
    );

    if (failures != 0) {
        (void)fprintf(
            stderr,
            "%d extension test(s) failed.\n",
            failures
        );
        return 1;
    }

    puts("All Module 16 extension tests passed.");
    return 0;
}
