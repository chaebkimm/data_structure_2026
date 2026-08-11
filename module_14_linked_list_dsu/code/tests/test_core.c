#include "dsu.h"
#include "linked_list.h"
#include "undirected_edge_list.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

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

static bool take_list_snapshot(
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

static bool list_matches_snapshot(
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
        size_t created = DSU_NO_ELEMENT;

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
    graph.logical_edge_count = 5U;
    graph.incident_count = 10U;

    graph.incidents[0] = (UndirectedIncidentRecord){
        3U, 2U, INT64_C(5), 4U
    };
    graph.incidents[1] = (UndirectedIncidentRecord){
        1U, 0U, INT64_C(1), 0U
    };
    graph.incidents[2] = (UndirectedIncidentRecord){
        0U, 2U, INT64_C(3), 2U
    };
    graph.incidents[3] = (UndirectedIncidentRecord){
        0U, 1U, INT64_C(4), 1U
    };
    graph.incidents[4] = (UndirectedIncidentRecord){
        1U, 2U, INT64_C(2), 3U
    };
    graph.incidents[5] = (UndirectedIncidentRecord){
        0U, 1U, INT64_C(1), 0U
    };
    graph.incidents[6] = (UndirectedIncidentRecord){
        1U, 0U, INT64_C(4), 1U
    };
    graph.incidents[7] = (UndirectedIncidentRecord){
        2U, 1U, INT64_C(2), 3U
    };
    graph.incidents[8] = (UndirectedIncidentRecord){
        2U, 3U, INT64_C(5), 4U
    };
    graph.incidents[9] = (UndirectedIncidentRecord){
        2U, 0U, INT64_C(3), 2U
    };

    return graph;
}

static bool test_list_canonical_ownership_and_deletion(void)
{
    LinkedList list = {0};
    ListSnapshot absent_snapshot;
    size_t baseline = linked_list_test_live_node_count();
    int value = 812;
    bool removed = false;

    REQUIRE(linked_list_init(NULL, 4U) ==
        LINKED_LIST_INVALID_ARGUMENT);
    REQUIRE(linked_list_init(&list, 4U) == LINKED_LIST_OK);
    active_list = &list;
    REQUIRE(linked_list_is_valid(&list));
    REQUIRE(linked_list_get(&list, 0U, &value) ==
        LINKED_LIST_OUT_OF_RANGE);
    REQUIRE(value == 812);

    REQUIRE(linked_list_push_front(&list, 31) == LINKED_LIST_OK);
    REQUIRE(linked_list_push_front(&list, 23) == LINKED_LIST_OK);
    REQUIRE(linked_list_push_front(&list, 17) == LINKED_LIST_OK);
    REQUIRE(linked_list_test_live_node_count() == baseline + 3U);
    REQUIRE(list.size == 3U);
    REQUIRE(list.head != NULL && list.head->value == 17);
    REQUIRE(list.head->next != NULL &&
        list.head->next->value == 23);
    REQUIRE(list.head->next->next != NULL &&
        list.head->next->next->value == 31);
    REQUIRE(list.head->next->next->next == NULL);

    REQUIRE(linked_list_get(&list, 0U, &value) ==
        LINKED_LIST_OK);
    REQUIRE(value == 17);
    REQUIRE(linked_list_get(&list, 2U, &value) ==
        LINKED_LIST_OK);
    REQUIRE(value == 31);

    REQUIRE(linked_list_remove_first(&list, 23, &removed) ==
        LINKED_LIST_OK);
    REQUIRE(removed);
    REQUIRE(list.size == 2U);
    REQUIRE(list.head->value == 17);
    REQUIRE(list.head->next != NULL &&
        list.head->next->value == 31);
    REQUIRE(list.head->next->next == NULL);
    REQUIRE(linked_list_test_live_node_count() == baseline + 2U);

    REQUIRE(take_list_snapshot(&list, &absent_snapshot));
    removed = true;
    REQUIRE(linked_list_remove_first(&list, 99, &removed) ==
        LINKED_LIST_OK);
    REQUIRE(!removed);
    REQUIRE(list_matches_snapshot(&list, &absent_snapshot));

    linked_list_destroy(&list);
    active_list = NULL;
    REQUIRE(list.head == NULL && list.size == 0U &&
        list.limit == 0U);
    REQUIRE(linked_list_is_valid(&list));
    REQUIRE(linked_list_test_live_node_count() == baseline);
    linked_list_destroy(&list);
    linked_list_destroy(NULL);
    REQUIRE(linked_list_test_live_node_count() == baseline);
    return true;
}

static bool test_list_limits_and_allocation_preservation(void)
{
    LinkedList list = {0};
    LinkedList zero_before = list;
    ListSnapshot before_failure;
    ListSnapshot before_full;
    size_t baseline = linked_list_test_live_node_count();
    bool removed = false;

    REQUIRE(linked_list_init(
        &list,
        (size_t)LINKED_LIST_MAX_NODES + 1U
    ) == LINKED_LIST_OUT_OF_RANGE);
    REQUIRE(list.head == zero_before.head &&
        list.size == zero_before.size &&
        list.limit == zero_before.limit);

    REQUIRE(linked_list_init(&list, 4U) == LINKED_LIST_OK);
    active_list = &list;
    REQUIRE(linked_list_push_front(&list, 31) == LINKED_LIST_OK);
    REQUIRE(linked_list_push_front(&list, 23) == LINKED_LIST_OK);
    REQUIRE(linked_list_push_front(&list, 17) == LINKED_LIST_OK);
    REQUIRE(take_list_snapshot(&list, &before_failure));

    linked_list_test_fail_next_allocation();
    REQUIRE(linked_list_push_front(&list, 9) ==
        LINKED_LIST_ALLOCATION);
    REQUIRE(list_matches_snapshot(&list, &before_failure));
    REQUIRE(linked_list_test_live_node_count() == baseline + 3U);

    REQUIRE(linked_list_push_front(&list, 9) == LINKED_LIST_OK);
    REQUIRE(list.size == 4U);
    REQUIRE(take_list_snapshot(&list, &before_full));

    linked_list_test_fail_next_allocation();
    REQUIRE(linked_list_push_front(&list, 5) == LINKED_LIST_FULL);
    REQUIRE(list_matches_snapshot(&list, &before_full));

    REQUIRE(linked_list_remove_first(&list, 9, &removed) ==
        LINKED_LIST_OK);
    REQUIRE(removed);
    REQUIRE(linked_list_push_front(&list, 5) ==
        LINKED_LIST_ALLOCATION);
    REQUIRE(linked_list_push_front(&list, 5) == LINKED_LIST_OK);

    linked_list_destroy(&list);
    active_list = NULL;
    REQUIRE(linked_list_test_live_node_count() == baseline);
    return true;
}

static bool test_dsu_canonical_size_and_compression(void)
{
    static const size_t before_parent[8] = {
        0U, 0U, 0U, 2U, 0U, 4U, 4U, 6U
    };
    static const size_t after_find_parent[8] = {
        0U, 0U, 0U, 2U, 0U, 4U, 0U, 0U
    };
    static const size_t final_parent[8] = {
        0U, 0U, 0U, 0U, 0U, 4U, 0U, 0U
    };
    Dsu sets;
    size_t root = DSU_NO_ELEMENT;
    size_t index;
    bool merged = true;

    REQUIRE(dsu_init(&sets) == DSU_OK);
    REQUIRE(dsu_is_valid(&sets));
    REQUIRE(make_elements(&sets, 8U));

    REQUIRE(merge_pair(&sets, 0U, 1U));
    REQUIRE(merge_pair(&sets, 2U, 3U));
    REQUIRE(merge_pair(&sets, 0U, 2U));
    REQUIRE(merge_pair(&sets, 4U, 5U));
    REQUIRE(merge_pair(&sets, 6U, 7U));
    REQUIRE(merge_pair(&sets, 4U, 6U));
    REQUIRE(merge_pair(&sets, 0U, 4U));

    REQUIRE(sets.element_count == 8U);
    REQUIRE(sets.component_count == 1U);
    REQUIRE(sets.component_size[0] == 8U);
    for (index = 0U; index < 8U; ++index) {
        REQUIRE(sets.parent[index] == before_parent[index]);
        if (index != 0U) {
            REQUIRE(sets.component_size[index] == 0U);
        }
    }
    REQUIRE(dsu_is_valid(&sets));

    REQUIRE(dsu_find(&sets, 7U, &root) == DSU_OK);
    REQUIRE(root == 0U);
    for (index = 0U; index < 8U; ++index) {
        REQUIRE(sets.parent[index] == after_find_parent[index]);
    }

    REQUIRE(dsu_union(&sets, 3U, 7U, &merged) == DSU_OK);
    REQUIRE(!merged);
    for (index = 0U; index < 8U; ++index) {
        REQUIRE(sets.parent[index] == final_parent[index]);
    }
    REQUIRE(sets.component_size[0] == 8U);
    REQUIRE(sets.component_count == 1U);
    REQUIRE(dsu_is_valid(&sets));
    return true;
}

static bool test_dsu_relationships_and_failure_preservation(void)
{
    static const size_t stream[][2] = {
        {0U, 1U},
        {1U, 2U},
        {3U, 4U},
        {2U, 4U},
        {0U, 4U},
        {5U, 5U}
    };
    static const bool expected_cycle[] = {
        false, false, false, false, true, true
    };
    Dsu sets;
    Dsu before;
    size_t index;
    size_t root = 99U;
    bool answer = false;

    REQUIRE(dsu_init(&sets) == DSU_OK);
    REQUIRE(make_elements(&sets, 6U));

    for (index = 0U;
         index < sizeof stream / sizeof stream[0];
         ++index) {
        bool cycle = !expected_cycle[index];

        REQUIRE(dsu_add_connection(
            &sets,
            stream[index][0],
            stream[index][1],
            &cycle
        ) == DSU_OK);
        REQUIRE(cycle == expected_cycle[index]);
    }

    REQUIRE(sets.component_count == 2U);
    REQUIRE(dsu_connected(&sets, 0U, 3U, &answer) == DSU_OK);
    REQUIRE(answer);
    REQUIRE(dsu_connected(&sets, 0U, 5U, &answer) == DSU_OK);
    REQUIRE(!answer);
    REQUIRE(dsu_is_valid(&sets));

    before = sets;
    REQUIRE(dsu_find(&sets, 6U, &root) == DSU_OUT_OF_RANGE);
    REQUIRE(root == 99U);
    REQUIRE(
        sets.element_count == before.element_count &&
        sets.component_count == before.component_count
    );
    for (index = 0U; index < (size_t)DSU_MAX_ELEMENTS; ++index) {
        REQUIRE(sets.parent[index] == before.parent[index]);
        REQUIRE(
            sets.component_size[index] ==
            before.component_size[index]
        );
    }
    return true;
}

static bool test_edge_builder_parallel_and_sort(void)
{
    static const size_t sorted_ids[5] = {
        0U, 3U, 2U, 1U, 4U
    };
    UndirectedIncidentGraph graph = canonical_incident_graph();
    UndirectedIncidentGraph self_loop_graph = {0};
    UndirectedEdgeList list;
    UndirectedEdgeList self_loop_list;
    UndirectedEdge low = {0U, 3U, INT64_MIN, 5U};
    UndirectedEdge high = {2U, 3U, INT64_MAX, 4U};
    size_t index;

    REQUIRE(undirected_incident_graph_validate(&graph) ==
        UNDIRECTED_EDGE_LIST_OK);
    REQUIRE(undirected_edge_list_build(&graph, &list) ==
        UNDIRECTED_EDGE_LIST_OK);
    REQUIRE(list.size == 5U);
    REQUIRE(undirected_edge_list_validate(&list) ==
        UNDIRECTED_EDGE_LIST_OK);

    for (index = 0U; index < list.size; ++index) {
        REQUIRE(list.edges[index].edge_id == index);
        REQUIRE(list.edges[index].u <= list.edges[index].v);
    }
    REQUIRE(list.edges[0].u == 0U && list.edges[0].v == 1U &&
        list.edges[0].weight == INT64_C(1));
    REQUIRE(list.edges[1].u == 0U && list.edges[1].v == 1U &&
        list.edges[1].weight == INT64_C(4));

    REQUIRE(undirected_edge_list_sort(&list) ==
        UNDIRECTED_EDGE_LIST_OK);
    for (index = 0U; index < list.size; ++index) {
        REQUIRE(list.edges[index].edge_id == sorted_ids[index]);
    }
    REQUIRE(undirected_edge_list_validate(&list) ==
        UNDIRECTED_EDGE_LIST_OK);

    self_loop_graph.vertex_count = 1U;
    self_loop_graph.logical_edge_count = 1U;
    self_loop_graph.incident_count = 2U;
    self_loop_graph.incidents[0] = (UndirectedIncidentRecord){
        0U, 0U, -INT64_C(7), 0U
    };
    self_loop_graph.incidents[1] = (UndirectedIncidentRecord){
        0U, 0U, -INT64_C(7), 0U
    };
    REQUIRE(undirected_edge_list_build(
        &self_loop_graph,
        &self_loop_list
    ) == UNDIRECTED_EDGE_LIST_OK);
    REQUIRE(self_loop_list.size == 1U);
    REQUIRE(self_loop_list.edges[0].u == 0U);
    REQUIRE(self_loop_list.edges[0].v == 0U);
    REQUIRE(self_loop_list.edges[0].weight == -INT64_C(7));
    REQUIRE(undirected_edge_compare(&low, &high) < 0);
    REQUIRE(undirected_edge_compare(&high, &low) > 0);
    return true;
}

static bool test_public_status_boundaries(void)
{
    LinkedNode stack_node = {7, NULL};
    LinkedList malformed_list = {&stack_node, 0U, 1U};
    Dsu sets;
    Dsu before;
    UndirectedIncidentGraph graph = {0};
    UndirectedEdgeList bad_list = {0};
    size_t created = 707U;
    size_t root = 808U;
    size_t index;

    REQUIRE(linked_list_push_front(NULL, 1) ==
        LINKED_LIST_INVALID_ARGUMENT);
    REQUIRE(linked_list_push_front(&malformed_list, 1) ==
        LINKED_LIST_INVALID_STATE);

    REQUIRE(dsu_init(NULL) == DSU_INVALID_ARGUMENT);
    REQUIRE(dsu_init(&sets) == DSU_OK);
    REQUIRE(make_elements(&sets, (size_t)DSU_MAX_ELEMENTS));
    before = sets;
    REQUIRE(dsu_make_set(&sets, &created) == DSU_FULL);
    REQUIRE(created == 707U);
    for (index = 0U; index < (size_t)DSU_MAX_ELEMENTS; ++index) {
        REQUIRE(sets.parent[index] == before.parent[index]);
        REQUIRE(
            sets.component_size[index] ==
            before.component_size[index]
        );
    }

    REQUIRE(dsu_init(&sets) == DSU_OK);
    REQUIRE(dsu_make_set(&sets, &created) == DSU_OK);
    sets.parent[0] = DSU_NO_ELEMENT;
    before = sets;
    REQUIRE(dsu_find(&sets, 0U, &root) == DSU_INVALID_STATE);
    REQUIRE(root == 808U);
    REQUIRE(sets.parent[0] == before.parent[0]);
    REQUIRE(sets.component_size[0] == before.component_size[0]);

    REQUIRE(undirected_incident_graph_validate(NULL) ==
        UNDIRECTED_EDGE_LIST_INVALID_ARGUMENT);
    graph.vertex_count =
        (size_t)UNDIRECTED_EDGE_LIST_MAX_VERTICES + 1U;
    REQUIRE(undirected_incident_graph_validate(&graph) ==
        UNDIRECTED_EDGE_LIST_LIMIT);

    graph = (UndirectedIncidentGraph){0};
    graph.vertex_count = 1U;
    graph.logical_edge_count = 1U;
    graph.incident_count = 2U;
    graph.incidents[0] = (UndirectedIncidentRecord){
        0U, 1U, INT64_C(1), 0U
    };
    graph.incidents[1] = (UndirectedIncidentRecord){
        1U, 0U, INT64_C(1), 0U
    };
    REQUIRE(undirected_incident_graph_validate(&graph) ==
        UNDIRECTED_EDGE_LIST_OUT_OF_RANGE);

    graph = (UndirectedIncidentGraph){0};
    graph.vertex_count = 2U;
    graph.logical_edge_count = 1U;
    graph.incident_count = 2U;
    graph.incidents[0] = (UndirectedIncidentRecord){
        0U, 1U, INT64_C(1), 0U
    };
    graph.incidents[1] = (UndirectedIncidentRecord){
        0U, 1U, INT64_C(1), 0U
    };
    REQUIRE(undirected_incident_graph_validate(&graph) ==
        UNDIRECTED_EDGE_LIST_INVALID_GRAPH);

    bad_list.size = 1U;
    bad_list.edges[0] = (UndirectedEdge){
        1U, 0U, INT64_C(1), 0U
    };
    REQUIRE(undirected_edge_list_validate(&bad_list) ==
        UNDIRECTED_EDGE_LIST_INVALID_LIST);
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
        test_list_canonical_ownership_and_deletion,
        "linked-list canonical ownership and deletion"
    );
    failures += run_test(
        test_list_limits_and_allocation_preservation,
        "linked-list limits and allocation preservation"
    );
    failures += run_test(
        test_dsu_canonical_size_and_compression,
        "DSU union-by-size and two-pass compression"
    );
    failures += run_test(
        test_dsu_relationships_and_failure_preservation,
        "DSU relationships, cycles, and bounds"
    );
    failures += run_test(
        test_edge_builder_parallel_and_sort,
        "edge-list mirror, parallel edge, and qsort order"
    );
    failures += run_test(
        test_public_status_boundaries,
        "public invalid, full, range, limit, and state statuses"
    );

    if (failures != 0) {
        (void)fprintf(stderr, "%d core test(s) failed.\n", failures);
        return 1;
    }

    puts("All Module 14 core tests passed.");
    return 0;
}
