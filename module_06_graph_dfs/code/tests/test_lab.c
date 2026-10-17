/*
 * Exercise the current array lab under its valid-input assumptions.
 * Each case clears globals to model a fresh one-call program. The supplied
 * wrappers do not clear BCC results, validate roots, or guard stack capacity.
 * Compile this file alone with the repository root on the include path.
 */
#include <stdio.h>
#include <string.h>

#include "../../student/lab.c"

#define CHECK(condition) do { \
    if (!(condition)) { \
        printf("  line %d: %s\n", __LINE__, #condition); \
        return 0; \
    } \
} while (0)

static void fresh_graph(int count)
{
    (void)memset(nodes, 0, sizeof nodes);
    (void)memset(visit_num, 0, sizeof visit_num);
    (void)memset(parent, 0, sizeof parent);
    (void)memset(back_num, 0, sizeof back_num);
    (void)memset(edges, 0, sizeof edges);
    (void)memset(edge_index, 0, sizeof edge_index);
    (void)memset(bcc, 0, sizeof bcc);
    (void)memset(bcc_size, 0, sizeof bcc_size);
    nodes_size = count;
    visit_time = 0;
    edges_size = 0;
    current_bcc = 0;
    top = -1;
    for (int i = 0; i < count; ++i) {
        nodes[i].data = (char)('A' + i);
    }
}

static void connect_nodes(int u, int v)
{
    nodes[u].adj_list[nodes[u].adj_size++] = v;
    nodes[v].adj_list[nodes[v].adj_size++] = u;
}

static void run_lab(int root)
{
    init_edges_list(root);
    find_bcc(root);
}

/* Every stored edge belongs to exactly one active row, and both endpoint
 * orders look up that edge. This checks the result independently of pop order.
 */
static int check_partition(void)
{
    int seen[45] = {0};
    CHECK(top == -1);
    CHECK(current_bcc >= 0 && current_bcc <= 9);
    CHECK(edges_size >= 0 && edges_size <= 45);
    for (int row = 0; row < current_bcc; ++row) {
        CHECK(bcc_size[row] > 0 && bcc_size[row] <= 45);
        for (int pos = 0; pos < bcc_size[row]; ++pos) {
            int edge = bcc[row][pos];
            CHECK(edge >= 0 && edge < edges_size);
            CHECK(++seen[edge] == 1);
        }
    }
    for (int edge = 0; edge < edges_size; ++edge) {
        int u = edges[edge].from, v = edges[edge].to;
        CHECK(seen[edge] == 1);
        CHECK(edge_index[u][v] == edge && edge_index[v][u] == edge);
    }
    return 1;
}

static int supplied_alphabet_graph(void)
{
    const int expected_edges[8][2] = {
        {0, 1}, {1, 2}, {1, 3}, {3, 4},
        {4, 1}, {4, 5}, {5, 1}, {5, 3}
    };
    const int expected_parent[6] = {-1, 0, 1, 1, 3, 4};
    const int expected_low[6] = {1, 2, 3, 2, 2, 2};
    const int expected_rows[3][6] = {{1}, {7, 6, 5, 4, 3, 2}, {0}};
    const int expected_sizes[3] = {1, 6, 1};
    fresh_graph(10);
    alphabet_nodes_init();
    edges_init();
    run_lab(0);
    CHECK(edges_size == 8 && current_bcc == 3 && visit_time == 6);
    for (int i = 0; i < 6; ++i) {
        CHECK(visit_num[i] == i + 1);
        CHECK(parent[i] == expected_parent[i] && back_num[i] == expected_low[i]);
    }
    for (int i = 6; i < nodes_size; ++i) {
        CHECK(visit_num[i] == 0 && parent[i] == -1);
    }
    CHECK(edge_index[6][7] == -1 && edge_index[0][9] == -1);
    for (int i = 0; i < edges_size; ++i) {
        CHECK(edges[i].from == expected_edges[i][0]);
        CHECK(edges[i].to == expected_edges[i][1]);
    }
    for (int row = 0; row < current_bcc; ++row) {
        CHECK(bcc_size[row] == expected_sizes[row]);
        for (int i = 0; i < bcc_size[row]; ++i) {
            CHECK(bcc[row][i] == expected_rows[row][i]);
        }
    }
    return check_partition();
}

static int supplied_slide_graph(void)
{
    const int pairs[10][2] = {
        {0, 1}, {0, 2}, {1, 2}, {1, 6}, {2, 3},
        {2, 5}, {2, 6}, {3, 4}, {3, 5}, {4, 5}
    };
    const int expected_visit[7] = {1, 2, 3, 4, 5, 6, 7};
    const int expected_parent[7] = {-1, 0, 1, 2, 3, 4, 2};
    const int expected_low[7] = {1, 1, 1, 3, 3, 3, 2};
    const int expected_rows[2][5] = {{7, 6, 5, 4, 3}, {9, 8, 2, 1, 0}};
    fresh_graph(7);
    for (int i = 0; i < 10; ++i) {
        connect_nodes(pairs[i][0], pairs[i][1]);
    }
    run_lab(0);
    CHECK(edges_size == 10 && current_bcc == 2);
    for (int i = 0; i < nodes_size; ++i) {
        CHECK(visit_num[i] == expected_visit[i]);
        CHECK(parent[i] == expected_parent[i] && back_num[i] == expected_low[i]);
    }
    for (int row = 0; row < current_bcc; ++row) {
        CHECK(bcc_size[row] == 5);
        for (int pos = 0; pos < 5; ++pos) {
            CHECK(bcc[row][pos] == expected_rows[row][pos]);
        }
    }
    return check_partition();
}

static int isolated_vertex_and_ignored_loop(void)
{
    fresh_graph(1);
    connect_nodes(0, 0); /* The lab deliberately omits self-loop records. */
    run_lab(0);
    CHECK(visit_num[0] == 1 && parent[0] == -1 && back_num[0] == 1);
    CHECK(edges_size == 0 && current_bcc == 0 && edge_index[0][0] == -1);
    return check_partition();
}

static int one_bridge(void)
{
    fresh_graph(2);
    connect_nodes(0, 1);
    run_lab(0);
    CHECK(current_bcc == 1 && bcc_size[0] == 1 && bcc[0][0] == 0);
    CHECK(back_num[1] > visit_num[0]);
    return check_partition();
}

static int triangle_closes_on_equal_low(void)
{
    fresh_graph(3);
    connect_nodes(0, 1);
    connect_nodes(1, 2);
    connect_nodes(2, 0);
    run_lab(0);
    CHECK(back_num[1] == visit_num[0]);
    CHECK(back_num[2] < visit_num[1]);
    CHECK(current_bcc == 1 && bcc_size[0] == 3);
    CHECK(bcc[0][0] == 2 && bcc[0][1] == 1 && bcc[0][2] == 0);
    return check_partition();
}

static int root_with_multiple_children(void)
{
    fresh_graph(4);
    connect_nodes(0, 1);
    connect_nodes(0, 2);
    connect_nodes(0, 3);
    run_lab(0);
    CHECK(current_bcc == 3);
    for (int row = 0; row < current_bcc; ++row) {
        CHECK(bcc_size[row] == 1 && bcc[row][0] == row);
    }
    return check_partition();
}

static int ten_vertex_path_uses_nine_rows(void)
{
    fresh_graph(10);
    for (int i = 0; i < 9; ++i) {
        connect_nodes(i, i + 1);
    }
    run_lab(0);
    CHECK(edges_size == 9 && current_bcc == 9);
    for (int row = 0; row < current_bcc; ++row) {
        CHECK(bcc_size[row] == 1 && bcc[row][0] == 8 - row);
    }
    return check_partition();
}

static int complete_five_vertex_block_uses_ten_stack_slots(void)
{
    fresh_graph(5);
    for (int u = 0; u < 5; ++u) {
        for (int v = u + 1; v < 5; ++v) {
            connect_nodes(u, v);
        }
    }
    run_lab(0);
    CHECK(edges_size == 10 && current_bcc == 1 && bcc_size[0] == 10);
    for (int i = 0; i < 10; ++i) {
        CHECK(bcc[0][i] == 9 - i);
    }
    return check_partition();
}

static int more_records_than_stack_slots(void)
{
    /* Two K4 blocks share root 0. Each six-edge block is removed before
     * the next starts, so twelve records fit the unchanged ten-slot stack.
     */
    const int blocks[2][4] = {{0, 1, 2, 3}, {0, 4, 5, 6}};
    fresh_graph(7);
    for (int block = 0; block < 2; ++block) {
        for (int u = 0; u < 4; ++u) {
            for (int v = u + 1; v < 4; ++v) {
                connect_nodes(blocks[block][u], blocks[block][v]);
            }
        }
    }
    run_lab(0);
    CHECK(edges_size == 12 && current_bcc == 2);
    for (int row = 0; row < current_bcc; ++row) {
        CHECK(bcc_size[row] == 6);
        for (int pos = 0; pos < 6; ++pos) {
            CHECK(bcc[row][pos] == 6 * row + 5 - pos);
        }
    }
    return check_partition();
}

int main(void)
{
    const struct {
        const char *name;
        int (*run)(void);
    } tests[] = {
        {"alphabet graph records, low links, and pop order", supplied_alphabet_graph},
        {"slide graph retains pending parent edges", supplied_slide_graph},
        {"isolated vertex and omitted self-loop", isolated_vertex_and_ignored_loop},
        {"single bridge includes its boundary edge", one_bridge},
        {"equal low closes and smaller low continues", triangle_closes_on_equal_low},
        {"root closes each independent child block", root_with_multiple_children},
        {"ten-vertex path fills nine result rows", ten_vertex_path_uses_nine_rows},
        {"complete five-vertex block fills ten stack slots", complete_five_vertex_block_uses_ten_stack_slots},
        {"twelve records with at most six pending edges", more_records_than_stack_slots}
    };
    int failures = 0;
    for (size_t i = 0; i < sizeof tests / sizeof tests[0]; ++i) {
        int passed = tests[i].run();
        printf("%s %s\n", passed ? "PASS" : "FAIL", tests[i].name);
        if (!passed) ++failures;
    }
    printf("\n%zu lab test(s), %d failure(s)\n",
           sizeof tests / sizeof tests[0], failures);
    return failures == 0 ? 0 : 1;
}
