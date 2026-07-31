#include "dsu.h"
#include "linked_list.h"
#include "undirected_edge_list.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef bool (*TestFunction)(void);

typedef struct {
    LinkedNode *head;
    size_t size;
    size_t limit;
    LinkedNode *nodes[LINKED_LIST_MAX_NODES];
    LinkedNode *next[LINKED_LIST_MAX_NODES];
    int values[LINKED_LIST_MAX_NODES];
} ListSnapshot;

static LinkedList *active_list = NULL;

static void cleanup_active_list(void)
{
    if (active_list != NULL) {
        linked_list_destroy(active_list);
        active_list = NULL;
    }
}

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
            cleanup_active_list();                                           \
            return false;                                                    \
        }                                                                    \
    } while (false)

static bool snapshot_list(
    const LinkedList *list,
    ListSnapshot *snapshot
)
{
    LinkedNode *current;
    size_t index;

    if (!linked_list_is_valid(list) || snapshot == NULL) {
        return false;
    }

    snapshot->head = list->head;
    snapshot->size = list->size;
    snapshot->limit = list->limit;
    current = list->head;
    for (index = 0U; index < list->size; ++index) {
        snapshot->nodes[index] = current;
        snapshot->next[index] = current->next;
        snapshot->values[index] = current->value;
        current = current->next;
    }
    return true;
}

static bool list_matches(
    const LinkedList *list,
    const ListSnapshot *snapshot
)
{
    LinkedNode *current;
    size_t index;

    if (list == NULL || snapshot == NULL ||
        list->head != snapshot->head ||
        list->size != snapshot->size ||
        list->limit != snapshot->limit) {
        return false;
    }

    current = list->head;
    for (index = 0U; index < list->size; ++index) {
        if (current != snapshot->nodes[index] ||
            current->next != snapshot->next[index] ||
            current->value != snapshot->values[index]) {
            return false;
        }
        current = current->next;
    }
    return current == NULL;
}

static bool make_elements(Dsu *sets, size_t count)
{
    size_t index;

    for (index = 0U; index < count; ++index) {
        size_t created = 99U;

        if (dsu_make_set(sets, &created) != DSU_OK ||
            created != index) {
            return false;
        }
    }
    return true;
}

static bool merge_pair(Dsu *sets, size_t left, size_t right)
{
    bool merged = false;

    return dsu_union(sets, left, right, &merged) == DSU_OK && merged;
}

static UndirectedIncidentGraph canonical_incident_graph(void)
{
    UndirectedIncidentGraph graph = {0};

    graph.vertex_count = 4U;
    graph.logical_edge_count = 6U;
    graph.incident_count = 12U;
    graph.incidents[0] = (UndirectedIncidentRecord){
        3U, 2U, INT64_MAX, 4U
    };
    graph.incidents[1] = (UndirectedIncidentRecord){
        1U, 0U, INT64_C(7), 0U
    };
    graph.incidents[2] = (UndirectedIncidentRecord){
        2U, 2U, INT64_C(5), 3U
    };
    graph.incidents[3] = (UndirectedIncidentRecord){
        0U, 1U, INT64_C(2), 2U
    };
    graph.incidents[4] = (UndirectedIncidentRecord){
        0U, 3U, INT64_MIN, 5U
    };
    graph.incidents[5] = (UndirectedIncidentRecord){
        1U, 2U, -INT64_C(3), 1U
    };
    graph.incidents[6] = (UndirectedIncidentRecord){
        0U, 1U, INT64_C(7), 0U
    };
    graph.incidents[7] = (UndirectedIncidentRecord){
        1U, 0U, INT64_C(2), 2U
    };
    graph.incidents[8] = (UndirectedIncidentRecord){
        2U, 1U, -INT64_C(3), 1U
    };
    graph.incidents[9] = (UndirectedIncidentRecord){
        3U, 0U, INT64_MIN, 5U
    };
    graph.incidents[10] = (UndirectedIncidentRecord){
        2U, 3U, INT64_MAX, 4U
    };
    graph.incidents[11] = (UndirectedIncidentRecord){
        2U, 2U, INT64_C(5), 3U
    };
    return graph;
}

static bool test_list_duplicates_hook_order_and_boundaries(void)
{
    LinkedList list = {0};
    ListSnapshot before;
    size_t baseline = linked_list_test_live_node_count();
    LinkedNode *older_seven;
    bool removed = false;
    int value = 444;

    REQUIRE(linked_list_init(&list, 2U) == LINKED_LIST_OK);
    active_list = &list;
    REQUIRE(linked_list_push_front(&list, 7) == LINKED_LIST_OK);
    older_seven = list.head;
    REQUIRE(linked_list_push_front(&list, 7) == LINKED_LIST_OK);
    REQUIRE(list.head != older_seven && list.head->next == older_seven);

    REQUIRE(linked_list_remove_first(&list, 7, &removed) ==
        LINKED_LIST_OK);
    REQUIRE(removed && list.head == older_seven && list.size == 1U);
    REQUIRE(linked_list_test_live_node_count() == baseline + 1U);
    REQUIRE(linked_list_push_front(&list, 8) == LINKED_LIST_OK);
    REQUIRE(snapshot_list(&list, &before));

    linked_list_test_fail_next_allocation();
    REQUIRE(linked_list_push_front(&list, 9) == LINKED_LIST_FULL);
    REQUIRE(list_matches(&list, &before));
    REQUIRE(linked_list_remove_first(&list, 7, &removed) ==
        LINKED_LIST_OK);
    REQUIRE(removed);
    REQUIRE(linked_list_push_front(&list, 9) ==
        LINKED_LIST_ALLOCATION);
    REQUIRE(linked_list_push_front(&list, 9) == LINKED_LIST_OK);

    REQUIRE(snapshot_list(&list, &before));
    REQUIRE(linked_list_get(&list, list.size, &value) ==
        LINKED_LIST_OUT_OF_RANGE);
    REQUIRE(value == 444);
    REQUIRE(list_matches(&list, &before));
    REQUIRE(linked_list_remove_first(&list, 8, NULL) ==
        LINKED_LIST_INVALID_ARGUMENT);
    REQUIRE(list_matches(&list, &before));
    REQUIRE(linked_list_init(
        &list,
        (size_t)LINKED_LIST_MAX_NODES + 1U
    ) == LINKED_LIST_OUT_OF_RANGE);
    REQUIRE(list_matches(&list, &before));

    linked_list_destroy(&list);
    active_list = NULL;
    REQUIRE(linked_list_test_live_node_count() == baseline);
    return true;
}

static bool test_list_diagnostic_rejects_bad_shapes(void)
{
    LinkedNode first = {1, NULL};
    LinkedNode second = {2, NULL};
    LinkedList cycle;
    LinkedList short_chain;
    LinkedList head_mismatch;

    first.next = &second;
    second.next = &first;
    cycle.head = &first;
    cycle.size = 2U;
    cycle.limit = 2U;
    REQUIRE(!linked_list_is_valid(&cycle));

    second.next = NULL;
    short_chain.head = &first;
    short_chain.size = 3U;
    short_chain.limit = 3U;
    REQUIRE(!linked_list_is_valid(&short_chain));

    head_mismatch.head = &first;
    head_mismatch.size = 0U;
    head_mismatch.limit = 1U;
    REQUIRE(!linked_list_is_valid(&head_mismatch));
    REQUIRE(!linked_list_is_valid(NULL));
    return true;
}

static bool test_dsu_equal_size_full_and_sentinels(void)
{
    Dsu sets;
    Dsu full_before;
    size_t created = 777U;
    size_t index;

    REQUIRE(dsu_init(NULL) == DSU_INVALID_ARGUMENT);
    REQUIRE(dsu_init(&sets) == DSU_OK);
    for (index = 0U; index < (size_t)DSU_MAX_ELEMENTS; ++index) {
        REQUIRE(sets.parent[index] == DSU_NO_ELEMENT);
        REQUIRE(sets.component_size[index] == 0U);
    }

    REQUIRE(make_elements(&sets, 4U));
    REQUIRE(merge_pair(&sets, 1U, 0U));
    REQUIRE(sets.parent[1] == 0U && sets.component_size[0] == 2U);
    REQUIRE(merge_pair(&sets, 3U, 2U));
    REQUIRE(sets.parent[3] == 2U && sets.component_size[2] == 2U);
    REQUIRE(merge_pair(&sets, 2U, 0U));
    REQUIRE(sets.parent[2] == 0U);
    REQUIRE(sets.component_size[0] == 4U);
    REQUIRE(sets.component_size[2] == 0U);
    REQUIRE(dsu_is_valid(&sets));

    REQUIRE(dsu_init(&sets) == DSU_OK);
    REQUIRE(make_elements(&sets, (size_t)DSU_MAX_ELEMENTS));
    full_before = sets;
    REQUIRE(dsu_make_set(&sets, &created) == DSU_FULL);
    REQUIRE(created == 777U);
    REQUIRE(memcmp(&sets, &full_before, sizeof sets) == 0);
    return true;
}

static bool test_dsu_malformed_second_path_is_atomic(void)
{
    Dsu sets;
    Dsu before;
    bool answer = true;
    size_t root = 555U;

    REQUIRE(dsu_init(&sets) == DSU_OK);
    REQUIRE(make_elements(&sets, 6U));
    REQUIRE(merge_pair(&sets, 0U, 1U));
    REQUIRE(merge_pair(&sets, 2U, 3U));
    REQUIRE(merge_pair(&sets, 0U, 2U));
    REQUIRE(sets.parent[3] == 2U);

    sets.parent[4] = 5U;
    sets.parent[5] = 4U;
    sets.component_size[4] = 0U;
    sets.component_size[5] = 0U;
    before = sets;
    REQUIRE(!dsu_is_valid(&sets));

    REQUIRE(dsu_connected(&sets, 3U, 5U, &answer) ==
        DSU_INVALID_STATE);
    REQUIRE(answer);
    REQUIRE(memcmp(&sets, &before, sizeof sets) == 0);

    REQUIRE(dsu_union(&sets, 3U, 5U, &answer) ==
        DSU_INVALID_STATE);
    REQUIRE(answer);
    REQUIRE(memcmp(&sets, &before, sizeof sets) == 0);

    REQUIRE(dsu_add_connection(&sets, 3U, 5U, &answer) ==
        DSU_INVALID_STATE);
    REQUIRE(answer);
    REQUIRE(memcmp(&sets, &before, sizeof sets) == 0);

    REQUIRE(dsu_find(&sets, 5U, &root) == DSU_INVALID_STATE);
    REQUIRE(root == 555U);
    REQUIRE(memcmp(&sets, &before, sizeof sets) == 0);
    return true;
}

static bool test_dsu_large_size_and_invalid_id_preservation(void)
{
    Dsu sets;
    Dsu before;
    bool merged = true;
    size_t root = 333U;

    REQUIRE(dsu_init(&sets) == DSU_OK);
    REQUIRE(make_elements(&sets, 2U));
    sets.component_size[0] = SIZE_MAX;
    before = sets;
    REQUIRE(dsu_union(&sets, 0U, 1U, &merged) ==
        DSU_INVALID_STATE);
    REQUIRE(merged);
    REQUIRE(memcmp(&sets, &before, sizeof sets) == 0);

    REQUIRE(dsu_init(&sets) == DSU_OK);
    REQUIRE(make_elements(&sets, 2U));
    before = sets;
    REQUIRE(dsu_find(&sets, 2U, &root) == DSU_OUT_OF_RANGE);
    REQUIRE(root == 333U);
    REQUIRE(memcmp(&sets, &before, sizeof sets) == 0);
    return true;
}

static bool test_edge_malformed_mirrors_preserve_output(void)
{
    UndirectedIncidentGraph graph = canonical_incident_graph();
    UndirectedEdgeList output;
    UndirectedEdgeList before;

    (void)memset(&output, 0xA5, sizeof output);
    before = output;
    graph.incidents[6].weight = INT64_C(8);
    REQUIRE(undirected_edge_list_build(&graph, &output) ==
        UNDIRECTED_EDGE_LIST_INVALID_GRAPH);
    REQUIRE(memcmp(&output, &before, sizeof output) == 0);

    graph = canonical_incident_graph();
    graph.incidents[6].from = 1U;
    graph.incidents[6].to = 0U;
    REQUIRE(undirected_incident_graph_validate(&graph) ==
        UNDIRECTED_EDGE_LIST_INVALID_GRAPH);

    graph = canonical_incident_graph();
    graph.incidents[0].from = 4U;
    REQUIRE(undirected_incident_graph_validate(&graph) ==
        UNDIRECTED_EDGE_LIST_OUT_OF_RANGE);

    graph = canonical_incident_graph();
    graph.incidents[0].edge_id = 99U;
    REQUIRE(undirected_incident_graph_validate(&graph) ==
        UNDIRECTED_EDGE_LIST_INVALID_GRAPH);

    graph = canonical_incident_graph();
    graph.incident_count = 11U;
    REQUIRE(undirected_incident_graph_validate(&graph) ==
        UNDIRECTED_EDGE_LIST_INVALID_GRAPH);

    graph = canonical_incident_graph();
    graph.incidents[12].weight = INT64_C(1);
    REQUIRE(undirected_incident_graph_validate(&graph) ==
        UNDIRECTED_EDGE_LIST_INVALID_GRAPH);
    return true;
}

static bool test_edge_list_sort_validation_and_total_order(void)
{
    static const size_t sorted_ids[6] = {
        5U, 1U, 2U, 3U, 0U, 4U
    };
    UndirectedIncidentGraph graph = canonical_incident_graph();
    UndirectedEdgeList list;
    UndirectedEdgeList sorted;
    UndirectedEdgeList before;
    UndirectedEdge first = {0U, 1U, INT64_C(4), 1U};
    UndirectedEdge second = {0U, 2U, INT64_C(4), 0U};
    UndirectedEdge third = {0U, 2U, INT64_C(4), 3U};
    UndirectedEdge low = {0U, 3U, INT64_MIN, 5U};
    UndirectedEdge high = {2U, 3U, INT64_MAX, 4U};

    REQUIRE(undirected_edge_list_build(&graph, &list) ==
        UNDIRECTED_EDGE_LIST_OK);
    REQUIRE(list.size == 6U);
    REQUIRE(list.edges[0].u == 0U && list.edges[0].v == 1U);
    REQUIRE(list.edges[2].u == 0U && list.edges[2].v == 1U);
    REQUIRE(list.edges[3].u == 2U && list.edges[3].v == 2U);
    sorted = list;
    REQUIRE(undirected_edge_list_sort(&sorted) ==
        UNDIRECTED_EDGE_LIST_OK);
    {
        size_t index;

        for (index = 0U; index < sorted.size; ++index) {
            REQUIRE(sorted.edges[index].edge_id == sorted_ids[index]);
        }
    }

    list.edges[1].edge_id = list.edges[0].edge_id;
    before = list;
    REQUIRE(undirected_edge_list_sort(&list) ==
        UNDIRECTED_EDGE_LIST_INVALID_LIST);
    REQUIRE(memcmp(&list, &before, sizeof list) == 0);

    REQUIRE(undirected_edge_compare(&first, &second) < 0);
    REQUIRE(undirected_edge_compare(&second, &first) > 0);
    REQUIRE(undirected_edge_compare(&second, &third) < 0);
    REQUIRE(undirected_edge_compare(&third, &second) > 0);
    REQUIRE(undirected_edge_compare(&second, &second) == 0);
    REQUIRE(undirected_edge_compare(&low, &high) < 0);
    REQUIRE(undirected_edge_compare(&high, &low) > 0);

    REQUIRE(undirected_edge_list_validate(NULL) ==
        UNDIRECTED_EDGE_LIST_INVALID_ARGUMENT);
    REQUIRE(undirected_edge_list_build(&graph, NULL) ==
        UNDIRECTED_EDGE_LIST_INVALID_ARGUMENT);
    return true;
}

static bool test_argument_rejection_and_status_names(void)
{
    LinkedList list;
    Dsu sets;
    Dsu before;
    int value = 808;
    bool answer = true;
    size_t element = 909U;

    REQUIRE(linked_list_init(&list, 0U) == LINKED_LIST_OK);
    REQUIRE(linked_list_push_front(&list, 1) == LINKED_LIST_FULL);
    linked_list_destroy(&list);
    REQUIRE(linked_list_init(
        &list,
        (size_t)LINKED_LIST_MAX_NODES
    ) == LINKED_LIST_OK);
    REQUIRE(linked_list_is_valid(&list));
    linked_list_destroy(&list);
    REQUIRE(linked_list_push_front(NULL, 1) ==
        LINKED_LIST_INVALID_ARGUMENT);
    REQUIRE(linked_list_get(NULL, 0U, &value) ==
        LINKED_LIST_INVALID_ARGUMENT);
    REQUIRE(value == 808);
    REQUIRE(linked_list_get(&list, 0U, NULL) ==
        LINKED_LIST_INVALID_ARGUMENT);
    REQUIRE(linked_list_remove_first(NULL, 1, &answer) ==
        LINKED_LIST_INVALID_ARGUMENT);
    REQUIRE(answer);

    REQUIRE(dsu_init(&sets) == DSU_OK);
    REQUIRE(dsu_make_set(&sets, &element) == DSU_OK);
    REQUIRE(element == 0U);
    before = sets;
    REQUIRE(dsu_make_set(&sets, NULL) == DSU_INVALID_ARGUMENT);
    REQUIRE(dsu_find(&sets, 0U, NULL) == DSU_INVALID_ARGUMENT);
    REQUIRE(dsu_connected(&sets, 0U, 0U, NULL) ==
        DSU_INVALID_ARGUMENT);
    REQUIRE(dsu_union(&sets, 0U, 0U, NULL) ==
        DSU_INVALID_ARGUMENT);
    REQUIRE(dsu_add_connection(&sets, 0U, 0U, NULL) ==
        DSU_INVALID_ARGUMENT);
    REQUIRE(memcmp(&sets, &before, sizeof sets) == 0);

    REQUIRE(undirected_incident_graph_validate(NULL) ==
        UNDIRECTED_EDGE_LIST_INVALID_ARGUMENT);
    REQUIRE(undirected_edge_list_sort(NULL) ==
        UNDIRECTED_EDGE_LIST_INVALID_ARGUMENT);

    REQUIRE(strcmp(
        linked_list_status_name(LINKED_LIST_ALLOCATION),
        "LINKED_LIST_ALLOCATION"
    ) == 0);
    REQUIRE(strcmp(
        dsu_status_name(DSU_FULL),
        "DSU_FULL"
    ) == 0);
    REQUIRE(strcmp(
        undirected_edge_list_status_name(
            UNDIRECTED_EDGE_LIST_INVALID_GRAPH
        ),
        "UNDIRECTED_EDGE_LIST_INVALID_GRAPH"
    ) == 0);
    REQUIRE(strcmp(
        linked_list_status_name((LinkedListStatus)99),
        "LINKED_LIST_UNKNOWN_STATUS"
    ) == 0);
    REQUIRE(strcmp(
        dsu_status_name((DsuStatus)99),
        "DSU_UNKNOWN_STATUS"
    ) == 0);
    REQUIRE(strcmp(
        undirected_edge_list_status_name(
            (UndirectedEdgeListStatus)99
        ),
        "UNDIRECTED_EDGE_LIST_UNKNOWN_STATUS"
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
        test_list_duplicates_hook_order_and_boundaries,
        "list duplicates, full-before-allocation, and boundaries"
    );
    failures += run_test(
        test_list_diagnostic_rejects_bad_shapes,
        "list diagnostic rejects cycles and size mismatches"
    );
    failures += run_test(
        test_dsu_equal_size_full_and_sentinels,
        "DSU equal-size tie, full state, and sentinels"
    );
    failures += run_test(
        test_dsu_malformed_second_path_is_atomic,
        "DSU malformed second path is atomic"
    );
    failures += run_test(
        test_dsu_large_size_and_invalid_id_preservation,
        "DSU malformed size and invalid-ID preservation"
    );
    failures += run_test(
        test_edge_malformed_mirrors_preserve_output,
        "edge malformed mirrors and preserved output"
    );
    failures += run_test(
        test_edge_list_sort_validation_and_total_order,
        "edge-list validation and relational total order"
    );
    failures += run_test(
        test_argument_rejection_and_status_names,
        "argument rejection and status-name coverage"
    );

    if (failures != 0) {
        (void)fprintf(
            stderr,
            "%d extension test(s) failed.\n",
            failures
        );
        return 1;
    }

    puts("All Module 13 extension tests passed.");
    return 0;
}
