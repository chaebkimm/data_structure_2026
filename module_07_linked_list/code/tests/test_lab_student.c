#include "lab_test_support.h"

int main(void)
{
    /* Smoke case. Add three original groups required by student/lab.md. */
    reset_lab();
    int first = new_lnode(17, -1);
    int second = new_lnode(23, -1);
    assert(first != -1 && second != -1);
    link_lnode(first, second);
    assert(lnodes[first].data == 17 && lnodes[first].next == second);
    int removed = delete_next_lnode(first);
    assert(removed == second && lnodes[first].next == -1);
    free_lnode(removed);
    assert(free_head == second);
    /* The public queue accepts and returns values; it owns slot recycling. */
    reset_lab();
    bool added = enqueue(31);
    assert(added && head == tail && !is_empty_queue());
    int value = dequeue();
    assert(value == 31 && is_empty_queue() && head == -1 && tail == -1);
    puts("Week 7 student smoke test passed; add three original linked-list groups.");
    return 0;
}
