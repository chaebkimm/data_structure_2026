#include "lab_test_support.h"

static void test_empty_leaf_and_heights(void)
{
    reset_lab();
    assert_lab_tree(-1, 0);
    assert(get_height(-1) == -1);
    int root = insert_lab(-1, 7);
    assert(root == 7 && height[7] == 0);
    assert_lab_tree(root, 1);
    root = insert_lab(root, 3);
    assert(root == 7 && nodes[7].left == 3 && height[7] == 1);
    assert(get_balance(nodes[7].left, nodes[7].right) == 1);
    assert_lab_tree(root, 2);
}

static void test_four_cases(void)
{
    const int orders[4][3] = {
        {2, 1, 0}, {0, 1, 2}, {2, 0, 1}, {0, 2, 1}
    };
    for (int case_id = 0; case_id < 4; ++case_id) {
        int root = build_lab_order(orders[case_id], 3, 1);
        assert(root == 1 && nodes[root].data == 'B');
        assert(nodes[1].left == 0 && nodes[1].right == 2);
        assert(nodes[0].left == -1 && nodes[0].right == -1);
        assert(nodes[2].left == -1 && nodes[2].right == -1);
        assert(height[1] == 1 && height[0] == 0 && height[2] == 0);
    }
}

static void test_middle_subtrees(void)
{
    const int orders[6][6] = {
        {5, 3, 6, 1, 4, 0}, /* LL: E moves to F.left. */
        {1, 3, 0, 5, 2, 6}, /* RR: C moves to B.right. */
        {6, 2, 8, 0, 4, 3}, /* LR: D moves to C.right. */
        {6, 2, 8, 0, 4, 5}, /* LR: F moves to G.left. */
        {2, 0, 6, 4, 8, 5}, /* RL: F moves to G.left. */
        {2, 0, 6, 4, 8, 3}  /* RL: D moves to C.right. */
    };
    for (int case_id = 0; case_id < 6; ++case_id) {
        int root = build_lab_order(orders[case_id], 6, 1);
        assert(root == (case_id < 2 ? 3 : 4));
        if (case_id == 0) assert(nodes[5].left == 4);
        if (case_id == 1) assert(nodes[1].right == 2);
        if (case_id == 2 || case_id == 5) assert(nodes[2].right == 3);
        if (case_id == 3 || case_id == 4) assert(nodes[6].left == 5);
        assert_lab_tree(root, 6);
    }
}

static void test_duplicates_and_capacity(void)
{
    reset_lab();
    int root = -1;
    for (int id = 0; id < 10; ++id) {
        nodes[id].data = 'Q';
        root = insert_lab(root, id);
        assert_lab_tree(root, id + 1);
        if (id == 2) {
            assert(root == 1);
            assert(nodes[1].left == 2 && nodes[1].right == 0);
        }
    }
    /* Invalid or already linked IDs and an eleventh node are outside contract. */
    const int ascending[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const int descending[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    (void)build_lab_order(ascending, 10, 1);
    (void)build_lab_order(descending, 10, 1);
}

static void test_measurements(void)
{
    const int orders[3][7] = {
        {0, 1, 2, 3, 4, 5, 6}, {6, 5, 4, 3, 2, 1, 0},
        {3, 1, 5, 0, 2, 4, 6}
    };
    const char present[3] = {'G', 'A', 'G'};
    const char missing[3] = {'H', '@', 'H'};
    for (int case_id = 0; case_id < 3; ++case_id) {
        for (int avl = 0; avl <= 1; ++avl) {
            int root = build_lab_order(orders[case_id], 7, avl);
            int expected_height = avl || case_id == 2 ? 2 : 6;
            int expected_count = avl || case_id == 2 ? 3 : 7;
            assert(assert_lab_shape(root, 7, avl) == expected_height);
            if (avl) assert(root == 3);
            int found;
            assert(search_comparisons(root, present[case_id], &found) == expected_count);
            assert(found);
            assert(search_comparisons(root, missing[case_id], &found) == expected_count);
            assert(!found);
        }
    }
}

static int permutation_cases;

static void check_permutations(int *order, int pos)
{
    if (pos == 7) {
        (void)build_lab_order(order, 7, 1);
        ++permutation_cases;
        return;
    }
    for (int next = pos; next < 7; ++next) {
        int tmp = order[pos]; order[pos] = order[next]; order[next] = tmp;
        check_permutations(order, pos + 1);
        tmp = order[pos]; order[pos] = order[next]; order[next] = tmp;
    }
}

int main(void)
{
    test_empty_leaf_and_heights();
    test_four_cases();
    test_middle_subtrees();
    test_duplicates_and_capacity();
    test_measurements();
    int order[7] = {0, 1, 2, 3, 4, 5, 6};
    check_permutations(order, 0);
    assert(permutation_cases == 5040);
    puts("Module 12 core passed: four cases, transferred subtrees, duplicates,");
    puts("ten slots, measurements, and all 5,040 seven-key insertion orders.");
    return 0;
}
