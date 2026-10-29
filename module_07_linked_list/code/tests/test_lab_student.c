#include "lab_test_support.h"

int main(void)
{
    /* Smoke case. Add the three original groups required by student/lab.md. */
    expect_clean_lab();
    int first = allocate_value(17);
    int second = allocate_value(23);
    simple_link_lnode_to_prev(first, second);
    CHECK(lnodes[first].data == 17 && lnodes[first].next == second);
    int removed = simple_delink_next_lnode_from_prev(first);
    CHECK(removed == second && lnodes[first].next == -1);
    CHECK(lnodes[removed].next == -1);
    free_lnode(removed);
    free_lnode(first);
    expect_clean_lab();

    int node = allocate_value(31);
    enqueue_lnode(node);
    CHECK(qhead == node && qtail == node && !is_empty_queue());
    removed = dequeue_lnode();
    CHECK(removed == node && lnodes[removed].data == 31);
    CHECK(lnodes[removed].next == -1 && is_empty_queue());
    CHECK(qhead == -1 && qtail == -1);
    free_lnode(removed);
    expect_clean_lab();
    puts("Week 7 student smoke test passed; add three original linked-list groups.");
    return 0;
}
