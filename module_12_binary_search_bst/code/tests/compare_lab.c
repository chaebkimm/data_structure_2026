#include "lab_test_support.h"

int main(void)
{
    const int orders[3][7] = {
        {0, 1, 2, 3, 4, 5, 6}, {6, 5, 4, 3, 2, 1, 0},
        {3, 1, 5, 0, 2, 4, 6}
    };
    const char *names[] = {"ascending", "descending", "mixed"};
    const char present[] = {'G', 'A', 'G'};
    const char missing[] = {'H', '@', 'H'};
    puts("order       tree root height present/comparisons missing/comparisons");
    for (int case_id = 0; case_id < 3; ++case_id) {
        for (int avl = 0; avl <= 1; ++avl) {
            int root = build_lab_order(orders[case_id], 7, avl);
            int actual = assert_lab_shape(root, 7, avl);
            int found;
            int hit = search_comparisons(root, present[case_id], &found);
            assert(found);
            int miss = search_comparisons(root, missing[case_id], &found);
            assert(!found);
            int expected_height = avl || case_id == 2 ? 2 : 6;
            int expected_count = avl || case_id == 2 ? 3 : 7;
            assert(actual == expected_height);
            assert(hit == expected_count && miss == expected_count);
            if (avl) assert(root == 3);
            printf("%-11s %-4s %c    %d      %c/%d                 %c/%d\n",
                   names[case_id], avl ? "AVL" : "BST", nodes[root].data,
                   actual, present[case_id], hit, missing[case_id], miss);
        }
    }
    puts("Counts are driver measurements; lab.c exports no search counters.");
    return 0;
}
