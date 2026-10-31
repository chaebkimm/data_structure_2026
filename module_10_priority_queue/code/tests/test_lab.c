#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "lab.c"

/* Include the actual teaching source once. Do not link another lab.c object. */
static void check_live_heap(void)
{
    int seen[10] = {0};
    assert(size >= 0 && size <= 10);
    for (int i = 0; i < size; ++i) {
        int id = heap[i];
        assert(id >= 0 && id < 10);
        assert(!seen[id]);
        seen[id] = 1;
        assert(node_heap_pos[id] == i);
        assert(node_dist[id] >= 0);
        if (i > 0) {
            int p = (i - 1) / 2;
            assert(node_dist[heap[p]] <= node_dist[id]);
        }
    }
    /* Removed IDs' entries may be stale; the inverse map covers live IDs only. */
}

static void reset_heap(void)
{
    init_heap();
    assert(size == 0);
    for (int id = 0; id < 10; ++id) {
        assert(node_heap_pos[id] == -1);
        node_dist[id] = -1;
    }
    assert(left(0) == -1 && right(0) == -1);
    assert(heap_parent(0) == -1);
}

static void test_insert_and_remove(void)
{
    const int ids[] = {8, 3, 6, 1, 9, 4};
    const int costs[] = {70, 30, 50, 10, 90, 40};
    const int expected_heap[] = {1, 3, 4, 8, 9, 6};
    const int expected_order[] = {1, 3, 4, 6, 8, 9};
    reset_heap();
    for (int i = 0; i < 6; ++i) {
        add_node(ids[i], costs[i]);
        check_live_heap();
    }
    for (int i = 0; i < 6; ++i) {
        assert(heap[i] == expected_heap[i]);
    }
    assert(comp(0, 1));           /* Keys 10 and 30, not IDs or positions. */
    assert(!comp(1, 0));
    assert(!comp(2, 2));
    for (int i = 0; i < 6; ++i) {
        assert(size > 0);
        assert(remove_root() == expected_order[i]);
        check_live_heap();
    }
    assert(size == 0);
}

static void test_heap_boundaries_and_ties(void)
{
    reset_heap();
    add_node(7, 10);
    assert(remove_root() == 7 && size == 0);
    check_live_heap();

    /* Three nodes become a parent with one left child after removal. */
    add_node(7, 10);
    add_node(2, 20);
    add_node(9, 30);
    assert(remove_root() == 7);
    assert(size == 2 && heap[0] == 2 && heap[1] == 9);
    check_live_heap();

    reset_heap();
    for (int id = 9; id >= 0; --id) {
        add_node(id, id + 1);
        check_live_heap();
    }
    assert(size == 10);
    for (int id = 0; id < 10; ++id) {
        assert(remove_root() == id);
        check_live_heap();
    }

    reset_heap();
    const int equal_ids[] = {4, 0, 9, 2, 1};
    int seen[10] = {0};
    for (int i = 0; i < 5; ++i) {
        add_node(equal_ids[i], 12);
        check_live_heap();
    }
    while (size > 0) {
        int id = remove_root();
        assert(node_dist[id] == 12 && !seen[id]);
        seen[id] = 1;
        check_live_heap();
    }
    for (int i = 0; i < 5; ++i) {
        assert(seen[equal_ids[i]]);
    }
    /* Equal priorities need heap order, not an arrival-order guarantee. */
}

static void test_update_both_directions(void)
{
    const int ids[] = {8, 2, 5, 1, 7, 6, 3};
    reset_heap();
    for (int i = 0; i < 7; ++i) {
        add_node(ids[i], 10 * (i + 1));
    }
    update_value(3, 5);            /* Leaf to root. */
    assert(heap[0] == 3);
    check_live_heap();
    update_value(3, 100);          /* Root down through two levels. */
    assert(heap[0] == 8);
    check_live_heap();
    update_value(2, 90);           /* Increase an interior key. */
    check_live_heap();
    update_value(7, 1);
    assert(heap[0] == 7);
    check_live_heap();
    int previous = -1;
    while (size > 0) {
        int id = remove_root();
        assert(node_dist[id] >= previous);
        previous = node_dist[id];
        check_live_heap();
    }
}

static void reset_graph(int count)
{
    assert(count >= 1 && count <= 10);
    alphabet_nodes_init();
    nodes_size = count;
    for (int u = 0; u < 10; ++u) {
        for (int v = 0; v < 10; ++v) {
            edge_length[u][v] = 0;
        }
    }
}

static void add_arc(int u, int v, int weight)
{
    assert(u >= 0 && u < nodes_size && v >= 0 && v < nodes_size);
    assert(u != v && weight > 0);
    assert(nodes[u].adj_size < 10 && edge_length[u][v] == 0);
    nodes[u].adj_list[nodes[u].adj_size++] = v;
    edge_length[u][v] = weight;
}

/* Independent repeated-relaxation oracle over the matrix, not a heap or
   the adjacency-list run loop. Test weights and path sums are small. */
static void reference_distances(int source, int expected[10])
{
    for (int i = 0; i < 10; ++i) {
        expected[i] = -1;
    }
    expected[source] = 0;
    for (int pass = 0; pass < nodes_size - 1; ++pass) {
        for (int u = 0; u < nodes_size; ++u) {
            if (expected[u] == -1) {
                continue;
            }
            for (int v = 0; v < nodes_size; ++v) {
                if (edge_length[u][v] > 0) {
                    int candidate = expected[u] + edge_length[u][v];
                    if (expected[v] == -1 || candidate < expected[v]) {
                        expected[v] = candidate;
                    }
                }
            }
        }
    }
}

static void check_shortest_paths(int source)
{
    int expected[10];
    reference_distances(source, expected);
    min_dist(source);
    assert(size == 0);
    for (int i = 0; i < 10; ++i) {
        assert(node_dist[i] == expected[i]);
        assert(found[i] == (expected[i] != -1));
    }
}

static void test_canonical_and_repeated_runs(void)
{
    const int expected[] = {0, 5, 2, 4, 6, -1};
    reset_graph(6);
    add_arc(0, 1, 9);
    add_arc(0, 2, 2);
    add_arc(0, 4, 14);
    add_arc(1, 3, 1);
    add_arc(1, 4, 8);
    add_arc(2, 1, 3);
    add_arc(2, 3, 2);
    add_arc(3, 4, 2);
    check_shortest_paths(0);
    for (int i = 0; i < 6; ++i) {
        assert(node_dist[i] == expected[i]);
    }
    check_shortest_paths(2);
    check_shortest_paths(5);
    check_shortest_paths(0);
    /* init_dist must also reset a previously nonempty heap. */
    add_node(9, 1);
    check_shortest_paths(0);
}

static void test_isolated_and_undirected_graphs(void)
{
    reset_graph(1);
    check_shortest_paths(0);
    reset_graph(10);
    for (int source = 0; source < 10; ++source) {
        check_shortest_paths(source);
    }
    /* Undirected connections are two explicit adjacency entries. */
    reset_graph(4);
    add_arc(0, 1, 4);
    add_arc(1, 0, 4);
    add_arc(1, 2, 2);
    add_arc(2, 1, 2);
    add_arc(0, 2, 9);
    add_arc(2, 0, 9);
    for (int source = 0; source < 4; ++source) {
        check_shortest_paths(source);
    }
}

static uint32_t next_random(uint32_t *state)
{
    *state = *state * UINT32_C(1664525) + UINT32_C(1013904223);
    return *state;
}

static void test_reference_graphs(void)
{
    uint32_t random_state = UINT32_C(2026);
    for (int trial = 0; trial < 80; ++trial) {
        int count = 2 + trial % 9;
        reset_graph(count);
        for (int u = 0; u < count; ++u) {
            for (int v = 0; v < count; ++v) {
                if (u != v && (next_random(&random_state) >> 16) % UINT32_C(4) == 0) {
                    int weight = 1 + (int)(next_random(&random_state) % UINT32_C(20));
                    add_arc(u, v, weight);
                }
            }
        }
        check_shortest_paths(0);
        check_shortest_paths(count - 1);
        check_shortest_paths(trial % count);
    }
}

int main(void)
{
    test_insert_and_remove();
    test_heap_boundaries_and_ties();
    test_update_both_directions();
    test_canonical_and_repeated_runs();
    test_isolated_and_undirected_graphs();
    test_reference_graphs();
    puts("Module 11 lab core tests passed (heap invariants and 80 reference graphs).");
    return 0;
}
