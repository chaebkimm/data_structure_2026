#include "minimum_spanning_forest.h"

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

static UndirectedIncidentGraph canonical_graph(void)
{
    UndirectedIncidentGraph graph;

    (void)mst_graph_init(&graph, 5U);
    (void)add_edge(&graph, 0U, 1U, INT64_C(4));
    (void)add_edge(&graph, 0U, 2U, INT64_C(4));
    (void)add_edge(&graph, 1U, 2U, INT64_C(1));
    (void)add_edge(&graph, 1U, 3U, INT64_C(5));
    (void)add_edge(&graph, 2U, 3U, INT64_C(2));
    (void)add_edge(&graph, 2U, 4U, INT64_C(3));
    (void)add_edge(&graph, 3U, 4U, INT64_C(3));
    (void)add_edge(&graph, 0U, 4U, INT64_C(10));
    return graph;
}

static bool selected_ids_equal(
    const MstForest *forest,
    const size_t *expected,
    size_t count
)
{
    size_t index;

    if (forest->selected_count != count) {
        return false;
    }
    for (index = 0U; index < count; ++index) {
        if (forest->selected_edges[index].edge_id != expected[index]) {
            return false;
        }
    }
    return true;
}

static bool test_signed_parser_graph_builder_and_index(void)
{
    UndirectedIncidentGraph graph;
    UndirectedIncidentGraph before;
    UndirectedEdgeList edges;
    MstAdjacencyIndex adjacency;
    int64_t weight = INT64_C(777);
    size_t index;

    REQUIRE(mst_parse_weight(" -9223372036854775808 ", &weight) ==
        MST_OK);
    REQUIRE(weight == INT64_MIN);
    REQUIRE(mst_parse_weight("+9223372036854775807", &weight) ==
        MST_OK);
    REQUIRE(weight == INT64_MAX);
    REQUIRE(mst_parse_weight("9223372036854775808", &weight) ==
        MST_WEIGHT_OUT_OF_RANGE);
    REQUIRE(weight == INT64_MAX);
    REQUIRE(mst_parse_weight("--1", &weight) ==
        MST_INVALID_WEIGHT_TEXT);
    REQUIRE(weight == INT64_MAX);
    REQUIRE(mst_parse_weight("", &weight) ==
        MST_INVALID_WEIGHT_TEXT);
    REQUIRE(mst_parse_weight("1x", &weight) ==
        MST_INVALID_WEIGHT_TEXT);
    REQUIRE(mst_parse_weight(NULL, &weight) ==
        MST_INVALID_ARGUMENT);
    REQUIRE(mst_parse_weight("1", NULL) ==
        MST_INVALID_ARGUMENT);

    REQUIRE(mst_graph_init(&graph, 3U) == MST_OK);
    REQUIRE(add_edge(&graph, 0U, 1U, -INT64_C(2)));
    REQUIRE(add_edge(&graph, 0U, 1U, INT64_C(5)));
    REQUIRE(add_edge(&graph, 1U, 1U, -INT64_C(100)));
    REQUIRE(graph.logical_edge_count == 3U);
    REQUIRE(graph.incident_count == 6U);
    REQUIRE(graph.incidents[4].from == 1U);
    REQUIRE(graph.incidents[4].to == 1U);
    REQUIRE(graph.incidents[5].from == 1U);
    REQUIRE(graph.incidents[5].to == 1U);
    REQUIRE(mst_graph_validate(&graph) == MST_OK);

    before = graph;
    REQUIRE(mst_graph_add_edge(&graph, 0U, 3U, INT64_C(1)) ==
        MST_OUT_OF_RANGE);
    REQUIRE(memcmp(&graph, &before, sizeof graph) == 0);
    REQUIRE(undirected_edge_list_build(&graph, &edges) ==
        UNDIRECTED_EDGE_LIST_OK);
    REQUIRE(mst_adjacency_index_build(
        &graph,
        &edges,
        &adjacency
    ) == MST_OK);
    REQUIRE(adjacency.incident_count == 6U);
    REQUIRE(adjacency.offsets[0] == 0U);
    REQUIRE(adjacency.offsets[1] == 2U);
    REQUIRE(adjacency.offsets[2] == 6U);
    REQUIRE(adjacency.offsets[3] == 6U);
    REQUIRE(adjacency.edge_ids[0] == 0U);
    REQUIRE(adjacency.edge_ids[1] == 1U);
    for (index = 1U; index < 6U; ++index) {
        if (index != 2U) {
            REQUIRE(
                adjacency.edge_ids[index - 1U] <=
                    adjacency.edge_ids[index] ||
                index == adjacency.offsets[1]
            );
        }
    }
    return true;
}

static bool test_canonical_prim_and_kruskal(void)
{
    static const size_t prim_ids[4] = {0U, 2U, 4U, 5U};
    static const size_t kruskal_ids[4] = {2U, 4U, 5U, 0U};
    UndirectedIncidentGraph graph = canonical_graph();
    PrimResult prim;
    KruskalResult kruskal;

    REQUIRE(prim_minimum_spanning_forest(&graph, &prim) == MST_OK);
    REQUIRE(kruskal_minimum_spanning_forest(&graph, &kruskal) ==
        MST_OK);

    REQUIRE(selected_ids_equal(&prim.forest, prim_ids, 4U));
    REQUIRE(prim.forest.component_count == 1U);
    REQUIRE(prim.forest.total_weight == INT64_C(10));
    REQUIRE(prim.push_count == 8U);
    REQUIRE(prim.pop_count == 8U);
    REQUIRE(prim.stale_pop_count == 3U);
    REQUIRE(prim.already_in_tree_pop_count == 0U);
    REQUIRE(prim.frontier_peak == 5U);
    REQUIRE(prim.incident_scan_count == 16U);
    REQUIRE(prim.eligible_crossing_count == 8U);
    REQUIRE(prim.key_improvement_count == 7U);

    REQUIRE(selected_ids_equal(&kruskal.forest, kruskal_ids, 4U));
    REQUIRE(kruskal.forest.component_count == 1U);
    REQUIRE(kruskal.forest.total_weight == INT64_C(10));
    REQUIRE(kruskal.examined_edge_count == 8U);
    REQUIRE(kruskal.cycle_skip_count == 4U);
    REQUIRE(kruskal.self_loop_skip_count == 0U);

    REQUIRE(mst_forest_validate(&graph, &prim.forest) == MST_OK);
    REQUIRE(mst_forest_validate(&graph, &kruskal.forest) ==
        MST_OK);
    return true;
}

static bool test_singleton_empty_and_disconnected_boundaries(void)
{
    static const size_t prim_ids[3] = {2U, 1U, 3U};
    static const size_t kruskal_ids[3] = {1U, 3U, 2U};
    UndirectedIncidentGraph graph;
    PrimResult prim;
    KruskalResult kruskal;

    REQUIRE(mst_graph_init(&graph, 0U) == MST_OK);
    REQUIRE(prim_minimum_spanning_forest(&graph, &prim) == MST_OK);
    REQUIRE(kruskal_minimum_spanning_forest(&graph, &kruskal) ==
        MST_OK);
    REQUIRE(prim.forest.selected_count == 0U);
    REQUIRE(prim.forest.component_count == 0U);
    REQUIRE(prim.forest.total_weight == INT64_C(0));
    REQUIRE(kruskal.forest.component_count == 0U);
    REQUIRE(mst_forest_validate(&graph, &prim.forest) == MST_OK);

    REQUIRE(mst_graph_init(&graph, 1U) == MST_OK);
    REQUIRE(prim_minimum_spanning_forest(&graph, &prim) == MST_OK);
    REQUIRE(kruskal_minimum_spanning_forest(&graph, &kruskal) ==
        MST_OK);
    REQUIRE(prim.forest.selected_count == 0U);
    REQUIRE(prim.forest.component_count == 1U);
    REQUIRE(prim.push_count == 1U && prim.pop_count == 1U);
    REQUIRE(kruskal.forest.component_count == 1U);
    REQUIRE(mst_forest_validate(&graph, &kruskal.forest) == MST_OK);

    REQUIRE(mst_graph_init(&graph, 6U) == MST_OK);
    REQUIRE(add_edge(&graph, 0U, 1U, INT64_C(4)));
    REQUIRE(add_edge(&graph, 1U, 2U, -INT64_C(2)));
    REQUIRE(add_edge(&graph, 0U, 2U, INT64_C(3)));
    REQUIRE(add_edge(&graph, 3U, 4U, INT64_C(1)));
    REQUIRE(add_edge(&graph, 3U, 4U, INT64_C(1)));
    REQUIRE(add_edge(&graph, 4U, 4U, -INT64_C(9)));

    REQUIRE(prim_minimum_spanning_forest(&graph, &prim) == MST_OK);
    REQUIRE(kruskal_minimum_spanning_forest(&graph, &kruskal) ==
        MST_OK);
    REQUIRE(selected_ids_equal(&prim.forest, prim_ids, 3U));
    REQUIRE(selected_ids_equal(&kruskal.forest, kruskal_ids, 3U));
    REQUIRE(prim.forest.component_count == 3U);
    REQUIRE(kruskal.forest.component_count == 3U);
    REQUIRE(prim.forest.total_weight == INT64_C(2));
    REQUIRE(kruskal.forest.total_weight == INT64_C(2));
    REQUIRE(kruskal.self_loop_skip_count == 1U);
    REQUIRE(kruskal.cycle_skip_count == 2U);
    REQUIRE(mst_forest_validate(&graph, &prim.forest) == MST_OK);
    REQUIRE(mst_forest_validate(&graph, &kruskal.forest) ==
        MST_OK);
    return true;
}

static bool test_equal_alternatives_choose_different_edges(void)
{
    static const size_t prim_ids[3] = {0U, 2U, 1U};
    static const size_t kruskal_ids[3] = {2U, 0U, 3U};
    UndirectedIncidentGraph graph;
    PrimResult prim;
    KruskalResult kruskal;

    REQUIRE(mst_graph_init(&graph, 4U) == MST_OK);
    REQUIRE(add_edge(&graph, 0U, 3U, INT64_C(1)));
    REQUIRE(add_edge(&graph, 2U, 3U, INT64_C(1)));
    REQUIRE(add_edge(&graph, 0U, 1U, INT64_C(1)));
    REQUIRE(add_edge(&graph, 1U, 2U, INT64_C(1)));

    REQUIRE(prim_minimum_spanning_forest(&graph, &prim) == MST_OK);
    REQUIRE(kruskal_minimum_spanning_forest(&graph, &kruskal) ==
        MST_OK);
    REQUIRE(selected_ids_equal(&prim.forest, prim_ids, 3U));
    REQUIRE(selected_ids_equal(&kruskal.forest, kruskal_ids, 3U));
    REQUIRE(prim.forest.total_weight == INT64_C(3));
    REQUIRE(kruskal.forest.total_weight == INT64_C(3));
    REQUIRE(mst_forest_validate(&graph, &prim.forest) == MST_OK);
    REQUIRE(mst_forest_validate(&graph, &kruskal.forest) ==
        MST_OK);
    return true;
}

static bool test_large_total_cancellation_and_out_of_range(void)
{
    UndirectedIncidentGraph graph;
    PrimResult prim;
    KruskalResult kruskal;
    PrimResult prim_before;
    KruskalResult kruskal_before;

    REQUIRE(mst_graph_init(&graph, 3U) == MST_OK);
    REQUIRE(add_edge(&graph, 0U, 1U, INT64_C(2000000000)));
    REQUIRE(add_edge(&graph, 1U, 2U, INT64_C(2000000000)));
    REQUIRE(add_edge(&graph, 0U, 2U, INT64_C(2100000000)));
    REQUIRE(prim_minimum_spanning_forest(&graph, &prim) == MST_OK);
    REQUIRE(kruskal_minimum_spanning_forest(&graph, &kruskal) ==
        MST_OK);
    REQUIRE(prim.forest.total_weight == INT64_C(4000000000));
    REQUIRE(kruskal.forest.total_weight == INT64_C(4000000000));

    REQUIRE(mst_graph_init(&graph, 4U) == MST_OK);
    REQUIRE(add_edge(&graph, 0U, 1U, INT64_MAX));
    REQUIRE(add_edge(&graph, 1U, 2U, INT64_MAX));
    REQUIRE(add_edge(&graph, 2U, 3U, INT64_MIN));
    REQUIRE(prim_minimum_spanning_forest(&graph, &prim) == MST_OK);
    REQUIRE(kruskal_minimum_spanning_forest(&graph, &kruskal) ==
        MST_OK);
    REQUIRE(prim.forest.total_weight == INT64_MAX - INT64_C(1));
    REQUIRE(kruskal.forest.total_weight == INT64_MAX - INT64_C(1));
    REQUIRE(mst_forest_validate(&graph, &prim.forest) == MST_OK);
    REQUIRE(mst_forest_validate(&graph, &kruskal.forest) ==
        MST_OK);

    (void)memset(&prim, 0xA5, sizeof prim);
    (void)memset(&kruskal, 0x5A, sizeof kruskal);
    prim_before = prim;
    kruskal_before = kruskal;
    REQUIRE(mst_graph_init(&graph, 3U) == MST_OK);
    REQUIRE(add_edge(&graph, 0U, 1U, INT64_MAX));
    REQUIRE(add_edge(&graph, 1U, 2U, INT64_C(1)));
    REQUIRE(prim_minimum_spanning_forest(&graph, &prim) ==
        MST_TOTAL_OUT_OF_RANGE);
    REQUIRE(kruskal_minimum_spanning_forest(&graph, &kruskal) ==
        MST_TOTAL_OUT_OF_RANGE);
    REQUIRE(memcmp(&prim, &prim_before, sizeof prim) == 0);
    REQUIRE(memcmp(&kruskal, &kruskal_before, sizeof kruskal) == 0);

    REQUIRE(mst_graph_init(&graph, 3U) == MST_OK);
    REQUIRE(add_edge(&graph, 0U, 1U, INT64_MIN));
    REQUIRE(add_edge(&graph, 1U, 2U, -INT64_C(1)));
    REQUIRE(prim_minimum_spanning_forest(&graph, &prim) ==
        MST_TOTAL_OUT_OF_RANGE);
    REQUIRE(kruskal_minimum_spanning_forest(&graph, &kruskal) ==
        MST_TOTAL_OUT_OF_RANGE);
    REQUIRE(memcmp(&prim, &prim_before, sizeof prim) == 0);
    REQUIRE(memcmp(&kruskal, &kruskal_before, sizeof kruskal) == 0);
    return true;
}

static bool test_invalid_endpoint_and_validator_diagnostics(void)
{
    UndirectedIncidentGraph graph = canonical_graph();
    PrimResult prim;
    KruskalResult kruskal;
    PrimResult prim_before;
    KruskalResult kruskal_before;
    MstForest bad;
    UndirectedEdgeList edge_list;

    (void)memset(&prim, 0xA5, sizeof prim);
    (void)memset(&kruskal, 0x5A, sizeof kruskal);
    prim_before = prim;
    kruskal_before = kruskal;
    graph.incidents[0].to = graph.vertex_count;
    REQUIRE(prim_minimum_spanning_forest(&graph, &prim) ==
        MST_OUT_OF_RANGE);
    REQUIRE(kruskal_minimum_spanning_forest(&graph, &kruskal) ==
        MST_OUT_OF_RANGE);
    REQUIRE(memcmp(&prim, &prim_before, sizeof prim) == 0);
    REQUIRE(memcmp(&kruskal, &kruskal_before, sizeof kruskal) == 0);

    graph = canonical_graph();
    REQUIRE(prim_minimum_spanning_forest(&graph, &prim) == MST_OK);
    bad = prim.forest;
    bad.total_weight += INT64_C(1);
    REQUIRE(mst_forest_validate(&graph, &bad) ==
        MST_INVALID_RESULT);
    bad = prim.forest;
    bad.selected_edges[0].edge_id = 99U;
    REQUIRE(mst_forest_validate(&graph, &bad) ==
        MST_INVALID_RESULT);

    REQUIRE(mst_graph_init(&graph, 3U) == MST_OK);
    REQUIRE(add_edge(&graph, 0U, 1U, INT64_C(1)));
    REQUIRE(add_edge(&graph, 1U, 2U, INT64_C(2)));
    REQUIRE(add_edge(&graph, 0U, 2U, INT64_C(3)));
    REQUIRE(undirected_edge_list_build(&graph, &edge_list) ==
        UNDIRECTED_EDGE_LIST_OK);
    (void)memset(&bad, 0, sizeof bad);
    bad.vertex_count = 3U;
    bad.input_edge_count = 3U;
    bad.selected_edges[0] = edge_list.edges[0];
    bad.selected_edges[1] = edge_list.edges[2];
    bad.selected_count = 2U;
    bad.component_count = 1U;
    bad.total_weight = INT64_C(4);
    REQUIRE(mst_forest_validate(&graph, &bad) ==
        MST_NOT_MINIMUM);
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
        test_signed_parser_graph_builder_and_index,
        "signed parser, multigraph builder, and indexed adjacency"
    );
    failures += run_test(
        test_canonical_prim_and_kruskal,
        "canonical Prim and Kruskal traces"
    );
    failures += run_test(
        test_singleton_empty_and_disconnected_boundaries,
        "empty, singleton, and disconnected forest boundaries"
    );
    failures += run_test(
        test_equal_alternatives_choose_different_edges,
        "equal alternatives agree on total, not selected IDs"
    );
    failures += run_test(
        test_large_total_cancellation_and_out_of_range,
        "int64 total, cancellation, and final range"
    );
    failures += run_test(
        test_invalid_endpoint_and_validator_diagnostics,
        "invalid endpoint preservation and validator diagnostics"
    );

    if (failures != 0) {
        (void)fprintf(stderr, "%d core test(s) failed.\n", failures);
        return 1;
    }

    puts("All Module 16 core tests passed.");
    return 0;
}
