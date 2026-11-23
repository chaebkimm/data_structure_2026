#include "lab_test_support.h"

/* Supplied smoke checks. Add original assertions in these three groups;
   explain a claim and independently predict its expected state first. */
static void test_1_rotations(void)
{
    const int order[] = {2, 0, 1};
    int root = build_lab_order(order, 3, 1);
    assert(root == 1 && nodes[1].left == 0 && nodes[1].right == 2);
    assert_lab_tree(root, 3);
    /* Extend with a different case and a nonempty transferred subtree. */
}

static void test_2_measurements(void)
{
    const int order[] = {0, 1, 2, 3, 4, 5, 6};
    int root = build_lab_order(order, 7, 0);
    assert(assert_lab_shape(root, 7, 0) == 6);
    root = build_lab_order(order, 7, 1);
    assert(root == 3 && height[root] == 2);
    int found;
    assert(search_comparisons(root, 'H', &found) == 3 && !found);
    /* Extend with descending/mixed orders and an independent search trace. */
}

static void test_3_duplicates_and_boundaries(void)
{
    reset_lab();
    int root = -1;
    for (int id = 0; id < 3; ++id) {
        nodes[id].data = 'Q';
        root = insert_lab(root, id);
        assert_lab_tree(root, id + 1);
    }
    assert(nodes[root].right != -1);
    assert(nodes[nodes[root].right].data == nodes[root].data);
    /* Extend through ten fresh IDs and test a reset/rebuild. Do not call
       _add with an invalid ID, a linked ID, or a full pool's eleventh ID. */
}

int main(void)
{
    test_1_rotations();
    test_2_measurements();
    test_3_duplicates_and_boundaries();
    puts("Module 12 student smoke checks passed; add original evidence.");
    return 0;
}
